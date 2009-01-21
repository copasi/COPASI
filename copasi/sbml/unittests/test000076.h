// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000076.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/01/21 20:22:44 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000076_H__
#define TEST_000076_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

// Bug 1035
// Test export of models with references to local variables

class test000076 : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(test000076);
    CPPUNIT_TEST(test_bug1035_1);
    CPPUNIT_TEST(test_bug1035_2);
    CPPUNIT_TEST(test_bug1035_3);
    CPPUNIT_TEST_SUITE_END();

  protected:
    static const char* MODEL_STRING1;
    static const char* MODEL_STRING2;
    static const char* MODEL_STRING3;

  public:
    void setUp();

    void tearDown();

    void test_bug1035_1();
    void test_bug1035_2();
    void test_bug1035_3();
  };

#endif /* TEST000076_H__ */
