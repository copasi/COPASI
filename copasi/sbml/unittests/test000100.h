// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000100_H__
#define TEST_000100_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

/**
 * Test for exporting Level 3 models before or after Level 2 models
 */

class CDataModel;

class test000100 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000100);
  CPPUNIT_TEST(test_bug1692_1);
  CPPUNIT_TEST(test_bug1692_2);
  CPPUNIT_TEST_SUITE_END();

protected:
  // CPS model for the test
  // Since the bug only occurs if functions are exported,
  // function definitions are crucial for this test
  static const char* CPS_STRING;

  CDataModel* pDataModel;

public:
  void setUp();

  void tearDown();

  // test whether exporting an SBML Level 3 file after an SBML Level 2 file
  // succeeds
  void test_bug1692_1();

  // test whether exporting an SBML Level 3 file before an SBML Level 2 file
  // succeeds
  void test_bug1692_2();
};

#endif /* TEST000100_H__ */
