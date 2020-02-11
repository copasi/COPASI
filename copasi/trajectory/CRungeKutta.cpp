// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 *   CRungeKutta
 *
 *   This class is the ODE solver in terms Ronge-Kutta Method ODE45.
 *
 *   File name: CRungeKutta.cpp
 *   Author: Shuo Wang
 *   Email: shuowang.learner@gmail.com
 *
 *   Last change: 07, July 2014
 *
 */

#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <string.h>

#include "CRungeKutta.h"

// Uncomment this line below to get debug print out.
// #define DEBUG_OUTPUT 1

//*********************************//
//* Constructor and Destructor    *//
//*********************************//

/*
 * Default Constructor
 */
CRungeKutta::CRungeKutta()
{
  // Default error tolerances
  mAbsTol = 1e-12;
  mRelTol = 1e-10;
  mMaxSteps = 100000;

  // Default function pointers
  mpDerivFunc = NULL;
  mpEventFunc = NULL;

  // Default system state
  mpDim = NULL;
  mTEnd = 0;
  mTRight = 0;
  mTLeft = 0;
  mpY = NULL;
  mYRight = NULL;
  mYLeft = NULL;
  mK = NULL;

  // Default coefficients
  mP = 0;
  mStage = 0;
  mOrderY = 0;
  mOrderYp = 0;

  // Default step size related
  mh = 0;
  mhMin = 0;
  mhMax = 0;
  mFac = 0;
  mFacMin = 0;
  mFacMax = 0;
  mFacMaxRej = 0;

  // Default solver status
  mhNoFailed      = false;
  mMethodStatus   = ERROR;
  mContinueFromInterpolation = false;

  // Default root finder related
  mRootNum = 0;
  mRootValueRight = NULL;
  mRootValuesLeft = NULL;
  mRootValueTmp = NULL;

  // Default statistic variables
  mStepNum = 0;
  mAcceptNum = 0;
  mRejectNum = 0;
  mfEvalNum = 0;
  mrEvalNum = 0;

  // Default tempt variable
  mZ1 = NULL;
  mZ2 = NULL;
  mZ3 = NULL;

  mpRootValueCalculator = new CBrent::EvalTemplate< CRungeKutta >(this, &CRungeKutta::rootValue);

  return;
}

/*
 * Default Destructor
 */
CRungeKutta::~CRungeKutta()
{
  if (mpDerivFunc)
    mpDerivFunc = NULL;

  if (mpEventFunc)
    mpEventFunc = NULL;

  pdelete(mYRight);
  pdelete(mYLeft);

  if (mK)
    {
      for (int i = (int)mStage; i >= 0; i--)
        pdelete(mK[i])

        pdelete(mK);
    }

  pdelete(mRootValuesLeft);
  pdelete(mRootValueRight);
  pdelete(mRootValueTmp);
  pdelete(mZ1);
  pdelete(mZ2);
  pdelete(mZ3);

  return;
}

//*************************//
//* Main Process Function *//
//*************************//

/**
 * Main function processing integration along time
 */
CRungeKutta::RKMethodStatus CRungeKutta::operator()(const size_t * pDim,
    C_FLOAT64 * pY,
    C_FLOAT64 * pTime,
    C_FLOAT64 * pEndTime,
    const size_t rootCount,
    C_INT * pRoots,
    const CRungeKutta::RKMethodStatus & status,
    const bool & oneStep,
    C_FLOAT64 * rtol,
    C_FLOAT64 * atol,
    unsigned C_INT32 * pMaxSteps,
    EvalDeriv pEvalDerivatives,
    EvalRoot pEvalRoots)
{
  //====================//
  // 1 check mODEstate  //
  //====================//
  mMethodStatus = checkODEState(status) ? status : ERROR;

  if (mMethodStatus == ERROR) return mMethodStatus;

#ifdef DEBUG_OUTPUT
  std::cout << "Status:    " << mMethodStatus << std::endl;
#endif // DEBUG_OUTPUT

  if (status == INITIALIZE)
    {
      initialize(pDim, pY, pTime, pEndTime, rootCount, pRoots, status, rtol, atol, pMaxSteps, pEvalDerivatives, pEvalRoots);

      if (mMethodStatus == ERROR) return mMethodStatus;
    }

  if (mMethodStatus == RESTART) //Restart
    {
      mTLeft = *pTime;
      memcpy(mYLeft, mpY, *mpDim * sizeof(C_FLOAT64));
      mContinueFromInterpolation = false;

      setInitialStepSize();

      mpDerivFunc(mpDim, &mTLeft, mYLeft, mK[0]); //record derivative to

      // Calculate root at initial time
      if (mRootNum > 0)
        {
          (*mpEventFunc)(mpDim, &mTLeft, mYLeft, &mRootNum, mRootValuesLeft);
        }

#ifdef DEBUG_OUTPUT
      std::cout << "old Y:    " << CVectorCore< C_FLOAT64 >(*mpDim, mYLeft) << std::endl;
      std::cout << "old Root: " << CVectorCore< C_FLOAT64 >(mRootNum, mRootValuesLeft) << std::endl;
#endif // DEBUG_OUTPUT
    }
  else if (mMethodStatus != CONTINUE) // has event
    {
      mMethodStatus = ERROR;
      return mMethodStatus;
    }

  mTEnd = *pEndTime;

  assert(mContinueFromInterpolation || mTLeft == *pTime);

  C_FLOAT64 Tolerance = 100.0 * (fabs(mTEnd) * std::numeric_limits< C_FLOAT64 >::epsilon() + std::numeric_limits< C_FLOAT64 >::min());

  if (mContinueFromInterpolation)
    {
      // Complete the interrupted step.
      checkRoots();

      if (mMethodStatus == ROOTFOUND) //has events
        {
          *pTime = *mpY;

          // We need to check whether pTime is actually mTEnd in which case we need to advance
          if (fabs(*pTime - mTEnd) < Tolerance)
            {
              advanceStep();
              memcpy(mpY, mYRight, *mpDim * sizeof(C_FLOAT64));
              *pTime = *mpY;
            }

          return mMethodStatus;
        }

      //~~~~~~~~~~~~~~~~~~~~~~//
      // (5) Advance New Step //
      //~~~~~~~~~~~~~~~~~~~~~~//
      advanceStep();
    }

  unsigned C_INT32 StepCounter = 0;

  //=============//
  // 2 Main Loop //
  //=============//
  while (mTLeft < mTEnd && StepCounter < mMaxSteps)
    {
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
      // (1) Check Whether mT is close to mTEnd //
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
      if (1.1 * mh >= (mTEnd - mTLeft))
        mh = mTEnd - mTLeft;

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
      // (2) Set Some Parameters before One Step //
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
      mhNoFailed = true;

      //~~~~~~~~~~~~~~~~~~~~~~~//
      // (3) Continue One Step //
      //~~~~~~~~~~~~~~~~~~~~~~~//
      while (true)
        {
          // (i) Do One Single Step
          doOneStep();

          // (ii) Update Statistic Record
          mfEvalNum += mStage;

          // (iii) Estimate Error
          C_FLOAT64 error = estimateError();

          //(iv) Update step size mh
          if (std::isnan(error))
            {
              {
                mMethodStatus = ERROR;
                mErrorMessage << "Failure at t=" << mTLeft << std::endl;
                mErrorMessage << "NaN values encountered in simulation." << std::endl;

                return mMethodStatus;
              }
            }
          else if (error > 1.0) // Step Rejected
            {
              mhNoFailed = false;
              mRejectNum++;
              mh *= 0.5; // Use half step size h

              if (mh < mhMin)
                {
                  mMethodStatus = ERROR;
                  mErrorMessage << "Failure at t=" << mTLeft << std::endl;
                  mErrorMessage << "Unable to meet integration tolerances without reducing the step size below the smallest value!" << std::endl;

                  return mMethodStatus;
                }
            }
          else // Step Accept
            {
              mhMin = deps(mTRight) * 16.0;
              mAcceptNum++;

              C_FLOAT64 fac = pow(1 / error, 1.0 / (mP + 1.0));

              if (!mhNoFailed) //previous step is rejected
                mh *= std::min(mFacMaxRej, std::max(mFacMin, mFac * fac));
              else
                mh *= std::min(mFacMax, std::max(mFacMin, mFac * fac));

              break;
            }
        } // end while

      StepCounter++;

      mStepNum++;

      //~~~~~~~~~~~~~~~~~~//
      // (4) Check Events //
      //~~~~~~~~~~~~~~~~~~//
      if (mRootNum > 0)
        {
          checkRoots();

          if (mMethodStatus == ROOTFOUND) //has events
            {
              *pTime = *mpY;

              // We need to check whether pTime is actually mTEnd in which case we need to advance
              if (fabs(*pTime - mTEnd) < Tolerance)
                {
                  advanceStep();
                  memcpy(mpY, mYRight, *mpDim * sizeof(C_FLOAT64));
                  *pTime = *mpY;
                }

              return mMethodStatus;
            }
        }

      //~~~~~~~~~~~~~~~~~~~~~~//
      // (5) Advance New Step //
      //~~~~~~~~~~~~~~~~~~~~~~//
      advanceStep();

      if (oneStep) break;
    } // end while

  if (StepCounter < mMaxSteps)
    {
      //~~~~~~~~~~~~~~~~~~~~~~~~~~//
      //  Integration Finished    //
      //~~~~~~~~~~~~~~~~~~~~~~~~~~//

      mMethodStatus = END;
    }
  else
    {
      mErrorMessage << "The internal step limit has been reached." << std::endl;

      mMethodStatus = ERROR;
    }

  memcpy(mpY, mYRight, *mpDim * sizeof(C_FLOAT64));
  *pTime = *mpY;

  return mMethodStatus;
}

std::string CRungeKutta::getErrorMesssage() const
{
  return mErrorMessage.str();
}

/**
 * Check the state attribute mODEState.
 * If mODEState=0, first call of this method, initialization are required
 * If mODEState=1, restart this method, method key parameters should be checked
 * If mODEState=2, continue from last step which has an event (mODEState=3).
 *                 First check if events left. If not, continue, else return with next event
 * Else, method has error.
 */
bool CRungeKutta::checkODEState(const RKMethodStatus & status)
{
  if (mMethodStatus == ERROR && status != INITIALIZE)
    {
      mErrorMessage << "To recover from an error the integrator needs to be called with INITIALIZE!" << std::endl;
      return false;
    }

  if (status != CONTINUE &&
      status != RESTART &&
      status != INITIALIZE)
    {
      mErrorMessage << "The only valid entry state are INITIALIZE, RESTART or CONTINUE!" << std::endl;
      return false;
    }

  return true;
}

/*
 * doOneStep()
 * This is a virtual function for RK Method which calculates approximated derivatives,
 * new Y and new T.
 */
void CRungeKutta::doOneStep()
{
  C_FLOAT64 t;

  // (1) Calculate mK[1] to mK[mStage-1]
  for (size_t s = 1; s < mStage; s++)
    {
      t = mTLeft + mh * mC[s]; //tmp time
      memcpy(mZ1, mYLeft, *mpDim * sizeof(C_FLOAT64));

      for (size_t i = 0; i < s; i++) //tmp Y + Yp*h
        {
          C_FLOAT64 a = mA[s][i] * mh;

          for (size_t j = 0; j < *mpDim; j++)
            mZ1[j] += mK[i][j] * a;
        }

      mpDerivFunc(mpDim, &t, mZ1, mK[s]);
    }

  // (2) New Time, mTNew
  size_t s = mStage - 1;
  mTRight = mTLeft + mh;

  // (3) New Y, mYNew
  memcpy(mYRight, mYLeft, *mpDim * sizeof(C_FLOAT64));

  for (size_t s = 0; s < mStage; s++)
    {
      C_FLOAT64 b = mB[s] * mh;

      for (size_t i = 0; i < *mpDim; i++)
        mYRight[i] += b * mK[s][i];
    }

  *mYRight = mTRight;

  // (4) New Yp, recording it into last row of mK
  mpDerivFunc(mpDim, &mTRight, mYRight, mK[mStage]);

  return;
}

/*
 * estimateError()
 * Function that calculate error in terms of algorithms in book ""
 * Chapter II, Automatic Step Size Control, pp 167-169.
 */
C_FLOAT64 CRungeKutta::estimateError()
{
  // (1) Calculate |ynew - ynew*| in terms of mE
  for (size_t i = 0; i < *mpDim; i++)
    mZ2[i] = 0;

  for (size_t s = 0; s < mStage + 1; s++)
    {
      C_FLOAT64 e = mE[s] * mh;

      for (size_t i = 0; i < *mpDim; i++)
        mZ2[i] += e * mK[s][i];
    }

  // (2) Calculate Standard sc=Atol + max(|y|,|ynew|)*Rtol
  for (size_t i = 0; i < *mpDim; i++)
    mZ3[i] = mAbsTol + std::max(fabs(mYLeft[i]), fabs(mYRight[i])) * mRelTol;

  // (3) Calculate Error
  C_FLOAT64 error = 0, tmp;

  for (size_t i = 0; i < *mpDim; i++)
    {
      tmp = mZ2[i] / mZ3[i];
      error += tmp * tmp;
    }

  error = sqrt(error / *mpDim);

  return error;
}

/*
 * advanceStep()
 * Set new mT, mY and mK[0]
 */
void CRungeKutta::advanceStep()
{
  mContinueFromInterpolation = false;
  mTLeft = mTRight;
  memcpy(mYLeft, mYRight, *mpDim * sizeof(C_FLOAT64));
  memcpy(mK[0], mK[mStage], *mpDim * sizeof(C_FLOAT64));

  return;
}

//***************************************//
//* Functions for System Initialization *//
//***************************************//
/*
 * initialize()
 * Initialize statistic record variables, coefficients for RK method, mODEState
 * and check event function mEventFunc.
 */
void CRungeKutta::initialize(const size_t * pDim,
                             C_FLOAT64 * pY,
                             C_FLOAT64 * pTime,
                             C_FLOAT64 * pEndTime,
                             const size_t rootCount,
                             C_INT * pRoots,
                             const RKMethodStatus & status,
                             C_FLOAT64 * rtol,
                             C_FLOAT64 * atol,
                             unsigned C_INT32 * pMaxSteps,
                             EvalDeriv pEvalDerivatives,
                             EvalRoot pEvalRoots)
{
  assert(status == INITIALIZE);

  mMethodStatus = INITIALIZE;

  if (!checkParameter(pDim, pY, pTime, pEndTime, rootCount, pRoots, status, rtol, atol, pMaxSteps, pEvalDerivatives, pEvalRoots))
    {
      mMethodStatus = ERROR;
    }

  if (mMethodStatus == ERROR) return;

  mpDim = pDim;
  mpY = pY;
  mTLeft = * pTime;
  mTEnd = *pEndTime;
  mRootNum = rootCount,
  mRootFound.initialize(mRootNum, pRoots);
  mMethodStatus = RESTART;
  mContinueFromInterpolation = false;

  if (rtol != NULL) mRelTol = *rtol;

  if (atol != NULL) mAbsTol = *atol;

  if (pMaxSteps != NULL) mMaxSteps = *pMaxSteps;

  mpDerivFunc = pEvalDerivatives;
  mpEventFunc = pEvalRoots;

  setStatRecord();
  setCoeff();
  allocateSpace();

  mErrorMessage.str("");

  return;
}

/**
 * Update time, results and other necessary stuff
 */
void CRungeKutta::allocateSpace()
{
  // ----(1)----
  //----Set mK----
  if (mK)
    {
      for (int i = (int)mStage; i >= 0; i--)
        pdelete(mK[i]);

      pdelete(mK);
    }

  mK = new C_FLOAT64*[mStage + 1];

  for (size_t r = 0; r < mStage + 1; r++)
    mK[r] = new C_FLOAT64[*mpDim];

  //----Set mYNew----
  pdelete(mYRight);
  mYRight = new C_FLOAT64[*mpDim];

  //----Set mYCp----
  pdelete(mYLeft);
  mYLeft = new C_FLOAT64[*mpDim];

  // ----(2)----
  size_t size = (*mpDim > mRootNum) ? *mpDim : mRootNum;
  size = (size > (MAX_STAGE + 2)) ? size : (MAX_STAGE + 2);

  pdelete(mZ1);
  mZ1 = new C_FLOAT64[size];

  pdelete(mZ2);
  mZ2 = new C_FLOAT64[size];

  pdelete(mZ3);
  mZ3 = new C_FLOAT64[size];

  if (mRootNum > 0)
    {
      pdelete(mRootValuesLeft);
      mRootValuesLeft = new C_FLOAT64[mRootNum];

      pdelete(mRootValueRight);
      mRootValueRight    = new C_FLOAT64[mRootNum];

      pdelete(mRootValueTmp);
      mRootValueTmp    = new C_FLOAT64[mRootNum];
    }

  return;
}

/**
 * Set coefficients for ODE45
 */
void CRungeKutta::setCoeff()
{
  mP       = 4;
  mStage   = 6;
  mOrderY  = 4;
  mOrderYp = 3;

  //----Set mA----
  C_FLOAT64 A[6][6] =
  {
    {0,            0,           0,         0,            0,  0},
    {1. / 5,            0,           0,         0,            0,  0},
    {3. / 40,        9. / 40,           0,         0,            0,  0},
    {44. / 45,      -56. / 15,       32. / 9,         0,            0,  0},
    {19372. / 6561, -25360. / 2187, 64448. / 6561, -212. / 729,            0,  0},
    {9017. / 3168,     -355. / 33, 46732. / 5247,   49. / 176, -5103. / 18656,  0}
  };

  for (size_t r = 0; r < mStage; r++)
    {
      for (size_t c = 0; c < mStage; c++)
        mA[r][c] = A[r][c];
    }

  //----Set mC----
  C_FLOAT64 C[6] = {0, 1. / 5, 3. / 10, 4. / 5, 8. / 9, 1.};

  for (size_t c = 0; c < mStage; c++)
    mC[c] = C[c];

  //----Set mB----
  C_FLOAT64 B[6] = {35. / 384, 0, 500. / 1113, 125. / 192, -2187. / 6784, 11. / 84};

  for (size_t c = 0; c < mStage; c++)
    mB[c] = B[c];

  //----Set mE----
  C_FLOAT64 E[7] = {71. / 57600, 0, -71. / 16695, 71. / 1920, -17253. / 339200, 22. / 525, -1. / 40};

  for (size_t c = 0; c < mStage + 1; c++)
    mE[c] = E[c];

  //----Set mI----
  C_FLOAT64 I[7][4] =
  {
    {1.,  -183. / 64,     37. / 12,   -145. / 128},
    {0,          0,          0,           0},
    {0,  1500. / 371, -1000. / 159,   1000. / 371},
    {0,   -125. / 32,    125. / 12,    -375. / 64},
    {0, 9477. / 3392,  -729. / 106, 25515. / 6784},
    {0,     -11. / 7,      11. / 3,     -55. / 28},
    {0,       3. / 2,        -4.,        5. / 2}
  };

  for (size_t r = 0; r < mStage + 1; r++)
    {
      for (size_t c = 0; c < mOrderY; c++)
        mI[r][c] = I[r][c];
    }

  return;
}

/*
 * setStatRecord()
 * Function is used to set statistc record related variables to be 0
 */
void CRungeKutta::setStatRecord()
{
  mStepNum   = 0;
  mAcceptNum = 0;
  mRejectNum = 0;
  mfEvalNum  = 0;
  mrEvalNum  = 0;

  return;
}

/*
 * setInitialStepSize()
 * Function is used to set the initial step size mh. Algorithm which is applied
 * is the one given in Book "Solving Ordinary Differential Equitions I", page
 * 169. Vector norm is the infinity norm picking the element having maximum
 * absolute value.
 */
void CRungeKutta::setInitialStepSize()
{
  // (1) First, set parameters, related step size control
  C_FLOAT64 absT   = fabs(mTLeft);

  mhMin      = 16.0 * deps(mTLeft);
  mhMax      = fabs(mTEnd - mTLeft) / 10;
  mFac       = 0.8;
  mFacMin    = 0.1;
  mFacMax    = 4;
  mFacMaxRej = 1.0;

  C_FLOAT64 d0, d1, d2, h0, h1;

  // (2) Calculate h0
  d0 = infNorm(*mpDim, mYLeft);
  mpDerivFunc(mpDim, &mTLeft, mYLeft, mZ1);//mZ1 is y'(t)
  d1 = infNorm(*mpDim, mZ1);

  if ((d0 < 1.0e-5) || (d1 < 1.0e-5))
    h0 = 1.0e-6;
  else
    h0 = 0.01 * (d0 / d1);

  // (3) Calculate h1
  for (size_t i = 0; i < *mpDim; i++)
    mZ3[i] = mYLeft[i] + h0 * mZ1[i]; // mZ3 is y(t+h0)

  C_FLOAT64 tCp = mTLeft;
  mTLeft += h0;
  mpDerivFunc(mpDim, &mTLeft, mZ3, mZ2);// mZ2 is y'(t+h0)

  for (size_t i = 0; i < *mpDim; i++)
    mZ3[i] = (mZ1[i] - mZ2[i]) / h0; // mZ3 is y''(t+h0)

  d2 = infNorm(*mpDim, mZ3);

  C_FLOAT64 tmp = std::max(d1, d2);

  if (tmp <= 1.0e-15)
    h1 = std::max(1.0e-6, h0 * 1.0e-3);
  else
    h1 = pow(0.01 / tmp, 1.0 / (mP + 1.0));

  // (4) Calculate h
  mh = std::min(100 * h0, h1);

  mTLeft = tCp;

  return;
}

//************************//
// Root Finder Functions *//
//************************//
/**
 * Set initial step size of integrator
 */
void CRungeKutta::interpolation(const C_FLOAT64 tInterp, C_FLOAT64 *yInterp)
{
  C_FLOAT64 tmp = (tInterp - mTLeft) / (mTRight - mTLeft);
  C_FLOAT64 S[MAX_STAGE];

  //S[0] = tmp * (mTNew-mTOld);
  S[0] = tInterp - mTLeft;

  for (size_t i = 1; i < mOrderY; i++)
    S[i] = S[i - 1] * tmp;

  memcpy(yInterp, mYLeft, *mpDim * sizeof(C_FLOAT64));

  for (size_t s = 0; s < mStage + 1; s++)
    {
      tmp = 0;

      for (size_t j = 0; j < mOrderY; j++)
        tmp += S[j] * mI[s][j];

      for (size_t d = 0; d < *mpDim; d++)
        yInterp[d] += tmp * mK[s][d];
    }

  *yInterp = tInterp;

  return;
}

/**
 * Check whether there is a root
 */
void CRungeKutta::checkRoots()
{
  C_FLOAT64 LastTime = mContinueFromInterpolation ? *mpY : mTLeft;

  C_FLOAT64 LeftTime = mTLeft;
  C_FLOAT64 * pLeftRoots = mRootValuesLeft;

  C_FLOAT64 RightTime = mTLeft;
  C_FLOAT64 * pRightRoots = mRootValueRight;

  C_FLOAT64 step = (mTRight - mTLeft) / 4;

  for (size_t s = 1; s < 5; ++s)
    {
      // Boundaries of the current interval
      LeftTime = RightTime;
      RightTime = mTLeft + s * step;

      if (LastTime >= RightTime)
        {
          continue;
        }
      else if (LastTime > LeftTime)
        {
          LeftTime = LastTime;
        }

      interpolation(RightTime, mZ1);
      (*mpEventFunc)(mpDim, &RightTime, mZ1, &mRootNum, mRootValueRight);
      mrEvalNum++;

      for (size_t r = 0; r < mRootNum; ++r)
        {
          if (*(mRootValuesLeft + r) **(mRootValueRight + r) < 0 ||
              *(mRootValueRight + r) == 0)
            {
              // We have found at least one root in the current interval.
              C_FLOAT64 RootTime;
              C_FLOAT64 RootValue;

              // Find the "exact" location of the left most root.

#ifdef DEBUG_OUTPUT
              std::cout << "old Y: " << CVectorCore< C_FLOAT64 >(*mpDim, mYLeft) << std::endl;
              std::cout << "new Y: " << CVectorCore< C_FLOAT64 >(*mpDim, mYRight) << std::endl;
#endif // DEBUG_OUTPUT

              if (!CBrent::findRoot(LeftTime, RightTime, mpRootValueCalculator, &RootTime, &RootValue, mRelTol))
                {
                  fatalError();
                }

              // We must not use mTRight as that is controlled by the Runge Kutta algorithm
              interpolation(RootTime, mZ1);
              (*mpEventFunc)(mpDim, &RootTime, mZ1, &mRootNum, mRootValueTmp);
              mrEvalNum++;

              mRootFound = 0;

              C_FLOAT64 * pRoot = mRootValueTmp;
              C_FLOAT64 * pRootEnd = pRoot + mRootNum;

              const C_FLOAT64 * pRootOld = mRootValuesLeft;
              const C_FLOAT64 * pRootNew = mRootValueRight;

              C_INT * pRootFound = mRootFound.array();

              for (; pRoot != pRootEnd; ++pRoot, ++pRootOld, ++pRootNew, ++pRootFound)
                {
                  // We are only looking for roots which change sign in [pOld, pNew]
                  if (*pRootOld **pRootNew < 0 || *pRootNew == 0)
                    {
                      if (*pRootOld **pRoot < 0)
                        {
                          *pRootFound = 1; // CMath::ToggleBoth
                          mMethodStatus = ROOTFOUND;
                        }
                      else if (fabs(*pRoot) <= (1.0 + std::numeric_limits< C_FLOAT64 >::epsilon()) * fabs(RootValue))
                        {
                          *pRoot *= -1;
                          *pRootFound = 1; // CMath::ToggleBoth
                          mMethodStatus = ROOTFOUND;
                        }
                      else
                        {
                          *pRootFound = 0;
                        }
                    }
                }

#ifdef DEBUG_OUTPUT
              std::cout << "root value: " << CVectorCore< C_FLOAT64 >(mRootNum, mRootValueTmp) << std::endl;
              std::cout << "root found: " << mRootFound << std::endl;
#endif // DEBUG_OUTPUT

              break;
            }
        }

      // Assure that the root values are recorded for the next integration step.
      if (mMethodStatus == ROOTFOUND)
        {
          mContinueFromInterpolation = true;
          memcpy(mpY, mZ1, *mpDim * sizeof(C_FLOAT64));
          memcpy(mRootValuesLeft, mRootValueTmp, mRootNum * sizeof(C_FLOAT64));

          break;
        }
      else
        {
          memcpy(mRootValuesLeft, mRootValueRight, mRootNum * sizeof(C_FLOAT64));
        }
    }

  return;
}

C_FLOAT64 CRungeKutta::rootValue(const C_FLOAT64 & time)
{
  interpolation(time, mZ1);
  (*mpEventFunc)(mpDim, &time, mZ1, &mRootNum, mRootValueTmp);
  mrEvalNum++;

  const C_FLOAT64 * pRoot = mRootValueTmp;
  const C_FLOAT64 * pRootEnd = pRoot + mRootNum;

  const C_FLOAT64 * pRootOld = mRootValuesLeft;
  const C_FLOAT64 * pRootNew = mRootValueRight;

  C_FLOAT64 MaxRootValue = - std::numeric_limits< C_FLOAT64 >::infinity();
  C_FLOAT64 RootValue;

  for (; pRoot != pRootEnd; ++pRoot, ++pRootOld, ++pRootNew)
    {
      // We are only looking for roots which change sign in [pOld, pNew]
      if (*pRootOld **pRootNew < 0 || *pRootNew == 0)
        {
          // Assure that the RootValue is increasing between old and new for each
          // candidate root.
          RootValue = (*pRootNew >= *pRootOld) ? *pRoot : -*pRoot;

          if (RootValue > MaxRootValue)
            {
              MaxRootValue = RootValue;
            }
        }
    }

#ifdef DEBUG_OUTPUT
  std::cout << "old Value: " << CVectorCore< C_FLOAT64 >(mRootNum, mRootValuesLeft) << std::endl;
  std::cout << "tmp Value: " << CVectorCore< C_FLOAT64 >(mRootNum, mRootValueTmp) << std::endl;
  std::cout << "new Value: " << CVectorCore< C_FLOAT64 >(mRootNum, mRootValueRight) << std::endl;

  std::cout << "rootValue: " << CVectorCore< C_FLOAT64 >(*mpDim, mZ1) << ", " << MaxRootValue << std::endl;
#endif // DEBUG_OUTPUT

  return MaxRootValue;
}

/**
 * Check whether a slow function fired in this step
 */
//*****************************//
//* Parameters Check Function *//
//*****************************//

/**
 * Check parameters used in the integration
 */
bool CRungeKutta::checkParameter(const size_t * pDim,
                                 C_FLOAT64 * pY,
                                 C_FLOAT64 * pTime,
                                 C_FLOAT64 * pEndTime,
                                 const size_t rootCount,
                                 C_INT * pRoots,
                                 const RKMethodStatus & status,
                                 C_FLOAT64 * rtol,
                                 C_FLOAT64 * atol,
                                 unsigned C_INT32 * pMaxSteps,
                                 EvalDeriv pEvalDerivatives,
                                 EvalRoot pEvalRoots)
{
  if (pDim == NULL || *pDim <= 0) //check dimension
    {
      mErrorMessage << "Dimension of system should be POSITIVE" << std::endl;
      return false;
    }

  if (pTime == NULL)
    {
      mErrorMessage << "pTime must not be NULL" << std::endl;
      return false;
    }

  if (pEndTime == NULL)
    {
      mErrorMessage << "pEndTime must not be NULL" << std::endl;
      return false;
    }

  if (pY == NULL)
    {
      mErrorMessage << "pY must not be NULL" << std::endl;
      return false;
    }

  if (rtol != NULL && *rtol < 0)
    {
      mErrorMessage << "The relative tolerance must be nonnegative" << std::endl;
      return false;
    }

  if (atol != NULL && *atol < 0)
    {
      mErrorMessage << "The absolute tolerance must be nonnegative" << std::endl;
      return false;
    }

  if (pMaxSteps != NULL && *pMaxSteps <= 0)
    {
      mErrorMessage << "The max step size must be positive" << std::endl;
      return false;
    }

  if (*pEndTime <= *pTime)
    {
      mErrorMessage << "In this solver, we just support positive integration where stop time should be larger than start time!" << std::endl;
      return false;
    }

  if (pEvalDerivatives == NULL)
    {
      mErrorMessage << "Function that calculates derivatives should be set!" << std::endl;
      return false;
    }

  if (rootCount < 0)
    {
      mErrorMessage << "Root Number should be a non-negative integer!" << std::endl;
      return false;
    }

  if (rootCount > 0)
    {
      if (pRoots == NULL)
        {
          mErrorMessage << "pRoots must not be NULL" << std::endl;
          return false;
        }

      if (pEvalRoots == NULL)
        {
          mErrorMessage << "Function that calculates roots should be set!" << std::endl;
          return false;
        }
    }

  return true;
}

//***************************//
//* Other Helpful Functions *//
//***************************//

/**
 * Calculate infinity norm value
 */
C_FLOAT64 CRungeKutta::infNorm(const size_t &len, const C_FLOAT64 *y)
{
  C_FLOAT64 result, tmp;
  result = (y[0] >= 0) ? y[0] : -y[0];

  for (size_t i = 1; i < len; i++)
    {
      tmp = (y[i] >= 0) ? y[i] : -y[i];

      if (tmp > result)
        result = tmp;
    }

  return result;
}

/**
 * Calculate eps of a given value
 */
inline C_FLOAT64 CRungeKutta::deps(const C_FLOAT64 &x)
{
  return (x == 0) ? EPS0 : fabs(x) * EPS1;
}

/**
 * Clear queue that records roots
 */
