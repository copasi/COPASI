// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000091.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/05 11:34:27 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000091_H__
#define TEST_000091_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CCopasiDataModel;

class test000091 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000091);
  CPPUNIT_TEST(test_delay_in_kinetic_law);
  CPPUNIT_TEST(test_delay_in_kinetic_law_local_parameter);
  CPPUNIT_TEST_SUITE_END();

protected:
  static const char* MODEL_STRING1;
  static const char* MODEL_STRING2;
  static CCopasiDataModel* pCOPASIDATAMODEL;

public:
  void setUp();

  void tearDown();

  void test_delay_in_kinetic_law();
  void test_delay_in_kinetic_law_local_parameter();
};

#endif /* TEST000091_H__ */
