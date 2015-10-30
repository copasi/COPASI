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
  : CCopasiUndoCommand("Compartment", COMPARTMENT_DELETE)
  , mFirstTime(true)
  , mpCompartmentData(new UndoCompartmentData(mpCompartment->mpCompartment))
  , mpCompartment(pCompartment)
{
  setName(mpCompartmentData->getName());
  setText(QString(": Deleted compartment %1").arg(mpCompartmentData->getName().c_str()));
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

DeleteCompartmentCommand::~DeleteCompartmentCommand()
{
  pdelete(mpCompartmentData);
}
