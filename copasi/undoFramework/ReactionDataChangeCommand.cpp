// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * ReactionDataChangeCommand.cpp
 *
 *  Created on: 3 Jul 2014
 *      Author: dada
 */
#include "report/CCopasiRootContainer.h"

#include "ReactionDataChangeCommand.h"
#include "CQReactionDM.h"
#include <QDebug>
#include "qtUtilities.h"

ReactionDataChangeCommand::ReactionDataChangeCommand(QModelIndex index, const QVariant value, int role, CQReactionDM *pReactionDM)
{
  // stores the data
  mOld = index.data(Qt::DisplayRole);
  mNew = value;
  mpReactionDM = pReactionDM;
  mIndex = index;
  mRole = role;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiVectorNS < CReaction > &reactions = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getReactions();

  if (reactions.size() <= index.row())
    {
      // TODO: here you have the case of a new reaction added, that you need to handle
      //       otherwise it will crash, for now return
      return;
    }

  CReaction *pRea = reactions[index.row()];
  mOldFunctionName = FROM_UTF8(pRea->getFunction()->getObjectName());
  mNewFunctionName = "";

  //mPathIndex = pathFromIndex(index);
  this->setText(reactionDataChangeText());
}

ReactionDataChangeCommand::~ReactionDataChangeCommand()
{
  // TODO Auto-generated destructor stub
}

void ReactionDataChangeCommand::redo()
{
  mpReactionDM->reactionDataChange(mIndex, mNew, mRole, mNewFunctionName);
}
void ReactionDataChangeCommand::undo()
{
  //mIndex = pathToIndex(mPathIndex, mpReactionDM);
  mpReactionDM->reactionDataChange(mIndex, mOld, mRole, mOldFunctionName);
}
QString ReactionDataChangeCommand::reactionDataChangeText() const
{
  return QObject::tr(": Changed Reaction Data");
}
