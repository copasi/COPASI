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

//

class COptProblem
  {
    //data member

  private:

    double * mParameterValues;        // pointer to parameters
    int mParameterNum;          // the number of parameters
    double mBestValue;          // the best result of the problem
    double * mParameterMin;     // the minimum values of parameters
    double * mParameterMax;     // the maximum values of parameters

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
     * set the minimum value of parameters
     */
    void setParameterMin(double * aDouble);

    /*
     * get the minimum value of parameters
     */
    double * getParameterMin();

    /*
     * set the maximum value of the paramters
     */
    void setParameterMax(double * aDouble);

    /*
     * get the maximum value of the parameters
     */
    double * getParameterMax();
  };

#endif  // the end
