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
}
void CreateNewSpecieCommand::redo()
{
  mpSpecieDetail->createNewSpecie();

  std::string sName = mpSpecieDetail->mpMetab->getObjectName();
  mpSpecieData->setName(sName);
  mpSpecieData->setIConc(mpSpecieDetail->mpMetab->getInitialConcentration());
  mpSpecieData->setCompartment(mpSpecieDetail->mpMetab->getCompartment()->getObjectName());
  mpSpecieData->setStatus(mpSpecieDetail->mpMetab->getStatus());
}

void CreateNewSpecieCommand::undo()
{
  mpSpecieDetail->deleteSpecie(mpSpecieData);
}

QString CreateNewSpecieCommand::createNewSpecieText() const
{
  std::string myEntityName(": Create New Species ");
  char* entityName = (char*)myEntityName.c_str();
  return QObject::tr(entityName);
}

CreateNewSpecieCommand::~CreateNewSpecieCommand()
{
  // TODO Auto-generated destructor stub
}
