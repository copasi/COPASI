// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
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

#include "UndoSpeciesData.h"
#include "UndoReactionData.h"
#include "UndoEventData.h"

#include "DeleteSpeciesCommand.h"

DeleteSpeciesCommand::DeleteSpeciesCommand(CQSpeciesDetail *pSpecieDetail)
  : CCopasiUndoCommand("Species", SPECIES_DELETE)
  , mFirstTime(true)
  , mpSpeciesData(new UndoSpeciesData())
  , mpSpecieDetail(pSpecieDetail)
{

  const std::string& sName = mpSpecieDetail->mpMetab->getObjectName();
  mpSpeciesData->setName(sName);

  mpSpeciesData->setStatus(mpSpecieDetail->mpMetab->getStatus());

  if (mpSpecieDetail->mpMetab->getStatus() != CModelEntity::ASSIGNMENT)
    {
      mpSpeciesData->setIConc(mpSpecieDetail->mpMetab->getInitialConcentration());
    }

  if (mpSpecieDetail->mpMetab->getStatus() ==  CModelEntity::ASSIGNMENT || mpSpecieDetail->mpMetab->getStatus() == CModelEntity::ODE)
    {
      mpSpeciesData->setExpression(mpSpecieDetail->mpMetab->getExpression());
    }

  // set initial expression
  if (mpSpecieDetail->mpMetab->getStatus() != CModelEntity::ASSIGNMENT)
    {
      mpSpeciesData->setInitialExpression(mpSpecieDetail->mpMetab->getInitialExpression());
    }

  //store to be deleted data
  setDependentObjects(mpSpecieDetail->mpMetab->getDeletedObjects());
  mpSpeciesData->setReactionDependencyObjects(getReactionData());
  mpSpeciesData->setGlobalQuantityDependencyObjects(getGlobalQuantityData());
  mpSpeciesData->setEventDependencyObjects(getEventData());

  setName(sName);
  this->setText(deleteSpecieText(sName));
}

void DeleteSpeciesCommand::redo()
{
  if (mFirstTime)
    {
      mpSpecieDetail->deleteSpecie();
      mFirstTime = false;
    }
  else
    {
      mpSpecieDetail->deleteSpecie(mpSpeciesData);
    }

  setUndoState(true);
  setAction("Delete");
}

void DeleteSpeciesCommand::undo()
{
  mpSpecieDetail->addSpecie(mpSpeciesData);
  setUndoState(false);
  setAction("Undelete");
}

QString DeleteSpeciesCommand::deleteSpecieText(const std::string &name) const
{
//  std::string myEntityName(": Delete Species " + name);
//  char* entityName = (char*)myEntityName.c_str();
//  return QObject::tr(entityName);
  return QString(": Deleted species %1").arg(name.c_str());
}

UndoData *DeleteSpeciesCommand::getUndoData() const
{
  return mpSpeciesData;
}

DeleteSpeciesCommand::~DeleteSpeciesCommand()
{
  pdelete(mpSpeciesData);
}
