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
#include "COptProblem.h"

using namespace std;

// Default constructor
COptAlgorithm::COptAlgorithm()
{
  initialize();

  mOptProblem = NULL;
  mParameters = NULL;
  mParameterNum = 0;        // the number of parameters
  mParameterMin = NULL;     // the minimum values of parameters
  mParameterMax = NULL;     // the maximum values of parameters

  for (unsigned C_INT32 i = 0; i < mOptAlgmParams.size(); i++)
    {
      mOptAlgmParams[i].setName("unknown");
      mOptAlgmParams[i].setValue(0.0);
    }

  mMethodVersion = "0";
  mMethodName = "Unknown";
  mBounds = false;
}

//YOHE: seems "virtual" cannot be outside of class declaration
COptAlgorithm::~COptAlgorithm()
{ }

// copy constructor
COptAlgorithm::COptAlgorithm(const COptAlgorithm& source):
    mParameters(source.mParameters),
    mParameterNum(source.mParameterNum),
    mParameterMin(source.mParameterMin),
    mParameterMax(source.mParameterMax),
    mOptAlgmParams(source.mOptAlgmParams),

    mMethodVersion(source.mMethodVersion),
    mMethodName(source.mMethodName),
    mBounds(source.mBounds),
    mOptProblem(source.mOptProblem)
{
  /*
  mOptProblem = source.mOptProblem;
  mParameters = source.mParameters;
  mParameterNum = source.mParameterNum;
  mParameterMin = source.mParameterMin;
  mParameterMax = source.mParameterMax;
  mOptAlgmParams = source.mOptAlgmParams;

  mMethodVersion = source.mMethodVersion;
  mMethodName = source.mMethodName; 
  mBounds = source.mBounds;  
  */
}

// Object assignment overloading,
COptAlgorithm & COptAlgorithm::operator = (const COptAlgorithm& source)
{
  cleanup();

  if (this != &source)
    {
      mOptProblem = source.mOptProblem;
      mParameters = source.mParameters;
      mParameterNum = source.mParameterNum;
      mParameterMin = source.mParameterMin;
      mParameterMax = source.mParameterMax;
      mOptAlgmParams = source.mOptAlgmParams;

      mMethodVersion = source.mMethodVersion;
      mMethodName = source.mMethodName;
      mBounds = source.mBounds;
    }

  return *this;
}

// Initialization of private variables
bool COptAlgorithm::initialize(void)
{
  cleanup();

  mOptProblem = new COptProblem();
  mParameters = new C_FLOAT64();
  mParameterMin = new C_FLOAT64();
  mParameterMax = new C_FLOAT64();

  /*
    for (C_INT32 i=0; i<mOptAlgmParams.size(); i++)
    {
    mOptAlgmParams[i].setName("unknown");
    mOptAlgmParams[i].setValue(0.0);
    }
  */

  return true;
}

//clean up mem
void COptAlgorithm::cleanup(void)
{
  if (mOptProblem)
    mOptProblem = NULL;
  if (mParameters)
    mParameters = NULL;
  if (mParameterMin)
    mParameterMin = NULL;
  if (mParameterMax)
    mParameterMax = NULL;

  if (!mOptAlgmParams.empty())
    mOptAlgmParams.clear();

  return;
}

// set the number of method parameters
void COptAlgorithm::setMethodParameterNumber(C_INT32 aNum)
{
  mParameterNum = aNum;
}

void COptAlgorithm::setProblem(COptProblem * problem)
{
  mOptProblem = problem;
}

// get method parameter number
unsigned C_INT32 COptAlgorithm::getMethodParameterNumber(void)
{
  return mParameterNum;
}

// get method parameters
vector <COptAlgorithmParameter> & COptAlgorithm::getMethodParameters()
{
  return mOptAlgmParams;
}

// set method parameter value
void COptAlgorithm::setMethodParameterValue(C_INT32 i, C_FLOAT64 value)
{
  mOptAlgmParams[i].setValue(value);
}

// get method parameter value
C_FLOAT64 COptAlgorithm::getMethodParameterValue(C_INT32 i)
{
  return mOptAlgmParams[i].getValue();
}

// get method parameter name
string COptAlgorithm::getMethodParameterName(C_INT32 i)
{
  return mOptAlgmParams[i].getName();
}

// get method name
string COptAlgorithm::getMethodName(void)
{
  return mMethodName;
}

// get method version
string COptAlgorithm::getMethodVersion(void)
{
  return mMethodVersion;
}

// Returns True if this method is capable of handling adjustable parameter boundary
// constraints, False otherwise
bool COptAlgorithm::isBounded(void)
{
  return mBounds;
}

// YOHE: declare it as a virtual function in COptAlgorithm.h file
//
// Execute the optimization algorithm calling simulation routine (passed as argument)
// when needed. It is noted that this procedure can give feedback of its progress by
// the callback function set with SetCallback
//virtual C_INT32 COptAlgorithm::Optimise(C_FLOAT64 (*func) (void))
C_INT32 COptAlgorithm::optimise(void)
{
  return 0;
}
