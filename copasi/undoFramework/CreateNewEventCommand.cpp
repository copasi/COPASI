// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CreateNewEventCommand.cpp
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#include "UI/CQEventWidget1.h"
#include "UndoEventData.h"

#include "CreateNewEventCommand.h"

CreateNewEventCommand::CreateNewEventCommand(CQEventWidget1 *pEventWidget)
{
  mpEventWidget = pEventWidget;
  mpEventData = new UndoEventData();
  this->setText(createNewEventText());
  mType = EVENTCREATE;
  setEntityType("Event");
}
void CreateNewEventCommand::redo()
{
  mpEventWidget->createNewEvent();

  std::string sName = mpEventWidget->mpEvent->getObjectName();
  mpEventData->setName(sName);
  mpEventData->setDelayExpression(mpEventWidget->mpEvent->getDelayExpression());
  mpEventData->setTriggerExpression(mpEventWidget->mpEvent->getTriggerExpression());
  mpEventData->setPriorityExpression(mpEventWidget->mpEvent->getPriorityExpression());
  setUndoState(true);
  setAction("Create");
  setName(sName);
}

void CreateNewEventCommand::undo()
{
  mpEventWidget->deleteEvent(mpEventData);
  setUndoState(false);
  setAction("Delete");
}

QString CreateNewEventCommand::createNewEventText() const
{
  std::string myEntityName(": Create New Event ");
  char* entityName = (char*)myEntityName.c_str();
  return QObject::tr(entityName);
}

CreateNewEventCommand::~CreateNewEventCommand()
{
  // TODO Auto-generated destructor stub
}

UndoData *CreateNewEventCommand::getUndoData() const
{
  return mpEventData;
}
