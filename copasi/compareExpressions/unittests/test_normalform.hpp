// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_normalform.hpp,v $
//   $Revision: 1.20 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/03/09 21:27:09 $
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

#ifndef TEST_NORMALFORM_HPP__
#define TEST_NORMALFORM_HPP__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CNormalFraction;
class CNormalLogicalItem;

class test_normalform : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test_normalform);
  CPPUNIT_TEST(test_item_number);
  CPPUNIT_TEST(test_item_variable);
  CPPUNIT_TEST(test_item_constant);
  CPPUNIT_TEST(test_item_function);

  CPPUNIT_TEST(test_sum_numbers);
  CPPUNIT_TEST(test_sum_variables);
  CPPUNIT_TEST(test_sum_constants);
  CPPUNIT_TEST(test_sum_functions);
  CPPUNIT_TEST(test_sum_functions_reversed);
  CPPUNIT_TEST(test_sum_mixed_1);
  CPPUNIT_TEST(test_sum_mixed_1_reversed);
  CPPUNIT_TEST(test_sum_mixed_2);
  CPPUNIT_TEST(test_sum_mixed_2_reversed);

  CPPUNIT_TEST(test_product_numbers);
  CPPUNIT_TEST(test_product_variables);
  CPPUNIT_TEST(test_product_variables_reversed);
  CPPUNIT_TEST(test_product_constants);
  CPPUNIT_TEST(test_product_constants_reversed);
  CPPUNIT_TEST(test_product_functions);
  CPPUNIT_TEST(test_product_functions_reversed);
  CPPUNIT_TEST(test_product_mixed_1);
  CPPUNIT_TEST(test_product_mixed_1_reversed);
  CPPUNIT_TEST(test_product_mixed_2);
  CPPUNIT_TEST(test_product_mixed_2_reversed);

  CPPUNIT_TEST(test_fraction_numbers);
  CPPUNIT_TEST(test_fraction_variables);
  CPPUNIT_TEST(test_fraction_constants);
  CPPUNIT_TEST(test_fraction_functions);
  CPPUNIT_TEST(test_fraction_mixed_1);
  CPPUNIT_TEST(test_fraction_mixed_2);

  CPPUNIT_TEST(test_itempower_numbers);
  CPPUNIT_TEST(test_itempower_variables);
  CPPUNIT_TEST(test_itempower_constants);
  CPPUNIT_TEST(test_itempower_functions);

  CPPUNIT_TEST(test_generalpower_number_and_variable);
  CPPUNIT_TEST(test_generalpower_variable_and_variable);
  CPPUNIT_TEST(test_generalpower_function_and_function);
  CPPUNIT_TEST(test_generalpower_constant_and_constant);
  CPPUNIT_TEST(test_generalpower_mixed_1);
  CPPUNIT_TEST(test_generalpower_mixed_2);
  CPPUNIT_TEST(test_generalpower_mixed_3);
  CPPUNIT_TEST(test_generalpower_mixed_4);

  CPPUNIT_TEST(test_generalmodulus_number_and_variable);
  CPPUNIT_TEST(test_generalmodulus_variable_and_variable);
  CPPUNIT_TEST(test_generalmodulus_function_and_function);
  CPPUNIT_TEST(test_generalmodulus_constant_and_constant);
  CPPUNIT_TEST(test_generalmodulus_mixed_1);
  CPPUNIT_TEST(test_generalmodulus_mixed_2);
  CPPUNIT_TEST(test_generalmodulus_mixed_3);
  CPPUNIT_TEST(test_generalmodulus_mixed_4);

  CPPUNIT_TEST(test_simple_stepwise_numbers);
  CPPUNIT_TEST(test_simple_stepwise_fractions);
  CPPUNIT_TEST(test_simple_nested_stepwise_numbers);
  CPPUNIT_TEST(test_simple_nested_stepwise_fractions);
  CPPUNIT_TEST(test_nested_stepwise_numbers_2levels_1);
  CPPUNIT_TEST(test_nested_stepwise_numbers_2levels_2);
  CPPUNIT_TEST(test_nested_stepwise_numbers_2levels_3);
  CPPUNIT_TEST(test_nested_stepwise_fractions_3levels);
  CPPUNIT_TEST(test_nested_fractions_itempowers_1level);

  CPPUNIT_TEST(test_nested_fractions_itempower_generalpower_1level);
  CPPUNIT_TEST(test_nested_fractions_itempower_generalpower_1level_2);
  CPPUNIT_TEST(test_nested_fractions_generalpower_itempower_1level);
  CPPUNIT_TEST(test_nested_fractions_generalpowers_1level);

  CPPUNIT_TEST(test_nested_fractions_itempowers_2level);
  CPPUNIT_TEST(test_nested_fractions_itempower_generalpower_2level);
  CPPUNIT_TEST(test_nested_fractions_generalpower_itempower_2level);
  CPPUNIT_TEST(test_nested_fractions_generalpowers_2level);

  CPPUNIT_TEST(test_nested_fractions_itempowers_2level_complex);
  CPPUNIT_TEST(test_nested_fractions_itempower_generalpower_2level_complex);
  CPPUNIT_TEST(test_nested_fractions_generalpower_itempower_2level_complex);
  CPPUNIT_TEST(test_nested_fractions_generalpowers_2level_complex);

  CPPUNIT_TEST(test_sum_with_nested_fractions_1);
  CPPUNIT_TEST(test_product_of_sums_1);
  CPPUNIT_TEST(test_product_of_sums_2);

  // test for bugs
  CPPUNIT_TEST(test_cancel_bug_1);
  CPPUNIT_TEST(test_cancel_bug_2);
  CPPUNIT_TEST(test_cancel_bug_3);
  CPPUNIT_TEST(test_cancel_bug_4);
  CPPUNIT_TEST(test_cancel_bug_5);
  CPPUNIT_TEST(test_bug_1);
  CPPUNIT_TEST(test_bug_2);
  CPPUNIT_TEST(test_bug_3);
  CPPUNIT_TEST(test_bug_4);
  CPPUNIT_TEST(test_bug_5);
  CPPUNIT_TEST(test_bug_6);
  CPPUNIT_TEST(test_bug_7);
  CPPUNIT_TEST(test_bug_8);
  CPPUNIT_TEST(test_bug_9);
  //CPPUNIT_TEST(test_bug_10);
  CPPUNIT_TEST(test_bug_11);

  CPPUNIT_TEST_SUITE_END();

protected:
  const CNormalFraction* pFraction;

public:
  void setUp();

  void tearDown();

  void test_item_number();
  void test_item_variable();
  void test_item_constant();
  void test_item_function();

  void test_sum_numbers();
  void test_sum_variables();
  void test_sum_constants();
  void test_sum_functions();
  void test_sum_functions_reversed();
  void test_sum_mixed_1();
  void test_sum_mixed_1_reversed();
  void test_sum_mixed_2();
  void test_sum_mixed_2_reversed();

  void test_product_numbers();
  void test_product_variables();
  void test_product_variables_reversed();
  void test_product_constants();
  void test_product_constants_reversed();
  void test_product_functions();
  void test_product_functions_reversed();
  void test_product_mixed_1();
  void test_product_mixed_1_reversed();
  void test_product_mixed_2();
  void test_product_mixed_2_reversed();

  void test_fraction_numbers();
  void test_fraction_variables();
  void test_fraction_constants();
  void test_fraction_functions();
  void test_fraction_mixed_1();
  void test_fraction_mixed_2();

  void test_itempower_numbers();
  void test_itempower_variables();
  void test_itempower_constants();
  void test_itempower_functions();

  void test_generalpower_number_and_variable();
  void test_generalpower_variable_and_variable();
  void test_generalpower_function_and_function();
  void test_generalpower_constant_and_constant();
  void test_generalpower_mixed_1();
  void test_generalpower_mixed_2();
  void test_generalpower_mixed_3();
  void test_generalpower_mixed_4();

  void test_generalmodulus_number_and_variable();
  void test_generalmodulus_variable_and_variable();
  void test_generalmodulus_function_and_function();
  void test_generalmodulus_constant_and_constant();
  void test_generalmodulus_mixed_1();
  void test_generalmodulus_mixed_2();
  void test_generalmodulus_mixed_3();
  void test_generalmodulus_mixed_4();

  void test_simple_stepwise_numbers();
  void test_simple_stepwise_fractions();
  void test_simple_nested_stepwise_numbers();
  void test_simple_nested_stepwise_fractions();
  void test_nested_stepwise_numbers_2levels_1();
  void test_nested_stepwise_numbers_2levels_2();
  void test_nested_stepwise_numbers_2levels_3();
  void test_nested_stepwise_fractions_3levels();

  void test_nested_fractions_itempowers_1level();
  void test_nested_fractions_itempower_generalpower_1level();
  void test_nested_fractions_itempower_generalpower_1level_2();
  void test_nested_fractions_generalpower_itempower_1level();
  void test_nested_fractions_generalpowers_1level();

  void test_nested_fractions_itempowers_2level();
  void test_nested_fractions_itempower_generalpower_2level();
  void test_nested_fractions_generalpower_itempower_2level();
  void test_nested_fractions_generalpowers_2level();

  void test_nested_fractions_itempowers_2level_complex();
  void test_nested_fractions_itempower_generalpower_2level_complex();
  void test_nested_fractions_generalpower_itempower_2level_complex();
  void test_nested_fractions_generalpowers_2level_complex();

  void test_sum_with_nested_fractions_1();
  void test_product_of_sums_1();
  void test_product_of_sums_2();

  // L * Ks^(1+n) -> Ks * L * Ks^n
  void test_cancel_bug_1();

  // L * Ks^(n-1) -> Ks^-1 * L * Ks^n
  void test_cancel_bug_2();

  // L * Ks^(1+n-x+3) -> Ks^4 * L * Ks^n * Ks^(-x)
  void test_cancel_bug_3();

  // L * Ks^(-1-n+x+3) -> (K^2 L * Ks^x) / * Ks^n
  void test_cancel_bug_4();

  // L * Ks^(-n-1) -> (L / (Ks * Ks^n)
  void test_cancel_bug_5();

  // A/B - C/D -> (A*D - C*B) / (B*D))
  void test_bug_1();

  // A/B + C/D -> (A*D + C*B) / (B*D))
  void test_bug_2();

  // (B*(1/B)) -> 1
  void test_bug_3();

  // B*(1-(1/B)) -> B-1
  void test_bug_4();

  // B*(1-D/(B*E)) -> (B*E-D)/E
  void test_bug_5();


  // A*(B/C)*(1-D/(B*E)) -> (-A*D+A*B*E)/(C*E)
  void test_bug_6();

  // (1/F)^3/(1/F) -> 1/F^2
  void test_bug_7();

  // (A/F)^3/(A/F) -> A^2/F^2
  void test_bug_8();

  // (A*(-(B/C)+D))/(E*(1+(B/F)+(D/E))) -> (-A*B*F+A*C*D)/(B*C*E+C*D*F+C*E*F)
  void test_bug_9();

  // very nasty equation from reaction vdead in Biomodels 217
  void test_bug_10();

  //  "Kd*Kms*Vr*a*product*-1+(Kms*Modifier*Vr*b*product*-1+(Kd*Kmp*Vf*a*substrate+Kmp*Modifier*Vf*b*substrate))"
  void test_bug_11();

  // PI < A
  bool check_LogicalItemA(const CNormalLogicalItem* pLogicalItem);

  // 4 != A
  bool check_LogicalItemB(const CNormalLogicalItem* pLogicalItem);

  //2==T
  bool check_LogicalItemC(const CNormalLogicalItem* pLogicalItem);

  // D == F
  bool check_LogicalItemD(const CNormalLogicalItem* pLogicalItem);

  // SIN(PI*D) < X
  bool check_LogicalItemE(const CNormalLogicalItem* pLogicalItem);

  // 2*T^(3*J) != 6.2
  bool check_LogicalItemF(const CNormalLogicalItem* pLogicalItem);

  // A <= PI
  bool check_LogicalItemNotA(const CNormalLogicalItem* pLogicalItem);

  // 4 == A
  bool check_LogicalItemNotB(const CNormalLogicalItem* pLogicalItem);

  //2!=T
  bool check_LogicalItemNotC(const CNormalLogicalItem* pLogicalItem);

  // D != F
  bool check_LogicalItemNotD(const CNormalLogicalItem* pLogicalItem);

  // X <= SIN(PI*D)
  bool check_LogicalItemNotE(const CNormalLogicalItem* pLogicalItem);

  // 2*T^(3*J) == 6.2
  bool check_LogicalItemNotF(const CNormalLogicalItem* pLogicalItem);


};

#endif /* TEST_NORMALFORM_HPP__ */
