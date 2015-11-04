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

void
InsertReactionRowsCommand::redo()
{
  if (mpReactionData == NULL)
    {
      mpReactionDM->insertNewReactionRow(this);
    }
  else
    {
      mpReactionDM->addReactionRow(mpReactionData);
    }

  setUndoState(true);
  setAction("Add to list");
  setName(mpReactionData->getName());
}

void
InsertReactionRowsCommand::undo()
{
  mpReactionDM->deleteReactionRow(mpReactionData);
  setUndoState(false);
  setAction("Remove from list");
}

const QVariant&
InsertReactionRowsCommand::value() const
{
  return mValue;
}

void
InsertReactionRowsCommand::setValue(const QVariant &value)
{
  mValue = value;
}

const QModelIndex&
InsertReactionRowsCommand::index() const
{
  return mIndex;
}

void
InsertReactionRowsCommand::setIndex(const QModelIndex &index)
{
  mIndex = index;
}

int
InsertReactionRowsCommand::position() const
{
  return mPosition;
}

void
InsertReactionRowsCommand::setPosition(int position)
{
  mPosition = position;
}

int
InsertReactionRowsCommand::rows() const
{
  return mRows;
}

void
InsertReactionRowsCommand::setRows(int rows)
{
  mRows = rows;
}

void InsertReactionRowsCommand::initializeUndoData(CReaction * reaction, const std::vector<std::string>& createdKeys)
{
  pdelete(mpReactionData);
  mpReactionData = new UndoReactionData(reaction);
  mpReactionData->setAdditionalKeys(createdKeys);

}

