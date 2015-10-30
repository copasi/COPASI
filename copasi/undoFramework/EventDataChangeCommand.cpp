// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * EventDataChangeCommand.cpp
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CEvent.h"
#include "model/CModel.h"
#include "qtUtilities.h"

#include "CQEventDM.h"

#include "EventDataChangeCommand.h"

EventDataChangeCommand::EventDataChangeCommand(QModelIndex index, const QVariant value, int role, CQEventDM *pEventDM)
  : CCopasiUndoCommand("Event", EVENT_DATA_CHANGE, "Change")
  , mNew(value)
  , mOld(index.data(Qt::DisplayRole))
  , mIndex(index)
  , mpEventDM(pEventDM)
  , mRole(role)
  , mPathIndex()
{
  //set the data for UNDO history
  GET_MODEL_OR_RETURN(pModel);


  if (pModel->getEvents().size() <= (size_t)index.row())
    {
      return;
    }

  CEvent *pEvent = pModel->getEvents()[index.row()];
  setName(pEvent->getObjectName());
  setOldValue(TO_UTF8(mOld.toString()));
  setNewValue(TO_UTF8(mNew.toString()));

  switch (index.column())
    {
      case 0:
        setProperty("");
        break;

      case 1:
        setProperty("Name");
        break;
    }

  this->setText(QString(": Changed event %1").arg(getProperty().c_str()));
}

void EventDataChangeCommand::redo()
{
  mpEventDM->eventDataChange(mIndex, mNew, mRole);
}

void EventDataChangeCommand::undo()
{
  mpEventDM->eventDataChange(mIndex, mOld, mRole);
  setAction("Undone change");
}

EventDataChangeCommand::~EventDataChangeCommand()
{
}
