// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include <copasi/model/CModel.h>
#include <copasi/model/CMetab.h>
#include <copasi/model/CCompartment.h>

#include <copasi/function/CExpression.h>

#include <copasi/undoFramework/CCopasiUndoCommand.h>
#include <copasi/undoFramework/UndoData.h>
#include <copasi/undoFramework/UndoDependentData.h>
#include <copasi/undoFramework/UndoCompartmentData.h>

#include <copasi/report/CCopasiRootContainer.h>

UndoCompartmentData::UndoCompartmentData()
  : UndoData()
  , mInitialValue()
  , mInitialExpression()
  , mExpression()
  , mStatus()
{
}

UndoCompartmentData::UndoCompartmentData(const CCompartment *compartment,
    bool trackDependencies /*= true*/)
  : UndoData(compartment->getKey(), compartment->getObjectName())
  , mInitialValue(compartment->getInitialValue())
  , mInitialExpression(compartment->getInitialExpression())
  , mExpression(compartment->getExpression())
  , mStatus(compartment->getStatus())
{
  if (trackDependencies)
    mpData->initializeFrom(compartment);
}

UndoCompartmentData::~UndoCompartmentData()
{
}

CCompartment *
UndoCompartmentData::createObjectIn(CModel *pModel)
{
  if (pModel == NULL) return NULL;

  CCompartment *pCompartment = pModel->createCompartment(mName);

  if (pCompartment == NULL)
    return NULL;

  createDependentObjects(pModel);

  mKey = pCompartment->getKey();

  return pCompartment;
}

CCompartment *
UndoCompartmentData::restoreObjectIn(CModel *pModel)
{
  CCompartment *pCompartment = createObjectIn(pModel);

  if (pCompartment == NULL)
    return NULL;

  fillObject(pModel);
  fillDependentObjects(pModel);

  return pCompartment;
}

void UndoCompartmentData::fillObject(CModel *)
{
  CCompartment* pCompartment = dynamic_cast<CCompartment*>(
                                 CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (pCompartment == NULL) return;

  pCompartment->setInitialValue(getInitialValue());
  pCompartment->setStatus(getStatus());

  if (getStatus() == CModelEntity::ODE || getStatus() == CModelEntity::ASSIGNMENT)
    {
      pCompartment->setExpression(getExpression());
    }

  // set initial expression
  if (getStatus() != CModelEntity::ASSIGNMENT)
    {
      pCompartment->setInitialExpression(getInitialExpression());
    }
}

CModelEntity::Status
UndoCompartmentData::getStatus() const
{
  return mStatus;
}

void
UndoCompartmentData::setStatus(CModelEntity::Status status)
{
  mStatus = status;
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
