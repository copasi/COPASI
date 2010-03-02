// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000088.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/02 16:16:29 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000088_H__
#define TEST_000088_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CCopasiDataModel;

class test000088 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000088);

  CPPUNIT_TEST(test_import_assignment_without_expression);
  CPPUNIT_TEST(test_import_initialassignment_without_expression);
  CPPUNIT_TEST(test_import_eventassignment_without_expression);

  CPPUNIT_TEST_SUITE_END();

protected:
  static CCopasiDataModel* pCOPASIDATAMODEL;
  static const char* MODEL_STRING1;
  static const char* MODEL_STRING2;
  static const char* MODEL_STRING3;

public:
  void setUp();

  void tearDown();

  void test_import_assignment_without_expression();
  void test_import_initialassignment_without_expression();
  void test_import_eventassignment_without_expression();
};

#endif /* TEST000088_H__ */
