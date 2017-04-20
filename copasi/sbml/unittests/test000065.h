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

#ifndef TEST_000065_H__
#define TEST_000065_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CDataModel;

// This tests is for the fix for Bug 1015

class test000065 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000065);
  CPPUNIT_TEST(test_import_reaction_with_unsuitable_kinetic_1);
  CPPUNIT_TEST(test_import_reaction_with_unsuitable_kinetic_2);
  CPPUNIT_TEST_SUITE_END();

protected:
  static const char* MODEL_STRING1;
  static const char* MODEL_STRING2;
  static CDataModel* pCOPASIDATAMODEL;

public:
  void setUp();

  void tearDown();

  void test_import_reaction_with_unsuitable_kinetic_1();
  void test_import_reaction_with_unsuitable_kinetic_2();
};

#endif /* TEST000065_H__ */
