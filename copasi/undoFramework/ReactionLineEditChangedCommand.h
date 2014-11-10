// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * ReactionLineEditChangedCommand.h
 *
 *  Created on: 25 Jul 2014
 *      Author: dada
 */

#ifndef REACTIONLINEEDITCHANGEDCOMMAND_H_
#define REACTIONLINEEDITCHANGEDCOMMAND_H_

#include "CCopasiUndoCommand.h"

class ReactionLineEditChangedCommand: public CCopasiUndoCommand
{
public:
  ReactionLineEditChangedCommand(ReactionsWidget1 *pReactionWidget);
  void redo();
  void undo();
  QString lineEditChangedText() const;
  virtual ~ReactionLineEditChangedCommand();

private:
  ReactionsWidget1* mpReactionWidget;
  std::string mEq, mOldEq;
  std::string mFunctionName, mOldFunctionName;
  bool mFirstTime;
};

#endif /* REACTIONLINEEDITCHANGEDCOMMAND_H_ */
