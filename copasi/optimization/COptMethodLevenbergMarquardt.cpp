/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodLevenbergMarquardt.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: mendes $ 
   $Date: 2006/04/05 12:15:06 $
   End CVS Header */

// adapted by Pedro Mendes, April 2005, from the original Gepasi file
// levmarq.cpp : Restricted step Newton method (Marquardt iteration)

#include "copasi.h"

#include "COptMethod.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "report/CCopasiObjectReference.h"
#include "clapackwrap.h"

#define LAMBDA_MAX 1e80

COptMethodLevenbergMarquardt::COptMethodLevenbergMarquardt(const CCopasiContainer * pParent):
    COptMethod(CCopasiTask::optimization, CCopasiMethod::LevenbergMarquardt, pParent)
{
  addParameter("Iteration Limit", CCopasiParameter::UINT, (unsigned C_INT32) 200);
  addParameter("Tolerance", CCopasiParameter::DOUBLE, (C_FLOAT64) 1.e-005);

  initObjects();
}

COptMethodLevenbergMarquardt::COptMethodLevenbergMarquardt(const COptMethodLevenbergMarquardt & src,
    const CCopasiContainer * pParent):
    COptMethod(src, pParent)
{initObjects();}

COptMethodLevenbergMarquardt::~COptMethodLevenbergMarquardt()
{cleanup();}

void COptMethodLevenbergMarquardt::initObjects()
{
  addObjectReference("Current Iteration", mIteration, CCopasiObject::ValueInt);
}

#ifdef WIN32 
// warning C4056: overflow in floating-point constant arithmetic
// warning C4756: overflow in constant arithmetic
# pragma warning (disable: 4056 4756)
#endif

bool COptMethodLevenbergMarquardt::optimise()
{
  if (!initialize()) return false;

  C_INT dim, starts, info, nrhs;
  unsigned C_INT32 i;
  C_FLOAT64 tmp, LM_lambda, nu, convp, convx;
  bool calc_grad, calc_hess;
  nrhs = 1;

  // initial point is first guess but we have to make sure that we
  // are within the parameter domain
  for (i = 0; i < mVariableSize; i++)
    {
      const COptItem & OptItem = *(*mpOptItem)[i];

      switch (OptItem.checkConstraint())
        {
        case - 1:
          mCurrent[i] = *OptItem.getLowerBoundValue();
          break;

        case 1:
          mCurrent[i] = *OptItem.getUpperBoundValue();
          break;

        case 0:
          mCurrent[i] = *OptItem.getObjectValue();
          break;
        }
      // keep this value for later comparisons
      mOld[i] = mCurrent[i];

      (*(*mpSetCalculateVariable)[i])(mCurrent[i]);
    }
  mContinue = evaluate();
  mOldValue = mBestValue = mEvaluationValue;
  // signal the best result so far
  mpOptProblem->setSolutionVariables(mCurrent);
  mContinue = mpOptProblem->setSolutionValue(mBestValue);

  // initialise LM_lambda
  LM_lambda = 1.0;
  nu = 2.0;
  calc_hess = true;
  starts = 1;

  for (mIteration = 0; (mIteration < mIterationLimit) && (nu != 0.0) ; mIteration++)
    {
      // calculate gradient and hessian
      if (calc_hess) hessian(mCurrent);
      calc_hess = true;
      // put gradient in h
      mStep = mGradient;
      // add Marquardt lambda to Hessian
      for (i = 0; i <= mVariableSize; i++)
        mHessian[i][i] *= 1.0 + LM_lambda;
      // Cholesky decomposition of Hessian
      dim = (C_INT) mVariableSize;
      //  SUBROUTINE DPOTRF(UPLO, N, A, LDA, INFO)
      dpotrf_("L", &dim, mHessian.array(), &dim, &info);
      // if Hessian is positive definite solve Hess * h = -grad
      //  SUBROUTINE DPOTRS(UPLO, N, NRHS, A, LDA, B, LDB, INFO)
      if (info == 0) dpotrs_("L", &dim, &nrhs, mHessian.array(), &dim, mStep.array(), &dim, &info);
      // advance
      convp = 0.0;
      for (i = 0; i < mVariableSize; i++)
        {
          mCurrent[i] = mOld[i] + mStep[i];
          const COptItem & OptItem = *(*mpOptItem)[i];

          switch (OptItem.checkConstraint())
            {
            case - 1:
              mCurrent[i] = *OptItem.getLowerBoundValue();
              break;

            case 1:
              mCurrent[i] = *OptItem.getUpperBoundValue();
              break;

            case 0:
              mCurrent[i] = *OptItem.getObjectValue();
              break;
            }
          convp += fabs((mCurrent[i] - mOld[i]) / mOld[i]);

          (*(*mpSetCalculateVariable)[i])(mCurrent[i]);
        }
      // calculate the objective function value
      mContinue = evaluate();
      mBestValue = mEvaluationValue;
      // set the convergence check amplitudes
      convx = (mOldValue - mBestValue) / mOldValue;
      convp /= mVariableSize;
      if (LM_lambda * mBestValue <= LM_lambda * mOldValue)
        {
          // decrease LM_lambda
          LM_lambda /= nu;
          // keep this value
          mOldValue = mBestValue;
          // store the new parameter set
          mOld = mCurrent;
          if ((convp <= mTolerance) && (convx <= mTolerance))
            {
              if (starts < 3)
                {
                  // let's restart with lambda=1
                  LM_lambda = 1.0;
                  starts++;
                }
              else
                // signal the end
                nu = 0.0;
            }
        }
      else
        {
          // restore the old parameter values
          mCurrent = mOld;
          mBestValue = mOldValue;
          // if lambda too high terminate
          if (LM_lambda > LAMBDA_MAX) nu = 0.0;
          else
            {
              // increase lambda
              LM_lambda *= nu * 2;
              // don't recalculate the Hessian
              calc_hess = false;
              // correct the number of iterations
              mIteration--;
            }
          continue;
        }
      mpOptProblem->setSolutionVariables(mCurrent);
      mContinue = mpOptProblem->setSolutionValue(mBestValue);
      // We found a new best value lets report it.
      //if (mpReport) mpReport->printBody();
      mpParentTask->doOutput();

      if (mpCallBack)
        mContinue &= mpCallBack->progress(mhIteration);
    }
  return true;
}

bool COptMethodLevenbergMarquardt::cleanup()
{
  return true;
}

bool COptMethodLevenbergMarquardt::evaluate()
{
  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  // evaluate the fitness
  if (!mpOptProblem->checkParametricConstraints())
    {
      mEvaluationValue = DBL_MAX;
      return mContinue;
    }

  mContinue &= mpOptProblem->calculate();

  // check wheter the functional constraints are fulfilled
  if (!mpOptProblem->checkFunctionalConstraints())
    mEvaluationValue = DBL_MAX;
  else
    // get the value of the objective function
    mEvaluationValue = mpOptProblem->getCalculateValue();

  return mContinue;
}

bool COptMethodLevenbergMarquardt::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mIterationLimit = * getValue("Iteration Limit").pUINT;
  mTolerance = * getValue("Tolerance").pDOUBLE;

  mIteration = 0;
  if (mpCallBack)
    mhIteration =
      mpCallBack->addItem("Current Iteration",
                          CCopasiParameter::UINT,
                          & mIteration,
                          & mIterationLimit);

  mVariableSize = mpOptItem->size();

  mCurrent.resize(mVariableSize);
  mOld.resize(mVariableSize);
  mStep.resize(mVariableSize);
  mGradient.resize(mVariableSize);
  mHessian.resize(mVariableSize, mVariableSize);

  mBestValue = 2.0 * DBL_MAX;

  return true;
}

#ifdef WIN32
# pragma warning (default: 4056 4756)
#endif

// evaluate the value of the gradient by forward differences
void COptMethodLevenbergMarquardt::gradient()
{
  unsigned C_INT32 i;

  C_FLOAT64 y;
  C_FLOAT64 x;

  y = evaluate();

  for (i = 0; i < mVariableSize && mContinue; i++)
    {
      if ((x = *(*mpOptItem)[i]->getObjectValue()) != 0.0)
        {
          (*(*mpSetCalculateVariable)[i])(x * 1.001);
          mGradient[i] = (y - evaluate()) / (x * 0.001);
        }

      else
        {
          (*(*mpSetCalculateVariable)[i])(1e-7);
          mGradient[i] = (y - evaluate()) / 1e-7;
        }

      (*(*mpSetCalculateVariable)[i])(x);
    }
}

// evaluate the value of the gradient by forward differences
void COptMethodLevenbergMarquardt::gradientP(const CVector< C_FLOAT64 > &point)
{
  unsigned C_INT32 i;

  C_FLOAT64 y;
  C_FLOAT64 x;

  y = evaluate();
  for (i = 0; i < mVariableSize && mContinue; i++)
    {
      (*(*mpSetCalculateVariable)[i])(point[i]);
    }

  for (i = 0; i < mVariableSize && mContinue; i++)
    {
      if ((x = point[i]) != 0.0)
        {
          (*(*mpSetCalculateVariable)[i])(x * 1.001);
          mGradient[i] = (y - evaluate()) / (x * 0.001);
        }

      else
        {
          (*(*mpSetCalculateVariable)[i])(1e-7);
          mGradient[i] = (y - evaluate()) / 1e-7;
        }

      (*(*mpSetCalculateVariable)[i])(x);
    }
}

//evaluate the Hessian
void COptMethodLevenbergMarquardt::hessian(CVector< C_FLOAT64 > &point)
{
  unsigned C_INT32 i, j;
  C_FLOAT64 x;

  // calculate the gradient
  gradientP(point);
  // and store it
  mTemp = mGradient;

  // calculate rows of the Hessian
  for (i = 0; i < mVariableSize; i++)
    {
      if ((x = point[i]) != 0.0)
        {
          point[i] = x * 1.001;
          gradientP(point);
          for (j = 0; j < i; j++)
            mHessian[i][j] = (mGradient[j] - mTemp[j]) / (point[i] * 0.001);
        }
      else
        {
          point[i] = 1e-7;
          for (j = 0; j < i; j++)
            mHessian[i][j] = (mGradient[j] - mTemp[j]) * 1e7;
        }
      // restore the original parameter value
      point[i] = x;
    }
  // make the matrix symetric
  for (i = 0; i < mVariableSize; i++)
    for (j = i + 1; j < mVariableSize; j++)
      mHessian[i][j] = mHessian[j][i];
  // restore the gradient
  mGradient = mTemp;
}
