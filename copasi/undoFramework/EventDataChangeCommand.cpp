// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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
{
  // stores the data
  mOld = index.data(Qt::DisplayRole);
  mNew = value;
  mpEventDM = pEventDM;
  mIndex = index;
  mRole = role;

  //mPathIndex = pathFromIndex(index);
  this->setText(eventDataChangeText());

  //set the data for UNDO history
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();
  CEvent *pEvent = pModel->getEvents()[index.row()];
  mType = EVENTDATACHANGE;
  setEntityType("Event");
  setAction("Change");
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
}

void EventDataChangeCommand::redo()
{
  mpEventDM->eventDataChange(mIndex, mNew, mRole);
}
void EventDataChangeCommand::undo()
{
  //mIndex = pathToIndex(mPathIndex, mpEventDM);
  mpEventDM->eventDataChange(mIndex, mOld, mRole);
  setAction("Unchange");
}
QString EventDataChangeCommand::eventDataChangeText() const
{
  return QObject::tr(": Changed Global Quantity Data");
}

EventDataChangeCommand::~EventDataChangeCommand()
{
  // TODO Auto-generated destructor stub
}
