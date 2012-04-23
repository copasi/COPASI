// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLRelAbsVector.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/04/23 15:44:51 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <iostream>
#include <sstream>
#include <limits>
#include <cmath>
#include <string.h>
#include <stdlib.h>

#include <sbml/packages/render/sbml/RelAbsVector.h>

#include "CLRelAbsVector.h"


/**
 * Constructor with two values.
 * First value sets the absolute value, econd sets the relative value.
 */
CLRelAbsVector::CLRelAbsVector(double a, double r): mAbs(a), mRel(r)
{
}

/**
 * Constructor with two values.
 * First value sets the absolute value, econd sets the relative value.
 */
CLRelAbsVector::CLRelAbsVector(const std::string& coordString): mAbs(0.0), mRel(0.0)
{
  setCoordinate(coordString);
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLRelAbsVector::CLRelAbsVector(const RelAbsVector& source):
    mAbs(source.getAbsoluteValue()),
    mRel(source.getRelativeValue())
{
}

/**
 * Sets the coordiantes.
 */
void CLRelAbsVector::setCoordinate(double abs, double rel)
{
  this->mAbs = abs;
  this->mRel = rel;
}

/**
 * Sets the coordiantes from the given string.
 */
void CLRelAbsVector::setCoordinate(const std::string& coordString)
{
  bool result = true;
  // first we remove all whitespaces from the string
  size_t i, iMax = coordString.size();
  std::string trimmed;

  for (i = 0; i < iMax; ++i)
    {
      if (!(coordString[i] == ' ' || coordString[i] == '\t' || coordString[i] == '\n' || coordString[i] == '\r'))
        {
          trimmed += coordString[i];
        }
    }

  if (trimmed.empty())
    {
      result = false;
    }
  else
    {
      char* s = new char[trimmed.size()+1];
      strncpy(s, trimmed.c_str(), trimmed.size() + 1);
      char* p = s;
      char* pp;
      // p is changed if the value is parsed
      double value = strtod(p, &pp);

      // check if strtod stopped at the '%' and if it is the last character in the string
      if ((*pp) == '%' && pp == (s + trimmed.size() - 1))
        {
          // we only have a relative value
          this->mAbs = 0.0;
          this->mRel = value;
        }
      else
        {
          // either pp is at the end, then we only have an absolute value
          // or pp has stopped on a '+' or '-' which connects the relative to the absolute value
          // or we have an error
          if ((*pp) == '\0')
            {
              this->mAbs = value;
              this->mRel = 0.0;
            }
          else if ((*pp) == '+' || (*pp) == '-')
            {
              this->mAbs = value;
              p = pp;
              double value = strtod(p, &pp);

              // pp must point to the '%' character
              if ((*pp) != '%' || pp != (s + trimmed.size() - 1))
                {
                  result = false;
                }
              else
                {
                  this->mRel = value;
                }
            }
          else
            {
              result = false;
            }
        }

      delete[] s;
    }

  if (result == false)
    {
      // set relative and absolute value to NaN
      this->mAbs = std::numeric_limits<double>::quiet_NaN();
      this->mRel = std::numeric_limits<double>::quiet_NaN();
    }
}

/**
 * Sets the absolute coordinate value.
 */
void CLRelAbsVector::setAbsoluteValue(double abs)
{
  this->mAbs = abs;
}

/**
 * Sets the relative coordinate value.
 */
void CLRelAbsVector::setRelativeValue(double rel)
{
  this->mRel = rel;
}

/**
 * Returns the absolute coordinate value.
 */
double CLRelAbsVector::getAbsoluteValue() const
{
  return this->mAbs;
}

/**
 * Returns the relative coordinate value.
 */
double CLRelAbsVector::getRelativeValue() const
{
  return this->mRel;
}

/**
 * addition operator
 */
CLRelAbsVector CLRelAbsVector::operator+(const CLRelAbsVector& other) const
{
  return CLRelAbsVector(this->mAbs + other.mAbs, this->mRel + other.mRel);
}

/**
 * division by a double.
 */
CLRelAbsVector CLRelAbsVector::operator/(double x) const
{
  return CLRelAbsVector(this->mAbs / x, this->mRel / x);
}

bool CLRelAbsVector::operator==(const CLRelAbsVector& other) const
{
  bool result = true;

  if (this->mAbs == 0.0)
    {
      result = (fabs(other.mAbs) < 1e-12);
    }
  else
    {
      result = (fabs((this->mAbs - other.mAbs) / this->mAbs) < 1e-12);
    }

  if (result)
    {
      if (this->mRel == 0.0)
        {
          result = (fabs(other.mRel) < 1e-12);
        }
      else
        {
          result = (fabs((this->mRel - other.mRel) / this->mRel) < 1e-12);
        }
    }

  return result;
}

bool CLRelAbsVector::operator!=(const CLRelAbsVector& other) const
{
  return !((*this) == other);
}

std::string CLRelAbsVector::toString() const
{
  std::ostringstream os;

  if (this->mAbs != 0.0 || this->mRel == 0.0)
    {
      os << this->mAbs;

      if (this->mRel < 0.0)
        {
          os << this->mRel << "%";
        }
      else if (this->mRel > 0.0)
        {
          os << "+" << this->mRel << "%";
        }
    }
  else
    {
      os << this->mRel << "%";
    }

  return os.str();
}

std::ostream& operator<<(std::ostream& os, const CLRelAbsVector& v)
{
  os << v.toString();
  return os;
}

CLRelAbsVector& CLRelAbsVector::operator=(const CLRelAbsVector & src)
{
  if (&src != this)
    {
      this->mAbs = src.mAbs;
      this->mRel = src.mRel;
    }

  return *this;
}

/**
 * Converts this object to the corresponding SBML object.
 */
RelAbsVector* CLRelAbsVector::toSBML() const
{
  return new RelAbsVector(mAbs, mRel);
}
