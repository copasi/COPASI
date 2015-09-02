// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CreateNewGlobalQuantityCommand.cpp
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#include "model/CModelValue.h"
#include "UI/CQModelValue.h"
#include "UndoGlobalQuantityData.h"

#include "CreateNewGlobalQuantityCommand.h"

CreateNewGlobalQuantityCommand::CreateNewGlobalQuantityCommand(CQModelValue *pModelValue)
  : CCopasiUndoCommand("Global Quantity", GLOBALQUANTITYCREATE)
  , mpGlobalQuantityData(new UndoGlobalQuantityData())
  , mpModelValue(pModelValue)
{
  this->setText(createNewGlobalQuantityText());
}
void CreateNewGlobalQuantityCommand::redo()
{
  mpModelValue->createNewGlobalQuantity();

  std::string sName = mpModelValue->mpModelValue->getObjectName();
  mpGlobalQuantityData->setName(sName);
  mpGlobalQuantityData->setStatus(mpModelValue->mpModelValue->getStatus());

  if (mpModelValue->mpModelValue->getStatus() != CModelEntity::ASSIGNMENT)
    {
      mpGlobalQuantityData->setInitialValue(mpModelValue->mpModelValue->getInitialValue());
    }

  // set expression
  if (mpModelValue->mpModelValue->getStatus() != CModelEntity::FIXED)
    {

      mpGlobalQuantityData->setExpression(mpModelValue->mpModelValue->getExpression());
    }

  // set initial expression
  if (mpModelValue->mpModelValue->getStatus() != CModelEntity::ASSIGNMENT)
    {
      mpGlobalQuantityData->setInitialExpression(mpModelValue->mpModelValue->getInitialExpression());
    }

  setUndoState(true);
  setAction("Create");
  setName(sName);
}

void CreateNewGlobalQuantityCommand::undo()
{
  mpModelValue->deleteGlobalQuantity(mpGlobalQuantityData);
  setUndoState(false);
  setAction("Delete");
}

QString CreateNewGlobalQuantityCommand::createNewGlobalQuantityText() const
{
  return QObject::tr(": Created new global quantity ");
}

UndoData *CreateNewGlobalQuantityCommand::getUndoData() const
{
  return mpGlobalQuantityData;
}

CreateNewGlobalQuantityCommand::~CreateNewGlobalQuantityCommand()
{
  pdelete(mpGlobalQuantityData);
}
