// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * DeleteGlobalQuantityCommand.cpp
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CModelValue.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "UI/CQModelValue.h"

#include "UndoGlobalQuantityData.h"
#include "UndoReactionData.h"

#include "DeleteGlobalQuantityCommand.h"

DeleteGlobalQuantityCommand::DeleteGlobalQuantityCommand(CQModelValue *pModelValue)
{
  mpModelValue = pModelValue;
  mFirstTime = true;
  mpGlobalQuantityData = new UndoGlobalQuantityData();
  std::string sName = mpModelValue->mpModelValue->getObjectName();
  mpGlobalQuantityData->setName(sName);
  mpGlobalQuantityData->setInitialValue(mpModelValue->mpModelValue->getInitialValue());
  mpGlobalQuantityData->setStatus(mpModelValue->mpModelValue->getStatus());

  //store to be deleted data
  setDependentObjects(mpModelValue->mpModelValue->getDeletedObjects());
  mpGlobalQuantityData->setReactionDependencyObjects(getReactionData());

  this->setText(deleteGlobalQuantityText(sName));
}

void DeleteGlobalQuantityCommand::redo()
{
  if (mFirstTime)
    {
      mpModelValue->deleteGlobalQuantity();
      mFirstTime = false;
    }
  else
    {
      mpModelValue->deleteGlobalQuantity(mpGlobalQuantityData);
    }
}

void DeleteGlobalQuantityCommand::undo()
{
  mpModelValue->addGlobalQuantity(mpGlobalQuantityData);
}

QString DeleteGlobalQuantityCommand::deleteGlobalQuantityText(std::string &name) const
{
  std::string myEntityName(": Delete Global Quantity " + name);
  char* entityName = (char*)myEntityName.c_str();
  return QObject::tr(entityName);
}

DeleteGlobalQuantityCommand::~DeleteGlobalQuantityCommand()
{
  // TODO Auto-generated destructor stub
}
