// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * DeleteReactionCommand.cpp
 *
 *  Created on: 4 Jul 2014
 *      Author: dada
 */

#include "qtUtilities.h"

#include "report/CCopasiRootContainer.h"
#include "model/CReaction.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "UI/ReactionsWidget1.h"
#include "UndoReactionData.h"

#include "DeleteReactionCommand.h"

DeleteReactionCommand::DeleteReactionCommand(ReactionsWidget1 *pReactionWidget)
  : CCopasiUndoCommand("Reaction", REACTION_DELETE)
  , mReaObjectName()
  , mpRi(NULL)
  , mpReaction(NULL)
  , mpReactionData(NULL)
  , mpReactionWidget(pReactionWidget)
{
  mpReaction = dynamic_cast< CReaction * >(CCopasiRootContainer::getKeyFactory()->get(mpReactionWidget->mKey));
  mReaObjectName = mpReaction->getObjectName();
  mpRi = new CReactionInterface((*CCopasiRootContainer::getDatamodelList())[0]->getModel());
  mpRi->initFromReaction(mpReaction);

  mpReactionData = new UndoReactionData(mpReaction);

  setText(QString(": Deleted reaction %1").arg(mReaObjectName.c_str()));
  setName(mReaObjectName);
}

DeleteReactionCommand::~DeleteReactionCommand()
{
  pdelete(mpReactionData);
  pdelete(mpRi);
}

void DeleteReactionCommand::redo()
{
  mpReactionWidget->deleteReaction();
  setUndoState(true);
  setAction("Delete");
}

void DeleteReactionCommand::undo()
{
  mpReactionWidget->addReaction(mReaObjectName, mpRi);
  setUndoState(false);
  setAction("Undelete");
}
