// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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
#include "UndoSpecieData.h"
#include "UndoReactionData.h"

UndoReactionData::UndoReactionData()
{
  // TODO Auto-generated constructor stub
}

UndoReactionData::~UndoReactionData()
{
  // TODO Auto-generated destructor stub
}

CReactionInterface *UndoReactionData::getRi() const
{
  return mpRi;
}

void UndoReactionData::setRi(CReactionInterface *mpRi)
{
  this->mpRi = mpRi;
}

QList<UndoSpecieData*> *UndoReactionData::getSpecieDependencyObjects() const
{
  return mSpecieDependencyObjects;
}

void UndoReactionData::setSpecieDependencyObjects(QList<UndoSpecieData*> *specieDependencyObjects)
{
  mSpecieDependencyObjects = specieDependencyObjects;
}
