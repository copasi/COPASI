// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveAllReactionRowsCommand.cpp
 *
 *  Created on: 12 Aug 2014
 *      Author: dada
 */

#include <QtCore/QList>

#include "report/CCopasiRootContainer.h"
#include "model/CReaction.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "CQReactionDM.h"

#include "RemoveAllReactionRowsCommand.h"
#include "UndoReactionData.h"

RemoveAllReactionRowsCommand::RemoveAllReactionRowsCommand(
  CQReactionDM * pReaDM, const QModelIndex&)
  : CCopasiUndoCommand("Reaction", REACTION_REMOVE_ALL)
  , mpReactionDM(pReaDM)
  , mpReaData()
{

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  assert(pModel != NULL);

  for (int i = 0; i != pReaDM->rowCount() - 1; ++i)
    {
      UndoReactionData *data = new UndoReactionData();
      CReactionInterface* ri = new CReactionInterface((*CCopasiRootContainer::getDatamodelList())[0]->getModel());

      if (pModel->getReactions()[i])
        {
          data->setName(pModel->getReactions()[i]->getObjectName());
          ri->initFromReaction(pModel->getReactions()[i]->getKey());
          data->setRi(ri);
          mpReaData.append(data);
        }
    }

  setText(removeAllReactionRowsText());
}

void RemoveAllReactionRowsCommand::redo()
{
  mpReactionDM->removeAllReactionRows();
  setUndoState(true);
  setAction("Delete all");
}

void RemoveAllReactionRowsCommand::undo()
{
  mpReactionDM->insertReactionRows(mpReaData);
  setUndoState(false);
  setAction("Undelete all");
}

QString RemoveAllReactionRowsCommand::removeAllReactionRowsText() const
{
  return QObject::tr(": Removed All Reaction Rows");
}

RemoveAllReactionRowsCommand::~RemoveAllReactionRowsCommand()
{
  // freeing the memory allocated above
  foreach(UndoReactionData * data, mpReaData)
  {
    pdelete(data);
  }
  mpReaData.clear();

}
