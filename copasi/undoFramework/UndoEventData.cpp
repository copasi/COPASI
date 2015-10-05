// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoEventData.cpp
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#include <QtCore/QList>

#include "model/CModel.h"
#include <copasi/model/CEvent.h>

#include "UndoEventData.h"

#include "UndoEventAssignmentData.h"

UndoEventData::UndoEventData(const std::string &key  /*= ""*/,
                             const std::string &name /*= ""*/,
                             const std::string &type /*= ""*/)
  : UndoData(key, name, type)
  , mPriorityExpression()
  , mTriggerExpression()
  , mDelayExpression()
  , mType(Discontinuity)
  , mDelayAssignment(false)
  , mFireAtInitialTime(false)
  , mPersistentTrigger(false)
  , mEventAssignmentData(new QList <UndoEventAssignmentData*>())
{
}

UndoEventData::~UndoEventData()
{
  pdelete(mEventAssignmentData);
}

const std::string&
UndoEventData::getDelayExpression() const
{
  return mDelayExpression;
}

const std::string&
UndoEventData::getPriorityExpression() const
{
  return mPriorityExpression;
}

const std::string&
UndoEventData::getTriggerExpression() const
{
  return mTriggerExpression;
}

UndoEventData::Type
UndoEventData::getType() const
{
  return mType;
}

bool
UndoEventData::isDelayAssignment() const
{
  return mDelayAssignment;
}

bool
UndoEventData::isFireAtInitialTime() const
{
  return mFireAtInitialTime;
}

bool
UndoEventData::isPersistentTrigger() const
{
  return mPersistentTrigger;
}

void
UndoEventData::setDelayAssignment(bool delayAssignment)
{
  mDelayAssignment = delayAssignment;
}

void
UndoEventData::setDelayExpression(const std::string &delayExpression)
{
  mDelayExpression = delayExpression;
}

void
UndoEventData::setPriorityExpression(const std::string &priorityExpression)
{
  mPriorityExpression = priorityExpression;
}

void
UndoEventData::setFireAtInitialTime(bool fireAtInitialTime)
{
  mFireAtInitialTime = fireAtInitialTime;
}

void
UndoEventData::setPersistentTrigger(bool persistentTrigger)
{
  mPersistentTrigger = persistentTrigger;
}

void
UndoEventData::setTriggerExpression(const std::string &triggerExpression)
{
  mTriggerExpression = triggerExpression;
}

void UndoEventData::setType(Type &type)
{
  mType = type;
}

QList<UndoEventAssignmentData*> *
UndoEventData::getEventAssignmentData() const
{
  return mEventAssignmentData;
}

void UndoEventData::appendEventAssignmentData(
  UndoEventAssignmentData *eventAssignData)
{
  mEventAssignmentData->append(eventAssignData);
}

CEvent *
UndoEventData::createEventFromData(CModel *pModel)
{
  CEvent *pEvent =  pModel->createEvent(getName());

  //set the expressions
  pEvent->setTriggerExpression(getTriggerExpression());
  pEvent->setDelayExpression(getDelayExpression());
  pEvent->setPriorityExpression(getPriorityExpression());

  QList <UndoEventAssignmentData *> *assignmentData = getEventAssignmentData();
  QList <UndoEventAssignmentData *>::const_iterator i;

  for (i = assignmentData->begin(); i != assignmentData->end(); ++i)
    {
      UndoEventAssignmentData * assignData = *i;
      assignData->addToEvent(pEvent);
    }

  return pEvent;
}
