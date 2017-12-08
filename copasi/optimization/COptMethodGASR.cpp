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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <cmath>

#include "copasi.h"

#include "COptMethodGASR.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "randomGenerator/CRandom.h"
#include "randomGenerator/CPermutation.h"
#include "utilities/CProcessReport.h"
#include "copasi/core/CDataObjectReference.h"

COptMethodGASR::COptMethodGASR(const CDataContainer * pParent,
                               const CTaskEnum::Method & methodType,
                               const CTaskEnum::Task & taskType):
  COptPopulationMethod(pParent, methodType, taskType),
  mCrossOverFalse(0),
  mCrossOver(0),
  mpPermutation(NULL),
  mWins(0),
  mMutationVarians(0.1),
  mStopAfterStalledGenerations(0),
  mEvaluationValue(std::numeric_limits< C_FLOAT64 >::max()),
  mBestValue(std::numeric_limits< C_FLOAT64 >::max()),
  mBestIndex(C_INVALID_INDEX)
{
  addParameter("Number of Generations", CCopasiParameter::UINT, (unsigned C_INT32) 200);
  addParameter("Population Size", CCopasiParameter::UINT, (unsigned C_INT32) 20);
  addParameter("Random Number Generator", CCopasiParameter::UINT, (unsigned C_INT32) CRandom::mt19937);
  addParameter("Seed", CCopasiParameter::UINT, (unsigned C_INT32) 0);
  addParameter("Pf", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.475);  //*****ADDED for SR

  if (mEnableAdditionalParameters)
  {
    addParameter("Mutation Variance", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.1);
    addParameter("Stop after # Stalled Generations", CCopasiParameter::UINT, (unsigned C_INT32) 0);
  }

  addParameter("#LogVerbosity", CCopasiParameter::UINT, (unsigned C_INT32) 0);

  initObjects();
}

COptMethodGASR::COptMethodGASR(const COptMethodGASR & src,
                               const CDataContainer * pParent):
  COptPopulationMethod(src, pParent),
  mCrossOverFalse(0),
  mCrossOver(0),
  mpPermutation(NULL),
  mWins(0),
  mMutationVarians(0.1),
  mStopAfterStalledGenerations(0),
  mEvaluationValue(std::numeric_limits< C_FLOAT64 >::max()),
  mBestValue(std::numeric_limits< C_FLOAT64 >::max()),
  mBestIndex(C_INVALID_INDEX)
{initObjects();}

COptMethodGASR::~COptMethodGASR()
{cleanup();}

// evaluate the fitness of one individual
bool COptMethodGASR::evaluate(const CVector< C_FLOAT64 > & /* individual */)
{
  bool Continue = true;

  // We do not need to check whether the parametric constraints are fulfilled
  // since this method allows for parameters outside the bounds

  // evaluate the fitness
  Continue = mpOptProblem->calculate();

  // We do not need to check whether the functional constraints are fulfilled
  // since this method allows for solutions outside the bounds.

  mEvaluationValue = mpOptProblem->getCalculateValue();

  return Continue;
}

bool COptMethodGASR::swap(size_t from, size_t to)
{
  CVector< C_FLOAT64 > * pTmp = mIndividuals[to];
  mIndividuals[to] = mIndividuals[from];
  mIndividuals[from] = pTmp;

  //**** Added for swapping individual Phi values also for Stochastic Ranking
  C_FLOAT64 dTmp = mPhi[to];
  mPhi[to] = mPhi[from];
  mPhi[from] = dTmp;

  dTmp = mValues[to];
  mValues[to] = mValues[from];
  mValues[from] = dTmp;

  size_t iTmp = mWins[to];
  mWins[to] = mWins[from];
  mWins[from] = iTmp;

  return true;
}

//mutate one individual
bool COptMethodGASR::mutate(CVector< C_FLOAT64 > & individual)
{
  size_t j;

  // mutate the parameters
  for (j = 0; j < mVariableSize; j++)
    {
      C_FLOAT64 & mut = individual[j];

      // calculate the mutated parameter
      mut *= mpRandom->getRandomNormal(1, mMutationVarians);

      // for SR do not force to be within bounds

      // We need to set the value here so that further checks take
      // account of the value.
      *mContainerVariables[j] = mut;
    }

  return true;
}

bool COptMethodGASR::crossover(const CVector< C_FLOAT64 > & parent1,
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

bool COptMethodGASR::replicate()
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
      Continue = evaluate(*mIndividuals[i]);
      mValues[i] = mEvaluationValue;

      /* Calculate the phi value of the individual for SR*/
      mPhi[i] = phi(i);
    }

  return Continue;
}

// select mPopulationSize individuals
bool COptMethodGASR::select()
{
  size_t i, j;
  size_t TotalPopulation = 2 * mPopulationSize;
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
          if ((mPhi[j] == 0 && mPhi[j + 1] == 0) ||              // within bounds
              (mpRandom->getRandomOO() < mPf))      // random chance to compare values outside bounds
            {
              // compare obj fcn using mValue alternative code
              if (mValues[j] > mValues[j + 1])
                {
                  swap(j, j + 1);
                  wasSwapped = true;
                }
            }
          else //mPhi values are not equal and not within boundary
            {
              if (mPhi[j] > mPhi[j + 1]) // j further outside then j+1
                {
                  swap(j, j + 1);
                  wasSwapped = true;
                }
            }
        }

      // if no swap then break
      if (wasSwapped == false) break;
    }

  return true;
}

// evaluate the distance of parameters and constraints to boundaries
C_FLOAT64 COptMethodGASR::phi(size_t indivNum)
{
  C_FLOAT64 phiVal = 0.0;
  C_FLOAT64 phiCalc;

  std::vector< COptItem * >::const_iterator it = mpOptItem->begin();
  std::vector< COptItem * >::const_iterator end = mpOptItem->end();
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

  it = mpOptContraints->begin();
  end = mpOptContraints->end();

  for (; it != end; ++it)
    {
      phiCalc = (*it)->getConstraintViolation();

      if (phiCalc > 0.0)
        phiVal += phiCalc * phiCalc;
    }

  return phiVal;
}

// check the best individual at this generation
size_t COptMethodGASR::fittest()
{
  size_t i, BestIndex = C_INVALID_INDEX;
  C_FLOAT64 BestValue = std::numeric_limits< C_FLOAT64 >::max();

  for (i = 0; i < mPopulationSize; i++)
    if (mValues[i] < BestValue && !(mPhi[i] != 0))
      {
        BestIndex = i;
        BestValue = mValues[i];
      }

  return BestIndex;
}

// initialize the population
bool COptMethodGASR::creation(size_t first,
                              size_t last)
{
  size_t Last = std::min< size_t >(last, mPopulationSize);

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

          // We need to set the value here so that further checks take
          // account of the value.
          *mContainerVariables[j] = mut;
        }

      // calculate its fitness
      Continue = evaluate(*mIndividuals[i]);
      mValues[i] = mEvaluationValue;

      /* Calculate the phi value of the individual for SR*/
      mPhi[i] = phi(i);
    }

  return Continue;
}

void COptMethodGASR::initObjects()
{
}

bool COptMethodGASR::initialize()
{
  cleanup();

  size_t i;

  if (!COptPopulationMethod::initialize()) return false;

  mLogVerbosity = getValue< unsigned C_INT32 >("#LogVerbosity");

  mCurrentGeneration = 0;
  mGenerations = getValue< unsigned C_INT32 >("Number of Generations");

  if (mpCallBack)
    mhGenerations =
      mpCallBack->addItem("Current Generation",
                          mCurrentGeneration,
                          & mGenerations);

  mCurrentGeneration++;

  mPopulationSize = getValue< unsigned C_INT32 >("Population Size");
  mPf = getValue< C_FLOAT64 >("Pf");

  if (mPf < 0.0 || 1.0 < mPf)
    {
      mPf = 0.475;
      setValue("Pf", mPf);

      mMethodLog.enterLogItem(COptLogItem(COptLogItem::GASR_usrdef_error_pf).with(mPf));
    }

  mIndividuals.resize(2 * mPopulationSize);
  mPhi.resize(2 * mPopulationSize);

  for (i = 0; i < 2 * mPopulationSize; i++)
    mIndividuals[i] = new CVector< C_FLOAT64 >(mVariableSize);

  mCrossOverFalse.resize(mVariableSize);
  mCrossOverFalse = false;
  mCrossOver.resize(mVariableSize);

  mValues.resize(2 * mPopulationSize);
  mValues = std::numeric_limits<double>::infinity();

  mpPermutation = new CPermutation(mpRandom, mPopulationSize);

  mWins.resize(2 * mPopulationSize);

  // initialize the variance for mutations
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

bool COptMethodGASR::cleanup()
{
  pdelete(mpPermutation);

  return COptPopulationMethod::cleanup();
}

bool COptMethodGASR::optimise()
{
  bool Continue = true;

  if (!initialize())
    {
      if (mpCallBack)
        mpCallBack->finishItem(mhGenerations);

      return false;
    }

  mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_start).with("OD.Genetic.Algorithm.SR"));

  // Counters to determine whether the optimization process has stalled
  // They count the number of generations without advances.
  size_t Stalled, Stalled10, Stalled30, Stalled50;
  Stalled = Stalled10 = Stalled30 = Stalled50 = 0;

  size_t i;

  // initialize the population
  // first individual is the initial guess
  for (i = 0; i < mVariableSize; i++)
    (*mIndividuals[0])[i] = (*mpOptItem)[i]->getStartValue();

  // calculate the fitness
  size_t j;

  // set the parameter values
  for (j = 0; j < mVariableSize; j++)
    *mContainerVariables[j] = (*mIndividuals[0])[j];

  Continue = evaluate(*mIndividuals[0]);
  mValues[0] = mEvaluationValue;

  /* Calculate the phi value of the individual for SR*/
  mPhi[0] = phi(0);

  // the others are random
  Continue = creation(1, mPopulationSize);

  // get the index of the fittest
  mBestIndex = fittest();

  if (mBestIndex != C_INVALID_INDEX)
    {
      // and store that value
      mBestValue = mValues[mBestIndex];
      Continue = mpOptProblem->setSolution(mBestValue, *mIndividuals[mBestIndex]);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

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
          if (mLogVerbosity >= 1) mMethodLog.enterLogItem(COptLogItem(COptLogItem::GASR_fittest_not_changed_x_random_generated).iter(mCurrentGeneration).with(Stalled50 - 1).with(50));

          Continue = creation((size_t)(mPopulationSize * 0.5),
                              mPopulationSize);
          Stalled10 = Stalled30 = Stalled50 = 0;
        }
      else if (Stalled > 30 && Stalled30 > 30)
        {
          if (mLogVerbosity >= 1) mMethodLog.enterLogItem(COptLogItem(COptLogItem::GASR_fittest_not_changed_x_random_generated).iter(mCurrentGeneration).with(Stalled50 - 1).with(30));

          Continue = creation((size_t)(mPopulationSize * 0.7),
                              mPopulationSize);
          Stalled10 = Stalled30 = 0;
        }
      else if (Stalled > 10 && Stalled10 > 10)
        {
          if (mLogVerbosity >= 1) mMethodLog.enterLogItem(COptLogItem(COptLogItem::GASR_fittest_not_changed_x_random_generated).iter(mCurrentGeneration).with(Stalled50 - 1).with(10));

          Continue = creation((size_t)(mPopulationSize * 0.9),
                              mPopulationSize);
          Stalled10 = 0;
        }
      // replicate the individuals
      else
        Continue = replicate();

      // select the most fit
      Continue = select();

      // get the index of the fittest
      mBestIndex = fittest();

      if (mBestIndex != C_INVALID_INDEX &&
          mValues[mBestIndex] < mBestValue)
        {
          Stalled = Stalled10 = Stalled30 = Stalled50 = 0;
          mBestValue = mValues[mBestIndex];

          Continue = mpOptProblem->setSolution(mBestValue, *mIndividuals[mBestIndex]);

          // We found a new best value lets report it.
          mpParentTask->output(COutputInterface::DURING);
        }

      if (mpCallBack)
        Continue = mpCallBack->progressItem(mhGenerations);

      //use a different output channel. It will later get a proper enum name
      mpParentTask->output(COutputInterface::MONITORING);
    }

  mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_finish_x_of_max_gener).iter(mCurrentGeneration - 1).with(mGenerations));

  if (mpCallBack)
    mpCallBack->finishItem(mhGenerations);

  cleanup();

  return true;
}

unsigned C_INT32 COptMethodGASR::getMaxLogVerbosity() const
{
  return 1;
}
