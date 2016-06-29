// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * ReactionLineEditChangedCommand.h
 *
 *  Created on: 25 Jul 2014
 *      Author: dada
 */

#ifndef REACTION_CHANGE_COMMAND_H_
#define REACTION_CHANGE_COMMAND_H_

#include <vector>

#include "CCopasiUndoCommand.h"

class ReactionsWidget1;
class CReaction;

class ReactionChangeCommand: public CCopasiUndoCommand
{
public:
  ReactionChangeCommand(
    CCopasiUndoCommand::Type type,
    const QVariant& oldValue,
    const QVariant& newValue,
    ReactionsWidget1 *pReactionWidget,
    CReaction* pReaction,
    const QVariant& oldSecondValue = "",
    const QVariant& newSecondValueValue = ""
  );
  virtual ~ReactionChangeCommand();

  void redo();
  void undo();

  static void removeCreatedObjects(const std::vector<std::string>& createdObjects);

  const std::vector< std::string >& getCreatedObjects() const;
  void setCreatedObjects(const std::vector<std::string>& createdObjects);

private:
  ReactionsWidget1* mpReactionWidget;
  std::string mKey;
  QVariant mOldValue;
  QVariant mNewValue;
  QVariant mOldSecondValue;
  QVariant mNewSecondValue;
  std::vector<std::string> mCreatedObjects;
};

#endif /* REACTION_CHANGE_COMMAND_H_ */
