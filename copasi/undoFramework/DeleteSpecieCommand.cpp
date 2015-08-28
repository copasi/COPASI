// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * DeleteSpecieCommand.cpp
 *
 *  Created on: 2 Sep 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CMetab.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "CQSpecieDM.h"
#include "function/CFunctionDB.h"
#include "UI/CQSpeciesDetail.h"

#include "UndoSpecieData.h"
#include "UndoReactionData.h"
#include "UndoEventData.h"

#include "DeleteSpecieCommand.h"

DeleteSpecieCommand::DeleteSpecieCommand(CQSpeciesDetail *pSpecieDetail)
  : CCopasiUndoCommand("Species", SPECIEDELETE)
  , mFirstTime(true)
  , mpSpecieData(new UndoSpecieData())
  , mpSpecieDetail(pSpecieDetail)
{

  const std::string& sName = mpSpecieDetail->mpMetab->getObjectName();
  mpSpecieData->setName(sName);

  mpSpecieData->setStatus(mpSpecieDetail->mpMetab->getStatus());

  if (mpSpecieDetail->mpMetab->getStatus() != CModelEntity::ASSIGNMENT)
    {
      mpSpecieData->setIConc(mpSpecieDetail->mpMetab->getInitialConcentration());
    }

  if (mpSpecieDetail->mpMetab->getStatus() ==  CModelEntity::ASSIGNMENT || mpSpecieDetail->mpMetab->getStatus() == CModelEntity::ODE)
    {
      mpSpecieData->setExpression(mpSpecieDetail->mpMetab->getExpression());
    }

  // set initial expression
  if (mpSpecieDetail->mpMetab->getStatus() != CModelEntity::ASSIGNMENT)
    {
      mpSpecieData->setInitialExpression(mpSpecieDetail->mpMetab->getInitialExpression());
    }

  //store to be deleted data
  setDependentObjects(mpSpecieDetail->mpMetab->getDeletedObjects());
  mpSpecieData->setReactionDependencyObjects(getReactionData());
  mpSpecieData->setGlobalQuantityDependencyObjects(getGlobalQuantityData());
  mpSpecieData->setEventDependencyObjects(getEventData());

  setName(sName);
  this->setText(deleteSpecieText(sName));
}

void DeleteSpecieCommand::redo()
{
  if (mFirstTime)
    {
      mpSpecieDetail->deleteSpecie();
      mFirstTime = false;
    }
  else
    {
      mpSpecieDetail->deleteSpecie(mpSpecieData);
    }

  setUndoState(true);
  setAction("Delete");
}

void DeleteSpecieCommand::undo()
{
  mpSpecieDetail->addSpecie(mpSpecieData);
  setUndoState(false);
  setAction("Undelete");
}

QString DeleteSpecieCommand::deleteSpecieText(const std::string &name) const
{
//  std::string myEntityName(": Delete Species " + name);
//  char* entityName = (char*)myEntityName.c_str();
//  return QObject::tr(entityName);
  return QString(": Deleted species %1").arg(name.c_str());
}

UndoData *DeleteSpecieCommand::getUndoData() const
{
  return mpSpecieData;
}

DeleteSpecieCommand::~DeleteSpecieCommand()
{
  pdelete(mpSpecieData);
}
