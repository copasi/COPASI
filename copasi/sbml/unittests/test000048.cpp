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

#include "test000048.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Rule.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/math/ASTNode.h"

#include "copasi/core/CRootContainer.h"

CDataModel* test000048::pCOPASIDATAMODEL = NULL;

void test000048::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000048::tearDown()
{
  CRootContainer::destroy();
}

void test000048::test_bug919()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000048::MODEL_STRING);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 3).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // assert that there is only one compartment and
  // assert the compartment is constant
  CPPUNIT_ASSERT(pModel->getNumCompartments() == 1);
  Compartment* pCompartment = pModel->getCompartment(0);
  CPPUNIT_ASSERT(pCompartment->getConstant() == false);
  // since the compartment is no constant all species should be
  // exported with the hasOnlySubstanceUnits flag set to true
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  const Species* pA = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getHasOnlySubstanceUnits() == true);
  const Species* pB = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getHasOnlySubstanceUnits() == true);

  CPPUNIT_ASSERT(pModel->getNumInitialAssignments() == 1);
  // check the initial assignment
  const InitialAssignment* pIA = pModel->getInitialAssignment(0);
  CPPUNIT_ASSERT(pIA != NULL);
  CPPUNIT_ASSERT(pIA->getSymbol() == pCompartment->getId());
  CPPUNIT_ASSERT(pIA->isSetMath() == true);
  const ASTNode* pNode = pIA->getMath();
  CPPUNIT_ASSERT(pNode != NULL);
  // since the quantity unit is set to particle numbers, the expression should
  // consists of only one node which is a reference to species A
  CPPUNIT_ASSERT(pNode->getType() == AST_NAME);
  CPPUNIT_ASSERT(pNode->getName() == pA->getId());
  CPPUNIT_ASSERT(pModel->getNumRules() == 1);
  // check the rule
  const Rule* pRule = pModel->getRule(0);
  CPPUNIT_ASSERT(pRule != NULL);
  const RateRule* pRateRule = dynamic_cast<const RateRule*>(pRule);
  CPPUNIT_ASSERT(pRateRule != NULL);
  CPPUNIT_ASSERT(pRateRule->getVariable() == pCompartment->getId());
  CPPUNIT_ASSERT(pRule->isSetMath() == true);
  pNode = pRateRule->getMath();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->getType() == AST_NAME);
  CPPUNIT_ASSERT(pNode->getName() == pA->getId());
}

const char* test000048::MODEL_STRING =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.2.23++ (Debug) (http://www.copasi.org) at 2007-12-05 21:20:21 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"23\">\n"
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
  "    <Function key=\"Function_44\" name=\"Objective Function\" type=\"Expression\">\n"
  "      <Expression>\n"
  "        \n"
  "      </Expression>\n"
  "    </Function>\n"
  "  </ListOfFunctions>\n"
  "  <Model key=\"Model_1\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"#\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        \n"
  "      </body>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"ode\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=ParticleNumber&gt;\n"
  "        </Expression>\n"
  "        <InitialExpression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=InitialParticleNumber&gt;\n"
  "        </InitialExpression>\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"B\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfReactions>\n"
  "      <Reaction key=\"Reaction_0\" name=\"reaction\" reversible=\"false\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_103\" name=\"k1\" value=\"0.1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_13\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_81\">\n"
  "              <SourceParameter reference=\"Parameter_103\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_79\">\n"
  "              <SourceParameter reference=\"Metabolite_0\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "    </ListOfReactions>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 1000 1000 100\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n"
  ;
