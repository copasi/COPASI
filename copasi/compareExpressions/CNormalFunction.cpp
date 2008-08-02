// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalFunction.cpp,v $
//   $Revision: 1.5 $
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

#include "CNormalFunction.h"
#include "CNormalFraction.h"

const char* CNormalFunction::NAMES[] =
  {"LOG",
   "LOG10",
   "EXP",
   "SIN",
   "COS",
   "TAN",
   "SEC",
   "CSC",
   "COT",
   "SIN",
   "COS",
   "TAN",
   "SEC",
   "CSC",
   "COT",
   "ARCSIN",
   "ARCCOS",
   "ARCTAN",
   "ARCSEC",
   "ARCCSC",
   "ARCCOT",
   "ARCSINH",
   "ARCCOSH",
   "ARCTANH",
   "ARCSECH",
   "ARCCSCH",
   "ARCCOTH",
   "SQRT",
   "ABS",
   "FLOOR",
   "CEIL",
   "FACTORIAL"
  };

CNormalFunction::CNormalFunction(): CNormalBase(), mType(CNormalFunction::INVALID), mpFraction(NULL)
{}

CNormalFunction::CNormalFunction(const CNormalFunction& src): CNormalBase(src), mType(src.getType()), mpFraction(new CNormalFraction(src.getFraction()))
{}

CNormalFunction::~CNormalFunction()
{
  if (this->mpFraction != NULL) delete mpFraction;
}

CNormalFunction& CNormalFunction::operator=(const CNormalFunction& src)
{
  if (this->mpFraction != NULL) delete this->mpFraction;
  this->mpFraction = new CNormalFraction(src.getFraction());
  this->mType = src.getType();
  return *this;
}

std::string CNormalFunction::toString() const
  {
    std::ostringstream s;
    if (this->mType != INVALID && this->mpFraction != NULL)
      {
        s << CNormalFunction::NAMES[this->mType] << "(" << *this->mpFraction << ")";
      }
    return s.str();
  }

CNormalFunction::Type CNormalFunction::getType() const
  {
    return this->mType;
  }

void CNormalFunction::setType(CNormalFunction::Type type)
{
  this->mType = type;
}

CNormalFraction& CNormalFunction::getFraction()
{
  return *mpFraction;
}

const CNormalFraction& CNormalFunction::getFraction() const
  {
    return *mpFraction;
  }

void CNormalFunction::setFraction(const CNormalFraction& frac)
{
  if (this->mpFraction != NULL) delete this->mpFraction;
  this->mpFraction = new CNormalFraction(frac);
}

std::ostream& operator<<(std::ostream& os, const CNormalFunction& fun)
{
  os << fun.toString();
  return os;
}

bool CNormalFunction::operator==(const CNormalFunction& rhs) const
  {
    return ((this->mType == rhs.mType) && (*this->mpFraction) == (*rhs.mpFraction));
  }

bool CNormalFunction::operator<(const CNormalFunction& rhs) const
  {
    bool result = false;
    if (this->mType < rhs.mType)
      {
        result = true;
      }
    else if (this->mType == rhs.mType)
      {
        result = (*this->mpFraction) < (*rhs.mpFraction);
      }
    return result;
  }

bool CNormalFunction::simplify()
{
  bool result = true;
  if (this->mpFraction != NULL) result = this->mpFraction->simplify();
  return result;
}

CNormalBase * CNormalFunction::copy() const
  {
    return new CNormalFunction(*this);
  }
