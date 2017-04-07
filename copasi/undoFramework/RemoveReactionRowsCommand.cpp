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

#include "copasi.h"

#include "report/CCopasiRootContainer.h"
#include "model/CReaction.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "CQReactionDM.h"

#include "RemoveReactionRowsCommand.h"
#include "UndoReactionData.h"

RemoveReactionRowsCommand::RemoveReactionRowsCommand(
  QModelIndexList rows, CQReactionDM * pReaDM, const QModelIndex&)
  : CCopasiUndoCommand("Reaction", REACTION_REMOVE)
  , mpReactionDM(pReaDM)
  , mRows(rows)
  , mpReaData()
  , mFirstTime(true)
{
  CCopasiDataModel * pDataModel = pReaDM->getDataModel();
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
  if (mFirstTime)
    {
      mpReactionDM->removeReactionRows(mRows, QModelIndex());
      mFirstTime = false;
    }
  else
    {
      mpReactionDM->deleteReactionRows(mpReaData);
    }

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
