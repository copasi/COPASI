// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000017.hpp,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/02/15 13:11:24 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000017_HPP__
#define TEST_000017_HPP__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class test000017 : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(test000017);
    CPPUNIT_TEST(test_references_to_species);
    CPPUNIT_TEST_SUITE_END();

  protected:
    static const char* MODEL_STRING;

  public:
    void setUp();

    void tearDown();

    void test_references_to_species();
  };

#endif /* TEST000017_HPP__ */
