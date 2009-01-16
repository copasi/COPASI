// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_compare_utilities.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/01/16 16:29:00 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_COMPARE_UTILITIES_H__
#define TEST_COMPARE_UTILITIES_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class test_compare_utilities : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(test_compare_utilities);
    CPPUNIT_TEST(test_copasi_function_expansion);
    CPPUNIT_TEST_SUITE_END();

  protected:
    static const char* MODEL_STRING1;

  public:
    void setUp();

    void tearDown();

    void test_copasi_function_expansion();
  };

#endif /* TEST_COMPARE_UTILITIES_H__ */
