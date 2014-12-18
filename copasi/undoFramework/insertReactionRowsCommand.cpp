// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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
#include "insertReactionRowsCommand.h"

insertReactionRowsCommand::insertReactionRowsCommand(int position, int rows, CQReactionDM *pReactionDM, const QModelIndex&): CCopasiUndoCommand()
{
  mpReactionDM = pReactionDM;
  this->setText(insertRowsText());
  mRows = rows;
  mPosition = position;
  mType = REACTIONINSERT;
  setEntityType("Reaction");
}

insertReactionRowsCommand::~insertReactionRowsCommand()
{
  // TODO Auto-generated destructor stub
}

void insertReactionRowsCommand::redo()
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
  setUndoState(true);
  setAction("Add to list");
  setName(mpReactionData->getName());
}

void insertReactionRowsCommand::undo()
{
  mpReactionDM->deleteReactionRow(mpReaction);
  setUndoState(false);
  setAction("Remove from list");
}

QString insertReactionRowsCommand::insertRowsText() const
{
  return QObject::tr(": Inserted New Reaction");
}

UndoData *insertReactionRowsCommand::getUndoData() const
{
  return mpReactionData;
}
