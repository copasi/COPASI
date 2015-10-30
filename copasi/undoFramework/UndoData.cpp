// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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
#include <copasi/UI/qtUtilities.h>
#include <copasi/UI/listviews.h>

#include <copasi/undoFramework/UndoCompartmentData.h>
#include <copasi/undoFramework/UndoSpeciesData.h>
#include <copasi/undoFramework/UndoEventData.h>
#include <copasi/undoFramework/UndoReactionData.h>
#include <copasi/undoFramework/UndoGlobalQuantityData.h>
#include <copasi/undoFramework/UndoDependentData.h>

#include <copasi/model/CModel.h>
#include <copasi/model/CReaction.h>
#include <copasi/model/CReactionInterface.h>

#include <copasi/function/CExpression.h>

UndoData::UndoData(const std::string &key  /*= ""*/,
                   const std::string &name /*= ""*/,
                   const std::string &type /*= ""*/)
  : QObject()
  , mpData(new UndoDependentData())
  , mKey(key)
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

