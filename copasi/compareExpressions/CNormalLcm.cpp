// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalLcm.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/08/08 10:27:29 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <vector>
#include <set>
#include "copasi.h"
#include <math.h>

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
CNormalLcm & CNormalLcm::operator=(const CNormalLcm& src)
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
    case 0:    //Sum must contain at least one product!
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
  switch (sum.getProducts().size())
    {
    case 0:
      {
        return false;
      }
    case 1:
      {
        const CNormalProduct* product = *sum.getProducts().begin();
        std::set <CNormalItemPower*, compareItemPowers >::const_iterator it;
        std::set <CNormalItemPower*, compareItemPowers >::const_iterator itEnd = product->getItemPowers().end();
        for (it = product->getItemPowers().begin(); it != itEnd; ++it)
          {
            if (remove(**it) == false)
              return false;
          }
        return true;
      }
    default:
      {
        std::vector<CNormalSum*>::iterator it;
        std::vector<CNormalSum*>::iterator itEnd = mSums.end();
        for (it = mSums.begin(); it != itEnd; ++it)
          {
            if (**it == sum)
              {
                delete *it;
                mSums.erase(it);
                return true;
              }
          }
        return false;
      }
      return false;
    }
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
