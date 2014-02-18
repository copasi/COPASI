// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <limits>

#include "copasi.h"

#include "CProcessQueue.h"
#include "CMathModel.h"

#include "function/CExpression.h"

#include <copasi/report/CCopasiRootContainer.h>
#include <copasi/commandline/CConfigurationFile.h>

CProcessQueue::CKey::CKey() :
  mExecutionTime(0.0),
  mCascadingLevel(0),
  mEquality(false),
  mOrder(0),
  mEventId(std::numeric_limits<size_t>::max())
{}

CProcessQueue::CKey::CKey(const CKey & src) :
  mExecutionTime(src.mExecutionTime),
  mCascadingLevel(src.mCascadingLevel),
  mEquality(src.mEquality),
  mOrder(src.mOrder),
  mEventId(src.mEventId)
{}

CProcessQueue::CKey::CKey(const C_FLOAT64 & executionTime,
                          const bool & equality,
                          const size_t & order,
                          const size_t & eventId,
                          const size_t & cascadingLevel) :
  mExecutionTime(executionTime),
  mCascadingLevel(cascadingLevel),
  mEquality(equality),
  mOrder(order),
  mEventId(eventId)
{}

CProcessQueue::CKey::~CKey()
{}

bool CProcessQueue::CKey::operator < (const CProcessQueue::CKey & rhs) const
{
  if (mExecutionTime != rhs.mExecutionTime)
    return mExecutionTime < rhs.mExecutionTime;

  if (mCascadingLevel != rhs.mCascadingLevel)
    return mCascadingLevel > rhs.mCascadingLevel;

  if (mEquality != rhs.mEquality)
    return mEquality;

  if (mOrder != rhs.mOrder)
    return mOrder < rhs.mOrder;

  return mEventId < rhs.mEventId;
}

//*********************************************************

CProcessQueue::CAction::CAction() :
  mpTarget(NULL),
  mValue(),
  mpExpression(NULL),
  mpEvent(NULL),
  mpProcessQueue(NULL)
{}

CProcessQueue::CAction::CAction(const CAction & src) :
  mpTarget(src.mpTarget),
  mValue(src.mValue),
  mpExpression(src.mpExpression),
  mpEvent(src.mpEvent),
  mpProcessQueue(src.mpProcessQueue)
{}

CProcessQueue::CAction::CAction(C_FLOAT64 * pTarget,
                                const C_FLOAT64 & value,
                                CMathEvent * pEvent,
                                CProcessQueue * pProcessQueue) :
  mpTarget(pTarget),
  mValue(value),
  mpExpression(NULL),
  mpEvent(pEvent),
  mpProcessQueue(pProcessQueue)
{}

CProcessQueue::CAction::CAction(C_FLOAT64 * pTarget,
                                CExpression * pExpression,
                                CMathEvent * pEvent,
                                CProcessQueue * pProcessQueue) :
  mpTarget(pTarget),
  mValue(),
  mpExpression(pExpression),
  mpEvent(pEvent),
  mpProcessQueue(pProcessQueue)
{}

CProcessQueue::CAction::~CAction()
{}

void CProcessQueue::CAction::process(const size_t & eventId)
{
  // If the expression pointer is not NULL we have a calculation.
  if (mpExpression != NULL)
    {
      // Calculate the execution time for delayed events.
      C_FLOAT64 AssignmentTime = mpEvent->getAssignmentTime(mpProcessQueue->mTime);

      mpProcessQueue->addAssignment(AssignmentTime,
                                    mpProcessQueue->mEquality,
                                    mpEvent->getOrder(),
                                    eventId,
                                    mpTarget,
                                    mpExpression->calcValue(),
                                    mpEvent);
    }
  else
    {
      C_INT32 result = 0;

      //there may be special events in the queue that do
      //not have an assignment at all
      //These are represented by a CAction without target
      if (mpTarget)
        {
          *mpTarget = mValue;
        }

      if (mpProcessQueue->mpEventCallBack)
        (*mpProcessQueue->mpEventCallBack)(mpProcessQueue->mpCallbackTask, mpEvent->getType());
    }
}

//*********************************************************

CProcessQueue::CProcessQueue() :
  mCalculations(),
  mAssignments(),
  mExecutionLimit(10000),
  mExecutionCounter(0),
  mTime(0.0),
  mEquality(true),
  mCascadingLevel(0),
  mSimultaneousAssignments(false),
  mEventIdSet(),
  mpMathModel(NULL),
  mRootsFound(0),
  mRootValues1(0),
  mRootValues2(0),
  mpRootValuesBefore(&mRootValues1),
  mpRootValuesAfter(&mRootValues2),
  mpResolveSimultaneousAssignments(NULL),
  mpCallbackTask(NULL),
  mpEventCallBack(NULL)
{}

CProcessQueue::CProcessQueue(const CProcessQueue & src):
  mCalculations(src.mCalculations),
  mAssignments(src.mAssignments),
  mExecutionLimit(src.mExecutionLimit),
  mExecutionCounter(src.mExecutionCounter),
  mTime(src.mTime),
  mEquality(src.mEquality),
  mCascadingLevel(src.mCascadingLevel),
  mSimultaneousAssignments(src.mSimultaneousAssignments),
  mEventIdSet(src.mEventIdSet),
  mpMathModel(src.mpMathModel),
  mRootsFound(src.mRootsFound),
  mRootValues1(src.mRootValues1),
  mRootValues2(src.mRootValues2),
  mpRootValuesBefore(&src.mRootValues1 == src.mpRootValuesBefore ? &mRootValues1 : &mRootValues2),
  mpRootValuesAfter(&src.mRootValues1 == src.mpRootValuesAfter ? &mRootValues1 : &mRootValues2),
  mpResolveSimultaneousAssignments(src.mpResolveSimultaneousAssignments),
  mpCallbackTask(src.mpCallbackTask),
  mpEventCallBack(src.mpEventCallBack)
{}

CProcessQueue::~CProcessQueue()
{}

bool CProcessQueue::addAssignment(const C_FLOAT64 & executionTime,
                                  const bool & equality,
                                  const size_t & order,
                                  const size_t & eventId,
                                  C_FLOAT64 * pTarget,
                                  const C_FLOAT64 & value,
                                  CMathEvent * pEvent)
{
  // It is not possible to proceed backwards in time.
  if (executionTime < mTime) return false;

  size_t CascadingLevel = mCascadingLevel;

  if (executionTime > mTime)
    CascadingLevel = 0;

  mAssignments.insert(std::make_pair(CKey(executionTime,
                                          equality,
                                          order,
                                          eventId,
                                          CascadingLevel),
                                     CAction(pTarget, value, pEvent, this)));

  return true;
}

bool CProcessQueue::addCalculation(const C_FLOAT64 & executionTime,
                                   const bool & equality,
                                   const size_t & order,
                                   const size_t & eventId,
                                   C_FLOAT64 * pTarget,
                                   CExpression * pExpression,
                                   CMathEvent * pEvent)
{
  // It is not possible to proceed backwards in time.
  if (executionTime < mTime) return false;

  size_t CascadingLevel = mCascadingLevel;

  if (executionTime > mTime)
    CascadingLevel = 0;

  mCalculations.insert(std::make_pair(CKey(executionTime,
                                      equality,
                                      order,
                                      eventId,
                                      CascadingLevel),
                                      CAction(pTarget,
                                          pExpression,
                                          pEvent,
                                          this)));

  return true;
}

void CProcessQueue::initialize(CMathModel * pMathModel)
{
  mpMathModel = pMathModel;
  assert(mpMathModel != NULL);

  mTime = mpMathModel->getInitialTime();

  mCalculations.clear();
  mAssignments.clear();
  mEventIdSet.clear();
  mSimultaneousAssignments = false;

  size_t NumRoots = mpMathModel->getNumRoots();
  mRootsFound.resize(NumRoots);
  mRootsFound = 0;
  mRootValues1.resize(NumRoots);
  mRootValues2.resize(NumRoots);
  mpRootValuesBefore = &mRootValues1;
  mpRootValuesAfter = &mRootValues2;

  return;
}

bool CProcessQueue::process(const C_FLOAT64 & time,
                            const bool & priorToOutput,
                            resolveSimultaneousAssignments pResolveSimultaneousAssignments)
{
  if (getProcessQueueExecutionTime() > time)
    return false;

  mTime = time;
  mEquality = priorToOutput;
  mpResolveSimultaneousAssignments = pResolveSimultaneousAssignments;
  mExecutionCounter = 0;
  mCascadingLevel = 0;

  bool success = true;
  bool stateChanged = false;

  range Calculations = getCalculations();

  if (notEmpty(Calculations))
    {
      // Execute and remove all current calculations.
      success = executeCalculations(Calculations);
    }

  range Assignments = getAssignments();

  if (success &&
      notEmpty(Assignments))
    {
      mpMathModel->evaluateRoots(*mpRootValuesBefore, false);
      stateChanged = true;
    }

  // The algorithm below will work properly for user ordered events
  // as the queue enforces the proper ordering.
  while (success &&
         notEmpty(Assignments) &&
         mCascadingLevel != std::numeric_limits<size_t>::max())
    {
      // We switch to the next cascading level so that events triggered by the
      // execution of assignments are properly scheduled.
      mCascadingLevel++;

      // Execute and remove all current assignments.
      success = executeAssignments(Assignments);

      // We need to compare the roots before the execution and after
      // to determine which roots need to be charged.
      if (rootsFound())
        {
          // We have to deal with both types of found roots.
          mpMathModel->processRoots(mTime, mRootsFound);
        }

      // Note, applying the events may have added new events to the queue.
      // The setting of the equality flag for these events may be either true
      // or false.

      // First we handle equalities.
      mEquality = true;

      // Retrieve the pending calculations.
      Calculations = getCalculations();

      if (notEmpty(Calculations))
        {
          // Execute and remove all current calculations.
          success = executeCalculations(Calculations);
        }

      // Retrieve the pending assignments.
      Assignments = getAssignments();

      if (notEmpty(Assignments))
        continue;

      // If we are here there are no more calculations and assignments for equality
      // for this level.
      mEquality = false;

      // Retrieve the pending calculations.
      Calculations = getCalculations();

      if (notEmpty(Calculations))
        {
          // Execute and remove all current calculations.
          success = executeCalculations(Calculations);
        }

      // Retrieve the pending assignments.
      Assignments = getAssignments();

      while (!notEmpty(Assignments) &&
             mCascadingLevel > 0)
        {
          // If we are here we have no more calculations and assignment for this level.
          mCascadingLevel--;

          // This will only return assignments when we have resolution algorithms for
          // them.
          Assignments = getAssignments();
        }
    }

  if (mSimultaneousAssignments)
    {
      if (!CCopasiRootContainer::getConfiguration()->allowSimultaneousEventAssignments())
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCMathModel + 1);
          success = false;
        }
      else
        {
          CCopasiMessage(CCopasiMessage::WARNING_FILTERED, "CMathModel (1): Simultaneous event assignments encountered.");
        }
    }

  return stateChanged;
}

CProcessQueue::range CProcessQueue::getCalculations()
{
  range Calculations;

  CKey UpperBound(mTime, mEquality,
                  std::numeric_limits<size_t>::max(),
                  std::numeric_limits<size_t>::max(),
                  mCascadingLevel);

  Calculations.first = mCalculations.begin();

  if (Calculations.first != mCalculations.end() &&
      Calculations.first->first < UpperBound)
    {
      Calculations.second = mCalculations.upper_bound(Calculations.first->first);

      // Check whether we have a second set of assignments with a different ID.
      if (Calculations.second != mCalculations.end() &&
          Calculations.second->first < UpperBound)
        {
          if (!CCopasiRootContainer::getConfiguration()->allowSimultaneousEventAssignments())
            {
              mSimultaneousAssignments = true;

              // The resolution of simultaneous events is algorithm dependent.
              // The simulation routine should provide a call back function.
              if (mpResolveSimultaneousAssignments == NULL)
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCMathModel + 1);
                }

              return (*mpResolveSimultaneousAssignments)(mCalculations, mTime, mEquality, mCascadingLevel);
            }
          else
            {
              CCopasiMessage(CCopasiMessage::WARNING_FILTERED, "CMathModel (1): Simultaneous event assignments encountered.");
            }
        }
    }
  else
    {
      Calculations.first = Calculations.second = mCalculations.end();
    }

  return Calculations;
}

CProcessQueue::range CProcessQueue::getAssignments()
{
  range Assignments;
  CKey UpperBound(mTime, mEquality,
                  std::numeric_limits<size_t>::max(),
                  std::numeric_limits<size_t>::max(),
                  mCascadingLevel);

  Assignments.first = mAssignments.begin();

  if (Assignments.first != mAssignments.end() &&
      Assignments.first->first < UpperBound)
    {
      Assignments.second = mAssignments.upper_bound(Assignments.first->first);

      // Check whether we have a second set of assignments with a different ID.
      if (Assignments.second != mAssignments.end() &&
          Assignments.second->first < UpperBound)
        {
          if (!CCopasiRootContainer::getConfiguration()->allowSimultaneousEventAssignments())
            {
              mSimultaneousAssignments = true;

              // The resolution of simultaneous events is algorithm dependent.
              // The simulation routine should provide a call back function.
              if (mpResolveSimultaneousAssignments == NULL)
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCMathModel + 1);
                }

              return (*mpResolveSimultaneousAssignments)(mAssignments, mTime, mEquality, mCascadingLevel);
            }
          else
            {
              CCopasiMessage(CCopasiMessage::WARNING_FILTERED, "CMathModel (1): Simultaneous event assignments encountered.");
            }
        }
    }
  else
    {
      Assignments.first = Assignments.second = mAssignments.end();
    }

  return Assignments;
}

bool CProcessQueue::executeCalculations(CProcessQueue::range & calculations)
{
  bool success = true;

  iterator it = calculations.first;
  assert(it != mCalculations.end());

  size_t EventIdOld = it->first.getEventId();
  size_t EventIdNew = createEventId();

  CMathEvent * pEvent = it->second.mpEvent;

  // Assure that all values are up to date.
  pEvent->applyValueRefreshes();

  for (; it != calculations.second; ++it)
    {
      if (it->first.getEventId() != EventIdOld)
        {
          destroyEventId(EventIdOld);
          EventIdOld = it->first.getEventId();
          EventIdNew = createEventId();
        }

      it->second.process(EventIdNew);
    }

  destroyEventId(EventIdOld);
  mCalculations.erase(calculations.first, calculations.second);

  return success;
}

bool CProcessQueue::executeAssignments(CProcessQueue::range & assignments)
{
  bool success = (mExecutionCounter < mExecutionLimit);

  iterator it = assignments.first;
  assert(it != mAssignments.end());

  size_t EventIdOld = it->first.getEventId();
  size_t EventIdNew = 0;

  CMathEvent * pEvent = it->second.mpEvent;

  EventIdNew = createEventId();

  for (; it != assignments.second; ++it)
    it->second.process(EventIdNew);

  destroyEventId(EventIdOld);
  mAssignments.erase(assignments.first, assignments.second);

  // Update all dependent values.
  pEvent->applyDependentRefreshes();

  mExecutionCounter++;

  return success;
}

bool CProcessQueue::rootsFound()
{
  bool rootsFound = false;

  // Calculate the current root values
  mpMathModel->evaluateRoots(*mpRootValuesAfter, false);

  // Compare the root values before and after;
  C_INT * pRootFound = mRootsFound.array();
  C_INT * pRootEnd = pRootFound + mRootsFound.size();
  C_FLOAT64 * pValueBefore = mpRootValuesBefore->array();
  C_FLOAT64 * pValueAfter = mpRootValuesAfter->array();
  CMathTrigger::CRootFinder *const* ppRootFinder = mpMathModel->getRootFinders().array();

  for (; pRootFound != pRootEnd; ++pRootFound, ++pValueBefore, ++pValueAfter, ++ppRootFinder)
    {
      // Root values which did not change are not found
      if (*pValueBefore == *pValueAfter)
        {
          *pRootFound = 0;
          continue;
        }

      // Handle equality
      if ((*ppRootFinder)->isEquality())
        {
          if ((*ppRootFinder)->isTrue())
            {
              if (*pValueAfter >= 0.0 || *pValueAfter > *pValueBefore)
                {
                  *pRootFound = 0;
                }
              else
                {
                  *pRootFound = 1;
                  rootsFound = true;
                }
            }
          else
            {
              if (*pValueAfter < 0.0 || *pValueAfter < *pValueBefore)
                {
                  *pRootFound = 0;
                }
              else
                {
                  *pRootFound = 1;
                  rootsFound = true;
                }
            }
        }
      else
        {
          if ((*ppRootFinder)->isTrue())
            {
              if (*pValueAfter > 0.0 || *pValueAfter > *pValueBefore)
                {
                  *pRootFound = 0;
                }
              else
                {
                  *pRootFound = 1;
                  rootsFound = true;
                }
            }
          else
            {
              if (*pValueAfter <= 0.0 || *pValueAfter < *pValueBefore)
                {
                  *pRootFound = 0;
                }
              else
                {
                  *pRootFound = 1;
                  rootsFound = true;
                }
            }
        }
    }

  // Swap before and after.
  CVector< C_FLOAT64 > * pTmp = mpRootValuesBefore;
  mpRootValuesBefore = mpRootValuesAfter;
  mpRootValuesAfter = pTmp;

  return rootsFound;
}

// static
bool CProcessQueue::notEmpty(const CProcessQueue::range & range)
{
  return range.first != range.second;
}

const size_t & CProcessQueue::createEventId()
{
  size_t EventId = 0;

  if (mEventIdSet.size() > 0)
    {
      EventId = * mEventIdSet.rbegin();
    }

  return * mEventIdSet.insert(++EventId).first;
}

void CProcessQueue::destroyEventId(const size_t & eventId)
{
  mEventIdSet.erase(eventId);
}

const C_FLOAT64 & CProcessQueue::getProcessQueueExecutionTime() const
{
  static C_FLOAT64 Infinity =
    std::numeric_limits< C_FLOAT64 >::infinity();

  const C_FLOAT64 * CalculationTime =
    mCalculations.size() > 0 ? &mCalculations.begin()->first.getExecutionTime() : &Infinity;

  const C_FLOAT64 * AssignmentTime =
    mAssignments.size() > 0 ? &mAssignments.begin()->first.getExecutionTime() : &Infinity;

  return std::min(*CalculationTime, *AssignmentTime);
}

bool CProcessQueue::isEmpty() const
{
  return (mAssignments.size() == 0) && (mCalculations.size() == 0);
}

void CProcessQueue::setEventCallBack(void* pTask, EventCallBack ecb)
{
  mpCallbackTask = pTask;
  mpEventCallBack = ecb;
}

std::ostream &operator<<(std::ostream &os, const CProcessQueue & o)
{
  os << "Process Queue" << std::endl;
  std::multimap< CProcessQueue::CKey, CProcessQueue::CAction >::const_iterator it;

  if (o.mCalculations.size()) os << " Calculations:" << std::endl;

  for (it = o.mCalculations.begin(); it != o.mCalculations.end(); ++it)
    {
      os << "exec time " << it->first.mExecutionTime << ", cascading lvl "
         << it->first.mCascadingLevel << ", "
         << (it->first.mEquality ? "equality, " : "inequality, ")
         << "order " << it->first.mOrder << ", event ID "
         << it->first.mEventId;

      os << std::endl;

      os << "target (" << it->second.mpTarget << "->" << (it->second.mpTarget ? *it->second.mpTarget : -999.999) << ")"
         << ", value " << it->second.mValue
         << ", expr " << it->second.mpExpression
         << ", event (" << it->second.mpEvent << (it->second.mpEvent->getType() == CEvent::CutPlane ? " cut plane)" : ")");

      os << std::endl << std::endl;
    }

  if (o.mAssignments.size()) os << " Assignments:" << std::endl;

  for (it = o.mAssignments.begin(); it != o.mAssignments.end(); ++it)
    {
      os << "exec time " << it->first.mExecutionTime << ", cascading lvl "
         << it->first.mCascadingLevel << ", "
         << (it->first.mEquality ? "equality, " : "inequality, ")
         << "order " << it->first.mOrder << ", event ID "
         << it->first.mEventId;

      os << std::endl;

      os << "target " << it->second.mpTarget
         << ", value " << it->second.mValue
         << ", expr " << it->second.mpExpression
         << ", event " << it->second.mpEvent;

      os << std::endl << std::endl;
    }

  return os;
}
