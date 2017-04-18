// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

class CQEventDM;

class EventDataChangeCommand: public CCopasiUndoCommand
{
public:
  EventDataChangeCommand(QModelIndex index, const QVariant value, CQEventDM *pEventDM);
  virtual ~EventDataChangeCommand();

  void redo();
  void undo();

private:
  QVariant mNew, mOld;
  QModelIndex mIndex;
  CQEventDM *mpEventDM;
};

#endif /* EVENTDATACHANGECOMMAND_H_ */
