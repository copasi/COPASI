// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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
#include "UndoSpecieData.h"

#include "CreateNewSpecieCommand.h"

CreateNewSpecieCommand::CreateNewSpecieCommand(CQSpeciesDetail *pSpecieDetail)
  : CCopasiUndoCommand("Species", SPECIECREATE)
  , mpSpecieData(new UndoSpecieData())
  , mpSpecieDetail(pSpecieDetail)
{
  this->setText(createNewSpecieText());
}

void CreateNewSpecieCommand::redo()
{
  mpSpecieDetail->createNewSpecie();

  std::string sName = mpSpecieDetail->mpMetab->getObjectName();
  mpSpecieData->setName(sName);
  mpSpecieData->setIConc(mpSpecieDetail->mpMetab->getInitialConcentration());
  mpSpecieData->setCompartment(mpSpecieDetail->mpMetab->getCompartment()->getObjectName());
  mpSpecieData->setStatus(mpSpecieDetail->mpMetab->getStatus());
  setUndoState(true);
  setAction("Create");
  setName(sName);
}

void CreateNewSpecieCommand::undo()
{
  mpSpecieDetail->deleteSpecie(mpSpecieData);
  setUndoState(false);
  setAction("Delete");
}

QString CreateNewSpecieCommand::createNewSpecieText() const
{
  return QObject::tr(": Created new species ");
}

UndoData *CreateNewSpecieCommand::getUndoData() const
{
  return mpSpecieData;
}

CreateNewSpecieCommand::~CreateNewSpecieCommand()
{
  pdelete(mpSpecieData);
}
