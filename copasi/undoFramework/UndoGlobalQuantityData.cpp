// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

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

#include "copasi/copasi.h"

#include "copasi/model/CModelValue.h"
#include "copasi/model/CModel.h"
#include "copasi/function/CExpression.h"
#include "copasi/core/CRootContainer.h"

#include "UndoGlobalQuantityData.h"
#include "UndoEventData.h"
#include "UndoGlobalQuantityData.h"
#include "CCopasiUndoCommand.h"
#include "UndoDependentData.h"

UndoGlobalQuantityData::UndoGlobalQuantityData(const std::string &key  /*= ""*/,
    const std::string &name /*= ""*/,
    const std::string &type /*= ""*/)
  : UndoData(key, name, type)
  , mInitialValue()
  , mStatus(CModelEntity::Status::FIXED)
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

CDataObject *
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

CDataObject *
UndoGlobalQuantityData::restoreObjectIn(CModel *pModel)
{
  CDataObject *pGlobalQuantity =  createObjectIn(pModel);

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
    dynamic_cast<CModelValue*>(CRootContainer::getKeyFactory()->get(mKey));

  if (pGlobalQuantity == NULL) return;

  pGlobalQuantity->setStatus(getStatus());

  if (getStatus() != CModelEntity::Status::ASSIGNMENT)
    {
      pGlobalQuantity->setInitialValue(getInitialValue());
    }

  if (getStatus() != CModelEntity::Status::FIXED)
    {
      pGlobalQuantity->setExpression(getExpression());
    }

  // set initial expression
  if (getStatus() != CModelEntity::Status::ASSIGNMENT)
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
