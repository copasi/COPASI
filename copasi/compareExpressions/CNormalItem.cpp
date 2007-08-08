// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalItem.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/08/08 10:27:29 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "function/CEvaluationTree.h"
#include "function/CEvaluationNode.h"
#include "function/CEvaluationNodeOperator.h"
#include "function/CEvaluationNodeFunction.h"

#include "CNormalItem.h"
#include "CNormalFraction.h"

#include "copasi.h"

/**
 * Default constructor
 */
CNormalItem::CNormalItem(): CNormalBase(), mName("no name")
{}

/**
 * Data constructor
 */
CNormalItem::CNormalItem(const std::string& name, const Type& type): CNormalBase(), mName(name), mType(type)
{}

/**
 * Copy contructor
 */
CNormalItem::CNormalItem(const CNormalItem& src): CNormalBase(src), mName(src.mName), mType(src.mType)
{}

/**
 * Assignment operator
 */
CNormalItem& CNormalItem::operator=(const CNormalItem& src)
{
  this->mName = src.mName;
  this->mType = src.mType;
  return *this;
}

/**
 * Set the name of this item
 * @return true.
 */
bool CNormalItem::setName(const std::string& name)
{
  mName = name;
  return true;
}

/**
 * Set the type of this item.
 * @return true.
 */
bool CNormalItem::setType(const Type& type)
{
  mType = type;
  return true;
}

/**
 * Retrieve the name of this item.
 * @return mName
 */
const std::string CNormalItem::getName() const
  {
    return mName;
  }

/**
 * Retrieve the type of this item.
 * @return mType
 */
const CNormalItem::Type& CNormalItem::getType() const
  {
    return mType;
  }

/**
 * Examine equality of two items.
 * @return bool.
 */
bool CNormalItem::operator==(const CNormalItem & rhs) const
  {return ((rhs.mName == mName) && (rhs.mType == mType));}

/**
 * Examine inequality of two item.
 * @return bool.
 */
bool CNormalItem::operator<(const CNormalItem & rhs) const
  {
    if (mType < rhs.mType)
      return true;
    if (rhs.mType < mType)
      return false;
    return (mName < rhs.mName);
  }

std::string CNormalItem::toString() const
  {
    return this->mName;
  }

std::ostream & operator<< (std::ostream &os, const CNormalItem & d)
{
  os << d.toString();
  return os;
}

CNormalItem* CNormalItem::copy() const
  {
    return new CNormalItem(*this);
  }
