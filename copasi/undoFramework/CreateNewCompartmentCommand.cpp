// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CreateNewCompartmentCommand.cpp
 *
 *  Created on: 16 Sep 2014
 *      Author: dada
 */

#include "model/CCompartment.h"
#include "UI/CQCompartment.h"
#include "UndoCompartmentData.h"

#include "CreateNewCompartmentCommand.h"

CreateNewCompartmentCommand::CreateNewCompartmentCommand(
  CQCompartment *pCompartment)
  : CCopasiUndoCommand("Compartment", COMPARTMENT_CREATE)
  , mpCompartmentData(new UndoCompartmentData())
  , mpCompartment(pCompartment)
{
  this->setText(": Created new compartment ");
}

void CreateNewCompartmentCommand::redo()
{
  mpCompartment->createNewCompartment();


  std::string sName = mpCompartment->mpCompartment->getObjectName();
  mpCompartmentData->setName(sName);
  mpCompartmentData->setKey(mpCompartment->mpCompartment->getKey());
  mpCompartmentData->setInitialValue(mpCompartment->mpCompartment->getInitialValue());
  mpCompartmentData->setStatus(mpCompartment->mpCompartment->getStatus());
  setUndoState(true);
  setName(sName);
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

UndoData *CreateNewCompartmentCommand::getUndoData() const
{
  return mpCompartmentData;
}

