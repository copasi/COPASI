// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000090.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/03 16:14:28 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000090_H__
#define TEST_000090_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CCopasiDataModel;

class test000090 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000090);
  CPPUNIT_TEST(test_delay_in_function);
  CPPUNIT_TEST_SUITE_END();

protected:
  static const char* MODEL_STRING;
  static CCopasiDataModel* pCOPASIDATAMODEL;

public:
  void setUp();

  void tearDown();

  void test_delay_in_function();
};

#endif /* TEST000090_H__ */
