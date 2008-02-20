// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test.cpp,v $
//   $Revision: 1.1.2.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/02/20 19:13:07 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <cppunit/ui/text/TestRunner.h>

#include "test000001.hpp"
#include "test000002.hpp"
#include "test000003.hpp"
#include "test000004.hpp"
#include "test000005.hpp"
#include "test000006.hpp"
#include "test000007.hpp"
#include "test000008.hpp"
#include "test000009.hpp"
#include "test000010.hpp"
#include "test000011.hpp"
#include "test000012.hpp"
#include "test000013.hpp"
#include "test000014.hpp"
#include "test000015.hpp"
#include "test000016.hpp"
#include "test000017.hpp"
#include "test000018.hpp"
#include "test000019.hpp"
#include "test000020.hpp"
#include "test000021.h"

#define COPASI_MAIN

#include "copasi.h"

int main(int /*argc*/, char ** /*argv*/)
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(test000001::suite());
  runner.addTest(test000002::suite());
  runner.addTest(test000003::suite());
  runner.addTest(test000004::suite());
  runner.addTest(test000005::suite());
  runner.addTest(test000006::suite());
  runner.addTest(test000007::suite());
  runner.addTest(test000008::suite());
  runner.addTest(test000009::suite());
  runner.addTest(test000010::suite());
  runner.addTest(test000011::suite());
  runner.addTest(test000012::suite());
  runner.addTest(test000013::suite());
  runner.addTest(test000014::suite());
  runner.addTest(test000015::suite());
  runner.addTest(test000016::suite());
  runner.addTest(test000017::suite());
  runner.addTest(test000018::suite());
  runner.addTest(test000019::suite());
  runner.addTest(test000020::suite());
  runner.addTest(test000021::suite());
  runner.run();
  return 0;
}
