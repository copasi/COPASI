// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveAllGlobalQuantityRowsCommand.cpp
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#include "copasi.h"

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

RemoveAllGlobalQuantityRowsCommand::RemoveAllGlobalQuantityRowsCommand(
  CQGlobalQuantityDM * pGlobalQuantityDM, const QModelIndex&)
  : CCopasiUndoCommand("Global Quantity", GLOBALQUANTITY_REMOVE_ALL)
  , mpGlobalQuantityDM(pGlobalQuantityDM)
  , mpGlobalQuantityData()
{
  CCopasiDataModel * pDataModel = mpGlobalQuantityDM->getDataModel();
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);

  for (int i = 0; i != pGlobalQuantityDM->rowCount() - 1; ++i)
    {
      if (&pModel->getModelValues()[i])
        {
          UndoGlobalQuantityData *data =
            new UndoGlobalQuantityData(&pModel->getModelValues()[i]);
          mpGlobalQuantityData.append(data);
        }
    }

  setText(QObject::tr(": Removed All Global Quantities"));
}

void RemoveAllGlobalQuantityRowsCommand::redo()
{
  mpGlobalQuantityDM->removeAllGlobalQuantityRows();
  setUndoState(true);
  setAction("Delete all");
}

void RemoveAllGlobalQuantityRowsCommand::undo()
{
  mpGlobalQuantityDM->insertGlobalQuantityRows(mpGlobalQuantityData);
  setUndoState(false);
  setAction("Undelete all");
}

RemoveAllGlobalQuantityRowsCommand::~RemoveAllGlobalQuantityRowsCommand()
{
  // freeing the memory allocated above
  foreach(UndoGlobalQuantityData * data, mpGlobalQuantityData)
  {
    pdelete(data);
  }

  mpGlobalQuantityData.clear();
}
