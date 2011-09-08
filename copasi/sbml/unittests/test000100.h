// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000100.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/09/08 09:25:34 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
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

class CCopasiDataModel;

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

  CCopasiDataModel* pDataModel;

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
