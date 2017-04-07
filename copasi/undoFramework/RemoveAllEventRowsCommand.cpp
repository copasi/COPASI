// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveAllEventRowsCommand.cpp
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#include "copasi.h"

#include "report/CCopasiRootContainer.h"
#include "model/CEvent.h"
#include "model/CModel.h"
#include "UI/CQEventDM.h"

#include "UndoEventData.h"
#include "UndoEventAssignmentData.h"
#include "RemoveAllEventRowsCommand.h"

RemoveAllEventRowsCommand::RemoveAllEventRowsCommand(
  CQEventDM * pEventDM, const QModelIndex&)
  : CCopasiUndoCommand("Event", EVENT_REMOVE_ALL, "Remove All")
  , mpEventDM(pEventDM)
  , mpEventData()
{
  CCopasiDataModel * pDataModel = mpEventDM->getDataModel();
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);

  for (int i = 0; i != pEventDM->rowCount() - 1; ++i)
    {
      if (&pModel->getEvents()[i])
        {
          UndoEventData *data = new UndoEventData(&pModel->getEvents()[i]);
          mpEventData.append(data);
        }
    }

  setText(QObject::tr(": Removed All Events"));
}

void RemoveAllEventRowsCommand::redo()
{
  mpEventDM->removeAllEventRows();
  setUndoState(true);
  setAction("Delete all");
}

void RemoveAllEventRowsCommand::undo()
{
  mpEventDM->insertEventRows(mpEventData);
  setUndoState(false);
  setAction("Undelete all");
}

RemoveAllEventRowsCommand::~RemoveAllEventRowsCommand()
{
  // freeing the memory allocated above
  foreach(UndoEventData * data, mpEventData)
  {
    pdelete(data);
  }

  mpEventData.clear();
}
