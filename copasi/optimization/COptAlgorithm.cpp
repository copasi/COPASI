/**
 *  File name: COptAlgorithm.cpp
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the implementation (.cpp file) of the COptAlgorithm class. 
 *           It contains the designed abstract interaction between a simulation
 *           subsystem and optimization algorithms. This base class defines
 *           methods by which the simulation subsystem accesses several 
 *           optimization algorithms. 
 */
#include <math.h>
#include "COptAlgorithm.h"


// Default constructor
COptAlgorithm::COptAlgorithm()
{
  mOptProblem = NULL;
  mParameter = NULL; 
  mParamterNum = 0;         // the number of parameters
  mParameterMin = NULL;     // the minimum values of parameters
  mParameterMax = NULL;     // the maximum values of parameters
  //if (mOptAlgmParams != ; //vector of COptAlgorithmParameter object
 
  mMethodVersion = "0";
  mMethodName = "Unknown";
  mBounds = false;
}

//YOHE: seems virtual cannot be outside of class declaration
COptAlgorithm::~COptAlgorithm()
{ }

// Initialization of private variables
bool COptAlgorithm::initialize(void)
{
  
  if (!mOptAlgmParams.empty())
    mOptAlgmParams.clear();
}

//clean up mem
int COptAlgorithm::cleanup(void)
{
  mOptProblem = NULL;
  mParameter = NULL; 
  mParameterMin = NULL;    
  mParameterMax = NULL;
}

int COptAlgorithm::getMethodParameterNumber(void)
{
  return mParamNum;
}


void COptAlgorithm::setMethodParameter(int i, double value)
{
  mMethodParams(i) = value;
}

double COptAlgorithm::getMethodParameter(int i)
{
  return mOptParams(i);
}

String COptAlgorithm::getMethodParameterName(int i)
{
  return mMethodParam(i);
}

String COptAlgorithm::getMethodName(void)
{
  return mMethodName;
}

String COptAlgorithm::getMethodVersion(void)
{
  return mMethodVersion;
}

// Returns True if this method is capable of handling adjustable parameter boundary
// constraints, False otherwise
bool COptAlgorithm::IsBounded( void )
{
  return mBounds;

}


// YOHE: declare it as a virtual function in COptAlgorithm.h file
//
// Execute the optimization algorithm calling simulation routine (passed as argument)
// when needed. It is noted that this procedure can give feedback of its progress by 
// the callback function set with SetCallback
//virtual int COptAlgorithm::Optimise( double (*func) (void) )
int COptAlgorithm::Optimise(void)
{
  return 0;
}



















