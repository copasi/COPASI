// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_depth_first_iterator.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:26:44 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_DEPTH_FIRST_ITERATOR_H__
#define TEST_DEPTH_FIRST_ITERATOR_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CNormalFraction;
class CNormalLogicalItem;

class test_depth_first_iterator : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test_depth_first_iterator);
  CPPUNIT_TEST(test_dfi);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();

  void tearDown();

  void test_dfi();

};

#endif /* TEST_DEPTH_FIRST_ITERATOR_H__ */
