// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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

CreateNewCompartmentCommand::CreateNewCompartmentCommand(CQCompartment *pCompartment)
{
  mpCompartment = pCompartment;
  mpCompartmentData = new UndoCompartmentData();
  this->setText(createNewCompartmentText());
  mType = COMPARTMENTCREATE;
  setEntityType("Compartment");
}
void CreateNewCompartmentCommand::redo()
{
  mpCompartment->createNewCompartment();

  std::string sName = mpCompartment->mpCompartment->getObjectName();
  mpCompartmentData->setName(sName);
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

QString CreateNewCompartmentCommand::createNewCompartmentText() const
{
  std::string myEntityName(": Create New Compartment ");
  char* entityName = (char*)myEntityName.c_str();
  return QObject::tr(entityName);
}

CreateNewCompartmentCommand::~CreateNewCompartmentCommand()
{
  // TODO Auto-generated destructor stub
}

UndoData *CreateNewCompartmentCommand::getUndoData() const
{
  return mpCompartmentData;
}

void CreateNewCompartmentCommand::setType(const CreateNewCompartmentCommand::Type & type)
{
  mType = COMPARTMENTCREATE;
}
