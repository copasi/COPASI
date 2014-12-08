// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * DeleteEventCommand.cpp
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CEvent.h"
#include "model/CModel.h"
#include "UI/CQEventWidget1.h"

#include "UndoEventData.h"
#include "UndoEventAssignmentData.h"

#include "DeleteEventCommand.h"

DeleteEventCommand::DeleteEventCommand(CQEventWidget1 *pEVentWidget1)
{
  mpEVentWidget1 = pEVentWidget1;
  mFirstTime = true;
  mpEventData = new UndoEventData();
  std::string sName = mpEVentWidget1->mpEvent->getObjectName();
  mpEventData->setName(sName);

  CCopasiVector< CEventAssignment >::const_iterator it = mpEVentWidget1->mpEvent->getAssignments().begin();
  CCopasiVector< CEventAssignment >::const_iterator end = mpEVentWidget1->mpEvent->getAssignments().end();

  for (; it != end; ++it)
    {
      UndoEventAssignmentData *eventAssignData = new UndoEventAssignmentData();
      eventAssignData->setName((*it)->getObjectName());
      eventAssignData->setExpression((*it)->getExpression());
      eventAssignData->setTargetKey((*it)->getTargetKey());
      mpEventData->getEventAssignmentData()->append(eventAssignData);
    }

  /* for (; it != end; ++it)
     {
       CEventAssignment *eventAssign = new CEventAssignment((*it)->getTargetKey(), mpEVentWidget1->mpEvent->getObjectParent());
       eventAssign->setExpression((*it)->getExpression());
       mpEventData->getAssignments()->append(eventAssign);
     }*/

  mpEventData->setTriggerExpression(mpEVentWidget1->mpEvent->getTriggerExpression());
  mpEventData->setDelayExpression(mpEVentWidget1->mpEvent->getDelayExpression());
  mpEventData->setPriorityExpression(mpEVentWidget1->mpEvent->getPriorityExpression());

  this->setText(deleteEventText(sName));
}

void DeleteEventCommand::redo()
{
  if (mFirstTime)
    {
      mpEVentWidget1->deleteEvent();
      mFirstTime = false;
    }
  else
    {
      mpEVentWidget1->deleteEvent(mpEventData);
    }
}

void DeleteEventCommand::undo()
{
  mpEVentWidget1->addEvent(mpEventData);
}

QString DeleteEventCommand::deleteEventText(std::string &name) const
{
  std::string myEntityName(": Delete Event " + name);
  char* entityName = (char*)myEntityName.c_str();
  return QObject::tr(entityName);
}

DeleteEventCommand::~DeleteEventCommand()
{
  // TODO Auto-generated destructor stub
}
