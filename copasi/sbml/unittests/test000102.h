// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000102_H__
#define TEST_000102_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CDataModel;

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

  CDataModel* pDataModel;

public:
  void setUp();

  void tearDown();

  void test_bug1741();
};

#endif /* TEST000102_H__ */
