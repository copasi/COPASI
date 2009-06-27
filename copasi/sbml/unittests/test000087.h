// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000087.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/06/27 09:52:11 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000087_H__
#define TEST_000087_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CCopasiDataModel;

class test000087 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000087);

  CPPUNIT_TEST(test_import_reaction_flux_reference_1);
  CPPUNIT_TEST(test_import_reaction_flux_reference_2);
  CPPUNIT_TEST(test_import_reaction_flux_reference_3);
  CPPUNIT_TEST(test_export_reaction_flux_reference_1);
  CPPUNIT_TEST(test_export_reaction_flux_reference_2);
  CPPUNIT_TEST(test_simulate_reaction_flux_reference_1);

  CPPUNIT_TEST_SUITE_END();

protected:
  static CCopasiDataModel* pCOPASIDATAMODEL;
  static const char* MODEL_STRING1;
  static const char* MODEL_STRING2;
  static const char* MODEL_STRING3;
  static const char* MODEL_STRING4;
  static const char* MODEL_STRING5;

public:
  void setUp();

  void tearDown();

  void test_import_reaction_flux_reference_1();
  void test_import_reaction_flux_reference_2();
  void test_import_reaction_flux_reference_3();
  void test_export_reaction_flux_reference_1();
  void test_export_reaction_flux_reference_2();
  void test_simulate_reaction_flux_reference_1();
};

#endif /* TEST000087_H__ */
