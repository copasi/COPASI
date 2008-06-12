// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000064.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/06/12 08:16:55 $
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
  "        <p>Model with fixed compartment volume, two species where both have the hasOnlySubstanceUnits flag set to false. The units are set to ml and mMol. There is an assignment rule for the species with the hasOnlySubstanceUnits flag set to true.</p>"
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

const char* test000064::MODEL_STRING3 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species where both have the hasOnlySubstanceUnits flag set to false. The units are set to ml and item. There is an assignment rule for the species with the hasOnlySubstanceUnits flag set to true.</p>"
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

void test000064::test_import_event_assignment_expression_and_hasOnlySubstanceUnits_5()
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

void test000064::test_import_event_assignment_expression_and_hasOnlySubstanceUnits_6()
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
  "        <p>Model with fixed compartment volume, two species where both have the hasOnlySubstanceUnits flag set to false. The units are set to ml and mMol. There is an event assignment for the species with the hasOnlySubstanceUnits flag set to true.</p>"
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

void test000064::test_import_event_assignment_expression_and_hasOnlySubstanceUnits_7()
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

const char* test000064::MODEL_STRING7 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species where both have the hasOnlySubstanceUnits flag set to false. The units are set to ml and item. There is an event assignment for the species with the hasOnlySubstanceUnits flag set to true.</p>"
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

void test000064::test_import_event_assignment_expression_and_hasOnlySubstanceUnits_8()
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
