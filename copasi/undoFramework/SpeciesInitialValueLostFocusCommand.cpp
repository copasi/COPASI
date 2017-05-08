// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
  , mpSpeciesData(new UndoSpeciesData(mpSpecieDetail->mpMetab))
  , mFirstTime(true)
{

  std::string sName = mpSpecieDetail->mpMetab->getObjectName();
  setText(QString(": Species Initial Value Change for %1").arg(FROM_UTF8(sName)));
  setName(mpSpeciesData->getName());

  {
    double newValue = mpSpecieDetail->mpEditInitialValue->text().toDouble();
    std::ostringstream strs;
    strs.precision(std::numeric_limits< double >::digits10 + 2);
    strs << newValue;
    std::string str = strs.str();
    setNewValue(str);
  }
  {
    std::ostringstream strs;
    strs.precision(std::numeric_limits< double >::digits10 + 2);
    strs << mpSpecieDetail->mInitialConcentration;
    std::string str = strs.str();
    setOldValue(str);
  }
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

  setAction("Change");
}
void SpeciesInitialValueLostFocusCommand::undo()
{
  mpSpecieDetail->speciesInitialValueLostFocus(mpSpeciesData);
  setAction("Undone change");
}

SpeciesInitialValueLostFocusCommand::~SpeciesInitialValueLostFocusCommand()
{
  pdelete(mpSpeciesData);
}
