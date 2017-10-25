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

#include "copasi/copasi.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CModel.h"
#include "copasi/UI/CQGlobalQuantityDM.h"
#include "copasi/function/CFunctionDB.h"

#include "copasi/model/CReaction.h"
#include "copasi/model/CReactionInterface.h"
#include "copasi/CopasiDataModel/CDataModel.h"

#include "UndoGlobalQuantityData.h"
#include "RemoveAllGlobalQuantityRowsCommand.h"

RemoveAllGlobalQuantityRowsCommand::RemoveAllGlobalQuantityRowsCommand(
  CQGlobalQuantityDM * pGlobalQuantityDM, const QModelIndex&)
  : CCopasiUndoCommand("Global Quantity", GLOBALQUANTITY_REMOVE_ALL)
  , mpGlobalQuantityDM(pGlobalQuantityDM)
  , mpGlobalQuantityData()
{
  CDataModel * pDataModel = mpGlobalQuantityDM->getDataModel();
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
  foreach (UndoGlobalQuantityData * data, mpGlobalQuantityData)
    {
      pdelete(data);
    }

  mpGlobalQuantityData.clear();
}
