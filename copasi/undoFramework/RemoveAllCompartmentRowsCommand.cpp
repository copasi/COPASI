// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveAllCompartmentRowsCommand.cpp
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#include "copasi/UI/CQCompartmentDM.h"

#include "copasi/copasi.h"

#include "RemoveAllCompartmentRowsCommand.h"
#include "UndoCompartmentData.h"
#include "UndoReactionData.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"

RemoveAllCompartmentRowsCommand::RemoveAllCompartmentRowsCommand(CQCompartmentDM * pCompartmentDM, const QModelIndex&)
  : CCopasiUndoCommand("Compartment", COMPARTMENT_REMOVE_ALL)
  , mpCompartmentDM(pCompartmentDM)
  , mpCompartmentData()
{
  assert(pCompartmentDM->getDataModel() != NULL);
  CModel * pModel = pCompartmentDM->getDataModel()->getModel();
  assert(pModel != NULL);

  for (int i = 0; i != pCompartmentDM->rowCount() - 1; ++i)
    {
      CCompartment* compartment = &pModel->getCompartments()[i];

      if (compartment != NULL)
        {
          UndoCompartmentData *data = new UndoCompartmentData(compartment);
          mpCompartmentData.append(data);
        }
    }

  setText(QObject::tr(": Removed all compartments"));
}

void RemoveAllCompartmentRowsCommand::redo()
{
  mpCompartmentDM->removeAllCompartmentRows();
  setUndoState(true);
  setAction("Delete all");
}

void RemoveAllCompartmentRowsCommand::undo()
{
  mpCompartmentDM->insertCompartmentRows(mpCompartmentData);
  setUndoState(false);
  setAction("Undelete all");
}

RemoveAllCompartmentRowsCommand::~RemoveAllCompartmentRowsCommand()
{
  // freeing the memory allocated above
  foreach(UndoCompartmentData * data, mpCompartmentData)
  {
    pdelete(data);
  }

  mpCompartmentData.clear();
}
