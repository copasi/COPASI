// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_normalform.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/08/09 15:35:08 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "test_normalform.hpp"

#include <string>
#include <set>

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

void test_normalform::setUp(){}

void test_normalform::tearDown(){}

void test_normalform::test_item_number()
{
  std::string infix("7.0");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  std::set<CNormalProduct*, compareProducts >::iterator it = products.begin();
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

  const CNormalSum& numerator = pFraction->getNumerator();
  CPPUNIT_ASSERT(numerator.getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >& products = numerator.getProducts();
  CPPUNIT_ASSERT(products.size() == 1);
  const CNormalProduct* pProduct = *(products.begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == (7.0 / 3.0));
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);
}

void test_normalform::test_fraction_variables()
{
  std::string infix("A/B");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  std::set<CNormalProduct*, compareProducts>::const_iterator it = products2.begin();
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  std::set<CNormalProduct*, compareProducts>::const_iterator it = products2.begin();
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
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
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
}

void test_normalform::test_simple_stepwise_fractions()
{
  std::string infix("IF(TRUE,A/TAN(X)^R,SIN(PI)/A^6)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
}

void test_normalform::test_simple_nested_stepwise_numbers()
{
  std::string infix("IF(IF(IF(TRUE,FALSE,TRUE),IF(FALSE,TRUE,FALSE),IF(FALSE,FALSE,FALSE)),2.3,4.5)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
}

void test_normalform::test_simple_nested_stepwise_fractions()
{
  std::string infix("IF(IF(IF(TRUE,FALSE,TRUE),IF(FALSE,TRUE,FALSE),IF(FALSE,FALSE,FALSE)),A/TAN(X)^R,SIN(PI)/A^6)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
}

void test_normalform::test_nested_stepwise_fractions()
{
  std::string infix("IF(IF(IF(A gt PI,FALSE,4.0 ne A),IF(2 eq T,FALSE,D eq F),IF(SIN(D*PI) lt X,TRUE,2*T^(3*J) ne 6.2)),A/TAN(X)^R,SIN(PI)/A^6)");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
}
