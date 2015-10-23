// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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

InsertEventRowsCommand::InsertEventRowsCommand(int position, int rows, CQEventDM *pEventDM, const QModelIndex& index)
  : CCopasiUndoCommand("Event", EVENT_INSERT)
  , mpEventDM(pEventDM)
  , mRows(rows)
  , mPosition(position)
  , mIndex(index)
  , mpEventData(new UndoEventData())
  , firstTime(true)
{
  this->setText(insertRowsText());
}

void InsertEventRowsCommand::redo()
{
  if (firstTime)
    {
      mpEventDM->insertNewEventRow(mPosition, mRows);
      GET_MODEL_OR_RETURN(pModel);

      CEvent *pEvent = pModel->getEvents()[mPosition];

      mpEventData->setName(pEvent->getObjectName());
      mpEventData->setKey(pEvent->getKey());
      mpEventData->setPriorityExpression(pEvent->getPriorityExpression());
      mpEventData->setDelayExpression(pEvent->getDelayExpression());
      mpEventData->setTriggerExpression(pEvent->getTriggerExpression());

      CCopasiVector< CEventAssignment >::const_iterator it = pEvent->getAssignments().begin();
      CCopasiVector< CEventAssignment >::const_iterator end = pEvent->getAssignments().end();

      for (; it != end; ++it)
        {
          const CModelEntity * pEntity = dynamic_cast< CModelEntity * >(CCopasiRootContainer::getKeyFactory()->get((*it)->getTargetKey()));
          mpEventData->getEventAssignmentData()->append(
            new UndoEventAssignmentData(pEntity, (*it)->getExpression()));
        }

      firstTime = false;
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

QString InsertEventRowsCommand::insertRowsText() const
{
  return QObject::tr(": Inserted new event");
}

UndoData *InsertEventRowsCommand::getUndoData() const
{
  return mpEventData;
}

InsertEventRowsCommand::~InsertEventRowsCommand()
{
  pdelete(mpEventData);
}
