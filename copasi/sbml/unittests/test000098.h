// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000098_H__
#define TEST_000098_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

/**
 * Tests for dealing with notes on different  model elements
 */

class CDataModel;

class test000098 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000098);
  CPPUNIT_TEST(test_import_notes);
  CPPUNIT_TEST(test_export_notes);
  CPPUNIT_TEST_SUITE_END();

protected:
  // SBML model with notes
  static const char* SBML_MODEL_1;
  // COPASI model with notes
  static const char* CPS_MODEL_1;

  CDataModel* pDataModel;

public:
  void setUp();

  void tearDown();

  // check if we can import notes on all elements
  void test_import_notes();

  // check if we can export notes on all elements
  void test_export_notes();
};

#endif /* TEST000098_H__ */
