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
#include <cmath>
#include <sstream>

#include "copasi/copasi.h"

#include "CNormalItemPower.h"
#include "CNormalProduct.h"
#include "CNormalLcm.h"
#include "CNormalFraction.h"
#include "CNormalSum.h"
#include "CNormalGeneralPower.h"

#include "copasi/utilities/CCopasiMessage.h"

bool compareProducts::operator()(const CNormalProduct* product1, const CNormalProduct* product2) const
{
  // first compare the factors
  if (product1->getFactor() < product2->getFactor())
    {
      return true;
    }
  else if (product2->getFactor() < product1->getFactor())
    {
      return false;
    }

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
  const CNormalProduct* pTmpProduct = NULL;

  for (it = src.mProducts.begin(); it != itEnd; ++it)
    {
      pTmpProduct = *it;
      //std::string s = pTmpProduct->toString();
      bool tmpRes = mProducts.insert(new CNormalProduct(*pTmpProduct)).second;
      assert(tmpRes == true);
    }

  std::set<CNormalFraction*>::const_iterator it2;
  std::set<CNormalFraction*>::const_iterator it2End = src.mFractions.end();

  for (it2 = src.mFractions.begin(); it2 != it2End; ++it2)
    {
      bool tmpRes = mFractions.insert(new CNormalFraction(**it2)).second;
      assert(tmpRes == true);
    }
}

/**
 * Assignment operator
 */
CNormalSum & CNormalSum::operator=(const CNormalSum & src)
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
    {
      return true;
    }

  std::set<CNormalProduct*, compareProducts >::iterator it = mProducts.begin();
  std::set<CNormalProduct*, compareProducts >::iterator itEnd = mProducts.end();

  while (it != itEnd)
    {
      if ((*it)->checkSamePowerList(product))
        {
          (*it)->setFactor((*it)->getFactor() + product.getFactor());

          // if this results in a 0, remove the item
          if (fabs((*it)->getFactor()) < 1.0E-100)
            {
              //unsigned int count=this->mProducts.size();
              mProducts.erase(it);
              //assert(count == this->mProducts.size()+1);
            }

          return true;
        }

      ++it;
    }

  CNormalProduct* tmp = new CNormalProduct(product);
  /*bool result=*/mProducts.insert(tmp);//.second;
  //assert(result == true);
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
  std::set<CNormalProduct*, compareProducts >::const_iterator itProduct = sum.mProducts.begin();
  std::set<CNormalProduct*, compareProducts >::const_iterator itProductEnd = sum.mProducts.end();

  while (itProduct != itProductEnd)
    {
      add(**itProduct);
      ++itProduct;
    }

  std::set<CNormalFraction*>::const_iterator itFraction = sum.getFractions().begin();
  std::set<CNormalFraction*>::const_iterator itFractionEnd = sum.getFractions().end();

  while (itFraction != itFractionEnd)
    {
      add(**itFraction);
      ++itFraction;
    }

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
  CNormalSum* pSum = NULL;

  for (it = tmpProducts.begin(); it != itEnd; ++it)
    {
      pSum = (*it)->multiply(sum);
      assert(pSum != NULL);
      add(*pSum);
      delete pSum;
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
  //std::string s = lcm.toString();
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
      //std::string s2 = (*it)->toString();
      assert(summand2 != NULL);
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
  // TODO incorporate the denominator of the product if it is not 1
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
  //std::set<CNormalProduct*, compareProducts >::const_iterator it2End = rhs.mProducts.end();

  for (it = mProducts.begin(), it2 = rhs.mProducts.begin(); it != itEnd; ++it, ++it2)
    {
      if (!(**it == **it2))
        return false;
    }

  std::set<CNormalFraction*>::const_iterator it3;
  std::set<CNormalFraction*>::const_iterator it3End = this->mFractions.end();
  std::set<CNormalFraction*>::const_iterator it4;
  //std::set<CNormalFraction*>::const_iterator it4End = rhs.mFractions.end();

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
      std::set<CNormalFraction*>::const_iterator it2 = rhs.mFractions.begin();//, endit2 = rhs.mFractions.end();

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
              std::set<CNormalProduct*, compareProducts>::const_iterator it4 = rhs.mProducts.begin();//, endit4 = rhs.mProducts.end();

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
  // it is a bad idea to work directly on the items in the set.
  // this messes up the set
  // better copy the set first
  std::set<CNormalFraction*> fractionsCopy(this->mFractions);
  this->mFractions.clear();
  std::set<CNormalFraction*>::iterator it3 = fractionsCopy.begin(), endit3 = fractionsCopy.end();
  CNormalFraction* pTmpFraction = NULL;

  while (it3 != endit3)
    {
      pTmpFraction = *it3;
      pTmpFraction->simplify();
      this->add(*pTmpFraction);
      delete pTmpFraction;
      ++it3;
    }

  std::set<CNormalProduct*, compareProducts>::iterator it = this->mProducts.begin(), endit = this->mProducts.end();
  // add code to find general power items with exponent 1 where the parent
  // power item also has exponent 1
  // if the base of those has a denominator of 1, we add the products of
  // the numerator to this sum, otherwise, we have to add the whole base
  // to the fractions of this sum
  // afterwards, we have to simplify all products and all fractions again
  std::vector<CNormalBase*> newProducts;
  // go through all products and check the denominators
  CNormalProduct* pTmpProduct;
  CNormalBase* pTmpProduct2;

  while (it != endit)
    {
      pTmpProduct = *it;
      pTmpProduct->simplify();

      if (pTmpProduct->getItemPowers().size() == 1 &&
          fabs(((*pTmpProduct->getItemPowers().begin())->getExp() - 1.0) / 1.0) < 1e-12 &&
          (*pTmpProduct->getItemPowers().begin())->getItemType() == CNormalItemPower::POWER &&
          ((CNormalGeneralPower&)(*pTmpProduct->getItemPowers().begin())->getItem()).getRight().checkNumeratorOne() &&
          ((CNormalGeneralPower&)(*pTmpProduct->getItemPowers().begin())->getItem()).getRight().checkDenominatorOne()
         )
        {
          if (((CNormalGeneralPower&)(*pTmpProduct->getItemPowers().begin())->getItem()).getLeft().checkDenominatorOne())
            {
              // this copy returns a CNormalSum
              // in order to keep the factor, we have to multiply
              // the sum with the factor
              pTmpProduct2 = ((CNormalGeneralPower&)(*pTmpProduct->getItemPowers().begin())->getItem()).getLeft().getNumerator().copy();
              dynamic_cast<CNormalSum*>(pTmpProduct2)->multiply(pTmpProduct->getFactor());
              newProducts.push_back(pTmpProduct2);
            }
          else
            {
              // this copy returns a fraction
              // so in order to retain the factor, we need to multiply the fraction with
              // a factor
              pTmpProduct2 = ((CNormalGeneralPower&)(*pTmpProduct->getItemPowers().begin())->getItem()).getLeft().copy();
              dynamic_cast<CNormalFraction*>(pTmpProduct2)->multiply(pTmpProduct->getFactor());
              newProducts.push_back(pTmpProduct2);
            }

          delete pTmpProduct;
        }
      else
        {
          // if the denominator is not NULL, transform the product to a fraction
          CNormalGeneralPower* pDenom = pTmpProduct->getDenominator();

          if (pDenom == NULL || pDenom->checkIsOne())
            {
              newProducts.push_back(pTmpProduct);
            }
          else
            {
              // before creating the product, the denominators of all general items in
              // the product have to be set to 1 by calling setDenominatorsOne on the product
              pTmpProduct->setDenominatorsOne();
              CNormalFraction* pFraction = NULL;

              if (pDenom->getRight().checkIsOne())
                {
                  // the denominator is the left side of pDenom
                  pFraction = new CNormalFraction(pDenom->getLeft());
                  //
                  //pFraction = new CNormalFraction(pDenom->getLeft());
                  //// now we set the numerator
                  //CNormalSum* pSum = new CNormalSum();
                  //pSum->add(**it);
                  //pFraction->setNumerator(*pSum);
                  //delete pSum;
                }
              else
                {
                  // the fraction has the found denominator as its denominator and the
                  // numerator is the product of all items
                  pFraction = new CNormalFraction();
                  CNormalSum* pSum = new CNormalSum();
                  pSum->add(*pTmpProduct);
                  pFraction->setNumerator(*pSum);
                  delete pSum;
                  // now we have to invert the general fraction that is the
                  // denominator
                  CNormalFraction* pTmpFraction = CNormalFraction::createUnitFraction();
                  CNormalSum* pTmpSum = new CNormalSum(pDenom->getLeft().getDenominator());
                  pTmpFraction->setNumerator(*pTmpSum);
                  delete pTmpSum;
                  pDenom->setLeft(*pTmpFraction);
                  delete pTmpFraction;
                  CNormalProduct* pTmpProduct = CNormalProduct::createUnitProduct();
                  CNormalItemPower* pTmpItemPower = new CNormalItemPower();
                  pTmpItemPower->setExp(1.0);
                  pTmpItemPower->setItem(*pDenom);
                  pTmpProduct->multiply(*pTmpItemPower);
                  delete pTmpItemPower;
                  pTmpSum = new CNormalSum();
                  pTmpSum->add(*pTmpProduct);
                  delete pTmpProduct;
                  pFraction->setDenominator(*pTmpSum);
                  delete pTmpSum;
                }

              delete pTmpProduct;
              newProducts.push_back(pFraction);
            }

          if (pDenom != NULL) delete pDenom;
        }

      ++it;
    }

  this->mProducts.clear();
  std::vector<CNormalBase*>::const_iterator it2 = newProducts.begin(), endit2 = newProducts.end();
  const CNormalFraction* pFrac = NULL;
  const CNormalSum* pSum = NULL;
  const CNormalProduct* pProd = NULL;
  std::set<CNormalSum*> multipliers;

  while (it2 != endit2)
    {
      pProd = dynamic_cast<const CNormalProduct*>(*it2);

      if (pProd != NULL)
        {
          this->add(*pProd);
        }
      else
        {
          pFrac = dynamic_cast<const CNormalFraction*>(*it2);

          if (pFrac != NULL)
            {
              this->add(*pFrac);
            }
          else
            {
              pSum = dynamic_cast<const CNormalSum*>(*it2);

              if (pSum != NULL)
                {
                  this->add(*pSum);
                  /*
                  // check if the sum contains more then one product
                  // we have to multiply the sum with that other sum in the end
                  if(pSum->getProducts().size()>1)
                  {
                    multipliers.insert(static_cast<CNormalSum*>(pSum->copy()));
                  }
                  else
                  {
                    if(pSum->getProducts().size()==1 && (*pSum->getProducts().begin())->getItemPowers.size()==1)
                    {
                        // check if the one item power is a general power with
                        // an exponent of one and a denominator of one.
                        const CNormalItemPower* pPower=(*(*pSum->getProducts().begin())->getItemPowers().begin());
                        if(fabs(pPow->getExp()-1.0/1.0)<1e-12 && pPower->getItemType()==CNormalItemPower::POWER)
                        {
                            // check if it is a power operator and not modulo,
                            // check if the exponent is one and the denominator
                            // is one
                            const CNormalGeneralPower* pGenPow=static_cast<const CNormalGeneralPower*>(pPower->getItem());
                            if(pGenPow->getType()==CNormalGeneralPower::POWER && pGenPower->getRight().checkIsOne() && pGenPower->getLeft().checkDenominatorOne())
                            {
                                // check if there are more then one product in
                            }
                            else
                            {
                                this->add(*pSum);
                            }
                        }
                        else
                        {
                            this->add(*pSum);
                        }
                    }
                    else
                    {
                      this->add(*pSum);
                    }
                  }*/
                }
              else
                {
                  // this can never happen
                  fatalError();
                }
            }
        }

      delete *it2;
      ++it2;
    }

  std::set<CNormalSum*>::iterator it4 = multipliers.begin(), endit4 = multipliers.end();

  while (it4 != endit4)
    {
      this->multiply(**it4);
      delete *it4;
      ++it4;
    }

  return result;
}

bool CNormalSum::checkIsOne() const
{
  bool result = false;

  if ((mProducts.size() == 1))
    {

      CNormalGeneralPower* pTmpPow = (*mProducts.begin())->getDenominator();

      if ((mFractions.size() == 0)
          && ((*mProducts.begin())->getItemPowers().size() == 0)
          && (fabs((*mProducts.begin())->getFactor() - 1.0) < 1.E-100)
          && ((pTmpPow == NULL) || (pTmpPow->checkIsOne()))
         )
        {
          result = true;
        }

      if (pTmpPow != NULL) delete pTmpPow;
    }

  return result;
}

bool CNormalSum::checkIsZero() const
{
  // fractions must be zero and products must be either 0 or 1 with a
  // factor of 0.0
  if (mFractions.size() == 0 &&
      (mProducts.size() == 0
       || (mProducts.size() == 1 && ((*mProducts.begin())->getItemPowers().size() == 0) && (fabs((*mProducts.begin())->getFactor() - 0.0) < 1.E-100)))
     )
    {
      return true;
    }

  return false;
}

CNormalSum* CNormalSum::createUnitSum()
{
  CNormalSum* pSum = new CNormalSum();
  CNormalProduct* pTmpProduct = CNormalProduct::createUnitProduct();
  pSum->add(*pTmpProduct);
  delete pTmpProduct;
  return pSum;
}

void CNormalSum::printProducts(const CNormalSum* pSum)
{
  std::set<CNormalProduct*, compareProducts >::const_iterator it = pSum->mProducts.begin();
  std::set<CNormalProduct*, compareProducts >::const_iterator itEnd = pSum->mProducts.end();
  std::cout << "products: " << std::endl;

  while (it != itEnd)
    {
      std::cout << (*it)->toString() << std::endl;
      ++it;
    }

  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

}
