// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveSpecieRowsCommand.cpp
 *
 *  Created on: 28 Aug 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CMetab.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "CQSpecieDM.h"
#include "function/CFunctionDB.h"

#include "UndoSpeciesData.h"
#include "UndoReactionData.h"
#include "UndoEventData.h"
#include "UndoGlobalQuantityData.h"
#include "RemoveSpeciesRowsCommand.h"

RemoveSpecieRowsCommand::RemoveSpecieRowsCommand(
  QModelIndexList rows, CQSpecieDM * pSpecieDM, const QModelIndex&)
  : CCopasiUndoCommand("Species", SPECIES_REMOVE)
  , mpSpecieDM(pSpecieDM)
  , mRows(rows)
  , mpSpeciesData()
  , mFirstTime(true)
{
  GET_MODEL_OR_RETURN(pModel);

  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (pSpecieDM->isDefaultRow(*i) || pModel->getMetabolites()[(*i).row()] == NULL)
        continue;

      UndoSpeciesData *data = new UndoSpeciesData(pModel->getMetabolites()[(*i).row()]);

      setDependentObjects(pModel->getMetabolites()[(*i).row()]->getDeletedObjects(),
                          data->getReactionDependencyObjects(),
                          NULL,
                          data->getGlobalQuantityDependencyObjects(),
                          data->getEventDependencyObjects());

      mpSpeciesData.append(data);

    }

  this->setText(removeSpecieRowsText());
}

void RemoveSpecieRowsCommand::redo()
{
  if (mFirstTime)
    {
      mpSpecieDM->removeSpecieRows(mRows, QModelIndex());
      mFirstTime = false;
    }
  else
    {
      mpSpecieDM->deleteSpecieRows(mpSpeciesData);
    }

  setUndoState(true);
  setAction("Delete set");
}

void RemoveSpecieRowsCommand::undo()
{
  mpSpecieDM->insertSpecieRows(mpSpeciesData);
  setUndoState(false);
  setAction("Undelete set");
}

QString RemoveSpecieRowsCommand::removeSpecieRowsText() const
{
  return QObject::tr(": Removed Species");
}

RemoveSpecieRowsCommand::~RemoveSpecieRowsCommand()
{
  // freeing the memory allocated above
  foreach(UndoSpeciesData * data, mpSpeciesData)
  {
    pdelete(data);
  }
  mpSpeciesData.clear();
}
