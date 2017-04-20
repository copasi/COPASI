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

#ifndef TEST_000066_H__
#define TEST_000066_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CDataModel;

// test recognition of constant flux

class test000066 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000066);
  CPPUNIT_TEST(test_import_reaction_with_constant_flux);
  CPPUNIT_TEST(test_import_reaction_with_constant_flux_global_parameter);
  CPPUNIT_TEST(test_import_reaction_with_constant_flux_function);
  CPPUNIT_TEST(test_import_reaction_with_constant_flux_function_global_parameter);
  CPPUNIT_TEST(test_import_reaction_with_constant_flux_reversible);
  CPPUNIT_TEST(test_import_reaction_with_constant_flux_reversible_global_parameter);
  CPPUNIT_TEST(test_import_reaction_with_constant_flux_reversible_function);
  CPPUNIT_TEST(test_import_reaction_with_constant_flux_reversible_function_global_parameter);
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
  static CDataModel* pCOPASIDATAMODEL;

public:
  void setUp();

  void tearDown();

  void test_import_reaction_with_constant_flux();
  void test_import_reaction_with_constant_flux_function();
  void test_import_reaction_with_constant_flux_global_parameter();
  void test_import_reaction_with_constant_flux_function_global_parameter();
  void test_import_reaction_with_constant_flux_reversible();
  void test_import_reaction_with_constant_flux_reversible_function();
  void test_import_reaction_with_constant_flux_reversible_global_parameter();
  void test_import_reaction_with_constant_flux_reversible_function_global_parameter();
};

#endif /* TEST000066_H__ */
