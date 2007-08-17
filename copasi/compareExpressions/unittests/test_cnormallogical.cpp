// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_cnormallogical.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/08/17 13:33:08 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "test_cnormallogical.hpp"
#include "compareExpressions/CNormalLogicalItem.h"
#include "compareExpressions/CNormalChoiceLogical.h"
#include "compareExpressions/CNormalFraction.h"

void test_cnormallogical::setUp(){}

void test_cnormallogical::tearDown(){}

void test_cnormallogical::test_SetSorter_LogicalItem()
{
  CNormalLogical::ItemSet set;
  CPPUNIT_ASSERT(set.size() == 0);
  CNormalLogicalItem* pItem = new CNormalLogicalItem();

  pItem->setType(CNormalLogicalItem::TRUE);
  set.insert(std::make_pair(pItem->copy(), false));
  CPPUNIT_ASSERT(set.size() == 1);
  set.insert(std::make_pair(pItem->copy(), false));
  CPPUNIT_ASSERT(set.size() == 1);
  set.insert(std::make_pair(pItem->copy(), true));
  CPPUNIT_ASSERT(set.size() == 2);
  CNormalLogical::cleanSet(set);
  CPPUNIT_ASSERT(set.size() == 0);

  pItem->setType(CNormalLogicalItem::FALSE);
  set.insert(std::make_pair(pItem->copy(), false));
  CPPUNIT_ASSERT(set.size() == 1);
  set.insert(std::make_pair(pItem->copy(), false));
  CPPUNIT_ASSERT(set.size() == 1);
  set.insert(std::make_pair(pItem->copy(), true));
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
  set.insert(std::make_pair(pItem->copy(), false));
  CPPUNIT_ASSERT(set.size() == 1);
  set.insert(std::make_pair(pItem->copy(), false));
  CPPUNIT_ASSERT(set.size() == 1);
  set.insert(std::make_pair(pItem->copy(), true));
  CPPUNIT_ASSERT(set.size() == 2);
  CNormalLogical::cleanSet(set);
  CPPUNIT_ASSERT(set.size() == 0);
}

void test_cnormallogical::test_SetOfSetsSorter_LogicalItem()
{
  CNormalLogical::ItemSetOfSets setOfSets;
  CPPUNIT_ASSERT(setOfSets.size() == 0);
  CNormalLogical::ItemSet set;
  CNormalLogicalItem* pLogicalItem = new CNormalLogicalItem();
  pLogicalItem->setType(CNormalLogicalItem::TRUE);

  set.insert(std::make_pair(pLogicalItem->copy(), false));
  setOfSets.insert(std::make_pair(set, false));
  CPPUNIT_ASSERT(setOfSets.size() == 1);
  // add the same thing again
  CNormalLogical::cleanSet(set);
  CPPUNIT_ASSERT(set.size() == 0);
  set.insert(std::make_pair(pLogicalItem->copy(), false));
  setOfSets.insert(std::make_pair(set, false));
  CPPUNIT_ASSERT(setOfSets.size() == 1);

  CNormalLogical::cleanSet(set);
  CPPUNIT_ASSERT(set.size() == 0);
  set.insert(std::make_pair(pLogicalItem->copy(), true));
  setOfSets.insert(std::make_pair(set, false));
  CPPUNIT_ASSERT(setOfSets.size() == 2);
  // add the same thing again
  CNormalLogical::cleanSet(set);
  CPPUNIT_ASSERT(set.size() == 0);
  set.insert(std::make_pair(pLogicalItem->copy(), true));
  setOfSets.insert(std::make_pair(set, false));
  CPPUNIT_ASSERT(setOfSets.size() == 2);

  CNormalLogical::cleanSet(set);
  CPPUNIT_ASSERT(set.size() == 0);
  set.insert(std::make_pair(pLogicalItem->copy(), false));
  setOfSets.insert(std::make_pair(set, true));
  CPPUNIT_ASSERT(setOfSets.size() == 3);
  // add the same thing again
  CNormalLogical::cleanSet(set);
  CPPUNIT_ASSERT(set.size() == 0);
  set.insert(std::make_pair(pLogicalItem->copy(), false));
  setOfSets.insert(std::make_pair(set, true));
  CPPUNIT_ASSERT(setOfSets.size() == 3);

  CNormalLogical::cleanSet(set);
  CPPUNIT_ASSERT(set.size() == 0);
  set.insert(std::make_pair(pLogicalItem->copy(), true));
  setOfSets.insert(std::make_pair(set, true));
  CPPUNIT_ASSERT(setOfSets.size() == 4);
  // add the same thing again
  CNormalLogical::cleanSet(set);
  CPPUNIT_ASSERT(set.size() == 0);
  set.insert(std::make_pair(pLogicalItem->copy(), true));
  setOfSets.insert(std::make_pair(set, true));
  CPPUNIT_ASSERT(setOfSets.size() == 4);
}
