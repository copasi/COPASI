// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveReactionRowsCommand.cpp
 *
 *  Created on: 11 Aug 2014
 *      Author: dada
 */

#include <QtCore/QList>

#include "report/CCopasiRootContainer.h"
#include "model/CReaction.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "CQReactionDM.h"

#include "RemoveReactionRowsCommand.h"
#include "UndoReactionData.h"

RemoveReactionRowsCommand::RemoveReactionRowsCommand(QModelIndexList rows, CQReactionDM * pReaDM, const QModelIndex&)
{
  mpReactionDM = pReaDM;
  mRows = rows;
  mFirstTime = true;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  assert(pModel != NULL);

  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      UndoReactionData *data = new UndoReactionData();
      CReactionInterface* ri = new CReactionInterface((*CCopasiRootContainer::getDatamodelList())[0]->getModel());

      if (!pReaDM->isDefaultRow(*i) && pModel->getReactions()[(*i).row()])
        {
          data->setName(pModel->getReactions()[(*i).row()]->getObjectName());
          ri->initFromReaction(pModel->getReactions()[(*i).row()]->getKey());
          data->setRi(ri);
          mpReaData.append(data);
        }
    }

  mType = REACTIONREMOVE;
  setEntityType("Reaction");

  this->setText(removeReactionRowsText());
}

void RemoveReactionRowsCommand::redo()
{
  if (mFirstTime)
    {
      mpReactionDM->removeReactionRows(mRows, QModelIndex());
      mFirstTime = false;
    }
  else
    {
      mpReactionDM->deleteReactionRows(mpReaData);
    }

  setUndoState(true);
  setAction("Delete set");
}

void RemoveReactionRowsCommand::undo()
{
  mpReactionDM->insertReactionRows(mpReaData);
  setUndoState(false);
  setAction("Undelete set");
}

QString RemoveReactionRowsCommand::removeReactionRowsText() const
{
  return QObject::tr(": Removed Reaction Rows");
}

RemoveReactionRowsCommand::~RemoveReactionRowsCommand()
{
  // TODO Auto-generated destructor stub
}
