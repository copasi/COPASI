// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * ReactionDataChangeCommand.h
 *
 *  Created on: 3 Jul 2014
 *      Author: dada
 */

#ifndef REACTIONDATACHANGECOMMAND_H_
#define REACTIONDATACHANGECOMMAND_H_

#include "CCopasiUndoCommand.h"

class CQReactionDM;
class ReactionDataChangeCommand: public CCopasiUndoCommand
{

public:
  ReactionDataChangeCommand(QModelIndex index, const QVariant value, int role, CQReactionDM *pReactionDM);
  void redo();
  void undo();
  QString reactionDataChangeText() const;
  virtual ~ReactionDataChangeCommand();

private:
  QVariant mNew, mOld;
  QModelIndex mIndex;
  CQReactionDM *mpReactionDM;
  int mRole;
  Path mPathIndex;
  QString mOldFunctionName, mNewFunctionName;
};

#endif /* REACTIONDATACHANGECOMMAND_H_ */
