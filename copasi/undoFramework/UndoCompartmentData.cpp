// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoCompartmentData.cpp
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#include <QtCore/QList>

#include "model/CMetab.h"
#include "UndoData.h"
#include "UndoCompartmentData.h"

UndoCompartmentData::UndoCompartmentData()
{
  // TODO Auto-generated constructor stub
}

UndoCompartmentData::~UndoCompartmentData()
{
  // TODO Auto-generated destructor stub
}

QList<UndoData*> *UndoCompartmentData::getDependencyObjects() const
{
  return mDependencyObjects;
}

CModelEntity::Status UndoCompartmentData::getStatus() const
{
  return mStatus;
}

void UndoCompartmentData::setDependencyObjects(QList<UndoData*> *dependencyObjects)
{
  mDependencyObjects = dependencyObjects;
}

void UndoCompartmentData::setStatus(CModelEntity::Status status)
{
  mStatus = status;
}

QList<UndoReactionData*> *UndoCompartmentData::getReactionDependencyObjects() const
{
  return mReactionDependencyObjects;
}

QList<UndoSpecieData*> *UndoCompartmentData::getSpecieDependencyObjects() const
{
  return mSpecieDependencyObjects;
}

void UndoCompartmentData::setReactionDependencyObjects(QList<UndoReactionData*> *reactionDependencyObjects)
{
  mReactionDependencyObjects = reactionDependencyObjects;
}

void UndoCompartmentData::setSpecieDependencyObjects(QList<UndoSpecieData*> *specieDependencyObjects)
{
  mSpecieDependencyObjects = specieDependencyObjects;
}

double UndoCompartmentData::getInitialValue() const
{
  return mInitialValue;
}

void UndoCompartmentData::setInitialValue(double initialValue)
{
  mInitialValue = initialValue;
}

QList<UndoGlobalQuantityData*> *UndoCompartmentData::getGlobalQuantityDependencyObjects() const
{
  return mGlobalQuantityDependencyObjects;
}

void UndoCompartmentData::setGlobalQuantityDependencyObjects(QList<UndoGlobalQuantityData*> *globalQuantityDependencyObjects)
{
  mGlobalQuantityDependencyObjects = globalQuantityDependencyObjects;
}

QList<UndoEventData*> *UndoCompartmentData::getEventDependencyObjects() const
{
  return mEventDependencyObjects;
}

void UndoCompartmentData::setEventDependencyObjects(QList<UndoEventData*> *eventDependencyObjects)
{
  mEventDependencyObjects = eventDependencyObjects;
}
