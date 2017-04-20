// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000099_H__
#define TEST_000099_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

/**
 * Tests for dealing with notes on different  model elements
 */

class CDataModel;

class test000099 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000099);
  CPPUNIT_TEST(test_bug1675);
  CPPUNIT_TEST_SUITE_END();

protected:
  // incorrect SBML model
  static const char* SBML_MODEL_BAD;

  // correct SBML model with same name as incorrect model
  static const char* SBML_MODEL_GOOD;

  CDataModel* pDataModel;

public:
  void setUp();

  void tearDown();

  // test for bug 1675
  // After an import failed, the model that was created during import should be gone
  void test_bug1675();
};

#endif /* TEST000099_H__ */
