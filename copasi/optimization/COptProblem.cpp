/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptProblem.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:59 $
   End CVS Header */

/**
 *  File name: COptProblem.cpp
 *
 *  Programmer: Yongqun He
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the source file of the COptProblem class.
 *           It specifies the optimization problem with its own members and
 *           functions. It's used by COptAlgorithm class and COptimization class
 */
#include <float.h>

#include "copasi.h"
#include "COptProblem.h"
#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "trajectory/CTrajectoryProblem.h"

#include "model/CModel.h"
#include "model/CCompartment.h"

//  Default constructor
COptProblem::COptProblem():
    mOptItemList("OptProblem"),
    mBestValue(DBL_MAX),
    mParameter(),
    mParameterMin(),
    mParameterMax(),
    mBestParameter(),
    mpSteadyState(NULL),
    mpTrajectory(NULL)
{}

// copy constructor
COptProblem::COptProblem(const COptProblem& src):
    mOptItemList(src.mOptItemList),
    mBestValue(src.mBestValue),
    mParameter(src.mParameter),
    mParameterMin(src.mParameterMin),
    mParameterMax(src.mParameterMax),
    mBestParameter(src.mBestParameter),
    mpSteadyState(src.mpSteadyState),
    mpTrajectory(src.mpTrajectory)
{}

// Destructor
COptProblem::~COptProblem()
{}

// Object assignment overloading,
COptProblem & COptProblem::operator = (const COptProblem& src)
{
  if (this != &src)
    {
      mParameter = src.mParameter;
      mParameterMin = src.mParameterMin;
      mParameterMax = src.mParameterMax;
      mBestValue = src.mBestValue;
      mBestParameter = src.mBestParameter;
      mpSteadyState = src.mpSteadyState;
      mpTrajectory = src.mpTrajectory;
    }

  return *this;
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
  if (mpSteadyState != NULL)
    {
      ((CSteadyStateProblem *) mpSteadyState->getProblem())->
      setInitialState(mpSteadyState->getProblem()->getModel()->getInitialState());
      mpSteadyState->process();
    }

  if (mpTrajectory != NULL)
    {
      ((CTrajectoryProblem *) mpTrajectory->getProblem())->
      setInitialState(mpTrajectory->getProblem()->getModel()->getInitialState());
      mpTrajectory->process();
    }
  return 0;
}

// get parameter values
CVector< C_FLOAT64 > & COptProblem::getParameter()
{
  return mParameter;
}

//set a parameter
void COptProblem::setParameter(C_INT32 aNum, C_FLOAT64 aDouble)
{
  mParameter[aNum] = aDouble;
}

// get a parameter
C_FLOAT64 COptProblem::getParameter(C_INT32 aNum)
{
  return mParameter[aNum];
}

// set parameter number
void COptProblem::setParameterNum(C_INT32 aNum)
{
  mParameter.resize(aNum);
  mParameterMin.resize(aNum);
  mParameterMax.resize(aNum);
  mBestParameter.resize(aNum);
}

// get parameter number
C_INT32 COptProblem::getParameterNum()
{
  return mParameter.size();
}

// set the best value
void COptProblem::setBestValue(C_FLOAT64 aDouble)
{
  mBestValue = aDouble;
}

//get the best value
C_FLOAT64 COptProblem::getBestValue()
{
  return mBestValue;
}

//set best value in array
void COptProblem::setBestParameter(C_INT32 i, C_FLOAT64 value)
{
  mBestParameter[i] = value;
}

//get best value from array
C_FLOAT64 COptProblem::getBestValue(C_INT32 i)
{
  return mBestParameter[i];
}

// get the parameters leading the best value
CVector< C_FLOAT64 > & COptProblem::getBestParameter()
{
  return mBestParameter;
}

// set individual minimum value
void COptProblem::setParameterMin(C_INT32 i, C_FLOAT64 value)
{
  mParameterMin[i] = value;
}

// get the minimum value of parameters
CVector< C_FLOAT64 > & COptProblem::getParameterMin()
{
  return mParameterMin;
}

// get minimum value from array
C_FLOAT64 COptProblem::getParameterMin(C_INT32 i)
{
  return mParameterMin[i];
}

// set individual array element
void COptProblem::setParameterMax(C_INT32 i, C_FLOAT64 value)
{
  mParameterMax[i] = value;
}

// get the maximum value of the parameters
CVector< C_FLOAT64 > & COptProblem::getParameterMax()
{
  return mParameterMax;
}

// get individual element from array
C_FLOAT64 COptProblem::getParameterMax(C_INT32 i)
{
  return mParameterMax[i];
}

// set the type of problem : Steady State OR Trajectory
void COptProblem::setProblemType(ProblemType t)
{
  if (t == SteadyState)
    mpSteadyState = new CSteadyStateTask();
  if (t == Trajectory)
    mpTrajectory = new CTrajectoryTask();
}
