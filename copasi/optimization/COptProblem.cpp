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


// double * mParameterValues;        // pointer to parameters
 
   
//  Default constructor
COptProblem::COptProblem()
{
  mParameterValues = NULL;
  mParameterNum = 0;
  mBestValue = 0.0;
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
  mParameterValues = source.mParameterValues;
  mParameterNum = source.mParameterNum;
  mBestValue =source.mBestValue;
  mParameterMin = source.mParameterMin;     // the minimum values of parameters
  mParameterMax = source.mParameterMax;    
}

// Object assignment overloading,
COptProblem & COptProblem::operator = (const COptProblem& source)
{
  cleanup();
    
  if(this != &source)
    {
      mParameterValues = source.mParameterValues; 
      mParameterNum = source.mParameterNum;
      mBestValue = source.mBestValue;
      mParameterMin = source.mParameterMin;     // the minimum values of parameters
      mParameterMax = source.mParameterMax;  	
    }
    
  return *this;
}


//clean up memory
int COptProblem::cleanup(void)
{
  mParameterValues = NULL;
  mParameterNum = 0;
  mBestValue = 0.0;
}

 
//  Initialization of private variables
int COptProblem::initialize(void)
{
  mParameterValues = new double[mParameterNum];
  mParameterMin = new double;
  mParameterMax = new double;
}

 
// 
void COptProblem::calculate() 
{ }
   

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
  
// set the minimum value of parameters
void COptProblem::setParameterMin(double * aDouble)
{
  mParameterMin = aDouble;
}  

// get the minimum value of parameters
double * COptProblem::getParameterMin()
{
  return mParameterMin;
}

// set the maximum value of the paramters
void COptProblem::setParameterMax(double * aDouble)
{
  mParameterMax = aDouble;
}
   
// get the maximum value of the parameters
double * COptProblem::getParameterMax()
{
  return mParameterMax;
}
   
