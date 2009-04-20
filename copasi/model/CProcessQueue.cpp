// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CProcessQueue.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/20 13:30:38 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <limits>

#include "copasi.h"

#include "CProcessQueue.h"

CProcessQueue::CProcessQueueKey::CProcessQueueKey() :
    mExecutionTime(0.0),
    mEquality(false),
    mEventId(std::numeric_limits<unsigned C_INT32>::max()),
    mCascadingLevel(0)
{}

CProcessQueue::CProcessQueueKey::CProcessQueueKey(const CProcessQueueKey & src) :
    mExecutionTime(src.mExecutionTime),
    mEquality(src.mEquality),
    mEventId(src.mEventId),
    mCascadingLevel(src.mCascadingLevel)
{}

CProcessQueue::CProcessQueueKey::CProcessQueueKey(const C_FLOAT64 & executionTime,
    const bool & equality,
    const unsigned C_INT32 & eventId,
    const unsigned C_INT32 & cascadingLevel) :
    mExecutionTime(executionTime),
    mEquality(equality),
    mEventId(eventId),
    mCascadingLevel(cascadingLevel)
{}

CProcessQueue::CProcessQueueKey::~CProcessQueueKey()
{}

bool CProcessQueue::CProcessQueueKey::operator < (const CProcessQueue::CProcessQueueKey & rhs) const
{
  if (mExecutionTime != rhs.mExecutionTime)
    return mExecutionTime < rhs.mExecutionTime;

  if (mCascadingLevel != rhs.mCascadingLevel)
    return mCascadingLevel > rhs.mCascadingLevel;

  if (mEquality != rhs.mEquality)
    return mEquality;

  return mEventId < rhs.mEventId;
}

CProcessQueue::CProcessQueueAction::CProcessQueueAction() :
    mpTarget(NULL),
    mValue(),
    mpExpression(NULL),
    mpProcessQueue(NULL)
{}

CProcessQueue::CProcessQueueAction::CProcessQueueAction(const CProcessQueueAction & src) :
    mpTarget(src.mpTarget),
    mValue(src.mValue),
    mpExpression(src.mpExpression),
    mpProcessQueue(src.mpProcessQueue)
{}

CProcessQueue::CProcessQueueAction::CProcessQueueAction(C_FLOAT64 * pTarget,
    const C_FLOAT64 & value) :
    mpTarget(pTarget),
    mValue(value),
    mpExpression(NULL),
    mpProcessQueue(NULL)
{}

CProcessQueue::CProcessQueueAction::CProcessQueueAction(C_FLOAT64 * pTarget,
    CExpression * pExpression,
    CProcessQueue * pProcessQueue) :
    mpTarget(pTarget),
    mValue(),
    mpExpression(pExpression),
    mpProcessQueue(pProcessQueue)
{}

CProcessQueue::CProcessQueueAction::~CProcessQueueAction()
{}

void CProcessQueue::CProcessQueueAction::process()
{
  // TODO Implement me!
}

CProcessQueue::CProcessQueue() :
    mCalculations(),
    mAssignments(),
    mExecutionLimit(10000),
    mTime(0.0),
    mEquality(true),
    mCascadingLevel(0)
{}

CProcessQueue::CProcessQueue(const CProcessQueue & src):
    mCalculations(src.mCalculations),
    mAssignments(src.mAssignments),
    mExecutionLimit(src.mExecutionLimit),
    mTime(src.mTime),
    mEquality(src.mEquality),
    mCascadingLevel(src.mCascadingLevel)
{}

CProcessQueue::~CProcessQueue()
{}

bool CProcessQueue::addAssignment(const C_FLOAT64 & executionTime,
                                  const bool & equality,
                                  const unsigned C_INT32 & eventId,
                                  C_FLOAT64 * pTarget,
                                  const C_FLOAT64 & value)
{
  // It is not possible to proceed backwards in time.
  if (executionTime < mTime) return false;

  unsigned C_INT32 CascadingLevel = mCascadingLevel;

  if (executionTime > mTime)
    CascadingLevel = 0;

  mAssignments.insert(std::make_pair(CProcessQueueKey(executionTime,
                                     equality,
                                     eventId,
                                     CascadingLevel),
                                     CProcessQueueAction(pTarget, value)));

  return true;
}

bool CProcessQueue::addCalculation(const C_FLOAT64 & executionTime,
                                   const bool & equality,
                                   const unsigned C_INT32 & eventId,
                                   C_FLOAT64 * pTarget,
                                   CExpression * pExpression)
{
  // It is not possible to proceed backwards in time.
  if (executionTime < mTime) return false;

  unsigned C_INT32 CascadingLevel = mCascadingLevel;

  if (executionTime > mTime)
    CascadingLevel = 0;

  mCalculations.insert(std::make_pair(CProcessQueueKey(executionTime,
                                      equality,
                                      eventId,
                                      CascadingLevel),
                                      CProcessQueueAction(pTarget,
                                                          pExpression,
                                                          this)));

  return true;
}

bool CProcessQueue::process(const C_FLOAT64 & time,
                            const bool & priorToOutput)
{
  mTime = time;
  mEquality = priorToOutput;
  mCascadingLevel = 0;

  bool success = true;

  range Calculations = getCalculations();

  if (notEmpty(Calculations))
    {
      // Execute and remove all current calculations.
      success = executeCalculations(Calculations);
    }

  range Assignments = getAssignments();

  if (notEmpty(Assignments))
    {
      while (mCascadingLevel != std::numeric_limits<unsigned C_INT32>::max() && success)
        {
          // Execute and remove all current assignments.
          success = executeAssignments(Assignments);

          // We have no more calculations and assignments pending at this point
          // for this time and level.

          // Update the model.
          // TODO Implement me!

          // Note, updating the model may have added new events to the queue.
          // The setting of the equality flag for these events may be either true
          // or false.

          // Switch to the next cascading level.
          mCascadingLevel++;
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

          if (notEmpty(Assignments))
            continue;

          // If we are here we have no more calculations and assignment for this level.
          mCascadingLevel--;
        }
    }

  return success;
}
CProcessQueue::range CProcessQueue::getCalculations()
{
  range Calculations;
  CProcessQueueKey UpperBound(mTime, mEquality,
                              std::numeric_limits<unsigned C_INT32>::max(),
                              mCascadingLevel);

  Calculations.first = mCalculations.begin();

  if (Calculations.first->first < UpperBound)
    {
      Calculations.second = mCalculations.upper_bound(Calculations.first->first);
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
  CProcessQueueKey UpperBound(mTime, mEquality,
                              std::numeric_limits<unsigned C_INT32>::max(),
                              mCascadingLevel);

  Assignments.first = mAssignments.begin();

  if (Assignments.first->first < UpperBound)
    {
      Assignments.second = mAssignments.upper_bound(Assignments.first->first);

      // Check whether we have a second set of assignments with a different ID.
      if (Assignments.second != mAssignments.end() &&
          Assignments.second->first < UpperBound)
        {
          mSimultaneousAssignments = true;
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

  for (; it != calculations.second; ++it)
    it->second.process();

  mCalculations.erase(calculations.first, calculations.second);

  return success;
}

bool CProcessQueue::executeAssignments(CProcessQueue::range & assignments)
{
  bool success = true;

  iterator it = assignments.first;

  for (; it != assignments.second; ++it)
    it->second.process();

  mAssignments.erase(assignments.first, assignments.second);

  return success;
}

// static
bool CProcessQueue::notEmpty(const CProcessQueue::range & range)
{
  return range.first != range.second;
}
