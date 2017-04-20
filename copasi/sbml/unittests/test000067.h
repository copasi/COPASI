// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000067_H__
#define TEST_000067_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class Model;
class CDataModel;

/**
 * This test is for Bug 1060.
 */

class test000067 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000067);
  CPPUNIT_TEST(test_bug1060);
  CPPUNIT_TEST_SUITE_END();

protected:
  static const char* MODEL_STRING1;
  static CDataModel* pCOPASIDATAMODEL;

public:
  void setUp();

  void tearDown();

  // tests with SBML files
  void test_bug1060();
};

#endif // TEST000067_H__
