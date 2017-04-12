// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveReactionRowsCommand.h
 *
 *  Created on: 11 Aug 2014
 *      Author: dada
 */

#ifndef REMOVEREACTIONROWSCOMMAND_H_
#define REMOVEREACTIONROWSCOMMAND_H_

#include "CCopasiUndoCommand.h"

class UndoReactionData;
class CQReactionDM;

class RemoveReactionRowsCommand: public CCopasiUndoCommand
{
public:
  RemoveReactionRowsCommand(QModelIndexList rows, CQReactionDM * pReaDM, const QModelIndex&);
  virtual ~RemoveReactionRowsCommand();

  void redo();
  void undo();

private:
  CQReactionDM *mpReactionDM;
  QModelIndexList mRows;
  QList <UndoReactionData *> mpReaData;
};

#endif /* REMOVEREACTIONROWSCOMMAND_H_ */
