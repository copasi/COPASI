// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000079_H__
#define TEST_000079_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CDataModel;

class test000079 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000079);

  CPPUNIT_TEST(test_import_fast);

  CPPUNIT_TEST_SUITE_END();

protected:
  static CDataModel* pCOPASIDATAMODEL;
  static const char* MODEL_STRING1;

public:
  void setUp();

  void tearDown();

  void test_import_fast();
};

#endif /* TEST000079_H__ */
