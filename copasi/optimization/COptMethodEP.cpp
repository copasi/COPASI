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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <cmath>

#include "copasi/copasi.h"

#include "COptMethodEP.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "copasi/randomGenerator/CRandom.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/utilities/CSort.h"

COptMethodEP::COptMethodEP(const CDataContainer * pParent,
                           const CTaskEnum::Method & methodType,
                           const CTaskEnum::Task & taskType):
  COptPopulationMethod(pParent, methodType, taskType, false),
  mBestIndex(C_INVALID_INDEX),
  mLosses(0),
  mEvaluationValue(std::numeric_limits< C_FLOAT64 >::max()),
  mStopAfterStalledGenerations(0),
  mVariance(0)
{
  assertParameter("Number of Generations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 200);
  assertParameter("Population Size", CCopasiParameter::Type::UINT, (unsigned C_INT32) 20);
  assertParameter("Random Number Generator", CCopasiParameter::Type::UINT, (unsigned C_INT32) CRandom::mt19937, eUserInterfaceFlag::editable);
  assertParameter("Seed", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);
  assertParameter("Stop after # Stalled Generations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);

  initObjects();
}

COptMethodEP::COptMethodEP(const COptMethodEP & src,
                           const CDataContainer * pParent)
  : COptPopulationMethod(src, pParent),
    mBestIndex(C_INVALID_INDEX),
    mLosses(0),
    mEvaluationValue(std::numeric_limits< C_FLOAT64 >::max()),
    mStopAfterStalledGenerations(0),
    mVariance(0)
{initObjects();}

COptMethodEP::~COptMethodEP()
{
  cleanup();
}

bool COptMethodEP::optimise()
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
        "For more information about this method see: http://copasi.org/Support/User_Manual/Methods/Optimization_Methods/Evolutionary_Programming/"
      )
    );

  bool Continue = true;

  // Initialize the population
  Continue = creation();

  // get the index of the fittest
  mBestIndex = fittest();

  if (mBestIndex != C_INVALID_INDEX)
    setSolution(mValues[mBestIndex], *mIndividuals[mBestIndex], true);

  if (!Continue)
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

  // iterate over Generations
  for (mCurrentGeneration = 2;
       mCurrentGeneration <= mGenerations && Continue;
       mCurrentGeneration++, Stalled++)
    {

      if (mStopAfterStalledGenerations != 0 && Stalled > mStopAfterStalledGenerations)
        break;

      // replicate the individuals
      Continue = replicate();

      // select the most fit
      Continue = select();

      // get the index of the fittest
      mBestIndex = fittest();

      if (mBestIndex != C_INVALID_INDEX &&
          mValues[mBestIndex] < getBestValue())
        {
          Stalled = 0;
          setSolution(mValues[mBestIndex], *mIndividuals[mBestIndex], true);
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

  if (mProcessReport
      && !mProcessReport.finishItem(mhGenerations))
    signalStop();

  cleanup();

  return true;
}

bool COptMethodEP::cleanup()
{

  size_t i;

  for (i = 0; i < mVariance.size(); i++)
    {
      pdelete(mVariance[i]);
    }

  return COptPopulationMethod::cleanup();
}

bool COptMethodEP::initialize()
{
  cleanup();

  size_t i;

  if (!COptPopulationMethod::initialize()) return false;

  mVariableSize = mProblemContext.master()->getOptItemList(true).size();

  mIndividuals.resize(2 * mPopulationSize);

  mVariance.resize(2 * mPopulationSize);

  for (i = 0; i < 2 * mPopulationSize; i++)
    {
      mIndividuals[i] = new CVector< C_FLOAT64 >(mVariableSize);
      mVariance[i] = new CVector< C_FLOAT64 >(mVariableSize);
    }

  mValues.resize(2 * mPopulationSize);
  mValues = std::numeric_limits< C_FLOAT64 >::infinity();

  mLosses.resize(2 * mPopulationSize);
  mLosses = 0;

  // Initialize the parameters to update the variances
  tau1 = 1.0 / sqrt(2 * double(mVariableSize));
  tau2 = 1.0 / sqrt(2 * sqrt(double(mVariableSize)));

  if (getParameter("Stop after # Stalled Generations"))
    mStopAfterStalledGenerations = getValue <unsigned C_INT32>("Stop after # Stalled Generations");

  return true;
}

void COptMethodEP::initObjects()
{
}

// virtual
void COptMethodEP::finalizeCreation(const size_t & individual, const size_t & index, const COptItem & item, CRandom * /* pRandom */)
{
  (*mVariance[individual])[index] = fabs(item.getItemValue()) * 0.5;
}

bool COptMethodEP::creation()
{
  size_t i;
  size_t j;

  C_FLOAT64 mn;
  C_FLOAT64 mx;
  C_FLOAT64 la;

  // set the first individual to the initial guess
  createIndividual(C_INVALID_INDEX, COptItem::CheckPolicyFlag::All);
  mValues[0] = evaluate({EvaluationPolicy::Constraints});

  //candx[0] = evaluate(0);

  // and copy it to the rest
  // for(i=1; i<half; i++)
  //  candx[i] = candx[0];
  // set the other half to random values within the boundaries
  // for(i=half; i<mVariableSizeze; i++)

  for (i = 1; i < mPopulationSize && proceed(); i++)
    {
      createIndividual(i, COptItem::CheckPolicyFlag::All);
      mValues[i] = evaluate({EvaluationPolicy::Constraints});
    }

  return true;
}

bool COptMethodEP::select()
{
  size_t i, j, nopp, opp;
  size_t TotalPopulation = 2 * mPopulationSize;

  // tournament competition
  mLosses = 0; // Set all losses to 0.

  // compete with ~ 20% of the TotalPopulation
  nopp = std::max<size_t>(1, mPopulationSize / 5);

  // parents and offspring are all in competition
  for (i = 0; i < TotalPopulation; i++)
    for (j = 0; j < nopp; j++)
      {
        // get random opponent
        do
          {
            opp = mRandomContext.master()->getRandomU((unsigned C_INT32)(TotalPopulation - 1));
          }
        while (i == opp);

        if (mValues[i] < mValues[opp])
          mLosses[opp]++;
        else
          mLosses[i]++;
      }

  partialSortWithPivot(mLosses.array(),
                       mLosses.array() + mPopulationSize,
                       mLosses.array() + TotalPopulation,
                       mPivot);

  FSwapClass<COptMethodEP, size_t, bool> Swap(this, &COptMethodEP::swap);
  applyPartialPivot(mPivot, mPopulationSize, Swap);

  return true;
}

bool COptMethodEP::swap(size_t from, size_t to)
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

  size_t iTmp = mLosses[to];
  mLosses[to] = mLosses[from];
  mLosses[from] = iTmp;

  return true;
}

size_t COptMethodEP::fittest()
{
  size_t i, BestIndex = 0;
  C_FLOAT64 BestValue = mValues[0];

  for (i = 1; i < mPopulationSize && !mLosses[i]; i++)
    if (mValues[i] < BestValue)
      {
        BestIndex = i;
        BestValue = mValues[i];
      }

  return BestIndex;
}

bool COptMethodEP::replicate()
{
  size_t i;
  size_t j;
  bool Continue = true;

  // iterate over parents
  for (i = 0; i < mPopulationSize && Continue; i++)
    {
      // replicate them
      for (j = 0; j < mVariableSize; j++)
        {
          (*mIndividuals[mPopulationSize + i])[j] = (*mIndividuals[i])[j];
          (*mVariance[mPopulationSize + i])[j] = (*mVariance[i])[j];
        }

      mValues[mPopulationSize + i] = mValues[i];

      // possibly mutate the offspring
      Continue = mutate(mPopulationSize + i);
    }

  return Continue;
}

bool COptMethodEP::mutate(size_t i)
{
  size_t j;
  C_FLOAT64 v1;

  CVector<C_FLOAT64> & Individual = *mIndividuals[i];
  CVector<C_FLOAT64> & Variance = *mVariance[i];

  v1 = mRandomContext.master()->getRandomNormal01();

  const std::vector< COptItem * > & OptItemList = mProblemContext.master()->getOptItemList(true);

  // update the variances
  for (j = 0; j < mVariableSize; j++)
    {
      C_FLOAT64 & mut = Individual[j];
      COptItem & OptItem = *OptItemList[j];

      try
        {
          // update the parameter for the variances
          Variance[j] =
            std::max(Variance[j] * exp(tau1 * v1 + tau2 * mRandomContext.master()->getRandomNormal01()), 1e-8);

          // calculate the mutated parameter
          mut += Variance[j] * mRandomContext.master()->getRandomNormal01();
        }

      catch (...)
        {
          mut = (*OptItem.getUpperBoundValue() + *OptItem.getLowerBoundValue()) * 0.5;
        }

      OptItem.setItemValue(mut, COptItem::CheckPolicyFlag::All);
    }

  // calculate its fitness
  mValues[i] = evaluate({EvaluationPolicy::Constraints});

  return true;
}

unsigned C_INT32 COptMethodEP::getMaxLogVerbosity() const
{
  return 0;
}
