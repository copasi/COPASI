// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CreateNewReactionCommand.cpp
 *
 *  Created on: 23 Jul 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CReaction.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "UI/ReactionsWidget1.h"

#include "CreateNewReactionCommand.h"
#include "UndoReactionData.h"

CreateNewReactionCommand::CreateNewReactionCommand(ReactionsWidget1 *pReactionWidget)
  : CCopasiUndoCommand("Reaction", REACTION_CREATE)
  , mpReactionWidget(pReactionWidget)
  , mpReaction(NULL)
  , mpReactionData(new UndoReactionData())
{
  this->setText(createNewReactionText());
}

void CreateNewReactionCommand::redo()
{
  // TODO: should only happen once
  mpReactionWidget->createNewReaction();
  mpReaction = dynamic_cast< CReaction * >(mpReactionWidget->mpObject);
  std::string sName = mpReaction->getObjectName();
  mpReactionData->setName(sName);
  mpReactionData->setKey(mpReaction->getKey());
  CReactionInterface* ri = new CReactionInterface((*CCopasiRootContainer::getDatamodelList())[0]->getModel());
  ri->initFromReaction(mpReaction);
  mpReactionData->setRi(ri);
  setUndoState(true);
  setAction("Create");
  setName(sName);
}

void CreateNewReactionCommand::undo()
{
  mpReactionWidget->deleteReaction(mpReaction);
  setUndoState(false);
  setAction("Delete");
}

QString CreateNewReactionCommand::createNewReactionText() const
{
  return QObject::tr(": Created new reaction ");
}

UndoData *CreateNewReactionCommand::getUndoData() const
{
  return mpReactionData;
}

CreateNewReactionCommand::~CreateNewReactionCommand()
{
  pdelete(mpReactionData);
}
