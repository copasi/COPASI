// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalGeneralPower.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/09/24 15:36:37 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CNormalGeneralPower.h"
#include "CNormalFraction.h"

#include <sstream>

char* CNormalGeneralPower::SYMBOLS[] = {"^", "%"};

CNormalGeneralPower::CNormalGeneralPower(): CNormalBase(), mType(CNormalGeneralPower::INVALID), mpLeft(NULL), mpRight(NULL)
{}

CNormalGeneralPower::CNormalGeneralPower(const CNormalGeneralPower& src): CNormalBase(src), mType(src.getType()), mpLeft(new CNormalFraction(src.getLeft())), mpRight(new CNormalFraction(src.getRight()))
{}

CNormalGeneralPower::~CNormalGeneralPower()
{
  if (this->mpLeft != NULL) delete this->mpLeft;
  if (this->mpRight != NULL) delete this->mpRight;
}

CNormalGeneralPower& CNormalGeneralPower::operator=(const CNormalGeneralPower& src)
{
  if (this->mpLeft != NULL) delete this->mpLeft;
  if (this->mpRight != NULL) delete this->mpRight;
  this->mType = src.getType();
  this->mpLeft = new CNormalFraction(src.getLeft());
  this->mpRight = new CNormalFraction(src.getRight());
  return *this;
}

std::string CNormalGeneralPower::toString() const
  {
    std::ostringstream s;
    s << "(" << this->mpLeft->toString() << ")" << CNormalGeneralPower::SYMBOLS[this->mType] << "(" << this->mpRight->toString() << ")";
    return s.str();
  }

CNormalFraction& CNormalGeneralPower::getLeft()
{
  return *this->mpLeft;
}

const CNormalFraction& CNormalGeneralPower::getLeft() const
  {
    return *this->mpLeft;
  }

void CNormalGeneralPower::setLeft(const CNormalFraction& left)
{
  if (this->mpLeft != NULL) delete this->mpLeft;
  this->mpLeft = new CNormalFraction(left);
}

CNormalFraction& CNormalGeneralPower::getRight()
{
  return *this->mpRight;
}

const CNormalFraction& CNormalGeneralPower::getRight() const
  {
    return *this->mpRight;
  }

void CNormalGeneralPower::setRight(const CNormalFraction& right)
{
  if (this->mpRight != NULL) delete this->mpRight;
  this->mpRight = new CNormalFraction(right);
}

CNormalGeneralPower::Type CNormalGeneralPower::getType() const
  {
    return this->mType;
  }

void CNormalGeneralPower::setType(CNormalGeneralPower::Type type)
{
  this->mType = type;
}

std::ostream& operator<<(std::ostream& os, const CNormalGeneralPower& pow)
{
  os << pow.toString();
  return os;
}

bool CNormalGeneralPower::operator==(const CNormalGeneralPower& rhs) const
  {
    return ((this->mType == rhs.mType) && (*this->mpLeft) == (*rhs.mpLeft) && (*this->mpRight) == (*rhs.mpRight));
  }

bool CNormalGeneralPower::operator<(const CNormalGeneralPower& rhs) const
  {
    bool result = false;
    if (this->mType < rhs.mType)
      {
        result = true;
      }
    else if (this->mType == rhs.mType)
      {
        if ((*this->mpLeft) < (*rhs.mpLeft))
          {
            result = true;
          }
        else if ((*this->mpLeft) == (*rhs.mpLeft))
          {
            result = ((*this->mpRight) < (*rhs.mpRight));
          }
      }
    return result;
  }

bool CNormalGeneralPower::simplify()
{
  bool result = true;
  if (this->mpLeft != NULL && this->mpRight != NULL)
    {
      result = (this->mpLeft->simplify() && this->mpRight->simplify());
    }
  return result;
}

CNormalBase * CNormalGeneralPower::copy() const
  {
    return new CNormalGeneralPower(*this);
  }
