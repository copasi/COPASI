// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_normalform.cpp,v $
//   $Revision: 1.31 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/07/26 11:59:51 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "test_normalform.hpp"

#include <string>
#include <set>
#include <math.h>

#include "function/CEvaluationTree.h"
#include "function/CEvaluationNode.h"
#include "compareExpressions/CNormalFraction.h"
#include "compareExpressions/CNormalTranslation.h"
#include "compareExpressions/CNormalSum.h"
#include "compareExpressions/CNormalProduct.h"
#include "compareExpressions/CNormalItemPower.h"
#include "compareExpressions/CNormalItem.h"
#include "compareExpressions/CNormalFunction.h"
#include "compareExpressions/CNormalGeneralPower.h"
#include "compareExpressions/CNormalChoice.h"
#include "compareExpressions/CNormalChoiceLogical.h"
#include "compareExpressions/CNormalLogical.h"
#include "compareExpressions/CNormalLogicalItem.h"

#ifdef __SUNPRO_CC
typedef std::set<CNormalProduct*, compareProducts>::iterator ProductIterator;
typedef std::set<CNormalItemPower*, compareItemPowers>::iterator ItemPowerIterator;
#else
typedef std::set<CNormalProduct*, compareProducts>::const_iterator ProductIterator;
typedef std::set<CNormalItemPower*, compareItemPowers>::const_iterator ItemPowerIterator;
#endif // __SUNPRO_CC

void test_normalform::setUp()
{
  pFraction = NULL;
}

void test_normalform::tearDown()
{
  if (pFraction != NULL) delete pFraction;
}

void test_normalform::test_item_number()
{
  std::string infix("7.0");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 7.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_item_variable()
{
  std::string infix("Vmax");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "Vmax");
}

void test_normalform::test_item_constant()
{
  std::string infix("PI");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");
}

void test_normalform::test_item_function()
{
  std::string infix("SIN(3.0)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::SIN);

  const CNormalFraction* pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_sum_numbers()
{
  std::string infix("7.0+3.0");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  ProductIterator it = products.begin();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 10.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_sum_variables()
{
  std::string infix("A+B");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 2);
  ProductIterator it = products.begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
}

void test_normalform::test_sum_constants()
{
  std::string infix("PI+EXPONENTIALE");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 2);
  ProductIterator it = products.begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "EXPONENTIALE");
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");
}

void test_normalform::test_sum_functions()
{
  std::string infix("SIN(5.0)+COS(3.0)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 2);
  std::set<CNormalProduct*, compareProducts >::iterator it = products.begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::SIN);

  const CNormalFraction* pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 5.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::COS);

  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_sum_functions_reversed()
{
  std::string infix("COS(3.0)+SIN(5.0)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 2);
  std::set<CNormalProduct*, compareProducts >::iterator it = products.begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::SIN);

  const CNormalFraction* pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 5.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::COS);

  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_sum_mixed_1()
{
  std::string infix("7.0+SIN(4.0)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  std::set<CNormalProduct*, compareProducts >::iterator it = products.begin();
  CPPUNIT_ASSERT(products.size() == 2);
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 7.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::SIN);

  const CNormalFraction* pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 4.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_sum_mixed_1_reversed()
{
  std::string infix("SIN(4.0)+7.0");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  std::set<CNormalProduct*, compareProducts >::iterator it = products.begin();
  CPPUNIT_ASSERT(products.size() == 2);
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 7.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::SIN);

  const CNormalFraction* pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 4.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_sum_mixed_2()
{
  std::string infix("A+COS(0.0)+PI");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  std::set<CNormalProduct*, compareProducts >::iterator it = products.begin();
  CPPUNIT_ASSERT(products.size() == 3);
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");

  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");

  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::COS);

  const CNormalFraction* pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 0);
}

void test_normalform::test_sum_mixed_2_reversed()
{
  std::string infix("PI+COS(0.0)+A");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  std::set<CNormalProduct*, compareProducts >::iterator it = products.begin();
  CPPUNIT_ASSERT(products.size() == 3);
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");

  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");

  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::COS);

  const CNormalFraction* pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 0);
}

void test_normalform::test_product_numbers()
{
  std::string infix("7.0*3.0");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 21.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_product_variables()
{
  std::string infix("A*B");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = products.begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
}

void test_normalform::test_product_variables_reversed()
{
  std::string infix("B*A");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = products.begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
}

void test_normalform::test_product_constants()
{
  std::string infix("PI*EXPONENTIALE");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = products.begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "EXPONENTIALE");
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");
}

void test_normalform::test_product_constants_reversed()
{
  std::string infix("EXPONENTIALE*PI");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = products.begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "EXPONENTIALE");
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");
}

void test_normalform::test_product_functions()
{
  std::string infix("SIN(2.1)*COS(3.5)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = products.begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pItem = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalFunction::SIN);

  const CNormalFraction* pFraction2 = &pItem->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 2.1);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  pItem = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalFunction::COS);

  const CNormalFraction* pFraction3 = &pItem->getFraction();
  CPPUNIT_ASSERT(pFraction3->checkDenominatorOne() == true);
  const CNormalSum& numerator3 = pFraction3->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.5);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_product_functions_reversed()
{
  std::string infix("COS(3.5)*SIN(2.1)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = products.begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pItem = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalFunction::SIN);

  const CNormalFraction* pFraction2 = &pItem->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 2.1);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  pItem = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalFunction::COS);

  const CNormalFraction* pFraction3 = &pItem->getFraction();
  CPPUNIT_ASSERT(pFraction3->checkDenominatorOne() == true);
  const CNormalSum& numerator3 = pFraction3->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.5);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_product_mixed_1()
{
  std::string infix("7.0*SIN(1.5)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 7.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::SIN);

  const CNormalFraction* pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.5);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_product_mixed_1_reversed()
{
  std::string infix("SIN(1.5)*7.0");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 7.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::SIN);

  const CNormalFraction* pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.5);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_product_mixed_2()
{
  std::string infix("A*COS(1.2)*7.0*PI");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 7.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 3);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it = pProduct->getItemPowers().begin();

  const CNormalItemPower* pItemPower = *(it);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");
  ++it;

  pItemPower = *(it);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  ++it;

  pItemPower = *(it);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::COS);

  const CNormalFraction* pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.2);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_product_mixed_2_reversed()
{
  std::string infix("PI*7.0*COS(1.2)*A");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 7.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 3);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it = pProduct->getItemPowers().begin();

  const CNormalItemPower* pItemPower = *(it);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");
  ++it;

  pItemPower = *(it);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  ++it;

  pItemPower = *(it);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::COS);

  const CNormalFraction* pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.2);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_fraction_numbers()
{
  std::string infix("7.0/3.0");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  double quotient = (double)7.0 / (double)3.0;
  CPPUNIT_ASSERT(fabs((pProduct->getFactor() - quotient) / quotient) < 1e-15);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_fraction_variables()
{
  std::string infix("A/B");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");

  const CNormalSum& denominator = pFraction->getDenominator();
  CPPUNIT_ASSERT(denominator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = denominator.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
}

void test_normalform::test_fraction_constants()
{
  std::string infix("PI/EXPONENTIALE");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");

  const CNormalSum& denominator = pFraction->getDenominator();
  CPPUNIT_ASSERT(denominator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = denominator.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "EXPONENTIALE");
}

void test_normalform::test_fraction_functions()
{
  std::string infix("SIN(1.4)/COS(1.3)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::SIN);

  const CNormalFraction* pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.4);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);

  const CNormalSum& denominator = pFraction->getDenominator();
  CPPUNIT_ASSERT(denominator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = denominator.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::COS);

  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products4 = numerator3.getProducts();
  CPPUNIT_ASSERT(products4.size() == 1);
  pProduct = *(products4.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.3);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_fraction_mixed_1()
{
  std::string infix("7.0/A");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 7.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);

  const CNormalSum& denominator = pFraction->getDenominator();
  CPPUNIT_ASSERT(denominator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = denominator.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
}

void test_normalform::test_fraction_mixed_2()
{
  std::string infix("PI/TAN(A)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");

  const CNormalSum& denominator = pFraction->getDenominator();
  CPPUNIT_ASSERT(denominator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = denominator.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::TAN);

  const CNormalFraction* pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products4 = numerator3.getProducts();
  CPPUNIT_ASSERT(products4.size() == 1);
  pProduct = *(products4.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
}

void test_normalform::test_itempower_numbers()
{
  std::string infix("4.0^3");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 64.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_itempower_variables()
{
  std::string infix("A^2");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
}

void test_normalform::test_itempower_constants()
{
  std::string infix("PI^2");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");
}

void test_normalform::test_itempower_functions()
{
  std::string infix("SIN(5.5)^5");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 5.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::SIN);

  const CNormalFraction* pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 5.5);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_generalpower_number_and_variable()
{
  std::string infix("7.0^A");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pPower != NULL);
  CPPUNIT_ASSERT(pPower->getType() == CNormalGeneralPower::POWER);

  const CNormalFraction* pFraction2 = &pPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 7.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);

  pFraction2 = &pPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
}

void test_normalform::test_generalpower_variable_and_variable()
{
  std::string infix("B^A");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pPower != NULL);
  CPPUNIT_ASSERT(pPower->getType() == CNormalGeneralPower::POWER);

  const CNormalFraction* pFraction2 = &pPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");

  pFraction2 = &pPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
}

void test_normalform::test_generalpower_constant_and_constant()
{
  std::string infix("PI^EXPONENTIALE");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pPower != NULL);
  CPPUNIT_ASSERT(pPower->getType() == CNormalGeneralPower::POWER);

  const CNormalFraction* pFraction2 = &pPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");

  pFraction2 = &pPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "EXPONENTIALE");
}

void test_normalform::test_generalpower_function_and_function()
{
  std::string infix("COS(5.0)^SIN(2.0)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pPower != NULL);
  CPPUNIT_ASSERT(pPower->getType() == CNormalGeneralPower::POWER);

  const CNormalFraction* pFraction2 = &pPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::COS);

  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 5.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);

  pFraction2 = &pPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator4 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator4.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products4 = numerator4.getProducts();
  CPPUNIT_ASSERT(products4.size() == 1);
  pProduct = *(products4.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::SIN);

  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator5 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator5.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products5 = numerator5.getProducts();
  CPPUNIT_ASSERT(products5.size() == 1);
  pProduct = *(products5.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 2.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_generalmodulus_number_and_variable()
{
  std::string infix("7.0%A");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pPower != NULL);
  CPPUNIT_ASSERT(pPower->getType() == CNormalGeneralPower::MODULO);

  const CNormalFraction* pFraction2 = &pPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 7.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);

  pFraction2 = &pPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
}

void test_normalform::test_generalmodulus_variable_and_variable()
{
  std::string infix("B%A");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pPower != NULL);
  CPPUNIT_ASSERT(pPower->getType() == CNormalGeneralPower::MODULO);

  const CNormalFraction* pFraction2 = &pPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");

  pFraction2 = &pPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
}

void test_normalform::test_generalmodulus_constant_and_constant()
{
  std::string infix("PI%EXPONENTIALE");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pPower != NULL);
  CPPUNIT_ASSERT(pPower->getType() == CNormalGeneralPower::MODULO);

  const CNormalFraction* pFraction2 = &pPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");

  pFraction2 = &pPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "EXPONENTIALE");
}

void test_normalform::test_generalmodulus_function_and_function()
{
  std::string infix("COS(5.0)%SIN(2.0)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pPower != NULL);
  CPPUNIT_ASSERT(pPower->getType() == CNormalGeneralPower::MODULO);

  const CNormalFraction* pFraction2 = &pPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::COS);

  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 5.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);

  pFraction2 = &pPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator4 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator4.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products4 = numerator4.getProducts();
  CPPUNIT_ASSERT(products4.size() == 1);
  pProduct = *(products4.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::SIN);

  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator5 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator5.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products5 = numerator5.getProducts();
  CPPUNIT_ASSERT(products5.size() == 1);
  pProduct = *(products5.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 2.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_generalpower_mixed_1()
{
  std::string infix("(7.0+X)^FLOOR(PI/2)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pPower != NULL);
  CPPUNIT_ASSERT(pPower->getType() == CNormalGeneralPower::POWER);

  const CNormalFraction* pFraction2 = &pPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 2);
  ProductIterator it = products2.begin();
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 7.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "X");

  pFraction2 = &pPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator4 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator4.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products4 = numerator4.getProducts();
  CPPUNIT_ASSERT(products4.size() == 1);
  pProduct = *(products4.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::FLOOR);

  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator5 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator5.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products5 = numerator5.getProducts();
  CPPUNIT_ASSERT(products5.size() == 1);
  pProduct = *(products5.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 0.5);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *pProduct->getItemPowers().begin();
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");
}

void test_normalform::test_generalpower_mixed_2()
{
  std::string infix("TAN(5.0)^A");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pPower != NULL);
  CPPUNIT_ASSERT(pPower->getType() == CNormalGeneralPower::POWER);

  const CNormalFraction* pFraction2 = &pPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::TAN);

  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 5.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);

  pFraction2 = &pPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator4 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator4.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products4 = numerator4.getProducts();
  CPPUNIT_ASSERT(products4.size() == 1);
  pProduct = *(products4.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
}

void test_normalform::test_generalpower_mixed_3()
{
  std::string infix("A^CEIL(PI)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pPower != NULL);
  CPPUNIT_ASSERT(pPower->getType() == CNormalGeneralPower::POWER);

  const CNormalFraction* pFraction2 = &pPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");

  pFraction2 = &pPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator4 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator4.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products4 = numerator4.getProducts();
  CPPUNIT_ASSERT(products4.size() == 1);
  pProduct = *(products4.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::CEIL);

  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator5 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator5.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products5 = numerator5.getProducts();
  CPPUNIT_ASSERT(products5.size() == 1);
  pProduct = *(products5.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *pProduct->getItemPowers().begin();
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");
}

void test_normalform::test_generalpower_mixed_4()
{
  std::string infix("EXPONENTIALE^A");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pPower != NULL);
  CPPUNIT_ASSERT(pPower->getType() == CNormalGeneralPower::POWER);

  const CNormalFraction* pFraction2 = &pPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "EXPONENTIALE");

  pFraction2 = &pPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
}

void test_normalform::test_generalmodulus_mixed_1()
{
  std::string infix("(7.0+X)%FLOOR(PI/2)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pPower != NULL);
  CPPUNIT_ASSERT(pPower->getType() == CNormalGeneralPower::MODULO);

  const CNormalFraction* pFraction2 = &pPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 2);
  ProductIterator it = products2.begin();
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 7.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "X");

  pFraction2 = &pPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator4 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator4.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products4 = numerator4.getProducts();
  CPPUNIT_ASSERT(products4.size() == 1);
  pProduct = *(products4.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::FLOOR);

  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator5 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator5.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products5 = numerator5.getProducts();
  CPPUNIT_ASSERT(products5.size() == 1);
  pProduct = *(products5.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 0.5);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *pProduct->getItemPowers().begin();
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");
}

void test_normalform::test_generalmodulus_mixed_2()
{
  std::string infix("TAN(5.0)%A");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pPower != NULL);
  CPPUNIT_ASSERT(pPower->getType() == CNormalGeneralPower::MODULO);

  const CNormalFraction* pFraction2 = &pPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::TAN);

  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 5.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);

  pFraction2 = &pPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator4 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator4.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products4 = numerator4.getProducts();
  CPPUNIT_ASSERT(products4.size() == 1);
  pProduct = *(products4.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
}

void test_normalform::test_generalmodulus_mixed_3()
{
  std::string infix("A%CEIL(PI)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pPower != NULL);
  CPPUNIT_ASSERT(pPower->getType() == CNormalGeneralPower::MODULO);

  const CNormalFraction* pFraction2 = &pPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");

  pFraction2 = &pPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator4 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator4.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products4 = numerator4.getProducts();
  CPPUNIT_ASSERT(products4.size() == 1);
  pProduct = *(products4.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::CEIL);

  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum& numerator5 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator5.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products5 = numerator5.getProducts();
  CPPUNIT_ASSERT(products5.size() == 1);
  pProduct = *(products5.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *pProduct->getItemPowers().begin();
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");
}

void test_normalform::test_generalmodulus_mixed_4()
{
  std::string infix("EXPONENTIALE%A");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pPower != NULL);
  CPPUNIT_ASSERT(pPower->getType() == CNormalGeneralPower::MODULO);

  const CNormalFraction* pFraction2 = &pPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator2 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator2.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products2 = numerator2.getProducts();
  CPPUNIT_ASSERT(products2.size() == 1);
  pProduct = *(products2.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "EXPONENTIALE");

  pFraction2 = &pPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  const CNormalSum& numerator3 = pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator3.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products3 = numerator3.getProducts();
  CPPUNIT_ASSERT(products3.size() == 1);
  pProduct = *(products3.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
}

void test_normalform::test_simple_stepwise_numbers()
{
  std::string infix("IF(TRUE,2.3,4.5)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

  const CNormalSum* numerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  const CNormalProduct* pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::CHOICE);
  const CNormalChoice* pChoice = dynamic_cast<const CNormalChoice*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pChoice != NULL);

  // check the condition
  const CNormalLogical* pLogical = &pChoice->getCondition();
  CPPUNIT_ASSERT(pLogical != NULL);
  CPPUNIT_ASSERT(pLogical->isNegated() == false);
  CPPUNIT_ASSERT(pLogical->getChoices().size() == 0);
  CPPUNIT_ASSERT(pLogical->getAndSets().size() == 1);
  std::pair<CNormalLogical::ItemSet, bool> outerpair = *(pLogical->getAndSets().begin());
  CPPUNIT_ASSERT(outerpair.second == false);
  CPPUNIT_ASSERT(outerpair.first.size() == 1);
  std::pair<CNormalLogicalItem*, bool> innerpair = *(outerpair.first.begin());
  CPPUNIT_ASSERT(innerpair.second == false);
  const CNormalLogicalItem* pLogicalItem = innerpair.first;
  CPPUNIT_ASSERT(pLogicalItem != NULL);
  CPPUNIT_ASSERT(pLogicalItem->getType() == CNormalLogicalItem::TRUE);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::CHOICE);

  // check the true branch
  const CNormalFraction* pFraction2 = &pChoice->getTrueExpression();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 2.3);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);

  // check the false branch
  pFraction2 = &pChoice->getFalseExpression();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 4.5);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_simple_stepwise_fractions()
{
  std::string infix("IF(TRUE,A/TAN(X)^R,SIN(PI)/A^6)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

  const CNormalSum* numerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  const CNormalProduct* pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::CHOICE);
  const CNormalChoice* pChoice = dynamic_cast<const CNormalChoice*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pChoice != NULL);

  // check the condition
  const CNormalLogical* pLogical = &pChoice->getCondition();
  CPPUNIT_ASSERT(pLogical != NULL);
  CPPUNIT_ASSERT(pLogical->isNegated() == false);
  CPPUNIT_ASSERT(pLogical->getChoices().size() == 0);
  CPPUNIT_ASSERT(pLogical->getAndSets().size() == 1);
  std::pair<CNormalLogical::ItemSet, bool> outerpair = *(pLogical->getAndSets().begin());
  CPPUNIT_ASSERT(outerpair.second == false);
  CPPUNIT_ASSERT(outerpair.first.size() == 1);
  std::pair<CNormalLogicalItem*, bool> innerpair = *(outerpair.first.begin());
  CPPUNIT_ASSERT(innerpair.second == false);
  const CNormalLogicalItem* pLogicalItem = innerpair.first;
  CPPUNIT_ASSERT(pLogicalItem != NULL);
  CPPUNIT_ASSERT(pLogicalItem->getType() == CNormalLogicalItem::TRUE);

  // check the true branch
  const CNormalFraction* pFraction2 = &pChoice->getTrueExpression();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  const CNormalSum* denominator = &pFraction2->getDenominator();
  CPPUNIT_ASSERT(denominator->getFractions().size() == 0);
  products = &denominator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::TAN);
  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "X");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "R");

  // check false branch
  pFraction2 = &pChoice->getFalseExpression();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::SIN);
  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");

  // set pFraction2 again since it has been set to the fraction of the function
  // above
  pFraction2 = &pChoice->getFalseExpression();
  denominator = &pFraction2->getDenominator();
  CPPUNIT_ASSERT(denominator->getFractions().size() == 0);
  products = &denominator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 6.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
}

void test_normalform::test_simple_nested_stepwise_numbers()
{
  std::string infix("IF(IF(IF(TRUE,FALSE,TRUE),IF(FALSE,TRUE,FALSE),IF(FALSE,FALSE,FALSE)),2.3,4.5)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

  const CNormalSum* numerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  const CNormalProduct* pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::CHOICE);
  const CNormalChoice* pChoice = dynamic_cast<const CNormalChoice*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pChoice != NULL);

  // check the condition
  const CNormalLogical* pLogical = &pChoice->getCondition();
  CPPUNIT_ASSERT(pLogical != NULL);
  CPPUNIT_ASSERT(pLogical->isNegated() == false);
  CPPUNIT_ASSERT(pLogical->getChoices().size() == 0);
  CPPUNIT_ASSERT(pLogical->getAndSets().size() == 1);
  std::pair<CNormalLogical::ItemSet, bool> outerpair = *(pLogical->getAndSets().begin());
  CPPUNIT_ASSERT(outerpair.second == false);
  CPPUNIT_ASSERT(outerpair.first.size() == 1);
  std::pair<CNormalLogicalItem*, bool> innerpair = *(outerpair.first.begin());
  CPPUNIT_ASSERT(innerpair.second == false);
  const CNormalLogicalItem* pLogicalItem = innerpair.first;
  CPPUNIT_ASSERT(pLogicalItem != NULL);
  CPPUNIT_ASSERT(pLogicalItem->getType() == CNormalLogicalItem::FALSE);

  // check the true branch
  const CNormalFraction* pFraction2 = &pChoice->getTrueExpression();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 2.3);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);

  // check the false branch
  pFraction2 = &pChoice->getFalseExpression();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 4.5);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_simple_nested_stepwise_fractions()
{
  std::string infix("IF(IF(IF(TRUE,FALSE,TRUE),IF(FALSE,TRUE,FALSE),IF(FALSE,FALSE,FALSE)),A/TAN(X)^R,SIN(PI)/A^6)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

  const CNormalSum* numerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  const CNormalProduct* pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::CHOICE);
  const CNormalChoice* pChoice = dynamic_cast<const CNormalChoice*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pChoice != NULL);

  // check the condition
  const CNormalLogical* pLogical = &pChoice->getCondition();
  CPPUNIT_ASSERT(pLogical != NULL);
  CPPUNIT_ASSERT(pLogical->isNegated() == false);
  CPPUNIT_ASSERT(pLogical->getChoices().size() == 0);
  CPPUNIT_ASSERT(pLogical->getAndSets().size() == 1);
  std::pair<CNormalLogical::ItemSet, bool> outerpair = *(pLogical->getAndSets().begin());
  CPPUNIT_ASSERT(outerpair.second == false);
  CPPUNIT_ASSERT(outerpair.first.size() == 1);
  std::pair<CNormalLogicalItem*, bool> innerpair = *(outerpair.first.begin());
  CPPUNIT_ASSERT(innerpair.second == false);
  const CNormalLogicalItem* pLogicalItem = innerpair.first;
  CPPUNIT_ASSERT(pLogicalItem != NULL);
  CPPUNIT_ASSERT(pLogicalItem->getType() == CNormalLogicalItem::FALSE);

  // check the true branch
  const CNormalFraction* pFraction2 = &pChoice->getTrueExpression();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  const CNormalSum* denominator = &pFraction2->getDenominator();
  CPPUNIT_ASSERT(denominator->getFractions().size() == 0);
  products = &denominator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::TAN);
  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "X");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "R");

  // check false branch
  pFraction2 = &pChoice->getFalseExpression();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::SIN);
  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");

  // set pFraction2 again since it has been set to the fraction of the function
  // above
  pFraction2 = &pChoice->getFalseExpression();
  denominator = &pFraction2->getDenominator();
  CPPUNIT_ASSERT(denominator->getFractions().size() == 0);
  products = &denominator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 6.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
}

void test_normalform::test_nested_stepwise_numbers_2levels_1()
{
  std::string infix("IF(IF(A gt PI,FALSE,4.0 ne A),2.3,4.5)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

  const CNormalSum* numerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  const CNormalProduct* pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::CHOICE);
  const CNormalChoice* pChoice = dynamic_cast<const CNormalChoice*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pChoice != NULL);

  // check the condition
  const CNormalLogical* pLogical = &pChoice->getCondition();
  CPPUNIT_ASSERT(pLogical != NULL);
  CPPUNIT_ASSERT(pLogical->isNegated() == false);
  CPPUNIT_ASSERT(pLogical->getChoices().size() == 0);
  CPPUNIT_ASSERT(pLogical->getAndSets().size() == 1);

  CNormalLogical::ItemSetOfSets::const_iterator outerIt = pLogical->getAndSets().begin();
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 2);
  CNormalLogical::ItemSet::const_iterator innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  const CNormalLogicalItem* pLogicalItem = innerIt->first;
  CPPUNIT_ASSERT(check_LogicalItemB(pLogicalItem) == true);

  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  pLogicalItem = innerIt->first;
  CPPUNIT_ASSERT(check_LogicalItemNotA(pLogicalItem) == true);

  // check the true branch
  const CNormalFraction* pFraction2 = &pChoice->getTrueExpression();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 2.3);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);

  // check the false branch
  pFraction2 = &pChoice->getFalseExpression();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 4.5);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_nested_stepwise_numbers_2levels_2()
{
  std::string infix("IF(IF(2 eq T,FALSE,NOT (D eq F)),2.3,4.5)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

  const CNormalSum* numerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  const CNormalProduct* pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::CHOICE);
  const CNormalChoice* pChoice = dynamic_cast<const CNormalChoice*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pChoice != NULL);

  // check condition
  const CNormalLogical* pLogical = &pChoice->getCondition();
  CPPUNIT_ASSERT(pLogical != NULL);
  CPPUNIT_ASSERT(pLogical->isNegated() == false);
  CPPUNIT_ASSERT(pLogical->getChoices().size() == 0);
  CPPUNIT_ASSERT(pLogical->getAndSets().size() == 1);
  CNormalLogical::ItemSetOfSets::const_iterator outerIt = pLogical->getAndSets().begin();
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 2);
  CNormalLogical::ItemSet::const_iterator innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);

  const CNormalLogicalItem* pLogicalItem = innerIt->first;
  // check type, left side and right side
  CPPUNIT_ASSERT(check_LogicalItemNotD(pLogicalItem) == true);

  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  pLogicalItem = innerIt->first;
  // check type, left side and right side
  CPPUNIT_ASSERT(check_LogicalItemNotC(pLogicalItem) == true);

  // check the true branch
  const CNormalFraction* pFraction2 = &pChoice->getTrueExpression();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 2.3);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);

  // check the false branch
  pFraction2 = &pChoice->getFalseExpression();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 4.5);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_nested_stepwise_numbers_2levels_3()
{
  std::string infix("IF(IF(SIN(D*PI) lt X,TRUE,2*T^(3*J) ne 6.2),2.3,4.5)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

  const CNormalSum* numerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  const CNormalProduct* pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::CHOICE);
  const CNormalChoice* pChoice = dynamic_cast<const CNormalChoice*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pChoice != NULL);

  // check condition
  const CNormalLogical* pLogical = &pChoice->getCondition();
  CPPUNIT_ASSERT(pLogical != NULL);
  CPPUNIT_ASSERT(pLogical->isNegated() == false);
  CPPUNIT_ASSERT(pLogical->getChoices().size() == 0);
  CPPUNIT_ASSERT(pLogical->getAndSets().size() == 3);
  CNormalLogical::ItemSetOfSets::const_iterator outerIt = pLogical->getAndSets().begin();
  // (2*T^(3J)==6.2 && SIN(PI*D)<X)
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 2);
  CNormalLogical::ItemSet::const_iterator innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  const CNormalLogicalItem* pLogicalItem = innerIt->first;
  // check type, left side and right side
  CPPUNIT_ASSERT(check_LogicalItemNotF(pLogicalItem) == true);

  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  pLogicalItem = innerIt->first;
  // check type, left side and right side
  CPPUNIT_ASSERT(check_LogicalItemE(pLogicalItem) == true);

  ++outerIt;
  // check the second and set
  // (2*T^(3J)!=6.2 && SIN(PI*D)<X)
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 2);
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  pLogicalItem = innerIt->first;
  // check type, left side and right side
  CPPUNIT_ASSERT(check_LogicalItemF(pLogicalItem) == true);

  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  pLogicalItem = innerIt->first;
  // check type, left side and right side
  CPPUNIT_ASSERT(check_LogicalItemE(pLogicalItem) == true);

  ++outerIt;
  // check the second and set
  // (2*T^(3J)!=6.2 && x<=SIN(PI*D))
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 2);
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  pLogicalItem = innerIt->first;
  // check type, left side and right side
  CPPUNIT_ASSERT(check_LogicalItemF(pLogicalItem) == true);

  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  pLogicalItem = innerIt->first;
  // check type, left side and right side
  CPPUNIT_ASSERT(check_LogicalItemNotE(pLogicalItem) == true);
  // check the true branch
  const CNormalFraction* pFraction2 = &pChoice->getTrueExpression();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 2.3);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);

  // check the false branch
  pFraction2 = &pChoice->getFalseExpression();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 4.5);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_nested_stepwise_fractions_3levels()
{
  // the condition expression in this test should lead to a truth table with 64 entries and 6 items in each
  // entry, 24 of those items evaluate to false,so 40 entries remain after
  // normalization
  // to simplify the display, the individual logical items are substituted by
  // one letter variables
  // A: A < PI
  // B: 4 != A
  // C: 2 == T
  // D: NOT (D == F)
  // E: SIND(D*PI) < X
  // F: "*T^(3J) != 6.2
  //
  // So the simplified condition is:
  // IF(IF(A,FALSE,B),IF(C,FALSE,D),IF(E,TRUE,F))
  //
  // And the resulting truth table is:
  //     A B C D E F      RESULT
  // 01: 0 0 0 0 0 0        0
  // 02: 0 0 0 0 0 1        1
  // 03: 0 0 0 0 1 0        1
  // 04: 0 0 0 0 1 1        1
  // 05: 0 0 0 1 0 0        0
  // 06: 0 0 0 1 0 1        1
  // 07: 0 0 0 1 1 0        1
  // 08: 0 0 0 1 1 1        1
  // 09: 0 0 1 0 0 0        0
  // 10: 0 0 1 0 0 1        1
  // 11: 0 0 1 0 1 0        1
  // 12: 0 0 1 0 1 1        1
  // 13: 0 0 1 1 0 0        0
  // 14: 0 0 1 1 0 1        1
  // 15: 0 0 1 1 1 0        1
  // 16: 0 0 1 1 1 1        1
  // 17: 0 1 0 0 0 0        0
  // 18: 0 1 0 0 0 1        0
  // 19: 0 1 0 0 1 0        0
  // 20: 0 1 0 0 1 1        0
  // 21: 0 1 0 1 0 0        1
  // 22: 0 1 0 1 0 1        1
  // 23: 0 1 0 1 1 0        1
  // 24: 0 1 0 1 1 1        1
  // 25: 0 1 1 0 0 0        0
  // 26: 0 1 1 0 0 1        0
  // 27: 0 1 1 0 1 0        0
  // 28: 0 1 1 0 1 1        0
  // 29: 0 1 1 1 0 0        0
  // 30: 0 1 1 1 0 1        0
  // 31: 0 1 1 1 1 0        0
  // 32: 0 1 1 1 1 1        0
  // 33: 1 0 0 0 0 0        0
  // 34: 1 0 0 0 0 1        1
  // 35: 1 0 0 0 1 0        1
  // 36: 1 0 0 0 1 1        1
  // 37: 1 0 0 1 0 0        0
  // 38: 1 0 0 1 0 1        1
  // 39: 1 0 0 1 1 0        1
  // 40: 1 0 0 1 1 1        1
  // 41: 1 0 1 0 0 0        0
  // 42: 1 0 1 0 0 1        1
  // 43: 1 0 1 0 1 0        1
  // 44: 1 0 1 0 1 1        1
  // 45: 1 0 1 1 0 0        0
  // 46: 1 0 1 1 0 1        1
  // 47: 1 0 1 1 1 0        1
  // 48: 1 0 1 1 1 1        1
  // 49: 1 1 0 0 0 0        0
  // 50: 1 1 0 0 0 1        1
  // 51: 1 1 0 0 1 0        1
  // 52: 1 1 0 0 1 1        1
  // 53: 1 1 0 1 0 0        0
  // 54: 1 1 0 1 0 1        1
  // 55: 1 1 0 1 1 0        1
  // 56: 1 1 0 1 1 1        1
  // 57: 1 1 1 0 0 0        0
  // 58: 1 1 1 0 0 1        1
  // 59: 1 1 1 0 1 0        1
  // 60: 1 1 1 0 1 1        1
  // 61: 1 1 1 1 0 0        0
  // 62: 1 1 1 1 0 1        1
  // 63: 1 1 1 1 1 0        1
  // 64: 1 1 1 1 1 1        1
  //
  // normalized and simplified forms of logical elements:
  // A: (A < PI)           !A: (PI <= A)
  // B: (4 != A)           !B: (4 == A)
  // C: (2 == T)           !C: (2 != T)
  // D: (D != F)           !D: (D == F)
  // E: (SIN (D*PI) < X)   !E: (X <= SIN(D*PI))
  // F: (6.2 != 2*T^(3J))  !F: (6.2 == 2*T^(3J))
  //
  // after removing the false entries, we are left with the following 40
  // entries.
  // the expanded form is ordered according to the comparison operators
  //     A B C D E F      expanded and ordered
  // 01: 0 0 0 0 0 1   (4 == A) & (D == F) & (2 != T) & (6.2 != 2*T^(3J)) & (PI <= A) & (X <= SIN(D*PI))
  // 02: 0 0 0 0 1 0   (4 == A) & (D == F) & (6.2 == 2*T^(3J)) & (2 != T) & (SIN (D*PI) < X) & (PI <= A)
  // 03: 0 0 0 0 1 1   (4 == A) & (D == F) & (2 != T) & (6.2 != 2*T^(3J)) & (SIN (D*PI) < X) & (PI <= A)
  // 04: 0 0 0 1 0 1   (4 == A) & (2 != T) & (6.2 != 2*T^(3J)) & (D != F) & (PI <= A) & (X <= SIN(D*PI))
  // 05: 0 0 0 1 1 0   (4 == A) & (6.2 == 2*T^(3J)) & (2 != T) & (D != F) & (SIN (D*PI) < X) & (PI <= A)
  // 06: 0 0 0 1 1 1   (4 == A) & (2 != T) & (6.2 != 2*T^(3J)) & (D != F) & (SIN (D*PI) < X) & (PI <= A)
  // 07: 0 0 1 0 0 1   (2 == T) & (4 == A) & (D == F) & (6.2 != 2*T^(3J)) & (PI <= A) & (X <= SIN(D*PI))
  // 08: 0 0 1 0 1 0   (2 == T) & (4 == A) & (6.2 == 2*T^(3J)) & (D == F) & (SIN (D*PI) < X) & (PI <= A)
  // 09: 0 0 1 0 1 1   (2 == T) & (4 == A) & (D == F) & (6.2 != 2*T^(3J)) & (SIN (D*PI) < X) & (PI <= A)
  // 10: 0 0 1 1 0 1   (2 == T) & (4 == A) & (6.2 != 2*T^(3J)) & (D != F) & (PI <= A) & (X <= SIN(D*PI))
  // 11: 0 0 1 1 1 0   (2 == T) & (4 == A) & (6.2 == 2*T^(3J)) & (D != F) & (SIN (D*PI) < X) & (PI <= A)
  // 12: 0 0 1 1 1 1   (2 == T) & (4 == A) & (6.2 != 2*T^(3J)) & (D != F) & (SIN (D*PI) < X) & (PI <= A)
  // 13: 0 1 0 1 0 0   (6.2 == 2*T^(3J)) & (2 != T) & (4 != A) & (D != F) & (PI <= A) & (X <= SIN(D*PI))
  // 14: 0 1 0 1 0 1   (2 != T) & (4 != A) & (6.2 != 2*T^(3J)) & (D != F) & (PI <= A) & (X <= SIN(D*PI))
  // 15: 0 1 0 1 1 0   (6.2 == 2*T^(3J)) & (2 != T) & (4 != A) & (D != F) & (SIN (D*PI) < X) & (PI <= A)
  // 16: 0 1 0 1 1 1   (2 != T) & (4 != A) & (6.2 != 2*T^(3J)) & (D != F) & (SIN (D*PI) < X) & (PI <= A)
  // 17: 1 0 0 0 0 1   (4 == A) & (D == F) & (2 != T) & (6.2 != 2*T^(3J)) & (A  < PI) & (X <= SIN(D*PI))
  // 18: 1 0 0 0 1 0   (4 == A) & (6.2 == 2*T^(3J)) & (D == F) & (2 != T) & (A  < PI) & (SIN (D*PI) < X)
  // 19: 1 0 0 0 1 1   (4 == A) & (D == F) & (2 != T) & (6.2 != 2*T^(3J)) & (A  < PI) & (SIN (D*PI) < X)
  // 20: 1 0 0 1 0 1   (4 == A) & (2 != T) & (6.2 != 2*T^(3J)) & (D != F) & (A  < PI) & (X <= SIN(D*PI))
  // 21: 1 0 0 1 1 0   (4 == A) & (2 != T) & (6.2 == 2*T^(3J)) & (D != F) & (A  < PI) & (SIN (D*PI) < X)
  // 22: 1 0 0 1 1 1   (4 == A) & (2 != T) & (6.2 != 2*T^(3J)) & (D != F) & (A  < PI) & (SIN (D*PI) < X)
  // 23: 1 0 1 0 0 1   (2 == T) & (4 == A) & (D == F) & (6.2 != 2*T^(3J)) & (A  < PI) & (X <= SIN(D*PI))
  // 24: 1 0 1 0 1 0   (2 == T) & (4 == A) & (6.2 == 2*T^(3J)) & (D == F) & (A  < PI) & (SIN (D*PI) < X)
  // 25: 1 0 1 0 1 1   (2 == T) & (4 == A) & (D == F) & (6.2 != 2*T^(3J)) & (A  < PI) & (SIN (D*PI) < X)
  // 26: 1 0 1 1 0 1   (2 == T) & (4 == A) & (6.2 != 2*T^(3J)) & (D != F) & (A  < PI) & (X <= SIN(D*PI))
  // 27: 1 0 1 1 1 0   (2 == T) & (4 == A) & (6.2 == 2*T^(3J)) & (D != F) & (A  < PI) & (SIN (D*PI) < X)
  // 28: 1 0 1 1 1 1   (2 == T) & (4 == A) & (6.2 != 2*T^(3J)) & (D != F) & (A  < PI) & (SIN (D*PI) < X)
  // 29: 1 1 0 0 0 1   (D == F) & (2 != T) & (4 != A) & (6.2 != 2*T^(3J)) & (A  < PI) & (X <= SIN(D*PI))
  // 30: 1 1 0 0 1 0   (6.2 == 2*T^(3J)) & (D == F) & (2 != T) & (4 != A) & (A  < PI) & (SIN (D*PI) < X)
  // 31: 1 1 0 0 1 1   (D == F) & (2 != T) & (4 != A) & (6.2 != 2*T^(3J)) & (A  < PI) & (SIN (D*PI) < X)
  // 32: 1 1 0 1 0 1   (2 != T) & (4 != A) & (6.2 != 2*T^(3J)) & (D != F) & (A  < PI) & (X <= SIN(D*PI))
  // 33: 1 1 0 1 1 0   (6.2 == 2*T^(3J)) & (2 != T) & (4 != A) & (D != F) & (A  < PI) & (SIN (D*PI) < X)
  // 34: 1 1 0 1 1 1   (2 != T) & (4 != A) & (6.2 != 2*T^(3J)) & (D != F) & (A  < PI) & (SIN (D*PI) < X)
  // 35: 1 1 1 0 0 1   (2 == T) & (D == F) & (4 != A) & (6.2 != 2*T^(3J)) & (A  < PI) & (X <= SIN(D*PI))
  // 36: 1 1 1 0 1 0   (2 == T) & (6.2 == 2*T^(3J)) & (D == F) & (4 != A) & (A  < PI) & (SIN (D*PI) < X)
  // 37: 1 1 1 0 1 1   (2 == T) & (D == F) & (4 != A) & (6.2 != 2*T^(3J)) & (A  < PI) & (SIN (D*PI) < X)
  // 38: 1 1 1 1 0 1   (2 == T) & (4 != A) & (6.2 != 2*T^(3J)) & (D != F) & (A  < PI) & (X <= SIN(D*PI))
  // 39: 1 1 1 1 1 0   (2 == T) & (6.2 == 2*T^(3J)) & (4 != A) & (D != F) & (A  < PI) & (SIN (D*PI) < X)
  // 40: 1 1 1 1 1 1   (2 == T) & (4 != A) & (6.2 != 2*T^(3J)) & (D != F) & (A  < PI) & (SIN (D*PI) < X)
  //
  //
  std::string infix("IF(IF(IF(A gt PI,FALSE,4.0 ne A),IF(2 eq T,FALSE,NOT (D eq F)),IF(SIN(D*PI) lt X,TRUE,2*T^(3*J) ne 6.2)),A/TAN(X)^R,SIN(PI)/A^6)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  //std::cout << pFraction->toString() << std::endl;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

  const CNormalSum* numerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  const CNormalProduct* pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::CHOICE);
  const CNormalChoice* pChoice = dynamic_cast<const CNormalChoice*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pChoice != NULL);

  // check condition
  const CNormalLogical* pLogical = &pChoice->getCondition();
  CPPUNIT_ASSERT(pLogical != NULL);
  CPPUNIT_ASSERT(pLogical->isNegated() == false);
  CPPUNIT_ASSERT(pLogical->getChoices().size() == 0);
  CPPUNIT_ASSERT(pLogical->getAndSets().size() == 40);

  // 40 sets
  CNormalLogical::ItemSetOfSets::const_iterator outerIt = pLogical->getAndSets().begin();
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 1
  // 6 items in each set
  CNormalLogical::ItemSet::const_iterator innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 2
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 3
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 4
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 5
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 6
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 7
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 8
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 9
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 10
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 11
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 12
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 13
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 14
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 15
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 16
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 17
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotA(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 18
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotA(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 19
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotA(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 20
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotA(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 21
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotA(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 22
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotA(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 23
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotA(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 24
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotA(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 25
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotA(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 26
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemE(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotA(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 27
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 28
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 29
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 30
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 31
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 32
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 33
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 34
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 35
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 36
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 37
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 38
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 39
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotE(innerIt->first) == true);

  ++outerIt;
  CPPUNIT_ASSERT(outerIt->second == false);
  CPPUNIT_ASSERT(outerIt->first.size() == 6);
  // 40
  innerIt = outerIt->first.begin();
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotD(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotC(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemF(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemB(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotA(innerIt->first) == true);
  ++innerIt;
  CPPUNIT_ASSERT(innerIt->second == false);
  CPPUNIT_ASSERT(check_LogicalItemNotE(innerIt->first) == true);

  // check the true branch
  const CNormalFraction* pFraction2 = &pChoice->getTrueExpression();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  const CNormalSum* denominator = &pFraction2->getDenominator();
  CPPUNIT_ASSERT(denominator->getFractions().size() == 0);
  products = &denominator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::TAN);
  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "X");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "R");

  // check false branch
  pFraction2 = &pChoice->getFalseExpression();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::FUNCTION);
  pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CNormalFunction::SIN);
  pFraction2 = &pFunction->getFraction();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  numerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(numerator->getFractions().size() == 0);
  products = &numerator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pItem->getName() == "PI");

  // set pFraction2 again since it has been set to the fraction of the function
  // above
  pFraction2 = &pChoice->getFalseExpression();
  denominator = &pFraction2->getDenominator();
  CPPUNIT_ASSERT(denominator->getFractions().size() == 0);
  products = &denominator->getProducts();
  CPPUNIT_ASSERT(products->size() == 1);
  pProduct = *(products->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 6.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
}

// PI < A
bool test_normalform::check_LogicalItemA(const CNormalLogicalItem* pLogicalItem)
{
  bool result = true;
  if (pLogicalItem == NULL) return false;
  if (pLogicalItem->getType() != CNormalLogicalItem::LT) return false;

  const CNormalFraction* pFraction = &pLogicalItem->getLeft();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  if (pNumerator->getFractions().size() != 0) return false;
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  if (pProducts->size() != 1) return false;
  const CNormalProduct* pProduct = *(pProducts->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  const CNormalItem* pNormalItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pNormalItem == NULL) return false;
  if (pNormalItem->getType() != CNormalItem::CONSTANT) return false;
  if (pNormalItem->getName() != "PI") return false;

  pFraction = &pLogicalItem->getRight();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  pNumerator = &pFraction->getNumerator();
  if (pNumerator->getFractions().size() != 0) return false;
  pProducts = &pNumerator->getProducts();
  if (pProducts->size() != 1) return false;
  pProduct = *(pProducts->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  pNormalItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pNormalItem == NULL) return false;
  if (pNormalItem->getType() != CNormalItem::VARIABLE) return false;
  if (pNormalItem->getName() != "A") return false;
  return result;
}

// 4 != A
bool test_normalform::check_LogicalItemB(const CNormalLogicalItem* pLogicalItem)
{
  bool result = true;
  if (pLogicalItem == NULL) return false;
  if (pLogicalItem->getType() != CNormalLogicalItem::NE) return false;

  const CNormalFraction* pFraction = &pLogicalItem->getLeft();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  if (pNumerator->getFractions().size() != 0) return false;
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  if (pProducts->size() != 1) return false;
  const CNormalProduct* pProduct = *(pProducts->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 4.0) return false;
  if (pProduct->getItemPowers().size() != 0) return false;

  pFraction = &pLogicalItem->getRight();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  pNumerator = &pFraction->getNumerator();
  if (pNumerator->getFractions().size() != 0) return false;
  pProducts = &pNumerator->getProducts();
  if (pProducts->size() != 1) return false;
  pProduct = *(pProducts->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  const CNormalItem* pNormalItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pNormalItem == NULL) return false;
  if (pNormalItem->getType() != CNormalItem::VARIABLE) return false;
  if (pNormalItem->getName() != "A") return false;
  return result;
}

//2==T
bool test_normalform::check_LogicalItemC(const CNormalLogicalItem* pLogicalItem)
{
  bool result = true;
  if (pLogicalItem == NULL) return false;
  if (pLogicalItem->getType() != CNormalLogicalItem::EQ) return false;
  const CNormalFraction* pFraction = &pLogicalItem->getLeft();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  const CNormalSum* numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  const std::set<CNormalProduct*, compareProducts >* products = &numerator->getProducts();
  if (products->size() != 1) return false;
  const CNormalProduct* pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 2.0) return false;
  if (pProduct->getItemPowers().size() != 0) return false;

  pFraction = &pLogicalItem->getRight();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  products = &numerator->getProducts();
  if (products->size() != 1) return false;
  pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  const CNormalItem* pNormalItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pNormalItem == NULL) return false;
  if (pNormalItem->getType() != CNormalItem::VARIABLE) return false;
  if (pNormalItem->getName() != "T") return false;
  return result;
}

// D == F
bool test_normalform::check_LogicalItemD(const CNormalLogicalItem* pLogicalItem)
{
  bool result = true;
  if (pLogicalItem == NULL) return false;
  if (pLogicalItem->getType() != CNormalLogicalItem::EQ) return false;
  const CNormalFraction* pFraction = &pLogicalItem->getLeft();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  const CNormalSum* numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  const std::set<CNormalProduct*, compareProducts >* products = &numerator->getProducts();
  if (products->size() != 1) return false;
  const CNormalProduct* pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  const CNormalItem* pNormalItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pNormalItem == NULL) return false;
  if (pNormalItem->getType() != CNormalItem::VARIABLE) return false;
  if (pNormalItem->getName() != "D") return false;

  pFraction = &pLogicalItem->getRight();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  products = &numerator->getProducts();
  if (products->size() != 1) return false;
  pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  pNormalItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pNormalItem == NULL) return false;
  if (pNormalItem->getType() != CNormalItem::VARIABLE) return false;
  if (pNormalItem->getName() != "F") return false;
  return result;
}

// SIN(PI*D) < X
bool test_normalform::check_LogicalItemE(const CNormalLogicalItem* pLogicalItem)
{
  bool result = true;
  if (pLogicalItem == NULL) return false;
  if (pLogicalItem->getType() != CNormalLogicalItem::LT) return false;
  const CNormalFraction* pFraction = &pLogicalItem->getLeft();
  if (pFraction == NULL) return false;
  const CNormalSum* numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  const std::set<CNormalProduct*, compareProducts >* products = &numerator->getProducts();
  if (products->size() != 1) return false;
  const CNormalProduct* pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::FUNCTION) return false;
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  if (pFunction == NULL) return false;
  if (pFunction->getType() != CNormalFunction::SIN) return false;
  pFraction = &pFunction->getFraction();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  products = &numerator->getProducts();
  if (products->size() != 1) return false;
  ProductIterator productsIt = products->begin();
  pProduct = *(productsIt);
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 2) return false;
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator itemPowersIt = pProduct->getItemPowers().begin();
  pItemPower = *(itemPowersIt);
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pItem == NULL) return false;
  if (pItem->getType() != CNormalItem::CONSTANT) return false;
  if (pItem->getName() != "PI") return false;
  ++itemPowersIt;
  pItemPower = *(itemPowersIt);
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pItem == NULL) return false;
  if (pItem->getType() != CNormalItem::VARIABLE) return false;
  if (pItem->getName() != "D") return false;

  pFraction = &pLogicalItem->getRight();
  if (pFraction == NULL) return false;
  numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  products = &numerator->getProducts();
  if (products->size() != 1) return false;
  pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pItem == NULL) return false;
  if (pItem->getType() != CNormalItem::VARIABLE) return false;
  if (pItem->getName() != "X") return false;
  return result;
}

// 2*T^(3*J) != 6.2
bool test_normalform::check_LogicalItemF(const CNormalLogicalItem* pLogicalItem)
{
  bool result = true;
  if (pLogicalItem == NULL) return false;
  if (pLogicalItem->getType() != CNormalLogicalItem::NE) return false;
  const CNormalFraction* pFraction = &pLogicalItem->getLeft();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() == false) return false;
  const CNormalSum* numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  const std::set<CNormalProduct*, compareProducts >* products = &numerator->getProducts();
  if (products->size() != 1) return false;
  const CNormalProduct* pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 2.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  const CNormalItemPower* pItemPower = *pProduct->getItemPowers().begin();
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::POWER) return false;
  const CNormalGeneralPower* pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  if (pGeneralPower == NULL) return false;
  // check this general power which should be (t^(3*J))
  if (pGeneralPower->getType() != CNormalGeneralPower::POWER) return false;
  pFraction = &pGeneralPower->getLeft();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  products = &numerator->getProducts();
  if (products->size() != 1) return false;
  pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pItem == NULL) return false;
  if (pItem->getType() != CNormalItem::VARIABLE) return false;
  if (pItem->getName() != "T") return false;
  pFraction = &pGeneralPower->getRight();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  products = &numerator->getProducts();
  if (products->size() != 1) return false;
  pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 3.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pItem == NULL) return false;
  if (pItem->getType() != CNormalItem::VARIABLE) return false;
  if (pItem->getName() != "J") return false;

  pFraction = &pLogicalItem->getRight();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  products = &numerator->getProducts();
  if (products->size() != 1) return false;
  pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 6.2) return false;
  if (pProduct->getItemPowers().size() != 0) return false;
  return result;
}

// A <= PI
bool test_normalform::check_LogicalItemNotA(const CNormalLogicalItem* pLogicalItem)
{
  bool result = true;
  if (pLogicalItem == NULL) return false;
  if (pLogicalItem->getType() != CNormalLogicalItem::LE) return false;
  const CNormalFraction* pFraction = &pLogicalItem->getLeft();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;

  const CNormalSum* pNumerator = &pFraction->getNumerator();
  if (pNumerator->getFractions().size() != 0) return false;
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  if (pProducts->size() != 1) return false;
  const CNormalProduct* pProduct = *(pProducts->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  const CNormalItem* pNormalItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pNormalItem == NULL) return false;
  if (pNormalItem->getType() != CNormalItem::VARIABLE) return false;
  if (pNormalItem->getName() != "A") return false;

  pFraction = &pLogicalItem->getRight();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;

  pNumerator = &pFraction->getNumerator();
  if (pNumerator->getFractions().size() != 0) return false;
  pProducts = &pNumerator->getProducts();
  if (pProducts->size() != 1) return false;
  pProduct = *(pProducts->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  pNormalItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pNormalItem == NULL) return false;
  if (pNormalItem->getType() != CNormalItem::CONSTANT) return false;
  if (pNormalItem->getName() != "PI") return false;
  return result;
}

// 4 == A
bool test_normalform::check_LogicalItemNotB(const CNormalLogicalItem* pLogicalItem)
{
  bool result = true;
  if (pLogicalItem == NULL) return false;
  if (pLogicalItem->getType() != CNormalLogicalItem::EQ) return false;

  const CNormalFraction* pFraction = &pLogicalItem->getLeft();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  if (pNumerator->getFractions().size() != 0) return false;
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  if (pProducts->size() != 1) return false;
  const CNormalProduct* pProduct = *(pProducts->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 4.0) return false;
  if (pProduct->getItemPowers().size() != 0) return false;

  pFraction = &pLogicalItem->getRight();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  pNumerator = &pFraction->getNumerator();
  if (pNumerator->getFractions().size() != 0) return false;
  pProducts = &pNumerator->getProducts();
  if (pProducts->size() != 1) return false;
  pProduct = *(pProducts->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  const CNormalItem* pNormalItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pNormalItem == NULL) return false;
  if (pNormalItem->getType() != CNormalItem::VARIABLE) return false;
  if (pNormalItem->getName() != "A") return false;
  return result;
}

// 2!=T
bool test_normalform::check_LogicalItemNotC(const CNormalLogicalItem* pLogicalItem)
{
  bool result = true;
  if (pLogicalItem == NULL) return false;
  if (pLogicalItem->getType() != CNormalLogicalItem::NE) return false;
  const CNormalFraction* pFraction = &pLogicalItem->getLeft();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  const CNormalSum* numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  const std::set<CNormalProduct*, compareProducts >* products = &numerator->getProducts();
  if (products->size() != 1) return false;
  const CNormalProduct* pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 2.0) return false;
  if (pProduct->getItemPowers().size() != 0) return false;

  pFraction = &pLogicalItem->getRight();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  products = &numerator->getProducts();
  if (products->size() != 1) return false;
  pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  const CNormalItem* pNormalItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pNormalItem == NULL) return false;
  if (pNormalItem->getType() != CNormalItem::VARIABLE) return false;
  if (pNormalItem->getName() != "T") return false;
  return result;
}

// D != F
bool test_normalform::check_LogicalItemNotD(const CNormalLogicalItem* pLogicalItem)
{
  bool result = true;
  if (pLogicalItem == NULL) return false;
  if (pLogicalItem->getType() != CNormalLogicalItem::NE) return false;
  const CNormalFraction* pFraction = &pLogicalItem->getLeft();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  const CNormalSum* numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  const std::set<CNormalProduct*, compareProducts >* products = &numerator->getProducts();
  if (products->size() != 1) return false;
  const CNormalProduct* pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  const CNormalItem* pNormalItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pNormalItem == NULL) return false;
  if (pNormalItem->getType() != CNormalItem::VARIABLE) return false;
  if (pNormalItem->getName() != "D") return false;

  pFraction = &pLogicalItem->getRight();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  products = &numerator->getProducts();
  if (products->size() != 1) return false;
  pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  pNormalItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pNormalItem == NULL) return false;
  if (pNormalItem->getType() != CNormalItem::VARIABLE) return false;
  if (pNormalItem->getName() != "F") return false;
  return result;
}

// X <= SIN(PI*D)
bool test_normalform::check_LogicalItemNotE(const CNormalLogicalItem* pLogicalItem)
{
  bool result = true;
  if (pLogicalItem == NULL) return false;
  if (pLogicalItem->getType() != CNormalLogicalItem::LE) return false;

  const CNormalFraction* pFraction = &pLogicalItem->getLeft();
  if (pFraction == NULL) return false;
  const CNormalSum* numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  const std::set<CNormalProduct*, compareProducts >* products = &numerator->getProducts();
  if (products->size() != 1) return false;
  const CNormalProduct* pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pItem == NULL) return false;
  if (pItem->getType() != CNormalItem::VARIABLE) return false;
  if (pItem->getName() != "X") return false;

  pFraction = &pLogicalItem->getRight();
  if (pFraction == NULL) return false;
  numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  products = &numerator->getProducts();
  if (products->size() != 1) return false;
  pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::FUNCTION) return false;
  const CNormalFunction* pFunction = dynamic_cast<const CNormalFunction*>(&pItemPower->getItem());
  if (pFunction == NULL) return false;
  if (pFunction->getType() != CNormalFunction::SIN) return false;
  pFraction = &pFunction->getFraction();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  products = &numerator->getProducts();
  if (products->size() != 1) return false;
  ProductIterator productsIt = products->begin();
  pProduct = *(productsIt);
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 2) return false;
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator itemPowersIt = pProduct->getItemPowers().begin();
  pItemPower = *(itemPowersIt);
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pItem == NULL) return false;
  if (pItem->getType() != CNormalItem::CONSTANT) return false;
  if (pItem->getName() != "PI") return false;
  ++itemPowersIt;
  pItemPower = *(itemPowersIt);
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pItem == NULL) return false;
  if (pItem->getType() != CNormalItem::VARIABLE) return false;
  if (pItem->getName() != "D") return false;
  return result;
}

// 2*T^(3*J) == 6.2
bool test_normalform::check_LogicalItemNotF(const CNormalLogicalItem* pLogicalItem)
{
  bool result = true;
  if (pLogicalItem == NULL) return false;
  if (pLogicalItem->getType() != CNormalLogicalItem::EQ) return false;
  const CNormalFraction* pFraction = &pLogicalItem->getLeft();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  const CNormalSum* numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  const std::set<CNormalProduct*, compareProducts >* products = &numerator->getProducts();
  if (products->size() != 1) return false;
  const CNormalProduct* pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 2.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  const CNormalItemPower* pItemPower = *pProduct->getItemPowers().begin();
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::POWER) return false;
  const CNormalGeneralPower* pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  if (pGeneralPower == NULL) return false;
  // check this general power which should be (t^(3*J))
  if (pGeneralPower->getType() != CNormalGeneralPower::POWER) return false;
  pFraction = &pGeneralPower->getLeft();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  products = &numerator->getProducts();
  if (products->size() != 1) return false;
  pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 1.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pItem == NULL) return false;
  if (pItem->getType() != CNormalItem::VARIABLE) return false;
  if (pItem->getName() != "T") return false;
  pFraction = &pGeneralPower->getRight();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  products = &numerator->getProducts();
  if (products->size() != 1) return false;
  pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 3.0) return false;
  if (pProduct->getItemPowers().size() != 1) return false;
  pItemPower = *(pProduct->getItemPowers().begin());
  if (pItemPower == NULL) return false;
  if (pItemPower->getExp() != 1.0) return false;
  if (pItemPower->getItemType() != CNormalItemPower::ITEM) return false;
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  if (pItem == NULL) return false;
  if (pItem->getType() != CNormalItem::VARIABLE) return false;
  if (pItem->getName() != "J") return false;

  pFraction = &pLogicalItem->getRight();
  if (pFraction == NULL) return false;
  if (pFraction->checkDenominatorOne() != true) return false;
  numerator = &pFraction->getNumerator();
  if (numerator->getFractions().size() != 0) return false;
  products = &numerator->getProducts();
  if (products->size() != 1) return false;
  pProduct = *(products->begin());
  if (pProduct == NULL) return false;
  if (pProduct->getFactor() != 6.2) return false;
  if (pProduct->getItemPowers().size() != 0) return false;
  return result;
}

void test_normalform::test_nested_fractions_itempowers_1level()
{
  std::string infix("(A+B)^3/(A+B)^2");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  std::string s = pFraction->toString();
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  CNormalProduct* pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  pProduct = *(++pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
}

void test_normalform::test_nested_fractions_itempower_generalpower_1level()
{
  std::string infix("(A+B)^n/(A+B)^l"); // -> (A+B)^n / (A+B)^l
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  CNormalProduct* pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be ((A+B)^n)
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  const CNormalFraction* pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  pProduct = *(++pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n");
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be ((A+B)^l)
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  pProduct = *(++pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "l");
}

void test_normalform::test_nested_fractions_itempower_generalpower_1level_2()
{
  std::string infix("(A+B)^(n-l)"); // -> (A+B)^n / (A+B)^l
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  CNormalProduct* pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be ((A+B)^n)
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  const CNormalFraction* pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  pProduct = *(++pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n");
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be ((A+B)^l)
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  pProduct = *(++pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "l");
}

void test_normalform::test_nested_fractions_generalpower_itempower_1level()
{
  std::string infix("(A+B)^n/(A+B)^2"); // -> (A+B)^n/(A+B)^2
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  CNormalProduct* pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be ((A+B)^n)
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  const CNormalFraction* pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  pProduct = *(++pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n");
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be ((A+B)^2)
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  pProduct = *(++pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_nested_fractions_generalpowers_1level()
{
  std::string infix("(A+B)^2/(A+B)^l"); // -> (A+B)^2/(A+B)^l
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  // numerator
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  const CNormalProduct* pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be ((A+B)^2)
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  const CNormalFraction* pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  pProduct = *(++pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
  // denominator
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be ((A+B)^l)
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  pProduct = *(++pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "l");
}

void test_normalform::test_nested_fractions_itempowers_2level()
{
  std::string infix("((A+B)/F)^3/((A+B)/F)"); // -> (A+B)^2/F^2
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  CNormalProduct* pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be ((A+B)^2)
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  const CNormalFraction* pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  pProduct = *(++pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
  // denominator
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");
}

void test_normalform::test_nested_fractions_itempower_generalpower_2level()
{
  std::string infix("((A+B)/F)^(n-2)/((A+B)/F)^3"); // -> ((A+B)^n * F^5) / ((A+B)^5 * F^n)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  // numerator
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  CNormalProduct* pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);
  // first product part (F^5)
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 5.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");
  // second product part
  pItemPower = *(++pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be ((A+B)^n)
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  const CNormalFraction* pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  CNormalProduct* pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  pProduct2 = *(++pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n");
  // denominator
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be (F^n)
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n");
  // second product part (A+B)^5
  pItemPower = *(++pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 5.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be ((A+B)^1)
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  pProduct = *(++pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_nested_fractions_generalpower_itempower_2level()
{
  std::string infix("((A+B)/F)^3/((A+B)/F)^(n+3)"); // -> (F^n) / ((A+B)^n)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  // numerator
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  CNormalProduct* pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be (F^n)
  const CNormalFraction* pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n");
  // denominator
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be ((A+B)^n)
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  pProduct = *(++pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n");
}

void test_normalform::test_nested_fractions_generalpowers_2level()
{
  std::string infix("((A+B)/F)^(n-2)/((A+B)/F)^(x+3)"); // ->  (F^5 * F^x * (A+B)^(n)) / (F^n * (A+B)^5 * (A+B)^x)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  std::string s = pFraction->toString();
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  // numerator F^5 * F^x * (A+B)^n
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  CNormalProduct* pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 3);
  // first product part (F^5)
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 5.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");
  // second product part (F^x)
  pItemPower = *(++pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  const CNormalFraction* pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  CNormalProduct* pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "x");
  // third product part (A+B)^n
  pItemPower = *(++(++pProduct->getItemPowers().begin()));
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be ((A+B)^n)
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  pProduct2 = *(++pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n");
  // denominator (F^n * (A+B)^5 * (A+B)^x)
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 3);
  // first product part
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be (F^n)
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n");
  // second product part (A+B)^5
  pItemPower = *(++pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 5.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be ((A+B))
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  pProduct2 = *(++pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  // third product part (A+B)^x
  pItemPower = *(++(++pProduct->getItemPowers().begin()));
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be ((A+B)^x)
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  pProduct2 = *(++pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "x");
}

void test_normalform::test_nested_fractions_itempowers_2level_complex()
{
  std::string infix("(((A*B)+(C*D))/((E*F)+(G*H)))^4/(((A*B)+(C*D))/((E*F)+(G*H)))^5"); // -> ((E*F)+(G*H))/((A*B)+(C*D))
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  // numerator (E*F) + (G*H)
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  CNormalProduct* pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);
  // first summand (E*F)
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");
  pItemPower = *(++pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");
  // second summand (G*H)
  pProduct = *(++pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");
  pItemPower = *(++pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");
  // denominator (A*B)+(C*D)
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);
  // first summand (A*B)
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  pItemPower = *(++pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  // second summand (C*D)
  pProduct = *(++pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");
  pItemPower = *(++pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");
}

void test_normalform::test_nested_fractions_itempower_generalpower_2level_complex()
{
  std::string infix("(((A*B)+(C*D))/((E*F)+(G*H)))^4/(((A*B)+(C*D))/((E*F)+(G*H)))^(n-3)"); // -> (((A*B)+(C*D))^7 * ((E*F)+(G*H))^n) / (((A*B)+(C*D))^n * (((E*F)+(G*H))^7)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  // numerator (((A*B)+(C*D))^7 * ((E*F)+(G*H))^n)
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  // product ((A*B)+(C*D))^7 * ((E*F)+(G*H))^n)
  CNormalProduct* pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);
  // first product item ((A*B)+(C*D))^7
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 7.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  // left side of power ((A*B)+(C*D))
  const CNormalFraction* pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts2 = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts2->size() == 2);
  // first product (A*B)
  const CNormalProduct* pProduct2 = *(pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part A
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  // second product part B
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  // second product (C*D)
  pProduct2 = *(++pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part C
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");
  // second product part D
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");
  // exponent 1
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 0);
  // second product item ((E*F)+(G*H))^n
  pItemPower = *(++pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  // left side of power ((E*F)+(G*H))
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts2 = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts2->size() == 2);
  // first product (E*F)
  pProduct2 = *(pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part E
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");
  // second product part F
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");
  // second product (G*H)
  pProduct2 = *(++pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part G
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");
  // second product part H
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");
  // exponent n
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n");

  // denominator (((A*B)+(C*D))^n * ((E*F)+(G*H))^7)
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  // product ((A*B)+(C*D))^n * ((E*F)+(G*H))^7
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  // left side of power ((A*B)+(C*D))
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts2 = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts2->size() == 2);
  // first product (A*B)
  pProduct2 = *(pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part A
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  // second product part B
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  // second product (C*D)
  pProduct2 = *(++pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part C
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");
  // second product part D
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");
  // exponent n
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n");
  // second product item ((E*F)+(G*H))^7
  pItemPower = *(++pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 7.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  // left side of power ((E*F)+(G*H))
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts2 = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts2->size() == 2);
  // first product (E*F)
  pProduct2 = *(pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part E
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");
  // second product part F
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");
  // second product (G*H)
  pProduct2 = *(++pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part G
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");
  // second product part H
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");
  // exponent 1
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 0);
}

void test_normalform::test_nested_fractions_generalpower_itempower_2level_complex()
{
  std::string infix("(((A*B)+(C*D))/((E*F)+(G*H)))^(n-3)/(((A*B)+(C*D))/((E*F)+(G*H)))^5"); // -> (((A*B)+(C*D))^n*((E*F)+(G*H))^8)/(((A*B)+(C*D))^8*((E*F)+(G*H))^n)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  // numerator (((A*B)+(C*D))^n * ((E*F)+(G*H))^8)
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  // product ((A*B)+(C*D))^n * ((E*F)+(G*H))^8)
  CNormalProduct* pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);
  // first product item ((A*B)+(C*D))^n
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  // left side of power ((A*B)+(C*D))
  const CNormalFraction* pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts2 = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts2->size() == 2);
  // first product (A*B)
  const CNormalProduct* pProduct2 = *(pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part A
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  // second product part B
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  // second product (C*D)
  pProduct2 = *(++pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part C
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");
  // second product part D
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");
  // exponent n
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n");
  // second product item ((E*F)+(G*H))^8
  pItemPower = *(++pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 8.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  // left side of power ((E*F)+(G*H))
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts2 = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts2->size() == 2);
  // first product (E*F)
  pProduct2 = *(pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part E
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");
  // second product part F
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");
  // second product (G*H)
  pProduct2 = *(++pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part G
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");
  // second product part H
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");
  // exponent 1
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 0);

  // denominator (((A*B)+(C*D))^8 * ((E*F)+(G*H))^n)
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  // product ((A*B)+(C*D))^8 * ((E*F)+(G*H))^n
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 8.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  // left side of power ((A*B)+(C*D))
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts2 = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts2->size() == 2);
  // first product (A*B)
  pProduct2 = *(pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part A
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  // second product part B
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  // second product (C*D)
  pProduct2 = *(++pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part C
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");
  // second product part D
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");
  // exponent 1
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 0);
  // second product item ((E*F)+(G*H))^n
  pItemPower = *(++pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  // left side of power ((E*F)+(G*H))
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts2 = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts2->size() == 2);
  // first product (E*F)
  pProduct2 = *(pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part E
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");
  // second product part F
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");
  // second product (G*H)
  pProduct2 = *(++pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part G
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");
  // second product part H
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");
  // exponent n
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n");
}

void test_normalform::test_nested_fractions_generalpowers_2level_complex()
{
  std::string infix("(((A*B)+(C*D))/((E*F)+(G*H)))^(n-3)/(((A*B)+(C*D))/((E*F)+(G*H)))^(x+7)"); // -> (((A*B)+(C*D))^n * ((E*F)+(G*H))^10 * ((E*F)+(G*H))^x)/(((A*B)+(C*D))^10 * ((A*B)+(C*D))^x * ((E*F)+(G*H))^n)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  // numerator (((A*B)+(C*D))^n * ((E*F)+(G*H))^10 * ((E*F)+(G*H))^x)
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  // product ((A*B)+(C*D))^n * ((E*F)+(G*H))^10) * ((E*F)+(G*H))^x)
  CNormalProduct* pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 3);
  // first product item ((A*B)+(C*D))^n
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  // left side of power ((A*B)+(C*D))
  const CNormalFraction* pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts2 = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts2->size() == 2);
  // first product (A*B)
  const CNormalProduct* pProduct2 = *(pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part A
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  // second product part B
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  // second product (C*D)
  pProduct2 = *(++pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part C
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");
  // second product part D
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");
  // exponent n
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n");
  // second product item ((E*F)+(G*H))^10
  pItemPower = *(++pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 10.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  // left side of power ((E*F)+(G*H))
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts2 = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts2->size() == 2);
  // first product (E*F)
  pProduct2 = *(pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part E
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");
  // second product part F
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");
  // second product (G*H)
  pProduct2 = *(++pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part G
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");
  // second product part H
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");
  // exponent 1
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 0);
  // third product item ((E*F)+(G*H))^x
  pItemPower = *(++(++pProduct->getItemPowers().begin()));
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  // left side of power ((E*F)+(G*H))
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts2 = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts2->size() == 2);
  // first product (E*F)
  pProduct2 = *(pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part E
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");
  // second product part F
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");
  // second product (G*H)
  pProduct2 = *(++pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part G
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");
  // second product part H
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");
  // exponent x
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "x");

  // denominator (((A*B)+(C*D))^10 * ((A*B)+(C*D))^x * ((E*F)+(G*H))^n)
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  // product ((A*B)+(C*D))^10 * ((A*B)+(C*D))^x * ((E*F)+(G*H))^n
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 3);
  // first product part ((A*B)+(C*D))^10
  pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 10.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  // left side of power ((A*B)+(C*D))
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts2 = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts2->size() == 2);
  // first product (A*B)
  pProduct2 = *(pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part A
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  // second product part B
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  // second product (C*D)
  pProduct2 = *(++pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part C
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");
  // second product part D
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");
  // exponent 1
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 0);
  // second product part ((A*B)+(C*D))^x
  pItemPower = *(++pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  // left side of power ((A*B)+(C*D))
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts2 = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts2->size() == 2);
  // first product (A*B)
  pProduct2 = *(pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part A
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  // second product part B
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  // second product (C*D)
  pProduct2 = *(++pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part C
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");
  // second product part D
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");
  // exponent x
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "x");
  // third product item ((E*F)+(G*H))^n
  pItemPower = *(++(++pProduct->getItemPowers().begin()));
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  // left side of power ((E*F)+(G*H))
  pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts2 = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts2->size() == 2);
  // first product (E*F)
  pProduct2 = *(pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part E
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");
  // second product part F
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");
  // second product (G*H)
  pProduct2 = *(++pProducts2->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 2);
  // first product part G
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");
  // second product part H
  pItemPower = *(++pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");
  // exponent n
  pFraction2 = &pGeneralPower->getRight();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  pNumerator = &pFraction2->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct2 = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct2 != NULL);
  CPPUNIT_ASSERT(pProduct2->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct2->getItemPowers().size() == 1);
  pItemPower = *(pProduct2->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n");
}

void test_normalform::test_sum_with_nested_fractions_1()
{
  std::string infix("(A+B+(C/D))/(A+B+E)"); // -> ((A*D)+(B*D)+C)/(A*D+B*D+E*D)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  std::string s = pFraction->toString();
  // numerator A*D+B*D+C
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 3);
  ProductIterator productIt = pProducts->begin();
  // first product A*D
  const CNormalProduct* pProduct = (*productIt);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(fabs((pProduct->getFactor() - 1.0) / 1.0) < 1e-12);
  const std::set<CNormalItemPower*, compareItemPowers>* pItemPowers = &pProduct->getItemPowers();
  CPPUNIT_ASSERT(pItemPowers->size() == 2);
  ItemPowerIterator itemPowerIt = pItemPowers->begin();
  // first item A
  const CNormalItemPower* pItemPower = (*itemPowerIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  // second item D
  ++itemPowerIt;
  pItemPower = (*itemPowerIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");
  // second product B*D
  ++productIt;
  pProduct = (*productIt);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(fabs((pProduct->getFactor() - 1.0) / 1.0) < 1e-12);
  pItemPowers = &pProduct->getItemPowers();
  CPPUNIT_ASSERT(pItemPowers->size() == 2);
  itemPowerIt = pItemPowers->begin();
  // first item B
  pItemPower = (*itemPowerIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  // second item D
  ++itemPowerIt;
  pItemPower = (*itemPowerIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");
  // third product C
  ++productIt;
  pProduct = (*productIt);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(fabs((pProduct->getFactor() - 1.0) / 1.0) < 1e-12);
  pItemPowers = &pProduct->getItemPowers();
  CPPUNIT_ASSERT(pItemPowers->size() == 1);
  itemPowerIt = pItemPowers->begin();
  // first item C
  pItemPower = (*itemPowerIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");
  // denominator A*D+B*D+D*E
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 3);
  productIt = pProducts->begin();
  // first product A*D
  pProduct = (*productIt);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(fabs((pProduct->getFactor() - 1.0) / 1.0) < 1e-12);
  pItemPowers = &pProduct->getItemPowers();
  CPPUNIT_ASSERT(pItemPowers->size() == 2);
  itemPowerIt = pItemPowers->begin();
  // first item A
  pItemPower = (*itemPowerIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  // second item D
  ++itemPowerIt;
  pItemPower = (*itemPowerIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");
  // second product B*D
  ++productIt;
  pProduct = (*productIt);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(fabs((pProduct->getFactor() - 1.0) / 1.0) < 1e-12);
  pItemPowers = &pProduct->getItemPowers();
  CPPUNIT_ASSERT(pItemPowers->size() == 2);
  itemPowerIt = pItemPowers->begin();
  // first item B
  pItemPower = (*itemPowerIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  // second item D
  ++itemPowerIt;
  pItemPower = (*itemPowerIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");
  // third product D*E
  ++productIt;
  pProduct = (*productIt);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(fabs((pProduct->getFactor() - 1.0) / 1.0) < 1e-12);
  pItemPowers = &pProduct->getItemPowers();
  CPPUNIT_ASSERT(pItemPowers->size() == 2);
  itemPowerIt = pItemPowers->begin();
  // first item D
  pItemPower = (*itemPowerIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");
  // second item E
  ++itemPowerIt;
  pItemPower = (*itemPowerIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");
}

void test_normalform::test_product_of_sums_1()
{
  std::string infix("((A+B)*(C+D)*E)"); // -> (A*C*E)+(A*D*E)+(B*C*E)+(B*D*E)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  std::string s = pFraction->toString();
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne());
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 4);
  ProductIterator productsIt;
  // first product A*C*E
  productsIt = pProducts->begin();
  const CNormalProduct* pProduct = (*productsIt);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(fabs((pProduct->getFactor() - 1.0) / 1.0) < 1e-12);
  const std::set<CNormalItemPower*, compareItemPowers>* pPowerItems = &pProduct->getItemPowers();
  CPPUNIT_ASSERT(pPowerItems != NULL);
  CPPUNIT_ASSERT(pPowerItems->size() == 3);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator powerItemIt;
  // first item A
  powerItemIt = pPowerItems->begin();
  const CNormalItemPower* pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  // second item C
  ++powerItemIt;
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");
  // third item E
  ++powerItemIt;
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");
  // second product A*D*E
  ++productsIt;
  pProduct = (*productsIt);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(fabs((pProduct->getFactor() - 1.0) / 1.0) < 1e-12);
  pPowerItems = &pProduct->getItemPowers();
  CPPUNIT_ASSERT(pPowerItems != NULL);
  CPPUNIT_ASSERT(pPowerItems->size() == 3);
  // first item A
  powerItemIt = pPowerItems->begin();
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  // second item D
  ++powerItemIt;
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");
  // third item E
  ++powerItemIt;
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");
  // third product B*C*E
  ++productsIt;
  pProduct = (*productsIt);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(fabs((pProduct->getFactor() - 1.0) / 1.0) < 1e-12);
  pPowerItems = &pProduct->getItemPowers();
  CPPUNIT_ASSERT(pPowerItems != NULL);
  CPPUNIT_ASSERT(pPowerItems->size() == 3);
  // first item B
  powerItemIt = pPowerItems->begin();
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  // second item C
  ++powerItemIt;
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");
  // third item E
  ++powerItemIt;
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");
  // fourth product B*D*E
  ++productsIt;
  pProduct = (*productsIt);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(fabs((pProduct->getFactor() - 1.0) / 1.0) < 1e-12);
  pPowerItems = &pProduct->getItemPowers();
  CPPUNIT_ASSERT(pPowerItems != NULL);
  CPPUNIT_ASSERT(pPowerItems->size() == 3);
  // first item B
  powerItemIt = pPowerItems->begin();
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  // second item D
  ++powerItemIt;
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");
  // third item E
  ++powerItemIt;
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");
}

void test_normalform::test_product_of_sums_2()
{
  std::string infix("((A+B)*(C-D)*E)"); // -> (A*C*E) + -1.0*(A*D*E) + (B*C*E) + -1.0*(B*D*E)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  std::string s = pFraction->toString();
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne());
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 4);
  ProductIterator productsIt;
  // first product A*C*E
  productsIt = pProducts->begin();
  const CNormalProduct* pProduct = (*productsIt);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(fabs((pProduct->getFactor() - 1.0) / 1.0) < 1e-12);
  const std::set<CNormalItemPower*, compareItemPowers>* pPowerItems = &pProduct->getItemPowers();
  CPPUNIT_ASSERT(pPowerItems != NULL);
  CPPUNIT_ASSERT(pPowerItems->size() == 3);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator powerItemIt;
  // first item A
  powerItemIt = pPowerItems->begin();
  const CNormalItemPower* pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  // second item C
  ++powerItemIt;
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");
  // third item E
  ++powerItemIt;
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");
  // second product -1.0*A*D*E
  ++productsIt;
  pProduct = (*productsIt);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(fabs((pProduct->getFactor() + 1.0) / -1.0) < 1e-12);
  pPowerItems = &pProduct->getItemPowers();
  CPPUNIT_ASSERT(pPowerItems != NULL);
  CPPUNIT_ASSERT(pPowerItems->size() == 3);
  // first item A
  powerItemIt = pPowerItems->begin();
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "A");
  // second item D
  ++powerItemIt;
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");
  // third item E
  ++powerItemIt;
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");
  // third product B*C*E
  ++productsIt;
  pProduct = (*productsIt);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(fabs((pProduct->getFactor() - 1.0) / 1.0) < 1e-12);
  pPowerItems = &pProduct->getItemPowers();
  CPPUNIT_ASSERT(pPowerItems != NULL);
  CPPUNIT_ASSERT(pPowerItems->size() == 3);
  // first item B
  powerItemIt = pPowerItems->begin();
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  // second item C
  ++powerItemIt;
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");
  // third item E
  ++powerItemIt;
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");
  // fourth product -1.0*B*D*E
  ++productsIt;
  pProduct = (*productsIt);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(fabs((pProduct->getFactor() + 1.0) / -1.0) < 1e-12);
  pPowerItems = &pProduct->getItemPowers();
  CPPUNIT_ASSERT(pPowerItems != NULL);
  CPPUNIT_ASSERT(pPowerItems->size() == 3);
  // first item B
  powerItemIt = pPowerItems->begin();
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  // second item D
  ++powerItemIt;
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");
  // third item E
  ++powerItemIt;
  pItemPower = (*powerItemIt);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(fabs((pItemPower->getExp() - 1.0) / 1.0) < 1e-12);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");
}
