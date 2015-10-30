// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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
  : CCopasiUndoCommand("Global Quantity", GLOBALQUANTITY_DELETE)
  , mFirstTime(true)
  , mpGlobalQuantityData(new UndoGlobalQuantityData(mpModelValue->mpModelValue))
  , mpModelValue(pModelValue)
{

  const std::string& sName = mpModelValue->mpModelValue->getObjectName();
  this->setText(deleteGlobalQuantityText(sName));
  setName(sName);
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

  setUndoState(true);
  setAction("Delete");
}

void DeleteGlobalQuantityCommand::undo()
{
  mpModelValue->addGlobalQuantity(mpGlobalQuantityData);
  setUndoState(false);
  setAction("Undelete");
}

QString DeleteGlobalQuantityCommand::deleteGlobalQuantityText(const std::string &name) const
{
//  std::string myEntityName(": Delete Global Quantity " + name);
//  char* entityName = (char*)myEntityName.c_str();
//  return QObject::tr(entityName);
  return QString(": Deleted global quantity %1").arg(name.c_str());
}

UndoData *DeleteGlobalQuantityCommand::getUndoData() const
{
  return mpGlobalQuantityData;
}

DeleteGlobalQuantityCommand::~DeleteGlobalQuantityCommand()
{
  pdelete(mpGlobalQuantityData);
}
