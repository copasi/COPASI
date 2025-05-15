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

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <cmath>
#include <limits>
#include <string>
#ifdef DEBUG_OPT
# include <iostream>
# include <fstream>
#endif

#include "copasi/copasi.h"

#include "COptMethodGA.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "copasi/randomGenerator/CRandom.h"
#include "copasi/randomGenerator/CPermutation.h"
#include "copasi/utilities/CProcessReport.h"
#include "copasi/utilities/CSort.h"
#include "copasi/core/CDataObjectReference.h"

COptMethodGA::COptMethodGA(const CDataContainer * pParent,
                           const CTaskEnum::Method & methodType,
                           const CTaskEnum::Task & taskType)
  : COptPopulationMethod(pParent, methodType, taskType, true)
  , mCrossOverFalse(0)
  , mCrossOver(0)
  , mEvaluationValue(std::numeric_limits< C_FLOAT64 >::max())
  , mpPermutation(NULL)
  , mLosses(0)
  , mPivot(0)
  , mMutationVariance(0.1)
  , mStopAfterStalledGenerations(0)
  , mBestIndex(C_INVALID_INDEX)

{
  assertParameter("Number of Generations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 200);
  assertParameter("Population Size", CCopasiParameter::Type::UINT, (unsigned C_INT32) 20);
  assertParameter("Random Number Generator", CCopasiParameter::Type::UINT, (unsigned C_INT32) CRandom::mt19937, eUserInterfaceFlag::editable);
  assertParameter("Seed", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);
  assertParameter("Mutation Variance", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) 0.1, eUserInterfaceFlag::editable);
  assertParameter("Stop after # Stalled Generations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);

  initObjects();
}

COptMethodGA::COptMethodGA(const COptMethodGA & src,
                           const CDataContainer * pParent,
                           const bool & parallel)
  : COptPopulationMethod(src, pParent, parallel)
  , mCrossOverFalse(0)
  , mCrossOver(0)
  , mEvaluationValue(std::numeric_limits< C_FLOAT64 >::max())
  , mpPermutation(NULL)
  , mLosses(0)
  , mPivot(0)
  , mMutationVariance(0.1)
  , mStopAfterStalledGenerations(0)
  , mBestIndex(C_INVALID_INDEX)
{
  initObjects();
}

COptMethodGA::~COptMethodGA()
{cleanup();}

bool COptMethodGA::swap(size_t from, size_t to)
{
  std::swap(mIndividuals[to], mIndividuals[from]);
  std::swap(mValues[to], mValues[from]);
  std::swap(mLosses[to], mLosses[from]);

  return true;
}

//mutate one individual
bool COptMethodGA::mutate(size_t index)
{
  CVector< C_FLOAT64 > & Individual = *mIndividuals[index];
  COptProblem *& pOptProblem = mProblemContext.active();
  CRandom *& pRandom = mRandomContext.active();
  const std::vector< COptItem * > & OptItemList = pOptProblem->getOptItemList(true);

  // mutate the parameters
  for (size_t j = 0; j < mVariableSize; j++)
    {
      COptItem & OptItem = *OptItemList[j];
      C_FLOAT64 & mut = Individual[j];

      // calculate the mutated parameter
      mut *= pRandom->getRandomNormal(1, mMutationVariance);
      OptItem.setItemValue(mut, COptItem::CheckPolicyFlag::All);
    }

  return true;
}

bool COptMethodGA::crossover(const CVector< C_FLOAT64 > & parent1,
                             const CVector< C_FLOAT64 > & parent2,
                             CVector< C_FLOAT64 > & child1,
                             CVector< C_FLOAT64 > & child2)
{
  size_t nCross = 0;

  CRandom *& pRandom = mRandomContext.active();
  mCrossOver = mCrossOverFalse;

  if (mVariableSize > 1)
    nCross = pRandom->getRandomU((unsigned C_INT32)(mVariableSize / 2));

  if (nCross == 0)
    {
      // if less than 0 just copy parent to child
      child1 = parent1;
      child2 = parent2;

      return true;
    }

  // choose cross over points;
  // We do not mind if a crossover point gets drawn twice
  for (size_t i = 0; i < nCross; i++)
    mCrossOver[pRandom->getRandomU((unsigned C_INT32)(mVariableSize - 1))] = true;

  const CVector< C_FLOAT64 > * pParent1 = & parent1;
  const CVector< C_FLOAT64 > * pParent2 = & parent2;
  const CVector< C_FLOAT64 > * pTmp;

  for (size_t i = 0; i < mVariableSize; i++)
    {
      if (mCrossOver[i])
        std::swap(pParent1, pParent2);

      child1[i] = pParent1->operator[](i);
      child2[i] = pParent2->operator[](i);
    }

  return true;
}

bool COptMethodGA::replicate()
{
  size_t i;
  // generate a random order for the parents
  mpPermutation->shuffle();

  // reproduce in consecutive pairs
  for (i = 0; i < mPopulationSize / 2; i++)
    crossover(*mIndividuals[mpPermutation->next()],
              *mIndividuals[mpPermutation->next()],
              *mIndividuals[mPopulationSize + i * 2],
              *mIndividuals[mPopulationSize + i * 2 + 1]);

  // check if there is one left over and just copy it
  if (mPopulationSize % 2 > 0)
    *mIndividuals[2 * mPopulationSize - 1] = *mIndividuals[mpPermutation->next()];

  // mutate the offspring

#pragma omp parallel for schedule(runtime)
  for (i = mPopulationSize; i < 2 * mPopulationSize; i++)
    if (proceed())
      {
        mutate(i);
        mValues[i] = evaluate({EvaluationPolicy::Constraints});
      }

  return true;
}

// select mPopulationSize individuals
bool COptMethodGA::select()
{
  size_t i, j, nopp, opp;
  size_t TotalPopulation = 2 * mPopulationSize;

  // tournament competition
  mLosses = 0; // Set all wins to 0.

  // compete with ~ 20% of the TotalPopulation
  nopp = std::max<size_t>(1, mPopulationSize / 5);
  CRandom * pRandom = mRandomContext.master();

  // parents and offspring are all in competition
  for (i = 0; i < TotalPopulation; i++)
    for (j = 0; j < nopp; j++)
      {
        // get random opponent
        do
          {
            opp = pRandom->getRandomU((unsigned C_INT32)(TotalPopulation - 1));
          }
        while (i == opp);

        if (mValues[i] < mValues[opp])
          mLosses[opp]++;
        else
          mLosses[i]++;
      }

  // selection of top mPopulationSize winners
  partialSortWithPivot(mLosses.array(),
                       mLosses.array() + mPopulationSize,
                       mLosses.array() + TotalPopulation,
                       mPivot);

  FSwapClass<COptMethodGA, size_t, bool> Swap(this, &COptMethodGA::swap);
  applyPartialPivot(mPivot, mPopulationSize, Swap);

  return true;
}

// check the best individual at this generation
size_t COptMethodGA::fittest()
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

#ifdef DEBUG_OPT
// serialize the population to a file for debugging purposes
bool COptMethodGA::serializepop(size_t first, size_t last)
{
  size_t Last = std::min(last, (size_t) mPopulationSize);

  size_t i;
  size_t j;

  std::ofstream ofile;
//std::ifstream test("gapop.txt");
//if(!test.good() ) return false;

  // open the file for output, in append mode
  ofile.open("gapop.txt", std::ios::out | std::ios::app);

  if (! ofile.is_open())
    {
      std::cerr << "error opening file \'gapop.txt\'" << std::endl;
      return false;
    }

  for (i = first; i < Last; i++)
    {
      for (j = 0; j < mVariableSize; j++)
        {
          C_FLOAT64 & mut = (*mIndividuals[i])[j];
          // print this parameter
          ofile << mut << "\t";
        }

      // print the fitness of the individual
      ofile << mValues[i] << std::endl;
    }

  ofile << std::endl;
  ofile.close();
  return true;
}
#endif

// initialise the population
bool COptMethodGA::creation(size_t first,
                            size_t last)
{
  size_t Last = std::min(last, (size_t) mPopulationSize);
  size_t i;

#pragma omp parallel for schedule(runtime)
  for (i = first; i < Last; i++)
    {
      createIndividual(i, COptItem::CheckPolicyFlag::All);
      mValues[i] = evaluate({EvaluationPolicy::Constraints});
    }

  return true;
}

void COptMethodGA::initObjects()
{}

bool COptMethodGA::initialize()
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

  mIndividuals.resize(2 * mPopulationSize);

  mGenerations = (unsigned C_INT32)getValue< unsigned C_INT32 >("Number of Generations");
  mCurrentGeneration = 0;

  for (i = 0; i < 2 * mPopulationSize; i++)
    mIndividuals[i] = new CVector< C_FLOAT64 >(mVariableSize);

  mCrossOverFalse.resize(mVariableSize);
  mCrossOverFalse = false;
  mCrossOver.resize(mVariableSize);

  mValues.resize(2 * mPopulationSize);
  mValues = std::numeric_limits<C_FLOAT64>::infinity();

  mpPermutation = new CPermutation(mRandomContext.master(), mPopulationSize);

  mLosses.resize(2 * mPopulationSize);

  // Initialize the variance for mutations
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

bool COptMethodGA::cleanup()
{
  pdelete(mpPermutation);

  return COptPopulationMethod::cleanup();
}

bool COptMethodGA::optimise()
{
  if (!initialize())
    {
      // initialisation failed, we exit
      if (mProcessReport
          && !mProcessReport.finishItem(mhGenerations))
        signalStop();

      return false;
    }

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry(
        "Algorithm started.",
        "For more information about this method see: http://copasi.org/Support/User_Manual/Methods/Optimization_Methods/Genetic_Algorithm/"
      )
    );

  // Counters to determine whether the optimization process has stalled
  // They count the number of generations without advances.
  size_t Stalled, Stalled10, Stalled30, Stalled50;
  Stalled = Stalled10 = Stalled30 = Stalled50 = 0;

  size_t i;
  createIndividual(C_INVALID_INDEX, COptItem::CheckPolicyFlag::All);
  mValues[0] = evaluate({EvaluationPolicy::Constraints});
  setSolution(mValues[0], *mIndividuals[0], true);

  // the others are random
  creation(1, 2 * mPopulationSize);

#ifdef DEBUG_OPT
  serializepop(0, mPopulationSize);
#endif

  select();
  mBestIndex = fittest();

  if (mBestIndex != C_INVALID_INDEX &&
      mValues[mBestIndex] < getBestValue())
    setSolution(mValues[mBestIndex], *mIndividuals[mBestIndex], true);

  // test if the user wants to stop, and do so if needed
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

  // ITERATE FOR gener GENERATIONS
  for (mCurrentGeneration = 2;
       mCurrentGeneration <= mGenerations && proceed();
       mCurrentGeneration++, Stalled++, Stalled10++, Stalled30++, Stalled50++)
    {

      if (mStopAfterStalledGenerations != 0 && Stalled > mStopAfterStalledGenerations)
        break;

      // perturb the population if we have stalled for a while
      if (Stalled > 50 && Stalled50 > 50)
        {
          if (mLogVerbosity > 0)
            mMethodLog.enterLogEntry(
              COptLogEntry(
                "Generation " + std::to_string(mCurrentGeneration) +
                ": Fittest individual has not changed for the last " + std::to_string(Stalled50 - 1) +
                " generations. 50% of individuals randomized."
              ));

          creation((size_t)(mPopulationSize / 2), mPopulationSize);
          Stalled10 = Stalled30 = Stalled50 = 0;
        }
      else if (Stalled > 30 && Stalled30 > 30)
        {
          if (mLogVerbosity > 0)
            mMethodLog.enterLogEntry(
              COptLogEntry(
                "Generation " + std::to_string(mCurrentGeneration) +
                ": Fittest individual has not changed for the last " + std::to_string(Stalled30 - 1) +
                " generations. 30% of individuals randomized."
              ));

          creation((size_t)(mPopulationSize * 0.7), mPopulationSize);
          Stalled10 = Stalled30 = 0;
        }
      else if (Stalled > 10 && Stalled10 > 10)
        {
          if (mLogVerbosity > 0)
            mMethodLog.enterLogEntry(
              COptLogEntry(
                "Generation " + std::to_string(mCurrentGeneration) +
                ": Fittest individual has not changed for the last " + std::to_string(Stalled10 - 1) +
                " generations. 10% of individuals randomized."
              ));

          creation((size_t)(mPopulationSize * 0.9), mPopulationSize);
          Stalled10 = 0;
        }
      // replicate the individuals
      else
        replicate();

      // select the most fit
      select();

      // get the index of the fittest
      mBestIndex = fittest();

      if (mBestIndex != C_INVALID_INDEX
          && mValues[mBestIndex] < getBestValue()
          && setSolution(mValues[mBestIndex], *mIndividuals[mBestIndex], true))
        {
          // reset the stalled counters, since we made progress this time
          Stalled = Stalled10 = Stalled30 = Stalled50 = 0;
        }

      if (mProcessReport
          && !mProcessReport.progressItem(mhGenerations))
        signalStop();

      //use a different output channel. It will later get a proper enum name
      mpParentTask->output(COutputInterface::MONITORING);

#ifdef DEBUG_OPT
      serializepop(0, mPopulationSize);
#endif
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

unsigned C_INT32 COptMethodGA::getMaxLogVerbosity() const
{
  return 1;
}
