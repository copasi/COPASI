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
}

void EventDataChangeCommand::redo()
{
  mpEventDM->eventDataChange(mIndex, mNew, mRole);
}
void EventDataChangeCommand::undo()
{
  //mIndex = pathToIndex(mPathIndex, mpEventDM);
  mpEventDM->eventDataChange(mIndex, mOld, mRole);
}
QString EventDataChangeCommand::eventDataChangeText() const
{
  return QObject::tr(": Changed Global Quantity Data");
}

EventDataChangeCommand::~EventDataChangeCommand()
{
  // TODO Auto-generated destructor stub
}
