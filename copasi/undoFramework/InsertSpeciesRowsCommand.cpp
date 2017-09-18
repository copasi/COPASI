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

InsertSpecieRowsCommand::InsertSpecieRowsCommand(int position, int rows, CQSpecieDM * pSpecieDM)
  : CCopasiUndoCommand("Species", SPECIES_INSERT)
  , mpSpecieDM(pSpecieDM)
  , mRows(rows)
  , mPosition(position)
  , mIndex()
  , mpSpeciesData()
  , mValue()
{
  setText(QObject::tr(": Inserted new species"));
}

InsertSpecieRowsCommand::InsertSpecieRowsCommand(int position, int rows, CQSpecieDM *pSpecieDM, const QModelIndex& index, const QVariant& value)
  : CCopasiUndoCommand("Species", SPECIES_INSERT)
  , mpSpecieDM(pSpecieDM)
  , mRows(rows)
  , mPosition(position)
  , mIndex(index)
  , mpSpeciesData()
  , mValue(value)
{
  setText(QObject::tr(": Inserted new species"));
}

void InsertSpecieRowsCommand::redo()
{
  if (mpSpeciesData.count() == 0)
    {
      mpSpeciesData = mpSpecieDM->insertNewSpecieRow(mPosition, mRows, mIndex, mValue);
    }
  else
    {
      mpSpecieDM->insertSpecieRows(mpSpeciesData);
    }

  setUndoState(true);
  setAction("Add to list");

  if (!mpSpeciesData.empty())
    setName(mpSpeciesData[0]->getName());
}

void InsertSpecieRowsCommand::undo()
{
  mpSpecieDM->deleteSpecieRows(mpSpeciesData);
  setUndoState(false);
  setAction("Remove from list");
}

InsertSpecieRowsCommand::~InsertSpecieRowsCommand()
{
  foreach(UndoSpeciesData * data, mpSpeciesData)
  {
    pdelete(data);
  }
  mpSpeciesData.clear();
}
