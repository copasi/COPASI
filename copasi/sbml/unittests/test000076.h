// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
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

class CDataModel;

class test000076 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000076);
  CPPUNIT_TEST(test_bug1035_1);
  CPPUNIT_TEST(test_bug1035_2);
  CPPUNIT_TEST(test_bug1035_3);
  CPPUNIT_TEST_SUITE_END();

protected:
  static CDataModel* pCOPASIDATAMODEL;
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
