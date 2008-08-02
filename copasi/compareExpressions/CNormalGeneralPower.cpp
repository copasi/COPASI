// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalGeneralPower.cpp,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/08/02 14:09:17 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243)
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
#endif  // WIN32

#include <sstream>

#include "CNormalGeneralPower.h"
#include "CNormalFraction.h"
#include "CNormalSum.h"
#include "CNormalProduct.h"

const char* CNormalGeneralPower::SYMBOLS[] = {"^", "%"};

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
    if (this->mType != INVALID)
      {
        // if the exponent is not 1, we have to add parentheses around the left
        // side, otherwise we don't
        // we check the numerator and the denominator separately because if they
        // are both equal bot not 1, we want to display the actual fraction not the
        // canceled fraction
        if (!(this->mpRight->getNumerator().checkIsOne() && this->mpRight->getDenominator().checkIsOne()))
          {
            s << "(" << *this->mpLeft << ")";
            s << CNormalGeneralPower::SYMBOLS[this->mType] << "(" << *this->mpRight << ")";
          }
        else
          {
            // we also have to addd parentesis if the denominator of the left
            // side is 1
            if (this->mpLeft->checkDenominatorOne())
              {
                s << "(" << *this->mpLeft << ")";
              }
            else
              {
                s << *this->mpLeft;
              }
          }
      }
    else
      {
        s << "(!!!INVALID GENERAL POWER!!!)";
      }
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

void CNormalGeneralPower::multiply(const CNormalGeneralPower& generalPower)
{
  // make sure we don't multiply with a general power that is 1
  // this would make the simplification process more complicated.
  if (generalPower.checkIsOne()) return;
  if (this->checkIsOne())
    {
      delete this->mpLeft;
      delete this->mpRight;
      this->mpLeft = new CNormalFraction(*generalPower.mpLeft);
      this->mpRight = new CNormalFraction(*generalPower.mpRight);
    }
  else
    {
      // (A/B)^(C/D)*(E/F)^(G/H) -> // (A^(C/D)*E^(G/H))/(B^(C/D)*F^(G/H))
      // new exponent is 1
      CNormalFraction* pNewExponent = CNormalFraction::createUnitFraction();
      // initialize the new base with 1
      CNormalFraction* pNewBase = CNormalFraction::createUnitFraction();
      // the numerator of the new base is (A^(C/D)*E^(G/H))
      CNormalProduct* pTmpProduct = (*pNewBase->getNumerator().getProducts().begin());
      assert(pTmpProduct != NULL);
      // A^(C/D)
      if (!this->mpLeft->getNumerator().checkIsOne())
        {
          CNormalGeneralPower* pTmpPower = new CNormalGeneralPower();
          pTmpPower->setType(CNormalGeneralPower::POWER);
          CNormalFraction* pTmpFraction = new CNormalFraction(*pNewExponent);
          pTmpFraction->setNumerator(this->mpLeft->getNumerator());
          pTmpPower->setLeft(*pTmpFraction);
          delete pTmpFraction;
          pTmpPower->setRight(*this->mpRight);
          pTmpProduct->multiply(*pTmpPower);
          delete pTmpPower;
        }
      // E^(G/H)
      if (!generalPower.mpLeft->getNumerator().checkIsOne())
        {
          CNormalGeneralPower* pTmpPower = new CNormalGeneralPower();
          pTmpPower->setType(CNormalGeneralPower::POWER);
          CNormalFraction* pTmpFraction = new CNormalFraction(*pNewExponent);
          pTmpFraction->setNumerator(generalPower.mpLeft->getNumerator());
          pTmpPower->setLeft(*pTmpFraction);
          delete pTmpFraction;
          pTmpPower->setRight(*generalPower.mpRight);
          pTmpProduct->multiply(*pTmpPower);
          delete pTmpPower;
        }
      // the denominator of the new base is (B^(C/D)*F^(G/H))
      pTmpProduct = (*pNewBase->getDenominator().getProducts().begin());
      assert(pTmpProduct != NULL);
      // B^(C/D)
      if (!this->mpLeft->getDenominator().checkIsOne())
        {
          CNormalGeneralPower* pTmpPower = new CNormalGeneralPower();
          pTmpPower->setType(CNormalGeneralPower::POWER);
          CNormalFraction* pTmpFraction = new CNormalFraction(*pNewExponent);
          pTmpFraction->setNumerator(this->mpLeft->getDenominator());
          pTmpPower->setLeft(*pTmpFraction);
          delete pTmpFraction;
          pTmpPower->setRight(*this->mpRight);
          pTmpProduct->multiply(*pTmpPower);
          delete pTmpPower;
        }
      // F^(G/H)
      if (!generalPower.mpLeft->getDenominator().checkIsOne())
        {
          CNormalGeneralPower* pTmpPower = new CNormalGeneralPower();
          pTmpPower->setType(CNormalGeneralPower::POWER);
          CNormalFraction* pTmpFraction = new CNormalFraction(*pNewExponent);
          pTmpFraction->setNumerator(generalPower.mpLeft->getDenominator());
          pTmpPower->setLeft(*pTmpFraction);
          delete pTmpFraction;
          pTmpPower->setRight(*generalPower.mpRight);
          pTmpProduct->multiply(*pTmpPower);
          delete pTmpPower;
        }
      delete this->mpRight;
      this->mpRight = pNewExponent;
      delete this->mpLeft;
      this->mpLeft = pNewBase;
    }
}

bool CNormalGeneralPower::checkIsOne() const
  {
    // the general power is one if either the exponent is 0.0
    // or if the base is 1.0
    return (this->mpLeft->checkIsOne() ||
            this->mpRight->checkIsZero());
  }

CNormalGeneralPower* CNormalGeneralPower::createUnitGeneralPower()
{
  CNormalGeneralPower* pGeneralPower = new CNormalGeneralPower();
  pGeneralPower->setType(CNormalGeneralPower::POWER);
  delete pGeneralPower->mpLeft;
  delete pGeneralPower->mpRight;
  pGeneralPower->mpLeft = CNormalFraction::createUnitFraction();
  pGeneralPower->mpRight = CNormalFraction::createUnitFraction();
  return pGeneralPower;
}
