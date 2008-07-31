// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test.cpp,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/07/31 13:40:48 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.
#define COPASI_MAIN

#include <cppunit/ui/text/TestRunner.h>

#define COPASI_MAIN

#include "copasi.h"

#include "test_node_conversion.hpp"
#include "test_expression_comparison.hpp"
#include "test_normalform.hpp"
#include "test_cnormallogical.hpp"

int main(int /*argc*/, char ** /*argv*/)
{
  CppUnit::TextUi::TestRunner runner;
  //runner.addTest(test_cnormallogical::suite());
  runner.addTest(test_normalform::suite());
  //runner.addTest(test_node_conversion::suite());
  //runner.addTest(test_expression_comparison::suite());
  runner.run();
  return 0;
}
