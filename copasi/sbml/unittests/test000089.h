// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000089.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/02 17:48:33 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000089_H__
#define TEST_000089_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CCopasiDataModel;

// test for bug 1412

class test000089 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000089);

  CPPUNIT_TEST(test_bug1412);

  CPPUNIT_TEST_SUITE_END();

protected:
  static CCopasiDataModel* pCOPASIDATAMODEL;
  static const char* MODEL_STRING1;

public:
  void setUp();

  void tearDown();

  void test_bug1412();
};

#endif /* TEST000089_H__ */
