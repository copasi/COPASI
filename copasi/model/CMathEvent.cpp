// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/Attic/CMathEvent.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/06/18 20:03:50 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <limits>

#include "copasi.h"

#include "CMathEvent.h"
#include "CMathModel.h"

#include "CEvent.h"

#include "report/CCopasiRootContainer.h"

CMathEvent::CAssignment::CAssignment(const CCopasiContainer * pParent) :
    CCopasiContainer("MathEventAssignment", pParent),
    mpTarget(NULL),
    mExpression("Expression", this)
{}

CMathEvent::CAssignment::CAssignment(const CMathEvent::CAssignment & src,
                                     const CCopasiContainer * pParent) :
    CCopasiContainer(src, pParent),
    mpTarget(src.mpTarget),
    mExpression(src.mExpression, this)
{}

CMathEvent::CAssignment::~CAssignment()
{}

bool CMathEvent::CAssignment::compile(const CEventAssignment * pAssignment,
                                      std::vector< CCopasiContainer * > listOfContainer)
{
  if (pAssignment == NULL)
    return false;

  bool success = true;

  mpTarget = NULL;

  if (pAssignment->getTargetObject() != NULL)
    {
      mpTarget = (C_FLOAT64 *) pAssignment->getTargetObject()->getValuePointer();
    }

  if (mpTarget == NULL)
    success = false;

  success &= mExpression.setInfix(pAssignment->getExpression());
  success &= mExpression.compile(listOfContainer);

  setDirectDependencies(mExpression.getDirectDependencies());

  return success;
}

CMathEvent::CMathEvent(const CCopasiContainer * pParent) :
    CCopasiContainer("MathEvent", pParent, "MathEvent"),
    mTrigger(this),
    mOrder(false),
    mHaveDelay(false),
    mDelay("DelayExpression", this),
    mDelayAssignment(true),
    mAssignments("ListOfMathEventAssignment", this),
    mDelayValueRefreshes(),
    mAssignmentValueRefreshes(),
    mDependentValueRefreshes()
{}

CMathEvent::CMathEvent(const CMathEvent & src,
                       const CCopasiContainer * pParent) :
    CCopasiContainer(src, pParent),
    mTrigger(src.mTrigger, this),
    mOrder(src.mOrder),
    mHaveDelay(src.mHaveDelay),
    mDelay(src.mDelay, this),
    mDelayAssignment(src.mDelayAssignment),
    mAssignments(src.mAssignments, this),
    mDelayValueRefreshes(src.mDelayValueRefreshes),
    mAssignmentValueRefreshes(src.mAssignmentValueRefreshes),
    mDependentValueRefreshes(src.mDependentValueRefreshes)
{}

CMathEvent::~CMathEvent()
{}

bool CMathEvent::compile(const CEvent * pEvent,
                         std::vector< CCopasiContainer * > listOfContainer)
{
  // A CMathEvent must be part of CMathModel to be compiled.
  CMathModel * pMathModel = dynamic_cast< CMathModel *>(getObjectAncestor("CMathModel"));

  if (pMathModel == NULL)
    return false;

  bool success = true;

  success &= mTrigger.compile(pEvent->getTriggerExpressionPtr(), listOfContainer);

  success &= mDelay.setInfix(pEvent->getDelayExpression());
  success &= mDelay.compile(listOfContainer);

  mHaveDelay = (mDelay.getInfix() != "");

  // Build the list of refresh calls needed to assure that the delay expression
  // can be calculated.

  mDelayValueRefreshes = pMathModel->buildRequiredRefreshList(mDelay.getDirectDependencies());

  mDelayAssignment = pEvent->getDelayAssignment();

  mAssignments.clear();

  CCopasiVectorN< CEventAssignment >::const_iterator it = pEvent->getAssignments().begin();
  CCopasiVectorN< CEventAssignment >::const_iterator end = pEvent->getAssignments().end();

  std::set< const CCopasiObject * > Assignments;
  std::set< const CCopasiObject * > Targets;

  for (; it != end; ++it)
    {
      CAssignment * pAssignment = new CAssignment();

      mAssignments.add(pAssignment, true);
      success &= pAssignment->compile(*it, listOfContainer);

      Assignments.insert(pAssignment);
      Targets.insert((*it)->getTargetObject());
    }

  // Build the list of refresh calls needed to assure that the assignment expressions
  // can be calculated.
  mAssignmentValueRefreshes = pMathModel->buildRequiredRefreshList(Assignments);

  // Build the list of refresh calls needed to assure that all dependent model values
  // are updated after the assignments are executed.
  mDependentValueRefreshes = pMathModel->buildRequiredRefreshList(Targets);

  return success;
}

void CMathEvent::processRoot(const C_FLOAT64 & time,
                             CProcessQueue & processQueue)
{
  // We first need ask the trigger whether to fire.
  bool Fire = mTrigger.fire();

  // If the event fires we need to schedule the event in the process queue
  if (Fire)
    {
      bool Equality = mTrigger.calculateEquality();

      unsigned C_INT32 EventId = processQueue.createEventId();

      // Add each assignment to the calculation queue
      CCopasiVector< CAssignment >::iterator itAssignment = mAssignments.begin();
      CCopasiVector< CAssignment >::iterator endAssignment = mAssignments.end();

      // Determine the execution time of the calculation of the event.
      C_FLOAT64 ExecutionTime = getExecutionTime(time);

      // We can only add calculations even if the calculation time is the current time.
      // This is due to the fact that equality and inequality checks are treated differently.
      for (; itAssignment != endAssignment; ++itAssignment)
        {
          // We must delay the calculation of the new target value
          processQueue.addCalculation(ExecutionTime,
                                      Equality,
                                      mOrder,
                                      EventId,
                                      (*itAssignment)->mpTarget,
                                      &(*itAssignment)->mExpression,
                                      this);
        }
    }
}

void CMathEvent::applyDelayRefreshes()
{
  std::vector< Refresh * >::const_iterator itRefresh = mDelayValueRefreshes.begin();
  std::vector< Refresh * >::const_iterator endRefresh = mDelayValueRefreshes.end();

  while (itRefresh != endRefresh)
    (**itRefresh++)();

  return;
}

void CMathEvent::applyValueRefreshes()
{
  std::vector< Refresh * >::const_iterator itRefresh = mAssignmentValueRefreshes.begin();
  std::vector< Refresh * >::const_iterator endRefresh = mAssignmentValueRefreshes.end();

  while (itRefresh != endRefresh)
    (**itRefresh++)();

  return;
}

void CMathEvent::applyDependentRefreshes()
{
  std::vector< Refresh * >::const_iterator itRefresh = mDependentValueRefreshes.begin();
  std::vector< Refresh * >::const_iterator endRefresh = mDependentValueRefreshes.end();

  while (itRefresh != endRefresh)
    (**itRefresh++)();

  return;
}

CMathTrigger & CMathEvent::getMathTrigger()
{
  return mTrigger;
}

const unsigned C_INT32 & CMathEvent::getOrder() const
{
  return mOrder;
}

C_FLOAT64 CMathEvent::getExecutionTime(const C_FLOAT64 & currentTime)
{
  // Determine the execution time of the event.
  C_FLOAT64 ExecutionTime = currentTime;

  if (mDelay.getInfix() != "")
    {
      // We make sure everything is up to date.
      applyDelayRefreshes();

      ExecutionTime += mDelay.calcValue();

      // Events are only allowed in forward integration. Thus the ExecutionTime
      // must not be less than the time.
      if (ExecutionTime - currentTime < 0.0)
        {
          // We allow small numerical errors.
          C_FLOAT64 Scale =
            (fabs(ExecutionTime) + fabs(currentTime)) * 50.0 * std::numeric_limits< C_FLOAT64 >::epsilon();

          // Both are approximately zero
          if (Scale < 100.0 * std::numeric_limits< C_FLOAT64 >::min())
            {
              ExecutionTime = currentTime;
            }
          // The difference is small compared to the scale
          else if (fabs(ExecutionTime - currentTime) < Scale)
            {
              ExecutionTime = currentTime;
            }
          // The execution time is definitely in the past
          else
            {
              // Create an error message and throw an exception.
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCMathModel + 2, ExecutionTime, currentTime);
            }
        }
    }

  return ExecutionTime;
}
