// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodPraxis.cpp,v $
//   $Revision: 1.4.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/12/14 21:21:58 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "COptMethodPraxis.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "parameterFitting/CFitProblem.h"
#include "report/CCopasiObjectReference.h"

COptMethodPraxis::COptMethodPraxis(const CCopasiContainer * pParent):
    COptMethod(CCopasiTask::optimization, CCopasiMethod::Praxis, pParent),
    mpPraxis(new FPraxisTemplate<COptMethodPraxis>(this, &COptMethodPraxis::evaluateFunction))

{
  addParameter("Tolerance", CCopasiParameter::DOUBLE, (C_FLOAT64) 1.e-005);
  initObjects();
}

COptMethodPraxis::COptMethodPraxis(const COptMethodPraxis & src,
                                   const CCopasiContainer * pParent):
    COptMethod(src, pParent),
    mpPraxis(new FPraxisTemplate<COptMethodPraxis>(this, &COptMethodPraxis::evaluateFunction))
{initObjects();}

COptMethodPraxis::~COptMethodPraxis()
{

  pdelete(mpPraxis);
  cleanup();
}

void COptMethodPraxis::initObjects()
{
  addObjectReference("Current Iteration", mIteration, CCopasiObject::ValueInt);
}

#ifdef WIN32
// warning C4056: overflow in floating-point constant arithmetic
// warning C4756: overflow in constant arithmetic
# pragma warning (disable: 4056 4756)
#endif

bool COptMethodPraxis::optimise()
{
  if (!initialize()) return false;

  C_INT i;
  C_INT prin = 0;
  C_FLOAT64 tmp = 0.0;
  C_FLOAT64 machep, stepmx, d1, d2;

  // initial point is the first guess but we have to make sure that
  // we are within the parameter domain

  for (i = 0; i < mVariableSize; i++)
    {
      const COptItem & OptItem = *(*mpOptItem)[i];
      mCurrent[i] = OptItem.getStartValue();

      //force it to be within the bounds
      switch (OptItem.checkConstraint(mCurrent[i]))
        {
        case - 1:
          mCurrent[i] = *OptItem.getLowerBoundValue();
          break;

        case 1:
          mCurrent[i] = *OptItem.getUpperBoundValue();
          break;
        }

      //set the value
      (*(*mpSetCalculateVariable)[i])(mCurrent[i]);
    }

  // Report the first value as the current best
  mBestValue = evaluate();
  mBest = mCurrent;
  mContinue = mpOptProblem->setSolution(mBestValue, mBest);

  // We found a new best value lets report it.
  mpParentTask->output(COutputInterface::DURING);

  //estimate the machine epsilon
  d1 = 1.0;
  do
    {
      d1 /= 2.0;
      d2 = d1 + 1.;
    }
  while (d2 != 1.0);
  machep = d1 * 2.0;

  //estimate the maximum step size
  stepmx = 0.6;

  //carry out the minimisation
  try
    {
      praxis_(&mTolerance, &machep, &stepmx, &mVariableSize, &prin, mCurrent.array(), mpPraxis, &tmp);
    }
  catch (bool)
  {}

  return mContinue;
}

bool COptMethodPraxis::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mTolerance = * getValue("Tolerance").pDOUBLE;
  mIteration = 0;

  mVariableSize = mpOptItem->size();
  mCurrent.resize(mVariableSize);
  mBest.resize(mVariableSize);

  mContinue = true;

  return true;
}

bool COptMethodPraxis::cleanup()
{
  return true;
}

// evaluate the value of the objective function
const C_FLOAT64 COptMethodPraxis::evaluateFunction(C_FLOAT64 *x, C_INT *n)
{
  C_INT i;
  for (i = 0; i < *n; i++)
    (*(*mpSetCalculateVariable)[i])(x[i]);

  //carry out the function evaluation
  evaluate();

  if (mEvaluationValue < mBestValue)
    {
      // We found a new best value lets report it.
      // and store that value
      for (i = 0; i < *n; i++)
        mBest[i] = x[i];

      mBestValue = mEvaluationValue;
      mContinue = mpOptProblem->setSolution(mBestValue, mBest);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  if (!mContinue)
    throw bool(mContinue);

  return mEvaluationValue;
}

const C_FLOAT64 & COptMethodPraxis::evaluate()
{
  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  mContinue = mpOptProblem->calculate();
  mEvaluationValue = mpOptProblem->getCalculateValue();

  // when we leave the either the parameter or functional domain
  // we penalize the objective value by forcing it to be larger
  // than the best value recorded so far.
  if (mEvaluationValue < mBestValue &&
      (!mpOptProblem->checkParametricConstraints() ||
       !mpOptProblem->checkFunctionalConstraints()))
    mEvaluationValue = mBestValue + mBestValue - mEvaluationValue;

  return mEvaluationValue;
}
