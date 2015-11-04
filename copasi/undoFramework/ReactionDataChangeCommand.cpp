// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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

ReactionDataChangeCommand::ReactionDataChangeCommand(
  const QModelIndex& index,
  const QVariant& value,
  int role,
  CQReactionDM *pReactionDM)
  : CCopasiUndoCommand("Reaction", REACTION_DATA_CHANGE, "Change")
  , mNew(value)
  , mOld(index.data(Qt::DisplayRole))
  , mIndex(index)
  , mpReactionDM(pReactionDM)
  , mRole(role)
  , mPathIndex()
  , mOldFunctionName()
  , mNewFunctionName("")
  , mCreatedObjects()
{
  // stores the data

  GET_MODEL_OR_RETURN(pModel);

  CCopasiVectorNS < CReaction > &reactions = pModel->getReactions();

  if ((int)reactions.size() <= index.row())
    {
      return;
    }

  CReaction *pRea = reactions[index.row()];
  mOldFunctionName = FROM_UTF8(pRea->getFunction()->getObjectName());

  //mPathIndex = pathFromIndex(index);

  //set the data for UNDO history
  setName(pRea->getObjectName());
  setOldValue(TO_UTF8(mOld.toString()));
  setNewValue(TO_UTF8(mNew.toString()));

  switch (index.column())
    {
      case 0:
        setProperty("");
        break;

      case 1:
        setProperty("Name");
        break;

      case 2:
        setProperty("Reaction");
        break;
    }

  setText(QString(": Changed reaction %1").arg(getProperty().c_str()));
}

ReactionDataChangeCommand::~ReactionDataChangeCommand()
{
}

void ReactionDataChangeCommand::redo()
{
  mpReactionDM->reactionDataChange(mIndex, mNew, mRole, mNewFunctionName, mCreatedObjects);
}

void ReactionDataChangeCommand::undo()
{
  //mIndex = pathToIndex(mPathIndex, mpReactionDM);
  mpReactionDM->reactionDataChange(mIndex, mOld, mRole, mOldFunctionName, mCreatedObjects);
  setAction("Undone change");
}
