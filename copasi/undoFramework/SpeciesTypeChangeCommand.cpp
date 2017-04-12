// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * SpecieTypeChangeCommand.cpp
 *
 *  Created on: 4 Sep 2014
 *      Author: dada
 */

#include "qtUtilities.h"

#include "model/CMetab.h"
#include "UI/CQSpeciesDetail.h"
#include "model/CCompartment.h"

#include "UndoSpeciesData.h"

#include "SpeciesTypeChangeCommand.h"

SpeciesTypeChangeCommand::SpeciesTypeChangeCommand(
  int type, int currentType, CQSpeciesDetail *pSpeciesDetail)
  : CCopasiUndoCommand("Species", SPECIES_TYPE_CHANGE, "Change", "Type",
                       CModelEntity::XMLStatus[type], CModelEntity::XMLStatus[currentType],
                       pSpeciesDetail->mpMetab->getObjectName())
  , mNewType(type)
  , mOldType(currentType)
  , mpSpeciesDetail(pSpeciesDetail)
  , mpSpeciesData(new UndoSpeciesData(mpSpeciesDetail->mpMetab))
  , useInitialExpression(false)
{

  mpSpeciesData->setStatus((CModelEntity::Status)type);

  setText(QString(": Species Type Change for %1").arg(FROM_UTF8(mName)));
}

void
SpeciesTypeChangeCommand::redo()
{
  mpSpeciesDetail->speciesTypeChanged(mpSpeciesData, mNewType);

  setAction("Change");
}

void
SpeciesTypeChangeCommand::undo()
{
  mpSpeciesDetail->speciesTypeChanged(mpSpeciesData, mOldType);
  setAction("Undone change");
}

SpeciesTypeChangeCommand::~SpeciesTypeChangeCommand()
{
  pdelete(this->mpSpeciesData);
}
