// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveEventRowsCommand.h
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#ifndef REMOVEEVENTROWSCOMMAND_H_
#define REMOVEEVENTROWSCOMMAND_H_

#include "CCopasiUndoCommand.h"

class CQEventDM;

class RemoveEventRowsCommand: public CCopasiUndoCommand
{
public:
  RemoveEventRowsCommand(QModelIndexList rows, CQEventDM * pEventDM, const QModelIndex&);
  virtual ~RemoveEventRowsCommand();

  void redo();
  void undo();

private:
  CQEventDM *mpEventDM;
  QModelIndexList mRows;
  QList <UndoEventData *> mpEventData;

  bool mFirstTime;
};

#endif /* REMOVEEVENTROWSCOMMAND_H_ */
