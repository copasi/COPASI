// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
#include "model/CCompartment.h"

#include <copasi/model/CModel.h>
#include <copasi/function/CExpression.h>

#include "UndoSpeciesData.h"
#include "UndoReactionData.h"
#include "UndoGlobalQuantityData.h"
#include "UndoEventData.h"

#include <copasi/undoFramework/CCopasiUndoCommand.h>
#include <copasi/undoFramework/UndoDependentData.h>

#include <copasi/report/CCopasiRootContainer.h>

UndoSpeciesData::UndoSpeciesData(const CMetab *metab
                                 , bool trackDependencies /*= true*/)
  : UndoData(metab->getKey(), metab->getObjectName())
  , mIConc(metab->getInitialConcentration())
  , mINumber(metab->getInitialValue())
  , mCompartment(metab->getCompartment()->getObjectName())
  , mStatus(metab->getStatus())
  , mInitialExpression(metab->getInitialExpression())
  , mExpression(metab->getExpression())
  , mCreatedCompartment(false)
{
  setCN(metab->getCN());

  mIndex = metab->getModel()->getMetabolites().getIndex(metab);

  if (trackDependencies)
    mpData->initializeFrom(metab);
}

UndoSpeciesData::~UndoSpeciesData()
{
}

CMetab *
UndoSpeciesData::createObjectIn(CModel *pModel)
{
  if (pModel == NULL)
    return NULL;

  createDependentObjects(pModel);

  if (pModel->getCompartments().getIndex(mCompartment) == C_INVALID_INDEX)
    return NULL;

  CCompartment * pCompartment = &pModel->getCompartments()[getCompartment()];

  if (pCompartment == NULL)
    return NULL;

  if (pCompartment->getMetabolites().getIndex(getName()) != C_INVALID_INDEX)
    return NULL;

  CMetab *pSpecies =  pModel->createMetabolite(getName(), getCompartment(), getIConc(), getStatus());

  if (pSpecies == NULL)
    return NULL;

  mKey = pSpecies->getKey();

  return pSpecies;
}

CMetab *
UndoSpeciesData::restoreObjectIn(CModel *pModel)
{
  CMetab *pSpecies = createObjectIn(pModel);

  if (pSpecies == NULL)
    return NULL;

  fillObject(pModel);
  fillDependentObjects(pModel);

  return pSpecies;
}

void
UndoSpeciesData::fillObject(CModel *)
{
  CMetab * pSpecies =
    dynamic_cast<CMetab*>(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (pSpecies == NULL) return;

  if (getStatus() != CModelEntity::ASSIGNMENT)
    {
      pSpecies->setInitialConcentration(getIConc());
      pSpecies->setInitialValue(getINumber());
    }

  if (getStatus() == CModelEntity::ODE || getStatus() == CModelEntity::ASSIGNMENT)
    {
      pSpecies->setExpression(getExpression());
    }

  // set initial expression
  if (getStatus() != CModelEntity::ASSIGNMENT)
    {
      pSpecies->setInitialExpression(getInitialExpression());
    }
}

void UndoSpeciesData::createDependentObjects(CModel *pModel)
{
  UndoData::createDependentObjects(pModel);

  if (mCreatedCompartment)
    {
      pModel->createCompartment(mCompartment);
    }
}

const std::string&
UndoSpeciesData::getCompartment() const
{
  return mCompartment;
}

double
UndoSpeciesData::getIConc() const
{
  return mIConc;
}

void
UndoSpeciesData::setCompartment(const std::string& compartment)
{
  mCompartment = compartment;
}

void
UndoSpeciesData::setIConc(double iConc)
{
  mIConc = iConc;
}

CModelEntity::Status
UndoSpeciesData::getStatus() const
{
  return mStatus;
}

void
UndoSpeciesData::setStatus(CModelEntity::Status status)
{
  mStatus = status;
}

const std::string &
UndoSpeciesData::getExpression() const
{
  return mExpression;
}

const std::string &
UndoSpeciesData::getInitialExpression() const
{
  return mInitialExpression;
}

void
UndoSpeciesData::setExpression(const std::string &expression)
{
  mExpression = expression;
}

void
UndoSpeciesData::setInitialExpression(
  const std::string &initialExpression)
{
  mInitialExpression = initialExpression;
}

double
UndoSpeciesData::getINumber() const
{
  return mINumber;
}

void
UndoSpeciesData::setINumber(double iNumber)
{
  mINumber = iNumber;
}

bool UndoSpeciesData::getCreatedCompartment() const
{
  return mCreatedCompartment;
}

void UndoSpeciesData::setCreatedCompartment(bool createdCompartment)
{
  mCreatedCompartment = createdCompartment;
}

CCopasiObject *UndoSpeciesData::getObject(CModel *pModel)
{
  CCopasiObject *result = UndoData::getObject(pModel);

  if (result == NULL && mIndex < pModel->getNumMetabs())
    return &pModel->getMetabolites()[mIndex];

  return result;
}
