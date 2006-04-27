/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodLevenbergMarquardt.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:29:53 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// adapted by Pedro Mendes, April 2005, from the original Gepasi file
// levmarq.cpp : Restricted step Newton method (Marquardt iteration)

#include "copasi.h"

#include "COptMethod.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "parameterFitting/CFitProblem.h"
#include "report/CCopasiObjectReference.h"

#include "clapackwrap.h"
#include "blaswrap.h"

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
  C_INT one = 1;

  unsigned C_INT32 i;
  C_FLOAT64 tmp, LM_lambda, nu, convp, convx;
  bool calc_grad, calc_hess;
  nrhs = 1;

  dim = (C_INT) mVariableSize;

#ifdef XXXX
  CVector< C_INT > Pivot(dim);
  CVector< C_FLOAT64 > Work(1);
  C_INT LWork = -1;

  //  SUBROUTINE DSYTRF(UPLO, N, A, LDA, IPIV, WORK, LWORK, INFO)
  dsytrf_("L", &dim, mHessianLM.array(), &dim, Pivot.array(),
          Work.array(), &LWork, &info);
  LWork = Work[0];
  Work.resize(LWork);
#endif // XXXX

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

      (*(*mpSetCalculateVariable)[i])(mCurrent[i]);
    }

  // keep the current parameter for later
  mBest = mCurrent;

  evaluate();

  if (!isnan(mEvaluationValue))
    {
      // and store that value
      mBestValue = mEvaluationValue;
      mpOptProblem->setSolutionVariables(mBest);
      mContinue &= mpOptProblem->setSolutionValue(mBestValue);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  // initialise LM_lambda
  LM_lambda = 1.0;
  nu = 2.0;
  calc_hess = true;
  starts = 1;

  for (mIteration = 0; (mIteration < mIterationLimit) && (nu != 0.0) && mContinue; mIteration++)
    {
      // calculate gradient and hessian
      if (calc_hess) hessian();

      calc_hess = true;

      // Cholesky decomposition of Hessian
      mHessianLM = mHessian;
      // add Marquardt lambda to Hessian
      // put -gradient in h
      for (i = 0; i < mVariableSize; i++)
        {
          mHessianLM[i][i] *= 1.0 + LM_lambda; // Improved
          // mHessianLM[i][i] += LM_lambda; // Orginal
          mStep[i] = - mGradient[i];
        }

      // SUBROUTINE DSYTRF(UPLO, N, A, LDA, IPIV, WORK, LWORK, INFO)
      // dsytrf_("L", &dim, mHessianLM.array(), &dim, Pivot.array(),
      //         Work.array(), &LWork, &info);

      // SUBROUTINE DPOTRF(UPLO, N, A, LDA, INFO)
      dpotrf_("L", &dim, mHessianLM.array(), &dim, &info);

      // if Hessian is positive definite solve Hess * h = -grad
      if (info == 0)
        {
          // SUBROUTINE DPOTRS(UPLO, N, NRHS, A, LDA, B, LDB, INFO)
          dpotrs_("L", &dim, &one, mHessianLM.array(), &dim, mStep.array(), &dim, &info);

          // SUBROUTINE DSYTRS(UPLO, N, NRHS, A, LDA, IPIV, B, LDB, INFO);
          // dsytrs_("L", &dim, &one, mHessianLM.array(), &dim, Pivot.array(), mStep.array(),
          //         &dim, &info);
        }

      // Assure that the step will stay within the bounds but is
      // in its original direction.
      C_FLOAT64 Factor = 1.0;
      while (true)
        {
          convp = 0.0;

          for (i = 0; i < mVariableSize; i++)
            {
              mStep[i] *= Factor;
              mCurrent[i] = mBest[i] + mStep[i];
            }

          Factor = 1.0;

          for (i = 0; i < mVariableSize; i++)
            {
              const COptItem & OptItem = *(*mpOptItem)[i];

              switch (OptItem.checkConstraint(mCurrent[i]))
                {
                case - 1:
                  Factor =
                    std::min(Factor, (*OptItem.getLowerBoundValue() - mBest[i]) / mStep[i]);
                  break;

                case 1:
                  Factor =
                    std::min(Factor, (*OptItem.getUpperBoundValue() - mBest[i]) / mStep[i]);
                  break;

                case 0:
                  break;
                }
            }

          if (Factor == 1.0) break;
        }

      for (i = 0; i < mVariableSize; i++)
        {
          (*(*mpSetCalculateVariable)[i])(mCurrent[i]);
          convp += fabs((mCurrent[i] - mBest[i]) / mBest[i]);
        }

      // calculate the objective function value
      evaluate();

      // set the convergence check amplitudes
      convx = (mBestValue - mEvaluationValue) / mBestValue;
      convp /= mVariableSize;

      if (mEvaluationValue < mBestValue)
        {
          // keep this value
          mBestValue = mEvaluationValue;

          // store the new parameter set
          mBest = mCurrent;

          // Inform the problem about the new solution.
          mpOptProblem->setSolutionVariables(mBest);
          mContinue &= mpOptProblem->setSolutionValue(mBestValue);

          // We found a new best value lets report it.
          mpParentTask->output(COutputInterface::DURING);

          // decrease LM_lambda
          LM_lambda /= nu;

          if ((convp < mTolerance) && (convx < mTolerance))
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
          mCurrent = mBest;
          for (i = 0; i < mVariableSize; i++)
            (*(*mpSetCalculateVariable)[i])(mCurrent[i]);

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
        }

      if (mpCallBack)
        mContinue &= mpCallBack->progress(mhIteration);
    }
  return true;
}

bool COptMethodLevenbergMarquardt::cleanup()
{
  return true;
}

const C_FLOAT64 & COptMethodLevenbergMarquardt::evaluate()
{
  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  mContinue &= mpOptProblem->calculate();
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
  mBest.resize(mVariableSize);
  mStep.resize(mVariableSize);
  mGradient.resize(mVariableSize);
  mHessian.resize(mVariableSize, mVariableSize);

  mBestValue = 2.0 * DBL_MAX;

  mContinue = true;

  CFitProblem * pFitProblem = dynamic_cast< CFitProblem * >(mpOptProblem);
  if (pFitProblem != NULL)
    // if (false)
    {
      mHaveResiduals = true;
      pFitProblem->setResidualsRequired(true);
      mResidualJacobianT.resize(mVariableSize, pFitProblem->getResiduals().size());
    }
  else
    mHaveResiduals = false;

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
      if ((x = mCurrent[i]) != 0.0)
        {
          (*(*mpSetCalculateVariable)[i])(x * 1.001);
          mGradient[i] = (evaluate() - y) / (x * 0.001);
        }

      else
        {
          (*(*mpSetCalculateVariable)[i])(1e-7);
          mGradient[i] = (evaluate() - y) / 1e-7;
        }

      (*(*mpSetCalculateVariable)[i])(x);
    }
}

//evaluate the Hessian
void COptMethodLevenbergMarquardt::hessian()
{
  unsigned C_INT32 i, j;

  if (mHaveResiduals)
    {
      evaluate();

      const CVector< C_FLOAT64 > & Residuals =
        static_cast<CFitProblem *>(mpOptProblem)->getResiduals();

      const CVector< C_FLOAT64 > CurrentResiduals = Residuals;

      unsigned C_INT32 ResidualSize = Residuals.size();

      C_FLOAT64 * pJacobianT = mResidualJacobianT.array();

      const C_FLOAT64 * pCurrentResiduals;
      const C_FLOAT64 * pEnd = CurrentResiduals.array() + ResidualSize;
      const C_FLOAT64 * pResiduals;

      C_FLOAT64 Delta;
      C_FLOAT64 x;

      for (i = 0; i < mVariableSize && mContinue; i++)
        {
          if ((x = mCurrent[i]) != 0.0)
            {
              Delta = 1.0 / (x * 0.001);
              (*(*mpSetCalculateVariable)[i])(x * 1.001);
            }

          else
            {
              Delta = 1e7;
              (*(*mpSetCalculateVariable)[i])(1e-7);
            }

          // evaluate another column of the jacobian
          evaluate();
          pCurrentResiduals = CurrentResiduals.array();
          pResiduals = Residuals.array();

          for (; pCurrentResiduals != pEnd; pCurrentResiduals++, pResiduals++, pJacobianT++)
            *pJacobianT = (*pResiduals - *pCurrentResiduals) * Delta;

          (*(*mpSetCalculateVariable)[i])(x);
        }

#ifdef XXXX
      // calculate the gradient
      C_INT m = 1;
      C_INT n = mGradient.size();
      C_INT k = mResidualJacobianT.numCols(); /* == CurrentResiduals.size() */

      char op = 'N';

      C_FLOAT64 Alpha = 1.0;
      C_FLOAT64 Beta = 0.0;

      dgemm_("N", "T", &m, &n, &k, &Alpha,
             const_cast<C_FLOAT64 *>(CurrentResiduals.array()), &m,
             mResidualJacobianT.array(), &n, &Beta,
             const_cast<C_FLOAT64 *>(mGradient.array()), &m);
#endif //XXXX

      C_FLOAT64 * pGradient = mGradient.array();
      pJacobianT = mResidualJacobianT.array();

      for (i = 0; i < mVariableSize; i++, pGradient++)
        {
          *pGradient = 0.0;
          pCurrentResiduals = CurrentResiduals.array();

          for (; pCurrentResiduals != pEnd; pCurrentResiduals++, pJacobianT++)
            *pGradient += *pJacobianT * *pCurrentResiduals;

          // This is formally correct but cancels out with factor 2 below
          // *pGradient *= 2.0;
        }

      // calculate the Hessian
      C_FLOAT64 * pHessian;
      C_FLOAT64 * pJacobian;

      for (i = 0; i < mVariableSize; i++)
        {
          pHessian = mHessian[i];
          for (j = 0; j <= i; j++, pHessian++)
            {
              *pHessian = 0.0;
              pJacobianT = mResidualJacobianT[i];
              pEnd = pJacobianT + ResidualSize;
              pJacobian = mResidualJacobianT[j];

              for (; pJacobianT != pEnd; pJacobianT++, pJacobian++)
                *pHessian += *pJacobianT * *pJacobian;

              // This is formally correct but cancels out with factor 2 above
              // *pHessian *= 2.0;
            }
        }
    }
  else
    {
      C_FLOAT64 Delta;
      C_FLOAT64 x;

      // calculate the gradient
      gradient();

      // and store it
      mTemp = mGradient;

      // calculate rows of the Hessian
      for (i = 0; i < mVariableSize; i++)
        {
          if ((x = mCurrent[i]) != 0.0)
            {
              mCurrent[i] = x * 1.001;
              Delta = 1.0 / (x * 0.001);
            }
          else
            {
              mCurrent[i] = 1e-7;
              Delta = 1e7;
            }

          (*(*mpSetCalculateVariable)[i])(mCurrent[i]);
          gradient();

          for (j = 0; j <= i; j++)
            mHessian[i][j] = (mGradient[j] - mTemp[j]) * Delta;

          // restore the original parameter value
          mCurrent[i] = x;
          (*(*mpSetCalculateVariable)[i])(x);
        }

      // restore the gradient
      mGradient = mTemp;
    }

  // make the matrix symetric
  // not realy necessary
  for (i = 0; i < mVariableSize; i++)
    for (j = i + 1; j < mVariableSize; j++)
      mHessian[i][j] = mHessian[j][i];
}
