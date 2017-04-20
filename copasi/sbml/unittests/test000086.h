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

#ifndef TEST_000086_H__
#define TEST_000086_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

/**
 * Test for 0D compartment unit import and export.
 */

class CDataModel;

class test000086 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000086);
  CPPUNIT_TEST(test_import_compartment_units_1);
  CPPUNIT_TEST(test_import_compartment_units_2);
  CPPUNIT_TEST(test_import_compartment_units_3);
  CPPUNIT_TEST(test_import_compartment_units_4);
  CPPUNIT_TEST(test_import_compartment_units_5);
  CPPUNIT_TEST(test_import_compartment_units_6);
  CPPUNIT_TEST(test_import_compartment_units_7);
  CPPUNIT_TEST(test_import_compartment_units_8);
  CPPUNIT_TEST(test_import_compartment_units_9);
  CPPUNIT_TEST(test_import_compartment_units_10);
  CPPUNIT_TEST(test_import_compartment_units_11);
  CPPUNIT_TEST_SUITE_END();

protected:
  // models for import test

  // L2V1 model with no global length unit
  // and local unit length
  static const char* MODEL_STRING1;
  // L2V1 model with no global length unit
  // and local unit m
  static const char* MODEL_STRING2;
  // L2V1 model with no global length unit
  // and no local length unit
  static const char* MODEL_STRING3;
  // L2V1 model with no global length unit
  // and a local length unit of "volume"
  static const char* MODEL_STRING4;
  // L2V1 model with no global length unit
  // and a local length unit of "area"
  static const char* MODEL_STRING5;
  // L2V1 model with no global length unit
  // and a local length unit of "dimensionless"
  static const char* MODEL_STRING6;
  // L2V1 model with no global length unit
  // and a local length unit of "m^2"
  static const char* MODEL_STRING7;
  // L2V1 model with no global length unit
  // and a local length unit of "dimensionless"
  static const char* MODEL_STRING8;
  // L2V1 model with no global length unit
  // and a local length unit of "mole"
  static const char* MODEL_STRING9;
  // L2V1 model with no global length unit
  // and a local length unit of "substance"
  static const char* MODEL_STRING10;
  // L2V1 model with two compartments
  // one has no unit set, the other uses dimensionless
  static const char* MODEL_STRING11;

  static CDataModel* pCOPASIDATAMODEL;

public:
  void setUp();

  void tearDown();

  void test_import_compartment_units_1();
  void test_import_compartment_units_2();
  void test_import_compartment_units_3();
  void test_import_compartment_units_4();
  void test_import_compartment_units_5();
  void test_import_compartment_units_6();
  void test_import_compartment_units_7();
  void test_import_compartment_units_8();
  void test_import_compartment_units_9();
  void test_import_compartment_units_10();
  void test_import_compartment_units_11();
};

#endif /* TEST000086_H__ */
