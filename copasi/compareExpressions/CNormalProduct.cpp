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

#include <set>
#include <cmath>
#include <sstream>

#include "copasi/copasi.h"

#include "CNormalSum.h"
#include "CNormalLcm.h"
#include "CNormalItem.h"
#include "CNormalItemPower.h"
#include "CNormalProduct.h"
#include "CNormalFunction.h"
#include "CNormalGeneralPower.h"
#include "CNormalChoice.h"
#include "CNormalFraction.h"

bool compareItemPowers::operator()(const CNormalItemPower* itemPower1, const CNormalItemPower* itemPower2) const
{
  return *itemPower1 < *itemPower2;
}

/**
 * Default constructor
 */
CNormalProduct::CNormalProduct(): CNormalBase(), mFactor(1.0)
{}

/**
 * Copy contructor
 */
CNormalProduct::CNormalProduct(const CNormalProduct& src): CNormalBase(src), mFactor(src.mFactor)
{
  std::set<CNormalItemPower*, compareItemPowers >::const_iterator it;
  std::set<CNormalItemPower*, compareItemPowers >::const_iterator itEnd = src.mItemPowers.end();
  const CNormalItemPower* pSrcItemPower = NULL;
  CNormalItemPower* pDestItemPower = NULL;

  for (it = src.mItemPowers.begin(); it != itEnd; ++it)
    {
      pSrcItemPower = *it;
      pDestItemPower = new CNormalItemPower(*pSrcItemPower);
      bool result = this->mItemPowers.insert(pDestItemPower).second;
      assert(result == true);
    }
}

/**
 * Assignment operator
 */
CNormalProduct & CNormalProduct::operator=(const CNormalProduct & src)
{
  mFactor = src.mFactor;
  std::set<CNormalItemPower*, compareItemPowers >::const_iterator it;
  std::set<CNormalItemPower*, compareItemPowers >::const_iterator itEnd = src.mItemPowers.end();

  for (it = src.mItemPowers.begin(); it != itEnd; ++it)
    mItemPowers.insert(new CNormalItemPower(**it));

  return *this;
}

/**
 * Destructor
 */
CNormalProduct::~CNormalProduct()
{
  std::set<CNormalItemPower*, compareItemPowers >::const_iterator it;
  std::set<CNormalItemPower*, compareItemPowers >::const_iterator itEnd = mItemPowers.end();

  for (it = mItemPowers.begin(); it != itEnd; ++it)
    delete *it;
}

/**
 * Set the factor for this product.
 * @return true.
 */
bool CNormalProduct::setFactor(const C_FLOAT64& number)
{
  mFactor = number;

  if (fabs(mFactor) < 1.0E-100)
    {
      std::set<CNormalItemPower*, compareItemPowers>::iterator it = mItemPowers.begin(), endit = mItemPowers.end();

      while (it != endit)
        {
          delete *it;
          ++it;
        }

      mItemPowers.clear();
      //mPowers.clear();
    }

  return true;
}

/**
 * Multiply this product with a number.
 * @return true.
 */
bool CNormalProduct::multiply(const C_FLOAT64& number)
{
  mFactor = mFactor * number;

  if (fabs(mFactor) < 1.0E-100)
    {
      std::set<CNormalItemPower*, compareItemPowers>::iterator it = mItemPowers.begin(), endit = mItemPowers.end();

      while (it != endit)
        {
          delete *it;
          ++it;
        }

      mItemPowers.clear();
      //mPowers.clear();
    }

  return true;
}

/**
 * Multiply an choice to this product.
 * @return true.
 */
bool CNormalProduct::multiply(const CNormalChoice& choice)
{
  if (fabs(mFactor) < 1.0E-100)
    return true;

  std::set <CNormalItemPower*, compareItemPowers >::const_iterator it;
  std::set <CNormalItemPower*, compareItemPowers >::const_iterator itEnd = mItemPowers.end();

  for (it = mItemPowers.begin(); it != itEnd; ++it)
    {
      if ((*it)->getItem().areEqual(choice) == true)
        {
          (*it)->setExp((*it)->getExp() + 1.0);
          return true;
        }
    }

  CNormalItemPower* tmp = new CNormalItemPower(choice, 1.0);
  mItemPowers.insert(tmp);
  return true;
}

/**
 * Multiply an item to this product.
 * @return true.
 */
bool CNormalProduct::multiply(const CNormalGeneralPower& pow)
{
  if (fabs(mFactor) < 1.0E-100)
    return true;

  std::set <CNormalItemPower*, compareItemPowers >::const_iterator it;
  std::set <CNormalItemPower*, compareItemPowers >::const_iterator itEnd = mItemPowers.end();

  for (it = mItemPowers.begin(); it != itEnd; ++it)
    {
      if ((*it)->getItem().areEqual(pow) == true)
        {
          (*it)->setExp((*it)->getExp() + 1.0);
          return true;
        }
    }

  CNormalItemPower* tmp = new CNormalItemPower(pow, 1.0);
  mItemPowers.insert(tmp);
  return true;
}

/**
 * Multiply an item to this product.
 * @return true.
 */
bool CNormalProduct::multiply(const CNormalFunction& fun)
{
  if (fabs(mFactor) < 1.0E-100)
    return true;

  std::set <CNormalItemPower*, compareItemPowers >::const_iterator it;
  std::set <CNormalItemPower*, compareItemPowers >::const_iterator itEnd = mItemPowers.end();

  for (it = mItemPowers.begin(); it != itEnd; ++it)
    {
      if ((*it)->getItem().areEqual(fun) == true)
        {
          (*it)->setExp((*it)->getExp() + 1.0);
          return true;
        }
    }

  CNormalItemPower* tmp = new CNormalItemPower(fun, 1.0);
  mItemPowers.insert(tmp);
  return true;
}

/**
 * Multiply an item to this product.
 * @return true.
 */
bool CNormalProduct::multiply(const CNormalItem& item)
{
  if (fabs(mFactor) < 1.0E-100)
    return true;

  std::set <CNormalItemPower*, compareItemPowers >::const_iterator it;
  std::set <CNormalItemPower*, compareItemPowers >::const_iterator itEnd = mItemPowers.end();

  for (it = mItemPowers.begin(); it != itEnd; ++it)
    {
      if ((*it)->getItem().areEqual(item) == true)
        {
          (*it)->setExp((*it)->getExp() + 1.0);
          return true;
        }
    }

  CNormalItemPower* tmp = new CNormalItemPower(item, 1.0);
  mItemPowers.insert(tmp);
  return true;
}

/**
 * Multiply an itempower to this product.
 * @return true.
 */
bool CNormalProduct::multiply(const CNormalItemPower& itemPower)
{
  if (fabs(mFactor) < 1.0E-100)
    return true;

  std::set <CNormalItemPower*, compareItemPowers >::const_iterator it;
  std::set <CNormalItemPower*, compareItemPowers >::const_iterator itEnd = mItemPowers.end();

  for (it = mItemPowers.begin(); it != itEnd; ++it)
    {
      if ((*it)->getItem().areEqual(itemPower.getItem()))
        {
          (*it)->setExp((*it)->getExp() + itemPower.getExp());
          return true;
        }
    }

  CNormalItemPower* tmp = new CNormalItemPower(itemPower);
  mItemPowers.insert(tmp);
  return true;
}

/**
 * Multiply a list of itempowers to this product.
 * @return true.
 */
bool CNormalProduct::multiply(const std::set <CNormalItemPower*, compareItemPowers >& itemPowers)
{
  if (fabs(mFactor) < 1.0E-100)
    return true;

  std::set <CNormalItemPower*, compareItemPowers >::const_iterator it;
  std::set <CNormalItemPower*, compareItemPowers >::const_iterator itEnd = itemPowers.end();

  for (it = itemPowers.begin(); it != itEnd; ++it)
    multiply(**it);

  return true;
}

/**
 * Remove an itempower from this product, provided it is a factor of it.
 * @return true.
 */
bool CNormalProduct::remove(std::set<CNormalItemPower*, compareItemPowers >::iterator it)
{
  delete(*it);
  mItemPowers.erase(it);
  return true;
}

/**
 * Remove an itempower from this product, provided it is a factor of it.
 * -used in multiplication with lcm-
 * @return true.
 */
bool CNormalProduct::remove(const CNormalItemPower& itemPower)
{
  std::set <CNormalItemPower*, compareItemPowers >::iterator it;
  std::set <CNormalItemPower*, compareItemPowers >::iterator itEnd = mItemPowers.end();

  for (it = mItemPowers.begin(); it != itEnd; ++it)
    {
      if ((*it)->getItem().areEqual(itemPower.getItem()))
        {
          C_FLOAT64 dif = (*it)->getExp() - itemPower.getExp();

          if (dif >= 1.0E-100)
            {
              (*it)->setExp(dif);
              return true;
            }

          if (fabs(dif) < 1.0E-100)
            {
              delete(*it);
              mItemPowers.erase(it);
              return true;
            }

          return false;
        }
    }

  return false;
}

/**
 * Multiply this product with another product.
 * @return true
 */
bool CNormalProduct::multiply(const CNormalProduct& product)
{
  multiply(product.getFactor());

  if (fabs(mFactor) < 1.0E-100)
    return true;

  multiply(product.getItemPowers());
  return true;
}

/**
 * Multiply this product with a sum NOT CONTAINING FRACTIONS!.
 * @return sum.
 */
CNormalSum* CNormalProduct::multiply(const CNormalSum& sum)
{
  if (fabs(mFactor) < 1.0E-100)
    {
      CNormalSum* zeroSum = new CNormalSum();
      zeroSum->add(*this);
      return zeroSum;
    }

  CNormalSum* tmp = new CNormalSum(sum);
  CNormalSum* newsum = new CNormalSum();
  std::set<CNormalProduct*, compareProducts>::const_iterator it;
  std::set<CNormalProduct*, compareProducts>::const_iterator itEnd = tmp->getProducts().end();

  for (it = tmp->getProducts().begin(); it != itEnd; ++it)
    {
      (*it)->multiply(*this);
      newsum->add(**it);
    }

  delete tmp;
  return newsum;
}

/**
 * Multiply this product with a lcm.
 * @return true
 */
const CNormalSum* CNormalProduct::multiply(const CNormalLcm& lcm)
{
  if (fabs(mFactor) < 1.0E-100)
    {
      CNormalSum* zeroSum = new CNormalSum();
      zeroSum->add(*this);
      return zeroSum;
    }

  CNormalLcm* tmp = new CNormalLcm(lcm);
  multiply(tmp->getItemPowers());
  CNormalSum* sum = new CNormalSum();
  sum->add(*this);
  std::vector<CNormalSum*>::const_iterator it;
  std::vector<CNormalSum*>::const_iterator itEnd = tmp->getSums().end();

  for (it = tmp->getSums().begin(); it != itEnd; ++it)
    {
      sum->multiply(**it);
    }

  delete tmp;
  return sum;
}

/**
 * Retrieve the factor of this product.
 * @return mFactor.
 */
const C_FLOAT64 & CNormalProduct::getFactor() const
{
  return mFactor;
}

/**
 * Retrieve the set of itempowers of this product.
 * @return mItemPowers.
 */
const std::set <CNormalItemPower*, compareItemPowers >& CNormalProduct::getItemPowers() const
{
  return mItemPowers;
}

bool CNormalProduct::checkSamePowerList(const CNormalProduct & rhs) const
{
  if (mItemPowers.size() != rhs.mItemPowers.size())
    return false;

  std::set< CNormalItemPower*, compareItemPowers >::const_iterator it;
  std::set< CNormalItemPower*, compareItemPowers >::const_iterator itEnd = mItemPowers.end();
  std::set< CNormalItemPower*, compareItemPowers >::const_iterator it2;
  //std::set< CNormalItemPower*, compareItemPowers >::const_iterator it2End = rhs.mItemPowers.end();

  for (it = mItemPowers.begin(), it2 = rhs.mItemPowers.begin(); it != itEnd; ++it, ++it2)
    {
      if (!(**it == **it2))
        return false;
    }

  return true;
}

bool CNormalProduct::operator==(const CNormalProduct & rhs) const
{
  if (mFactor != rhs.mFactor)
    return false;

  if (checkSamePowerList(rhs))
    return true;

  return false;
}

std::ostream & operator<< (std::ostream &os, const CNormalProduct & d)
{
  os << d.toString();
  return os;
}

std::string CNormalProduct::toString() const
{
  std::ostringstream os;
  bool firstFactor = true;

  if ((fabs(this->mFactor - 1.0) >= 1.0E-100) || (this->mItemPowers.size() == 0))
    {
      if (this->mFactor < 0.0)
        os << "(" << this->mFactor << ")";
      else
        {
          os.precision(std::numeric_limits<double>::digits10 + 2);
          os << this->mFactor;
        }

      firstFactor = false;
    }

  std::set <CNormalItemPower*, compareItemPowers >::const_iterator it;
  std::set <CNormalItemPower*, compareItemPowers >::const_iterator itEnd = this->mItemPowers.end();

  for (it = this->mItemPowers.begin(); it != itEnd; ++it)
    {
      if (firstFactor == false)
        os << " * ";

      os << **it;
      firstFactor = false;
    }

  return os.str();
}

CNormalBase * CNormalProduct::copy() const
{
  return new CNormalProduct(*this);
}

bool CNormalProduct::operator<(const CNormalProduct& rhs) const
{
  bool result = false;

  if (this->mFactor < rhs.mFactor)
    {
      result = true;
    }
  else if (this->mFactor == rhs.mFactor)
    {
      if (this->mItemPowers.size() < rhs.mItemPowers.size())
        {
          result = true;
        }
      else if (this->mItemPowers.size() == rhs.mItemPowers.size())
        {
          std::set<CNormalItemPower*, compareItemPowers >::const_iterator it = this->mItemPowers.begin(), endit = this->mItemPowers.end();
          std::set<CNormalItemPower*, compareItemPowers >::const_iterator it2 = rhs.mItemPowers.begin();
          compareItemPowers comp;

          while (result == false && it != endit)
            {
              if (comp(*it, *it2))
                {
                  result = true;
                }

              if (comp(*it2, *it))
                {
                  break;
                }

              ++it;
              ++it2;
            }
        }
    }

  return result;
}

void CNormalProduct::setItemPowers(const std::set<CNormalItemPower*, compareItemPowers>& set)
{
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it = this->mItemPowers.begin(), endit = this->mItemPowers.end();

  while (it != endit)
    {
      delete *it;
      ++it;
    }

  it = set.begin(), endit = set.end();
  this->mItemPowers.clear();

  while (it != endit)
    {
      this->mItemPowers.insert(new CNormalItemPower(**it));
      ++it;
    }
}

bool CNormalProduct::simplify()
{
  bool result = true;
  // don't work on the items in the set directly
  // make a copy, otherwise the set will be messed up
  std::set<CNormalItemPower*, compareItemPowers> itemPowersCopy(this->mItemPowers);
  std::set<CNormalItemPower*, compareItemPowers>::iterator it = itemPowersCopy.begin(), endit = itemPowersCopy.end();
  CNormalItemPower* pTmpItemPower = NULL;
  this->mItemPowers.clear();

  while (it != endit && result == true)
    {
      pTmpItemPower = *it;
      result = pTmpItemPower->simplify();

      if (result)
        {
          this->multiply(*pTmpItemPower);
        }

      delete pTmpItemPower;
      ++it;
    }

  // we should combine all general power items of type power into
  // one large general power item which is again simplified
  // this we only do if the CNormalItemPower parent has an exponent of 1
  it = this->mItemPowers.begin();
  endit = this->mItemPowers.end();
  std::vector<CNormalItemPower*> tmpV;
  // create a unit CNormalItemPower with one unit CNormalGeneralPower
  // and an exponent of 1
  CNormalGeneralPower* pGeneralPower = NULL; //CNormalGeneralPower::createUnitGeneralPower();

  while (it != endit)
    {
      if ((*it)->getExp() == 1.0 && (*it)->getItemType() == CNormalItemPower::POWER &&
          dynamic_cast<CNormalGeneralPower*>(&(*it)->getItem())->getType() == CNormalGeneralPower::POWER
          &&
          dynamic_cast<CNormalGeneralPower*>(&(*it)->getItem())->getRight().checkIsOne()
         )
        {
          if (pGeneralPower)
            {
              pGeneralPower->multiply(*static_cast<CNormalGeneralPower*>(&(*it)->getItem()));
            }
          else
            {
              pGeneralPower = static_cast<CNormalGeneralPower*>(&(*it)->getItem());
              pGeneralPower = new CNormalGeneralPower(*pGeneralPower);
            }

          delete *it;
        }
      else
        {
          if ((*it)->getItemType() == CNormalItemPower::POWER &&
              dynamic_cast<CNormalGeneralPower*>(&(*it)->getItem())->getType() == CNormalGeneralPower::POWER &&
              dynamic_cast<CNormalGeneralPower*>(&(*it)->getItem())->getLeft().checkIsOne()
             )
            {
              delete *it;
            }
          else
            {
              tmpV.push_back(*it);
            }
        }

      ++ it;
    }

  if (pGeneralPower && !pGeneralPower->checkIsOne())
    {
      CNormalItemPower* pTmpItemPower = new CNormalItemPower();
      pTmpItemPower->setExp(1.0);
      pTmpItemPower->setItem(*pGeneralPower);
      tmpV.push_back(pTmpItemPower);
    }

  delete pGeneralPower;
  // clear the current set of items and add all the item in tmpV
  this->mItemPowers.clear();
  std::vector<CNormalItemPower*>::iterator vIt = tmpV.begin();
  std::vector<CNormalItemPower*>::iterator vEndIt = tmpV.end();

  while (vIt != vEndIt)
    {
      this->multiply(**vIt);
      delete *vIt;
      ++vIt;
    }

  return result;
}

CNormalGeneralPower* CNormalProduct::getDenominator() const
{
  // go though all items that are general powers and check for general items
  // of type power that have denominators in their base that differ from 1
  // from all those denominators create a common denoninator and return it

  // first we generate a general power that is 1
  CNormalGeneralPower* pResult = new CNormalGeneralPower();
  pResult->setType(CNormalGeneralPower::POWER);
  CNormalSum* pTmpSum = new CNormalSum();
  CNormalFraction* pTmpFrac = new CNormalFraction();
  CNormalProduct* pTmpProduct = new CNormalProduct();
  pTmpSum->add(*pTmpProduct);
  delete pTmpProduct;
  pTmpFrac->setNumerator(*pTmpSum);
  pTmpFrac->setDenominator(*pTmpSum);
  pResult->setLeft(*pTmpFrac);
  pResult->setRight(*pTmpFrac);
  delete pTmpFrac;
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it = this->mItemPowers.begin(), endit = this->mItemPowers.end();

  while (it != endit)
    {
      if ((*it)->getItemType() == CNormalItemPower::POWER)
        {
          CNormalGeneralPower* pTmpPow = dynamic_cast<CNormalGeneralPower*>(&(*it)->getItem());
          assert(pTmpPow != NULL);

          // only set the numerator to 1 if it is a power item and the
          // denominator is not 1
          if (pTmpPow->getType() == CNormalGeneralPower::POWER && !pTmpPow->getLeft().checkDenominatorOne())
            {
              // set the numerator to 1
              pTmpPow = new CNormalGeneralPower(*pTmpPow);
              pTmpPow->getLeft().setNumerator(*pTmpSum);
              pResult->multiply(*pTmpPow);
              delete pTmpPow;
            }
        }

      ++it;
    }

  delete pTmpSum;
  return pResult;
}

void CNormalProduct::setDenominatorsOne()
{
  // goes through all items and sets the denominators of the bases of all
  // general power items of type power to one
  CNormalSum* pTmpSum = new CNormalSum();
  CNormalProduct* pTmpProduct = new CNormalProduct();
  pTmpSum->add(*pTmpProduct);
  delete pTmpProduct;
  std::set<CNormalItemPower*, compareItemPowers>::iterator it = this->mItemPowers.begin(), endit = this->mItemPowers.end();

  while (it != endit)
    {
      if ((*it)->getItemType() == CNormalItemPower::POWER)
        {
          CNormalGeneralPower* pGenPow = dynamic_cast<CNormalGeneralPower*>(&(*it)->getItem());
          assert(pGenPow != NULL);

          // only set the denominator to 1 if it is a power item
          if (pGenPow->getType() == CNormalGeneralPower::POWER)
            {
              pGenPow->getLeft().setDenominator(*pTmpSum);
            }
        }

      ++it;
    }

  delete pTmpSum;
}

CNormalProduct* CNormalProduct::createUnitProduct()
{
  return new CNormalProduct();
}
