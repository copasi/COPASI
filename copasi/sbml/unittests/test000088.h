// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000088_H__
#define TEST_000088_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CDataModel;

class test000088 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000088);

  CPPUNIT_TEST(test_import_assignment_without_expression);
  CPPUNIT_TEST(test_import_initialassignment_without_expression);
  CPPUNIT_TEST(test_import_eventassignment_without_expression);

  CPPUNIT_TEST_SUITE_END();

protected:
  static CDataModel* pCOPASIDATAMODEL;
  static const char* MODEL_STRING1;
  static const char* MODEL_STRING2;
  static const char* MODEL_STRING3;

public:
  void setUp();

  void tearDown();

  void test_import_assignment_without_expression();
  void test_import_initialassignment_without_expression();
  void test_import_eventassignment_without_expression();
};

#endif /* TEST000088_H__ */
