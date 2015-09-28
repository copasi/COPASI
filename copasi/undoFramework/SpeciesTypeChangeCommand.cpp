// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
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
                       CModelEntity::XMLStatus[type], CModelEntity::XMLStatus[currentType], mpSpeciesData->getName())
  , mNewType(type)
  , mOldType(currentType)
  , mpSpeciesDetail(pSpeciesDetail)
  , mpSpeciesData(new UndoSpeciesData(mpSpeciesDetail->mpMetab))
  , mFirstTime(true)
  , useInitialExpression(false)
{

  mpSpeciesData = new UndoSpeciesData(mpSpeciesDetail->mpMetab);
  mpSpeciesData->setStatus((CModelEntity::Status)type);

  setText(specieTypeChangeText(getName()));
}

void
SpeciesTypeChangeCommand::redo()
{
  if (mFirstTime)
    {
      mpSpeciesDetail->speciesTypeChanged(mpSpeciesDetail->mpComboBoxType->currentIndex());
      mFirstTime = false;
    }
  else
    {
      mpSpeciesDetail->speciesTypeChanged(mpSpeciesData, mNewType);
    }
}

void
SpeciesTypeChangeCommand::undo()
{
  mpSpeciesDetail->speciesTypeChanged(mpSpeciesData, mOldType);
  setAction("Undone change");
}

QString
SpeciesTypeChangeCommand::specieTypeChangeText(const std::string &name) const
{
  return QString(": Species Type Change for %1").arg(FROM_UTF8(name));
}

SpeciesTypeChangeCommand::~SpeciesTypeChangeCommand()
{
  pdelete(this->mpSpeciesData);
}
