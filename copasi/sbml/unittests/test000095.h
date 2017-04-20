// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000095_H__
#define TEST_000095_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

/**
 * Test for event import/export and especially the handling of the
 * delayAssignment flag and the corresponding flag in SBML.
 */

class CDataModel;

class test000095 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000095);
  CPPUNIT_TEST(test_import_l3_event_1);
  CPPUNIT_TEST(test_import_l3_event_2);
  CPPUNIT_TEST(test_import_l3_event_3);
  CPPUNIT_TEST(test_import_l3_event_4);
  CPPUNIT_TEST(test_import_l3_event_5);
  CPPUNIT_TEST_SUITE_END();

protected:
  // models for import test

  // event with event priority
  static const char* MODEL_STRING1;

  // event with initial trigger value
  static const char* MODEL_STRING2;

  // event with initial value and priority
  static const char* MODEL_STRING3;

  // event non-persistent trigger
  static const char* MODEL_STRING4;

  // event without initial value and priority
  static const char* MODEL_STRING5;

  static CDataModel* pCOPASIDATAMODEL;

public:
  void setUp();

  void tearDown();

  void test_import_l3_event_1();
  void test_import_l3_event_2();
  void test_import_l3_event_3();
  void test_import_l3_event_4();
  void test_import_l3_event_5();
};

#endif /* TEST000095_H__ */
