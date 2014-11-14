// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoGlobalQuantityData.cpp
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#include <QtCore/QList>

#include "model/CModelValue.h"
#include "UndoGlobalQuantityData.h"
#include "UndoReactionData.h"
#include "UndoEventData.h"
#include "UndoSpecieData.h"

#include "UndoGlobalQuantityData.h"

UndoGlobalQuantityData::UndoGlobalQuantityData()
{
  // TODO Auto-generated constructor stub
}

double UndoGlobalQuantityData::getInitialValue() const
{
  return mInitialValue;
}

CModelEntity::Status UndoGlobalQuantityData::getStatus() const
{
  return mStatus;
}

void UndoGlobalQuantityData::setInitialValue(double initialValue)
{
  mInitialValue = initialValue;
}

void UndoGlobalQuantityData::setStatus(CModelEntity::Status status)
{
  mStatus = status;
}

UndoGlobalQuantityData::~UndoGlobalQuantityData()
{
  // TODO Auto-generated destructor stub
}

QList<UndoReactionData*> *UndoGlobalQuantityData::getReactionDependencyObjects() const
{
  return mReactionDependencyObjects;
}

void UndoGlobalQuantityData::setReactionDependencyObjects(QList<UndoReactionData*> *reactionDependencyObjects)
{
  mReactionDependencyObjects = reactionDependencyObjects;
}

bool UndoGlobalQuantityData::isFixed() const
{
  return fixed;
}

void UndoGlobalQuantityData::setFixed(bool fixed)
{
  this->fixed = fixed;
}

const std::string & UndoGlobalQuantityData::getExpression() const
{
  return mExpression;
}

void UndoGlobalQuantityData::setExpression(const std::string &expression)
{
  mExpression = expression;
}

CModelValue UndoGlobalQuantityData::getModelValue() const
{
  return modelValue;
}

void UndoGlobalQuantityData::setModelValue(CModelValue modelValue)
{
  this->modelValue = modelValue;
}

const std::string & UndoGlobalQuantityData::getInitialExpression() const
{
  return mInitialExpression;
}

void UndoGlobalQuantityData::setInitialExpression(const std::string &initialExpression)
{
  mInitialExpression = initialExpression;
}

QList<UndoEventData*> *UndoGlobalQuantityData::getEventDependencyObjects() const
{
  return mEventDependencyObjects;
}

QList<UndoSpecieData*> *UndoGlobalQuantityData::getSpecieDependencyObjects() const
{
  return mSpecieDependencyObjects;
}

void UndoGlobalQuantityData::setEventDependencyObjects(QList<UndoEventData*> *eventDependencyObjects)
{
  mEventDependencyObjects = eventDependencyObjects;
}

void UndoGlobalQuantityData::setSpecieDependencyObjects(QList<UndoSpecieData*> *specieDependencyObjects)
{
  mSpecieDependencyObjects = specieDependencyObjects;
}
