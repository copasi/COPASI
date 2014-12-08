// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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

InsertEventRowsCommand::InsertEventRowsCommand(int position, int rows, CQEventDM *pEventDM, const QModelIndex&): CCopasiUndoCommand()
{
  mpEventDM = pEventDM;
  mpEventData = new UndoEventData();
  this->setText(insertRowsText());
  mRows = rows;
  mPosition = position;
  firstTime = true;
}

void InsertEventRowsCommand::redo()
{
  if (firstTime)
    {
      mpEventDM->insertNewEventRow(mPosition, mRows, QModelIndex());
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
      assert(pDataModel != NULL);
      CModel * pModel = pDataModel->getModel();
      assert(pModel != NULL);

      CEvent *pEvent = pModel->getEvents()[mPosition];

      mpEventData->setName(pEvent->getObjectName());
      mpEventData->setPriorityExpression(pEvent->getPriorityExpression());
      mpEventData->setDelayExpression(pEvent->getDelayExpression());
      mpEventData->setTriggerExpression(pEvent->getTriggerExpression());

      CCopasiVector< CEventAssignment >::const_iterator it = pEvent->getAssignments().begin();
      CCopasiVector< CEventAssignment >::const_iterator end = pEvent->getAssignments().end();

      for (; it != end; ++it)
        {
          UndoEventAssignmentData *eventAssignData = new UndoEventAssignmentData();
          eventAssignData->setName((*it)->getObjectName());
          eventAssignData->setExpression((*it)->getExpression());
          eventAssignData->setTargetKey((*it)->getTargetKey());
          mpEventData->getEventAssignmentData()->append(eventAssignData);
        }

      /*     for (; it != end; ++it)
             {
               CEventAssignment *eventAssign = new CEventAssignment((*it)->getTargetKey(), pEvent->getObjectParent());
               eventAssign->setExpression((*it)->getExpression());
               mpEventData->getAssignments()->append(eventAssign);
             }*/

      firstTime = false;
    }
  else
    {
      mpEventDM->addEventRow(mpEventData);
    }
}

void InsertEventRowsCommand::undo()
{
  mpEventDM->deleteEventRow(mpEventData);
}

QString InsertEventRowsCommand::insertRowsText() const
{
  return QObject::tr(": Inserted New Event");
}

InsertEventRowsCommand::~InsertEventRowsCommand()
{
  // TODO Auto-generated destructor stub
}
