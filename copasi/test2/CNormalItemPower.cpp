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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CNormalItemPower.h"
#include "copasi/function/CEvaluationNode.h"

CNormalItemPower::CNormalItemPower()
  : mExp(1.0)
{}

CNormalItemPower::CNormalItemPower(const CNormalItemPower& src)
  : mItem(src.mItem), mExp(src.mExp)
{}

CNormalItemPower::CNormalItemPower(const CNormalItem& item, const C_FLOAT64& exp)
  : mItem(item), mExp(exp)
{}

CNormalItemPower * CNormalItemPower::createItemPower(const CEvaluationNode* node)
{
  CNormalItemPower * itemPower = new CNormalItemPower();
  CNormalItem* item = CNormalItem::createItem(static_cast<const CEvaluationNode*>(node->getChild()));
  itemPower->setItem(*item);
  itemPower->setExp(static_cast<const CEvaluationNode*>(node->getChild()->getSibling())->value());
  delete item;
  return itemPower;
}

bool CNormalItemPower::setItem(const CNormalItem& item)
{
  mItem = item;
  return true;
}

bool CNormalItemPower::setExp(const C_FLOAT64& number)
{
  if (mExp < 0.0)
    return false;

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

bool CNormalItemPower::operator<(const CNormalItemPower & rhs) const
{
  if (mItem < rhs.mItem) return true;

  if (rhs.mItem < mItem) return false;

  return (rhs.mExp < mExp);
}

std::ostream & operator<<(std::ostream &os, const CNormalItemPower & d)
{
  if (d.mItem.getType() != CNormalItem::FUNCTION)
    os << d.mItem;
  else
    os << "(" << d.mItem << ")";

  if (d.mExp != 1.0)
    os << "^" << d.mExp;

  return os;
}

/*
CNormalPower::CNormalPower()
{}


CNormalPower::CNormalPower(const CNormalPower& src)
    : mBase(src.mBase), mExp(src.mExp)
{}


CNormalPower::CNormalPower(const CNormalSum& sum, const CNormalProduct& product)
    : mBase(sum), mExp(product)
{}


bool CNormalPower::setBase(const CNormalSum& sum)
{
  mBase = sum;
  return true;
}


bool CNormalPower::setExp(const CNormalProduct& product)
{
  if (product.getFactor() < 1.0E-100)
    return false;
  mExp = product;
  return true;
}


bool CNormalPower::setExpFactor(const C_FLOAT64 & factor)
{
  if (factor < 1.0E-100)
    return false;
  mExp.setFactor(factor);
  return true;
}


bool CNormalPower::multiply(const CNormalPower& power)
{
  if (mExp == power.mExp)
  {
    mBase.multiply(power.mBase);
    return true;
  }
  return false;
}


const CNormalSum& CNormalPower::getBase() const
{
  return mBase;
}


const CNormalProduct& CNormalPower::getExp() const
{
  return mExp;
}


bool CNormalPower::operator==(const CNormalPower & rhs) const
{
  if ((mBase == rhs.mBase) && (mExp == rhs.mExp))
    return true;
  else
    return false;
}


bool CNormalPower::operator<(const CNormalPower & rhs) const
{
  if (mExp < rhs.mExp) return true;
  if (rhs.mExp < mExp) return false;
  return (rhs.mExp.getFactor() < mExp.getFactor());
}


std::ostream & operator<<(std::ostream &os, const CNormalPower & d)
{
  //if ((d.mBase.getProducts().size() == 1)
    //&& (((*d.mBase.getProducts().begin())->getSize() == 1) ||))
    //os << d.mBase;
  //else
    //os << "(" << d.mBase << ")";
  //os << "^";
  //if (d.mExp)
  //os << "(" << d.mExp << ")";


  os << "(" << d.mBase << ")^(" << d.mExp << ")";
  return os;
}


 */
