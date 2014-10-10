// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveAllGlobalQuantityRowsCommand.cpp
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CModelValue.h"
#include "model/CModel.h"
#include "UI/CQGlobalQuantityDM.h"
#include "function/CFunctionDB.h"

#include "model/CReaction.h"
#include "model/CReactionInterface.h"

#include "UndoGlobalQuantityData.h"
#include "UndoReactionData.h"
#include "RemoveAllGlobalQuantityRowsCommand.h"

RemoveAllGlobalQuantityRowsCommand::RemoveAllGlobalQuantityRowsCommand(CQGlobalQuantityDM * pGlobalQuantityDM, const QModelIndex&)
{
  mpGlobalQuantityDM = pGlobalQuantityDM;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  assert(pModel != NULL);

  for (int i = 0; i != pGlobalQuantityDM->rowCount() - 1; ++i)
    {

      UndoGlobalQuantityData *data = new UndoGlobalQuantityData();

      if (pModel->getModelValues()[i])
        {
          data->setName(pModel->getModelValues()[i]->getObjectName());
          data->setInitialValue(pModel->getModelValues()[i]->getInitialValue());
          data->setStatus(pModel->getModelValues()[i]->getStatus());
          setDependentObjects(pModel->getModelValues()[i]->getDeletedObjects());
          data->setReactionDependencyObjects(getReactionData());
          mpGlobalQuantityData.append(data);
        }
    }

  this->setText(removeAllGlobalQuantityRowsText());
}

void RemoveAllGlobalQuantityRowsCommand::redo()
{
  mpGlobalQuantityDM->removeAllGlobalQuantityRows();
}

void RemoveAllGlobalQuantityRowsCommand::undo()
{
  mpGlobalQuantityDM->insertGlobalQuantityRows(mpGlobalQuantityData);
}

QString RemoveAllGlobalQuantityRowsCommand::removeAllGlobalQuantityRowsText() const
{
  return QObject::tr(": Removed All Global Quantities");
}

RemoveAllGlobalQuantityRowsCommand::~RemoveAllGlobalQuantityRowsCommand()
{
  // TODO Auto-generated destructor stub
}
