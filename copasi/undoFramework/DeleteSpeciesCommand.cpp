// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
  , mpSpeciesData(new UndoSpeciesData(pSpecieDetail->mpMetab))
  , mpSpecieDetail(pSpecieDetail)
{
  const std::string& sName = mpSpecieDetail->mpMetab->getObjectName();
  setName(sName);
  setText(QString(": Deleted species %1").arg(sName.c_str()));
}

void DeleteSpeciesCommand::redo()
{
  if (mFirstTime && !mpSpecieDetail->getKey().empty())
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

DeleteSpeciesCommand::~DeleteSpeciesCommand()
{
  pdelete(mpSpeciesData);
}
