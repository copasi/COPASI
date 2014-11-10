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

#include "UI/ReactionsWidget1.h"

#include "ReactionLineEditChangedCommand.h"

ReactionLineEditChangedCommand::ReactionLineEditChangedCommand(ReactionsWidget1 *pReactionWidget)
{
  mFirstTime = true;
  mpReactionWidget = pReactionWidget;
  mOldEq = mpReactionWidget->mpRi->getChemEqString();
  mOldFunctionName = mpReactionWidget->mpRi->getFunctionName();
  this->setText(lineEditChangedText());
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
}

void ReactionLineEditChangedCommand::undo()
{
  mpReactionWidget->restoreLineEditChanged(mOldEq, mOldFunctionName);
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
