// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// originally implemented by Michalina Kaszuba, 2012, University of Manchester

#include <limits>
#include <string>
#include <cmath>

#include "copasi/copasi.h"
#include "COptMethodDE.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "copasi/randomGenerator/CRandom.h"
#include "copasi/randomGenerator/CPermutation.h"
#include "copasi/utilities/CProcessReport.h"
#include "copasi/utilities/CSort.h"
#include "copasi/core/CDataObjectReference.h"

COptMethodDE::COptMethodDE(const CDataContainer * pParent,
                           const CTaskEnum::Method & methodType,
                           const CTaskEnum::Task & taskType)
  : COptPopulationMethod(pParent, methodType, taskType, true)
  , mpPermutation(NULL)
  , mMutationVariance(0.1)
  , mStopAfterStalledGenerations(0)
  , mBestIndex(C_INVALID_INDEX)

{
  assertParameter("Number of Generations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 2000);
  assertParameter("Population Size", CCopasiParameter::Type::UINT, (unsigned C_INT32) 10);
  assertParameter("Random Number Generator", CCopasiParameter::Type::UINT, (unsigned C_INT32) CRandom::mt19937, eUserInterfaceFlag::editable);
  assertParameter("Seed", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);
  assertParameter("Mutation Variance", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) 0.1, eUserInterfaceFlag::editable);
  assertParameter("Stop after # Stalled Generations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);

  initObjects();
}

COptMethodDE::COptMethodDE(const COptMethodDE & src,
                           const CDataContainer * pParent)
  : COptPopulationMethod(src, pParent)
  , mpPermutation(NULL)
  , mMutationVariance(0.1)
  , mStopAfterStalledGenerations(0)
  , mBestIndex(C_INVALID_INDEX)
{
  initObjects();
}

COptMethodDE::~COptMethodDE()
{cleanup();}

bool COptMethodDE::replicate()
{
  size_t i, j;
  size_t a, b, c;

  const std::vector< COptItem * > & OptItemList = mProblemContext.master()->getOptItemList(true);
  mpPermutation->shuffle();

#pragma omp parallel for schedule(runtime)
  for (i = mPopulationSize; i < 2 * mPopulationSize; i++)
    {
      // MUTATION a, b, c in [0, mPopulationSize - 1]
      a = mpPermutation->pick();
      // b is guaranteed to be different from a
      b = mpPermutation->next();
      // c is guaranteed to be different from a and b
      c = mpPermutation->next();

      // MUTATE CURRENT GENERATION
      for (j = 0; j < mVariableSize; j++)
        {
          COptItem & OptItem = *OptItemList[j];
          C_FLOAT64 & mut = (*mIndividuals[i])[j];

          mut = (*mIndividuals[c])[j] + 2 * ((*mIndividuals[a])[j] - (*mIndividuals[b])[j]);
          OptItem.setItemValue(mut, COptItem::CheckPolicyFlag::All);
        }

      mValues[i] = evaluate(EvaluationPolicy::Constraints);
    }

  //CROSSOVER MUTATED GENERATION WITH THE CURRENT ONE
#pragma omp parallel for schedule(runtime)
  for (i = 2 * mPopulationSize; i < 3 * mPopulationSize; i++)
    {
      for (j = 0; j < mVariableSize; j++)
        {
          COptItem & OptItem = *OptItemList[j];
          C_FLOAT64 & mut = (*mIndividuals[i])[j];

          size_t r = mRandomContext.master()->getRandomU(mPopulationSize - 1);

          if (r < 0.6 * mPopulationSize)
            {
              mut = (*mIndividuals[i - mPopulationSize])[j] *
                    mRandomContext.master()->getRandomNormal(1, mMutationVariance);
            }
          else
            mut = (*mIndividuals[i - 2 * mPopulationSize])[j];

          OptItem.setItemValue(mut, COptItem::CheckPolicyFlag::All);
        }

      mValues[i] = evaluate(EvaluationPolicy::Constraints);
    }

  //SELECT NEXT GENERATION
  for (i = 2 * mPopulationSize; i < 3 * mPopulationSize; i++)
    {
      if (mValues[i - mPopulationSize] > mValues[i]
          && mValues[i - 2 * mPopulationSize] > mValues[i])
        {
          *mIndividuals[i - 2 * mPopulationSize] = *mIndividuals[i];
          mValues[i - 2 * mPopulationSize] = mValues[i];
        }
      else if (mValues[i - mPopulationSize] < mValues[i - 2 * mPopulationSize])
        {
          *mIndividuals[i - 2 * mPopulationSize] = *mIndividuals[i - mPopulationSize];
          mValues[i - 2 * mPopulationSize] = mValues[i - mPopulationSize];
        }
    }

  return true;
}

// check the best individual at this generation
size_t COptMethodDE::fittest()
{
  size_t i, BestIndex = C_INVALID_INDEX;
  C_FLOAT64 BestValue = std::numeric_limits< C_FLOAT64 >::max();

  for (i = 0; i < mPopulationSize; i++)
    if (mValues[i] < BestValue)
      {
        BestIndex = i;
        BestValue = mValues[i];
      }

  return BestIndex;
}

// check the best individual at this generation
void COptMethodDE::boost()
{
  size_t i;

  for (i = 2 * mPopulationSize; i < 3 * mPopulationSize; i++)
    if (mValues[i] < mValues[i - 2 * mPopulationSize])
      {
        *mIndividuals[i - 2 * mPopulationSize] = *mIndividuals[i];
        mValues[i - 2 * mPopulationSize] = mValues[i];
      }
}

// Initialize the population
bool COptMethodDE::creation(size_t first, size_t last)
{
  size_t Last = std::min(last, (size_t) mPopulationSize);
  size_t i, j;

  C_FLOAT64 mn;
  C_FLOAT64 mx;
  C_FLOAT64 la;

#pragma omp parallel for schedule(runtime)
  for (i = first; i < Last; i++)
    {
      // We do not want to loose the best individual;
      if (mBestIndex != i)
        {
          createIndividual(i, COptItem::CheckPolicyFlag::All);
          mValues[i] = evaluate({EvaluationPolicy::Constraints});
        }
    }

  return true;
}

void COptMethodDE::initObjects()
{
}

bool COptMethodDE::initialize()
{
  cleanup();

  size_t i;

  if (!COptPopulationMethod::initialize())
    {
      if (mProcessReport
          && !mProcessReport.finishItem(mhGenerations))
        signalStop();

      return false;
    }

  if (mPopulationSize < 4)
    {
      if (mLogVerbosity > 0)
        mMethodLog.enterLogEntry(COptLogEntry("User defined Population Size too small. Reset to minimum (4)."));

      mPopulationSize = 4;
      setValue("Population Size", mPopulationSize);
    }

  mpPermutation = new CPermutation(mRandomContext.master(), mPopulationSize);

  mIndividuals.resize(3 * mPopulationSize);

  for (i = 0; i < 3 * mPopulationSize; i++)
    mIndividuals[i] = new CVector< C_FLOAT64 >(mVariableSize);

  mValues.resize(3 * mPopulationSize);
  mValues = std::numeric_limits<C_FLOAT64>::infinity();

  mMutationVariance = 0.1;

  if (getParameter("Mutation Variance"))
    {
      mMutationVariance = getValue< C_FLOAT64 >("Mutation Variance");

      if (mMutationVariance < 0.0 || 1.0 < mMutationVariance)
        {
          mMutationVariance = 0.1;
          setValue("Mutation Variance", mMutationVariance);
        }
    }

  if (getParameter("Stop after # Stalled Generations"))
    mStopAfterStalledGenerations = getValue <unsigned C_INT32>("Stop after # Stalled Generations");

  return true;
}

bool COptMethodDE::cleanup()
{
  pdelete(mpPermutation);
  return COptPopulationMethod::cleanup();
}

bool COptMethodDE::optimise()
{
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
        "Algorithm started.",
        "For more information about this method see: http://copasi.org/Support/User_Manual/Methods/Optimization_Methods/Differential_Evolution/"
      )
    );

  size_t i;

  // initialise the population
  // first individual is the initial guess
  bool pointInParameterDomain = true;
  createIndividual(C_INVALID_INDEX, COptItem::CheckPolicyFlag::All);

  mValues[0] = evaluate(EvaluationPolicy::Constraints);

  if (!std::isnan(mValues[0]))
    setSolution(mValues[0], *mIndividuals[0], true);

  // the others are random
  creation(1, mPopulationSize);

  mBestIndex = fittest();

  if (mBestIndex != C_INVALID_INDEX &&
      mValues[mBestIndex] < getBestValue())
    setSolution(mValues[mBestIndex], *mIndividuals[mBestIndex], true);

  if (!proceed())
    {
      if (mLogVerbosity > 0)
        mMethodLog.enterLogEntry(COptLogEntry("Algorithm was terminated by user after initial population creation."));

      if (mProcessReport
          && !mProcessReport.finishItem(mhGenerations))
        signalStop();

      cleanup();
      return true;
    }

  size_t Stalled = 0;

  // ITERATE FOR gener GENERATIONS
  for (mCurrentGeneration = 2;
       mCurrentGeneration <= mGenerations && proceed();
       mCurrentGeneration++, Stalled++)
    {

      if (mStopAfterStalledGenerations != 0 && Stalled > mStopAfterStalledGenerations)
        break;

      if (Stalled > 50)
        {
          if (mLogVerbosity > 0)
            mMethodLog.enterLogEntry(
              COptLogEntry(
                "Generation " + std::to_string(mCurrentGeneration) +
                ": Fittest individual has not changed in the last " + std::to_string(Stalled - 1) +
                " generations. 40% of individuals randomized."
              ));

          Stalled = 0;

          creation((size_t) 0.4 * mPopulationSize, (size_t) 0.8 * mPopulationSize);
        }

      // perturb the population a bit
      creation((size_t)(mPopulationSize * 0.9), mPopulationSize);
      replicate();

      // get the index of the fittest
      mBestIndex = fittest();

      if ((mBestIndex != C_INVALID_INDEX) && (mValues[mBestIndex] < getBestValue()))
        {
          Stalled = 0;
          setSolution(mValues[mBestIndex], *mIndividuals[mBestIndex], true);
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

  cleanup();

  return true;
}

unsigned C_INT32 COptMethodDE::getMaxLogVerbosity() const
{
  return 1;
}
