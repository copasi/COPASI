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
