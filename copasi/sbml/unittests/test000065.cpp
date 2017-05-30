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

#include "test000065.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CReaction.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationNodeVariable.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Reaction.h"

#include "copasi/core/CRootContainer.h"

/**
 * These tests are supposed to make sure that assignments on a species with the
 * hasOnlySubstanceUnits flag set are exported correctly.
 * It tests rules and event assignments with and without the flag set.
 */
CDataModel* test000065::pCOPASIDATAMODEL = NULL;

void test000065::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000065::tearDown()
{
  CRootContainer::destroy();
}

void test000065::test_import_reaction_with_unsuitable_kinetic_1()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING1));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CUnit::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CUnit::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CUnit::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::Status::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 4);
  CPPUNIT_ASSERT(pModel->getReactions().size() == 1);
  const CReaction* pReaction = pModel->getReactions()[0];
  CPPUNIT_ASSERT(pReaction != NULL);
  CPPUNIT_ASSERT(pReaction->getChemEq().getSubstrates().size() == 2);
  CPPUNIT_ASSERT(pReaction->getChemEq().getProducts().size() == 2);
  CPPUNIT_ASSERT(pReaction->getChemEq().getModifiers().size() == 0);
  CPPUNIT_ASSERT(pReaction->isReversible() == false);
  const CFunction* pFunction = pReaction->getFunction();
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CEvaluationTree::UserDefined);
  CPPUNIT_ASSERT(pFunction->isReversible() == TriUnspecified);
  // just to be sure also check the tree
  const CEvaluationNode* pRoot = pFunction->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(pRoot->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pRoot->subType() == CEvaluationNode::SubType::DIVIDE);
  const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pRoot->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::MULTIPLY);
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  const CEvaluationNodeVariable* pVariableNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVariableNode != NULL);
  CPPUNIT_ASSERT(pVariableNode->getData() == "Vmax");
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  pVariableNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVariableNode != NULL);
  // can't check the variable name here since  I don't know what name has been
  // created for it
  pChild = dynamic_cast<const CEvaluationNode*>(pRoot->getChild()->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::PLUS);
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  pVariableNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVariableNode != NULL);
  CPPUNIT_ASSERT(pVariableNode->getData() == "Km");
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  pVariableNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVariableNode != NULL);
  // can't check the variable name here since  I don't know what name has been
  // created for it
}

void test000065::test_import_reaction_with_unsuitable_kinetic_2()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING2));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CUnit::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CUnit::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CUnit::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::Status::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 4);
  CPPUNIT_ASSERT(pModel->getReactions().size() == 1);
  const CReaction* pReaction = pModel->getReactions()[0];
  CPPUNIT_ASSERT(pReaction != NULL);
  CPPUNIT_ASSERT(pReaction->getChemEq().getSubstrates().size() == 2);
  CPPUNIT_ASSERT(pReaction->getChemEq().getProducts().size() == 2);
  CPPUNIT_ASSERT(pReaction->getChemEq().getModifiers().size() == 0);
  CPPUNIT_ASSERT(pReaction->isReversible() == false);
  const CFunction* pFunction = pReaction->getFunction();
  CPPUNIT_ASSERT(pFunction != NULL);
  CPPUNIT_ASSERT(pFunction->getType() == CEvaluationTree::UserDefined);
  CPPUNIT_ASSERT(pFunction->isReversible() == TriUnspecified);
  // just to be sure also check the tree
  const CEvaluationNode* pRoot = pFunction->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(pRoot->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pRoot->subType() == CEvaluationNode::SubType::DIVIDE);
  const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pRoot->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::MULTIPLY);
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  const CEvaluationNodeVariable* pVariableNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVariableNode != NULL);
  CPPUNIT_ASSERT(pVariableNode->getData() == "Vmax");
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  pVariableNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVariableNode != NULL);
  // can't check the variable name here since  I don't know what name has been
  // created for it
  pChild = dynamic_cast<const CEvaluationNode*>(pRoot->getChild()->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::PLUS);
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  pVariableNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVariableNode != NULL);
  CPPUNIT_ASSERT(pVariableNode->getData() == "Km");
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  pVariableNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVariableNode != NULL);
  // can't check the variable name here since  I don't know what name has been
  // created for it
}

const char* test000065::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with one reaction that uses a kinetic law that is not"
  "        suitable for the reaction.</p>"
  "        <p>The function created for this reaction should therefore be set"
  "        to TriUnspecified</p>"
  "      </body>"
  "    </notes>"
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
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "      <species id=\"species_3\" name=\"C\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "      <species id=\"species_4\" name=\"D\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "  <listOfReactions>"
  "    <reaction id=\"reaction1\" reversible=\"false\">"
  "      <listOfReactants>"
  "        <speciesReference species=\"species_1\"/>"
  "        <speciesReference species=\"species_2\"/>"
  "      </listOfReactants>"
  "      <listOfProducts>"
  "        <speciesReference species=\"species_3\"/>"
  "        <speciesReference species=\"species_4\"/>"
  "      </listOfProducts>"
  "      <kineticLaw>"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "          <apply>"
  "            <times/>"
  "            <ci> compartment_1 </ci>"
  "            <apply>"
  "              <divide/>"
  "              <apply>"
  "                <times/>"
  "                  <ci> Vmax </ci>"
  "                  <ci> species_1 </ci>"
  "              </apply>"
  "              <apply>"
  "                <plus/>"
  "                  <ci> Km </ci>"
  "                  <ci> species_1 </ci>"
  "              </apply>"
  "            </apply>"
  "          </apply>"
  "        </math>"
  "        <listOfParameters>"
  "          <parameter id=\"Vmax\" value=\"0.015\"/>"
  "          <parameter id=\"Km\" value=\"0.015\"/>"
  "        </listOfParameters>"
  "      </kineticLaw>"
  "    </reaction>"
  "   </listOfReactions>"
  "  </model>"
  "</sbml>"
  ;

const char* test000065::MODEL_STRING2 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with one reaction that uses a kinetic law that is not"
  "        suitable for the reaction.</p>"
  "        <p>The function created for this reaction should therefore be set"
  "        to TriUnspecified</p>"
  "      </body>"
  "    </notes>"
  "    <listOfFunctionDefinitions>"
  "      <functionDefinition id=\"function_1\" name=\"MM\">"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "          <lambda>"
  "            <bvar>"
  "              <ci> Vmax </ci>"
  "            </bvar>"
  "            <bvar>"
  "              <ci> Km </ci>"
  "            </bvar>"
  "            <bvar>"
  "              <ci> S </ci>"
  "            </bvar>"
  "            <apply>"
  "              <divide/>"
  "              <apply>"
  "                <times/>"
  "                  <ci> Vmax </ci>"
  "                  <ci> S </ci>"
  "              </apply>"
  "              <apply>"
  "                <plus/>"
  "                  <ci> Km </ci>"
  "                  <ci> S </ci>"
  "              </apply>"
  "            </apply>"
  "          </lambda>"
  "        </math>"
  "      </functionDefinition>"
  "    </listOfFunctionDefinitions>"
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
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "      <species id=\"species_3\" name=\"C\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "      <species id=\"species_4\" name=\"D\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "  <listOfReactions>"
  "    <reaction id=\"reaction1\" reversible=\"false\">"
  "      <listOfReactants>"
  "        <speciesReference species=\"species_1\"/>"
  "        <speciesReference species=\"species_2\"/>"
  "      </listOfReactants>"
  "      <listOfProducts>"
  "        <speciesReference species=\"species_3\"/>"
  "        <speciesReference species=\"species_4\"/>"
  "      </listOfProducts>"
  "      <kineticLaw>"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "          <apply>"
  "            <times/>"
  "            <ci> compartment_1 </ci>"
  "            <apply>"
  "              <ci> function_1 </ci>"
  "              <ci> Vmax </ci>"
  "              <ci> Km  </ci>"
  "              <ci> species_1 </ci>"
  "            </apply>"
  "          </apply>"
  "        </math>"
  "        <listOfParameters>"
  "          <parameter id=\"Vmax\" value=\"0.015\"/>"
  "          <parameter id=\"Km\" value=\"0.015\"/>"
  "        </listOfParameters>"
  "      </kineticLaw>"
  "    </reaction>"
  "  </listOfReactions>"
  "  </model>"
  "</sbml>"
  ;
