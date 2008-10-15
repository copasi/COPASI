// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_simplify.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/10/15 15:42:33 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_SIMPLIFY_H__
#define TEST_SIMPLIFY_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class test_simplify : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(test_simplify);
    CPPUNIT_TEST(test_simplify_1);
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();

    void tearDown();

    void test_simplify_1();
  };

#endif // TEST_SIMPLIFY_H__
