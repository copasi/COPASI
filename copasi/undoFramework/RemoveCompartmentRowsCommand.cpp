// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
  GET_MODEL_OR_RETURN(pModel);

  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (pCompartmentDM->isDefaultRow(*i))
        continue;

      UndoCompartmentData *data = new UndoCompartmentData(&pModel->getCompartments()[i->row()]);
      mpCompartmentData.append(data);
    }

  setText(QObject::tr(": Removed Compartments"));
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

RemoveCompartmentRowsCommand::~RemoveCompartmentRowsCommand()
{
  foreach(UndoCompartmentData * data, mpCompartmentData)
  {
    pdelete(data);
  }
  mpCompartmentData.clear();
}
