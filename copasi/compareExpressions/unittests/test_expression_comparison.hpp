// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_expression_comparison.hpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:26:44 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef TEST_EXPRESSION_COMPARISON_HPP_
#define TEST_EXPRESSION_COMPARISON_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string>

class test_expression_comparison : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test_expression_comparison);
  CPPUNIT_TEST(test_fraction_to_a_power);
  CPPUNIT_TEST(test_allosteric_inhibition);
  CPPUNIT_TEST(test_hyperbolic_modifier);
  CPPUNIT_TEST(test_substrate_activation);
  CPPUNIT_TEST(test_specific_activation_reversible);
  CPPUNIT_TEST(test_ordered_bi_bi);
  CPPUNIT_TEST(test_reversible_hill);
  CPPUNIT_TEST(test_reversible_hill_one_modifier);
  CPPUNIT_TEST(test_reversible_hill_two_modifiers);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();

  void tearDown();

  bool are_expressions_equal(const std::string& expr1, const std::string& expr2, const std::string& filename = "", bool oldStyle = false);

  void test_fraction_to_a_power();
  void test_allosteric_inhibition();
  void test_hyperbolic_modifier();
  void test_substrate_activation();
  void test_specific_activation_reversible();
  void test_ordered_bi_bi();
  void test_reversible_hill();
  void test_reversible_hill_one_modifier();
  void test_reversible_hill_two_modifiers();
};

#endif /*TEST_EXPRESSION_COMPARISON_HPP_ */
