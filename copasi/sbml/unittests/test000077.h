// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000077.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/07/01 15:50:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000077_H__
#define TEST_000077_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

// Bug 1129
// Test import and export of dimensionless units

class CCopasiDataModel;

class test000077 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000077);
  // correct dimensionless model
  CPPUNIT_TEST(test_import_dimensionless_1);

  // correct dimensionless model, but with multipliers and scales
  CPPUNIT_TEST(test_import_dimensionless_2);

  // incorrect volume unit
  CPPUNIT_TEST(test_import_dimensionless_3);

  // incorrect time unit
  CPPUNIT_TEST(test_import_dimensionless_4);

  // incorrect quantity unit
  CPPUNIT_TEST(test_import_dimensionless_5);

  // test for export of dimensionless
  CPPUNIT_TEST(test_export_dimensionless);
  CPPUNIT_TEST_SUITE_END();

protected:
  static CCopasiDataModel* pCOPASIDATAMODEL;
  static const char* MODEL_STRING1;
  static const char* MODEL_STRING2;
  static const char* MODEL_STRING3;
  static const char* MODEL_STRING4;
  static const char* MODEL_STRING5;
  static const char* MODEL_STRING6;

public:
  void setUp();

  void tearDown();

  void test_import_dimensionless_1();
  void test_import_dimensionless_2();
  void test_import_dimensionless_3();
  void test_import_dimensionless_4();
  void test_import_dimensionless_5();
  void test_export_dimensionless();
};

#endif /* TEST000077_H__ */
