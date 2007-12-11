// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalLogicalItem.cpp,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/12/11 20:55:55 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243)
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
#endif  // WIN32

#include <sstream>

#include "CNormalLogicalItem.h"

CNormalLogicalItem::CNormalLogicalItem(): CNormalBase(), mType(CNormalLogicalItem::INVALID)
{}

CNormalLogicalItem::CNormalLogicalItem(const CNormalLogicalItem& src): CNormalBase(src), mType(src.mType), mLeft(src.mLeft), mRight(src.mRight)
{}

CNormalLogicalItem::~CNormalLogicalItem()
{}

CNormalLogicalItem& CNormalLogicalItem::operator=(const CNormalLogicalItem& src)
{
  this->mType = src.mType;
  this->mLeft = src.mLeft;
  this->mRight = src.mRight;
  return *this;
}

bool CNormalLogicalItem::operator<(const CNormalLogicalItem& rhs) const
  {
    bool result = false;
    if (this->mType < rhs.mType)
      {
        result = true;
      }
    else if (this->mType == rhs.mType)
      {
        if (this->mLeft == rhs.mLeft)
          {
            result = (this->mRight < rhs.mRight);
          }
        else
          {
            result = (this->mLeft < rhs.mLeft);
          }
      }
    return result;
  }

CNormalBase * CNormalLogicalItem::copy() const
  {
    return new CNormalLogicalItem(*this);
  }

std::string CNormalLogicalItem::toString() const
  {
    std::ostringstream str;
    switch (this->mType)
      {
      case CNormalLogicalItem::TRUE:
        str << "TRUE";
        break;
      case CNormalLogicalItem::FALSE:
        str << "FALSE";
        break;
      case CNormalLogicalItem::EQ:
        str << "(" << this->mLeft << " == " << this->mRight << ")";
        break;
      case CNormalLogicalItem::NE:
        str << "(" << this->mLeft << " != " << this->mRight << ")";
        break;
      case CNormalLogicalItem::LT:
        str << "(" << this->mLeft << " < " << this->mRight << ")";
        break;
      case CNormalLogicalItem::GT:
        str << "(" << this->mLeft << " > " << this->mRight << ")";
        break;
      case CNormalLogicalItem::GE:
        str << "(" << this->mLeft << " >= " << this->mRight << ")";
        break;
      case CNormalLogicalItem::LE:
        str << "(" << this->mLeft << " <= " << this->mRight << ")";
        break;
      case INVALID:
        break;
      }
    return str.str();
  }

bool CNormalLogicalItem::simplify()
{
  bool result = true;
  if (this->mType == GT)
    {
      // replace by LT and switch mpLeft and mpRight
      this->mType = LT;
      CNormalFraction TMP = this->mLeft;
      this->mLeft = this->mRight;
      this->mRight = TMP;
    }
  else if (this->mType == GE)
    {
      // replace by LE and switch mpLeft and mpRight
      this->mType = LE;
      CNormalFraction TMP = this->mLeft;
      this->mLeft = this->mRight;
      this->mRight = TMP;
    }
  result &= this->mLeft.simplify();
  if (result) result &= this->mRight.simplify();
  return result;
}

CNormalFraction& CNormalLogicalItem::getLeft()
{
  return this->mLeft;
}

const CNormalFraction& CNormalLogicalItem::getLeft() const
  {
    return this->mLeft;
  }

CNormalFraction& CNormalLogicalItem::getRight()
{
  return this->mRight;
}

const CNormalFraction& CNormalLogicalItem::getRight() const
  {
    return this->mRight;
  }

bool CNormalLogicalItem::setLeft(const CNormalFraction& left)
{
  bool result = false;
  if (this->mType != CNormalLogicalItem::TRUE && this->mType != CNormalLogicalItem::FALSE)
    {
      this->mLeft = left;
    }
  return result;
}

bool CNormalLogicalItem::setRight(const CNormalFraction& right)
{
  bool result = false;
  if (this->mType != CNormalLogicalItem::TRUE && this->mType != CNormalLogicalItem::FALSE)
    {
      this->mRight = right;
    }
  return result;
}

CNormalLogicalItem::Type CNormalLogicalItem::getType() const
  {
    return this->mType;
  }

void CNormalLogicalItem::setType(CNormalLogicalItem::Type type)
{
  switch (type)
    {
    case CNormalLogicalItem::TRUE:
    case CNormalLogicalItem::FALSE:
      this->mLeft = CNormalFraction();
      this->mRight = CNormalFraction();
      break;
    default:
      break;
    }
  this->mType = type;
}

std::ostream& operator<<(std::ostream& os, const CNormalLogicalItem& item)
{
  os << item.toString();
  return os;
}

void CNormalLogicalItem::negate()
{
  switch (this->mType)
    {
    case TRUE:
      this->mType = FALSE;
      break;
    case FALSE:
      this->mType = TRUE;
      break;
    case EQ:
      this->mType = NE;
      break;
    case NE:
      this->mType = EQ;
      break;
    case GT:
      this->mType = LE;
      break;
    case LT:
      this->mType = GE;
      break;
    case LE:
      this->mType = GT;
      break;
    case GE:
      this->mType = LT;
      break;
    case INVALID:
      break;
    }
}

bool CNormalLogicalItem::operator==(const CNormalLogicalItem& rhs) const
  {
    bool result = true;
    if (this->mType == rhs.mType)
      {
        result = (this->mLeft == rhs.mLeft);
        if (result)
          {
            result = (this->mRight == rhs.mRight);
          }
      }
    else
      {
        result = false;
      }
    return result;
  }
