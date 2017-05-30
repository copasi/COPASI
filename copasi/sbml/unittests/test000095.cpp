// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "test000095.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CEvent.h"

#include "sbml/math/ASTNode.h"
#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Compartment.h"
#include "sbml/Parameter.h"
#include "sbml/Event.h"
#include "sbml/Trigger.h"
#include "sbml/Delay.h"
#include "sbml/EventAssignment.h"

#include "copasi/core/CRootContainer.h"

CDataModel* test000095::pCOPASIDATAMODEL = NULL;

void test000095::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000095::tearDown()
{
  CRootContainer::destroy();
}

void test000095::test_import_l3_event_1()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING1));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 0);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 0);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModel->getEvents().size() == 1);
  const CEvent* pEvent = pModel->getEvents()[0];
  CPPUNIT_ASSERT(pEvent != NULL);

  // check the trigger expression
  const CExpression* pExpr = pEvent->getTriggerExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::LOGICAL);
  CPPUNIT_ASSERT(pNode->subType() == CEvaluationNode::SubType::GT);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCommonName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  CObjectInterface::ContainerList listOfContainers;
  listOfContainers.push_back(pModel);
  const CDataObject* pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModel);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::NUMBER);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 2.0) / 2.0) < 1e-6);
  // check that there is a delay

  CPPUNIT_ASSERT(pEvent->getAssignments().size() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignments()[0]->getTargetKey();
  CPPUNIT_ASSERT(key == pModelValue->getKey());
  pExpr = pEvent->getAssignments()[0]->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::NUMBER);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT((fabs(pNumberNode->getValue() - 8.0) / 8.0) < 1e-9);

  // check that the message stack contains a warning about event priorities
  // MCSBML + 98
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 97) == false);
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 98) == true);
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 99) == false);
}

void test000095::test_import_l3_event_2()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING2));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 0);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 0);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModel->getEvents().size() == 1);
  const CEvent* pEvent = pModel->getEvents()[0];
  CPPUNIT_ASSERT(pEvent != NULL);

  // check the trigger expression
  const CExpression* pExpr = pEvent->getTriggerExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::LOGICAL);
  CPPUNIT_ASSERT(pNode->subType() == CEvaluationNode::SubType::GT);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCommonName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  CObjectInterface::ContainerList listOfContainers;
  listOfContainers.push_back(pModel);
  const CDataObject* pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModel);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::NUMBER);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 2.0) / 2.0) < 1e-6);
  // check that there is a delay

  CPPUNIT_ASSERT(pEvent->getAssignments().size() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignments()[0]->getTargetKey();
  CPPUNIT_ASSERT(key == pModelValue->getKey());
  pExpr = pEvent->getAssignments()[0]->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::NUMBER);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT((fabs(pNumberNode->getValue() - 8.0) / 8.0) < 1e-9);

  // check that the message stack contains a warning about initial values for triggers
  // MCSBML + 97
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 97) == true);
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 98) == false);
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 99) == false);
}

void test000095::test_import_l3_event_3()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING3));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 0);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 0);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModel->getEvents().size() == 1);
  const CEvent* pEvent = pModel->getEvents()[0];
  CPPUNIT_ASSERT(pEvent != NULL);

  // check the trigger expression
  const CExpression* pExpr = pEvent->getTriggerExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::LOGICAL);
  CPPUNIT_ASSERT(pNode->subType() == CEvaluationNode::SubType::GT);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCommonName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  CObjectInterface::ContainerList listOfContainers;
  listOfContainers.push_back(pModel);
  const CDataObject* pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModel);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::NUMBER);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 2.0) / 2.0) < 1e-6);
  // check that there is a delay

  CPPUNIT_ASSERT(pEvent->getAssignments().size() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignments()[0]->getTargetKey();
  CPPUNIT_ASSERT(key == pModelValue->getKey());
  pExpr = pEvent->getAssignments()[0]->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::NUMBER);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT((fabs(pNumberNode->getValue() - 8.0) / 8.0) < 1e-9);

  // check that the message stack contains a warning about event priorities
  // MCSBML + 98
  // check that the message stack contains a warning about initial values for triggers
  // MCSBML + 97
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 97) == true);
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 98) == true);
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 99) == false);
}

void test000095::test_import_l3_event_4()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING4));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 0);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 0);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModel->getEvents().size() == 1);
  const CEvent* pEvent = pModel->getEvents()[0];
  CPPUNIT_ASSERT(pEvent != NULL);

  // check the trigger expression
  const CExpression* pExpr = pEvent->getTriggerExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::LOGICAL);
  CPPUNIT_ASSERT(pNode->subType() == CEvaluationNode::SubType::GT);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCommonName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  CObjectInterface::ContainerList listOfContainers;
  listOfContainers.push_back(pModel);
  const CDataObject* pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModel);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::NUMBER);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 2.0) / 2.0) < 1e-6);
  // check that there is a delay

  CPPUNIT_ASSERT(pEvent->getAssignments().size() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignments()[0]->getTargetKey();
  CPPUNIT_ASSERT(key == pModelValue->getKey());
  pExpr = pEvent->getAssignments()[0]->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::NUMBER);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT((fabs(pNumberNode->getValue() - 8.0) / 8.0) < 1e-9);

  // check that the message stack contains a warning about non-persistent triggers
  // MCSBML + 99
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 97) == false);
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 98) == false);
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 99) == true);
}

void test000095::test_import_l3_event_5()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING5));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 0);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 0);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModel->getEvents().size() == 1);
  const CEvent* pEvent = pModel->getEvents()[0];
  CPPUNIT_ASSERT(pEvent != NULL);

  // check the trigger expression
  const CExpression* pExpr = pEvent->getTriggerExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::LOGICAL);
  CPPUNIT_ASSERT(pNode->subType() == CEvaluationNode::SubType::GT);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCommonName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  CObjectInterface::ContainerList listOfContainers;
  listOfContainers.push_back(pModel);
  const CDataObject* pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModel);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getSibling());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::NUMBER);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 2.0) / 2.0) < 1e-6);
  // check that there is a delay

  CPPUNIT_ASSERT(pEvent->getAssignments().size() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignments()[0]->getTargetKey();
  CPPUNIT_ASSERT(key == pModelValue->getKey());
  pExpr = pEvent->getAssignments()[0]->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::NUMBER);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT((fabs(pNumberNode->getValue() - 8.0) / 8.0) < 1e-9);

  // check that there is no MCSBML + 97, MCSBML + 98 or MCSBML + 99  error message
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 97) == false);
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 98) == false);
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 99) == false);
}

const char* test000095::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L3V1 model with event priority.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfEvents>"
  "      <event>"
  "        <trigger initialValue=\"true\" persistent=\"true\">"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <apply>"
  "              <gt/>"
  "              <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/time\"> time </csymbol>"
  "              <cn> 2.0 </cn>"
  "            </apply>"
  "          </math>"
  "        </trigger>"
  "        <priority>"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <cn> 2.0 </cn>"
  "          </math>"
  "        </priority>"
  "        <listOfEventAssignments>"
  "          <eventAssignment variable=\"parameter_1\">"
  "            <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "              <cn> 8.0 </cn>"
  "            </math>"
  "          </eventAssignment>"
  "        </listOfEventAssignments>"
  "      </event>"
  "    </listOfEvents>"
  "  </model>"
  "</sbml>"
  ;

const char* test000095::MODEL_STRING2 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L3V1 model with event priority.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfEvents>"
  "      <event>"
  "        <trigger initialValue=\"false\" persistent=\"true\" >"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <apply>"
  "              <gt/>"
  "              <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/time\"> time </csymbol>"
  "              <cn> 2.0 </cn>"
  "            </apply>"
  "          </math>"
  "        </trigger>"
  "        <listOfEventAssignments>"
  "          <eventAssignment variable=\"parameter_1\">"
  "            <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "              <cn> 8.0 </cn>"
  "            </math>"
  "          </eventAssignment>"
  "        </listOfEventAssignments>"
  "      </event>"
  "    </listOfEvents>"
  "  </model>"
  "</sbml>"
  ;

const char* test000095::MODEL_STRING3 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L3V1 model with event priority.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfEvents>"
  "      <event>"
  "        <trigger initialValue=\"false\" persistent=\"true\" >"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <apply>"
  "              <gt/>"
  "              <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/time\"> time </csymbol>"
  "              <cn> 2.0 </cn>"
  "            </apply>"
  "          </math>"
  "        </trigger>"
  "        <priority>"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <cn> 2.0 </cn>"
  "          </math>"
  "        </priority>"
  "        <listOfEventAssignments>"
  "          <eventAssignment variable=\"parameter_1\">"
  "            <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "              <cn> 8.0 </cn>"
  "            </math>"
  "          </eventAssignment>"
  "        </listOfEventAssignments>"
  "      </event>"
  "    </listOfEvents>"
  "  </model>"
  "</sbml>"
  ;

const char* test000095::MODEL_STRING4 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L3V1 model with event priority.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfEvents>"
  "      <event>"
  "        <trigger initialValue=\"true\" persistent=\"false\" >"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <apply>"
  "              <gt/>"
  "              <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/time\"> time </csymbol>"
  "              <cn> 2.0 </cn>"
  "            </apply>"
  "          </math>"
  "        </trigger>"
  "        <listOfEventAssignments>"
  "          <eventAssignment variable=\"parameter_1\">"
  "            <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "              <cn> 8.0 </cn>"
  "            </math>"
  "          </eventAssignment>"
  "        </listOfEventAssignments>"
  "      </event>"
  "    </listOfEvents>"
  "  </model>"
  "</sbml>"
  ;

const char* test000095::MODEL_STRING5 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L3V1 model with event priority.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfEvents>"
  "      <event>"
  "        <trigger initialValue=\"true\" persistent=\"true\" >"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <apply>"
  "              <gt/>"
  "              <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/time\"> time </csymbol>"
  "              <cn> 2.0 </cn>"
  "            </apply>"
  "          </math>"
  "        </trigger>"
  "        <listOfEventAssignments>"
  "          <eventAssignment variable=\"parameter_1\">"
  "            <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "              <cn> 8.0 </cn>"
  "            </math>"
  "          </eventAssignment>"
  "        </listOfEventAssignments>"
  "      </event>"
  "    </listOfEvents>"
  "  </model>"
  "</sbml>"
  ;
