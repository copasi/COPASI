// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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
#include "UndoSpeciesData.h"

#include "UndoGlobalQuantityData.h"

UndoGlobalQuantityData::UndoGlobalQuantityData(const std::string &key  /*= ""*/,
    const std::string &name /*= ""*/,
    const std::string &type /*= ""*/)
  : UndoData(key, name, type)
  , mModelValue()
  , mFixed(false)
  , mInitialValue()
  , mStatus(CModelEntity::FIXED)
  , mExpression()
  , mInitialExpression()
  , mSpecieDependencyObjects(new QList<UndoSpeciesData*>())
  , mReactionDependencyObjects(new QList<UndoReactionData*>())
  , mEventDependencyObjects(new QList<UndoEventData*>())
{
}

UndoGlobalQuantityData::~UndoGlobalQuantityData()
{
  pdelete(mSpecieDependencyObjects);
  pdelete(mReactionDependencyObjects);
  pdelete(mEventDependencyObjects);
}

double
UndoGlobalQuantityData::getInitialValue() const
{
  return mInitialValue;
}

CModelEntity::Status
UndoGlobalQuantityData::getStatus() const
{
  return mStatus;
}

void
UndoGlobalQuantityData::setInitialValue(double initialValue)
{
  mInitialValue = initialValue;
}

void UndoGlobalQuantityData::setStatus(CModelEntity::Status status)
{
  mStatus = status;
}

QList<UndoReactionData*> *
UndoGlobalQuantityData::getReactionDependencyObjects() const
{
  return mReactionDependencyObjects;
}

void
UndoGlobalQuantityData::setReactionDependencyObjects(
  QList<UndoReactionData*> *reactionDependencyObjects)
{
  mReactionDependencyObjects = reactionDependencyObjects;
}

bool
UndoGlobalQuantityData::isFixed() const
{
  return mFixed;
}

void
UndoGlobalQuantityData::setFixed(bool fixed)
{
  this->mFixed = fixed;
}

const std::string &
UndoGlobalQuantityData::getExpression() const
{
  return mExpression;
}

void
UndoGlobalQuantityData::setExpression(const std::string &expression)
{
  mExpression = expression;
}

const CModelValue&
UndoGlobalQuantityData::getModelValue() const
{
  return mModelValue;
}

void
UndoGlobalQuantityData::setModelValue(const CModelValue& modelValue)
{
  mModelValue = modelValue;
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

QList<UndoSpeciesData*> *UndoGlobalQuantityData::getSpecieDependencyObjects() const
{
  return mSpecieDependencyObjects;
}

void UndoGlobalQuantityData::setEventDependencyObjects(QList<UndoEventData*> *eventDependencyObjects)
{
  mEventDependencyObjects = eventDependencyObjects;
}

void UndoGlobalQuantityData::setSpecieDependencyObjects(QList<UndoSpeciesData*> *specieDependencyObjects)
{
  mSpecieDependencyObjects = specieDependencyObjects;
}
