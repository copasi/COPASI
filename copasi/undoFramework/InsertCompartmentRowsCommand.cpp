// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * InsertCompartmentRowsCommand.cpp
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CCompartment.h"
#include "model/CModel.h"

#include <utilities/CCopasiException.h>

#include "CQCompartmentDM.h"

#include "UndoCompartmentData.h"

#include "InsertCompartmentRowsCommand.h"

InsertCompartmentRowsCommand::InsertCompartmentRowsCommand(
  int position,
  int rows,
  CQCompartmentDM *pCompartmentDM,
  const QModelIndex&)
  : CCopasiUndoCommand("Compartment", COMPARTMENT_INSERT)
  , mpCompartmentDM(pCompartmentDM)
  , mRows(rows)
  , mPosition(position)
  , mIndex()
  , mpCompartmentData(new UndoCompartmentData())
  , firstTime(true)
{
  setText(QObject::tr(": Inserted new compartment"));
}

void InsertCompartmentRowsCommand::redo()
{
  if (firstTime)
    {
      mpCompartmentDM->insertNewCompartmentRow(mPosition, mRows, QModelIndex());
      GET_MODEL_OR_RETURN(pModel);

      CCompartment *pCompartment = pModel->getCompartments()[mPosition];
      mpCompartmentData->setName(pCompartment->getObjectName());
      mpCompartmentData->setKey(pCompartment->getKey());
      mpCompartmentData->setStatus(pCompartment->getStatus());
      mpCompartmentData->setInitialValue(pCompartment->getInitialValue());
      firstTime = false;
    }
  else
    {
      mpCompartmentDM->addCompartmentRow(mpCompartmentData);
    }

  setUndoState(true);
  setAction("Add to list");
  setName(mpCompartmentData->getName());
}

void InsertCompartmentRowsCommand::undo()
{
  try
    {
      mpCompartmentDM->deleteCompartmentRow(mpCompartmentData);
      setUndoState(false);
      setAction("Remove from list");
    }
  catch (CCopasiException&)
    {
      // handle the case that the compartment does not
      // exist that is to be removed
    }
}

InsertCompartmentRowsCommand::~InsertCompartmentRowsCommand()
{
  pdelete(mpCompartmentData);
}
