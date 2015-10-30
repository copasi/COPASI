// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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

RemoveGlobalQuantityRowsCommand::RemoveGlobalQuantityRowsCommand(
  QModelIndexList rows, CQGlobalQuantityDM * pGlobalQuantityDM, const QModelIndex&)
  : CCopasiUndoCommand("Global Quantity", GLOBALQUANTITY_REMOVE)
  , mpGlobalQuantityDM(pGlobalQuantityDM)
  , mRows(rows)
  , mpGlobalQuantityData()
  , mFirstTime(true)
{

  GET_MODEL_OR_RETURN(pModel);

  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      CModelValue* pModelValue = pModel->getModelValues()[(*i).row()];

      if (pGlobalQuantityDM->isDefaultRow(*i) || pModelValue == NULL)
        continue;


      UndoGlobalQuantityData *data = new UndoGlobalQuantityData(pModelValue);

      mpGlobalQuantityData.append(data);

    }

  setText(QObject::tr(": Removed Global Quantity"));
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

RemoveGlobalQuantityRowsCommand::~RemoveGlobalQuantityRowsCommand()
{
  // freeing the memory allocated above
  foreach(UndoGlobalQuantityData * data, mpGlobalQuantityData)
  {
    pdelete(data);
  }
  mpGlobalQuantityData.clear();
}
