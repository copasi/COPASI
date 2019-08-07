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

#include "CNormalItem.h"
#include "CNormalItemPower.h"
#include "CNormalProduct.h"
#include "CNormalSum.h"
#include "CNormalLcm.h"
#include "CNormalFraction.h"
#include "copasi/function/CEvaluationNode.h"

bool compareProducts::operator()(const CNormalProduct* product1, const CNormalProduct* product2)
{
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it;
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator itEnd = product1->getItemPowers().end();
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2;
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2End = product2->getItemPowers().end();

  for (it = product1->getItemPowers().begin(), it2 = product2->getItemPowers().begin(); (it != itEnd) && (it2 != it2End); ++it, ++it2)
    {
      if (**it < **it2) return true;

      if (**it2 < **it) return false;
    }

  return (product1->getItemPowers().size() < product2->getItemPowers().size());
}

CNormalSum::CNormalSum()
{}

CNormalSum::CNormalSum(const CNormalSum& src)
{
  std::set<CNormalProduct*, compareProducts>::const_iterator it;
  std::set<CNormalProduct*, compareProducts>::const_iterator itEnd = src.mProducts.end();

  for (it = src.mProducts.begin(); it != itEnd; ++it)
    mProducts.insert(new CNormalProduct(**it));

  std::set<CNormalFraction*>::const_iterator it2;
  std::set<CNormalFraction*>::const_iterator it2End = src.mFractions.end();

  for (it2 = src.mFractions.begin(); it2 != it2End; ++it2)
    mFractions.insert(new CNormalFraction(**it2));
}

CNormalSum & CNormalSum::operator=(const CNormalSum& src)
{
  std::set<CNormalProduct*, compareProducts>::const_iterator it;
  std::set<CNormalProduct*, compareProducts>::const_iterator itEnd = src.mProducts.end();

  for (it = src.mProducts.begin(); it != itEnd; ++it)
    mProducts.insert(new CNormalProduct(**it));

  std::set<CNormalFraction*>::const_iterator it2;
  std::set<CNormalFraction*>::const_iterator it2End = src.mFractions.end();

  for (it2 = src.mFractions.begin(); it2 != it2End; ++it2)
    mFractions.insert(new CNormalFraction(**it2));

  return *this;
}

CNormalSum::~CNormalSum()
{
  std::set<CNormalProduct*, compareProducts>::const_iterator it;
  std::set<CNormalProduct*, compareProducts>::const_iterator itEnd = mProducts.end();

  for (it = mProducts.begin(); it != itEnd; ++it)
    delete *it;

  std::set<CNormalFraction*>::const_iterator it2;
  std::set<CNormalFraction*>::const_iterator it2End = mFractions.end();

  for (it2 = mFractions.begin(); it2 != it2End; ++it2)
    delete *it2;
}

CNormalSum* CNormalSum::createSum(const CEvaluationNode* node)
{
  CNormalSum* sum = new CNormalSum();

  if (node->getData() != "+")
    {
      if (node->getData() == "/")
        {
          CNormalFraction* fraction = CNormalFraction::createFraction(node);
          sum->add(*fraction);
          delete fraction;
          return sum;
        }
      else
        {
          CNormalProduct* product = CNormalProduct::createProduct(node);
          sum->add(*product);
          delete product;
          return sum;
        }
    }
  else
    {
      CNormalSum* sum1 = createSum(static_cast<const CEvaluationNode*>(node->getChild()));
      CNormalSum* sum2 = createSum(static_cast<const CEvaluationNode*>(node->getChild()->getSibling()));
      sum->add(*sum1);
      sum->add(*sum2);
      delete sum1;
      delete sum2;
      return sum;
    }
}

int CNormalSum::getSize() const
{
  return mProducts.size() + mFractions.size();
}

bool CNormalSum::add(const CNormalProduct& product)
{
  if (fabs(product.getFactor()) < 1.0E-100)
    return true;

  std::set<CNormalProduct*, compareProducts>::iterator it;
  std::set<CNormalProduct*, compareProducts>::iterator itEnd = mProducts.end();

  for (it = mProducts.begin(); it != itEnd; ++it)
    {
      if ((*it)->checkSamePowerList(product))
        {
          (*it)->setFactor((*it)->getFactor() + product.getFactor());
          return true;
        }
    }

  CNormalProduct* tmp = new CNormalProduct(product);
  mProducts.insert(tmp);
  return true;
}

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

bool CNormalSum::add(const CNormalSum& sum)
{
  std::set<CNormalProduct*, compareProducts>::const_iterator itProduct;
  std::set<CNormalProduct*, compareProducts>::const_iterator itProductEnd = sum.getProducts().end();

  for (itProduct = sum.getProducts().begin(); itProduct != itProductEnd; ++itProduct)
    add(**itProduct);

  std::set<CNormalFraction*>::const_iterator itFraction;
  std::set<CNormalFraction*>::const_iterator itFractionEnd = sum.getFractions().end();

  for (itFraction = sum.getFractions().begin(); itFraction != itFractionEnd; ++itFraction)
    add(**itFraction);

  return true;
}

bool CNormalSum::multiply(const C_FLOAT64& number)
{
  if (fabs(number) < 1.0E-100)
    {
      std::set<CNormalProduct*, compareProducts>::iterator it3;
      std::set<CNormalProduct*, compareProducts>::iterator it3End = mProducts.end();

      for (it3 = mProducts.begin(); it3 != it3End; ++it3)
        delete *it3;

      std::set<CNormalFraction*>::iterator it4;
      std::set<CNormalFraction*>::iterator it4End = mFractions.end();

      for (it4 = mFractions.begin(); it4 != it4End; ++it4)
        delete *it4;

      return true;
    }

  std::set<CNormalProduct*, compareProducts>::iterator it;
  std::set<CNormalProduct*, compareProducts>::iterator itEnd = mProducts.end();

  for (it = mProducts.begin(); it != itEnd; ++it)
    (*it)->multiply(number);

  std::set<CNormalFraction*>::iterator it2;
  std::set<CNormalFraction*>::iterator it2End = mFractions.end();

  for (it2 = mFractions.begin(); it2 != it2End; ++it2)
    (*it2)->multiply(number);

  return true;
}

bool CNormalSum::multiply(const CNormalItemPower& itemPower)
{
  std::set<CNormalProduct*, compareProducts>::iterator it;
  std::set<CNormalProduct*, compareProducts>::iterator itEnd = mProducts.end();

  for (it = mProducts.begin(); it != itEnd; ++it)
    (*it)->multiply(itemPower);

  std::set<CNormalFraction*>::iterator it2;
  std::set<CNormalFraction*>::iterator it2End = mFractions.end();

  for (it2 = mFractions.begin(); it2 != it2End; ++it2)
    (*it2)->multiply(itemPower);

  return true;
}

bool CNormalSum::multiply(const CNormalSum& sum)  //both sums do not contain fractions.
{
  std::set<CNormalProduct*, compareProducts> tmpProducts = mProducts;
  mProducts.clear();
  std::set<CNormalProduct*, compareProducts>::iterator it;
  std::set<CNormalProduct*, compareProducts>::iterator itEnd = tmpProducts.end();

  for (it = tmpProducts.begin(); it != itEnd; ++it)
    {
      add(*(*it)->multiply(sum));
      delete *it;
    }

  return true;
}

bool CNormalSum::multiply(const CNormalLcm& lcm) //the fractions of this sum do not contain further fractions!
{
  std::set<CNormalProduct*, compareProducts> tmpProducts = mProducts;
  mProducts.clear();
  std::set<CNormalProduct*, compareProducts>::const_iterator it2;
  std::set<CNormalProduct*, compareProducts>::const_iterator it2End = tmpProducts.end();

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
      add(*summand2);
      delete summand2;
      delete *it;
    }

  mFractions.clear();  //after multiplication this sum does not contain fractions anymore
  return true;
}

bool CNormalSum::divide(const CNormalItemPower& itemPower) //this sum does not contain fractions! Assume itemPower is factor
{
  std::set<CNormalProduct*, compareProducts>::iterator it;
  std::set<CNormalProduct*, compareProducts>::iterator itEnd = mProducts.end();

  for (it = mProducts.begin(); it != itEnd; ++it)
    (*it)->remove(itemPower);

  return true;
}

C_FLOAT64 CNormalSum::checkFactor(const CNormalItemPower& itemPower) const //sum does not contain fractions!!
{
  C_FLOAT64 exp = itemPower.getExp();
  std::set<CNormalProduct*, compareProducts>::iterator it;
  std::set<CNormalProduct*, compareProducts>::iterator itEnd = mProducts.end();

  for (it = mProducts.begin(); it != itEnd; ++it)
    {
      bool containsFactor = false;
      std::set<CNormalItemPower*, compareItemPowers>::iterator it2;
      std::set<CNormalItemPower*, compareItemPowers>::iterator it2End = (*it)->getItemPowers().end();

      for (it2 = (*it)->getItemPowers().begin(); it2 != it2End; ++it2)
        {
          if ((*it2)->getItem() == itemPower.getItem())
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

const std::set<CNormalProduct*, compareProducts>& CNormalSum::getProducts() const
{
  return mProducts;
}

const std::set<CNormalFraction*>& CNormalSum::getFractions() const
{
  return mFractions;
}

bool CNormalSum::operator==(const CNormalSum & rhs) const
{
  if (mProducts.size() != rhs.mProducts.size())
    return false;

  if (mFractions.size() != rhs.mFractions.size())
    return false;

  std::set<CNormalProduct*, compareProducts>::const_iterator it;
  std::set<CNormalProduct*, compareProducts>::const_iterator itEnd = this->mProducts.end();
  std::set<CNormalProduct*, compareProducts>::const_iterator it2;
  std::set<CNormalProduct*, compareProducts>::const_iterator it2End = rhs.mProducts.end();

  for (it = mProducts.begin(), it2 = rhs.mProducts.begin(); it != itEnd; ++it, ++it2)
    {
      if (!(**it == **it2))
        return false;
    }

  std::set<CNormalFraction*>::const_iterator it3;
  std::set<CNormalFraction*>::const_iterator it3End = this->mFractions.end();
  std::set<CNormalFraction*>::const_iterator it4;
  std::set<CNormalFraction*>::const_iterator it4End = rhs.mFractions.end();

  for (it3 = mFractions.begin(), it4 = rhs.mFractions.begin(); it3 != it3End; ++it3, ++it4)
    {
      if (!(**it3 == **it4))
        return false;
    }

  return true;
}

std::ostream & operator<<(std::ostream &os, const CNormalSum & d)
{
  if (d.getSize() != 0)
    {
      bool firstSummand = true;
      std::set<CNormalProduct*, compareProducts>::const_iterator it;
      std::set<CNormalProduct*, compareProducts>::const_iterator itEnd = d.mProducts.end();

      for (it = d.mProducts.begin(); it != itEnd; ++it)
        {
          if (firstSummand == false)
            os << " + ";

          os << **it;
          firstSummand = false;
        }

      std::set<CNormalFraction*>::const_iterator it2;
      std::set<CNormalFraction*>::const_iterator it2End = d.mFractions.end();

      for (it2 = d.mFractions.begin(); it2 != it2End; ++it2)
        {
          if (firstSummand == false)
            os << " + ";

          os << **it2;
          firstSummand = false;
        }
    }
  else
    os << "0.0";

  return os;
}
