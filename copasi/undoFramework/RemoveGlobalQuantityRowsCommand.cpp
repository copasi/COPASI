// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveGlobalQuantityRowsCommand.cpp
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CModelValue.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "CQGlobalQuantityDM.h"
#include "function/CFunctionDB.h"

#include "UndoGlobalQuantityData.h"
#include "UndoReactionData.h"
#include "RemoveGlobalQuantityRowsCommand.h"

RemoveGlobalQuantityRowsCommand::RemoveGlobalQuantityRowsCommand(QModelIndexList rows, CQGlobalQuantityDM * pGlobalQuantityDM, const QModelIndex&)
{
  mpGlobalQuantityDM = pGlobalQuantityDM;
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
      UndoGlobalQuantityData *data = new UndoGlobalQuantityData();

      if (!pGlobalQuantityDM->isDefaultRow(*i) && pModel->getModelValues()[(*i).row()])
        {
          data->setName(pModel->getModelValues()[(*i).row()]->getObjectName());
          data->setStatus(pModel->getModelValues()[(*i).row()]->getStatus());

          if (pModel->getModelValues()[(*i).row()]->getStatus() != CModelEntity::ASSIGNMENT)
            {
              data->setInitialValue(pModel->getModelValues()[(*i).row()]->getInitialValue());
            }

          // set expression
          if (pModel->getModelValues()[(*i).row()]->getStatus() != CModelEntity::FIXED)
            {
              data->setExpression(pModel->getModelValues()[(*i).row()]->getExpression());
            }

          // set initial expression
          if (pModel->getModelValues()[(*i).row()]->getStatus() != CModelEntity::ASSIGNMENT)
            {
              data->setInitialExpression(pModel->getModelValues()[(*i).row()]->getInitialExpression());
            }

          setDependentObjects(pModel->getModelValues()[(*i).row()]->getDeletedObjects());
          data->setReactionDependencyObjects(getReactionData());
          data->setSpecieDependencyObjects(getSpecieData());
          data->setEventDependencyObjects(getEventData());

          mpGlobalQuantityData.append(data);
        }
    }

  mType = GLOBALQUANTITYREMOVE;
  setEntityType("Global Quantity");
  this->setText(removeGlobalQuantityRowsText());
}

void RemoveGlobalQuantityRowsCommand::redo()
{
  if (mFirstTime)
    {
      mpGlobalQuantityDM->removeGlobalQuantityRows(mRows, QModelIndex());
      mFirstTime = false;
    }
  else
    {
      mpGlobalQuantityDM->deleteGlobalQuantityRows(mpGlobalQuantityData);
    }

  setUndoState(true);
  setAction("Delete set");
}

void RemoveGlobalQuantityRowsCommand::undo()
{
  mpGlobalQuantityDM->insertGlobalQuantityRows(mpGlobalQuantityData);
  setUndoState(false);
  setAction("Undelete set");
}

QString RemoveGlobalQuantityRowsCommand::removeGlobalQuantityRowsText() const
{
  return QObject::tr(": Removed Global Quantity");
}

RemoveGlobalQuantityRowsCommand::~RemoveGlobalQuantityRowsCommand()
{
  // TODO Auto-generated destructor stub
}
