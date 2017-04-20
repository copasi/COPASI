// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

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

#include "RemoveCompartmentRowsCommand.h"

#include "copasi/copasi.h"

#include "UndoCompartmentData.h"
#include "UndoReactionData.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CReactionInterface.h"
#include "copasi/model/CModel.h"
#include "copasi/UI/CQCompartmentDM.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/CopasiDataModel/CDataModel.h"

RemoveCompartmentRowsCommand::RemoveCompartmentRowsCommand(
  const QModelIndexList& rows,
  CQCompartmentDM * pCompartmentDM)
  : CCopasiUndoCommand("Compartment", COMPARTMENT_REMOVE, "Remove")
  , mpCompartmentDM(pCompartmentDM)
  , mpCompartmentData()
{
  CDataModel * pDataModel = mpCompartmentDM->getDataModel();
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);

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
  mpCompartmentDM->deleteCompartmentRows(mpCompartmentData);

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
