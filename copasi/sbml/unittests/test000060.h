// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000060.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/05/05 10:50:18 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000060_H__
#define TEST_000060_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class Model;

/**
 * This test checks if the constant and boundaryCondition flags are set
 * correctly when a FIXED metabolite is changed back to status REACTIONS.
 *
 */

class test000060 : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(test000060);
    CPPUNIT_TEST(test_bug_1026);
    CPPUNIT_TEST_SUITE_END();

  protected:
    static const char* MODEL_STRING1;

  public:
    void setUp();

    void tearDown();

    void test_bug_1026();
  };

#endif /* TEST000060_H__ */
