/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test2/CNormalProduct.cpp,v $
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

CNormalProduct::CNormalProduct()
    : mFactor(1.0)
{}

CNormalProduct::CNormalProduct(const CNormalProduct& src)
    : mFactor(src.mFactor)
{
  std::vector<CNormalItemPower*>::const_iterator it;
  std::vector<CNormalItemPower*>::const_iterator itEnd = src.mItemPowers.end();
  for (it = src.mItemPowers.begin(); it != itEnd; ++it)
    {
      mItemPowers.push_back(new CNormalItemPower(**it));
    }
}

bool CNormalProduct::setFactor(const C_FLOAT64& number)
{
  mFactor = number;
  return true;
}

bool CNormalProduct::multiply(const C_FLOAT64& number)
{
  mFactor = mFactor * number;
  return true;
}

bool CNormalProduct::multiply(const CNormalItemPower& power)
{
  std::vector<CNormalItemPower*>::const_iterator it;
  std::vector<CNormalItemPower*>::const_iterator itEnd = mItemPowers.end();
  for (it = mItemPowers.begin(); it != itEnd; ++it)
    {
      if ((*it)->getItem() == power.getItem())
        {
          (*it)->setExp((*it)->getExp() + power.getExp());
          return true;
        }
    }
  CNormalItemPower* tmp = new CNormalItemPower(power);
  mItemPowers.push_back(tmp);
  return true;
}

bool CNormalProduct::multiply(const CNormalItem& item)
{
  std::vector<CNormalItemPower*>::const_iterator it;
  std::vector<CNormalItemPower*>::const_iterator itEnd = mItemPowers.end();
  for (it = mItemPowers.begin(); it != itEnd; ++it)
    {
      if ((*it)->getItem() == item)
        {
          (*it)->setExp((*it)->getExp() + 1.0);
          return true;
        }
    }
  CNormalItemPower* tmp = new CNormalItemPower(item, 1.0);
  mItemPowers.push_back(tmp);
  return true;
}

bool CNormalProduct::multiply(const std::vector<CNormalItemPower*>& itemPowers)
{
  std::vector<CNormalItemPower*>::const_iterator it;
  std::vector<CNormalItemPower*>::const_iterator itEnd = itemPowers.end();
  for (it = itemPowers.begin(); it != itEnd; ++it)
    {
      multiply(**it);
    }
  return true;
}

bool CNormalProduct::remove(const CNormalItemPower& itemPower)
{
  std::vector<CNormalItemPower*>::iterator it;
  std::vector<CNormalItemPower*>::iterator itEnd = mItemPowers.end();
  for (it = mItemPowers.begin(); it != itEnd; ++it)
    {
      if ((*it)->getItem() == itemPower.getItem())
        {
          C_FLOAT64 dif = (*it)->getExp() - itemPower.getExp();
          if (dif >= 1.0E-30)
            {
              (*it)->setExp(dif);
              return true;
            }
          if (fabs(dif) < 1.0E-30)
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

bool CNormalProduct::multiply(const CNormalProduct& product)
{
  multiply(product.getFactor());
  multiply(product.getItemPowers());
  return true;
}

CNormalSum* CNormalProduct::multiply(const CNormalSum& sum)  //sum and newsum do not contain fractions
{
  CNormalSum* tmp = new CNormalSum(sum);
  CNormalSum* newsum = new CNormalSum();
  std::vector<CNormalProduct*>::const_iterator it;
  std::vector<CNormalProduct*>::const_iterator itEnd = tmp->getProducts().end();
  for (it = tmp->getProducts().begin(); it != itEnd; ++it)
    {
      (*it)->multiply(*this);
      newsum->add(**it);
    }
  return newsum;
}

const CNormalSum* CNormalProduct::multiply(const CNormalLcm& lcm)
{
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
  return sum;
}

const C_FLOAT64 & CNormalProduct::getFactor() const
  {
    return mFactor;
  }

const std::vector<CNormalItemPower*>& CNormalProduct::getItemPowers() const
  {
    return mItemPowers;
  }

bool CNormalProduct::operator==(const CNormalProduct & rhs) const
  {
    if (mFactor != rhs.mFactor)
      return false;
    if (mItemPowers.size() != rhs.mItemPowers.size())
      return false;
    std::vector<CNormalItemPower*>::const_iterator it;
    std::vector<CNormalItemPower*>::const_iterator itEnd = this->mItemPowers.end();
    std::vector<CNormalItemPower*>::const_iterator it2;
    std::vector<CNormalItemPower*>::const_iterator it2End = rhs.mItemPowers.end();
    for (it = mItemPowers.begin(), it2 = rhs.mItemPowers.begin(); it != itEnd; ++it, ++it2)
      {
        if (!(**it == **it2))
          return false;
      }
    return true;
  }

std::ostream & operator<<(std::ostream &os, const CNormalProduct & d)
{
  bool firstFactor = true;
  if (fabs(d.mFactor - 1.0) >= 1.0E-30)
    {
      os << d.mFactor;
      firstFactor = false;
    }
  std::vector<CNormalItemPower*>::const_iterator it;
  std::vector<CNormalItemPower*>::const_iterator itEnd = d.mItemPowers.end();
  for (it = d.mItemPowers.begin(); it != itEnd; ++it)
    {
      if (firstFactor == false)
        os << " * ";
      os << **it;
      firstFactor = false;
    }
  return os;
}
