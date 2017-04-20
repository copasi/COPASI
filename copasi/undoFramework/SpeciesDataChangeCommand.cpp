// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * SpecieDataChangeCommand.cpp
 *
 *  Created on: 27 Aug 2014
 *      Author: dada
 */

#include "CQSpecieDM.h"
#include "SpeciesDataChangeCommand.h"

#include "copasi.h"
#include "UI/qtUtilities.h"
#include "UndoSpeciesData.h"

#include "copasi/core/CRootContainer.h"
#include "model/CMetab.h"
#include "model/CModel.h"

SpecieDataChangeCommand::SpecieDataChangeCommand(
  const CMetab* pMetab,
  const QVariant& newValue,
  const QVariant &oldValue,
  int column,
  CQSpecieDM *pSpecieDM)
  : CCopasiUndoCommand("Species", SPECIES_DATA_CHANGE)
  , mpSpeciesData(new UndoSpeciesData(pMetab))
  , mNew(newValue)
  , mOld(oldValue)
  , mColumn(column)
  , mpSpecieDM(pSpecieDM)
{

  //set the data for UNDO history
  CModel * pModel = pMetab->getModel();
  assert(pModel != NULL);

  if (pMetab == NULL)
    return;

  setAction("Change");

  setName(pMetab->getObjectName());
  setOldValue(TO_UTF8(mOld.toString()));
  setNewValue(TO_UTF8(mNew.toString()));

  switch (column)
    {
      case 0:
        setProperty("");
        break;

      case 1:
        setProperty("Name");
        break;

      case 2:
        setProperty("Compartment");
        break;

      case 3:
        setProperty("Type");

        switch (mNew.toInt())
          {
            case 0:
              setNewValue("reactions");
              break;

            case 1:
              setNewValue("fixed");
              break;

            case 2:
              setNewValue("assignment");
              break;

            case 3:
              setNewValue("ode");
              break;
          }

        break;

      case 4:
        setProperty("Initial Concentration");
        break;
    }

  setText(QString(": Changed species %1").arg(getProperty().c_str()));
}

SpecieDataChangeCommand::~SpecieDataChangeCommand()
{
  pdelete(mpSpeciesData);
}

void SpecieDataChangeCommand::redo()
{
  mpSpecieDM->specieDataChange(mpSpeciesData, mNew, mColumn);
  setAction("Change");
}

void SpecieDataChangeCommand::undo()
{
  mpSpecieDM->specieDataChange(mpSpeciesData, mOld, mColumn);
  setAction("Undone change");
}
