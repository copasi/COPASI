// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_node_conversion.hpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/04/23 15:03:22 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
    CPPUNIT_TEST(test_0001);
    CPPUNIT_TEST(test_0002);
    CPPUNIT_TEST(test_0003);
    CPPUNIT_TEST(test_0004);
    CPPUNIT_TEST(test_0005);
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();
    void test_0001();
    void test_0002();
    void test_0003();
    void test_0004();
    void test_0005();
  };

#endif /*TEST_NODE_CONVERSION_HPP__ */
