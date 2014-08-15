// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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

CreateNewReactionCommand::CreateNewReactionCommand(ReactionsWidget1 *pReactionWidget)
{
  mpReactionWidget = pReactionWidget;
  this->setText(createNewReactionText());
}
void CreateNewReactionCommand::redo()
{
  mpReactionWidget->createNewReaction();
  mpReaction = dynamic_cast< CReaction * >(mpReactionWidget->mpObject);
}

void CreateNewReactionCommand::undo()
{
  mpReactionWidget->deleteReaction(mpReaction);
}

QString CreateNewReactionCommand::createNewReactionText() const
{
  std::string myEntityName(": Create New Reaction ");
  char* entityName = (char*)myEntityName.c_str();
  return QObject::tr(entityName);
}

CreateNewReactionCommand::~CreateNewReactionCommand()
{
  // TODO Auto-generated destructor stub
}
