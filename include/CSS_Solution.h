/**
  CSS_Solution.h

 */

#ifndef CSS_Solution_H
#define CSS_Solution_H

#include "CNewton.h"
#include "CTrajectory.h"
#include <cmath>
#include "Clsoda.h"

using namespace std;

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

typedef bool BOOL; // this one should be declared somewhere else

class CSS_Solution
{
//Attibutes
private:

    /**
     *  The CModel to work with
     */
     CModel * mModel;


     //ss_x = new double[Model.TotMetab+1]; 
     //ss_xnew = new double[Model.TotMetab+1];    
    /**
     *  The CNewton to work with
     */
     CNewton * mNewton;

    /**
     *  variable for steady-state solution
     */
     C_FLOAT64 * mSs_x;

    /**
     *  variable for steady-state solution
     */
     C_FLOAT64 * mSs_xnew;

    /**
     *  variable for steady-state solution
     */
     C_INT32 mSs_nfunction; 

     //more variables
     C_FLOAT64 mNjeval;

     C_FLOAT64 mNfeval;
  
     C_INT32 mSs_njacob;

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
     void SetOption(C_INT32 anOption);

    /**
     * get option
     * @return int mOption 
     */
     C_INT32 GetOption() const;

    /**
     *  set CModel
     *  @param aModel is the CModel set as mModel
     */
     void SetModel(CModel * aModel);

    /**
     *  get CModel
     *  @return mModel
     */
     CModel * GetModel() const;

    /**
     *  set CNewton
     *  @param aNewton, CNewton pointer to be set as mNewton
     */
     void SetNewton(CNewton * aNewton);

    /**
     *  get CNewton
     *  @return mNewton private member
     */
     CNewton * GetNewton() const;

    /**
     *  set CTrajectory pointer
     *  @param aTraj, a CTrajectory pointer to be set as mTraj
     */
     void SetTrajectory(CTrajectory * aTraj);

    /**
     *  get CTrajectory pointer
     *  @return mTraj
     */
     CTrajectory * GetTrajectory() const;

    /**
     *  to process the primary function of this class
     */
     void Process(void);

    /**
     *  Analyze steady state
     */
     void SteadyState(void);  

    /**
     *  Check if it is steady state
     *  @return an int acting like a bool
     */
     C_INT32 IsSteadyState( void );

    /**
    * returns the largest value in a vector
    * @param mtm is a pointer to ??????
    */
    C_FLOAT64 SS_XNorn( C_FLOAT64 *mtx );

};



#endif  //CSS_Solution_H
