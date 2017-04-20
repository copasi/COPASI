// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveGlobalQuantityRowsCommand.cpp
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#include "copasi/copasi.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CReactionInterface.h"
#include "copasi/model/CModel.h"
#include "copasi/UI/CQGlobalQuantityDM.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/CopasiDataModel/CDataModel.h"

#include "UndoGlobalQuantityData.h"
#include "UndoReactionData.h"
#include "RemoveGlobalQuantityRowsCommand.h"

RemoveGlobalQuantityRowsCommand::RemoveGlobalQuantityRowsCommand(
  QModelIndexList rows, CQGlobalQuantityDM * pGlobalQuantityDM)
  : CCopasiUndoCommand("Global Quantity", GLOBALQUANTITY_REMOVE)
  , mpGlobalQuantityDM(pGlobalQuantityDM)
  , mpGlobalQuantityData()
{

  CDataModel * pDataModel = pGlobalQuantityDM->getDataModel();
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);

  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      CModelValue* pModelValue = &pModel->getModelValues()[i->row()];

      if (pGlobalQuantityDM->isDefaultRow(*i) || pModelValue == NULL)
        continue;

      UndoGlobalQuantityData *data = new UndoGlobalQuantityData(pModelValue);
      mpGlobalQuantityData.append(data);
    }

  setText(QObject::tr(": Removed Global Quantity"));
}

void RemoveGlobalQuantityRowsCommand::redo()
{
  mpGlobalQuantityDM->deleteGlobalQuantityRows(mpGlobalQuantityData);
  setUndoState(true);
  setAction("Delete set");
}

void RemoveGlobalQuantityRowsCommand::undo()
{
  mpGlobalQuantityDM->insertGlobalQuantityRows(mpGlobalQuantityData);
  setUndoState(false);
  setAction("Undelete set");
}

RemoveGlobalQuantityRowsCommand::~RemoveGlobalQuantityRowsCommand()
{
  // freeing the memory allocated above
  foreach(UndoGlobalQuantityData * data, mpGlobalQuantityData)
  {
    pdelete(data);
  }

  mpGlobalQuantityData.clear();
}
