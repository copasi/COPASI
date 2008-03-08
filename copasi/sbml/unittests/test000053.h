// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000053.h,v $
//   $Revision: 1.1.2.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/03/08 21:27:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000053_H__
#define TEST_000053_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class test000053 : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(test000053);
    CPPUNIT_TEST(test1_bug1000);
    CPPUNIT_TEST(test2_bug1000);
    CPPUNIT_TEST(test3_bug1000);
    CPPUNIT_TEST(test4_bug1000);
    CPPUNIT_TEST(test5_bug1000);
    CPPUNIT_TEST_SUITE_END();

  protected:
    static const char* MODEL_STRING_1;
    static const char* MODEL_STRING_2;
    static const char* MODEL_STRING_3;
    static const char* MODEL_STRING_4;
    static const char* MODEL_STRING_5;

  public:
    void setUp();

    void tearDown();

    void test1_bug1000();
    void test2_bug1000();
    void test3_bug1000();
    void test4_bug1000();
    void test5_bug1000();
  };

#endif /* TEST000053_H__ */
