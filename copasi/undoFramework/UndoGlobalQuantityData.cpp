// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include <copasi/undoFramework/CCopasiUndoCommand.h>
#include <copasi/undoFramework/UndoDependentData.h>

#include <copasi/report/CCopasiRootContainer.h>

UndoGlobalQuantityData::UndoGlobalQuantityData(const std::string &key  /*= ""*/,
    const std::string &name /*= ""*/,
    const std::string &type /*= ""*/)
  : UndoData(key, name, type)
  , mInitialValue()
  , mStatus(CModelEntity::FIXED)
  , mExpression()
  , mInitialExpression()
{
}

UndoGlobalQuantityData::UndoGlobalQuantityData(const CModelValue* pModelValue
    , bool trackDependencies /*= true*/)
  : UndoData(pModelValue->getKey(), pModelValue->getObjectName())
  , mInitialValue(pModelValue->getInitialValue())
  , mStatus(pModelValue->getStatus())
  , mExpression(pModelValue->getExpression())
  , mInitialExpression(pModelValue->getInitialExpression())
{
  if (trackDependencies)
    mpData->initializeFrom(pModelValue);
}

UndoGlobalQuantityData::~UndoGlobalQuantityData()
{
}

CModelValue *
UndoGlobalQuantityData::createObjectIn(CModel *pModel)
{
  if (pModel == NULL) return NULL;

  if (pModel->getModelValues().getIndex(getName()) != C_INVALID_INDEX)
    return NULL;

  createDependentObjects(pModel);

  CModelValue *pGlobalQuantity =  pModel->createModelValue(getName());

  if (pGlobalQuantity == NULL)
    return NULL;

  mKey = pGlobalQuantity->getKey();

  return pGlobalQuantity;
}

CModelValue *
UndoGlobalQuantityData::restoreObjectIn(CModel *pModel)
{
  CModelValue *pGlobalQuantity =  createObjectIn(pModel);

  if (pGlobalQuantity == NULL)
    return NULL;

  fillObject(pModel);
  fillDependentObjects(pModel);

  return pGlobalQuantity;
}

void
UndoGlobalQuantityData::fillObject(CModel *)
{
  CModelValue * pGlobalQuantity =
    dynamic_cast<CModelValue*>(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (pGlobalQuantity == NULL) return;

  pGlobalQuantity->setStatus(getStatus());

  if (getStatus() != CModelEntity::ASSIGNMENT)
    {
      pGlobalQuantity->setInitialValue(getInitialValue());
    }

  if (getStatus() != CModelEntity::FIXED)
    {
      pGlobalQuantity->setExpression(getExpression());
    }

  // set initial expression
  if (getStatus() != CModelEntity::ASSIGNMENT)
    {
      pGlobalQuantity->setInitialExpression(getInitialExpression());
    }
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

const std::string&
UndoGlobalQuantityData::getInitialExpression() const
{
  return mInitialExpression;
}

void
UndoGlobalQuantityData::setInitialExpression(const std::string &initialExpression)
{
  mInitialExpression = initialExpression;
}
