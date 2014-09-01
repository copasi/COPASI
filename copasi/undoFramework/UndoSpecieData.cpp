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

UndoSpecieData::UndoSpecieData() {
	// TODO Auto-generated constructor stub

}

UndoSpecieData::~UndoSpecieData() {
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

CMetab *UndoSpecieData::getSpecie() const
{
    return mpSpecie;
}

void UndoSpecieData::setSpecie(CMetab *mpSpecie)
{
    this->mpSpecie = mpSpecie;
}

CModelEntity::Status UndoSpecieData::getStatus() const
{
    return mStatus;
}

void UndoSpecieData::setStatus(CModelEntity::Status status)
{
    mStatus = status;
}

QList<UndoReactionData*> UndoSpecieData::getDependencyObjects() const
{
    return mDependencyObjects;
}

void UndoSpecieData::setDependencyObjects(QList<UndoReactionData*> dependencyObjects)
{
    mDependencyObjects = dependencyObjects;
}










