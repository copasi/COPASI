// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test.cpp,v $
//   $Revision: 1.1.2.10 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/02/27 13:18:11 $
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
#include "test000022.h"
#include "test000023.h"
#include "test000024.h"
#include "test000025.h"
#include "test000026.h"
#include "test000027.h"
#include "test000028.h"
#include "test000029.h"
#include "test000030.h"
#include "test000031.h"
#include "test000032.h"
#include "test000033.h"
#include "test000034.h"
#include "test000035.h"
#include "test000036.h"
#include "test000037.h"
#include "test000038.h"
#include "test000039.h"
#include "test000040.h"
#include "test000041.h"
#include "test000042.h"
#include "test000043.h"
#include "test000044.h"
#include "test000045.h"
#include "test000046.h"
#include "test000047.h"
#include "test000048.h"
#include "test000049.h"
#include "test000050.h"

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
  runner.addTest(test000022::suite());
  runner.addTest(test000023::suite());
  runner.addTest(test000024::suite());
  runner.addTest(test000025::suite());
  runner.addTest(test000026::suite());
  runner.addTest(test000027::suite());
  runner.addTest(test000028::suite());
  runner.addTest(test000029::suite());
  runner.addTest(test000030::suite());
  runner.addTest(test000031::suite());
  runner.addTest(test000032::suite());
  runner.addTest(test000033::suite());
  runner.addTest(test000034::suite());
  runner.addTest(test000035::suite());
  runner.addTest(test000036::suite());
  runner.addTest(test000037::suite());
  runner.addTest(test000038::suite());
  runner.addTest(test000039::suite());
  runner.addTest(test000040::suite());
  runner.addTest(test000041::suite());
  runner.addTest(test000042::suite());
  runner.addTest(test000043::suite());
  runner.addTest(test000044::suite());
  runner.addTest(test000045::suite());
  runner.addTest(test000046::suite());
  runner.addTest(test000047::suite());
  runner.addTest(test000048::suite());
  runner.addTest(test000049::suite());
  runner.addTest(test000050::suite());
  runner.run();
  return 0;
}
