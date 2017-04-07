// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CreateNewGlobalQuantityCommand.cpp
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#include "copasi.h"
#include "model/CModelValue.h"
#include "UI/CQModelValue.h"
#include "UndoGlobalQuantityData.h"

#include "CreateNewGlobalQuantityCommand.h"

CreateNewGlobalQuantityCommand::CreateNewGlobalQuantityCommand(CQModelValue *pModelValue)
  : CCopasiUndoCommand("Global Quantity", GLOBALQUANTITY_CREATE)
  , mpGlobalQuantityData(NULL)
  , mpModelValue(pModelValue)
{
  this->setText(QObject::tr(": Created new global quantity "));
}

void CreateNewGlobalQuantityCommand::redo()
{
  if (mpGlobalQuantityData == NULL)
    {
      // TODO: this is again needs to happen only once
      mpModelValue->createNewGlobalQuantity();
      std::string sName = mpModelValue->mpModelValue->getObjectName();
      mpGlobalQuantityData = new UndoGlobalQuantityData(mpModelValue->mpModelValue);
      setName(sName);
    }
  else
    {
      mpModelValue->addGlobalQuantity(mpGlobalQuantityData);
    }

  setUndoState(true);
  setAction("Create");
}

void CreateNewGlobalQuantityCommand::undo()
{
  mpModelValue->deleteGlobalQuantity(mpGlobalQuantityData);
  setUndoState(false);
  setAction("Delete");
}

CreateNewGlobalQuantityCommand::~CreateNewGlobalQuantityCommand()
{
  pdelete(mpGlobalQuantityData);
}
