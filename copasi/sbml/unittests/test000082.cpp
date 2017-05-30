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

#include "test000082.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
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
#include "sbml/Event.h"
#include "sbml/Trigger.h"
#include "sbml/Delay.h"
#include "sbml/EventAssignment.h"

#include "copasi/core/CRootContainer.h"

CDataModel* test000082::pCOPASIDATAMODEL = NULL;

void test000082::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000082::tearDown()
{
  CRootContainer::destroy();
}

void test000082::test_import_delayAssignment_1()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING1));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CUnit::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CUnit::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CUnit::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 1);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
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
  pExpr = pEvent->getDelayExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::NUMBER);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 10.0) / 10.0) < 1e-6);
  // check that the delayAssignment flag is set to true
  CPPUNIT_ASSERT(pEvent->getDelayAssignment() == true);

  CPPUNIT_ASSERT(pEvent->getAssignments().size() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignments()[0]->getTargetKey();
  CPPUNIT_ASSERT(key == pA->getKey());
  pExpr = pEvent->getAssignments()[0]->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
}

const char* test000082::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with event and delay expression.</p>"
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
  "        <delay>"
  "         <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "           <cn> 10 </cn>"
  "         </math>"
  "       </delay>"
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

void test000082::test_import_delayAssignment_2()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING2));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CUnit::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CUnit::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CUnit::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 1);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
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
  pExpr = pEvent->getDelayExpressionPtr();
  CPPUNIT_ASSERT(pExpr == NULL);
  // check that the delayAssignment flag is set to true
  CPPUNIT_ASSERT(pEvent->getDelayAssignment() == true);

  CPPUNIT_ASSERT(pEvent->getAssignments().size() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignments()[0]->getTargetKey();
  CPPUNIT_ASSERT(key == pA->getKey());
  pExpr = pEvent->getAssignments()[0]->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
}

const char* test000082::MODEL_STRING2 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with event and delay expression.</p>"
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

void test000082::test_import_delayAssignment_3()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING3));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CUnit::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CUnit::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CUnit::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 1);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
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
  pExpr = pEvent->getDelayExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::NUMBER);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 10.0) / 10.0) < 1e-6);
  // check that the delayAssignment flag is set to true
  CPPUNIT_ASSERT(pEvent->getDelayAssignment() == true);

  CPPUNIT_ASSERT(pEvent->getAssignments().size() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignments()[0]->getTargetKey();
  CPPUNIT_ASSERT(key == pA->getKey());
  pExpr = pEvent->getAssignments()[0]->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
}

const char* test000082::MODEL_STRING3 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version4\" level=\"2\" version=\"4\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V4 model with event and delay expression.</p>"
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
  "        <delay>"
  "         <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "           <cn> 10 </cn>"
  "         </math>"
  "       </delay>"
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

void test000082::test_import_delayAssignment_4()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING4));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CUnit::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CUnit::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CUnit::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 1);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
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
  pExpr = pEvent->getDelayExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::NUMBER);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 10.0) / 10.0) < 1e-6);
  // check that the delayAssignment flag is set to true
  CPPUNIT_ASSERT(pEvent->getDelayAssignment() == true);

  CPPUNIT_ASSERT(pEvent->getAssignments().size() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignments()[0]->getTargetKey();
  CPPUNIT_ASSERT(key == pA->getKey());
  pExpr = pEvent->getAssignments()[0]->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
}

const char* test000082::MODEL_STRING4 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version4\" level=\"2\" version=\"4\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V4 model with event and delay expression.</p>"
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
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfEvents>"
  "      <event useValuesFromTriggerTime=\"true\">"
  "        <trigger>"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <apply>"
  "              <gt/>"
  "              <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/time\"> time </csymbol>"
  "              <cn> 2.0 </cn>"
  "            </apply>"
  "          </math>"
  "        </trigger>"
  "        <delay>"
  "         <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "           <cn> 10 </cn>"
  "         </math>"
  "       </delay>"
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

void test000082::test_import_delayAssignment_5()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING5));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CUnit::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CUnit::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CUnit::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 1);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
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
  pExpr = pEvent->getDelayExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::NUMBER);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 10.0) / 10.0) < 1e-6);
  // check that the delayAssignment flag is set to false
  CPPUNIT_ASSERT(pEvent->getDelayAssignment() == false);

  CPPUNIT_ASSERT(pEvent->getAssignments().size() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignments()[0]->getTargetKey();
  CPPUNIT_ASSERT(key == pA->getKey());
  pExpr = pEvent->getAssignments()[0]->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
}

const char* test000082::MODEL_STRING5 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version4\" level=\"2\" version=\"4\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V4 model with event and delay expression.</p>"
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
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfEvents>"
  "      <event useValuesFromTriggerTime=\"false\">"
  "        <trigger>"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <apply>"
  "              <gt/>"
  "              <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/time\"> time </csymbol>"
  "              <cn> 2.0 </cn>"
  "            </apply>"
  "          </math>"
  "        </trigger>"
  "        <delay>"
  "         <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "           <cn> 10 </cn>"
  "         </math>"
  "       </delay>"
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

void test000082::test_import_delayAssignment_6()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING6));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CUnit::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CUnit::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CUnit::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 1);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
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
  pExpr = pEvent->getDelayExpressionPtr();
  CPPUNIT_ASSERT(pExpr == NULL);
  // check that the delayAssignment flag is set to true
  CPPUNIT_ASSERT(pEvent->getDelayAssignment() == true);

  CPPUNIT_ASSERT(pEvent->getAssignments().size() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignments()[0]->getTargetKey();
  CPPUNIT_ASSERT(key == pA->getKey());
  pExpr = pEvent->getAssignments()[0]->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
}

const char* test000082::MODEL_STRING6 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version4\" level=\"2\" version=\"4\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V4 model with event and delay expression.</p>"
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

void test000082::test_import_delayAssignment_7()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING7));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CUnit::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CUnit::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CUnit::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 1);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
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
  pExpr = pEvent->getDelayExpressionPtr();
  CPPUNIT_ASSERT(pExpr == NULL);
  // check that the delayAssignment flag is set to true
  CPPUNIT_ASSERT(pEvent->getDelayAssignment() == true);

  CPPUNIT_ASSERT(pEvent->getAssignments().size() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignments()[0]->getTargetKey();
  CPPUNIT_ASSERT(key == pA->getKey());
  pExpr = pEvent->getAssignments()[0]->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
}

const char* test000082::MODEL_STRING7 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version4\" level=\"2\" version=\"4\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V4 model with event and delay expression.</p>"
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
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfEvents>"
  "      <event useValuesFromTriggerTime=\"true\">"
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

void test000082::test_import_delayAssignment_8()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING8));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CUnit::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CUnit::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CUnit::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 1);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
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
  pExpr = pEvent->getDelayExpressionPtr();
  CPPUNIT_ASSERT(pExpr == NULL);
  // check that the delayAssignment flag is set to true
  CPPUNIT_ASSERT(pEvent->getDelayAssignment() == true);

  CPPUNIT_ASSERT(pEvent->getAssignments().size() == 1);
  // check the event assignment
  std::string key = pEvent->getAssignments()[0]->getTargetKey();
  CPPUNIT_ASSERT(key == pA->getKey());
  pExpr = pEvent->getAssignments()[0]->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModelValue);
}

const char* test000082::MODEL_STRING8 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version4\" level=\"2\" version=\"4\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V4 model with event and delay expression.</p>"
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
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfEvents>"
  "      <event useValuesFromTriggerTime=\"false\">"
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

void test000082::test_export_delayAssignment_1()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000082::MODEL_STRING101);
  bool result = load_cps_model_from_stream(iss, *pDataModel);
  CPPUNIT_ASSERT(result == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 4).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  CPPUNIT_ASSERT(pDocument->getLevel() == 2);
  CPPUNIT_ASSERT(pDocument->getVersion() == 4);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // check the units
  UnitDefinition* pUDef = pModel->getUnitDefinition("time");
  Unit* pUnit = NULL;

  // since second is the default time unit, it does not have to be exported and
  // might be NULL
  if (pUDef != NULL)
    {
      CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
      pUnit = pUDef->getUnit(0);
      CPPUNIT_ASSERT(pUnit != NULL);
      CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_SECOND);
      CPPUNIT_ASSERT(pUnit->getScale() == 0);
      CPPUNIT_ASSERT(pUnit->getExponent() == 1);
      CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
    }

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
  CPPUNIT_ASSERT(pModel->getNumParameters() == 1);
  Parameter* pParameter1 = pModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter1 != NULL);
  CPPUNIT_ASSERT(pParameter1->getName() == "K");
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  Species* pSpecies1 = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pSpecies1->getName() == "A");
  Species* pSpecies2 = pModel->getSpecies(1);
  CPPUNIT_ASSERT(pSpecies2->getName() == "B");
  CPPUNIT_ASSERT(pModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pModel->getNumReactions() == 0);
  CPPUNIT_ASSERT(pModel->getNumEvents() == 1);
  Event* pEvent = pModel->getEvent(0);
  CPPUNIT_ASSERT(pEvent != NULL);
  // check the trigger
  CPPUNIT_ASSERT(pEvent->isSetTrigger());
  Trigger* pTrigger = pEvent->getTrigger();
  CPPUNIT_ASSERT(pTrigger != NULL);
  CPPUNIT_ASSERT(pTrigger->isSetMath());
  const ASTNode* pMath = pTrigger->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_RELATIONAL_GT);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  const ASTNode* pChild = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_NAME_TIME);
  pChild = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild->getReal() - 2.0) / 2.0) < 1e-6);
  // check the delay
  CPPUNIT_ASSERT(pEvent->isSetDelay());
  CPPUNIT_ASSERT(pEvent->getUseValuesFromTriggerTime() == true);
  Delay* pDelay = pEvent->getDelay();
  CPPUNIT_ASSERT(pDelay != NULL);
  CPPUNIT_ASSERT(pDelay->isSetMath());
  pMath = pDelay->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pMath->getReal() - 4.0) / 4.0) < 1e-6);
  // check the event assignment
  CPPUNIT_ASSERT(pEvent->getNumEventAssignments() == 1);
  EventAssignment* pEA = pEvent->getEventAssignment(0);
  CPPUNIT_ASSERT(pEA != NULL);
  CPPUNIT_ASSERT(pEA->getVariable() == pSpecies1->getId());
  pMath = pEA->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains only one node that is a
  // reference to the global parameter
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter1->getId());
}

void test000082::test_export_delayAssignment_2()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000082::MODEL_STRING101);
  bool result = load_cps_model_from_stream(iss, *pDataModel);
  CPPUNIT_ASSERT(result == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 1).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  CPPUNIT_ASSERT(pDocument->getLevel() == 2);
  CPPUNIT_ASSERT(pDocument->getVersion() == 1);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // check the units
  UnitDefinition* pUDef = pModel->getUnitDefinition("time");
  Unit* pUnit = NULL;

  // since second is the default time unit, it does not have to be exported and
  // might be NULL
  if (pUDef != NULL)
    {
      CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
      pUnit = pUDef->getUnit(0);
      CPPUNIT_ASSERT(pUnit != NULL);
      CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_SECOND);
      CPPUNIT_ASSERT(pUnit->getScale() == 0);
      CPPUNIT_ASSERT(pUnit->getExponent() == 1);
      CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
    }

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
  CPPUNIT_ASSERT(pModel->getNumParameters() == 1);
  Parameter* pParameter1 = pModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter1 != NULL);
  CPPUNIT_ASSERT(pParameter1->getName() == "K");
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  Species* pSpecies1 = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pSpecies1->getName() == "A");
  Species* pSpecies2 = pModel->getSpecies(1);
  CPPUNIT_ASSERT(pSpecies2->getName() == "B");
  CPPUNIT_ASSERT(pModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pModel->getNumReactions() == 0);
  CPPUNIT_ASSERT(pModel->getNumEvents() == 1);
  Event* pEvent = pModel->getEvent(0);
  CPPUNIT_ASSERT(pEvent != NULL);
  // check the trigger
  CPPUNIT_ASSERT(pEvent->isSetTrigger());
  Trigger* pTrigger = pEvent->getTrigger();
  CPPUNIT_ASSERT(pTrigger != NULL);
  CPPUNIT_ASSERT(pTrigger->isSetMath());
  const ASTNode* pMath = pTrigger->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_RELATIONAL_GT);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  const ASTNode* pChild = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_NAME_TIME);
  pChild = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild->getReal() - 2.0) / 2.0) < 1e-6);
  // check the delay
  CPPUNIT_ASSERT(pEvent->isSetDelay());
  CPPUNIT_ASSERT(pEvent->getUseValuesFromTriggerTime() == true);
  Delay* pDelay = pEvent->getDelay();
  CPPUNIT_ASSERT(pDelay != NULL);
  CPPUNIT_ASSERT(pDelay->isSetMath());
  pMath = pDelay->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pMath->getReal() - 4.0) / 4.0) < 1e-6);
  // check the event assignment
  CPPUNIT_ASSERT(pEvent->getNumEventAssignments() == 1);
  EventAssignment* pEA = pEvent->getEventAssignment(0);
  CPPUNIT_ASSERT(pEA != NULL);
  CPPUNIT_ASSERT(pEA->getVariable() == pSpecies1->getId());
  pMath = pEA->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains only one node that is a
  // reference to the global parameter
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter1->getId());
  // make sure there is actually no warning MCSBML + 77
  unsigned int i = 0, iMax = CCopasiMessage::size();

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();
      CPPUNIT_ASSERT(message.getNumber() != MCSBML + 77);
      ++i;
    }
}

const char* test000082::MODEL_STRING101 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.4.26 (Debug) (http://www.copasi.org) at 2008-06-12 09:00:21 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"26\">\n"
  "  <Model key=\"Model_0\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:9pt;font-family:Sans Serif\">\n"
  "<p>Simple model with two species and one global parameter. The compartment is fixed and one species is changed by an event assignment.</p>\n"
  "<p>The substance unit is set to mmol.</p>\n"
  "<p>On export both species should be exported with the hasOnlySubstanceUnits flag set to false and the expression for the event assignment should contain a reference to the global parameter.</p>\n"
  "</body></html>\n"
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
  "    <ListOfEvents>\n"
  "      <Event key=\"Event_0\" name=\"event\" delayAssignment=\"true\" >\n"
  "        <TriggerExpression>\n"
  "          &lt;CN=Root,Model=New Model,Reference=Time&gt; gt 2.0\n"
  "        </TriggerExpression>\n"
  "        <DelayExpression>\n"
  "          4.0\n"
  "        </DelayExpression>\n"
  "        <ListOfAssignments>\n"
  "          <Assignment targetKey=\"Metabolite_0\">\n"
  "            <Expression>\n"
  "              &lt;CN=Root,Model=New Model,Vector=Values[K],Reference=Value&gt;\n"
  "            </Expression>\n"
  "          </Assignment>\n"
  "        </ListOfAssignments>\n"
  "      </Event>\n"
  "    </ListOfEvents>\n"
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

void test000082::test_export_delayAssignment_3()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000082::MODEL_STRING102);
  bool result = load_cps_model_from_stream(iss, *pDataModel);
  CPPUNIT_ASSERT(result == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 4).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  CPPUNIT_ASSERT(pDocument->getLevel() == 2);
  CPPUNIT_ASSERT(pDocument->getVersion() == 4);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // check the units
  UnitDefinition* pUDef = pModel->getUnitDefinition("time");
  Unit* pUnit = NULL;

  // since second is the default time unit, it does not have to be exported and
  // might be NULL
  if (pUDef != NULL)
    {
      CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
      pUnit = pUDef->getUnit(0);
      CPPUNIT_ASSERT(pUnit != NULL);
      CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_SECOND);
      CPPUNIT_ASSERT(pUnit->getScale() == 0);
      CPPUNIT_ASSERT(pUnit->getExponent() == 1);
      CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
    }

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
  CPPUNIT_ASSERT(pModel->getNumParameters() == 1);
  Parameter* pParameter1 = pModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter1 != NULL);
  CPPUNIT_ASSERT(pParameter1->getName() == "K");
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  Species* pSpecies1 = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pSpecies1->getName() == "A");
  Species* pSpecies2 = pModel->getSpecies(1);
  CPPUNIT_ASSERT(pSpecies2->getName() == "B");
  CPPUNIT_ASSERT(pModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pModel->getNumReactions() == 0);
  CPPUNIT_ASSERT(pModel->getNumEvents() == 1);
  Event* pEvent = pModel->getEvent(0);
  CPPUNIT_ASSERT(pEvent != NULL);
  // check the trigger
  CPPUNIT_ASSERT(pEvent->isSetTrigger());
  Trigger* pTrigger = pEvent->getTrigger();
  CPPUNIT_ASSERT(pTrigger != NULL);
  CPPUNIT_ASSERT(pTrigger->isSetMath());
  const ASTNode* pMath = pTrigger->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_RELATIONAL_GT);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  const ASTNode* pChild = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_NAME_TIME);
  pChild = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild->getReal() - 2.0) / 2.0) < 1e-6);
  // check the delay
  CPPUNIT_ASSERT(pEvent->isSetDelay());
  CPPUNIT_ASSERT(pEvent->getUseValuesFromTriggerTime() == false);
  Delay* pDelay = pEvent->getDelay();
  CPPUNIT_ASSERT(pDelay != NULL);
  CPPUNIT_ASSERT(pDelay->isSetMath());
  pMath = pDelay->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pMath->getReal() - 4.0) / 4.0) < 1e-6);
  // check the event assignment
  CPPUNIT_ASSERT(pEvent->getNumEventAssignments() == 1);
  EventAssignment* pEA = pEvent->getEventAssignment(0);
  CPPUNIT_ASSERT(pEA != NULL);
  CPPUNIT_ASSERT(pEA->getVariable() == pSpecies1->getId());
  pMath = pEA->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains only one node that is a
  // reference to the global parameter
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter1->getId());
}

void test000082::test_export_delayAssignment_4()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000082::MODEL_STRING102);
  bool result = load_cps_model_from_stream(iss, *pDataModel);
  CPPUNIT_ASSERT(result == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 1).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  CPPUNIT_ASSERT(pDocument->getLevel() == 2);
  CPPUNIT_ASSERT(pDocument->getVersion() == 1);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // check the units
  UnitDefinition* pUDef = pModel->getUnitDefinition("time");
  Unit* pUnit = NULL;

  // since second is the default time unit, it does not have to be exported and
  // might be NULL
  if (pUDef != NULL)
    {
      CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
      pUnit = pUDef->getUnit(0);
      CPPUNIT_ASSERT(pUnit != NULL);
      CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_SECOND);
      CPPUNIT_ASSERT(pUnit->getScale() == 0);
      CPPUNIT_ASSERT(pUnit->getExponent() == 1);
      CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
    }

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
  CPPUNIT_ASSERT(pModel->getNumParameters() == 1);
  Parameter* pParameter1 = pModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter1 != NULL);
  CPPUNIT_ASSERT(pParameter1->getName() == "K");
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  Species* pSpecies1 = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pSpecies1->getName() == "A");
  Species* pSpecies2 = pModel->getSpecies(1);
  CPPUNIT_ASSERT(pSpecies2->getName() == "B");
  CPPUNIT_ASSERT(pModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pModel->getNumReactions() == 0);
  CPPUNIT_ASSERT(pModel->getNumEvents() == 1);
  Event* pEvent = pModel->getEvent(0);
  CPPUNIT_ASSERT(pEvent != NULL);
  // check the trigger
  CPPUNIT_ASSERT(pEvent->isSetTrigger());
  Trigger* pTrigger = pEvent->getTrigger();
  CPPUNIT_ASSERT(pTrigger != NULL);
  CPPUNIT_ASSERT(pTrigger->isSetMath());
  const ASTNode* pMath = pTrigger->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_RELATIONAL_GT);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  const ASTNode* pChild = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_NAME_TIME);
  pChild = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild->getReal() - 2.0) / 2.0) < 1e-6);
  // check the delay
  CPPUNIT_ASSERT(pEvent->isSetDelay());
  CPPUNIT_ASSERT(pEvent->getUseValuesFromTriggerTime() == true);
  Delay* pDelay = pEvent->getDelay();
  CPPUNIT_ASSERT(pDelay != NULL);
  CPPUNIT_ASSERT(pDelay->isSetMath());
  pMath = pDelay->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pMath->getReal() - 4.0) / 4.0) < 1e-6);
  // check the event assignment
  CPPUNIT_ASSERT(pEvent->getNumEventAssignments() == 1);
  EventAssignment* pEA = pEvent->getEventAssignment(0);
  CPPUNIT_ASSERT(pEA != NULL);
  CPPUNIT_ASSERT(pEA->getVariable() == pSpecies1->getId());
  pMath = pEA->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains only one node that is a
  // reference to the global parameter
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter1->getId());
  // make sure there is actually a warning MCSBML + 77
  unsigned int i = 0, iMax = CCopasiMessage::size();

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      if (message.getNumber() == MCSBML + 77)
        {
          break;
        }

      ++i;
    }

  CPPUNIT_ASSERT(i != iMax);
}

const char* test000082::MODEL_STRING102 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.4.26 (Debug) (http://www.copasi.org) at 2008-06-12 09:00:21 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"26\">\n"
  "  <Model key=\"Model_0\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:9pt;font-family:Sans Serif\">\n"
  "<p>Simple model with two species and one global parameter. The compartment is fixed and one species is changed by an event assignment.</p>\n"
  "<p>The substance unit is set to mmol.</p>\n"
  "<p>On export both species should be exported with the hasOnlySubstanceUnits flag set to false and the expression for the event assignment should contain a reference to the global parameter.</p>\n"
  "</body></html>\n"
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
  "    <ListOfEvents>\n"
  "      <Event key=\"Event_0\" name=\"event\" delayAssignment=\"false\" >\n"
  "        <TriggerExpression>\n"
  "          &lt;CN=Root,Model=New Model,Reference=Time&gt; gt 2.0\n"
  "        </TriggerExpression>\n"
  "        <DelayExpression>\n"
  "          4.0\n"
  "        </DelayExpression>\n"
  "        <ListOfAssignments>\n"
  "          <Assignment targetKey=\"Metabolite_0\">\n"
  "            <Expression>\n"
  "              &lt;CN=Root,Model=New Model,Vector=Values[K],Reference=Value&gt;\n"
  "            </Expression>\n"
  "          </Assignment>\n"
  "        </ListOfAssignments>\n"
  "      </Event>\n"
  "    </ListOfEvents>\n"
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

void test000082::test_export_delayAssignment_5()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000082::MODEL_STRING103);
  bool result = load_cps_model_from_stream(iss, *pDataModel);
  CPPUNIT_ASSERT(result == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 4).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  CPPUNIT_ASSERT(pDocument->getLevel() == 2);
  CPPUNIT_ASSERT(pDocument->getVersion() == 4);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // check the units
  UnitDefinition* pUDef = pModel->getUnitDefinition("time");
  Unit* pUnit = NULL;

  // since second is the default time unit, it does not have to be exported and
  // might be NULL
  if (pUDef != NULL)
    {
      CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
      pUnit = pUDef->getUnit(0);
      CPPUNIT_ASSERT(pUnit != NULL);
      CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_SECOND);
      CPPUNIT_ASSERT(pUnit->getScale() == 0);
      CPPUNIT_ASSERT(pUnit->getExponent() == 1);
      CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
    }

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
  CPPUNIT_ASSERT(pModel->getNumParameters() == 1);
  Parameter* pParameter1 = pModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter1 != NULL);
  CPPUNIT_ASSERT(pParameter1->getName() == "K");
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  Species* pSpecies1 = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pSpecies1->getName() == "A");
  Species* pSpecies2 = pModel->getSpecies(1);
  CPPUNIT_ASSERT(pSpecies2->getName() == "B");
  CPPUNIT_ASSERT(pModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pModel->getNumReactions() == 0);
  CPPUNIT_ASSERT(pModel->getNumEvents() == 1);
  Event* pEvent = pModel->getEvent(0);
  CPPUNIT_ASSERT(pEvent != NULL);
  // check the trigger
  CPPUNIT_ASSERT(pEvent->isSetTrigger());
  Trigger* pTrigger = pEvent->getTrigger();
  CPPUNIT_ASSERT(pTrigger != NULL);
  CPPUNIT_ASSERT(pTrigger->isSetMath());
  const ASTNode* pMath = pTrigger->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_RELATIONAL_GT);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  const ASTNode* pChild = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_NAME_TIME);
  pChild = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild->getReal() - 2.0) / 2.0) < 1e-6);
  // check the delay
  CPPUNIT_ASSERT(pEvent->isSetDelay() == false);
  CPPUNIT_ASSERT(pEvent->getUseValuesFromTriggerTime() == true);
  Delay* pDelay = pEvent->getDelay();
  CPPUNIT_ASSERT(pDelay == NULL);
  // check the event assignment
  CPPUNIT_ASSERT(pEvent->getNumEventAssignments() == 1);
  EventAssignment* pEA = pEvent->getEventAssignment(0);
  CPPUNIT_ASSERT(pEA != NULL);
  CPPUNIT_ASSERT(pEA->getVariable() == pSpecies1->getId());
  pMath = pEA->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains only one node that is a
  // reference to the global parameter
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter1->getId());
}

void test000082::test_export_delayAssignment_6()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000082::MODEL_STRING103);
  bool result = load_cps_model_from_stream(iss, *pDataModel);
  CPPUNIT_ASSERT(result == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 1).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  CPPUNIT_ASSERT(pDocument->getLevel() == 2);
  CPPUNIT_ASSERT(pDocument->getVersion() == 1);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // check the units
  UnitDefinition* pUDef = pModel->getUnitDefinition("time");
  Unit* pUnit = NULL;

  // since second is the default time unit, it does not have to be exported and
  // might be NULL
  if (pUDef != NULL)
    {
      CPPUNIT_ASSERT(pUDef->getNumUnits() == 1);
      pUnit = pUDef->getUnit(0);
      CPPUNIT_ASSERT(pUnit != NULL);
      CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_SECOND);
      CPPUNIT_ASSERT(pUnit->getScale() == 0);
      CPPUNIT_ASSERT(pUnit->getExponent() == 1);
      CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
    }

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
  CPPUNIT_ASSERT(pModel->getNumParameters() == 1);
  Parameter* pParameter1 = pModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter1 != NULL);
  CPPUNIT_ASSERT(pParameter1->getName() == "K");
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  Species* pSpecies1 = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pSpecies1->getName() == "A");
  Species* pSpecies2 = pModel->getSpecies(1);
  CPPUNIT_ASSERT(pSpecies2->getName() == "B");
  CPPUNIT_ASSERT(pModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pModel->getNumReactions() == 0);
  CPPUNIT_ASSERT(pModel->getNumEvents() == 1);
  Event* pEvent = pModel->getEvent(0);
  CPPUNIT_ASSERT(pEvent != NULL);
  // check the trigger
  CPPUNIT_ASSERT(pEvent->isSetTrigger());
  Trigger* pTrigger = pEvent->getTrigger();
  CPPUNIT_ASSERT(pTrigger != NULL);
  CPPUNIT_ASSERT(pTrigger->isSetMath());
  const ASTNode* pMath = pTrigger->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_RELATIONAL_GT);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  const ASTNode* pChild = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_NAME_TIME);
  pChild = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild->getReal() - 2.0) / 2.0) < 1e-6);
  // check the delay
  CPPUNIT_ASSERT(pEvent->isSetDelay() == false);
  CPPUNIT_ASSERT(pEvent->getUseValuesFromTriggerTime() == true);
  Delay* pDelay = pEvent->getDelay();
  CPPUNIT_ASSERT(pDelay == NULL);
  // check the event assignment
  CPPUNIT_ASSERT(pEvent->getNumEventAssignments() == 1);
  EventAssignment* pEA = pEvent->getEventAssignment(0);
  CPPUNIT_ASSERT(pEA != NULL);
  CPPUNIT_ASSERT(pEA->getVariable() == pSpecies1->getId());
  pMath = pEA->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains only one node that is a
  // reference to the global parameter
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter1->getId());
  // make sure there is actually no warning MCSBML + 77
  unsigned int i = 0, iMax = CCopasiMessage::size();

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();
      CPPUNIT_ASSERT(message.getNumber() != MCSBML + 77);
      ++i;
    }
}

const char* test000082::MODEL_STRING103 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.4.26 (Debug) (http://www.copasi.org) at 2008-06-12 09:00:21 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"26\">\n"
  "  <Model key=\"Model_0\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:9pt;font-family:Sans Serif\">\n"
  "<p>Simple model with two species and one global parameter. The compartment is fixed and one species is changed by an event assignment.</p>\n"
  "<p>The substance unit is set to mmol.</p>\n"
  "<p>On export both species should be exported with the hasOnlySubstanceUnits flag set to false and the expression for the event assignment should contain a reference to the global parameter.</p>\n"
  "</body></html>\n"
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
  "    <ListOfEvents>\n"
  "      <Event key=\"Event_0\" name=\"event\" delayAssignment=\"true\" >\n"
  "        <TriggerExpression>\n"
  "          &lt;CN=Root,Model=New Model,Reference=Time&gt; gt 2.0\n"
  "        </TriggerExpression>\n"
  "        <ListOfAssignments>\n"
  "          <Assignment targetKey=\"Metabolite_0\">\n"
  "            <Expression>\n"
  "              &lt;CN=Root,Model=New Model,Vector=Values[K],Reference=Value&gt;\n"
  "            </Expression>\n"
  "          </Assignment>\n"
  "        </ListOfAssignments>\n"
  "      </Event>\n"
  "    </ListOfEvents>\n"
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
