// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include "DeleteReactionCommand.h"

DeleteReactionCommand::DeleteReactionCommand(ReactionsWidget1 *pReactionWidget)
{
  mpReactionWidget = pReactionWidget;
  mpReaction = dynamic_cast< CReaction * >(CCopasiRootContainer::getKeyFactory()->get(mpReactionWidget->mKey));
  mReaObjectName = mpReaction->getObjectName();
  mpRi = new CReactionInterface((*CCopasiRootContainer::getDatamodelList())[0]->getModel());
  mpRi->initFromReaction(mpReaction->getKey());
  this->setText(deleteReactionText(mReaObjectName));
}

DeleteReactionCommand::~DeleteReactionCommand()
{
  // TODO Auto-generated destructor stub
}

void DeleteReactionCommand::redo()
{
  mpReactionWidget->deleteReaction();
}

void DeleteReactionCommand::undo()
{
  mpReactionWidget->addReaction(mReaObjectName, mpRi);
}

QString DeleteReactionCommand::deleteReactionText(std::string &name) const
{
  std::string myEntityName(": Delete Reaction " + name);
  char* entityName = (char*)myEntityName.c_str();
  return QObject::tr(entityName);
}
