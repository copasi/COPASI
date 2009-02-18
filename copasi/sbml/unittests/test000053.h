// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000053.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:41:02 $
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

class CCopasiDataModel;

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
    static CCopasiDataModel* pCOPASIDATAMODEL;

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
