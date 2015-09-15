// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoEventAssignmentData.cpp
 *
 *  Created on: 20 Nov 2014
 *      Author: dada
 */

#include "UndoEventAssignmentData.h"

#include <copasi/model/CModel.h>
#include <copasi/model/CEvent.h>
#include "copasi/function/CExpression.h"

UndoEventAssignmentData::UndoEventAssignmentData()
  : UndoData()
{
}

UndoEventAssignmentData::~UndoEventAssignmentData()
{
}

const std::string&
UndoEventAssignmentData::getExpression() const
{
  return mExpression;
}

void
UndoEventAssignmentData::setExpression(const std::string &expression)
{
  mExpression = expression;
}

void
UndoEventAssignmentData::addToEvent(CEvent *pEvent, CModel *pModel) const
{
  CCopasiObject * pObject = NULL;

  if (pModel->findMetabByName(getName()) != C_INVALID_INDEX)
    {
      pObject = pModel->getMetabolites()[pModel->findMetabByName(getName())];
    }
  else  if (pModel->getModelValues().getIndex(getName()) != C_INVALID_INDEX)
    {
      pObject = pModel->getModelValues()[getName()];
    }
  else  if (pModel->getCompartments().getIndex(getName()) != C_INVALID_INDEX)
    {
      pObject = pModel->getCompartments()[getName()];
    }
  else if (pModel->getReactions().getIndex(getName()) != C_INVALID_INDEX)
    {
      pObject = pModel->getReactions()[getName()];
    }

  if (pObject == NULL)
    return;

  CEventAssignment *eventAssign =
    new CEventAssignment(pObject->getKey(), pEvent->getObjectParent());
  eventAssign->setExpression(getExpression());
  eventAssign->getExpressionPtr()->compile();
  pEvent->getAssignments().add(eventAssign);
}
