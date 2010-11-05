// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000094.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/11/05 12:41:56 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000094_H__
#define TEST_000094_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

// these are testcases for handling SBML models with required and non-required packages

class CCopasiDataModel;

class test000094 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000094);
  CPPUNIT_TEST(test_required_package);
  CPPUNIT_TEST(test_notrequired_package);
  CPPUNIT_TEST_SUITE_END();

protected:
  static const char* MODEL_STRING1;
  static const char* MODEL_STRING2;
  static CCopasiDataModel* pCOPASIDATAMODEL;

public:
  void setUp();

  void tearDown();

  void test_required_package();
  void test_notrequired_package();
};

#endif /* TEST000094_H__ */
