// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  File name: COptProblem.cpp
 *
 *  Programmer: Yongqun He
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the source file of the COptProblem class.
 *           It specifies the optimization problem with its own members and
 *           functions. It's used by COptAlgorithm class and COptimization class
 */
#include <cmath>

#include "copasi.h"
#include "COptTask.h"
#include "COptProblem.h"
#include "COptItem.h"

#include "function/CFunctionDB.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"

#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "trajectory/CTrajectoryProblem.h"

#include "model/CModel.h"
#include "model/CCompartment.h"

#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"

#include "utilities/CProcessReport.h"
#include "utilities/CCopasiException.h"

//  Default constructor
COptProblem::COptProblem(const CCopasiTask::Type & type,
                         const CCopasiContainer * pParent):
  CCopasiProblem(type, pParent),
  mWorstValue(0.0),
  mpParmSubtaskCN(NULL),
  mpParmObjectiveExpression(NULL),
  mpParmMaximize(NULL),
  mpParmRandomizeStartValues(NULL),
  mpParmCalculateStatistics(NULL),
  mpGrpItems(NULL),
  mpGrpConstraints(NULL),
  mpOptItems(NULL),
  mpConstraintItems(NULL),
  mpSubtask(NULL),
  mpObjectiveExpression(NULL),
  mUpdateMethods(),
  mInitialRefreshMethods(),
  mRefreshMethods(),
  mRefreshConstraints(),
  mCalculateValue(0),
  mSolutionVariables(),
  mOriginalVariables(),
  mSolutionValue(0),
  mCounter(0),
  mFailedCounter(0),
  mConstraintCounter(0),
  mFailedConstraintCounter(0),
  mCPUTime(CCopasiTimer::PROCESS, this),
  mhSolutionValue(C_INVALID_INDEX),
  mhCounter(C_INVALID_INDEX),
  mStoreResults(false),
  mHaveStatistics(false),
  mGradient(0)
{
  initializeParameter();
  initObjects();
}

// copy constructor
COptProblem::COptProblem(const COptProblem& src,
                         const CCopasiContainer * pParent):
  CCopasiProblem(src, pParent),
  mWorstValue(src.mWorstValue),
  mpParmSubtaskCN(NULL),
  mpParmObjectiveExpression(NULL),
  mpParmMaximize(NULL),
  mpParmRandomizeStartValues(NULL),
  mpParmCalculateStatistics(NULL),
  mpGrpItems(NULL),
  mpGrpConstraints(NULL),
  mpOptItems(NULL),
  mpConstraintItems(NULL),
  mpSubtask(NULL),
  mpObjectiveExpression(NULL),
  mUpdateMethods(),
  mInitialRefreshMethods(),
  mRefreshMethods(),
  mRefreshConstraints(),
  mCalculateValue(src.mCalculateValue),
  mSolutionVariables(src.mSolutionVariables),
  mOriginalVariables(src.mOriginalVariables),
  mSolutionValue(src.mSolutionValue),
  mCounter(0),
  mFailedCounter(0),
  mConstraintCounter(0),
  mFailedConstraintCounter(0),
  mCPUTime(CCopasiTimer::PROCESS, this),
  mhSolutionValue(C_INVALID_INDEX),
  mhCounter(C_INVALID_INDEX),
  mStoreResults(src.mStoreResults),
  mHaveStatistics(src.mHaveStatistics),
  mGradient(src.mGradient)
{
  initializeParameter();
  initObjects();
}

// Destructor
COptProblem::~COptProblem()
{}

void COptProblem::initializeParameter()
{
  mpParmSubtaskCN =
    assertParameter("Subtask", CCopasiParameter::CN, CCopasiObjectName(""))->getValue().pCN;
  mpParmObjectiveExpression =
    assertParameter("ObjectiveExpression", CCopasiParameter::EXPRESSION, std::string(""))->getValue().pEXPRESSION;
  mpParmMaximize =
    assertParameter("Maximize", CCopasiParameter::BOOL, false)-> getValue().pBOOL;
  mpParmRandomizeStartValues =
    assertParameter("Randomize Start Values", CCopasiParameter::BOOL, false)-> getValue().pBOOL;
  mpParmCalculateStatistics =
    assertParameter("Calculate Statistics", CCopasiParameter::BOOL, true)-> getValue().pBOOL;

  mpGrpItems = assertGroup("OptimizationItemList");
  mpGrpConstraints = assertGroup("OptimizationConstraintList");

  elevateChildren();
}

bool COptProblem::elevateChildren()
{
  // We need to handle the old file format which had two different task keys
  if (mpParmSubtaskCN != NULL)
    {
      CCopasiParameter * pParameter;

      if ((pParameter = getParameter("Steady-State")) != NULL)
        {
          if (*pParameter->getValue().pSTRING != "")
            {
              setSubtaskType(CCopasiTask::steadyState);
            }

          removeParameter("Steady-State");
        }

      if ((pParameter = getParameter("Time-Course")) != NULL)
        {
          if (*pParameter->getValue().pSTRING != "")
            {
              setSubtaskType(CCopasiTask::timeCourse);
            }

          removeParameter("Time-Course");
        }

      // If no subtask is defined we default to steady-state
      if (*mpParmSubtaskCN == "")
        setSubtaskType(CCopasiTask::steadyState);
    }

  // Handle old file format in which the objective expression was stored in the function DB
  if (mpParmObjectiveExpression != NULL)
    {
      CCopasiParameter * pParameter = getParameter("ObjectiveFunction");
      CExpression * pObjectiveFunction = NULL;

      // We do not use the key to find the objective function because keys are not re-mapped
      // for unknown parameters, instead we rely on the uniqueness of the name and the fact that
      // this is the only expression in the list.
      size_t Index = CCopasiRootContainer::getFunctionList()->loadedFunctions().getIndex("Objective Function");

      if (Index != C_INVALID_INDEX)
        {
          pObjectiveFunction =
            dynamic_cast<CExpression *>(CCopasiRootContainer::getFunctionList()->loadedFunctions()[Index]);
        }

      if (pObjectiveFunction != NULL &&
          pParameter != NULL)
        {
          *mpParmObjectiveExpression = pObjectiveFunction->getInfix();

          removeParameter("ObjectiveFunction");
        }

      setObjectiveFunction(*mpParmObjectiveExpression);
    }

  mpGrpItems =
    elevate<CCopasiParameterGroup, CCopasiParameterGroup>(mpGrpItems);

  if (!mpGrpItems) return false;

  std::vector<CCopasiParameter *> * pValue =
    mpGrpItems->CCopasiParameter::getValue().pGROUP;

  index_iterator it = pValue->begin();
  index_iterator end = pValue->end();

  for (; it != end; ++it)
    if (!elevate<COptItem, CCopasiParameterGroup>(*it)) return false;

  mpOptItems =
    static_cast<std::vector<COptItem * > * >(mpGrpItems->CCopasiParameter::getValue().pVOID);

  mpGrpConstraints =
    elevate<CCopasiParameterGroup, CCopasiParameterGroup>(mpGrpConstraints);

  if (!mpGrpConstraints) return false;

  pValue = mpGrpConstraints->CCopasiParameter::getValue().pGROUP;

  it = pValue->begin();
  end = pValue->end();

  for (; it != end; ++it)
    if (!elevate<COptItem, CCopasiParameterGroup>(*it)) return false;

  mpConstraintItems =
    static_cast<std::vector<COptItem * > * >(mpGrpConstraints->CCopasiParameter::getValue().pVOID);

  return true;
}

bool COptProblem::setModel(CModel * pModel)
{
  mpModel = pModel;
  return true;
}

void COptProblem::reset()
{
  mSolutionValue = (*mpParmMaximize ? - std::numeric_limits<C_FLOAT64>::infinity() : std::numeric_limits<C_FLOAT64>::infinity());
  mCounter = 0;
}

bool COptProblem::setCallBack(CProcessReport * pCallBack)
{
  CCopasiProblem::setCallBack(pCallBack);

  if (pCallBack)
    {
      reset();

      // We need to reset mSolutionValue to correctly initialize the progress item.
      mhSolutionValue =
        mpCallBack->addItem("Best Value",
                            mSolutionValue);
      // We need to reset mCounter to correctly initialize the progress item.
      mhCounter =
        mpCallBack->addItem("Function Evaluations",
                            mCounter);
    }

  return true;
}

void COptProblem::initObjects()
{
  addObjectReference("Function Evaluations", mCounter, CCopasiObject::ValueInt);
  addObjectReference("Best Value", mSolutionValue, CCopasiObject::ValueDbl);
  addVectorReference("Best Parameters", mSolutionVariables, CCopasiObject::ValueDbl);
}

bool COptProblem::initializeSubtaskBeforeOutput()
{
  if (mpParmSubtaskCN != NULL)
    {
      std::vector< CCopasiContainer * > ListOfContainer;
      ListOfContainer.push_back(getObjectAncestor("Vector"));
      mpSubtask =
        dynamic_cast< CCopasiTask * >(getObjectDataModel()->ObjectFromName(ListOfContainer, *mpParmSubtaskCN));

      try
        {
          if (mpSubtask != NULL)
            return mpSubtask->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);
        }

      catch (...) {}

      return false;
    }

  // We have a CFitProblem for which it is OK not to have a subtask.
  mpSubtask = NULL;
  return true;
}

bool COptProblem::initialize()
{
  mWorstValue = (*mpParmMaximize ? - std::numeric_limits<C_FLOAT64>::infinity() : std::numeric_limits<C_FLOAT64>::infinity());

  if (!mpModel) return false;

  mpModel->compileIfNecessary(mpCallBack);

  bool success = true;

  mpReport = NULL;
  mCounter = 0;
  mFailedCounter = 0;
  mConstraintCounter = 0;
  mFailedConstraintCounter = 0;

  mSolutionValue = mWorstValue;

  std::vector< CCopasiContainer * > ContainerList;
  ContainerList.push_back(mpModel);

  COptTask * pTask = dynamic_cast<COptTask *>(getObjectParent());

  if (pTask)
    {
      ContainerList.push_back(pTask);
      mpReport = &pTask->getReport();

      if (!mpReport->getStream()) mpReport = NULL;
    }

  if (mpSubtask != NULL)
    ContainerList.push_back(mpSubtask);

  size_t i;
  size_t Size = mpOptItems->size();

  mUpdateMethods.resize(Size);
  mSolutionVariables.resize(Size);
  mOriginalVariables.resize(Size);

  mSolutionVariables = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mOriginalVariables = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  std::vector< COptItem * >::iterator it = mpOptItems->begin();
  std::vector< COptItem * >::iterator end = mpOptItems->end();

  if (it == end)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 6);
      return false;
    }

  std::set< const CCopasiObject * > changedObjects;

  for (i = 0; it != end; ++it, i++)
    {
      success &= (*it)->compile(ContainerList);

      mUpdateMethods[i] = (*it)->getUpdateMethod();
      changedObjects.insert((*it)->getObject());
      mOriginalVariables[i] = *(*it)->COptItem::getObjectValue();
    }

  changedObjects.erase(NULL);
  mInitialRefreshMethods = mpModel->buildInitialRefreshSequence(changedObjects);

  it = mpConstraintItems->begin();
  end = mpConstraintItems->end();

  // We need to build a refresh sequence so the constraint values are updated
  std::set< const CCopasiObject * > Objects;

  for (i = 0; it != end; ++it, i++)
    {
      if (!(*it)->compile(ContainerList)) return false;

      Objects.insert((*it)->getDirectDependencies().begin(),
                     (*it)->getDirectDependencies().end());
    }

  mRefreshConstraints = CCopasiObject::buildUpdateSequence(Objects, mpModel->getUptoDateObjects());

  mCPUTime.start();

  if (mpObjectiveExpression == NULL ||
      mpObjectiveExpression->getInfix() == "" ||
      !mpObjectiveExpression->compile(ContainerList))
    {
      mRefreshMethods.clear();
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 5);
      return false;
    }

  mRefreshMethods = CCopasiObject::buildUpdateSequence(mpObjectiveExpression->getDirectDependencies(), mpModel->getUptoDateObjects());

  return success;
}

void COptProblem::restoreModel(const bool & updateModel)
{
  std::vector<COptItem * >::iterator it = mpOptItems->begin();
  std::vector<COptItem * >::iterator end = mpOptItems->end();
  const C_FLOAT64 * pTmp;
  std::set< const CCopasiObject * > ChangedObjects;

  if (updateModel && mSolutionValue != mWorstValue)
    {
      // Set the model values and start values to the solution values
      pTmp = mSolutionVariables.array();

      for (; it != end; ++it, pTmp++)
        {
          if ((*it)->getObject())
            {
              (*(*it)->COptItem::getUpdateMethod())(*pTmp);
              (*it)->setStartValue(*pTmp);

              ChangedObjects.insert((*it)->getObject());
            }
        }
    }
  else
    {
      // Reset the model values to the original values
      pTmp = mOriginalVariables.array();

      for (; it != end; ++it, pTmp++)
        {
          if ((*it)->getObject())
            {
              if (!isnan(*pTmp))
                (*(*it)->COptItem::getUpdateMethod())(*pTmp);

              ChangedObjects.insert((*it)->getObject());
            }
        }
    }

  // We need to update the dependent initial values
  std::vector< Refresh * > UpdateSequence = mpModel->buildInitialRefreshSequence(ChangedObjects);
  std::vector< Refresh * >::iterator itUpdate = UpdateSequence.begin();
  std::vector< Refresh * >::iterator endUpdate = UpdateSequence.end();

  for (; itUpdate != endUpdate; ++itUpdate)
    {
      (**itUpdate)();
    }
}

bool COptProblem::restore(const bool & updateModel)
{
  bool success = true;

  if (mpSubtask != NULL)
    success &= mpSubtask->restore();

  restoreModel(updateModel);

  if (mFailedCounter * 20 > mCounter) // > 5% failure rate
    CCopasiMessage(CCopasiMessage::WARNING, MCOptimization + 8, mFailedCounter, mCounter);

  if (10 * mFailedConstraintCounter > 8 * mConstraintCounter) // > 80 % failure rate
    CCopasiMessage(CCopasiMessage::WARNING, MCOptimization + 9, mFailedConstraintCounter, mConstraintCounter);

  return success;
}

bool COptProblem::checkParametricConstraints()
{
  std::vector< COptItem * >::const_iterator it = mpOptItems->begin();
  std::vector< COptItem * >::const_iterator end = mpOptItems->end();

  for (; it != end; ++it)
    if ((*it)->checkConstraint()) return false;

  return true;
}

bool COptProblem::checkFunctionalConstraints()
{
  // Make sure the constraint values are up to date.
  std::vector< Refresh *>::const_iterator itRefresh = mRefreshConstraints.begin();
  std::vector< Refresh *>::const_iterator endRefresh = mRefreshConstraints.end();

  for (; itRefresh != endRefresh; ++itRefresh)
    (**itRefresh)();

  std::vector< COptItem * >::const_iterator it = mpConstraintItems->begin();
  std::vector< COptItem * >::const_iterator end = mpConstraintItems->end();

  mConstraintCounter++;

  for (; it != end; ++it)
    if ((*it)->checkConstraint())
      {
        mFailedConstraintCounter++;
        return false;
      }

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
  mCounter++;
  bool success = false;
  COutputHandler * pOutputHandler = NULL;

  if (mpSubtask == NULL)
    return false;

  if (mStoreResults &&
      mpSubtask->getType() == CCopasiTask::timeCourse)
    {
      static_cast< CTrajectoryProblem * >(mpSubtask->getProblem())->setTimeSeriesRequested(true);

      pOutputHandler = new COutputHandler();
      mpSubtask->initialize(CCopasiTask::ONLY_TIME_SERIES, pOutputHandler, NULL);
    }

  try
    {
      // Update all initial values which depend on the optimization items.
      std::vector< Refresh * >::const_iterator it = mInitialRefreshMethods.begin();
      std::vector< Refresh * >::const_iterator end = mInitialRefreshMethods.end();

      for (; it != end; ++it)
        (**it)();

      success = mpSubtask->process(true);

      // Refresh all values needed to calculate the objective function.
      it = mRefreshMethods.begin();
      end = mRefreshMethods.end();

      for (; it != end; ++it)
        (**it)();

      mCalculateValue = *mpParmMaximize ? -mpObjectiveExpression->calcValue() : mpObjectiveExpression->calcValue();
    }

  catch (CCopasiException & /*Exception*/)
    {
      // We do not want to clog the message cue.
      CCopasiMessage::getLastMessage();

      success = false;
    }

  catch (...)
    {
      success = false;
    }

  if (mStoreResults &&
      mpSubtask->getType() == CCopasiTask::timeCourse)
    {
      mStoreResults = false;
      mpSubtask->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);
      pdelete(pOutputHandler);
    }

  if (!success || isnan(mCalculateValue))
    {
      mFailedCounter++;
      mCalculateValue = std::numeric_limits< C_FLOAT64 >::infinity();
    }

  if (mpCallBack) return mpCallBack->progressItem(mhCounter);

  return true;
}

bool COptProblem::calculateStatistics(const C_FLOAT64 & factor,
                                      const C_FLOAT64 & resolution)
{
  // Set the current values to the solution values.
  size_t i, imax = mSolutionVariables.size();

  mGradient.resize(imax);
  mGradient = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  // Recalculate the best solution.
  for (i = 0; i < imax; i++)
    (*mUpdateMethods[i])(mSolutionVariables[i]);

  // This is necessary so that the result can be displayed.
  mStoreResults = true;
  calculate();
  mStoreResults = false;

  // Make sure the timer is accurate.
  mCPUTime.getRefresh();

  if (mSolutionValue == mWorstValue)
    return false;

  if (*mpParmCalculateStatistics)
    {
      mHaveStatistics = true;

      C_FLOAT64 Current;
      C_FLOAT64 Delta;

      // Calculate the gradient
      for (i = 0; i < imax; i++)
        {
          Current = mSolutionVariables[i];

          if (fabs(Current) > resolution)
            {
              (*mUpdateMethods[i])(Current * (1.0 + factor));
              Delta = 1.0 / (Current * factor);
            }
          else
            {
              (*mUpdateMethods[i])(resolution);
              Delta = 1.0 / resolution;
            }

          calculate();

          mGradient[i] = ((*mpParmMaximize ? -mCalculateValue : mCalculateValue) - mSolutionValue) * Delta;

          // Restore the value
          (*mUpdateMethods[i])(Current);
        }

      calculate();

      // Make sure the timer is accurate.
      (*mCPUTime.getRefresh())();
    }

  return true;
}

const C_FLOAT64 & COptProblem::getCalculateValue() const
{return mCalculateValue;}

const CVector< C_FLOAT64 > & COptProblem::getSolutionVariables() const
{return mSolutionVariables;}

const CVector< C_FLOAT64 > & COptProblem::getVariableGradients() const
{return mGradient;}

bool COptProblem::setSolution(const C_FLOAT64 & value,
                              const CVector< C_FLOAT64 > & variables)
{
  mSolutionValue = *mpParmMaximize ? -value : value;
  mSolutionVariables = variables;

  bool Continue = true;

  if (value == -std::numeric_limits< C_FLOAT64 >::infinity())
    Continue = false;

  if (mpCallBack)
    Continue &= mpCallBack->progressItem(mhSolutionValue);

  return Continue;
}

const C_FLOAT64 & COptProblem::getSolutionValue() const
{return mSolutionValue;}

COptItem & COptProblem::getOptItem(const size_t & index)
{return *(*mpOptItems)[index];}

size_t COptProblem::getOptItemSize() const
{return mpGrpItems->size();}

COptItem & COptProblem::addOptItem(const CCopasiObjectName & objectCN)
{
  CCopasiDataModel* pDataModel = getObjectDataModel();
  assert(pDataModel != NULL);

  COptItem * pItem = new COptItem(pDataModel);
  pItem->setObjectCN(objectCN);

  mpGrpItems->addParameter(pItem);

  return *pItem;
}

bool COptProblem::removeOptItem(const size_t & index)
{return mpGrpItems->removeParameter(index);}

bool COptProblem::swapOptItem(const size_t & iFrom,
                              const size_t & iTo)
{return mpGrpItems->swap(iFrom, iTo);}

const std::vector< COptItem * > & COptProblem::getOptItemList() const
{return *mpOptItems;}

const std::vector< COptItem * > & COptProblem::getConstraintList() const
{return *mpConstraintItems;}

const std::vector< UpdateMethod * > & COptProblem::getCalculateVariableUpdateMethods() const
{return mUpdateMethods;}

bool COptProblem::setObjectiveFunction(const std::string & infix)
{
  *mpParmObjectiveExpression = infix;

  if (mpObjectiveExpression == NULL)
    mpObjectiveExpression = new CExpression("Expression", this);

  return mpObjectiveExpression->setInfix(infix);
}

const std::string COptProblem::getObjectiveFunction()
{
  return *mpParmObjectiveExpression;
}

bool COptProblem::setSubtaskType(const CCopasiTask::Type & subtaskType)
{
  mpSubtask = NULL;
  *mpParmSubtaskCN = "";

  CCopasiVectorN< CCopasiTask > * pTasks =
    dynamic_cast< CCopasiVectorN< CCopasiTask > *>(getObjectAncestor("Vector"));

  CCopasiDataModel* pDataModel = getObjectDataModel();

  if (pTasks == NULL && pDataModel)
    pTasks = pDataModel->getTaskList();

  if (pTasks)
    {
      size_t i, imax = pTasks->size();

      for (i = 0; i < imax; i++)
        if ((*pTasks)[i]->getType() == subtaskType)
          {
            mpSubtask = (*pTasks)[i];
            *mpParmSubtaskCN = mpSubtask->getCN();
            return true;
          }
    }

  return false;
}

CCopasiTask::Type COptProblem::getSubtaskType() const
{
  std::vector< CCopasiContainer * > ListOfContainer;
  ListOfContainer.push_back(getObjectAncestor("Vector"));
  mpSubtask =
    dynamic_cast< CCopasiTask * >(const_cast< CCopasiObject *>(getObjectDataModel()->ObjectFromName(ListOfContainer, *mpParmSubtaskCN)));

  if (mpSubtask == NULL)
    return CCopasiTask::unset;

  return mpSubtask->getType();
}

void COptProblem::setMaximize(const bool & maximize)
{*mpParmMaximize = maximize;}

const bool & COptProblem::maximize() const
{return *mpParmMaximize;}

void COptProblem::setRandomizeStartValues(const bool & randomize)
{*mpParmRandomizeStartValues = randomize;}

const bool & COptProblem::getRandomizeStartValues() const
{return *mpParmRandomizeStartValues;}

void COptProblem::randomizeStartValues()
{
  if (*mpParmRandomizeStartValues)
    {
      std::vector< COptItem * >::iterator it = mpOptItems->begin();
      std::vector< COptItem * >::iterator end = mpOptItems->end();

      for (; it != end; ++it)
        {
          (*it)->setStartValue((*it)->getRandomValue());
        }
    }

  return;
}

void COptProblem::rememberStartValues()
{
  std::vector< COptItem * >::iterator it = mpOptItems->begin();
  std::vector< COptItem * >::iterator end = mpOptItems->end();

  for (; it != end; ++it)
    {
      (*it)->rememberStartValue();
    }

  return;
}

void COptProblem::setCalculateStatistics(const bool & calculate)
{*mpParmCalculateStatistics = calculate;}

const bool & COptProblem::getCalculateStatistics() const
{return *mpParmCalculateStatistics;}

const unsigned C_INT32 & COptProblem::getFunctionEvaluations() const
{return mCounter;}

void COptProblem::incrementEvaluations(unsigned C_INT32 increment)
{mCounter += increment;}

void COptProblem::resetEvaluations()
{mCounter = 0;}

const C_FLOAT64 & COptProblem::getExecutionTime() const
{
  return mCPUTime.getElapsedTimeSeconds();
}

void COptProblem::print(std::ostream * ostream) const
{*ostream << *this;}

void COptProblem::printResult(std::ostream * ostream) const
{
  std::ostream & os = *ostream;

  if (mSolutionVariables.size() == 0)
    {
      return;
    }

  os << "    Objective Function Value:\t" << mSolutionValue << std::endl;

  CCopasiTimeVariable CPUTime = const_cast<COptProblem *>(this)->mCPUTime.getElapsedTime();

  os << "    Function Evaluations:\t" << mCounter << std::endl;
  os << "    CPU Time [s]:\t"
     << CCopasiTimeVariable::LL2String(CPUTime.getSeconds(), 1) << "."
     << CCopasiTimeVariable::LL2String(CPUTime.getMilliSeconds(true), 3) << std::endl;
  os << "    Evaluations/Second [1/s]:\t" << mCounter / (C_FLOAT64)(CPUTime.getMilliSeconds() / 1e3) << std::endl;
  os << std::endl;

  std::vector< COptItem * >::const_iterator itItem =
    mpOptItems->begin();
  std::vector< COptItem * >::const_iterator endItem =
    mpOptItems->end();

  size_t i;

  for (i = 0; itItem != endItem; ++itItem, i++)
    {
      os << "    " << (*itItem)->getObjectDisplayName() << ": "
         << mSolutionVariables[i] << std::endl;
    }
}

std::ostream &operator<<(std::ostream &os, const COptProblem & o)
{
  os << "Problem Description:" << std::endl;

  os << "Subtask: " << std::endl;

  if (o.mpSubtask)
    o.mpSubtask->getDescription().print(&os);
  else
    os << "No Subtask specified.";

  os << std::endl;

  if (o.mpObjectiveExpression)
    {
      os << "Objective Function:" << std::endl;
      os << "    " << o.mpObjectiveExpression->getDisplayString() << std::endl;
      os << std:: endl;
    }

  os << "List of Optimization Items:" << std::endl;

  std::vector< COptItem * >::const_iterator itItem =
    o.mpOptItems->begin();
  std::vector< COptItem * >::const_iterator endItem =
    o.mpOptItems->end();

  for (; itItem != endItem; ++itItem)
    os << "    " << **itItem << std::endl;

  itItem = o.mpConstraintItems->begin();
  endItem = o.mpConstraintItems->end();

  for (; itItem != endItem; ++itItem)
    os << "    " << **itItem << std::endl;

  return os;
}
