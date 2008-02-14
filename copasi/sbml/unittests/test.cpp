// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test.cpp,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/02/14 10:52:44 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <cppunit/ui/text/TestRunner.h>

#include "test000001.hpp"

#define COPASI_MAIN

#include "copasi.h"

int main(int /*argc*/, char ** /*argv*/)
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(test000001::suite());
  runner.run();
  return 0;
}
