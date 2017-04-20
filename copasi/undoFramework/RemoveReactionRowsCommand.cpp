// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveReactionRowsCommand.cpp
 *
 *  Created on: 11 Aug 2014
 *      Author: dada
 */

#include <QtCore/QList>

#include "copasi/copasi.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CReactionInterface.h"
#include "copasi/model/CModel.h"
#include "copasi/UI/CQReactionDM.h"
#include "copasi/CopasiDataModel/CDataModel.h"

#include "RemoveReactionRowsCommand.h"
#include "UndoReactionData.h"

RemoveReactionRowsCommand::RemoveReactionRowsCommand(
  QModelIndexList rows, CQReactionDM * pReaDM)
  : CCopasiUndoCommand("Reaction", REACTION_REMOVE)
  , mpReactionDM(pReaDM)
  , mpReaData()
{
  CDataModel * pDataModel = pReaDM->getDataModel();
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);

  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {

      if (pReaDM->isDefaultRow(*i) || &pModel->getReactions()[i->row()] == NULL)
        continue;

      UndoReactionData *data = new UndoReactionData(&pModel->getReactions()[i->row()]);
      mpReaData.append(data);
    }

  setText(QObject::tr(": Removed Reaction Rows"));
}

void RemoveReactionRowsCommand::redo()
{
  mpReactionDM->deleteReactionRows(mpReaData);
  setUndoState(true);
  setAction("Delete set");
}

void RemoveReactionRowsCommand::undo()
{
  mpReactionDM->insertReactionRows(mpReaData);
  setUndoState(false);
  setAction("Undelete set");
}

RemoveReactionRowsCommand::~RemoveReactionRowsCommand()
{
  // freeing the memory allocated above
  foreach(UndoReactionData * data, mpReaData)
  {
    pdelete(data);
  }

  mpReaData.clear();
}
