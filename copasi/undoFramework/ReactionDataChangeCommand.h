// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include <vector>
#include <string>

#include "CCopasiUndoCommand.h"

class CQReactionDM;
class ReactionDataChangeCommand: public CCopasiUndoCommand
{

public:
  ReactionDataChangeCommand(const QModelIndex& index,
                            const QVariant& value,
                            CQReactionDM *pReactionDM);
  virtual ~ReactionDataChangeCommand();

  void redo();
  void undo();

private:
  QVariant mNew, mOld;
  CQReactionDM *mpReactionDM;
  int mColumn;
  Path mPathIndex;
  QString mOldFunctionName, mNewFunctionName;
  std::vector<std::string> mCreatedObjects;
};

#endif /* REACTIONDATACHANGECOMMAND_H_ */
