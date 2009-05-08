// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000084.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/05/08 15:54:06 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000084_H__
#define TEST_000084_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

/**
 * Test for 2D compartment unit import and export.
 */

class CCopasiDataModel;

class test000084 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000084);
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
  CPPUNIT_TEST(test_import_compartment_units_12);
  CPPUNIT_TEST(test_import_compartment_units_13);
  CPPUNIT_TEST(test_import_compartment_units_14);
  CPPUNIT_TEST(test_import_compartment_units_15);
  CPPUNIT_TEST(test_import_compartment_units_16);
  CPPUNIT_TEST(test_import_compartment_units_17);
  CPPUNIT_TEST(test_import_compartment_units_18);
  CPPUNIT_TEST(test_import_compartment_units_19);
  CPPUNIT_TEST(test_import_compartment_units_20);
  CPPUNIT_TEST(test_import_compartment_units_21);
  CPPUNIT_TEST_SUITE_END();

protected:
  // models for import test

  // L2V1 model with global area unit "nm^2"
  static const char* MODEL_STRING1;
  // L2V1 model with global area unit "10e-4*m^2"
  static const char* MODEL_STRING2;
  // L2V1 model with global area unit "mole"
  static const char* MODEL_STRING3;
  // L2V1 model with global area unit "nm^2"
  // and local unit mm^2
  static const char* MODEL_STRING4;
  // L2V1 model with global area unit "nm^2"
  // and local unit mole
  static const char* MODEL_STRING5;
  // L2V1 model with global area unit "mole"
  // and local unit nm^2
  static const char* MODEL_STRING6;
  // L2V1 model with no global area unit
  // and local unit nm^2
  static const char* MODEL_STRING7;
  // L2V1 model with no global area unit
  // and local unit area
  static const char* MODEL_STRING8;
  // L2V1 model with no global area unit
  // and local unit m^2
  static const char* MODEL_STRING9;
  // L2V1 model with no global area unit
  // and no local area unit
  static const char* MODEL_STRING10;
  // L2V1 model with no global area unit
  // and a local area unit of "volume"
  static const char* MODEL_STRING11;
  // L2V1 model with no global area unit
  // and a local area unit of "length"
  static const char* MODEL_STRING12;
  // L2V1 model with no global area unit
  // and a local area unit of "dimensionless"
  static const char* MODEL_STRING13;
  // L2V1 model with no global area unit
  // and a local area unit of "m^3"
  static const char* MODEL_STRING14;
  // L2V1 model with no global area unit
  // and a local area unit of "m"
  static const char* MODEL_STRING15;
  // L2V1 model with no global area unit
  // and a local area unit of "mole"
  static const char* MODEL_STRING16;
  // L2V1 model with no global area unit
  // and a local area unit of "substance"
  static const char* MODEL_STRING17;
  // L2V1 model with two compartments
  // one has no unit set, the other uses area
  static const char* MODEL_STRING18;
  // L2V1 model with two compartments
  // one has no unit set, the other uses m^2
  static const char* MODEL_STRING19;
  // L2V1 model with two compartments
  // one has no unit set, the other uses nm^2
  static const char* MODEL_STRING20;
  // L2V1 model with two compartments
  // one uses nm^2, the other has no unit set
  static const char* MODEL_STRING21;

  static CCopasiDataModel* pCOPASIDATAMODEL;

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
  void test_import_compartment_units_12();
  void test_import_compartment_units_13();
  void test_import_compartment_units_14();
  void test_import_compartment_units_15();
  void test_import_compartment_units_16();
  void test_import_compartment_units_17();
  void test_import_compartment_units_18();
  void test_import_compartment_units_19();
  void test_import_compartment_units_20();
  void test_import_compartment_units_21();
};

#endif /* TEST000084_H__ */
