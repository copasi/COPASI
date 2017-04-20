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

#ifndef TEST_000087_H__
#define TEST_000087_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CDataModel;

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
  static CDataModel* pCOPASIDATAMODEL;
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
