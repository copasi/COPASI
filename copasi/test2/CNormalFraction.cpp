/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test2/CNormalFraction.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:32:06 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//#include "CNormalItem.h"
#include "CNormalProduct.h"
#include "CNormalSum.h"
#include "CNormalLcm.h"
#include "CNormalFraction.h"

CNormalFraction::CNormalFraction()
{}

CNormalFraction::CNormalFraction(const CNormalFraction& src)
    : mNumerator(src.mNumerator), mDenominator(src.mDenominator)
{}

CNormalFraction* CNormalFraction::createFraction(const CEvaluationNode* node)
{
  if (node->getData() == "/")
    {// always executed except on root node possibly not
      CNormalFraction* fraction = new CNormalFraction();
      CNormalSum* num = CNormalSum::createSum(static_cast<const CEvaluationNode*>(node->getChild()));
      CNormalSum* denom = CNormalSum::createSum(static_cast<const CEvaluationNode*>(node->getChild()->getSibling()));
      fraction->setNumerator(*num);
      fraction->setDenominator(*denom);
      fraction->cancel();
      delete num;
      delete denom;
      return fraction;
    }
  else
    {// only possible for root node
      CNormalFraction* fraction = new CNormalFraction();
      CNormalSum* num = CNormalSum::createSum(node);
      CNormalSum* denom = new CNormalSum();
      CNormalProduct* product = new CNormalProduct();
      denom->add(*product);
      fraction->setNumerator(*num);
      fraction->setDenominator(*denom);
      fraction->cancel();
      delete product;
      delete num;
      delete denom;
      return fraction;
    }
}

bool CNormalFraction::setNumerator(const CNormalSum& numerator)
{
  mNumerator = numerator;
  return true;
}

bool CNormalFraction::setDenominator(const CNormalSum& denominator)
{
  mDenominator = denominator;
  if (mDenominator.getSize() == 0)
    return false;
  return true;
}

bool CNormalFraction::checkDenominatorOne() const
  {
    if ((mDenominator.getProducts().size() == 1)
        && (mDenominator.getFractions().size() == 0)
        && ((*mDenominator.getProducts().begin())->getItemPowers().size() == 0)
        && (fabs((*mDenominator.getProducts().begin())->getFactor() - 1.0) < 1.E-100)
)
      {
        return true;
      }
    return false;
  }

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

bool CNormalFraction::expand(const CNormalLcm& lcm)
{
  mNumerator.multiply(lcm);
  mDenominator.multiply(lcm);
  if (mDenominator.getSize() == 0)
    return false;
  return true;
}

bool CNormalFraction::cancel()
{
  if (mDenominator == mNumerator)
    {
      setDenominatorOne();
      setNumerator(mDenominator);
      return true;
    }

  if (mDenominator.getProducts().size() != 0)
    {
      C_FLOAT64 factor = (*mDenominator.getProducts().begin())->getFactor();
      if (fabs(factor) < 1.0E-100)
        return false;
      else
        {
          mNumerator.multiply(1.0 / factor);  //factor != 0 as checked earlier
          mDenominator.multiply(1.0 / factor);
        }
    }

  if (checkForFractions() == false)
    {
      std::set<CNormalItemPower*, compareItemPowers>::iterator it;
      std::set<CNormalItemPower*, compareItemPowers>::iterator itEnd = (*mDenominator.getProducts().begin())->getItemPowers().end();
      for (it = (*mDenominator.getProducts().begin())->getItemPowers().begin(); it != itEnd; ++it)
        {//runs through all item powers in the first product of the denominator
          C_FLOAT64 exp = mNumerator.checkFactor(**it);
          if (fabs(exp) >= 1.0E-100)
            {
              exp = mDenominator.checkFactor(**it) < exp ? mDenominator.checkFactor(**it) : exp;
              if (fabs(exp) >= 1.0E-100)
                {
                  const CNormalItemPower* itemPower = new CNormalItemPower((*it)->getItem(), exp);

                  mNumerator.divide(*itemPower);
                  mDenominator.divide(*itemPower);
                  delete itemPower;
                }
            }
        }
    }
  return true;
}

bool CNormalFraction::multiply(const C_FLOAT64& number)
{
  mNumerator.multiply(number);
  if (mNumerator.getSize() == 0)
    setDenominatorOne();
  return true;
}

bool CNormalFraction::multiply(const CNormalItemPower& itemPower)
{
  C_FLOAT64 exp = mDenominator.checkFactor(itemPower);
  if (fabs(exp) >= 1.0E-100)
    {
      CNormalItemPower* tmp1 = new CNormalItemPower(itemPower.getItem(), exp);
      mDenominator.divide(*tmp1);
      if (fabs(itemPower.getExp() - exp) >= 1.0E-100)
        {
          CNormalItemPower* tmp2 = new CNormalItemPower(itemPower.getItem(), fabs(itemPower.getExp() - exp));
          mNumerator.multiply(*tmp2);
          return true;
        }
      return true;
    }
  else
    mNumerator.multiply(itemPower);
  return true;
}

const CNormalSum& CNormalFraction::getNumerator() const
  {
    return mNumerator;
  }

const CNormalSum& CNormalFraction::getDenominator() const
  {
    return mDenominator;
  }

bool CNormalFraction::checkForFractions() const
  {
    if (mNumerator.getFractions().size() + mDenominator.getFractions().size() == 0)
      return false;
    return true;
  }

const CNormalLcm* CNormalFraction::findLcm() const
  {
    CNormalLcm* lcm = new CNormalLcm();

    std::set<CNormalFraction*>::const_iterator it;
    std::set<CNormalFraction*>::const_iterator itEnd = mNumerator.getFractions().end();
    for (it = mNumerator.getFractions().begin(); it != itEnd; ++it)
      {
        lcm->add((*it)->getDenominator());
      }

    std::set<CNormalFraction*>::const_iterator it2;
    std::set<CNormalFraction*>::const_iterator it2End = mDenominator.getFractions().end();
    for (it2 = mDenominator.getFractions().begin(); it2 != it2End; ++it2)
      {
        lcm->add((*it2)->getDenominator());
      }

    return lcm;
  }

const CNormalSum* CNormalFraction::multiply(CNormalLcm lcm)  //This fraction must not contain further fractions
{
  if (mDenominator.getFractions().size() != 0)
    return false;
  if (lcm.remove(mDenominator) == false)
    return false;
  mNumerator.multiply(lcm);
  CNormalSum * sum = new CNormalSum(mNumerator);
  return sum;
}

bool CNormalFraction::simplify()
{
  if (mNumerator.getFractions().size() + mDenominator.getFractions().size() > 0)
    {
      std::set<CNormalFraction*>::const_iterator it;
      std::set<CNormalFraction*>::const_iterator itEnd = mNumerator.getFractions().end();
      for (it = mNumerator.getFractions().begin(); it != itEnd; ++it)
        {
          (*it)->simplify();
        }
      std::set<CNormalFraction*>::const_iterator it2;
      std::set<CNormalFraction*>::const_iterator it2End = mDenominator.getFractions().end();
      for (it2 = mDenominator.getFractions().begin(); it2 != it2End; ++it2)
        {
          (*it2)->simplify();
        }
      const CNormalLcm* lcm = findLcm();
      expand(*lcm);
      delete lcm;
    }
  cancel();
  return true;
}

bool CNormalFraction::operator==(const CNormalFraction & rhs) const
  {
    if ((mNumerator == rhs.mNumerator) && (mDenominator == rhs.mDenominator))
      return true;
    else
      return false;
  }

std::ostream & operator<<(std::ostream &os, const CNormalFraction & d)
{
  if (d.checkDenominatorOne() == true)
    os << d.mNumerator;
  else
    os << "(" << d.mNumerator << ")/(" << d.mDenominator << ")";
  return os;
}

/*CNormalSum* CNormalFraction::removeDenominator()  //only execute if mDenominator == 1.
{
  return &mNumerator;
}


bool CNormalFraction::multiply(const CNormalSum& sum)
{
  if (mDenominator == sum)
  {
    setDenominatorOne();
    return true;
  }
  mNumerator.multiply(sum);
  cancel();
  return true;
}


bool CNormalFraction::multiply(const CNormalFraction& fraction)
{
  CNormalFraction* tmp1 = new CNormalFraction();
  CNormalFraction* tmp2 = new CNormalFraction();
  tmp1->setNumerator(this->getNumerator());
  tmp1->setDenominator(fraction.getDenominator());
  tmp1->cancel();
  tmp2->setNumerator(fraction.getNumerator());
  tmp2->setDenominator(this->getDenominator());
  tmp2->cancel();
  setNumerator(tmp1->getNumerator().multiply(tmp2->getNumerator()));
  setDenominator(tmp1->getDenominator().multiply(tmp2->getDenominator()));
  cancel();
  delete tmp1;
  delete tmp2;
  return true;
}


bool CNormalFraction::divide(const CNormalFraction& fraction)
{
  CNormalFraction* tmp = new CNormalFraction();
  tmp->setNumerator(fraction.mDenominator);
  tmp->setDenominator(fraction.mNumerator);
  multiply(*tmp);
  delete tmp;
  return true;
}


bool CNormalFraction::checkEqual(const CNormalFraction& fraction) const
{
  CNormalFraction* tmp1 = new CNormalFraction(*this);
  CNormalFraction* tmp2 = new CNormalFraction(fraction);
  tmp1->simplify();
  tmp2->simplify();
  if (tmp1 == tmp2)
  {
    delete tmp1;
    delete tmp2;
    return true;
  }
  delete tmp1;
  delete tmp2;
  return false;
}
 */
