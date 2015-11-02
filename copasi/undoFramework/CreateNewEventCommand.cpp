// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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
  : CCopasiUndoCommand("Event", EVENT_CREATE)
  , mpEventData(NULL)
  , mpEventWidget(pEventWidget)
{
  this->setText(QObject::tr(": Created new event "));
}

void CreateNewEventCommand::redo()
{
  if (mpEventData == NULL)
    {
      mpEventWidget->createNewEvent();

      std::string sName = mpEventWidget->mpEvent->getObjectName();
      mpEventData = new UndoEventData(mpEventWidget->mpEvent);
      setName(sName);
    }
  else
    {
      mpEventWidget->addEvent(mpEventData);
    }

  setUndoState(true);
  setAction("Create");
}

void CreateNewEventCommand::undo()
{
  mpEventWidget->deleteEvent(mpEventData);
  setUndoState(false);
  setAction("Delete");
}

CreateNewEventCommand::~CreateNewEventCommand()
{
  pdelete(mpEventData);
}

