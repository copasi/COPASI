// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CompartmentDataChangeCommand.cpp
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#include "copasi/copasi.h"
#include "copasi/UI/qtUtilities.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CModel.h"
#include "copasi/UI/CQCompartmentDM.h"

#include "CompartmentDataChangeCommand.h"
#include "UndoCompartmentData.h"

CompartmentDataChangeCommand::CompartmentDataChangeCommand(
  const QModelIndex& index,
  const QVariant& value,
  CQCompartmentDM *pCompartmentDM)
  : CCopasiUndoCommand("Compartment", COMPARTMENT_DATA_CHANGE, "Change")
  , mNew(value)
  , mOld(index.data(Qt::DisplayRole))
  , mIndex(index)
  , mpCompartmentDM(pCompartmentDM)
  , mpCompartmentUndoData(NULL)

{
  //set the data for UNDO history
  assert(pCompartmentDM->getDataModel() != NULL);
  CModel * pModel = pCompartmentDM->getDataModel()->getModel();
  assert(pModel != NULL);

  if (pModel->getCompartments().size() <= (size_t)index.row())
    {
      return;
    }

  CCompartment *pCompartment = &pModel->getCompartments()[index.row()];

  // need to store additional undo data to be able to restore
  // species initial concentrations / particle numbers
  mpCompartmentUndoData = new UndoCompartmentData(pCompartment, false);

  setKey(pCompartment->getKey());
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

  setText(QString(": Changed compartment %1").arg(getProperty().c_str()));
}

void CompartmentDataChangeCommand::redo()
{
  mpCompartmentDM->compartmentDataChange(mIndex, mNew, mpCompartmentUndoData);
  setAction("Change");
}

void CompartmentDataChangeCommand::undo()
{
  mpCompartmentDM->compartmentDataChange(mIndex, mOld, mpCompartmentUndoData);
  setAction("Undone change");
}

CompartmentDataChangeCommand::~CompartmentDataChangeCommand()
{
  pdelete(mpCompartmentUndoData);
}
