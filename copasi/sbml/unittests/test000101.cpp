// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "test000101.h"

#include <iostream>
#ifndef WIN32
#include <signal.h>
#endif
#include <stdexcept>

#include <copasi/report/CRootContainer.h>
#include <copasi/CopasiDataModel/CDataModel.h>

// Since this bug leads to segmentation fault
// we need to make sure that the call to abort made by assert does not end the program.
// For this we change the signal handler to one that throws an exception.
// The current version is specific to linux. If these tests are to be run under windows,
// the mechanism for setting the signal handler will probably have to be modified.
void test000101::abort_handler(int)
{
  throw std::runtime_error("Received SIGSEGV signal.");
}

#ifndef WIN32
struct sigaction* test000101::pOldAct = new struct sigaction();
struct sigaction* test000101::pNewAct = new struct sigaction();
#endif
void test000101::setUp()
{
#ifndef WIN32
  // set a new action handler for SIGABRT that throws an exception
  // instead of terminating the program. This is needed to handle failed assertions
  // in debug versions.
  pNewAct->sa_handler = &test000101::abort_handler;
  int x = sigaction(SIGSEGV, test000101::pNewAct, test000101::pOldAct);

  if (x != 0)
    {
      std::cerr << "Setting the signal handler failed." << std::endl;
    }

#endif
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  pDataModel = CRootContainer::addDatamodel();
}

void test000101::tearDown()
{
#ifndef WIN32
  CRootContainer::destroy();
  // restore the old action handler
  int x = sigaction(SIGSEGV, test000101::pOldAct, NULL);

  if (x != 0)
    {
      std::cerr << "Resetting the signal handler failed." << std::endl;
    }

#endif
}

void test000101::test_bug1740()
{
  pDataModel->importSBMLFromString(SBML_STRING);
  pDataModel->exportSBMLToString(NULL, 3, 1);

  try
    {
      // the second export crashes without a bug fix
      pDataModel->exportSBMLToString(NULL, 3, 1);
    }
  catch (const std::runtime_error& e)
    {
      CPPUNIT_ASSERT_MESSAGE("The second export to Level 3 Version 1 failed.", false);
    }
}

const char* test000101::SBML_STRING = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                      "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                                      "  <model id=\"Module_1_RL2_1\" name=\"Module_1_RL2\">\n"
                                      "    <listOfReactions>\n"
                                      "      <reaction fast=\"false\" id=\"reaction_0\" name=\"reaction_0\" reversible=\"false\">\n"
                                      "      </reaction>\n"
                                      "    </listOfReactions>\n"
                                      "  </model>\n"
                                      "</sbml>\n";
