// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
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

UndoSpeciesData::UndoSpeciesData(const std::string &key  /*= ""*/,
                                 const std::string &name /*= ""*/,
                                 const std::string &type /*= ""*/)
  : UndoData(key, name, type)
  , mIConc(0)
  , mINumber(0)
  , mCompartment()
  , mStatus(CModelEntity::REACTIONS)
  , mInitialExpression()
  , mExpression()
  , mReactionDependencyObjects(new QList <UndoReactionData*>())
  , mGlobalQuantityDependencyObjects(new QList <UndoGlobalQuantityData*>())
  , mEventDependencyObjects(new QList <UndoEventData*>())
{
}

UndoSpeciesData::UndoSpeciesData(const CMetab *metab)
  : UndoData(metab->getKey(), metab->getObjectName())
  , mIConc(metab->getInitialConcentration())
  , mINumber(metab->getInitialValue())
  , mCompartment(metab->getCompartment()->getObjectName())
  , mStatus(metab->getStatus())
  , mInitialExpression(metab->getInitialExpression())
  , mExpression(metab->getExpression())
  , mReactionDependencyObjects(new QList <UndoReactionData*>())
  , mGlobalQuantityDependencyObjects(new QList <UndoGlobalQuantityData*>())
  , mEventDependencyObjects(new QList <UndoEventData*>())
{
  CCopasiUndoCommand::setDependentObjects(
    metab->getDeletedObjects(),
    mReactionDependencyObjects,
    NULL,
    mGlobalQuantityDependencyObjects,
    mEventDependencyObjects);
}

UndoSpeciesData::~UndoSpeciesData()
{
  pdelete(mEventDependencyObjects);
  pdelete(mReactionDependencyObjects);
  pdelete(mGlobalQuantityDependencyObjects);
}

CMetab *UndoSpeciesData::createMetabFromData(CModel *pModel)
{
  if (pModel == NULL)
    return NULL;

  if (pModel->getCompartments().getIndex(mCompartment) == C_INVALID_INDEX)
    return NULL;

  CCompartment * pCompartment = pModel->getCompartments()[getCompartment()];

  if (pCompartment == NULL)
    return NULL;

  if (pCompartment->getMetabolites().getIndex(getName()) != C_INVALID_INDEX)
    return NULL;

  CMetab *pSpecies =  pModel->createMetabolite(getName(), getCompartment(), getIConc(), getStatus());

  if (pSpecies == NULL)
    return NULL;

  if (getStatus() != CModelEntity::ASSIGNMENT)
    {
      pSpecies->setInitialConcentration(getIConc());
    }

  if (getStatus() == CModelEntity::ODE || getStatus() == CModelEntity::ASSIGNMENT)
    {
      pSpecies->setExpression(getExpression());
      pSpecies->getExpressionPtr()->compile();
    }

  // set initial expression
  if (getStatus() != CModelEntity::ASSIGNMENT)
    {
      pSpecies->setInitialExpression(getInitialExpression());
      pSpecies->getInitialExpressionPtr()->compile();
    }

  return pSpecies;
}

void UndoSpeciesData::restoreDependentObjects(CModel* pModel)
{
  UndoData::restoreDependentObjects(pModel, getGlobalQuantityDependencyObjects());
  UndoData::restoreDependentObjects(pModel, getReactionDependencyObjects());
  UndoData::restoreDependentObjects(pModel, getEventDependencyObjects());
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

QList<UndoReactionData*> *
UndoSpeciesData::getReactionDependencyObjects() const
{
  return mReactionDependencyObjects;
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

QList<UndoGlobalQuantityData*> *
UndoSpeciesData::getGlobalQuantityDependencyObjects() const
{
  return mGlobalQuantityDependencyObjects;
}

QList<UndoEventData*> *
UndoSpeciesData::getEventDependencyObjects() const
{
  return mEventDependencyObjects;
}
