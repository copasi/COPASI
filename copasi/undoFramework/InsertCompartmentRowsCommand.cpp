// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * InsertCompartmentRowsCommand.cpp
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#include "CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "model/CCompartment.h"
#include "model/CModel.h"

#include <utilities/CCopasiException.h>

#include "CQCompartmentDM.h"

#include "UndoCompartmentData.h"

#include "InsertCompartmentRowsCommand.h"

InsertCompartmentRowsCommand::InsertCompartmentRowsCommand(
  int position,
  int rows,
  CQCompartmentDM *pCompartmentDM)
  : CCopasiUndoCommand("Compartment", COMPARTMENT_INSERT)
  , mpCompartmentDM(pCompartmentDM)
  , mRows(rows)
  , mPosition(position)
  , mIndex()
  , mpCompartmentData(NULL)
  , mValue()
{
  setText(QObject::tr(": Inserted new compartment"));
}

InsertCompartmentRowsCommand::InsertCompartmentRowsCommand(
  int position,
  int rows,
  CQCompartmentDM *pCompartmentDM,
  const QModelIndex &index,
  const QVariant &value)
  : CCopasiUndoCommand("Compartment", COMPARTMENT_INSERT)
  , mpCompartmentDM(pCompartmentDM)
  , mRows(rows)
  , mPosition(position)
  , mIndex(index)
  , mpCompartmentData(NULL)
  , mValue(value)
{
  setText(QObject::tr(": Inserted new compartment"));
}

void InsertCompartmentRowsCommand::redo()
{
  if (mpCompartmentData == NULL)
    {
      assert(mpCompartmentDM->getDataModel() != NULL);
      CModel * pModel = mpCompartmentDM->getDataModel()->getModel();
      assert(pModel != NULL);

      mpCompartmentDM->insertNewCompartmentRow(mPosition, mRows, mIndex, mValue);

      // the new compartment has to be the last compartment ... as create compartment
      // adds it at the end
      CCompartment *pCompartment = &pModel->getCompartments()[pModel->getCompartments().size() - 1];
      mpCompartmentData = new UndoCompartmentData(pCompartment);
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
