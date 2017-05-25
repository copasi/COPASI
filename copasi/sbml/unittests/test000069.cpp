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

#include "test000069.h"

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

/**
 * These tests are supposed to make sure that assignments on a species with the
 * hasOnlySubstanceUnits flag set are exported correctly.
 * It tests rules and event assignments with and without the flag set.
 */
CDataModel* test000069::pCOPASIDATAMODEL = NULL;

void test000069::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000069::tearDown()
{
  CRootContainer::destroy();
}

void test000069::test_bug1069()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000069::MODEL_STRING1);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument == NULL);
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
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 1, 2).empty() == false);
  // check the sbml model
  pDocument = pCOPASIDATAMODEL->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  CPPUNIT_ASSERT(pDocument->getLevel() == 1);
  CPPUNIT_ASSERT(pDocument->getVersion() == 2);
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

const char* test000069::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.4.27 (Debug) (http://www.copasi.org) at 2008-08-30 15:28:23 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"27\">\n"
  "  <ListOfFunctions>\n"
  "    <Function key=\"Function_37\" name=\"function_1\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        3*k\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_260\" name=\"k\" order=\"0\" role=\"variable\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_38\" name=\"function_2\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        B+A\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_258\" name=\"A\" order=\"0\" role=\"variable\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_243\" name=\"B\" order=\"1\" role=\"variable\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_39\" name=\"function_3\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        C-k*1.3\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_246\" name=\"k\" order=\"0\" role=\"variable\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_250\" name=\"C\" order=\"1\" role=\"variable\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_40\" name=\"function_4\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        function_2(x,y)/2\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_254\" name=\"x\" order=\"0\" role=\"variable\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_261\" name=\"y\" order=\"1\" role=\"variable\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_41\" name=\"function_5\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        function_3(c,a)+(function_1(b)-5.23)\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_262\" name=\"a\" order=\"0\" role=\"variable\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_263\" name=\"b\" order=\"1\" role=\"variable\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_264\" name=\"c\" order=\"2\" role=\"variable\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_42\" name=\"function_6\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        function_5(k1,k2,k3)\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_265\" name=\"k1\" order=\"0\" role=\"variable\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_266\" name=\"k2\" order=\"1\" role=\"variable\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_267\" name=\"k3\" order=\"2\" role=\"variable\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_54\" name=\"Function for reaction1\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        3*parameter_1\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_269\" name=\"parameter_1\" order=\"0\" role=\"constant\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_55\" name=\"Function for reaction2\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        parameter_2+parameter_1\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_272\" name=\"parameter_1\" order=\"0\" role=\"constant\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_273\" name=\"parameter_2\" order=\"1\" role=\"constant\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_56\" name=\"Function for reaction3\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        species_2-parameter_1*1.3\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_276\" name=\"parameter_1\" order=\"0\" role=\"constant\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_277\" name=\"species_2\" order=\"1\" role=\"product\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_57\" name=\"Function for reaction4\" type=\"UserDefined\" reversible=\"true\">\n"
  "      <Expression>\n"
  "        function_2(species_1,species_2)/2\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_280\" name=\"species_1\" order=\"0\" role=\"substrate\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_281\" name=\"species_2\" order=\"1\" role=\"product\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_58\" name=\"Function for reaction5\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        function_3(species_2,parameter_1)+(function_1(parameter_3)-5.23)\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_285\" name=\"parameter_1\" order=\"0\" role=\"constant\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_286\" name=\"parameter_3\" order=\"1\" role=\"constant\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_287\" name=\"species_2\" order=\"2\" role=\"product\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_59\" name=\"Function for reaction6\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        function_5(parameter_1,parameter_2,parameter_3)\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_291\" name=\"parameter_1\" order=\"0\" role=\"constant\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_292\" name=\"parameter_2\" order=\"1\" role=\"constant\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_293\" name=\"parameter_3\" order=\"2\" role=\"constant\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "  </ListOfFunctions>\n"
  "  <Model key=\"Model_1\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"l\" quantityUnit=\"mol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "  <p>Model with function call in kinetics and rules.</p>\n"
  "  <p>This is to check function expansion for export to L1V2</p>\n"
  "</body>\n"
  "\n"
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
  "      <Metabolite key=\"Metabolite_2\" name=\"C\" simulationType=\"assignment\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          function_5(&lt;CN=Root,Model=New Model,Vector=Values[K1],Reference=Value&gt;,2.4,3.5)\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_3\" name=\"D\" simulationType=\"ode\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          function_2(&lt;CN=Root,Model=New Model,Vector=Values[K1],Reference=Value&gt;,3.4)\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_4\" name=\"E\" simulationType=\"ode\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          function_4(1.4,&lt;CN=Root,Model=New Model,Vector=Values[K2],Reference=Value&gt;)\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_5\" name=\"F\" simulationType=\"ode\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          function_6(&lt;CN=Root,Model=New Model,Vector=Values[K3],Reference=Value&gt;,&lt;CN=Root,Model=New Model,Vector=Values[K1],Reference=Value&gt;,3.4)\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"K1\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          function_1(4.5)\n"
  "        </Expression>\n"
  "      </ModelValue>\n"
  "      <ModelValue key=\"ModelValue_1\" name=\"K2\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "      <ModelValue key=\"ModelValue_2\" name=\"K3\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          function_3(2,&lt;CN=Root,Model=New Model,Vector=Values[K1],Reference=Value&gt;)\n"
  "        </Expression>\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <ListOfReactions>\n"
  "      <Reaction key=\"Reaction_0\" name=\"reaction1\" reversible=\"true\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_81\" name=\"parameter_1\" value=\"1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_54\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_269\">\n"
  "              <SourceParameter reference=\"ModelValue_0\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "      <Reaction key=\"Reaction_1\" name=\"reaction2\" reversible=\"true\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_80\" name=\"parameter_1\" value=\"1\"/>\n"
  "          <Constant key=\"Parameter_79\" name=\"parameter_2\" value=\"1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_55\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_272\">\n"
  "              <SourceParameter reference=\"ModelValue_0\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_273\">\n"
  "              <SourceParameter reference=\"ModelValue_1\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "      <Reaction key=\"Reaction_2\" name=\"reaction3\" reversible=\"true\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_78\" name=\"parameter_1\" value=\"1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_56\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_276\">\n"
  "              <SourceParameter reference=\"ModelValue_0\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_277\">\n"
  "              <SourceParameter reference=\"Metabolite_1\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "      <Reaction key=\"Reaction_3\" name=\"reaction4\" reversible=\"true\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <KineticLaw function=\"Function_57\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_280\">\n"
  "              <SourceParameter reference=\"Metabolite_0\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_281\">\n"
  "              <SourceParameter reference=\"Metabolite_1\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "      <Reaction key=\"Reaction_4\" name=\"reaction5\" reversible=\"true\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_77\" name=\"parameter_1\" value=\"1\"/>\n"
  "          <Constant key=\"Parameter_76\" name=\"parameter_3\" value=\"1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_58\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_285\">\n"
  "              <SourceParameter reference=\"ModelValue_0\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_286\">\n"
  "              <SourceParameter reference=\"ModelValue_2\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_287\">\n"
  "              <SourceParameter reference=\"Metabolite_1\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "      <Reaction key=\"Reaction_5\" name=\"reaction6\" reversible=\"true\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_67\" name=\"parameter_1\" value=\"1\"/>\n"
  "          <Constant key=\"Parameter_68\" name=\"parameter_2\" value=\"1\"/>\n"
  "          <Constant key=\"Parameter_71\" name=\"parameter_3\" value=\"1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_59\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_291\">\n"
  "              <SourceParameter reference=\"ModelValue_0\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_292\">\n"
  "              <SourceParameter reference=\"ModelValue_1\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_293\">\n"
  "              <SourceParameter reference=\"ModelValue_2\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "    </ListOfReactions>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_3\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_4\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_5\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_2\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_2\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 6.0221415e+23 6.0221415e+23 6.0221415e+23 6.0221415e+23 6.0221415e+23 6.0221415e+23 1.1 1.3 1.2 1\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n"
  ;
