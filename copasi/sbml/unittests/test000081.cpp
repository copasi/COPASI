// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "test000081.h"

#include "utilities.hpp"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/utilities/CCopasiException.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Species.h"

CDataModel* test000081::pCOPASIDATAMODEL = NULL;

/**
 * Test for bug 1205
 */
void test000081::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000081::tearDown()
{
  CRootContainer::destroy();
}

void test000081::test_bug1205()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000081::MODEL_STRING1);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument == NULL);
  std::string sbmlString;

  try
    {
      sbmlString = pDataModel->exportSBMLToString(NULL, 2, 1);
    }
  catch (...)
    {
      // fail if an uncaught exception occurs during export
      CPPUNIT_ASSERT(false);
    }

  CPPUNIT_ASSERT(!sbmlString.empty());
  // check if the exported SBML model has three compartments
  pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  const Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  unsigned int iMax = pModel->getListOfCompartments()->size();
  CPPUNIT_ASSERT(iMax == 3);
  // check that the compartment named compartment_2 has the id compartment_1
  const Compartment* pCompartment = pModel->getCompartment("compartment_1");
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getName() == "compartment_2");

  // check if the exported SBML model has three species
  iMax = pModel->getListOfSpecies()->size();
  CPPUNIT_ASSERT(iMax == 3);
  // check that the species named species_2 has the id species_1
  const Species* pSpecies = pModel->getSpecies("species_1");
  CPPUNIT_ASSERT(pSpecies != NULL);
  CPPUNIT_ASSERT(pSpecies->getName() == "species_2");

  // check if the exported SBML model has three parameters
  iMax = pModel->getListOfParameters()->size();
  CPPUNIT_ASSERT(iMax == 3);
  // check that the parameter named quantity_2 has the id parameter_1
  const Parameter* pParameter = pModel->getParameter("parameter_1");
  CPPUNIT_ASSERT(pParameter != NULL);
  CPPUNIT_ASSERT(pParameter->getName() == "quantity_2");

  // check if the exported SBML model has three reactions
  iMax = pModel->getListOfReactions()->size();
  CPPUNIT_ASSERT(iMax == 3);
  // check that the reaction named reaction_2 has the id reaction_1
  const Reaction* pReaction = pModel->getReaction("reaction_1");
  CPPUNIT_ASSERT(pReaction != NULL);
  CPPUNIT_ASSERT(pReaction->getName() == "reaction_2");
}

const char* test000081::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.5.30 (Debug) (http://www.copasi.org) at 2009-05-07 08:59:15 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"30\">\n"
  "  <ListOfFunctions>\n"
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
  "  <Model key=\"Model_1\" name=\"Model_1\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "  <head>\n"
  "    <meta name=\"qrichtext\" content=\"1\"/>\n"
  "  </head>\n"
  "  <body style=\"font-size:13pt;font-family:Lucida Grande\">\n"
  "    <p>This is a test model for Bug 1205</p>\n"
  "  </body>\n"
  "</html>\n"
  "\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"fixed\">\n"
  "      </Compartment>\n"
  "      <Compartment key=\"Compartment_1\" name=\"compartment_1\" simulationType=\"fixed\">\n"
  "      </Compartment>\n"
  "      <Compartment key=\"Compartment_2\" name=\"compartment_2\" simulationType=\"fixed\">\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"species\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"species_1\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_2\" name=\"species_2\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"quantity\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "      <ModelValue key=\"ModelValue_1\" name=\"quantity_1\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "      <ModelValue key=\"ModelValue_2\" name=\"quantity_2\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <ListOfReactions>\n"
  "      <Reaction key=\"Reaction_1\" name=\"reaction\" reversible=\"false\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_79\" name=\"k1\" value=\"0.1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_13\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_81\">\n"
  "              <SourceParameter reference=\"Parameter_79\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_79\">\n"
  "              <SourceParameter reference=\"Metabolite_0\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "      <Reaction key=\"Reaction_0\" name=\"reaction_1\" reversible=\"false\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_80\" name=\"k1\" value=\"0.1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_13\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_81\">\n"
  "              <SourceParameter reference=\"Parameter_80\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_79\">\n"
  "              <SourceParameter reference=\"Metabolite_1\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "      <Reaction key=\"Reaction_2\" name=\"reaction_2\" reversible=\"false\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_2\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_507\" name=\"k1\" value=\"0.1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_13\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_81\">\n"
  "              <SourceParameter reference=\"Parameter_507\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_79\">\n"
  "              <SourceParameter reference=\"Metabolite_2\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "    </ListOfReactions>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_2\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_2\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_2\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 6.022141500000001e+20 6.022141500000001e+20 6.022141500000001e+20 0 0 0 1 1 1\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "  <GUI>\n"
  "  </GUI>\n"
  "  <SBMLReference file=\"bug1205.xml\">\n"
  "    <SBMLMap SBMLid=\"compartment_1\" COPASIkey=\"Compartment_2\"/>\n"
  "    <SBMLMap SBMLid=\"parameter_1\" COPASIkey=\"ModelValue_2\"/>\n"
  "    <SBMLMap SBMLid=\"reaction_1\" COPASIkey=\"Reaction_2\"/>\n"
  "    <SBMLMap SBMLid=\"species_1\" COPASIkey=\"Metabolite_2\"/>\n"
  "  </SBMLReference>\n"
  "</COPASI>\n";
