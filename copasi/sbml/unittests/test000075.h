// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000075.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/10/09 12:46:18 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000075_H__
#define TEST_000075_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

// Test for import of explicitely time dependent function defintitions
// Problems related to this are also tracked in Bug 1093.
// This test also covers the bugs described there.

class test000075 : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(test000075);
    CPPUNIT_TEST(test_import_time_dependent_function_definition);
    CPPUNIT_TEST_SUITE_END();

  protected:
    static const char* MODEL_STRING1;

  public:
    void setUp();

    void tearDown();

    void test_import_time_dependent_function_definition();
  };

#endif /* TEST000075_H__ */
