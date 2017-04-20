// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000091_H__
#define TEST_000091_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CDataModel;

class test000091 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000091);
  CPPUNIT_TEST(test_delay_in_kinetic_law);
  CPPUNIT_TEST(test_delay_in_kinetic_law_local_parameter);
  CPPUNIT_TEST_SUITE_END();

protected:
  static const char* MODEL_STRING1;
  static const char* MODEL_STRING2;
  static CDataModel* pCOPASIDATAMODEL;

public:
  void setUp();

  void tearDown();

  void test_delay_in_kinetic_law();
  void test_delay_in_kinetic_law_local_parameter();
};

#endif /* TEST000091_H__ */
