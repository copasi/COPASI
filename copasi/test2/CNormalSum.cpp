/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test2/CNormalSum.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/07/28 13:46:06 $
   End CVS Header */

#include "CNormalItem.h"
#include "CNormalProduct.h"
#include "CNormalSum.h"
#include "CNormalLcm.h"
#include "CNormalFraction.h"

CNormalSum::CNormalSum()
{}

CNormalSum::CNormalSum(const CNormalSum& src)
{
  std::vector<CNormalProduct*>::const_iterator it;
  std::vector<CNormalProduct*>::const_iterator itEnd = src.mProducts.end();
  for (it = src.mProducts.begin(); it != itEnd; ++it)
    {
      mProducts.push_back(new CNormalProduct(**it));
    }
  std::vector<CNormalFraction*>::const_iterator it2;
  std::vector<CNormalFraction*>::const_iterator it2End = src.mFractions.end();
  for (it2 = src.mFractions.begin(); it2 != it2End; ++it2)
    {
      mFractions.push_back(new CNormalFraction(**it2));
    }
}

int CNormalSum::getSize() const
  {
    return mProducts.size() + mFractions.size();
  }

bool CNormalSum::add(const CNormalProduct& product)
{
  if (fabs(product.getFactor()) < 1.0E-30)
    return true;
  std::vector<CNormalProduct*>::iterator it;
  std::vector<CNormalProduct*>::iterator itEnd = mProducts.end();
  for (it = mProducts.begin(); it != itEnd; ++it)
    {
      if ((*it)->getItemPowers().size() == product.getItemPowers().size())
        {
          std::vector<CNormalItemPower*>::const_iterator it2;
          std::vector<CNormalItemPower*>::const_iterator it2End = (*it)->getItemPowers().end();
          std::vector<CNormalItemPower*>::const_iterator it3;
          std::vector<CNormalItemPower*>::const_iterator it3End = product.getItemPowers().end();
          bool itemPowerListsEqual = true;
          for (it2 = (*it)->getItemPowers().begin(), it3 = product.getItemPowers().begin(); it2 != it2End; ++it2, ++it3)
            {
              if (!(**it2 == **it3))
                {
                  itemPowerListsEqual = false;
                  break;
                }
            }
          if (itemPowerListsEqual == true)
            {
              (*it)->setFactor((*it)->getFactor() + product.getFactor());
              return true;
            }
        }
    }
  CNormalProduct* tmp = new CNormalProduct(product);
  mProducts.push_back(tmp);
  return true;
}

bool CNormalSum::add(const CNormalFraction& fraction)
{
  CNormalFraction* tmp = new CNormalFraction(fraction);
  mFractions.push_back(tmp);
  return true;
}

bool CNormalSum::add(const CNormalSum& sum)
{
  CNormalSum* tmp = new CNormalSum(sum);
  std::vector<CNormalProduct*>::const_iterator itProduct;
  std::vector<CNormalProduct*>::const_iterator itProductEnd = tmp->getProducts().end();
  for (itProduct = tmp->getProducts().begin(); itProduct != itProductEnd; ++itProduct)
    {
      add(**itProduct);
    }
  std::vector<CNormalFraction*>::const_iterator itFraction;
  std::vector<CNormalFraction*>::const_iterator itFractionEnd = tmp->getFractions().end();
  for (itFraction = tmp->getFractions().begin(); itFraction != itFractionEnd; ++itFraction)
    {
      add(**itFraction);
    }
  return true;
}

bool CNormalSum::checkForFractions() const
  {
    if (mFractions.size() >= 1)
      {
        return true;
      }
    else
      {
        return false;
      }
  }

bool CNormalSum::multiply(const C_FLOAT64& number)
{
  std::vector<CNormalProduct*>::iterator it;
  std::vector<CNormalProduct*>::iterator itEnd = mProducts.end();
  for (it = mProducts.begin(); it != itEnd; ++it)
    {
      (*it)->multiply(number);
    }
  std::vector<CNormalFraction*>::iterator it2;
  std::vector<CNormalFraction*>::iterator it2End = mFractions.end();
  for (it2 = mFractions.begin(); it2 != it2End; ++it2)
    {
      (*it2)->multiply(number);
    }
  return true;
}

bool CNormalSum::multiply(const CNormalItemPower& itemPower)
{
  std::vector<CNormalProduct*>::iterator it;
  std::vector<CNormalProduct*>::iterator itEnd = mProducts.end();
  for (it = mProducts.begin(); it != itEnd; ++it)
    {
      (*it)->multiply(itemPower);
    }
  std::vector<CNormalFraction*>::iterator it2;
  std::vector<CNormalFraction*>::iterator it2End = mFractions.end();
  for (it2 = mFractions.begin(); it2 != it2End; ++it2)
    {
      (*it2)->multiply(itemPower);
    }
  return true;
}

bool CNormalSum::multiply(const CNormalSum& sum)  //all of these sums do not contain fractions.
{
  std::vector<CNormalProduct*> tmpProducts = mProducts;
  mProducts.clear();
  std::vector<CNormalProduct*>::iterator it;
  std::vector<CNormalProduct*>::iterator itEnd = tmpProducts.end();
  for (it = tmpProducts.begin(); it != itEnd; ++it)
    {
      add(*((*it)->multiply(sum)));
    }
  return true;
}

bool CNormalSum::multiply(const CNormalLcm& lcm)
{
  std::vector<CNormalProduct*> tmpProducts = mProducts;
  mProducts.clear();
  std::vector<CNormalProduct*>::const_iterator it2;
  std::vector<CNormalProduct*>::const_iterator it2End = tmpProducts.end();
  for (it2 = tmpProducts.begin(); it2 != it2End; ++it2)
    {
      add(*((*it2)->multiply(lcm)));
      delete *it2;
    }
  std::vector<CNormalFraction*>::const_iterator it;
  std::vector<CNormalFraction*>::const_iterator itEnd = mFractions.end();
  for (it = mFractions.begin(); it != itEnd; ++it)
    {
      add(*((*it)->multiply(lcm)));
      delete *it;
    }
  mFractions.clear();
  return true;
}

const std::vector<CNormalProduct*>& CNormalSum::getProducts() const
  {
    return mProducts;
  }

const std::vector<CNormalFraction*>& CNormalSum::getFractions() const
  {
    return mFractions;
  }

bool CNormalSum::operator==(const CNormalSum & rhs) const
  {
    if (mProducts.size() != rhs.mProducts.size())
      return false;
    if (mFractions.size() != rhs.mFractions.size())
      return false;
    std::vector<CNormalProduct*>::const_iterator it;
    std::vector<CNormalProduct*>::const_iterator itEnd = this->mProducts.end();
    std::vector<CNormalProduct*>::const_iterator it2;
    std::vector<CNormalProduct*>::const_iterator it2End = rhs.mProducts.end();
    for (it = mProducts.begin(), it2 = rhs.mProducts.begin(); it != itEnd; ++it, ++it2)
      {
        if (!(**it == **it2))
          return false;
      }
    std::vector<CNormalFraction*>::const_iterator it3;
    std::vector<CNormalFraction*>::const_iterator it3End = this->mFractions.end();
    std::vector<CNormalFraction*>::const_iterator it4;
    std::vector<CNormalFraction*>::const_iterator it4End = rhs.mFractions.end();
    for (it3 = mFractions.begin(), it4 = rhs.mFractions.begin(); it3 != it3End; ++it3, ++it4)
      {
        if (!(**it3 == **it4))
          return false;
      }
    return true;
  }

std::ostream & operator<<(std::ostream &os, const CNormalSum & d)
{
  bool firstSummand = true;
  std::vector<CNormalProduct*>::const_iterator it;
  std::vector<CNormalProduct*>::const_iterator itEnd = d.mProducts.end();
  for (it = d.mProducts.begin(); it != itEnd; ++it)
    {
      if (firstSummand == false)
        {
          os << " + ";
        }
      os << **it;
      firstSummand = false;
    }
  std::vector<CNormalFraction*>::const_iterator it2;
  std::vector<CNormalFraction*>::const_iterator it2End = d.mFractions.end();
  for (it2 = d.mFractions.begin(); it2 != it2End; ++it2)
    {
      if (firstSummand == false)
        {
          os << " + ";
        }
      os << **it2;
      firstSummand = false;
    }
  return os;
}
