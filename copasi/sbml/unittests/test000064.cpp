// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000064.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/06/12 11:08:39 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "test000064.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CReaction.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CExpression.h"

#include "sbml/math/ASTNode.h"
#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Compartment.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/Rule.h"
#include "sbml/UnitDefinition.h"
#include "sbml/Unit.h"
#include "sbml/UnitKind.h"

/**
 * These tests are supposed to make sure that assignments on a species with the
 * hasOnlySubstanceUnits flag set are exported correctly.
 * It tests rules and event assignments with and without the flag set.
 */
void test000064::setUp()
{
  // Create the root container.
  CCopasiContainer::init();

  // Create the global data model.
  CCopasiDataModel::Global = new CCopasiDataModel;
}

void test000064::tearDown()
{
  delete CCopasiDataModel::Global;
  CCopasiDataModel::Global = NULL;
  delete CCopasiContainer::Root;
  CCopasiContainer::Root = NULL;
}

void test000064::test_import_rule_expression_and_hasOnlySubstanceUnits_1()
{
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING1));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CModel::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CModel::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CModel::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::ASSIGNMENT);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::REACTIONS);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::FIXED);
  const CExpression* pExpr = pA->getExpressionPtr();
  // check the expression
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OPERATOR);
  CPPUNIT_ASSERT((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pNode->getType()) == CEvaluationNodeOperator::DIVIDE);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCopasiObjectName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Volume"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pCompartment);
}

const char* test000064::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species where one has the hasOnlySubstanceUnits flag set to true. The units are set to ml and mMol. There is an assignment rule for the species with the hasOnlySubstanceUnits flag set to true.</p>"
  "        <p>The imported model should contain an assignment for the species that consists of the original expression divided by the volume of the compartment.</p>"
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
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" hasOnlySubstanceUnits=\"true\"/>"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfRules>"
  "      <assignmentRule variable=\"species_1\">"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "          <ci> parameter_1 </ci>"
  "        </math>"
  "      </assignmentRule>"
  "    </listOfRules>"
  "  </model>"
  "</sbml>"
;

void test000064::test_import_rule_expression_and_hasOnlySubstanceUnits_2()
{
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING2));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CModel::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CModel::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CModel::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::ASSIGNMENT);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::REACTIONS);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::FIXED);
  const CExpression* pExpr = pA->getExpressionPtr();
  // check the expression
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCopasiObjectName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
}

const char* test000064::MODEL_STRING2 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species where both have the hasOnlySubstanceUnits flag set to false. The units are set to ml and mMol. There is an assignment rule for the first species.</p>"
  "        <p>The imported model should contain an assignment for the species that consists of the original expression.</p>"
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
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" />"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfRules>"
  "      <assignmentRule variable=\"species_1\">"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "          <ci> parameter_1 </ci>"
  "        </math>"
  "      </assignmentRule>"
  "    </listOfRules>"
  "  </model>"
  "</sbml>"
;

void test000064::test_import_rule_expression_and_hasOnlySubstanceUnits_3()
{
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING3));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CModel::number);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CModel::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CModel::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::ASSIGNMENT);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::REACTIONS);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::FIXED);
  const CExpression* pExpr = pA->getExpressionPtr();
  // check the expression
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCopasiObjectName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
}

const char* test000064::MODEL_STRING3 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species where both have the hasOnlySubstanceUnits flag set to false. The units are set to ml and item. There is an assignment rule for the first species.</p>"
  "        <p>The imported model should contain an assignment for the species that consists of the original expression.</p>"
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
  "          <unit kind=\"item\" />"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>"
  "    </listOfCompartments>"
  "    <listOfSpecies>"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" />"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfRules>"
  "      <assignmentRule variable=\"species_1\">"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "          <ci> parameter_1 </ci>"
  "        </math>"
  "      </assignmentRule>"
  "    </listOfRules>"
  "  </model>"
  "</sbml>"
;

void test000064::test_import_rule_expression_and_hasOnlySubstanceUnits_4()
{
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING4));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CModel::number);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CModel::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CModel::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::ASSIGNMENT);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::REACTIONS);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::FIXED);
  const CExpression* pExpr = pA->getExpressionPtr();
  // check the expression
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OPERATOR);
  CPPUNIT_ASSERT((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pNode->getType()) == CEvaluationNodeOperator::DIVIDE);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCopasiObjectName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Volume"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pCompartment);
}

const char* test000064::MODEL_STRING4 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species where one has the hasOnlySubstanceUnits flag set to true. The units are set to ml and item. There is an assignment rule for the species with the hasOnlySubstanceUnits flag set to true.</p>"
  "        <p>The imported model should contain an assignment for the species that consists of the original expression divided by the volume of the compartment.</p>"
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
  "          <unit kind=\"item\" />"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>"
  "    </listOfCompartments>"
  "    <listOfSpecies>"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" hasOnlySubstanceUnits=\"true\" />"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfRules>"
  "      <assignmentRule variable=\"species_1\">"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "          <ci> parameter_1 </ci>"
  "        </math>"
  "      </assignmentRule>"
  "    </listOfRules>"
  "  </model>"
  "</sbml>"
;

void test000064::test_import_event_assignment_expression_and_hasOnlySubstanceUnits_1()
{
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING5));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CModel::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CModel::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CModel::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::REACTIONS);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::REACTIONS);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getEvents().size() == 1);
  const CEvent* pEvent = pModel->getEvents()[0];
  CPPUNIT_ASSERT(pEvent != NULL);
  // check the trigger expression
  const CExpression* pExpr = pEvent->getTriggerExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::LOGICAL);
  CPPUNIT_ASSERT((CEvaluationNodeLogical::SubType)CEvaluationNode::subType(pNode->getType()) == CEvaluationNodeLogical::GT);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCopasiObjectName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModel);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::NUMBER);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 2.0) / 2.0) < 1e-6);
  // check that there is no delay
  const CExpression* pExpression = pEvent->getDelayExpressionPtr();
  CPPUNIT_ASSERT(pExpression == NULL);
  CPPUNIT_ASSERT(pEvent->getNumAssignments() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignmentObjectKey(0);
  CPPUNIT_ASSERT(key == pA->getKey());
  pExpression = pEvent->getAssignmentExpressionPtr(0);
  CPPUNIT_ASSERT(pExpression != NULL);
  pNode = pExpression->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OPERATOR);
  CPPUNIT_ASSERT((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pNode->getType()) == CEvaluationNodeOperator::DIVIDE);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Volume"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pCompartment);
}

const char* test000064::MODEL_STRING5 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species where one has the hasOnlySubstanceUnits flag set to true. The units are set to ml and mMol. There is an event assignment for the species with the hasOnlySubstanceUnits flag set to true.</p>"
  "        <p>The imported model should contain an event assignment for the species that consists of the original expression divided by the volume of the compartment.</p>"
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
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" hasOnlySubstanceUnits=\"true\"/>"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfEvents>"
  "      <event>"
  "        <trigger>"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <apply>"
  "              <gt/>"
  "              <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/time\"> time </csymbol>"
  "              <cn> 2.0 </cn>"
  "            </apply>"
  "          </math>"
  "        </trigger>"
  "        <listOfEventAssignments>"
  "          <eventAssignment variable=\"species_1\">"
  "            <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "              <ci> parameter_1 </ci>"
  "            </math>"
  "          </eventAssignment>"
  "        </listOfEventAssignments>"
  "      </event>"
  "    </listOfEvents>"
  "  </model>"
  "</sbml>"
;

void test000064::test_import_event_assignment_expression_and_hasOnlySubstanceUnits_2()
{
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING6));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CModel::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CModel::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CModel::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::REACTIONS);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::REACTIONS);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getEvents().size() == 1);
  const CEvent* pEvent = pModel->getEvents()[0];
  CPPUNIT_ASSERT(pEvent != NULL);
  // check the trigger expression
  const CExpression* pExpr = pEvent->getTriggerExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::LOGICAL);
  CPPUNIT_ASSERT((CEvaluationNodeLogical::SubType)CEvaluationNode::subType(pNode->getType()) == CEvaluationNodeLogical::GT);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCopasiObjectName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModel);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::NUMBER);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 2.0) / 2.0) < 1e-6);
  // check that there is no delay
  const CExpression* pExpression = pEvent->getDelayExpressionPtr();
  CPPUNIT_ASSERT(pExpression == NULL);
  CPPUNIT_ASSERT(pEvent->getNumAssignments() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignmentObjectKey(0);
  CPPUNIT_ASSERT(key == pA->getKey());
  pExpression = pEvent->getAssignmentExpressionPtr(0);
  CPPUNIT_ASSERT(pExpression != NULL);
  pNode = pExpression->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
}

const char* test000064::MODEL_STRING6 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species where both have the hasOnlySubstanceUnits flag set to false. The units are set to ml and mMol. There is an event assignment for the first species.</p>"
  "        <p>The imported model should contain an event assignment for the species that consists of the original expression.</p>"
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
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" />"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfEvents>"
  "      <event>"
  "        <trigger>"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <apply>"
  "              <gt/>"
  "              <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/time\"> time </csymbol>"
  "              <cn> 2.0 </cn>"
  "            </apply>"
  "          </math>"
  "        </trigger>"
  "        <listOfEventAssignments>"
  "          <eventAssignment variable=\"species_1\">"
  "            <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "              <ci> parameter_1 </ci>"
  "            </math>"
  "          </eventAssignment>"
  "        </listOfEventAssignments>"
  "      </event>"
  "    </listOfEvents>"
  "  </model>"
  "</sbml>"
;

void test000064::test_import_event_assignment_expression_and_hasOnlySubstanceUnits_3()
{
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING7));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CModel::number);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CModel::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CModel::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::REACTIONS);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::REACTIONS);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getEvents().size() == 1);
  const CEvent* pEvent = pModel->getEvents()[0];
  CPPUNIT_ASSERT(pEvent != NULL);
  // check the trigger expression
  const CExpression* pExpr = pEvent->getTriggerExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::LOGICAL);
  CPPUNIT_ASSERT((CEvaluationNodeLogical::SubType)CEvaluationNode::subType(pNode->getType()) == CEvaluationNodeLogical::GT);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCopasiObjectName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModel);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::NUMBER);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 2.0) / 2.0) < 1e-6);
  // check that there is no delay
  const CExpression* pExpression = pEvent->getDelayExpressionPtr();
  CPPUNIT_ASSERT(pExpression == NULL);
  CPPUNIT_ASSERT(pEvent->getNumAssignments() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignmentObjectKey(0);
  CPPUNIT_ASSERT(key == pA->getKey());
  pExpression = pEvent->getAssignmentExpressionPtr(0);
  CPPUNIT_ASSERT(pExpression != NULL);
  pNode = pExpression->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
}

const char* test000064::MODEL_STRING7 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species where both have the hasOnlySubstanceUnits flag set to false. The units are set to ml and item. There is an event assignment for the first species.</p>"
  "        <p>The imported model should contain an event assignment for the species that consists of the original expression.</p>"
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
  "          <unit kind=\"item\" />"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>"
  "    </listOfCompartments>"
  "    <listOfSpecies>"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" />"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfEvents>"
  "      <event>"
  "        <trigger>"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <apply>"
  "              <gt/>"
  "              <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/time\"> time </csymbol>"
  "              <cn> 2.0 </cn>"
  "            </apply>"
  "          </math>"
  "        </trigger>"
  "        <listOfEventAssignments>"
  "          <eventAssignment variable=\"species_1\">"
  "            <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "              <ci> parameter_1 </ci>"
  "            </math>"
  "          </eventAssignment>"
  "        </listOfEventAssignments>"
  "      </event>"
  "    </listOfEvents>"
  "  </model>"
  "</sbml>"
;

void test000064::test_import_event_assignment_expression_and_hasOnlySubstanceUnits_4()
{
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING8));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CModel::number);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CModel::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CModel::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::REACTIONS);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::REACTIONS);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getEvents().size() == 1);
  const CEvent* pEvent = pModel->getEvents()[0];
  CPPUNIT_ASSERT(pEvent != NULL);
  // check the trigger expression
  const CExpression* pExpr = pEvent->getTriggerExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::LOGICAL);
  CPPUNIT_ASSERT((CEvaluationNodeLogical::SubType)CEvaluationNode::subType(pNode->getType()) == CEvaluationNodeLogical::GT);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCopasiObjectName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModel);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::NUMBER);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 2.0) / 2.0) < 1e-6);
  // check that there is no delay
  const CExpression* pExpression = pEvent->getDelayExpressionPtr();
  CPPUNIT_ASSERT(pExpression == NULL);
  CPPUNIT_ASSERT(pEvent->getNumAssignments() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignmentObjectKey(0);
  CPPUNIT_ASSERT(key == pA->getKey());
  pExpression = pEvent->getAssignmentExpressionPtr(0);
  CPPUNIT_ASSERT(pExpression != NULL);
  pNode = pExpression->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OPERATOR);
  CPPUNIT_ASSERT((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pNode->getType()) == CEvaluationNodeOperator::DIVIDE);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Volume"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pCompartment);
}

const char* test000064::MODEL_STRING8 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species where one has the hasOnlySubstanceUnits flag set to true. The units are set to ml and item. There is an event assignment for the species with the hasOnlySubstanceUnits flag set to true.</p>"
  "        <p>The imported model should contain an event assignment for the species that consists of the original expression divided by the volume of the compartment.</p>"
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
  "          <unit kind=\"item\" />"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>"
  "    </listOfCompartments>"
  "    <listOfSpecies>"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" hasOnlySubstanceUnits=\"true\" />"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfEvents>"
  "      <event>"
  "        <trigger>"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <apply>"
  "              <gt/>"
  "              <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/time\"> time </csymbol>"
  "              <cn> 2.0 </cn>"
  "            </apply>"
  "          </math>"
  "        </trigger>"
  "        <listOfEventAssignments>"
  "          <eventAssignment variable=\"species_1\">"
  "            <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "              <ci> parameter_1 </ci>"
  "            </math>"
  "          </eventAssignment>"
  "        </listOfEventAssignments>"
  "      </event>"
  "    </listOfEvents>"
  "  </model>"
  "</sbml>"
;

void test000064::test_import_rule_expression_and_hasOnlySubstanceUnits_5()
{
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING9));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CModel::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CModel::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CModel::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::ASSIGNMENT);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::REACTIONS);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::FIXED);
  const CExpression* pExpr = pA->getExpressionPtr();
  // check the expression
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCopasiObjectName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
}

const char* test000064::MODEL_STRING9 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species where one has the hasOnlySubstanceUnits flag set to true. The units are set to ml and mMol. There is an assignment rule for the species with the hasOnlySubstanceUnits flag set to true.</p>"
  "        <p>The imported model should contain an assignment for the species that consists a reference to the parameter.</p>"
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
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" hasOnlySubstanceUnits=\"true\"/>"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfRules>"
  "      <assignmentRule variable=\"species_1\">"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "          <apply>"
  "            <times/>"
  "            <ci> parameter_1 </ci>"
  "            <ci> compartment_1 </ci>"
  "          </apply>"
  "        </math>"
  "      </assignmentRule>"
  "    </listOfRules>"
  "  </model>"
  "</sbml>"
;

void test000064::test_import_rule_expression_and_hasOnlySubstanceUnits_6()
{
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING10));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CModel::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CModel::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CModel::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::ASSIGNMENT);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::REACTIONS);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::FIXED);
  const CExpression* pExpr = pA->getExpressionPtr();
  // check the expression
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OPERATOR);
  CPPUNIT_ASSERT((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pNode->getType()) == CEvaluationNodeOperator::MULTIPLY);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCopasiObjectName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Volume"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pCompartment);
}

const char* test000064::MODEL_STRING10 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species where both have the hasOnlySubstanceUnits flag set to false. The units are set to ml and mMol. There is an assignment rule for the first species.</p>"
  "        <p>The imported model should contain an assignment for the species that consists of a reference to the global parameter multiplied by the compartment volume.</p>"
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
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" />"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfRules>"
  "      <assignmentRule variable=\"species_1\">"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "          <apply>"
  "            <times/>"
  "            <ci> parameter_1 </ci>"
  "            <ci> compartment_1 </ci>"
  "          </apply>"
  "        </math>"
  "      </assignmentRule>"
  "    </listOfRules>"
  "  </model>"
  "</sbml>"
;

void test000064::test_import_rule_expression_and_hasOnlySubstanceUnits_7()
{
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING11));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CModel::number);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CModel::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CModel::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::ASSIGNMENT);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::REACTIONS);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::FIXED);
  const CExpression* pExpr = pA->getExpressionPtr();
  // check the expression
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OPERATOR);
  CPPUNIT_ASSERT((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pNode->getType()) == CEvaluationNodeOperator::MULTIPLY);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCopasiObjectName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Volume"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pCompartment);
}

const char* test000064::MODEL_STRING11 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species where both have the hasOnlySubstanceUnits flag set to false. The units are set to ml and item. There is an assignment rule for the first species.</p>"
  "        <p>The imported model should contain an assignment for the species that consists of a reference to the global parameter multiplied by the compartment volume.</p>"
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
  "          <unit kind=\"item\" />"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>"
  "    </listOfCompartments>"
  "    <listOfSpecies>"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" />"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfRules>"
  "      <assignmentRule variable=\"species_1\">"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "          <apply>"
  "            <times/>"
  "            <ci> parameter_1 </ci>"
  "            <ci> compartment_1 </ci>"
  "          </apply>"
  "        </math>"
  "      </assignmentRule>"
  "    </listOfRules>"
  "  </model>"
  "</sbml>"
;

void test000064::test_import_rule_expression_and_hasOnlySubstanceUnits_8()
{
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING12));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CModel::number);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CModel::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CModel::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::ASSIGNMENT);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::REACTIONS);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::FIXED);
  const CExpression* pExpr = pA->getExpressionPtr();
  // check the expression
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCopasiObjectName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
}

const char* test000064::MODEL_STRING12 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species where one has the hasOnlySubstanceUnits flag set to true. The units are set to ml and item. There is an assignment rule for the species with the hasOnlySubstanceUnits flag set to true.</p>"
  "        <p>The imported model should contain an assignment for the species that consists of a reference to the global parameter.</p>"
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
  "          <unit kind=\"item\" />"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>"
  "    </listOfCompartments>"
  "    <listOfSpecies>"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" hasOnlySubstanceUnits=\"true\" />"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfRules>"
  "      <assignmentRule variable=\"species_1\">"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "          <apply>"
  "            <times/>"
  "            <ci> parameter_1 </ci>"
  "            <ci> compartment_1 </ci>"
  "          </apply>"
  "        </math>"
  "      </assignmentRule>"
  "    </listOfRules>"
  "  </model>"
  "</sbml>"
;

void test000064::test_import_event_assignment_expression_and_hasOnlySubstanceUnits_5()
{
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING13));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CModel::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CModel::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CModel::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::REACTIONS);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::REACTIONS);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getEvents().size() == 1);
  const CEvent* pEvent = pModel->getEvents()[0];
  CPPUNIT_ASSERT(pEvent != NULL);
  // check the trigger expression
  const CExpression* pExpr = pEvent->getTriggerExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::LOGICAL);
  CPPUNIT_ASSERT((CEvaluationNodeLogical::SubType)CEvaluationNode::subType(pNode->getType()) == CEvaluationNodeLogical::GT);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCopasiObjectName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModel);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::NUMBER);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 2.0) / 2.0) < 1e-6);
  // check that there is no delay
  const CExpression* pExpression = pEvent->getDelayExpressionPtr();
  CPPUNIT_ASSERT(pExpression == NULL);
  CPPUNIT_ASSERT(pEvent->getNumAssignments() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignmentObjectKey(0);
  CPPUNIT_ASSERT(key == pA->getKey());
  pExpression = pEvent->getAssignmentExpressionPtr(0);
  CPPUNIT_ASSERT(pExpression != NULL);
  pNode = pExpression->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
}

const char* test000064::MODEL_STRING13 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species where one has the hasOnlySubstanceUnits flag set to true. The units are set to ml and mMol. There is an event assignment for the species with the hasOnlySubstanceUnits flag set to true.</p>"
  "        <p>The imported model should contain an event assignment for the species that consists of a reference to the global parameter.</p>"
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
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" hasOnlySubstanceUnits=\"true\"/>"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfEvents>"
  "      <event>"
  "        <trigger>"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <apply>"
  "              <gt/>"
  "              <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/time\"> time </csymbol>"
  "              <cn> 2.0 </cn>"
  "            </apply>"
  "          </math>"
  "        </trigger>"
  "        <listOfEventAssignments>"
  "          <eventAssignment variable=\"species_1\">"
  "            <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "              <apply>"
  "                <times/>"
  "                <ci> parameter_1 </ci>"
  "                <ci> compartment_1 </ci>"
  "              </apply>"
  "            </math>"
  "          </eventAssignment>"
  "        </listOfEventAssignments>"
  "      </event>"
  "    </listOfEvents>"
  "  </model>"
  "</sbml>"
;

void test000064::test_import_event_assignment_expression_and_hasOnlySubstanceUnits_6()
{
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING14));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CModel::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CModel::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CModel::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::REACTIONS);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::REACTIONS);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getEvents().size() == 1);
  const CEvent* pEvent = pModel->getEvents()[0];
  CPPUNIT_ASSERT(pEvent != NULL);
  // check the trigger expression
  const CExpression* pExpr = pEvent->getTriggerExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::LOGICAL);
  CPPUNIT_ASSERT((CEvaluationNodeLogical::SubType)CEvaluationNode::subType(pNode->getType()) == CEvaluationNodeLogical::GT);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCopasiObjectName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModel);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::NUMBER);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 2.0) / 2.0) < 1e-6);
  // check that there is no delay
  const CExpression* pExpression = pEvent->getDelayExpressionPtr();
  CPPUNIT_ASSERT(pExpression == NULL);
  CPPUNIT_ASSERT(pEvent->getNumAssignments() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignmentObjectKey(0);
  CPPUNIT_ASSERT(key == pA->getKey());
  pExpression = pEvent->getAssignmentExpressionPtr(0);
  CPPUNIT_ASSERT(pExpression != NULL);
  pNode = pExpression->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OPERATOR);
  CPPUNIT_ASSERT((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pNode->getType()) == CEvaluationNodeOperator::MULTIPLY);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Volume"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pCompartment);
}

const char* test000064::MODEL_STRING14 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species where both have the hasOnlySubstanceUnits flag set to false. The units are set to ml and mMol. There is an event assignment for the first species.</p>"
  "        <p>The imported model should contain an event assignment for the species that consists of a reference to the global parameter multiplied by the compartment volume.</p>"
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
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" />"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfEvents>"
  "      <event>"
  "        <trigger>"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <apply>"
  "              <gt/>"
  "              <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/time\"> time </csymbol>"
  "              <cn> 2.0 </cn>"
  "            </apply>"
  "          </math>"
  "        </trigger>"
  "        <listOfEventAssignments>"
  "          <eventAssignment variable=\"species_1\">"
  "            <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "              <apply>"
  "                <times/>"
  "                <ci> parameter_1 </ci>"
  "                <ci> compartment_1 </ci>"
  "              </apply>"
  "            </math>"
  "          </eventAssignment>"
  "        </listOfEventAssignments>"
  "      </event>"
  "    </listOfEvents>"
  "  </model>"
  "</sbml>"
;

void test000064::test_import_event_assignment_expression_and_hasOnlySubstanceUnits_7()
{
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING15));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CModel::number);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CModel::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CModel::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::REACTIONS);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::REACTIONS);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getEvents().size() == 1);
  const CEvent* pEvent = pModel->getEvents()[0];
  CPPUNIT_ASSERT(pEvent != NULL);
  // check the trigger expression
  const CExpression* pExpr = pEvent->getTriggerExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::LOGICAL);
  CPPUNIT_ASSERT((CEvaluationNodeLogical::SubType)CEvaluationNode::subType(pNode->getType()) == CEvaluationNodeLogical::GT);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCopasiObjectName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModel);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::NUMBER);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 2.0) / 2.0) < 1e-6);
  // check that there is no delay
  const CExpression* pExpression = pEvent->getDelayExpressionPtr();
  CPPUNIT_ASSERT(pExpression == NULL);
  CPPUNIT_ASSERT(pEvent->getNumAssignments() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignmentObjectKey(0);
  CPPUNIT_ASSERT(key == pA->getKey());
  pExpression = pEvent->getAssignmentExpressionPtr(0);
  CPPUNIT_ASSERT(pExpression != NULL);
  pNode = pExpression->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OPERATOR);
  CPPUNIT_ASSERT((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pNode->getType()) == CEvaluationNodeOperator::MULTIPLY);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Volume"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pCompartment);
}

const char* test000064::MODEL_STRING15 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species where both have the hasOnlySubstanceUnits flag set to false. The units are set to ml and item. There is an event assignment for the first species.</p>"
  "        <p>The imported model should contain an event assignment for the species that consists of a reference to the global parameter multiplied by the compartment volume.</p>"
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
  "          <unit kind=\"item\" />"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>"
  "    </listOfCompartments>"
  "    <listOfSpecies>"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" />"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfEvents>"
  "      <event>"
  "        <trigger>"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <apply>"
  "              <gt/>"
  "              <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/time\"> time </csymbol>"
  "              <cn> 2.0 </cn>"
  "            </apply>"
  "          </math>"
  "        </trigger>"
  "        <listOfEventAssignments>"
  "          <eventAssignment variable=\"species_1\">"
  "            <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "              <apply>"
  "                <times/>"
  "                <ci> parameter_1 </ci>"
  "                <ci> compartment_1 </ci>"
  "              </apply>"
  "            </math>"
  "          </eventAssignment>"
  "        </listOfEventAssignments>"
  "      </event>"
  "    </listOfEvents>"
  "  </model>"
  "</sbml>"
;

void test000064::test_import_event_assignment_expression_and_hasOnlySubstanceUnits_8()
{
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING16));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CModel::number);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CModel::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CModel::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::REACTIONS);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::REACTIONS);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getEvents().size() == 1);
  const CEvent* pEvent = pModel->getEvents()[0];
  CPPUNIT_ASSERT(pEvent != NULL);
  // check the trigger expression
  const CExpression* pExpr = pEvent->getTriggerExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::LOGICAL);
  CPPUNIT_ASSERT((CEvaluationNodeLogical::SubType)CEvaluationNode::subType(pNode->getType()) == CEvaluationNodeLogical::GT);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCopasiObjectName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModel);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::NUMBER);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 2.0) / 2.0) < 1e-6);
  // check that there is no delay
  const CExpression* pExpression = pEvent->getDelayExpressionPtr();
  CPPUNIT_ASSERT(pExpression == NULL);
  CPPUNIT_ASSERT(pEvent->getNumAssignments() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignmentObjectKey(0);
  CPPUNIT_ASSERT(key == pA->getKey());
  pExpression = pEvent->getAssignmentExpressionPtr(0);
  CPPUNIT_ASSERT(pExpression != NULL);
  pNode = pExpression->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
}

const char* test000064::MODEL_STRING16 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species where one has the hasOnlySubstanceUnits flag set to true. The units are set to ml and item. There is an event assignment for the species with the hasOnlySubstanceUnits flag set to true.</p>"
  "        <p>The imported model should contain an event assignment for the species that consists of a reference to the global parameter.</p>"
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
  "          <unit kind=\"item\" />"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>"
  "    </listOfCompartments>"
  "    <listOfSpecies>"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" hasOnlySubstanceUnits=\"true\" />"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfEvents>"
  "      <event>"
  "        <trigger>"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <apply>"
  "              <gt/>"
  "              <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/time\"> time </csymbol>"
  "              <cn> 2.0 </cn>"
  "            </apply>"
  "          </math>"
  "        </trigger>"
  "        <listOfEventAssignments>"
  "          <eventAssignment variable=\"species_1\">"
  "            <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "              <apply>"
  "                <times/>"
  "                <ci> parameter_1 </ci>"
  "                <ci> compartment_1 </ci>"
  "              </apply>"
  "            </math>"
  "          </eventAssignment>"
  "        </listOfEventAssignments>"
  "      </event>"
  "    </listOfEvents>"
  "  </model>"
  "</sbml>"
;

void test000064::test_export_rule_expression_and_hasOnlySubstanceUnits_1()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  std::istringstream iss(test000064::MODEL_STRING101);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 3).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // check the units
  UnitDefinition* pUDef = pModel->getUnitDefinition("time");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  Unit* pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_SECOND);
  CPPUNIT_ASSERT(pUnit->getScale() == 0);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  pUDef = pModel->getUnitDefinition("substance");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_MOLE);
  CPPUNIT_ASSERT(pUnit->getScale() == -3);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  pUDef = pModel->getUnitDefinition("volume");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_LITRE);
  CPPUNIT_ASSERT(pUnit->getScale() == -3);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  // assert that there is only one compartment and
  // assert the compartment is constant
  CPPUNIT_ASSERT(pModel->getNumCompartments() == 1);
  Compartment* pCompartment = pModel->getCompartment(0);
  CPPUNIT_ASSERT(pCompartment->getConstant() == true);
  CPPUNIT_ASSERT(pModel->getNumParameters() == 1);
  Parameter* pParameter = pModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter != NULL);
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  Species* pSpecies1 = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pSpecies1->getHasOnlySubstanceUnits() == false);
  std::string idSpeciesA = pSpecies1->getId();
  Species* pSpecies2 = pModel->getSpecies(1);
  CPPUNIT_ASSERT(pSpecies2->getHasOnlySubstanceUnits() == false);
  CPPUNIT_ASSERT(pModel->getNumRules() == 1);
  AssignmentRule* pRule = dynamic_cast<AssignmentRule*>(pModel->getRule(0));
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getVariable() == pSpecies1->getId());
  const ASTNode* pMath = pRule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains only one node that is a
  // reference to the global parameter
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter->getId());
  CPPUNIT_ASSERT(pModel->getNumReactions() == 0);
}

const char* test000064::MODEL_STRING101 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.4.26 (Debug) (http://www.copasi.org) at 2008-06-12 09:00:21 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"26\">\n"
  "  <Model key=\"Model_0\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:9pt;font-family:Sans Serif\">\n"
  "<p>Simple model with two species and a global parameter. The compartment is fixed and one species is determined by an assignment rule.</p>\n"
  "<p>The substance unit is set to mmol.</p>\n"
  "<p>On export both species should be exported with the hasOnlySubstanceUnits flag set to false and the expression for the assignment should contain only a reference to the global parameter.</p>\n"
  "</body></html>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"fixed\">\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"assignment\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Values[K],Reference=Value&gt;\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"B\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"K\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 1.2044283e+21 6.022141500000001e+20 2 1\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n"
;

void test000064::test_export_rule_expression_and_hasOnlySubstanceUnits_2()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  std::istringstream iss(test000064::MODEL_STRING102);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 3).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // check the units
  UnitDefinition* pUDef = pModel->getUnitDefinition("time");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  Unit* pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_SECOND);
  CPPUNIT_ASSERT(pUnit->getScale() == 0);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  pUDef = pModel->getUnitDefinition("substance");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_MOLE);
  CPPUNIT_ASSERT(pUnit->getScale() == -3);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  pUDef = pModel->getUnitDefinition("volume");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_LITRE);
  CPPUNIT_ASSERT(pUnit->getScale() == -3);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  // assert that there is only one compartment and
  // assert the compartment is not constant
  CPPUNIT_ASSERT(pModel->getNumCompartments() == 1);
  Compartment* pCompartment = pModel->getCompartment(0);
  CPPUNIT_ASSERT(pCompartment->getConstant() == false);
  CPPUNIT_ASSERT(pModel->getNumParameters() == 2);
  Parameter* pParameter1 = pModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter1 != NULL);
  Parameter* pParameter2 = NULL;
  if (pParameter1->getName() == "K")
    {
      pParameter2 = pModel->getParameter(1);
      CPPUNIT_ASSERT(pParameter2 != NULL);
    }
  else
    {
      pParameter2 = pParameter1;
      pParameter1 = pModel->getParameter(1);
      CPPUNIT_ASSERT(pParameter1 != NULL);
    }
  CPPUNIT_ASSERT(pParameter1->getName() == "K");
  CPPUNIT_ASSERT(pParameter2->getName() == "P");
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  Species* pSpecies1 = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pSpecies1->getHasOnlySubstanceUnits() == false);
  std::string idSpeciesA = pSpecies1->getId();
  Species* pSpecies2 = pModel->getSpecies(1);
  CPPUNIT_ASSERT(pSpecies2->getHasOnlySubstanceUnits() == false);
  CPPUNIT_ASSERT(pModel->getNumRules() == 2);
  AssignmentRule* pRule1 = dynamic_cast<AssignmentRule*>(pModel->getRule(0));
  AssignmentRule* pRule2 = NULL;
  CPPUNIT_ASSERT(pRule1 != NULL);
  if (pRule1->getVariable() == pSpecies1->getId())
    {
      pRule2 = pRule1;
      pRule1 = dynamic_cast<AssignmentRule*>(pModel->getRule(1));
    }
  else
    {
      pRule2 = dynamic_cast<AssignmentRule*>(pModel->getRule(1));
    }
  // check the rule for the compartment
  const ASTNode* pMath = pRule1->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains only one node that is a
  // reference to the global parameter P
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter2->getId());
  pMath = pRule2->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains a multiplication of the
  // global parameter K and the compartment volume
  CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  ASTNode* pChild1 = pMath->getChild(0);
  ASTNode* pChild2 = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild1->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild2->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild1->getName() == pParameter1->getId() || pChild2->getName() == pParameter1->getId());
  CPPUNIT_ASSERT(pChild1->getName() == pCompartment->getId() || pChild2->getName() == pCompartment->getId());
  CPPUNIT_ASSERT(pModel->getNumReactions() == 0);
}

const char* test000064::MODEL_STRING102 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.4.26 (Debug) (http://www.copasi.org) at 2008-06-12 09:00:21 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"26\">\n"
  "  <Model key=\"Model_0\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:9pt;font-family:Sans Serif\">\n"
  "<p>Simple model with two species and two global parameters. The compartment is variable and one species is determined by an assignment rule.</p>\n"
  "<p>The substance unit is set to mmol.</p>\n"
  "<p>On export both species should be exported with the hasOnlySubstanceUnits flag set to true and the expression for the assignment should contain a reference to the global parameter multiplied by the volume of the compartment.</p>\n"
  "</body></html>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Values[P],Reference=Value&gt;\n"
  "        </Expression>\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"assignment\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Values[K],Reference=Value&gt;\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"B\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"K\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "      <ModelValue key=\"ModelValue_1\" name=\"P\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 1.2044283e+21 6.022141500000001e+20 2 3 1\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n"
;

void test000064::test_export_rule_expression_and_hasOnlySubstanceUnits_3()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  std::istringstream iss(test000064::MODEL_STRING103);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 3).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // check the units
  UnitDefinition* pUDef = pModel->getUnitDefinition("time");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  Unit* pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_SECOND);
  CPPUNIT_ASSERT(pUnit->getScale() == 0);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  pUDef = pModel->getUnitDefinition("substance");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_ITEM);
  CPPUNIT_ASSERT(pUnit->getScale() == 0);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  pUDef = pModel->getUnitDefinition("volume");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_LITRE);
  CPPUNIT_ASSERT(pUnit->getScale() == -3);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  // assert that there is only one compartment and
  // assert the compartment is constant
  CPPUNIT_ASSERT(pModel->getNumCompartments() == 1);
  Compartment* pCompartment = pModel->getCompartment(0);
  CPPUNIT_ASSERT(pCompartment->getConstant() == true);
  CPPUNIT_ASSERT(pModel->getNumParameters() == 1);
  Parameter* pParameter = pModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter != NULL);
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  Species* pSpecies1 = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pSpecies1->getHasOnlySubstanceUnits() == false);
  std::string idSpeciesA = pSpecies1->getId();
  Species* pSpecies2 = pModel->getSpecies(1);
  CPPUNIT_ASSERT(pSpecies2->getHasOnlySubstanceUnits() == false);
  CPPUNIT_ASSERT(pModel->getNumRules() == 1);
  AssignmentRule* pRule = dynamic_cast<AssignmentRule*>(pModel->getRule(0));
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getVariable() == pSpecies1->getId());
  const ASTNode* pMath = pRule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains only one node that is a
  // reference to the global parameter
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter->getId());
  CPPUNIT_ASSERT(pModel->getNumReactions() == 0);
}

const char* test000064::MODEL_STRING103 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.4.26 (Debug) (http://www.copasi.org) at 2008-06-12 09:00:21 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"26\">\n"
  "  <Model key=\"Model_0\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"#\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:9pt;font-family:Sans Serif\">\n"
  "<p>Simple model with two species and a global parameter. The compartment is fixed and one species is determined by an assignment rule.</p>\n"
  "<p>The substance unit is set to particle number.</p>\n"
  "<p>On export both species should be exported with the hasOnlySubstanceUnits flag set to false and the expression for the assignment should contain only a reference to the global parameter.</p>\n"
  "</body></html>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"fixed\">\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"assignment\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Values[K],Reference=Value&gt;\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"B\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"K\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 1.2044283e+21 6.022141500000001e+20 2 1\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n"
;

void test000064::test_export_rule_expression_and_hasOnlySubstanceUnits_4()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  std::istringstream iss(test000064::MODEL_STRING104);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 3).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // check the units
  UnitDefinition* pUDef = pModel->getUnitDefinition("time");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  Unit* pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_SECOND);
  CPPUNIT_ASSERT(pUnit->getScale() == 0);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  pUDef = pModel->getUnitDefinition("substance");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_ITEM);
  CPPUNIT_ASSERT(pUnit->getScale() == 0);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  pUDef = pModel->getUnitDefinition("volume");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_LITRE);
  CPPUNIT_ASSERT(pUnit->getScale() == -3);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  // assert that there is only one compartment and
  // assert the compartment is not constant
  CPPUNIT_ASSERT(pModel->getNumCompartments() == 1);
  Compartment* pCompartment = pModel->getCompartment(0);
  CPPUNIT_ASSERT(pCompartment->getConstant() == false);
  CPPUNIT_ASSERT(pModel->getNumParameters() == 2);
  Parameter* pParameter1 = pModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter1 != NULL);
  Parameter* pParameter2 = NULL;
  if (pParameter1->getName() == "K")
    {
      pParameter2 = pModel->getParameter(1);
      CPPUNIT_ASSERT(pParameter2 != NULL);
    }
  else
    {
      pParameter2 = pParameter1;
      pParameter1 = pModel->getParameter(1);
      CPPUNIT_ASSERT(pParameter1 != NULL);
    }
  CPPUNIT_ASSERT(pParameter1->getName() == "K");
  CPPUNIT_ASSERT(pParameter2->getName() == "P");
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  Species* pSpecies1 = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pSpecies1->getHasOnlySubstanceUnits() == false);
  std::string idSpeciesA = pSpecies1->getId();
  Species* pSpecies2 = pModel->getSpecies(1);
  CPPUNIT_ASSERT(pSpecies2->getHasOnlySubstanceUnits() == false);
  CPPUNIT_ASSERT(pModel->getNumRules() == 2);
  AssignmentRule* pRule1 = dynamic_cast<AssignmentRule*>(pModel->getRule(0));
  AssignmentRule* pRule2 = NULL;
  CPPUNIT_ASSERT(pRule1 != NULL);
  if (pRule1->getVariable() == pSpecies1->getId())
    {
      pRule2 = pRule1;
      pRule1 = dynamic_cast<AssignmentRule*>(pModel->getRule(1));
    }
  else
    {
      pRule2 = dynamic_cast<AssignmentRule*>(pModel->getRule(1));
    }
  // check the rule for the compartment
  const ASTNode* pMath = pRule1->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains only one node that is a
  // reference to the global parameter P
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter2->getId());
  pMath = pRule2->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains a multiplication of the
  // global parameter K and the compartment volume
  CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  ASTNode* pChild1 = pMath->getChild(0);
  ASTNode* pChild2 = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild1->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild2->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild1->getName() == pParameter1->getId() || pChild2->getName() == pParameter1->getId());
  CPPUNIT_ASSERT(pChild1->getName() == pCompartment->getId() || pChild2->getName() == pCompartment->getId());
  CPPUNIT_ASSERT(pModel->getNumReactions() == 0);
}

const char* test000064::MODEL_STRING104 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.4.26 (Debug) (http://www.copasi.org) at 2008-06-12 09:00:21 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"26\">\n"
  "  <Model key=\"Model_0\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"#\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:9pt;font-family:Sans Serif\">\n"
  "<p>Simple model with two species and two global parameters. The compartment is variable and one species is determined by an assignment rule.</p>\n"
  "<p>The substance unit is set to particle number.</p>\n"
  "<p>On export both species should be exported with the hasOnlySubstanceUnits flag set to true and the expression for the assignment should contain a reference to the global parameter multiplied by the volume of the compartment.</p>\n"
  "</body></html>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Values[P],Reference=Value&gt;\n"
  "        </Expression>\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"assignment\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Values[K],Reference=Value&gt;\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"B\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"K\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "      <ModelValue key=\"ModelValue_1\" name=\"P\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 1.2044283e+21 6.022141500000001e+20 2 3 1\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n"
;
void test000064::test_export_rule_expression_and_hasOnlySubstanceUnits_5()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  std::istringstream iss(test000064::MODEL_STRING105);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 3).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // check the units
  UnitDefinition* pUDef = pModel->getUnitDefinition("time");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  Unit* pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_SECOND);
  CPPUNIT_ASSERT(pUnit->getScale() == 0);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  pUDef = pModel->getUnitDefinition("substance");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_MOLE);
  CPPUNIT_ASSERT(pUnit->getScale() == -3);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  pUDef = pModel->getUnitDefinition("volume");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_LITRE);
  CPPUNIT_ASSERT(pUnit->getScale() == -3);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  // assert that there is only one compartment and
  // assert the compartment is constant
  CPPUNIT_ASSERT(pModel->getNumCompartments() == 1);
  Compartment* pCompartment = pModel->getCompartment(0);
  CPPUNIT_ASSERT(pCompartment->getConstant() == true);
  CPPUNIT_ASSERT(pModel->getNumParameters() == 1);
  Parameter* pParameter = pModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter != NULL);
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  Species* pSpecies1 = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pSpecies1->getHasOnlySubstanceUnits() == false);
  std::string idSpeciesA = pSpecies1->getId();
  Species* pSpecies2 = pModel->getSpecies(1);
  CPPUNIT_ASSERT(pSpecies2->getHasOnlySubstanceUnits() == false);
  CPPUNIT_ASSERT(pModel->getNumRules() == 1);
  AssignmentRule* pRule = dynamic_cast<AssignmentRule*>(pModel->getRule(0));
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getVariable() == pSpecies1->getId());
  const ASTNode* pMath = pRule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains only one node that is a
  // reference to the global parameter
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter->getId());
  CPPUNIT_ASSERT(pModel->getNumReactions() == 0);
}

const char* test000064::MODEL_STRING105 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.4.26 (Debug) (http://www.copasi.org) at 2008-06-12 09:00:21 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"26\">\n"
  "  <Model key=\"Model_0\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:9pt;font-family:Sans Serif\">\n"
  "<p>Simple model with two species and a global parameter. The compartment is fixed and one species is determined by an assignment rule.</p>\n"
  "<p>The substance unit is set to mmol.</p>\n"
  "<p>On export both species should be exported with the hasOnlySubstanceUnits flag set to false and the expression for the assignment should contain only a reference to the global parameter.</p>\n"
  "</body></html>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"fixed\">\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"assignment\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Values[K],Reference=Value&gt;\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"B\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"K\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 1.2044283e+21 6.022141500000001e+20 2 1\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n"
;

void test000064::test_export_rule_expression_and_hasOnlySubstanceUnits_6()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  std::istringstream iss(test000064::MODEL_STRING106);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 3).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // check the units
  UnitDefinition* pUDef = pModel->getUnitDefinition("time");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  Unit* pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_SECOND);
  CPPUNIT_ASSERT(pUnit->getScale() == 0);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  pUDef = pModel->getUnitDefinition("substance");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_MOLE);
  CPPUNIT_ASSERT(pUnit->getScale() == -3);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  pUDef = pModel->getUnitDefinition("volume");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_LITRE);
  CPPUNIT_ASSERT(pUnit->getScale() == -3);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  // assert that there is only one compartment and
  // assert the compartment is not constant
  CPPUNIT_ASSERT(pModel->getNumCompartments() == 1);
  Compartment* pCompartment = pModel->getCompartment(0);
  CPPUNIT_ASSERT(pCompartment->getConstant() == false);
  CPPUNIT_ASSERT(pModel->getNumParameters() == 2);
  Parameter* pParameter1 = pModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter1 != NULL);
  Parameter* pParameter2 = NULL;
  if (pParameter1->getName() == "K")
    {
      pParameter2 = pModel->getParameter(1);
      CPPUNIT_ASSERT(pParameter2 != NULL);
    }
  else
    {
      pParameter2 = pParameter1;
      pParameter1 = pModel->getParameter(1);
      CPPUNIT_ASSERT(pParameter1 != NULL);
    }
  CPPUNIT_ASSERT(pParameter1->getName() == "K");
  CPPUNIT_ASSERT(pParameter2->getName() == "P");
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  Species* pSpecies1 = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pSpecies1->getHasOnlySubstanceUnits() == false);
  std::string idSpeciesA = pSpecies1->getId();
  Species* pSpecies2 = pModel->getSpecies(1);
  CPPUNIT_ASSERT(pSpecies2->getHasOnlySubstanceUnits() == false);
  CPPUNIT_ASSERT(pModel->getNumRules() == 2);
  AssignmentRule* pRule1 = dynamic_cast<AssignmentRule*>(pModel->getRule(0));
  AssignmentRule* pRule2 = NULL;
  CPPUNIT_ASSERT(pRule1 != NULL);
  if (pRule1->getVariable() == pSpecies1->getId())
    {
      pRule2 = pRule1;
      pRule1 = dynamic_cast<AssignmentRule*>(pModel->getRule(1));
    }
  else
    {
      pRule2 = dynamic_cast<AssignmentRule*>(pModel->getRule(1));
    }
  // check the rule for the compartment
  const ASTNode* pMath = pRule1->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains only one node that is a
  // reference to the global parameter P
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter2->getId());
  pMath = pRule2->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains a multiplication of the
  // global parameter K and the compartment volume
  CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  ASTNode* pChild1 = pMath->getChild(0);
  ASTNode* pChild2 = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild1->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild2->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild1->getName() == pParameter1->getId() || pChild2->getName() == pParameter1->getId());
  CPPUNIT_ASSERT(pChild1->getName() == pCompartment->getId() || pChild2->getName() == pCompartment->getId());
  CPPUNIT_ASSERT(pModel->getNumReactions() == 0);
}

const char* test000064::MODEL_STRING106 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.4.26 (Debug) (http://www.copasi.org) at 2008-06-12 09:00:21 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"26\">\n"
  "  <Model key=\"Model_0\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:9pt;font-family:Sans Serif\">\n"
  "<p>Simple model with two species and two global parameters. The compartment is variable and one species is determined by an assignment rule.</p>\n"
  "<p>The substance unit is set to mmol.</p>\n"
  "<p>On export both species should be exported with the hasOnlySubstanceUnits flag set to true and the expression for the assignment should contain a reference to the global parameter multiplied by the volume of the compartment.</p>\n"
  "</body></html>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Values[P],Reference=Value&gt;\n"
  "        </Expression>\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"assignment\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Values[K],Reference=Value&gt;\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"B\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"K\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "      <ModelValue key=\"ModelValue_1\" name=\"P\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 1.2044283e+21 6.022141500000001e+20 2 3 1\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n"
;

void test000064::test_export_rule_expression_and_hasOnlySubstanceUnits_7()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  std::istringstream iss(test000064::MODEL_STRING107);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 3).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // check the units
  UnitDefinition* pUDef = pModel->getUnitDefinition("time");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  Unit* pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_SECOND);
  CPPUNIT_ASSERT(pUnit->getScale() == 0);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  pUDef = pModel->getUnitDefinition("substance");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_ITEM);
  CPPUNIT_ASSERT(pUnit->getScale() == 0);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  pUDef = pModel->getUnitDefinition("volume");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_LITRE);
  CPPUNIT_ASSERT(pUnit->getScale() == -3);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  // assert that there is only one compartment and
  // assert the compartment is constant
  CPPUNIT_ASSERT(pModel->getNumCompartments() == 1);
  Compartment* pCompartment = pModel->getCompartment(0);
  CPPUNIT_ASSERT(pCompartment->getConstant() == true);
  CPPUNIT_ASSERT(pModel->getNumParameters() == 1);
  Parameter* pParameter = pModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter != NULL);
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  Species* pSpecies1 = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pSpecies1->getHasOnlySubstanceUnits() == false);
  std::string idSpeciesA = pSpecies1->getId();
  Species* pSpecies2 = pModel->getSpecies(1);
  CPPUNIT_ASSERT(pSpecies2->getHasOnlySubstanceUnits() == false);
  CPPUNIT_ASSERT(pModel->getNumRules() == 1);
  AssignmentRule* pRule = dynamic_cast<AssignmentRule*>(pModel->getRule(0));
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getVariable() == pSpecies1->getId());
  const ASTNode* pMath = pRule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains only one node that is a
  // reference to the global parameter
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter->getId());
  CPPUNIT_ASSERT(pModel->getNumReactions() == 0);
}

const char* test000064::MODEL_STRING107 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.4.26 (Debug) (http://www.copasi.org) at 2008-06-12 09:00:21 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"26\">\n"
  "  <Model key=\"Model_0\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"#\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:9pt;font-family:Sans Serif\">\n"
  "<p>Simple model with two species and a global parameter. The compartment is fixed and one species is determined by an assignment rule.</p>\n"
  "<p>The substance unit is set to particle number.</p>\n"
  "<p>On export both species should be exported with the hasOnlySubstanceUnits flag set to false and the expression for the assignment should contain only a reference to the global parameter.</p>\n"
  "</body></html>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"fixed\">\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"assignment\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Values[K],Reference=Value&gt;\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"B\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"K\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 1.2044283e+21 6.022141500000001e+20 2 1\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n"
;

void test000064::test_export_rule_expression_and_hasOnlySubstanceUnits_8()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  std::istringstream iss(test000064::MODEL_STRING108);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 3).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // check the units
  UnitDefinition* pUDef = pModel->getUnitDefinition("time");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  Unit* pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_SECOND);
  CPPUNIT_ASSERT(pUnit->getScale() == 0);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  pUDef = pModel->getUnitDefinition("substance");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_ITEM);
  CPPUNIT_ASSERT(pUnit->getScale() == 0);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  pUDef = pModel->getUnitDefinition("volume");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
  pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_LITRE);
  CPPUNIT_ASSERT(pUnit->getScale() == -3);
  CPPUNIT_ASSERT(pUnit->getExponent() == 1);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  // assert that there is only one compartment and
  // assert the compartment is not constant
  CPPUNIT_ASSERT(pModel->getNumCompartments() == 1);
  Compartment* pCompartment = pModel->getCompartment(0);
  CPPUNIT_ASSERT(pCompartment->getConstant() == false);
  CPPUNIT_ASSERT(pModel->getNumParameters() == 2);
  Parameter* pParameter1 = pModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter1 != NULL);
  Parameter* pParameter2 = NULL;
  if (pParameter1->getName() == "K")
    {
      pParameter2 = pModel->getParameter(1);
      CPPUNIT_ASSERT(pParameter2 != NULL);
    }
  else
    {
      pParameter2 = pParameter1;
      pParameter1 = pModel->getParameter(1);
      CPPUNIT_ASSERT(pParameter1 != NULL);
    }
  CPPUNIT_ASSERT(pParameter1->getName() == "K");
  CPPUNIT_ASSERT(pParameter2->getName() == "P");
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  Species* pSpecies1 = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pSpecies1->getHasOnlySubstanceUnits() == false);
  std::string idSpeciesA = pSpecies1->getId();
  Species* pSpecies2 = pModel->getSpecies(1);
  CPPUNIT_ASSERT(pSpecies2->getHasOnlySubstanceUnits() == false);
  CPPUNIT_ASSERT(pModel->getNumRules() == 2);
  AssignmentRule* pRule1 = dynamic_cast<AssignmentRule*>(pModel->getRule(0));
  AssignmentRule* pRule2 = NULL;
  CPPUNIT_ASSERT(pRule1 != NULL);
  if (pRule1->getVariable() == pSpecies1->getId())
    {
      pRule2 = pRule1;
      pRule1 = dynamic_cast<AssignmentRule*>(pModel->getRule(1));
    }
  else
    {
      pRule2 = dynamic_cast<AssignmentRule*>(pModel->getRule(1));
    }
  // check the rule for the compartment
  const ASTNode* pMath = pRule1->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains only one node that is a
  // reference to the global parameter P
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter2->getId());
  pMath = pRule2->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains a multiplication of the
  // global parameter K and the compartment volume
  CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  ASTNode* pChild1 = pMath->getChild(0);
  ASTNode* pChild2 = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild1->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild2->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild1->getName() == pParameter1->getId() || pChild2->getName() == pParameter1->getId());
  CPPUNIT_ASSERT(pChild1->getName() == pCompartment->getId() || pChild2->getName() == pCompartment->getId());
  CPPUNIT_ASSERT(pModel->getNumReactions() == 0);
}

const char* test000064::MODEL_STRING108 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.4.26 (Debug) (http://www.copasi.org) at 2008-06-12 09:00:21 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"26\">\n"
  "  <Model key=\"Model_0\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"#\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:9pt;font-family:Sans Serif\">\n"
  "<p>Simple model with two species and two global parameters. The compartment is variable and one species is determined by an assignment rule.</p>\n"
  "<p>The substance unit is set to particle number.</p>\n"
  "<p>On export both species should be exported with the hasOnlySubstanceUnits flag set to true and the expression for the assignment should contain a reference to the global parameter multiplied by the volume of the compartment.</p>\n"
  "</body></html>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Values[P],Reference=Value&gt;\n"
  "        </Expression>\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"assignment\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Values[K],Reference=Value&gt;\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"B\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"K\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "      <ModelValue key=\"ModelValue_1\" name=\"P\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 1.2044283e+21 6.022141500000001e+20 2 3 1\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n"
;
