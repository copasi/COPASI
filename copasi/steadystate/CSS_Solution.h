/**
 *  File name: CSS_Solution.h
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the .h file for the class CSS_Solution. 
 *           It is to solve the steady state solution problem with different approaches,
 *           e.g., (1) Newton, (2) Integration (Trajectory), (3) Newton + Integration,
 *           (4) Backward Integration, (5) Backward integration if all else fails.
 */


#ifndef COPASI_CSS_Solution
#define COPASI_CSS_Solution

#include "copasi.h"
#include "model/model.h"
#include "CNewton.h"
#include "CJacob.h"
#include "CEigen.h"

#include "trajectory/CTrajectory.h"
// #include <cmath>
#include "trajectory/Clsoda.h"

//#define NEWTON 1;
//#define TRAJ 2;
//#define TRAJBACK 3;

//these defines are directly from GepasiDoc.h
//#define SS_FOUND 0
//#define SS_NOT_FOUND 1
//YH: change the #define value for easy condition evalution
//#define SS_FOUND 1
//#define SS_NOT_FOUND 0              //declare in copasi.h file


//#define SS_SINGULAR_JACOBIAN 2
//#define SS_DAMPING_LIMIT 3
//#define SS_ITERATION_LIMIT 4
//#define MCA_OK 0
//#define MCA_SINGULAR 1              //declare in copasi.h file

/**
 * These are from CNewton.h
 */
#define DefaultNewtonLimit 1
//Note: they may not be 1.0, check where it comes from orignially (Y.H.)
#define DefaultSSRes 1.0 
#define DefaultDerivFactor 1.0

class CNewton;
class CTrajectory;

class CSS_Solution
{
  //Attibutes
 private:

  /**
   *  The CModel to work with
   */
  CModel * mModel;

  /**
   *  The CNewton to work with
   */
  CNewton * mNewton;

  /**
   *  The CEigen to work with
   */
  CEigen * mEigen;

  /**
   *  variable for steady-state solution
   */
  C_FLOAT64 * mSs_x; 

  /**
   *  variable for steady-state solution
   */
  C_FLOAT64 * mY_traj;

  /**
   *  variable for steady-state solution
   */
  TNT::Vector < C_FLOAT64 > mSs_dxdt;

  /**
   * The steady state resolution
   */
  C_FLOAT64 mSSRes;


  // variables for steady-state solution
  //add more variables here

  /**
   *  variable for steady-state solution
   */
  C_INT32 mSs_nfunction; 

  /**
   *  variable for steady-state back integer
   */
  C_INT32 mSSBackInt; 

  /**
   *  The flux of the reaction
   */
  C_FLOAT64 mFlux;

  /**
   *  variable for steady-state solution
   *  its result is either SS_FOUND or SS_NOT_FOUND
   */
  C_INT32 mSs_solution;

  C_FLOAT64 mDerivFactor;

  //more variables
  C_FLOAT64 mNjeval;

  C_FLOAT64 mNfeval;
  
  C_INT32 mSs_njacob;

  /**
   *  The CTrajectory to work with
   */
  CTrajectory * mTraj;

  /**
   *  The CJacob to work with
   */
  CJacob * mJacob;

  /**
   *  The option to choose from 0-normal 1-Integr.only 2-Newton only 3-back.integr.only
   */
  C_INT32 mOption;
  //same as an int in GepasiDoc: int SSStrategy;




  //Operations
 public:


  /**
   * default constructor 
   */
  CSS_Solution();

  /**
   * copy constructor 
   * @param source a CSS_Solution object for copy
   */
  CSS_Solution(const CSS_Solution& source);

  /**
   * Object assignment overloading 
   * @param source a CSS_Solution object for copy
   * @return an assigned CSS_Solution object
   */
  CSS_Solution& operator=(const CSS_Solution& source);

  /**
   *  destructor
   */
  ~CSS_Solution();

  /**
   *  initialize()
   */
  void initialize();

  /**
   * Clean up internal pointer variables
   */
  void cleanup(void);

  /**
   *  Loads parameters for this solver with data coming from a 
   *  CReadConfig object. (CReadConfig object reads an input stream)
   *  @param configbuffer reference to a CReadConfig object.
   *  @return mFail
   *  @see mFail
   */
  C_INT32 load(CReadConfig & configbuffer);

  /**
   *  Saves the parameters of the solver to a CWriteConfig object.
   *  (Which usually has a file attached but may also have socket)
   *  @param configbuffer reference to a CWriteConfig object.
   *  @return mFail
   *  @see mFail
   */
  C_INT32 save(CWriteConfig & configbuffer);

  /**
   *  set mOption
   *  @param anOption that's an int
   */
  void setOption(C_INT32 anOption);

  /**
   * get option
   * @return int mOption 
   */
  C_INT32 getOption() const;


  /**
   * set mSSRes
   * @param aDouble a double value 
   */
  void setSSRes(C_FLOAT64 aDouble);

  /**
   * get mSSRes
   * @return int mOption 
   */
  C_FLOAT64 getSSRes() const;


  /**
   *  Sets the flux of the reaction
   *  @param C_FLOAT64 flux
   */
  //void setFlux(C_FLOAT64 flux);

  /**
   *  Retrieves the flux of the reaction
   *  @return C_FLOAT64
   */
  //C_FLOAT64 getFlux() const;

  /**
   *  set CModel
   *  @param aModel is the CModel set as mModel
   */
  void setModel(CModel * aModel);

  /**
   *  get CModel
   *  @return mModel
   */
  CModel * getModel() const;

  /**
   *  set CNewton
   *  @param aNewton, CNewton pointer to be set as mNewton
   */
  void setNewton(CNewton * aNewton);

  /**
   *  get CNewton
   *  @return mNewton private member
   */
  CNewton * getNewton() const;

  /**
   *  set CEigen
   *  @param aEigen, CNewton pointer to be set as mNewton
   */
  void setEigen(CEigen * aEigen);

  /**
   *  get CEigen
   *  @return mEigen private member
   */
  CEigen * getEigen() const;

  /**
   *  set CTrajectory pointer
   *  @param aTraj, a CTrajectory pointer to be set as mTraj
   */
  void setTrajectory(CTrajectory * aTraj);

  /**
   *  get CTrajectory pointer
   *  @return mTraj
   */
  CTrajectory * getTrajectory() const;

  /**
   *  set mY_traj
   *  @param aXnew is the double to be set as mY_traj
   */
  void setY_traj(C_FLOAT64 * aY);

  /**
   *  get mY_traj
   *  @return mY_traj
   */
  C_FLOAT64 * getY_traj() const;

  /**
   *  set mJacob
   *  @param aJ is the CJocob pointer to be set as mJacob
   */
  void setJacob(CJacob * aJ);

  /**
   *  get mJacob
   *  @return mY_traj
   */
  CJacob * getJacob() const;

  /**
   *  set mXx_x
   *  @param aX is the double to be set as mXx_s
   */
  void setSs_x(C_FLOAT64 * aX);

  /**
   *  get mSs_x
   *  @return mSs_x
   */
  C_FLOAT64 * getSs_x() const;

  /**
   *  get mSs_dxdt
   *  @return mSs_dxdt
   */
  const TNT::Vector < C_FLOAT64 > & getSs_dxdt() const;


  /**
   *  to process the primary function of this class
   */
  void process(void);


  /**
   *  Process after the steady state is found
   */
  void afterFindSteadyState();

  /**
   *  Analyze steady state
   */
  void steadyState(void);  

  /**
   *  Check if it is steady state
   *  @return an int acting like a bool
   */
  //C_INT32 isSteadyState( void );

  
  /**
   *  Check if it is steady state after processing trajectory
   *  It's based on if (mY[i]-mY_old[i])/delta(t) < mSSRes
   *  @return an int acting like a bool
   */
  C_INT32 isSteadyStateAfterTrajectory();

};



#endif // COPASI_CSS_Solution













