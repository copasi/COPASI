// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000089_H__
#define TEST_000089_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CDataModel;

// test for bug 1412

class test000089 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000089);

  CPPUNIT_TEST(test_bug1412);

  CPPUNIT_TEST_SUITE_END();

protected:
  static CDataModel* pCOPASIDATAMODEL;
  static const char* MODEL_STRING1;

public:
  void setUp();

  void tearDown();

  void test_bug1412();
};

#endif /* TEST000089_H__ */
