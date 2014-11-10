// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * EventDataChangeCommand.h
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#ifndef EVENTDATACHANGECOMMAND_H_
#define EVENTDATACHANGECOMMAND_H_

#include "CCopasiUndoCommand.h"

class EventDataChangeCommand: public CCopasiUndoCommand
{
public:
  EventDataChangeCommand(QModelIndex index, const QVariant value, int role, CQEventDM *pEventDM);
  void redo();
  void undo();
  QString eventDataChangeText() const;

private:
  QVariant mNew, mOld;
  QModelIndex mIndex;
  CQEventDM *mpEventDM;
  int mRole;
  Path mPathIndex;
  virtual ~EventDataChangeCommand();
};

#endif /* EVENTDATACHANGECOMMAND_H_ */
