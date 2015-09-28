// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * InsertSpecieRowsCommand.cpp
 *
 *  Created on: 27 Aug 2014
 *      Author: dada
 */

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CMetab.h"
//#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "CQSpecieDM.h"

#include "InsertSpeciesRowsCommand.h"
#include "UndoSpeciesData.h"

InsertSpecieRowsCommand::InsertSpecieRowsCommand(int position, int rows, CQSpecieDM *pSpecieDM, const QModelIndex& index)
  : CCopasiUndoCommand("Species", SPECIES_INSERT)
  , mpSpecieDM(pSpecieDM)
  , mRows(rows)
  , mPosition(position)
  , mIndex(index)
  , mpSpeciesData(new UndoSpeciesData())
  , firstTime(true)
{
  this->setText(insertRowsText());
}

void InsertSpecieRowsCommand::redo()
{
  if (firstTime)
    {
      mpSpecieDM->insertNewSpecieRow(mPosition, mRows, QModelIndex());
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
      assert(pDataModel != NULL);
      CModel * pModel = pDataModel->getModel();
      assert(pModel != NULL);

      CMetab *pSpecies = pModel->getMetabolites()[mPosition];
      mpSpeciesData->setName(pSpecies->getObjectName());
      mpSpeciesData->setKey(pSpecies->getKey());
      mpSpeciesData->setIConc(pSpecies->getInitialConcentration());
      mpSpeciesData->setCompartment(pSpecies->getCompartment()->getObjectName());
      firstTime = false;
    }
  else
    {
      mpSpecieDM->addSpecieRow(mpSpeciesData);
    }

  setUndoState(true);
  setAction("Add to list");
  setName(mpSpeciesData->getName());
}

void InsertSpecieRowsCommand::undo()
{
  mpSpecieDM->deleteSpecieRow(mpSpeciesData);
  setUndoState(false);
  setAction("Remove from list");
}

QString InsertSpecieRowsCommand::insertRowsText() const
{
  return QObject::tr(": Inserted new species");
}

UndoData *InsertSpecieRowsCommand::getUndoData() const
{
  return mpSpeciesData;
}

InsertSpecieRowsCommand::~InsertSpecieRowsCommand()
{
  pdelete(mpSpeciesData);
}
