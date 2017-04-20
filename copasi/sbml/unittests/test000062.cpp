// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "test000062.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CModelValue.h"
#include "copasi/function/CFunctionDB.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Rule.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/math/ASTNode.h"

#include "copasi/core/CRootContainer.h"

CDataModel* test000062::pCOPASIDATAMODEL = NULL;

void test000062::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000062::tearDown()
{
  CRootContainer::destroy();
}

void test000062::test_kineticlaw_without_math()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000062::MODEL_STRING1));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CPPUNIT_ASSERT(pModel->getReactions().size() == 1);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 0);
  // check if the reactions function is set correctly
  CReaction* pReaction = pModel->getReactions()[0];
  CPPUNIT_ASSERT(pReaction->getFunction() == CRootContainer::getUndefinedFunction());
  // check if the correct error message has been created
#if LIBSBML_VERSION >= 40200
  // recent libsbml versions will complain about missing math element!
  CPPUNIT_ASSERT(CCopasiMessage::size() == 2);
#else
  CPPUNIT_ASSERT(CCopasiMessage::size() == 1);
#endif
  const CCopasiMessage& message = CCopasiMessage::getLastMessage();
  CPPUNIT_ASSERT(message.getType() == CCopasiMessage::WARNING);
  CPPUNIT_ASSERT(message.getNumber() == MCSBML + 56);
}

/**
 * The units given for the two parameters in the kinetic law are wrong and they
 * are only there to stop libsbml from issuing warnings about best modeling practice.
 */
const char* test000062::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"Kinetic Law Without Math Element\">"
  "    <listOfUnitDefinitions>"
  "      <unitDefinition id=\"volume\">"
  "        <listOfUnits>"
  "          <unit kind=\"litre\" scale=\"-3\"/>"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "      <unitDefinition id=\"substance\">"
  "        <listOfUnits>"
  "          <unit kind=\"mole\" scale=\"-3\"/>"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>"
  "    </listOfCompartments>"
  "    <listOfSpecies>"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"0.1\"/>"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"0.1\"/>"
  "    </listOfSpecies>"
  "    <listOfReactions>"
  "      <reaction id=\"reaction_1\" name=\"reaction\" reversible=\"false\">"
  "        <listOfReactants>"
  "          <speciesReference species=\"species_1\"/>"
  "        </listOfReactants>"
  "        <listOfProducts>"
  "          <speciesReference species=\"species_2\"/>"
  "        </listOfProducts>"
  "        <kineticLaw>"
  "          <listOfParameters>"
  "            <parameter id=\"Km\" value=\"0.1\" units=\"substance\"/>"
  "            <parameter id=\"V\" value=\"0.1\" units=\"substance\"/>"
  "          </listOfParameters>"
  "        </kineticLaw>"
  "      </reaction>"
  "    </listOfReactions>"
  "  </model>"
  "</sbml>"
  ;
