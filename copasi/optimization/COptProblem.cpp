/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptProblem.cpp,v $
   $Revision: 1.45 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/07/01 15:18:56 $
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

#include "function/CFunctionDB.h"

#include "CopasiDataModel/CCopasiDataModel.h"

#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "trajectory/CTrajectoryProblem.h"

#include "model/CModel.h"
#include "model/CCompartment.h"

#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"

#include "utilities/CProcessReport.h"

//  Default constructor
COptProblem::COptProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::optimization, pParent),
    mpSteadyState(NULL),
    mpTrajectory(NULL),
    mpFunction(NULL),
    mOptItemList()
{
  addGroup("OptimizationItemList");
  addGroup("OptimizationConstraintList");

  addParameter("SteadyState", CCopasiParameter::STRING, (std::string) "");
  addParameter("Trajectory", CCopasiParameter::STRING, (std::string) "");
  addParameter("ObjectiveFunction", CCopasiParameter::KEY, (std::string) "");
  addParameter("Maximize", CCopasiParameter::BOOL, (bool) false);
}

// copy constructor
COptProblem::COptProblem(const COptProblem& src,
                         const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent),
    mpSteadyState(src.mpSteadyState),
    mpTrajectory(src.mpTrajectory),
    mpFunction(NULL),
    mOptItemList()
{
  if (src.mpFunction)
    {
      createObjectiveFunction();
      mpFunction->setInfix(src.mpFunction->getInfix());
      setValue("ObjectiveFunction", mpFunction->getKey());
    }
}

// Destructor
COptProblem::~COptProblem()
{
  std::vector<COptItem *>::iterator it = mOptItemList.begin();
  std::vector<COptItem *>::iterator end = mOptItemList.end();

  for (; it != end; ++it)
    pdelete(*it);

  pdelete(mpFunction);
}

bool COptProblem::setModel(CModel * pModel)
{
  mpModel = pModel;
  return true;
}

bool COptProblem::setCallBack(CProcessReport * pCallBack)
{
  CCopasiProblem::setCallBack(pCallBack);

  mpCallBack->addItem("Best Value",
                      CCopasiParameter::DOUBLE,
                      getObject(CCopasiObjectName("Reference=Best Value")));
  mpCallBack->addItem("Simulation Counter",
                      CCopasiParameter::DOUBLE,
                      getObject(CCopasiObjectName("Reference=Simulation Counter")));

  return true;
}

void COptProblem::initObjects()
{
  addObjectReference("Best Value", mSolutionValue, CCopasiObject::ValueDbl);
  addObjectReference("Simulation Counter", mCounter, CCopasiObject::ValueDbl);
}

bool COptProblem::initialize()
{
  if (!mpModel) return false;
  mpModel->compileIfNecessary();

  std::vector< CCopasiContainer * > ContainerList;
  ContainerList.push_back(mpModel);
  ContainerList.push_back(getObjectParent());

  unsigned C_INT32 i;
  unsigned C_INT32 Size = mOptItemList.size();
  mUpdateMethods.resize(Size);
  mSolutionVariables.resize(Size);

  std::vector< COptItem * >::iterator it = mOptItemList.begin();
  std::vector< COptItem * >::iterator end = mOptItemList.end();

  for (i = 0; it != end; ++it, i++)
    {
      if (!(*it)->compile(ContainerList)) return false;
      mUpdateMethods[i] = (*it)->getUpdateMethod();
    }

  if (!mpFunction)
    mpFunction =
      dynamic_cast<CExpression *>(GlobalKeys.get(* getValue("ObjectiveFunction").pKEY));

  if (!mpFunction) return false;

  return mpFunction->compile(ContainerList);
}

bool COptProblem::checkParametricConstraints()
{
  std::vector< COptItem * >::const_iterator it = mOptItemList.begin();
  std::vector< COptItem * >::const_iterator end = mOptItemList.end();

  for (; it != end; ++it)
    if (!(*it)->checkConstraint()) return false;

  return true;
}

bool COptProblem::checkFunctionalConstraints()
{
  return true; // :TODO:
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

  mCalculateValue = mpFunction->calcValue();

  mCounter += 1;

  if (mpCallBack) return mpCallBack->progress();
  return true;
}

const C_FLOAT64 & COptProblem::getCalculateValue() const
{return mCalculateValue;}

void COptProblem::setSolutionVariables(const CVector< C_FLOAT64 > & variables)
{mSolutionVariables = variables;}

const CVector< C_FLOAT64 > & COptProblem::getSolutionVariables() const
  {return mSolutionVariables;}

void COptProblem::setSolutionValue(const C_FLOAT64 & value)
{mSolutionValue = value;}

const C_FLOAT64 & COptProblem::getSolutionValue() const
  {return mSolutionValue;}

// set the type of problem : Steady State OR Trajectory
void COptProblem::setProblemType(ProblemType type)
{
  // :TODO:
  if (type == SteadyState)
    mpSteadyState = new CSteadyStateTask(/*this*/NULL);
  if (type == Trajectory)
    mpTrajectory = new CTrajectoryTask(/*this*/NULL);
}

COptItem & COptProblem::getOptItem(const unsigned C_INT32 & index)
{
  assert (index < mOptItemList.size());
  return *mOptItemList[index];
}

const unsigned C_INT32 COptProblem::getOptItemSize() const
  {return getValue("OptimizationItemList").pGROUP->size();}

COptItem & COptProblem::addOptItem(const CCopasiObjectName & objectCN)
{
  unsigned C_INT32 index = getOptItemSize();

  CCopasiParameterGroup * pOptimizationItemList = (CCopasiParameterGroup *) getParameter("OptimizationItemList");

  pOptimizationItemList->addGroup("OptimizationItem");

  CCopasiParameterGroup * pOptItem =
    (CCopasiParameterGroup *) pOptimizationItemList->getParameter(index);

  assert(pOptItem != NULL);

  COptItem * pTmp = new COptItem(*pOptItem);

  //pTmp->setLowerBound(

  if (!pTmp->initialize(objectCN)) fatalError();

  mOptItemList.push_back(pTmp);

  return *pTmp;
}

bool COptProblem::removeOptItem(const unsigned C_INT32 & index)
{
  if (!(index < mOptItemList.size())) return false;

  pdelete(mOptItemList[index]);
  mOptItemList.erase(mOptItemList.begin() + index);

  return ((CCopasiParameterGroup *) getParameter("OptimizationItemList"))->removeParameter(index);
}

bool COptProblem::swapOptItem(const unsigned C_INT32 & iFrom,
                              const unsigned C_INT32 & iTo)
{
  if (!(iFrom < mOptItemList.size()) ||
      !(iTo < mOptItemList.size()))
    return false;

  COptItem * pTmp = mOptItemList[iFrom];
  mOptItemList[iFrom] = mOptItemList[iTo];
  mOptItemList[iTo] = pTmp;

  return ((CCopasiParameterGroup *) getParameter("OptimizationItemList"))->swap(iFrom, iTo);
}

const std::vector< COptItem * > & COptProblem::getOptItemList() const
{return mOptItemList;}

const std::vector< UpdateMethod * > & COptProblem::getCalculateVariableUpdateMethods() const
  {return mUpdateMethods;}

bool COptProblem::setObjectiveFunction(const std::string & infix)
{
  if (!mpFunction) createObjectiveFunction();

  return mpFunction->setInfix(infix);
}

const std::string COptProblem::getObjectiveFunction()
{
  if (!mpFunction) createObjectiveFunction();

  return mpFunction->getInfix();
}

bool COptProblem::createObjectiveFunction()
{
  mpFunction =
    dynamic_cast<CExpression *>(GlobalKeys.get(* getValue("ObjectiveFunction").pKEY));

  CCopasiVectorN<CEvaluationTree> & FunctionList =
    CCopasiDataModel::Global->getFunctionList()->loadedFunctions();

  if (!mpFunction)
    {
      std::ostringstream Name;
      Name << "Objective Function";

      int i = 0;

      while (FunctionList.getIndex(Name.str()) != C_INVALID_INDEX)
        {
          i++;
          Name.str("");
          Name << "Objective Function " << i;
        }

      mpFunction = new CExpression(Name.str(), this);
      FunctionList.add(mpFunction, false);

      setValue("ObjectiveFunction", mpFunction->getKey());
    }
  else
    {
      mpFunction->setObjectParent(this);

      if (FunctionList.getIndex(mpFunction->getObjectName()) == C_INVALID_INDEX)
        FunctionList.add(mpFunction, false);
    }

  return true;
}
