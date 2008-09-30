// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000072.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/30 10:24:40 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000072_H__
#define TEST_000072_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

// Bug 1086

class test000072 : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(test000072);
    CPPUNIT_TEST(test_bug1086);
    CPPUNIT_TEST_SUITE_END();

  protected:
    static const char* MODEL_STRING1;

  public:
    void setUp();

    void tearDown();

    void test_bug1086();
  };

#endif /* TEST000072_H__ */
