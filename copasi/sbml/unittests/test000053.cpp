// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000053.cpp,v $
//   $Revision: 1.1.2.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/03/08 21:27:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "test000053.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CMetab.h"
#include "copasi/function/CExpression.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationNodeLogical.h"
#include "copasi/function/CEvaluationNodeChoice.h"
#include "copasi/function/CEvaluationNodeNumber.h"
#include "copasi/function/CEvaluationNodeConstant.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Rule.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/math/ASTNode.h"

void test000053::setUp()
{
  // Create the root container.
  CCopasiContainer::init();

  // Create the global data model.
  CCopasiDataModel::Global = new CCopasiDataModel();
}

void test000053::tearDown()
{
  delete CCopasiDataModel::Global;
  CCopasiDataModel::Global = NULL;
  delete CCopasiContainer::Root;
  CCopasiContainer::Root = NULL;
}

void test000053::test1_bug1000()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000053::MODEL_STRING_1));
  const CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 0);
  CPPUNIT_ASSERT(pModel->getReactions().size() == 0);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 1);
  const CMetab* pMetab = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pMetab != NULL);
  CPPUNIT_ASSERT(pMetab->getObjectName() == "A");
  CPPUNIT_ASSERT(pMetab->getStatus() == CModelEntity::ASSIGNMENT);
  const CExpression* pExpr = pMetab->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pRoot = pExpr->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pRoot->getType()) == CEvaluationNode::CHOICE);
  const CEvaluationNodeChoice* pChoiceNode = dynamic_cast<const CEvaluationNodeChoice*>(pRoot);
  CPPUNIT_ASSERT(pChoiceNode != NULL);
  const CEvaluationNode* pChild1 = dynamic_cast<const CEvaluationNode*>(pChoiceNode->getChild());
  CPPUNIT_ASSERT(pChild1 != NULL);
  const CEvaluationNode* pChild2 = dynamic_cast<const CEvaluationNode*>(pChild1->getSibling());
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::NUMBER);
  CPPUNIT_ASSERT(((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pChild2->getType())) == CEvaluationNodeNumber::DOUBLE);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pChild2);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 0.5) / 0.5) < 1e-6);
  const CEvaluationNode* pChild3 = dynamic_cast<const CEvaluationNode*>(pChild2->getSibling());
  CPPUNIT_ASSERT(pChild3 != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pChild3->getType()) == CEvaluationNode::NUMBER);
  CPPUNIT_ASSERT(((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pChild3->getType())) == CEvaluationNodeNumber::DOUBLE);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pChild3);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 1.5) / 1.5) < 1e-6);
  CPPUNIT_ASSERT(pChild3->getSibling() == NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pChild1->getType()) == CEvaluationNode::LOGICAL);
  CPPUNIT_ASSERT(((CEvaluationNodeLogical::SubType)CEvaluationNode::subType(pChild1->getType())) == CEvaluationNodeLogical::GT);
  pChild1 = dynamic_cast<const CEvaluationNode*>(pChild1->getChild());
  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pChild1->getType()) == CEvaluationNode::NUMBER);
  CPPUNIT_ASSERT(((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pChild1->getType())) == CEvaluationNodeNumber::DOUBLE);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pChild1);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 3.0) / 3.0) < 1e-6);
  pChild2 = dynamic_cast<const CEvaluationNode*>(pChild1->getSibling());
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::NUMBER);
  CPPUNIT_ASSERT(((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pChild2->getType())) == CEvaluationNodeNumber::DOUBLE);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pChild2);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 4.0) / 4.0) < 1e-6);
}

const char* test000053::MODEL_STRING_1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model id=\"Model_1\" name=\"New Model\">\n"
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
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" boundaryCondition=\"true\"/>\n"
  "    </listOfSpecies>\n"
  "    <listOfRules>\n"
  "      <assignmentRule variable=\"species_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <piecewise>\n"
  "            <piece>\n"
  "              <cn> 0.5 </cn>\n"
  "              <apply>\n"
  "                <gt/>\n"
  "                <cn> 3 </cn>\n"
  "                <cn> 4 </cn>\n"
  "              </apply>\n"
  "            </piece>\n"
  "            <otherwise>\n"
  "              <cn> 1.5 </cn>\n"
  "            </otherwise>\n"
  "          </piecewise>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "    </listOfRules>\n"
  "  </model>\n"
  "</sbml>\n"
;

void test000053::test2_bug1000()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000053::MODEL_STRING_2));
  const CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 0);
  CPPUNIT_ASSERT(pModel->getReactions().size() == 0);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 1);
  const CMetab* pMetab = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pMetab != NULL);
  CPPUNIT_ASSERT(pMetab->getObjectName() == "A");
  CPPUNIT_ASSERT(pMetab->getStatus() == CModelEntity::ASSIGNMENT);
  const CExpression* pExpr = pMetab->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pRoot = pExpr->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pRoot->getType()) == CEvaluationNode::CONSTANT);
  const CEvaluationNodeConstant* pConstantNode = dynamic_cast<const CEvaluationNodeConstant*>(pRoot);
  CPPUNIT_ASSERT(pConstantNode != NULL);
  CPPUNIT_ASSERT(((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(pConstantNode->getType())) == CEvaluationNodeConstant::_NaN);
}

const char* test000053::MODEL_STRING_2 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model id=\"Model_1\" name=\"New Model\">\n"
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
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" boundaryCondition=\"true\"/>\n"
  "    </listOfSpecies>\n"
  "    <listOfRules>\n"
  "      <assignmentRule variable=\"species_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <piecewise>\n"
  "          </piecewise>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "    </listOfRules>\n"
  "  </model>\n"
  "</sbml>\n"
;

void test000053::test3_bug1000()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000053::MODEL_STRING_3));
  const CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 0);
  CPPUNIT_ASSERT(pModel->getReactions().size() == 0);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 1);
  const CMetab* pMetab = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pMetab != NULL);
  CPPUNIT_ASSERT(pMetab->getObjectName() == "A");
  CPPUNIT_ASSERT(pMetab->getStatus() == CModelEntity::ASSIGNMENT);
  const CExpression* pExpr = pMetab->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pRoot = pExpr->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pRoot->getType()) == CEvaluationNode::CHOICE);
  const CEvaluationNodeChoice* pChoiceNode = dynamic_cast<const CEvaluationNodeChoice*>(pRoot);
  CPPUNIT_ASSERT(pChoiceNode != NULL);
  const CEvaluationNode* pChild1 = dynamic_cast<const CEvaluationNode*>(pChoiceNode->getChild());
  CPPUNIT_ASSERT(pChild1 != NULL);
  const CEvaluationNode* pChild2 = dynamic_cast<const CEvaluationNode*>(pChild1->getSibling());
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::NUMBER);
  CPPUNIT_ASSERT(((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pChild2->getType())) == CEvaluationNodeNumber::DOUBLE);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pChild2);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 0.5) / 0.5) < 1e-6);
  const CEvaluationNode* pChild3 = dynamic_cast<const CEvaluationNode*>(pChild2->getSibling());
  CPPUNIT_ASSERT(pChild3 != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pChild3->getType()) == CEvaluationNode::CONSTANT);
  CPPUNIT_ASSERT(((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(pChild3->getType())) == CEvaluationNodeConstant::_NaN);
  pChild1 = dynamic_cast<const CEvaluationNode*>(pChild1->getChild());
  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pChild1->getType()) == CEvaluationNode::NUMBER);
  CPPUNIT_ASSERT(((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pChild1->getType())) == CEvaluationNodeNumber::DOUBLE);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pChild1);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 3.0) / 3.0) < 1e-6);
  pChild2 = dynamic_cast<const CEvaluationNode*>(pChild1->getSibling());
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::NUMBER);
  CPPUNIT_ASSERT(((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pChild2->getType())) == CEvaluationNodeNumber::DOUBLE);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pChild2);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 4.0) / 4.0) < 1e-6);
}

const char* test000053::MODEL_STRING_3 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model id=\"Model_1\" name=\"New Model\">\n"
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
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" boundaryCondition=\"true\"/>\n"
  "    </listOfSpecies>\n"
  "    <listOfRules>\n"
  "      <assignmentRule variable=\"species_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <piecewise>\n"
  "            <piece>\n"
  "              <cn> 0.5 </cn>\n"
  "              <apply>\n"
  "                <gt/>\n"
  "                <cn> 3 </cn>\n"
  "                <cn> 4 </cn>\n"
  "              </apply>\n"
  "            </piece>\n"
  "          </piecewise>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "    </listOfRules>\n"
  "  </model>\n"
  "</sbml>\n"
;

void test000053::test4_bug1000()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000053::MODEL_STRING_4));
  const CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 0);
  CPPUNIT_ASSERT(pModel->getReactions().size() == 0);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 1);
  const CMetab* pMetab = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pMetab != NULL);
  CPPUNIT_ASSERT(pMetab->getObjectName() == "A");
  CPPUNIT_ASSERT(pMetab->getStatus() == CModelEntity::ASSIGNMENT);
  const CExpression* pExpr = pMetab->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pRoot = pExpr->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pRoot->getType()) == CEvaluationNode::NUMBER);
  CPPUNIT_ASSERT(((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pRoot->getType())) == CEvaluationNodeNumber::DOUBLE);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pRoot);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 1.5) / 1.5) < 1e-6);
}

const char* test000053::MODEL_STRING_4 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model id=\"Model_1\" name=\"New Model\">\n"
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
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" boundaryCondition=\"true\"/>\n"
  "    </listOfSpecies>\n"
  "    <listOfRules>\n"
  "      <assignmentRule variable=\"species_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <piecewise>\n"
  "            <otherwise>\n"
  "              <cn> 1.5 </cn>\n"
  "            </otherwise>\n"
  "          </piecewise>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "    </listOfRules>\n"
  "  </model>\n"
  "</sbml>\n"
;

void test000053::test5_bug1000()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000053::MODEL_STRING_5));
  const CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 0);
  CPPUNIT_ASSERT(pModel->getReactions().size() == 0);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 1);
  const CMetab* pMetab = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pMetab != NULL);
  CPPUNIT_ASSERT(pMetab->getObjectName() == "A");
  CPPUNIT_ASSERT(pMetab->getStatus() == CModelEntity::ASSIGNMENT);
  const CExpression* pExpr = pMetab->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pRoot = pExpr->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pRoot->getType()) == CEvaluationNode::CHOICE);
  const CEvaluationNodeChoice* pChoiceNode = dynamic_cast<const CEvaluationNodeChoice*>(pRoot);
  CPPUNIT_ASSERT(pChoiceNode != NULL);
  const CEvaluationNode* pChild1 = dynamic_cast<const CEvaluationNode*>(pChoiceNode->getChild());
  CPPUNIT_ASSERT(pChild1 != NULL);
  const CEvaluationNode* pChild2 = dynamic_cast<const CEvaluationNode*>(pChild1->getSibling());
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::NUMBER);
  CPPUNIT_ASSERT(((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pChild2->getType())) == CEvaluationNodeNumber::DOUBLE);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pChild2);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 0.5) / 0.5) < 1e-6);
  const CEvaluationNode* pChild3 = dynamic_cast<const CEvaluationNode*>(pChild2->getSibling());
  CPPUNIT_ASSERT(pChild3 != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pChild3->getType()) == CEvaluationNode::NUMBER);
  CPPUNIT_ASSERT(((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pChild3->getType())) == CEvaluationNodeNumber::DOUBLE);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pChild3);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 1.5) / 1.5) < 1e-6);
  CPPUNIT_ASSERT(pChild3->getSibling() == NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pChild1->getType()) == CEvaluationNode::LOGICAL);
  CPPUNIT_ASSERT(((CEvaluationNodeLogical::SubType)CEvaluationNode::subType(pChild1->getType())) == CEvaluationNodeLogical::GT);
  pChild1 = dynamic_cast<const CEvaluationNode*>(pChild1->getChild());
  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pChild1->getType()) == CEvaluationNode::NUMBER);
  CPPUNIT_ASSERT(((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pChild1->getType())) == CEvaluationNodeNumber::DOUBLE);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pChild1);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 3.0) / 3.0) < 1e-6);
  pChild2 = dynamic_cast<const CEvaluationNode*>(pChild1->getSibling());
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::NUMBER);
  CPPUNIT_ASSERT(((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pChild2->getType())) == CEvaluationNodeNumber::DOUBLE);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pChild2);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 4.0) / 4.0) < 1e-6);
}

const char* test000053::MODEL_STRING_5 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model id=\"Model_1\" name=\"New Model\">\n"
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
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" boundaryCondition=\"true\"/>\n"
  "    </listOfSpecies>\n"
  "    <listOfRules>\n"
  "      <assignmentRule variable=\"species_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <piecewise>\n"
  "            <piece>\n"
  "              <cn> 0.5 </cn>\n"
  "              <apply>\n"
  "                <ge/>\n"
  "                <cn> 3 </cn>\n"
  "                <cn> 4 </cn>\n"
  "              </apply>\n"
  "            </piece>\n"
  "            <piece>\n"
  "              <cn> 0.5 </cn>\n"
  "              <apply>\n"
  "                <gt/>\n"
  "                <cn> 3 </cn>\n"
  "                <cn> 4 </cn>\n"
  "              </apply>\n"
  "            </piece>\n"
  "            <piece>\n"
  "              <cn> 0.5 </cn>\n"
  "              <apply>\n"
  "                <le/>\n"
  "                <cn> 3 </cn>\n"
  "                <cn> 4 </cn>\n"
  "              </apply>\n"
  "            </piece>\n"
  "            <piece>\n"
  "              <cn> 0.5 </cn>\n"
  "              <apply>\n"
  "                <eq/>\n"
  "                <cn> 3 </cn>\n"
  "                <cn> 4 </cn>\n"
  "              </apply>\n"
  "            </piece>\n"
  "            <otherwise>\n"
  "              <cn> 1.5 </cn>\n"
  "            </otherwise>\n"
  "          </piecewise>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "    </listOfRules>\n"
  "  </model>\n"
  "</sbml>\n"
;
