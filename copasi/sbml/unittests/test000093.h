// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000093.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:33:09 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000093_H__
#define TEST_000093_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CCopasiDataModel;

class test000093 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000093);
  CPPUNIT_TEST(test_bug1503_1);
  CPPUNIT_TEST(test_bug1503_2);
  CPPUNIT_TEST_SUITE_END();

protected:
  static const char* MODEL_STRING_1;
  static const char* MODEL_STRING_2;
  static CCopasiDataModel* pCOPASIDATAMODEL;

public:
  void setUp();

  void tearDown();

  void test_bug1503_1();
  void test_bug1503_2();
};

#endif /* TEST000093_H__ */
