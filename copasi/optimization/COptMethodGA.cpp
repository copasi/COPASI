// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"

#include "COptMethodGA.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "randomGenerator/CRandom.h"
#include "randomGenerator/CPermutation.h"
#include "utilities/CProcessReport.h"
#include "utilities/CSort.h"
#include "copasi/core/CDataObjectReference.h"

COptMethodGA::COptMethodGA(const CDataContainer * pParent,
  const CTaskEnum::Method & methodType,
  const CTaskEnum::Task & taskType) :
  COptPopulationMethod(pParent, methodType, taskType),
  mCrossOverFalse(0),
  mCrossOver(0),
  mEvaluationValue(std::numeric_limits< C_FLOAT64 >::max()),
  mpPermutation(NULL),
  mLosses(0),
  mPivot(0),
  mMutationVarians(0.1),
  mStopAfterStalledGenerations(0),
  mBestValue(std::numeric_limits< C_FLOAT64 >::max()),
  mBestIndex(C_INVALID_INDEX)

{
  addParameter("Number of Generations", CCopasiParameter::UINT, (unsigned C_INT32) 200);
  addParameter("Population Size", CCopasiParameter::UINT, (unsigned C_INT32) 20);
  addParameter("Random Number Generator", CCopasiParameter::UINT, (unsigned C_INT32) CRandom::mt19937);
  addParameter("Seed", CCopasiParameter::UINT, (unsigned C_INT32) 0);

  if (mEnableAdditionalParameters)
  {
    addParameter("Mutation Variance", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.1);
    addParameter("Stop after # Stalled Generations", CCopasiParameter::UINT, (unsigned C_INT32) 0);
  }

  addParameter("Log Verbosity", CCopasiParameter::UINT, (unsigned C_INT32) 0);

  initObjects();
}

COptMethodGA::COptMethodGA(const COptMethodGA & src,
                           const CDataContainer * pParent):
  COptPopulationMethod(src, pParent),
  mCrossOverFalse(0),
  mCrossOver(0),
  mEvaluationValue(std::numeric_limits< C_FLOAT64 >::max()),
  mpPermutation(NULL),
  mLosses(0),
  mPivot(0),
  mMutationVarians(0.1),
  mStopAfterStalledGenerations(0),
  mBestValue(std::numeric_limits< C_FLOAT64 >::max()),
  mBestIndex(C_INVALID_INDEX)
{initObjects();}

COptMethodGA::~COptMethodGA()
{cleanup();}

// evaluate the fitness of one individual
bool COptMethodGA::evaluate(const CVector< C_FLOAT64 > & /* individual */)
{
  bool Continue = true;

  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  // evaluate the fitness
  Continue &= mpOptProblem->calculate();

  // check whether the functional constraints are fulfilled
  if (!mpOptProblem->checkFunctionalConstraints())
    mEvaluationValue = std::numeric_limits<C_FLOAT64>::infinity();
  else
    mEvaluationValue = mpOptProblem->getCalculateValue();

  return Continue;
}

bool COptMethodGA::swap(size_t from, size_t to)
{
  CVector< C_FLOAT64 > * pTmp = mIndividuals[to];
  mIndividuals[to] = mIndividuals[from];
  mIndividuals[from] = pTmp;

  C_FLOAT64 dTmp = mValues[to];
  mValues[to] = mValues[from];
  mValues[from] = dTmp;

  size_t iTmp = mLosses[to];
  mLosses[to] = mLosses[from];
  mLosses[from] = iTmp;

  return true;
}

//mutate one individual
bool COptMethodGA::mutate(CVector< C_FLOAT64 > & individual)
{
  size_t j;

  // mutate the parameters
  for (j = 0; j < mVariableSize; j++)
    {
      COptItem & OptItem = *(*mpOptItem)[j];
      C_FLOAT64 & mut = individual[j];

      // calculate the mutated parameter
      mut *= mpRandom->getRandomNormal(1, mMutationVarians);

      // force it to be within the bounds
      switch (OptItem.checkConstraint(mut))
        {
          case - 1:
            mut = *OptItem.getLowerBoundValue();
            break;

          case 1:
            mut = *OptItem.getUpperBoundValue();
            break;
        }

      // We need to set the value here so that further checks take
      // account of the value.
      *mContainerVariables[j] = mut;
    }

  return true;
}

bool COptMethodGA::crossover(const CVector< C_FLOAT64 > & parent1,
                             const CVector< C_FLOAT64 > & parent2,
                             CVector< C_FLOAT64 > & child1,
                             CVector< C_FLOAT64 > & child2)
{
  size_t i, crp;
  size_t nCross = 0;

  mCrossOver = mCrossOverFalse;

  if (mVariableSize > 1)
    nCross = mpRandom->getRandomU((unsigned C_INT32)(mVariableSize / 2));

  if (nCross == 0)
    {
      // if less than 0 just copy parent to child
      child1 = parent1;
      child2 = parent2;

      return true;
    }

  // choose cross over points;
  // We do not mind if a crossover point gets drawn twice
  for (i = 0; i < nCross; i++)
    {
      crp = mpRandom->getRandomU((unsigned C_INT32)(mVariableSize - 1));
      mCrossOver[crp] = true;
    }

  const CVector< C_FLOAT64 > * pParent1 = & parent1;

  const CVector< C_FLOAT64 > * pParent2 = & parent2;

  const CVector< C_FLOAT64 > * pTmp;

  for (i = 0; i < mVariableSize; i++)
    {
      if (mCrossOver[i])
        {
          pTmp = pParent1;
          pParent1 = pParent2;
          pParent2 = pTmp;
        }

      child1[i] = (*pParent1)[i];
      child2[i] = (*pParent2)[i];
    }

  return true;
}

bool COptMethodGA::replicate()
{
  size_t i;
  bool Continue = true;

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
    *mIndividuals[2 * mPopulationSize - 1] = *mIndividuals[mPopulationSize - 1];

  // mutate the offspring
  for (i = mPopulationSize; i < 2 * mPopulationSize && Continue; i++)
    {
      mutate(*mIndividuals[i]);
      Continue &= evaluate(*mIndividuals[i]);
      mValues[i] = mEvaluationValue;
    }

  return Continue;
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

  // parents and offspring are all in competition
  for (i = 0; i < TotalPopulation; i++)
    for (j = 0; j < nopp; j++)
      {
        // get random opponent
        do
          {
            opp = mpRandom->getRandomU((unsigned C_INT32)(TotalPopulation - 1));
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

  for (i = 0; i < mPopulationSize && !mLosses[i]; i++)
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
  size_t j;

  C_FLOAT64 mn;
  C_FLOAT64 mx;
  C_FLOAT64 la;

  bool Continue = true;

  for (i = first; i < Last && Continue; i++)
    {
      for (j = 0; j < mVariableSize; j++)
        {
          // calculate lower and upper bounds
          COptItem & OptItem = *(*mpOptItem)[j];
          mn = *OptItem.getLowerBoundValue();
          mx = *OptItem.getUpperBoundValue();

          C_FLOAT64 & mut = (*mIndividuals[i])[j];

          try
            {
              // determine if linear or log scale
              if ((mn < 0.0) || (mx <= 0.0))
                mut = mn + mpRandom->getRandomCC() * (mx - mn);
              else
                {
                  la = log10(mx) - log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min()));

                  if (la < 1.8)
                    mut = mn + mpRandom->getRandomCC() * (mx - mn);
                  else
                    mut = pow(10.0, log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min())) + la * mpRandom->getRandomCC());
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
                break;

              case 1:
                mut = *OptItem.getUpperBoundValue();
                break;
            }

          // We need to set the value here so that further checks take
          // account of the value.
          *mContainerVariables[j] = mut;
        }

      // calculate its fitness
      Continue &= evaluate(*mIndividuals[i]);
      mValues[i] = mEvaluationValue;
    }

  return Continue;
}

void COptMethodGA::initObjects()
{
}

bool COptMethodGA::initialize()
{
  cleanup();

  size_t i;

  if (!COptPopulationMethod::initialize())
    {
      if (mpCallBack)
        mpCallBack->finishItem(mhGenerations);

      return false;
    }

  mIndividuals.resize(2 * mPopulationSize);

  mLogVerbosity = getValue< unsigned C_INT32 >("Log Verbosity");

  mGenerations = (unsigned C_INT32)getValue< unsigned C_INT32 >("Number of Generations");
  mCurrentGeneration = 0;

  for (i = 0; i < 2 * mPopulationSize; i++)
    mIndividuals[i] = new CVector< C_FLOAT64 >(mVariableSize);

  mCrossOverFalse.resize(mVariableSize);
  mCrossOverFalse = false;
  mCrossOver.resize(mVariableSize);

  mValues.resize(2 * mPopulationSize);
  mValues = std::numeric_limits<C_FLOAT64>::infinity();
  mBestValue = std::numeric_limits<C_FLOAT64>::infinity();

  mpPermutation = new CPermutation(mpRandom, mPopulationSize);

  mLosses.resize(2 * mPopulationSize);

  // Initialize the variance for mutations
  mMutationVarians = 0.1;

  if (getParameter("Mutation Variance"))
  {
    mMutationVarians = getValue< C_FLOAT64 >("Mutation Variance");

    if (mMutationVarians < 0.0 || 1.0 < mMutationVarians)
    {
      mMutationVarians = 0.1;
      setValue("Mutation Variance", mMutationVarians);
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
  bool Continue = true;

  if (!initialize())
    {
      // initialisation failed, we exit
      if (mpCallBack)
        mpCallBack->finishItem(mhGenerations);

      return false;
    }

  mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_start).with("OD.Genetic.Algorithm"));

  // Counters to determine whether the optimization process has stalled
  // They count the number of generations without advances.
  size_t Stalled, Stalled10, Stalled30, Stalled50;
  Stalled = Stalled10 = Stalled30 = Stalled50 = 0;

  size_t i;

  // initialise the population
  // first individual is the initial guess
  bool pointInParameterDomain = true;

  for (i = 0; i < mVariableSize; i++)
    {
      C_FLOAT64 & mut = (*mIndividuals[0])[i];
      COptItem & OptItem = *(*mpOptItem)[i];

      mut = OptItem.getStartValue();

      // force it to be within the bounds
      switch (OptItem.checkConstraint(mut))
        {
          case - 1:
            mut = *OptItem.getLowerBoundValue();
            pointInParameterDomain = false;
            break;

          case 1:
            mut = *OptItem.getUpperBoundValue();
            pointInParameterDomain = false;
            break;
        }

      // We need to set the value here so that further checks take
      // account of the value.
      *mContainerVariables[i] = mut;
    }

  if (!pointInParameterDomain) mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_initial_point_out_of_domain));

  Continue &= evaluate(*mIndividuals[0]);
  mValues[0] = mEvaluationValue;

  if (!isnan(mEvaluationValue))
    {
      // and store that value
      mBestValue = mValues[0];
      Continue &= mpOptProblem->setSolution(mBestValue, *mIndividuals[0]);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  // the others are random
  Continue &= creation(1, 2 * mPopulationSize);

#ifdef DEBUG_OPT
  serializepop(0, mPopulationSize);
#endif

  Continue &= select();
  mBestIndex = fittest();

  if (mBestIndex != C_INVALID_INDEX &&
      mValues[mBestIndex] < mBestValue)
    {
      // and store that value
      mBestValue = mValues[mBestIndex];
      Continue = mpOptProblem->setSolution(mBestValue, *mIndividuals[mBestIndex]);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  // test if the user wants to stop, and do so if needed
  if (!Continue)
    {
      mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_early_stop));

      if (mpCallBack)
        mpCallBack->finishItem(mhGenerations);

      cleanup();
      return true;
    }

  // ITERATE FOR gener GENERATIONS
  for (mCurrentGeneration = 2;
       mCurrentGeneration <= mGenerations && Continue;
       mCurrentGeneration++, Stalled++, Stalled10++, Stalled30++, Stalled50++)
    {

      if (mStopAfterStalledGenerations != 0 && Stalled > mStopAfterStalledGenerations)
        break;

      // perturb the population if we have stalled for a while
      if (Stalled > 50 && Stalled50 > 50)
        {
          if (mLogVerbosity >= 1) mMethodLog.enterLogItem(COptLogItem(COptLogItem::GA_fittest_not_changed_x_random_generated).iter(mCurrentGeneration).with(Stalled50 - 1).with(50));

          Continue &= creation((size_t)(mPopulationSize / 2),
                               mPopulationSize);
          Stalled10 = Stalled30 = Stalled50 = 0;
        }
      else if (Stalled > 30 && Stalled30 > 30)
        {
          if (mLogVerbosity >= 1) mMethodLog.enterLogItem(COptLogItem(COptLogItem::GA_fittest_not_changed_x_random_generated).iter(mCurrentGeneration).with(Stalled50 - 1).with(30));

          Continue &= creation((size_t)(mPopulationSize * 0.7),
                               mPopulationSize);
          Stalled10 = Stalled30 = 0;
        }
      else if (Stalled > 10 && Stalled10 > 10)
        {
          if (mLogVerbosity >= 1) mMethodLog.enterLogItem(COptLogItem(COptLogItem::GA_fittest_not_changed_x_random_generated).iter(mCurrentGeneration).with(Stalled50 - 1).with(10));

          Continue &= creation((size_t)(mPopulationSize * 0.9),
                               mPopulationSize);
          Stalled10 = 0;
        }
      // replicate the individuals
      else
        Continue &= replicate();

      // select the most fit
      Continue &= select();

      // get the index of the fittest
      mBestIndex = fittest();

      if (mBestIndex != C_INVALID_INDEX &&
          mValues[mBestIndex] < mBestValue)
        {
          // reset the stalled counters, since we made progress this time
          Stalled = Stalled10 = Stalled30 = Stalled50 = 0;
          // keep best value
          mBestValue = mValues[mBestIndex];
          // pass the current best value upstream
          Continue &= mpOptProblem->setSolution(mBestValue, *mIndividuals[mBestIndex]);
          // We found a new best value lets report it.
          mpParentTask->output(COutputInterface::DURING);
        }

      if (mpCallBack)
        Continue &= mpCallBack->progressItem(mhGenerations);

      //use a different output channel. It will later get a proper enum name
      mpParentTask->output(COutputInterface::MONITORING);

#ifdef DEBUG_OPT
      serializepop(0, mPopulationSize);
#endif
    }

  mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_finish_x_of_max_gener).iter(mCurrentGeneration - 1).with(mGenerations));

  if (mpCallBack)
    mpCallBack->finishItem(mhGenerations);

  cleanup();
  return true;
}

unsigned C_INT32 COptMethodGA::getMaxLogVerbosity() const
{
  return 1;
}
