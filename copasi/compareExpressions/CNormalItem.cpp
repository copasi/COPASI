// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243)
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
#endif  // WIN32

#include "copasi/copasi.h"

#include "CNormalItem.h"
#include "CNormalFraction.h"

#include "copasi/function/CEvaluationTree.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationNodeOperator.h"
#include "copasi/function/CEvaluationNodeFunction.h"

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

CNormalBase * CNormalItem::copy() const
{
  return new CNormalItem(*this);
}
