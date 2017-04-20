// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000104_H__
#define TEST_000104_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CDataModel;

// test for bug 1744
// COPASI crashes if an SBML level 3 model is imported that
// uses an extends unit id in the model element that is not defined
// later in the unit definitions

class test000104 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000104);
  CPPUNIT_TEST(test_bug1744);
  CPPUNIT_TEST_SUITE_END();

protected:
  // SBML model for the test
  static const char* SBML_STRING;

  CDataModel* pDataModel;

public:
  void setUp();

  void tearDown();

  void test_bug1744();
};

#endif /* TEST000104_H__ */
