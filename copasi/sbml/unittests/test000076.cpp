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

#include "test000076.h"

#include <sstream>
#include <string>
#include <vector>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include <sbml/SBMLDocument.h>
#include <sbml/Model.h>
#include <sbml/Compartment.h>
#include <sbml/Rule.h>
#include <sbml/Reaction.h>
#include <sbml/SpeciesReference.h>
#include <sbml/Parameter.h>
#include <sbml/KineticLaw.h>
#include <sbml/InitialAssignment.h>
#include <sbml/math/ASTNode.h>

// TODO add tests for models with references to local parameters in event
// TODO triggers and event assignments

CDataModel* test000076::pCOPASIDATAMODEL = NULL;

/**
 * Test the export of models with references to local parameters in
 * expressions.
 */
void test000076::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000076::tearDown()
{
  CRootContainer::destroy();
}

void test000076::test_bug1035_1()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000076::MODEL_STRING1);
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
  // check if the exported SBML model has two parameters
  pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  const Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getListOfParameters()->size() == 2);
  const Parameter *pP1 = NULL, *pP2 = NULL;
  pP1 = pModel->getParameter(0);
  CPPUNIT_ASSERT(pP1 != NULL);

  if (pP1->getName() != std::string("K"))
    {
      pP2 = pP1;
      pP1 = pModel->getParameter(1);
    }
  else
    {
      pP2 = pModel->getParameter(1);
    }

  CPPUNIT_ASSERT(pP2->getName() == std::string("reaction_k1"));
  CPPUNIT_ASSERT(pP2->getConstant() == true);
  CPPUNIT_ASSERT(fabs((pP2->getValue() - 0.1) / 0.1) < 1e-6);
  CPPUNIT_ASSERT(pP1->getName() == std::string("K"));
  CPPUNIT_ASSERT(pP1->getConstant() == false);
  CPPUNIT_ASSERT(fabs((pP1->getValue() - 0.1) / 0.1) < 1e-6);
  // check there is exactly one rule
  CPPUNIT_ASSERT(pModel->getListOfRules()->size() == 1);
  const Rule* pRule = pModel->getRule(0);
  CPPUNIT_ASSERT(pRule != NULL);
  const AssignmentRule* pAssignmentRule = dynamic_cast<const AssignmentRule*>(pRule);
  CPPUNIT_ASSERT(pAssignmentRule != NULL);
  CPPUNIT_ASSERT(pAssignmentRule->getVariable() == pP1->getId());
  const ASTNode* pMath = pAssignmentRule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == std::string(pP2->getId()));
  // now check the reaction
  CPPUNIT_ASSERT(pModel->getListOfReactions()->size() == 1);
  const Reaction* pReaction = pModel->getReaction(0);
  CPPUNIT_ASSERT(pReaction != NULL);
  CPPUNIT_ASSERT(pReaction->getListOfReactants()->size() == 1);
  CPPUNIT_ASSERT(pReaction->getListOfProducts()->size() == 1);
  CPPUNIT_ASSERT(pReaction->getListOfModifiers()->size() == 0);
  const KineticLaw* pKLaw = pReaction->getKineticLaw();
  CPPUNIT_ASSERT(pKLaw != NULL);
  CPPUNIT_ASSERT(pKLaw->getListOfParameters()->size() == 0);
  const SpeciesReference* pSpeciesReference = pReaction->getReactant(0);
  CPPUNIT_ASSERT(pSpeciesReference != NULL);
  CPPUNIT_ASSERT(pModel->getListOfCompartments()->size() == 1);
  const Compartment* pCompartment = pModel->getCompartment(0);
  CPPUNIT_ASSERT(pCompartment != NULL);
  pMath = pKLaw->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // check that the expression is the compartment times the substrate times the
  // parameter
  CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
  std::vector<std::string> ids;
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2 || pMath->getNumChildren() == 3);

  if (pMath->getNumChildren() == 3)
    {
      CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_NAME);
      CPPUNIT_ASSERT(pMath->getChild(1)->getType() == AST_NAME);
      CPPUNIT_ASSERT(pMath->getChild(2)->getType() == AST_NAME);
      ids.push_back(pMath->getChild(0)->getName());
      ids.push_back(pMath->getChild(1)->getName());
      ids.push_back(pMath->getChild(2)->getName());
    }
  else
    {
      if (pMath->getChild(0)->getType() == AST_NAME)
        {
          ids.push_back(pMath->getChild(0)->getName());
          pMath = pMath->getChild(1);
        }
      else
        {
          CPPUNIT_ASSERT(pMath->getChild(1)->getType() == AST_NAME);
          ids.push_back(pMath->getChild(1)->getName());
          pMath = pMath->getChild(0);
        }

      CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
      CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
      CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_NAME);
      CPPUNIT_ASSERT(pMath->getChild(1)->getType() == AST_NAME);
      ids.push_back(pMath->getChild(0)->getName());
      ids.push_back(pMath->getChild(1)->getName());
    }

  CPPUNIT_ASSERT(ids.size() == 3);
  CPPUNIT_ASSERT(std::find(ids.begin(), ids.end(), std::string(pCompartment->getId())) != ids.end());
  CPPUNIT_ASSERT(std::find(ids.begin(), ids.end(), std::string(pP2->getId())) != ids.end());
  CPPUNIT_ASSERT(std::find(ids.begin(), ids.end(), std::string(pSpeciesReference->getSpecies())) != ids.end());
}

// This test makes sure a reference to a local parameter in an initial
// assignment is exported correctly.
void test000076::test_bug1035_2()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000076::MODEL_STRING2);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument == NULL);
  std::string sbmlString;

  try
    {
      // we need to export to Level 2 Version 3 because of the initial assignment
      sbmlString = pDataModel->exportSBMLToString(NULL, 2, 3);
    }
  catch (...)
    {
      // fail if any exception occurs during the export
      CPPUNIT_ASSERT(false);
    }

  CPPUNIT_ASSERT(!sbmlString.empty());
  // check if the exported SBML model has two parameters
  pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  const Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getListOfParameters()->size() == 2);
  const Parameter *pP1 = NULL, *pP2 = NULL;
  pP1 = pModel->getParameter(0);
  CPPUNIT_ASSERT(pP1 != NULL);

  if (pP1->getName() != std::string("K"))
    {
      pP2 = pP1;
      pP1 = pModel->getParameter(1);
    }
  else
    {
      pP2 = pModel->getParameter(1);
    }

  CPPUNIT_ASSERT(pP2->getName() == std::string("reaction_k1"));
  CPPUNIT_ASSERT(pP2->getConstant() == true);
  CPPUNIT_ASSERT(fabs((pP2->getValue() - 0.1) / 0.1) < 1e-6);
  CPPUNIT_ASSERT(pP1->getName() == std::string("K"));
  CPPUNIT_ASSERT(pP1->getConstant() == true);
  CPPUNIT_ASSERT(fabs((pP1->getValue() - 0.1) / 0.1) < 1e-6);
  // check there is exactly one initial assignment
  CPPUNIT_ASSERT(pModel->getListOfInitialAssignments()->size() == 1);
  const InitialAssignment* pAssignment = pModel->getInitialAssignment(0);
  CPPUNIT_ASSERT(pAssignment != NULL);
  CPPUNIT_ASSERT(pAssignment->getSymbol() == pP1->getId());
  const ASTNode* pMath = pAssignment->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == std::string(pP2->getId()));
  // now check the reaction
  CPPUNIT_ASSERT(pModel->getListOfReactions()->size() == 1);
  const Reaction* pReaction = pModel->getReaction(0);
  CPPUNIT_ASSERT(pReaction != NULL);
  CPPUNIT_ASSERT(pReaction->getListOfReactants()->size() == 1);
  CPPUNIT_ASSERT(pReaction->getListOfProducts()->size() == 1);
  CPPUNIT_ASSERT(pReaction->getListOfModifiers()->size() == 0);
  const KineticLaw* pKLaw = pReaction->getKineticLaw();
  CPPUNIT_ASSERT(pKLaw != NULL);
  CPPUNIT_ASSERT(pKLaw->getListOfParameters()->size() == 0);
  const SpeciesReference* pSpeciesReference = pReaction->getReactant(0);
  CPPUNIT_ASSERT(pSpeciesReference != NULL);
  CPPUNIT_ASSERT(pModel->getListOfCompartments()->size() == 1);
  const Compartment* pCompartment = pModel->getCompartment(0);
  CPPUNIT_ASSERT(pCompartment != NULL);
  pMath = pKLaw->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // check that the expression is the compartment times the substrate times the
  // parameter
  CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
  std::vector<std::string> ids;
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2 || pMath->getNumChildren() == 3);

  if (pMath->getNumChildren() == 3)
    {
      CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_NAME);
      CPPUNIT_ASSERT(pMath->getChild(1)->getType() == AST_NAME);
      CPPUNIT_ASSERT(pMath->getChild(2)->getType() == AST_NAME);
      ids.push_back(pMath->getChild(0)->getName());
      ids.push_back(pMath->getChild(1)->getName());
      ids.push_back(pMath->getChild(2)->getName());
    }
  else
    {
      if (pMath->getChild(0)->getType() == AST_NAME)
        {
          ids.push_back(pMath->getChild(0)->getName());
          pMath = pMath->getChild(1);
        }
      else
        {
          CPPUNIT_ASSERT(pMath->getChild(1)->getType() == AST_NAME);
          ids.push_back(pMath->getChild(1)->getName());
          pMath = pMath->getChild(0);
        }

      CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
      CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
      CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_NAME);
      CPPUNIT_ASSERT(pMath->getChild(1)->getType() == AST_NAME);
      ids.push_back(pMath->getChild(0)->getName());
      ids.push_back(pMath->getChild(1)->getName());
    }

  CPPUNIT_ASSERT(ids.size() == 3);
  CPPUNIT_ASSERT(std::find(ids.begin(), ids.end(), std::string(pCompartment->getId())) != ids.end());
  CPPUNIT_ASSERT(std::find(ids.begin(), ids.end(), std::string(pP2->getId())) != ids.end());
  CPPUNIT_ASSERT(std::find(ids.begin(), ids.end(), std::string(pSpeciesReference->getSpecies())) != ids.end());
}

// This test makes sure that the new feature does not break the
// current export of local parameters.
// This models does not contain a reference to a local parameter and therefor
// the local parameter should stay local during export.
void test000076::test_bug1035_3()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000076::MODEL_STRING3);
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
  // check if the exported SBML model has two parameters
  pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  const Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getListOfParameters()->size() == 1);
  const Parameter *pP1 = pModel->getParameter(0);
  CPPUNIT_ASSERT(pP1 != NULL);
  CPPUNIT_ASSERT(pP1->getName() == std::string("K"));
  CPPUNIT_ASSERT(pP1->getConstant() == true);
  CPPUNIT_ASSERT(fabs((pP1->getValue() - 0.1) / 0.1) < 1e-6);
  // check there are no rules and no initial assignments
  CPPUNIT_ASSERT(pModel->getListOfRules()->size() == 0);
  CPPUNIT_ASSERT(pModel->getListOfInitialAssignments()->size() == 0);
  // now check the reaction
  CPPUNIT_ASSERT(pModel->getListOfReactions()->size() == 1);
  const Reaction* pReaction = pModel->getReaction(0);
  CPPUNIT_ASSERT(pReaction != NULL);
  CPPUNIT_ASSERT(pReaction->getListOfReactants()->size() == 1);
  CPPUNIT_ASSERT(pReaction->getListOfProducts()->size() == 1);
  CPPUNIT_ASSERT(pReaction->getListOfModifiers()->size() == 0);
  const KineticLaw* pKLaw = pReaction->getKineticLaw();
  CPPUNIT_ASSERT(pKLaw != NULL);
  CPPUNIT_ASSERT(pKLaw->getListOfParameters()->size() == 1);
  pP1 = pKLaw->getParameter(0);
  CPPUNIT_ASSERT(pP1 != NULL);
  CPPUNIT_ASSERT(pP1->getId() == std::string("k1"));
  const SpeciesReference* pSpeciesReference = pReaction->getReactant(0);
  CPPUNIT_ASSERT(pSpeciesReference != NULL);
  CPPUNIT_ASSERT(pModel->getListOfCompartments()->size() == 1);
  const Compartment* pCompartment = pModel->getCompartment(0);
  CPPUNIT_ASSERT(pCompartment != NULL);
  const ASTNode* pMath = pKLaw->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // check that the expression is the compartment times the substrate times the
  // local parameter
  CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
  std::vector<std::string> ids;
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2 || pMath->getNumChildren() == 3);

  if (pMath->getNumChildren() == 3)
    {
      CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_NAME);
      CPPUNIT_ASSERT(pMath->getChild(1)->getType() == AST_NAME);
      CPPUNIT_ASSERT(pMath->getChild(2)->getType() == AST_NAME);
      ids.push_back(pMath->getChild(0)->getName());
      ids.push_back(pMath->getChild(1)->getName());
      ids.push_back(pMath->getChild(2)->getName());
    }
  else
    {
      if (pMath->getChild(0)->getType() == AST_NAME)
        {
          ids.push_back(pMath->getChild(0)->getName());
          pMath = pMath->getChild(1);
        }
      else
        {
          CPPUNIT_ASSERT(pMath->getChild(1)->getType() == AST_NAME);
          ids.push_back(pMath->getChild(1)->getName());
          pMath = pMath->getChild(0);
        }

      CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
      CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
      CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_NAME);
      CPPUNIT_ASSERT(pMath->getChild(1)->getType() == AST_NAME);
      ids.push_back(pMath->getChild(0)->getName());
      ids.push_back(pMath->getChild(1)->getName());
    }

  CPPUNIT_ASSERT(ids.size() == 3);
  CPPUNIT_ASSERT(std::find(ids.begin(), ids.end(), std::string(pCompartment->getId())) != ids.end());
  // make sure the local parameter is multiplied in
  CPPUNIT_ASSERT(std::find(ids.begin(), ids.end(), std::string(pP1->getId())) != ids.end());
  CPPUNIT_ASSERT(std::find(ids.begin(), ids.end(), std::string(pSpeciesReference->getSpecies())) != ids.end());
}

const char* test000076::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.4.29 (Debug) (http://www.copasi.org) at 2009-01-21 10:40:31 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"29\">\n"
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
  "  <Model key=\"Model_0\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        \n"
  "      </body>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"fixed\">\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"B\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"K\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Reactions[reaction],ParameterGroup=Parameters,Parameter=k1,Reference=Value&gt;\n"
  "        </Expression>\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <ListOfReactions>\n"
  "      <Reaction key=\"Reaction_0\" name=\"reaction\" reversible=\"false\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_78\" name=\"k1\" value=\"0.1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_13\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_81\">\n"
  "              <SourceParameter reference=\"Parameter_78\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_79\">\n"
  "              <SourceParameter reference=\"Metabolite_0\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "    </ListOfReactions>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 6.022141500000001e+19 6.022141500000001e+19 0.1 1\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n";

const char* test000076::MODEL_STRING2 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.4.29 (Debug) (http://www.copasi.org) at 2009-01-21 19:47:46 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"29\">\n"
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
  "  <Model key=\"Model_1\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        \n"
  "      </body>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"fixed\">\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"B\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"K\" simulationType=\"fixed\">\n"
  "        <InitialExpression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Reactions[reaction],ParameterGroup=Parameters,Parameter=k1,Reference=Value&gt;\n"
  "        </InitialExpression>\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <ListOfReactions>\n"
  "      <Reaction key=\"Reaction_0\" name=\"reaction\" reversible=\"false\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_81\" name=\"k1\" value=\"0.1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_13\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_81\">\n"
  "              <SourceParameter reference=\"Parameter_81\"/>\n"
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
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 6.022141500000001e+19 6.022141500000001e+19 0.1 1\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n";

const char* test000076::MODEL_STRING3 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.4.29 (Debug) (http://www.copasi.org) at 2009-01-21 19:51:24 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"29\">\n"
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
  "  <Model key=\"Model_1\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        \n"
  "      </body>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"fixed\">\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"B\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"K\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <ListOfReactions>\n"
  "      <Reaction key=\"Reaction_0\" name=\"reaction\" reversible=\"false\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_81\" name=\"k1\" value=\"0.1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_13\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_81\">\n"
  "              <SourceParameter reference=\"Parameter_81\"/>\n"
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
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 6.022141500000001e+19 6.022141500000001e+19 0.1 1\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n";
