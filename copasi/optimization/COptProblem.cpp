/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptProblem.cpp,v $
   $Revision: 1.25 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/01/20 20:40:08 $
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
#include "COptItem.h"

#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "trajectory/CTrajectoryProblem.h"

#include "model/CModel.h"
#include "model/CCompartment.h"

//  Default constructor
COptProblem::COptProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::optimization, pParent),
    mCalculateVariablesMin(),
    mCalculateVariablesMax(),
    mpSteadyState(NULL),
    mpTrajectory(NULL)
{
  addGroup("OptimizationItemList");
  addGroup("OptimizationConstraintList");

  addParameter("SteadyState", CCopasiParameter::STRING, (std::string) "");
  addParameter("Trajectory", CCopasiParameter::STRING, (std::string) "");
  addParameter("ObjectiveFunction", CCopasiParameter::STRING, (std::string) "");
  addParameter("Maximize", CCopasiParameter::BOOL, (bool) false);
}

// copy constructor
COptProblem::COptProblem(const COptProblem& src,
                         const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent),
    mCalculateVariablesMin(src.mCalculateVariablesMin),
    mCalculateVariablesMax(src.mCalculateVariablesMax),
    mpSteadyState(src.mpSteadyState),
    mpTrajectory(src.mpTrajectory)
{}

// Destructor
COptProblem::~COptProblem()
{}

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
bool COptProblem::calculate()
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
  return true;
}

void COptProblem::setSolutionValue(const C_FLOAT64 & value)
{
  getSolutionResults()[0] = value;
}

// get the minimum value of parameters
CVector< C_FLOAT64 > & COptProblem::getParameterMin()
{
  return mCalculateVariablesMin;
}

// get the maximum value of the parameters
CVector< C_FLOAT64 > & COptProblem::getParameterMax()
{
  return mCalculateVariablesMax;
}

// set the type of problem : Steady State OR Trajectory
void COptProblem::setProblemType(ProblemType type)
{
  if (type == SteadyState)
    mpSteadyState = new CSteadyStateTask(/*this*/NULL);
  if (type == Trajectory)
    mpTrajectory = new CTrajectoryTask(/*this*/NULL);
}

COptItem COptProblem::getOptItem(const unsigned C_INT32 & index)
{
  CCopasiParameterGroup * pOptimizationItemList
  = (CCopasiParameterGroup *) getValue("OptimizationItemList");

  CCopasiParameterGroup * pOptItem
  = (CCopasiParameterGroup *) pOptimizationItemList->getValue(0);

  if (!pOptItem || !COptItem::isValid(*pOptItem)) fatalError();

  return COptItem(*pOptItem);
}

const unsigned C_INT32 COptProblem::getOptItemSize() const
{return ((CCopasiParameterGroup *) getValue("OptimizationItemList"))->size();}

COptItem COptProblem::addOptItem(const CCopasiObjectName & objectCN)
{
  unsigned C_INT32 index = getOptItemSize();
  CCopasiParameterGroup * pOptimizationItemList
  = (CCopasiParameterGroup *) getValue("OptimizationItemList");
  pOptimizationItemList->addGroup("OptimizationItem");

  CCopasiParameterGroup * pOptItem = (CCopasiParameterGroup *) pOptimizationItemList->getValue(index);
  pOptItem->addParameter("ObjectCN", CCopasiParameter::STRING, (std::string) objectCN);
  pOptItem->addParameter("LowerBound", CCopasiParameter::STRING, (std::string) "-inf");
  pOptItem->addParameter("LowerRelation", CCopasiParameter::STRING, (std::string) "<=");
  pOptItem->addParameter("UpperBound", CCopasiParameter::STRING, (std::string) "inf");
  pOptItem->addParameter("UpperRelation", CCopasiParameter::STRING, (std::string) "<=");

  if (!pOptItem || !COptItem::isValid(*pOptItem)) fatalError();

  return COptItem(*pOptItem);
}

bool COptProblem::swapOptItem(const unsigned C_INT32 & iFrom,
                              const unsigned C_INT32 & iTo)
{return ((CCopasiParameterGroup *) getValue("OptimizationItemList"))->swap(iFrom, iTo);}
