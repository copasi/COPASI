// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * GlobalQuantityDataChangeCommand.cpp
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */
#include "report/CCopasiRootContainer.h"
#include "model/CModelValue.h"
#include "model/CModel.h"
#include "qtUtilities.h"

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

  if (mRole == COL_TYPE_GQ)
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

  this->setText(globalQuantityDataChangeText());
}

void GlobalQuantityDataChangeCommand::redo()
{
  mpGlobalQuantityDM->globalQuantityDataChange(mIndex, mNew, mRole);
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();
  CModelValue *pModelValue = pModelValue = pModel->getModelValues()[mIndex.row()];
  setName(pModelValue->getObjectName());
}
void GlobalQuantityDataChangeCommand::undo()
{
  //mIndex = pathToIndex(mPathIndex, mpGlobalQuantityDM);
  mpGlobalQuantityDM->globalQuantityDataChange(mIndex, mOld, mRole);
  setAction("Undone change");
}
QString GlobalQuantityDataChangeCommand::globalQuantityDataChangeText() const
{
  return QString(": Changed global quantity %1").arg(getProperty().c_str());
  //QObject::tr(": Changed Global Quantity Data");
}

GlobalQuantityDataChangeCommand::~GlobalQuantityDataChangeCommand()
{
}
