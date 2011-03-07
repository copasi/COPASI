// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_biomodels217_expression.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:26:44 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "test_biomodels217_expression.h"

#include <string>

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
#include "report/CCopasiRootContainer.h"


const char* test_biomodels217_expression::factor_num = "P*A";
const char* test_biomodels217_expression::term_num1 = "f1*B/J";
const char* test_biomodels217_expression::term_num2 = "3*e1*C*O/(D*L*(1+3*C/D+3*C^2/(D*F)+C^3/(D*F*H)))";
const char* test_biomodels217_expression::term_num3 = "3*h1*C*B*O/(D*J*L*(1+3*C/D+3*C^2/(D*F)+C^3/(D*F*H)))";
const char* test_biomodels217_expression::term_num4 = "g1*C^3*N/(E*G*I*M*(1+3*C/E+3*C^2/(E*G)+C^3/(E*G*I)))";
const char* test_biomodels217_expression::term_num5 = "j1*C^3*B*N/(E*G*I*J*M*(1+3*C/E+3*C^2/(E*G)+C^3/(E*G*I)))";
const char* test_biomodels217_expression::term_num6 = "3*i1*C^4*O*N/(D*E*G*I*L*M*(1+3*C/D+3*C^2/(D*F)+C^3/(D*F*H))*(1+3*C/E+3*C^2/(E*G)+C^3/(E*G*I)))";
const char* test_biomodels217_expression::term_num7 = "3*k1*C^4*B*O*N/(D*E*G*I*J*L*M*(1+3*C/D+3*C^2/(D*F)+C^3/(D*F*H))*(1+3*C/E+3*C^2/(E*G)+C^3/(E*G*I)))";

const char* test_biomodels217_expression::factor_den = "K+A";
const char* test_biomodels217_expression::term_den1 = "1+B/J";
const char* test_biomodels217_expression::term_den2 = "3*C*O/(D*L*(1+3*C/D+3*C^2/(D*F)+C^3/(D*F*H)))";
const char* test_biomodels217_expression::term_den3 = "3*C*B*O/(D*J*L*(1+3*C/D+3*C^2/(D*F)+C^3/(D*F*H))*l1)";
const char* test_biomodels217_expression::term_den4 = "C^3*N/(E*G*I*M*(1+3*C/E+3*C^2/(E*G)+C^3/(E*G*I)))";
const char* test_biomodels217_expression::term_den5 = "C^3*B*N/(E*G*I*J*M*(1+3*C/E+3*C^2/(E*G)+C^3/(E*G*I))*n1)";
const char* test_biomodels217_expression::term_den6 = "3*C^4*O*N/(D*E*G*I*L*M*(1+3*C/D+3*C^2/(D*F)+C^3/(D*F*H))*(1+3*C/E+3*C^2/(E*G)+C^3/(E*G*I))*m1)";
const char* test_biomodels217_expression::term_den7 = "3*C^4*B*O*N/(D*E*G*I*J*L*M*(1+3*C/D+3*C^2/(D*F)+C^3/(D*F*H))*(1+3*C/E+3*C^2/(E*G)+C^3/(E*G*I))*o1)";



void test_biomodels217_expression::setUp()
{
  CCopasiRootContainer::init(false, 0, NULL);
}

void test_biomodels217_expression::tearDown()
{
  CCopasiRootContainer::destroy();
}


//----------- denominator ------------------

void test_biomodels217_expression::test_term_num1()
{
  // f1*B/J -> (B*f1)/J
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(term_num1);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  const CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  std::string s = pFraction->toString();
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  // numerator B*f1
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = pProducts->begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  // B
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");
  ++it2;
  // f1
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "f1");

  // denominator
  // J
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  it = pProducts->begin();
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  delete pFraction;
}


void test_biomodels217_expression::test_term_num2()
{
  // 3*e1*C*O/(D*L*(1+3*C/D+3*C^2/(D*F)+C^3/(D*F*H)))
  // -> (3*C*F*H*O*e1)/(3*C*F*H*L + 3*C^2*H*L + C^3*L + D*F*H*L)

  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(term_num2);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  const CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  // numerator
  // (3*C*F*H*O*e1)
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = pProducts->begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 5);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  // C
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  ++it2;
  // F
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  ++it2;
  // H
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  ++it2;
  // O
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "O");

  ++it2;
  // e1
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "e1");


  // denominator
  // (3*C*F*H*L + 3*C^2*H*L + C^3*L + D*F*H*L)
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 4);
  // 3*C*F*H*L
  it = pProducts->begin();
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);


  // C
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // 3*C^2*H*L
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 3);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");


  // C^3*L
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // D*F*H*L
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);

  // D
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  delete pFraction;
}


void test_biomodels217_expression::test_term_num3()
{
  // 3*h1*C*B*O/(D*J*L*(1+3*C/D+3*C^2/(D*F)+C^3/(D*F*H)))
  // -> (3*B*C*F*H*O*h1)/(3*C*F*H*J*L + 3*C^2*H*J*L + C^3*J*L + D*F*H*J*L)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(term_num3);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  const CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  // numerator
  // (3*B*C*F*H*O*h1)
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = pProducts->begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 6);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  // B
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");

  ++it2;
  // C
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  ++it2;
  // F
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  ++it2;
  // H
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  ++it2;
  // O
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "O");

  ++it2;
  // h1
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "h1");


  // denominator
  // (3*C*F*H*J*L + 3*C^2*H*J*L + C^3*J*L + D*F*H*J*L)
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 4);
  // 3*C*F*H*J*L
  it = pProducts->begin();
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 5);


  // C
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // 3*C^2*H*J*L
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // C^3*J*L
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 3);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // D*F*H*J*L
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 5);

  // D
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");


  delete pFraction;
}

void test_biomodels217_expression::test_term_num4()
{
  // g1*C^3*N/(E*G*I*M*(1+3*C/E+3*C^2/(E*G)+C^3/(E*G*I)))
  // -> (C^3*N*g1)/(3*C*G*I*M + 3*C^2*I*M + C^3*M + E*G*I*M)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(term_num4);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  const CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  // numerator
  // (C^3*N*g1)
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = pProducts->begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 3);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  // C^3
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  ++it2;
  // N
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "N");

  ++it2;
  // g1
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "g1");


  // denominator
  // (3*C*G*I*M + 3*C^2*I*M + C^3*M + E*G*I*M)
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 4);
  // 3*C*G*I*M
  it = pProducts->begin();
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);


  // C
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 3*C^2*I*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 3);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");


  // C^3*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // E*G*I*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);

  // E
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  delete pFraction;
}

void test_biomodels217_expression::test_term_num5()
{
  // j1*C^3*B*N/(E*G*I*J*M*(1+3*C/E+3*C^2/(E*G)+C^3/(E*G*I)))
  // -> (B*C^3*N*j1)/(3*C*G*I*J*M + 3*C^2*I*J*M + C^3*J*M + E*G*I*J*M)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(term_num5);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  const CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  // numerator
  // (B*C^3*N*j1)
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = pProducts->begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  // B
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");

  ++it2;
  // C^3
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  ++it2;
  // N
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "N");

  ++it2;
  // j1
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "j1");


  // denominator
  // (3*C*G*I*J*M + 3*C^2*I*J*M + C^3*J*M + E*G*I*J*M)
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 4);
  // 3*C*G*I*J*M
  it = pProducts->begin();
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 5);


  // C
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 3*C^2*I*J*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");


  // C^3*J*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 3);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // E*G*I*J*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 5);

  // E
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  delete pFraction;
}


void test_biomodels217_expression::test_term_num6()
{
  // 3*i1*C^4*O*N/(D*E*G*I*L*M*(1+3*C/D+3*C^2/(D*F)+C^3/(D*F*H))*(1+3*C/E+3*C^2/(E*G)+C^3/(E*G*I)))
  // -> (3*C^4*F*H*N*O*i1)/(3*C*D*F*G*H*I*L*M + 3*C^2*D*F*H*I*L*M + C^3*D*F*H*L*M + 3*C*E*F*G*H*I*L*M + 3*C^2*E*G*H*I*L*M + C^3*E*G*I*L*M + 9*C^2*F*G*H*I*L*M + 9*C^3*F*H*I*L*M + 3*C^4*F*H*L*M + 9*C^3*G*H*I*L*M + 3*C^4*G*I*L*M + 9*C^4*H*I*L*M + 3*C^5*H*L*M + 3*C^5*I*L*M + C^6*L*M + D*E*F*G*H*I*L*M)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(term_num6);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  const CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  // numerator
  // (3*C^4*F*H*N*O*i1)
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = pProducts->begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 6);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  // C^4
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 4.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  ++it2;
  // F
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  ++it2;
  // H
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  ++it2;
  // N
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "N");

  ++it2;
  // O
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "O");

  ++it2;
  // i1
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "i1");


  // denominator
  // (3*C*D*F*G*H*I*L*M + 3*C^2*D*F*H*I*L*M + C^3*D*F*H*L*M + 3*C*E*F*G*H*I*L*M + 3*C^2*E*G*H*I*L*M + C^3*E*G*I*L*M + 9*C^2*F*G*H*I*L*M + 9*C^3*F*H*I*L*M + 3*C^4*F*H*L*M + 9*C^3*G*H*I*L*M + 3*C^4*G*I*L*M + 9*C^4*H*I*L*M + 3*C^5*H*L*M + 3*C^5*I*L*M + C^6*L*M + D*E*F*G*H*I*L*M)
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 16);
  // 3*C*D*F*G*H*I*L*M
  it = pProducts->begin();
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 8);


  // C
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // D
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 3*C^2*D*F*H*I*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 7);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // D
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");


  // C^3*D*F*H*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 6);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // D
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 3*C*E*F*G*H*I*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 8);

  // C
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // E
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 3*C^2*E*G*H*I*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 7);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // E
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // C^3*E*G*I*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 6);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // E
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");


  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 9*C^2*F*G*H*I*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 9.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 7);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 9*C^3*F*H*I*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 9.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 6);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");


  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 3*C^4*F*H*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 5);

  // C^4
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 4.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 9*C^3*G*H*I*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 9.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 6);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 3*C^4*G*I*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 5);

  // C^4
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 4.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 9*C^4*H*I*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 9.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 5);

  // C^4
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 4.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 3*C^5*H*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);

  // C^5
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 5.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 3*C^5*I*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);

  // C^5
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 5.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // C^6*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 3);

  // C^6
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 6.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // D*E*F*G*H*I*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 8);

  // D
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // E
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  delete pFraction;
}


void test_biomodels217_expression::test_term_num7()
{
  // 3*k1*C^4*B*O*N/(D*E*G*I*J*L*M*(1+3*C/D+3*C^2/(D*F)+C^3/(D*F*H))*(1+3*C/E+3*C^2/(E*G)+C^3/(E*G*I)))
  // -> (3*B*C^4*F*N*O*k1)/(C^3*D*E*F*G*I*J*L*M + 3*C^4*D*F*G*I*J*L*M + 3*C^5*D*F*I*J*L*M + C^6*D*F*J*L*M + 3*C*E*F*G*I*J*L*M + 3*C^2*E*G*I*J*L*M + 9*C^2*F*G*I*J*L*M + 9*C^3*F*I*J*L*M + 3*C^4*F*J*L*M + 9*C^3*G*I*J*L*M + 9*C^4*I*J*L*M + 3*C^5*J*L*M)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(term_num7);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  const CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  // numerator
  // (3*B*C^4*F*N*O*k1)
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = pProducts->begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 6);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  // B
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");

  ++it2;
  // C^4
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 4.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  ++it2;
  // F
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  ++it2;
  // N
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "N");

  ++it2;
  // O
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "O");

  ++it2;
  // k1
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "k1");


  // denominator
  // (C^3*D*E*F*G*I*J*L*M + 3*C^4*D*F*G*I*J*L*M + 3*C^5*D*F*I*J*L*M + C^6*D*F*J*L*M + 3*C*E*F*G*I*J*L*M + 3*C^2*E*G*I*J*L*M + 9*C^2*F*G*I*J*L*M + 9*C^3*F*I*J*L*M + 3*C^4*F*J*L*M + 9*C^3*G*I*J*L*M + 9*C^4*I*J*L*M + 3*C^5*J*L*M)
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 12);

  // C^3*D*E*F*G*I*J*L*M
  it = pProducts->begin();
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 9);


  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // D
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // E
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 3*C^4*D*F*G*I*J*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 8);

  // C^4
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 4.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // D
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");


  // 3*C^5*D*F*I*J*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 7);

  // C^5
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 5.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // D
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // C^6*D*F*J*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 6);

  // C
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 6.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // D
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 3*C*E*F*G*I*J*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 8);

  // C
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // E
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 3*C^2*E*G*I*J*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 7);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // E
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 9*C^2*F*G*I*J*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 9.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 7);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 9*C^3*F*I*J*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 9.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 6);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");


  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 3*C^4*F*J*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 5);

  // C^4
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 4.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 9*C^3*G*I*J*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 9.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 6);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 9*C^4*I*J*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 9.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 5);

  // C^4
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 4.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 3*C^5*J*L*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 2.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);

  // C^5
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 5.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  delete pFraction;
}


//----------- denominator ------------------

void test_biomodels217_expression::test_term_den1()
{
  // 1+B/J -> (B+J)/J
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(term_den1);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  const CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  // numerator
  // B+J
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 2);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = pProducts->begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  // B
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");

  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  it2 = pProduct->getItemPowers().begin();
  // J
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // denominator
  // J
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  it = pProducts->begin();
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  delete pFraction;
}


void test_biomodels217_expression::test_term_den2()
{
  // 3*C*O/(D*L*(1+3*C/D+3*C^2/(D*F)+C^3/(D*F*H)))
  // -> (2*C*F*H*O)/(3*C*F*H*L + 3*C^2*H*L + C^3*L + D*F*H*L)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(term_den2);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  const CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  // numerator
  // (2*C*F*H*O)
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = pProducts->begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 2.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  // C
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  ++it2;
  // F
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  ++it2;
  // H
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  ++it2;
  // O
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "O");


  // denominator
  // (3*C*F*H*L + 3*C^2*H*L + C^3*L + D*F*H*L)
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 4);
  // 3*C*F*H*L
  it = pProducts->begin();
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);


  // C
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // 3*C^2*H*L
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 3);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");


  // C^3*L
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // D*F*H*L
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);

  // D
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");


  delete pFraction;
}


void test_biomodels217_expression::test_term_den3()
{
  // 3*C*B*O/(D*J*L*(1+3*C/D+3*C^2/(D*F)+C^3/(D*F*H))*l1)
  // -> (3*B*C*F*H*O)/(3*C*F*H*J*L*l1 + 3*C^2*H*J*L*l1 + C^3*J*L*l1 + D*F*H*J*L*l1)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(term_den3);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  const CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);


  // numerator
  // (3*B*C*F*H*O)
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = pProducts->begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 5);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  // B
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");

  ++it2;
  // C
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  ++it2;
  // F
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  ++it2;
  // H
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  ++it2;
  // O
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "O");


  // denominator
  // (3*C*F*H*J*L*l1 + 3*C^2*H*J*L*l1 + C^3*J*L*l1 + D*F*H*J*L*l1)
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 4);
  // 3*C*F*H*J*L*l1
  it = pProducts->begin();
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 5);


  // C
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // l1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "l1");

  // 3*C^2*H*J*L*l1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // l1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "l1");

  // C^3*J*L*l1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 3);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // l1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "l1");

  // D*F*H*J*L*l1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 5);

  // D
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // l1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "l1");

  delete pFraction;
}


void test_biomodels217_expression::test_term_den4()
{
  // C^3*N/(E*G*I*M*(1+3*C/E+3*C^2/(E*G)+C^3/(E*G*I)))
  // -> (C^3*N)/(3*C*G*I*M + 3*C^2*I*M + C^3*M + E*G*I*M)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(term_den4);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  const CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  // numerator
  // (C^3*N)
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = pProducts->begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  // C^3
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  ++it2;
  // N
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "N");

  // denominator
  // (3*C*G*I*M + 3*C^2*I*M + C^3*M + E*G*I*M)
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 4);
  // 3*C*G*I*M
  it = pProducts->begin();
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);


  // C
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // 3*C^2*I*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 3);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");


  // C^3*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 2);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // E*G*I*M
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);

  // E
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");


  delete pFraction;
}


void test_biomodels217_expression::test_term_den5()
{
  // C^3*B*N/(E*G*I*J*M*(1+3*C/E+3*C^2/(E*G)+C^3/(E*G*I))*n1)
  // -> (B*C^3*N)/(3*C*G*I*J*M*n1 + 3*C^2*I*J*M*n1 + C^3*J*M*n1 + E*G*I*J*M*n1)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(term_den5);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  const CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  // numerator
  // (B*C^3*N)
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = pProducts->begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  // B
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");

  ++it2;
  // C^3
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  ++it2;
  // N
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "N");


  // denominator
  // (3*C*G*I*J*M*n1 + 3*C^2*I*J*M*n1 + C^3*J*M*n1 + E*G*I*J*M*n1)
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 4);
  // 3*C*G*I*J*M*n1
  it = pProducts->begin();
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 6);

  // C
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // n1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n1");

  // 3*C^2*I*J*M*n1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 5);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // n1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n1");

  // C^3*J*M*n1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // n1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n1");

  // E*G*I*J*M*n1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 6);

  // E
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // n1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "n1");


  delete pFraction;
}


void test_biomodels217_expression::test_term_den6()
{
  // 3*C^4*O*N/(D*E*G*I*L*M*(1+3*C/D+3*C^2/(D*F)+C^3/(D*F*H))*(1+3*C/E+3*C^2/(E*G)+C^3/(E*G*I))*m1)
  // -> (3*C^4*F*H*N*O)/(3*C*D*F*G*H*I*L*M*m1 + 3*C^2*D*F*H*I*L*M*m1 + C^3*D*F*H*L*M*m1 + 3*C*E*F*G*H*I*L*M*m1 + 3*C^2*E*G*H*I*L*M*m1 + C^3*E*G*I*L*M*m1 + 9*C^2*F*G*H*I*L*M*m1 + 9*C^3*F*H*I*L*M*m1 + 3*C^4*F*H*L*M*m1 + 9*C^3*G*H*I*L*M*m1 + 3*C^4*G*I*L*M*m1 + 9*C^4*H*I*L*M*m1 + 3*C^5*H*L*M*m1 + 3*C^5*I*L*M*m1 + C^6*L*M*m1 + D*E*F*G*H*I*L*M*m1)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(term_den6);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  const CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  // numerator
  // (3*C^4*F*H*N*O)
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = pProducts->begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 5);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  // C^4
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 4.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  ++it2;
  // F
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  ++it2;
  // H
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  ++it2;
  // N
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "N");

  ++it2;
  // O
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "O");


  // denominator
  // (3*C*D*F*G*H*I*L*M*m1 + 3*C^2*D*F*H*I*L*M*m1 + C^3*D*F*H*L*M*m1 + 3*C*E*F*G*H*I*L*M*m1 + 3*C^2*E*G*H*I*L*M*m1 + C^3*E*G*I*L*M*m1 + 9*C^2*F*G*H*I*L*M*m1 + 9*C^3*F*H*I*L*M*m1 + 3*C^4*F*H*L*M*m1 + 9*C^3*G*H*I*L*M*m1 + 3*C^4*G*I*L*M*m1 + 9*C^4*H*I*L*M*m1 + 3*C^5*H*L*M*m1 + 3*C^5*I*L*M*m1 + C^6*L*M*m1 + D*E*F*G*H*I*L*M*m1)
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 16);
  // 3*C*D*F*G*H*I*L*M*m1
  it = pProducts->begin();
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 9);


  // C
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // D
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // m1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "m1");

  // 3*C^2*D*F*H*I*L*M*m1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 8);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // D
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // m1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "m1");


  // C^3*D*F*H*L*M*m1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 7);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // D
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // m1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "m1");

  // 3*C*E*F*G*H*I*L*M*m1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 9);

  // C
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // E
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // m1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "m1");

  // 3*C^2*E*G*H*I*L*M*m1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 8);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // E
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // m1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "m1");

  // C^3*E*G*I*L*M*m1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 7);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // E
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");


  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // m1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "m1");

  // 9*C^2*F*G*H*I*L*M*m1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 9.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 8);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // m1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "m1");

  // 9*C^3*F*H*I*L*M*m1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 9.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 7);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");


  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // m1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "m1");

  // 3*C^4*F*H*L*M*m1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 6);

  // C^4
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 4.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // m1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "m1");

  // 9*C^3*G*H*I*L*M*m1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 9.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 7);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // m1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "m1");

  // 3*C^4*G*I*L*M*m1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 6);

  // C^4
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 4.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // m1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "m1");

  // 9*C^4*H*I*L*M*m1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 9.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 6);

  // C^4
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 4.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // m1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "m1");

  // 3*C^5*H*L*M*m1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 5);

  // C^5
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 5.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // m1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "m1");

  // 3*C^5*I*L*M*m1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 5);

  // C^5
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 5.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // m1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "m1");

  // C^6*L*M*m1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 4);

  // C^6
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 6.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // m1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "m1");

  // D*E*F*G*H*I*L*M*m1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 9);

  // D
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // E
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // m1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "m1");

  delete pFraction;
}

// --------------- unfinished ----------------------

void test_biomodels217_expression::test_term_den7()
{
  // 3*C^4*B*O*N/(D*E*G*I*J*L*M*(1+3*C/D+3*C^2/(D*F)+C^3/(D*F*H))*(1+3*C/E+3*C^2/(E*G)+C^3/(E*G*I))*o1)
  // -> (3*B*C^4*F*H*N*O)/(3*C*D*F*G*H*I*J*L*M*o1 + 3*C^2*D*F*H*I*J*L*M*o1 + C^3*D*F*H*J*L*M*o1 + 3*C*E*F*G*H*I*J*L*M*o1 + 3*C^2*E*G*H*I*J*L*M*o1 + C^3*E*G*I*J*L*M*o1 + 9*C^2*F*G*H*I*J*L*M*o1 + 9*C^3*F*H*I*J*L*M*o1 + 3*C^4*F*H*J*L*M*o1 + 9*C^3*G*H*I*J*L*M*o1 + 3*C^4*G*I*J*L*M*o1 + 9*C^4*H*I*J*L*M*o1 + 3*C^5*H*J*L*M*o1 + 3*C^5*I*J*L*M*o1 + C^6*J*L*M*o1 + D*E*F*G*H*I*J*L*M*o1)
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(term_den7);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  const CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  delete pTree;
  CPPUNIT_ASSERT(pFraction != NULL);

  // numerator
  // (3*B*C^4*F*H*N*O)
  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  std::set<CNormalProduct*, compareProducts >::const_iterator it = pProducts->begin();
  const CNormalProduct* pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 6);
  std::set<CNormalItemPower*, compareItemPowers>::const_iterator it2 = pProduct->getItemPowers().begin();
  // B
  const CNormalItemPower* pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "B");

  ++it2;
  // C^4
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 4.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  ++it2;
  // F
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  ++it2;
  // H
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  ++it2;
  // N
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "N");

  ++it2;
  // O
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "O");


  // denominator
  // (3*C*D*F*G*H*I*J*L*M*o1 + 3*C^2*D*F*H*I*J*L*M*o1 + C^3*D*F*H*J*L*M*o1 + 3*C*E*F*G*H*I*J*L*M*o1 + 3*C^2*E*G*H*I*J*L*M*o1 + C^3*E*G*I*J*L*M*o1 + 9*C^2*F*G*H*I*J*L*M*o1 + 9*C^3*F*H*I*J*L*M*o1 + 3*C^4*F*H*J*L*M*o1 + 9*C^3*G*H*I*J*L*M*o1 + 3*C^4*G*I*J*L*M*o1 + 9*C^4*H*I*J*L*M*o1 + 3*C^5*H*J*L*M*o1 + 3*C^5*I*J*L*M*o1 + C^6*J*L*M*o1 + D*E*F*G*H*I*J*L*M*o1)
  const CNormalSum* pDenominator = &pFraction->getDenominator();
  CPPUNIT_ASSERT(pDenominator->getFractions().size() == 0);
  pProducts = &pDenominator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 12);

  // 3*C*D*F*G*H*I*J*L*M*o1
  it = pProducts->begin();
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 10);


  // C
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // D
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // o1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "o1");

  // 3*C^2*D*F*H*I*J*L*M*o1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 9);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // D
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // o1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "o1");


  // C^3*D*F*H*J*L*M*o1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 8);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // D
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // o1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "o1");

  // 3*C*E*F*G*H*I*J*L*M*o1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 10);

  // C
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 6.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // E
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // o1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "o1");

  // 3*C^2*E*G*H*I*J*L*M*o1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 9);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // E
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // o1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "o1");

  // C^3*E*G*I*J*L*M*o1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 8);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // E
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // o1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "o1");

  // 9*C^2*F*G*H*I*J*L*M*o1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 9.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 9);

  // C^2
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 2.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // o1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "o1");

  // 9*C^3*F*H*I*J*L*M*o1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 9.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 8);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");


  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // o1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "o1");

  // 3*C^4*F*H*J*L*M*o1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 7);

  // C^4
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 4.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // o1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "o1");

  // 9*C^3*G*H*I*J*L*M*o1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 9.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 8);

  // C^3
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 3.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // o1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "o1");

  // 3*C^4*G*I*J*L*M*o1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 7);

  // C^4
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 4.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // o1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "o1");

  // 9*C^4*H*I*J*L*M*o1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 9.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 7);

  // C^4
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 4.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");


  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // o1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "o1");

  // 3*C^5*H*J*L*M*o1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 6);

  // C^5
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 5.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // o1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "o1");

  // 3*C^5*I*J*L*M*o1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 3.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 6);

  // C^5
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 5.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // o1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "o1");

  // C^6*J*L*M*o1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 5);

  // C^6
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 6.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "C");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // o1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "o1");

  // D*E*F*G*H*I*J*L*M*o1
  ++it;
  pProduct = *(it);
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 10);

  // D
  it2 = pProduct->getItemPowers().begin();
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "D");

  // E
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "E");


  // F
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "F");

  // G
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "G");

  // H
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "H");

  // I
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "I");

  // J
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "J");

  // L
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "L");

  // M
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "M");

  // o1
  ++it2;
  pItemPower = *(it2);
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  pItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pItem != NULL);
  CPPUNIT_ASSERT(pItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pItem->getName() == "o1");

  delete pFraction;
}


