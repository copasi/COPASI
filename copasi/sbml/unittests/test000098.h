// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000098.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/24 16:32:32 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000098_H__
#define TEST_000098_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

/**
 * Tests for dealing with notes on different  model elements
 */

class CCopasiDataModel;

class test000098 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000098);
  CPPUNIT_TEST(test_import_notes);
  CPPUNIT_TEST(test_export_notes);
  CPPUNIT_TEST_SUITE_END();

protected:
  // SBML model with notes
  static const char* SBML_MODEL_1;
  // COPASI model with notes
  static const char* CPS_MODEL_1;

  CCopasiDataModel* pDataModel;

public:
  void setUp();

  void tearDown();

  // check if we can import notes on all elements
  void test_import_notes();

  // check if we can export notes on all elements
  void test_export_notes();

};

#endif /* TEST000098_H__ */
