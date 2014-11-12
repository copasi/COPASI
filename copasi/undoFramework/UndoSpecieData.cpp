// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoSpecieData.cpp
 *
 *  Created on: 26 Aug 2014
 *      Author: dada
 */

#include <QtCore/QList>

#include "model/CMetab.h"
#include "UndoSpecieData.h"
#include "UndoReactionData.h"
#include "UndoGlobalQuantityData.h"
#include "UndoEventData.h"

UndoSpecieData::UndoSpecieData()
{
  // TODO Auto-generated constructor stub
}

UndoSpecieData::~UndoSpecieData()
{
  // TODO Auto-generated destructor stub
}

std::string UndoSpecieData::getCompartment() const
{
  return mCompartment;
}

double UndoSpecieData::getIConc() const
{
  return mIConc;
}

void UndoSpecieData::setCompartment(std::string compartment)
{
  mCompartment = compartment;
}

void UndoSpecieData::setIConc(double iConc)
{
  mIConc = iConc;
}

CModelEntity::Status UndoSpecieData::getStatus() const
{
  return mStatus;
}

void UndoSpecieData::setStatus(CModelEntity::Status status)
{
  mStatus = status;
}

const std::string & UndoSpecieData::getExpression() const
{
  return mExpression;
}

const std::string & UndoSpecieData::getInitialExpression() const
{
  return mInitialExpression;
}

void UndoSpecieData::setExpression(const std::string &expression)
{
  mExpression = expression;
}

void UndoSpecieData::setInitialExpression(const std::string &initialExpression)
{
  mInitialExpression = initialExpression;
}

QList<UndoReactionData*> *UndoSpecieData::getReactionDependencyObjects() const
{
  return mReactionDependencyObjects;
}

void UndoSpecieData::setReactionDependencyObjects(QList<UndoReactionData*> *reactionDependencyObjects)
{
  mReactionDependencyObjects = reactionDependencyObjects;
}

double UndoSpecieData::getINumber() const
{
  return mINumber;
}

void UndoSpecieData::setINumber(double iNumber)
{
  mINumber = iNumber;
}

QList<UndoGlobalQuantityData*> *UndoSpecieData::getGlobalQuantityDependencyObjects() const
{
  return mGlobalQuantityDependencyObjects;
}

void UndoSpecieData::setGlobalQuantityDependencyObjects(QList<UndoGlobalQuantityData*> *globalQuantityDependencyObjects)
{
  mGlobalQuantityDependencyObjects = globalQuantityDependencyObjects;
}

QList<UndoEventData*> *UndoSpecieData::getEventDependencyObjects() const
{
  return mEventDependencyObjects;
}

void UndoSpecieData::setEventDependencyObjects(QList<UndoEventData*> *eventDependencyObjects)
{
  mEventDependencyObjects = eventDependencyObjects;
}
