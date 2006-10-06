/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodPS.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/10/06 15:56:08 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <float.h>

#include "copasi.h"
#include "mathematics.h"
#include "COptMethodPS.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "randomGenerator/CRandom.h"
#include "utilities/CProcessReport.h"
#include "utilities/CSort.h"
#include "report/CCopasiObjectReference.h"

COptMethodPS::COptMethodPS(const CCopasiContainer * pParent):
    COptMethod(CCopasiTask::optimization, CCopasiMethod::ParticleSwarm, pParent),
    mIterationLimit(0),
    mSwarmSize(0),
    mTolerance(0.0),
    mpRandom(NULL),
    mIteration(0),
    mhIteration(C_INVALID_INDEX),
    mVariableSize(0),
    mIndividuals(),
    mValues(),
    mVelocities(),
    mBestValues(),
    mBestPositions(),
    mInformants(),
    mBestIndex(0),
    mEvaluationValue(0),
    mContinue(true)
{
  addParameter("Iteration Limit", CCopasiParameter::UINT, (unsigned C_INT32) 2000);
  addParameter("Swarm Size", CCopasiParameter::UINT, (unsigned C_INT32) 50);
  addParameter("Tolerance", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-9);
  addParameter("Random Number Generator", CCopasiParameter::UINT, (unsigned C_INT32) CRandom::mt19937);
  addParameter("Seed", CCopasiParameter::UINT, (unsigned C_INT32) 0);

  initObjects();
}

COptMethodPS::COptMethodPS(const COptMethodPS & src,
                           const CCopasiContainer * pParent):
    COptMethod(src, pParent),
    mIterationLimit(0),
    mSwarmSize(0),
    mTolerance(0.0),
    mpRandom(NULL),
    mIteration(0),
    mhIteration(C_INVALID_INDEX),
    mVariableSize(0),
    mIndividuals(),
    mValues(),
    mVelocities(),
    mBestValues(),
    mBestPositions(),
    mInformants(),
    mBestIndex(0),
    mEvaluationValue(0),
    mContinue(true)
{initObjects();}

COptMethodPS::~COptMethodPS()
{cleanup();}

// evaluate the fitness of one individual
const C_FLOAT64 & COptMethodPS::evaluate()
{
  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  // evaluate the fitness
  mContinue &= mpOptProblem->calculate();

  // check wheter the functional constraints are fulfilled
  if (!mpOptProblem->checkFunctionalConstraints())
    mEvaluationValue = DBL_MAX;
  else
    mEvaluationValue = mpOptProblem->getCalculateValue();

  return mEvaluationValue;
}

// move an individual
bool COptMethodPS::move(const unsigned C_INT32 & index)
{
  const C_FLOAT64 w = 1 / (2 * log(2));
  const C_FLOAT64 c = 0.5 + log(2);

  bool Improved = false;

  C_FLOAT64 * pIndividual = mIndividuals[index].array();
  C_FLOAT64 * pEnd = pIndividual + mVariableSize;
  C_FLOAT64 * pVelocity = mVelocities[index];
  C_FLOAT64 * pBestPosition = mBestPositions[index];
  std::vector< COptItem * >::const_iterator itOptItem = mpOptItem->begin();
  std::vector< UpdateMethod * >::const_iterator itSetCalculateVariable = mpSetCalculateVariable->begin();

  C_FLOAT64 * pBestInformantPosition = mBestPositions[index];
  C_FLOAT64 BestInformantValue = mBestValues[index];

  std::set< unsigned C_INT32 >::const_iterator itInformant = mInformants[index].begin();
  std::set< unsigned C_INT32 >::const_iterator endInformant = mInformants[index].end();

  for (; itInformant != endInformant; ++itInformant)
    if (mBestValues[*itInformant] < BestInformantValue)
      {
        BestInformantValue = mBestValues[*itInformant];
        pBestInformantPosition = mBestPositions[*itInformant];
      }

  for (; pIndividual != pEnd;
       ++pIndividual, ++pVelocity, ++pBestPosition, ++itOptItem, ++itSetCalculateVariable, ++pBestInformantPosition)
    {
      *pVelocity *= w;
      *pVelocity += c * mpRandom->getRandomCC() * (*pBestPosition - *pIndividual);
      *pVelocity += c * mpRandom->getRandomCC() * (*pBestInformantPosition - *pIndividual);

      *pIndividual += *pVelocity;

      COptItem & OptItem = **itOptItem;

      // force it to be within the bounds
      switch (OptItem.checkConstraint(*pIndividual))
        {
        case - 1:
          *pIndividual = *OptItem.getLowerBoundValue();
          *pVelocity = 0.0;
          break;

        case 1:
          *pIndividual = *OptItem.getUpperBoundValue();
          *pVelocity = 0.0;
          break;
        }

      // We need to set the value here so that further checks take
      // account of the value.
      (**itSetCalculateVariable)(*pIndividual);
    }

  // calculate its fitness
  mValues[index] = evaluate();

  // Check if we improved individually
  if (mEvaluationValue < mBestValues[index])
    {
      Improved = true;

      // Save the individually best value;
      mBestValues[index] = mEvaluationValue;
      memcpy(mBestPositions[index], mIndividuals[index].array(), sizeof(C_FLOAT64) * mVariableSize);

      // Check if we improved globally
      if (mEvaluationValue < mBestValues[mBestIndex])
        {
          // and store that value
          mBestIndex = index;
          mpOptProblem->setSolutionVariables(mIndividuals[index]);
          mContinue &= mpOptProblem->setSolutionValue(mBestValues[index]);

          // We found a new best value lets report it.
          mpParentTask->output(COutputInterface::DURING);
        }
    }

  return Improved;
}

// initialise an individual
bool COptMethodPS::create(const unsigned C_INT32 & index)
{
  C_FLOAT64 * pIndividual = mIndividuals[index].array();
  C_FLOAT64 * pEnd = pIndividual + mVariableSize;
  C_FLOAT64 * pVelocity = mVelocities[index];
  C_FLOAT64 * pBestPosition = mBestPositions[index];
  std::vector< COptItem * >::const_iterator itOptItem = mpOptItem->begin();
  std::vector< UpdateMethod * >::const_iterator itSetCalculateVariable = mpSetCalculateVariable->begin();

  C_FLOAT64 mn, mx, la;

  for (; pIndividual != pEnd;
       ++pIndividual, ++pVelocity, ++pBestPosition, ++itOptItem, ++itSetCalculateVariable)
    {
      COptItem & OptItem = **itOptItem;

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
                {
                  *pIndividual = mn + mpRandom->getRandomCC() * (mx - mn);
                  *pVelocity = mn + mpRandom->getRandomCC() * (mx - mn) - *pIndividual;
                }
              else
                {
                  *pIndividual = pow(10, log10(std::max(mn, DBL_MIN)) + la * mpRandom->getRandomCC());
                  *pVelocity =
                    pow(10, log10(std::max(mn, DBL_MIN)) + la * mpRandom->getRandomCC()) - *pIndividual;
                }
            }
          else if (mx > 0) // 0 is in the interval (mn, mx)
            {
              la = log10(mx) + log10(-mn);

              if (la < 3.6) // linear
                {
                  *pIndividual = mn + mpRandom->getRandomCC() * (mx - mn);
                  *pVelocity = mn + mpRandom->getRandomCC() * (mx - mn) - *pIndividual;
                }
              else
                {
                  C_FLOAT64 mean = (mx + mn) * 0.5;
                  C_FLOAT64 sigma = mean * 0.01;
                  do
                    {
                      *pIndividual = mpRandom->getRandomNormal(mean, sigma);
                    }
                  while ((*pIndividual < mn) || (*pIndividual > mx));

                  *pVelocity = mpRandom->getRandomNormal(mean, sigma) - *pIndividual;
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
                {
                  *pIndividual = - (mn + mpRandom->getRandomCC() * (mx - mn));
                  *pVelocity = - (mn + mpRandom->getRandomCC() * (mx - mn)) - *pIndividual;
                }
              else
                {
                  *pIndividual = - pow(10, log10(std::max(mn, DBL_MIN)) + la * mpRandom->getRandomCC());
                  *pVelocity =
                    - pow(10, log10(std::max(mn, DBL_MIN)) + la * mpRandom->getRandomCC()) - *pIndividual;
                }
            }
        }

      catch (...)
        {
          *pIndividual = (mx + mn) * 0.5;
          *pVelocity = 0.0;
        }

      // force it to be within the bounds
      switch (OptItem.checkConstraint(*pIndividual))
        {
        case - 1:
          *pIndividual = *OptItem.getLowerBoundValue();
          break;

        case 1:
          *pIndividual = *OptItem.getUpperBoundValue();
          break;
        }

      *pBestPosition = *pIndividual;

      // We need to set the value here so that further checks take
      // account of the value.
      (**itSetCalculateVariable)(*pIndividual);
    }

  // calculate its fitness
  mBestValues[index] = mValues[index] = evaluate();

  if (mBestValues[index] < mBestValues[mBestIndex])
    {
      // and store that value
      mBestIndex = index;
      mpOptProblem->setSolutionVariables(mIndividuals[index]);
      mContinue &= mpOptProblem->setSolutionValue(mBestValues[index]);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  return mContinue;
}

void COptMethodPS::initObjects()
{
  addObjectReference("Current Iteration", mIteration, CCopasiObject::ValueInt);
}

#ifdef WIN32
// warning C4056: overflow in floating-point constant arithmetic
// warning C4756: overflow in constant arithmetic
# pragma warning (disable: 4056 4756)
#endif

bool COptMethodPS::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mIterationLimit = * getValue("Iteration Limit").pUINT;
  mIteration = 0;

  if (mpCallBack)
    mhIteration =
      mpCallBack->addItem("Iteration Limit",
                          CCopasiParameter::UINT,
                          & mIteration,
                          & mIterationLimit);

  mSwarmSize = * getValue("Swarm Size").pUINT;
  mTolerance = * getValue("Tolerance").pUDOUBLE;

  mpRandom =
    CRandom::createGenerator(* (CRandom::Type *) getValue("Random Number Generator").pUINT,
                             * (unsigned C_INT32 *) getValue("Seed").pUINT);

  mVariableSize = mpOptItem->size();

  mIndividuals.resize(mSwarmSize);

  for (unsigned C_INT32 i = 0; i < mSwarmSize; i++)
    mIndividuals[i].resize(mVariableSize);

  mValues.resize(mSwarmSize);
  mVelocities.resize(mSwarmSize, mVariableSize);
  mBestValues.resize(mSwarmSize);
  mBestPositions.resize(mSwarmSize, mVariableSize);

  mNumInformed = std::max<unsigned C_INT32>(mSwarmSize / 10, 5);

  mContinue = true;

  return mContinue;
}

#ifdef WIN32
# pragma warning (default: 4056 4756)
#endif

bool COptMethodPS::cleanup()
{
  pdelete(mpRandom);

  return true;
}

void COptMethodPS::buildInformants()
{
  mInformants.clear();
  mInformants.resize(mSwarmSize);

  unsigned C_INT32 i, j;
  unsigned C_INT32 Informed;

  for (i = 0; i < mSwarmSize; i++)
    {
      mInformants[i].insert(i);

      for (j = 1; j < mNumInformed; j++)
        {
          Informed = (i + 1 + mpRandom->getRandomU(mSwarmSize - 2)) % mSwarmSize;
          mInformants[Informed].insert(i);
        }
    }

  return;
}

bool COptMethodPS::reachedTolerance()
{
  // Check whether the swarm has settled
  C_FLOAT64 sum = 0.0;
  C_FLOAT64 curmin = 0.0;

  for (unsigned C_INT32 i = 0; i < mSwarmSize; ++i)
    {
      sum += mValues[i];
      curmin += mValues[i] * mValues[i];
    }

  sum /= mSwarmSize;
  curmin /= mSwarmSize;

  return (sqrt(curmin - sum * sum) < mTolerance);
}

bool COptMethodPS::optimise()
{
  unsigned C_INT32 i;

  if (!initialize()) return false;

  C_FLOAT64 * pIndividual = mIndividuals[0].array();
  C_FLOAT64 * pEnd = pIndividual + mVariableSize;
  C_FLOAT64 * pVelocity = mVelocities[0];
  C_FLOAT64 * pBestPosition = mBestPositions[0];
  std::vector< COptItem * >::const_iterator itOptItem = mpOptItem->begin();
  std::vector< UpdateMethod * >::const_iterator itSetCalculateVariable = mpSetCalculateVariable->begin();

  // initialise the population
  // first individual is the initial guess
  for (; pIndividual != pEnd;
       ++pIndividual, ++pVelocity, ++pBestPosition, ++itOptItem, ++itSetCalculateVariable)
    {
      COptItem & OptItem = **itOptItem;

      *pIndividual = *OptItem.getObjectValue();

      // force it to be within the bounds
      switch (OptItem.checkConstraint(*pIndividual))
        {
        case - 1:
          *pIndividual = *OptItem.getLowerBoundValue();
          break;

        case 1:
          *pIndividual = *OptItem.getUpperBoundValue();
          break;
        }

      *pBestPosition = *pIndividual;
      *pVelocity = 0.0;

      // We need to set the value here so that further checks take
      // account of the value.
      (**itSetCalculateVariable)(*pIndividual);
    }

  // calculate its fitness
  mBestValues[0] = mValues[0] = evaluate();

  // and store that value
  mBestIndex = 0;
  mpOptProblem->setSolutionVariables(mIndividuals[0]);
  mContinue &= mpOptProblem->setSolutionValue(mBestValues[0]);

  // We found a new best value lets report it.
  mpParentTask->output(COutputInterface::DURING);

  // the others are random
  for (i = 1; i < mSwarmSize && mContinue; i++)
    create(i);

  // create the informant list
  buildInformants();

  bool Improved;

  for (; mIteration < mIterationLimit && mContinue; mIteration++)
    {
      Improved = false;

      for (i = 0; i < mSwarmSize; i++)
        Improved |= move(i);

      if (!Improved)
        buildInformants();
      else if (reachedTolerance())
        break;

      if (mpCallBack)
        mContinue &= mpCallBack->progress(mhIteration);
    }

  cleanup();

  return mContinue;
}
