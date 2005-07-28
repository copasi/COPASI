/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test2/CNormalLcm.cpp,v $
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

CNormalLcm::CNormalLcm()
{}

CNormalLcm::CNormalLcm(const CNormalLcm& src)
{
  std::vector<CNormalItemPower*>::const_iterator it;
  std::vector<CNormalItemPower*>::const_iterator itEnd = src.mItemPowers.end();
  for (it = src.mItemPowers.begin(); it != itEnd; ++it)
    {
      mItemPowers.push_back(new CNormalItemPower(**it));
    }
  std::vector<CNormalSum*>::const_iterator it2;
  std::vector<CNormalSum*>::const_iterator it2End = src.mSums.end();
  for (it2 = src.mSums.begin(); it2 != it2End; ++it2)
    {
      mSums.push_back(new CNormalSum(**it2));
    }
}

bool CNormalLcm::add(const CNormalItemPower& itemPower)
{
  std::vector<CNormalItemPower*>::iterator it;
  std::vector<CNormalItemPower*>::iterator itEnd = mItemPowers.end();
  for (it = mItemPowers.begin(); it != itEnd; ++it)
    {
      if ((*it)->getItem() == itemPower.getItem())
        {
          (*it)->setExp((*it)->getExp() > itemPower.getExp() ? (*it)->getExp() : itemPower.getExp());
          return true;
        }
    }
  CNormalItemPower* tmp = new CNormalItemPower(itemPower);
  mItemPowers.push_back(tmp);
  return true;
}

bool CNormalLcm::add(const CNormalSum& sum) //Sum must not contain fractions!!
{
  switch (sum.getProducts().size())
    {
    case 0:    //Sum must contain at least one product!
      {
        return false;
      }
    case 1:
      {
        CNormalProduct* product = sum.getProducts()[0];
        std::vector<CNormalItemPower*>::const_iterator it;
        std::vector<CNormalItemPower*>::const_iterator itEnd = product->getItemPowers().end();
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

bool CNormalLcm::remove(const CNormalItemPower& itemPower)
{
  std::vector<CNormalItemPower*>::iterator it;
  std::vector<CNormalItemPower*>::iterator itEnd = mItemPowers.end();
  for (it = mItemPowers.begin(); it != itEnd; ++it)
    {
      if ((*it)->getItem() == itemPower.getItem())
        {
          (*it)->setExp((*it)->getExp() - itemPower.getExp());
          if (fabs((*it)->getExp()) < 1.0E-20)
            {
              delete *it;
              mItemPowers.erase(it);
            }
          if ((*it)->getExp() < -1.0E-20)
            return false;
          return true;
        }
    }
  return false;
}

bool CNormalLcm::remove(const CNormalSum& sum) //sum must not contain fractions!!
{
  switch (sum.getProducts().size())
    {
    case 0:
      {
        return false;
      }
    case 1:
      {
        const CNormalProduct* product = sum.getProducts()[0];
        std::vector<CNormalItemPower*>::const_iterator it;
        std::vector<CNormalItemPower*>::const_iterator itEnd = product->getItemPowers().end();
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

const std::vector<CNormalItemPower*>& CNormalLcm::getItemPowers() const
  {
    return mItemPowers;
  }

const std::vector<CNormalSum*>& CNormalLcm::getSums() const
  {
    return mSums;
  }

std::ostream & operator<<(std::ostream &os, const CNormalLcm & d)
{
  bool firstFactor = true;
  std::vector<CNormalItemPower*>::const_iterator it;
  std::vector<CNormalItemPower*>::const_iterator itEnd = d.mItemPowers.end();
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
  return os;
}
