// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 *   CExpRKMethod
 *
 *   This class is the ODE solver in terms Ronge-Kutta Method ODE45
 *   
 *   File name: CExpRKMethod.h
 *   Author: Shuo Wang
 *   Email: shuowang.learner@gmail.com
 *
 *   Last change: 07, July 2014
 *
 */

#ifndef CEXPRKMETHOD
#define CEXPRKMETHOD

#include <iostream>
#include "copasi/utilities/CVersion.h"
#include "copasi.h"

#define MAX_STAGE 8
#define EPS1      2.220446049250313e-16
#define EPS0      4.940656458412465e-300

/**
 *Define function pointer of functions for computing derivative and 
 * event function
 * Parameters:
 * 1. C_FLOAT64 mT
 * 2. C_FLOAT64 mY
 * 3. size_t mRootNum
 * 4. C_FLOAT64 mRootValue
 */
typedef void (*pEvalRoot)(const size_t *, 
			  const C_FLOAT64 * , const C_FLOAT64 * ,
			  const size_t *, C_FLOAT64 * );

//Need static?
// Parameters:
// 1. C_FLOAT64 mT
// 2. C_FLOAT64 mY
// 3. C_FLOAT64 Yp
typedef void (*pEvalDeriv)(const size_t *, const C_FLOAT64 *, 
			   const C_FLOAT64 *, C_FLOAT64 * );

/**
 * A simple structure recording root id and firing time t
 */
struct SRoot
{
  int id;
  C_FLOAT64 t;
};

/**
 * Comparing function for quick sort
 */
int compare(const void *r1, const void *r2);

class CExpRKMethod
{
  /*============Functions============*/
public:

  //*********************************//
  //* Constructor and Destructor    *//
  //*********************************//

  /**
   * Default constructor
   */
  CExpRKMethod();

  /**
   * Default destructor
   */
  ~CExpRKMethod();

  //*************************//
  //* Main Process Function *//
  //*************************//

  /**
   * Main function processing integration along time 
   */
  void integrate();

private:

  /**
   * Check status of this ODE solver
   */
  void checkODEState();

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
  void initialize();

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
   * Locate roots
   */
  void findRoots();

  /**
   * Locate roots in terms of Secant Method
   */
  C_FLOAT64 rootFindBySecant(const size_t id, const C_FLOAT64 leftT, const C_FLOAT64 leftV,
                             const C_FLOAT64 rightT, const C_FLOAT64 rightV);

  /**
   * Locate roots in terms of Bisection Method
   */
  C_FLOAT64 rootFindByBisection(const size_t id, const C_FLOAT64 leftT, const C_FLOAT64 leftV,
                             const C_FLOAT64 rightT, const C_FLOAT64 rightV);

  /**
   * Locate roots in terms of Falsi Method
   */
  C_FLOAT64 rootFindByFalsi(const size_t id, const C_FLOAT64 leftT, const C_FLOAT64 leftV,
                             const C_FLOAT64 rightT, const C_FLOAT64 rightV);

  /**
   * Check whether a slow function fired in this step
   */
  void findSlowReaction();

  /**
   * Interpolation system state at given root
   */
  void calculateRootState();

  //*****************************//
  //* Parameters Check Function *//
  //*****************************//
  /**
   * Check parameters used in the integration
   */
  void checkParameter();


  //***************************//
  //* Other Helpful Functions *//
  //***************************//
  /**
   * Calculate infinity norm value
   */
  C_FLOAT64 infNorm(const size_t &, const C_FLOAT64*);

  /**
   * Calculate the maxinum element of an array
   */
  C_FLOAT64 dmax(const C_FLOAT64&, const C_FLOAT64&);

  /**
   * Calculate the minimum element of an array
   */
  C_FLOAT64 dmin(const C_FLOAT64&, const C_FLOAT64&);

  /**
   * Calculate absolute value
   */
  C_FLOAT64 dabs(const C_FLOAT64&);

  /**
   * Calculate eps of a given value
   */
  C_FLOAT64 deps(const C_FLOAT64&);

  /**
   * Clear queue that records roots
   */
  void clearQueue();

  /**
   * Check whether a queue is empty
   */
  bool queueIsEmpty();

  /**
   * Pop the first element in the queue
   */
  void queuePop();

  /**
   * Push an element into the queue
   */
  void queuePush(const SRoot&);

  /**
   * Shrink the queue which just contains only one root for
   * each event
   */
  void shrinkQueue();

  /*============Attributes============*/

  //*****************************************//
  //* Attributs that should be set by users *//
  //*****************************************//
 public:
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //~~~~~~~~Input Parameters~~~~~~~~
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  /**
   * mDim, dimension of this problem
   */
  size_t *mDim;

  /**
   * mRootNum, a size_t variable, number of roots
   */
  size_t mRootNum;

  /**
   * mAbsTol, absolute error tolerance 
   * mRelTol. relative error tolerance
   */ 
  C_FLOAT64 mAbsTol;
  C_FLOAT64 mRelTol;

  /**
   * mTEnd, terminal time this solver will reach
   */
  C_FLOAT64 mTEnd;

  /**
   * mDerivFunc, function pointer of function calculating
   *             derivatives
   */
  pEvalDeriv mDerivFunc;

  /**
   * mEventFunc, function pointer of function calculating
   *             event values
   */
  pEvalRoot mEventFunc;


  /**
   * mHybrid, a boolean variable
   * mHybrid == false, a regular ODE solver
   * mHybrid == true,  providing inverse interpolation for hybrid method
   */
  bool mHybrid;

  
  /**
   * mStatic, a boolean variable 
   * mStatic == 1, write statistic results into a txt file
   * mStatic == 0, do not output statistic results
   */
  bool mStatis;

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //~~~~~~~~Output Parameters~~~~~~~~~
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  /**
   * mRootId, a size_t variable indicating which root is found
   *          0 <= mRootId <= mRootNum-1
   */
  int mRootId;


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //~~~~~~~~Input and Output Parameters~~~~~~~~
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  /**
   * mT, current time
   */
  C_FLOAT64 mT;

  /**
   * mY, a C_FLOAT64 pointer pointing to an array recording 
   *     system values at privous step
   */
  C_FLOAT64 *mY;

  /**
   * mODEState, an int varialbe, recording the state of the solver
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
  int mODEState;


  
 private:
  //**********************************************//
  //* Variables recording system states          *//
  //**********************************************//
  
  /**
   * mODEStateRecord, recording state of mODEState 
   * before return, in usage of checking correctness
   * of mODEState setting at the initial step
   */
  int mODEStateRecord;

  /**
   * mInitTCp, copy of initial time
   */
  C_FLOAT64 mInitTCp;

  /**
   * mTNew, new time in the next step
   */
  C_FLOAT64 mTNew;
  C_FLOAT64 mTOld;

  /**
   * mYNew, a C_FLOAT64 pointer pointing to an array recording
   *        system values at new step
   */
  C_FLOAT64 *mYNew;

  /**
   * mYOld, a C_FLOAT64 pointer pointing to an array recording 
   *        mY
   */ 
  C_FLOAT64 *mYOld;

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
   * mFacMaxRej, maxmum factor value after a rejected step
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

  /**
   * mHasEvent, a boolean variable
   * mHasEvent == true,  mEventFunc != NULL
   * mHasEvent == false, mEventFunc == NULL
   */
  bool mHasEvent;

  
  //********************************************//
  //* Integration process statistic variables  *//
  //********************************************//
  
  /**
   * mStepNum, a size_t variable, recording how many steps are executed
   */
  size_t mStepNum;

  /**
   * mAcceptNum, a size_t varialbe, recording how many successful steps
   */
  size_t mAcceptNum;

  /**
   * mRejectNum, a size_t varialbe, recording how many rejected steps
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

 private:
  /**
   * mRootQueue, a queue of struct SRoot, which recording
   * root index and corresponding time, in a time ascending 
   * order
   */
  SRoot *mRootQueue;

  size_t mQueueLen;
  size_t mQueueSite;

  /**
   * mI, a two dimension C_FLOAT64 array, for interpolation 
   */
  C_FLOAT64 mI[MAX_STAGE][MAX_STAGE];

  /**
   * mRootValueOld, a C_FLOAT64 array pointer, recording root values
   *                at previous step
   */
  C_FLOAT64 *mRootValueOld;

  /**
   * mRootValue, a C_FLOAT64 array pointer, recording root value at
   *             current time mT
   */
  C_FLOAT64 *mRootValue;
  

  /**
   * mOrderY, the order of Y interpolation can achieve
   */
  size_t mOrderY;

  /**
   * mOrderYp, the order of Y prime interpolation can achieve
   */
  size_t mOrderYp;

  /**
   * mHasMutipleRoots, indicates whether there are multiple roots found in one step
   */
  bool mHasMultipleRoots;

  
  //************************//
  //* Some Other Attributs *//
  //************************//
  C_FLOAT64 *mZ1, *mZ2, *mZ3;

  C_FLOAT64 *mIn1, *mIn2, *mIn3, *mtArray;

  bool mFindRoots, mFindSlow;

};


#endif 
