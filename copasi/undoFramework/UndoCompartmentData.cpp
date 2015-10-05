// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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

#include "CCopasiUndoCommand.h"
#include "UndoData.h"
#include "UndoCompartmentData.h"

UndoCompartmentData::UndoCompartmentData()
  : UndoData()
  , mInitialValue()
  , mInitialExpression()
  , mExpression()
  , mStatus()
  , mDependencyObjects(new QList<UndoData*>())
  , mSpecieDependencyObjects(new QList<UndoSpeciesData*>())
  , mReactionDependencyObjects(new QList<UndoReactionData*>())
  , mGlobalQuantityDependencyObjects(new QList<UndoGlobalQuantityData*>())
  , mEventDependencyObjects(new QList<UndoEventData*>())
{

}

UndoCompartmentData::UndoCompartmentData(CCompartment *compartment)
  : UndoData(compartment->getKey(), compartment->getObjectName())
  , mInitialValue(compartment->getInitialValue())
  , mInitialExpression(compartment->getInitialExpression())
  , mExpression(compartment->getExpression())
  , mStatus(compartment->getStatus())
  , mDependencyObjects(new QList<UndoData*>())
  , mSpecieDependencyObjects(new QList<UndoSpeciesData*>())
  , mReactionDependencyObjects(new QList<UndoReactionData*>())
  , mGlobalQuantityDependencyObjects(new QList<UndoGlobalQuantityData*>())
  , mEventDependencyObjects(new QList<UndoEventData*>())
{
  CCopasiUndoCommand::setDependentObjects(
    compartment->getDeletedObjects(),
    mReactionDependencyObjects,
    mSpecieDependencyObjects,
    mGlobalQuantityDependencyObjects,
    mEventDependencyObjects);
}

UndoCompartmentData::~UndoCompartmentData()
{
  pdelete(mDependencyObjects);
  pdelete(mSpecieDependencyObjects);
  pdelete(mReactionDependencyObjects);
  pdelete(mGlobalQuantityDependencyObjects);
  pdelete(mEventDependencyObjects);

}

QList<UndoData*> *
UndoCompartmentData::getDependencyObjects() const
{
  return mDependencyObjects;
}

CModelEntity::Status
UndoCompartmentData::getStatus() const
{
  return mStatus;
}

void
UndoCompartmentData::setDependencyObjects(QList<UndoData*> *dependencyObjects)
{
  pdelete(mDependencyObjects);
  mDependencyObjects = dependencyObjects;
}

void
UndoCompartmentData::setStatus(CModelEntity::Status status)
{
  mStatus = status;
}

QList<UndoReactionData*> *
UndoCompartmentData::getReactionDependencyObjects() const
{
  return mReactionDependencyObjects;
}

QList<UndoSpeciesData*> *
UndoCompartmentData::getSpecieDependencyObjects() const
{
  return mSpecieDependencyObjects;
}

double
UndoCompartmentData::getInitialValue() const
{
  return mInitialValue;
}

void
UndoCompartmentData::setInitialValue(double initialValue)
{
  mInitialValue = initialValue;
}

QList<UndoGlobalQuantityData*> *
UndoCompartmentData::getGlobalQuantityDependencyObjects() const
{
  return mGlobalQuantityDependencyObjects;
}

QList<UndoEventData*> *
UndoCompartmentData::getEventDependencyObjects() const
{
  return mEventDependencyObjects;
}

const std::string&
UndoCompartmentData::getInitialExpression() const
{
  return mInitialExpression;
}

void UndoCompartmentData::setInitialExpression(const std::string &initialExpression)
{
  mInitialExpression = initialExpression;
}

const std::string& UndoCompartmentData::getExpression() const
{
  return mExpression;
}

void UndoCompartmentData::setExpression(const std::string &expression)
{
  mExpression = expression;
}


