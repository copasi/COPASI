// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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

RemoveEventRowsCommand::RemoveEventRowsCommand(QModelIndexList rows, CQEventDM * pEventDM, const QModelIndex&)
{
  mpEventDM = pEventDM;
  mRows = rows;
  mFirstTime = true;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  assert(pModel != NULL);

  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      UndoEventData *data = new UndoEventData();

      if (!pEventDM->isDefaultRow(*i) && pModel->getEvents()[(*i).row()])
        {
          data->setName(pModel->getEvents()[(*i).row()]->getObjectName());
          data->setPriorityExpression(pModel->getEvents()[(*i).row()]->getPriorityExpression());
          data->setDelayExpression(pModel->getEvents()[(*i).row()]->getDelayExpression());
          data->setTriggerExpression(pModel->getEvents()[(*i).row()]->getTriggerExpression());

          CCopasiVector< CEventAssignment >::const_iterator it = pModel->getEvents()[(*i).row()]->getAssignments().begin();
          CCopasiVector< CEventAssignment >::const_iterator end = pModel->getEvents()[(*i).row()]->getAssignments().end();

          for (; it != end; ++it)
            {
              UndoEventAssignmentData *eventAssignData = new UndoEventAssignmentData();
              eventAssignData->setName((*it)->getObjectName());
              eventAssignData->setExpression((*it)->getExpression());
              eventAssignData->setTargetKey((*it)->getTargetKey());
              data->getEventAssignmentData()->append(eventAssignData);
            }

          mpEventData.append(data);
        }
    }

  this->setText(removeEventRowsText());
  mType = EVENTREMOVE;
  setEntityType("Event");
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
  // TODO Auto-generated destructor stub
}
