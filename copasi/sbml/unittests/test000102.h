// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000102.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/12/01 17:05:18 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000102_H__
#define TEST_000102_H__


#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CCopasiDataModel;

// libsbml will not add units to unit definitions of Level 3 documents
// if not all attributes are explicitely set.
// Prior versions of the exporter did not set the multiplier on all units and therefore
// most units were not exported correctly to Level 3.


class test000102 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000102);
  CPPUNIT_TEST(test_bug1741);
  CPPUNIT_TEST_SUITE_END();

protected:
  // SBML model for the test
  static const char* SBML_STRING;

  CCopasiDataModel* pDataModel;

public:
  void setUp();

  void tearDown();

  void test_bug1741();

};

#endif /* TEST000102_H__ */
