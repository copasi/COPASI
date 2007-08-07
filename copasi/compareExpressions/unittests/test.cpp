// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/08/07 16:49:50 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <cppunit/ui/text/TestRunner.h>

#include "test_node_conversion.hpp"
#include "test_expression_comparison.hpp"
#include "test_normalform.hpp"

#define COPASI_MAIN

#include "copasi.h"

int main(int /*argc*/, char ** /*argv*/)
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(test_normalform::suite());
  //runner.addTest(test_node_conversion::suite());
  //runner.addTest(test_expression_comparison::suite());
  runner.run();
  return 0;
}
