/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptProblem.h,v $
   $Revision: 1.18 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:25:25 $
   End CVS Header */

/**
 *  File name: COptProblem.h
 *
 *  Programmer: Yongqun He
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the header file of the COptProblem class.
 *           It specifies the optimization problem with its own members and
 *           functions. It's used by COptAlgorithm class and COptimization class
 */

#ifndef COPTPROBLEM_H
#define COPTPROBLEM_H

#include <string>
#include <copasi.h>
#include <vector>

#include "utilities/CVector.h"
#include "utilities/CMethodParameterList.h"
#include "utilities/CCopasiVector.h"

class CSteadyStateTask;
class CTrajectoryTask;

enum ProblemType
{
  SteadyState,
  Trajectory
};

/** @dia:pos -4.4,4.15 */
class COptProblem
  {
    //data member
  private:

    CCopasiVectorNS < CMethodParameterList > mOptItemList;

    /**
     * The best result of the problem
     */
    C_FLOAT64 mBestValue;

    /**
     * The paramters for wich the optimization function has to be calculated
     */
    CVector< C_FLOAT64 > mParameter;

    /**
     * The minimum values of the parameters
     */
    CVector< C_FLOAT64 > mParameterMin;

    /**
     * The maximum values of the parameters
     */
    CVector< C_FLOAT64 > mParameterMax;

    /**
     * The parameters leading to the best result
     */
    CVector< C_FLOAT64 > mBestParameter;

    /**
     * Pointer to CSteadyStateTask.  To be used in calculate() to select between
     * trajectory and steady state method
     */
    CSteadyStateTask * mpSteadyState;

    /**
     * Pointer to CTrajectory.  To be used in calculate() to select between
     * trajectory and steady state method
     */
    CTrajectoryTask * mpTrajectory;

    // Implementation
  public:

    /**
     * Default constructor
     */
    COptProblem();

    /**
     * Destructor
     */
    virtual ~COptProblem();

    /**
     * Copy constructor
     * @param source a COptProblem object for copy
     */
    COptProblem(const COptProblem& source);

    /**
     * Object assignment overloading
     * @param const COptProblem& src
     * @return COptProblem & *this
     */
    COptProblem& operator=(const COptProblem& src);

    /**
     * calculate function for optimization
     */
    virtual C_FLOAT64 calculate();

    /**
     * calculate function for optimization
     */
    virtual bool checkParametricConstraints();

    /**
     * calculate function for optimization
     */
    virtual bool checkFunctionalConstraints();

    /**
     * get the parameter values
     */
    CVector< C_FLOAT64 > & getParameter();

    /*
     * set a parameter
     */
    void setParameter(C_INT32 aNum, C_FLOAT64 aDouble);

    /**
     * get a parameter
     */
    C_FLOAT64 getParameter(C_INT32 aNum);

    /*
     * set parameter number
     */
    void setParameterNum(C_INT32 aNum);

    /*
     * get parameter number
     */
    C_INT32 getParameterNum();

    /*
     * set the best value
     */
    void setBestValue(C_FLOAT64 aDouble);

    /*
     * get the best value
     */
    C_FLOAT64 getBestValue();

    /*
     * set one parameter in the array of best values -- overloaded function
     */
    void setBestParameter(C_INT32 i, C_FLOAT64 value);

    /*
     * get the best value parameters
     */
    CVector< C_FLOAT64 > & getBestParameter();

    /*
     * get one parameter from the array -- overloaded function
     */
    C_FLOAT64 getBestValue(C_INT32 i);

    /*
     * set minimum value in an array
     */
    void setParameterMin(C_INT32, C_FLOAT64);

    /*
     * get the minimum value of parameters
     */
    CVector< C_FLOAT64 > & getParameterMin();

    /*
     * get minimum from array
     */
    C_FLOAT64 getParameterMin(C_INT32);

    /*
     * set maximum in an array
     */
    void setParameterMax(C_INT32, C_FLOAT64);

    /*
     * get the maximum value of the parameters
     */
    CVector< C_FLOAT64 > & getParameterMax();

    /*
     * get maximum value from array
     */
    C_FLOAT64 getParameterMax(C_INT32);

    /*
     * set problem type : Steady State or Trajectory
     * @param: ProblemType
     */
    void setProblemType(ProblemType);
  };

#endif  // the end
