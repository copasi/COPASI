// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000062.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/06/09 12:11:05 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "test000062.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CModelValue.h"
#include "copasi/function/CFunctionDB.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Rule.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/math/ASTNode.h"

void test000062::setUp()
{
  // Create the root container.
  CCopasiContainer::init();

  // Create the global data model.
  CCopasiDataModel::Global = new CCopasiDataModel();
}

void test000062::tearDown()
{
  delete CCopasiDataModel::Global;
  CCopasiDataModel::Global = NULL;
  delete CCopasiContainer::Root;
  CCopasiContainer::Root = NULL;
}

void test000062::test_kineticlaw_without_math()
{
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000062::MODEL_STRING1));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CPPUNIT_ASSERT(pModel->getReactions().size() == 1);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 0);
  // check if the reactions function is set correctly
  CReaction* pReaction = pModel->getReactions()[0];
  CPPUNIT_ASSERT(pReaction->getFunction() == CCopasiDataModel::Global->mpUndefined);
  // check if the correct error message has been created
  CPPUNIT_ASSERT(CCopasiMessage::size() == 1);
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
