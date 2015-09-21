// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CreateNewSpecieCommand.cpp
 *
 *  Created on: 2 Sep 2014
 *      Author: dada
 */

#include "model/CModel.h"
#include "model/CMetab.h"
#include "UI/CQSpeciesDetail.h"
#include "UndoSpeciesData.h"

#include "CreateNewSpeciesCommand.h"

CreateNewSpeciesCommand::CreateNewSpeciesCommand(CQSpeciesDetail *pSpecieDetail)
  : CCopasiUndoCommand("Species", SPECIES_CREATE)
  , mpSpeciesData(new UndoSpeciesData())
  , mpSpecieDetail(pSpecieDetail)
{
  this->setText(createNewSpecieText());
}

void CreateNewSpeciesCommand::redo()
{
  mpSpecieDetail->createNewSpecie();

  std::string sName = mpSpecieDetail->mpMetab->getObjectName();
  mpSpeciesData->setName(sName);
  mpSpeciesData->setIConc(mpSpecieDetail->mpMetab->getInitialConcentration());
  mpSpeciesData->setCompartment(mpSpecieDetail->mpMetab->getCompartment()->getObjectName());
  mpSpeciesData->setStatus(mpSpecieDetail->mpMetab->getStatus());
  setUndoState(true);
  setAction("Create");
  setName(sName);
}

void CreateNewSpeciesCommand::undo()
{
  mpSpecieDetail->deleteSpecie(mpSpeciesData);
  setUndoState(false);
  setAction("Delete");
}

QString CreateNewSpeciesCommand::createNewSpecieText() const
{
  return QObject::tr(": Created new species ");
}

UndoData *CreateNewSpeciesCommand::getUndoData() const
{
  return mpSpeciesData;
}

CreateNewSpeciesCommand::~CreateNewSpeciesCommand()
{
  pdelete(mpSpeciesData);
}
