// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_cnormallogical.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/09/26 19:45:53 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "test_cnormallogical.hpp"
#include "compareExpressions/CNormalLogicalItem.h"
#include "compareExpressions/CNormalChoiceLogical.h"
#include "compareExpressions/CNormalFraction.h"
#include "function/CEvaluationTree.h"
#include "compareExpressions/CNormalTranslation.h"
#include "compareExpressions/CNormalSum.h"
#include "compareExpressions/CNormalItemPower.h"
#include "compareExpressions/CNormalProduct.h"
#include "compareExpressions/CNormalItem.h"

void test_cnormallogical::setUp(){}

void test_cnormallogical::tearDown(){}

void test_cnormallogical::test_SetOfSetsSorter_operator()
{
  CNormalLogical::SetOfSetsSorter<CNormalLogicalItem> sorter;
  CNormalLogicalItem* pLogicalItem1 = new CNormalLogicalItem();
  pLogicalItem1->setType(CNormalLogicalItem::TRUE);
  CNormalLogicalItem* pLogicalItem2 = new CNormalLogicalItem();
  pLogicalItem2->setType(CNormalLogicalItem::FALSE);
  CNormalLogicalItem* pLogicalItem3 = new CNormalLogicalItem();
  pLogicalItem3->setType(CNormalLogicalItem::EQ);
  CNormalFraction* pFraction1 = new CNormalFraction();
  pFraction1->multiply(7.0);
  CNormalFraction* pFraction2 = new CNormalFraction();
  pFraction1->multiply(9.0);
  pLogicalItem3->setLeft(*pFraction1);
  pLogicalItem3->setRight(*pFraction2);
  delete pFraction1;
  delete pFraction2;
  CNormalLogical::ItemSet set1;
  CNormalLogical::ItemSet set2;
  CNormalLogical::ItemSet set3;
  CNormalLogical::ItemSet set4;
  CNormalLogical::ItemSet set5;
  CNormalLogical::ItemSet set6;
  CNormalLogical::ItemSet set7;
  CNormalLogical::ItemSet set8;
  CNormalLogical::ItemSet set9;
  CNormalLogical::ItemSet set10;
  CNormalLogical::ItemSet set11;
  CNormalLogical::ItemSet set12;
  set1.insert(std::make_pair(pLogicalItem1, true));
  set2.insert(std::make_pair(pLogicalItem2, true));
  set3.insert(std::make_pair(pLogicalItem3, true));
  set4.insert(std::make_pair(pLogicalItem1, false));
  set5.insert(std::make_pair(pLogicalItem2, false));
  set6.insert(std::make_pair(pLogicalItem3, false));
  std::pair<CNormalLogical::ItemSet, bool> pair1 = std::make_pair(set1, true);
  std::pair<CNormalLogical::ItemSet, bool> pair2 = std::make_pair(set2, true);
  std::pair<CNormalLogical::ItemSet, bool> pair3 = std::make_pair(set3, true);
  std::pair<CNormalLogical::ItemSet, bool> pair4 = std::make_pair(set4, true);
  std::pair<CNormalLogical::ItemSet, bool> pair5 = std::make_pair(set5, true);
  std::pair<CNormalLogical::ItemSet, bool> pair6 = std::make_pair(set6, true);
  std::pair<CNormalLogical::ItemSet, bool> pair7 = std::make_pair(set1, false);
  std::pair<CNormalLogical::ItemSet, bool> pair8 = std::make_pair(set2, false);
  std::pair<CNormalLogical::ItemSet, bool> pair9 = std::make_pair(set3, false);
  std::pair<CNormalLogical::ItemSet, bool> pair10 = std::make_pair(set4, false);
  std::pair<CNormalLogical::ItemSet, bool> pair11 = std::make_pair(set5, false);
  std::pair<CNormalLogical::ItemSet, bool> pair12 = std::make_pair(set6, false);

  CPPUNIT_ASSERT(sorter(pair1, pair2) == true);
  CPPUNIT_ASSERT(sorter(pair1, pair3) == true);
  CPPUNIT_ASSERT(sorter(pair1, pair4) == true);
  CPPUNIT_ASSERT(sorter(pair1, pair5) == true);
  CPPUNIT_ASSERT(sorter(pair1, pair6) == true);
  CPPUNIT_ASSERT(sorter(pair1, pair7) == true);
  CPPUNIT_ASSERT(sorter(pair1, pair8) == true);
  CPPUNIT_ASSERT(sorter(pair1, pair9) == true);
  CPPUNIT_ASSERT(sorter(pair1, pair10) == true);
  CPPUNIT_ASSERT(sorter(pair1, pair11) == true);
  CPPUNIT_ASSERT(sorter(pair1, pair12) == true);

  CPPUNIT_ASSERT(sorter(pair2, pair3) == true);
  CPPUNIT_ASSERT(sorter(pair2, pair4) == true);
  CPPUNIT_ASSERT(sorter(pair2, pair5) == true);
  CPPUNIT_ASSERT(sorter(pair2, pair6) == true);
  CPPUNIT_ASSERT(sorter(pair2, pair7) == true);
  CPPUNIT_ASSERT(sorter(pair2, pair8) == true);
  CPPUNIT_ASSERT(sorter(pair2, pair9) == true);
  CPPUNIT_ASSERT(sorter(pair2, pair10) == true);
  CPPUNIT_ASSERT(sorter(pair2, pair11) == true);
  CPPUNIT_ASSERT(sorter(pair2, pair12) == true);

  CPPUNIT_ASSERT(sorter(pair3, pair4) == true);
  CPPUNIT_ASSERT(sorter(pair3, pair5) == true);
  CPPUNIT_ASSERT(sorter(pair3, pair6) == true);
  CPPUNIT_ASSERT(sorter(pair3, pair7) == true);
  CPPUNIT_ASSERT(sorter(pair3, pair8) == true);
  CPPUNIT_ASSERT(sorter(pair3, pair9) == true);
  CPPUNIT_ASSERT(sorter(pair3, pair10) == true);
  CPPUNIT_ASSERT(sorter(pair3, pair11) == true);
  CPPUNIT_ASSERT(sorter(pair3, pair12) == true);

  CPPUNIT_ASSERT(sorter(pair4, pair5) == true);
  CPPUNIT_ASSERT(sorter(pair4, pair6) == true);
  CPPUNIT_ASSERT(sorter(pair4, pair7) == true);
  CPPUNIT_ASSERT(sorter(pair4, pair8) == true);
  CPPUNIT_ASSERT(sorter(pair4, pair9) == true);
  CPPUNIT_ASSERT(sorter(pair4, pair10) == true);
  CPPUNIT_ASSERT(sorter(pair4, pair11) == true);
  CPPUNIT_ASSERT(sorter(pair4, pair12) == true);

  CPPUNIT_ASSERT(sorter(pair5, pair6) == true);
  CPPUNIT_ASSERT(sorter(pair5, pair7) == true);
  CPPUNIT_ASSERT(sorter(pair5, pair8) == true);
  CPPUNIT_ASSERT(sorter(pair5, pair9) == true);
  CPPUNIT_ASSERT(sorter(pair5, pair10) == true);
  CPPUNIT_ASSERT(sorter(pair5, pair11) == true);
  CPPUNIT_ASSERT(sorter(pair5, pair12) == true);

  CPPUNIT_ASSERT(sorter(pair6, pair7) == true);
  CPPUNIT_ASSERT(sorter(pair6, pair8) == true);
  CPPUNIT_ASSERT(sorter(pair6, pair9) == true);
  CPPUNIT_ASSERT(sorter(pair6, pair10) == true);
  CPPUNIT_ASSERT(sorter(pair6, pair11) == true);
  CPPUNIT_ASSERT(sorter(pair6, pair12) == true);

  CPPUNIT_ASSERT(sorter(pair7, pair8) == true);
  CPPUNIT_ASSERT(sorter(pair7, pair9) == true);
  CPPUNIT_ASSERT(sorter(pair7, pair10) == true);
  CPPUNIT_ASSERT(sorter(pair7, pair11) == true);
  CPPUNIT_ASSERT(sorter(pair7, pair12) == true);

  CPPUNIT_ASSERT(sorter(pair8, pair9) == true);
  CPPUNIT_ASSERT(sorter(pair8, pair10) == true);
  CPPUNIT_ASSERT(sorter(pair8, pair11) == true);
  CPPUNIT_ASSERT(sorter(pair8, pair12) == true);

  CPPUNIT_ASSERT(sorter(pair9, pair10) == true);
  CPPUNIT_ASSERT(sorter(pair9, pair11) == true);
  CPPUNIT_ASSERT(sorter(pair9, pair12) == true);

  CPPUNIT_ASSERT(sorter(pair10, pair11) == true);
  CPPUNIT_ASSERT(sorter(pair10, pair12) == true);

  CPPUNIT_ASSERT(sorter(pair11, pair12) == true);

  // turn all tests around
  CPPUNIT_ASSERT(sorter(pair2, pair1) == false);
  CPPUNIT_ASSERT(sorter(pair3, pair1) == false);
  CPPUNIT_ASSERT(sorter(pair4, pair1) == false);
  CPPUNIT_ASSERT(sorter(pair5, pair1) == false);
  CPPUNIT_ASSERT(sorter(pair6, pair1) == false);
  CPPUNIT_ASSERT(sorter(pair7, pair1) == false);
  CPPUNIT_ASSERT(sorter(pair8, pair1) == false);
  CPPUNIT_ASSERT(sorter(pair9, pair1) == false);
  CPPUNIT_ASSERT(sorter(pair10, pair1) == false);
  CPPUNIT_ASSERT(sorter(pair11, pair1) == false);
  CPPUNIT_ASSERT(sorter(pair12, pair1) == false);

  CPPUNIT_ASSERT(sorter(pair3, pair2) == false);
  CPPUNIT_ASSERT(sorter(pair4, pair2) == false);
  CPPUNIT_ASSERT(sorter(pair5, pair2) == false);
  CPPUNIT_ASSERT(sorter(pair6, pair2) == false);
  CPPUNIT_ASSERT(sorter(pair7, pair2) == false);
  CPPUNIT_ASSERT(sorter(pair8, pair2) == false);
  CPPUNIT_ASSERT(sorter(pair9, pair2) == false);
  CPPUNIT_ASSERT(sorter(pair10, pair2) == false);
  CPPUNIT_ASSERT(sorter(pair11, pair2) == false);
  CPPUNIT_ASSERT(sorter(pair12, pair2) == false);

  CPPUNIT_ASSERT(sorter(pair4, pair3) == false);
  CPPUNIT_ASSERT(sorter(pair5, pair3) == false);
  CPPUNIT_ASSERT(sorter(pair6, pair3) == false);
  CPPUNIT_ASSERT(sorter(pair7, pair3) == false);
  CPPUNIT_ASSERT(sorter(pair8, pair3) == false);
  CPPUNIT_ASSERT(sorter(pair9, pair3) == false);
  CPPUNIT_ASSERT(sorter(pair10, pair3) == false);
  CPPUNIT_ASSERT(sorter(pair11, pair3) == false);
  CPPUNIT_ASSERT(sorter(pair12, pair3) == false);

  CPPUNIT_ASSERT(sorter(pair5, pair4) == false);
  CPPUNIT_ASSERT(sorter(pair6, pair4) == false);
  CPPUNIT_ASSERT(sorter(pair7, pair4) == false);
  CPPUNIT_ASSERT(sorter(pair8, pair4) == false);
  CPPUNIT_ASSERT(sorter(pair9, pair4) == false);
  CPPUNIT_ASSERT(sorter(pair10, pair4) == false);
  CPPUNIT_ASSERT(sorter(pair11, pair4) == false);
  CPPUNIT_ASSERT(sorter(pair12, pair4) == false);

  CPPUNIT_ASSERT(sorter(pair6, pair5) == false);
  CPPUNIT_ASSERT(sorter(pair7, pair5) == false);
  CPPUNIT_ASSERT(sorter(pair8, pair5) == false);
  CPPUNIT_ASSERT(sorter(pair9, pair5) == false);
  CPPUNIT_ASSERT(sorter(pair10, pair5) == false);
  CPPUNIT_ASSERT(sorter(pair11, pair5) == false);
  CPPUNIT_ASSERT(sorter(pair12, pair5) == false);

  CPPUNIT_ASSERT(sorter(pair7, pair6) == false);
  CPPUNIT_ASSERT(sorter(pair8, pair6) == false);
  CPPUNIT_ASSERT(sorter(pair9, pair6) == false);
  CPPUNIT_ASSERT(sorter(pair10, pair6) == false);
  CPPUNIT_ASSERT(sorter(pair11, pair6) == false);
  CPPUNIT_ASSERT(sorter(pair12, pair6) == false);

  CPPUNIT_ASSERT(sorter(pair8, pair7) == false);
  CPPUNIT_ASSERT(sorter(pair9, pair7) == false);
  CPPUNIT_ASSERT(sorter(pair10, pair7) == false);
  CPPUNIT_ASSERT(sorter(pair11, pair7) == false);
  CPPUNIT_ASSERT(sorter(pair12, pair7) == false);

  CPPUNIT_ASSERT(sorter(pair9, pair8) == false);
  CPPUNIT_ASSERT(sorter(pair10, pair8) == false);
  CPPUNIT_ASSERT(sorter(pair11, pair8) == false);
  CPPUNIT_ASSERT(sorter(pair12, pair8) == false);

  CPPUNIT_ASSERT(sorter(pair10, pair9) == false);
  CPPUNIT_ASSERT(sorter(pair11, pair9) == false);
  CPPUNIT_ASSERT(sorter(pair12, pair9) == false);

  CPPUNIT_ASSERT(sorter(pair11, pair10) == false);
  CPPUNIT_ASSERT(sorter(pair12, pair10) == false);

  CPPUNIT_ASSERT(sorter(pair12, pair11) == false);

  // make sure no entry is smaller than itself
  CPPUNIT_ASSERT(sorter(pair1, pair1) == false);
  CPPUNIT_ASSERT(sorter(pair2, pair2) == false);
  CPPUNIT_ASSERT(sorter(pair3, pair3) == false);
  CPPUNIT_ASSERT(sorter(pair4, pair4) == false);
  CPPUNIT_ASSERT(sorter(pair5, pair5) == false);
  CPPUNIT_ASSERT(sorter(pair6, pair6) == false);
  CPPUNIT_ASSERT(sorter(pair7, pair7) == false);
  CPPUNIT_ASSERT(sorter(pair8, pair6) == false);
  CPPUNIT_ASSERT(sorter(pair9, pair9) == false);
  CPPUNIT_ASSERT(sorter(pair10, pair10) == false);
  CPPUNIT_ASSERT(sorter(pair11, pair11) == false);
  CPPUNIT_ASSERT(sorter(pair12, pair12) == false);

  delete pLogicalItem1;
  delete pLogicalItem2;
  delete pLogicalItem3;
}

void test_cnormallogical::test_SetSorter_operator()
{
  CNormalLogical::SetSorter<CNormalLogicalItem> sorter;
  CNormalLogicalItem* pLogicalItem1 = new CNormalLogicalItem();
  pLogicalItem1->setType(CNormalLogicalItem::TRUE);
  CNormalLogicalItem* pLogicalItem2 = new CNormalLogicalItem();
  pLogicalItem2->setType(CNormalLogicalItem::FALSE);
  CNormalLogicalItem* pLogicalItem3 = new CNormalLogicalItem();
  pLogicalItem3->setType(CNormalLogicalItem::EQ);
  CNormalFraction* pFraction1 = new CNormalFraction();
  pFraction1->multiply(7.0);
  CNormalFraction* pFraction2 = new CNormalFraction();
  pFraction1->multiply(9.0);
  pLogicalItem3->setLeft(*pFraction1);
  pLogicalItem3->setRight(*pFraction2);
  delete pFraction1;
  delete pFraction2;
  std::pair<CNormalLogicalItem*, bool> pair1 = std::make_pair(pLogicalItem1, false);
  std::pair<CNormalLogicalItem*, bool> pair2 = std::make_pair(pLogicalItem1, true);
  std::pair<CNormalLogicalItem*, bool> pair3 = std::make_pair(pLogicalItem2, false);
  std::pair<CNormalLogicalItem*, bool> pair4 = std::make_pair(pLogicalItem2, true);
  std::pair<CNormalLogicalItem*, bool> pair5 = std::make_pair(pLogicalItem3, false);
  std::pair<CNormalLogicalItem*, bool> pair6 = std::make_pair(pLogicalItem3, true);

  CPPUNIT_ASSERT(sorter(pair1, pair3) == true);
  CPPUNIT_ASSERT(sorter(pair3, pair5) == true);
  CPPUNIT_ASSERT(sorter(pair1, pair5) == true);

  CPPUNIT_ASSERT(sorter(pair2, pair4) == true);
  CPPUNIT_ASSERT(sorter(pair4, pair6) == true);
  CPPUNIT_ASSERT(sorter(pair2, pair6) == true);

  CPPUNIT_ASSERT(sorter(pair2, pair1) == true);
  CPPUNIT_ASSERT(sorter(pair4, pair1) == true);
  CPPUNIT_ASSERT(sorter(pair6, pair1) == true);

  CPPUNIT_ASSERT(sorter(pair2, pair3) == true);
  CPPUNIT_ASSERT(sorter(pair4, pair3) == true);
  CPPUNIT_ASSERT(sorter(pair6, pair3) == true);

  CPPUNIT_ASSERT(sorter(pair2, pair5) == true);
  CPPUNIT_ASSERT(sorter(pair4, pair5) == true);
  CPPUNIT_ASSERT(sorter(pair6, pair5) == true);

  // turn all comparisons around
  CPPUNIT_ASSERT(sorter(pair3, pair1) == false);
  CPPUNIT_ASSERT(sorter(pair5, pair3) == false);
  CPPUNIT_ASSERT(sorter(pair5, pair1) == false);

  CPPUNIT_ASSERT(sorter(pair4, pair2) == false);
  CPPUNIT_ASSERT(sorter(pair6, pair4) == false);
  CPPUNIT_ASSERT(sorter(pair6, pair2) == false);

  CPPUNIT_ASSERT(sorter(pair1, pair2) == false);
  CPPUNIT_ASSERT(sorter(pair1, pair4) == false);
  CPPUNIT_ASSERT(sorter(pair1, pair6) == false);

  CPPUNIT_ASSERT(sorter(pair3, pair2) == false);
  CPPUNIT_ASSERT(sorter(pair3, pair4) == false);
  CPPUNIT_ASSERT(sorter(pair3, pair6) == false);

  CPPUNIT_ASSERT(sorter(pair5, pair2) == false);
  CPPUNIT_ASSERT(sorter(pair5, pair4) == false);
  CPPUNIT_ASSERT(sorter(pair5, pair6) == false);

  // make sure no entry is smaller than itself
  CPPUNIT_ASSERT(sorter(pair1, pair1) == false);
  CPPUNIT_ASSERT(sorter(pair2, pair2) == false);
  CPPUNIT_ASSERT(sorter(pair3, pair3) == false);
  CPPUNIT_ASSERT(sorter(pair4, pair4) == false);
  CPPUNIT_ASSERT(sorter(pair5, pair5) == false);
  CPPUNIT_ASSERT(sorter(pair6, pair6) == false);

  delete pLogicalItem1;
  delete pLogicalItem2;
  delete pLogicalItem3;
}

void test_cnormallogical::test_SetSorter_LogicalItem()
{
  CNormalLogical::ItemSet set;
  CPPUNIT_ASSERT(set.size() == 0);
  CNormalLogicalItem* pItem = new CNormalLogicalItem();

  pItem->setType(CNormalLogicalItem::TRUE);
  CNormalLogicalItem* pNewItem = dynamic_cast<CNormalLogicalItem*>(pItem->copy());
  CPPUNIT_ASSERT(pNewItem != NULL);
  set.insert(std::make_pair(pNewItem, false));
  CPPUNIT_ASSERT(set.size() == 1);
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pItem->copy());
  set.insert(std::make_pair(pNewItem, false));
  CPPUNIT_ASSERT(set.size() == 1);
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pItem->copy());
  CPPUNIT_ASSERT(pNewItem != NULL);
  set.insert(std::make_pair(pNewItem, true));
  CPPUNIT_ASSERT(set.size() == 2);
  CNormalLogical::cleanSet(set);
  CPPUNIT_ASSERT(set.size() == 0);

  pItem->setType(CNormalLogicalItem::FALSE);
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pItem->copy());
  CPPUNIT_ASSERT(pNewItem != NULL);
  set.insert(std::make_pair(pNewItem, false));
  CPPUNIT_ASSERT(set.size() == 1);
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pItem->copy());
  set.insert(std::make_pair(pNewItem, false));
  CPPUNIT_ASSERT(set.size() == 1);
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pItem->copy());
  CPPUNIT_ASSERT(pNewItem != NULL);
  set.insert(std::make_pair(pNewItem, true));
  CPPUNIT_ASSERT(set.size() == 2);
  CNormalLogical::cleanSet(set);
  CPPUNIT_ASSERT(set.size() == 0);

  pItem->setType(CNormalLogicalItem::LT);
  CNormalFraction* pFraction = new CNormalFraction();
  pFraction->multiply(3.0);
  pItem->setLeft(*pFraction);
  pFraction->multiply(5.0);
  pItem->setRight(*pFraction);
  delete pFraction;
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pItem->copy());
  CPPUNIT_ASSERT(pNewItem != NULL);
  set.insert(std::make_pair(pNewItem, false));
  CPPUNIT_ASSERT(set.size() == 1);
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pItem->copy());
  set.insert(std::make_pair(pNewItem, false));
  CPPUNIT_ASSERT(set.size() == 1);
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pItem->copy());
  CPPUNIT_ASSERT(pNewItem != NULL);
  set.insert(std::make_pair(pNewItem, true));
  CPPUNIT_ASSERT(set.size() == 2);
  CNormalLogical::cleanSet(set);
  CPPUNIT_ASSERT(set.size() == 0);

  delete pItem;
}

void test_cnormallogical::test_SetOfSetsSorter_LogicalItem()
{
  CNormalLogical::ItemSetOfSets setOfSets;
  CPPUNIT_ASSERT(setOfSets.size() == 0);
  CNormalLogical::ItemSet set;
  CNormalLogicalItem* pLogicalItem = new CNormalLogicalItem();
  pLogicalItem->setType(CNormalLogicalItem::TRUE);
  CNormalLogicalItem* pNewItem = dynamic_cast<CNormalLogicalItem*>(pLogicalItem->copy());
  CPPUNIT_ASSERT(pNewItem != NULL);

  set.insert(std::make_pair(pNewItem, false));
  setOfSets.insert(std::make_pair(set, false));
  CPPUNIT_ASSERT(setOfSets.size() == 1);
  // add the same thing again
  set.clear();
  CPPUNIT_ASSERT(set.size() == 0);
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pLogicalItem->copy());
  CPPUNIT_ASSERT(pNewItem != NULL);
  set.insert(std::make_pair(pNewItem, false));
  setOfSets.insert(std::make_pair(set, false));
  CPPUNIT_ASSERT(setOfSets.size() == 1);

  CNormalLogical::cleanSet(set);
  CPPUNIT_ASSERT(set.size() == 0);
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pLogicalItem->copy());
  CPPUNIT_ASSERT(pNewItem != NULL);
  set.insert(std::make_pair(pNewItem, true));
  setOfSets.insert(std::make_pair(set, false));
  CPPUNIT_ASSERT(setOfSets.size() == 2);
  // add the same thing again
  set.clear();
  CPPUNIT_ASSERT(set.size() == 0);
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pLogicalItem->copy());
  CPPUNIT_ASSERT(pNewItem != NULL);
  set.insert(std::make_pair(pNewItem, true));
  setOfSets.insert(std::make_pair(set, false));
  CPPUNIT_ASSERT(setOfSets.size() == 2);

  CNormalLogical::cleanSet(set);
  CPPUNIT_ASSERT(set.size() == 0);
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pLogicalItem->copy());
  CPPUNIT_ASSERT(pNewItem != NULL);
  set.insert(std::make_pair(pNewItem, false));
  setOfSets.insert(std::make_pair(set, true));
  CPPUNIT_ASSERT(setOfSets.size() == 3);
  // add the same thing again
  set.clear();
  CPPUNIT_ASSERT(set.size() == 0);
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pLogicalItem->copy());
  CPPUNIT_ASSERT(pNewItem != NULL);
  set.insert(std::make_pair(pNewItem, false));
  setOfSets.insert(std::make_pair(set, true));
  CPPUNIT_ASSERT(setOfSets.size() == 3);

  CNormalLogical::cleanSet(set);
  CPPUNIT_ASSERT(set.size() == 0);
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pLogicalItem->copy());
  CPPUNIT_ASSERT(pNewItem != NULL);
  set.insert(std::make_pair(pNewItem, true));
  setOfSets.insert(std::make_pair(set, true));
  CPPUNIT_ASSERT(setOfSets.size() == 4);
  // add the same thing again
  set.clear();
  CPPUNIT_ASSERT(set.size() == 0);
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pLogicalItem->copy());
  CPPUNIT_ASSERT(pNewItem != NULL);
  set.insert(std::make_pair(pNewItem, true));
  setOfSets.insert(std::make_pair(set, true));
  CPPUNIT_ASSERT(setOfSets.size() == 4);
  CNormalLogical::cleanSet(set);
  CNormalLogical::cleanSetOfSets(setOfSets);
  delete pLogicalItem;
}

void test_cnormallogical::test_simplify_1()
{
  CNormalLogicalItem* pCond = new CNormalLogicalItem();
  pCond->setType(CNormalLogicalItem::GT);
  std::string infix("A");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  const CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  pCond->setLeft(*pFraction);
  delete pTree;
  delete pFraction;

  infix = "PI";
  pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  pCond->setRight(*pFraction);
  delete pTree;
  delete pFraction;

  CNormalLogicalItem* pTrue = new CNormalLogicalItem();
  pTrue->setType(CNormalLogicalItem::FALSE);

  CNormalLogicalItem* pFalse = new CNormalLogicalItem();
  pFalse->setType(CNormalLogicalItem::NE);
  infix = "4";
  pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  pFalse->setLeft(*pFraction);
  delete pTree;
  delete pFraction;

  infix = "A";
  pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  pFalse->setRight(*pFraction);
  delete pTree;
  delete pFraction;

  CNormalChoiceLogical* pLogicalChoice = new CNormalChoiceLogical();
  CNormalLogical* pTmpLogical = new CNormalLogical();
  CNormalLogical::ItemSet tmpSet;
  tmpSet.insert(std::make_pair(new CNormalLogicalItem(*pCond), false));
  pTmpLogical->getAndSets().insert(std::make_pair(tmpSet, false));
  pLogicalChoice->setCondition(*pTmpLogical);
  delete pCond;
  delete pTmpLogical;
  tmpSet.clear();

  pTmpLogical = new CNormalLogical();
  tmpSet.insert(std::make_pair(new CNormalLogicalItem(*pTrue), false));
  pTmpLogical->getAndSets().insert(std::make_pair(tmpSet, false));
  pLogicalChoice->setTrueExpression(*pTmpLogical);
  delete pTrue;
  delete pTmpLogical;
  tmpSet.clear();

  pTmpLogical = new CNormalLogical();
  tmpSet.insert(std::make_pair(new CNormalLogicalItem(*pFalse), false));
  pTmpLogical->getAndSets().insert(std::make_pair(tmpSet, false));
  pLogicalChoice->setFalseExpression(*pTmpLogical);
  delete pFalse;
  delete pTmpLogical;
  tmpSet.clear();

  CNormalLogical* pLogical = new CNormalLogical();
  CNormalLogical::ChoiceSet set;
  set.insert(std::make_pair(pLogicalChoice, false));
  pLogical->getChoices().insert(std::make_pair(set, false));

  CPPUNIT_ASSERT(pLogical->simplify() == true);

  CPPUNIT_ASSERT(pLogical->getChoices().size() == 0);
  const CNormalLogical::ItemSetOfSets& orItems = pLogical->getAndSets();
  CPPUNIT_ASSERT(orItems.size() == 1);

  CNormalLogical::ItemSetOfSets::const_iterator it = orItems.begin();
  CPPUNIT_ASSERT(it->second == false);
  const CNormalLogical::ItemSet& andSet2 = it->first;
  CPPUNIT_ASSERT(andSet2.size() == 2);

  CNormalLogical::ItemSet::const_iterator it2 = andSet2.begin();
  CPPUNIT_ASSERT(it2->second == false);
  const CNormalLogicalItem* pItem = it2->first;
  CPPUNIT_ASSERT(pItem->getType() == CNormalLogicalItem::NE);

  pFraction = &pItem->getLeft();
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

  const CNormalSum* pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  const CNormalProduct* pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 4.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);

  pFraction = &pItem->getRight();
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

  pNumerator = &pFraction->getNumerator();
  CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
  pProducts = &pNumerator->getProducts();
  CPPUNIT_ASSERT(pProducts->size() == 1);
  pProduct = *(pProducts->begin());
  CPPUNIT_ASSERT(pProduct != NULL);
  CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
  CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
  const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
  CPPUNIT_ASSERT(pItemPower != NULL);
  CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
  CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
  const CNormalItem* pNormalItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pNormalItem != NULL);
  CPPUNIT_ASSERT(pNormalItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pNormalItem->getName() == "A");

  ++it2;
  CPPUNIT_ASSERT(it2->second == false);
  pItem = it2->first;
  CPPUNIT_ASSERT(pItem->getType() == CNormalLogicalItem::LE);

  pFraction = &pItem->getLeft();
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

  pNumerator = &pFraction->getNumerator();
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
  pNormalItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pNormalItem != NULL);
  CPPUNIT_ASSERT(pNormalItem->getType() == CNormalItem::VARIABLE);
  CPPUNIT_ASSERT(pNormalItem->getName() == "A");

  pFraction = &pItem->getRight();
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

  pNumerator = &pFraction->getNumerator();
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
  pNormalItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
  CPPUNIT_ASSERT(pNormalItem != NULL);
  CPPUNIT_ASSERT(pNormalItem->getType() == CNormalItem::CONSTANT);
  CPPUNIT_ASSERT(pNormalItem->getName() == "PI");

  delete pLogical;
}

/* This test is not necessary right now.
void test_cnormallogical::test_simplify_2()
{
// if(2==T) then FALSE else NOT(D==F)
CNormalLogicalItem* pCond=new CNormalLogicalItem();
pCond->setType(CNormalLogicalItem::EQ);
std::string infix("2");
CEvaluationTree* pTree = new CEvaluationTree();
pTree->setInfix(infix);
CPPUNIT_ASSERT(pTree->getRoot() != NULL);
const CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
pCond->setLeft(*pFraction);
delete pTree;
delete pFraction;

infix="T";
pTree = new CEvaluationTree();
pTree->setInfix(infix);
CPPUNIT_ASSERT(pTree->getRoot() != NULL);
pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
pCond->setRight(*pFraction);
delete pTree;
delete pFraction;

CNormalLogicalItem* pTrue=new CNormalLogicalItem();
pTrue->setType(CNormalLogicalItem::FALSE);

CNormalLogicalItem* pFalse=new CNormalLogicalItem();
pFalse->setType(CNormalLogicalItem::EQ);
infix="D";
pTree = new CEvaluationTree();
pTree->setInfix(infix);
CPPUNIT_ASSERT(pTree->getRoot() != NULL);
pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
pFalse->setLeft(*pFraction);
delete pTree;
delete pFraction;

infix="F";
pTree = new CEvaluationTree();
pTree->setInfix(infix);
CPPUNIT_ASSERT(pTree->getRoot() != NULL);
pFraction = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
pFalse->setRight(*pFraction);
delete pTree;
delete pFraction;

CNormalChoiceLogical* pLogicalChoice=new CNormalChoiceLogical();
CNormalLogical* pTmpLogical=new CNormalLogical();
CNormalLogical::ItemSet tmpSet;
tmpSet.insert(std::make_pair(new CNormalLogicalItem(*pCond),false));
pTmpLogical->getAndSets().insert(std::make_pair(tmpSet,false));
pLogicalChoice->setCondition(*pTmpLogical);
delete pCond;
delete pTmpLogical;
tmpSet.clear();

pTmpLogical=new CNormalLogical();
tmpSet.insert(std::make_pair(new CNormalLogicalItem(*pTrue),false));
pTmpLogical->getAndSets().insert(std::make_pair(tmpSet,false));
pLogicalChoice->setTrueExpression(*pTmpLogical);
delete pTrue;
delete pTmpLogical;
tmpSet.clear();

pTmpLogical=new CNormalLogical();
tmpSet.insert(std::make_pair(new CNormalLogicalItem(*pFalse),false));
pTmpLogical->getAndSets().insert(std::make_pair(tmpSet,false));
pLogicalChoice->setFalseExpression(*pTmpLogical);
delete pFalse;
delete pTmpLogical;
tmpSet.clear();

CNormalLogical* pLogical=new CNormalLogical();
CNormalLogical::ChoiceSet set;
set.insert(std::make_pair(pLogicalChoice,false));
pLogical->getChoices().insert(std::make_pair(set,false));

pLogical->simplify();

CPPUNIT_ASSERT(pLogical->getChoices().size()==0);
const CNormalLogical::ItemSetOfSets& orItems=pLogical->getAndSets();
CPPUNIT_ASSERT(orItems.size()==2);

CNormalLogical::ItemSetOfSets::const_iterator it=orItems.begin();
CPPUNIT_ASSERT(it->second==false);
const CNormalLogical::ItemSet& andSet=it->first;
CPPUNIT_ASSERT(andSet.size()==1);
CNormalLogical::ItemSet::const_iterator it2=andSet.begin();
CPPUNIT_ASSERT(it2->second==false);
const CNormalLogicalItem* pItem=it2->first;
CPPUNIT_ASSERT(pItem->getType()==CNormalLogicalItem::FALSE);

++it;
CPPUNIT_ASSERT(it->second==false);
const CNormalLogical::ItemSet& andSet2=it->first;
CPPUNIT_ASSERT(andSet2.size()==2);

it2=andSet2.begin();
CPPUNIT_ASSERT(it2->second==false);
pItem=it2->first;
CPPUNIT_ASSERT(pItem->getType()==CNormalLogicalItem::NE);

pFraction=&pItem->getLeft();
CPPUNIT_ASSERT(pFraction != NULL);
CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

const CNormalSum* pNumerator = &pFraction->getNumerator();
CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
const std::set<CNormalProduct*, compareProducts >* pProducts = &pNumerator->getProducts();
CPPUNIT_ASSERT(pProducts->size() == 1);
const CNormalProduct* pProduct = *(pProducts->begin());
CPPUNIT_ASSERT(pProduct != NULL);
CPPUNIT_ASSERT(pProduct->getFactor() == 4.0);
CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 0);

pFraction=&pItem->getRight();
CPPUNIT_ASSERT(pFraction != NULL);
CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

pNumerator = &pFraction->getNumerator();
CPPUNIT_ASSERT(pNumerator->getFractions().size() == 0);
pProducts = &pNumerator->getProducts();
CPPUNIT_ASSERT(pProducts->size() == 1);
pProduct = *(pProducts->begin());
CPPUNIT_ASSERT(pProduct != NULL);
CPPUNIT_ASSERT(pProduct->getFactor() == 1.0);
CPPUNIT_ASSERT(pProduct->getItemPowers().size() == 1);
const CNormalItemPower* pItemPower = *(pProduct->getItemPowers().begin());
CPPUNIT_ASSERT(pItemPower != NULL);
CPPUNIT_ASSERT(pItemPower->getExp() == 1.0);
CPPUNIT_ASSERT(pItemPower->getItemType() == CNormalItemPower::ITEM);
const CNormalItem* pNormalItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
CPPUNIT_ASSERT(pNormalItem != NULL);
CPPUNIT_ASSERT(pNormalItem->getType() == CNormalItem::VARIABLE);
CPPUNIT_ASSERT(pNormalItem->getName() == "A");

++it2;
CPPUNIT_ASSERT(it2->second==false);
pItem=it2->first;
CPPUNIT_ASSERT(pItem->getType()==CNormalLogicalItem::LE);

pFraction=&pItem->getLeft();
CPPUNIT_ASSERT(pFraction != NULL);
CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

pNumerator = &pFraction->getNumerator();
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
pNormalItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
CPPUNIT_ASSERT(pNormalItem != NULL);
CPPUNIT_ASSERT(pNormalItem->getType() == CNormalItem::VARIABLE);
CPPUNIT_ASSERT(pNormalItem->getName() == "A");

pFraction=&pItem->getRight();
CPPUNIT_ASSERT(pFraction != NULL);
CPPUNIT_ASSERT(pFraction->checkDenominatorOne() == true);

pNumerator = &pFraction->getNumerator();
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
pNormalItem = dynamic_cast<const CNormalItem*>(&pItemPower->getItem());
CPPUNIT_ASSERT(pNormalItem != NULL);
CPPUNIT_ASSERT(pNormalItem->getType() == CNormalItem::CONSTANT);
CPPUNIT_ASSERT(pNormalItem->getName() == "PI");

delete pLogical;
}
 */
