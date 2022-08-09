// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

#include "COptMethodSRES.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "copasi/randomGenerator/CRandom.h"
#include "copasi/utilities/CProcessReport.h"
#include "copasi/utilities/CSort.h"
#include "copasi/core/CDataObjectReference.h"

#ifdef RANDOMIZE
# undef RANDOMIZE
#endif

#define childrate 7

COptMethodSRES::COptMethodSRES(const CDataContainer * pParent,
                               const CTaskEnum::Method & methodType,
                               const CTaskEnum::Task & taskType):
  COptPopulationMethod(pParent, methodType, taskType, false),
  mStopAfterStalledGenerations(0),
  mEvaluationValue(std::numeric_limits< C_FLOAT64 >::max()),
  mBestValue(std::numeric_limits< C_FLOAT64 >::max())

{
  assertParameter("Number of Generations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 200);
  assertParameter("Population Size", CCopasiParameter::Type::UINT, (unsigned C_INT32) 20);
  assertParameter("Random Number Generator", CCopasiParameter::Type::UINT, (unsigned C_INT32) CRandom::mt19937, eUserInterfaceFlag::editable);
  assertParameter("Seed", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);
  assertParameter("Pf", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) 0.475);  //*****ADDED for SR
  assertParameter("Stop after # Stalled Generations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);

  initObjects();
}

COptMethodSRES::COptMethodSRES(const COptMethodSRES & src,
                               const CDataContainer * pParent):
  COptPopulationMethod(src, pParent),
  mStopAfterStalledGenerations(0),
  mEvaluationValue(std::numeric_limits< C_FLOAT64 >::max()),
  mBestValue(std::numeric_limits< C_FLOAT64 >::max())
{initObjects();}

COptMethodSRES::~COptMethodSRES()
{cleanup();}

// evaluate the fitness of one individual
bool COptMethodSRES::evaluate(const CVector< C_FLOAT64 > & /* individual */)
{
  bool Continue = true;

  // We do not need to check whether the parametric constraints are fulfilled
  // since this method allows for parameters outside the bounds

  // evaluate the fitness
  Continue = mProblemContext.master()->calculate();

  // We do not need to check whether the functional constraints are fulfilled
  // since this method allows for solutions outside the bounds.

  mEvaluationValue = mProblemContext.master()->getCalculateValue();

  return Continue;
}

bool COptMethodSRES::swap(size_t from, size_t to)
{
  CVector< C_FLOAT64 > * pTmp = mIndividuals[to];
  mIndividuals[to] = mIndividuals[from];
  mIndividuals[from] = pTmp;

  pTmp = mVariance[to];
  mVariance[to] = mVariance[from];
  mVariance[from] = pTmp;

  C_FLOAT64 dTmp = mValues[to];
  mValues[to] = mValues[from];
  mValues[from] = dTmp;

  dTmp = mPhi[to];
  mPhi[to] = mPhi[from];
  mPhi[from] = dTmp;

  return true;
}

bool COptMethodSRES::replicate()
{
  bool Continue = true;

  size_t Parent;
  size_t i, j;

  std::vector< CVector < C_FLOAT64 > * >::iterator itSrc = mIndividuals.begin();
  std::vector< CVector < C_FLOAT64 > * >::iterator endSrc = itSrc + mPopulationSize;
  std::vector< CVector < C_FLOAT64 > * >::iterator itTarget = endSrc;

  std::vector< CVector < C_FLOAT64 > * >::iterator itSrcVariance = mVariance.begin();
  std::vector< CVector < C_FLOAT64 > * >::iterator itTargetVariance = itSrcVariance + mPopulationSize;

  C_FLOAT64 * pVariance, * pVarianceEnd, * pParentVariance;

  // iterate over parents
  for (i = 0; itSrc != endSrc && Continue; ++itSrc, ++itSrcVariance, ++i)
    {
      // iterate over the child rate - 1 since the first child is the parent.
      for (j = 1; j < childrate; ++j, ++itTarget, ++itTargetVariance)
        {
          // first just copy the individuals
          **itTarget = **itSrc;
          **itTargetVariance = **itSrcVariance;

          // do recombination on the sigma
          // since sigmas already have one parent's component
          // need only average with the sigmas of the other parent
          Parent = (i + mRandomContext.master()->getRandomU(mPopulationSize - 1)) % mPopulationSize;

          pVariance = (*itTargetVariance)->array();
          pVarianceEnd = pVariance + mVariableSize;
          pParentVariance = mVariance[Parent]->array();

          for (; pVariance != pVarianceEnd; ++pVariance, ++pParentVariance)
            *pVariance = (*pVariance + *pParentVariance) * .5;
        }
    }

  Continue &= mutate();

  return Continue;
}

//mutate one individual
bool COptMethodSRES::mutate()
{
  std::vector< CVector < C_FLOAT64 > * >::iterator it = mIndividuals.begin() + mPopulationSize;
  std::vector< CVector < C_FLOAT64 > * >::iterator end = mIndividuals.end();
  std::vector< CVector < C_FLOAT64 > * >::iterator itVariance = mVariance.begin() + mPopulationSize;

  C_FLOAT64 * pVariable, * pVariableEnd, * pVariance, * pMaxVariance;
  C_FLOAT64 * pPhi = mPhi.array() + mPopulationSize;
  C_FLOAT64 * pValue = mValues.array() + mPopulationSize;

  bool Continue = true;
  size_t i, j;
  C_FLOAT64 v1;

  // Mutate each new individual
  for (i = mPopulationSize; it != end && Continue; ++it, ++itVariance, ++i)
    {
      pVariable = (*it)->array();
      pVariableEnd = pVariable + mVariableSize;
      pVariance = (*itVariance)->array();
      pMaxVariance = mMaxVariance.array();

      v1 = mRandomContext.master()->getRandomNormal01();

      for (j = 0; pVariable != pVariableEnd; ++pVariable, ++pVariance, ++pMaxVariance, ++j)
        {
          C_FLOAT64 & mut = *pVariable;
          C_FLOAT64 Store = mut;

          const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[j];

          size_t l = C_INVALID_INDEX;

          try
            {
              // update the parameter for the variances
              *pVariance =
                std::min(*pVariance * exp(mTauPrime * v1 + mTau * mRandomContext.master()->getRandomNormal01()), *pMaxVariance);

              for (l = 0; l < 10; l++)
                {
                  // calculate the mutated parameter
                  mut = Store + *pVariance * mRandomContext.master()->getRandomNormal01();

                  if (OptItem.checkConstraint(mut) == 0)
                    break;
                }
            }

          catch (...)
            {
              mut = (*OptItem.getUpperBoundValue() + *OptItem.getLowerBoundValue()) * 0.5;
            }

          if (l == 10)
            mut = Store;

          // We need to set the value here so that further checks take
          // account of the value.
          *mProblemContext.master()->getContainerVariables(true)[j] = (mut);
        }

      // calculate its fitness
      Continue = evaluate(**it);
      *pValue++ = mEvaluationValue;
      *pPhi++ = phi(i);
    }

  return Continue;
}

// select mPopulationSize individuals
void COptMethodSRES::select()
{
  size_t i, j;
  size_t TotalPopulation = mIndividuals.size();
  bool wasSwapped;
  size_t sweepNum = TotalPopulation;  // This is default based on paper

  // Selection Method for Stochastic Ranking
  // stochastic ranking "bubble sort"

  for (i = 0; i < sweepNum; i++) // Here sweepNum is optimal number of sweeps from paper
    {
      wasSwapped = false;

      // :TODO: since we are only interested in mPopulationSize highest ranked
      // individuals the upper limit of the loop can be improved.
      for (j = 0; j < TotalPopulation - 1; j++)  // lambda is number of individuals
        {
          if ((mPhi[j] == 0 && mPhi[j + 1] == 0) || // within bounds
              (mRandomContext.master()->getRandomOO() < mPf))      // random chance to compare values outside bounds
            {
              // compare obj fcn using mValue alternative code
              if (mValues[j] > mValues[j + 1])
                {
                  swap(j, j + 1);
                  wasSwapped = true;
                }
            }
          else
            {
              if (mPhi[j] > mPhi[j + 1]) // j further outside then j+1
                {
                  swap(j, j + 1);
                  wasSwapped = true;
                }
            }
        }

      // if nothing was swapped, then they're ordered!
      if (wasSwapped == false) break;
    }
}

// check the best individual at this generation
size_t COptMethodSRES::fittest()
{
  size_t i, BestIndex = C_INVALID_INDEX;
  C_FLOAT64 BestValue = std::numeric_limits< C_FLOAT64 >::max();

  for (i = 0; i < mPopulationSize; i++)
    if (mValues[i] < BestValue && mPhi[i] == 0)
      {
        BestIndex = i;
        BestValue = mValues[i];
      }

  return BestIndex;
}

// Initialize the population
bool COptMethodSRES::creation(size_t first)
{
  size_t i;
  size_t j;

  C_FLOAT64 mn;
  C_FLOAT64 mx;
  C_FLOAT64 la;

  bool Continue = true;

  std::vector< CVector < C_FLOAT64 > * >::iterator it =
    mIndividuals.begin() + first;
  std::vector< CVector < C_FLOAT64 > * >::iterator end =
    mIndividuals.begin() + mPopulationSize;
  std::vector< CVector < C_FLOAT64 > * >::iterator itVariance =
    mVariance.begin() + first;

  C_FLOAT64 * pVariable, * pVariableEnd, * pVariance, * pMaxVariance;
  C_FLOAT64 * pPhi = mPhi.array() + first;
  C_FLOAT64 * pValue = mValues.array() + first;

  // set the first individual to the initial guess
  if (it == mIndividuals.begin())
    {
      pVariable = (*it)->array();
      pVariableEnd = pVariable + mVariableSize;
      pVariance = (*itVariance)->array();
      pMaxVariance = mMaxVariance.array();

      bool pointInParameterDomain = true;

      for (j = 0; pVariable != pVariableEnd; ++pVariable, ++pVariance, ++pMaxVariance, ++j)
        {
          C_FLOAT64 & mut = *pVariable;
          const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[j];

          mut = OptItem.getStartValue();

          // force it to be within the bounds
          switch (OptItem.checkConstraint(mut))
            {
              case - 1:
                mut = *OptItem.getLowerBoundValue();

                if (!OptItem.checkLowerBound(mut)) // Inequality
                  {
                    if (mut == 0.0)
                      mut = std::numeric_limits< C_FLOAT64 >::min();
                    else
                      mut += mut * std::numeric_limits< C_FLOAT64 >::epsilon();
                  }

                pointInParameterDomain = false;

                break;

              case 1:
                mut = *OptItem.getUpperBoundValue();

                if (!OptItem.checkUpperBound(mut)) // Inequality
                  {
                    if (mut == 0.0)
                      mut = - std::numeric_limits< C_FLOAT64 >::min();
                    else
                      mut -= mut * std::numeric_limits< C_FLOAT64 >::epsilon();
                  }

                pointInParameterDomain = false;

                break;
            }

          // We need to set the value here so that further checks take
          // account of the value.
          *mProblemContext.master()->getContainerVariables(true)[j] = (mut);

          // Set the variance for this parameter.
          *pVariance = std::min(*OptItem.getUpperBoundValue() - mut, mut - *OptItem.getLowerBoundValue()) / sqrt(double(mVariableSize));
        }

      if (!pointInParameterDomain && (mLogVerbosity > 0))
        mMethodLog.enterLogEntry(COptLogEntry("Initial point outside parameter domain."));

      Continue = evaluate(**it);
      *pValue++ = mEvaluationValue;
      *pPhi++ = phi(0);

      ++it;
      ++itVariance;
      ++first;
    }

  for (i = first; it < end ; ++it, ++itVariance, ++i)
    {
      pVariable = (*it)->array();
      pVariableEnd = pVariable + mVariableSize;
      pVariance = (*itVariance)->array();
      pMaxVariance = mMaxVariance.array();

      for (j = 0; pVariable != pVariableEnd; ++pVariable, ++pVariance, ++pMaxVariance, ++j)
        {
          C_FLOAT64 & mut = *pVariable;
          const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[j];

          // calculate lower and upper bounds
          mn = *OptItem.getLowerBoundValue();
          mx = *OptItem.getUpperBoundValue();

          try
            {
              // First determine the location of the intervall
              // Secondly determine whether to distribute the parameter linearly or not
              // depending on the location and act uppon it.
              if (0.0 <= mn) // the interval [mn, mx) is in [0, inf)
                {
                  la = log10(mx) - log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min()));

                  if (la < 1.8 || !(mn > 0.0)) // linear
                    mut = mn + mRandomContext.master()->getRandomCC() * (mx - mn);
                  else
                    mut = pow(10.0, log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min())) + la * mRandomContext.master()->getRandomCC());
                }
              else if (mx > 0) // 0 is in the interval (mn, mx)
                {
                  la = log10(mx) + log10(-mn);

                  if (la < 3.6) // linear
                    mut = mn + mRandomContext.master()->getRandomCC() * (mx - mn);
                  else
                    {
                      C_FLOAT64 mean = (mx + mn) * 0.5;
                      C_FLOAT64 sigma = mean * 0.01;

                      do
                        {
                          mut = mRandomContext.master()->getRandomNormal(mean, sigma);
                        }
                      while ((mut < mn) || (mut > mx));
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
                    mut = - (mn + mRandomContext.master()->getRandomCC() * (mx - mn));
                  else
                    mut = - pow(10.0, log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min())) + la * mRandomContext.master()->getRandomCC());
                }
            }

          catch (...)
            {
              mut = (mx + mn) * 0.5;
            }

          // force it to be within the bounds
          switch (OptItem.checkConstraint(mut))
            {
              case - 1:
                mut = *OptItem.getLowerBoundValue();

                if (!OptItem.checkLowerBound(mut)) // Inequality
                  {
                    if (mut == 0.0)
                      mut = std::numeric_limits< C_FLOAT64 >::min();
                    else
                      mut += mut * std::numeric_limits< C_FLOAT64 >::epsilon();
                  }

                break;

              case 1:
                mut = *OptItem.getUpperBoundValue();

                if (!OptItem.checkUpperBound(mut)) // Inequality
                  {
                    if (mut == 0.0)
                      mut = - std::numeric_limits< C_FLOAT64 >::min();
                    else
                      mut -= mut * std::numeric_limits< C_FLOAT64 >::epsilon();
                  }

                break;
            }

          // We need to set the value here so that further checks take
          // account of the value.
          *mProblemContext.master()->getContainerVariables(true)[j] = (mut);

          // Set the variance for this parameter.
          *pVariance = std::min(*OptItem.getUpperBoundValue() - mut, mut - *OptItem.getLowerBoundValue()) / sqrt(double(mVariableSize));
        }

      // calculate its fitness
      Continue = evaluate(**it);
      *pValue++ = mEvaluationValue;
      *pPhi++ = phi(i);
    }

  return Continue;
}

void COptMethodSRES::initObjects()
{
}

bool COptMethodSRES::initialize()
{
  cleanup();

  size_t i;

  if (!COptPopulationMethod::initialize()) return false;

  mPf = getValue< C_FLOAT64 >("Pf");

  if (mPf < 0.0 || 1.0 < mPf)
    {
      mPf = 0.475;
      setValue("Pf", mPf);

      if (mLogVerbosity > 0)
        mMethodLog.enterLogEntry(
          COptLogEntry("User defined Pf not in interval (0,1). Reset to default: " + std::to_string(mPf) + "."
                      ));
    }

  mIndividuals.resize(childrate * mPopulationSize);

  for (i = 0; i < childrate * mPopulationSize; i++)
    mIndividuals[i] = new CVector< C_FLOAT64 >(mVariableSize);

  mVariance.resize(childrate * mPopulationSize);

  for (i = 0; i < childrate * mPopulationSize; i++)
    mVariance[i] = new CVector< C_FLOAT64 >(mVariableSize);

  mMaxVariance.resize(mVariableSize);

  for (i = 0; i < mVariableSize; i++)
    {
      const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[i];

      try
        {
          mMaxVariance[i] =
            (*OptItem.getUpperBoundValue() - *OptItem.getLowerBoundValue()) / sqrt(double(mVariableSize));
        }
      catch (...)
        {
          mMaxVariance[i] = 1.0e3;
        }
    }

  mValues.resize(childrate * mPopulationSize);
  mValues = std::numeric_limits<C_FLOAT64>::infinity();
  mBestValue = std::numeric_limits<C_FLOAT64>::infinity();

  mPhi.resize(childrate * mPopulationSize);

  try
    {
      /*
      C_FLOAT64 alpha = 0.2;
      C_FLOAT64 chi = 1 / (2 * sqrt(double(mVariableSize))) + 1 / (2 * double(mVariableSize));
      C_FLOAT64 varphi = sqrt(2/chi * log(1/alpha) *exp(chi/2 -(1-alpha)));
      */

      C_FLOAT64 varphi = 1;
      mTau = varphi / sqrt(2 * sqrt(double(mVariableSize)));
      mTauPrime = varphi / sqrt(2 * double(mVariableSize));
    }
  catch (...)
    {
      mTau = mTauPrime = 1;
    }

  if (getParameter("Stop after # Stalled Generations"))
    mStopAfterStalledGenerations = getValue <unsigned C_INT32>("Stop after # Stalled Generations");

  return true;
}

bool COptMethodSRES::cleanup()
{
  size_t i;

  for (i = 0; i < mVariance.size(); i++)
    {
      pdelete(mVariance[i]);
    }

  return COptPopulationMethod::cleanup();
}

// evaluate the distance of parameters and constraints to boundaries
C_FLOAT64 COptMethodSRES::phi(size_t indivNum)
{
  C_FLOAT64 phiVal = 0.0;
  C_FLOAT64 phiCalc;

  std::vector< COptItem * >::const_iterator it = mProblemContext.master()->getOptItemList(true).begin();
  std::vector< COptItem * >::const_iterator end = mProblemContext.master()->getOptItemList(true).end();
  C_FLOAT64 * pValue = mIndividuals[indivNum]->array();

  for (; it != end; ++it, pValue++)
    {
      switch ((*it)->checkConstraint())
        {
          case - 1:
            phiCalc = *(*it)->getLowerBoundValue() - *pValue;
            phiVal += phiCalc * phiCalc;
            break;

          case 1:
            phiCalc = *pValue - *(*it)->getUpperBoundValue();
            phiVal += phiCalc * phiCalc;
            break;
        }
    }

  it = mProblemContext.master()->getConstraintList().begin();
  end = mProblemContext.master()->getConstraintList().end();

  for (; it != end; ++it)
    {
      phiCalc = (*it)->getConstraintViolation();

      if (phiCalc > 0.0)
        phiVal += phiCalc * phiCalc;
    }

  return phiVal;
}

bool COptMethodSRES::optimise()
{
  bool Continue = true;
  size_t BestIndex = C_INVALID_INDEX;

  size_t Stalled = 0;
#ifdef RANDOMIZE
  // Counters to determine whether the optimization process has stalled
  // They count the number of generations without advances.
  size_t Stalled10, Stalled20, Stalled40, Stalled80;
  Stalled10 = Stalled20 = Stalled40 = Stalled80 = 0;
#endif // RANDOMIZE

  if (!initialize())
    {
      if (mProcessReport)
        mProcessReport.finishItem(mhGenerations);

      return false;
    }

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry(
        "Algorithm started",
        "For more information about this method see: http://copasi.org/Support/User_Manual/Methods/Optimization_Methods/Evolutionary_Strategy_SRES/"
      )
    );

  // initialise the population
  Continue = creation(0);
  mProblemContext.master()->setSolution(mValues[0], *mIndividuals[0], true);

  // get the index of the fittest
  BestIndex = fittest();

  if (BestIndex != C_INVALID_INDEX)
    {
      // and store that value
      mBestValue = mValues[BestIndex];
      Continue = mProblemContext.master()->setSolution(mBestValue, *mIndividuals[BestIndex], true);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  if (!Continue)
    {
      if (mLogVerbosity > 0)
        mMethodLog.enterLogEntry(COptLogEntry("Algorithm was terminated by user."));

      if (mProcessReport)
        mProcessReport.finishItem(mhGenerations);

      cleanup();
      return true;
    }

  // ITERATE FOR gener GENERATIONS
#ifdef RANDOMIZE

  for (mCurrentGeneration = 2;
       mCurrentGeneration <= mGenerations && Continue;
       mCurrentGeneration++, Stalled++, Stalled10++, Stalled20++, Stalled40++, Stalled80++)
    {
      // perturb the population if we have stalled for a while
      if (Stalled80 > 80)
        {
          if (mLogVerbosity > 0)
            mMethodLog.enterLogEntry(
              COptLogEntry(
                "Generation " + std::to_string(mCurrentGeneration) +
                "generations: Fittest individual has not changed for the last " + std::to_string(Stalled80 - 1) +
                ". 80% of individuals randomized."
              ));

          Continue = creation((size_t)(mPopulationSize * 0.2));
          Stalled10 = Stalled20 = Stalled40 = Stalled80 = 0;
        }
      else if (Stalled40 > 40)
        {
          if (mLogVerbosity > 0)
            mMethodLog.enterLogEntry(
              COptLogEntry(
                "Generation " + std::to_string(mCurrentGeneration) +
                "generations: Fittest individual has not changed for the last " + std::to_string(Stalled40 - 1) +
                ". 40% of individuals randomized."
              ));

          Continue = creation((size_t)(mPopulationSize * 0.6));
          Stalled10 = Stalled20 = Stalled40 = 0;
        }
      else if (Stalled20 > 20)
        {
          if (mLogVerbosity > 0)
            mMethodLog.enterLogEntry(
              COptLogEntry(
                "Generation " + std::to_string(mCurrentGeneration) +
                "generations: Fittest individual has not changed for the last " + std::to_string(Stalled20 - 1) +
                ". 20% of individuals randomized."
              ));

          Continue = creation((size_t)(mPopulationSize * 0.8));
          Stalled10 = Stalled20 = 0;
        }
      else if (Stalled10 > 10)
        {
          if (mLogVerbosity > 0)
            mMethodLog.enterLogEntry(
              COptLogEntry(
                "Generation " + std::to_string(mCurrentGeneration) +
                "generations: Fittest individual has not changed for the last " + std::to_string(Stalled10 - 1) +
                ". 10% of individuals randomized."
              ));

          Continue = creation((size_t)(mPopulationSize * 0.9));
          Stalled10 = 0;
        }

#else

  for (mCurrentGeneration = 2;
       mCurrentGeneration <= mGenerations && Continue;
       mCurrentGeneration++, Stalled++)
    {
#endif // RANDOMIZE

      if (mStopAfterStalledGenerations != 0 && Stalled > mStopAfterStalledGenerations)
        break;

      Continue = replicate();

      // select the most fit
      select();

      // get the index of the fittest
      BestIndex = fittest();

      if (BestIndex != C_INVALID_INDEX &&
          mValues[BestIndex] < mBestValue)
        {
#ifdef RANDOMIZE
          Stalled = Stalled10 = Stalled20 = Stalled40 = Stalled80 = 0;
#else
          Stalled = 0;
#endif // RANDOMIZE

          mBestValue = mValues[BestIndex];

          Continue = mProblemContext.master()->setSolution(mBestValue, *mIndividuals[BestIndex], true);

          // We found a new best value lets report it.
          mpParentTask->output(COutputInterface::DURING);
        }

      if (mProcessReport)
        Continue = mProcessReport.progressItem(mhGenerations);

      //use a different output channel. It will later get a proper enum name
      mpParentTask->output(COutputInterface::MONITORING);
    }

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry("Algorithm finished.",
                   "Terminated after " + std::to_string(mCurrentGeneration - 1) + " of " +
                   std::to_string(mGenerations) + " generations."));

  if (mProcessReport)
    mProcessReport.finishItem(mhGenerations);

  return true;
}

unsigned C_INT32 COptMethodSRES::getMaxLogVerbosity() const
{
  return 1;
}
