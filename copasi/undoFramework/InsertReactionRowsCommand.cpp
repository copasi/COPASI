// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * insertReactionRowsCommand.cpp
 *
 *  Created on: 5 Aug 2014
 *      Author: dada
 */

#include <QUndoCommand>
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CChemEqInterface.h"
#include "model/CReaction.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "CQReactionDM.h"
#include "qtUtilities.h"

#include "UndoReactionData.h"
#include "InsertReactionRowsCommand.h"

InsertReactionRowsCommand::InsertReactionRowsCommand(int position, int rows, CQReactionDM *pReactionDM)
  : CCopasiUndoCommand("Reaction", REACTION_INSERT)
  , mpReactionDM(pReactionDM)
  , mRows(rows)
  , mPosition(position)
  , mIndex()
  , mpReaction(NULL)
  , mpRi(NULL)
  , mpReactionData(NULL)
  , mValue()
{
  setText(QObject::tr(": Inserted new reaction"));

}

InsertReactionRowsCommand::InsertReactionRowsCommand(int position, int rows, CQReactionDM *pReactionDM, const QModelIndex& index, const QVariant& value)
  : CCopasiUndoCommand("Reaction", REACTION_INSERT)
  , mpReactionDM(pReactionDM)
  , mRows(rows)
  , mPosition(position)
  , mIndex(index)
  , mpReaction(NULL)
  , mpRi(NULL)
  , mpReactionData(NULL)
  , mValue(value)
{
  setText(QObject::tr(": Inserted new reaction"));
}

InsertReactionRowsCommand::~InsertReactionRowsCommand()
{
  pdelete(mpReactionData)
}

void InsertReactionRowsCommand::redo()
{
  if (mpReactionData == NULL)
    {
      mpReactionDM->insertNewReactionRow(mPosition, mRows, mIndex, mValue);
      GET_MODEL_OR_RETURN(pModel);
      mpReaction = pModel->getReactions()[mPosition];
      mpReactionData = new UndoReactionData(mpReaction);
    }
  else
    {
      mpReactionDM->addReactionRow(mpReactionData);
    }

  setUndoState(true);
  setAction("Add to list");
  setName(mpReactionData->getName());
}

void InsertReactionRowsCommand::undo()
{
  mpReactionDM->deleteReactionRow(mpReactionData);
  setUndoState(false);
  setAction("Remove from list");
}

