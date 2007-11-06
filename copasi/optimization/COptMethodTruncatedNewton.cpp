// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodTruncatedNewton.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: jdada $
//   $Date: 2007/11/06 15:01:39 $
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

{
  initObjects();
}

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

  // initial point is the first guess but we have to make sure that
  // we are within the parameter domain
  C_INT i, repeat;

  for (i = 0; i < mVariableSize; i++)
    {
      const COptItem & OptItem = *(*mpOptItem)[i];

      low[i] = *OptItem.getLowerBoundValue();
      up[i] = *OptItem.getUpperBoundValue();

      mCurrent[i] = *OptItem.getObjectValue();

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

  repeat = 0;
  do
    {
      if (repeat > 0)
        {
          for (i = 0; i < mVariableSize; i++)
            {
              mCurrent[i] = mCurrent[i] * (1 + 0.2);
              //force it to be within the bounds
              if (mCurrent[i] <= low[i]) mCurrent[i] = low[i] + 5 * DBL_EPSILON;
              else
                if (mCurrent[i] >= up[i]) mCurrent[i] = up[i] - 5 * DBL_EPSILON;

              (*(*mpSetCalculateVariable)[i])(mCurrent[i]);
            }
        }

      // calculate the function value at this point
      evaluateFunction(&mVariableSize, mCurrent.array(), &mEvaluationValue);
      // mBest = mCurrent;

      initialParam = mCurrent;
      if (repeat == 0) initialValue = mEvaluationValue;

      // estimate minimum is 1/10 initial function value
      fest = 0.1 * mEvaluationValue;

      // minimise
      try
        {
          tnbc_(&ierror, &mVariableSize, mCurrent.array(), &fest, mGradient.array(), dwork.array(),
                &lw, mpTruncatedNewton, low.array(), up.array(), iPivot.array());
          repeat = 0;
          mEvaluationValue = fest;
        }
      catch (unsigned C_INT e)
        {
          C_INT feasibleParams = 0;

          //varify adjustable parameter constraints
          for (i = 0; i < mVariableSize; i++)
            {
              mCurrent[i] = mCurrent[i];
              const COptItem & OptItem = *(*mpOptItem)[i];
              switch (OptItem.checkConstraint(mCurrent[i]))
                {
                case - 1:
                  feasibleParams = 1;
                  break;

                case 1:
                  feasibleParams = 1;
                  break;

                case 0:
                  break;
                }
            }
          // caculate the function value at this point
          if (!feasibleParams)
            {
              evaluateFunction(&mVariableSize, mCurrent.array(), &mEvaluationValue);
              std::cout << "mValues02: \t" << mEvaluationValue << std::endl;

              // is it better than initial guess?
              if (mEvaluationValue < initialValue) repeat = 0;
              else repeat++;
            }
          else
            {
              if (repeat < 3) repeat++;
              else
                {
                  // first guess is our only possible answer
                  mEvaluationValue = initialValue;
                  mCurrent = initialParam;
                  repeat = 0;
                }
            }
        }
    }
  while (repeat);

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

// objective function evaluation for specified parameter
bool COptMethodTruncatedNewton::evaluateFunction(C_INT *n, C_FLOAT64 *x, C_FLOAT64 *f)
{
  C_INT32 i;

  // set the parameter values
  for (i = 0; i < *n; i++)
    {
      (*(*mpSetCalculateVariable)[i])(x[i]);
    }

  //carry out the function evaluation
  mEvaluationValue = evaluate();

  // We found a new best value lets report it.
  mBest = mCurrent;
  if (!isnan(mEvaluationValue))
    {
      // and store that value
      mBestValue = mEvaluationValue;
      mContinue = mpOptProblem->setSolution(mBestValue, mBest);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  *f = mBestValue;
  return true;
}

// callback function, evaluate the value of the objective function and its gradient
//(by finite differences), translated by f2c, edited by Pedro and then modified for COPASI by Joseph
C_INT COptMethodTruncatedNewton::sFun(C_INT *n, C_FLOAT64 *x, C_FLOAT64 *f, C_FLOAT64 *g)
{
  C_INT i, i_1;
  C_FLOAT64 h, h1, fh, xh;

  //parameter adjustments
  --g;
  --x;

  h = 0.01; h1 = h + 1.0;

  //evaluate function
  evaluateFunction(n, &x[1], f);
  i_1 = *n;
  for (i = 1; i <= i_1; ++i)
    {
      xh = x[i];
      x[i] *= h1;

      // evalute function
      evaluateFunction(n, &x[1], &fh);
      g[i] = (fh - *f) / (h * xh);
      x[i] = xh;
    }
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
