// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000012.hpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:42:28 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000012_HPP__
#define TEST_000012_HPP__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CCopasiDataModel;

class test000012 : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(test000012);
    CPPUNIT_TEST(test_references_to_species);
    CPPUNIT_TEST_SUITE_END();

  protected:
    static const char* MODEL_STRING;
    static CCopasiDataModel* pCOPASIDATAMODEL;

  public:
    void setUp();

    void tearDown();

    void test_references_to_species();
  };

#endif /* TEST000012_HPP__ */
