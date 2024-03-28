// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <cmath>

#include "copasi/copasi.h"

#include "COptMethodPS.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "copasi/randomGenerator/CRandom.h"
#include "copasi/randomGenerator/CPermutation.h"
#include "copasi/utilities/CProcessReport.h"
#include "copasi/utilities/CSort.h"
#include "copasi/core/CDataObjectReference.h"

#ifdef _MSC_VER
#include <io.h>
#else
#include <unistd.h>
#endif

COptMethodPS::COptMethodPS(const CDataContainer * pParent,
                           const CTaskEnum::Method & methodType,
                           const CTaskEnum::Task & taskType)
  : COptPopulationMethod(pParent, methodType, taskType, true)
  , mVariance(0.0)
  , mVelocities()
  , mBestValue()
  , mBestValues()
  , mBestPositions()
  , mImprovements()
  , mpPermutation(NULL)
  , mInformants()
  , mNumInformedMin(0)
  , mNumInformed(0)
  , mBestIndex(0)
  , mStopAfterStalledIterations(0)
  , mContinue(true)
{
  assertParameter("Iteration Limit", CCopasiParameter::Type::UINT, (unsigned C_INT32) 2000);
  assertParameter("Swarm Size", CCopasiParameter::Type::UINT, (unsigned C_INT32) 50);
  assertParameter("Std. Deviation", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.0e-6);
  assertParameter("Random Number Generator", CCopasiParameter::Type::UINT, (unsigned C_INT32) CRandom::mt19937, eUserInterfaceFlag::editable);
  assertParameter("Seed", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);
  assertParameter("Stop after # Stalled Iterations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);

  initObjects();
}

COptMethodPS::COptMethodPS(const COptMethodPS & src,
                           const CDataContainer * pParent)
  : COptPopulationMethod(src, pParent)
  , mVariance(0.0)
  , mVelocities()
  , mBestValue()
  , mBestValues()
  , mBestPositions()
  , mImprovements()
  , mpPermutation(NULL)
  , mInformants()
  , mNumInformedMin(0)
  , mNumInformed(0)
  , mBestIndex(0)
  , mContinue(true)
{
  initObjects();
}

COptMethodPS::~COptMethodPS()
{
  cleanup();
}

// evaluate the fitness of one individual
C_FLOAT64 COptMethodPS::evaluate()
{
  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.
  COptProblem *& pOptProblem = mProblemContext.active();

  // evaluate the fitness
  if (!pOptProblem->calculate())
#pragma omp critical
    mContinue = false;

  C_FLOAT64 EvaluationValue;

  // check whether the functional constraints are fulfilled
  if (!pOptProblem->checkFunctionalConstraints())
    EvaluationValue = std::numeric_limits<C_FLOAT64>::infinity();
  else
    EvaluationValue = pOptProblem->getCalculateValue();

  if (mProblemContext.isThread(&pOptProblem))
    {
#pragma omp critical
      mProblemContext.master()->incrementCounters(pOptProblem->getCounters());

      pOptProblem->resetCounters();
    }

  return EvaluationValue;
}

// move an individual
bool COptMethodPS::move(const size_t & index)
{
  COptProblem *& pProblem = mProblemContext.active();
  CRandom * pRandom = mRandomContext.active();

  static const C_FLOAT64 w = 1 / (2 * log(2.0));
  static const C_FLOAT64 c = 0.5 + log(2.0);

  bool Improved = false;

  C_FLOAT64 * pIndividual = mIndividuals[index]->array();
  C_FLOAT64 * pEnd = pIndividual + mVariableSize;
  C_FLOAT64 * pVelocity = mVelocities[index];
  C_FLOAT64 * pBestPosition = mBestPositions[index];
  std::vector< COptItem * >::const_iterator itOptItem = pProblem->getOptItemList(true).begin();
  C_FLOAT64 ** ppContainerVariable = pProblem->getContainerVariables(true).array();

  C_FLOAT64 * pBestInformantPosition = mBestPositions[index];
  C_FLOAT64 BestInformantValue = mBestValues[index];

  std::set< size_t >::const_iterator itInformant = mInformants[index].begin();
  std::set< size_t >::const_iterator endInformant = mInformants[index].end();

  size_t i = mNumInformed + mNumInformedMin;

  for (; i && itInformant != endInformant; --i, ++itInformant)
    if (mBestValues[*itInformant] < BestInformantValue)
      {
        BestInformantValue = mBestValues[*itInformant];
        pBestInformantPosition = mBestPositions[*itInformant];
      }

  for (; pIndividual != pEnd;
       ++pIndividual, ++pVelocity, ++pBestPosition, ++itOptItem, ++ppContainerVariable, ++pBestInformantPosition)
    {
      *pVelocity *= w;
      *pVelocity += c * pRandom->getRandomCC() * (*pBestPosition - *pIndividual);
      *pVelocity += c * pRandom->getRandomCC() * (*pBestInformantPosition - *pIndividual);

      *pIndividual += *pVelocity;

      COptItem & OptItem = **itOptItem;

      // force it to be within the bounds
      switch (OptItem.checkConstraint(*pIndividual))
        {
          case - 1:
            *pIndividual = *OptItem.getLowerBoundValue();
            *pVelocity = 0.0;
            break;

          case 1:
            *pIndividual = *OptItem.getUpperBoundValue();
            *pVelocity = 0.0;
            break;
        }

      // We need to set the value here so that further checks take
      // account of the value.
      **ppContainerVariable = *pIndividual;
    }

  // calculate its fitness
  C_FLOAT64 EvaluationValue = evaluate();
  mValues[index] = EvaluationValue;

  // Check if we improved individually
  if (EvaluationValue < mBestValues[index])
    {
      Improved = true;

#pragma omp critical
      {
        mImprovements[index] = EvaluationValue;

        // Check if we improved globally
        if (EvaluationValue < mBestValue)
          {
            // and store that value
            mBestValue = EvaluationValue;
            mBestIndex = index;
            mContinue &= mProblemContext.master()->setSolution(EvaluationValue, *mIndividuals[mBestIndex], true);

            // We found a new best value lets report it.
            mpParentTask->output(COutputInterface::DURING);
          }
      }
    }

  return Improved;
}

// initialise an individual
bool COptMethodPS::create(const size_t & index)
{
  COptProblem *& pProblem = mProblemContext.active();
  CRandom * pRandom = mRandomContext.active();

  C_FLOAT64 * pIndividual = mIndividuals[index]->array();
  C_FLOAT64 * pEnd = pIndividual + mVariableSize;
  C_FLOAT64 * pVelocity = mVelocities[index];
  C_FLOAT64 * pBestPosition = mBestPositions[index];
  std::vector< COptItem * >::const_iterator itOptItem = pProblem->getOptItemList(true).begin();
  C_FLOAT64 ** ppContainerVariable = pProblem->getContainerVariables(true).array();

  C_FLOAT64 mn, mx, la;

  for (; pIndividual != pEnd;
       ++pIndividual, ++pVelocity, ++pBestPosition, ++itOptItem, ++ppContainerVariable)
    {
      COptItem & OptItem = **itOptItem;

      // calculate lower and upper bounds
      mn = *OptItem.getLowerBoundValue();
      mx = *OptItem.getUpperBoundValue();

      try
        {
          // First determine the location of the interval
          // Secondly determine whether to distribute the parameter linearly or not
          // depending on the location and act upon it.
          if (0.0 <= mn) // the interval [mn, mx) is in [0, inf)
            {
              la = log10(mx) - log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min()));

              if (la < 1.8 || !(mn > 0.0)) // linear
                {
                  *pIndividual = mn + pRandom->getRandomCC() * (mx - mn);
                  *pVelocity = mn + pRandom->getRandomCC() * (mx - mn) - *pIndividual;
                }
              else
                {
                  *pIndividual = pow(10.0, log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min())) + la * pRandom->getRandomCC());
                  *pVelocity =
                    pow(10.0, log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min())) + la * pRandom->getRandomCC()) - *pIndividual;
                }
            }
          else if (mx > 0) // 0 is in the interval (mn, mx)
            {
              la = log10(mx) + log10(-mn);

              if (la < 3.6) // linear
                {
                  *pIndividual = mn + pRandom->getRandomCC() * (mx - mn);
                  *pVelocity = mn + pRandom->getRandomCC() * (mx - mn) - *pIndividual;
                }
              else
                {
                  C_FLOAT64 mean = (mx + mn) * 0.5;
                  C_FLOAT64 sigma = std::min(std::numeric_limits< C_FLOAT64 >::max(), mx - mn) / 3.0;

                  do
                    {
                      *pIndividual = pRandom->getRandomNormal(mean, sigma);
                    }
                  while ((*pIndividual < mn) || (*pIndividual > mx));

                  *pVelocity = pRandom->getRandomNormal(mean, sigma) - *pIndividual;
                }
            }
          else // the interval (mn, mx] is in (-inf, 0]
            {
              // Switch lower and upper bound and change sign, i.e.,
              // we can treat it similarly as location 1:
              mx = - *OptItem.getLowerBoundValue();
              mn = - *OptItem.getUpperBoundValue();

              la = log10(mx) - log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min()));

              if (la < 1.8 || !(mn > 0.0)) // linear
                {
                  *pIndividual = - (mn + pRandom->getRandomCC() * (mx - mn));
                  *pVelocity = - (mn + pRandom->getRandomCC() * (mx - mn)) - *pIndividual;
                }
              else
                {
                  *pIndividual = - pow(10.0, log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min())) + la * pRandom->getRandomCC());
                  *pVelocity =
                    - pow(10.0, log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min())) + la * pRandom->getRandomCC()) - *pIndividual;
                }
            }
        }

      catch (...)
        {
          *pIndividual = (mx + mn) * 0.5;
          *pVelocity = 0.0;
        }

      // force it to be within the bounds
      switch (OptItem.checkConstraint(*pIndividual))
        {
          case - 1:
            *pIndividual = *OptItem.getLowerBoundValue();
            break;

          case 1:
            *pIndividual = *OptItem.getUpperBoundValue();
            break;
        }

      *pBestPosition = *pIndividual;

      // We need to set the value here so that further checks take
      // account of the value.
      **ppContainerVariable = *pIndividual;
    }

  // calculate its fitness
  mBestValues[index] = mValues[index] = evaluate();
  memcpy(mBestPositions[index], mIndividuals[index]->array(), sizeof(C_FLOAT64) * mVariableSize);

  if (mBestValues[index] < mBestValue)
#pragma omp critical
    {
      // and store that value
      mBestIndex = index;
      mBestValue = mBestValues[mBestIndex];
      mContinue &= mProblemContext.master()->setSolution(mBestValues[mBestIndex], *mIndividuals[mBestIndex], true);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  return mContinue;
}

void COptMethodPS::initObjects()
{
  addObjectReference("Current Iteration", mCurrentGeneration, CDataObject::ValueInt);
}

bool COptMethodPS::initialize()
{
  cleanup();

  if (!COptPopulationMethod::initialize()) return false;

  mGenerations = getValue< unsigned C_INT32 >("Iteration Limit");
  mCurrentGeneration = 0;

  if (mProcessReport)
    mhGenerations =
      mProcessReport.addItem("Iteration Limit",
                             mCurrentGeneration,
                             & mGenerations);

  mPopulationSize = getValue< unsigned C_INT32 >("Swarm Size");

  if (mPopulationSize < 5)
    {

      mPopulationSize = 5;
      setValue("Swarm Size", mPopulationSize);

      if (mLogVerbosity > 0)
        mMethodLog.enterLogEntry(COptLogEntry("User defined Swarm Size too small. Reset to minimum number (5)."));
    }

  mVariance = getValue< C_FLOAT64 >("Std. Deviation");
  mVariance *= mVariance;

  mIndividuals.resize(mPopulationSize);

  size_t i;

  for (i = 0; i < mPopulationSize; ++i)
    {
      mIndividuals[i] = new CVector< C_FLOAT64 >(mVariableSize);
      *mIndividuals[i] = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
    }

  mValues.resize(mPopulationSize);
  mValues = std::numeric_limits<double>::infinity();

  mVelocities.resize(mPopulationSize, mVariableSize);
  mVelocities = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mBestValue = std::numeric_limits<double>::infinity();
  mBestValues.resize(mPopulationSize);
  mBestValues = std::numeric_limits<double>::infinity();
  mBestPositions.resize(mPopulationSize, mVariableSize);
  mBestPositions = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

  mNumInformedMin = std::max<size_t>(mPopulationSize / 10, 5) - 1;
  mNumInformed = mNumInformedMin;

  mpPermutation = new CPermutation(mRandomContext.master(), mPopulationSize);

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry(
        "Minimal number of informants per particle is " + std::to_string(mNumInformedMin) +
        " at a swarm size of " + std::to_string(mPopulationSize) + " particles."
      ));

  mContinue = true;

  if (getParameter("Stop after # Stalled Iterations"))
    mStopAfterStalledIterations = getValue <unsigned C_INT32>("Stop after # Stalled Iterations");

  return mContinue;
}

bool COptMethodPS::cleanup()
{
  pdelete(mpPermutation);

  return COptPopulationMethod::cleanup();
}

void COptMethodPS::buildInformants()
{
  if (mNumInformed < mPopulationSize)
    mNumInformed++;
  else
    return;

  mInformants.clear();
  mInformants.resize(mPopulationSize);
  mpPermutation->shuffle();

  size_t i, j;
  size_t Informant;

  for (i = 0; i < mPopulationSize; i++)
    {
      mInformants[i].insert(i);

      Informant = mpPermutation->pick();

      for (j = 1; j < mNumInformed; j++, Informant = mpPermutation->next())
        {
          if (Informant == i)
            {
              Informant = mpPermutation->next();
            }

          mInformants[Informant].insert(i);
        }
    }

  return;
}

bool COptMethodPS::reachedStdDeviation()
{
  if (mNumInformed > mNumInformedMin + 1)
    mNumInformed--;

  // Check whether the swarm has settled
  C_FLOAT64 * pValue = mValues.array();
  C_FLOAT64 * pEnd = pValue + mPopulationSize;

  if (calcFValVariance() > mVariance)
    return false;

  // The variance of the function value is smaller than required. We now
  // Check the variance of the flock positions.

  for (size_t i = 0; i < mVariableSize; ++i)
    {
      if (calcVariableVariance(i) > mVariance) return false;
    }

  return true;
}

C_FLOAT64 COptMethodPS::calcFValVariance() const
{
  const C_FLOAT64 * pValue = mValues.array();
  const C_FLOAT64 * pEnd = pValue + mPopulationSize;

  C_FLOAT64 Delta;

  C_FLOAT64 Mean = 0.0;
  C_FLOAT64 Variance = 0.0;
  size_t N = 0;

  for (; pValue != pEnd; ++pValue)
    {
      // We need to deal with infinity values since they indicate failure
      if (*pValue == std::numeric_limits<C_FLOAT64>::infinity())
        return false;

      //WARNING:This function returns C_FLOAT64, but above we have return false; !!!!!
      // should we return 0.0 instead? (yes, false is often represeted with 0, but it
      // does not have to!)

      Delta = *pValue - Mean;
      Mean += Delta / ++N;
      // This uses the new mean, i.e., not Delta * Delta
      Variance += Delta * (*pValue - Mean);
    }

  Variance /= (N - 1);

  return Variance;
}

C_FLOAT64 COptMethodPS::calcVariableVariance(const size_t & variable) const
{
  C_FLOAT64 FirstMoment = 0.0;
  C_FLOAT64 SecondMoment = 0.0;

  const C_FLOAT64 * pValue;

  std::vector<CVector< C_FLOAT64 > *>::const_iterator pIndividual = mIndividuals.begin();
  std::vector<CVector< C_FLOAT64 > *>::const_iterator pIndividualEnd = mIndividuals.end();

  // WARNING: parameter values can be infinity, this needs to deal with that (as above)
  for (; pIndividual != pIndividualEnd; ++pIndividual)
    {
      pValue = (*pIndividual)->array() + variable;
      FirstMoment += *pValue;
      SecondMoment += *pValue **pValue;
    }

  return (SecondMoment - FirstMoment * FirstMoment / mPopulationSize) / (mPopulationSize - 1);
}

bool COptMethodPS::optimise()
{
  if (!initialize())
    {
      if (mProcessReport)
        mProcessReport.finishItem(mhGenerations);

      return false;
    }

  C_FLOAT64 * pIndividual = mIndividuals[0]->array();
  C_FLOAT64 * pEnd = pIndividual + mVariableSize;
  C_FLOAT64 * pVelocity = mVelocities[0];
  C_FLOAT64 * pBestPosition = mBestPositions[0];
  std::vector< COptItem * >::const_iterator itOptItem = mProblemContext.master()->getOptItemList(true).begin();
  C_FLOAT64 ** ppContainerVariable = mProblemContext.master()->getContainerVariables(true).array();

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry(
        "Particle Swarm algorithm started",
        "For more information about this method see: http://copasi.org/Support/User_Manual/Methods/Optimization_Methods/Particle_Swarm/"
      )
    );

  // initialise the population
  // first individual is the initial guess
  bool pointInParameterDomain = true;

  for (; pIndividual != pEnd;
       ++pIndividual, ++pVelocity, ++pBestPosition, ++itOptItem, ++ppContainerVariable)
    {
      COptItem & OptItem = **itOptItem;

      *pIndividual = OptItem.getStartValue();

      // force it to be within the bounds
      switch (OptItem.checkConstraint(*pIndividual))
        {
          case -1:
            *pIndividual = *OptItem.getLowerBoundValue();
            pointInParameterDomain = false;
            break;

          case 1:
            *pIndividual = *OptItem.getUpperBoundValue();
            pointInParameterDomain = false;
            break;
        }

      *pBestPosition = *pIndividual;
      *pVelocity = 0.0;

      // We need to set the value here so that further checks take
      // account of the value.
      **ppContainerVariable = *pIndividual;
    }

  if (!pointInParameterDomain && (mLogVerbosity > 0))
    mMethodLog.enterLogEntry(COptLogEntry("Initial point outside parameter domain."));

  // calculate its fitness
  mBestValues[0] = mValues[0] = mBestValue = evaluate();
  memcpy(mBestPositions[0], mIndividuals[0]->array(), sizeof(C_FLOAT64) * mVariableSize);

  // and store that value
  mBestIndex = 0;
  mContinue &= mProblemContext.master()->setSolution(mBestValues[mBestIndex], *mIndividuals[mBestIndex], true);

  // We found a new best value lets report it.
  mpParentTask->output(COutputInterface::DURING);

  // the others are random
  C_INT32 k, kmax = (C_INT32) mPopulationSize;

#pragma omp parallel for schedule(runtime)

  for (k = 1; k < kmax; k++)
    if (mContinue)
      create(k);

  // create the informant list
  buildInformants();

  size_t Stalled = 0;

  for (; mCurrentGeneration < mGenerations && mContinue; mCurrentGeneration++, Stalled++)
    {
      if (mStopAfterStalledIterations != 0 && Stalled > mStopAfterStalledIterations)
        break;

      size_t oldIndex = mBestIndex;

      C_INT32 k, kmax = (C_INT32) mPopulationSize;

#pragma omp parallel for schedule(runtime)

      for (k = 0; k < kmax; k++)
        if (mContinue)
          move(k);

      if (mImprovements.empty())
        {
          buildInformants();

          if (mLogVerbosity > 1)
            mMethodLog.enterLogEntry(
              COptLogEntry(
                "Iteration " + std::to_string(mCurrentGeneration) +
                ": None of the particles improved in objective function value.",
                "Rebuilding with " + std::to_string(mNumInformed) + " informants per particle.",
                dumpStatus()));
        }
      else
        {
          std::map< size_t, C_FLOAT64 >::const_iterator itImproved = mImprovements.begin();
          std::map< size_t, C_FLOAT64 >::const_iterator endImproved = mImprovements.end();

          for (; itImproved != endImproved; ++itImproved)
            {
              // Save the individually best value;
              mBestValues[itImproved->first] = itImproved->second;
              memcpy(mBestPositions[itImproved->first], mIndividuals[itImproved->first]->array(), sizeof(C_FLOAT64) * mVariableSize);
            }

          mImprovements.clear();

          if (reachedStdDeviation())
            {
              if (mLogVerbosity > 1)
                mMethodLog.enterLogEntry(
                  COptLogEntry(
                    "Iteration " + std::to_string(mCurrentGeneration) +
                    ": Standard deviation of the particles was lower than tolerance. Terminating.",
                    "",
                    dumpStatus()));

              break;
            }

          if (oldIndex != mBestIndex)
            Stalled = 0;
        }

      if (mProcessReport)
        mContinue &= mProcessReport.progressItem(mhGenerations);

      //use a different output channel. It will later get a proper enum name
      mpParentTask->output(COutputInterface::MONITORING);
    }

  if (mProcessReport)
    mProcessReport.finishItem(mhGenerations);

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry("Algorithm finished.",
                   "Terminated after " + std::to_string(mCurrentGeneration) +
                   " of " + std::to_string(mGenerations) + " iterations.",
                   dumpStatus()
                  ));

  cleanup();

  return true;
}

unsigned C_INT32 COptMethodPS::getMaxLogVerbosity() const
{
  return 2;
}

std::string COptMethodPS::dumpStatus() const
{
  if (mLogVerbosity > 1)
    {
      std::stringstream status;

      status << "Current Best Individual:" << std::endl;
      status << "  FVal: " << mValues[mBestIndex] << std::endl;

      const CVector < C_FLOAT64 >& bestIndividual = *mIndividuals[mBestIndex];

      for (size_t i = 0; i < mVariableSize; ++i)
        {
          auto& current = bestIndividual[i];
          status << "  Param " << i << ": " << current << std::endl;
        }

      status << std::endl;

      status << "Current Swarm Variances:" << std::endl;
      status << "  FVal: " << calcFValVariance() << std::endl;

      for (size_t i = 0; i < mVariableSize; ++i)
        {
          status << "  Param " << i << ": " << calcVariableVariance(i) << std::endl;
        }

      status << std::endl;

      return status.str();
    }
  else
    return "";
}
