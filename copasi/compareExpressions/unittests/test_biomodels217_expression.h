// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_biomodels217_expression.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 22:16:01 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_BIOMODELS217_EXPRESSION_H_
#define TEST_BIOMODELS217_EXPRESSION_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>


class test_biomodels217_expression : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test_biomodels217_expression);
  CPPUNIT_TEST(test_term_num1);
  CPPUNIT_TEST(test_term_num2);
  CPPUNIT_TEST(test_term_num3);
  CPPUNIT_TEST(test_term_num4);
  CPPUNIT_TEST(test_term_num5);
  CPPUNIT_TEST(test_term_num6);
  CPPUNIT_TEST(test_term_num7);
  CPPUNIT_TEST(test_term_den1);
  CPPUNIT_TEST(test_term_den2);
  CPPUNIT_TEST(test_term_den3);
  CPPUNIT_TEST(test_term_den4);
  CPPUNIT_TEST(test_term_den5);
  CPPUNIT_TEST(test_term_den6);
  CPPUNIT_TEST(test_term_den7);

  CPPUNIT_TEST(test_term_den12);
  CPPUNIT_TEST(test_term_den123);
  CPPUNIT_TEST(test_term_den1234);
  CPPUNIT_TEST(test_term_den12345);
  CPPUNIT_TEST(test_term_den123456);
  CPPUNIT_TEST(test_term_den1234567);
  CPPUNIT_TEST(test_term_den67);
  CPPUNIT_TEST(test_term_den56);
  CPPUNIT_TEST(test_term_den456);
  CPPUNIT_TEST(test_term_den3456);
  CPPUNIT_TEST(test_term_den356);
  CPPUNIT_TEST(test_term_den346);
  CPPUNIT_TEST(test_term_den36);

  CPPUNIT_TEST_SUITE_END();

protected:
  // numerator
  static const char* factor_num;
  static const char* term_num1;
  static const char* term_num2;
  static const char* term_num3;
  static const char* term_num4;
  static const char* term_num5;
  static const char* term_num6;
  static const char* term_num7;

  static const char* factor_den;
  static const char* term_den1;
  static const char* term_den2;
  static const char* term_den3;
  static const char* term_den4;
  static const char* term_den5;
  static const char* term_den6;
  static const char* term_den7;


public:
  void setUp();

  void tearDown();

  void test_term_num1();
  void test_term_num2();
  void test_term_num3();
  void test_term_num4();
  void test_term_num5();
  void test_term_num6();
  void test_term_num7();

  void test_term_den1();
  void test_term_den2();
  void test_term_den3();
  void test_term_den4();
  void test_term_den5();
  void test_term_den6();
  void test_term_den7();

  void test_term_den12();
  void test_term_den123();
  void test_term_den1234();
  void test_term_den12345();
  void test_term_den123456();
  void test_term_den1234567();
  void test_term_den67();
  void test_term_den56();
  void test_term_den456();
  void test_term_den3456();
  void test_term_den356();
  void test_term_den346();
  void test_term_den36();


};

#endif // TEST_BIOMODELS217_EXPRESSION_H_

