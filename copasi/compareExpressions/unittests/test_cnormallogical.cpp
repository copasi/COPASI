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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "test_cnormallogical.hpp"
#include "copasi/compareExpressions/CNormalLogicalItem.h"
#include "copasi/compareExpressions/CNormalChoiceLogical.h"
#include "copasi/compareExpressions/CNormalFraction.h"
#include "copasi/function/CEvaluationTree.h"
#include "copasi/compareExpressions/CNormalTranslation.h"
#include "copasi/compareExpressions/CNormalSum.h"
#include "copasi/compareExpressions/CNormalItemPower.h"
#include "copasi/compareExpressions/CNormalProduct.h"
#include "copasi/compareExpressions/CNormalItem.h"
#include "copasi/core/CRootContainer.h"

template void CNormalLogical::cleanSet(const CNormalLogical::ItemSet&);

void test_cnormallogical::setUp()
{
  CRootContainer::init(false, 0, NULL);
}

void test_cnormallogical::tearDown()
{
  CRootContainer::destroy();
}

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
  delete pNewItem;
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pItem->copy());
  CPPUNIT_ASSERT(pNewItem != NULL);
  set.insert(std::make_pair(pNewItem, true));
  CPPUNIT_ASSERT(set.size() == 2);
  CNormalLogical::cleanSet(set);
  set.clear();
  CPPUNIT_ASSERT(set.size() == 0);

  pItem->setType(CNormalLogicalItem::FALSE);
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pItem->copy());
  CPPUNIT_ASSERT(pNewItem != NULL);
  set.insert(std::make_pair(pNewItem, false));
  CPPUNIT_ASSERT(set.size() == 1);
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pItem->copy());
  set.insert(std::make_pair(pNewItem, false));
  CPPUNIT_ASSERT(set.size() == 1);
  delete pNewItem;
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pItem->copy());
  CPPUNIT_ASSERT(pNewItem != NULL);
  set.insert(std::make_pair(pNewItem, true));
  CPPUNIT_ASSERT(set.size() == 2);
  CNormalLogical::cleanSet(set);
  set.clear();
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
  delete pNewItem;
  pNewItem = dynamic_cast<CNormalLogicalItem*>(pItem->copy());
  CPPUNIT_ASSERT(pNewItem != NULL);
  set.insert(std::make_pair(pNewItem, true));
  CPPUNIT_ASSERT(set.size() == 2);
  CNormalLogical::cleanSet(set);
  set.clear();
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
  set.clear();
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
  set.clear();
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
  set.clear();
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
  set.clear();
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

void test_cnormallogical::test_SetSorter_operator2()
{
  // create items to sort
  // A: (PI < A)           !A: (A <= PI)
  // B: (4 != A)           !B: (4 == A)
  // C: (2 == T)           !C: (2 != T)
  // D: (D != F)           !D: (D == F)
  // E: (SIN (PI*D) < X)   !E: (X <= SIN(PI*D))
  // F: (2*T^(3J) != 6.2)  !F: (2*T^(3J) == 6.2)
  std::string infix("A");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction* pA = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pA != NULL);
  infix = "PI";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction*pPI = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pPI != NULL);
  infix = "D";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction*pD = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pD != NULL);
  infix = "F";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction*pF = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pF != NULL);
  infix = "T";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction*pT = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pT != NULL);
  infix = "X";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction*pX = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pX != NULL);
  infix = "SIN(PI*D)";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction*pSIN = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pSIN != NULL);
  infix = "2*T^(3*J)";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction*pPOWER = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pPOWER != NULL);
  infix = "2";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction*pTWO = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pTWO != NULL);
  infix = "4";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction*pFOUR = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pFOUR != NULL);
  infix = "6.2";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction*pSIX = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pSIX != NULL);
  delete pTree;

  // A: (PI < A)           !A: (A <= PI)
  CNormalLogicalItem* pLA = new CNormalLogicalItem();
  pLA->setType(CNormalLogicalItem::LT);
  pLA->setLeft(*pPI);
  pLA->setRight(*pA);
  CNormalLogicalItem* pLNotA = new CNormalLogicalItem();
  pLNotA->setType(CNormalLogicalItem::LE);
  pLNotA->setLeft(*pA);
  pLNotA->setRight(*pPI);
  // B: (4 != A)           !B: (4 == A)
  CNormalLogicalItem* pLB = new CNormalLogicalItem();
  pLB->setType(CNormalLogicalItem::NE);
  pLB->setLeft(*pFOUR);
  pLB->setRight(*pA);
  CNormalLogicalItem* pLNotB = new CNormalLogicalItem();
  pLNotB->setType(CNormalLogicalItem::EQ);
  pLNotB->setLeft(*pFOUR);
  pLNotB->setRight(*pA);
  // C: (2 == T)           !C: (2 != T)
  CNormalLogicalItem* pLC = new CNormalLogicalItem();
  pLC->setType(CNormalLogicalItem::EQ);
  pLC->setLeft(*pTWO);
  pLC->setRight(*pT);
  CNormalLogicalItem* pLNotC = new CNormalLogicalItem();
  pLNotC->setType(CNormalLogicalItem::NE);
  pLNotC->setLeft(*pTWO);
  pLNotC->setRight(*pT);
  // D: (D != F)           !D: (D == F)
  CNormalLogicalItem* pLD = new CNormalLogicalItem();
  pLD->setType(CNormalLogicalItem::NE);
  pLD->setLeft(*pD);
  pLD->setRight(*pF);
  CNormalLogicalItem* pLNotD = new CNormalLogicalItem();
  pLNotD->setType(CNormalLogicalItem::EQ);
  pLNotD->setLeft(*pD);
  pLNotD->setRight(*pF);
  // E: (SIN (PI*D) < X)   !E: (X <= SIN(PI*D))
  CNormalLogicalItem* pLE = new CNormalLogicalItem();
  pLE->setType(CNormalLogicalItem::LT);
  pLE->setLeft(*pSIN);
  pLE->setRight(*pX);
  CNormalLogicalItem* pLNotE = new CNormalLogicalItem();
  pLNotE->setType(CNormalLogicalItem::LE);
  pLNotE->setLeft(*pX);
  pLNotE->setRight(*pSIN);
  // F: (2*T^(3J) != 6.2)  !F: (2*T^(3J) == 6.2)
  CNormalLogicalItem* pLF = new CNormalLogicalItem();
  pLF->setType(CNormalLogicalItem::NE);
  pLF->setLeft(*pPOWER);
  pLF->setRight(*pSIX);
  CNormalLogicalItem* pLNotF = new CNormalLogicalItem();
  pLNotF->setType(CNormalLogicalItem::EQ);
  pLNotF->setLeft(*pPOWER);
  pLNotF->setRight(*pSIX);

  delete pA;
  delete pPI;
  delete pT;
  delete pX;
  delete pF;
  delete pD;
  delete pPOWER;
  delete pSIN;
  delete pTWO;
  delete pFOUR;
  delete pSIX;

  // now compare the items with each other
  CNormalLogical::SetSorter<CNormalLogicalItem> sorter;
  // pLA with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLA, false), std::pair<CNormalLogicalItem*, bool>(pLA, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLA, false), std::pair<CNormalLogicalItem*, bool>(pLNotA, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLA, false), std::pair<CNormalLogicalItem*, bool>(pLB, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLA, false), std::pair<CNormalLogicalItem*, bool>(pLNotB, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLA, false), std::pair<CNormalLogicalItem*, bool>(pLC, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLA, false), std::pair<CNormalLogicalItem*, bool>(pLNotC, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLA, false), std::pair<CNormalLogicalItem*, bool>(pLD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLA, false), std::pair<CNormalLogicalItem*, bool>(pLNotD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLA, false), std::pair<CNormalLogicalItem*, bool>(pLE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLA, false), std::pair<CNormalLogicalItem*, bool>(pLNotE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLA, false), std::pair<CNormalLogicalItem*, bool>(pLF, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLA, false), std::pair<CNormalLogicalItem*, bool>(pLNotF, false)) == false);

  // pLNotA with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotA, false), std::pair<CNormalLogicalItem*, bool>(pLA, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotA, false), std::pair<CNormalLogicalItem*, bool>(pLNotA, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotA, false), std::pair<CNormalLogicalItem*, bool>(pLB, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotA, false), std::pair<CNormalLogicalItem*, bool>(pLNotB, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotA, false), std::pair<CNormalLogicalItem*, bool>(pLC, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotA, false), std::pair<CNormalLogicalItem*, bool>(pLNotC, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotA, false), std::pair<CNormalLogicalItem*, bool>(pLD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotA, false), std::pair<CNormalLogicalItem*, bool>(pLNotD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotA, false), std::pair<CNormalLogicalItem*, bool>(pLE, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotA, false), std::pair<CNormalLogicalItem*, bool>(pLNotE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotA, false), std::pair<CNormalLogicalItem*, bool>(pLF, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotA, false), std::pair<CNormalLogicalItem*, bool>(pLNotF, false)) == false);

  // pLB with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLB, false), std::pair<CNormalLogicalItem*, bool>(pLA, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLB, false), std::pair<CNormalLogicalItem*, bool>(pLNotA, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLB, false), std::pair<CNormalLogicalItem*, bool>(pLB, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLB, false), std::pair<CNormalLogicalItem*, bool>(pLNotB, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLB, false), std::pair<CNormalLogicalItem*, bool>(pLC, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLB, false), std::pair<CNormalLogicalItem*, bool>(pLNotC, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLB, false), std::pair<CNormalLogicalItem*, bool>(pLD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLB, false), std::pair<CNormalLogicalItem*, bool>(pLNotD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLB, false), std::pair<CNormalLogicalItem*, bool>(pLE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLB, false), std::pair<CNormalLogicalItem*, bool>(pLNotE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLB, false), std::pair<CNormalLogicalItem*, bool>(pLF, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLB, false), std::pair<CNormalLogicalItem*, bool>(pLNotF, false)) == false);

  // pLNotB with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotB, false), std::pair<CNormalLogicalItem*, bool>(pLA, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotB, false), std::pair<CNormalLogicalItem*, bool>(pLNotA, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotB, false), std::pair<CNormalLogicalItem*, bool>(pLB, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotB, false), std::pair<CNormalLogicalItem*, bool>(pLNotB, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotB, false), std::pair<CNormalLogicalItem*, bool>(pLC, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotB, false), std::pair<CNormalLogicalItem*, bool>(pLNotC, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotB, false), std::pair<CNormalLogicalItem*, bool>(pLD, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotB, false), std::pair<CNormalLogicalItem*, bool>(pLNotD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotB, false), std::pair<CNormalLogicalItem*, bool>(pLE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotB, false), std::pair<CNormalLogicalItem*, bool>(pLNotE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotB, false), std::pair<CNormalLogicalItem*, bool>(pLF, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotB, false), std::pair<CNormalLogicalItem*, bool>(pLNotF, false)) == false);

  // pLC with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLC, false), std::pair<CNormalLogicalItem*, bool>(pLA, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLC, false), std::pair<CNormalLogicalItem*, bool>(pLNotA, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLC, false), std::pair<CNormalLogicalItem*, bool>(pLB, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLC, false), std::pair<CNormalLogicalItem*, bool>(pLNotB, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLC, false), std::pair<CNormalLogicalItem*, bool>(pLC, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLC, false), std::pair<CNormalLogicalItem*, bool>(pLNotC, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLC, false), std::pair<CNormalLogicalItem*, bool>(pLD, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLC, false), std::pair<CNormalLogicalItem*, bool>(pLNotD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLC, false), std::pair<CNormalLogicalItem*, bool>(pLE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLC, false), std::pair<CNormalLogicalItem*, bool>(pLNotE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLC, false), std::pair<CNormalLogicalItem*, bool>(pLF, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLC, false), std::pair<CNormalLogicalItem*, bool>(pLNotF, false)) == true);

  // pLNotC with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotC, false), std::pair<CNormalLogicalItem*, bool>(pLA, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotC, false), std::pair<CNormalLogicalItem*, bool>(pLNotA, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotC, false), std::pair<CNormalLogicalItem*, bool>(pLB, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotC, false), std::pair<CNormalLogicalItem*, bool>(pLNotB, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotC, false), std::pair<CNormalLogicalItem*, bool>(pLC, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotC, false), std::pair<CNormalLogicalItem*, bool>(pLNotC, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotC, false), std::pair<CNormalLogicalItem*, bool>(pLD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotC, false), std::pair<CNormalLogicalItem*, bool>(pLNotD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotC, false), std::pair<CNormalLogicalItem*, bool>(pLE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotC, false), std::pair<CNormalLogicalItem*, bool>(pLNotE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotC, false), std::pair<CNormalLogicalItem*, bool>(pLF, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotC, false), std::pair<CNormalLogicalItem*, bool>(pLNotF, false)) == false);

  // pLD with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLD, false), std::pair<CNormalLogicalItem*, bool>(pLA, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLD, false), std::pair<CNormalLogicalItem*, bool>(pLNotA, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLD, false), std::pair<CNormalLogicalItem*, bool>(pLB, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLD, false), std::pair<CNormalLogicalItem*, bool>(pLNotB, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLD, false), std::pair<CNormalLogicalItem*, bool>(pLC, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLD, false), std::pair<CNormalLogicalItem*, bool>(pLNotC, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLD, false), std::pair<CNormalLogicalItem*, bool>(pLD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLD, false), std::pair<CNormalLogicalItem*, bool>(pLNotD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLD, false), std::pair<CNormalLogicalItem*, bool>(pLE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLD, false), std::pair<CNormalLogicalItem*, bool>(pLNotE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLD, false), std::pair<CNormalLogicalItem*, bool>(pLF, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLD, false), std::pair<CNormalLogicalItem*, bool>(pLNotF, false)) == false);

  // pLNotD with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotD, false), std::pair<CNormalLogicalItem*, bool>(pLA, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotD, false), std::pair<CNormalLogicalItem*, bool>(pLNotA, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotD, false), std::pair<CNormalLogicalItem*, bool>(pLB, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotD, false), std::pair<CNormalLogicalItem*, bool>(pLNotB, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotD, false), std::pair<CNormalLogicalItem*, bool>(pLC, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotD, false), std::pair<CNormalLogicalItem*, bool>(pLNotC, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotD, false), std::pair<CNormalLogicalItem*, bool>(pLD, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotD, false), std::pair<CNormalLogicalItem*, bool>(pLNotD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotD, false), std::pair<CNormalLogicalItem*, bool>(pLE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotD, false), std::pair<CNormalLogicalItem*, bool>(pLNotE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotD, false), std::pair<CNormalLogicalItem*, bool>(pLF, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotD, false), std::pair<CNormalLogicalItem*, bool>(pLNotF, false)) == true);

  // pLE with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLE, false), std::pair<CNormalLogicalItem*, bool>(pLA, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLE, false), std::pair<CNormalLogicalItem*, bool>(pLNotA, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLE, false), std::pair<CNormalLogicalItem*, bool>(pLB, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLE, false), std::pair<CNormalLogicalItem*, bool>(pLNotB, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLE, false), std::pair<CNormalLogicalItem*, bool>(pLC, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLE, false), std::pair<CNormalLogicalItem*, bool>(pLNotC, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLE, false), std::pair<CNormalLogicalItem*, bool>(pLD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLE, false), std::pair<CNormalLogicalItem*, bool>(pLNotD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLE, false), std::pair<CNormalLogicalItem*, bool>(pLE, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLE, false), std::pair<CNormalLogicalItem*, bool>(pLNotE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLE, false), std::pair<CNormalLogicalItem*, bool>(pLF, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLE, false), std::pair<CNormalLogicalItem*, bool>(pLNotF, false)) == false);

  // pLNotE with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotE, false), std::pair<CNormalLogicalItem*, bool>(pLA, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotE, false), std::pair<CNormalLogicalItem*, bool>(pLNotA, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotE, false), std::pair<CNormalLogicalItem*, bool>(pLB, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotE, false), std::pair<CNormalLogicalItem*, bool>(pLNotB, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotE, false), std::pair<CNormalLogicalItem*, bool>(pLC, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotE, false), std::pair<CNormalLogicalItem*, bool>(pLNotC, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotE, false), std::pair<CNormalLogicalItem*, bool>(pLD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotE, false), std::pair<CNormalLogicalItem*, bool>(pLNotD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotE, false), std::pair<CNormalLogicalItem*, bool>(pLE, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotE, false), std::pair<CNormalLogicalItem*, bool>(pLNotE, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotE, false), std::pair<CNormalLogicalItem*, bool>(pLF, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotE, false), std::pair<CNormalLogicalItem*, bool>(pLNotF, false)) == false);

  // pLF with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLF, false), std::pair<CNormalLogicalItem*, bool>(pLA, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLF, false), std::pair<CNormalLogicalItem*, bool>(pLNotA, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLF, false), std::pair<CNormalLogicalItem*, bool>(pLB, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLF, false), std::pair<CNormalLogicalItem*, bool>(pLNotB, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLF, false), std::pair<CNormalLogicalItem*, bool>(pLC, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLF, false), std::pair<CNormalLogicalItem*, bool>(pLNotC, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLF, false), std::pair<CNormalLogicalItem*, bool>(pLD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLF, false), std::pair<CNormalLogicalItem*, bool>(pLNotD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLF, false), std::pair<CNormalLogicalItem*, bool>(pLE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLF, false), std::pair<CNormalLogicalItem*, bool>(pLNotE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLF, false), std::pair<CNormalLogicalItem*, bool>(pLF, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLF, false), std::pair<CNormalLogicalItem*, bool>(pLNotF, false)) == false);

  // pLNotF with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotF, false), std::pair<CNormalLogicalItem*, bool>(pLA, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotF, false), std::pair<CNormalLogicalItem*, bool>(pLNotA, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotF, false), std::pair<CNormalLogicalItem*, bool>(pLB, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotF, false), std::pair<CNormalLogicalItem*, bool>(pLNotB, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotF, false), std::pair<CNormalLogicalItem*, bool>(pLC, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotF, false), std::pair<CNormalLogicalItem*, bool>(pLNotC, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotF, false), std::pair<CNormalLogicalItem*, bool>(pLD, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotF, false), std::pair<CNormalLogicalItem*, bool>(pLNotD, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotF, false), std::pair<CNormalLogicalItem*, bool>(pLE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotF, false), std::pair<CNormalLogicalItem*, bool>(pLNotE, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotF, false), std::pair<CNormalLogicalItem*, bool>(pLF, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogicalItem*, bool>(pLNotF, false), std::pair<CNormalLogicalItem*, bool>(pLNotF, false)) == false);

  // now try the whole thing in a real set
  std::set<std::pair<CNormalLogicalItem*, bool>, CNormalLogical::SetSorter<CNormalLogicalItem> > sortedSet;
  sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLA, false));
  sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLNotA, false));
  sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLB, false));
  sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLNotB, false));
  sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLC, false));
  sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLNotC, false));
  sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLD, false));
  sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLNotD, false));
  sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLE, false));
  sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLNotE, false));
  sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLF, false));
  sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLNotF, false));
  CPPUNIT_ASSERT(sortedSet.size() == 12);
  // make sure no item is inserted twice
  CPPUNIT_ASSERT(sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLA, false)).second == false);
  CPPUNIT_ASSERT(sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLNotA, false)).second == false);
  CPPUNIT_ASSERT(sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLB, false)).second == false);
  CPPUNIT_ASSERT(sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLNotB, false)).second == false);
  CPPUNIT_ASSERT(sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLC, false)).second == false);
  CPPUNIT_ASSERT(sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLNotC, false)).second == false);
  CPPUNIT_ASSERT(sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLD, false)).second == false);
  CPPUNIT_ASSERT(sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLNotD, false)).second == false);
  CPPUNIT_ASSERT(sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLE, false)).second == false);
  CPPUNIT_ASSERT(sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLNotE, false)).second == false);
  CPPUNIT_ASSERT(sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLF, false)).second == false);
  CPPUNIT_ASSERT(sortedSet.insert(std::pair<CNormalLogicalItem*, bool>(pLNotF, false)).second == false);
  CPPUNIT_ASSERT(sortedSet.size() == 12);

  // check the order in the set
  std::set<std::pair<CNormalLogicalItem*, bool>, CNormalLogical::SetSorter<CNormalLogicalItem> >::iterator it = sortedSet.begin();
  CPPUNIT_ASSERT(it->first == pLNotD);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLC);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotF);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotB);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLD);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotC);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLF);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLB);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLA);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLE);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotA);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotE);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it == sortedSet.end());

  delete pLA;
  delete pLNotA;
  delete pLB;
  delete pLNotB;
  delete pLC;
  delete pLNotC;
  delete pLD;
  delete pLNotD;
  delete pLE;
  delete pLNotE;
  delete pLF;
  delete pLNotF;
}

void test_cnormallogical::test_SetOfSetsSorter_operator2()
{
  // create items to sort
  // A: (PI < A)           !A: (A <= PI)
  // B: (4 != A)           !B: (4 == A)
  // C: (2 == T)           !C: (2 != T)
  // D: (D != F)           !D: (D == F)
  // E: (SIN (PI*D) < X)   !E: (X <= SIN(PI*D))
  // F: (2*T^(3J) != 6.2)  !F: (2*T^(3J) == 6.2)
  std::string infix("A");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction* pA = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pA != NULL);
  infix = "PI";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction* pPI = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pPI != NULL);
  infix = "D";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction* pD = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pD != NULL);
  infix = "F";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction* pF = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pF != NULL);
  infix = "T";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction* pT = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pT != NULL);
  infix = "X";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction* pX = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pX != NULL);
  infix = "SIN(PI*D)";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction* pSIN = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pSIN != NULL);
  infix = "2*T^(3*J)";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction* pPOWER = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pPOWER != NULL);
  infix = "2";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction* pTWO = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pTWO != NULL);
  infix = "4";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction* pFOUR = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pFOUR != NULL);
  infix = "6.2";
  pTree->setInfix(infix);
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CNormalFraction* pSIX = CNormalTranslation::normAndSimplifyReptdly(pTree->getRoot());
  CPPUNIT_ASSERT(pSIX != NULL);
  delete pTree;

  // A: (PI < A)           !A: (A <= PI)
  CNormalLogicalItem* pLA = new CNormalLogicalItem();
  pLA->setType(CNormalLogicalItem::LT);
  pLA->setLeft(*pPI);
  pLA->setRight(*pA);
  CNormalLogicalItem* pLNotA = new CNormalLogicalItem();
  pLNotA->setType(CNormalLogicalItem::LE);
  pLNotA->setLeft(*pA);
  pLNotA->setRight(*pPI);
  // B: (4 != A)           !B: (4 == A)
  CNormalLogicalItem* pLB = new CNormalLogicalItem();
  pLB->setType(CNormalLogicalItem::NE);
  pLB->setLeft(*pFOUR);
  pLB->setRight(*pA);
  CNormalLogicalItem* pLNotB = new CNormalLogicalItem();
  pLNotB->setType(CNormalLogicalItem::EQ);
  pLNotB->setLeft(*pFOUR);
  pLNotB->setRight(*pA);
  // C: (2 == T)           !C: (2 != T)
  CNormalLogicalItem* pLC = new CNormalLogicalItem();
  pLC->setType(CNormalLogicalItem::EQ);
  pLC->setLeft(*pTWO);
  pLC->setRight(*pT);
  CNormalLogicalItem* pLNotC = new CNormalLogicalItem();
  pLNotC->setType(CNormalLogicalItem::NE);
  pLNotC->setLeft(*pTWO);
  pLNotC->setRight(*pT);
  // D: (D != F)           !D: (D == F)
  CNormalLogicalItem* pLD = new CNormalLogicalItem();
  pLD->setType(CNormalLogicalItem::NE);
  pLD->setLeft(*pD);
  pLD->setRight(*pF);
  CNormalLogicalItem* pLNotD = new CNormalLogicalItem();
  pLNotD->setType(CNormalLogicalItem::EQ);
  pLNotD->setLeft(*pD);
  pLNotD->setRight(*pF);
  // E: (SIN (PI*D) < X)   !E: (X <= SIN(PI*D))
  CNormalLogicalItem* pLE = new CNormalLogicalItem();
  pLE->setType(CNormalLogicalItem::LT);
  pLE->setLeft(*pSIN);
  pLE->setRight(*pX);
  CNormalLogicalItem* pLNotE = new CNormalLogicalItem();
  pLNotE->setType(CNormalLogicalItem::LE);
  pLNotE->setLeft(*pX);
  pLNotE->setRight(*pSIN);
  // F: (2*T^(3J) != 6.2)  !F: (2*T^(3J) == 6.2)
  CNormalLogicalItem* pLF = new CNormalLogicalItem();
  pLF->setType(CNormalLogicalItem::NE);
  pLF->setLeft(*pPOWER);
  pLF->setRight(*pSIX);
  CNormalLogicalItem* pLNotF = new CNormalLogicalItem();
  pLNotF->setType(CNormalLogicalItem::EQ);
  pLNotF->setLeft(*pPOWER);
  pLNotF->setRight(*pSIX);

  delete pA;
  delete pPI;
  delete pT;
  delete pX;
  delete pF;
  delete pD;
  delete pPOWER;
  delete pSIN;
  delete pTWO;
  delete pFOUR;
  delete pSIX;

  // create 12 sorted sets and add them to a Set of Sets
  CNormalLogical::ItemSet sortedSet1, sortedSet2, sortedSet3, sortedSet4, sortedSet5, sortedSet6, sortedSet7, sortedSet8, sortedSet9, sortedSet10, sortedSet11, sortedSet12;
  // add one item to each sorted set
  sortedSet1.insert(std::pair<CNormalLogicalItem*, bool>(pLA, false));
  sortedSet2.insert(std::pair<CNormalLogicalItem*, bool>(pLNotA, false));
  sortedSet3.insert(std::pair<CNormalLogicalItem*, bool>(pLB, false));
  sortedSet4.insert(std::pair<CNormalLogicalItem*, bool>(pLNotB, false));
  sortedSet5.insert(std::pair<CNormalLogicalItem*, bool>(pLC, false));
  sortedSet6.insert(std::pair<CNormalLogicalItem*, bool>(pLNotC, false));
  sortedSet7.insert(std::pair<CNormalLogicalItem*, bool>(pLD, false));
  sortedSet8.insert(std::pair<CNormalLogicalItem*, bool>(pLNotD, false));
  sortedSet9.insert(std::pair<CNormalLogicalItem*, bool>(pLE, false));
  sortedSet10.insert(std::pair<CNormalLogicalItem*, bool>(pLNotE, false));
  sortedSet11.insert(std::pair<CNormalLogicalItem*, bool>(pLF, false));
  sortedSet12.insert(std::pair<CNormalLogicalItem*, bool>(pLNotF, false));

  // check the sets agains each other
  CNormalLogical::SetOfSetsSorter<CNormalLogicalItem> sorter;
  // sortedSet1 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet2 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet3 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet4 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet5 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == true);

  // sortedSet6 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet7 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet8 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == true);

  // sortedSet9 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet10 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet11 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet12 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // test with several entries per ItemSet
  // add one item to each sorted set
  sortedSet1.clear();
  sortedSet2.clear();
  sortedSet3.clear();
  sortedSet4.clear();
  sortedSet5.clear();
  sortedSet6.clear();
  sortedSet7.clear();
  sortedSet8.clear();
  sortedSet9.clear();
  sortedSet10.clear();
  sortedSet11.clear();
  sortedSet12.clear();

  // fill set1 with 6 items and check if they are in the right order
  sortedSet1.insert(std::pair<CNormalLogicalItem*, bool>(pLA, false));
  sortedSet1.insert(std::pair<CNormalLogicalItem*, bool>(pLNotB, false));
  sortedSet1.insert(std::pair<CNormalLogicalItem*, bool>(pLE, false));
  sortedSet1.insert(std::pair<CNormalLogicalItem*, bool>(pLD, false));
  sortedSet1.insert(std::pair<CNormalLogicalItem*, bool>(pLNotC, false));
  sortedSet1.insert(std::pair<CNormalLogicalItem*, bool>(pLF, false));
  CNormalLogical::ItemSet::iterator it = sortedSet1.begin();
  CPPUNIT_ASSERT(it->first == pLNotB);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLD);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotC);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLF);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLA);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLE);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it == sortedSet1.end());

  // fill set2 with 6 items and check if they are in the right order
  sortedSet2.insert(std::pair<CNormalLogicalItem*, bool>(pLA, false));
  sortedSet2.insert(std::pair<CNormalLogicalItem*, bool>(pLNotB, false));
  sortedSet2.insert(std::pair<CNormalLogicalItem*, bool>(pLE, false));
  sortedSet2.insert(std::pair<CNormalLogicalItem*, bool>(pLNotD, false));
  sortedSet2.insert(std::pair<CNormalLogicalItem*, bool>(pLC, false));
  sortedSet2.insert(std::pair<CNormalLogicalItem*, bool>(pLNotF, false));
  it = sortedSet2.begin();
  CPPUNIT_ASSERT(it->first == pLNotD);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLC);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotF);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotB);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLA);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLE);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it == sortedSet2.end());

  // fill set3 with 6 items and check if they are in the right order
  sortedSet3.insert(std::pair<CNormalLogicalItem*, bool>(pLNotA, false));
  sortedSet3.insert(std::pair<CNormalLogicalItem*, bool>(pLNotB, false));
  sortedSet3.insert(std::pair<CNormalLogicalItem*, bool>(pLE, false));
  sortedSet3.insert(std::pair<CNormalLogicalItem*, bool>(pLNotD, false));
  sortedSet3.insert(std::pair<CNormalLogicalItem*, bool>(pLNotC, false));
  sortedSet3.insert(std::pair<CNormalLogicalItem*, bool>(pLNotF, false));
  it = sortedSet3.begin();
  CPPUNIT_ASSERT(it->first == pLNotD);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotF);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotB);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotC);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLE);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotA);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it == sortedSet3.end());

  // fill set4 with 6 items and check if they are in the right order
  sortedSet4.insert(std::pair<CNormalLogicalItem*, bool>(pLA, false));
  sortedSet4.insert(std::pair<CNormalLogicalItem*, bool>(pLB, false));
  sortedSet4.insert(std::pair<CNormalLogicalItem*, bool>(pLE, false));
  sortedSet4.insert(std::pair<CNormalLogicalItem*, bool>(pLNotD, false));
  sortedSet4.insert(std::pair<CNormalLogicalItem*, bool>(pLNotC, false));
  sortedSet4.insert(std::pair<CNormalLogicalItem*, bool>(pLNotF, false));
  it = sortedSet4.begin();
  CPPUNIT_ASSERT(it->first == pLNotD);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotF);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotC);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLB);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLA);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLE);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it == sortedSet4.end());

  // fill set5 with 6 items and check if they are in the right order
  sortedSet5.insert(std::pair<CNormalLogicalItem*, bool>(pLA, false));
  sortedSet5.insert(std::pair<CNormalLogicalItem*, bool>(pLNotB, false));
  sortedSet5.insert(std::pair<CNormalLogicalItem*, bool>(pLNotE, false));
  sortedSet5.insert(std::pair<CNormalLogicalItem*, bool>(pLNotD, false));
  sortedSet5.insert(std::pair<CNormalLogicalItem*, bool>(pLC, false));
  sortedSet5.insert(std::pair<CNormalLogicalItem*, bool>(pLF, false));
  it = sortedSet5.begin();
  CPPUNIT_ASSERT(it->first == pLNotD);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLC);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotB);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLF);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLA);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotE);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it == sortedSet5.end());

  // fill set6 with 6 items and check if they are in the right order
  sortedSet6.insert(std::pair<CNormalLogicalItem*, bool>(pLA, false));
  sortedSet6.insert(std::pair<CNormalLogicalItem*, bool>(pLB, false));
  sortedSet6.insert(std::pair<CNormalLogicalItem*, bool>(pLNotE, false));
  sortedSet6.insert(std::pair<CNormalLogicalItem*, bool>(pLNotD, false));
  sortedSet6.insert(std::pair<CNormalLogicalItem*, bool>(pLC, false));
  sortedSet6.insert(std::pair<CNormalLogicalItem*, bool>(pLF, false));
  it = sortedSet6.begin();
  CPPUNIT_ASSERT(it->first == pLNotD);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLC);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLF);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLB);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLA);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotE);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it == sortedSet6.end());

  // fill set7 with 6 items and check if they are in the right order
  sortedSet7.insert(std::pair<CNormalLogicalItem*, bool>(pLA, false));
  sortedSet7.insert(std::pair<CNormalLogicalItem*, bool>(pLNotB, false));
  sortedSet7.insert(std::pair<CNormalLogicalItem*, bool>(pLE, false));
  sortedSet7.insert(std::pair<CNormalLogicalItem*, bool>(pLNotD, false));
  sortedSet7.insert(std::pair<CNormalLogicalItem*, bool>(pLNotC, false));
  sortedSet7.insert(std::pair<CNormalLogicalItem*, bool>(pLF, false));
  it = sortedSet7.begin();
  CPPUNIT_ASSERT(it->first == pLNotD);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotB);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotC);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLF);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLA);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLE);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it == sortedSet7.end());

  // fill set8 with 6 items and check if they are in the right order
  sortedSet8.insert(std::pair<CNormalLogicalItem*, bool>(pLA, false));
  sortedSet8.insert(std::pair<CNormalLogicalItem*, bool>(pLNotB, false));
  sortedSet8.insert(std::pair<CNormalLogicalItem*, bool>(pLNotE, false));
  sortedSet8.insert(std::pair<CNormalLogicalItem*, bool>(pLD, false));
  sortedSet8.insert(std::pair<CNormalLogicalItem*, bool>(pLNotC, false));
  sortedSet8.insert(std::pair<CNormalLogicalItem*, bool>(pLF, false));
  it = sortedSet8.begin();
  CPPUNIT_ASSERT(it->first == pLNotB);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLD);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotC);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLF);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLA);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotE);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it == sortedSet8.end());

  // fill set9 with 6 items and check if they are in the right order
  sortedSet9.insert(std::pair<CNormalLogicalItem*, bool>(pLA, false));
  sortedSet9.insert(std::pair<CNormalLogicalItem*, bool>(pLNotB, false));
  sortedSet9.insert(std::pair<CNormalLogicalItem*, bool>(pLE, false));
  sortedSet9.insert(std::pair<CNormalLogicalItem*, bool>(pLD, false));
  sortedSet9.insert(std::pair<CNormalLogicalItem*, bool>(pLC, false));
  sortedSet9.insert(std::pair<CNormalLogicalItem*, bool>(pLF, false));
  it = sortedSet9.begin();
  CPPUNIT_ASSERT(it->first == pLC);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotB);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLD);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLF);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLA);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLE);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it == sortedSet9.end());

  // fill set10 with 6 items and check if they are in the right order
  sortedSet10.insert(std::pair<CNormalLogicalItem*, bool>(pLA, false));
  sortedSet10.insert(std::pair<CNormalLogicalItem*, bool>(pLNotB, false));
  sortedSet10.insert(std::pair<CNormalLogicalItem*, bool>(pLE, false));
  sortedSet10.insert(std::pair<CNormalLogicalItem*, bool>(pLD, false));
  sortedSet10.insert(std::pair<CNormalLogicalItem*, bool>(pLC, false));
  sortedSet10.insert(std::pair<CNormalLogicalItem*, bool>(pLNotF, false));
  it = sortedSet10.begin();
  CPPUNIT_ASSERT(it->first == pLC);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotF);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotB);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLD);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLA);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLE);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it == sortedSet10.end());

  // fill set11 with 6 items and check if they are in the right order
  sortedSet11.insert(std::pair<CNormalLogicalItem*, bool>(pLA, false));
  sortedSet11.insert(std::pair<CNormalLogicalItem*, bool>(pLB, false));
  sortedSet11.insert(std::pair<CNormalLogicalItem*, bool>(pLE, false));
  sortedSet11.insert(std::pair<CNormalLogicalItem*, bool>(pLD, false));
  sortedSet11.insert(std::pair<CNormalLogicalItem*, bool>(pLNotC, false));
  sortedSet11.insert(std::pair<CNormalLogicalItem*, bool>(pLF, false));
  it = sortedSet11.begin();
  CPPUNIT_ASSERT(it->first == pLD);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotC);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLF);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLB);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLA);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLE);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it == sortedSet11.end());

  // fill set12 with 6 items and check if they are in the right order
  sortedSet12.insert(std::pair<CNormalLogicalItem*, bool>(pLA, false));
  sortedSet12.insert(std::pair<CNormalLogicalItem*, bool>(pLNotB, false));
  sortedSet12.insert(std::pair<CNormalLogicalItem*, bool>(pLE, false));
  sortedSet12.insert(std::pair<CNormalLogicalItem*, bool>(pLNotD, false));
  sortedSet12.insert(std::pair<CNormalLogicalItem*, bool>(pLC, false));
  sortedSet12.insert(std::pair<CNormalLogicalItem*, bool>(pLF, false));
  it = sortedSet12.begin();
  CPPUNIT_ASSERT(it->first == pLNotD);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLC);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLNotB);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLF);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLA);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it->first == pLE);
  CPPUNIT_ASSERT(it->second == false);
  ++it;
  CPPUNIT_ASSERT(it == sortedSet12.end());

  // now we compare the sets against each other

  // sortedSet1 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet2 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == true);

  // sortedSet3 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet4 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet5 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet6 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet7 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet8 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet9 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet10 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet11 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // sortedSet12 with the rest
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false)) == false);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false)) == true);
  CPPUNIT_ASSERT(sorter(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false), std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false)) == false);

  // now test the whole thing in a real set
  CNormalLogical::ItemSetOfSets sset;
  sset.insert(std::pair<CNormalLogical::ItemSet, bool>(sortedSet1, false));
  sset.insert(std::pair<CNormalLogical::ItemSet, bool>(sortedSet2, false));
  sset.insert(std::pair<CNormalLogical::ItemSet, bool>(sortedSet3, false));
  sset.insert(std::pair<CNormalLogical::ItemSet, bool>(sortedSet4, false));
  sset.insert(std::pair<CNormalLogical::ItemSet, bool>(sortedSet5, false));
  sset.insert(std::pair<CNormalLogical::ItemSet, bool>(sortedSet6, false));
  sset.insert(std::pair<CNormalLogical::ItemSet, bool>(sortedSet7, false));
  sset.insert(std::pair<CNormalLogical::ItemSet, bool>(sortedSet8, false));
  sset.insert(std::pair<CNormalLogical::ItemSet, bool>(sortedSet9, false));
  sset.insert(std::pair<CNormalLogical::ItemSet, bool>(sortedSet10, false));
  sset.insert(std::pair<CNormalLogical::ItemSet, bool>(sortedSet11, false));
  sset.insert(std::pair<CNormalLogical::ItemSet, bool>(sortedSet12, false));
  CPPUNIT_ASSERT(sset.size() == 12);
  CNormalLogical::ItemSetOfSets::iterator sit = sset.begin();
  CPPUNIT_ASSERT(sit->first == sortedSet2);
  CPPUNIT_ASSERT(sit->second == false);
  ++sit;
  CPPUNIT_ASSERT(sit->first == sortedSet12);
  CPPUNIT_ASSERT(sit->second == false);
  ++sit;
  CPPUNIT_ASSERT(sit->first == sortedSet5);
  CPPUNIT_ASSERT(sit->second == false);
  ++sit;
  CPPUNIT_ASSERT(sit->first == sortedSet6);
  CPPUNIT_ASSERT(sit->second == false);
  ++sit;
  CPPUNIT_ASSERT(sit->first == sortedSet3);
  CPPUNIT_ASSERT(sit->second == false);
  ++sit;
  CPPUNIT_ASSERT(sit->first == sortedSet4);
  CPPUNIT_ASSERT(sit->second == false);
  ++sit;
  CPPUNIT_ASSERT(sit->first == sortedSet7);
  CPPUNIT_ASSERT(sit->second == false);
  ++sit;
  CPPUNIT_ASSERT(sit->first == sortedSet10);
  CPPUNIT_ASSERT(sit->second == false);
  ++sit;
  CPPUNIT_ASSERT(sit->first == sortedSet9);
  CPPUNIT_ASSERT(sit->second == false);
  ++sit;
  CPPUNIT_ASSERT(sit->first == sortedSet1);
  CPPUNIT_ASSERT(sit->second == false);
  ++sit;
  CPPUNIT_ASSERT(sit->first == sortedSet8);
  CPPUNIT_ASSERT(sit->second == false);
  ++sit;
  CPPUNIT_ASSERT(sit->first == sortedSet11);
  CPPUNIT_ASSERT(sit->second == false);
  ++sit;
  CPPUNIT_ASSERT(sit == sset.end());

  delete pLA;
  delete pLNotA;
  delete pLB;
  delete pLNotB;
  delete pLC;
  delete pLNotC;
  delete pLD;
  delete pLNotD;
  delete pLE;
  delete pLNotE;
  delete pLF;
  delete pLNotF;
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
