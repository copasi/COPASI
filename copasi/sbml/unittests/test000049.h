// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000049.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/02/27 13:18:11 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000049_H__
#define TEST_000049_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class test000049 : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(test000049);
    CPPUNIT_TEST(test_bug894);
    CPPUNIT_TEST_SUITE_END();

  protected:
    static const char* MODEL_STRING;

  public:
    void setUp();

    void tearDown();

    void test_bug894();
  };

#endif /* TEST000049_H__ */
