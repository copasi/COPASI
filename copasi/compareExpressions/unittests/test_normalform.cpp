// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_normalform.cpp,v $
//   $Revision: 1.19 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/05/06 11:58:13 $
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
  std::string infix("IF(IF(IF(A gt PI,FALSE,4.0 ne A),IF(2 eq T,FALSE,NOT (D eq F)),IF(SIN(D*PI) lt X,TRUE,2*T^(3*J) ne 6.2)),A/TAN(X)^R,SIN(PI)/A^6)");
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
  CPPUNIT_ASSERT(pLogical->getAndSets().size() == 40);

  // 40 sets
  CNormalLogical::ItemSetOfSets::const_iterator outerIt = pLogical->getAndSets().begin();
  CPPUNIT_ASSERT(outerIt->second == false);
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
  std::set<CNormalProduct*, compareProducts>::const_iterator productsIt = products->begin();
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
  std::set<CNormalProduct*, compareProducts>::const_iterator productsIt = products->begin();
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
  std::string s = pFraction->toString();
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
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
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
  CPPUNIT_ASSERT(pProduct->getFactor() == 2.0);
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
  // denominator
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts>* pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  const CNormalProduct* pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::POWER);
  const CNormalGeneralPower* pGeneralPower = dynamic_cast<const CNormalGeneralPower*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pGeneralPower != NULL);
  // check this general power which should be ((A+B)^l)
  CPPUNIT_ASSERT(pGeneralPower->getType() == CNormalGeneralPower::POWER);
  const CNormalFraction* pFraction2 = &pGeneralPower->getLeft();
  CPPUNIT_ASSERT(pFraction2 != NULL);
  CPPUNIT_ASSERT(pFraction2->checkDenominatorOne() == true);
  const CNormalSum* pNumerator = &pFraction2->getNumerator();
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
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
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
  CPPUNIT_ASSERT(pProduct->getFactor() == 2.0);
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
  std::string infix("((A+B)/F)^(n-2)/((A+B)/F)^3"); // -> ((A+B)/F)^n/((A+B)/F)^5 I don't know if the current code gets rid of the double fraction
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(false);
}

void test_normalform::test_nested_fractions_generalpower_itempower_2level()
{
  std::string infix("((A+B)/F)^3/((A+B)/F)^(n+3)"); // -> 1/((A+B)/F)^n
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(false);
}

void test_normalform::test_nested_fractions_generalpowers_2level()
{
  std::string infix("((A+B)/F)^(n-2)/((A+B)/F)^(x+3)"); // -> ((A+B)/F)^n/(((A+B)/F)^x*((A+B)/F)^5)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(false);
}

void test_normalform::test_nested_fractions_itempowers_2level_complex()
{
  std::string infix("(((A*B)+(C*D))/((E*F)+(G*H)))^4/(((A*B)+(C*D))/((E*F)+(G*H)))^5"); // -> 1/(((A*B)+(C*D))/((E*F)+(G*H)))
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(false);
}

void test_normalform::test_nested_fractions_itempower_generalpower_2level_complex()
{
  std::string infix("(((A*B)+(C*D))/((E*F)+(G*H)))^4/(((A*B)+(C*D))/((E*F)+(G*H)))^(n-3)"); // -> (((A*B)+(C*D))/((E*F)+(G*H)))/(((A*B)+(C*D))/((E*F)+(G*H)))^n
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(false);
}

void test_normalform::test_nested_fractions_generalpower_itempower_2level_complex()
{
  std::string infix("(((A*B)+(C*D))/((E*F)+(G*H)))^(n-3)/(((A*B)+(C*D))/((E*F)+(G*H)))^5"); // -> (((A*B)+(C*D))/((E*F)+(G*H)))^n/(((A*B)+(C*D))/((E*F)+(G*H)))^8
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(false);
}

void test_normalform::test_nested_fractions_generalpowers_2level_complex()
{
  std::string infix("(((A*B)+(C*D))/((E*F)+(G*H)))^(n-3)/(((A*B)+(C*D))/((E*F)+(G*H)))^(x+7)"); // -> (((A*B)+(C*D))/((E*F)+(G*H)))^n/((((A*B)+(C*D))/((E*F)+(G*H)))^x*(((A*B)+(C*D))/((E*F)+(G*H)))^10)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(false);
}
