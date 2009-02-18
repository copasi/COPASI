// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000065.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:41:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000065_H__
#define TEST_000065_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CCopasiDataModel;

// This tests is for the fix for Bug 1015

class test000065 : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(test000065);
    CPPUNIT_TEST(test_import_reaction_with_unsuitable_kinetic_1);
    CPPUNIT_TEST(test_import_reaction_with_unsuitable_kinetic_2);
    CPPUNIT_TEST_SUITE_END();

  protected:
    static const char* MODEL_STRING1;
    static const char* MODEL_STRING2;
    static CCopasiDataModel* pCOPASIDATAMODEL;

  public:
    void setUp();

    void tearDown();

    void test_import_reaction_with_unsuitable_kinetic_1();
    void test_import_reaction_with_unsuitable_kinetic_2();
  };

#endif /* TEST000065_H__ */
