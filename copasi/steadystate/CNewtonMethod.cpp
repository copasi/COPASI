/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CNewtonMethod.cpp,v $
   $Revision: 1.38 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/12/02 15:25:28 $
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
#include "utilities/COutputHandler.h"

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
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-006);
  addParameter("Newton.LSODA.AbsoluteTolerance",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-012);
  addParameter("Newton.LSODA.AdamsMaxOrder",
               CCopasiParameter::UINT, (unsigned C_INT32) 12);
  addParameter("Newton.LSODA.BDFMaxOrder",
               CCopasiParameter::UINT, (unsigned C_INT32) 5);
  addParameter("Newton.LSODA.MaxStepsInternal",
               CCopasiParameter::UINT, (unsigned C_INT32) 10000);
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
  if (mIpiv) delete [] mIpiv; mIpiv = NULL;
  // pdelete(mIpiv);
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

      configBuffer.getVariable("SSResoltion", "C_FLOAT64", &Dbl); //typo is necessary!!
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
  mX = const_cast< CVector< C_FLOAT64 > * >(&mpSteadyStateX->getVariableNumberVector());

  mH.resize(mDimension);
  mXold.resize(mDimension);
  mdxdt.resize(mDimension);
  //mJacobianX.resize(mDimension, mDimension);
  mIpiv = new C_INT [mDimension];

  if (mpProgressHandler) mpProgressHandler->init(0, "performing steady state calculation...", true);

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
      pTrajectoryMethod->setValue("LSODA.MaxStepsInternal",
                                  * (unsigned C_INT32 *) getValue("Newton.LSODA.MaxStepsInternal"));

      pTrajectory->initialize();
    }

  bool stepLimitReached = false;
  C_FLOAT64 EndTime;
  if (mUseIntegration)
    {
      std::cout << "Try integrating ..." << std::endl;
      for (EndTime = 1; EndTime < 1.0e10; EndTime *= 10)
        {
          if (mpProgressHandler) mpProgressHandler->reInit(0, "forward integrating...");
          if (mpProgressHandler) if (mpProgressHandler->progress(-1)) break;
          std::cout << "   integrating up to " << EndTime << std::endl;

          pTrajectoryProblem->setInitialState(mpProblem->getInitialState()); //TODO: on second run do not start from the beginning
          pTrajectoryProblem->setEndTime(pTrajectoryProblem->getStartTime() + EndTime);
          try
            {
              stepLimitReached = !pTrajectory->processSimple(true); //single step
            }
          catch (CCopasiException Exception)
            {
              std::cout << std::endl << "exception in trajectory task" << std::endl;
              *mpSteadyStateX = *pTrajectory->getState();
              break;
            }

          *mpSteadyStateX = *pTrajectory->getState();
          const_cast<CModel *>(mpSteadyStateX->getModel())->getDerivativesX_particles(mpSteadyStateX, mdxdt);
          if (isSteadyState(targetFunction(mdxdt)))
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

          if (stepLimitReached)
            {
              std::cout << "Step limit reached at Endtime " << EndTime << std::endl;
              break;
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
          pTrajectory->processSimple();

          *mpSteadyStateX = *pTrajectory->getState();
          const_cast<CModel *>(mpSteadyStateX->getModel())->getDerivativesX_particles(mpSteadyStateX, mdxdt);
          if (isSteadyState(targetFunction(mdxdt)))
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

  if (mpProgressHandler) mpProgressHandler->finish();

  *mpSteadyState = *mpSteadyStateX; //convert back to CState
  return returnProcess(false, mFactor, mResolution);
}

CNewtonMethod::NewtonReturnCode CNewtonMethod::processNewton ()
{
  CNewtonMethod::NewtonReturnCode ReturnCode = CNewtonMethod::notFound;
  C_INT32 i, j, k;
  C_FLOAT64 oldMaxRate, newMaxRate;

  const_cast<CModel *>(mpSteadyStateX->getModel())->getDerivativesX_particles(mpSteadyStateX, mdxdt);
  oldMaxRate = targetFunction(mdxdt);
  if (isSteadyState(oldMaxRate))
    return returnNewton(CNewtonMethod::found);

  std::cout << "Before: " << oldMaxRate << std::endl;

  // Start the iterations
  C_INT info = 0;
  char T = 'T'; /* difference between fortran's and c's matrix storrage */
  C_INT one = 1;

  std::cout << "processNewton called" << std::endl;

  for (k = 0; k < mIterationLimit && oldMaxRate > mScaledResolution; k++)
    {
      if (mpProgressHandler) /*flagStopped =*/ mpProgressHandler->reInit(0, "newton method...");
      if (mpProgressHandler) if (mpProgressHandler->progress(-1)) break;
      //std::cout << "newton: " << k << std::endl << mStateX;

      //memcpy(mXold.array(), mX->array(), mDimension * sizeof(C_FLOAT64));
      mXold = *mX; //should be almost as efficient as the above

      //      DebugFile << "Iteration: " << k << std::endl;
      mpSteadyStateX->calculateJacobian(*mpJacobianX, std::min(mFactor, oldMaxRate),
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

      newMaxRate = oldMaxRate * 1.001;

      // copy values of increment to h
      for (i = 0; i < mDimension; i++)
        mH[i] = mdxdt[i];

      for (i = 0; (i < 32) && (newMaxRate >= oldMaxRate); i++)
        {
          for (j = 0; j < mDimension; j++)
            {
              (*mX)[j] = mXold[j] - mH[j];
              mH[j] /= 2;
            }

          const_cast<CModel *>(mpSteadyStateX->getModel())->getDerivativesX_particles(mpSteadyStateX, mdxdt);
          newMaxRate = targetFunction(mdxdt);
          std::cout << "k: " << k << " i: " << i << " target: " << newMaxRate << std::endl;
        }

      std::cout << k << "th Newton Step. i = " << i << " maxRate = " << newMaxRate << std::endl;

      if (i == 32)
        {
          std::cout << "a newton step did not improve the target function" << std::endl;

          //discard the step
          *mX = mXold; //memcpy(mX->array(), mXold.array(), mDimension * sizeof(C_FLOAT64));

          const_cast<CModel *>(mpSteadyStateX->getModel())->getDerivativesX_particles(mpSteadyStateX, mdxdt);
          oldMaxRate = targetFunction(mdxdt);

          if (isSteadyState(oldMaxRate))
            ReturnCode = CNewtonMethod::found;
          else if (oldMaxRate < mScaledResolution)
            ReturnCode = CNewtonMethod::notFound;
          else
            ReturnCode = CNewtonMethod::dampingLimitExceeded;

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

bool CNewtonMethod::isSteadyState(C_FLOAT64 value)
{
  if (value > mScaledResolution)
    return false;

  return true;
}

C_FLOAT64 CNewtonMethod::targetFunction(const CVector< C_FLOAT64 > & particlefluxes) const
  {
    const CCopasiVector<CMetab> & metabs = mpSteadyStateX->getModel()->getMetabolitesInd();
    const C_FLOAT64 & factor = mpSteadyStateX->getModel()->getNumber2QuantityFactor();

    C_FLOAT64 tmp, store = 0;

    C_INT32 i, imax = metabs.size();
    for (i = 0; i < imax; ++i)
      {
        tmp = fabs(mdxdt[i] * metabs[i]->getCompartment()->getVolumeInv() * factor);
        if (tmp > store)
          store = tmp;
        //std::cout << metabs[i]->getObjectName() << "  " << tmp << std::endl;
      }
    return store;
  }
