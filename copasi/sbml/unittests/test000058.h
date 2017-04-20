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

#ifndef TEST_000058_H__
#define TEST_000058_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class Model;
class CDataModel;

class test000058 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000058);
  CPPUNIT_TEST(test_bug1025_1);
  CPPUNIT_TEST(test_bug1025_2);
  CPPUNIT_TEST(test_bug1025_3);
  CPPUNIT_TEST(test_bug1025_4);
  CPPUNIT_TEST(test_bug1025_5);
  CPPUNIT_TEST(test_bug1025_6);
  CPPUNIT_TEST(test_bug1025_7);
  CPPUNIT_TEST(test_bug1025_8);
  CPPUNIT_TEST(test_bug1025_9);
  CPPUNIT_TEST(test_bug1025_10);
  CPPUNIT_TEST_SUITE_END();

protected:
  static const char* MODEL_STRING;
  static const char* MODEL_STRING2;
  static CDataModel* pCOPASIDATAMODEL;

  bool checkIfIdsUnique(const Model* pSBMLModel);

public:
  void setUp();

  void tearDown();

  // tests with SBML files
  // for reaction id
  void test_bug1025_1();
  // for compartment id
  void test_bug1025_2();
  // for species id
  void test_bug1025_3();
  // for parameter id
  void test_bug1025_4();
  // for function definition id
  void test_bug1025_5();

  // test with COPASI files created from an SBML file
  // for reaction id
  void test_bug1025_6();
  // for compartment id
  void test_bug1025_7();
  // for species id
  void test_bug1025_8();
  // for parameter id
  void test_bug1025_9();
  // for function definition id
  void test_bug1025_10();
};

#endif /* TEST000058_H__ */
