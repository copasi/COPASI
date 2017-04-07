// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * GlobalQuantityDataChangeCommand.cpp
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */
#include "copasi.h"

#include "UI/qtUtilities.h"

#include "report/CCopasiRootContainer.h"
#include "model/CModelValue.h"
#include "model/CModel.h"

#include "CQGlobalQuantityDM.h"

#include "GlobalQuantityDataChangeCommand.h"

GlobalQuantityDataChangeCommand::GlobalQuantityDataChangeCommand(
  const QModelIndex& index,
  const QVariant& value,
  int role,
  CQGlobalQuantityDM *pGlobalQuantityDM)
  : CCopasiUndoCommand("Global Quantity", GLOBALQUANTITY_DATA_CHANGE, "Change")
  , mNew(value)
  , mOld(index.data(Qt::DisplayRole))
  , mIndex(index)
  , mpGlobalQuantityDM(pGlobalQuantityDM)
  , mRole(role)
  , mPathIndex()
{
  // stores the data

  if (index.column() == COL_TYPE_GQ)
    mOld = pGlobalQuantityDM->statusToIndex(mOld.toString());

  //mPathIndex = pathFromIndex(index);

  //set the data for UNDO history
  setOldValue(TO_UTF8(mOld.toString()));
  setNewValue(TO_UTF8(mNew.toString()));

  switch (index.column())
    {
      case 0:
        setProperty("");
        break;

      case 1:
        setProperty("Name");
        break;

      case 2:
        setProperty("Type");

        switch (mNew.toInt())
          {
            case 0:
              setNewValue("fixed");
              break;

            case 1:
              setNewValue("assignment");
              break;

            case 2:
              setNewValue("ode");
              break;
          }

        break;

      case 3:
        setProperty("Initial Value");
        break;
    }

  setText(QString(": Changed global quantity %1").arg(getProperty().c_str()));
}

void GlobalQuantityDataChangeCommand::redo()
{
  mpGlobalQuantityDM->globalQuantityDataChange(mIndex, mNew, mRole);

  assert(mpGlobalQuantityDM->getDataModel() != NULL);
  CModel * pModel = mpGlobalQuantityDM->getDataModel()->getModel();
  assert(pModel != NULL);

  CModelValue *pModelValue = pModelValue = &pModel->getModelValues()[mIndex.row()];
  setName(pModelValue->getObjectName());
  setAction("Change");
}

void GlobalQuantityDataChangeCommand::undo()
{
  mpGlobalQuantityDM->globalQuantityDataChange(mIndex, mOld, mRole);
  setAction("Undone change");
}

GlobalQuantityDataChangeCommand::~GlobalQuantityDataChangeCommand()
{
}
