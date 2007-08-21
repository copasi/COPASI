// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_cnormallogical.hpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/08/21 15:29:42 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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
    CPPUNIT_TEST(test_SetOfSetsSorter_operator);
    CPPUNIT_TEST(test_SetSorter_LogicalItem);
    CPPUNIT_TEST(test_SetOfSetsSorter_LogicalItem);
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();

    void tearDown();

    void test_SetSorter_operator();
    void test_SetOfSetsSorter_operator();
    void test_SetSorter_LogicalItem();
    void test_SetOfSetsSorter_LogicalItem();
  };

#endif /* TEST_CNORMALLOGICAL_HPP__ */
