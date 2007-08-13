// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalLogicalItem.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/08/13 07:41:17 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CNormalLogicalItem.h"
#include "CNormalFraction.h"

#include <sstream>

CNormalLogicalItem::CNormalLogicalItem(): CNormalBase(), mType(CNormalLogicalItem::INVALID), mpLeft(new CNormalFraction()), mpRight(new CNormalFraction())
{}

CNormalLogicalItem::CNormalLogicalItem(const CNormalLogicalItem& src): CNormalBase(src), mType(src.mType), mpLeft(new CNormalFraction(*src.mpLeft)), mpRight(new CNormalFraction(*src.mpRight))
{}

CNormalLogicalItem::~CNormalLogicalItem()
{
  if (this->mpLeft != NULL) delete this->mpLeft;
  if (this->mpRight != NULL) delete this->mpRight;
}

CNormalLogicalItem& CNormalLogicalItem::operator=(const CNormalLogicalItem& src)
{
  if (this->mpLeft != NULL) delete this->mpLeft;
  mpLeft = NULL;
  if (this->mpRight != NULL) delete this->mpRight;
  mpRight = NULL;
  this->mType = src.mType;
  if (src.mpLeft != NULL)
    {
      this->mpLeft = new CNormalFraction(*src.mpLeft);
    }
  if (src.mpRight != NULL)
    {
      this->mpRight = new CNormalFraction(*src.mpRight);
    }
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
        if (this->mpLeft == NULL)
          {
            if (rhs.mpLeft != NULL)
              {
                result = true;
              }
            else
              {
                if (this->mpRight == NULL)
                  {
                    if (rhs.mpRight != NULL)
                      {
                        result = true;
                      }
                  }
                else
                  {
                    if (rhs.mpRight != NULL)
                      {
                        result = (*this->mpRight < *rhs.mpRight);
                      }
                  }
              }
          }
        else
          {
            if (rhs.mpLeft != NULL)
              {
                if (*this->mpLeft < *rhs.mpLeft)
                  {
                    result = true;
                  }
                else if (*this->mpLeft == *rhs.mpLeft)
                  {
                    if (this->mpRight == NULL)
                      {
                        if (rhs.mpRight != NULL)
                          {
                            result = true;
                          }
                      }
                    else
                      {
                        if (rhs.mpRight != NULL)
                          {
                            result = (*this->mpRight < *rhs.mpRight);
                          }
                      }
                  }
              }
          }
      }
    return result;
  }

CNormalLogicalItem* CNormalLogicalItem::copy() const
  {
    CNormalLogicalItem* pResult = NULL;
    if ((this->mpLeft != NULL) && (this->mpRight != NULL))
      {
        pResult = new CNormalLogicalItem(*this);
      }
    else
      {
        pResult = new CNormalLogicalItem();
        pResult->mType = this->mType;
        pResult->mpLeft = NULL;
        pResult->mpRight = NULL;
      }
    return pResult;
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
        str << "(";
        if (this->mpLeft != NULL)
          {
            str << this->mpLeft->toString();
          }
        str << " == ";
        if (this->mpRight != NULL)
          {
            str << this->mpRight->toString();
          }
        str << ")";
        break;
      case CNormalLogicalItem::NE:
        str << "(";
        if (this->mpLeft != NULL)
          {
            str << this->mpLeft->toString();
          }
        str << " != ";
        if (this->mpRight != NULL)
          {
            str << this->mpRight->toString();
          }
        str << ")";
        break;
      case CNormalLogicalItem::LT:
        str << "(";
        if (this->mpLeft != NULL)
          {
            str << this->mpLeft->toString();
          }
        str << " < ";
        if (this->mpRight != NULL)
          {
            str << this->mpRight->toString();
          }
        str << ")";
        break;
      case CNormalLogicalItem::GT:
        str << "(";
        if (this->mpLeft != NULL)
          {
            str << this->mpLeft->toString();
          }
        str << " > ";
        if (this->mpRight != NULL)
          {
            str << this->mpRight->toString();
          }
        str << ")";
        break;
      case CNormalLogicalItem::GE:
        str << "(";
        if (this->mpLeft != NULL)
          {
            str << this->mpLeft->toString();
          }
        str << " >= ";
        if (this->mpRight != NULL)
          {
            str << this->mpRight->toString();
          }
        str << ")";
        break;
      case CNormalLogicalItem::LE:
        str << "(";
        if (this->mpLeft != NULL)
          {
            str << this->mpLeft->toString();
          }
        str << " <= ";
        if (this->mpRight != NULL)
          {
            str << this->mpRight->toString();
          }
        str << ")";
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
      CNormalFraction* pTMP = this->mpLeft;
      this->mpLeft = this->mpRight;
      this->mpRight = pTMP;
    }
  else if (this->mType == GE)
    {
      // replace by LE and switch mpLeft and mpRight
      this->mType = LE;
      CNormalFraction* pTMP = this->mpLeft;
      this->mpLeft = this->mpRight;
      this->mpRight = pTMP;
    }
  if (this->mpLeft) result &= this->mpLeft->simplify();
  if (this->mpRight) result &= this->mpRight->simplify();
  return result;
}

CNormalFraction* CNormalLogicalItem::getLeft()
{
  return this->mpLeft;
}

const CNormalFraction* CNormalLogicalItem::getLeft() const
  {
    return this->mpLeft;
  }

CNormalFraction* CNormalLogicalItem::getRight()
{
  return this->mpRight;
}

const CNormalFraction* CNormalLogicalItem::getRight() const
  {
    return this->mpRight;
  }

bool CNormalLogicalItem::setLeft(const CNormalFraction& left)
{
  bool result = false;
  if (this->mType != CNormalLogicalItem::TRUE && this->mType != CNormalLogicalItem::FALSE)
    {
      if (this->mpLeft != NULL) delete this->mpLeft;
      this->mpLeft = new CNormalFraction(left);
    }
  return result;
}

bool CNormalLogicalItem::setRight(const CNormalFraction& right)
{
  bool result = false;
  if (this->mType != CNormalLogicalItem::TRUE && this->mType != CNormalLogicalItem::FALSE)
    {
      if (this->mpRight != NULL) delete this->mpRight;
      this->mpRight = new CNormalFraction(right);
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
      if (this->mpLeft != NULL)
        {
          delete this->mpLeft;
          this->mpLeft = new CNormalFraction();
        }
      if (this->mpRight != NULL)
        {
          delete this->mpRight;
          this->mpRight = new CNormalFraction();
        }
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
        result = ((*this->mpLeft) == (*rhs.mpLeft));
        if (result)
          {
            result = ((*this->mpRight) == (*rhs.mpRight));
          }
      }
    else
      {
        result = false;
      }
    return result;
  }
