// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * DeleteGlobalQuantityCommand.cpp
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#include "copasi.h"

#include "copasi/core/CRootContainer.h"
#include "model/CModelValue.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "UI/CQModelValue.h"

#include "UndoGlobalQuantityData.h"

#include "DeleteGlobalQuantityCommand.h"

DeleteGlobalQuantityCommand::DeleteGlobalQuantityCommand(CQModelValue *pModelValue)
  : CCopasiUndoCommand("Global Quantity", GLOBALQUANTITY_DELETE)
  , mpGlobalQuantityData(new UndoGlobalQuantityData(pModelValue->mpModelValue))
  , mpModelValue(pModelValue)
{

  const std::string& sName = mpModelValue->mpModelValue->getObjectName();
  setText(QString(": Deleted global quantity %1").arg(sName.c_str()));
  setName(sName);
}

void DeleteGlobalQuantityCommand::redo()
{

  mpModelValue->deleteGlobalQuantity(mpGlobalQuantityData);
  setUndoState(true);
  setAction("Delete");
}

void DeleteGlobalQuantityCommand::undo()
{
  mpModelValue->addGlobalQuantity(mpGlobalQuantityData);
  setUndoState(false);
  setAction("Undelete");
}

DeleteGlobalQuantityCommand::~DeleteGlobalQuantityCommand()
{
  pdelete(mpGlobalQuantityData);
}
