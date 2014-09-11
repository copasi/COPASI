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

UndoGlobalQuantityData::UndoGlobalQuantityData() {
	// TODO Auto-generated constructor stub

}

QList<UndoReactionData*> UndoGlobalQuantityData::getDependencyObjects() const
{
	return mDependencyObjects;
}

double UndoGlobalQuantityData::getInitialValue() const
{
	return mInitialValue;
}

CModelEntity::Status UndoGlobalQuantityData::getStatus() const
{
	return mStatus;
}

void UndoGlobalQuantityData::setDependencyObjects(QList<UndoReactionData*> dependencyObjects)
{
	mDependencyObjects = dependencyObjects;
}

void UndoGlobalQuantityData::setInitialValue(double initialValue)
{
	mInitialValue = initialValue;
}

void UndoGlobalQuantityData::setStatus(CModelEntity::Status status)
{
	mStatus = status;
}

UndoGlobalQuantityData::~UndoGlobalQuantityData() {
	// TODO Auto-generated destructor stub
}

