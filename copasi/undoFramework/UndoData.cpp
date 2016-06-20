// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoData.cpp
 *
 *  Created on: 15 Aug 2014
 *      Author: dada
 */

#include "UndoData.h"

#include <copasi/undoFramework/UndoCompartmentData.h>
#include <copasi/undoFramework/UndoSpeciesData.h>
#include <copasi/undoFramework/UndoEventData.h>
#include <copasi/undoFramework/UndoReactionData.h>
#include <copasi/undoFramework/UndoGlobalQuantityData.h>
#include <copasi/undoFramework/UndoDependentData.h>

#include <copasi/model/CModel.h>
#include <copasi/model/CReaction.h>
#include <copasi/model/CReactionInterface.h>

#include <copasi/CopasiDataModel/CCopasiDataModel.h>

#include <copasi/function/CExpression.h>

#include <copasi/report/CCopasiRootContainer.h>

#include <copasi/UI/qtUtilities.h>
#include <copasi/UI/listviews.h>

UndoData::UndoData(const std::string &key  /*= ""*/,
                   const std::string &name /*= ""*/,
                   const std::string &type /*= ""*/,
                   const std::string &cn /*= ""*/)
  : QObject()
  , mpData(new UndoDependentData())
  , mKey(key)
  , mCN(cn)
  , mName(name)
  , mType(type)
{
}

UndoData::~UndoData()
{
}

CCopasiObject *UndoData::createObjectIn(CModel *)
{
  return NULL;
}

CCopasiObject *UndoData::restoreObjectIn(CModel *)
{
  return NULL;
}

void UndoData::fillObject(CModel *)
{

}

void UndoData::restoreDependentObjects(CModel* pModel)
{
  mpData->restoreIn(pModel);
}

void UndoData::createDependentObjects(CModel *pModel)
{
  mpData->createIn(pModel);
}

void UndoData::fillDependentObjects(CModel *pModel)
{
  mpData->fillIn(pModel);
}

const std::string &
UndoData::getName() const
{
  return mName;
}

void
UndoData::setName(const std::string &name)
{
  mName = name;
}

bool UndoData::hasName() const
{
  return mName.empty();
}

const std::string &
UndoData::getType() const
{
  return mType;
}

void UndoData::setType(const std::string &type)
{
  mType = type;
}

const std::string &
UndoData::getKey() const
{
  return mKey;
}

void
UndoData::setKey(const std::string &key)
{
  mKey = key;
}

bool
UndoData::hasKey() const
{
  return mKey.empty();
}

const std::string &
UndoData::getCN() const
{
  return mCN;
}

void
UndoData::setCN(const std::string &cn)
{
  mCN = cn;
}


bool
UndoData::hasCN() const
{
  return mCN.empty();
}

const CCopasiObject *UndoData::getObject() const
{
  GET_MODEL_OR(pModel, return NULL);
  return getObject(pModel);
}

const CCopasiObject *UndoData::getObject(const CModel *pModel) const
{
  if (pModel == NULL) return NULL;

  return getObject(pModel->getObjectDataModel());
}

const CCopasiObject *UndoData::getObject(const CCopasiDataModel *pModel) const
{
  if (pModel == NULL) return NULL;

  return dynamic_cast<const CCopasiObject*>(pModel->getObject(getCN()));
}

CCopasiObject *UndoData::getObject()
{
  GET_MODEL_OR(pModel, return NULL);
  return getObject(pModel);
}

CCopasiObject *UndoData::getObject(CModel *pModel)
{
  if (pModel == NULL) return NULL;

  return getObject(pModel->getObjectDataModel());
}

CCopasiObject *UndoData::getObject(CCopasiDataModel *pModel)
{
  if (pModel == NULL) return NULL;

  return const_cast<CCopasiObject*>(
           dynamic_cast<const CCopasiObject*>(pModel->getObject(getCN())));
}
