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

#include <vector>
#include <set>
#include <cmath>
#include <sstream>

#include "copasi/copasi.h"

#include "CNormalSum.h"
#include "CNormalProduct.h"
#include "CNormalItemPower.h"
#include "CNormalLcm.h"

/**
 * Default constructor
 */
CNormalLcm::CNormalLcm()
{}

/**
 * Copy contructor
 */
CNormalLcm::CNormalLcm(const CNormalLcm& src)
{
  std::set <CNormalItemPower*, compareItemPowers >::const_iterator it;
  std::set <CNormalItemPower*, compareItemPowers >::const_iterator itEnd = src.mItemPowers.end();

  for (it = src.mItemPowers.begin(); it != itEnd; ++it)
    {
      mItemPowers.insert(new CNormalItemPower(**it));
    }

  std::vector<CNormalSum*>::const_iterator it2;
  std::vector<CNormalSum*>::const_iterator it2End = src.mSums.end();

  for (it2 = src.mSums.begin(); it2 != it2End; ++it2)
    {
      mSums.push_back(new CNormalSum(**it2));
    }
}

/**
 * Assignment operator
 */
CNormalLcm & CNormalLcm::operator=(const CNormalLcm & src)
{
  std::set<CNormalItemPower*, compareItemPowers >::const_iterator it;
  std::set<CNormalItemPower*, compareItemPowers >::const_iterator itEnd = src.mItemPowers.end();

  for (it = src.mItemPowers.begin(); it != itEnd; ++it)
    mItemPowers.insert(new CNormalItemPower(**it));

  std::vector<CNormalSum*>::const_iterator it2;
  std::vector<CNormalSum*>::const_iterator it2End = src.mSums.end();

  for (it2 = src.mSums.begin(); it2 != it2End; ++it2)
    mSums.push_back(new CNormalSum(**it2));

  return *this;
}

/**
 * Destructor
 */
CNormalLcm::~CNormalLcm()
{
  std::set<CNormalItemPower*, compareItemPowers >::const_iterator it;
  std::set<CNormalItemPower*, compareItemPowers >::const_iterator itEnd = mItemPowers.end();

  for (it = mItemPowers.begin(); it != itEnd; ++it)
    delete *it;

  std::vector<CNormalSum*>::const_iterator it2;
  std::vector<CNormalSum*>::const_iterator it2End = mSums.end();

  for (it2 = mSums.begin(); it2 != it2End; ++it2)
    delete *it2;
}

/**
 * Add an itempower to this lcm,
 * ie. lcm := LeastCommonMultiple(lcm,itempower)
 * @return true.
 */
bool CNormalLcm::add(const CNormalItemPower& itemPower)
{
  std::set <CNormalItemPower*, compareItemPowers >::iterator it;
  std::set <CNormalItemPower*, compareItemPowers >::iterator itEnd = mItemPowers.end();

  for (it = mItemPowers.begin(); it != itEnd; ++it)
    {
      if ((*it)->getItem().areEqual(itemPower.getItem()))
        {
          (*it)->setExp((*it)->getExp() > itemPower.getExp() ? (*it)->getExp() : itemPower.getExp());
          return true;
        }
    }

  CNormalItemPower* tmp = new CNormalItemPower(itemPower);
  mItemPowers.insert(tmp);
  return true;
}

/**
 * Add a fractionless sum to this lcm,
 * ie. lcm := LeastCommonMultiple(lcm,sum)
 * @return true.
 */
bool CNormalLcm::add(const CNormalSum& sum)
{
  switch (sum.getProducts().size())
    {
      case 0:     //Sum must contain at least one product!
      {
        return false;
      }

      case 1:
      {
        CNormalProduct* product = *sum.getProducts().begin();
        std::set<CNormalItemPower*, compareItemPowers >::const_iterator it;
        std::set<CNormalItemPower*, compareItemPowers >::const_iterator itEnd = product->getItemPowers().end();

        for (it = product->getItemPowers().begin(); it != itEnd; ++it)
          {
            add(**it);
          }

        return true;
      }

      default:
      {
        std::vector<CNormalSum*>::iterator it;
        std::vector<CNormalSum*>::iterator itEnd = mSums.end();

        for (it = mSums.begin(); it != itEnd; ++it)
          {
            if (sum == **it)
              {
                return true;
              }
          }

        CNormalSum* tmp = new CNormalSum(sum);
        mSums.push_back(tmp);
        return true;
      }
    }
}

/**
 * Remove an itempower from this lcm, provided it is a factor
 * @return true.
 */
bool CNormalLcm::remove(const CNormalItemPower& itemPower)
{
  std::set <CNormalItemPower*, compareItemPowers >::iterator it;
  std::set <CNormalItemPower*, compareItemPowers >::iterator itEnd = mItemPowers.end();

  for (it = mItemPowers.begin(); it != itEnd; ++it)
    {
      if ((*it)->getItem().areEqual(itemPower.getItem()))
        {
          C_FLOAT64 dif = (*it)->getExp() - itemPower.getExp();

          if (dif <= -1.0E-100)
            return false;

          if (fabs(dif) < 1.0E-100)
            {
              delete *it;
              mItemPowers.erase(it);
              return true;
            }

          (*it)->setExp(dif);
          return true;
        }
    }

  return false;
}

/**
 * Remove a fractionless sum from this lcm, provided it is a factor
 * @return true.
 */
bool CNormalLcm::remove(const CNormalSum& sum)   //sum must not contain fractions!!
{
  bool result = true;
  std::set <CNormalItemPower*, compareItemPowers >::const_iterator it, itEnd;
  std::vector<CNormalSum*>::iterator it2, itEnd2;
  const CNormalProduct* pProduct = NULL;

  switch (sum.getProducts().size())
    {
      case 0:
        result = false;
        break;

      case 1:
        pProduct = *sum.getProducts().begin();
        itEnd = pProduct->getItemPowers().end();

        for (it = pProduct->getItemPowers().begin(); it != itEnd && result == true; ++it)
          {
            if (remove(**it) == false)
              {
                result = false;
              }
          }

        break;

      default:
        itEnd2 = mSums.end();
        result = false;

        for (it2 = mSums.begin(); it2 != itEnd2; ++it2)
          {
            if (**it2 == sum)
              {
                delete *it2;
                mSums.erase(it2);
                result = true;
                break;
              }
          }

        // the below causes issues on VS, as in a way the iterator is no longer
        // valid after removal, instead the result is set in the loop
        //if (it2 == itEnd2)
        //{
        //  result = false;
        //}
    }

  return result;
}

/**
 * Retrieve the set of itempowers of this lcm.
 * @return mItemPowers.
 */
const std::set <CNormalItemPower*, compareItemPowers >& CNormalLcm::getItemPowers() const
{
  return mItemPowers;
}

/**
 * Retrieve the vector of sums of this lcm.
 * @return mSums.
 */
const std::vector<CNormalSum*>& CNormalLcm::getSums() const
{
  return mSums;
}

std::string CNormalLcm::toString() const
{
  std::ostringstream os;
  os << *this;
  return os.str();
}

std::ostream & operator<< (std::ostream &os, const CNormalLcm & d)
{
  if (d.mItemPowers.size() + d.mSums.size() != 0)
    {
      bool firstFactor = true;
      std::set <CNormalItemPower*, compareItemPowers >::const_iterator it;
      std::set <CNormalItemPower*, compareItemPowers >::const_iterator itEnd = d.mItemPowers.end();

      for (it = d.mItemPowers.begin(); it != itEnd; ++it)
        {
          if (firstFactor == false)
            {
              os << " * ";
            }

          os << **it;
          firstFactor = false;
        }

      std::vector<CNormalSum*>::const_iterator it2;
      std::vector<CNormalSum*>::const_iterator it2End = d.mSums.end();

      for (it2 = d.mSums.begin(); it2 != it2End; ++it2)
        {
          if (firstFactor == false)
            {
              os << " * ";
            }

          os << "(" << **it2 << ")";
          firstFactor = false;
        }
    }
  else
    {
      os << "1.0";
    }

  return os;
}

#ifdef COPASI_DEBUG
void CNormalLcm::refresh()
{
  this->mInfix = this->toString();
}
#endif /* COPASI_DEBUG */
