// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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

UndoEventAssignmentData::UndoEventAssignmentData()
{
  // TODO Auto-generated constructor stub
}

UndoEventAssignmentData::~UndoEventAssignmentData()
{
  // TODO Auto-generated destructor stub
}

std::string UndoEventAssignmentData::getTargetKey() const
{
  return mTargetKey;
}

void UndoEventAssignmentData::setTargetKey(const std::string &targetKey)
{
  mTargetKey = targetKey;
}

std::string UndoEventAssignmentData::getExpression() const
{
  return mExpression;
}

void UndoEventAssignmentData::setExpression(const std::string &expression)
{
  mExpression = expression;
}
