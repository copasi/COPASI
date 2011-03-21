// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000096.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/21 15:39:31 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000096_H__
#define TEST_000096_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

/**
 * Tests for setting notes on SBML models
 */


class test000096 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000096);
  CPPUNIT_TEST(test_export_model_notes_1);
  CPPUNIT_TEST(test_export_model_notes_2);
  CPPUNIT_TEST(test_export_model_notes_3);
  CPPUNIT_TEST(test_export_model_notes_4);
  CPPUNIT_TEST(test_export_model_notes_5);
  CPPUNIT_TEST(test_export_model_notes_6);
  CPPUNIT_TEST_SUITE_END();

protected:
  static const char* NOTES_STRING_1;
  static const char* NOTES_STRING_2;
  static const char* NOTES_STRING_3;
  static const char* NOTES_STRING_4;
  static const char* NOTES_STRING_5;
  static const char* NOTES_STRING_6;


public:
  void setUp();

  void tearDown();

  void test_export_model_notes_1();
  void test_export_model_notes_2();
  void test_export_model_notes_3();
  void test_export_model_notes_4();
  void test_export_model_notes_5();
  void test_export_model_notes_6();
};

#endif /* TEST000096_H__ */
