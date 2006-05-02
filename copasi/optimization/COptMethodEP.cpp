/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodEP.cpp,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/05/02 19:30:19 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "COptMethodEP.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "randomGenerator/CRandom.h"
#include "report/CCopasiObjectReference.h"
#include "utilities/CSort.h"

COptMethodEP::COptMethodEP(const CCopasiContainer * pParent):
    COptMethod(CCopasiTask::optimization, CCopasiMethod::EvolutionaryProgram, pParent),
    mGenerations(0),
    mGeneration(0),
    mPopulationSize(0),
    mpRandom(NULL),
    mBestIndex(C_INVALID_INDEX),
    mLosses(0),
    mBestValue(DBL_MAX),
    mEvaluationValue(DBL_MAX),
    mValue(0),
    mVariableSize(0),
    mIndividual(0),
    mVariance(0)
{
  addParameter("Number of Generations", CCopasiParameter::UINT, (unsigned C_INT32) 200);
  addParameter("Population Size", CCopasiParameter::UINT, (unsigned C_INT32) 20);
  addParameter("Random Number Generator", CCopasiParameter::UINT, (unsigned C_INT32) CRandom::mt19937);
  addParameter("Seed", CCopasiParameter::UINT, (unsigned C_INT32) 0);

  initObjects();
}

COptMethodEP::COptMethodEP(const COptMethodEP & src,
                           const CCopasiContainer * pParent): COptMethod(src, pParent),
    mGenerations(0),
    mGeneration(0),
    mPopulationSize(0),
    mpRandom(NULL),
    mBestIndex(C_INVALID_INDEX),
    mLosses(0),
    mBestValue(DBL_MAX),
    mEvaluationValue(DBL_MAX),
    mValue(0),
    mVariableSize(0),
    mIndividual(0),
    mVariance(0)
{initObjects();}

COptMethodEP::~COptMethodEP()
{
  cleanup();
}

bool COptMethodEP::optimise()
{
  if (!initialize()) return false;
  bool Continue = true;

  // initialise the population
  Continue = creation();

  // get the index of the fittest
  mBestIndex = fittest();

  if (mBestIndex != C_INVALID_INDEX)
    {
      // and store that value
      mBestValue = mValue[mBestIndex];
      mpOptProblem->setSolutionVariables(*mIndividual[mBestIndex]);
      Continue = mpOptProblem->setSolutionValue(mBestValue);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  if (!Continue)
    {
      cleanup();
      return false;
    }

  // iterate over Generations
  for (mGeneration = 2; mGeneration <= mGenerations && Continue; mGeneration++)
    {
      // replicate the individuals
      Continue = replicate();

      // select the most fit
      Continue = select();

      // get the index of the fittest
      mBestIndex = fittest();

      if (mBestIndex != C_INVALID_INDEX &&
          mValue[mBestIndex] < mBestValue)
        {
          mBestValue = mValue[mBestIndex];

          mpOptProblem->setSolutionVariables(*mIndividual[mBestIndex]);
          Continue = mpOptProblem->setSolutionValue(mBestValue);

          // We found a new best value lets report it.
          //if (mpReport) mpReport->printBody();
          mpParentTask->output(COutputInterface::DURING);
        }

      if (mpCallBack)
        Continue = mpCallBack->progress(mhGenerations);
    }

  cleanup();

  return Continue;
}

bool COptMethodEP::cleanup()
{
  unsigned C_INT32 i;
  // pdelete all used variables
  pdelete(mpRandom);
  for (i = 0; i < mIndividual.size(); i++)
    {
      pdelete(mIndividual[i]);
      pdelete(mVariance[i]);
    }
  return true;
}

bool COptMethodEP::initialize()
{
  cleanup();

  unsigned C_INT32 i;
  if (!COptMethod::initialize()) return false;

  mGenerations = * getValue("Number of Generations").pUINT;
  mGeneration = 0;

  if (mpCallBack)
    mhGenerations =
      mpCallBack->addItem("Current Generation",
                          CCopasiParameter::UINT,
                          & mGeneration,
                          & mGenerations);
  mGeneration++;

  mPopulationSize = * getValue("Population Size").pUINT;
  mpRandom =
    CRandom::createGenerator(* (CRandom::Type *) getValue("Random Number Generator").pUINT,
                             * (unsigned C_INT32 *) getValue("Seed").pUINT);

  mVariableSize = mpOptItem->size();

  mIndividual.resize(2*mPopulationSize);
  mVariance.resize(2*mPopulationSize);
  for (i = 0; i < 2*mPopulationSize; i++)
    {
      mIndividual[i] = new CVector< C_FLOAT64 >(mVariableSize);
      mVariance[i] = new CVector< C_FLOAT64 >(mVariableSize);
    }

  mValue.resize(2*mPopulationSize);
  mLosses.resize(2*mPopulationSize);

  // initialise the parameters to update the variances
  tau1 = 1.0 / sqrt(2 * mVariableSize);
  tau2 = 1.0 / sqrt(2 * sqrt(mVariableSize));

  return true;
}

// evaluate the fitness of one individual
bool COptMethodEP::evaluate(const CVector< C_FLOAT64 > & /* individual */)
{
  bool Continue = true;

  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  // evaluate the fitness
  Continue = mpOptProblem->calculate();

  // check wheter the functional constraints are fulfilled
  if (!mpOptProblem->checkFunctionalConstraints())
    mEvaluationValue = DBL_MAX;
  else
    mEvaluationValue = mpOptProblem->getCalculateValue();

  return Continue;
}

void COptMethodEP::initObjects()
{
  addObjectReference("Current Generation", mGeneration, CCopasiObject::ValueInt);
}

bool COptMethodEP::creation()
{
  unsigned C_INT32 i;
  unsigned C_INT32 j;

  C_FLOAT64 mn;
  C_FLOAT64 mx;
  C_FLOAT64 la;

  bool Continue = true;

  // set the first individual to the initial guess

  for (i = 0; i < mVariableSize; i++)
    {
      C_FLOAT64 & mut = (*mIndividual[0])[i];
      COptItem & OptItem = *(*mpOptItem)[i];

      mut = *OptItem.getObjectValue();

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

      // We need to set the value here so that further checks take
      // account of the value.
      (*(*mpSetCalculateVariable)[i])(mut);

      // Set the variance for this parameter.
      (*mVariance[0])[i] = fabs(mut) * 0.5;
    }

  Continue = evaluate(*mIndividual[0]);
  mValue[0] = mEvaluationValue;
  //candx[0] = evaluate(0);

  // and copy it to the rest
  // for(i=1; i<half; i++)
  //  candx[i] = candx[0];
  // set the other half to random values within the boundaries
  // for(i=half; i<mVariableSizeze; i++)

  for (i = 1; i < mPopulationSize; i++)
    {
      for (j = 0; j < mVariableSize; j++)
        {
          C_FLOAT64 & mut = (*mIndividual[i])[j];
          COptItem & OptItem = *(*mpOptItem)[j];

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
                  la = log10(mx) - log10(std::max(mn, DBL_MIN));

                  if (la < 1.8 || !(mn > 0.0)) // linear
                    mut = mn + mpRandom->getRandomCC() * (mx - mn);
                  else
                    mut = pow(10, log10(std::max(mn, DBL_MIN)) + la * mpRandom->getRandomCC());
                }
              else if (mx > 0) // 0 is in the interval (mn, mx)
                {
                  la = log10(mx) + log10(-mn);

                  if (la < 3.6) // linear
                    mut = mn + mpRandom->getRandomCC() * (mx - mn);
                  else
                    {
                      C_FLOAT64 mean = (mx + mn) * 0.5;
                      C_FLOAT64 sigma = mean * 0.01;
                      do
                        {
                          mut = mpRandom->getRandomNormal(mean, sigma);
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

                  la = log10(mx) - log10(std::max(mn, DBL_MIN));

                  if (la < 1.8 || !(mn > 0.0)) // linear
                    mut = - (mn + mpRandom->getRandomCC() * (mx - mn));
                  else
                    mut = - pow(10, log10(std::max(mn, DBL_MIN)) + la * mpRandom->getRandomCC());
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
          // We need to set the value here so that further checks take
          // account of the value.
          (*(*mpSetCalculateVariable)[j])(mut);

          // Set the variance for this parameter.
          (*mVariance[i])[j] = fabs(mut) * 0.5;
        }

      // calculate its fitness
      Continue = evaluate(*mIndividual[i]);
      mValue[i] = mEvaluationValue;
    }

  return Continue;
}

bool COptMethodEP::select()
{
  unsigned C_INT32 i, j, nopp, opp;
  unsigned C_INT32 TotalPopulation = 2 * mPopulationSize;

  // tournament competition
  mLosses = 0; // Set all losses to 0.

  // compete with ~ 20% of the TotalPopulation
  nopp = std::max<unsigned C_INT32>(1, mPopulationSize / 5);

  // parents and offspring are all in competition
  for (i = 0; i < TotalPopulation; i++)
    for (j = 0; j < nopp; j++)
      {
        // get random opponent
        opp = mpRandom->getRandomU(TotalPopulation - 1);

        if (mValue[i] < mValue[opp])
          mLosses[opp]++;
        else
          mLosses[i]++;
      }

  partialSortWithPivot(mLosses.array(),
                       mLosses.array() + mPopulationSize,
                       mLosses.array() + TotalPopulation,
                       mPivot);

  FSwapClass<COptMethodEP, unsigned C_INT32, bool> Swap(this, &COptMethodEP::swap);
  applyPartialPivot(mPivot, mPopulationSize, Swap);

  return true;
}

bool COptMethodEP::swap(unsigned C_INT32 from, unsigned C_INT32 to)
{
  CVector< C_FLOAT64 > * pTmp = mIndividual[to];
  mIndividual[to] = mIndividual[from];
  mIndividual[from] = pTmp;

  pTmp = mVariance[to];
  mVariance[to] = mVariance[from];
  mVariance[from] = pTmp;

  C_FLOAT64 dTmp = mValue[to];
  mValue[to] = mValue[from];
  mValue[from] = dTmp;

  C_INT32 iTmp = mLosses[to];
  mLosses[to] = mLosses[from];
  mLosses[from] = iTmp;

  return true;
}

unsigned C_INT32 COptMethodEP::fittest()
{
  unsigned C_INT32 i, BestIndex = 0;
  C_FLOAT64 BestValue = mValue[0];

  for (i = 1; i < mPopulationSize && !mLosses[i]; i++)
    if (mValue[i] < BestValue)
      {
        BestIndex = i;
        BestValue = mValue[i];
      }

  return BestIndex;
}

bool COptMethodEP::replicate()
{
  unsigned C_INT32 i;
  unsigned C_INT32 j;
  bool Continue = true;

  // iterate over parents
  for (i = 0; i < mPopulationSize && Continue; i++)
    {
      // replicate them
      for (j = 0; j < mVariableSize; j++)
        {
          (*mIndividual[mPopulationSize + i])[j] = (*mIndividual[i])[j];
          (*mVariance[mPopulationSize + i])[j] = (*mVariance[i])[j];
        }

      mValue[mPopulationSize + i] = mValue[i];

      // possibly mutate the offspring
      Continue = mutate(mPopulationSize + i);
    }

  return Continue;
}

bool COptMethodEP::mutate(unsigned C_INT32 i)
{
  unsigned C_INT32 j;
  C_FLOAT64 v1;

  CVector<C_FLOAT64> & Individual = *mIndividual[i];
  CVector<C_FLOAT64> & Variance = *mVariance[i];

  v1 = mpRandom->getRandomNormal01();

  // update the variances
  for (j = 0; j < mVariableSize; j++)
    {
      C_FLOAT64 & mut = Individual[j];
      COptItem & OptItem = *(*mpOptItem)[j];

      try
        {
          // update the parameter for the variances
          Variance[j] =
            std::max(Variance[j] * exp(tau1 * v1 + tau2 * mpRandom->getRandomNormal01()), 1e-8);

          // calculate the mutatated parameter
          mut += sqrt(Variance[j]) * mpRandom->getRandomNormal01();
        }

      catch (...)
        {
          mut = (*OptItem.getUpperBoundValue() + *OptItem.getLowerBoundValue()) * 0.5;
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

      // We need to set the value here so that further checks take
      // account of the value.
      (*(*mpSetCalculateVariable)[j])(mut);
    }

  // calculate its fitness
  bool Continue = evaluate(Individual);
  mValue[i] = mEvaluationValue;

  return Continue;
}
