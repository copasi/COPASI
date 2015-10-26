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
#include "model/CModel.h"
#include "function/CExpression.h"

#include "UndoGlobalQuantityData.h"
#include "UndoReactionData.h"
#include "UndoEventData.h"
#include "UndoSpeciesData.h"

#include "UndoGlobalQuantityData.h"

UndoGlobalQuantityData::UndoGlobalQuantityData(const std::string &key  /*= ""*/,
    const std::string &name /*= ""*/,
    const std::string &type /*= ""*/)
  : UndoData(key, name, type)
  , mInitialValue()
  , mStatus(CModelEntity::FIXED)
  , mExpression()
  , mInitialExpression()
  , mSpecieDependencyObjects(new QList<UndoSpeciesData*>())
  , mReactionDependencyObjects(new QList<UndoReactionData*>())
  , mEventDependencyObjects(new QList<UndoEventData*>())
{
}

UndoGlobalQuantityData::UndoGlobalQuantityData(const CModelValue* pModelValue)
  : UndoData(pModelValue->getKey(), pModelValue->getObjectName())
  , mInitialValue(pModelValue->getInitialValue())
  , mStatus(pModelValue->getStatus())
  , mExpression(pModelValue->getExpression())
  , mInitialExpression(pModelValue->getInitialExpression())
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

CModelValue*
UndoGlobalQuantityData::createQuantityFromData(CModel* pModel)
{
  if (pModel == NULL) return NULL;

  if (pModel->getModelValues().getIndex(getName()) != C_INVALID_INDEX)
    return NULL;


  CModelValue *pGlobalQuantity =  pModel->createModelValue(getName()); //, gData->getInitialValue());

  if (pGlobalQuantity == NULL)
    return NULL;


  pGlobalQuantity->setStatus(getStatus());

  if (getStatus() != CModelEntity::ASSIGNMENT)
    {
      pGlobalQuantity->setInitialValue(getInitialValue());
    }

  if (getStatus() != CModelEntity::FIXED)
    {
      pGlobalQuantity->setExpression(getExpression());
      pGlobalQuantity->getExpressionPtr()->compile();
    }

  // set initial expression
  if (getStatus() != CModelEntity::ASSIGNMENT)
    {
      pGlobalQuantity->setInitialExpression(getInitialExpression());
      pGlobalQuantity->getInitialExpressionPtr()->compile();
    }

  return pGlobalQuantity;
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

const std::string & UndoGlobalQuantityData::getInitialExpression() const
{
  return mInitialExpression;
}

void UndoGlobalQuantityData::setInitialExpression(const std::string &initialExpression)
{
  mInitialExpression = initialExpression;
}

void UndoGlobalQuantityData::restoreDependentObjects(CModel *pModel)
{
  if (pModel == NULL)
    return;

  UndoData::restoreDependentObjects(pModel, getSpecieDependencyObjects());
  UndoData::restoreDependentObjects(pModel, getReactionDependencyObjects());
  UndoData::restoreDependentObjects(pModel, getEventDependencyObjects());
}

QList<UndoEventData*> *UndoGlobalQuantityData::getEventDependencyObjects() const
{
  return mEventDependencyObjects;
}

QList<UndoSpeciesData*> *UndoGlobalQuantityData::getSpecieDependencyObjects() const
{
  return mSpecieDependencyObjects;
}
