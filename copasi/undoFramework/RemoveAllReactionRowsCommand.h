// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveAllReactionRowsCommand.h
 *
 *  Created on: 12 Aug 2014
 *      Author: dada
 */

#ifndef REMOVEALLREACTIONROWSCOMMAND_H_
#define REMOVEALLREACTIONROWSCOMMAND_H_

#include "CCopasiUndoCommand.h"

class CQReactionDM;

class RemoveAllReactionRowsCommand: public CCopasiUndoCommand
{
public:
  RemoveAllReactionRowsCommand(CQReactionDM * pReaDM, const QModelIndex&);
  virtual ~RemoveAllReactionRowsCommand();

  void redo();
  void undo();

private:
  CQReactionDM *mpReactionDM;
  QList <UndoReactionData *> mpReaData;
};

#endif /* REMOVEALLREACTIONROWSCOMMAND_H_ */
