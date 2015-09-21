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

UndoEventAssignmentData::UndoEventAssignmentData(const std::string &key  /*= ""*/,
    const std::string &name /*= ""*/,
    const std::string &type /*= ""*/)
  : UndoData(key, name, type)
  , mExpression()
{

}

UndoEventAssignmentData::UndoEventAssignmentData(const CModelEntity *pEntity,
    const std::string& expression)
  : UndoData(pEntity->getKey(), pEntity->getObjectName())
  , mExpression(expression)
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
UndoEventAssignmentData::addToEvent(CEvent *pEvent) const
{
  CEventAssignment *eventAssign =
    new CEventAssignment(getKey(), pEvent->getObjectParent());
  eventAssign->setExpression(getExpression());
  eventAssign->getExpressionPtr()->compile();
  pEvent->getAssignments().add(eventAssign);
}
