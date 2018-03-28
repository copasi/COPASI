// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// adapted by Pedro Mendes, April 2005, from the original Gepasi file
// levmarq.cpp : Restricted step Newton method (Marquardt iteration)

#include <cmath>
#include "copasi.h"

#include "COptMethodLevenbergMarquardt.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "parameterFitting/CFitProblem.h"
#include "copasi/core/CDataObjectReference.h"

#include "lapack/lapackwrap.h"
#include "lapack/blaswrap.h"

#define LAMBDA_MAX 1e80

COptMethodLevenbergMarquardt::COptMethodLevenbergMarquardt(const CDataContainer * pParent,
  const CTaskEnum::Method & methodType,
  const CTaskEnum::Task & taskType) :
  COptMethod(pParent, methodType, taskType),
  mIterationLimit(2000),
  mTolerance(1.e-006),
  mModulation(1.e-006),
  mIteration(0),
  mParameterOutOfBounds(0),
  mhIteration(C_INVALID_INDEX),
  mVariableSize(0),
  mCurrent(),
  mBest(),
  mGradient(),
  mStep(),
  mHessian(),
  mHessianLM(),
  mTemp(),
  mBestValue(std::numeric_limits< C_FLOAT64 >::infinity()),
  mEvaluationValue(std::numeric_limits< C_FLOAT64 >::infinity()),
  mStopAfterStalledIterations(0),
  mContinue(true),
  mHaveResiduals(false),
  mResidualJacobianT()
{
  addParameter("Iteration Limit", CCopasiParameter::UINT, (unsigned C_INT32) 2000);
  addParameter("Tolerance", CCopasiParameter::DOUBLE, (C_FLOAT64) 1.e-006);

  if (mEnableAdditionalParameters)
  {
    addParameter("Modulation", CCopasiParameter::DOUBLE, (C_FLOAT64) 1.e-006);
    addParameter("Stop after # Stalled Iterations", CCopasiParameter::UINT, (unsigned C_INT32) 0);
  }

  addParameter("Log Verbosity", CCopasiParameter::UINT, (unsigned C_INT32) 0);

  initObjects();
}

COptMethodLevenbergMarquardt::COptMethodLevenbergMarquardt(const COptMethodLevenbergMarquardt & src,
    const CDataContainer * pParent):
  COptMethod(src, pParent),
  mIterationLimit(src.mIterationLimit),
  mTolerance(src.mTolerance),
  mModulation(src.mModulation),
  mIteration(0),
  mParameterOutOfBounds(0),
  mhIteration(C_INVALID_INDEX),
  mVariableSize(0),
  mCurrent(),
  mBest(),
  mGradient(),
  mStep(),
  mHessian(),
  mHessianLM(),
  mTemp(),
  mBestValue(std::numeric_limits< C_FLOAT64 >::infinity()),
  mEvaluationValue(std::numeric_limits< C_FLOAT64 >::infinity()),
  mStopAfterStalledIterations(0),
  mContinue(true),
  mHaveResiduals(false),
  mResidualJacobianT()
{initObjects();}

COptMethodLevenbergMarquardt::~COptMethodLevenbergMarquardt()
{cleanup();}

void COptMethodLevenbergMarquardt::initObjects()
{
  addObjectReference("Current Iteration", mIteration, CDataObject::ValueInt);

  if(!mEnableAdditionalParameters)
  removeParameter("Modulation");
}

bool COptMethodLevenbergMarquardt::optimise()
{
  if (!initialize())
    {
      if (mpCallBack)
        mpCallBack->finishItem(mhIteration);

      return false;
    }

  mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_start).with("OD.Levenberg.Marquardt"));

  C_INT dim, starts, info, nrhs;
  C_INT one = 1;

  size_t i;
  C_FLOAT64 LM_lambda, nu, convp, convx;
  bool calc_hess;
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
  bool pointInParameterDomain = true;

  for (i = 0; i < mVariableSize; i++)
    {
      const COptItem & OptItem = *(*mpOptItem)[i];

      switch (OptItem.checkConstraint(OptItem.getStartValue()))
        {
          case -1:
            mCurrent[i] = *OptItem.getLowerBoundValue();
            pointInParameterDomain = false;
            break;

          case 1:
            mCurrent[i] = *OptItem.getUpperBoundValue();
            pointInParameterDomain = false;
            break;

          case 0:
            mCurrent[i] = OptItem.getStartValue();
            break;
        }

      *mContainerVariables[i] = mCurrent[i];
    }

  if (!pointInParameterDomain) mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_initial_point_out_of_domain));

  // keep the current parameter for later
  mBest = mCurrent;

  evaluate();

  if (!isnan(mEvaluationValue))
    {
      // and store that value
      mBestValue = mEvaluationValue;
      mContinue &= mpOptProblem->setSolution(mBestValue, mBest);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  // Initialize LM_lambda
  LM_lambda = 1.0;
  nu = 2.0;
  calc_hess = true;
  starts = 1;

  size_t Stalled = 0;

  for (mIteration = 0; (mIteration < mIterationLimit) && (nu != 0.0) && mContinue;
       mIteration++, Stalled++)
    {

      if (mStopAfterStalledIterations != 0 && Stalled > mStopAfterStalledIterations)
        break;

      // calculate gradient and Hessian
      if (calc_hess) hessian();

      calc_hess = true;

      // mHessianLM will be used for Cholesky decomposition
      mHessianLM = mHessian;

      // add Marquardt lambda to Hessian
      // put -gradient in h
      for (i = 0; i < mVariableSize; i++)
        {
          mHessianLM[i][i] *= 1.0 + LM_lambda; // Improved
          // mHessianLM[i][i] += LM_lambda; // Original
          mStep[i] = - mGradient[i];
        }

      // SUBROUTINE DSYTRF(UPLO, N, A, LDA, IPIV, WORK, LWORK, INFO)
      // dsytrf_("L", &dim, mHessianLM.array(), &dim, Pivot.array(),
      //         Work.array(), &LWork, &info);

      // SUBROUTINE DPOTRF(UPLO, N, A, LDA, INFO)
      // Cholesky factorization
      char UPLO = 'L';
      dpotrf_(&UPLO, &dim, mHessianLM.array(), &dim, &info);

      // if Hessian is positive definite solve Hess * h = -grad
      if (info == 0)
        {
          if (mLogVerbosity >= 1) mMethodLog.enterLogItem(COptLogItem(COptLogItem::LM_hess_pos_def).iter(mIteration));

          // SUBROUTINE DPOTRS(UPLO, N, NRHS, A, LDA, B, LDB, INFO)
          dpotrs_(&UPLO, &dim, &one, mHessianLM.array(), &dim, mStep.array(), &dim, &info);

          // SUBROUTINE DSYTRS(UPLO, N, NRHS, A, LDA, IPIV, B, LDB, INFO);
          // dsytrs_("L", &dim, &one, mHessianLM.array(), &dim, Pivot.array(), mStep.array(),
          //         &dim, &info);
        }
      else
        {
          if (mLogVerbosity >= 1 && info > 0) mMethodLog.enterLogItem(COptLogItem(COptLogItem::LM_hess_not_pos_def).iter(mIteration).with(info));

          // We are in a concave region. Thus the current step is an over estimation.
          // We reduce it by dividing by lambda
          for (i = 0; i < mVariableSize; i++)
            {
              mStep[i] /= LM_lambda;
            }
        }

//REVIEW:START
// This code is different between Gepasi and COPASI
// Gepasi goes along the direction until it hits the boundary
// COPASI moves in a different direction; this could be a problem

      // Force the parameters to stay within the defined boundaries.
      // Forcing the parameters gives better solution than forcing the steps.
      // It gives same results with Gepasi.
      pointInParameterDomain = true;

      for (i = 0; i < mVariableSize; i++)
        {
          mCurrent[i] = mBest[i] + mStep[i];

          const COptItem & OptItem = *(*mpOptItem)[i];

          switch (OptItem.checkConstraint(mCurrent[i]))
            {
              case - 1:
                mCurrent[i] = *OptItem.getLowerBoundValue() + std::numeric_limits< C_FLOAT64 >::epsilon();
                pointInParameterDomain = false;
                break;

              case 1:
                mCurrent[i] = *OptItem.getUpperBoundValue() - std::numeric_limits< C_FLOAT64 >::epsilon();
                pointInParameterDomain = false;
                break;

              case 0:
                break;
            }
        }

      if (!pointInParameterDomain) mParameterOutOfBounds++;

// This is the Gepasi code, which would do the truncation along the search line

      // Assure that the step will stay within the bounds but is
      // in its original direction.
      /* C_FLOAT64 Factor = 1.0;
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
       */
//REVIEW:END

      // calculate the relative change in each parameter
      for (convp = 0.0, i = 0; i < mVariableSize; i++)
        {
          *mContainerVariables[i] = mCurrent[i];
          convp += fabs((mCurrent[i] - mBest[i]) / mBest[i]);
        }

      // calculate the objective function value
      evaluate();

      // set the convergence check amplitudes
      // convx has the relative change in objective function value
      convx = (mBestValue - mEvaluationValue) / mBestValue;
      // convp has the average relative change in parameter values
      convp /= mVariableSize;

      if (mEvaluationValue < mBestValue)
        {

          Stalled = 0;

          // keep this value
          mBestValue = mEvaluationValue;

          // store the new parameter set
          mBest = mCurrent;

          // Inform the problem about the new solution.
          mContinue &= mpOptProblem->setSolution(mBestValue, mBest);

          // We found a new best value lets report it.
          mpParentTask->output(COutputInterface::DURING);

          // decrease LM_lambda
          LM_lambda /= nu;

          if ((convp < mTolerance) && (convx < mTolerance))
            {
              if (starts < 3)
                {
                  mMethodLog.enterLogItem(COptLogItem(COptLogItem::LM_fval_and_param_change_lower_than_tol).iter(mIteration).with(starts));

                  // let's restart with lambda=1
                  LM_lambda = 1.0;
                  starts++;
                }
              else
                {
                  mMethodLog.enterLogItem(COptLogItem(COptLogItem::LM_fval_and_param_change_lower_than_tol_termination).iter(mIteration).with(starts));
                  // signal the end
                  nu = 0.0;
                }
            }
        }
      else
        {
          // restore the old parameter values
          mCurrent = mBest;

          for (i = 0; i < mVariableSize; i++)
            *mContainerVariables[i] = mCurrent[i];

          // if lambda too high terminate
          if (LM_lambda > LAMBDA_MAX)
            {
              mMethodLog.enterLogItem(COptLogItem(COptLogItem::LM_lambda_max_termination).iter(mIteration));

              nu = 0.0;
            }
          else
            {
              if (mLogVerbosity >= 1) mMethodLog.enterLogItem(COptLogItem(COptLogItem::LM_inc_lambda).iter(mIteration));

              // increase lambda
              LM_lambda *= nu * 2;
              // don't recalculate the Hessian
              calc_hess = false;
              // correct the number of iterations
              mIteration--;
            }
        }

      if (mpCallBack)
        mContinue &= mpCallBack->progressItem(mhIteration);
    }

  mMethodLog.enterLogItem(COptLogItem(COptLogItem::LM_count_edge_of_param_domain).with(mParameterOutOfBounds));
  mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_finish_x_of_max_iter).iter(mIteration).with(mIterationLimit));

  if (mpCallBack)
    mpCallBack->finishItem(mhIteration);

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

  // when we leave either the parameter or functional domain
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

  mModulation = 0.001;
  mIterationLimit = getValue< unsigned C_INT32 >("Iteration Limit");
  mTolerance = getValue< C_FLOAT64 >("Tolerance");
  mLogVerbosity = getValue< unsigned C_INT32 >("Log Verbosity");

  if (getParameter("Modulation"))
  mModulation = getValue< C_FLOAT64 >("Modulation");

  mIteration = 0;

  if (mpCallBack)
    mhIteration =
      mpCallBack->addItem("Current Iteration",
                          mIteration,
                          & mIterationLimit);

  mVariableSize = mpOptItem->size();

  mCurrent.resize(mVariableSize);
  mBest.resize(mVariableSize);
  mStep.resize(mVariableSize);
  mGradient.resize(mVariableSize);
  mHessian.resize(mVariableSize, mVariableSize);

  mBestValue = std::numeric_limits<C_FLOAT64>::infinity();

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

  if (getParameter("Stop after # Stalled Iterations"))
  mStopAfterStalledIterations = getValue <unsigned C_INT32>("Stop after # Stalled Iterations");

  return true;
}

// evaluate the value of the gradient by forward finite differences
void COptMethodLevenbergMarquardt::gradient()
{
  size_t i;

  C_FLOAT64 y;
  C_FLOAT64 x;
  C_FLOAT64 mod1;

  mod1 = 1.0 + mModulation;

  y = evaluate();

  for (i = 0; i < mVariableSize && mContinue; i++)
    {
//REVIEW:START
      if ((x = mCurrent[i]) != 0.0)
        {
          *mContainerVariables[i] = (x * mod1);
          mGradient[i] = (evaluate() - y) / (x * mModulation);
        }

      else
        {
          *mContainerVariables[i] = (mModulation);
          mGradient[i] = (evaluate() - y) / mModulation;
        }

//REVIEW:END
      *mContainerVariables[i] = (x);
    }
}

//evaluate the Hessian
void COptMethodLevenbergMarquardt::hessian()
{
  size_t i, j;
  C_FLOAT64 mod1;

  mod1 = 1.0 + mModulation;

  if (mHaveResiduals)
    {
      evaluate();

      const CVector< C_FLOAT64 > & Residuals =
        static_cast<CFitProblem *>(mpOptProblem)->getResiduals();

      const CVector< C_FLOAT64 > CurrentResiduals = Residuals;

      size_t ResidualSize = Residuals.size();

      C_FLOAT64 * pJacobianT = mResidualJacobianT.array();

      const C_FLOAT64 * pCurrentResiduals;
      const C_FLOAT64 * pEnd = CurrentResiduals.array() + ResidualSize;
      const C_FLOAT64 * pResiduals;

      C_FLOAT64 Delta;
      C_FLOAT64 x;

      for (i = 0; i < mVariableSize && mContinue; i++)
        {
//REVIEW:START
          if ((x = mCurrent[i]) != 0.0)
            {
              Delta = 1.0 / (x * mModulation);
              *mContainerVariables[i] = (x * mod1);
            }

          else
            {
              Delta = 1.0 / mModulation;
              *mContainerVariables[i] = (mModulation);
//REVIEW:END
            }

          // evaluate another column of the Jacobian
          evaluate();
          pCurrentResiduals = CurrentResiduals.array();
          pResiduals = Residuals.array();

          for (; pCurrentResiduals != pEnd; pCurrentResiduals++, pResiduals++, pJacobianT++)
            *pJacobianT = (*pResiduals - *pCurrentResiduals) * Delta;

          *mContainerVariables[i] = (x);
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
            *pGradient += *pJacobianT **pCurrentResiduals;

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
                *pHessian += *pJacobianT **pJacobian;

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
//REVIEW:START
          if ((x = mCurrent[i]) != 0.0)
            {
              mCurrent[i] = x * mod1;
              Delta = 1.0 / (x * mModulation);
            }
          else
            {
              mCurrent[i] = mModulation;
              Delta = 1.0 / mModulation;
//REVIEW:END
            }

          *mContainerVariables[i] = mCurrent[i];
          gradient();

          for (j = 0; j <= i; j++)
            mHessian[i][j] = (mGradient[j] - mTemp[j]) * Delta;

          // restore the original parameter value
          mCurrent[i] = x;
          *mContainerVariables[i] = (x);
        }

      // restore the gradient
      mGradient = mTemp;
    }

  // make the matrix symmetric
  // not really necessary
  for (i = 0; i < mVariableSize; i++)
    for (j = i + 1; j < mVariableSize; j++)
      mHessian[i][j] = mHessian[j][i];
}

unsigned C_INT32 COptMethodLevenbergMarquardt::getMaxLogVerbosity() const
{
  return 1;
}
