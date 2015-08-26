// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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

CompartmentDataChangeCommand::CompartmentDataChangeCommand(
  const QModelIndex& index,
  const QVariant& value,
  int role,
  CQCompartmentDM *pCompartmentDM)
  : CCopasiUndoCommand("Compartment", COMPARTMENTDATACHANGE)
  , mNew(value)
  , mOld(index.data(Qt::DisplayRole))
  , mIndex(index)
  , mpCompartmentDM(pCompartmentDM)
  , mRole(role)
  , mPathIndex()

{

  //mPathIndex = pathFromIndex(index);

  //set the data for UNDO history
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel->getCompartments().size() <= (size_t)index.row())
    {
      return;
    }

  CCompartment *pCompartment = pModel->getCompartments()[index.row()];
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

  setText(compartmentDataChangeText());

}

void CompartmentDataChangeCommand::redo()
{
  mpCompartmentDM->compartmentDataChange(mIndex, mNew, mRole);
}

void CompartmentDataChangeCommand::undo()
{
  //mIndex = pathToIndex(mPathIndex, mpCompartmentDM);
  mpCompartmentDM->compartmentDataChange(mIndex, mOld, mRole);
  setAction("Undone change");
}

QString CompartmentDataChangeCommand::compartmentDataChangeText() const
{
  return QString(": Changed Compartment %1").arg(getProperty().c_str());
  //QObject::tr(": Changed Compartment Data");
}

CompartmentDataChangeCommand::~CompartmentDataChangeCommand()
{

}
