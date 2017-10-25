// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

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

#include "copasi/copasi.h"

#include "UndoEventData.h"
#include "UndoGlobalQuantityData.h"
#include "UndoDependentData.h"

#include "copasi/model/CModel.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CReactionInterface.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/function/CExpression.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/UI/listviews.h"

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

CDataObject *UndoData::createObjectIn(CModel *)
{
  return NULL;
}

CDataObject *UndoData::restoreObjectIn(CModel *)
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

const CDataObject *UndoData::getObject(const CModel *pModel) const
{
  if (pModel == NULL) return NULL;

  return getObject(pModel->getObjectDataModel());
}

const CDataObject *UndoData::getObject(const CDataModel *pModel) const
{
  if (pModel == NULL) return NULL;

  return dynamic_cast<const CDataObject*>(pModel->getObject(getCN()));
}

CDataObject *UndoData::getObject(CModel *pModel)
{
  if (pModel == NULL) return NULL;

  return getObject(pModel->getObjectDataModel());
}

CDataObject *UndoData::getObject(CDataModel *pDataModel)
{
  if (pDataModel == NULL) return NULL;

  return const_cast< CDataObject * >(CObjectInterface::DataObject(pDataModel->getObject(mCN)));
}
