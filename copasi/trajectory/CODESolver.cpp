/**
 * CODESolver
 * 
 * (C) Pedro Mendes 2001, based on code in Gepasi (C) Pedro Mendes 1990-2000
 */

/**
 * Protytpe use of this class:
 *
 * CODESolver solver;
 * solver.initialize(FEval, sy, n, method);
 * t_old = 0.0;
 * t_new = 0.0;
 * incr = t_final / n_incr;
 * for (i=0; i<n_incr; i++) 
 * {
 *      ret = solver.step(t_old, t_new);
 *      // if an error ocurred, make sure caller aborts
 *      if (ret) abort_trajectory(); 
 *      // signal caller success iteration
 *      // model copies sy values to arrays and outputs values
 *      Model.signal_iteration();
 *      t_new += incr;
 * }
 * solver.cleanUp();
 */

#include "copasi.h"
#include "CODESolver.h"

CODESolver::CODESolver()
{
  /* set version number */
  mVersion.setVersion(1,0,101);
  // initialize everything
  mName   = "Not selected";
  mMethod = 0;
  mY = NULL;
  mLsoda = NULL;
  mModel = NULL;
}


CODESolver::~CODESolver() 
{
  cleanup();
  cout << "~CODESolver " << mName << endl;
}

void CODESolver::initialize(CModel & model,
                            C_FLOAT64 * y, 
                            C_INT32 n, 
                            C_INT32 method)
{
  mModel = &model;
  mY = y;
  mDim = n;
  mState = 1;
  mMethod = method;
  switch (mMethod)
    {
    case 1: 
      mName = "LSODA"; 
      mLsoda = new Clsoda;

      break;
    default: mName = "Not selected"; break;
    }
}

void CODESolver::cleanup()
{
  switch (mMethod)
    {
    case 1:  // LSODA
      mLsoda->lsoda_freevectors();
      delete mLsoda;
      mLsoda = NULL;
      mName = "Not selected";
      mMethod = 0;
      break;
    default: break;
    }
  mState = -1; // so that calls without initialize() fail
}

string CODESolver::getName() {return mName;}

C_INT32 CODESolver::step(C_FLOAT64 t, C_FLOAT64 et)
{
  if ((mState<1) || (mState>2)) return mState;
  switch (mMethod)
    {
    case 1: //LSODA
      lSODAStep(t, et);
      if ((mState<1) || (mState>2)) return mState;
      else return 0;
    default:
      return -99;
    }
}


C_INT32 CODESolver::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;
    
  /* get version from ReadConfig */
  if (configbuffer.getVersion() < "4")
    {
      /* old Gepasi file, so integrator is LSODA for sure */
      mMethod = 1;
      mName = "LSODA";
    }
  else
    {
      /* read method number */
      Fail = configbuffer.getVariable("ODESolver", "C_INT32",
				      (void *) &mMethod,
				      CReadConfig::SEARCH);
      /* if no method number is found, assume LSODA for now */
      if (Fail)
        {
	  mMethod = 1;
	  mName = "LSODA";
        }
    }
  switch (mMethod)
    {
    case 1: return loadLSODAParameters(configbuffer);
    default: /* TODO: generate an error message */
      /* return error */
      return -1;
    }
}

C_INT32 CODESolver::save(CWriteConfig & configbuffer)
{
  C_INT32 Fail = 0;
    
  /* method */
  if ((Fail = configbuffer.setVariable("ODESolver", "C_INT32",
				       (void *) &mMethod)))
    return Fail;
  switch (mMethod)
    {
    case 1: return saveLSODAParameters(configbuffer);
    default: /* TODO: generate an error message */
      /* return error */
      return -1;
    }
}

C_INT32 CODESolver::loadLSODAParameters(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;
    
  if ((Fail = configbuffer.getVariable("RelativeTolerance", "C_FLOAT64",
				       (void *) &mRtol,
				       CReadConfig::LOOP)))
    return Fail;
  if ((Fail = configbuffer.getVariable("AbsoluteTolerance", "C_FLOAT64",
				       (void *) &mAtol)))
    return Fail;
  if ((Fail = configbuffer.getVariable("AdamsMaxOrder", "C_INT32",
				       (void *) &mAdams)))
    return Fail;
  if (mAdams<2) 
    mAdams = 2;
  else if (mAdams>12) 
    mAdams = 12;

  if ((Fail = configbuffer.getVariable("BDFMaxOrder", "C_INT32",
				       (void *) &mBDF)))
    return Fail;
  if (mBDF<2) 
    mBDF = 2;
  else if (mBDF>5) 
    mBDF = 5;

  return Fail;
}

C_INT32 CODESolver::lSODAStep(C_FLOAT64 t, C_FLOAT64 et)
{
  mTime = t;
  mEndt = et;
  mLsoda->lsoda(mModel,           // the function evaluator
		mDim,             // number of variables
		mY - 1,           // the array of current concentrations
		                  // fortran style vector !!!
		&mTime,           // the current time 
		mEndt,            // the final time
		1,                // scalar error control
		(&mRtol) - 1,     // relative tolerance array
		                  // fortran style vector !!!
		(&mAtol) - 1,     // absolute tolerance array
		                  // fortran style vector !!!
		1,                // output by overshoot & interpolatation
		&mState,          // the state control variable
		1,                // optional inputs are being used
		2,                // jacobian calculated internally 
		0,0,0,            // options left at default values
		10000,            // max iterations for each lsoda call
		0,                // another value left at the default
		mAdams,           // max order for Adams method
		mBDF,             // max order for BDF method
		0.0,0.0,0.0,0.0); // more options left at default values 
    
  if ((mState!=1) && (mState!=2))
    {
      mLsoda->lsoda_freevectors(); // freevectors is part of LSODA
      return mState;
    }
    
  // copy some lsoda counters
  intst = (C_FLOAT64) mLsoda->nst;
  nfeval = (C_FLOAT64) mLsoda->nfe;
  njeval = (C_FLOAT64) mLsoda->nje;
  stsize = mLsoda->h;
  return 0;
}

C_INT32 CODESolver::saveLSODAParameters(CWriteConfig & configbuffer)
{
  C_INT32 Fail = 0;
    
  if ((Fail = configbuffer.setVariable("RelativeTolerance", "C_FLOAT64",
				       (void *) &mRtol)))
    return Fail;
  if ((Fail = configbuffer.setVariable("AbsoluteTolerance", "C_FLOAT64",
				       (void *) &mAtol)))
    return Fail;
  if ((Fail = configbuffer.setVariable("AdamsMaxOrder", "C_INT32",
				       (void *) &mAdams)))
    return Fail;
  if ((Fail = configbuffer.setVariable("BDFMaxOrder", "C_INT32",
				       (void *) &mBDF)))
    return Fail;
  return Fail;
}
