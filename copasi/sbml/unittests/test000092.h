// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000092_H__
#define TEST_000092_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CDataModel;

class test000092 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000092);
  CPPUNIT_TEST(test_miriam_export_1);
  CPPUNIT_TEST(test_miriam_export_2);
  CPPUNIT_TEST(test_miriam_export_3);
  CPPUNIT_TEST(test_miriam_export_4);
  CPPUNIT_TEST(test_miriam_export_5);
  CPPUNIT_TEST(test_miriam_export_6);
  CPPUNIT_TEST(test_miriam_export_7);
  CPPUNIT_TEST(test_miriam_export_8);
  CPPUNIT_TEST(test_miriam_export_9);
  CPPUNIT_TEST(test_miriam_import_1);
  CPPUNIT_TEST_SUITE_END();

protected:
  static const char* MODEL_STRING1;
  static const char* MODEL_STRING2;
  static const char* MODEL_STRING3;
  static const char* MODEL_STRING4;
  static const char* MODEL_STRING5;
  static const char* MODEL_STRING6;
  static const char* MODEL_STRING7;
  static const char* MODEL_STRING8;
  static const char* MODEL_STRING9;
  static const char* MODEL_STRING10;
  static CDataModel* pCOPASIDATAMODEL;

public:
  void setUp();

  void tearDown();

  void test_miriam_export_1();
  void test_miriam_export_2();
  void test_miriam_export_3();
  void test_miriam_export_4();
  void test_miriam_export_5();
  void test_miriam_export_6();
  void test_miriam_export_7();
  void test_miriam_export_8();
  void test_miriam_export_9();
  void test_miriam_import_1();
};

#endif /* TEST000092_H__ */
