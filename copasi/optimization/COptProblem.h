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
/*
#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
 */

class CSteadyStateTask;
class CTrajectoryTask;

using std::ofstream;

enum ProblemType
{
  SteadyState,
  Trajectory
};

class COptProblem
  {
    //data member

  private:
    double * mParameterValues;  // pointer to parameters
    int mParameterNum;          // the number of parameters
    double mBestValue;          // the best result of the problem
    double * mBestParameters;   // the parameters leading the best result
    double * mParameterMin;     // the minimum values of parameters
    double * mParameterMax;     // the maximum values of parameters
    /**
     * Pointer to CSteadyStateTask.  To be used in calculate() to select between
     * trajectory and steady state method
     */
    CSteadyStateTask * steady_state;
    /**
     * Pointer to CTrajectory.  To be used in calculate() to select between
     * trajectory and steady state method
     */
    CTrajectoryTask * trajectory;

    /**
     * This is not permanant !  this will change when CSS_Solution.process(&ofstream) 
     * changes to CSS_Solution.process().  delete this parameter when this change is comitted.
     */
    ofstream out;

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
     * @param source a COptProblem object for copy
     * @return an assigned COptProblem object
     */
    COptProblem& operator=(const COptProblem& source);

    /**
     * clean up memory
     */
    void cleanup(void);

    /**
     * Initialization of private variables
     */
    void initialize(void);

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

    /*
     * set the parameter values
     */
    void setParamterValues(double * aDouble);

    /**
     * get the parameter values
     */
    double * getParameterValues();

    /*
     * set a parameter
     */
    void setParameter(int aNum, double aDouble);

    /**
     * get a parameter
     */
    double getParameter(int aNum);

    /*
     * set parameter number
     */
    void setParameterNum(int aNum);

    /*
     * get parameter number
     */
    int getParameterNum();

    /*
     * set the best value
     */
    void setBestValue(double aDouble);

    /*
     * get the best value
     */
    double getBestValue();

    /*
     * set one parameter in the array of best values -- overloaded function
     */
    void setBestParameter(int i, double value);

    /*
     * get one parameter from the array -- overloaded function
     */
    double getBestValue(int i);

    /*
     * set the minimum value of parameters
     */
    void setParameterMin(double * aDouble);

    /*
     * set minimum value in an array
     */
    void setParameterMin(int, double);

    /*
     * get the minimum value of parameters
     */
    double * getParameterMin();

    /*
     * get minimum from array
     */
    double getParameterMin(int);

    /*
     * set the maximum value of the paramters
     */
    void setParameterMax(double * aDouble);

    /*
     * set maximum in an array
     */
    void setParameterMax(int, double);

    /*
     * get the maximum value of the parameters
     */
    double * getParameterMax();

    /*
     * get maximum value from array
     */
    double getParameterMax(int);

    /*
     * set problem type : Steady State or Trajectory
     * @param: ProblemType
     */
    void setProblemType(ProblemType);
  };

#endif  // the end
