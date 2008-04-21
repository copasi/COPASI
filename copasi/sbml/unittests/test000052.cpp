// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000052.cpp,v $ 
//   $Revision: 1.1.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/03/04 13:49:55 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

#include "test000052.h"

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

void test000052::setUp()
{
  // Create the root container.
  CCopasiContainer::init();

  // Create the global data model.
  CCopasiDataModel::Global = new CCopasiDataModel;
}

void test000052::tearDown()
{
  delete CCopasiDataModel::Global;
  CCopasiDataModel::Global = NULL;
  delete CCopasiContainer::Root;
  CCopasiContainer::Root = NULL;
}

void test000052::test_bug988()
{
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CModel::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CModel::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CModel::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 1);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::ASSIGNMENT);
  const CExpression* pExpr = pA->getExpressionPtr();
  // check the expression
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  const CEvaluationNodeChoice* pChoiceNode = dynamic_cast<const CEvaluationNodeChoice*>(pNode);
  CPPUNIT_ASSERT(pChoiceNode != NULL);
  pNode=dynamic_cast<const CEvaluationNode*>(pChoiceNode->getChild());
  CPPUNIT_ASSERT(pNode!=NULL);
  const CEvaluationNodeLogical* pLogicalNode=dynamic_cast<const CEvaluationNodeLogical*>(pNode);
  CPPUNIT_ASSERT(pLogicalNode!=NULL);
  CPPUNIT_ASSERT(((CEvaluationNodeLogical::SubType)CEvaluationNode::subType(pLogicalNode->getType()))==CEvaluationNodeLogical::LT);
  const CEvaluationNodeObject* pObjectNode=dynamic_cast<const CEvaluationNodeObject*>(pLogicalNode->getChild());
  CPPUNIT_ASSERT(pObjectNode!=NULL);
  CCopasiObjectName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pModel);
  const CEvaluationNodeNumber* pNumberNode=dynamic_cast<const CEvaluationNodeNumber*>(pObjectNode->getSibling());
  CPPUNIT_ASSERT(pNumberNode!=NULL);
  CPPUNIT_ASSERT(((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pNumberNode->getType()))==CEvaluationNodeNumber::DOUBLE);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 5.0) / 5.0) < 1e-3);
  pNumberNode=dynamic_cast<const CEvaluationNodeNumber*>(pLogicalNode->getSibling());
  CPPUNIT_ASSERT(pNumberNode!=NULL);
  CPPUNIT_ASSERT(((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pNumberNode->getType()))==CEvaluationNodeNumber::DOUBLE);
  CPPUNIT_ASSERT(pNumberNode->value() < 1e-3);
  pNumberNode=dynamic_cast<const CEvaluationNodeNumber*>(pNumberNode->getSibling());
  CPPUNIT_ASSERT(pNumberNode!=NULL);
  CPPUNIT_ASSERT(((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pNumberNode->getType()))==CEvaluationNodeNumber::DOUBLE);
  CPPUNIT_ASSERT(fabs((pNumberNode->value() - 10.0) / 10.0) < 1e-3);

  CPPUNIT_ASSERT(pModel->getModelValues().size() == 0);
  CPPUNIT_ASSERT(pModel->getReactions().size() == 0);
}

const char* test000052::MODEL_STRING =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
"<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
"  <model id=\"Model_1\" name=\"New Model\">\n"
"    <notes>\n"
"      <body xmlns=\"http://www.w3.org/1999/xhtml\"/>\n"
"    </notes>\n"
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
"      <species id=\"species_1\" name=\"species\" compartment=\"compartment_1\" initialConcentration=\"0\" boundaryCondition=\"true\"/>\n"
"    </listOfSpecies>\n"
"    <listOfRules>\n"
"      <assignmentRule variable=\"species_1\">\n"
"        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
"          <piecewise>\n"
"            <piece>\n"
"              <cn> 0 </cn>\n"
"              <apply>\n"
"                <lt/>\n"
"                <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/time\"> time </csymbol>\n"
"                <cn> 5 </cn>\n"
"              </apply>\n"
"            </piece>\n"
"            <otherwise>\n"
"              <cn> 10 </cn>\n"
"            </otherwise>\n"
"          </piecewise>\n"
"        </math>\n"
"      </assignmentRule>\n"
"    </listOfRules>\n"
"  </model>\n"
"</sbml>\n"
;
