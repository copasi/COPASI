// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000090.cpp,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/03 16:14:28 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "test000090.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CReaction.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CExpression.h"

#include "copasi/report/CCopasiRootContainer.h"

CCopasiDataModel* test000090::pCOPASIDATAMODEL = NULL;

void test000090::setUp()
{
  // Create the root container.
  CCopasiRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CCopasiRootContainer::addDatamodel();
}

void test000090::tearDown()
{
  CCopasiRootContainer::destroy();
}

void test000090::test_delay_in_function()
{
  CCopasiDataModel* pDataModel = pCOPASIDATAMODEL;

  try
    {
      pDataModel->importSBMLFromString(MODEL_STRING);
    }
  catch (...)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();
      CPPUNIT_ASSERT(message.getType() == CCopasiMessage::EXCEPTION);
      std::string s = message.getText();
      CPPUNIT_ASSERT(!s.empty());
      CPPUNIT_ASSERT(s.find(std::string("Call to delay function used in function definition")) != std::string::npos);
      return;
    }

  // we should never get here
  CPPUNIT_ASSERT(false);
}

const char* test000090::MODEL_STRING =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">\n"
  "  <model id=\"Model_1\" name=\"New Model\">\n"
  "    <notes>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        <p>Model with a delay call in a function definition. This should lead to an exception and the model should not be imported.</p>\n"
  "      </body>\n"
  "    </notes>\n"
  "    <listOfFunctionDefinitions>"
  "      <functionDefinition id=\"function_1\" name=\"function with delay\">"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "          <lambda>"
  "            <bvar>"
  "              <ci> t </ci>"
  "            </bvar>"
  "            <apply>\n"
  "              <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/delay\">\n"
  "               delay\n"
  "              </csymbol>\n"
  "              <ci> t </ci>\n"
  "              <cn> 0.5 </cn>\n"
  "            </apply>\n"
  "          </lambda>"
  "        </math>"
  "      </functionDefinition>"
  "    </listOfFunctionDefinitions>"
  "    <listOfUnitDefinitions>\n"
  "      <unitDefinition id=\"volume\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"litre\" scale=\"-3\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"substance\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"mole\" scale=\"-3\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "    </listOfUnitDefinitions>\n"
  "    <listOfParameters>\n"
  "      <parameter id=\"parameter_1\" name=\"K1\" value=\"4\"/>\n"
  "      <parameter id=\"parameter_2\" name=\"K2\" value=\"5\"/>\n"
  "    </listOfParameters>\n"
  "    <listOfRules>\n"
  "      <assignmentRule variable=\"parameter_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <ci> function_1 </ci>"
  "            <ci> parameter_2 </ci>"
  "          </apply>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "    </listOfRules>\n"
  "  </model>\n"
  "</sbml>\n"
  ;
