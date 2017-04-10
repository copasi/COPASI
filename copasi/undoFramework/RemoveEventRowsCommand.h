// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

};

#endif /* REMOVEEVENTROWSCOMMAND_H_ */
