// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef TEST_000063_H__
#define TEST_000063_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class Model;
class CDataModel;

/**
 * This test check if a kinetic law without math element is imported
 * with the correct warning.
 */

class test000063 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000063);
  CPPUNIT_TEST(test_events_1);
  CPPUNIT_TEST_SUITE_END();

protected:
  static const char* MODEL_STRING1;
  static const char* MODEL_STRING2;
  static const char* MODEL_STRING3;
  static const char* MODEL_STRING4;
  static const char* MODEL_STRING5;
  static const char* MODEL_STRING6;
  static const char* MODEL_STRING7;
  static const char* MODEL_STRING8;
  static const char* MODEL_STRING9;
  static const char* MODEL_STRING10;
  static const char* MODEL_STRING11;
  static const char* MODEL_STRING12;
  static const char* MODEL_STRING13;
  static const char* MODEL_STRING14;
  static const char* MODEL_STRING15;
  static const char* MODEL_STRING16;
  static const char* MODEL_STRING17;
  static CDataModel* pCOPASIDATAMODEL;

public:
  void setUp();

  void tearDown();

  void test_events_1();
};

#endif /* TEST000063_H__ */
