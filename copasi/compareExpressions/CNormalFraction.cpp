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

#include "CNormalProduct.h"
#include "CNormalSum.h"
#include "CNormalLcm.h"
#include "CNormalItemPower.h"
#include "CNormalFraction.h"
//#include "CNormalLogical.h"
//#include "CNormalChoice.h"

/**
 * Default constructor
 */
CNormalFraction::CNormalFraction(): CNormalBase(), mpNumerator(new CNormalSum()), mpDenominator(new CNormalSum()) {}

/**
 * Copy contructor
 */
CNormalFraction::CNormalFraction(const CNormalFraction& src): CNormalBase(src),
  mpNumerator(new CNormalSum(*src.mpNumerator)),
  mpDenominator(new CNormalSum(*src.mpDenominator)) {}

/**
 * Assignment operator
 */
CNormalFraction& CNormalFraction::operator=(const CNormalFraction & src)
{
  if (this->mpNumerator != NULL) delete this->mpNumerator;

  if (this->mpDenominator != NULL) delete this->mpDenominator;

  this->mpNumerator = new CNormalSum(*src.mpNumerator);
  this->mpDenominator = new CNormalSum(*src.mpDenominator);
  return *this;
}

CNormalFraction::~CNormalFraction()
{
  if (mpNumerator != NULL) delete mpNumerator;

  if (mpDenominator != NULL) delete mpDenominator;
}

/**
 * Set numerator of this fraction
 * @return true.
 */
bool CNormalFraction::setNumerator(const CNormalSum& numerator)
{
  if (mpNumerator != NULL)
    {
      delete mpNumerator;
    }

  mpNumerator = new CNormalSum(numerator);
  return true;
}

/**
 * Set denominator of this fraction.
 * @return true.
 */
bool CNormalFraction::setDenominator(const CNormalSum& denominator)
{
  if (mpDenominator != NULL)
    {
      delete mpDenominator;
    }

  mpDenominator = new CNormalSum(denominator);

  if (mpDenominator->getSize() == 0)
    return false;

  return true;
}

/**
 * Check if the denominator of this fraction equals 1.
 * @return bool
 */
bool CNormalFraction::checkNumeratorOne() const
{
  return this->mpNumerator->checkIsOne();
}

/**
 * Check if the denominator of this fraction equals 1.
 * @return bool
 */
bool CNormalFraction::checkDenominatorOne() const
{
  return this->mpDenominator->checkIsOne();
}

/**
 * Set the denominator of this fraction equal 1.
 * @return true.
 */
bool CNormalFraction::setDenominatorOne()
{
  CNormalProduct* product = new CNormalProduct();
  CNormalSum* sum = new CNormalSum();
  sum->add(*product);
  delete product;
  setDenominator(*sum);
  delete sum;
  return true;
}

/**
 * Retrieve the numerator of this fraction.
 * @return mpNumerator.
 */
CNormalSum& CNormalFraction::getNumerator()
{
  return *mpNumerator;
}

/**
 * Retrieve the denominator of this fraction.
 * @return mpDenominator.
 */
CNormalSum& CNormalFraction::getDenominator()
{
  return *mpDenominator;
}

/**
 * Retrieve the numerator of this fraction.
 * @return mpNumerator.
 */
const CNormalSum& CNormalFraction::getNumerator() const
{
  return *mpNumerator;
}

/**
 * Retrieve the denominator of this fraction.
 * @return mpDenominator.
 */
const CNormalSum& CNormalFraction::getDenominator() const
{
  return *mpDenominator;
}

/**
 * Check if this fraction contains further fractions.
 * @return bool.
 */
bool CNormalFraction::checkForFractions() const
{
  if (mpNumerator->getFractions().size() + mpDenominator->getFractions().size() == 0)
    return false;

  return true;
}

/**
 * Expand this fraction by a lcm.
 * @return true.
 */
bool CNormalFraction::expand(const CNormalLcm& lcm)
{
  mpNumerator->multiply(lcm);
  mpDenominator->multiply(lcm);

  if (mpDenominator->getSize() == 0)
    return false;

  return true;
}

/**
 * Cancel common items of mpNumerator and mpDenominator.
 * @return true.
 */
bool CNormalFraction::cancel()
{
  if (mpNumerator->getProducts().size() != 0 || mpNumerator->getFractions().size() != 0 || mpDenominator->getProducts().size() != 0 || mpDenominator->getFractions().size() != 0)
    {
      if (*mpDenominator == *mpNumerator)
        {
          setDenominatorOne();
          setNumerator(*mpDenominator);
          return true;
        }

      if (mpDenominator->getProducts().size() != 0)
        {
          C_FLOAT64 factor = (*mpDenominator->getProducts().begin())->getFactor();

          if (fabs(factor) < 1.0E-100)
            return false;
          else
            {
              mpNumerator->multiply(1.0 / factor);  //factor != 0 as checked earlier
              mpDenominator->multiply(1.0 / factor);
            }
        }

      if (checkForFractions() == false)
        {
          if (mpDenominator->getProducts().size() != 0 && (*mpDenominator->getProducts().begin())->getItemPowers().size() != 0)
            {
              std::set<CNormalItemPower*, compareItemPowers >::const_iterator it = (*mpDenominator->getProducts().begin())->getItemPowers().begin();
              std::set<CNormalItemPower*, compareItemPowers >::const_iterator itEnd = (*mpDenominator->getProducts().begin())->getItemPowers().end();
              std::vector<CNormalItemPower*> tmpV;

              while (it != itEnd)
                {
                  //runs through all item powers in the first product of the denominator
                  C_FLOAT64 exp = mpNumerator->checkFactor(**it);

                  if (fabs(exp) >= 1.0E-100)
                    {
                      exp = mpDenominator->checkFactor(**it) < exp ? mpDenominator->checkFactor(**it) : exp;

                      if (fabs(exp) >= 1.0E-100)
                        {
                          CNormalItemPower* itemPower = new CNormalItemPower((*it)->getItem(), exp);
                          tmpV.push_back(itemPower);
                        }
                    }

                  ++it;
                }

              std::vector<CNormalItemPower*>::iterator it2 = tmpV.begin();
              std::vector<CNormalItemPower*>::iterator itEnd2 = tmpV.end();

              while (it2 != itEnd2)
                {
                  mpNumerator->divide(**it2);
                  mpDenominator->divide(**it2);
                  delete *it2;
                  ++it2;
                }
            }
        }
    }

  return true;
}

/**
 * Multiply this fraction with a number.
 * @return true.
 */
bool CNormalFraction::multiply(const C_FLOAT64& number)
{
  mpNumerator->multiply(number);

  if (mpNumerator->getSize() == 0)
    setDenominatorOne();

  return true;
}

/**
 * Multiply a fraction with an itempower.
 * @return true.
 */
bool CNormalFraction::multiply(const CNormalItemPower& itemPower)
{
  C_FLOAT64 exp = mpDenominator->checkFactor(itemPower);
  C_FLOAT64 tmpExp;

  if (fabs(exp) >= 1.0E-100)
    {
      CNormalItemPower* pTmp1 = new CNormalItemPower(itemPower.getItem(), exp);
      mpDenominator->divide(*pTmp1);
      delete pTmp1;

      if ((tmpExp = fabs(itemPower.getExp() - exp)) >= 1.0E-100)
        {
          // :TODO: Memory leak?
          CNormalItemPower * pTmp2 =
            new CNormalItemPower(itemPower.getItem(), tmpExp);
          mpNumerator->multiply(*pTmp2);
          delete pTmp2;
          return true;
        }

      return true;
    }
  else
    mpNumerator->multiply(itemPower);

  return true;
}

/**
 * Find lcm of denominators of respective fractions contained in this fraction.
 * @return pointer to lcm.
 */
const CNormalLcm* CNormalFraction::findLcm() const
{
  CNormalLcm* lcm = new CNormalLcm();

  std::set<CNormalFraction*>::const_iterator it;
  std::set<CNormalFraction*>::const_iterator itEnd = mpNumerator->getFractions().end();

  for (it = mpNumerator->getFractions().begin(); it != itEnd; ++it)
    {
      lcm->add((*it)->getDenominator());
    }

  std::set<CNormalFraction*>::const_iterator it2;
  std::set<CNormalFraction*>::const_iterator it2End = mpDenominator->getFractions().end();

  for (it2 = mpDenominator->getFractions().begin(); it2 != it2End; ++it2)
    {
      lcm->add((*it2)->getDenominator());
    }

  return lcm;
}

/**
 * Multiply this fraction by a lcm.
 * @return CNormalSum*, pointer to result of multiplication ie. a normal sum.
 * This fraction is useless now.
 */
const CNormalSum* CNormalFraction::multiply(CNormalLcm lcm)
{
  if (mpDenominator->getFractions().size() != 0)
    {
      return NULL;
    }

  if (lcm.remove(*mpDenominator) == false)
    {
      return NULL;
    }

  mpNumerator->multiply(lcm);
  CNormalSum * sum = new CNormalSum(*mpNumerator);
  return sum;
}

/**
 * Check if numerator and denominator contain fractions,
 * find lcm of respective denominators, expand this fraction by lcm and cancel.
 * @return true
 */
bool CNormalFraction::simplify()
{
  bool result = true;
  result = this->mpNumerator->simplify();

  if (result == true)
    {
      result = this->mpDenominator->simplify();
    }

  if (result == true)
    {
      if (mpNumerator->getFractions().size() + mpDenominator->getFractions().size() > 0)
        {
          // TODO  the following code does not work if there are fractions left.
          const CNormalLcm* lcm = findLcm();
          assert(expand(*lcm) == true);
          delete lcm;
        }
    }

  cancel();
  return result;
}

bool CNormalFraction::operator==(const CNormalFraction & rhs) const
{
  if ((*mpNumerator == *rhs.mpNumerator) && (*mpDenominator == *rhs.mpDenominator))
    return true;
  else
    return false;
}

std::ostream & operator<< (std::ostream &os, const CNormalFraction & d)
{
  os << d.toString();
  return os;
}

std::string CNormalFraction::toString() const
{
  std::ostringstream os;

  if (this->checkDenominatorOne() == true)
    {
      os << *this->mpNumerator;
    }
  else
    {
      os << "(" << *this->mpNumerator << ")/(" << *this->mpDenominator << ")";
    }

  return os.str();
}

CNormalBase * CNormalFraction::copy() const
{
  return new CNormalFraction(*this);
}

bool CNormalFraction::operator<(const CNormalFraction& src) const
{
  bool result = false;

  if ((*this->mpNumerator) < (*src.mpNumerator))
    {
      result = true;
    }
  else if ((*this->mpNumerator) == (*src.mpNumerator))
    {
      if ((*this->mpDenominator) < (*src.mpDenominator))
        {
          result = true;
        }
    }

  return result;
}

/*
std::set<const CNormalLogical*> CNormalFraction::findLogicals() const
{
    std::set<const CNormalLogical*> set;
    std::set<CNormalProduct*>::const_iterator it=this->mpDenominator->getProducts().begin();
    std::set<CNormalProduct*>::const_iterator endit=this->mpDenominator->getProducts().end();
    while(it!=endit)
    {
        std::set<CNormalItemPower*,compareItemPowers>::const_iterator it2=(*it)->getItemPowers().begin();
        std::set<CNormalItemPower*,compareItemPowers>::const_iterator endit2=(*it)->getItemPowers().end();
        while(it2!=endit2)
        {
          if((*it2)->getItemType()==CNormalItemPower::CHOICE)
          {
            const CNormalChoice* pChoice=dynamic_cast<const CNormalChoice*>(&(*it2)->getItem());
            const CNormalLogical* pLogical=&pChoice->getCondition();
            set.insert(pLogical);
            std::set<const CNormalLogical*> tmpSet=pLogical->findLogicals();
            set.insert(tmpSet.begin(),tmpSet.end());
          }
          else if((*it2)->getItemType()==CNormalItemPower::FUNCTION)
          {
          }
          else if((*it2)->getItemType()==CNormalItemPower::POWER)
          {
          }
          ++it2;
        }
        ++it;
    }
    it=this->mpNumerator->getProducts().begin();
    endit=this->mpNumerator->getProducts().end();
    while(it!=endit)
    {
        std::set<CNormalItemPower*,compareItemPowers>::const_iterator it2=(*it)->getItemPowers().begin();
        std::set<CNormalItemPower*,compareItemPowers>::const_iterator endit2=(*it)->getItemPowers().end();
        while(it2!=endit2)
        {
          if((*it2)->getItemType()==CNormalItemPower::CHOICE)
          {
            const CNormalChoice* pChoice=dynamic_cast<const CNormalChoice*>(&(*it2)->getItem());
            const CNormalLogical* pLogical=&pChoice->getCondition();
            set.insert(pLogical);
            std::set<const CNormalLogical*> tmpSet=pLogical->findLogicals();
            set.insert(tmpSet.begin(),tmpSet.end());
          }
          else if((*it2)->getItemType()==CNormalItemPower::FUNCTION)
          {
          }
          else if((*it2)->getItemType()==CNormalItemPower::POWER)
          {
          }
          ++it2;
        }
        ++it;
    }
    return set;
}
 */

bool CNormalFraction::checkIsOne() const
{
  // the fraction is one if numerator and denominator are equal
  return ((*mpNumerator) == (*mpDenominator));
}

bool CNormalFraction::checkIsZero() const
{
  // the fraction is 0.0 if the numerator is 0.0
  return this->mpNumerator->checkIsZero();
}

CNormalFraction* CNormalFraction::createUnitFraction()
{
  CNormalFraction* pFraction = new CNormalFraction();
  delete pFraction->mpNumerator;
  delete pFraction->mpDenominator;
  pFraction->mpNumerator = CNormalSum::createUnitSum();
  pFraction->mpDenominator = CNormalSum::createUnitSum();
  return pFraction;
}
