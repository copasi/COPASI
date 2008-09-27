// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000071.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/27 15:00:32 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000071_H__
#define TEST_000071_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

// Bug 1085

class test000071 : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(test000071);
    CPPUNIT_TEST(test_bug1085);
    CPPUNIT_TEST_SUITE_END();

  protected:
    static const char* MODEL_STRING1;

  public:
    void setUp();

    void tearDown();

    void test_bug1085();
  };

#endif /* TEST000071_H__ */
