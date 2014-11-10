// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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

class insertReactionRowsCommand: public CCopasiUndoCommand
{
public:
  insertReactionRowsCommand(int position, int rows, CQReactionDM *pReactionDM, const QModelIndex&);
  virtual ~insertReactionRowsCommand();
  void redo();
  void undo();
  QString insertRowsText() const;

private:
  CQReactionDM* mpReactionDM;
  int mRows, mPosition;
  QModelIndex mIndex;
  CReaction *mpReaction;
  CReactionInterface *mpRi;
};

#endif /* INSERTREACTIONROWSCOMMAND_H_ */
