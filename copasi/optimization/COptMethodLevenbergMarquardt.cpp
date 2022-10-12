// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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
#include <sstream>

#include "copasi/copasi.h"
#include "COptMethodLevenbergMarquardt.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "copasi/parameterFitting/CFitProblem.h"
#include "copasi/core/CDataObjectReference.h"

#include "copasi/lapack/lapackwrap.h"
#include "copasi/lapack/blaswrap.h"

#define LAMBDA_MAX 1e80

COptMethodLevenbergMarquardt::COptMethodLevenbergMarquardt(const CDataContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType) :
  COptMethod(pParent, methodType, taskType, false),
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
  assertParameter("Iteration Limit", CCopasiParameter::Type::UINT, (unsigned C_INT32) 2000);
  assertParameter("Tolerance", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) 1.e-006);
  assertParameter("Modulation", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) 1.e-006, eUserInterfaceFlag::editable);
  assertParameter("Stop after # stalled iterations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);
  assertParameter("Initial Lambda", CCopasiParameter::Type::DOUBLE, (C_FLOAT64)1.0, eUserInterfaceFlag::editable);
  assertParameter("Lambda Decrease", CCopasiParameter::Type::DOUBLE, (C_FLOAT64)2.0, eUserInterfaceFlag::editable);
  assertParameter("Lambda Increase", CCopasiParameter::Type::DOUBLE, (C_FLOAT64)4.0, eUserInterfaceFlag::editable);

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
}

bool COptMethodLevenbergMarquardt::optimise()
{
  if (!initialize())
    {
      if (mProcessReport)
        mProcessReport.finishItem(mhIteration);

      return false;
    }

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry(
        "Levenberg-Marquardt algorithm started",
        "For more information about this method see: http://copasi.org/Support/User_Manual/Methods/Optimization_Methods/Levenberg_-_Marquardt/"
      )
    );

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
      const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[i];

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

      *mProblemContext.master()->getContainerVariables(true)[i] = mCurrent[i];
    }

  if (!pointInParameterDomain && (mLogVerbosity > 0))
    mMethodLog.enterLogEntry(COptLogEntry("Initial point outside parameter domain."));

  // keep the current parameter for later
  mBest = mCurrent;

  evaluate();

  if (!std::isnan(mEvaluationValue))
    {
      // and store that value
      mBestValue = mEvaluationValue;
      mContinue &= mProblemContext.master()->setSolution(mBestValue, mBest, true);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  // Initialize LM_lambda
  LM_lambda = mInitialLamda;
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
      if (calc_hess)
        {
          hessian();

          //std::ofstream ohess; ohess.open("hessian.txt"); ohess << mResidualJacobianT; ohess.close();
          //std::ofstream osens; osens.open("sens.txt"); osens << dynamic_cast<CFitProblem*>(mProblemContext.master())->getTimeSensJac(); osens.close();
        }

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
          if (mLogVerbosity > 2)
            mMethodLog.enterLogEntry(
              COptLogEntry(
                "Iteration " + std::to_string(mIteration) + ": Hessian matrix is positive definite. Calculating gradient."
              ));

          // SUBROUTINE DPOTRS(UPLO, N, NRHS, A, LDA, B, LDB, INFO)
          dpotrs_(&UPLO, &dim, &one, mHessianLM.array(), &dim, mStep.array(), &dim, &info);

          // SUBROUTINE DSYTRS(UPLO, N, NRHS, A, LDA, IPIV, B, LDB, INFO);
          // dsytrs_("L", &dim, &one, mHessianLM.array(), &dim, Pivot.array(), mStep.array(),
          //         &dim, &info);
        }
      else
        {
          if (mLogVerbosity > 1)
            mMethodLog.enterLogEntry(
              COptLogEntry(
                "Iteration " + std::to_string(mIteration) +
                ": Hessian matrix is not positive definite because the leading minor of order " +
                std::to_string(info) + " is not positive definite. Reducing step size."
              ));

          // We are in a concave region. Thus the current step is an over estimation.
          // We reduce it by dividing by lambda
          for (i = 0; i < mVariableSize; i++)
            {
              mStep[i] /= LM_lambda;
            }
        }

      if (mLogVerbosity > 2)
        {
          C_INT oit;
          std::ostringstream auxStream;

          for (oit = 0; oit < dim; oit++)
            auxStream << "x[" << oit << "]=" << mStep[oit] << " ";

          mMethodLog.enterLogEntry(COptLogEntry("search direction: ", "", auxStream.str()));
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

          const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[i];

          switch (OptItem.checkConstraint(mCurrent[i]))
            {
              case - 1:
                mCurrent[i] = *OptItem.getLowerBoundValue() + std::numeric_limits< C_FLOAT64 >::epsilon();

                if (mLogVerbosity > 2)
                  mMethodLog.enterLogEntry(
                    COptLogEntry(
                      "Iteration " + std::to_string(mIteration) +
                      ": parameter #" + std::to_string(i) + " below the lower bound."
                    ));

                pointInParameterDomain = false;
                break;

              case 1:
                mCurrent[i] = *OptItem.getUpperBoundValue() - std::numeric_limits< C_FLOAT64 >::epsilon();
                pointInParameterDomain = false;

                if (mLogVerbosity > 2)
                  mMethodLog.enterLogEntry(
                    COptLogEntry(
                      "Iteration " + std::to_string(mIteration) +
                      ": parameter #" + std::to_string(i) + " above the upper bound."
                    ));

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
          *mProblemContext.master()->getContainerVariables(true)[i] = mCurrent[i];
          convp += fabs((mCurrent[i] - mBest[i]) / mBest[i]);
        }

      // calculate the objective function value
      evaluate();

      if (mLogVerbosity > 1)
        {
          C_INT oit;
          std::ostringstream string1, string2;

          string1 << "niter=" << mIteration << ", f=" << mEvaluationValue << ", fbest=" << mBestValue;
          string2 << "position: ";

          for (oit = 0; oit < dim; oit++)
            string2 << "x[" << oit << "]=" << mCurrent[oit] << " ";

          mMethodLog.enterLogEntry(COptLogEntry(string1.str(), "", string2.str()));
        }

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
          mContinue &= mProblemContext.master()->setSolution(mBestValue, mBest, true);

          // We found a new best value lets report it.
          mpParentTask->output(COutputInterface::DURING);

          // decrease LM_lambda
          LM_lambda /= mLambdaDown; // nu

          if ((convp < mTolerance) && (convx < mTolerance))
            {
              if (starts < 3)
                {
                  if (mLogVerbosity > 1)
                    mMethodLog.enterLogEntry(
                      COptLogEntry(
                        "Iteration " + std::to_string(mIteration) +
                        ": Objective function value and parameter change lower than tolerance (" +
                        std::to_string(starts) + "/3). Resetting lambda."
                      ));

                  // let's restart with lambda=1
                  LM_lambda = mInitialLamda;
                  starts++;
                }
              else
                {
                  if (mLogVerbosity > 1)
                    mMethodLog.enterLogEntry(
                      COptLogEntry(
                        "Iteration " + std::to_string(mIteration) +
                        ": Objective function value and parameter change lower than tolerance (3/3). Terminating."
                      ));

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
            *mProblemContext.master()->getContainerVariables(true)[i] = mCurrent[i];

          // if lambda too high terminate
          if (LM_lambda > LAMBDA_MAX)
            {
              if (mLogVerbosity > 1)
                mMethodLog.enterLogEntry(
                  COptLogEntry(
                    "Iteration " + std::to_string(mIteration) +
                    ": Lambda reached maximal value. Terminating."
                  ));

              nu = 0.0;
            }
          else
            {
              // increase lambda
              LM_lambda *= mLambdaUp; // nu * 2;
              // don't recalculate the Hessian
              calc_hess = false;
              // correct the number of iterations
              mIteration--;

              if (mLogVerbosity > 1)
                {
                  std::ostringstream auxStream;
                  auxStream << LM_lambda;
                  mMethodLog.enterLogEntry(
                    COptLogEntry(
                      "Iteration " + std::to_string(mIteration) +
                      ": Restarting iteration with increased lambda.",
                      "Lambda = " + auxStream.str()));
                }
            }
        }

      if (mProcessReport)
        mContinue &= mProcessReport.progressItem(mhIteration);

      mpParentTask->output(COutputInterface::MONITORING);
    }

  if ((mLogVerbosity > 1) && (mParameterOutOfBounds > 0))
    mMethodLog.enterLogEntry(
      COptLogEntry("Algorithm reached the edge of the parameter domain " +
                   std::to_string(mParameterOutOfBounds) + " times."));

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry("Algorithm finished.",
                   "Terminated after " + std::to_string(mIteration) + " of " + std::to_string(mIterationLimit) + " iterations."
                  ));

  if (mProcessReport)
    mProcessReport.finishItem(mhIteration);

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

  mContinue &= mProblemContext.master()->calculate();
  mEvaluationValue = mProblemContext.master()->getCalculateValue();

  // when we leave either the parameter or functional domain
  // we penalize the objective value by forcing it to be larger
  // than the best value recorded so far.
  if (mEvaluationValue < mBestValue &&
      (!mProblemContext.master()->checkParametricConstraints() ||
       !mProblemContext.master()->checkFunctionalConstraints()))
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

  if (getParameter("Lambda Increase"))
    mLambdaUp = getValue<C_FLOAT64>("Lambda Increase");
  else
    mLambdaUp = 4;

  if (getParameter("Lambda Decrease"))
    mLambdaDown = getValue<C_FLOAT64>("Lambda Decrease");
  else
    mLambdaDown = 2;

  if (getParameter("Initial Lambda"))
    mInitialLamda = getValue<C_FLOAT64>("Initial Lambda");
  else
    mInitialLamda = 1;

  if (getParameter("Modulation"))
    mModulation = getValue< C_FLOAT64 >("Modulation");

  mIteration = 0;

  if (mProcessReport)
    mhIteration =
      mProcessReport.addItem("Current Iteration",
                             mIteration,
                             & mIterationLimit);

  mVariableSize = mProblemContext.master()->getOptItemList(true).size();

  mCurrent.resize(mVariableSize);
  mBest.resize(mVariableSize);
  mStep.resize(mVariableSize);
  mGradient.resize(mVariableSize);
  mHessian.resize(mVariableSize, mVariableSize);

  mBestValue = std::numeric_limits<C_FLOAT64>::infinity();

  mContinue = true;

  CFitProblem * pFitProblem = dynamic_cast< CFitProblem * >(mProblemContext.master());

  if (pFitProblem != NULL)
    // if (false)
    {
      mHaveResiduals = true;
      pFitProblem->setResidualsRequired(true);
      mResidualJacobianT.resize(mVariableSize, pFitProblem->getResiduals().size());
    }
  else
    mHaveResiduals = false;

  if (getParameter("Stop after # stalled iterations"))
    mStopAfterStalledIterations = getValue <unsigned C_INT32>("Stop after # stalled iterations");

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
          *mProblemContext.master()->getContainerVariables(true)[i] = (x * mod1);
          mGradient[i] = (evaluate() - y) / (x * mModulation);
        }

      else
        {
          *mProblemContext.master()->getContainerVariables(true)[i] = (mModulation);
          mGradient[i] = (evaluate() - y) / mModulation;
        }

//REVIEW:END
      *mProblemContext.master()->getContainerVariables(true)[i] = (x);
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
      // evaluate();

      CFitProblem* pFit = static_cast<CFitProblem*>(mProblemContext.master());
      bool bUseTimeSens = pFit->getUseTimeSens();

      const CVector< C_FLOAT64 > & Residuals = pFit->getResiduals();

      const CVector< C_FLOAT64 > CurrentResiduals = Residuals;

      size_t ResidualSize = Residuals.size();

      C_FLOAT64 * pJacobianT = mResidualJacobianT.array();

      const C_FLOAT64 * pCurrentResiduals;
      const C_FLOAT64 * pEnd = CurrentResiduals.array() + ResidualSize;
      const C_FLOAT64 * pResiduals;

      if (!bUseTimeSens)
        {

          C_FLOAT64 Delta;
          C_FLOAT64 x;

          for (i = 0; i < mVariableSize && mContinue; i++)
            {
              //REVIEW:START
              if ((x = mCurrent[i]) != 0.0)
                {
                  Delta = 1.0 / (x * mModulation);
                  *mProblemContext.master()->getContainerVariables(true)[i] = (x * mod1);
                }

              else
                {
                  Delta = 1.0 / mModulation;
                  *mProblemContext.master()->getContainerVariables(true)[i] = (mModulation);
                  //REVIEW:END
                }

              // evaluate another column of the Jacobian
              evaluate();
              pCurrentResiduals = CurrentResiduals.array();
              pResiduals = Residuals.array();

              for (; pCurrentResiduals != pEnd; pCurrentResiduals++, pResiduals++, pJacobianT++)
                *pJacobianT = (*pResiduals - *pCurrentResiduals) * Delta;

              *mProblemContext.master()->getContainerVariables(true)[i] = (x);
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
                 const_cast<C_FLOAT64*>(CurrentResiduals.array()), &m,
                 mResidualJacobianT.array(), &n, &Beta,
                 const_cast<C_FLOAT64*>(mGradient.array()), &m);
#endif //XXXX
        }

      C_FLOAT64 * pGradient = mGradient.array();

      if (bUseTimeSens)
        pJacobianT = pFit->getTimeSensJac().array();
      else
        pJacobianT = mResidualJacobianT.array();

      for (i = 0; i < mVariableSize; i++, pGradient++)
        {
          *pGradient = 0.0;
          pCurrentResiduals = CurrentResiduals.array();

          for (; pCurrentResiduals != pEnd; pCurrentResiduals++, pJacobianT++)
            if (bUseTimeSens)
              *pGradient -= *pJacobianT * *pCurrentResiduals;
            else
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

              if (pFit && pFit->getUseTimeSens())
                pJacobianT = pFit->getTimeSensJac()[i];
              else
                pJacobianT = mResidualJacobianT[i];

              pEnd = pJacobianT + ResidualSize;

              if (pFit && pFit->getUseTimeSens())
                pJacobian = pFit->getTimeSensJac()[j];
              else
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

          *mProblemContext.master()->getContainerVariables(true)[i] = mCurrent[i];
          gradient();

          for (j = 0; j <= i; j++)
            mHessian[i][j] = (mGradient[j] - mTemp[j]) * Delta;

          // restore the original parameter value
          mCurrent[i] = x;
          *mProblemContext.master()->getContainerVariables(true)[i] = (x);
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

C_FLOAT64 COptMethodLevenbergMarquardt::getBestValue() const
{
  return mBestValue;
}

C_FLOAT64 COptMethodLevenbergMarquardt::getCurrentValue() const
{
  return mEvaluationValue;
}

const CVector< C_FLOAT64 >* COptMethodLevenbergMarquardt::getBestParameters() const
{
  return &mBest;
}

const CVector< C_FLOAT64 > * COptMethodLevenbergMarquardt::getCurrentParameters() const
{
  return &mCurrent;
}
