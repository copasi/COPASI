// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
{
  GET_MODEL_OR_RETURN(pModel);

  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (pSpecieDM->isDefaultRow(*i) || &pModel->getMetabolites()[i->row()] == NULL)
        continue;

      UndoSpeciesData *data = new UndoSpeciesData(&pModel->getMetabolites()[i->row()]);
      mpSpeciesData.append(data);
    }

  setText(QObject::tr(": Removed Species"));
}

void RemoveSpecieRowsCommand::redo()
{
  mpSpecieDM->deleteSpecieRows(mpSpeciesData);
  setUndoState(true);
  setAction("Delete set");
}

void RemoveSpecieRowsCommand::undo()
{
  mpSpecieDM->insertSpecieRows(mpSpeciesData);
  setUndoState(false);
  setAction("Undelete set");
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
