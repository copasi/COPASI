// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveAllSpecieRowsCommand.cpp
 *
 *  Created on: 26 Aug 2014
 *      Author: dada
 */

#include <QtCore/QList>

#include "report/CCopasiRootContainer.h"
#include "model/CMetab.h"
#include "model/CModel.h"
#include "UI/CQSpecieDM.h"
#include "function/CFunctionDB.h"

#include "model/CReaction.h"
#include "model/CReactionInterface.h"

#include "RemoveAllSpeciesRowsCommand.h"
#include "UndoSpeciesData.h"
#include "UndoReactionData.h"
#include "UndoGlobalQuantityData.h"
#include "UndoEventData.h"

RemoveAllSpecieRowsCommand::RemoveAllSpecieRowsCommand(
  CQSpecieDM * pSpecieDM, const QModelIndex&)
  : CCopasiUndoCommand("Species", SPECIES_REMOVE_ALL)
  , mpSpecieDM(pSpecieDM)
  , mpSpeciesData()
{
  GET_MODEL_OR_RETURN(pModel);

  for (int i = 0; i != pSpecieDM->rowCount() - 1; ++i)
    {

      if (pModel->getMetabolites()[i] == NULL)
        continue;

      UndoSpeciesData *data = new UndoSpeciesData(pModel->getMetabolites()[i]);
      mpSpeciesData.append(data);

    }

  setText(removeAllSpecieRowsText());
}

void RemoveAllSpecieRowsCommand::redo()
{
  mpSpecieDM->removeAllSpecieRows();
  setUndoState(true);
  setAction("Delete all");
}

void RemoveAllSpecieRowsCommand::undo()
{
  mpSpecieDM->insertSpecieRows(mpSpeciesData);
  setUndoState(false);
  setAction("Undelete all");
}

QString RemoveAllSpecieRowsCommand::removeAllSpecieRowsText() const
{
  return QObject::tr(": Removed All Species");
}

RemoveAllSpecieRowsCommand::~RemoveAllSpecieRowsCommand()
{
  // freeing the memory allocated above
  foreach(UndoSpeciesData * data, mpSpeciesData)
  {
    pdelete(data);
  }
  mpSpeciesData.clear();
}
