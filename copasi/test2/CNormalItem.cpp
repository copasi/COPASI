/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test2/CNormalItem.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/07/28 13:46:06 $
   End CVS Header */

#include "CNormalItem.h"

CNormalItem::CNormalItem()
    : mName("no name")
{}

CNormalItem::CNormalItem(const CNormalItem& src)
    : mName(src.mName)
{}

const std::string CNormalItem::getName() const
  {
    return mName;
  }

bool CNormalItem::operator==(const CNormalItem & rhs) const
  {return (rhs.mName == mName);}

std::ostream & operator<<(std::ostream &os, const CNormalItem & d)
{
  os << d.mName;
  return os;
}

bool compareItems(const CNormalItem* item1, const CNormalItem* item2)
{
  return true;
}

CNormalItemPower::CNormalItemPower()
    : mExp(1.0)
{}

CNormalItemPower::CNormalItemPower(const CNormalItemPower& src)
    : mItem(src.mItem), mExp(src.mExp)
{}

CNormalItemPower::CNormalItemPower(const CNormalItem& item, const C_FLOAT64& exp)
    : mItem(item), mExp(exp)
{}

bool CNormalItemPower::setItem(const CNormalItem& item)
{
  mItem = item;
  return true;
}

bool CNormalItemPower::setExp(const C_FLOAT64& number)
{
  mExp = number;
  return true;
}

const CNormalItem& CNormalItemPower::getItem() const
  {
    return mItem;
  }

const C_FLOAT64& CNormalItemPower::getExp() const
  {
    return mExp;
  }

bool CNormalItemPower::operator==(const CNormalItemPower & rhs) const
  {
    if ((mItem == rhs.mItem) && (mExp == rhs.mExp))
      return true;
    else
      return false;
  }

std::ostream & operator<<(std::ostream &os, const CNormalItemPower & d)
{
  if (d.mExp == 1.0)
    os << d.mItem;
  else
    os << d.mItem << "^" << d.mExp;
  return os;
}

bool compareItemPowers(const CNormalItemPower* itemPower1, const CNormalItemPower* itemPower2)
{
  return true;
}
