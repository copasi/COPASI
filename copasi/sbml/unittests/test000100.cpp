// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "test000100.h"

#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>
#ifndef WIN32
#include <signal.h>
#endif
#include "utilities.hpp"

#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"

// Since this bug leads to failed assertions in the debug version,
// we need to make sure that the call to abort made by assert does not end the program.
// For this we change the signal handler to one that throws an exception.
// The current version is specific to linux. If these tests are to be run under windows,
// the mechanism for setting the signal handler will probably have to be modified.
void abort_handler(int)
{
  throw std::runtime_error("Received SIGABRT signal.");
}

#ifndef WIN32
struct sigaction* pNewAct = NULL;
struct sigaction* pOldAct = NULL;
#endif
void test000100::setUp()
{
#ifndef WIN32
  // set a new action handler for SIGABRT that throws an exception
  // instead of terminating the program. This is needed to handle failed assertions
  // in debug versions.
  pNewAct = new struct sigaction();
  pNewAct->sa_handler = &abort_handler;
  pOldAct = new struct sigaction();
  int x = sigaction(SIGABRT, pNewAct, pOldAct);

  if (x != 0)
    {
      std::cerr << "Setting the signal handler failed." << std::endl;
    }

#endif
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  pDataModel = CRootContainer::addDatamodel();
}

void test000100::tearDown()
{
  CRootContainer::destroy();
#ifndef WIN32
  // restore the old action handler
  int x = sigaction(SIGABRT, pOldAct, NULL);

  if (x != 0)
    {
      std::cerr << "Resetting the signal handler failed." << std::endl;
    }

#endif
}

// test whether exporting an SBML Level 3 file after an SBML Level 2 file
// succeeds
void test000100::test_bug1692_1()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  std::istringstream iss(test000100::CPS_STRING);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  std::string s;

  try
    {
      s = pDataModel->exportSBMLToString(NULL, 2, 1);
    }
  catch (...)
    {
      CPPUNIT_ASSERT_MESSAGE("The first export to Level 2 Version 1 failed.", false);
    }

  try
    {
      s = pDataModel->exportSBMLToString(NULL, 3, 1);
    }
  catch (...)
    {
      CPPUNIT_ASSERT_MESSAGE("The second export to Level 3 Version 1 failed.", false);
    }
}

// test whether exporting an SBML Level 3 file before an SBML Level 2 file
// succeeds
void test000100::test_bug1692_2()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  std::istringstream iss(test000100::CPS_STRING);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  std::string s;

  try
    {
      s = pDataModel->exportSBMLToString(NULL, 3, 1);
    }
  catch (...)
    {
      CPPUNIT_ASSERT_MESSAGE("The first export to Level 3 Version 1 failed.", false);
    }

  try
    {
      s = pDataModel->exportSBMLToString(NULL, 2, 1);
    }
  catch (...)
    {
      CPPUNIT_ASSERT_MESSAGE("The second export to Level 2 Version 1 failed.", false);
    }
}

const char* test000100::CPS_STRING =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.7.34 (Debug) (http://www.copasi.org) at 2011-09-08 08:14:18 UTC -->\n"
  "<?oxygen RNGSchema=\"http://www.copasi.org/static/schema/CopasiML.rng\" type=\"xml\"?>\n"
  "<COPASI xmlns=\"http://www.copasi.org/static/schema\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"34\">\n"
  "  <ListOfFunctions>\n"
  "    <Function key=\"Function_6\" name=\"Constant flux (irreversible)\" type=\"PreDefined\" reversible=\"false\">\n"
  "      <Expression>\n"
  "        v\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_49\" name=\"v\" order=\"0\" role=\"constant\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_13\" name=\"Mass action (irreversible)\" type=\"MassAction\" reversible=\"false\">\n"
  "      <Expression>\n"
  "        k1*PRODUCT&lt;substrate_i&gt;\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_81\" name=\"k1\" order=\"0\" role=\"constant\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_79\" name=\"substrate\" order=\"1\" role=\"substrate\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "  </ListOfFunctions>\n"
  "  <Model key=\"Model_0\" name=\"New Model\" simulationType=\"time\" timeUnit=\"s\" volumeUnit=\"µl\" areaUnit=\"m²\" lengthUnit=\"m\" quantityUnit=\"nmol\" type=\"deterministic\" avogadroConstant=\"6.02214179e+23\">\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"cell\" simulationType=\"fixed\" dimensionality=\"3\">\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"glucose\" simulationType=\"fixed\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"glucose-6-phosphate\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_2\" name=\"ATP\" simulationType=\"fixed\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_3\" name=\"ADP\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"rateConstant\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          1.0/4.0+2.0\n"
  "        </Expression>\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <ListOfReactions>\n"
  "      <Reaction key=\"Reaction_0\" name=\"hexokinase\" reversible=\"false\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "          <Substrate metabolite=\"Metabolite_2\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "          <Product metabolite=\"Metabolite_3\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_93\" name=\"v\" value=\"0.5\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_6\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_49\">\n"
  "              <SourceParameter reference=\"Parameter_93\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "      <Reaction key=\"Reaction_1\" name=\"hexokinase-backwards\" reversible=\"false\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "          <Substrate metabolite=\"Metabolite_3\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "          <Product metabolite=\"Metabolite_2\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_94\" name=\"k1\" value=\"1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_13\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_81\">\n"
  "              <SourceParameter reference=\"ModelValue_0\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_79\">\n"
  "              <SourceParameter reference=\"Metabolite_1\"/>\n"
  "              <SourceParameter reference=\"Metabolite_3\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "    </ListOfReactions>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_3\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_2\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 0 0 2.25 3.011070895e+16 3.011070895e+16 5 \n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n";
