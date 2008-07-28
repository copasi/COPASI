// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_cnormallogical.hpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/07/28 16:28:18 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef TEST_CNORMALLOGICAL_HPP__
#define TEST_CNORMALLOGICAL_HPP__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

#include "compareExpressions/CNormalLogical.h"

class CNormalFraction;

class test_cnormallogical : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(test_cnormallogical);
    CPPUNIT_TEST(test_SetSorter_operator);
    CPPUNIT_TEST(test_SetSorter_operator2);
    CPPUNIT_TEST(test_SetOfSetsSorter_operator);
    CPPUNIT_TEST(test_SetOfSetsSorter_operator2);
    CPPUNIT_TEST(test_SetSorter_LogicalItem);
    CPPUNIT_TEST(test_SetOfSetsSorter_LogicalItem);
    CPPUNIT_TEST(test_simplify_1);
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();

    void tearDown();

    void test_SetSorter_operator();
    void test_SetOfSetsSorter_operator();
    void test_SetSorter_operator2();
    void test_SetOfSetsSorter_operator2();
    void test_SetSorter_LogicalItem();
    void test_SetOfSetsSorter_LogicalItem();
    void test_simplify_1();
  };

#endif /* TEST_CNORMALLOGICAL_HPP__ */
