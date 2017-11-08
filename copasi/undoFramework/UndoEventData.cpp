// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/copasi.h"

#include "copasi/model/CModel.h"
#include "copasi/model/CEvent.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "UndoEventData.h"

#include "UndoEventAssignmentData.h"

UndoEventData::UndoEventData(const std::string &key  /*= ""*/,
                             const std::string &name /*= ""*/,
                             const std::string &type /*= ""*/)
  : UndoData(key, name, type)
  , mPriorityExpression()
  , mTriggerExpression()
  , mDelayExpression()
  , mType(CEvent::Discontinuity)
  , mDelayAssignment(false)
  , mFireAtInitialTime(false)
  , mPersistentTrigger(false)
  , mEventAssignmentData(new QList <UndoEventAssignmentData * >())
{
}

UndoEventData::UndoEventData(const CEvent *pEvent)
  : UndoData(pEvent->getKey(), pEvent->getObjectName())
  , mPriorityExpression(pEvent->getPriorityExpression())
  , mTriggerExpression(pEvent->getTriggerExpression())
  , mDelayExpression(pEvent->getDelayExpression())
  , mType(pEvent->getType())
  , mDelayAssignment(pEvent->getDelayAssignment())
  , mFireAtInitialTime(pEvent->getFireAtInitialTime())
  , mPersistentTrigger(pEvent->getPersistentTrigger())
  , mEventAssignmentData(new QList <UndoEventAssignmentData * >())
{
  CDataVector< CEventAssignment >::const_iterator it = pEvent->getAssignments().begin();
  CDataVector< CEventAssignment >::const_iterator end = pEvent->getAssignments().end();

  CDataModel * pDataModel = pEvent->getObjectDataModel();

  for (; it != end; ++it)
    {
      const CModelEntity * pEntity = dynamic_cast< const CModelEntity * >(CObjectInterface::DataObject(pDataModel->getObject(it->getTargetCN())));
      mEventAssignmentData->append(
        new UndoEventAssignmentData(pEntity, it->getExpression()));
    }
}

UndoEventData::~UndoEventData()
{
  pdelete(mEventAssignmentData);
}

CDataObject *
UndoEventData::createObjectIn(CModel *pModel)
{
  if (pModel == NULL) return NULL;

  if (pModel->getEvents().getIndex(getName()) != C_INVALID_INDEX)
    return NULL;

  createDependentObjects(pModel);

  CEvent *pEvent =  pModel->createEvent(getName());

  if (pEvent == NULL)
    return NULL;

  mKey = pEvent->getKey();
  return pEvent;
}

CDataObject *
UndoEventData::restoreObjectIn(CModel *pModel)
{
  CDataObject *pEvent = createObjectIn(pModel);

  if (pEvent == NULL)
    return NULL;

  fillObject(pModel);
  fillDependentObjects(pModel);

  return pEvent;
}

void UndoEventData::fillObject(CModel *)
{
  CEvent* pEvent = dynamic_cast<CEvent*>(CRootContainer::getKeyFactory()->get(mKey));

  if (pEvent == NULL) return;

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

CEvent::Type
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

void UndoEventData::setType(CEvent::Type &type)
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
