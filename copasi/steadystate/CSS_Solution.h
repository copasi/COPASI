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

#include "trajectory/CTrajectory.h"
// #include <cmath>
#include "trajectory/Clsoda.h"

#define NEWTON 1;
#define TRAJ 2;
#define TRAJBACK 3;

//these defines are directly from GepasiDoc.h
#define SS_FOUND 0
#define SS_NOT_FOUND 1
#define SS_SINGULAR_JACOBIAN 2
#define SS_DAMPING_LIMIT 3
#define SS_ITERATION_LIMIT 4
#define MCA_OK 0
#define MCA_SINGULAR 1

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
   *  variable for steady-state solution
   */
  //C_FLOAT64 * mSs_x;

  /**
   *  variable for steady-state solution
   */
  //C_FLOAT64 * mSs_xnew;

  /**
   *  variable for steady-state solution
   */
  C_INT32 mSs_nfunction; 

  /**
   *  variable for steady-state solution
   *  its result is either SS_FOUND or SS_NOT_FOUND
   */
  C_INT32 mSs_solution;

  //more variables
  //C_FLOAT64 mNjeval;

  //C_FLOAT64 mNfeval;
  
  // C_INT32 mSs_njacob;

  /**
   *  The CTrajectory to work with
   */
  CTrajectory * mTraj;

  /**
   *  The option to choose from 1(NEWTON),2(TRAY), or 3(TRAJBACK)
   */
  C_INT32 mOption;
  //same as an int in GepasiDoc: int SSStrategy; // 0-normal 1-Integr.only 2-Newton only 3-back.integr.only




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
   *  to process the primary function of this class
   */
  void process(void);

  /**
   *  Analyze steady state
   */
  void steadyState(void);  

  /**
   *  Check if it is steady state
   *  @return an int acting like a bool
   */
  //C_INT32 isSteadyState( void );

};



#endif // COPASI_CSS_Solution
