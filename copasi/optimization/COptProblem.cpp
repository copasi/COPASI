// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/copasi.h"
#include "copasi/optimization/COptTask.h"
#include "copasi/optimization/COptProblem.h"
#include "copasi/optimization/COptItem.h"

#include "copasi/function/CFunctionDB.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"

#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/steadystate/CSteadyStateProblem.h"
#include "copasi/trajectory/CTrajectoryProblem.h"

#include "copasi/math/CMathContainer.h"
#include "copasi/math/CMathExpression.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CCompartment.h"

#include "copasi/core/CDataObjectReference.h"
#include "copasi/report/CKeyFactory.h"

#include "copasi/utilities/CProcessReport.h"
#include "copasi/utilities/CTaskFactory.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/utilities/CBrent.h"

// static
const CTaskEnum::Task COptProblem::ValidSubtasks[] =
{
  CTaskEnum::Task::steadyState,
  CTaskEnum::Task::timeCourse,
  CTaskEnum::Task::scan,
  CTaskEnum::Task::parameterFitting,
  CTaskEnum::Task::mca,
  CTaskEnum::Task::lyap,
  CTaskEnum::Task::tssAnalysis,
  CTaskEnum::Task::sens,
  CTaskEnum::Task::crosssection,
  CTaskEnum::Task::lna,
  CTaskEnum::Task::UnsetTask
};

// static
C_FLOAT64 COptProblem::MissingValue;

//  Default constructor
COptProblem::COptProblem(const CTaskEnum::Task & type,
                         const CDataContainer * pParent)
  : CCopasiProblem(type, pParent)
  , mWorstValue(0.0)
  , mpParmSubTaskCN(NULL)
  , mpParmObjectiveExpression(NULL)
  , mpParmMaximize(NULL)
  , mpParmRandomizeStartValues(NULL)
  , mpParmCalculateStatistics(NULL)
  , mpGrpItems(NULL)
  , mpGrpConstraints(NULL)
  , mpOptItems(NULL)
  , mpConstraintItems(NULL)
  , mpSubTaskSrc(NULL)
  , mpSubTask(NULL)
  , mpObjectiveExpression(NULL)
  , mpMathObjectiveExpression(NULL)
  , mInitialRefreshSequence()
  , mUpdateObjectiveFunction()
  , mUpdateConstraints()
  , mUpdateIntervals()
  , mCalculateValue(0)
  , mSolutionVariables()
  , mOriginalVariables()
  , mSolutionValue(0)
  , mCounters()
  , mCPUTime(CCopasiTimer::Type::PROCESS, this)
  , mhSolutionValue(C_INVALID_INDEX)
  , mhCounter(C_INVALID_INDEX)
  , mStoreResults(false)
  , mHaveStatistics(false)
  , mGradient(0)
  , mMinInterval(std::numeric_limits< C_FLOAT64 >::infinity())
  , mCountInfluencingIntervals(0)
  , mOptItem2Index()
  , mOptItemAlgorithm()
  , mSolutionVariablesAlgorithm()
{
  initializeParameter();
  initObjects();
}

// copy constructor
COptProblem::COptProblem(const COptProblem & src,
                         const CDataContainer * pParent)
  : CCopasiProblem(src, pParent)
  , mWorstValue(src.mWorstValue)
  , mpParmSubTaskCN(NULL)
  , mpParmObjectiveExpression(NULL)
  , mpParmMaximize(NULL)
  , mpParmRandomizeStartValues(NULL)
  , mpParmCalculateStatistics(NULL)
  , mpGrpItems(NULL)
  , mpGrpConstraints(NULL)
  , mpOptItems(NULL)
  , mpConstraintItems(NULL)
  , mpSubTaskSrc(NULL)
  , mpSubTask(NULL)
  , mpObjectiveExpression(NULL)
  , mpMathObjectiveExpression(NULL)
  , mInitialRefreshSequence()
  , mUpdateObjectiveFunction()
  , mUpdateConstraints()
  , mUpdateIntervals()
  , mCalculateValue(src.mCalculateValue)
  , mSolutionVariables(src.mSolutionVariables)
  , mOriginalVariables(src.mOriginalVariables)
  , mSolutionValue(src.mSolutionValue)
  , mCounters()
  , mCPUTime(CCopasiTimer::Type::PROCESS, this)
  , mhSolutionValue(C_INVALID_INDEX)
  , mhCounter(C_INVALID_INDEX)
  , mStoreResults(src.mStoreResults)
  , mHaveStatistics(src.mHaveStatistics)
  , mGradient(src.mGradient)
  , mMinInterval(src.mMinInterval)
  , mCountInfluencingIntervals(src.mCountInfluencingIntervals)
  , mOptItem2Index()
  , mOptItemAlgorithm()
  , mSolutionVariablesAlgorithm()
{
  initializeParameter();
  initObjects();
}

// Destructor
COptProblem::~COptProblem()
{
  pdelete(mpSubTask);
}

// virtual
void  COptProblem::calculateValue()
{
  mMinInterval = std::numeric_limits< C_FLOAT64 >::infinity();

  std::vector< COptItem * >::const_iterator it = mpOptItems->begin();
  std::vector< COptItem * >::const_iterator end = mpOptItems->end();

  for (COptItem * pOptItem : *mpOptItems)
    if (*static_cast< C_FLOAT64 * >(pOptItem->getValuePointer()) < mMinInterval)
      mMinInterval = *static_cast< C_FLOAT64 * >(pOptItem->getValuePointer());

  return;
}

// virtual
void * COptProblem::getValuePointer() const
{
  return const_cast< C_FLOAT64 * >(&mMinInterval);
}

void COptProblem::initializeParameter()
{
  mpParmSubTaskCN = assertParameter("Subtask", CCopasiParameter::Type::CN, CRegisteredCommonName());
  mpParmObjectiveExpression = assertParameter("ObjectiveExpression", CCopasiParameter::Type::EXPRESSION, std::string(""));
  mpParmMaximize = assertParameter("Maximize", CCopasiParameter::Type::BOOL, false);
  mpParmRandomizeStartValues = assertParameter("Randomize Start Values", CCopasiParameter::Type::BOOL, false);
  mpParmCalculateStatistics = assertParameter("Calculate Statistics", CCopasiParameter::Type::BOOL, true);

  mpGrpItems = assertGroup("OptimizationItemList");
  mpGrpConstraints = assertGroup("OptimizationConstraintList");

  // only used by the GUI to display more information on opt methods during runs
  assertParameter("DisplayPoplations", CCopasiParameter::Type::BOOL, false);

  elevateChildren();
}

bool COptProblem::elevateChildren()
{
  // We need to handle the old file format which had two different task keys
  if (mpParmSubTaskCN != NULL)
    {
      CCopasiParameter * pParameter;

      if ((pParameter = getParameter("Steady-State")) != NULL)
        {
          if (pParameter->getValue< std::string >() != "")
            {
              setSubtaskType(CTaskEnum::Task::steadyState);
            }

          removeParameter("Steady-State");
        }

      if ((pParameter = getParameter("Time-Course")) != NULL)
        {
          if (pParameter->getValue< std::string >() != "")
            {
              setSubtaskType(CTaskEnum::Task::timeCourse);
            }

          removeParameter("Time-Course");
        }

      // If no subtask is defined we default to steady-state
      if (*mpParmSubTaskCN == "")
        {
          setSubtaskType(CTaskEnum::Task::steadyState);
        }
    }

  // Handle old file format in which the objective expression was stored in the function DB
  if (mpParmObjectiveExpression != NULL)
    {
      CCopasiParameter * pParameter = getParameter("ObjectiveFunction");
      CExpression * pObjectiveFunction = NULL;

      // We do not use the key to find the objective function because keys are not re-mapped
      // for unknown parameters, instead we rely on the uniqueness of the name and the fact that
      // this is the only expression in the list.
      size_t Index = CRootContainer::getFunctionList()->loadedFunctions().getIndex("Objective Function");

      if (Index != C_INVALID_INDEX)
        {
          pObjectiveFunction =
            dynamic_cast<CExpression *>(&CRootContainer::getFunctionList()->loadedFunctions()[Index]);
        }

      if (pObjectiveFunction != NULL &&
          pParameter != NULL)
        {
          *mpParmObjectiveExpression = pObjectiveFunction->getInfix();

          removeParameter("ObjectiveFunction");
        }
    }

  setObjectiveFunction(mpParmObjectiveExpression != NULL ? *mpParmObjectiveExpression : "");

  mpGrpItems =
    elevate<CCopasiParameterGroup, CCopasiParameterGroup>(mpGrpItems);

  if (!mpGrpItems) return false;

  std::vector< CCopasiParameter * > * pValue =
    &mpGrpItems->CCopasiParameter::getValue< CCopasiParameterGroup::elements >();

  index_iterator it = pValue->begin();
  index_iterator end = pValue->end();

  for (; it != end; ++it)
    if (!elevate<COptItem, CCopasiParameterGroup>(*it)) return false;

  mpOptItems = &mpGrpItems->CCopasiParameter::getValue< std::vector< COptItem * > >();

  mpGrpConstraints =
    elevate<CCopasiParameterGroup, CCopasiParameterGroup>(mpGrpConstraints);

  if (!mpGrpConstraints) return false;

  pValue = &mpGrpConstraints->CCopasiParameter::getValue< CCopasiParameterGroup::elements >();

  it = pValue->begin();
  end = pValue->end();

  for (; it != end; ++it)
    if (!elevate<COptItem, CCopasiParameterGroup>(*it)) return false;

  mpConstraintItems =
    &mpGrpConstraints->CCopasiParameter::getValue< std::vector< COptItem * > >();

  return true;
}

void COptProblem::reset()
{
  mSolutionValue = (*mpParmMaximize ? - std::numeric_limits<C_FLOAT64>::infinity() : std::numeric_limits<C_FLOAT64>::infinity());
  mCounters = sCounter();
}

bool COptProblem::setCallBack(CProcessReportLevel callBack)
{
  bool success = CCopasiProblem::setCallBack(callBack);

  if (mpSubTask != NULL)
    {
      success &= mpSubTask->setCallBack(mProcessReport);
    }

  if (mProcessReport)
    {
      reset();

      // We need to reset mSolutionValue to correctly initialize the progress item.
      mhSolutionValue =
        mProcessReport.addItem("Best Value",
                               mSolutionValue);
      // We need to reset mCounter to correctly initialize the progress item.
      mhCounter =
        mProcessReport.addItem("Function Evaluations",
                               mCounters.Counter);
    }
  else
    {
      mhSolutionValue = C_INVALID_INDEX;
      mhCounter = C_INVALID_INDEX;
    }

  return true;
}

void COptProblem::initObjects()
{
  addObjectReference("Function Evaluations", mCounters.Counter, CDataObject::ValueInt);
  addObjectReference("Best Value", mSolutionValue, CDataObject::ValueDbl);
  addVectorReference("Best Parameters", mSolutionVariables, CDataObject::ValueDbl);
}

void COptProblem::signalMathContainerChanged()
{
  CCopasiProblem::signalMathContainerChanged();
}

bool COptProblem::initializeSubtaskBeforeOutput()
{
  mpSubTaskSrc = getSubTask();

  pdelete(mpSubTask);
  mpSubTask = CTaskFactory::copy(mpSubTaskSrc, this);

  try
    {
      if (mpSubTask != NULL)
        {
          mpSubTask->setMathContainer(mpContainer);
          mpSubTask->setCallBack(mProcessReport);

          return mpSubTask->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);
        }
    }

  catch (...)
    {
      return false;
    }

  return true;
}

bool COptProblem::initialize()
{
  mWorstValue = std::numeric_limits<C_FLOAT64>::infinity();

  if (*mpParmMaximize)
    {
      mWorstValue *= -1.0;
    }

  if (mpContainer == NULL) return false;

  bool success = true;

  mpReport = NULL;

  mCounters = sCounter();

  mSolutionValue = mWorstValue;

  CObjectInterface::ContainerList ContainerList;
  ContainerList.push_back(mpContainer);

  COptTask * pTask = dynamic_cast< COptTask * >(getObjectParent());

  if (pTask)
    {
      ContainerList.push_back(pTask);
      mpReport = &pTask->getReport();

      if (!mpReport->getStream()) mpReport = NULL;
    }

  if (mpSubTaskSrc != NULL)
    ContainerList.push_back(mpSubTaskSrc);

  size_t Size = mpOptItems->size();

  mOptItem2Index.clear();

  mSolutionVariables.resize(Size);
  mOriginalVariables.resize(Size);

  mSolutionVariables = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mOriginalVariables = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  if (mpOptItems->size() == 0 && pTask->getMethod()->getSubType() != CTaskEnum::Method::Statistics)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 6);
      return false;
    }

  CObjectInterface::ObjectSet ItemObjects;
  CObjectInterface::ObjectSet ItemObjectsWithVaryingInterval;

  mPrerequisits.clear();
  size_t i = 0;

  for (COptItem * pOptItem : *mpOptItems)
    {
      success &= pOptItem->compile(ContainerList);

      if (pOptItem->getPrerequisites().size() > 0)
        {
          ItemObjectsWithVaryingInterval.insert(pOptItem);
          mPrerequisits.insert(pOptItem);
        }

      if (success)
        {
          if (!pOptItem->isInitialValue())
            return false;

          ItemObjects.insert(pOptItem->getItemObject());
          mOriginalVariables[i] = pOptItem->getItemValue();
        }
      else
        {
          mOriginalVariables[i] = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
        }

      mOptItem2Index[pOptItem] = i++;
    }

  CMathDependencyGraph IntervalDependencies(mpContainer);
  IntervalDependencies.addObject(this);

  // std::ofstream Boundaries("IntervalDependencies.dot");
  // IntervalDependencies.exportDOTFormat(Boundaries, "IntervalDependencies");
  // Boundaries.close();

  std::vector< COptItem * > ItemsInfluencingIntervals;
  for (COptItem * pOptItem : *mpOptItems)
    if (IntervalDependencies.contains(pOptItem->getItemObject()))
      ItemsInfluencingIntervals.push_back(pOptItem);

  mCountInfluencingIntervals = ItemsInfluencingIntervals.size();
  CObjectInterface::ObjectSet ChangedObjects;

  CObjectInterface::ObjectSet Requested;
  Requested.insert(this);

  for (COptItem * pOptItem : ItemsInfluencingIntervals)
    {
      CCore::CUpdateSequence UpdateIntervals;
      CObjectInterface::ObjectSet ChangedObject;
      ChangedObject.insert(pOptItem->getItemObject());
      ChangedObjects.insert(pOptItem->getItemObject());

      IntervalDependencies.getUpdateSequence(UpdateIntervals, CCore::SimulationContext::UpdateMoieties, ChangedObject, ItemObjectsWithVaryingInterval);
      pOptItem->setIntervalUpdateSequence(UpdateIntervals);

      for (const CObjectInterface * pObject : UpdateIntervals)
        {
          if (dynamic_cast< const COptItem * >(pObject) != nullptr)
            pOptItem->addDependentItem(static_cast< COptItem * >(const_cast< CObjectInterface * >(pObject)));
        }
    }

  IntervalDependencies.getUpdateSequence(mUpdateIntervals, CCore::SimulationContext::UpdateMoieties, ChangedObjects, Requested);

  ChangedObjects.erase(NULL);
  mpContainer->getInitialDependencies().getUpdateSequence(mInitialRefreshSequence, CCore::SimulationContext::UpdateMoieties, ItemObjects, mpContainer->getInitialStateObjects());

  // Sort OptItems so that the items influencing intervals appear first and before all its dependents
  mOptItemAlgorithm.clear();
  mSolutionVariablesAlgorithm.resize(Size);
  mSolutionVariablesAlgorithm = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  CObjectInterface::ObjectSet ItemDealtWith;

  // Influencing items with fixed interval
  for (COptItem * pOptItem : ItemsInfluencingIntervals)
    if (pOptItem->getPrerequisites().empty())
      {
        ItemDealtWith.insert(pOptItem);
        mOptItemAlgorithm.push_back(pOptItem);
      }

  // Influencing items with varying interval
  for (const CObjectInterface * pObject : mUpdateIntervals)
    if (ItemDealtWith.find(pObject) == ItemDealtWith.end()
        && dynamic_cast< const COptItem * >(pObject) != nullptr
        && !static_cast< const COptItem * >(pObject)->getDependentItems().empty())
      {
        ItemDealtWith.insert(static_cast< const COptItem * >(pObject));
        mOptItemAlgorithm.push_back(static_cast< COptItem * >(const_cast< CObjectInterface * >(pObject)));
      }

  // Items with varying interval
  for (const CObjectInterface * pObject : mUpdateIntervals)
    if (ItemDealtWith.find(pObject) == ItemDealtWith.end()
        && dynamic_cast< const COptItem * >(pObject) != nullptr)
      {
        ItemDealtWith.insert(static_cast< const COptItem * >(pObject));
        mOptItemAlgorithm.push_back(static_cast< COptItem * >(const_cast< CObjectInterface * >(pObject)));
      }

  // Items with fixed interval
  for (COptItem * pOptItem : *mpOptItems)
    if (ItemDealtWith.find(pOptItem) == ItemDealtWith.end())
      {
        mOptItemAlgorithm.push_back(pOptItem);
      }

  assert(mOptItemAlgorithm.size() == mpOptItems->size());

  i = 0;

  if (!adjustStartValuesForIntervals())
    CCopasiMessage(CCopasiMessage::WARNING, MCOptimization + 13);

  std::vector< COptItem * >::iterator it = mpConstraintItems->begin();
  std::vector< COptItem * >::iterator end = mpConstraintItems->end();

  // We need to build a refresh sequence so the constraint values are updated
  CObjectInterface::ObjectSet Objects;

  for (i = 0; it != end; ++it, i++)
    {
      success &= (*it)->compile(ContainerList);

      if ((*it)->getItemObject() != NULL)
        {
          Objects.insert((*it)->getItemObject());
        }
    }

  mpContainer->getTransientDependencies().getUpdateSequence(mUpdateConstraints, CCore::SimulationContext::Default, mpContainer->getStateObjects(false), Objects, mpContainer->getSimulationUpToDateObjects());

  mCPUTime.start();

  // Sanity
  if (mpObjectiveExpression == NULL ||
      mpObjectiveExpression->getInfix() == "" ||
      !mpObjectiveExpression->compile(ContainerList) ||
      !mpObjectiveExpression->mapObjectNodes(mpSubTaskSrc, mpSubTask))
    {
      mUpdateObjectiveFunction.clear();
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 5);
      return false;
    }

  // The objective function refers result of the src subtask we need to map to them to results of the copy.
  pdelete(mpMathObjectiveExpression);

  mpMathObjectiveExpression = new CMathExpression(*mpObjectiveExpression, *mpContainer, false);
  Objects = mpMathObjectiveExpression->getPrerequisites();
  mpContainer->getTransientDependencies().getUpdateSequence(mUpdateObjectiveFunction, CCore::SimulationContext::Default, mpContainer->getStateObjects(false), Objects, mpContainer->getSimulationUpToDateObjects());

  // Transfer ownership from the math container to the problem to avoid deletion.
  add(mpMathObjectiveExpression, true);

  return success;
}

void COptProblem::updateContainer(const bool & update)
{
  std::vector<COptItem*>::iterator it = mpOptItems->begin();
  std::vector<COptItem*>::iterator end = mpOptItems->end();
  C_FLOAT64 *pRestore = (update && mSolutionValue != mWorstValue) ? mSolutionVariables.array() : mOriginalVariables.array();

  for (; it != end; ++it, ++pRestore)
    {
      (*it)->setItemValue(*pRestore, COptItem::CheckPolicyFlag::None);
    }
}

// virtual
CCopasiTask * COptProblem::getSubTask() const
{
  // We have a CFitProblem for which it is OK not to have a subtask.
  if (mpParmSubTaskCN == NULL)
    return NULL;

  CObjectInterface::ContainerList ListOfContainer;
  ListOfContainer.push_back(getObjectAncestor("Vector"));

  return dynamic_cast< CCopasiTask * >(CObjectInterface::GetObjectFromCN(ListOfContainer, *mpParmSubTaskCN));
}

bool COptProblem::restore(const bool & updateModel)
{
  bool success = true;

  if (mpSubTask != NULL)
    {
      success &= mpSubTask->restore(updateModel);
    }

  updateContainer(updateModel);
  mpContainer->applyUpdateSequence(mInitialRefreshSequence);
  mpContainer->pushInitialState();

  // Update the start values
  if (updateModel && mSolutionValue != mWorstValue)
    {
      std::vector< COptItem * >::iterator it = mpOptItems->begin();
      std::vector< COptItem * >::iterator end = mpOptItems->end();
      C_FLOAT64 * pSolution = mSolutionVariables.array();

      for (; it != end; ++it, ++pSolution)
        {
          (*it)->setStartValue(*pSolution);
        }
    }

  if ((mCounters.FailedCounterException + mCounters.FailedCounterNaN) * 20 > mCounters.Counter) // > 5% failure rate
    CCopasiMessage(CCopasiMessage::WARNING, MCOptimization + 8, mCounters.FailedCounterException + mCounters.FailedCounterNaN, mCounters.Counter);

  if (10 * mCounters.FailedConstraintCounter > 8 * (mCounters.ConstraintCounter - 1)) // > 80 % failure rate
    CCopasiMessage(CCopasiMessage::WARNING, MCOptimization + 9, mCounters.FailedConstraintCounter, mCounters.ConstraintCounter - 1);

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

C_FLOAT64 COptProblem::getParametricConstraintsViolation()
{
  C_FLOAT64 L2norm = 0.0;

  std::vector< COptItem * >::const_iterator it = mpOptItems->begin();
  std::vector< COptItem * >::const_iterator end = mpOptItems->end();

  for (; it != end; ++it)
    {
      C_FLOAT64 Violation = (*it)->getConstraintViolation();
      L2norm += Violation * Violation;
    }

  return sqrt(L2norm);
}

bool COptProblem::checkFunctionalConstraints()
{
  // Make sure the constraint values are up to date.
  mpContainer->applyUpdateSequence(mUpdateConstraints);

  std::vector< COptItem * >::const_iterator it = mpConstraintItems->begin();
  std::vector< COptItem * >::const_iterator end = mpConstraintItems->end();

  if (!mpConstraintItems->empty())
    mCounters.ConstraintCounter++;

  for (; it != end; ++it)
    if ((*it)->checkConstraint())
      {
        mCounters.FailedConstraintCounter++;
        return false;
      }

  return true;
}

C_FLOAT64 COptProblem::getFunctionalConstraintsViolation()
{
  C_FLOAT64 L2norm = 0.0;

  // Make sure the constraint values are up to date.
  mpContainer->applyUpdateSequence(mUpdateConstraints);

  std::vector< COptItem * >::const_iterator it = mpConstraintItems->begin();
  std::vector< COptItem * >::const_iterator end = mpConstraintItems->end();

  if (!mpConstraintItems->empty())
    mCounters.ConstraintCounter++;

  for (; it != end; ++it)
    {
      C_FLOAT64 Violation = (*it)->getConstraintViolation();
      L2norm += Violation * Violation;
    }

  if (L2norm > 0.0)
    mCounters.FailedConstraintCounter++;

  return sqrt(L2norm);
}

// virtual
bool  COptProblem::checkIntervals()
{
  mpContainer->applyUpdateSequence(mUpdateIntervals);

  return mMinInterval >= 0.0;
}

bool COptProblem::adjustStartValuesForIntervals()
{
  if (mCountInfluencingIntervals == 0)
    return true;

  CVector< C_FLOAT64 > InitialState = mpContainer->getCompleteInitialState();

  bool success = true;
  std::vector< COptItem * >::iterator it = mOptItemAlgorithm.begin();
  std::vector< COptItem * >::iterator end = it + mCountInfluencingIntervals;

  for (; it != end; ++it)
    {
      // std::cout << *it << ": " << (*it)->getObjectDisplayName() << ": " <<  (*it)->getStartValue() << std::endl;
      C_FLOAT64 Value = (*it)->getStartValue();
      success &= (*it)->setItemValue(Value, COptItem::CheckPolicyFlag::All);
    }

  mpContainer->setCompleteInitialState(InitialState);

  return success;
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
  mCounters.Counter++;
  bool success = false;
  COutputHandler * pOutputHandler = NULL;

  if (mpSubTask == NULL)
    return false;

  if (mStoreResults &&
      mpSubTask->getType() == CTaskEnum::Task::timeCourse)
    {
      static_cast< CTrajectoryProblem * >(mpSubTask->getProblem())->setTimeSeriesRequested(true);

      pOutputHandler = new COutputHandler();
      mpSubTask->initialize(CCopasiTask::ONLY_TIME_SERIES, pOutputHandler, NULL);
    }

  try
    {
      mpContainer->applyUpdateSequence(mInitialRefreshSequence);
      // Update all initial values which depend on the optimization items.

      success = mpSubTask->process(true);

      mpContainer->applyUpdateSequence(mUpdateObjectiveFunction);

      // Each thread has it's own container and thus objective expression
      mCalculateValue = *mpParmMaximize ? -mpMathObjectiveExpression->value() : mpMathObjectiveExpression->value();
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
      mpSubTask->getType() == CTaskEnum::Task::timeCourse)
    {
      mStoreResults = false;
      mpSubTask->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);
      pdelete(pOutputHandler);
    }

  if (!success)
    {
      mCounters.FailedCounterException++;
      mCalculateValue = std::numeric_limits< C_FLOAT64 >::infinity();
    }

  if (std::isnan(mCalculateValue))
    {
      mCounters.FailedCounterNaN++;
      mCalculateValue = std::numeric_limits< C_FLOAT64 >::infinity();
    }

  if (mProcessReport)
    return mProcessReport.progressItem(mhCounter);

  return true;
}

bool COptProblem::calculateStatistics(const C_FLOAT64 & factor,
                                      const C_FLOAT64 & resolution)
{
  // Set the current values to the solution values.
  size_t imax = mSolutionVariables.size();

  mGradient.resize(imax);
  mGradient = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  std::vector< COptItem * >::const_iterator it = mpOptItems->begin();
  std::vector< COptItem * >::const_iterator end = mpOptItems->end();
  C_FLOAT64 *pSolution = mSolutionVariables.array();

  for (; it != end; ++it, ++pSolution)
    {
      (*it)->setItemValue(*pSolution, COptItem::CheckPolicyFlag::None);
    }

  mpContainer->applyUpdateSequence(mInitialRefreshSequence);

  // This is necessary so that the result can be displayed.
  mStoreResults = true;
  calculate();
  mStoreResults = false;

  // Make sure the timer is accurate.
  mCPUTime.calculateValue();

  if (mSolutionValue == mWorstValue)
    return false;

  if (*mpParmCalculateStatistics)
    {
      mHaveStatistics = true;

      C_FLOAT64 Current;
      C_FLOAT64 Delta;

      // Calculate the gradient
      it = mpOptItems->begin();
      pSolution = mSolutionVariables.array();
      C_FLOAT64 * pGradient = mGradient.array();

      for (; it != end; ++it, ++pSolution, ++pGradient)
        {
          Current = *pSolution;

          if (fabs(Current) > resolution)
            {
              C_FLOAT64 X = Current * (1.0 + factor);
              (*it)->setItemValue(X, COptItem::CheckPolicyFlag::None);
              Delta = 1.0 / (X - Current);
            }
          else
            {
              C_FLOAT64 X = resolution;
              (*it)->setItemValue(X, COptItem::CheckPolicyFlag::None);
              Delta = 1.0 /  (X - resolution);
            }

          mpContainer->applyUpdateSequence(mInitialRefreshSequence);

          calculate();

          *pGradient = ((*mpParmMaximize ? -mCalculateValue : mCalculateValue) - mSolutionValue) * Delta;

          // Restore the value
          (*it)->setItemValue(Current, COptItem::CheckPolicyFlag::None);
        }

      mpContainer->applyUpdateSequence(mInitialRefreshSequence);
      calculate();

      // Make sure the timer is accurate.
      mCPUTime.calculateValue();
    }

  return true;
}

const C_FLOAT64 & COptProblem::getCalculateValue() const
{return mCalculateValue;}

const CVector< C_FLOAT64 > & COptProblem::getSolutionVariables(const bool & algorithmOrder) const
{
  return algorithmOrder ? mSolutionVariablesAlgorithm : mSolutionVariables;
}

const CVector< C_FLOAT64 > & COptProblem::getVariableGradients() const
{return mGradient;}

bool COptProblem::setSolution(const C_FLOAT64 & value,
                              const CVector< C_FLOAT64 > & variables,
                              const bool & algorithmOrder)
{
  mSolutionValue = *mpParmMaximize ? -value : value;

  // The initialization call from SRES and GASR have NULL as variables
  if (variables.size() != 0)
    if (algorithmOrder)
      {
        mSolutionVariablesAlgorithm = variables;
        C_FLOAT64 * pVariable = mSolutionVariablesAlgorithm.begin();

        for (COptItem * pOptItem : mOptItemAlgorithm)
          mSolutionVariables[mOptItem2Index[pOptItem]] = *pVariable++;
      }
    else
      {
        mSolutionVariables = variables;
        C_FLOAT64 * pVariable = mSolutionVariablesAlgorithm.begin();

        for (COptItem * pOptItem : mOptItemAlgorithm)
          *pVariable++ = mSolutionVariables[mOptItem2Index[pOptItem]];
      }

  bool Continue = true;

  if (value == -std::numeric_limits< C_FLOAT64 >::infinity())
    Continue = false;

  if (mProcessReport)
    Continue &= mProcessReport.progressItem(mhSolutionValue);

  return Continue;
}

const C_FLOAT64 & COptProblem::getSolutionValue() const
{
  return mSolutionValue;
}

COptItem & COptProblem::getOptConstraint(const size_t & index)
{
  return *(*mpConstraintItems)[index];
}

size_t COptProblem::getOptConstraintSize() const
{
  return mpGrpConstraints->size();
}

COptItem & COptProblem::addOptConstraint(const CRegisteredCommonName & objectCN)
{
  CDataModel * pDataModel = getObjectDataModel();
  assert(pDataModel != NULL);

  COptItem * pItem = new COptItem(pDataModel);
  pItem->setObjectCN(objectCN);

  mpGrpConstraints->addParameter(pItem);

  return *pItem;
}

bool COptProblem::removeOptConstraint(const size_t & index)
{
  return mpGrpConstraints->removeParameter(index);
}

COptItem & COptProblem::getOptItem(const size_t & index)
{return *(*mpOptItems)[index];}

size_t COptProblem::getOptItemSize() const
{return mpGrpItems->size();}

COptItem & COptProblem::addOptItem(const CRegisteredCommonName & objectCN)
{
  CDataModel* pDataModel = getObjectDataModel();
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

const std::vector< COptItem * > & COptProblem::getOptItemList(const bool & algorithmOrder) const
{
  return algorithmOrder ? mOptItemAlgorithm : *mpOptItems;
}

const std::vector< COptItem * > & COptProblem::getConstraintList() const
{return *mpConstraintItems;}

void COptProblem::setParameters(const CVectorCore< C_FLOAT64 > & parameters)
{
  std::vector< COptItem * >::const_iterator it = mpOptItems->begin();
  std::vector< COptItem * >::const_iterator end = mpOptItems->end();
  const C_FLOAT64 *pParameter = parameters.begin();

  for (; it != end; ++it, ++pParameter)
    {
      C_FLOAT64 Parameter = *pParameter;
      (*it)->setItemValue(Parameter, COptItem::CheckPolicyFlag::None);
    }
}

bool COptProblem::setObjectiveFunction(const std::string & infix)
{
  if (mpParmObjectiveExpression == NULL) return false;

  *mpParmObjectiveExpression = infix;

  if (mpObjectiveExpression == NULL)
    mpObjectiveExpression = new CExpression("Expression", this);

  return mpObjectiveExpression->setInfix(infix);
}

const std::string COptProblem::getObjectiveFunction()
{
  if (mpParmObjectiveExpression == NULL)
    return "";

  if (mpObjectiveExpression != NULL)
    {
      mpObjectiveExpression->updateInfix();
      *mpParmObjectiveExpression = mpObjectiveExpression->getInfix();
    }

  return *mpParmObjectiveExpression;
}

CRegisteredCommonName COptProblem::setSubtaskType(const CTaskEnum::Task & subtaskType)
{
  CDataVectorN< CCopasiTask > * pTasks =
    dynamic_cast< CDataVectorN< CCopasiTask > *>(getObjectAncestor("Vector"));

  CDataModel* pDataModel = getObjectDataModel();

  if (pTasks == NULL && pDataModel)
    pTasks = pDataModel->getTaskList();

  if (pTasks)
    {
      CDataVectorN< CCopasiTask >::const_iterator it = pTasks->begin();
      CDataVectorN< CCopasiTask >::const_iterator end = pTasks->end();

      for (; it != end; ++it)
        if (it->getType() == subtaskType)
          {
            if (mpParmSubTaskCN != NULL)
              {
                *mpParmSubTaskCN = it->getCN();
                mpSubTaskSrc = getSubTask();
              }

            return it->getCN();
          }
    }

  return CRegisteredCommonName();
}

CTaskEnum::Task COptProblem::getSubtaskType() const
{
  if (mpSubTaskSrc != NULL)
    return mpSubTaskSrc->getType();

  return CTaskEnum::Task::UnsetTask;
}

void COptProblem::setMaximize(const bool & maximize)
{
  *mpParmMaximize = maximize;
}

const bool & COptProblem::maximize() const
{
  return *mpParmMaximize;
}

void COptProblem::setRandomizeStartValues(const bool & randomize)
{
  *mpParmRandomizeStartValues = randomize;
}

const bool & COptProblem::getRandomizeStartValues() const
{
  return *mpParmRandomizeStartValues;
}

void COptProblem::randomizeStartValues()
{
  if (*mpParmRandomizeStartValues)
    {
      std::vector< COptItem * >::iterator it = mpOptItems->begin();
      std::vector< COptItem * >::iterator end = mpOptItems->end();

      for (; it != end; ++it)
        {
          (*it)->setStartValue((*it)->getRandomValue(&mpContainer->getRandomGenerator()));
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
{return mCounters.Counter;}

const unsigned C_INT32 & COptProblem::getConstraintEvaluations() const
{
  return mCounters.ConstraintCounter;
}

const COptProblem::sCounter & COptProblem::getCounters() const
{
  return mCounters;
}

void COptProblem::incrementCounters(const COptProblem::sCounter & increment)
{
  mCounters.Counter += increment.Counter;
  mCounters.FailedCounterException += increment.FailedCounterException;
  mCounters.FailedCounterNaN += increment.FailedCounterNaN;
  mCounters.ConstraintCounter += increment.ConstraintCounter;
  mCounters.FailedConstraintCounter += increment.FailedConstraintCounter;

  if (mProcessReport)
    mProcessReport.progressItem(mhCounter);
}

void COptProblem::resetCounters()
{
  mCounters = sCounter();
}

const unsigned C_INT32 & COptProblem::getFailedEvaluationsExc() const
{return mCounters.FailedCounterException;}

const unsigned C_INT32 & COptProblem::getFailedEvaluationsNaN() const
{return mCounters.FailedCounterNaN;}

const unsigned C_INT32 & COptProblem::geFailedConstraintCounter() const
{
  return mCounters.FailedConstraintCounter;
}

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

  os << "    Objective Function Value:\t" << mSolutionValue << "\n";

  CCopasiTimeVariable CPUTime = const_cast<COptProblem *>(this)->mCPUTime.getElapsedTime();

  os << "    Function Evaluations:\t" << mCounters.Counter << "\n";
  os << "    CPU Time [s]:\t"
     << CCopasiTimeVariable::LL2String(CPUTime.getSeconds(), 1) << "."
     << CCopasiTimeVariable::LL2String(CPUTime.getMilliSeconds(true), 3) << "\n";
  os << "    Evaluations/Second [1/s]:\t" << mCounters.Counter / (C_FLOAT64)(CPUTime.getMilliSeconds() / 1e3) << "\n";
  os << "\n";

  std::vector< COptItem * >::const_iterator itItem =
    mpOptItems->begin();
  std::vector< COptItem * >::const_iterator endItem =
    mpOptItems->end();

  size_t i;

  for (i = 0; itItem != endItem; ++itItem, i++)
    {
      os << "    " << (*itItem)->getObjectDisplayName() << ": "
         << mSolutionVariables[i] << "\n";
    }
}

std::ostream &operator<<(std::ostream &os, const COptProblem & o)
{
  os << "Problem Description:" << "\n";

  os << "Subtask: " << "\n";

  if (o.mpSubTask)
    o.mpSubTask->getDescription().print(&os);
  else
    os << "No Subtask specified.";

  os << "\n";

  if (o.mpObjectiveExpression)
    {
      os << "Objective Function:" << "\n";
      os << "    " << o.mpObjectiveExpression->getDisplayString() << "\n";
      os << std:: endl;
    }

  os << "List of Optimization Items:" << "\n";

  std::vector< COptItem * >::const_iterator itItem =
    o.mpOptItems->begin();
  std::vector< COptItem * >::const_iterator endItem =
    o.mpOptItems->end();

  for (; itItem != endItem; ++itItem)
    os << "    " << **itItem << "\n";

  os << "\n";
  os << "List of Constraint Items:" << "\n";

  itItem = o.mpConstraintItems->begin();
  endItem = o.mpConstraintItems->end();

  for (; itItem != endItem; ++itItem)
    os << "    " << **itItem << "\n";

  return os;
}
