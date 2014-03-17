// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <limits>

#include "copasi.h"

#include "CMathEventQueue.h"
#include "CMathContainer.h"
#include "CMathEvent.h"
#include "function/CExpression.h"

#include <copasi/report/CCopasiRootContainer.h>
#include <copasi/commandline/CConfigurationFile.h>

CMathEventQueue::CKey::CKey() :
  mExecutionTime(0.0),
  mCascadingLevel(0),
  mEquality(false)
{}

CMathEventQueue::CKey::CKey(const CKey & src) :
  mExecutionTime(src.mExecutionTime),
  mCascadingLevel(src.mCascadingLevel),
  mEquality(src.mEquality)
{}

CMathEventQueue::CKey::CKey(const C_FLOAT64 & executionTime,
                            const bool & equality,
                            const size_t & cascadingLevel):
  mExecutionTime(executionTime),
  mCascadingLevel(cascadingLevel),
  mEquality(equality)
{}

CMathEventQueue::CKey::~CKey()
{}

bool CMathEventQueue::CKey::operator < (const CMathEventQueue::CKey & rhs) const
{
  if (mExecutionTime != rhs.mExecutionTime)
    return mExecutionTime < rhs.mExecutionTime;

  if (mCascadingLevel != rhs.mCascadingLevel)
    return mCascadingLevel > rhs.mCascadingLevel;

  return mEquality < rhs.mEquality;
}

//*********************************************************

CMathEventQueue::CAction::CAction():
  mType(CMathEventQueue::CAction::Calculation),
  mValues(),
  mpPriority(NULL),
  mpEvent(NULL),
  mpProcessQueue(NULL)
{}

CMathEventQueue::CAction::CAction(const CMathEventQueue::CAction::Type & type,
                                  CMathEventN * pEvent,
                                  CMathEventQueue * pProcessQueue):
  mType(type),
  mValues(),
  mpPriority(NULL),
  mpEvent(pEvent),
  mpProcessQueue(pProcessQueue)
{
  if (mType == Assignment)
    {
      mpPriority = (const C_FLOAT64 *) pEvent->getPriority()->getValuePointer();
      mpEvent->getAssignmentValues(mValues);
    }
}

CMathEventQueue::CAction::CAction(const CAction & src):
  mType(src.mType),
  mpPriority(src.mpPriority),
  mValues(src.mValues),
  mpEvent(src.mpEvent),
  mpProcessQueue(src.mpProcessQueue)
{}

CMathEventQueue::CAction::~CAction()
{}

void CMathEventQueue::CAction::process(const size_t & eventId)
{
  if (mType == Assignment)
    {
      mpEvent->setTargetValues(mValues);
    }
  else
    {
      mpProcessQueue->addAssignment(mpEvent->getAssignmentTime(), mpProcessQueue->mEquality, mpEvent);
    }
}

//*********************************************************

CMathEventQueue::CMathEventQueue() :
  mpContainer(NULL),
  mpTime(NULL),
  mCalculations(),
  mAssignments(),
  mUpdateSequence(),
  mExecutionLimit(10000),
  mExecutionCounter(0),
  mEquality(true),
  mCascadingLevel(0),
  mSimultaneousAssignments(false),
  mEventIdSet(),
  mRootsFound(0),
  mRootValues1(0),
  mRootValues2(0),
  mpRootValuesBefore(&mRootValues1),
  mpRootValuesAfter(&mRootValues2),
  mpResolveSimultaneousAssignments(NULL),
  mContinueSimultaneousEvents(false),
  mpCallbackTask(NULL),
  mpEventCallBack(NULL)
{}

CMathEventQueue::CMathEventQueue(CMathContainer & container):
  mpContainer(& container),
  mpTime(container.getState().array() + container.getTimeIndex()),
  mCalculations(),
  mAssignments(),
  mUpdateSequence(),
  mExecutionLimit(10000),
  mExecutionCounter(0),
  mEquality(true),
  mCascadingLevel(0),
  mSimultaneousAssignments(false),
  mEventIdSet(),
  mRootsFound(0),
  mRootValues1(0),
  mRootValues2(0),
  mpRootValuesBefore(&mRootValues1),
  mpRootValuesAfter(&mRootValues2),
  mpResolveSimultaneousAssignments(NULL),
  mContinueSimultaneousEvents(false),
  mpCallbackTask(NULL),
  mpEventCallBack(NULL)
{}

CMathEventQueue::~CMathEventQueue()
{}

bool CMathEventQueue::addAssignment(const C_FLOAT64 & executionTime,
                                    const bool & equality,
                                    CMathEventN * pEvent)
{
  // It is not possible to proceed backwards in time.
  if (executionTime < *mpTime) return false;

  size_t CascadingLevel = mCascadingLevel;

  if (executionTime > *mpTime)
    CascadingLevel = 0;

  mAssignments.insert(std::make_pair(CKey(executionTime, equality, CascadingLevel),
                                     CAction(CAction::Assignment, pEvent, this)));

  return true;
}

bool CMathEventQueue::addCalculation(const C_FLOAT64 & executionTime,
                                     const bool & equality,
                                     CMathEventN * pEvent)
{
  // It is not possible to proceed backwards in time.
  if (executionTime < *mpTime) return false;

  size_t CascadingLevel = mCascadingLevel;

  if (executionTime > *mpTime)
    CascadingLevel = 0;

  mCalculations.insert(std::make_pair(CKey(executionTime, equality, CascadingLevel),
                                      CAction(CAction::Calculation, pEvent, this)));

  return true;
}

void CMathEventQueue::start()
{
  mCalculations.clear();
  mAssignments.clear();
  mEventIdSet.clear();
  mSimultaneousAssignments = false;

  size_t NumRoots = mpContainer->getRoots().size();
  mRootsFound.resize(NumRoots);
  mRootsFound = 0;
  mRootValues1.resize(NumRoots);
  mRootValues2.resize(NumRoots);
  mpRootValuesBefore = &mRootValues1;
  mpRootValuesAfter = &mRootValues2;

  return;
}

bool CMathEventQueue::process(const bool & priorToOutput,
                              resolveSimultaneousAssignments pResolveSimultaneousAssignments)
{
  if (getProcessQueueExecutionTime() > *mpTime)
    return false;

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
      *mpRootValuesBefore = mpContainer->getRoots();
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
          mpContainer->processRoots(mRootsFound);
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
      if (!mContinueSimultaneousEvents)
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

CMathEventQueue::range CMathEventQueue::getCalculations()
{
  range Calculations;

  CKey UpperBound(*mpTime, mEquality, mCascadingLevel);

  Calculations.first = mCalculations.begin();

  if (Calculations.first != mCalculations.end() &&
      Calculations.first->first < UpperBound)
    {
      Calculations.second = mCalculations.upper_bound(Calculations.first->first);

      // Check whether we have a second set of assignments with a different ID.
      if (Calculations.second != mCalculations.end() &&
          Calculations.second->first < UpperBound)
        {
          if (!mContinueSimultaneousEvents)
            {
              mSimultaneousAssignments = true;

              // The resolution of simultaneous events is algorithm dependent.
              // The simulation routine should provide a call back function.
              if (mpResolveSimultaneousAssignments == NULL)
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCMathModel + 1);
                }

              return (*mpResolveSimultaneousAssignments)(mCalculations, *mpTime, mEquality, mCascadingLevel);
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

CMathEventQueue::range CMathEventQueue::getAssignments()
{
  range Assignments;
  CKey UpperBound(*mpTime, mEquality, mCascadingLevel);

  Assignments = mAssignments.equal_range(UpperBound);

  // Find the assignments with the highest priority

  Assignments.first = mAssignments.begin();

  if (Assignments.first != mAssignments.end() &&
      Assignments.first->first == UpperBound)
    {
      Assignments.second = mAssignments.upper_bound(Assignments.first->first);

      // Check whether we have a second set of assignments with a different ID.
      if (Assignments.second != mAssignments.end() &&
          Assignments.second->first < UpperBound)
        {
          if (!mContinueSimultaneousEvents)
            {
              mSimultaneousAssignments = true;

              // The resolution of simultaneous events is algorithm dependent.
              // The simulation routine should provide a call back function.
              if (mpResolveSimultaneousAssignments == NULL)
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCMathModel + 1);
                }

              return (*mpResolveSimultaneousAssignments)(mAssignments, *mpTime, mEquality, mCascadingLevel);
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

bool CMathEventQueue::executeCalculations(CMathEventQueue::range & calculations)
{
  bool success = true;

  iterator it = calculations.first;
  assert(it != mCalculations.end());

  size_t EventIdOld = it->first.getEventId();
  size_t EventIdNew = createEventId();

  CMathEventN * pEvent = it->second.mpEvent;

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

bool CMathEventQueue::executeAssignments(CMathEventQueue::range & assignments)
{
  bool success = (mExecutionCounter < mExecutionLimit);

  iterator it = assignments.first;
  assert(it != mAssignments.end());

  size_t EventIdOld = it->first.getEventId();
  size_t EventIdNew = 0;

  CMathEventN * pEvent = it->second.mpEvent;

  EventIdNew = createEventId();

  for (; it != assignments.second; ++it)
    it->second.process(EventIdNew);

  destroyEventId(EventIdOld);
  mAssignments.erase(assignments.first, assignments.second);

  // Update all dependent values.
  mpContainer->updateEventSimulatedValues();

  mExecutionCounter++;

  return success;
}

bool CMathEventQueue::rootsFound()
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
bool CMathEventQueue::notEmpty(const CMathEventQueue::range & range)
{
  return range.first != range.second;
}

const size_t & CMathEventQueue::createEventId()
{
  size_t EventId = 0;

  if (mEventIdSet.size() > 0)
    {
      EventId = * mEventIdSet.rbegin();
    }

  return * mEventIdSet.insert(++EventId).first;
}

void CMathEventQueue::destroyEventId(const size_t & eventId)
{
  mEventIdSet.erase(eventId);
}

const C_FLOAT64 & CMathEventQueue::getProcessQueueExecutionTime() const
{
  static C_FLOAT64 Infinity =
    std::numeric_limits< C_FLOAT64 >::infinity();

  const C_FLOAT64 * CalculationTime =
    mCalculations.size() > 0 ? &mCalculations.begin()->first.getExecutionTime() : &Infinity;

  const C_FLOAT64 * AssignmentTime =
    mAssignments.size() > 0 ? &mAssignments.begin()->first.getExecutionTime() : &Infinity;

  return std::min(*CalculationTime, *AssignmentTime);
}

bool CMathEventQueue::isEmpty() const
{
  return (mAssignments.size() == 0) && (mCalculations.size() == 0);
}

void CMathEventQueue::setContinueSimultaneousEvents(const bool & continueSimultaneousEvents)
{
  mContinueSimultaneousEvents = continueSimultaneousEvents;
}

const bool & CMathEventQueue::getContinueSimultaneousEvents() const
{
  return mContinueSimultaneousEvents;
}

void CMathEventQueue::setEventCallBack(void* pTask, EventCallBack ecb)
{
  mpCallbackTask = pTask;
  mpEventCallBack = ecb;
}

std::ostream &operator<<(std::ostream &os, const CMathEventQueue & o)
{
  os << "Process Queue" << std::endl;
  std::multimap< CMathEventQueue::CKey, CMathEventQueue::CAction >::const_iterator it;

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
