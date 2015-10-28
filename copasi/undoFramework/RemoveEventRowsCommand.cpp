// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveEventRowsCommand.cpp
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CModel.h"
#include "CQEventDM.h"
#include "model/CEvent.h"

#include "UndoEventData.h"
#include "UndoEventAssignmentData.h"

#include "RemoveEventRowsCommand.h"

RemoveEventRowsCommand::RemoveEventRowsCommand(
  QModelIndexList rows, CQEventDM * pEventDM, const QModelIndex&)
  : CCopasiUndoCommand("Event", EVENT_REMOVE)
  , mpEventDM(pEventDM)
  , mRows(rows)
  , mpEventData()
  , mFirstTime(true)
{
  GET_MODEL_OR_RETURN(pModel);

  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {

      if (!pEventDM->isDefaultRow(*i) && pModel->getEvents()[(*i).row()])
        {
          UndoEventData *data = new UndoEventData(pModel->getEvents()[(*i).row()]);
          mpEventData.append(data);
        }
    }

  this->setText(removeEventRowsText());
}

void RemoveEventRowsCommand::redo()
{
  if (mFirstTime)
    {
      mpEventDM->removeEventRows(mRows, QModelIndex());
      mFirstTime = false;
    }
  else
    {
      mpEventDM->deleteEventRows(mpEventData);
    }

  setUndoState(true);
  setAction("Delete set");
}

void RemoveEventRowsCommand::undo()
{
  mpEventDM->insertEventRows(mpEventData);
  setUndoState(false);
  setAction("Undelete set");
}

QString RemoveEventRowsCommand::removeEventRowsText() const
{
  return QObject::tr(": Removed Event");
}

RemoveEventRowsCommand::~RemoveEventRowsCommand()
{
  // freeing the memory allocated above
  foreach(UndoEventData * data, mpEventData)
  {
    pdelete(data);
  }
  mpEventData.clear();

}
