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

#include "test000015.hpp"

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

CDataModel* test000015::pCOPASIDATAMODEL = NULL;

void test000015::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000015::tearDown()
{
  CRootContainer::destroy();
}

void test000015::test_references_to_species()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000015::MODEL_STRING);
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
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  Species* pSpecies = pModel->getSpecies(1);
  CPPUNIT_ASSERT(pSpecies->getHasOnlySubstanceUnits() == true);
  pSpecies = pModel->getSpecies(0);
  std::string idSpeciesA = pSpecies->getId();
  CPPUNIT_ASSERT(pSpecies->getHasOnlySubstanceUnits() == true);
  CPPUNIT_ASSERT(pModel->getNumRules() == 1);
  CPPUNIT_ASSERT(pModel->getNumInitialAssignments() == 1);
  InitialAssignment* pAssignment = pModel->getInitialAssignment(0);
  CPPUNIT_ASSERT(pAssignment != NULL);
  CPPUNIT_ASSERT(pModel->getNumParameters() == 2);
  Parameter* pParameter = pModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter != NULL);
  Parameter* pFactor = pModel->getParameter(1);
  CPPUNIT_ASSERT(pFactor != NULL);
  CPPUNIT_ASSERT(fabs((pFactor->getValue() - (AVOGADRO / 1000.0)) / (AVOGADRO / 1000.0)) < 1e-3);
  CPPUNIT_ASSERT(pAssignment->getSymbol() == pParameter->getId());
  const ASTNode* pMath = pAssignment->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // the expression shopuld be the species multiplied by a factor
  CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  CPPUNIT_ASSERT(pMath->getChild(0) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getChild(0)->getName() == idSpeciesA);
  CPPUNIT_ASSERT(pMath->getChild(1) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getChild(1)->getName() == pFactor->getId());
  CPPUNIT_ASSERT(pModel->getNumReactions() == 2);
  Reaction* pReaction = pModel->getReaction(0);
  // make sure this is reaction A ->
  CPPUNIT_ASSERT(pReaction != NULL);
  CPPUNIT_ASSERT(pReaction->getNumReactants() == 1);
  CPPUNIT_ASSERT(pReaction->getNumProducts() == 0);
  // check if all references in the kinetic law are unmodified
  // math element must be a multiplication of the mass action term by
  // the compartment volume
  // the mass action term is a multiplication of the parameter node by
  // the species node
  CPPUNIT_ASSERT(pReaction->isSetKineticLaw() == true);
  KineticLaw* pLaw = pReaction->getKineticLaw();
  CPPUNIT_ASSERT(pLaw != NULL);
  CPPUNIT_ASSERT(pLaw->isSetMath() == true);
  pMath = pLaw->getMath();
  CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  CPPUNIT_ASSERT(pMath->getChild(0) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getChild(0)->getName() == std::string("k1"));
  CPPUNIT_ASSERT(pMath->getChild(1) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getChild(1)->getName() == idSpeciesA);

  pReaction = pModel->getReaction(1);
  // make sure this is reaction A -> S
  CPPUNIT_ASSERT(pReaction != NULL);
  CPPUNIT_ASSERT(pReaction->getNumReactants() == 1);
  CPPUNIT_ASSERT(pReaction->getNumProducts() == 1);
  // check if all references in the kinetic law are unmodified
  // math element must be a multiplication of the compartments volume with
  // a function call with three arguments
  // the first argument is the reference to the species
  CPPUNIT_ASSERT(pReaction->isSetKineticLaw() == true);
  pLaw = pReaction->getKineticLaw();
  CPPUNIT_ASSERT(pLaw != NULL);
  CPPUNIT_ASSERT(pLaw->isSetMath() == true);
  pMath = pLaw->getMath();
  CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getChild(0)->getName() == pCompartment->getId());
  pMath = pMath->getChild(1);
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_FUNCTION);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 3);
  pMath = pMath->getChild(0);
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_DIVIDE);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  CPPUNIT_ASSERT(pMath->getChild(0) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getChild(0)->getName() == idSpeciesA);
  CPPUNIT_ASSERT(pMath->getChild(1) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getChild(1)->getName() == pCompartment->getId());
}

const char* test000015::MODEL_STRING =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.3.25 (Debug) (http://www.copasi.org) at 2008-02-15 09:41:38 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"25\">\n"
  "  <ListOfFunctions>\n"
  "    <Function key=\"Function_8\" name=\"Henri-Michaelis-Menten (irreversible)\" type=\"PreDefined\" reversible=\"false\">\n"
  "      <Expression>\n"
  "        V*substrate/(Km+substrate)\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_41\" name=\"substrate\" order=\"0\" role=\"substrate\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_30\" name=\"Km\" order=\"1\" role=\"constant\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_45\" name=\"V\" order=\"2\" role=\"constant\"/>\n"
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
  "  <Model key=\"Model_1\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:13pt;font-family:Lucida Grande\">\n"
  "<p>Model with variable volume compartment,mmol quantity units and a reference to the species initial amount.</p>\n"
  "<p>On export this should create an SBML file with the hasOnlySubstanceUnits flag on the species set.</p>\n"
  "<p>The reference in the initial assignment should be multiplied by a factor (6.023e20), the references in the reactions should be divided by the volume.</p>\n"
  "</body></html>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          3+4\n"
  "        </Expression>\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"S\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"K\" simulationType=\"fixed\">\n"
  "        <InitialExpression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=InitialParticleNumber&gt;\n"
  "        </InitialExpression>\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <ListOfReactions>\n"
  "      <Reaction key=\"Reaction_0\" name=\"reaction\" reversible=\"false\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_93\" name=\"k1\" value=\"0.1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_13\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_81\">\n"
  "              <SourceParameter reference=\"Parameter_93\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_79\">\n"
  "              <SourceParameter reference=\"Metabolite_0\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "      <Reaction key=\"Reaction_1\" name=\"reaction_1\" reversible=\"false\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_92\" name=\"Km\" value=\"0.1\"/>\n"
  "          <Constant key=\"Parameter_91\" name=\"V\" value=\"0.1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_8\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_41\">\n"
  "              <SourceParameter reference=\"Metabolite_0\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_30\">\n"
  "              <SourceParameter reference=\"Parameter_92\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_45\">\n"
  "              <SourceParameter reference=\"Parameter_91\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "    </ListOfReactions>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 4.215499050000001e+21 4.215499050000002e+20 7 4.215499050000001e+21\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n"
  ;
