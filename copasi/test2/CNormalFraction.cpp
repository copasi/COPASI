/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test2/CNormalFraction.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/07/28 13:46:06 $
   End CVS Header */

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

bool CNormalFraction::setNumerator(const CNormalSum& numerator)
{
  mNumerator = numerator;
  return true;
}

bool CNormalFraction::setDenominator(const CNormalSum& denominator)
{
  CNormalSum* tmp = new CNormalSum(denominator);
  switch (tmp->getSize())
    {
    case 0:
      return false;
    case 1:
      {
        switch (tmp->getProducts().size())
          {
          case 0:
            {
              mDenominator = tmp->getFractions()[0]->getNumerator();
              mNumerator.multiply(tmp->getFractions()[0]->getDenominator());
              return true;
            }
          case 1:
            {
              C_FLOAT64 factor = tmp->getProducts()[0]->getFactor();
              if (fabs(factor) < 1.0E-30)
                return false;
              if (fabs(factor - 1.0) >= 1.0E-30)
                {
                  mNumerator.multiply(1.0 / factor); // factor != 0, as checked earlier
                  tmp->getProducts()[0]->multiply(1.0 / factor);
                  mDenominator = *tmp;
                  return true;
                }
            }
          }
      }
    default:
      {
        mDenominator = *tmp;
        return true;
      }
    }
}

bool CNormalFraction::checkDenominatorOne() const
  {
    if (mDenominator.getSize() == 0)
      {
        return true;
      }
    if ((mDenominator.getProducts().size() == 1) && (mDenominator.getFractions().size() == 0)
        && (mDenominator.getProducts()[0]->getItemPowers().size() == 0) && (fabs(mDenominator.getProducts()[0]->getFactor() - 1.0) < 1.E-20))
      {
        return true;
      }
    return false;
  }

CNormalSum* CNormalFraction::removeDenominator()
{
  return &mNumerator;
}

bool CNormalFraction::expand(const CNormalLcm& lcm)
{
  mNumerator.multiply(lcm);
  mDenominator.multiply(lcm);
  return true;
}

bool CNormalFraction::cancel()
{
  return true;
}

bool CNormalFraction::multiply(const C_FLOAT64& number)
{
  mNumerator.multiply(number);
  return true;
}

bool CNormalFraction::multiply(const CNormalItemPower& itemPower)
{
  switch (mDenominator.getSize())
    {
    case 0:
      return false;
    case 1:
      {
        if (mDenominator.getFractions().size() != 0)
          return false;
        CNormalProduct* product = mDenominator.getProducts()[0];
        std::vector<CNormalItemPower*>::const_iterator it;
        std::vector<CNormalItemPower*>::const_iterator itEnd = product->getItemPowers().end();
        for (it = product->getItemPowers().begin(); it != itEnd; ++it)
          {
            if ((*it)->getItem() == itemPower.getItem())
              {
                C_FLOAT64 dif = (*it)->getExp() - itemPower.getExp();
                if (dif >= -1.0E-30)
                  return product->remove(itemPower);
                else
                  {
                    CNormalItemPower* tmp = new CNormalItemPower(itemPower.getItem(), -dif);
                    mNumerator.multiply(*tmp);
                    product->remove(**it);
                    return true;
                  }
              }
          }
        mNumerator.multiply(itemPower);
        return true;
      }
    default:
      {
        mNumerator.multiply(itemPower);
        return true;
      }
    }
}
//->checkDenominatorOne

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
    if ((mNumerator.CNormalSum::checkForFractions() == true) || (mDenominator.CNormalSum::checkForFractions() == true))
      {
        return true;
      }
    else
      {
        return false;
      }
  }

const CNormalLcm* CNormalFraction::findLcm() const
  {
    CNormalLcm* lcm = new CNormalLcm();
    std::vector<CNormalFraction*>::const_iterator it;
    std::vector<CNormalFraction*>::const_iterator itEnd = mNumerator.getFractions().end();
    for (it = mNumerator.getFractions().begin(); it != itEnd; ++it)
      {
        lcm->add((*it)->getDenominator());
      }
    std::vector<CNormalFraction*>::const_iterator it2;
    std::vector<CNormalFraction*>::const_iterator it2End = mDenominator.getFractions().end();
    for (it2 = mDenominator.getFractions().begin(); it2 != it2End; ++it2)
      {
        lcm->add((*it2)->getDenominator());
      }
    std::cout << "Lcm: " << *lcm << std::endl;
    return lcm;
  }

const CNormalSum* CNormalFraction::multiply(CNormalLcm lcm)  //This fraction must not contain further fractions
{
  if (mDenominator.getFractions().size() != 0)
    return false;
  lcm.remove(mDenominator);
  mNumerator.multiply(lcm);
  return &mNumerator;
}

bool CNormalFraction::simplifyFraction()
{
  if (checkForFractions() == true)
    {
      expand(*findLcm());
      return true;
    }
  return false;
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
  os << "(" << d.mNumerator << ")/(" << d.mDenominator << ")";
  return os;
}
