// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include "CNormalItem.h"
#include "CNormalProduct.h"
#include "CNormalSum.h"
#include "CNormalLcm.h"
#include "CNormalFraction.h"

bool compareItemPowers::operator()(const CNormalItemPower* itemPower1, const CNormalItemPower* itemPower2)
{
  return *itemPower1 < *itemPower2;
}

/*bool comparePowers::operator()(const CNormalPower* power1, const CNormalPower* power2)
{
  return *power1 < *power2;
}
 */
CNormalProduct::CNormalProduct()
  : mFactor(1.0)
{}

CNormalProduct::CNormalProduct(const CNormalProduct& src)
  : mFactor(src.mFactor)
{
  std::set <CNormalItemPower*, compareItemPowers>::const_iterator it;
  std::set <CNormalItemPower*, compareItemPowers>::const_iterator itEnd = src.mItemPowers.end();

  for (it = src.mItemPowers.begin(); it != itEnd; ++it)
    {
      mItemPowers.insert(new CNormalItemPower(**it));
    }

  /*
    std::set <CNormalPower*, comparePowers>::const_iterator it;
    std::set <CNormalPower*, comparePowers>::const_iterator itEnd = src.mPowers.end();
    for (it = src.mPowers.begin(); it != itEnd; ++it)
    {
      mPowers.insert(new CNormalPower(**it));
    }
  */
}

CNormalProduct & CNormalProduct::operator=(const CNormalProduct& src)
{
  mFactor = src.mFactor;
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it;
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator itEnd = src.mItemPowers.end();

  for (it = src.mItemPowers.begin(); it != itEnd; ++it)
    mItemPowers.insert(new CNormalItemPower(**it));

  return *this;
}

CNormalProduct::~CNormalProduct()
{
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it;
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator itEnd = mItemPowers.end();

  for (it = mItemPowers.begin(); it != itEnd; ++it)
    delete *it;

  /*
    std::set<CNormalPower*, comparePowers>::const_iterator it2;
    std::set<CNormalPower*, comparePowers>::const_iterator it2End = mPowers.end();
    for (it2 = mPowers.begin(); it2 != it2End; ++it2)
      delete *it;*/
}

CNormalProduct * CNormalProduct::createProduct(const CEvaluationNode* node)
{
  CNormalProduct * product = new CNormalProduct();

  switch (node->mainType())
    {
      case CEvaluationNode::MainType::OPERATOR:  // PLUS(->createSum), MINUS(translated as +(-..)) and DIVIDE(->createFraction) do not occur.
      {
        if (node->getData() == "^")
          {
            if (CEvaluationNode::type(static_cast<const CEvaluationNode*>(node->getChild()->getSibling())->getType()) == CEvaluationNode::MainType::NUMBER)
              {
                CNormalItemPower* power = CNormalItemPower::createItemPower(node);
                product->multiply(*power);
                delete power;
                return product;
              }
            else
              {
                CNormalItem* item = CNormalItem::createItem(node);
                product->multiply(*item);
                delete item;
                return product;
              }
          }

        if (node->getData() == "*")
          {
            CNormalProduct* product1 = createProduct(static_cast<const CEvaluationNode*>(node->getChild()));
            CNormalProduct* product2 = createProduct(static_cast<const CEvaluationNode*>(node->getChild()->getSibling()));
            product->multiply(*product1);
            product->multiply(*product2);
            delete product1;
            delete product2;
            return product;
          }

        //default (case MODULUS):
        CNormalItem* item = CNormalItem::createItem(node);
        product->multiply(*item);
        delete item;
        return product;
      }

      case CEvaluationNode::MainType::NUMBER:
      {
        product->multiply(node->value());
        return product;
      }

      case CEvaluationNode::MainType::FUNCTION:
      {
        if (node->getData() == "-")
          {
            product->multiply(-1.0);
            CNormalProduct * product2 = createProduct(dynamic_cast<const CEvaluationNode*>(node->getChild()));
            product->multiply(*product2);
            delete product2;
            return product;
          }

        CNormalItem * item = CNormalItem::createItem(node);
        product->multiply(*item);
        delete item;
        return product;
      }

      default:   //cases VARIABLE, CONSTANT, CALL, CHOICE, LOGICAL, OBJECT, VECTOR
      {
        CNormalItem * item = CNormalItem::createItem(node);
        product->multiply(*item);
        delete item;
        return product;
      }
    }
}

bool CNormalProduct::setFactor(const C_FLOAT64& number)
{
  mFactor = number;

  if (fabs(mFactor) < 1.0E-100)
    {
      mItemPowers.clear();
      //mPowers.clear();
    }

  return true;
}

bool CNormalProduct::multiply(const C_FLOAT64& number)
{
  mFactor = mFactor * number;

  if (fabs(mFactor) < 1.0E-100)
    {
      mItemPowers.clear();
      //mPowers.clear();
    }

  return true;
}

bool CNormalProduct::multiply(const CNormalItemPower& itemPower)
{
  if (fabs(mFactor) < 1.0E-100)
    return true;

  std::set <CNormalItemPower*, compareItemPowers>::const_iterator it;
  std::set <CNormalItemPower*, compareItemPowers>::const_iterator itEnd = mItemPowers.end();

  for (it = mItemPowers.begin(); it != itEnd; ++it)
    {
      if ((*it)->getItem() == itemPower.getItem())
        {
          (*it)->setExp((*it)->getExp() + itemPower.getExp());
          return true;
        }
    }

  CNormalItemPower* tmp = new CNormalItemPower(itemPower);
  mItemPowers.insert(tmp);
  return true;
}

/*bool CNormalProduct::multiply(const CNormalPower& power)
{
  if (fabs(mFactor) < 1.0E-100)
    return true;
  std::set <CNormalPower*, comparePowers>::const_iterator it;
  std::set <CNormalPower*, comparePowers>::const_iterator itEnd = mPowers.end();
  for (it = mPowers.begin(); it != itEnd; ++it)
  {
    if ((*it)->getExp() == power.getExp())
    {
      (*it)->setBase((*it)->getBase() * power.getBase());
      return true;
    }
    if (((*it)->getBase() == power.getBase()) && ((*it)->getExp()->checkSamePowerList(power.getExp()) == true))
    {
      (*it)->setExpFactor((*it)->getExp()->mFactor + power.getExp()->getFactor());
      if ((*it)->getExp()->getFactor() >= 1.0 + 1.0E-100)
      {
        (*it)->setExpFactor((*it)->getExp()->getFactor - 1.0);
        CNormalPower* tmp = new CNormalPower();
        tmp->setBase(*(*it)->getBase());
        CNormalProduct* exp = new CNormalProduct();
        exp->multiply((*it)->getExp()->getItemPowers());
        exp->multiply((*it)->getExp()->getPowers());
        tmp->setExp(*exp);
        this->multiply(*tmp);
        delete tmp;
        delete exp;
        return true;
      }
    }
  }
  CNormalPower* tmp = new CNormalPower(power);
  mPowers.insert(tmp);
  return true;
}*/

bool CNormalProduct::multiply(const CNormalItem& item)
{
  if (fabs(mFactor) < 1.0E-100)
    return true;

  std::set <CNormalItemPower*, compareItemPowers>::const_iterator it;
  std::set <CNormalItemPower*, compareItemPowers>::const_iterator itEnd = mItemPowers.end();

  for (it = mItemPowers.begin(); it != itEnd; ++it)
    {
      if ((*it)->getItem() == item)
        {
          (*it)->setExp((*it)->getExp() + 1.0);
          return true;
        }
    }

  CNormalItemPower* tmp = new CNormalItemPower(item, 1.0);
  mItemPowers.insert(tmp);
  return true;
}

bool CNormalProduct::multiply(const std::set <CNormalItemPower*, compareItemPowers>& itemPowers)
{
  if (fabs(mFactor) < 1.0E-100)
    return true;

  std::set <CNormalItemPower*, compareItemPowers>::const_iterator it;
  std::set <CNormalItemPower*, compareItemPowers>::const_iterator itEnd = itemPowers.end();

  for (it = itemPowers.begin(); it != itEnd; ++it)
    multiply(**it);

  return true;
}

/*bool CNormalProduct::multiply(const std::set <CNormalPower*, comparePowers>& powers)
{
  if (fabs(mFactor) < 1.0E-100)
    return true;
  std::set <CNormalPower*, comparePowers>::const_iterator it;
  std::set <CNormalPower*, comparePowers>::const_iterator itEnd = powers.end();
  for (it = powers.begin(); it != itEnd; ++it)
    multiply(**it);
  return true;
}*/

bool CNormalProduct::remove(std::set <CNormalItemPower*, compareItemPowers>::iterator it)
{
  delete(*it);
  mItemPowers.erase(it);
  return true;
}

bool CNormalProduct::remove(const CNormalItemPower& itemPower)
{
  std::set <CNormalItemPower*, compareItemPowers>::iterator it;
  std::set <CNormalItemPower*, compareItemPowers>::iterator itEnd = mItemPowers.end();

  for (it = mItemPowers.begin(); it != itEnd; ++it)
    {
      if ((*it)->getItem() == itemPower.getItem())
        {
          C_FLOAT64 dif = (*it)->getExp() - itemPower.getExp();

          if (dif >= 1.0E-100)
            {
              (*it)->setExp(dif);
              return true;
            }

          if (fabs(dif) < 1.0E-100)
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

  if (fabs(mFactor) < 1.0E-100)
    return true;

  multiply(product.getItemPowers());
  return true;
}

CNormalSum* CNormalProduct::multiply(const CNormalSum& sum)  //sum and newsum do not contain fractions
{
  if (fabs(mFactor) < 1.0E-100)
    {
      CNormalSum* zeroSum = new CNormalSum();
      zeroSum->add(*this);
      return zeroSum;
    }

  CNormalSum* tmp = new CNormalSum(sum);
  CNormalSum* newsum = new CNormalSum();
  std::set<CNormalProduct*>::const_iterator it;
  std::set<CNormalProduct*>::const_iterator itEnd = tmp->getProducts().end();

  for (it = tmp->getProducts().begin(); it != itEnd; ++it)
    {
      (*it)->multiply(*this);
      newsum->add(**it);
    }

  delete tmp;
  return newsum;
}

const CNormalSum* CNormalProduct::multiply(const CNormalLcm& lcm)
{
  if (fabs(mFactor) < 1.0E-100)
    {
      CNormalSum* zeroSum = new CNormalSum();
      zeroSum->add(*this);
      return zeroSum;
    }

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

  delete tmp;
  return sum;
}

const C_FLOAT64 & CNormalProduct::getFactor() const
{
  return mFactor;
}

const std::set <CNormalItemPower*, compareItemPowers>& CNormalProduct::getItemPowers() const
{
  return mItemPowers;
}

/*const std::set <CNormalPower*, comparePowers>& CNormalProduct::getPowers() const
{
  return mPowers;
}*/

bool CNormalProduct::checkSamePowerList(const CNormalProduct & rhs) const
{
  if (mItemPowers.size() != rhs.mItemPowers.size())
    return false;

  //if (mPowers.size() != rhs.mPowers.size())
  //return false;
  std::set<CNormalItemPower*>::const_iterator it;
  std::set<CNormalItemPower*>::const_iterator itEnd = mItemPowers.end();
  std::set<CNormalItemPower*>::const_iterator it2;
  std::set<CNormalItemPower*>::const_iterator it2End = rhs.mItemPowers.end();

  for (it = mItemPowers.begin(), it2 = rhs.mItemPowers.begin(); it != itEnd; ++it, ++it2)
    {
      if (!(**it == **it2))
        return false;
    }

  /*std::set<CNormalPower*>::const_iterator it;
  std::set<CNormalPower*>::const_iterator itEnd = mPowers.end();
  std::set<CNormalPower*>::const_iterator it2;
  std::set<CNormalPower*>::const_iterator it2End = rhs.mPowers.end();
  for (it = mPowers.begin(), it2 = rhs.mPowers.begin(); it != itEnd; ++it, ++it2)
  {
    if (!(**it == **it2))
      return false;
  }*/
  return true;
}

bool CNormalProduct::operator==(const CNormalProduct & rhs) const
{
  if (mFactor != rhs.mFactor)
    return false;

  if (checkSamePowerList(rhs))
    return true;

  return false;
}

std::ostream & operator<<(std::ostream &os, const CNormalProduct & d)
{
  bool firstFactor = true;

  if ((fabs(d.mFactor - 1.0) >= 1.0E-100) || (d.mItemPowers.size() == 0))
    {
      if (d.mFactor < 0.0)
        os << "(" << d.mFactor << ")";
      else
        os << d.mFactor;

      firstFactor = false;
    }

  std::set <CNormalItemPower*, compareItemPowers>::const_iterator it;
  std::set <CNormalItemPower*, compareItemPowers>::const_iterator itEnd = d.mItemPowers.end();

  for (it = d.mItemPowers.begin(); it != itEnd; ++it)
    {
      if (firstFactor == false)
        os << " * ";

      os << **it;
      firstFactor = false;
    }

  /*std::set <CNormalPower*, comparePowers>::const_iterator it;
  std::set <CNormalPower*, comparePowers>::const_iterator itEnd = d.mPowers.end();
  for (it = d.mPowers.begin(); it != itEnd; ++it)
  {
    if (firstFactor == false)
      os << " * ";
    os << **it;
    firstFactor = false;
  }*/
  return os;
}
