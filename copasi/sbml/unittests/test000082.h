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

#ifndef TEST_000082_H__
#define TEST_000082_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

/**
 * Test for event import/export and especially the handling of the
 * delayAssignment flag and the corresponding flag in SBML.
 */

class CDataModel;

class test000082 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000082);
  CPPUNIT_TEST(test_import_delayAssignment_1);
  CPPUNIT_TEST(test_import_delayAssignment_2);
  CPPUNIT_TEST(test_import_delayAssignment_3);
  CPPUNIT_TEST(test_import_delayAssignment_4);
  CPPUNIT_TEST(test_import_delayAssignment_5);
  CPPUNIT_TEST(test_import_delayAssignment_6);
  CPPUNIT_TEST(test_import_delayAssignment_7);
  CPPUNIT_TEST(test_import_delayAssignment_8);

  CPPUNIT_TEST(test_export_delayAssignment_1);
  CPPUNIT_TEST(test_export_delayAssignment_2);
  CPPUNIT_TEST(test_export_delayAssignment_3);
  CPPUNIT_TEST(test_export_delayAssignment_4);
  CPPUNIT_TEST(test_export_delayAssignment_5);
  CPPUNIT_TEST(test_export_delayAssignment_6);
  CPPUNIT_TEST_SUITE_END();

protected:
  // models for import test

  // L2V1 model with event and delay
  static const char* MODEL_STRING1;

  // L2V1 model with event and no delay
  static const char* MODEL_STRING2;

  // L2V4 model with event and delayEvent unset
  static const char* MODEL_STRING3;
  // L2V4 model with event and delayEvent=true
  static const char* MODEL_STRING4;
  // L2V4 model with event and delayEvent=false
  static const char* MODEL_STRING5;
  // L2V4 model without delay and delayEvent unset
  static const char* MODEL_STRING6;
  // L2V4 model without delay and delayEvent=false
  static const char* MODEL_STRING7;
  // L2V4 model without delay and delayEvent=true
  static const char* MODEL_STRING8;

  // models for export test

  // event with delayEvent=true
  static const char* MODEL_STRING101;
  // event with delayEvent=false
  static const char* MODEL_STRING102;
  // model without delay expression
  static const char* MODEL_STRING103;

  static CDataModel* pCOPASIDATAMODEL;

public:
  void setUp();

  void tearDown();

  void test_import_delayAssignment_1();
  void test_import_delayAssignment_2();
  void test_import_delayAssignment_3();
  void test_import_delayAssignment_4();
  void test_import_delayAssignment_5();
  void test_import_delayAssignment_6();
  void test_import_delayAssignment_7();
  void test_import_delayAssignment_8();

  void test_export_delayAssignment_1();
  void test_export_delayAssignment_2();
  void test_export_delayAssignment_3();
  void test_export_delayAssignment_4();
  void test_export_delayAssignment_5();
  void test_export_delayAssignment_6();
};

#endif /* TEST000082_H__ */
