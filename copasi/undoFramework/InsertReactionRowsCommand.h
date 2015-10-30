// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * insertReactionRowsCommand.h
 *
 *  Created on: 5 Aug 2014
 *      Author: dada
 */

#ifndef INSERTREACTIONROWSCOMMAND_H_
#define INSERTREACTIONROWSCOMMAND_H_

#include "CCopasiUndoCommand.h"

class UndoReactionData;
class CQReactionDM;
class CReaction;
class CReactionInterface;

class InsertReactionRowsCommand: public CCopasiUndoCommand
{
public:
  InsertReactionRowsCommand(int position, int rows, CQReactionDM *pReactionDM, const QModelIndex&);
  virtual ~InsertReactionRowsCommand();

  void redo();
  void undo();

private:
  CQReactionDM* mpReactionDM;
  int mRows, mPosition;
  QModelIndex mIndex;
  CReaction *mpReaction;
  CReactionInterface *mpRi;
  UndoReactionData *mpReactionData;
};

#endif /* INSERTREACTIONROWSCOMMAND_H_ */
