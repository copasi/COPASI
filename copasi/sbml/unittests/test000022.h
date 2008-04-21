// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000022.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/02/20 19:13:07 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000022_H__
#define TEST_000022_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class test000022 : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(test000022);
    CPPUNIT_TEST(test_hasOnlySubstanceUnits);
    CPPUNIT_TEST_SUITE_END();

  protected:
    static const char* MODEL_STRING;

  public:
    void setUp();

    void tearDown();

    void test_hasOnlySubstanceUnits();
  };

#endif /* TEST000022_H__ */
