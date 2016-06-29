// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
  CQReactionDM *pReactionDM)
  : CCopasiUndoCommand("Reaction", REACTION_DATA_CHANGE, "Change")
  , mNew(value)
  , mOld(index.data(Qt::DisplayRole))
  , mpReactionDM(pReactionDM)
  , mColumn(index.column())
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

  CReaction *pRea = &reactions[index.row()];
  mOldFunctionName = FROM_UTF8(pRea->getFunction()->getObjectName());

  //mPathIndex = pathFromIndex(index);

  //set the data for UNDO history
  setName(pRea->getObjectName());
  setKey(pRea->getKey());
  setOldValue(TO_UTF8(mOld.toString()));
  setNewValue(TO_UTF8(mNew.toString()));

  switch (mColumn)
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
  mpReactionDM->reactionDataChange(getKey(), mNew, mColumn, mNewFunctionName, mCreatedObjects);
  setAction("Change");
}

void ReactionDataChangeCommand::undo()
{
  //mIndex = pathToIndex(mPathIndex, mpReactionDM);
  mpReactionDM->reactionDataChange(getKey(), mOld, mColumn, mOldFunctionName, mCreatedObjects);
  setAction("Undone change");
}
