/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CNewtonMethod.cpp,v $
   $Revision: 1.69 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/05/04 21:00:36 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
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
#include "trajectory/CTrajectoryMethod.h"
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
  assertParameter("Derivation Factor", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-003);
  assertParameter("Resolution", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-009);

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

      if ((pParm = getParameter("Newton.DerivationFactor")) != NULL)
        {
          setValue("Derivation Factor", *pParm->getValue().pUDOUBLE);
          removeParameter("Newton.DerivationFactor");
        }

      if ((pParm = getParameter("Newton.Resolution")) != NULL)
        {
          setValue("Resolution", *pParm->getValue().pUDOUBLE);
          removeParameter("Newton.Resolution");
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
      setValue("Resolution", Dbl);
    }
}

CSteadyStateMethod::ReturnCode
CNewtonMethod::processInternal()
{
  if (mpProgressHandler)
    mpProgressHandler->setName("performing steady state calculation...");

  mpSteadyState->setUpdateDependentRequired(true);
  mX = mpSteadyState->beginIndependent();

  CNewtonMethod::NewtonReturnCode returnCode;
  if (mUseNewton)
    {
      returnCode = processNewton();
      // mpParentTask->separate(COutputInterface::DURING);

      if (returnCode == CNewtonMethod::found)
        return returnProcess(true, mFactor, mResolution);
    }

  bool stepLimitReached = false;
  C_FLOAT64 Duration;

  CTrajectoryProblem * pTrajectoryProblem;

  if (mpTrajectory)
    {
      pTrajectoryProblem =
        dynamic_cast<CTrajectoryProblem *>(mpTrajectory->getProblem());
      assert(pTrajectoryProblem);
      pTrajectoryProblem->setStepNumber(1);
    }

  if (mUseIntegration)
    {
      //std::cout << "Try integrating ..." << std::endl;

      unsigned C_INT32 hProcess;
      unsigned C_INT32 Step = 0;
      unsigned C_INT32 MaxSteps = (unsigned C_INT32) ceil(log(1.0e12) / log(2.0));

      if (mpProgressHandler)
        hProcess = mpProgressHandler->addItem("forward integrating...",
                                              CCopasiParameter::UINT,
                                              & Step,
                                              & MaxSteps);

      for (Duration = 0.01; Duration < 1.0e10; Duration *= 2, Step++)
        {
          if (mpProgressHandler && !mpProgressHandler->progress(hProcess)) break;

          pTrajectoryProblem->setDuration(Duration);
          try
            {
              stepLimitReached = !mpTrajectory->process(true); //single step
            }
          catch (CCopasiException Exception)
            {
              //std::cout << std::endl << "exception in trajectory task" << std::endl;
              *mpSteadyState = *mpTrajectory->getState();
              break;
            }

          // mpParentTask->output(COutputInterface::DURING);

          *mpSteadyState = *mpTrajectory->getState();

          if (containsNaN())
            break;

          if (!(mAcceptNegative || allPositive()))
            break;

          calculateDerivativesX();

          if (isSteadyState(targetFunction(mdxdt)))
            {
              return returnProcess(true, mFactor, mResolution);
            }

          if (mUseNewton)
            {
              returnCode = processNewton();
              // mpParentTask->separate(COutputInterface::DURING);

              if (returnCode == CNewtonMethod::found)
              {return returnProcess(true, mFactor, mResolution);}
            }

          if (stepLimitReached)
            {
              //std::cout << "Step limit reached at Endtime " << Duration << std::endl;
              break;
            }
        }
      if (mpProgressHandler) mpProgressHandler->finish(hProcess);
    }

  if (mUseBackIntegration)
    {
      unsigned C_INT32 hProcess;
      unsigned C_INT32 Step = 0;
      unsigned C_INT32 MaxSteps = (unsigned C_INT32) ceil(log(1.0e12) / log(2.0));

      if (mpProgressHandler)
        hProcess = mpProgressHandler->addItem("backward integrating...",
                                              CCopasiParameter::UINT,
                                              & Step,
                                              & MaxSteps);

      for (Duration = -0.01; Duration > -1.0e10; Duration *= 2, Step++)
        {
          if (mpProgressHandler && !mpProgressHandler->progress(hProcess)) break;

          pTrajectoryProblem->setDuration(Duration);

          try
            {
              stepLimitReached = !mpTrajectory->process(true); //single step
            }
          catch (CCopasiException Exception)
            {
              //std::cout << std::endl << "exception in trajectory task" << std::endl;
              *mpSteadyState = *mpTrajectory->getState();
              break;
            }

          // mpParentTask->output(COutputInterface::DURING);

          *mpSteadyState = *mpTrajectory->getState();

          if (containsNaN())
            break;

          if (!(mAcceptNegative || allPositive()))
            break;

          calculateDerivativesX();
          if (isSteadyState(targetFunction(mdxdt)))
            {
              return returnProcess(true, mFactor, mResolution);
            }

          //try Newton
          //mInitialStateX = mStateX;
          if (mUseNewton)
            {
              returnCode = processNewton();
              // mpParentTask->separate(COutputInterface::DURING);

              if (returnCode == CNewtonMethod::found)
              {return returnProcess(true, mFactor, mResolution);}
            }
          if (stepLimitReached)
            {
              //std::cout << "Step limit reached at Endtime " << Duration << std::endl;
              break;
            }
        }
      if (mpProgressHandler) mpProgressHandler->finish(hProcess);
    }

  if (mpProgressHandler) mpProgressHandler->finish();

  return returnProcess(false, mFactor, mResolution);
}

CNewtonMethod::NewtonReturnCode CNewtonMethod::processNewton ()
{
  CNewtonMethod::NewtonReturnCode ReturnCode = CNewtonMethod::notFound;
  C_INT32 i, j, k;
  C_FLOAT64 oldMaxRate, newMaxRate;

  calculateDerivativesX();
  oldMaxRate = targetFunction(mdxdt);
  if (isSteadyState(oldMaxRate))
    return returnNewton(CNewtonMethod::found);

  //std::cout << "Before: " << oldMaxRate << std::endl;

  // Start the iterations
  C_INT info = 0;
  char T = 'T'; /* difference between fortran's and c's matrix storrage */
  C_INT one = 1;

  //std::cout << "processNewton called" << std::endl;

  unsigned C_INT32 hProcess;
  k = 0;

  if (mpProgressHandler)
    hProcess = mpProgressHandler->addItem("newton method...",
                                          CCopasiParameter::UINT,
                                          & k,
                                          & mIterationLimit);

  for (k = 0; k < mIterationLimit && oldMaxRate > mScaledResolution; k++)
    {
      if (mpProgressHandler && !mpProgressHandler->progress(hProcess)) break;

      memcpy(mXold.array(), mX, mDimension * sizeof(C_FLOAT64));

      // DebugFile << "Iteration: " << k << std::endl;

      calculateJacobianX(oldMaxRate);

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
              if (mpProgressHandler) mpProgressHandler->finish(hProcess);
              return returnNewton(CNewtonMethod::singularJacobian);
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

      newMaxRate = oldMaxRate * 1.001;

      // copy values of increment to h
      mH = mdxdt;

      //repeat till the new max rate is smaller than the old and all concentrations are positive.
      //max 32 times
      for (i = 0; (i < 32) && !((newMaxRate < oldMaxRate) && (mAcceptNegative || allPositive())); i++)
        {
          C_FLOAT64 * pX = mX;
          C_FLOAT64 * pXold = mXold.array();
          C_FLOAT64 * pH = mH.array();
          C_FLOAT64 * pEnd = pH + mDimension;

          for (; pH != pEnd; ++pH, ++pX, ++pXold)
            {
              *pX = *pXold - *pH;
              (*pH) *= 0.5;
            }

          calculateDerivativesX();
          newMaxRate = targetFunction(mdxdt);

          // mpParentTask->output(COutputInterface::DURING);
          //std::cout << "k: " << k << " i: " << i << " target: " << newMaxRate << std::endl;
        }

      //      std::cout << k << "th Newton Step. i = " << i << " maxRate = " << newMaxRate << std::endl;

      if (i == 32)
        {
          //std::cout << "a newton step did not improve the target function" << std::endl;

          //discard the step
          memcpy(mX, mXold.array(), mDimension * sizeof(C_FLOAT64));

          calculateDerivativesX();
          oldMaxRate = targetFunction(mdxdt);

          if (isSteadyState(oldMaxRate) && (mAcceptNegative || allPositive()))
            ReturnCode = CNewtonMethod::found;
          else if (oldMaxRate < mScaledResolution)
            ReturnCode = CNewtonMethod::notFound;
          else
            ReturnCode = CNewtonMethod::dampingLimitExceeded;

          if (mpProgressHandler) mpProgressHandler->finish(hProcess);
          return returnNewton(ReturnCode);
        }

      //      for (i = 0; i < mDimension; i++)
      //        mSs_x[i] = mSs_xnew[i];

      oldMaxRate = newMaxRate;
    }

  if (isSteadyState(oldMaxRate))
    ReturnCode = CNewtonMethod::found;
  else if (oldMaxRate < mScaledResolution)
    ReturnCode = CNewtonMethod::notFound;
  else
    ReturnCode = CNewtonMethod::iterationLimitExceeded;

  if (mpProgressHandler) mpProgressHandler->finish(hProcess);
  return returnNewton(ReturnCode);
}

void CNewtonMethod::calculateDerivativesX()
{
  mpModel->setState(*mpSteadyState);
  mpModel->applyAssignments();
  mpModel->calculateDerivativesX(mdxdt.array());

  // DebugFile << "CNewtonMethod::calculateDerivativesX" << std::endl;
  // DebugFile << mdxdt << std::endl;
}

void CNewtonMethod::calculateJacobianX(const C_FLOAT64 & oldMaxRate)
{
  mpModel->setState(*mpSteadyState);
  mpModel->applyAssignments();
  mpModel->calculateElasticityMatrix(std::min(mFactor, oldMaxRate),
                                     mResolution);
  mpModel->calculateJacobianX(*mpJacobianX);
}

bool CNewtonMethod::allPositive()
{
  C_FLOAT64 ParticleResolution =
    - mResolution * mpModel->getQuantity2NumberFactor();

  const C_FLOAT64 * pIt = mpSteadyState->beginIndependent();
  const C_FLOAT64 * pEnd = mpSteadyState->endIndependent();

  CCopasiVector< CMetab >::const_iterator itMetab
  = mpModel->getMetabolitesX().begin();

  for (; pIt != pEnd; ++pIt, itMetab++)
    if (*pIt < ParticleResolution * (*itMetab)->getCompartment()->getVolume())
      return false;

  // This is necessarry since the dependent numbers are ignored during calculation.
  if (mpSteadyState->isUpdateDependentRequired())
    mpModel->setState(*mpSteadyState);

  pIt = mpSteadyState->beginDependent();
  pEnd = mpSteadyState->endDependent();

  for (; pIt != pEnd; ++pIt, itMetab++)
    if (*pIt < ParticleResolution * (*itMetab)->getCompartment()->getVolume())
      return false;

  return true;
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

CNewtonMethod::NewtonReturnCode
CNewtonMethod::returnNewton(const CNewtonMethod::NewtonReturnCode & returnCode)
{
  mpProblem->getModel()->setState(*mpSteadyState);
  mpProblem->getModel()->refreshConcentrations();

  // This is necessarry since the dependent numbers are ignored during calculation.

  return returnCode;
}

bool CNewtonMethod::isSteadyState(C_FLOAT64 value)
{
  if (value > mScaledResolution)
    return false;

  if (containsNaN())
    return false;

  return true;
}

C_FLOAT64 CNewtonMethod::targetFunction(const CVector< C_FLOAT64 > & particlefluxes) const
  {
    C_FLOAT64 tmp, store = 0;

    const C_FLOAT64 * pIt = particlefluxes.array();
    const C_FLOAT64 * pEnd = pIt + particlefluxes.size();

    // :TODO: This correct as long as we do not have userdefined assignments and ODEs
    CCopasiVector< CMetab >::const_iterator itMetab
    = mpModel->getMetabolitesX().begin();

    for (; pIt != pEnd; ++pIt, itMetab++)
      {
        tmp = fabs(*pIt / (*itMetab)->getCompartment()->getVolume());
        if (tmp > store)
          store = tmp;
      }

    return store * mpModel->getNumber2QuantityFactor();
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
      CCopasiMessage(CCopasiMessage::EXCEPTION, "At least one of the features \n   - UseNewton\n   - UseIntegration\n   - UseBackIntegration\nmust be activated.");
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
  mUseNewton = mUseIntegration = mUseBackIntegration = mAcceptNegative = false;

  if (* getValue("Use Newton").pBOOL)
    mUseNewton = true;
  if (* getValue("Use Integration").pBOOL)
    mUseIntegration = true;
  if (* getValue("Use Back Integration").pBOOL)
    mUseBackIntegration = true;
  if (* getValue("Accept Negative Concentrations").pBOOL)
    mAcceptNegative = true;

  mIterationLimit = * getValue("Iteration Limit").pUINT;
  mFactor = * getValue("Derivation Factor").pUDOUBLE;
  mResolution = * getValue("Resolution").pUDOUBLE;
  mScaledResolution =
    mResolution; // * initialState.getModel()->getQuantity2NumberFactor();
  //TODO discuss scaling

  // convert CState to CStateX
  //mInitialStateX = mpProblem->getInitialState();
  //*mpSteadyStateX = mInitialStateX; //not strictly necessary

  mDimension = mpProblem->getModel()->getMetabolitesInd().size();

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

      mpTrajectory->initialize(CCopasiTask::NO_OUTPUT, NULL);
    }

  return true;
}
