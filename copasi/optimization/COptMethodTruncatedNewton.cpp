// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodTruncatedNewton.cpp,v $
//   $Revision: 1.3.2.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/12/17 22:32:37 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "COptMethodTruncatedNewton.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "parameterFitting/CFitProblem.h"
#include "report/CCopasiObjectReference.h"

COptMethodTruncatedNewton::COptMethodTruncatedNewton(const CCopasiContainer * pParent):
    COptMethod(CCopasiTask::optimization, CCopasiMethod::TruncatedNewton, pParent),
    mpTruncatedNewton(new FTruncatedNewtonTemplate<COptMethodTruncatedNewton>(this, &COptMethodTruncatedNewton::sFun))
{initObjects();}

COptMethodTruncatedNewton::COptMethodTruncatedNewton(const COptMethodTruncatedNewton & src,
    const CCopasiContainer * pParent):
    COptMethod(src, pParent),
    mpTruncatedNewton(new FTruncatedNewtonTemplate<COptMethodTruncatedNewton>(this, &COptMethodTruncatedNewton::sFun))
{initObjects();}

COptMethodTruncatedNewton::~COptMethodTruncatedNewton()
{
  pdelete(mpTruncatedNewton);
  cleanup();
}

void COptMethodTruncatedNewton::initObjects()
{
  addObjectReference("Current Iteration", mIteration, CCopasiObject::ValueInt);
}

#ifdef WIN32
// warning C4056: overflow in floating-point constant arithmetic
// warning C4756: overflow in constant arithmetic
# pragma warning (disable: 4056 4756)
#endif

bool COptMethodTruncatedNewton::optimise()
{
  if (!initialize()) return false;

  C_FLOAT64 initialValue, fest;
  C_INT lw, ierror = 0;
  lw = 14 * mVariableSize;

  CVector< C_FLOAT64 > initialParam(mVariableSize);
  CVector< C_FLOAT64 > up(mVariableSize);
  CVector< C_FLOAT64 > low(mVariableSize);
  CVector< C_INT > iPivot(mVariableSize);
  CVector< C_FLOAT64 > dwork(lw);

  up = DBL_MAX;
  low = - DBL_MAX;

  // initial point is the first guess but we have to make sure that
  // we are within the parameter domain
  C_INT i, repeat;

  for (i = 0; i < mVariableSize; i++)
    {
      const COptItem & OptItem = *(*mpOptItem)[i];

      // :TODO: In COPASI the bounds are not necessarry fixed.
      // Since evaluate checks for boundaries and constraints this is not
      // needed. The question remaining is how does tnbc_ handle unconstraint problems?
      // low[i] = *OptItem.getLowerBoundValue();
      // up[i] = *OptItem.getUpperBoundValue();

      mCurrent[i] = OptItem.getStartValue();

      switch (OptItem.checkConstraint(mCurrent[i]))
        {
        case - 1:
          mCurrent[i] = *OptItem.getLowerBoundValue();
          break;

        case 1:
          mCurrent[i] = *OptItem.getUpperBoundValue();
          break;

        case 0:
          break;
        }

      // set the value
      (*(*mpSetCalculateVariable)[i])(mCurrent[i]);
    }

  // Report the first value as the current best
  mBestValue = evaluate();
  mBest = mCurrent;
  mContinue = mpOptProblem->setSolution(mBestValue, mBest);

  repeat = 0;

  while (repeat < 3 && mContinue)
    {
      initialParam = mCurrent;
      if (repeat == 0)
        initialValue = mEvaluationValue;

      // estimate minimum is 1/10 initial function value
      fest = 0.1 * mEvaluationValue;
      ierror = 0;

      // minimise
      try
        {
          tnbc_(&ierror, &mVariableSize, mCurrent.array(), &fest, mGradient.array(), dwork.array(),
                &lw, mpTruncatedNewton, low.array(), up.array(), iPivot.array());
          repeat = 0;
          mEvaluationValue = fest;
        }

      // This signals that the user opted to interupt
      catch (bool)
        {
          break;
        }

      if (ierror == 0)
        break;

      if (ierror < 0)
        fatalError(); // Invalid parameter values.

      repeat++;

      for (i = 0; i < mVariableSize; i++)
        {
          const COptItem & OptItem = *(*mpOptItem)[i];

          //force it to be within the bounds
          switch (OptItem.checkConstraint(mCurrent[i]))
            {
            case - 1:
              mCurrent[i] = *OptItem.getLowerBoundValue();
              break;

            case 1:
              mCurrent[i] = *OptItem.getUpperBoundValue();
              break;

            case 0:
              break;
            }
          (*(*mpSetCalculateVariable)[i])(mCurrent[i]);
        }

      evaluate();

      // is it better than initial guess?
      if (mEvaluationValue < mBestValue)
        {
          // We found a new best value lets report it.
          // and store that value
          mBest = mCurrent;
          mBestValue = mEvaluationValue;

          mContinue = mpOptProblem->setSolution(mBestValue, mBest);

          // We found a new best value lets report it.
          mpParentTask->output(COutputInterface::DURING);

          continue;
        }

      // Try another starting point
      for (i = 0; i < mVariableSize; i++)
        {
          mCurrent[i] *= 1.2;
          const COptItem & OptItem = *(*mpOptItem)[i];

          //force it to be within the bounds
          switch (OptItem.checkConstraint(mCurrent[i]))
            {
            case - 1:
              mCurrent[i] = *OptItem.getLowerBoundValue();
              break;

            case 1:
              mCurrent[i] = *OptItem.getUpperBoundValue();
              break;

            case 0:
              break;
            }

          (*(*mpSetCalculateVariable)[i])(mCurrent[i]);
        }

      evaluate();

      // Check whether we improved
      if (mEvaluationValue < mBestValue)
        {
          // We found a new best value lets report it.
          // and store that value
          mBest = mCurrent;
          mBestValue = mEvaluationValue;

          mContinue = mpOptProblem->setSolution(mBestValue, mBest);

          // We found a new best value lets report it.
          mpParentTask->output(COutputInterface::DURING);
        }
    }

  // Check whether we improved overall
  if (mEvaluationValue < mBestValue)
    {
      // We found a new best value lets report it.
      // and store that value
      mBest = mCurrent;
      mBestValue = mEvaluationValue;

      mContinue = mpOptProblem->setSolution(mBestValue, mBest);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  return true;
}

bool COptMethodTruncatedNewton::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mVariableSize = mpOptItem->size();
  mCurrent.resize(mVariableSize);
  mBest.resize(mVariableSize);

  mContinue = true;
  mBestValue = mpOptProblem->getSolutionValue();
  mGradient.resize(mVariableSize);

  return true;
}

bool COptMethodTruncatedNewton::cleanup()
{
  return true;
}

// callback function, evaluate the value of the objective function and its gradient
//(by finite differences), translated by f2c, edited by Pedro and then modified for COPASI by Joseph
C_INT COptMethodTruncatedNewton::sFun(C_INT *n, C_FLOAT64 *x, C_FLOAT64 *f, C_FLOAT64 *g)
{
  C_INT i;

  // set the parameter values
  for (i = 0; i < *n; i++)
    (*(*mpSetCalculateVariable)[i])(x[i]);

  //carry out the function evaluation
  *f = evaluate();

  // Check whether we improved
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

  // Calculate the gradient
  for (i = 0; i < *n && mContinue; i++)
    {
      if (x[i] != 0.0)
        {
          (*(*mpSetCalculateVariable)[i])(x[i] * 1.001);
          g[i] = (evaluate() - *f) / (x[i] * 0.001);
        }

      else
        {
          (*(*mpSetCalculateVariable)[i])(1e-7);
          g[i] = (evaluate() - *f) / 1e-7;
        }

      (*(*mpSetCalculateVariable)[i])(x[i]);
    }

  if (!mContinue)
    throw bool(mContinue);

  return 0;
}

const C_FLOAT64 & COptMethodTruncatedNewton::evaluate()
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
