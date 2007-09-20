// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodSRES.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/09/20 14:06:35 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <float.h>

#include "copasi.h"
#include "mathematics.h"

#include "COptMethodSRES.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "randomGenerator/CRandom.h"
#include "utilities/CProcessReport.h"
#include "utilities/CSort.h"
#include "report/CCopasiObjectReference.h"

#ifdef RANDOMIZE
# undef RANDOMIZE
#endif

#define childrate 7

COptMethodSRES::COptMethodSRES(const CCopasiContainer * pParent):
    COptMethod(CCopasiTask::optimization, CCopasiMethod::SRES, pParent),
    mGenerations(0),
    mPopulationSize(0),
    mpRandom(NULL),
    mVariableSize(0),
    mIndividual(0),
    mEvaluationValue(DBL_MAX),
    mValue(0),
    mBestValue(DBL_MAX),
    mGeneration(0)

{
  addParameter("Number of Generations", CCopasiParameter::UINT, (unsigned C_INT32) 200);
  addParameter("Population Size", CCopasiParameter::UINT, (unsigned C_INT32) 20);
  addParameter("Random Number Generator", CCopasiParameter::UINT, (unsigned C_INT32) CRandom::mt19937);
  addParameter("Seed", CCopasiParameter::UINT, (unsigned C_INT32) 0);
  addParameter("Pf", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.475);  //*****ADDED for SR

  initObjects();
}

COptMethodSRES::COptMethodSRES(const COptMethodSRES & src,
                               const CCopasiContainer * pParent):
    COptMethod(src, pParent),
    mGenerations(0),
    mPopulationSize(0),
    mpRandom(NULL),
    mVariableSize(0),
    mIndividual(0),
    mEvaluationValue(DBL_MAX),
    mValue(0),
    mBestValue(DBL_MAX),
    mGeneration(0)
{initObjects();}

COptMethodSRES::~COptMethodSRES()
{cleanup();}

// evaluate the fitness of one individual
bool COptMethodSRES::evaluate(const CVector< C_FLOAT64 > & /* individual */)
{
  bool Continue = true;

  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  // evaluate the fitness
  Continue &= mpOptProblem->calculate();

  // check wheter the functional constraints are fulfilled
  if (!mpOptProblem->checkFunctionalConstraints())
    mEvaluationValue = DBL_MAX;
  else
    mEvaluationValue = mpOptProblem->getCalculateValue();

  return Continue;
}

bool COptMethodSRES::swap(unsigned C_INT32 from, unsigned C_INT32 to)
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

  dTmp = mPhi[to];
  mPhi[to] = mPhi[from];
  mPhi[from] = dTmp;

  return true;
}

bool COptMethodSRES::replicate()
{
  bool Continue = true;

  unsigned C_INT32 Parent;
  unsigned C_INT32 i, j;

  std::vector< CVector < C_FLOAT64 > * >::iterator itSrc = mIndividual.begin();
  std::vector< CVector < C_FLOAT64 > * >::iterator endSrc = itSrc + mPopulationSize;
  std::vector< CVector < C_FLOAT64 > * >::iterator itTarget = endSrc;

  std::vector< CVector < C_FLOAT64 > * >::iterator itSrcVariance = mVariance.begin();
  std::vector< CVector < C_FLOAT64 > * >::iterator itTargetVariance = itSrcVariance + mPopulationSize;

  C_FLOAT64 * pVariance, * pVarianceEnd, * pParentVariance;

  // iterate over parents
  for (i = 0; itSrc != endSrc && Continue; ++itSrc, ++itSrcVariance, ++i)
    {
      // iterate over the childrate - 1 since the first child is the
      // parent.
      for (j = 1; j < childrate; ++j, ++itTarget, ++itTargetVariance)
        {
          // first just copy the individuals
          **itTarget = **itSrc;
          **itTargetVariance = **itSrcVariance;

          // do recombination on the sigma
          // since sigmas already have one parent's component
          // need only average with the sigmas of the other parent
          Parent = (i + mpRandom->getRandomU(mPopulationSize - 1)) % mPopulationSize;

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
  std::vector< CVector < C_FLOAT64 > * >::iterator it = mIndividual.begin() + mPopulationSize;
  std::vector< CVector < C_FLOAT64 > * >::iterator end = mIndividual.end();
  std::vector< CVector < C_FLOAT64 > * >::iterator itVariance = mVariance.begin() + mPopulationSize;

  C_FLOAT64 * pVariable, * pVariableEnd, * pVariance, * pMaxVariance;
  C_FLOAT64 * pPhi = mPhi.array() + mPopulationSize;
  C_FLOAT64 * pValue = mValue.array() + mPopulationSize;

  bool Continue = true;
  unsigned C_INT32 i, j;
  C_FLOAT64 v1;

  // Mutate each new individual
  for (i = mPopulationSize; it != end && Continue; ++it, ++itVariance, ++i)
    {
      pVariable = (*it)->array();
      pVariableEnd = pVariable + mVariableSize;
      pVariance = (*itVariance)->array();
      pMaxVariance = mMaxVariance.array();

      v1 = mpRandom->getRandomNormal01();

      for (j = 0; pVariable != pVariableEnd; ++pVariable, ++pVariance, ++pMaxVariance, ++j)
        {
          C_FLOAT64 & mut = *pVariable;
          C_FLOAT64 Store = mut;

          COptItem & OptItem = *(*mpOptItem)[j];

          unsigned C_INT32 l;

          try
            {
              // update the parameter for the variances
              *pVariance =
                std::min(*pVariance * exp(tau1 * v1 + tau2 * mpRandom->getRandomNormal01()), *pMaxVariance);

              for (l = 0; l < 10; l++)
                {
                  // calculate the mutated parameter
                  mut = Store + *pVariance * mpRandom->getRandomNormal01();
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
          (*(*mpSetCalculateVariable)[j])(mut);
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
  unsigned C_INT32 i, j;
  unsigned C_INT32 TotalPopulation = mIndividual.size();
  bool wasSwapped;
  unsigned C_INT32 sweepNum = TotalPopulation;  // This is default based on paper

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
              (mpRandom->getRandomOO() < mPf))      // random chance to compare values outside bounds
            {
              // compare obj fcn using mValue alternative code
              if (mValue[j] > mValue[j + 1])
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
unsigned C_INT32 COptMethodSRES::fittest()
{
  unsigned C_INT32 i, BestIndex = C_INVALID_INDEX;
  C_FLOAT64 BestValue = DBL_MAX;

  for (i = 0; i < mPopulationSize; i++)
    if (mValue[i] < BestValue && mPhi[i] == 0)
      {
        BestIndex = i;
        BestValue = mValue[i];
      }

  return BestIndex;
}

// initialise the population
bool COptMethodSRES::creation(unsigned C_INT32 first)
{
  unsigned C_INT32 i;
  unsigned C_INT32 j;

  C_FLOAT64 mn;
  C_FLOAT64 mx;
  C_FLOAT64 la;

  bool Continue = true;

  std::vector< CVector < C_FLOAT64 > * >::iterator it =
    mIndividual.begin() + first;
  std::vector< CVector < C_FLOAT64 > * >::iterator end =
    mIndividual.begin() + mPopulationSize;
  std::vector< CVector < C_FLOAT64 > * >::iterator itVariance =
    mVariance.begin() + first;

  C_FLOAT64 * pVariable, * pVariableEnd, * pVariance, * pMaxVariance;
  C_FLOAT64 * pPhi = mPhi.array() + first;
  C_FLOAT64 * pValue = mValue.array() + first;

  // set the first individual to the initial guess
  if (it == mIndividual.begin())
    {
      pVariable = (*it)->array();
      pVariableEnd = pVariable + mVariableSize;
      pVariance = (*itVariance)->array();
      pMaxVariance = mMaxVariance.array();

      for (j = 0; pVariable != pVariableEnd; ++pVariable, ++pVariance, ++pMaxVariance, ++j)
        {
          C_FLOAT64 & mut = *pVariable;
          COptItem & OptItem = *(*mpOptItem)[j];

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
          (*(*mpSetCalculateVariable)[j])(mut);

          // Set the variance for this parameter.
          *pVariance = *pMaxVariance;
        }

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
                    mut = pow(10.0, log10(std::max(mn, DBL_MIN)) + la * mpRandom->getRandomCC());
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
                    mut = - pow(10.0, log10(std::max(mn, DBL_MIN)) + la * mpRandom->getRandomCC());
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
          *pVariance = *pMaxVariance;
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
  addObjectReference("Current Generation", mGeneration, CCopasiObject::ValueInt);
}

#ifdef WIN32
// warning C4056: overflow in floating-point constant arithmetic
// warning C4756: overflow in constant arithmetic
# pragma warning (disable: 4056 4756)
#endif

bool COptMethodSRES::initialize()
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

  mPf = *(C_FLOAT64*) getValue("Pf").pDOUBLE;
  if (mPf < 0.0 || 1.0 < mPf)
    {
      mPf = 0.475;
      setValue("Pf", mPf);
    }

  mpRandom =
    CRandom::createGenerator(* (CRandom::Type *) getValue("Random Number Generator").pUINT,
                             * getValue("Seed").pUINT);

  mVariableSize = mpOptItem->size();

  mIndividual.resize(childrate * mPopulationSize);
  for (i = 0; i < childrate * mPopulationSize; i++)
    mIndividual[i] = new CVector< C_FLOAT64 >(mVariableSize);

  mVariance.resize(childrate * mPopulationSize);
  for (i = 0; i < childrate * mPopulationSize; i++)
    mVariance[i] = new CVector< C_FLOAT64 >(mVariableSize);

  mMaxVariance.resize(mVariableSize);
  for (i = 0; i < mVariableSize; i++)
    {
      COptItem & OptItem = *(*mpOptItem)[i];

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

  mValue.resize(childrate * mPopulationSize);
  mValue = mpOptProblem->getSolutionValue();
  mBestValue = mpOptProblem->getSolutionValue();

  mPhi.resize(childrate * mPopulationSize);

  try
    {
      tau1 = 1 / sqrt(2 * sqrt(double(mVariableSize)));
      tau2 = 1 / sqrt(2 * double(mVariableSize));
    }
  catch (...)
    {
      tau1 = tau2 = 1;
    }

  return true;
}

#ifdef WIN32
# pragma warning (default: 4056 4756)
#endif

bool COptMethodSRES::cleanup()
{
  unsigned C_INT32 i;

  pdelete(mpRandom);

  for (i = 0; i < mIndividual.size(); i++)
    {
      pdelete(mIndividual[i]);
      pdelete(mVariance[i]);
    }

  return true;
}

// evaluate the distance of parameters and constraints to boundaries
C_FLOAT64 COptMethodSRES::phi(C_INT32 /* indivNum */)
{
  C_FLOAT64 phiVal = 0.0;
  C_FLOAT64 phiCalc;

  std::vector< COptItem * >::const_iterator it;
  std::vector< COptItem * >::const_iterator end;

#ifdef XXXX // We force the variables to be within the domain
  it = mpOptItem->begin();
  end = mpOptItem->end();
  C_FLOAT64 * pVariable = mIndividual[indivNum]->array();

  for (; it != end; ++it, pVariable++)
    {
      switch ((*it)->checkConstraint())
        {
        case - 1:
          phiCalc = *(*it)->getLowerBoundValue() - *pVariable;
          phiVal += phiCalc * phiCalc;
          break;

        case 1:
          phiCalc = *pVariable - *(*it)->getUpperBoundValue();
          phiVal += phiCalc * phiCalc;
          break;
        }
    }
#endif // XXXX

  it = mpOptContraints->begin();
  end = mpOptContraints->end();

  for (; it != end; ++it)
    {
      switch ((*it)->checkConstraint())
        {
        case - 1:
        case 1:
          phiCalc = (*it)->getConstraintViolation();
          phiVal += phiCalc * phiCalc;
          break;

        default:
          break;
        }
    }

  return phiVal;
}

bool COptMethodSRES::optimise()
{
  bool Continue = true;
  unsigned BestIndex = C_INVALID_INDEX;

#ifdef RANDOMIZE
  // Counters to determine whether the optimization process has stalled
  // They count the number of generations without advances.
  unsigned C_INT32 Stalled10, Stalled20, Stalled40, Stalled80;
  Stalled10 = Stalled20 = Stalled40 = Stalled80 = 0;
#endif // RANDOMIZE

  if (!initialize()) return false;

  // initialise the population
  Continue = creation(0);

  // get the index of the fittest
  BestIndex = fittest();

  if (BestIndex != C_INVALID_INDEX)
    {
      // and store that value
      mBestValue = mValue[BestIndex];
      Continue = mpOptProblem->setSolution(mBestValue, *mIndividual[BestIndex]);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  if (!Continue)
    {
      cleanup();
      return false;
    }

  // ITERATE FOR gener GENERATIONS
#ifdef RANDOMIZE
  for (mGeneration = 2;
       mGeneration <= mGenerations && Continue;
       mGeneration++, Stalled10++, Stalled20++, Stalled40++, Stalled80++)
    {
      // perturb the population if we have stalled for a while
      if (Stalled80 > 80)
        {
          Continue = creation((unsigned C_INT32) (mPopulationSize * 0.2));
          Stalled10 = Stalled20 = Stalled40 = Stalled80 = 0;
        }
      else if (Stalled40 > 40)
        {
          Continue = creation((unsigned C_INT32) (mPopulationSize * 0.6));
          Stalled10 = Stalled20 = Stalled40 = 0;
        }
      else if (Stalled20 > 20)
        {
          Continue = creation((unsigned C_INT32) (mPopulationSize * 0.8));
          Stalled10 = Stalled20 = 0;
        }
      else if (Stalled10 > 10)
        {
          Continue = creation((unsigned C_INT32) (mPopulationSize * 0.9));
          Stalled10 = 0;
        }
#else
  for (mGeneration = 2;
       mGeneration <= mGenerations && Continue;
       mGeneration++)
    {
#endif // RANDOMIZE
      Continue = replicate();

      // select the most fit
      select();

      // get the index of the fittest
      BestIndex = fittest();

      if (BestIndex != C_INVALID_INDEX &&
          mValue[BestIndex] < mBestValue)
        {
#ifdef RANDOMIZE
          Stalled10 = Stalled20 = Stalled40 = Stalled80 = 0;
#endif // RANDOMIZE
          mBestValue = mValue[BestIndex];

          Continue = mpOptProblem->setSolution(mBestValue, *mIndividual[BestIndex]);

          // We found a new best value lets report it.
          mpParentTask->output(COutputInterface::DURING);
        }

      if (mpCallBack)
        Continue = mpCallBack->progress(mhGenerations);
    }
  return 0;
}
