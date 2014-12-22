// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CompartmentDataChangeCommand.cpp
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CCompartment.h"
#include "model/CModel.h"
#include "CQCompartmentDM.h"
#include "qtUtilities.h"

#include "CompartmentDataChangeCommand.h"

CompartmentDataChangeCommand::CompartmentDataChangeCommand(QModelIndex index, const QVariant value, int role, CQCompartmentDM *pCompartmentDM)
{
  // stores the data
  mOld = index.data(Qt::DisplayRole);
  mNew = value;
  mpCompartmentDM = pCompartmentDM;
  mIndex = index;
  mRole = role;

  //mPathIndex = pathFromIndex(index);
  this->setText(compartmentDataChangeText());

  //set the data for UNDO history
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();
  CCompartment *pCompartment = pModel->getCompartments()[index.row()];
  mType = COMPARTMENTDATACHANGE;
  setEntityType("Compartment");
  setAction("Change");
  setName(pCompartment->getObjectName());
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
        setProperty("Initial Volume");
        break;
    }
}

void CompartmentDataChangeCommand::redo()
{
  mpCompartmentDM->compartmentDataChange(mIndex, mNew, mRole);
}
void CompartmentDataChangeCommand::undo()
{
  //mIndex = pathToIndex(mPathIndex, mpCompartmentDM);
  mpCompartmentDM->compartmentDataChange(mIndex, mOld, mRole);
  setAction("Unchange");
}
QString CompartmentDataChangeCommand::compartmentDataChangeText() const
{
  return QObject::tr(": Changed Compartment Data");
}

CompartmentDataChangeCommand::~CompartmentDataChangeCommand()
{
  // TODO Auto-generated destructor stub
}
