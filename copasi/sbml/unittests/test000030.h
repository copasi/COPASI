// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000030.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:41:32 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000030_H__
#define TEST_000030_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CCopasiDataModel;

class test000030 : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(test000030);
    CPPUNIT_TEST(test_hasOnlySubstanceUnits);
    CPPUNIT_TEST_SUITE_END();

  protected:
    static const char* MODEL_STRING;
    static CCopasiDataModel* pCOPASIDATAMODEL;

  public:
    void setUp();

    void tearDown();

    void test_hasOnlySubstanceUnits();
  };

#endif /* TEST000030_H__ */
