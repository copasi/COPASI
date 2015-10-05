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

UndoData::UndoData(const std::string &key  /*= ""*/,
                   const std::string &name /*= ""*/,
                   const std::string &type /*= ""*/)
  : QObject()
  , mKey(key)
  , mName(name)
  , mType(type)
{
}

UndoData::~UndoData()
{
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

