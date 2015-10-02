// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveAllCompartmentRowsCommand.cpp
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CCompartment.h"
#include "model/CModel.h"
#include "UI/CQCompartmentDM.h"
//#include "function/CFunctionDB.h"

//#include "model/CReaction.h"
//#include "model/CReactionInterface.h"

#include "UndoCompartmentData.h"
#include "UndoReactionData.h"

#include "RemoveAllCompartmentRowsCommand.h"

RemoveAllCompartmentRowsCommand::RemoveAllCompartmentRowsCommand(CQCompartmentDM * pCompartmentDM, const QModelIndex&)
  : CCopasiUndoCommand("Compartment", COMPARTMENT_REMOVE_ALL)
  , mpCompartmentDM(pCompartmentDM)
  , mpCompartmentData()
{
  GET_MODEL_OR_RETURN(pModel);

  for (int i = 0; i != pCompartmentDM->rowCount() - 1; ++i)
    {
      CCompartment* compartment = pModel->getCompartments()[i];

      if (compartment != NULL)
        {
          UndoCompartmentData *data = new UndoCompartmentData(compartment);
          mpCompartmentData.append(data);
        }
    }

  this->setText(removeAllCompartmentRowsText());
}

void RemoveAllCompartmentRowsCommand::redo()
{
  mpCompartmentDM->removeAllCompartmentRows();
  setUndoState(true);
  setAction("Delete all");
}

void RemoveAllCompartmentRowsCommand::undo()
{
  mpCompartmentDM->insertCompartmentRows(mpCompartmentData);
  setUndoState(false);
  setAction("Undelete all");
}

QString RemoveAllCompartmentRowsCommand::removeAllCompartmentRowsText() const
{
  return QObject::tr(": Removed all compartments");
}

RemoveAllCompartmentRowsCommand::~RemoveAllCompartmentRowsCommand()
{
  // freeing the memory allocated above
  foreach(UndoCompartmentData * data, mpCompartmentData)
  {
    pdelete(data);
  }
  mpCompartmentData.clear();
}
