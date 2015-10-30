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
  , mpSpeciesData(new UndoSpeciesData(mpSpecieDetail->mpMetab))
  , mpSpecieDetail(pSpecieDetail)
{
  const std::string& sName = mpSpecieDetail->mpMetab->getObjectName();
  setName(sName);
  setText(deleteSpecieText(sName));
}

void DeleteSpeciesCommand::redo()
{
  if (mFirstTime)
    {
      mpSpecieDetail->deleteSpecies();
      mFirstTime = false;
    }
  else
    {
      mpSpecieDetail->deleteSpecies(mpSpeciesData);
    }

  setUndoState(true);
  setAction("Delete");
}

void DeleteSpeciesCommand::undo()
{
  mpSpecieDetail->addSpecies(mpSpeciesData);
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
