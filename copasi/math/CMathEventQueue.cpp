// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <limits>

#include "copasi/copasi.h"

#include "CMathEventQueue.h"
#include "CMathContainer.h"
#include "CMathEvent.h"
#include "copasi/function/CExpression.h"
#include "copasi/randomGenerator/CRandom.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CConfigurationFile.h"

// Uncomment this line below to get debug print out.
// #define DEBUG_OUTPUT 1

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

std::ostream &operator<<(std::ostream &os, const CMathEventQueue::CKey & o)
{
  os << "exec time " << o.mExecutionTime
     << ", cascading lvl " << o.mCascadingLevel
     << ", " << (o.mEquality ? "equality, " : "inequality");

  return os;
}

//*********************************************************

CMathEventQueue::CAction::CAction():
  mType(),
  mValues(),
  mpPriority(NULL),
  mpEvent(NULL),
  mpProcessQueue(NULL)
{}

CMathEventQueue::CAction::CAction(const CAction & src):
  mType(src.mType),
  mpPriority(src.mpPriority),
  mValues(src.mValues),
  mpEvent(src.mpEvent),
  mpProcessQueue(src.mpProcessQueue)
{}

CMathEventQueue::CAction::CAction(CMathEvent * pEvent,
                                  CMathEventQueue * pProcessQueue):
  mType(),
  mValues(),
  mpPriority(NULL),
  mpEvent(pEvent),
  mpProcessQueue(pProcessQueue)
{
  mpPriority = (const C_FLOAT64 *) pEvent->getPriority()->getValuePointer();

  switch (pEvent->getType())
    {
      case CEvent::Assignment:
      case CEvent::Discontinuity:
        mType = Calculation;
        break;

      case CEvent::Callback:
        mType = Callback;
        break;
    }
}

CMathEventQueue::CAction::CAction(const CVector< C_FLOAT64 > & values,
                                  CMathEvent * pEvent,
                                  CMathEventQueue * pProcessQueue) :
  mType(CMathEventQueue::CAction::Assignment),
  mValues(values),
  mpPriority(NULL),
  mpEvent(pEvent),
  mpProcessQueue(pProcessQueue)
{
  mpPriority = (const C_FLOAT64 *) pEvent->getPriority()->getValuePointer();
}

CMathEventQueue::CAction::~CAction()
{}

CMath::StateChange CMathEventQueue::CAction::process()
{
  // Assume that nothing is changed
  CMath::StateChange StateChange(CMath::StateChange::None);

  switch (mType)
    {
      case Calculation:

        if (mpEvent->delayAssignment())
          {
            mpProcessQueue->addAssignment(mpEvent->getExecutionTime(),
                                          mpProcessQueue->mEquality,
                                          mpEvent->getTargetValues(),
                                          mpEvent);
          }
        else
          {
            StateChange = mpEvent->executeAssignment();
          }

        break;

      case Assignment:
        StateChange = mpEvent->setTargetValues(mValues);
        break;

      case Callback:
        mpEvent->executeCallback(mpProcessQueue);
        break;
    }

  return StateChange;
}

CMathEvent * CMathEventQueue::CAction::getEvent() const {return mpEvent;}

const CMathEventQueue::CAction::Type & CMathEventQueue::CAction::getType() const {return mType;}

const C_FLOAT64 & CMathEventQueue::CAction::getPriority() const {return *mpPriority;}

std::ostream &operator<<(std::ostream &os, const CMathEventQueue::CAction & o)
{
  CMathEvent * pEvent = o.getEvent();

  os << "pEvent: 0x" << pEvent << ", Action: ";

  switch (o.getType())
    {
      case CMathEventQueue::CAction::Calculation:

        if (pEvent->delayAssignment())
          {
            os << "Calculation";
          }
        else
          {
            os << "Calculation & Assignment";
          }

        break;

      case CMathEventQueue::CAction::Assignment:
        os << "Assignment";
        break;

      case CMathEventQueue::CAction::Callback:
        os << "Callback";
        break;
    }

  return os;
}

//*********************************************************

CMathEventQueue::CMathEventQueue() :
  mpContainer(NULL),
  mpTime(NULL),
  mActions(),
  mUpdateSequence(),
  mExecutionLimit(10000),
  mExecutionCounter(0),
  mEquality(true),
  mCascadingLevel(0),
  mRootsFound(0),
  mRootValues1(0),
  mRootValues2(0),
  mpRootValuesBefore(&mRootValues1),
  mpRootValuesAfter(&mRootValues2)
{}

CMathEventQueue::CMathEventQueue(CMathContainer & container):
  mpContainer(& container),
  mpTime(NULL),
  mActions(),
  mUpdateSequence(),
  mExecutionLimit(10000),
  mExecutionCounter(0),
  mEquality(true),
  mCascadingLevel(0),
  mRootsFound(0),
  mRootValues1(0),
  mRootValues2(0),
  mpRootValuesBefore(&mRootValues1),
  mpRootValuesAfter(&mRootValues2)
{}

CMathEventQueue::~CMathEventQueue()
{}

bool CMathEventQueue::addAssignment(const C_FLOAT64 & executionTime,
                                    const bool & equality,
                                    const CVectorCore< C_FLOAT64 > & values,
                                    CMathEvent * pEvent)
{
  // It is not possible to proceed backwards in time.
  if (mpTime == NULL || executionTime < *mpTime) return false;

  size_t CascadingLevel = mCascadingLevel;

  // If the assignment is in the future or it has a priority the
  // cascading level must be zero.
  if (executionTime > *mpTime ||
      !std::isnan(* (C_FLOAT64 *) pEvent->getPriority()->getValuePointer()))
    CascadingLevel = 0;

  pEvent->addPendingAction(mActions.insert(std::make_pair(CKey(executionTime, equality, CascadingLevel),
                           CAction(values, pEvent, this))));

  return true;
}

bool CMathEventQueue::addCalculation(const C_FLOAT64 & executionTime,
                                     const bool & equality,
                                     CMathEvent * pEvent)
{
  // It is not possible to proceed backwards in time.
  if (mpTime == NULL || executionTime < *mpTime) return false;

  size_t CascadingLevel = mCascadingLevel;

  // If the assignment is in the future or it has a priority the
  // cascading level must be zero.
  if (executionTime > *mpTime ||
      !std::isnan(* (C_FLOAT64 *) pEvent->getPriority()->getValuePointer()))
    CascadingLevel = 0;

  pEvent->addPendingAction(mActions.insert(std::make_pair(CKey(executionTime, equality, CascadingLevel),
                           CAction(pEvent, this))));

  return true;
}

void CMathEventQueue::removeAction(const std::pair< CMathEventQueue::CKey, CMathEventQueue::CAction > & action)
{
  range PendingActions = mActions.equal_range(action.first);

  iterator itAction = PendingActions.first;

  for (; itAction != PendingActions.second; ++itAction)
    {
      if (itAction->second.getEvent() == action.second.getEvent())
        {
          mActions.erase(itAction);
          break;
        }
    }
}

void CMathEventQueue::start()
{
  mActions.clear();

  mpTime = mpContainer->getState(false).array() + mpContainer->getCountFixedEventTargets();

  size_t NumRoots = mpContainer->getRoots().size();
  mRootsFound.resize(NumRoots);
  mRootsFound = 0;
  mRootValues1.resize(NumRoots);
  mRootValues2.resize(NumRoots);
  mpRootValuesBefore = &mRootValues1;
  mpRootValuesAfter = &mRootValues2;

  return;
}

CMath::StateChange CMathEventQueue::process(const bool & priorToOutput)
{
  if (mpTime == NULL || getProcessQueueExecutionTime() > *mpTime)
    return CMath::StateChange::None;

  mEquality = priorToOutput;
  mExecutionCounter = 0;
  mCascadingLevel = 0;

  bool success = true;
  CMath::StateChange StateChange(CMath::StateChange::None);

  *mpRootValuesBefore = mpContainer->getRoots();
  mpContainer->updatePriorityValues();

  iterator itAction = getAction();

#ifdef DEBUG_OUTPUT
  std::cout << "State: " << mpContainer->getState(false) << std::endl;
  std::cout << "Roots: " << mpContainer->getRoots() << std::endl;
#endif //DEBUG_OUTPUT

  // The algorithm below will work properly for user ordered events
  // as the queue enforces the proper ordering.
  while (success &&
         itAction != mActions.end() &&
         mCascadingLevel != std::numeric_limits<size_t>::max())
    {
      CMath::StateChange ActionStateChange = executeAction(itAction);
      StateChange |= ActionStateChange;

      if (ActionStateChange)
        {
          mpContainer->updatePriorityValues();
        }

      // State change does not indicate whether we have any root changes. We need to
      // explicitly check for it.
#ifdef DEBUG_OUTPUT
      std::cout << "State: " << mpContainer->getState(false) << std::endl;
      std::cout << "Roots: " << mpContainer->getRoots() << std::endl;
#endif // DEBUG_OUTPUT

      // We switch to the next cascading level so that events triggered by the
      // execution of assignments are properly scheduled.
      mCascadingLevel++;

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

  return StateChange;
}

CMathEventQueue::iterator CMathEventQueue::getAction()
{
  if (mpTime == NULL) return mActions.end();

  CKey Pending(*mpTime, mEquality, mCascadingLevel);
  range PendingActions = mActions.equal_range(Pending);

  if (PendingActions.first == PendingActions.second)
    {
      return mActions.end();
    }

  iterator itAction = PendingActions.first;

  std::vector< iterator > PriorityActions;
  C_FLOAT64 HighestPriority = - std::numeric_limits< C_FLOAT64 >::infinity();

  for (; itAction != PendingActions.second; ++itAction)
    {
      // Events without priority are ignored
      if (std::isnan(itAction->second.getPriority()))
        {
          continue;
        }

      // The priority is lower than the highest
      if (itAction->second.getPriority() < HighestPriority)
        {
          continue;
        }

      // New highest priority
      if (HighestPriority < itAction->second.getPriority())
        {
          HighestPriority = itAction->second.getPriority();
          PriorityActions.clear();
          PriorityActions.push_back(itAction);

          continue;
        }

      // Equal highest priority
      PriorityActions.push_back(itAction);
    }

  switch (PriorityActions.size())
    {
      // No prioritized actions
      case 0:
        // We arbitrarily pick the first
        return PendingActions.first;
        break;

      // One action has the highest priority
      case 1:
        return PriorityActions[0];
        break;

      // Pick one randomly
      default:
        return PriorityActions[mpContainer->getRandomGenerator().getRandomU(PriorityActions.size() - 1)];
        break;
    }

  // We should never get here
  return mActions.end();
}

CMath::StateChange CMathEventQueue::executeAction(CMathEventQueue::iterator itAction)
{
  // Notify the event that the pending action is executed.
  itAction->second.getEvent()->removePendingAction();

  CMath::StateChange StateChange = itAction->second.process();

  mExecutionCounter++;

  mActions.erase(itAction);

  return StateChange;
}

bool CMathEventQueue::rootsFound()
{
  bool rootsFound = false;

  // Calculate the current root values
  *mpRootValuesAfter = mpContainer->getRoots();

  // Compare the root values before and after;
  C_INT * pRootFound = mRootsFound.array();
  C_INT * pRootEnd = pRootFound + mRootsFound.size();
  C_FLOAT64 * pValueBefore = mpRootValuesBefore->array();
  C_FLOAT64 * pValueAfter = mpRootValuesAfter->array();
  CMathEvent::CTrigger::CRootProcessor ** ppRootProcessor = mpContainer->getRootProcessors().array();

  for (; pRootFound != pRootEnd; ++pRootFound, ++pValueBefore, ++pValueAfter, ++ppRootProcessor)
    {
      // Root values which did not change are not found
      if (2.0 * fabs(*pValueAfter - *pValueBefore) <= (fabs(*pValueAfter) + fabs(*pValueBefore)) * std::numeric_limits< C_FLOAT64 >::epsilon())
        {
          *pRootFound = 0;
          continue;
        }

      // Detect whether we have an exact zero (within 10 * epsilon)
      bool zero = (fabs(*pValueAfter) < 10.0 * fabs(*pValueBefore) * std::numeric_limits< C_FLOAT64 >::epsilon());

      // Handle equality
      if ((*ppRootProcessor)->isEquality())
        {
          if ((*ppRootProcessor)->isTrue())
            {
              if (zero || *pValueAfter >= 0.0 || *pValueAfter > *pValueBefore)
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
          if ((*ppRootProcessor)->isTrue())
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
              if (zero || *pValueAfter <= 0.0 || *pValueAfter < *pValueBefore)
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

const C_FLOAT64 & CMathEventQueue::getProcessQueueExecutionTime() const
{
  static C_FLOAT64 Infinity =
    std::numeric_limits< C_FLOAT64 >::infinity();

  if (mActions.empty())
    {
      return Infinity;
    }

  return mActions.begin()->first.getExecutionTime();
}

std::ostream &operator<<(std::ostream &os, const CMathEventQueue & o)
{
  os << "Process Queue" << std::endl;
  CMathEventQueue::const_iterator it;

  if (o.mActions.size()) os << " Actions:" << std::endl;

  for (it = o.mActions.begin(); it != o.mActions.end(); ++it)
    {
      os << it->first << std::endl;
      os << it->second << std::endl;
      os << std::endl;
    }

  return os;
}
