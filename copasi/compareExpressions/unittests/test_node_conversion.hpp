// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_node_conversion.hpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/08/07 16:49:50 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef TEST_NODE_CONVERSION_HPP__
#define TEST_NODE_CONVERSION_HPP__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class test_node_conversion : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(test_node_conversion);
    CPPUNIT_TEST(test_convert_cnormalsum_1);
    CPPUNIT_TEST(test_convert_cnormalsum_2);
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();

    void tearDown();

    void test_convert_cnormalsum_1();

    void test_convert_cnormalsum_2();
  };

#endif /*TEST_NODE_CONVERSION_HPP__ */
