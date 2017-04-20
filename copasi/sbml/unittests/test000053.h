// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000053_H__
#define TEST_000053_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CDataModel;

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
  static CDataModel* pCOPASIDATAMODEL;

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
