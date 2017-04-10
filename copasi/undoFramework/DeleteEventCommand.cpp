// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * DeleteEventCommand.cpp
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#include "copasi.h"

#include "report/CCopasiRootContainer.h"
#include "model/CEvent.h"
#include "model/CModel.h"
#include "UI/CQEventWidget1.h"

#include "UndoEventData.h"
#include "UndoEventAssignmentData.h"

#include "DeleteEventCommand.h"

DeleteEventCommand::DeleteEventCommand(CQEventWidget1 *pEVentWidget1)
  : CCopasiUndoCommand("Event", EVENT_DELETE)
  , mpEventData(new UndoEventData(pEVentWidget1->mpEvent))
  , mpEVentWidget1(pEVentWidget1)
{
  const std::string& sName = mpEVentWidget1->mpEvent->getObjectName();
  setName(sName);
  this->setText(QString(": Deleted event %1").arg(sName.c_str()));
}

void DeleteEventCommand::redo()
{
  mpEVentWidget1->deleteEvent(mpEventData);
  setUndoState(true);
  setAction("Delete");
}

void DeleteEventCommand::undo()
{
  mpEVentWidget1->addEvent(mpEventData);
  setUndoState(false);
  setAction("Undelete");
}

DeleteEventCommand::~DeleteEventCommand()
{
  pdelete(mpEventData);
}
