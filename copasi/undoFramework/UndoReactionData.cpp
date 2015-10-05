// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoReactionData.cpp
 *
 *  Created on: 15 Aug 2014
 *      Author: dada
 */

#include <QtCore/QList>

#include "model/CMetab.h"
#include "UndoSpeciesData.h"
#include "UndoReactionData.h"

UndoReactionData::UndoReactionData(const std::string &key  /*= ""*/,
                                   const std::string &name /*= ""*/,
                                   const std::string &type /*= ""*/)
  : UndoData(key, name, type)
  , mpRi(NULL)
  , mSpeciesDependencyObjects(new QList <UndoSpeciesData*>())
{
}

UndoReactionData::~UndoReactionData()
{
  pdelete(mSpeciesDependencyObjects);
}

CReactionInterface *UndoReactionData::getRi() const
{
  return mpRi;
}

void UndoReactionData::setRi(CReactionInterface *pRi)
{
  mpRi = pRi;
}

QList<UndoSpeciesData*> *UndoReactionData::getSpeciesDependencyObjects() const
{
  return mSpeciesDependencyObjects;
}
