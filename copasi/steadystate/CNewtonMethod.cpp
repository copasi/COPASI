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

#include "clapackwrap.h"        //use CLAPACK
#include "utilities/utility.h"

CNewtonMethod::CNewtonMethod(const std::string & name,
                             const CCopasiContainer * pParent,
                             const std::string & type):
    CSteadyStateMethod(name, pParent, type),
    mIpiv(NULL)
{
  mTypeEnum = CSteadyStateMethod::Newton;
  setType(CSteadyStateMethod::TypeName[mTypeEnum]);

  add("Newton.UseNewton", 1, CMethodParameter::BOOL);
  add("Newton.UseIntegration", 1, CMethodParameter::BOOL);
  add("Newton.UseBackIntegration", 1, CMethodParameter::BOOL);
  add("Newton.IterationLimit", 50, CMethodParameter::UINT);
  add("Newton.DerivationFactor", 1.0e-003);
  add("Newton.Resolution", 1.0e-009);
  add("Newton.LSODA.RelativeTolerance", 1.0e-012);
  add("Newton.LSODA.AbsoluteTolerance", 1.0e-006);
  add("Newton.LSODA.AdamsMaxOrder", 12, CMethodParameter::UINT);
  add("Newton.LSODA.BDFMaxOrder", 5, CMethodParameter::UINT);
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
                         CReadConfig::Mode mode)
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

      configBuffer.getVariable("NewtonLimit", "C_FLOAT64", &Dbl,
                               CReadConfig::SEARCH);
      setValue("Newton.IterationLimit", Dbl);

      configBuffer.getVariable("SSResoltion", "C_FLOAT64", &Dbl);
      setValue("Newton.Resolution", Dbl);

      configBuffer.getVariable("RelativeTolerance", "C_FLOAT64", &Dbl);
      setValue("Newton.LSODA.RelativeTolerance", Dbl);

      configBuffer.getVariable("AbsoluteTolerance", "C_FLOAT64", &Dbl);
      setValue("Newton.LSODA.AbsoluteTolerance", Dbl);

      configBuffer.getVariable("AdamsMaxOrder", "C_FLOAT64", &Dbl);
      setValue("Newton.LSODA.AdamsMaxOrder", Dbl);

      configBuffer.getVariable("BDFMaxOrder", "C_FLOAT64", &Dbl);
      setValue("Newton.LSODA.BDFMaxOrder", Dbl);

      configBuffer.getVariable("DerivationFactor", "C_FLOAT64", &Dbl);
      setValue("Newton.DerivationFactor", Dbl);
    }
  else
    CMethodParameterList::load(configBuffer, mode);
}

CSteadyStateMethod::ReturnCode
CNewtonMethod::process(CState & steadyState,
                       const CState & initialState)
{
  std::ofstream output;
  CTrajectoryTask * pTrajectory = NULL;
  CTrajectoryProblem * pTrajectoryProblem = NULL;
  CTrajectoryMethod * pTrajectoryMethod = NULL;
  bool foundSteadyState = false;

  cleanup();

  /* Configure Newton */
  mUseNewton = mUseIntegration = mUseBackIntegration = false;

  if (getValue("Newton.UseNewton"))
    mUseNewton = true;
  if (getValue("Newton.UseIntegration"))
    mUseIntegration = true;
  if (getValue("Newton.UseBackIntegration"))
    mUseBackIntegration = true;
  mIterationLimit = (C_INT32) getValue("Newton.IterationLimit");
  mFactor = getValue("Newton.DerivationFactor");
  mResolution = getValue("Newton.Resolution");
  mScaledResolution =
    mResolution * initialState.getModel()->getQuantity2NumberFactor();

  if (mUseIntegration || mUseBackIntegration)
    {
      // create an appropriate trajectory task
      pTrajectoryProblem = new CTrajectoryProblem();
      pTrajectoryProblem->setModel(mpProblem->getModel());
      pTrajectoryProblem->setStepNumber(1);

      pTrajectoryMethod = CTrajectoryMethod::
                          createTrajectoryMethod(CTrajectoryMethod::deterministic);
      pTrajectoryMethod->setValue("LSODA.RelativeTolerance",
                                  getValue("Newton.LSODA.RelativeTolerance"));
      pTrajectoryMethod->setValue("LSODA.AbsoluteTolerance",
                                  getValue("Newton.LSODA.AbsoluteTolerance"));
      pTrajectoryMethod->setValue("LSODA.AdamsMaxOrder",
                                  getValue("Newton.LSODA.AdamsMaxOrder"));
      pTrajectoryMethod->setValue("LSODA.BDFMaxOrder",
                                  getValue("Newton.LSODA.BDFMaxOrder"));

      pTrajectory = new CTrajectoryTask();
      pTrajectory->setProblem(pTrajectoryProblem);
      pTrajectory->setMethod(pTrajectoryMethod);

      //      output.open("output.txt");
      //      pTrajectory->initializeReporting(output);
    }

  // make sure the steady state has the correct allocation
  CStateX InitialState = initialState;
  mSteadyState = InitialState;

  mDimension = mSteadyState.getVariableNumberSize();

  mX = const_cast< C_FLOAT64 * >(mSteadyState.getVariableNumberVectorDbl().array());
  mH.resize(mDimension);
  mXold.resize(mDimension);
  mdxdt.resize(mDimension);
  mJacobian.resize(mDimension, mDimension);
  mIpiv = new C_INT [mDimension];

  CNewtonMethod::NewtonReturnCode returnCode;

  if (mUseNewton && !foundSteadyState)
    {
      returnCode = processNewton(mSteadyState, InitialState);
      if (returnCode == CNewtonMethod::found)
        foundSteadyState = true;
    }

  C_FLOAT64 EndTime;

  if (mUseIntegration && !foundSteadyState)
    {
      for (EndTime = 1; EndTime < 1.0e10; EndTime *= 10)
        {
          pTrajectoryProblem->setInitialState(InitialState);
          pTrajectoryProblem->setEndTime(pTrajectoryProblem->getStartTime()
                                         + EndTime);
          pTrajectory->process();
          mSteadyState = *pTrajectory->getState();

          const_cast<CModel *>(mSteadyState.getModel())->
          getDerivatives(&mSteadyState, mdxdt);

          if (isSteadyState())
            {
              foundSteadyState = true;
              break;
            }

          InitialState = mSteadyState;

          if (mUseNewton)
            {
              returnCode = processNewton(mSteadyState, InitialState);
              if (returnCode == CNewtonMethod::found)
                {
                  foundSteadyState = true;
                  break;
                }
            }
        }
    }

  if (mUseBackIntegration && !foundSteadyState)
    {
      for (EndTime = -1; EndTime > -1.0e10; EndTime *= 10)
        {
          pTrajectoryProblem->setInitialState(InitialState);
          pTrajectoryProblem->setEndTime(pTrajectoryProblem->getStartTime()
                                         + EndTime);
          pTrajectory->process();
          mSteadyState = *pTrajectory->getState();

          const_cast<CModel *>(mSteadyState.getModel())->
          getDerivatives(&mSteadyState, mdxdt);

          if (isSteadyState())
            {
              foundSteadyState = true;
              break;
            }

          InitialState = mSteadyState;

          if (mUseNewton)
            {
              returnCode = processNewton(mSteadyState, InitialState);
              if (returnCode == CNewtonMethod::found)
                {
                  foundSteadyState = true;
                  break;
                }
            }
        }
    }

  pdelete(pTrajectory);
  cleanup();

  steadyState = mSteadyState;

  return returnProcess(foundSteadyState, mFactor, mResolution);
}

CNewtonMethod::NewtonReturnCode
CNewtonMethod::processNewton (CStateX & steadyState,
                              CStateX & initialState)
{
  CNewtonMethod::NewtonReturnCode ReturnCode = CNewtonMethod::notFound;
  C_INT32 i, j, k;
  C_FLOAT64 nmaxrate;

  const_cast<CModel *>(steadyState.getModel())->getDerivatives(&steadyState,
      mdxdt);

  if (isSteadyState())
    returnNewton(CNewtonMethod::found, steadyState, initialState);

  // Start the iterations
  C_INT info = 0;
  char T = 'T'; /* difference between fortran's and c's matrix storrage */
  C_INT one = 1;

  for (k = 0; k < mIterationLimit && mMaxrate > mScaledResolution; k++)
    {
      memcpy(mXold.array(), mX, mDimension * sizeof(C_FLOAT64));

      //      DebugFile << "Iteration: " << k << std::endl;
      steadyState.getJacobian(mJacobian, std::min(mFactor, mMaxrate),
                              mResolution);
      //      DebugFile << "Jacobien: " << mJacobian << std::endl;

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
      dgetrf_(&mDimension, &mDimension, mJacobian.array(),
              &mDimension, mIpiv, &info);

      if (info)
        {
          if (info > 0)
            return returnNewton(CNewtonMethod::singularJacobian,
                                steadyState, initialState);
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
      //      DebugFile << "b: " << mdxdt << std::endl;
      dgetrs_(&T, &mDimension, &one, mJacobian.array(),
              &mDimension, mIpiv, mdxdt.array(), &mDimension, &info);
      //      DebugFile << "a: " << mdxdt << std::endl << std::endl;

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

          const_cast<CModel *>(steadyState.getModel())->
          getDerivatives(&steadyState, mdxdt);
          nmaxrate = xNorm(mDimension,
                           mdxdt.array() - 1,             /* fortran style vector */
                           1);
        }

      if (i == 32)
        {
          memcpy(mX, mXold.array(), mDimension * sizeof(C_FLOAT64));
          const_cast<CModel *>(steadyState.getModel())->
          getDerivatives(&steadyState, mdxdt);

          if (isSteadyState())
            ReturnCode = CNewtonMethod::found;
          else if (mMaxrate < mScaledResolution)
            ReturnCode = CNewtonMethod::notFound;
          else
            ReturnCode = CNewtonMethod::dampingLimitExceeded;

          return returnNewton(ReturnCode, steadyState, initialState);
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

  return returnNewton(ReturnCode, steadyState, initialState);
}

CNewtonMethod::NewtonReturnCode
CNewtonMethod::returnNewton(const CNewtonMethod::NewtonReturnCode & returnCode,
                            CStateX & steadyState,
                            CStateX & initialState)
{
  /* Make sure the model reflects the current state */
  if (returnCode == CNewtonMethod::found)
    const_cast<CModel *>(steadyState.getModel())->
    getDerivatives(&steadyState, mdxdt);
  else
    const_cast<CModel *>(initialState.getModel())->
    getDerivatives(&initialState, mdxdt);

  return returnCode;
}

bool CNewtonMethod::isSteadyState()
{
  C_INT32 i;

  mMaxrate = xNorm(mDimension,
                   mdxdt.array() - 1,             /* fortran style vector */
                   1);

  if (mMaxrate > mScaledResolution)
    return false;

  for (i = 0; i < mDimension; i++)
    if (mX[i] < - mResolution) return false;

  return true;
}
