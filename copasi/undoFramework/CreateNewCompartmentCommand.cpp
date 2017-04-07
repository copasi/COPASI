// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CreateNewCompartmentCommand.cpp
 *
 *  Created on: 16 Sep 2014
 *      Author: dada
 */

#include "copasi.h"

#include "model/CCompartment.h"
#include "UI/CQCompartment.h"
#include "UndoCompartmentData.h"

#include "CreateNewCompartmentCommand.h"

CreateNewCompartmentCommand::CreateNewCompartmentCommand(
  CQCompartment *pCompartment)
  : CCopasiUndoCommand("Compartment", COMPARTMENT_CREATE)
  , mpCompartmentData(NULL)
  , mpCompartment(pCompartment)
{
  this->setText(": Created new compartment ");
}

void CreateNewCompartmentCommand::redo()
{
  if (mpCompartmentData == NULL)
    {
      mpCompartment->createNewCompartment();
      mpCompartmentData = new UndoCompartmentData(mpCompartment->mpCompartment);
    }
  else
    {
      mpCompartment->addCompartment(mpCompartmentData);
    }

  setUndoState(true);
  setAction("Create");
}

void CreateNewCompartmentCommand::undo()
{
  mpCompartment->deleteCompartment(mpCompartmentData);
  setUndoState(false);
  setAction("Delete");
}

CreateNewCompartmentCommand::~CreateNewCompartmentCommand()
{
  pdelete(mpCompartmentData);
}
