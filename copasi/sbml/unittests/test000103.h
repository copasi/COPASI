// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000103_H__
#define TEST_000103_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CDataModel;

// in earlier version of COPASI, setting the SBML id on a model prior to exporting it
// had no effect (bug 1743)

class test000103 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000103);
  CPPUNIT_TEST(test_bug1743_l2);
  CPPUNIT_TEST(test_bug1743_l3);
  CPPUNIT_TEST_SUITE_END();

protected:
  // SBML model for the test
  static const char* SBML_STRING;

  CDataModel* pDataModel;

public:
  void setUp();

  void tearDown();

  void test_bug1743_l2();
  void test_bug1743_l3();
};

#endif /* TEST000103_H__ */
