// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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
                               const CTaskEnum::Task & taskType)
  : COptPopulationMethod(pParent, methodType, taskType, true)
  , mStopAfterStalledGenerations(0)
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
                               const CDataContainer * pParent,
                               const bool & parallel)
  : COptPopulationMethod(src, pParent, parallel)
  , mStopAfterStalledGenerations(0)
{
  initObjects();
}

COptMethodSRES::~COptMethodSRES()
{cleanup();}

bool COptMethodSRES::swap(size_t from, size_t to)
{
  std::swap(mIndividuals[to], mIndividuals[from]);
  std::swap(mVariance[to], mVariance[from]);
  std::swap(mValues[to], mValues[from]);
  std::swap(mPhi[to], mPhi[from]);

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
      CRandom * pRandom = mRandomContext.active();

      // iterate over the child rate - 1 since the first child is the parent.
      for (j = 1; j < childrate; ++j, ++itTarget, ++itTargetVariance)
        {
          // first just copy the individuals
          **itTarget = **itSrc;
          **itTargetVariance = **itSrcVariance;

          // do recombination on the sigma
          // since sigmas already have one parent's component
          // need only average with the sigmas of the other parent
          Parent = (i + pRandom->getRandomU(mPopulationSize - 1)) % mPopulationSize;

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

  size_t i, j;
  C_FLOAT64 v1;

  // Mutate each new individual
#pragma omp parallel for schedule(runtime)
  for (i = mPopulationSize; i < 2 * mPopulationSize; ++i)
    {
      CRandom * pRandom = mRandomContext.active();
      const std::vector< COptItem * > & OptItemList = mProblemContext.active()->getOptItemList(true);

      C_FLOAT64 * pVariable = mIndividuals[i]->array();
      C_FLOAT64 * pVariableEnd = pVariable + mVariableSize;
      C_FLOAT64 * pVariance = mVariance[i]->array();
      C_FLOAT64 * pMaxVariance = mMaxVariance.array();

      v1 = pRandom->getRandomNormal01();

      for (j = 0; pVariable != pVariableEnd; ++pVariable, ++pVariance, ++pMaxVariance, ++j)
        {
          C_FLOAT64 & mut = *pVariable;
          C_FLOAT64 Store = mut;

          COptItem & OptItem = *OptItemList[j];

          size_t l = C_INVALID_INDEX;

          try
            {
              // update the parameter for the variances
              *pVariance =
                std::min(*pVariance * exp(mTauPrime * v1 + mTau * pRandom->getRandomNormal01()), *pMaxVariance);

              for (l = 0; l < 10; l++)
                {
                  // calculate the mutated parameter
                  mut = Store + *pVariance * pRandom->getRandomNormal01();

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
          OptItem.setItemValue(mut, COptItem::CheckPolicyFlag::None);
        }

      // calculate its fitness
      mValues[i] = evaluate(EvaluationPolicyFlag::None);
      mPhi[i] = phi(i);
    }

  return proceed();
}

// select mPopulationSize individuals
void COptMethodSRES::select()
{
  // Selection Method for Stochastic Ranking
  // stochastic ranking "bubble sort"

  // We use the bubble sort in the reverse direction. This will assure that within mPopulationSize iteration
  // we have properly sorted the top mPopulationSize individuals.
  for (size_t i = 0; i < mPopulationSize; i++)
    {
      CRandom * pRandom = mRandomContext.active();

      for (size_t j = mIndividuals.size() - 1; j > 0; --j)
        {
          if (mPhi[j] == 0.0 && mPhi[j - 1] == 0.0)
            {
              if (mValues[j] < mValues[j - 1])
                swap(j, j - 1);
            }
          else if (mPhi[j] != 0.0 && mPhi[j - 1] != 0.0)
            {
              if (mValues[j] + mPhi[j] < mValues[j - 1] + mPhi[j - 1])
                swap(j, j - 1);
            }
          else if (pRandom->getRandomOO() < mPf)      // random chance to compare values outside bounds
            {
              if (mValues[j] < mValues[j - 1])
                swap(j, j - 1);
            }
        }
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

// virtual
void COptMethodSRES::finalizeCreation(const size_t & individual, const size_t & index, const COptItem & item, CRandom * /* pRandom */)
{
  const C_FLOAT64 & Value = (*mIndividuals[individual])[index];
  (*mVariance[individual])[index] = std::min(*item.getUpperBoundValue() - Value, Value - *item.getLowerBoundValue()) / sqrt(double(mVariableSize));
}

// Initialize the population
bool COptMethodSRES::creation(size_t first)
{
  size_t i;

  // set the first individual to the initial guess
  if (first == 0)
    {
      createIndividual(C_INVALID_INDEX, COptItem::CheckPolicyFlag::All);

      mValues[0] = evaluate(EvaluationPolicyFlag::None);
      mPhi[0] = phi(0);

      ++first;
    }

#pragma omp parallel for schedule(runtime)
  for (i = first; i < mPopulationSize; ++i)
    {
      createIndividual(i, COptItem::CheckPolicyFlag::All);

      mValues[i] = evaluate(EvaluationPolicyFlag::None);
      mPhi[i] = phi(i);
    }

  return proceed();
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
      const COptItem & OptItem = *mProblemContext.active()->getOptItemList(true)[i];

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

  std::vector< COptItem * >::const_iterator it = mProblemContext.active()->getOptItemList(true).begin();
  std::vector< COptItem * >::const_iterator end = mProblemContext.active()->getOptItemList(true).end();
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

  it = mProblemContext.active()->getConstraintList().begin();
  end = mProblemContext.active()->getConstraintList().end();

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
      if (mProcessReport
          && !mProcessReport.finishItem(mhGenerations))
        signalStop();

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
  creation(0);

  // get the index of the fittest
  BestIndex = fittest();

  if (BestIndex != C_INVALID_INDEX)
    setSolution(mValues[BestIndex], *mIndividuals[BestIndex], true);

  if (!proceed())
    {
      if (mLogVerbosity > 0)
        mMethodLog.enterLogEntry(COptLogEntry("Algorithm was terminated by user."));

      if (mProcessReport
          && !mProcessReport.finishItem(mhGenerations))
        signalStop();

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
       mCurrentGeneration <= mGenerations && proceed();
       mCurrentGeneration++, Stalled++)
    {
#endif // RANDOMIZE

      if (mStopAfterStalledGenerations != 0 && Stalled > mStopAfterStalledGenerations)
        break;

      replicate();

      // select the most fit
      select();

      // get the index of the fittest
      BestIndex = fittest();

      if (BestIndex != C_INVALID_INDEX &&
          mValues[BestIndex] < getBestValue())
        {
#ifdef RANDOMIZE
          Stalled = Stalled10 = Stalled20 = Stalled40 = Stalled80 = 0;
#else
          Stalled = 0;
#endif // RANDOMIZE

          setSolution(mValues[BestIndex], *mIndividuals[BestIndex], true);
        }

      if (mProcessReport
          && !mProcessReport.progressItem(mhGenerations))
        signalStop();

      //use a different output channel. It will later get a proper enum name
      mpParentTask->output(COutputInterface::MONITORING);
    }

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry("Algorithm finished.",
                   "Terminated after " + std::to_string(mCurrentGeneration - 1) + " of " +
                   std::to_string(mGenerations) + " generations."));

  if (mProcessReport
      && !mProcessReport.finishItem(mhGenerations))
    signalStop();

  return true;
}

unsigned C_INT32 COptMethodSRES::getMaxLogVerbosity() const
{
  return 1;
}
