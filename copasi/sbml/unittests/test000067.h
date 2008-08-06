// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000067.h,v $
//   $Revision: 1.1.2.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/08/06 17:09:18 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
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

  public:
    void setUp();

    void tearDown();

    // tests with SBML files
    void test_bug1060();
  };

#endif // TEST000067_H__
