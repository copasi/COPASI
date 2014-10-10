// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * InsertGlobalQuantityRowsCommand.cpp
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModelValue.h"
#include "model/CModel.h"
#include "CQGlobalQuantityDM.h"

#include "InsertGlobalQuantityRowsCommand.h"
#include "UndoGlobalQuantityData.h"

#include "InsertGlobalQuantityRowsCommand.h"

InsertGlobalQuantityRowsCommand::InsertGlobalQuantityRowsCommand(int position, int rows, CQGlobalQuantityDM *pGlobalQuantityDM, const QModelIndex&): CCopasiUndoCommand()
{
  mpGlobalQuantityDM = pGlobalQuantityDM;
  mpGlobalQuantityData = new UndoGlobalQuantityData();
  this->setText(insertRowsText());
  mRows = rows;
  mPosition = position;
  firstTime = true;
}

void InsertGlobalQuantityRowsCommand::redo()
{
  if (firstTime)
    {
      mpGlobalQuantityDM->insertNewGlobalQuantityRow(mPosition, mRows, QModelIndex());
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
      assert(pDataModel != NULL);
      CModel * pModel = pDataModel->getModel();
      assert(pModel != NULL);

      CModelValue *pGlobalQuantity = pModel->getModelValues()[mPosition];
      mpGlobalQuantityData->setName(pGlobalQuantity->getObjectName());
      mpGlobalQuantityData->setInitialValue(pGlobalQuantity->getInitialValue());
      mpGlobalQuantityData->setStatus(pGlobalQuantity->getStatus());
      firstTime = false;
    }
  else
    {
      mpGlobalQuantityDM->addGlobalQuantityRow(mpGlobalQuantityData);
    }
}

void InsertGlobalQuantityRowsCommand::undo()
{
  mpGlobalQuantityDM->deleteGlobalQuantityRow(mpGlobalQuantityData);
}

QString InsertGlobalQuantityRowsCommand::insertRowsText() const
{
  return QObject::tr(": Inserted New Global Quantity");
}

InsertGlobalQuantityRowsCommand::~InsertGlobalQuantityRowsCommand()
{
  // TODO Auto-generated destructor stub
}
