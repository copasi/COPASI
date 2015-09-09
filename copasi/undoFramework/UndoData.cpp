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

UndoData::UndoData()
{

}

UndoData::~UndoData()
{

}

std::string UndoData::getName() const
{
  return mName;
}

void UndoData::setName(std::string name)
{
  mName = name;
}

std::string UndoData::getType() const
{
  return mType;
}

void UndoData::setType(std::string type)
{
  mType = type;
}
