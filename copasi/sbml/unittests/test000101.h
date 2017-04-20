// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000101_H__
#define TEST_000101_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

/**
 * Test for bug 1740.
 * Importing an SBML model with an empty reaction
 * will lead to a crash if the model is exported to SBML Level 3 Version 1 twice.
 */

class CDataModel;

class test000101 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000101);
  CPPUNIT_TEST(test_bug1740);
  CPPUNIT_TEST_SUITE_END();

protected:
  // SBML model for the test
  static const char* SBML_STRING;

  CDataModel* pDataModel;

  static struct sigaction* pNewAct;
  static struct sigaction* pOldAct;

  static void abort_handler(int);

public:
  void setUp();

  void tearDown();

  void test_bug1740();
};

#endif /* TEST000101_H__ */
