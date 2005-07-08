/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodGASR.cpp,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/07/08 19:35:59 $
   End CVS Header */

#include <float.h>

#include "copasi.h"
#include "mathematics.h"
#include "COptMethod.h"
#include "COptProblem.h"
#include "COptItem.h"

#include "randomGenerator/CRandom.h"
#include "utilities/CProcessReport.h"
#include "report/CCopasiObjectReference.h"

COptMethodGASR::COptMethodGASR(const CCopasiContainer * pParent):
    COptMethod(CCopasiMethod::GeneticAlgorithmSR, pParent),
    mGenerations(0),
    mPopulationSize(0),
    mpRandom(NULL),
    mVariableSize(0),
    mIndividual(0),
    mCrossOverFalse(0),
    mCrossOver(0),
    mEvaluationValue(DBL_MAX),
    mValue(0),
    mShuffle(0),
    mWins(0),
    mMutationVarians(0.1),
    mBestValue(DBL_MAX),
    mBestIndex(C_INVALID_INDEX),
    mGeneration(0)

{
  addParameter("Number of Generations", CCopasiParameter::UINT, (unsigned C_INT32) 200);
  addParameter("Population Size", CCopasiParameter::UINT, (unsigned C_INT32) 20);
  addParameter("Random Number Generator", CCopasiParameter::UINT, (unsigned C_INT32) CRandom::mt19937);
  addParameter("Seed", CCopasiParameter::UINT, (unsigned C_INT32) 0);
  addParameter("Pf", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.475);  //*****ADDED for SR
}

COptMethodGASR::COptMethodGASR(const COptMethodGASR & src,
                               const CCopasiContainer * pParent):
    COptMethod(src, pParent),
    mGenerations(0),
    mPopulationSize(0),
    mpRandom(NULL),
    mVariableSize(0),
    mIndividual(0),
    mCrossOverFalse(0),
    mCrossOver(0),
    mEvaluationValue(DBL_MAX),
    mValue(0),
    mShuffle(0),
    mWins(0),
    mMutationVarians(0.1),
    mBestValue(DBL_MAX),
    mBestIndex(C_INVALID_INDEX),
    mGeneration(0)
{}

COptMethodGASR::~COptMethodGASR()
{cleanup();}

bool COptMethodGASR::setCallBack(CProcessReport * pCallBack)
{
  CCopasiMethod::setCallBack(pCallBack);

  mGeneration = 0;
  mhGenerations =
    pCallBack->addItem("Current Generation",
                       CCopasiParameter::UINT,
                       & mGeneration,
                       & mGenerations);

  return true;
}

// evaluate the fitness of one individual
bool COptMethodGASR::evaluate(const CVector< C_FLOAT64 > & individual)
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

bool COptMethodGASR::swap(unsigned C_INT32 from, unsigned C_INT32 to)
{
  CVector< C_FLOAT64 > * pTmp = mIndividual[to];
  mIndividual[to] = mIndividual[from];
  mIndividual[from] = pTmp;

  //**** Added for swapping individual Phi values also for Stochastic Ranking
  C_FLOAT64 dTmp = mPhi[to];
  mPhi[to] = mPhi[from];
  mPhi[from] = dTmp;

  dTmp = mValue[to];
  mValue[to] = mValue[from];
  mValue[from] = dTmp;

  C_INT32 iTmp = mWins[to];
  mWins[to] = mWins[from];
  mWins[from] = iTmp;

  return true;
}

//mutate one individual
bool COptMethodGASR::mutate(CVector< C_FLOAT64 > & individual)
{
  unsigned C_INT32 j;

  // mutate the parameters
  for (j = 0; j < mVariableSize; j++)
    {
      COptItem & OptItem = *(*mpOptItem)[j];
      C_FLOAT64 & mut = individual[j];

      // calculate the mutatated parameter
      mut *= mpRandom->getRandomNormal(1, mMutationVarians);

      // for SR do not force to be within bounds

      // We need to set the value here so that further checks take
      // account of the value.
      (*(*mpSetCalculateVariable)[j])(mut);
    }

  return true;
}

bool COptMethodGASR::crossover(const CVector< C_FLOAT64 > & parent1,
                               const CVector< C_FLOAT64 > & parent2,
                               CVector< C_FLOAT64 > & child1,
                               CVector< C_FLOAT64 > & child2)
{
  unsigned C_INT32 i, crp;
  unsigned C_INT32 nCross = 0;

  mCrossOver = mCrossOverFalse;

  if (mVariableSize > 1)
    nCross = mpRandom->getRandomU(mVariableSize / 2);

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
      crp = mpRandom->getRandomU(mVariableSize - 1);
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

bool COptMethodGASR::shuffle()
{
  unsigned C_INT32 i, from, to, tmp;

  //  Why sort first? We can just keep shuffling.
  //  for(i=0; i<mPopulationSize; i++) mShuffle[i] = i;

  for (i = 0; i < mPopulationSize / 2; i++)
    {
      from = mpRandom->getRandomU(mPopulationSize - 1);
      to = mpRandom->getRandomU(mPopulationSize - 1);

      tmp = mShuffle[to];
      mShuffle[to] = mShuffle[from];
      mShuffle[from] = tmp;
    }

  return true;
}

bool COptMethodGASR::replicate()
{
  unsigned C_INT32 i;
  bool Continue = true;

  // generate a random order for the parents
  shuffle();

  // reproduce in consecutive pairs
  for (i = 0; i < mPopulationSize / 2; i++)
    crossover(*mIndividual[mShuffle[i * 2]],
              *mIndividual[mShuffle[i * 2 + 1]],
              *mIndividual[mPopulationSize + i * 2],
              *mIndividual[mPopulationSize + i * 2 + 1]);

  // check if there is one left over and just copy it
  if (mPopulationSize % 2 > 0)
    *mIndividual[2 * mPopulationSize - 1] = *mIndividual[mPopulationSize - 1];

  // mutate the offspring
  for (i = mPopulationSize; i < 2 * mPopulationSize && Continue; i++)
    {
      mutate(*mIndividual[i]);
      Continue = evaluate(*mIndividual[i]);
      mValue[i] = mEvaluationValue;

      /* Calculate the phi value of the individual for SR*/
      mPhi[i] = phi(i);
    }

  return Continue;
}

// select mPopulationSize individuals
bool COptMethodGASR::select()
{
  unsigned C_INT32 i, j;
  unsigned C_INT32 TotalPopulation = 2 * mPopulationSize;
  bool wasSwapped;
  unsigned C_INT32 sweepNum = TotalPopulation;  // This is default based on paper

  // Selection Method for Stochastic Ranking
  // stochastic ranking "bubble sort"

  for (i = 0; i < sweepNum; i++) // Here sweepNum is optimal number of sweeps from paper
    {
      wasSwapped = false;

      for (j = 0; j < TotalPopulation - 1; j++)  // lambda is number of individuals
        {
          if ((mPhi[j] == 0 && mPhi[j + 1] == 0) ||   // within bounds
              (mpRandom->getRandomOO() < mPf))      // random chance to compare values outside bounds
            {
              // compare obj fcn using mValue alternative code
              if (mValue[j] > mValue[j + 1])
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

// evaluate the distance ofparameters to boundaries
C_FLOAT64 COptMethodGASR::phi(C_INT32 indivNum)
{
  C_FLOAT64 phiVal = 0.0;
  C_FLOAT64 phiCalc;
  unsigned C_INT32 i;

  for (i = 0; i < mVariableSize; i++)
    {
      COptItem & OptItem = *(*mpOptItem)[i];

      // Go through parameter and constraints (all taken care of in single call)
      switch (OptItem.checkConstraint())
        {
        case - 1:  // to low
          phiCalc = *OptItem.getLowerBoundValue() - (*mIndividual[indivNum])[i];
          phiVal += phiCalc * phiCalc;
          break;

        case 1:    // to high
          phiCalc = (*mIndividual[indivNum])[i] - *OptItem.getUpperBoundValue();
          phiVal += phiCalc * phiCalc;
          break;
        }
    }

  return phiVal;
}

// check the best individual at this generation
unsigned C_INT32 COptMethodGASR::fittest()
{
  unsigned C_INT32 i, BestIndex = 0;
  C_FLOAT64 BestValue = mValue[0];

  for (i = 1; i < mPopulationSize; i++)
    if (mValue[i] < BestValue && !isnan(mValue[i]) && !(mPhi[i] != 0))
      {
        BestIndex = i;
        BestValue = mValue[i];
      }

  return BestIndex;
}

// initialise the population
bool COptMethodGASR::creation(unsigned C_INT32 first,
                              unsigned C_INT32 last)
{
  unsigned C_INT32 Last = std::min(last, mPopulationSize);

  unsigned C_INT32 i;
  unsigned C_INT32 j;

  C_FLOAT64 mn;
  C_FLOAT64 mx;
  C_FLOAT64 la;

  bool linear;
  bool Continue = true;

  for (i = first; i < Last && Continue; i++)
    {
      for (j = 0; j < mVariableSize; j++)
        {
          // calculate lower and upper bounds
          COptItem & OptItem = *(*mpOptItem)[j];
          mn = *OptItem.getLowerBoundValue();
          mx = *OptItem.getUpperBoundValue();

          C_FLOAT64 & mut = (*mIndividual[i])[j];

          try
            {
              // determine if linear or log scale
              linear = false; la = 1.0;

              if ((mn < 0.0) || (mx <= 0.0))
                linear = true;
              else
                {
                  la = log10(mx) - log10(std::max(mn, DBL_MIN));
                  if (la < 1.8)
                    linear = true;
                  else
                    mn = std::max(mn, DBL_MIN);
                }

              // set it to a random value within the interval
              if (linear)
                mut = mn + mpRandom->getRandomCC() * (mx - mn);
              else
                mut = mn * pow(10, la * mpRandom->getRandomCC());
            }

          catch (...)
            {
              mut = (mx + mn) * 0.5;
            }

          // We need to set the value here so that further checks take
          // account of the value.
          (*(*mpSetCalculateVariable)[j])(mut);
        }

      // calculate its fitness
      Continue = evaluate(*mIndividual[i]);
      mValue[i] = mEvaluationValue;

      /* Calculate the phi value of the individual for SR*/
      mPhi[i] = phi(i);
    }

  return Continue;
}

void COptMethodGASR::initObjects()
{
  addObjectReference("Current Generation", mGeneration, CCopasiObject::ValueInt);
  addObjectReference("Objective Value", mBestValue, CCopasiObject::ValueDbl);
}

bool COptMethodGASR::initialize()
{
  unsigned C_INT32 i;

  if (!COptMethod::initialize()) return false;

  mGenerations = * getValue("Number of Generations").pUINT;
  mPopulationSize = * getValue("Population Size").pUINT;
  C_FLOAT64 mPf = *(C_FLOAT64*) getValue("Pf").pDOUBLE;
  if (mPf <= 0.4 || 0.5 <= mPf) mPf = 0.475;
  mpRandom =
    CRandom::createGenerator(* (CRandom::Type *) getValue("Random Number Generator").pUINT,
                             * (unsigned C_INT32 *) getValue("Seed").pUINT);

  mVariableSize = mpOptItem->size();

  mIndividual.resize(2*mPopulationSize);
  mPhi.resize(2*mPopulationSize);
  for (i = 0; i < 2*mPopulationSize; i++)
    mIndividual[i] = new CVector< C_FLOAT64 >(mVariableSize);

  mCrossOverFalse.resize(mVariableSize);
  mCrossOverFalse = false;
  mCrossOver.resize(mVariableSize);

  mValue.resize(2*mPopulationSize);

  mShuffle.resize(mPopulationSize);
  for (i = 0; i < mPopulationSize; i++)
    mShuffle[i] = i;

  mWins.resize(2*mPopulationSize);

  // initialise the variance for mutations
  mMutationVarians = 0.1;

  return true;
}

bool COptMethodGASR::cleanup()
{
  unsigned C_INT32 i;

  pdelete(mpRandom);
  for (i = 0; i < 2*mPopulationSize; i++)
    pdelete(mIndividual[i]);

  return true;
}

bool COptMethodGASR::optimise()
{
  bool Continue = true;

  if (!initialize()) return false;

  // Counters to determine whether the optimization process has stalled
  // They count the number of generations without advances.
  unsigned C_INT32 Stalled, Stalled10, Stalled30, Stalled50;
  Stalled = Stalled10 = Stalled30 = Stalled50 = 0;

  unsigned C_INT32 i;

  // initialise the population
  // first individual is the initial guess
  for (i = 0; i < mVariableSize; i++)
    (*mIndividual[0])[i] = *(*mpOptItem)[i]->getObjectValue();

  // calculate the fitness
  unsigned C_INT32 j;
  std::vector< UpdateMethod *>::const_iterator itMethod = mpSetCalculateVariable->begin();

  // set the paramter values
  for (j = 0; j < mVariableSize; j++, ++itMethod)
    (**itMethod)((*mIndividual[0])[j]);

  Continue = evaluate(*mIndividual[0]);
  mValue[0] = mEvaluationValue;

  /* Calculate the phi value of the individual for SR*/
  mPhi[0] = phi(0);

  // the others are random
  Continue = creation(1, mPopulationSize);

  // get the index of the fittest
  mBestIndex = fittest();

  // and store that value
  mBestValue = mValue[mBestIndex];
  mpOptProblem->setSolutionVariables(*mIndividual[mBestIndex]);
  Continue = mpOptProblem->setSolutionValue(mBestValue);

  if (!Continue)
    {
      cleanup();
      return false;
    }

  // ITERATE FOR gener GENERATIONS
  for (mGeneration = 0;
       mGeneration < mGenerations && Continue;
       mGeneration++, Stalled++, Stalled10++, Stalled30++, Stalled50++)
    {
      // perturb the population if we have stalled for a while
      if (Stalled > 50 && Stalled50 > 50)
        {
          Continue = creation(mPopulationSize / 2, mPopulationSize);
          Stalled10 = Stalled30 = Stalled50 = 0;
        }
      else if (Stalled > 30 && Stalled30 > 30)
        {
          Continue = creation(mPopulationSize * 0.7, mPopulationSize);
          Stalled10 = Stalled30 = 0;
        }
      else if (Stalled > 10 && Stalled10 > 10)
        {
          Continue = creation(mPopulationSize * 0.9, mPopulationSize);
          Stalled10 = 0;
        }
      // replicate the individuals
      else
        Continue = replicate();

      // select the most fit
      Continue = select();

      // get the index of the fittest
      mBestIndex = fittest();
      if (mValue[mBestIndex] < mBestValue)
        {
          Stalled = Stalled10 = Stalled30 = Stalled50 = 0;
          mBestValue = mValue[mBestIndex];

          mpOptProblem->setSolutionVariables(*mIndividual[mBestIndex]);
          Continue = mpOptProblem->setSolutionValue(mBestValue);

          // We found a new best value lets report it.
          if (mpReport) mpReport->printBody();
        }

      if (mpCallBack)
        Continue = mpCallBack->progress(mhGenerations);
    }

  cleanup();

  return Continue;
}
