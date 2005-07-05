/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodGA.cpp,v $
   $Revision: 1.17 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/07/05 20:16:36 $
   End CVS Header */

// ga.cpp : Genetic algorithm optimisation.
//
#include <float.h>

#include "copasi.h"
#include "mathematics.h"
#include "COptMethod.h"
#include "COptProblem.h"
#include "COptItem.h"

#include "randomGenerator/CRandom.h"
#include "utilities/CProcessReport.h"
#include "report/CCopasiObjectReference.h"

COptMethodGA::COptMethodGA(const CCopasiContainer * pParent):
    COptMethod(CCopasiMethod::GeneticAlgorithm, pParent),
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
}

COptMethodGA::COptMethodGA(const COptMethodGA & src,
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

COptMethodGA::~COptMethodGA()
{cleanup();}

bool COptMethodGA::setCallBack(CProcessReport * pCallBack)
{
  CCopasiMethod::setCallBack(pCallBack);

  mhGenerations =
    pCallBack->addItem("Current Generation",
                       CCopasiParameter::UINT,
                       & mGeneration,
                       & mGenerations);

  return true;
}

// evaluate the fitness of one individual
bool COptMethodGA::evaluate(const CVector< C_FLOAT64 > & individual)
{
  unsigned C_INT32 j;
  bool Continue = true;

  std::vector< UpdateMethod *>::const_iterator itMethod = mpSetCalculateVariable->begin();

  // set the paramter values
  for (j = 0; j < mVariableSize; j++, ++itMethod)
    (**itMethod)(individual[j]);

  // check whether the parametric constraints are fulfilled
  if (!mpOptProblem->checkParametricConstraints())
    {
      mEvaluationValue = DBL_MAX;
      return Continue;
    }

  // evaluate the fitness
  try
  {Continue = mpOptProblem->calculate();}

  catch (...)
    {
      mEvaluationValue = DBL_MAX;
      return Continue;
    }

  // check wheter the functional constraints are fulfilled
  if (!mpOptProblem->checkFunctionalConstraints())
    mEvaluationValue = DBL_MAX;
  else
    mEvaluationValue = mpOptProblem->getCalculateValue();

  return Continue;
}

bool COptMethodGA::swap(unsigned C_INT32 from, unsigned C_INT32 to)
{
  CVector< C_FLOAT64 > * pTmp = mIndividual[to];
  mIndividual[to] = mIndividual[from];
  mIndividual[from] = pTmp;

  C_FLOAT64 dTmp = mValue[to];
  mValue[to] = mValue[from];
  mValue[from] = dTmp;

  C_INT32 iTmp = mWins[to];
  mWins[to] = mWins[from];
  mWins[from] = iTmp;

  return true;
}

//mutate one individual
bool COptMethodGA::mutate(CVector< C_FLOAT64 > & individual)
{
  unsigned C_INT32 j;

  // mutate the parameters
  for (j = 0; j < mVariableSize; j++)
    {
      COptItem & OptItem = *(*mpOptItem)[j];
      C_FLOAT64 & mut = individual[j];

      // calculate the mutatated parameter
      mut *= mpRandom->getRandomNormal(1, mMutationVarians);

      // force it to be within the bounds
      switch (OptItem.checkConstraint(mut))
        {
        case - 1:
          mut = *OptItem.getLowerBoundValue();
          if (!OptItem.checkLowerBound(mut)) // Inequality
            {
              if (mut == 0.0)
                mut = DBL_MIN;
              else
                mut += mut * DBL_EPSILON;
            }
          break;

        case 1:
          mut = *OptItem.getUpperBoundValue();
          if (!OptItem.checkUpperBound(mut)) // Inequality
            {
              if (mut == 0.0)
                mut = -DBL_MIN;
              else
                mut -= mut * DBL_EPSILON;
            }
          break;
        }
    }

  return true;
}

bool COptMethodGA::crossover(const CVector< C_FLOAT64 > & parent1,
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

bool COptMethodGA::shuffle()
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

bool COptMethodGA::replicate()
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
    }

  return Continue;
}

// select mPopulationSize individuals
bool COptMethodGA::select()
{
  unsigned C_INT32 i, j, nopp, opp, MaxIndex;
  unsigned C_INT32 TotalPopulation = 2 * mPopulationSize;
  C_FLOAT64 MaxValue;

  // tournament competition
  mWins = 0; // Set all wins to 0.

  // compete with ~ 20% of the TotalPopulation
  nopp = std::min<unsigned C_INT32>(1, mPopulationSize / 5);

  // parents and offspring are all in competition
  for (i = 0; i < TotalPopulation; i++)
    for (j = 0; j < nopp; j++)
      {
        // get random opponent
        opp = mpRandom->getRandomU(TotalPopulation - 1);

        if (mValue[i] < mValue[opp])
          mWins[i]++;
        else
          mWins[opp]++;
      }

  // selection of top mPopulationSize winners
  for (i = 0; i < mPopulationSize; i++)
    {
      MaxIndex = i;
      MaxValue = mWins[i];

      for (j = i + 1; j < TotalPopulation; j++)
        if (MaxValue < mWins[j])
          {
            MaxIndex = j;
            MaxValue = mWins[j];
          }

      swap(i, MaxIndex); // The best individual in [i, TotalPopulation] is swapped to the top (i) position.
    }

  return true;
}

// check the best individual at this generation
unsigned C_INT32 COptMethodGA::fittest()
{
  unsigned C_INT32 i, BestIndex = 0;
  C_FLOAT64 BestValue = mValue[0];

  for (i = 1; i < mPopulationSize; i++)
    if (mValue[i] < BestValue)
      {
        BestIndex = i;
        BestValue = mValue[i];
      }

  return BestIndex;
}

// initialise the population
bool COptMethodGA::creation(unsigned C_INT32 first,
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

              if (mn == 0.0) mn = DBL_EPSILON;

              if ((mn < 0.0) || (mx <= 0.0))
                linear = true;
              else
                {
                  la = log10(mx) - log10(mn);
                  if (la < 1.8) linear = true;
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

          // force it to be within the bounds
          switch (OptItem.checkConstraint(mut))
            {
            case - 1:
              mut = *OptItem.getLowerBoundValue();
              if (!OptItem.checkLowerBound(mut)) // Inequality
                {
                  if (mut == 0.0)
                    mut = DBL_MIN;
                  else
                    mut += mut * DBL_EPSILON;
                }
              break;

            case 1:
              mut = *OptItem.getUpperBoundValue();
              if (!OptItem.checkUpperBound(mut)) // Inequality
                {
                  if (mut == 0.0)
                    mut = - DBL_MIN;
                  else
                    mut -= mut * DBL_EPSILON;
                }
              break;
            }
        }
      try
        {
          // calculate its fitness
          Continue = evaluate(*mIndividual[i]);
          mValue[i] = mEvaluationValue;
        }
      catch (...)
        {
          mValue[i] = DBL_MAX;
        }
    }

  return Continue;
}

void COptMethodGA::initObjects()
{
  addObjectReference("Current Generation", mGeneration, CCopasiObject::ValueInt);
  addObjectReference("Objective Value", mBestValue, CCopasiObject::ValueDbl);
}

bool COptMethodGA::initialize()
{
  unsigned C_INT32 i;

  if (!COptMethod::initialize()) return false;

  mGenerations = * getValue("Number of Generations").pUINT;
  mPopulationSize = * getValue("Population Size").pUINT;
  mpRandom =
    CRandom::createGenerator(* (CRandom::Type *) getValue("Random Number Generator").pUINT,
                             * (unsigned C_INT32 *) getValue("Seed").pUINT);

  mVariableSize = mpOptItem->size();

  mIndividual.resize(2*mPopulationSize);
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

bool COptMethodGA::cleanup()
{
  unsigned C_INT32 i;

  pdelete(mpRandom);
  for (i = 0; i < 2*mPopulationSize; i++)
    pdelete(mIndividual[i]);

  return true;
}

bool COptMethodGA::optimise()
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

  try
    {
      // calculate the fitness
      Continue = evaluate(*mIndividual[0]);
      mValue[0] = mEvaluationValue;
    }

  catch (...)
    {
      mValue[0] = DBL_MAX;
    }

  if (!Continue)
    {
      cleanup();
      return false;
    }

  // the others are random
  if (!(Continue = creation(1, mPopulationSize)))
    {
      cleanup();
      return false;
    }

  // get the index of the fittest
  mBestIndex = fittest();
  // and store that value
  mBestValue = mValue[mBestIndex];

  mpOptProblem->setSolutionVariables(*mIndividual[mBestIndex]);

  if (!(Continue = mpOptProblem->setSolutionValue(mBestValue)))
    {
      cleanup();
      return false;
    }

  // ITERATE FOR gener GENERATIONS
  for (mGeneration = 0; mGeneration < mGenerations; mGeneration++, Stalled++, Stalled10++, Stalled30++, Stalled50++)
    {
      // perturb the population if we have stalled for a while
      if (Stalled > 50 && Stalled50 > 50)
        {
          if (!(Continue = creation(mPopulationSize / 2, mPopulationSize)))
            break;
          Stalled10 = Stalled30 = Stalled50 = 0;
        }
      else if (Stalled > 30 && Stalled30 > 30)
        {
          if (!(Continue = creation(mPopulationSize * 0.7, mPopulationSize)))
            break;
          Stalled10 = Stalled30 = 0;
        }
      else if (Stalled > 10 && Stalled10 > 10)
        {
          if (!(Continue = creation(mPopulationSize * 0.9, mPopulationSize)))
            break;
          Stalled10 = 0;
        }
      // replicate the individuals
      else if (!(Continue = replicate()))
        break;

      // select the most fit
      if (!(Continue = select()))
        break;

      // get the index of the fittest
      mBestIndex = fittest();
      if (mValue[mBestIndex] < mBestValue)
        {
          Stalled = Stalled10 = Stalled30 = Stalled50 = 0;
          mBestValue = mValue[mBestIndex];

          mpOptProblem->setSolutionVariables(*mIndividual[mBestIndex]);
          if (!(Continue = mpOptProblem->setSolutionValue(mBestValue)))
            break;
        }

      if (mpCallBack && !(Continue = mpCallBack->progress(mhGenerations)))
        break;
    }

  cleanup();

  return Continue;
}
