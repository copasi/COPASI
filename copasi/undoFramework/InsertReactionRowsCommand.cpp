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

InsertReactionRowsCommand::InsertReactionRowsCommand(int position, int rows, CQReactionDM *pReactionDM, const QModelIndex&)
  : CCopasiUndoCommand("Reaction", REACTION_INSERT)
  , mpReactionDM(pReactionDM)
  , mRows(rows)
  , mPosition(position)
  , mpReaction(NULL)
  , mpRi(NULL)
  , mpReactionData(new UndoReactionData())

{
  this->setText(insertRowsText());
}

InsertReactionRowsCommand::~InsertReactionRowsCommand()
{
  pdelete(mpReactionData)
}

void InsertReactionRowsCommand::redo()
{
  mpReactionDM->insertNewReactionRow(mPosition, mRows, QModelIndex());
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);
  mpReaction = pModel->getReactions()[mPosition];
  std::string sName = mpReaction->getObjectName();

  mpReactionData->setName(sName);

  CReactionInterface* ri = new CReactionInterface((*CCopasiRootContainer::getDatamodelList())[0]->getModel());
  ri->initFromReaction(mpReaction);

  mpReactionData->setRi(ri);
  mpReactionData->setKey(mpReaction->getKey());

  setUndoState(true);
  setAction("Add to list");

  setName(sName);
}

void InsertReactionRowsCommand::undo()
{
  mpReactionDM->deleteReactionRow(mpReaction);
  setUndoState(false);
  setAction("Remove from list");
}

QString InsertReactionRowsCommand::insertRowsText() const
{
  return QObject::tr(": Inserted new reaction");
}

UndoData *InsertReactionRowsCommand::getUndoData() const
{
  return mpReactionData;
}
