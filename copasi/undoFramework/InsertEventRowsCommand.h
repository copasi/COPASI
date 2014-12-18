// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * InsertEventRowsCommand.h
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#ifndef INSERTEVENTROWSCOMMAND_H_
#define INSERTEVENTROWSCOMMAND_H_

#include "CCopasiUndoCommand.h"

class UndoEventData;

class InsertEventRowsCommand: public CCopasiUndoCommand
{
public:
  InsertEventRowsCommand(int position, int rows, CQEventDM *pEventDM, const QModelIndex&);
  virtual ~InsertEventRowsCommand();
  void redo();
  void undo();
  QString insertRowsText() const;
  UndoData *getUndoData() const;

private:
  CQEventDM* mpEventDM;
  int mRows, mPosition;
  QModelIndex mIndex;
  UndoEventData* mpEventData;
  int firstTime;
};

#endif /* INSERTEVENTROWSCOMMAND_H_ */
