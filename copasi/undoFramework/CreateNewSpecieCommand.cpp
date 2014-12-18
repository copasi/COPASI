// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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
{
  mpSpecieDetail = pSpecieDetail;
  mpSpecieData = new UndoSpecieData();
  this->setText(createNewSpecieText());
  mType = SPECIECREATE;
  setEntityType("Species");
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
  std::string myEntityName(": Create New Species ");
  char* entityName = (char*)myEntityName.c_str();
  return QObject::tr(entityName);
}

UndoData *CreateNewSpecieCommand::getUndoData() const
{
  return mpSpecieData;
}

CreateNewSpecieCommand::~CreateNewSpecieCommand()
{
  // TODO Auto-generated destructor stub
}
