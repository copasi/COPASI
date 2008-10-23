// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CNewtonMethod.cpp,v $
//   $Revision: 1.88.2.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/10/23 14:48:25 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <algorithm>
#include <cmath>

#include "copasi.h"

#include "CSteadyStateMethod.h"
#include "CSteadyStateProblem.h"
#include "CSteadyStateTask.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CState.h"
#include "model/CModel.h"
#include "model/CCompartment.h"
#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
//#include "trajectory/CTrajectoryMethod.h"
#include "utilities/CCopasiException.h"
#include "utilities/utility.h"
#include "utilities/CProcessReport.h"

#include "clapackwrap.h"        //use CLAPACK

CNewtonMethod::CNewtonMethod(const CCopasiContainer * pParent):
    CSteadyStateMethod(CCopasiMethod::Newton, pParent),
    mIpiv(NULL),
    mpTrajectory(NULL)
{
  initializeParameter();
}

CNewtonMethod::CNewtonMethod(const CNewtonMethod & src,
                             const CCopasiContainer * pParent):
    CSteadyStateMethod(src, pParent),
    mIpiv(NULL),
    mpTrajectory(NULL)
{
  initializeParameter();
}

CNewtonMethod::~CNewtonMethod()
{cleanup();}

void CNewtonMethod::initializeParameter()
{
  CCopasiParameter *pParm;

  assertParameter("Use Newton", CCopasiParameter::BOOL, true);
  assertParameter("Use Integration", CCopasiParameter::BOOL, true);
  assertParameter("Use Back Integration", CCopasiParameter::BOOL, true);
  assertParameter("Accept Negative Concentrations", CCopasiParameter::BOOL, false);
  assertParameter("Iteration Limit", CCopasiParameter::UINT, (unsigned C_INT32) 50);
  assertParameter("Maximum duration for forward integration", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1e9);
  assertParameter("Maximum duration for backward integration", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1e6);
  //assertParameter("Force additional Newton step", CCopasiParameter::BOOL, true);
  //assertParameter("Keep Protocol", CCopasiParameter::BOOL, true);

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("Newton.UseNewton")) != NULL)
    {
      setValue("Use Newton", *pParm->getValue().pBOOL);
      removeParameter("Newton.UseNewton");

      if ((pParm = getParameter("Newton.UseIntegration")) != NULL)
        {
          setValue("Use Integration", *pParm->getValue().pBOOL);
          removeParameter("Newton.UseIntegration");
        }

      if ((pParm = getParameter("Newton.UseBackIntegration")) != NULL)
        {
          setValue("Use Back Integration", *pParm->getValue().pBOOL);
          removeParameter("Newton.UseBackIntegration");
        }

      if ((pParm = getParameter("Newton.acceptNegativeConcentrations")) != NULL)
        {
          setValue("Accept Negative Concentrations", *pParm->getValue().pBOOL);
          removeParameter("Newton.acceptNegativeConcentrations");
        }

      if ((pParm = getParameter("Newton.IterationLimit")) != NULL)
        {
          setValue("Iteration Limit", *pParm->getValue().pUINT);
          removeParameter("Newton.IterationLimit");
        }

      removeParameter("Newton.LSODA.RelativeTolerance");
      removeParameter("Newton.LSODA.AbsoluteTolerance");
      removeParameter("Newton.LSODA.AdamsMaxOrder");
      removeParameter("Newton.LSODA.BDFMaxOrder");
      removeParameter("Newton.LSODA.MaxStepsInternal");
    }
}

bool CNewtonMethod::elevateChildren()
{
  CSteadyStateMethod::initializeParameter();
  initializeParameter();
  return true;
}

void CNewtonMethod::cleanup()
{
  if (mIpiv) delete [] mIpiv; mIpiv = NULL;

  pdelete(mpTrajectory);
}

void CNewtonMethod::load(CReadConfig & configBuffer,
                         CReadConfig::Mode C_UNUSED(mode))
{
  if (configBuffer.getVersion() < "4.0")
    {
      C_FLOAT64 Dbl;
      C_INT32 Int;
      bool Bool;

      configBuffer.getVariable("SSStrategy", "C_INT32", &Int, CReadConfig::LOOP);
      switch (Int)
        {
        case 0:
          setValue("Use Newton", true);
          setValue("Use Integration", true);
          setValue("Use Back Integration", false);
          break;

        case 1:
          setValue("Use Newton", false);
          setValue("Use Integration", true);
          setValue("Use Back Integration", false);
          break;

        case 2:
          setValue("Use Newton", true);
          setValue("Use Integration", false);
          setValue("Use Back Integration", false);
          break;

        case 3:
          setValue("Use Newton", false);
          setValue("Use Integration", false);
          setValue("Use Back Integration", true);
          break;

        default:
          fatalError();
        }

      configBuffer.getVariable("SSBackIntegration", "bool", &Bool);
      setValue("Use Back Integration", Bool);

      configBuffer.getVariable("NewtonLimit", "C_INT32", &Int,
                               CReadConfig::SEARCH);
      setValue("Iteration Limit", Int);

      configBuffer.getVariable("SSResoltion", "C_FLOAT64", &Dbl); //typo is necessary!!
      //setValue("Steady State Resolution", Dbl);
      //setValue("Derivation Resolution", Dbl);
      //setValue("Stability Resolution", Dbl);
      setValue("Resolution", Dbl);
    }
}

//**********************************************************************************

CNewtonMethod::NewtonResultCode CNewtonMethod::doIntegration(bool forward)
{
  C_FLOAT64 iterationFactor = forward ? 10.0 : 2.0;
  C_FLOAT64 maxDuration = forward ? mMaxDurationForward : -mMaxDurationBackward;
  //minimum duration is either hardcoded or equal to maximum duration, whichever is smaller.
  C_FLOAT64 minDuration = forward ? (mMaxDurationForward < 1e-1 ? mMaxDurationForward : 1e-1)
                              : -(mMaxDurationBackward < 1e-2 ? mMaxDurationBackward : 1e-2);

  //progress bar
  unsigned C_INT32 hProcess;
  unsigned C_INT32 Step = 0;
  unsigned C_INT32 MaxSteps;
  MaxSteps = (unsigned C_INT32) ceil(log(maxDuration / minDuration) / log(iterationFactor));

  std::string tmpstring = forward ? "forward integrating..." : "backward integrating...";
  if (mpProgressHandler)
    hProcess = mpProgressHandler->addItem(tmpstring,
                                          CCopasiParameter::UINT,
                                          & Step,
                                          & MaxSteps);

  //setup trajectory
  CTrajectoryProblem * pTrajectoryProblem = NULL;

  if (mpTrajectory)
    {
      pTrajectoryProblem =
        dynamic_cast<CTrajectoryProblem *>(mpTrajectory->getProblem());
      assert(pTrajectoryProblem);
      pTrajectoryProblem->setStepNumber(1);
    }

  bool stepLimitReached;
  C_FLOAT64 duration;

  for (duration = minDuration; fabs(duration) <= fabs(maxDuration); duration *= iterationFactor, Step++)
    {
      if (mpProgressHandler && !mpProgressHandler->progress(hProcess)) break;

      pTrajectoryProblem->setDuration(duration);
      try
        {
          stepLimitReached = !mpTrajectory->process(true); //single step
        }
      catch (CCopasiException Exception)
        {
          //std::cout << std::endl << "exception in trajectory task" << std::endl;
          *mpSteadyState = *mpTrajectory->getState();
          if (mKeepProtocol)
            mMethodLog << "  Integration with duration " << duration << " failed (Exception).\n\n";
          break;
        }

      // mpParentTask->output(COutputInterface::DURING);

      *mpSteadyState = *mpTrajectory->getState();

      if (containsNaN())
        {
          if (mKeepProtocol)
            mMethodLog << "  Integration with duration " << duration << " failed (NaN).\n\n";
          break;
        }

      if (!(mAcceptNegative || allPositive()))
        {
          if (mKeepProtocol)
            mMethodLog << "  Integration with duration " << duration
            << " resulted in negative concentrations.\n\n";
          break;
        }

      calculateDerivativesX();
      C_FLOAT64 value = targetFunction(mdxdt);
      if (isSteadyState(value))
        {
          if (mpProgressHandler) mpProgressHandler->finish(hProcess);
          if (mKeepProtocol)
            mMethodLog << "  Integration with duration " << duration
            << ". Criterium matched by " << value << ".\n\n";
          return CNewtonMethod::found;
        }
      else
        {
          if (mKeepProtocol)
            mMethodLog << "  Integration with duration " << duration
            << ". Criterium not matched by " << value << ".\n\n";
        }

      if (mUseNewton)
        {
          if (mKeepProtocol) mMethodLog << "  Try Newton's method from this starting point. \n";
          NewtonResultCode returnCode = processNewton();
          if (mKeepProtocol) mMethodLog << "\n";
          // mpParentTask->separate(COutputInterface::DURING);

          if (returnCode == CNewtonMethod::found)
            {
              if (mpProgressHandler) mpProgressHandler->finish(hProcess);
              return CNewtonMethod::found;
            }
        }

      if (stepLimitReached)
        {
          if (mKeepProtocol)
            mMethodLog << "  Integration with duration " << duration
            << " reached internal step limit.\n";
          break;
        }
    }
  if (mpProgressHandler) mpProgressHandler->finish(hProcess);
  return CNewtonMethod::notFound;
}

//**********************************************************************************

CSteadyStateMethod::ReturnCode CNewtonMethod::processInternal()
{
  //clear log
  mMethodLog.str("");

  if (mpProgressHandler)
    mpProgressHandler->setName("performing steady state calculation...");

  mpX = mpSteadyState->beginIndependent();

  NewtonResultCode returnCode;

  // Newton
  if (mUseNewton)
    {
      if (mKeepProtocol) mMethodLog << "Try Newton's method. \n";

      returnCode = processNewton();

      if (returnCode == CNewtonMethod::found)
        return returnProcess(true);
    }

  // forward integration
  if (mUseIntegration)
    {
      if (mKeepProtocol) mMethodLog << "\nTry forward integration. \n";
      returnCode = doIntegration(true); //true means forward

      if (returnCode == CNewtonMethod::found)
        return returnProcess(true);
    }

  // backward integration
  if (mUseBackIntegration)
    {
      if (mKeepProtocol) mMethodLog << "\nTry backward integration. \n";
      returnCode = doIntegration(false); //false means backwards

      if (returnCode == CNewtonMethod::found)
        return returnProcess(true);
    }

  return returnProcess(false);
}

//**************************************************************

CNewtonMethod::NewtonResultCode CNewtonMethod::doNewtonStep(C_FLOAT64 & currentValue)
{
  C_INT info = 0;
  char T = 'T'; /* difference between fortran's and c's matrix storage */
  C_INT one = 1;

  memcpy(mXold.array(), mpX, mDimension * sizeof(C_FLOAT64));

  // DebugFile << "Iteration: " << k << std::endl;

  calculateJacobianX(currentValue);

  // DebugFile << "Jacobian: " << *mpJacobianX << std::endl;

  /* We use dgetrf_ and dgetrs_ to solve
      mJacobian * b = mH for b (the result is in mdxdt) */

  /* int dgetrf_(integer *m,
    *             integer *n,
    *             doublereal *a,
    *             integer * lda,
    *             integer *ipiv,
    *             integer *info)
    *
    *  Purpose
    *  =======
    *
    *  DGETRF computes an LU factorization of a general M-by-N matrix A
    *  using partial pivoting with row interchanges.
    *
    *  The factorization has the form
    *     A = P * L * U
    *  where P is a permutation matrix, L is lower triangular with unit
    *  diagonal elements (lower trapezoidal if m > n), and U is upper
    *  triangular (upper trapezoidal if m < n).
    *
    *  This is the right-looking Level 3 BLAS version of the algorithm.
    *
    *  Arguments
    *  =========
    *
    *  m       (input) INTEGER
    *          The number of rows of the matrix A.  m >= 0.
    *
    *  n       (input) INTEGER
    *          The number of columns of the matrix A.  n >= 0.
    *
    *  a       (input/output) DOUBLE PRECISION array, dimension (lda,n)
    *          On entry, the m by n matrix to be factored.
    *          On exit, the factors L and U from the factorization
    *          A = P*L*U; the unit diagonal elements of L are not stored.
    *
    *  lda     (input) INTEGER
    *          The leading dimension of the array A.  lda >= max(1,m).
    *
    *  ipiv    (output) INTEGER array, dimension (min(m,n))
    *          The pivot indices; for 1 <= i <= min(m,n), row i of the
    *          matrix was interchanged with row ipiv(i).
    *
    *  info    (output) INTEGER
    *          = 0: successful exit
    *          < 0: if info = -k, the k-th argument had an illegal value
    *          > 0: if info = k, U(k,k) is exactly zero. The factorization
    *               has been completed, but the factor U is exactly
    *               singular, and division by zero will occur if it is used
    *               to solve a system of equations.
    */
  dgetrf_(&mDimension, &mDimension, mpJacobianX->array(),
          &mDimension, mIpiv, &info);

  //std::cout << "Jacobian: " << mJacobianX << std::endl;

  if (info)
    {
      if (info > 0)
        {
          //if (mpProgressHandler) mpProgressHandler->finish(hProcess);
          if (mKeepProtocol)
            mMethodLog << "    Newton step failed. Jacobian could not be inverted.\n";
          return CNewtonMethod::singularJacobian;
        }
      fatalError();
    }

  /* int dgetrs_(char *trans,
    *             integer *n,
    *             integer *nrhs,
    *             doublereal *a,
    *             integer *lda,
    *             integer *ipiv,
    *             doublereal *b,
    *             integer * ldb,
    *             integer *info)
    *  Arguments
    *  =========
    *
    *  trans   (input) CHARACTER*1
    *          Specifies the form of the system of equations:
    *          = 'N':  a * x = b  (No transpose)
    *          = 'T':  a'* x = b  (Transpose)
    *          = 'C':  a'* x = b  (Conjugate transpose = Transpose)
    *
    *  n       (input) INTEGER
    *          The order of the matrix a.  n >= 0.
    *
    *  nrhs    (input) INTEGER
    *          The number of right hand sides, i.e., the number of columns
    *          of the matrix b.  nrhs >= 0.
    *
    *  a       (input) DOUBLE PRECISION array, dimension (lda,n)
    *          The factors L and U from the factorization a = P*L*U
    *          as computed by DGETRF.
    *
    *  lda     (input) INTEGER
    *          The leading dimension of the array a.  lda >= max(1,n).
    *
    *  ipiv    (input) INTEGER array, dimension (n)
    *          The pivot indices from DGETRF; for 1<=i<=n, row i of the
    *          matrix was interchanged with row ipiv(i).
    *
    *  b       (input/output) DOUBLE PRECISION array, dimension (ldb,nrhs)
    *          On entry, the right hand side matrix b.
    *          On exit, the solution matrix x.
    *
    *  ldb     (input) INTEGER
    *          The leading dimension of the array b.  ldb >= max(1,n).
    *
    *  info    (output) INTEGER
    *          = 0:  successful exit
    *          < 0:  if info = -i, the i-th argument had an illegal value
    */
  //std::cout << "b: " << mdxdt << std::endl;
  dgetrs_(&T, &mDimension, &one, mpJacobianX->array(),
          &mDimension, mIpiv, mdxdt.array(), &mDimension, &info);
  //std::cout << "a: " << mdxdt << std::endl << std::endl;

  if (info)
    fatalError();

  C_FLOAT64 newValue = currentValue * 1.001;

  // copy values of increment to h
  mH = mdxdt;

  //repeat till the new max rate is smaller than the old.
  //max 32 times
  unsigned C_INT32 i;
  for (i = 0; (i < 32) && !((newValue < currentValue)); i++)
    {
      C_FLOAT64 * pXit = mpX;
      C_FLOAT64 * pXoldIt = mXold.array();
      C_FLOAT64 * pHit = mH.array();
      C_FLOAT64 * pEnd = pHit + mDimension;

      for (; pHit != pEnd; ++pHit, ++pXit, ++pXoldIt)
        {
          *pXit = *pXoldIt - *pHit;
          (*pHit) *= 0.5;
        }

      calculateDerivativesX();
      newValue = targetFunction(mdxdt);

      // mpParentTask->output(COutputInterface::DURING);
      //std::cout << "k: " << k << " i: " << i << " target: " << newMaxRate << std::endl;
    }

  //      std::cout << k << "th Newton Step. i = " << i << " maxRate = " << newMaxRate << std::endl;

  if (i == 32)
    {
      //std::cout << "a newton step did not improve the target function" << std::endl;

      //discard the step
      memcpy(mpX, mXold.array(), mDimension * sizeof(C_FLOAT64));

      calculateDerivativesX();
      currentValue = targetFunction(mdxdt);

      if (mKeepProtocol) mMethodLog << "    Newton step failed. Damping limit exceeded.\n";
      return CNewtonMethod::dampingLimitExceeded;

      //       if (isSteadyState(oldMaxRate) && (mAcceptNegative || allPositive()))
      //         ReturnCode = CNewtonMethod::found;
      //       else if (oldMaxRate < *mpSSResolution)
      //         ReturnCode = CNewtonMethod::notFound;
      //       else
      //         ReturnCode = CNewtonMethod::dampingLimitExceeded;

      //if (mpProgressHandler) mpProgressHandler->finish(hProcess);
    }

  if (!(mAcceptNegative || allPositive()))
    {
      if (mKeepProtocol)
        mMethodLog << "    Newton step failed. Negative volume or concentration found.\n\n";

      return CNewtonMethod::negativeValueFound;
    }

  currentValue = newValue; //return the new target value

  if (mKeepProtocol)
    {
      if (i <= 1)
        mMethodLog << "    Regular Newton step.      New value: " << currentValue << "\n";
      else
        mMethodLog << "    Newton step with damping. New value: " << currentValue
        << " (" << i - 1 << " damping iteration(s))\n";
    }
  return CNewtonMethod::stepSuccesful;
}

//************************************************************

CNewtonMethod::NewtonResultCode CNewtonMethod::processNewton()
{
  NewtonResultCode result = CNewtonMethod::notFound;
  C_INT32 k;

  k = 0;
  //start progress bar
  unsigned C_INT32 hProcess;
  if (mpProgressHandler)
    hProcess = mpProgressHandler->addItem("Newton method...",
                                          CCopasiParameter::UINT,
                                          & k,
                                          & mIterationLimit);

  C_FLOAT64 targetValue;

  calculateDerivativesX();
  targetValue = targetFunction(mdxdt);

  {
    if (mKeepProtocol) mMethodLog << "   Starting Newton Iterations...\n";

    for (k = 0; k < mIterationLimit && !isSteadyState(targetValue); k++)
      {
        if (mpProgressHandler && !mpProgressHandler->progress(hProcess)) break;

        result = doNewtonStep(targetValue);

        if (singularJacobian == result) break;
        if (dampingLimitExceeded == result) break;
        if (negativeValueFound == result) break;
      }
  }

  //check if ss was found. If not make sure the correct return value is set
  if (isSteadyState(targetValue))
    result = CNewtonMethod::found;
  else if (CNewtonMethod::stepSuccesful == result)
    result = CNewtonMethod::iterationLimitExceeded;

  //log
  if (mKeepProtocol)
    {
      if (CNewtonMethod::found == result)
        mMethodLog << "   Success: Target criterium matched by " << targetValue << ".\n";
      else if (CNewtonMethod::dampingLimitExceeded == result)
        mMethodLog << "   Failed: Target criterium not matched after reaching iteration limit. " << targetValue << "\n";
    }

  //do an additional Newton step to refine the result
  if ((CNewtonMethod::found == result) && mForceNewton && targetValue > 0.0)
    {
      bool tmp = true;
      ++k; if (mpProgressHandler && !mpProgressHandler->progress(hProcess)) tmp = false;

      if (tmp)
        {
          if (mKeepProtocol) mMethodLog << "   Do additional step to refine result...\n";

          result = doNewtonStep(targetValue);

          if (CNewtonMethod::stepSuccesful == result)
            result = CNewtonMethod::found;

          if (CNewtonMethod::singularJacobian == result)
            {
              if (mKeepProtocol) mMethodLog << "   Additional step failed. Old values restored.\n";
              result = CNewtonMethod::found;
            }

          if (CNewtonMethod::dampingLimitExceeded == result)
            {
              if (mKeepProtocol) mMethodLog << "   Additional step failed. Old values restored.\n";
              result = CNewtonMethod::found;
            }

          if (CNewtonMethod::negativeValueFound == result)
            {
              if (mKeepProtocol) mMethodLog << "   Additional step failed. Old values restored.\n";
              result = CNewtonMethod::found;
            }
        }
    }

  //end progress bar
  if (mpProgressHandler) mpProgressHandler->finish(hProcess);
  return result;
}

void CNewtonMethod::calculateDerivativesX()
{
  mpModel->setState(*mpSteadyState);
  mpModel->updateSimulatedValues(true);
  mpModel->calculateDerivativesX(mdxdt.array());
}

bool CNewtonMethod::containsNaN() const
  {
    //checks for NaNs
    const C_FLOAT64 * pIt = mpSteadyState->beginIndependent();
    const C_FLOAT64 * pEnd = mpSteadyState->endIndependent();

    for (; pIt != pEnd; ++pIt)
      if (isnan(*pIt))
        return true;

    return false;
  }

bool CNewtonMethod::isSteadyState(C_FLOAT64 value)
{
  if (value > *mpSSResolution)
    return false;

  if (containsNaN())
    return false;

  return true;
}

C_FLOAT64 CNewtonMethod::targetFunction(const CVector< C_FLOAT64 > & particlefluxes) const
  {
    C_FLOAT64 tmp, store = 0;

    // We look at all ODE determined entity and dependent species rates.
    const C_FLOAT64 * pIt = particlefluxes.array();
    const C_FLOAT64 * pEnd = pIt + particlefluxes.size();
    const C_FLOAT64 * pAtol = mAtol.array();
    CModelEntity *const* ppEntity = mpModel->getStateTemplate().beginIndependent();

    for (; pIt != pEnd; ++pIt, ++pAtol, ++ppEntity)
      {
        tmp = fabs(*pIt) / std::max(*pAtol, fabs((*ppEntity)->getValue()));

        if (tmp > store)
          store = tmp;

        if (isnan(tmp))
          return DBL_MAX;
      }

    return store;
  }

//virtual
bool CNewtonMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CSteadyStateMethod::isValidProblem(pProblem)) return false;

  //const CSteadyStateProblem * pP = dynamic_cast<const CSteadyStateProblem *>(pProblem);

  if (!((* getValue("Use Newton").pBOOL)
        || (* getValue("Use Integration").pBOOL)
        || (* getValue("Use Back Integration").pBOOL)))
    {
      //would do nothing
      CCopasiMessage(CCopasiMessage::ERRoR, "At least one of the features \n   - UseNewton\n   - UseIntegration\n   - UseBackIntegration\nmust be activated.");
      return false;
    }

  if (*getValue("Maximum duration for forward integration").pUDOUBLE <= 0)
    {
      CCopasiMessage(CCopasiMessage::ERRoR, "Maximum duration for forward integration needs to be positive.");
      return false;
    }
  if (*getValue("Maximum duration for backward integration").pUDOUBLE <= 0)
    {
      CCopasiMessage(CCopasiMessage::ERRoR, "Maximum duration for backward integration needs to be positive.");
      return false;
    }

  return true;
}

bool CNewtonMethod::initialize(const CSteadyStateProblem * pProblem)
{
  if (!CSteadyStateMethod::initialize(pProblem)) return false;

  CTrajectoryProblem * pTrajectoryProblem = NULL;
  CTrajectoryMethod * pTrajectoryMethod = NULL;

  cleanup();

  /* Configure Newton */
  mUseNewton = mUseIntegration = mUseBackIntegration = mAcceptNegative
                                 = mForceNewton = mKeepProtocol = false;

  if (* getValue("Use Newton").pBOOL)
    mUseNewton = true;
  if (* getValue("Use Integration").pBOOL)
    mUseIntegration = true;
  if (* getValue("Use Back Integration").pBOOL)
    mUseBackIntegration = true;
  if (* getValue("Accept Negative Concentrations").pBOOL)
    mAcceptNegative = true;
  //if (* getValue("Force additional Newton step").pBOOL)
  mForceNewton = true;
  //if (* getValue("Keep Protocol").pBOOL)
  mKeepProtocol = true;

  mIterationLimit = * getValue("Iteration Limit").pUINT;

  mMaxDurationForward = *getValue("Maximum duration for forward integration").pUDOUBLE;
  mMaxDurationBackward = *getValue("Maximum duration for backward integration").pUDOUBLE;

  //mFactor = * getValue("Derivation Factor").pUDOUBLE;
  //mSSResolution = * getValue("Steady State Resolution").pUDOUBLE;
  //mScaledResolution =
  //  mSSResolution; // * initialState.getModel()->getQuantity2NumberFactor();
  // :TODO: discuss scaling

  // convert CState to CStateX
  //mInitialStateX = mpProblem->getInitialState();
  //*mpSteadyStateX = mInitialStateX; //not strictly necessary

  mDimension = mpProblem->getModel()->getStateTemplate().getNumIndependent();

  mAtol = mpModel->initializeAtolVector(1.e-6, true);
  mH.resize(mDimension);
  mXold.resize(mDimension);
  mdxdt.resize(mDimension);
  mIpiv = new C_INT [mDimension];

  if (mUseIntegration || mUseBackIntegration)
    {
      // create an appropriate trajectory task
      CTrajectoryTask * pSrc =
        dynamic_cast< CTrajectoryTask * >((*CCopasiDataModel::Global->getTaskList())["Time-Course"]);

      if (pSrc)
        mpTrajectory = new CTrajectoryTask(*pSrc, this);
      else
        mpTrajectory = new CTrajectoryTask(this);

      pTrajectoryProblem =
        dynamic_cast<CTrajectoryProblem *>(mpTrajectory->getProblem());
      assert(pTrajectoryProblem);

      if (mpTrajectory->getMethod()->getSubType() != CCopasiMethod::deterministic)
        mpTrajectory->setMethodType(CCopasiMethod::deterministic);

      pTrajectoryMethod =
        dynamic_cast<CTrajectoryMethod *>(mpTrajectory->getMethod());
      assert(pTrajectoryMethod);

      pTrajectoryProblem->setModel(mpProblem->getModel());
      pTrajectoryProblem->setStepNumber(1);

      mpTrajectory->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);
    }

  return true;
}
