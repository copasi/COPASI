// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * SpecieDataChangeCommand.cpp
 *
 *  Created on: 27 Aug 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CMetab.h"
#include "model/CModel.h"
#include "CQSpecieDM.h"

#include "qtUtilities.h"

#include "SpeciesDataChangeCommand.h"

SpecieDataChangeCommand::SpecieDataChangeCommand(
  const QModelIndex& index,
  const QVariant& value,
  int role,
  CQSpecieDM *pSpecieDM)
  : CCopasiUndoCommand("Species", SPECIES_DATA_CHANGE)
  , mNew(value)
  , mOld(index.data(Qt::DisplayRole))
  , mIndex(index)
  , mpSpecieDM(pSpecieDM)
  , mRole(role)
  , mPathIndex(pathFromIndex(index))
{

  //set the data for UNDO history
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel->getMetabolites().size() <= (size_t)index.row())
    {
      return;
    }

  CMetab *pSpecies = pModel->getMetabolites()[index.row()];

  setAction("Change");

  setName(pSpecies->getObjectName());
  setOldValue(TO_UTF8(mOld.toString()));
  setNewValue(TO_UTF8(mNew.toString()));

  switch (index.column())
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

  setText(specieDataChangeText());
}

SpecieDataChangeCommand::~SpecieDataChangeCommand()
{
}

void SpecieDataChangeCommand::redo()
{
  mIndex = pathToIndex(mPathIndex, mpSpecieDM);
  mpSpecieDM->specieDataChange(mIndex, mNew, mRole);
}

void SpecieDataChangeCommand::undo()
{
  mIndex = pathToIndex(mPathIndex, mpSpecieDM);
  mpSpecieDM->specieDataChange(mIndex, mOld, mRole);
  setAction("Undone change");
}

QString SpecieDataChangeCommand::specieDataChangeText() const
{
  return QString(": Changed species %1").arg(getProperty().c_str());
}
