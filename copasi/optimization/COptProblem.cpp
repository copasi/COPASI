/**
 *  File name: COptProblem.cpp
 *
 *  Programmer: Yongqun He
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the source file of the COptProblem class.
 *           It specifies the optimization problem with its own members and
 *           functions. It's used by COptAlgorithm class and COptimization class
 */

#include "COptProblem.h"

//  Default constructor
COptProblem::COptProblem()
{
  mParameterValues = NULL;
  mParameterNum = 0;
  mBestValue = 0.0;
  mBestParameters = NULL;   // array of best values
  mParameterMin = NULL;     // the minimum values of parameters
  mParameterMax = NULL;     // the maximum values of parameters
  initialize();
}

// Destructor
COptProblem::~COptProblem()
{ }

// copy constructor
COptProblem::COptProblem(const COptProblem& source)
{
  // :TODO: this is broken !!!
  mParameterValues = source.mParameterValues;
  mParameterNum = source.mParameterNum;
  mBestValue = source.mBestValue;
  mBestParameters = source.mBestParameters;
  mParameterMin = source.mParameterMin;     // the minimum values of parameters
  mParameterMax = source.mParameterMax;
}

// Object assignment overloading,
COptProblem & COptProblem::operator = (const COptProblem& source)
{
  cleanup();

  if (this != &source)
    {
      mParameterValues = source.mParameterValues;
      mParameterNum = source.mParameterNum;
      mBestValue = source.mBestValue;
      mBestParameters = source.mBestParameters;
      mParameterMin = source.mParameterMin;     // the minimum values of parameters
      mParameterMax = source.mParameterMax;
    }

  return *this;
}

//clean up memory
void COptProblem::cleanup(void)
{
  pfree(mParameterValues);
  pfree(mBestParameters);
  pfree(mParameterMin);
  pfree(mParameterMax);
}

//  Initialization of private variables
void COptProblem::initialize(void)
{
  cleanup();

  mParameterValues = new double[mParameterNum];
  mBestParameters = new double[mParameterNum];
  mParameterMin = new double[mParameterNum];
  mParameterMax = new double[mParameterNum];

  /**
   * Initializing the steady state and Trajectory pointers to NULL
   */
  steady_state = NULL;
  trajectory = NULL;

  //  For test purposes: delete test.txt after the CSS_Solution.process(&ofstream)
  //  is modified to CSS_Solution.process()

  ofstream out("test.txt");
}

// check constraints : unimplemented - always returns true
bool COptProblem::checkParametricConstraints()
{
  return true;
}

bool COptProblem::checkFunctionalConstraints()
{
  return true;
}

/**
 * calculate() decides whether the problem is a steady state problem or a
 * trajectory problem based on whether the pointer to that type of problem
 * is null or not.  It then calls the process() method for that type of 
 * problem.  Currently process takes ofstream& as a parameter but it will
 * change so that process() takes no parameters.
 */
C_FLOAT64 COptProblem::calculate()
{
  if (steady_state != NULL)
    {
      cout << "COptProblem: steady_state";
      steady_state->process(out);
    }
  if (trajectory != NULL)
    {
      cout << "COptProblem: trajectory";
      trajectory->process(out);
    }
  return 0;
}

//set the parameter values
void COptProblem::setParamterValues(double * aDouble)
{
  mParameterValues = aDouble;
}

// get parameter values
double * COptProblem::getParameterValues()
{
  return mParameterValues;
}

//set a parameter
void COptProblem::setParameter(int aNum, double aDouble)
{
  mParameterValues[aNum] = aDouble;
}

// get a parameter
double COptProblem::getParameter(int aNum)
{
  return mParameterValues[aNum];
}

// set parameter number
void COptProblem::setParameterNum(int aNum)
{
  mParameterNum = aNum;
  initialize();
}

// get parameter number
int COptProblem::getParameterNum()
{
  return mParameterNum;
}

// set the best value
void COptProblem::setBestValue(double aDouble)
{
  mBestValue = aDouble;
}

//get the best value
double COptProblem::getBestValue()
{
  return mBestValue;
}

//set best value in array
void COptProblem::setBestParameter(int i, double value)
{
  mBestParameters[i] = value;
}

//get best value from array
double COptProblem::getBestValue(int i)
{
  return mBestParameters[i];
}

// set the minimum value of parameters
void COptProblem::setParameterMin(double * aDouble)
{
  mParameterMin = aDouble;
}

// set individual minimum value
void COptProblem::setParameterMin(int i, double value)
{
  mParameterMin[i] = value;
}

// get the minimum value of parameters
double * COptProblem::getParameterMin()
{
  return mParameterMin;
}

// get minimum value from array
double COptProblem::getParameterMin(int i)
{
  return mParameterMin[i];
}

// set the maximum value of the paramters
void COptProblem::setParameterMax(double * aDouble)
{
  mParameterMax = aDouble;
}

// set individual array element
void COptProblem::setParameterMax(int i, double value)
{
  mParameterMax[i] = value;
}

// get the maximum value of the parameters
double * COptProblem::getParameterMax()
{
  return mParameterMax;
}

// get individual element from array
double COptProblem::getParameterMax(int i)
{
  return mParameterMax[i];
}

// set the type of problem : Steady State OR Trajectory
void COptProblem::setProblemType(ProblemType t)
{
  if (t == SteadyState)
    steady_state = new CSS_Solution();
  if (t == Trajectory)
    trajectory = new CTrajectory();
}
