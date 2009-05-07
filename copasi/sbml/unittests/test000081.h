// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000081.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/05/07 10:50:34 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
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

class CCopasiDataModel;

class test000081 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000081);

  CPPUNIT_TEST(test_bug1205);

  CPPUNIT_TEST_SUITE_END();

protected:
  static CCopasiDataModel* pCOPASIDATAMODEL;
  static const char* MODEL_STRING1;

public:
  void setUp();

  void tearDown();

  void test_bug1205();
};

#endif /* TEST000081_H__ */
