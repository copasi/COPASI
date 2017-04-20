// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/copasi.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CModel.h"
#include "copasi/UI/CQSpecieDM.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CReactionInterface.h"
#include "copasi/CopasiDataModel/CDataModel.h"

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
  CDataModel * pDataModel = pSpecieDM->getDataModel();
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);

  for (int i = 0; i != pSpecieDM->rowCount() - 1; ++i)
    {

      if (&pModel->getMetabolites()[i] == NULL)
        continue;

      UndoSpeciesData *data = new UndoSpeciesData(&pModel->getMetabolites()[i]);
      mpSpeciesData.append(data);
    }

  setText(QObject::tr(": Removed All Species"));
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

RemoveAllSpecieRowsCommand::~RemoveAllSpecieRowsCommand()
{
  // freeing the memory allocated above
  foreach(UndoSpeciesData * data, mpSpeciesData)
  {
    pdelete(data);
  }

  mpSpeciesData.clear();
}
