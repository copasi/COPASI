// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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
{
  mpModelValue = pModelValue;
  mpGlobalQuantityData = new UndoGlobalQuantityData();
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
}

void CreateNewGlobalQuantityCommand::undo()
{
  mpModelValue->deleteGlobalQuantity(mpGlobalQuantityData);
}

QString CreateNewGlobalQuantityCommand::createNewGlobalQuantityText() const
{
  std::string myEntityName(": Create New Global Quantity ");
  char* entityName = (char*)myEntityName.c_str();
  return QObject::tr(entityName);
}

CreateNewGlobalQuantityCommand::~CreateNewGlobalQuantityCommand()
{
  // TODO Auto-generated destructor stub
}
