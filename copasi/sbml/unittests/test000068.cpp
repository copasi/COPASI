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

#include "test000068.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CReaction.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationNodeVariable.h"
#include "copasi/function/CExpression.h"
#include "copasi/function/CEvaluationTree.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Reaction.h"

#include "copasi/core/CRootContainer.h"

CDataModel* test000068::pCOPASIDATAMODEL = NULL;

void test000068::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000068::tearDown()
{
  CRootContainer::destroy();
}

void test000068::test_bug1068()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING1));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CUnit::Mol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CUnit::l);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CUnit::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::Status::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 6);
  // check metabolites
  const CMetab* pMetab = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pMetab != NULL);
  CPPUNIT_ASSERT(pMetab->getObjectName() == "A");
  CPPUNIT_ASSERT(pMetab->getStatus() == CModelEntity::Status::REACTIONS);
  pMetab = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pMetab != NULL);
  CPPUNIT_ASSERT(pMetab->getObjectName() == "B");
  CPPUNIT_ASSERT(pMetab->getStatus() == CModelEntity::Status::REACTIONS);

  pMetab = pModel->getMetabolites()[2];
  CPPUNIT_ASSERT(pMetab != NULL);
  CPPUNIT_ASSERT(pMetab->getObjectName() == "C");
  CPPUNIT_ASSERT(pMetab->getStatus() == CModelEntity::Status::ASSIGNMENT);
  // check assignment
  const CEvaluationTree* pTree = pMetab->getExpressionPtr();
  CPPUNIT_ASSERT(pTree != NULL);
  const CEvaluationNode* pRoot = pTree->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(dynamic_cast<const CEvaluationNodeCall*>(pRoot) != NULL);
  CPPUNIT_ASSERT(dynamic_cast<const CEvaluationNodeCall*>(pRoot)->getData() == "function_5");

  pMetab = pModel->getMetabolites()[3];
  CPPUNIT_ASSERT(pMetab != NULL);
  CPPUNIT_ASSERT(pMetab->getObjectName() == "D");
  CPPUNIT_ASSERT(pMetab->getStatus() == CModelEntity::Status::ODE);
  // check ode
  pTree = pMetab->getExpressionPtr();
  CPPUNIT_ASSERT(pTree != NULL);
  pRoot = pTree->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(dynamic_cast<const CEvaluationNodeCall*>(pRoot) != NULL);
  CPPUNIT_ASSERT(dynamic_cast<const CEvaluationNodeCall*>(pRoot)->getData() == "function_2");

  pMetab = pModel->getMetabolites()[4];
  CPPUNIT_ASSERT(pMetab != NULL);
  CPPUNIT_ASSERT(pMetab->getObjectName() == "E");
  CPPUNIT_ASSERT(pMetab->getStatus() == CModelEntity::Status::ODE);
  // check ode
  pTree = pMetab->getExpressionPtr();
  CPPUNIT_ASSERT(pTree != NULL);
  pRoot = pTree->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(dynamic_cast<const CEvaluationNodeCall*>(pRoot) != NULL);
  CPPUNIT_ASSERT(dynamic_cast<const CEvaluationNodeCall*>(pRoot)->getData() == "function_4");

  pMetab = pModel->getMetabolites()[5];
  CPPUNIT_ASSERT(pMetab != NULL);
  CPPUNIT_ASSERT(pMetab->getObjectName() == "F");
  CPPUNIT_ASSERT(pMetab->getStatus() == CModelEntity::Status::ODE);
  // check ode
  pTree = pMetab->getExpressionPtr();
  CPPUNIT_ASSERT(pTree != NULL);
  pRoot = pTree->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(dynamic_cast<const CEvaluationNodeCall*>(pRoot) != NULL);
  CPPUNIT_ASSERT(dynamic_cast<const CEvaluationNodeCall*>(pRoot)->getData() == "function_6");

  // check model values
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 3);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getObjectName() == "K1");
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::Status::ASSIGNMENT);
  // check assignment
  pTree = pModelValue->getExpressionPtr();
  CPPUNIT_ASSERT(pTree != NULL);
  pRoot = pTree->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(dynamic_cast<const CEvaluationNodeCall*>(pRoot) != NULL);
  CPPUNIT_ASSERT(dynamic_cast<const CEvaluationNodeCall*>(pRoot)->getData() == "function_1");

  pModelValue = pModel->getModelValues()[1];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getObjectName() == "K2");
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::Status::FIXED);

  pModelValue = pModel->getModelValues()[2];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getObjectName() == "K3");
  // check assignment
  pTree = pModelValue->getExpressionPtr();
  CPPUNIT_ASSERT(pTree != NULL);
  pRoot = pTree->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(dynamic_cast<const CEvaluationNodeCall*>(pRoot) != NULL);
  CPPUNIT_ASSERT(dynamic_cast<const CEvaluationNodeCall*>(pRoot)->getData() == "function_3");

  CPPUNIT_ASSERT(pModel->getReactions().size() == 6);
  // check reactions
  const CReaction* pReaction = pModel->getReactions()[0];
  CPPUNIT_ASSERT(pReaction != NULL);
  CPPUNIT_ASSERT(pReaction->getChemEq().getSubstrates().size() == 1);
  CPPUNIT_ASSERT(pReaction->getChemEq().getProducts().size() == 1);
  CPPUNIT_ASSERT(pReaction->getChemEq().getModifiers().size() == 0);
  CPPUNIT_ASSERT(pReaction->isReversible() == true);
  // check the kinetic law
  CPPUNIT_ASSERT(pReaction->getParameters().size() == 1);
  const CFunction* pFunction = pReaction->getFunction();
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CEvaluationTree::UserDefined);
  CPPUNIT_ASSERT(pFunction->getObjectName() == "Function for reaction1");
  pRoot = pFunction->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);

  pReaction = pModel->getReactions()[1];
  CPPUNIT_ASSERT(pReaction != NULL);
  CPPUNIT_ASSERT(pReaction->getChemEq().getSubstrates().size() == 1);
  CPPUNIT_ASSERT(pReaction->getChemEq().getProducts().size() == 1);
  CPPUNIT_ASSERT(pReaction->getChemEq().getModifiers().size() == 0);
  CPPUNIT_ASSERT(pReaction->isReversible() == true);
  // check the kinetic law
  CPPUNIT_ASSERT(pReaction->getParameters().size() == 2);
  pFunction = pReaction->getFunction();
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CEvaluationTree::UserDefined);
  CPPUNIT_ASSERT(pFunction->getObjectName() == "Function for reaction2");
  pRoot = pFunction->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);

  pReaction = pModel->getReactions()[2];
  CPPUNIT_ASSERT(pReaction != NULL);
  CPPUNIT_ASSERT(pReaction->getChemEq().getSubstrates().size() == 1);
  CPPUNIT_ASSERT(pReaction->getChemEq().getProducts().size() == 1);
  CPPUNIT_ASSERT(pReaction->getChemEq().getModifiers().size() == 0);
  CPPUNIT_ASSERT(pReaction->isReversible() == true);
  // check the kinetic law
  CPPUNIT_ASSERT(pReaction->getParameters().size() == 1);
  pFunction = pReaction->getFunction();
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CEvaluationTree::UserDefined);
  CPPUNIT_ASSERT(pFunction->getObjectName() == "Function for reaction3");
  pRoot = pFunction->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);

  pReaction = pModel->getReactions()[3];
  CPPUNIT_ASSERT(pReaction != NULL);
  CPPUNIT_ASSERT(pReaction->getChemEq().getSubstrates().size() == 1);
  CPPUNIT_ASSERT(pReaction->getChemEq().getProducts().size() == 1);
  CPPUNIT_ASSERT(pReaction->getChemEq().getModifiers().size() == 0);
  CPPUNIT_ASSERT(pReaction->isReversible() == true);
  // check the kinetic law
  CPPUNIT_ASSERT(pReaction->getParameters().size() == 0);
  pFunction = pReaction->getFunction();
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CEvaluationTree::UserDefined);
  CPPUNIT_ASSERT(pFunction->getObjectName() == "Function for reaction4");
  pRoot = pFunction->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);

  pReaction = pModel->getReactions()[4];
  CPPUNIT_ASSERT(pReaction != NULL);
  CPPUNIT_ASSERT(pReaction->getChemEq().getSubstrates().size() == 1);
  CPPUNIT_ASSERT(pReaction->getChemEq().getProducts().size() == 1);
  CPPUNIT_ASSERT(pReaction->getChemEq().getModifiers().size() == 0);
  CPPUNIT_ASSERT(pReaction->isReversible() == true);
  // check the kinetic law
  CPPUNIT_ASSERT(pReaction->getParameters().size() == 2);
  pFunction = pReaction->getFunction();
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CEvaluationTree::UserDefined);
  CPPUNIT_ASSERT(pFunction->getObjectName() == "Function for reaction5");
  pRoot = pFunction->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);

  pReaction = pModel->getReactions()[5];
  CPPUNIT_ASSERT(pReaction != NULL);
  CPPUNIT_ASSERT(pReaction->getChemEq().getSubstrates().size() == 1);
  CPPUNIT_ASSERT(pReaction->getChemEq().getProducts().size() == 1);
  CPPUNIT_ASSERT(pReaction->getChemEq().getModifiers().size() == 0);
  CPPUNIT_ASSERT(pReaction->isReversible() == true);
  // check the kinetic law
  CPPUNIT_ASSERT(pReaction->getParameters().size() == 3);
  pFunction = pReaction->getFunction();
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CEvaluationTree::UserDefined);
  CPPUNIT_ASSERT(pFunction->getObjectName() == "Function for reaction6");
  pRoot = pFunction->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);

  // export to SBML
  std::string s = pDataModel->exportSBMLToString(NULL, 1, 2);
  CPPUNIT_ASSERT(s.empty() == false);
  // due to the bugfix for Bug 1086 and some issues with libsbml and the current exporter,
  // we now no longer have a L1 document in the datamodel if there was an SBMLDocument prior
  // to exporting to L1 already.
  // To test now, we have to call newModel on the datamodel to delete the old sbml document,
  // and reimport the exported model
  // This will also lead to a Level 2 Version 1 model since we convert all Level 1 model to
  //  Level 2 Version 1 on import, but we can at least test if the export worked.
  pCOPASIDATAMODEL->newModel(NULL, true);
  CPPUNIT_ASSERT(pCOPASIDATAMODEL->importSBMLFromString(s));
  // check the sbml model
  const SBMLDocument* pDocument = pCOPASIDATAMODEL->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  CPPUNIT_ASSERT(pDocument->getLevel() == 2);
  CPPUNIT_ASSERT(pDocument->getVersion() == 1);
  const Model* pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);

  CPPUNIT_ASSERT(pSBMLModel->getListOfFunctionDefinitions()->size() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getListOfCompartments()->size() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getListOfSpecies()->size() == 6);
  CPPUNIT_ASSERT(pSBMLModel->getListOfParameters()->size() == 3);
  CPPUNIT_ASSERT(pSBMLModel->getListOfRules()->size() == 6);
  CPPUNIT_ASSERT(pSBMLModel->getListOfReactions()->size() == 6);

  std::map<std::string, const Rule*> ruleMap;
  unsigned int i, iMax = pSBMLModel->getListOfRules()->size();
  const Rule* pRule = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pRule = pSBMLModel->getRule(i);
      ruleMap.insert(std::pair<std::string, const Rule*>(pRule->getVariable(), pRule));
    }

  // check the rules
  std::map<std::string, const Rule*>::const_iterator pos = ruleMap.find("parameter_1");
  CPPUNIT_ASSERT(pos != ruleMap.end());
  pRule = pos->second;
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getVariable() == "parameter_1");
  const ASTNode* pMath = pRule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // only check the infix
  std::string formula = pRule->getFormula();
  CPPUNIT_ASSERT(formula == "3 * 4.5");

  pos = ruleMap.find("parameter_3");
  CPPUNIT_ASSERT(pos != ruleMap.end());
  pRule = pos->second;
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getVariable() == "parameter_3");
  pRule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // only check the infix
  formula = pRule->getFormula();
  CPPUNIT_ASSERT(formula == "parameter_1 - 2 * 1.3");

  pos = ruleMap.find("species_3");
  CPPUNIT_ASSERT(pos != ruleMap.end());
  pRule = pos->second;
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getVariable() == "species_3");
  pRule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // only check the infix
  formula = pRule->getFormula();
  CPPUNIT_ASSERT(formula == "parameter_1 - 3.5 * 1.3 + (3 * 2.4 - 5.23)");

  pos = ruleMap.find("species_4");
  CPPUNIT_ASSERT(pos != ruleMap.end());
  pRule = pos->second;
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getVariable() == "species_4");
  pRule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // only check the infix
  formula = pRule->getFormula();
  CPPUNIT_ASSERT(formula == "3.4 + parameter_1");

  pos = ruleMap.find("species_5");
  CPPUNIT_ASSERT(pos != ruleMap.end());
  pRule = pos->second;
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getVariable() == "species_5");
  pRule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // only check the infix
  formula = pRule->getFormula();
  CPPUNIT_ASSERT(formula == "(parameter_2 + 1.4) / 2");

  pos = ruleMap.find("species_6");
  CPPUNIT_ASSERT(pos != ruleMap.end());
  pRule = pos->second;
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getVariable() == "species_6");
  pRule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // only check the infix
  formula = pRule->getFormula();
  CPPUNIT_ASSERT(formula == "parameter_3 - 3.4 * 1.3 + (3 * parameter_1 - 5.23)");

  // check the reactions
  const Reaction* pSBMLReaction = pSBMLModel->getReaction(0);
  CPPUNIT_ASSERT(pSBMLReaction != NULL);
  CPPUNIT_ASSERT(pSBMLReaction->getListOfReactants()->size() == 1);
  CPPUNIT_ASSERT(pSBMLReaction->getListOfProducts()->size() == 1);
  CPPUNIT_ASSERT(pSBMLReaction->getListOfModifiers()->size() == 0);
  CPPUNIT_ASSERT(pSBMLReaction->getReversible() == true);
  CPPUNIT_ASSERT(pSBMLReaction->getKineticLaw() != NULL);
  CPPUNIT_ASSERT(pSBMLReaction->getKineticLaw()->getListOfParameters()->size() == 0);
  pMath = pSBMLReaction->getKineticLaw()->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  formula = pSBMLReaction->getKineticLaw()->getFormula();
  CPPUNIT_ASSERT(formula == "compartment_1 * 3 * parameter_1");

  pSBMLReaction = pSBMLModel->getReaction(1);
  CPPUNIT_ASSERT(pSBMLReaction != NULL);
  CPPUNIT_ASSERT(pSBMLReaction->getListOfReactants()->size() == 1);
  CPPUNIT_ASSERT(pSBMLReaction->getListOfProducts()->size() == 1);
  CPPUNIT_ASSERT(pSBMLReaction->getListOfModifiers()->size() == 0);
  CPPUNIT_ASSERT(pSBMLReaction->getReversible() == true);
  CPPUNIT_ASSERT(pSBMLReaction->getKineticLaw() != NULL);
  CPPUNIT_ASSERT(pSBMLReaction->getKineticLaw()->getListOfParameters()->size() == 0);
  pMath = pSBMLReaction->getKineticLaw()->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  formula = pSBMLReaction->getKineticLaw()->getFormula();
  CPPUNIT_ASSERT(formula == "compartment_1 * (parameter_2 + parameter_1)");

  pSBMLReaction = pSBMLModel->getReaction(2);
  CPPUNIT_ASSERT(pSBMLReaction != NULL);
  CPPUNIT_ASSERT(pSBMLReaction->getListOfReactants()->size() == 1);
  CPPUNIT_ASSERT(pSBMLReaction->getListOfProducts()->size() == 1);
  CPPUNIT_ASSERT(pSBMLReaction->getListOfModifiers()->size() == 0);
  CPPUNIT_ASSERT(pSBMLReaction->getReversible() == true);
  CPPUNIT_ASSERT(pSBMLReaction->getKineticLaw() != NULL);
  CPPUNIT_ASSERT(pSBMLReaction->getKineticLaw()->getListOfParameters()->size() == 0);
  pMath = pSBMLReaction->getKineticLaw()->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  formula = pSBMLReaction->getKineticLaw()->getFormula();
  CPPUNIT_ASSERT(formula == "compartment_1 * (species_2 - parameter_1 * 1.3)");

  pSBMLReaction = pSBMLModel->getReaction(3);
  CPPUNIT_ASSERT(pSBMLReaction != NULL);
  CPPUNIT_ASSERT(pSBMLReaction->getListOfReactants()->size() == 1);
  CPPUNIT_ASSERT(pSBMLReaction->getListOfProducts()->size() == 1);
  CPPUNIT_ASSERT(pSBMLReaction->getListOfModifiers()->size() == 0);
  CPPUNIT_ASSERT(pSBMLReaction->getReversible() == true);
  CPPUNIT_ASSERT(pSBMLReaction->getKineticLaw() != NULL);
  CPPUNIT_ASSERT(pSBMLReaction->getKineticLaw()->getListOfParameters()->size() == 0);
  pMath = pSBMLReaction->getKineticLaw()->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  formula = pSBMLReaction->getKineticLaw()->getFormula();
  CPPUNIT_ASSERT(formula == "compartment_1 * ((species_2 + species_1) / 2)");

  pSBMLReaction = pSBMLModel->getReaction(4);
  CPPUNIT_ASSERT(pSBMLReaction != NULL);
  CPPUNIT_ASSERT(pSBMLReaction->getListOfReactants()->size() == 1);
  CPPUNIT_ASSERT(pSBMLReaction->getListOfProducts()->size() == 1);
  CPPUNIT_ASSERT(pSBMLReaction->getListOfModifiers()->size() == 0);
  CPPUNIT_ASSERT(pSBMLReaction->getReversible() == true);
  CPPUNIT_ASSERT(pSBMLReaction->getKineticLaw() != NULL);
  CPPUNIT_ASSERT(pSBMLReaction->getKineticLaw()->getListOfParameters()->size() == 0);
  pMath = pSBMLReaction->getKineticLaw()->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  formula = pSBMLReaction->getKineticLaw()->getFormula();
  CPPUNIT_ASSERT(formula == "compartment_1 * (parameter_1 - species_2 * 1.3 + (3 * parameter_3 - 5.23))");

  pSBMLReaction = pSBMLModel->getReaction(5);
  CPPUNIT_ASSERT(pSBMLReaction != NULL);
  CPPUNIT_ASSERT(pSBMLReaction->getListOfReactants()->size() == 1);
  CPPUNIT_ASSERT(pSBMLReaction->getListOfProducts()->size() == 1);
  CPPUNIT_ASSERT(pSBMLReaction->getListOfModifiers()->size() == 0);
  CPPUNIT_ASSERT(pSBMLReaction->getReversible() == true);
  CPPUNIT_ASSERT(pSBMLReaction->getKineticLaw() != NULL);
  CPPUNIT_ASSERT(pSBMLReaction->getKineticLaw()->getListOfParameters()->size() == 0);
  pMath = pSBMLReaction->getKineticLaw()->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  formula = pSBMLReaction->getKineticLaw()->getFormula();
  CPPUNIT_ASSERT(formula == "compartment_1 * (parameter_1 - parameter_3 * 1.3 + (3 * parameter_2 - 5.23))");
}

const char* test000068::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">\n"
  "  <model id=\"Model_1\" name=\"New Model\">\n"
  "    <notes>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        <p>Model with function call in kinetics and rules.</p>\n"
  "        <p>This is to check function expansion for export to L1V2</p>\n"
  "      </body>\n"
  "    </notes>\n"
  "    <listOfFunctionDefinitions>\n"
  "      <functionDefinition id=\"function_1\" name=\"function_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <lambda>\n"
  "            <bvar>\n"
  "              <ci> k </ci>\n"
  "            </bvar>\n"
  "            <apply>\n"
  "              <times/>\n"
  "              <cn> 3.0 </cn>\n"
  "              <ci> k </ci>\n"
  "            </apply>\n"
  "          </lambda>\n"
  "        </math>\n"
  "      </functionDefinition>\n"
  "      <functionDefinition id=\"function_2\" name=\"function_2\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <lambda>\n"
  "            <bvar>\n"
  "              <ci> A </ci>\n"
  "            </bvar>\n"
  "            <bvar>\n"
  "              <ci> B </ci>\n"
  "            </bvar>\n"
  "            <apply>\n"
  "              <plus/>\n"
  "              <ci> B </ci>\n"
  "              <ci> A </ci>\n"
  "            </apply>\n"
  "          </lambda>\n"
  "        </math>\n"
  "      </functionDefinition>\n"
  "      <functionDefinition id=\"function_3\" name=\"function_3\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <lambda>\n"
  "            <bvar>\n"
  "              <ci> k </ci>\n"
  "            </bvar>\n"
  "            <bvar>\n"
  "              <ci> C </ci>\n"
  "            </bvar>\n"
  "            <apply>\n"
  "              <minus/>\n"
  "              <ci> C </ci>\n"
  "              <apply>\n"
  "                <times/>\n"
  "                <ci> k </ci>\n"
  "                <cn> 1.3 </cn>\n"
  "              </apply>\n"
  "            </apply>\n"
  "          </lambda>\n"
  "        </math>\n"
  "      </functionDefinition>\n"
  "      <functionDefinition id=\"function_4\" name=\"function_4\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <lambda>\n"
  "            <bvar>\n"
  "              <ci> x </ci>\n"
  "            </bvar>\n"
  "            <bvar>\n"
  "              <ci> y </ci>\n"
  "            </bvar>\n"
  "            <apply>\n"
  "              <divide/>\n"
  "                <apply>\n"
  "                  <ci> function_2 </ci>\n"
  "                  <ci> x </ci>\n"
  "                  <ci> y </ci>\n"
  "                </apply>\n"
  "                <cn> 2.0 </cn>\n"
  "            </apply>\n"
  "          </lambda>\n"
  "        </math>\n"
  "      </functionDefinition>\n"
  "      <functionDefinition id=\"function_5\" name=\"function_5\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <lambda>\n"
  "            <bvar>\n"
  "              <ci> a </ci>\n"
  "            </bvar>\n"
  "            <bvar>\n"
  "              <ci> b </ci>\n"
  "            </bvar>\n"
  "            <bvar>\n"
  "              <ci> c </ci>\n"
  "            </bvar>\n"
  "            <apply>\n"
  "              <plus/>\n"
  "              <apply>\n"
  "                <ci> function_3 </ci>\n"
  "                <ci> c </ci>\n"
  "                <ci> a </ci>\n"
  "              </apply>\n"
  "              <apply>\n"
  "                <minus/>\n"
  "                <apply>\n"
  "                  <ci> function_1 </ci>\n"
  "                  <ci> b </ci>\n"
  "                </apply>\n"
  "                <cn> 5.23 </cn>\n"
  "              </apply>\n"
  "            </apply>\n"
  "          </lambda>\n"
  "        </math>\n"
  "      </functionDefinition>\n"
  "      <functionDefinition id=\"function_6\" name=\"function_6\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <lambda>\n"
  "            <bvar>\n"
  "              <ci> k1 </ci>\n"
  "            </bvar>\n"
  "            <bvar>\n"
  "              <ci> k2 </ci>\n"
  "            </bvar>\n"
  "            <bvar>\n"
  "              <ci> k3 </ci>\n"
  "            </bvar>\n"
  "            <apply>\n"
  "              <ci> function_5 </ci>\n"
  "              <ci> k1 </ci>\n"
  "              <ci> k2 </ci>\n"
  "              <ci> k3 </ci>\n"
  "            </apply>\n"
  "          </lambda>\n"
  "        </math>\n"
  "      </functionDefinition>\n"
  "    </listOfFunctionDefinitions>\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\"/>\n"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>\n"
  "      <species id=\"species_3\" name=\"C\" compartment=\"compartment_1\" initialConcentration=\"1\" constant=\"false\"/>\n"
  "      <species id=\"species_4\" name=\"D\" compartment=\"compartment_1\" initialConcentration=\"1\" constant=\"false\"/>\n"
  "      <species id=\"species_5\" name=\"E\" compartment=\"compartment_1\" initialConcentration=\"1\" constant=\"false\"/>\n"
  "      <species id=\"species_6\" name=\"F\" compartment=\"compartment_1\" initialConcentration=\"1\" constant=\"false\"/>\n"
  "    </listOfSpecies>\n"
  "    <listOfParameters>\n"
  "      <parameter id=\"parameter_1\" name=\"K1\" value=\"1.1\" constant=\"false\"/>\n"
  "      <parameter id=\"parameter_2\" name=\"K2\" value=\"1.2\"/>\n"
  "      <parameter id=\"parameter_3\" name=\"K3\" value=\"1.3\" constant=\"false\"/>\n"
  "    </listOfParameters>\n"
  "    <listOfRules>\n"
  "     <assignmentRule variable=\"parameter_1\">\n"
  "       <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "        <apply>\n"
  "          <ci> function_1 </ci>\n"
  "          <cn> 4.5 </cn>\n"
  "        </apply>\n"
  "       </math>\n"
  "     </assignmentRule>\n"
  "     <assignmentRule variable=\"parameter_3\">\n"
  "       <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "        <apply>\n"
  "          <ci> function_3 </ci>\n"
  "          <cn> 2.0 </cn>\n"
  "          <ci> parameter_1 </ci>\n"
  "        </apply>\n"
  "       </math>\n"
  "     </assignmentRule>\n"
  "     <assignmentRule variable=\"species_3\">\n"
  "       <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "        <apply>\n"
  "          <ci> function_5 </ci>\n"
  "          <ci> parameter_1 </ci>\n"
  "          <cn> 2.4 </cn>\n"
  "          <cn> 3.5 </cn>\n"
  "        </apply>\n"
  "       </math>\n"
  "     </assignmentRule>\n"
  "     <rateRule variable=\"species_4\">\n"
  "       <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "        <apply>\n"
  "          <ci> function_2 </ci>\n"
  "          <ci> parameter_1 </ci>\n"
  "          <cn> 3.4 </cn>\n"
  "        </apply>\n"
  "       </math>\n"
  "     </rateRule>\n"
  "     <rateRule variable=\"species_5\">\n"
  "       <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "        <apply>\n"
  "          <ci> function_4 </ci>\n"
  "          <cn> 1.4 </cn>\n"
  "          <ci> parameter_2 </ci>\n"
  "        </apply>\n"
  "       </math>\n"
  "     </rateRule>\n"
  "     <rateRule variable=\"species_6\">\n"
  "       <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "        <apply>\n"
  "          <ci> function_6 </ci>\n"
  "          <ci> parameter_3 </ci>\n"
  "          <ci> parameter_1 </ci>\n"
  "          <cn> 3.4 </cn>\n"
  "        </apply>\n"
  "       </math>\n"
  "     </rateRule>\n"
  "    </listOfRules>\n"
  "  <listOfReactions>\n"
  "    <reaction id=\"reaction1\" reversible=\"true\">\n"
  "      <listOfReactants>\n"
  "        <speciesReference species=\"species_1\"/>\n"
  "      </listOfReactants>\n"
  "      <listOfProducts>\n"
  "        <speciesReference species=\"species_2\"/>\n"
  "      </listOfProducts>\n"
  "      <kineticLaw>\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <times/>\n"
  "            <ci> compartment_1 </ci>\n"
  "            <apply>\n"
  "              <ci> function_1 </ci>\n"
  "              <ci> parameter_1 </ci>\n"
  "            </apply>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </kineticLaw>\n"
  "    </reaction>\n"
  "    <reaction id=\"reaction2\" reversible=\"true\">\n"
  "      <listOfReactants>\n"
  "        <speciesReference species=\"species_1\"/>\n"
  "      </listOfReactants>\n"
  "      <listOfProducts>\n"
  "        <speciesReference species=\"species_2\"/>\n"
  "      </listOfProducts>\n"
  "      <kineticLaw>\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <times/>\n"
  "            <ci> compartment_1 </ci>\n"
  "            <apply>\n"
  "              <ci> function_2 </ci>\n"
  "              <ci> parameter_1 </ci>\n"
  "              <ci> parameter_2 </ci>\n"
  "            </apply>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </kineticLaw>\n"
  "    </reaction>\n"
  "    <reaction id=\"reaction3\" reversible=\"true\">\n"
  "      <listOfReactants>\n"
  "        <speciesReference species=\"species_1\"/>\n"
  "      </listOfReactants>\n"
  "      <listOfProducts>\n"
  "        <speciesReference species=\"species_2\"/>\n"
  "      </listOfProducts>\n"
  "      <kineticLaw>\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <times/>\n"
  "            <ci> compartment_1 </ci>\n"
  "            <apply>\n"
  "              <ci> function_3 </ci>\n"
  "              <ci> parameter_1 </ci>\n"
  "              <ci> species_2 </ci>\n"
  "            </apply>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </kineticLaw>\n"
  "    </reaction>\n"
  "    <reaction id=\"reaction4\" reversible=\"true\">\n"
  "      <listOfReactants>\n"
  "        <speciesReference species=\"species_1\"/>\n"
  "      </listOfReactants>\n"
  "      <listOfProducts>\n"
  "        <speciesReference species=\"species_2\"/>\n"
  "      </listOfProducts>\n"
  "      <kineticLaw>\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <times/>\n"
  "            <ci> compartment_1 </ci>\n"
  "            <apply>\n"
  "              <ci> function_4 </ci>\n"
  "              <ci> species_1 </ci>\n"
  "              <ci> species_2 </ci>\n"
  "            </apply>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </kineticLaw>\n"
  "    </reaction>\n"
  "    <reaction id=\"reaction5\" reversible=\"true\">\n"
  "      <listOfReactants>\n"
  "        <speciesReference species=\"species_1\"/>\n"
  "      </listOfReactants>\n"
  "      <listOfProducts>\n"
  "        <speciesReference species=\"species_2\"/>\n"
  "      </listOfProducts>\n"
  "      <kineticLaw>\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <times/>\n"
  "            <ci> compartment_1 </ci>\n"
  "            <apply>\n"
  "              <ci> function_5 </ci>\n"
  "              <ci> parameter_1 </ci>\n"
  "              <ci> parameter_3 </ci>\n"
  "              <ci> species_2 </ci>\n"
  "            </apply>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </kineticLaw>\n"
  "    </reaction>\n"
  "    <reaction id=\"reaction6\" reversible=\"true\">\n"
  "      <listOfReactants>\n"
  "        <speciesReference species=\"species_1\"/>\n"
  "      </listOfReactants>\n"
  "      <listOfProducts>\n"
  "        <speciesReference species=\"species_2\"/>\n"
  "      </listOfProducts>\n"
  "      <kineticLaw>\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <times/>\n"
  "            <ci> compartment_1 </ci>\n"
  "            <apply>\n"
  "              <ci> function_6 </ci>\n"
  "              <ci> parameter_1 </ci>\n"
  "              <ci> parameter_2 </ci>\n"
  "              <ci> parameter_3 </ci>\n"
  "            </apply>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </kineticLaw>\n"
  "    </reaction>\n"
  "  </listOfReactions>\n"
  "  </model>\n"
  "</sbml>\n"
  ;
