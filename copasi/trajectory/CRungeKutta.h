// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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
 *   This class is the ODE solver in terms Runge-Kutta Method ODE45
 *
 *   File name: CRungeKutta.h
 *   Author: Shuo Wang
 *   Email: shuowang.learner@gmail.com
 *
 *   Last change: 07, July 2014
 *
 */

#ifndef COPASI_CRingeKutta
#define COPASI_CRingeKutta

#include <sstream>

#include "copasi/core/CVector.h"
#include "copasi/utilities/CBrent.h"

#define MAX_STAGE 8
#define EPS1      2.220446049250313e-16
#define EPS0      4.940656458412465e-300

/**
 * Callback function to evaluate root values for a given state
 * @param const size_t * pStateSize
 * @param const C_FLOAT64 * pTime
 * @param const C_FLOAT64 * pStateVariables,
 * @param const size_t * pRootSize,
 * @param C_FLOAT64 * pRoots
 */
typedef void (*EvalRoot)(const size_t *, const C_FLOAT64 * , const C_FLOAT64 * , const size_t *, C_FLOAT64 *);

/**
 * Callback function to evaluate derivatives for a given state
 * @param const size_t * pStateSize
 * @param const C_FLOAT64 * pTime
 * @param const C_FLOAT64 * pStateVariables,
 * @param C_FLOAT64 * pDerivatives
 */
typedef void (*EvalDeriv)(const size_t *, const C_FLOAT64 *, const C_FLOAT64 *, C_FLOAT64 *);

class CRungeKutta
{
  /*============Functions============*/
public:

  enum RKMethodStatus
  {
    INITIALIZE, // ODE solver is called firstly, need to be initialized
    RESTART, // ODE solver starts a new integration, without initialization
    CONTINUE, // ODE solver continues integration, coming back from event
    ROOTFOUND, // ODE solver stops at time t < tEnd, indicating having found roots
    END, // ODE solver finishes integration at t == tEnd*
    ERROR // some errors happened
  };

  //*********************************//
  //* Constructor and Destructor    *//
  //*********************************//

  /**
   * Default constructor
   */
  CRungeKutta();

  /**
   * Default destructor
   */
  ~CRungeKutta();

  /**
   * Do an integration step from the current state (pY, pTime) to the end time pEndTime
   * @param const size_t * pDim,
   * @param C_FLOAT64 * pY,
   * @param C_FLOAT64 * pTime,
   * @param C_FLOAT64 * pEndTime,
   * @param const size_t rootCount,
   * @param C_INT * pRoots,
   * @param const RKMethodStatus & status,
   * @param C_FLOAT64 * rtol,
   * @param C_FLOAT64 * atol,
   * @param EvalDeriv pEvalDerivatives,
   * @param EvalRoot pEvalRoots
   * @return RKMethodStatus status
   */
  RKMethodStatus operator()(const size_t * pDim,
                            C_FLOAT64 * pY,
                            C_FLOAT64 * pTime,
                            C_FLOAT64 * pEndTime,
                            const size_t rootCount,
                            C_INT * pRoots,
                            const RKMethodStatus & status,
                            const bool & oneStep,
                            C_FLOAT64 * rtol,
                            C_FLOAT64 * atol,
                            unsigned C_INT32 * pMaxSteps,
                            EvalDeriv pEvalDerivatives,
                            EvalRoot pEvalRoots);

  std::string getErrorMesssage() const;

private:

  /**
   * Check status of this ODE solver
   */
  bool checkODEState(const RKMethodStatus & status);

  /**
   * Integral one step along time
   */
  void doOneStep();

  /**
   * Estimate error after executing one step
   * If error is less than given tolerance, result is accept.
   * Else, re-integral this step
   */
  C_FLOAT64 estimateError();

  /**
   * Update time, results and other necessary stuff
   */
  void advanceStep();

  //***************************************//
  //* Functions for System Initialization *//
  //***************************************//
  /**
   * Initialize all the stuff used in this class
   */
  void initialize(const size_t * pDim,
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
                  EvalRoot pEvalRoots);

  /**
   * Allocate space for arrays used
   */
  void allocateSpace();

  /**
   * Set coefficients for ODE45
   */
  void setCoeff();

  /**
   * Set statistic parameters
   */
  void setStatRecord();

  //***********************************//
  //* Functions for step size control *//
  //***********************************//

  /**
   * Set initial step size of integrator
   */
  void setInitialStepSize();

  //*****************************//
  //* Function for Root Finder  *//
  //*****************************//

  /**
   * Do interpolation at given time
   */
  void interpolation(const C_FLOAT64, C_FLOAT64 *);

  /**
   * Check whether there is a root
   */
  void checkRoots();

  /**
   * Calculate the maximum root value for the given time for all
   * roots changing sign between mRootValueLeft and mRootValueRight.
   * rootValue is a continuous function which is positive at the right
   * and negative at the left.
   * @param const C_FLOAT64 & time
   * @return const C_FLOAT64 rootValue
   */
  C_FLOAT64 rootValue(const C_FLOAT64 & time);

  //*****************************//
  //* Parameters Check Function *//
  //*****************************//
  /**
   * Check parameters used in the integration
   */
  bool checkParameter(const size_t * pDim,
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
                      EvalRoot pEvalRoots);

  //***************************//
  //* Other Helpful Functions *//
  //***************************//
  /**
   * Calculate infinity norm value
   */
  C_FLOAT64 infNorm(const size_t &, const C_FLOAT64*);

  /**
   * Calculate eps of a given value
   */
  C_FLOAT64 deps(const C_FLOAT64&);

  /*============Attributes============*/

  //*****************************************//
  //* Attributes that should be set by users *//
  //*****************************************//
private:
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //~~~~~~~~Input Parameters~~~~~~~~
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  /**
   * mDim, dimension of this problem
   */
  const size_t * mpDim;

  /**
   * mRootNum, a size_t variable, number of roots
   */
  size_t mRootNum;
  CVectorCore< C_INT > mRootFound;

  /**
   * mAbsTol, absolute error tolerance
   * mRelTol. relative error tolerance
   */
  C_FLOAT64 mAbsTol;
  C_FLOAT64 mRelTol;
  unsigned C_INT32 mMaxSteps;

  /**
   * mTEnd, terminal time this solver will reach
   */
  C_FLOAT64 mTEnd;

  /**
   * mpDerivFunc, function pointer of function calculating
   *             derivatives
   */
  EvalDeriv mpDerivFunc;

  /**
   * mpEventFunc, function pointer of function calculating
   *             event values
   */
  EvalRoot mpEventFunc;

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //~~~~~~~~Output Parameters~~~~~~~~~
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //~~~~~~~~Input and Output Parameters~~~~~~~~
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  /**
   * mY, a C_FLOAT64 pointer pointing to an array recording
   *     system values at previous step
   */
  C_FLOAT64 * mpY;

  /**
   * mODEState, an int variable, recording the state of the solver
   * Input:
   *   mODEState == 0, ODE solver is called firstly, need to be initialized
   *   mODEState == 1, ODE solver starts a new integration, without initialization
   *   mODEState == 2, ODE solver continues integration, coming back from event
   *                   has been found
   *
   * Output:
   *   mODEState == -2, some errors happened
   *   mODEState == 3, ODE solver stops at time t < tEnd, indicating having events
   *   mODEState == 4, ODE solver finishes integration at t == tEnd;
   */
  RKMethodStatus mMethodStatus;
  bool mContinueFromInterpolation;

  //**********************************************//
  //* Variables recording system states          *//
  //**********************************************//

  /**
   * mTNew, new time in the next step
   */
  C_FLOAT64 mTRight;
  C_FLOAT64 mTLeft;

  /**
   * mYNew, a C_FLOAT64 pointer pointing to an array recording
   *        system values at new step
   */
  C_FLOAT64 *mYRight;

  /**
   * mYOld, a C_FLOAT64 pointer pointing to an array recording
   *        mY
   */
  C_FLOAT64 *mYLeft;

  //***********************************************************//
  //* Some coefficients should be set for process of one step *//
  //* calculation, according to formula                       *//
  //*    ki = f(t_n + c_i*h, y)n + h*(sum a_ij*k_j))          *//
  //*    y_n+1 = y_n + h*(sum b_i*k_i)                        *//
  //*                                                         *//
  //* Absolute local error of one step is calculated as       *//
  //*    absErr = h * (sum e_i*k_i)                           *//
  //***********************************************************//

  /**
   * mP, the order this solver provides
   */
  size_t mP;

  /**
   * mStage, the stage of this method
   */
  size_t mStage;

  /**
   * mA, a C_FLOAT64 two dimension array, recording
   *     coefficients a_ij
   */
  C_FLOAT64 mA[MAX_STAGE][MAX_STAGE];

  /**
   * mB, a C_FLOAT64 array, recording coefficients b_i
   */
  C_FLOAT64 mB[MAX_STAGE];

  /**
   * mC, a C_FLOAT64 array, recording coefficients c_i
   */
  C_FLOAT64 mC[MAX_STAGE];

  /**
   * mE, a C_FLOAT64 array, recording coefficients e_i
   *     for absolute error calculation
   */
  C_FLOAT64 mE[MAX_STAGE];

  /**
   * mK, a C_FLOAT64 pointer of a two dimension array, recording
   *     approximated derivatives (mStage*mDim)
   */
  C_FLOAT64 **mK;

  //*********************************************************//
  //* Step size h, and step size control related parameters *//
  //*********************************************************//

  /**
   * mh, step size
   */
  C_FLOAT64 mh;

  /**
   * mhMin, minimum step size
   */
  C_FLOAT64 mhMin;

  /**
   * mhMax, maximum step size
   */
  C_FLOAT64 mhMax;

  /**
   * mFac, a number as a factor for step size control
   */
  C_FLOAT64 mFac;

  /**
   * mFacMin, minimum factor value
   */
  C_FLOAT64 mFacMin;

  /**
   * mFacMax, maximum factor value
   */
  C_FLOAT64 mFacMax;

  /**
   * mFacMaxRej, maximum factor value after a rejected step
   */
  C_FLOAT64 mFacMaxRej;

  //*********************************************************//
  //* Some state records, for usage of ODE solver control   *//
  //*********************************************************//

  /**
   * mhNoFailed, a boolean variable
   * mhNoFailed == true, success after a reject step
   * mhNoFailed == false, previous step is accepted
   */
  bool mhNoFailed;

  //********************************************//
  //* Integration process statistic variables  *//
  //********************************************//

  /**
   * mStepNum, a size_t variable, recording how many steps are executed
   */
  size_t mStepNum;

  /**
   * mAcceptNum, a size_t variable, recording how many successful steps
   */
  size_t mAcceptNum;

  /**
   * mRejectNum, a size_t variable, recording how many rejected steps
   */
  size_t mRejectNum;

  /**
   * mfEvalNum, a size_t variable, recording how many times mDerivFunc
   *            are called
   */
  size_t mfEvalNum;

  /**
   * mrEvalNum, a size_t variable, recording how many times mEventFunc
   *            are called
   */
  size_t mrEvalNum;

  //******************************************//
  //* Variables for Root Finding functions   *//
  //******************************************//

  /**
   * mI, a two dimension C_FLOAT64 array, for interpolation
   */
  C_FLOAT64 mI[MAX_STAGE][MAX_STAGE];

  /**
   * mRootValueLeft, a C_FLOAT64 array pointer, recording root values
   * at previous step
   */
  C_FLOAT64 *mRootValuesLeft;

  /**
   * mRootValueRight, a C_FLOAT64 array pointer, recording root value at
   * current time mT
   */
  C_FLOAT64 *mRootValueRight;

  /**
   * mRootValueRight, a C_FLOAT64 array pointer, recording root value at
   * current time mT
   */
  C_FLOAT64 *mRootValueTmp;

  /**
   * Pointer to method used for function evaluations for the Brent root finding method.
   */
  CBrent::Eval * mpRootValueCalculator;

  /**
   * mOrderY, the order of Y interpolation can achieve
   */
  size_t mOrderY;

  /**
   * mOrderYp, the order of Y prime interpolation can achieve
   */
  size_t mOrderYp;

  //************************//
  //* Some Other Attributes *//
  //************************//
  C_FLOAT64 *mZ1, *mZ2, *mZ3;

  std::stringstream mErrorMessage;
};

#endif // COPASI_CRingeKutta
