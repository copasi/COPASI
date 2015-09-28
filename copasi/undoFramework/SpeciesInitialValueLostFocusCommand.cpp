// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * SpeciesInitialValueLostFocusCommand.cpp
 *
 *  Created on: 19 Sep 2014
 *      Author: dada
 */

#include "qtUtilities.h"

#include "model/CMetab.h"
#include "UI/CQSpeciesDetail.h"
#include "model/CCompartment.h"

#include "UndoSpeciesData.h"

#include "SpeciesInitialValueLostFocusCommand.h"

SpeciesInitialValueLostFocusCommand::SpeciesInitialValueLostFocusCommand(
  CQSpeciesDetail *pSpecieDetail)
  : CCopasiUndoCommand("Species", SPECIES_TYPE_CHANGE, "Change")
  , mpSpecieDetail(pSpecieDetail)
  , mpSpeciesData(new UndoSpeciesData())
  , mFirstTime(true)
{

  std::string sName = mpSpecieDetail->mpMetab->getObjectName();
  mpSpeciesData->setName(sName);
  mpSpeciesData->setIConc(mpSpecieDetail->mInitialConcentration);
  mpSpeciesData->setINumber(mpSpecieDetail->mInitialNumber);

  this->setText(specieInitialValueLostFocusText(sName));

  //set the data for UNDO history
  setName(mpSpeciesData->getName());

  std::ostringstream strs;
  strs << mpSpecieDetail->mInitialConcentration;
  std::string str = strs.str();
  setNewValue(str);
  strs.clear();
  strs << mpSpecieDetail->mpMetab->getInitialConcentration();
  str = strs.str();
  setOldValue(str);
  setProperty("Initial Value");
}
void SpeciesInitialValueLostFocusCommand::redo()
{
  if (mFirstTime)
    {
      mpSpecieDetail->speciesInitialValueLostFocus();
      mFirstTime = false;
    }
  else
    {
      mpSpecieDetail->speciesInitialValueLostFocus(mpSpeciesData);
    }
}
void SpeciesInitialValueLostFocusCommand::undo()
{
  mpSpecieDetail->speciesInitialValueLostFocus(mpSpeciesData);
  setAction("Undone change");
}

QString SpeciesInitialValueLostFocusCommand::specieInitialValueLostFocusText(std::string &name) const
{
  return QString(": Species Initial Value Change for %1").arg(FROM_UTF8(name));
}

SpeciesInitialValueLostFocusCommand::~SpeciesInitialValueLostFocusCommand()
{
  pdelete(mpSpeciesData);
}
