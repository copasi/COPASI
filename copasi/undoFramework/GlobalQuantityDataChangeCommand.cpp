// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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

GlobalQuantityDataChangeCommand::GlobalQuantityDataChangeCommand(QModelIndex index, const QVariant value, int role, CQGlobalQuantityDM *pGlobalQuantityDM)
{
  // stores the data
  mOld = index.data(Qt::DisplayRole);
  mNew = value;
  mpGlobalQuantityDM = pGlobalQuantityDM;
  mIndex = index;
  mRole = role;

  //mPathIndex = pathFromIndex(index);
  this->setText(globalQuantityDataChangeText());

  //set the data for UNDO history
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();
  CModelValue *pModelValue = pModel->getModelValues()[index.row()];
  mType = GLOBALQUANTITYDATACHANGE;
  setEntityType("Global Quantity");
  setAction("Change");
  setName(pModelValue->getObjectName());
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
}

void GlobalQuantityDataChangeCommand::redo()
{
  mpGlobalQuantityDM->globalQuantityDataChange(mIndex, mNew, mRole);
}
void GlobalQuantityDataChangeCommand::undo()
{
  //mIndex = pathToIndex(mPathIndex, mpGlobalQuantityDM);
  mpGlobalQuantityDM->globalQuantityDataChange(mIndex, mOld, mRole);
  setAction("Unchange");
}
QString GlobalQuantityDataChangeCommand::globalQuantityDataChangeText() const
{
  return QObject::tr(": Changed Global Quantity Data");
}

GlobalQuantityDataChangeCommand::~GlobalQuantityDataChangeCommand()
{
  // TODO Auto-generated destructor stub
}
