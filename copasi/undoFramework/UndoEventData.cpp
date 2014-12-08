// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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

//#include "model/CEvent.h"

#include "UndoEventData.h"

#include "UndoEventAssignmentData.h"

UndoEventData::UndoEventData()
{

  mEventAssignmentData = new QList <UndoEventAssignmentData*>();
}

UndoEventData::~UndoEventData()
{
  // TODO Auto-generated destructor stub
}

std::string UndoEventData::getDelayExpression() const
{
  return delayExpression;
}

std::string UndoEventData::getPriorityExpression() const
{
  return priorityExpression;
}

std::string UndoEventData::getTriggerExpression() const
{
  return triggerExpression;
}

UndoEventData::Type UndoEventData::getType() const
{
  return type;
}

bool UndoEventData::isDelayAssignment() const
{
  return mDelayAssignment;
}

bool UndoEventData::isFireAtInitialTime() const
{
  return mFireAtInitialTime;
}

bool UndoEventData::isPersistentTrigger() const
{
  return mPersistentTrigger;
}

void UndoEventData::setDelayAssignment(bool delayAssignment)
{
  mDelayAssignment = delayAssignment;
}

void UndoEventData::setDelayExpression(const std::string &delayExpression)
{
  this->delayExpression = delayExpression;
}

void UndoEventData::setPriorityExpression(const std::string &priorityXxpression)
{
  this->priorityExpression = priorityExpression;
}

void UndoEventData::setFireAtInitialTime(bool fireAtInitialTime)
{
  mFireAtInitialTime = fireAtInitialTime;
}

void UndoEventData::setPersistentTrigger(bool persistentTrigger)
{
  mPersistentTrigger = persistentTrigger;
}

void UndoEventData::setTriggerExpression(const std::string &triggerExpression)
{
  this->triggerExpression = triggerExpression;
}

void UndoEventData::setType(Type &type)
{
  this->type = type;
}

QList<UndoEventAssignmentData*> *UndoEventData::getEventAssignmentData() const
{
  return mEventAssignmentData;
}

void UndoEventData::setEventAssignmentData(QList<UndoEventAssignmentData *> *eventAssignmentData)
{
  mEventAssignmentData = eventAssignmentData;
}
