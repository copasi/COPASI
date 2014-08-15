// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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

class RemoveReactionRowsCommand: public CCopasiUndoCommand
{
public:
  RemoveReactionRowsCommand(QModelIndexList rows, CQReactionDM * pReaDM, const QModelIndex&);
  void redo();
  void undo();
  QString removeReactionRowsText() const;
  virtual ~RemoveReactionRowsCommand();

private:
  CQReactionDM *mpReactionDM;
  QModelIndexList mRows;
  QList <UndoReactionData *> mpReaData;
  bool mFirstTime;
};

#endif /* REMOVEREACTIONROWSCOMMAND_H_ */
