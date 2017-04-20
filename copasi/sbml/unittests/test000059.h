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

#ifndef TEST_000059_H__
#define TEST_000059_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class Model;
class CDataModel;

/**
 * These tests check if all elements in an SBML model get unique ids on export,
 * even if one element that has been exported before has an id that might
 * potentially be assigned to a different element that is exported later.
 * e.g. a species being named "reaction_2"
 * These tests assume a certain order for the export of elements.
 */

class test000059 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000059);
  CPPUNIT_TEST(test_unique_id_1);
  CPPUNIT_TEST(test_unique_id_2);
  CPPUNIT_TEST(test_unique_id_3);
  CPPUNIT_TEST(test_unique_id_4);
  CPPUNIT_TEST(test_unique_id_5);
  CPPUNIT_TEST(test_unique_id_6);
  CPPUNIT_TEST(test_unique_id_7);
  CPPUNIT_TEST(test_unique_id_8);
  CPPUNIT_TEST(test_unique_id_9);
  CPPUNIT_TEST(test_unique_id_10);
  CPPUNIT_TEST(test_unique_id_11);
  CPPUNIT_TEST(test_unique_id_12);
  CPPUNIT_TEST(test_unique_id_13);
  CPPUNIT_TEST(test_unique_id_14);
  CPPUNIT_TEST(test_unique_id_15);
  CPPUNIT_TEST(test_unique_id_16);
  CPPUNIT_TEST(test_unique_id_17);
  CPPUNIT_TEST(test_unique_id_18);
  CPPUNIT_TEST(test_unique_id_19);
  CPPUNIT_TEST(test_unique_id_20);
  CPPUNIT_TEST(test_unique_id_21);
  CPPUNIT_TEST(test_unique_id_21_2);
  CPPUNIT_TEST(test_unique_id_22);
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
  static const char* MODEL_STRING11;
  static const char* MODEL_STRING12;
  static const char* MODEL_STRING13;
  static const char* MODEL_STRING14;
  static const char* MODEL_STRING15;
  static const char* MODEL_STRING16;
  static const char* MODEL_STRING17;
  static const char* MODEL_STRING18;
  static const char* MODEL_STRING19;
  static const char* MODEL_STRING20;
  static const char* MODEL_STRING21;
  static const char* MODEL_STRING22;
  static CDataModel* pCOPASIDATAMODEL;

public:
  static bool checkIfIdsUnique(const Model* pSBMLModel);

  void setUp();

  void tearDown();

  // tests with SBML files
  void test_unique_id_1();
  void test_unique_id_2();
  void test_unique_id_3();
  void test_unique_id_4();
  void test_unique_id_5();
  void test_unique_id_6();
  void test_unique_id_7();
  void test_unique_id_8();
  void test_unique_id_9();
  void test_unique_id_10();
  void test_unique_id_17();
  void test_unique_id_18();
  void test_unique_id_19();
  void test_unique_id_20();

  // test with COPASI models
  void test_unique_id_11();
  void test_unique_id_12();
  void test_unique_id_13();
  void test_unique_id_14();
  void test_unique_id_15();
  void test_unique_id_16();

  // test for bug 1060
  void test_unique_id_21();
  void test_unique_id_21_2();

  // additional test for exporting references to local reaction parameters
  // (Bug 1035)
  void test_unique_id_22();
};

#endif /* TEST000059_H__ */
