// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalSum.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/06/21 14:40:37 $
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

#include <vector>
#include <math.h>
#include <sstream>

#include "copasi.h"

#include "CNormalItemPower.h"
#include "CNormalProduct.h"
#include "CNormalLcm.h"
#include "CNormalFraction.h"
#include "CNormalSum.h"
#include "CNormalGeneralPower.h"

bool compareProducts::operator()(const CNormalProduct* product1, const CNormalProduct* product2)
{
  std::set<CNormalItemPower*, compareItemPowers >::const_iterator it;
  std::set<CNormalItemPower*, compareItemPowers >::const_iterator itEnd = product1->getItemPowers().end();
  std::set<CNormalItemPower*, compareItemPowers >::const_iterator it2;
  std::set<CNormalItemPower*, compareItemPowers >::const_iterator it2End = product2->getItemPowers().end();
  for (it = product1->getItemPowers().begin(), it2 = product2->getItemPowers().begin(); (it != itEnd) && (it2 != it2End); ++it, ++it2)
    {
      if (**it < **it2) return true;
      if (**it2 < **it) return false;
    }
  return (product1->getItemPowers().size() < product2->getItemPowers().size());
}

/**
 * Default constructor
 */
CNormalSum::CNormalSum(): CNormalBase()
{}

/**
 * Copy Constructor
 */
CNormalSum::CNormalSum(const CNormalSum& src): CNormalBase(src)
{
  std::set<CNormalProduct*, compareProducts >::const_iterator it;
  std::set<CNormalProduct*, compareProducts >::const_iterator itEnd = src.mProducts.end();
  for (it = src.mProducts.begin(); it != itEnd; ++it)
    mProducts.insert(new CNormalProduct(**it));

  std::set<CNormalFraction*>::const_iterator it2;
  std::set<CNormalFraction*>::const_iterator it2End = src.mFractions.end();
  for (it2 = src.mFractions.begin(); it2 != it2End; ++it2)
    mFractions.insert(new CNormalFraction(**it2));
}

/**
 * Assignment operator
 */
CNormalSum & CNormalSum::operator=(const CNormalSum& src)
{
  std::set<CNormalProduct*, compareProducts >::const_iterator it;
  std::set<CNormalProduct*, compareProducts >::const_iterator itEnd = src.mProducts.end();
  for (it = src.mProducts.begin(); it != itEnd; ++it)
    mProducts.insert(new CNormalProduct(**it));

  std::set<CNormalFraction*>::const_iterator it2;
  std::set<CNormalFraction*>::const_iterator it2End = src.mFractions.end();
  for (it2 = src.mFractions.begin(); it2 != it2End; ++it2)
    mFractions.insert(new CNormalFraction(**it2));

  return *this;
}

/**
 * Destructor
 */
CNormalSum::~CNormalSum()
{
  std::set<CNormalProduct*, compareProducts >::const_iterator it;
  std::set<CNormalProduct*, compareProducts >::const_iterator itEnd = mProducts.end();
  for (it = mProducts.begin(); it != itEnd; ++it)
    delete *it;

  std::set<CNormalFraction*>::const_iterator it2;
  std::set<CNormalFraction*>::const_iterator it2End = mFractions.end();
  for (it2 = mFractions.begin(); it2 != it2End; ++it2)
    delete *it2;
}

/**
 * Retrieve the number of summands of this sum.
 * @return int
 */
int CNormalSum::getSize() const
  {
    return mProducts.size() + mFractions.size();
  }

/**
 * Add product to this sum.
 * @return true.
 */
bool CNormalSum::add(const CNormalProduct& product)
{
  if (fabs(product.getFactor()) < 1.0E-100)
    return true;
  std::set<CNormalProduct*, compareProducts >::iterator it;
  std::set<CNormalProduct*, compareProducts >::iterator itEnd = mProducts.end();
  for (it = mProducts.begin(); it != itEnd; ++it)
    {
      if ((*it)->checkSamePowerList(product))
        {
          (*it)->setFactor((*it)->getFactor() + product.getFactor());
          return true;
        }
    }
  CNormalProduct* tmp = new CNormalProduct(product);
  mProducts.insert(tmp);
  return true;
}

/**
 * Add fraction to this sum.
 * @return true.
 */
bool CNormalSum::add(const CNormalFraction& fraction)
{
  if (fraction.getNumerator().getSize() == 0)
    return true;
  std::set<CNormalFraction*>::iterator it;
  std::set<CNormalFraction*>::iterator itEnd = mFractions.end();
  for (it = mFractions.begin(); it != itEnd; ++it)
    {
      if (**it == fraction)
        {
          (*it)->multiply(2.0);
          return true;
        }
    }
  CNormalFraction* tmp = new CNormalFraction(fraction);
  mFractions.insert(tmp);
  return true;
}

/**
 * Add a sum to this sum.
 * @return true.
 */
bool CNormalSum::add(const CNormalSum& sum)
{
  std::set<CNormalProduct*, compareProducts >::const_iterator itProduct;
  std::set<CNormalProduct*, compareProducts >::const_iterator itProductEnd = sum.getProducts().end();
  for (itProduct = sum.getProducts().begin(); itProduct != itProductEnd; ++itProduct)
    add(**itProduct);

  std::set<CNormalFraction*>::const_iterator itFraction;
  std::set<CNormalFraction*>::const_iterator itFractionEnd = sum.getFractions().end();
  for (itFraction = sum.getFractions().begin(); itFraction != itFractionEnd; ++itFraction)
    add(**itFraction);

  return true;
}

/**
 * Multiply this sum with a number.
 * @return true.
 */
bool CNormalSum::multiply(const C_FLOAT64& number)
{
  if (fabs(number) < 1.0E-100)
    {
      std::set<CNormalProduct*, compareProducts >::iterator it3;
      std::set<CNormalProduct*, compareProducts >::iterator it3End = mProducts.end();
      for (it3 = mProducts.begin(); it3 != it3End; ++it3)
        delete *it3;

      std::set<CNormalFraction*>::iterator it4;
      std::set<CNormalFraction*>::iterator it4End = mFractions.end();
      for (it4 = mFractions.begin(); it4 != it4End; ++it4)
        delete *it4;

      return true;
    }

  std::set<CNormalProduct*, compareProducts >::iterator it;
  std::set<CNormalProduct*, compareProducts >::iterator itEnd = mProducts.end();
  for (it = mProducts.begin(); it != itEnd; ++it)
    (*it)->multiply(number);

  std::set<CNormalFraction*>::iterator it2;
  std::set<CNormalFraction*>::iterator it2End = mFractions.end();
  for (it2 = mFractions.begin(); it2 != it2End; ++it2)
    (*it2)->multiply(number);

  return true;
}

/**
 * Multiply this sum with an itempower.
 * @return true.
 */
bool CNormalSum::multiply(const CNormalItemPower& itemPower)
{
  std::set<CNormalProduct*, compareProducts >::iterator it;
  std::set<CNormalProduct*, compareProducts >::iterator itEnd = mProducts.end();
  for (it = mProducts.begin(); it != itEnd; ++it)
    (*it)->multiply(itemPower);

  std::set<CNormalFraction*>::iterator it2;
  std::set<CNormalFraction*>::iterator it2End = mFractions.end();
  for (it2 = mFractions.begin(); it2 != it2End; ++it2)
    (*it2)->multiply(itemPower);

  return true;
}

/**
 * Multiply this sum with another sum, both do not contain fractions!!
 * @return true.
 */
bool CNormalSum::multiply(const CNormalSum& sum)
{
  std::set<CNormalProduct*, compareProducts > tmpProducts = mProducts;
  mProducts.clear();
  std::set<CNormalProduct*, compareProducts >::iterator it;
  std::set<CNormalProduct*, compareProducts >::iterator itEnd = tmpProducts.end();
  for (it = tmpProducts.begin(); it != itEnd; ++it)
    {
      add(*(*it)->multiply(sum));
      delete *it;
    }
  return true;
}

/**
 * Multiply this sum by a lcm
 * Numerator and denominator of mFractions do not contain further fractions!
 * @return true.
 */
bool CNormalSum::multiply(const CNormalLcm& lcm)
{
  std::set<CNormalProduct*, compareProducts > tmpProducts = mProducts;
  mProducts.clear();
  std::set<CNormalProduct*, compareProducts >::const_iterator it2;
  std::set<CNormalProduct*, compareProducts >::const_iterator it2End = tmpProducts.end();
  for (it2 = tmpProducts.begin(); it2 != it2End; ++it2)
    {
      const CNormalSum* summand = (*it2)->multiply(lcm);
      add(*summand);
      delete summand;
      delete *it2;
    }

  std::set<CNormalFraction*>::const_iterator it;
  std::set<CNormalFraction*>::const_iterator itEnd = mFractions.end();
  for (it = mFractions.begin(); it != itEnd; ++it)
    {
      const CNormalSum* summand2 = (*it)->multiply(lcm);
      add(*summand2);
      delete summand2;
      delete *it;
    }
  mFractions.clear();  //after multiplication this sum does not contain fractions anymore
  return true;
}

/**
 * Divide this sum by an itempower, provided it is a factor of it
 * -This sum does not contain fractions!
 * @return true.
 */
bool CNormalSum::divide(const CNormalItemPower& itemPower)
{
  std::set<CNormalProduct*, compareProducts >::iterator it;
  std::set<CNormalProduct*, compareProducts >::iterator itEnd = mProducts.end();
  for (it = mProducts.begin(); it != itEnd; ++it)
    (*it)->remove(itemPower);
  return true;
}

C_FLOAT64 CNormalSum::checkFactor(const CNormalItemPower& itemPower) const //sum does not contain fractions!!
  {
    C_FLOAT64 exp = itemPower.getExp();
    std::set<CNormalProduct*, compareProducts >::const_iterator it;
    std::set<CNormalProduct*, compareProducts >::const_iterator itEnd = mProducts.end();
    for (it = mProducts.begin(); it != itEnd; ++it)
      {
        bool containsFactor = false;
        std::set<CNormalItemPower*, compareItemPowers >::const_iterator it2;
        std::set<CNormalItemPower*, compareItemPowers >::const_iterator it2End = (*it)->getItemPowers().end();
        for (it2 = (*it)->getItemPowers().begin(); it2 != it2End; ++it2)
          {
            if ((*it2)->getItem().areEqual(itemPower.getItem()))
              {
                exp = (*it2)->getExp() < exp ? (*it2)->getExp() : exp;
                containsFactor = true;
                break;
              }
          }
        if (containsFactor == false)
          return 0;
      }
    return exp;
  }

/**
 * Retrieve the set of products of this sum.
 * @return mProducts
 */
const std::set<CNormalProduct*, compareProducts >& CNormalSum::getProducts() const
  {
    return mProducts;
  }

/**
 * Retrieve the set of fractions of this sum.
 * @return mFractions.
 */
const std::set<CNormalFraction*>& CNormalSum::getFractions() const
  {
    return mFractions;
  }

/**
 * Examine equality of two sums.
 * @return bool.
 */
bool CNormalSum::operator==(const CNormalSum & rhs) const
  {
    if (mProducts.size() != rhs.mProducts.size())
      return false;
    if (mFractions.size() != rhs.mFractions.size())
      return false;
    std::set<CNormalProduct*, compareProducts >::const_iterator it;
    std::set<CNormalProduct*, compareProducts >::const_iterator itEnd = this->mProducts.end();
    std::set<CNormalProduct*, compareProducts >::const_iterator it2;
    std::set<CNormalProduct*, compareProducts >::const_iterator it2End = rhs.mProducts.end();
    for (it = mProducts.begin(), it2 = rhs.mProducts.begin(); it != itEnd; ++it, ++it2)
      {
        if (!(**it == **it2))
          return false;
      }
    std::set<CNormalFraction*>::const_iterator it3;
    std::set<CNormalFraction*>::const_iterator it3End = this->mFractions.end();
    std::set<CNormalFraction*>::const_iterator it4;
    std::set<CNormalFraction*>::const_iterator it4End = rhs.mFractions.end();
    for (it3 = mFractions.begin(), it4 = rhs.mFractions.begin(); it3 != it3End; ++it3, ++it4)
      {
        if (!(**it3 == **it4))
          return false;
      }
    return true;
  }

std::ostream & operator<< (std::ostream &os, const CNormalSum & d)
{
  os << d.toString();
  return os;
}

std::string CNormalSum::toString() const
  {
    std::ostringstream os;
    if (this->getSize() != 0)
      {
        bool firstSummand = true;
        std::set<CNormalProduct*, compareProducts >::const_iterator it;
        std::set<CNormalProduct*, compareProducts >::const_iterator itEnd = this->mProducts.end();
        for (it = this->mProducts.begin(); it != itEnd; ++it)
          {
            if (firstSummand == false)
              os << " + ";
            os << **it;
            firstSummand = false;
          }
        std::set<CNormalFraction*>::const_iterator it2;
        std::set<CNormalFraction*>::const_iterator it2End = this->mFractions.end();
        for (it2 = this->mFractions.begin(); it2 != it2End; ++it2)
          {
            if (firstSummand == false)
              os << " + ";
            os << **it2;
            firstSummand = false;
          }
      }
    else
      os << "0.0";
    return os.str();
  }

CNormalBase * CNormalSum::copy() const
  {
    return new CNormalSum(*this);
  }

bool CNormalSum::operator<(const CNormalSum& rhs) const
  {
    bool result = false;
    if (this->mFractions.size() < rhs.mFractions.size())
      {
        result = true;
      }
    else if (this->mFractions.size() == rhs.mFractions.size())
      {
        std::set<CNormalFraction*>::const_iterator it = this->mFractions.begin(), endit = this->mFractions.end();
        std::set<CNormalFraction*>::const_iterator it2 = rhs.mFractions.begin(), endit2 = rhs.mFractions.end();
        while (result == false && it != endit)
          {
            if ((**it) < (**it2))
              {
                result = true;
              }
            // if the fraction from the RHS is smaller than the one from here we
            // stop and declare that the rhs is smaller
            else if (!((**it) == (**it2)))
              {
                break;
              }
            ++it;
            ++it2;
          }
        // if all fractions were equal
        if (result == false && it == endit)
          {
            if (this->mProducts.size() < rhs.mProducts.size())
              {
                result = true;
              }
            else if (this->mProducts.size() == rhs.mProducts.size())
              {
                std::set<CNormalProduct*, compareProducts>::const_iterator it3 = this->mProducts.begin(), endit3 = this->mProducts.end();
                std::set<CNormalProduct*, compareProducts>::const_iterator it4 = rhs.mProducts.begin(), endit4 = rhs.mProducts.end();
                // I can not use the sorter to compare because the sorter does
                // not take the factor of a product into account.
                // This is a feature, but a bug
                while (result == false && it3 != endit3)
                  {
                    if ((**it3) < (**it4))
                      {
                        result = true;
                      }
                    // if the fraction from the RHS is smaller than the one from here we
                    // stop and declare that the rhs is smaller
                    else if (!((**it3) == (**it4)))
                      {
                        break;
                      }
                    ++it3;
                    ++it4;
                  }
              }
          }
      }
    return result;
  }

void CNormalSum::setProducts(const std::set<CNormalProduct*, compareProducts>& set)
{
  std::set<CNormalProduct*, compareProducts>::const_iterator it = this->mProducts.begin(), endit = this->mProducts.end();
  while (it != endit)
    {
      delete *it;
      ++it;
    }
  it = set.begin(), endit = set.end();
  this->mProducts.clear();
  while (it != endit)
    {
      this->mProducts.insert(new CNormalProduct(**it));
      ++it;
    }
}

void CNormalSum::setFractions(const std::set<CNormalFraction*>& set)
{
  std::set<CNormalFraction*>::const_iterator it = this->mFractions.begin(), endit = this->mFractions.end();
  while (it != endit)
    {
      delete *it;
      ++it;
    }
  it = set.begin(), endit = set.end();
  this->mFractions.clear();
  while (it != endit)
    {
      this->mFractions.insert(new CNormalFraction(**it));
      ++it;
    }
}

bool CNormalSum::simplify()
{
  bool result = true;
  std::set<CNormalProduct*, compareProducts>::iterator it = this->mProducts.begin(), endit = this->mProducts.end();
  while (it != endit)
    {
      (*it)->simplify();
      ++it;
    }
  it = this->mProducts.begin(), endit = this->mProducts.end();
  // TODO add code to find general power items with exponent 1 where the parent
  // TODO power item also has exponent 1
  // TODO if the base of those has a denominator of 1, we add the products of
  // TODO the numerator to this sum, otherwise, we have to add the whole base
  // TODO to the fractions of this sum
  // TODO afterwards, we have to simplify all products and all fractions again
  std::vector<CNormalProduct*> remainingProducts;
  while (it != endit)
    {
      if ((*it)->getItemPowers().size() == 1 &&
          fabs(((*(*it)->getItemPowers().begin())->getExp() - 1.0) / 1.0) < 1e-12 &&
          (*(*it)->getItemPowers().begin())->getItemType() == CNormalItemPower::POWER &&
          ((CNormalGeneralPower&)(*(*it)->getItemPowers().begin())->getItem()).getRight().checkNumeratorOne() &&
          ((CNormalGeneralPower&)(*(*it)->getItemPowers().begin())->getItem()).getRight().checkDenominatorOne()
)
        {
          if (((CNormalGeneralPower&)(*(*it)->getItemPowers().begin())->getItem()).getLeft().checkDenominatorOne())
            {
              this->add(((CNormalGeneralPower&)(*(*it)->getItemPowers().begin())->getItem()).getLeft().getNumerator());
            }
          else
            {
              this->add(((CNormalGeneralPower&)(*(*it)->getItemPowers().begin())->getItem()).getLeft());
            }
          delete (*it);
        }
      else
        {
          remainingProducts.push_back((*it));
        }
      ++it;
    }
  this->mProducts.clear();
  this->mProducts.insert(remainingProducts.begin(), remainingProducts.end());
  std::set<CNormalFraction*>::iterator it2 = this->mFractions.begin(), endit2 = this->mFractions.end();
  while (it2 != endit2)
    {
      (*it2)->simplify();
      ++it2;
    }
  return result;
}
