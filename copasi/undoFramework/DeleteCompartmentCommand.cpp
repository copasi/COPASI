// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * DeleteCompartmentCommand.cpp
 *
 *  Created on: 16 Sep 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CCompartment.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "UI/CQCompartment.h"

#include "UndoCompartmentData.h"
#include "UndoReactionData.h"

#include "DeleteCompartmentCommand.h"

DeleteCompartmentCommand::DeleteCompartmentCommand(CQCompartment *pCompartment)
  : CCopasiUndoCommand("Compartment", COMPARTMENTDELETE)
  , mFirstTime(true)
  , mpCompartmentData(new UndoCompartmentData())
  , mpCompartment(pCompartment)
{

  const std::string& sName = mpCompartment->mpCompartment->getObjectName();
  mpCompartmentData->setName(sName);
  mpCompartmentData->setInitialValue(mpCompartment->mpCompartment->getInitialValue());
  mpCompartmentData->setStatus(mpCompartment->mpCompartment->getStatus());

  //store to be deleted data
  setDependentObjects(mpCompartment->mpCompartment->getDeletedObjects());
  mpCompartmentData->setSpecieDependencyObjects(getSpecieData());
  mpCompartmentData->setReactionDependencyObjects(getReactionData());
  mpCompartmentData->setEventDependencyObjects(getEventData());

  this->setText(deleteCompartmentText(sName));
  setName(sName);
}

void DeleteCompartmentCommand::redo()
{
  if (mFirstTime)
    {
      mpCompartment->deleteCompartment();
      mFirstTime = false;
    }
  else
    {
      mpCompartment->deleteCompartment(mpCompartmentData);
    }

  setUndoState(true);
  setAction("Delete");
}

void DeleteCompartmentCommand::undo()
{
  mpCompartment->addCompartment(mpCompartmentData);
  setUndoState(false);
  setAction("Undelete");
}

QString DeleteCompartmentCommand::deleteCompartmentText(const std::string &name) const
{
//  std::string myEntityName(": Delete Compartment " + name);
//  char* entityName = (char*)myEntityName.c_str();
//  return QObject::tr(entityName);
  return QString(": Deleted compartment %1").arg(name.c_str());
}

UndoData *DeleteCompartmentCommand::getUndoData() const
{
  return mpCompartmentData;
}

DeleteCompartmentCommand::~DeleteCompartmentCommand()
{
  pdelete(mpCompartmentData);
}
