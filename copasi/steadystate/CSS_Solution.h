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

#include <iostream>

#include "model/model.h"
#include "CNewton.h"
#include "CJacob.h"
#include "CEigen.h"
#include "trajectory/CTrajectory.h"

using std::ofstream;

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

class CNewton;

class CTrajectory;

class COutputEvent;

class CSS_Solution
  {
    //Attibutes

  private:

    /**
     *  variable for steady-state solution
     *  its result is either SS_FOUND or SS_NOT_FOUND
     */
    C_INT32 mSs_solution;

    /**
     * The steady state resolution
     */
    C_FLOAT64 mSSRes;

    /**
     *  Limit of iterations used by the Newton method
     */
    C_INT32 mNewtonLimit;

    /**
     *  The derivation factor used in the Jacobian
     */
    C_FLOAT64 mDerivFactor;

    /**
     *  Whether to use the Newton Method
     */
    C_INT32 mUseNewton;

    /**
     *  Whether to use the Integration Method
     */
    C_INT32 mUseIntegration;

    /**
     *  Whether to use the Back-Integration Method
     */
    C_INT32 mUseBackIntegration;

    /**
     *  The coordinats of the steady-state solution
     */
    C_FLOAT64 * mSs_x;

    /**
     *  The time derivative of the steady-state solution
     */
    TNT::Vector < C_FLOAT64 > mSs_dxdt;

    /**
     *  The CModel to work with
     */
    CModel * mModel;

    /**
     *  The CNewton to work with
     */
    CNewton * mNewton;

    /**
     *  The CTrajectory to work with
     */
    CTrajectory * mTraj;

    /**
     *  The CJacob to work with
     */
    CJacob * mJacob;

    /**
     *  The CEigen to work with
     */
    CEigen * mEigen;

    /**
     * SteadyState Output Event
     */
    COutputEvent *mSSOutput;
    //Operations

  public:

    /**
     * default constructor
     */
    CSS_Solution();

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
    void load(CReadConfig & configbuffer);

    /**
     *  Saves the parameters of the solver to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param configbuffer reference to a CWriteConfig object.
     *  @return mFail
     *  @see mFail
     */
    void save(CWriteConfig & configbuffer);

    /**
     *  Set whether to use the Newton Method
     *  @param "const C_INT32 &" useNewton
     */
    void setUseNewton(const C_INT32 & useNewton);

    /**
     *  Retreives whether to use the Newton Method
     *  @return "const C_INT32 &" useNewton
     */
    const C_INT32 & getUseNewton() const;

    /**
     *  Set whether to use the Integration Method
     *  @param "const C_INT32 &" useIntegration
     */
    void setUseIntegration(const C_INT32 & useIntegration);

    /**
     *  Retreives whether to use the Intgration Method
     *  @return "const C_INT32 &" useIntegration
     */
    const C_INT32 & getUseIntegration() const;

    /**
     *  Set whether to use the Back-Integration Method
     *  @param "const C_INT32 &" useBackIntegration
     */
    void setUseBackIntegration(const C_INT32 & useBackIntegration);

    /**
     *  Retreives whether to use the Back-Intgration Method
     *  @return "const C_INT32 &" useBackIntegration
     */
    const C_INT32 & getUseBackIntegration() const;

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
     *  get CNewton
     *  @return mNewton private member
     */
    CNewton * getNewton() const;

    /**
     *  get CEigen
     *  @return mEigen private member
     */
    CEigen * getEigen() const;

    /**
     *  get CTrajectory pointer
     *  @return mTraj
     */
    CTrajectory * getTrajectory() const;

    /**
     *  get mJacob
     *  @return mY_traj
     */
    CJacob * getJacob() const;

    /**
     *  get mSs_x
     *  @return mSs_x
     */
    const C_FLOAT64 * getSs_x() const;

    /**
     *  get mSs_dxdt
     *  @return mSs_dxdt
     */
    const TNT::Vector < C_FLOAT64 > & getSs_dxdt() const;

    /**
     *  get mSs_solution
     *  @return mSs_solution  WeiSun 03/27/02
     */
    C_INT32 getSolution() const;

    /**
     * Get the pointer of SSRes for output  WeiSun 04/02/02
     */
    void * getSSResAddr();

    /**
     * Get the pointer of DerivFactor for output WeiSun 04/02/02
     */
    void * getDerivFactorAddr();

    /**
     *  to process the primary function of this class
     */
    void process(ofstream &fout);

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
    C_INT32 isSteadyState();
  };

#endif // COPASI_CSS_Solution
