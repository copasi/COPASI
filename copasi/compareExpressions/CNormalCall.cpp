// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalCall.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:26:19 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CNormalCall.h"

#include <sstream>

#include "CNormalFraction.h"

CNormalCall::CNormalCall(): CNormalBase(), mName(""), mType(CNormalCall::INVALID)
{};

/**
 * Copy Constructor
 */
CNormalCall::CNormalCall(const CNormalCall& src): CNormalBase(src)
{
  this->mName = src.mName;
  this->mType = src.mType;
  this->setFractions(src.mFractions);
}

/**
 * Assignment operator
 */
CNormalCall & CNormalCall::operator=(const CNormalCall & src)
{
  if (&src != this)
    {
      this->mName = src.mName;
      this->mType = src.mType;
      this->setFractions(src.mFractions);
    }

  return *this;
}

/**
 * Smaller operator
 */
bool CNormalCall::operator<(const CNormalCall& rhs) const
{
  bool result = false;

  if (this->mType < rhs.mType)
    {
      result = true;
    }
  else
    {
      if (this->mName < rhs.mName)
        {
          result = true;
        }
      else
        {
          if (this->mName == rhs.mName)
            {
              if (this->mFractions.size() < rhs.mFractions.size())
                {
                  result = true;
                }
              else
                {
                  if (this->mFractions.size() == rhs.mFractions.size())
                    {
                      bool smaller = true;
                      std::vector<CNormalFraction*>::const_iterator it = this->mFractions.begin(), endit = this->mFractions.end();
                      std::vector<CNormalFraction*>::const_iterator it2 = rhs.mFractions.begin();

                      while (it != endit && smaller == true)
                        {
                          smaller = ((*it2) < (*it));
                          ++it;
                          ++it2;
                        }

                      if (smaller)
                        {
                          result = true;
                        }
                    }
                }
            }
        }
    }

  return result;
}

/**
 * Destructor
 */
CNormalCall::~CNormalCall()
{
  // delete all fractions
  std::vector<CNormalFraction*>::iterator it = this->mFractions.begin(), endit = this->mFractions.end();

  while (it != endit)
    {
      delete *it;
      ++it;
    }
}

CNormalBase * CNormalCall::copy() const
{
  return new CNormalCall(*this);
}

/**
 * Retrieve the number of summands of this sum.
 * @return int
 */
int CNormalCall::getSize() const
{
  return this->mFractions.size();
}

/**
 * Add fraction to this sum.
 * @return true.
 */
bool CNormalCall::add(const CNormalFraction& fraction)
{
  this->mFractions.push_back(new CNormalFraction(fraction));
  return true;
}

/**
 * Retrieve the set of fractions of this sum.
 * @return mFractions.
 */
const std::vector<CNormalFraction*>& CNormalCall::getFractions() const
{
  return this->mFractions;
}

/**
 * Examine equality of two sums.
 * @return bool.
 */
bool CNormalCall::operator==(const CNormalCall & rhs) const
{
  bool result = true;

  if (this->mType == rhs.mType)
    {
      if (this->mName == rhs.mName)
        {
          if (this->mFractions.size() == rhs.mFractions.size())
            {
              std::vector<CNormalFraction*>::const_iterator it = this->mFractions.begin();
              std::vector<CNormalFraction*>::const_iterator it2 = rhs.mFractions.begin();
              std::vector<CNormalFraction*>::const_iterator endit = this->mFractions.end();

              while (it != endit && result == true)
                {
                  result = ((**it) == (**it2));
                  ++it;
                  ++it2;
                }
            }
          else
            {
              result = false;
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Sets the fractions of this product.
 */
void CNormalCall::setFractions(const std::vector<CNormalFraction*>& set)
{
  // delete all fractions
  std::vector<CNormalFraction*>::iterator it = this->mFractions.begin(), endit = this->mFractions.end();

  while (it != endit)
    {
      delete *it;
      ++it;
    }

  this->mFractions.clear();
  std::vector<CNormalFraction*>::const_iterator it2 = set.begin(), endit2 = set.end();

  while (it2 != endit2)
    {
      this->add(**it2);
      ++it2;
    }
}

std::string CNormalCall::toString() const
{
  std::ostringstream os;
  os << this->mName << "(";
  std::vector<CNormalFraction*>::const_iterator it = this->mFractions.begin(), endit = this->mFractions.end();

  while (it != endit)
    {
      os << (**it);
      ++it;

      if (it != endit)
        {
          os << ",";
        }
    }

  os << ")";
  return os.str();
}

bool CNormalCall::simplify()
{
  // simplify all children
  std::vector<CNormalFraction*>::iterator it = this->mFractions.begin(), endit = this->mFractions.end();

  while (it != endit)
    {
      (*it)->simplify();
      ++it;
    }

  return true;
}

std::ostream & operator<< (std::ostream &os, const CNormalCall & d)
{
  os << d.toString();
  return os;
}

const std::string& CNormalCall::getName() const
{
  return this->mName;
}

void CNormalCall::setName(const std::string& name)
{
  this->mName = name;
}

CNormalCall::Type CNormalCall::getType() const
{
  return this->mType;
}

void CNormalCall::setType(CNormalCall::Type type)
{
  this->mType = type;
}
