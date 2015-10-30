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

CreateNewSpeciesCommand::CreateNewSpeciesCommand(CQSpeciesDetail *pSpeciesDetail)
  : CCopasiUndoCommand("Species", SPECIES_CREATE)
  , mpSpeciesData(NULL)
  , mpSpeciesDetail(pSpeciesDetail)
{
  this->setText(QObject::tr(": Created new species "));
}

void CreateNewSpeciesCommand::redo()
{
  if (mpSpeciesData == NULL)
    {
      // TODO: should only happen once
      mpSpeciesDetail->createNewSpecies();
      std::string sName = mpSpeciesDetail->mpMetab->getObjectName();
      mpSpeciesData = new UndoSpeciesData(mpSpeciesDetail->mpMetab);
      setName(sName);
    }
  else
    {
      mpSpeciesDetail->addSpecies(mpSpeciesData);
    }

  setUndoState(true);
  setAction("Create");

}

void CreateNewSpeciesCommand::undo()
{
  mpSpeciesDetail->deleteSpecies(mpSpeciesData);
  setUndoState(false);
  setAction("Delete");
}

CreateNewSpeciesCommand::~CreateNewSpeciesCommand()
{
  pdelete(mpSpeciesData);
}
