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
  mEquality(false)
{}

CProcessQueue::CKey::CKey(const CKey & src) :
  mExecutionTime(src.mExecutionTime),
  mCascadingLevel(src.mCascadingLevel),
  mEquality(src.mEquality)
{}

CProcessQueue::CKey::CKey(const C_FLOAT64 & executionTime,
                          const bool & equality,
                          const size_t & cascadingLevel) :
  mExecutionTime(executionTime),
  mCascadingLevel(cascadingLevel),
  mEquality(equality)
{}

CProcessQueue::CKey::~CKey()
{}

bool CProcessQueue::CKey::operator < (const CProcessQueue::CKey & rhs) const
{
  if (mExecutionTime != rhs.mExecutionTime)
    return mExecutionTime < rhs.mExecutionTime;

  if (mCascadingLevel != rhs.mCascadingLevel)
    return mCascadingLevel > rhs.mCascadingLevel;

  return mEquality > rhs.mEquality;
}

//*********************************************************

CProcessQueue::CAction::CAction() :
  mType(),
  mValues(),
  mpEvent(NULL),
  mpProcessQueue(NULL)
{}

CProcessQueue::CAction::CAction(const CAction & src) :
  mType(src.mType),
  mValues(src.mValues),
  mpEvent(src.mpEvent),
  mpProcessQueue(src.mpProcessQueue)
{}

CProcessQueue::CAction::CAction(CMathEvent * pEvent,
                                CProcessQueue * pProcessQueue) :
  mType(),
  mValues(),
  mpEvent(pEvent),
  mpProcessQueue(pProcessQueue)
{
  switch (pEvent->getType())
    {
      case CEvent::Assignment:
        mType = Calculation;
        break;

      case CEvent::Callback:
        mType = Callback;
        break;
    }
}

CProcessQueue::CAction::CAction(const CVector< C_FLOAT64 > & values,
                                CMathEvent * pEvent,
                                CProcessQueue * pProcessQueue) :
  mType(CProcessQueue::CAction::Assignment),
  mValues(values),
  mpEvent(pEvent),
  mpProcessQueue(pProcessQueue)
{}

CProcessQueue::CAction::~CAction()
{}

bool CProcessQueue::CAction::process()
{
  // Assume that nothing is changed
  bool StateChanged = false;

  switch (mType)
    {
      case Calculation:

        if (mpEvent->delayAssignment())
          {
            mpProcessQueue->addAssignment(mpEvent->getAssignmentTime(mpProcessQueue->mTime),
                                          mpProcessQueue->mEquality,
                                          mpEvent->getTargetValues(),
                                          mpEvent);
          }
        else
          {
            StateChanged = mpEvent->executeAssignment();
          }

        break;

      case Assignment:
        StateChanged = mpEvent->setTargetValues(mValues);
        break;

      case Callback:

        if (mpProcessQueue->mpEventCallBack)
          {
            (*mpProcessQueue->mpEventCallBack)(mpProcessQueue->mpCallbackTask, mpEvent->getType());
          }

        break;
    }

  return StateChanged;
}

const CProcessQueue::CAction::Type & CProcessQueue::CAction::getType() const
{
  return mType;
}

//*********************************************************

CProcessQueue::CProcessQueue() :
  mActions(),
  mExecutionLimit(10000),
  mExecutionCounter(0),
  mTime(0.0),
  mEquality(true),
  mCascadingLevel(0),
  mSimultaneousAssignmentsFound(false),
  mEventIdSet(),
  mpMathModel(NULL),
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

CProcessQueue::CProcessQueue(const CProcessQueue & src):
  mActions(src.mActions),
  mExecutionLimit(src.mExecutionLimit),
  mExecutionCounter(src.mExecutionCounter),
  mTime(src.mTime),
  mEquality(src.mEquality),
  mCascadingLevel(src.mCascadingLevel),
  mSimultaneousAssignmentsFound(src.mSimultaneousAssignmentsFound),
  mEventIdSet(src.mEventIdSet),
  mpMathModel(src.mpMathModel),
  mRootsFound(src.mRootsFound),
  mRootValues1(src.mRootValues1),
  mRootValues2(src.mRootValues2),
  mpRootValuesBefore(&src.mRootValues1 == src.mpRootValuesBefore ? &mRootValues1 : &mRootValues2),
  mpRootValuesAfter(&src.mRootValues1 == src.mpRootValuesAfter ? &mRootValues1 : &mRootValues2),
  mpResolveSimultaneousAssignments(src.mpResolveSimultaneousAssignments),
  mContinueSimultaneousEvents(src.mContinueSimultaneousEvents),
  mpCallbackTask(src.mpCallbackTask),
  mpEventCallBack(src.mpEventCallBack)
{}

CProcessQueue::~CProcessQueue()
{}

bool CProcessQueue::addAssignment(const C_FLOAT64 & executionTime,
                                  const bool & equality,
                                  const CVector< C_FLOAT64 > & values,
                                  CMathEvent * pEvent)
{
  // It is not possible to proceed backwards in time.
  if (executionTime < mTime) return false;

  size_t CascadingLevel = mCascadingLevel;

  if (executionTime > mTime)
    CascadingLevel = 0;

  mActions.insert(std::make_pair(CKey(executionTime, equality, CascadingLevel),
                                 CAction(values, pEvent, this)));

  return true;
}

bool CProcessQueue::addCalculation(const C_FLOAT64 & executionTime,
                                   const bool & equality,
                                   CMathEvent * pEvent)
{
  // It is not possible to proceed backwards in time.
  if (executionTime < mTime) return false;

  size_t CascadingLevel = mCascadingLevel;

  if (executionTime > mTime)
    CascadingLevel = 0;

  mActions.insert(std::make_pair(CKey(executionTime, equality, CascadingLevel),
                                 CAction(pEvent, this)));

  return true;
}

void CProcessQueue::initialize(CMathModel * pMathModel)
{
  mpMathModel = pMathModel;
  assert(mpMathModel != NULL);

  mTime = mpMathModel->getInitialTime();

  mActions.clear();
  mEventIdSet.clear();
  mSimultaneousAssignmentsFound = false;

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

  mpMathModel->evaluateRoots(*mpRootValuesBefore, false);

  iterator itAction = getAction();

  // The algorithm below will work properly for user ordered events
  // as the queue enforces the proper ordering.
  while (success &&
         itAction != mActions.end() &&
         mCascadingLevel != std::numeric_limits<size_t>::max())
    {
      if (!executeAction(itAction))
        {
          itAction = getAction();
          continue;
        }

      stateChanged = true;

      // We switch to the next cascading level so that events triggered by the
      // execution of assignments are properly scheduled.
      mCascadingLevel++;

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

      // Independent from the setting priorToOutput we must only consider equality
      mEquality = true;

      // Retrieve the pending calculations.
      itAction = getAction();

      while (itAction == mActions.end() &&
             mCascadingLevel > 0)
        {
          // If we are here we have no more actions for this level.
          mCascadingLevel--;

          if (mCascadingLevel == 0)
            {
              mEquality = priorToOutput;
            }

          itAction = getAction();
        }
    }

  return stateChanged;
}

CProcessQueue::iterator CProcessQueue::getAction()
{
  CKey Pending(mTime, mEquality, mCascadingLevel);
  range PendingActions = mActions.equal_range(Pending);

  if (PendingActions.first == PendingActions.second)
    {
      return mActions.end();
    }

  iterator nextAction = PendingActions.first;
  ++nextAction;

  if (nextAction != PendingActions.second)
    {
      if (!mContinueSimultaneousEvents)
        {

          // The resolution of simultaneous events is algorithm dependent.
          // The simulation routine should provide a call back function.
          if (mpResolveSimultaneousAssignments == NULL)
            {
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCMathModel + 1);
            }

          return (*mpResolveSimultaneousAssignments)(mActions, mTime, mEquality, mCascadingLevel);
        }
      else if (mSimultaneousAssignmentsFound == false)
        {
          mSimultaneousAssignmentsFound = true;
          CCopasiMessage(CCopasiMessage::WARNING_FILTERED, "CMathModel (1): Simultaneous event assignments encountered.");
        }
    }

  return PendingActions.first;
}

bool CProcessQueue::executeAction(CProcessQueue::iterator itAction)
{
  bool StateChanged = itAction->second.process();

  if (StateChanged)
    {
      mExecutionCounter++;
    }

  mActions.erase(itAction);

  return StateChanged;
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

void CProcessQueue::destroyEventId(const size_t & eventId)
{
  mEventIdSet.erase(eventId);
}

const C_FLOAT64 & CProcessQueue::getProcessQueueExecutionTime() const
{
  static C_FLOAT64 Infinity =
    std::numeric_limits< C_FLOAT64 >::infinity();

  if (mActions.empty())
    {
      return Infinity;
    }

  return mActions.begin()->first.getExecutionTime();
}

void CProcessQueue::setContinueSimultaneousEvents(const bool & continueSimultaneousEvents)
{
  mContinueSimultaneousEvents = continueSimultaneousEvents;
}

const bool & CProcessQueue::getContinueSimultaneousEvents() const
{
  return mContinueSimultaneousEvents;
}

void CProcessQueue::setContinueSimultaneousEvents(const bool & continueSimultaneousEvents)
{
  mContinueSimultaneousEvents = continueSimultaneousEvents;
}

const bool & CProcessQueue::getContinueSimultaneousEvents() const
{
  return mContinueSimultaneousEvents;
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

  if (o.mActions.size()) os << " Actions:" << std::endl;

  for (it = o.mActions.begin(); it != o.mActions.end(); ++it)
    {
      os << "exec time " << it->first.mExecutionTime
         << ", cascading lvl " << it->first.mCascadingLevel
         << ", " << (it->first.mEquality ? "equality, " : "inequality");

      os << std::endl;

      CMathEvent * pEvent = it->second.mpEvent;

      os << "pEvent: 0x" << pEvent << ", Action: ";

      switch (it->second.mType)
        {
          case CProcessQueue::CAction::Calculation:

            if (pEvent->delayAssignment())
              {
                os << "Calculation";
              }
            else
              {
                os << "Calculation & Assignment";
              }

            break;

          case CProcessQueue::CAction::Assignment:
            os << "Assignment";
            break;

          case CProcessQueue::CAction::Callback:
            os << "Callback";
            break;
        }

      os << std::endl << std::endl;
    }

  return os;
}
