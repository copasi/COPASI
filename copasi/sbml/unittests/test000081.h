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

#ifndef TEST_000081_H__
#define TEST_000081_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

// Bug 1205
// If a CPS file was created from an SBML file and the user added some
// elements in COPASI and reexported it, the reexported model was missing
// elements because ids were assigned several times and elements got
// overwritten on reexport.

class CDataModel;

class test000081 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000081);

  CPPUNIT_TEST(test_bug1205);

  CPPUNIT_TEST_SUITE_END();

protected:
  static CDataModel* pCOPASIDATAMODEL;
  static const char* MODEL_STRING1;

public:
  void setUp();

  void tearDown();

  void test_bug1205();
};

#endif /* TEST000081_H__ */
