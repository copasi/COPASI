/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CNewtonMethod.cpp,v $
   $Revision: 1.34 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/10/06 09:59:33 $
   End CVS Header */

#include <algorithm>

#define  COPASI_TRACE_CONSTRUCTION
#include "copasi.h"

#include "CSteadyStateMethod.h"
#include "CSteadyStateProblem.h"

#include "model/CState.h"
#include "model/CModel.h"
#include "model/CCompartment.h"

#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "trajectory/CTrajectoryMethod.h"
#include "utilities/CCopasiException.h"

#include "clapackwrap.h"        //use CLAPACK
#include "utilities/utility.h"

CNewtonMethod::CNewtonMethod(const CCopasiContainer * pParent):
    CSteadyStateMethod(CCopasiMethod::Newton, pParent),
    mIpiv(NULL)
{
  addParameter("Newton.UseNewton",
               CCopasiParameter::BOOL, true);
  addParameter("Newton.UseIntegration",
               CCopasiParameter::BOOL, true);
  addParameter("Newton.UseBackIntegration",
               CCopasiParameter::BOOL, true);
  addParameter("Newton.IterationLimit",
               CCopasiParameter::UINT, (unsigned C_INT32) 50);
  addParameter("Newton.DerivationFactor",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-003);
  addParameter("Newton.Resolution",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-009);
  addParameter("Newton.LSODA.RelativeTolerance",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-012);
  addParameter("Newton.LSODA.AbsoluteTolerance",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-006);
  addParameter("Newton.LSODA.AdamsMaxOrder",
               CCopasiParameter::UINT, (unsigned C_INT32) 12);
  addParameter("Newton.LSODA.BDFMaxOrder",
               CCopasiParameter::UINT, (unsigned C_INT32) 5);
}

CNewtonMethod::CNewtonMethod(const CNewtonMethod & src,
                             const CCopasiContainer * pParent):
    CSteadyStateMethod(src, pParent),
    mIpiv(NULL)
{}

CNewtonMethod::~CNewtonMethod()
{cleanup();}

void CNewtonMethod::cleanup()
{
  pdelete(mIpiv);
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
          setValue("Newton.UseNewton", true);
          setValue("Newton.UseIntegration", true);
          setValue("Newton.UseBackIntegration", false);
          break;

        case 1:
          setValue("Newton.UseNewton", false);
          setValue("Newton.UseIntegration", true);
          setValue("Newton.UseBackIntegration", false);
          break;

        case 2:
          setValue("Newton.UseNewton", true);
          setValue("Newton.UseIntegration", false);
          setValue("Newton.UseBackIntegration", false);
          break;

        case 3:
          setValue("Newton.UseNewton", false);
          setValue("Newton.UseIntegration", false);
          setValue("Newton.UseBackIntegration", true);
          break;

        default:
          fatalError();
        }

      configBuffer.getVariable("SSBackIntegration", "bool", &Bool);
      setValue("Newton.UseBackIntegration", Bool);

      configBuffer.getVariable("NewtonLimit", "C_INT32", &Int,
                               CReadConfig::SEARCH);
      setValue("Newton.IterationLimit", Int);

      configBuffer.getVariable("SSResoltion", "C_FLOAT64", &Dbl);
      setValue("Newton.Resolution", Dbl);

      configBuffer.getVariable("RelativeTolerance", "C_FLOAT64", &Dbl);
      setValue("Newton.LSODA.RelativeTolerance", Dbl);

      configBuffer.getVariable("AbsoluteTolerance", "C_FLOAT64", &Dbl);
      setValue("Newton.LSODA.AbsoluteTolerance", Dbl);

      configBuffer.getVariable("AdamsMaxOrder", "C_INT32", &Int);
      setValue("Newton.LSODA.AdamsMaxOrder", Int);

      configBuffer.getVariable("BDFMaxOrder", "C_INT32", &Int);
      setValue("Newton.LSODA.BDFMaxOrder", Int);

      configBuffer.getVariable("DerivationFactor", "C_FLOAT64", &Dbl);
      setValue("Newton.DerivationFactor", Dbl);
    }
}

CSteadyStateMethod::ReturnCode
CNewtonMethod::processInternal()
{
  CTrajectoryTask * pTrajectory = NULL;
  CTrajectoryProblem * pTrajectoryProblem = NULL;
  CTrajectoryMethod * pTrajectoryMethod = NULL;

  cleanup();

  /* Configure Newton */
  mUseNewton = mUseIntegration = mUseBackIntegration = false;

  if (* (bool *) getValue("Newton.UseNewton"))
    mUseNewton = true;
  if (* (bool *) getValue("Newton.UseIntegration"))
    mUseIntegration = true;
  if (* (bool *) getValue("Newton.UseBackIntegration"))
    mUseBackIntegration = true;
  mIterationLimit = * (unsigned C_INT32 *) getValue("Newton.IterationLimit");
  mFactor = * (C_FLOAT64 *) getValue("Newton.DerivationFactor");
  mResolution = * (C_FLOAT64 *) getValue("Newton.Resolution");
  mScaledResolution =
    mResolution; // * initialState.getModel()->getQuantity2NumberFactor();
  //TODO discuss scaling

  // convert CState to CStateX
  mInitialStateX = mpProblem->getInitialState();
  *mpSteadyStateX = mInitialStateX; //not strictly necessary

  mDimension = mpSteadyStateX->getVariableNumberSize();
  mX = const_cast< C_FLOAT64 * >(mpSteadyStateX->getVariableNumberVector().array());

  mH.resize(mDimension);
  mXold.resize(mDimension);
  mdxdt.resize(mDimension);
  //mJacobianX.resize(mDimension, mDimension);
  mIpiv = new C_INT [mDimension];

  CNewtonMethod::NewtonReturnCode returnCode;
  if (mUseNewton)
    {
      returnCode = processNewton();
      if (returnCode == CNewtonMethod::found)
        return returnProcess(true, mFactor, mResolution);
    }

  if (mUseIntegration || mUseBackIntegration)
    {
      // create an appropriate trajectory task
      pTrajectory = new CTrajectoryTask();

      pTrajectoryProblem =
        dynamic_cast<CTrajectoryProblem *>(pTrajectory->getProblem());
      assert(pTrajectoryProblem);

      pTrajectoryMethod =
        dynamic_cast<CTrajectoryMethod *>(pTrajectory->getMethod());
      assert(pTrajectoryMethod);

      pTrajectoryProblem->setModel(mpProblem->getModel());
      pTrajectoryProblem->setStepNumber(1);

      pTrajectoryMethod->setValue("LSODA.RelativeTolerance",
                                  * (C_FLOAT64 *) getValue("Newton.LSODA.RelativeTolerance"));
      pTrajectoryMethod->setValue("LSODA.AbsoluteTolerance",
                                  * (C_FLOAT64 *) getValue("Newton.LSODA.AbsoluteTolerance"));
      pTrajectoryMethod->setValue("LSODA.AdamsMaxOrder",
                                  * (unsigned C_INT32 *) getValue("Newton.LSODA.AdamsMaxOrder"));
      pTrajectoryMethod->setValue("LSODA.BDFMaxOrder",
                                  * (unsigned C_INT32 *) getValue("Newton.LSODA.BDFMaxOrder"));

      pTrajectory->initialize();
    }

  C_FLOAT64 EndTime;
  if (mUseIntegration)
    {
      for (EndTime = 1; EndTime < 1.0e5; EndTime *= 10)
        {
          pTrajectoryProblem->setInitialState(mpProblem->getInitialState()); //TODO: on second run do not start from the beginning
          pTrajectoryProblem->setEndTime(pTrajectoryProblem->getStartTime() + EndTime);

          try
            {
              pTrajectory->process();
            }
          catch (CCopasiException Exception)
            {
              std::cout << std::endl << "exception in trajectory task" << std::endl;
              *mpSteadyStateX = *pTrajectory->getState();
              break;
            }

          *mpSteadyStateX = *pTrajectory->getState();
          const_cast<CModel *>(mpSteadyStateX->getModel())->getDerivativesX_particles(mpSteadyStateX, mdxdt);
          if (isSteadyState())
            {
              *mpSteadyState = *mpSteadyStateX; //convert back to CState
              return returnProcess(true, mFactor, mResolution);
            }

          //try Newton
          //mInitialStateX = mStateX;
          if (mUseNewton)
            {
              returnCode = processNewton();
              if (returnCode == CNewtonMethod::found)
              {return returnProcess(true, mFactor, mResolution);}
            }
        }
    }

  if (false /*mUseBackIntegration*/) //TODO:disabled at the moment
    {
      for (EndTime = -1; EndTime > -1.0e10; EndTime *= 10)
        {
          pTrajectoryProblem->setInitialState(mpProblem->getInitialState());
          pTrajectoryProblem->setEndTime(pTrajectoryProblem->getStartTime()
                                         + EndTime);
          pTrajectory->process();

          *mpSteadyStateX = *pTrajectory->getState();
          const_cast<CModel *>(mpSteadyStateX->getModel())->getDerivativesX_particles(mpSteadyStateX, mdxdt);
          if (isSteadyState())
            {
              *mpSteadyState = *mpSteadyStateX; //convert back to CState
              return returnProcess(true, mFactor, mResolution);
            }

          //try Newton
          //mInitialStateX = mStateX;
          if (mUseNewton)
            {
              returnCode = processNewton();
              if (returnCode == CNewtonMethod::found)
              {return returnProcess(true, mFactor, mResolution);}
            }
        }
    }

  pdelete(pTrajectory);
  cleanup();

  *mpSteadyState = *mpSteadyStateX; //convert back to CState
  return returnProcess(false, mFactor, mResolution);
}

CNewtonMethod::NewtonReturnCode CNewtonMethod::processNewton ()
{
  CNewtonMethod::NewtonReturnCode ReturnCode = CNewtonMethod::notFound;
  C_INT32 i, j, k;
  C_FLOAT64 nmaxrate;

  const_cast<CModel *>(mpSteadyStateX->getModel())->getDerivativesX_particles(mpSteadyStateX, mdxdt);
  if (isSteadyState())
    return returnNewton(CNewtonMethod::found);

  // Start the iterations
  C_INT info = 0;
  char T = 'T'; /* difference between fortran's and c's matrix storrage */
  C_INT one = 1;

  for (k = 0; k < mIterationLimit && mMaxrate > mScaledResolution; k++)
    {
      //std::cout << "newton: " << k << std::endl << mStateX;

      memcpy(mXold.array(), mX, mDimension * sizeof(C_FLOAT64));

      //      DebugFile << "Iteration: " << k << std::endl;
      mpSteadyStateX->calculateJacobian(*mpJacobianX, std::min(mFactor, mMaxrate),
                                        mResolution); //X
      //std::cout << "Jacobian: " << mJacobianX << std::endl;

      /* We use dgetrf_ and dgetrs_ to solve
         mJacobian * b = mH for b (the result is in mdxdt) */

      /* int dgetrf_(integer *m,
       *             integer *n, 
       *             doublereal *a, 
       *             integer * lda,
       *             integer *ipiv,
       *             integer *info)
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
            return returnNewton(CNewtonMethod::singularJacobian);
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

      nmaxrate = mMaxrate * 1.001;

      // copy values of increment to h
      for (i = 0; i < mDimension; i++)
        mH[i] = mdxdt[i];

      for (i = 0; (i < 32) && (nmaxrate >= mMaxrate); i++)
        {
          for (j = 0; j < mDimension; j++)
            {
              mX[j] = mXold[j] - mH[j];
              mH[j] /= 2;
            }

          const_cast<CModel *>(mpSteadyStateX->getModel())->getDerivativesX_particles(mpSteadyStateX, mdxdt);
          nmaxrate = xNorm(mDimension,
                           mdxdt.array() - 1,                           /* fortran style vector */
                           1);
        }

      if (i == 32)
        {
          std::cout << "a newton step did not succeed" << std::endl;

          //discard the step
          memcpy(mX, mXold.array(), mDimension * sizeof(C_FLOAT64));
          const_cast<CModel *>(mpSteadyStateX->getModel())->getDerivativesX_particles(mpSteadyStateX, mdxdt);

          if (isSteadyState())
            ReturnCode = CNewtonMethod::found;
          else if (mMaxrate < mScaledResolution)
            ReturnCode = CNewtonMethod::notFound;
          else
            ReturnCode = CNewtonMethod::dampingLimitExceeded;

          return returnNewton(ReturnCode);
        }

      //      for (i = 0; i < mDimension; i++)
      //        mSs_x[i] = mSs_xnew[i];

      mMaxrate = nmaxrate;
    }

  if (isSteadyState())
    ReturnCode = CNewtonMethod::found;
  else if (mMaxrate < mScaledResolution)
    ReturnCode = CNewtonMethod::notFound;
  else
    ReturnCode = CNewtonMethod::iterationLimitExceeded;

  return returnNewton(ReturnCode);
}

CNewtonMethod::NewtonReturnCode
CNewtonMethod::returnNewton(const CNewtonMethod::NewtonReturnCode & returnCode)
{
  mpProblem->getModel()->setStateX(mpSteadyStateX);
  mpProblem->getModel()->updateRates();
  *mpSteadyState = *mpSteadyStateX; //convert back to CState

  /*if (returnCode == CNewtonMethod::found)
    {
      const_cast<CModel *>(mStateX.getModel())->getDerivativesX_particles(&mStateX, mdxdt);
      *mpSteadyState = mStateX; //convert back to CState
    }
  else
    {
      const_cast<CModel *>(mpProblem->getInitialState().getModel())
      ->getDerivatives_particles(&mpProblem->getInitialState(), mdxdt);
      *mpSteadyState = mpProblem->getInitialState();
    }*/

  return returnCode;
}

bool CNewtonMethod::isSteadyState()
{
  C_INT32 i;

  if (mDimension == 0) return true;

  mMaxrate = xNorm(mDimension,
                   mdxdt.array() - 1,                           /* fortran style vector */
                   1);

  if (mMaxrate > mScaledResolution)
    return false;

  //for (i = 0; i < mDimension; i++)
  //  if (mX[i] < - mResolution) return false;
  //TODO: check if the above is really unnecessary...
  return true;
}
