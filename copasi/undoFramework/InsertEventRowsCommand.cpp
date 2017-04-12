// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * InsertEventRowsCommand.cpp
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CEvent.h"
#include "model/CModel.h"
#include "CQEventDM.h"

#include "UndoEventData.h"
#include "UndoEventAssignmentData.h"
#include "InsertEventRowsCommand.h"

InsertEventRowsCommand::InsertEventRowsCommand(int position, int rows, CQEventDM *pEventDM)
  : CCopasiUndoCommand("Event", EVENT_INSERT)
  , mpEventDM(pEventDM)
  , mRows(rows)
  , mPosition(position)
  , mIndex()
  , mpEventData(NULL)
  , mValue()
{
  this->setText(QObject::tr(": Inserted new event"));
}

InsertEventRowsCommand::InsertEventRowsCommand(int position, int rows, CQEventDM *pEventDM, const QModelIndex& index, const QVariant& value)
  : CCopasiUndoCommand("Event", EVENT_INSERT)
  , mpEventDM(pEventDM)
  , mRows(rows)
  , mPosition(position)
  , mIndex(index)
  , mpEventData(NULL)
  , mValue(value)
{
  this->setText(QObject::tr(": Inserted new event"));
}

void InsertEventRowsCommand::redo()
{
  if (mpEventData == NULL)
    {
      mpEventDM->insertNewEventRow(mPosition, mRows, mIndex, mValue);

      assert(mpEventDM->getDataModel() != NULL);
      CModel * pModel = mpEventDM->getDataModel()->getModel();
      assert(pModel != NULL);

      // create always adds element at the end
      CEvent *pEvent = &pModel->getEvents()[pModel->getEvents().size() - 1];
      mpEventData = new UndoEventData(pEvent);
    }
  else
    {
      mpEventDM->addEventRow(mpEventData);
    }

  setUndoState(true);
  setAction("Add to list");
  setName(mpEventData->getName());
}

void InsertEventRowsCommand::undo()
{
  mpEventDM->deleteEventRow(mpEventData);
  setUndoState(false);
  setAction("Remove from list");
}

InsertEventRowsCommand::~InsertEventRowsCommand()
{
  pdelete(mpEventData);
}
