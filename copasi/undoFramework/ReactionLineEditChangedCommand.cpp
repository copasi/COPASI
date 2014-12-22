// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * ReactionLineEditChangedCommand.cpp
 *
 *  Created on: 25 Jul 2014
 *      Author: dada
 */

#include "model/CReaction.h"
#include "UI/ReactionsWidget1.h"

#include "ReactionLineEditChangedCommand.h"

ReactionLineEditChangedCommand::ReactionLineEditChangedCommand(ReactionsWidget1 *pReactionWidget)
{
  mFirstTime = true;
  mpReactionWidget = pReactionWidget;
  mOldEq = mpReactionWidget->mpRi->getChemEqString();
  mOldFunctionName = mpReactionWidget->mpRi->getFunctionName();
  this->setText(lineEditChangedText());

  //set the data for UNDO history
  mType = REACTIONLINEEDITCHANGE;
  setEntityType("Reaction");
  setAction("Change");
  CReaction* reac = dynamic_cast< CReaction * >(mpReactionWidget->mpObject);
  setName(reac->getObjectName());
  setOldValue(mOldEq);
  setProperty("Reaction");
}
void ReactionLineEditChangedCommand::redo()
{
  if (mFirstTime)
    {
      mpReactionWidget->lineEditChanged();
      mEq = mpReactionWidget->mpRi->getChemEqString();
      mFunctionName = mpReactionWidget->mpRi->getFunctionName();
      mFirstTime = false;
    }
  else
    {
      mpReactionWidget->restoreLineEditChanged(mEq, mFunctionName);
    }

  setNewValue(mEq);
}

void ReactionLineEditChangedCommand::undo()
{
  mpReactionWidget->restoreLineEditChanged(mOldEq, mOldFunctionName);
  setProperty("Unchange");
}

QString ReactionLineEditChangedCommand::lineEditChangedText() const
{
  std::string myEntityName(": Reaction Line Edit ");
  char* entityName = (char*)myEntityName.c_str();
  return QObject::tr(entityName);
}

ReactionLineEditChangedCommand::~ReactionLineEditChangedCommand()
{
  // TODO Auto-generated destructor stub
}
