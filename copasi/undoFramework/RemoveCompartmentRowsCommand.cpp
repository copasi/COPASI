// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveCompartmentRowsCommand.cpp
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CMetab.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "CQCompartmentDM.h"
#include "function/CFunctionDB.h"

#include "UndoCompartmentData.h"
#include "UndoReactionData.h"

#include "RemoveCompartmentRowsCommand.h"

RemoveCompartmentRowsCommand::RemoveCompartmentRowsCommand(
  const QModelIndexList& rows,
  CQCompartmentDM * pCompartmentDM)
  : CCopasiUndoCommand("Compartment", COMPARTMENT_REMOVE, "Remove")
  , mRows(rows)
  , mpCompartmentDM(pCompartmentDM)
  , mpCompartmentData()
  , mFirstTime(true)
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  assert(pModel != NULL);

  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (pCompartmentDM->isDefaultRow(*i))
        continue;

      UndoCompartmentData *data = new UndoCompartmentData(pModel->getCompartments()[(*i).row()]);
      mpCompartmentData.append(data);
    }

  this->setText(removeCompartmentRowsText());
}

void RemoveCompartmentRowsCommand::redo()
{
  if (mFirstTime)
    {
      mpCompartmentDM->removeCompartmentRows(mRows, QModelIndex());
      mFirstTime = false;
    }
  else
    {
      mpCompartmentDM->deleteCompartmentRows(mpCompartmentData);
    }

  setUndoState(true);
  setAction("Delete set");
}

void RemoveCompartmentRowsCommand::undo()
{
  mpCompartmentDM->insertCompartmentRows(mpCompartmentData);
  setUndoState(false);
  setAction("Undelete set");
}

QString RemoveCompartmentRowsCommand::removeCompartmentRowsText() const
{
  return QObject::tr(": Removed Compartments");
}

UndoData *RemoveCompartmentRowsCommand::getUndoData() const
{
  return NULL;
}

RemoveCompartmentRowsCommand::~RemoveCompartmentRowsCommand()
{
  // TODO Auto-generated destructor stub
  pdelete(this->mpSpeciesData);
  pdelete(this->mpReactionData);
  pdelete(this->mpGlobalQuantityData);
  pdelete(this->mpEventData);
}
