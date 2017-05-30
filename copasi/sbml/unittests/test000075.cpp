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

#include "test000075.h"

#include <string>
#include <vector>

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CEvent.h"
#include "copasi/function/CExpression.h"
#include "copasi/function/CFunction.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationNodeCall.h"
#include "copasi/function/CEvaluationNodeObject.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/function/CFunctionDB.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/FunctionDefinition.h"
#include "sbml/math/ASTNode.h"
#include "sbml/Rule.h"
#include "sbml/KineticLaw.h"
#include "sbml/Reaction.h"
#include "sbml/InitialAssignment.h"
#include "sbml/Event.h"
#include "sbml/Trigger.h"
#include "sbml/EventAssignment.h"

#include "copasi/core/CRootContainer.h"

/**
 * Test if importing function definitions which are explicitely time dependent
 * works.
 * Problems related to this are also tracked in Bug 1093.
 * This test also covers the bugs described there.
 */
CDataModel* test000075::pCOPASIDATAMODEL = NULL;

void test000075::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000075::tearDown()
{
  CRootContainer::destroy();
}

void test000075::test_import_time_dependent_function_definition()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING1));
  // there have to be 2 function definitions, 1 compartment, 4 species, 4
  // parameters, 1 reaction, 1 initial assignment, 5 rules (2 rate + 2
  // assignment) and 1 event
  const CModel* pCModel = pCOPASIDATAMODEL->getModel();
  CPPUNIT_ASSERT(pCModel != NULL);
  CPPUNIT_ASSERT(pCModel->getCompartments().size() == 1);
  const CCompartment* pCCompartment = pCModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCCompartment != NULL);
  CPPUNIT_ASSERT(pCCompartment->getStatus() == CModelEntity::Status::FIXED);
  const CEvaluationNodeObject* pCObjectNode = NULL;
  const CRegisteredCommonName* pCObjectName = NULL;
  CObjectInterface::ContainerList listOfContainers;
  listOfContainers.push_back(pCOPASIDATAMODEL->getModel());
  const CDataObject* pCObject = NULL;

  CPPUNIT_ASSERT(pCModel->getMetabolites().size() == 4);
  // get species_1 and species_2 those two should have rules defined
  const CMetab* pCSpecies1 = NULL;
  const CMetab* pCSpecies2 = NULL;
  unsigned int i, iMax = pCModel->getMetabolites().size();

  for (i = 0; i < iMax; ++i)
    {
      if (pCModel->getMetabolites()[i]->getObjectName() == std::string("species_1"))
        {
          pCSpecies1 = pCModel->getMetabolites()[i];
        }
      else if (pCModel->getMetabolites()[i]->getObjectName() == std::string("species_2"))
        {
          pCSpecies2 = pCModel->getMetabolites()[i];
        }
    }

  CPPUNIT_ASSERT(pCSpecies1 != NULL);
  CPPUNIT_ASSERT(pCSpecies1->getStatus() == CModelEntity::Status::ASSIGNMENT);
  const CExpression* pCExpression = pCSpecies1->getExpressionPtr();
  CPPUNIT_ASSERT(pCExpression != NULL);
  const CEvaluationNode* pCRoot = pCExpression->getRoot();
  CPPUNIT_ASSERT(pCRoot != NULL);
  CPPUNIT_ASSERT(pCRoot->mainType() == CEvaluationNode::MainType::CALL);
  const CEvaluationNodeCall* pCCallNode = dynamic_cast<const CEvaluationNodeCall*>(pCRoot);
  CPPUNIT_ASSERT(pCCallNode != NULL);
  CPPUNIT_ASSERT(pCCallNode->getData() == std::string("time_dependent"));
  // the first child is a number
  const CEvaluationNode* pCChild1 = dynamic_cast<const CEvaluationNode*>(pCCallNode->getChild());
  CPPUNIT_ASSERT(pCChild1 != NULL);
  CPPUNIT_ASSERT(pCChild1->mainType() == CEvaluationNode::MainType::NUMBER);
  // the second node must be an object node that points to the model
  const CEvaluationNode* pCChild2 = dynamic_cast<const CEvaluationNode*>(pCChild1->getSibling());
  CPPUNIT_ASSERT(pCChild2 != NULL);
  CPPUNIT_ASSERT(pCChild2->mainType() == CEvaluationNode::MainType::OBJECT);
  pCObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pCChild2);
  CPPUNIT_ASSERT(pCObjectNode != NULL);
  pCObjectName = &pCObjectNode->getObjectCN();
  pCObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, *pCObjectName));
  CPPUNIT_ASSERT(pCObject != NULL);
  CPPUNIT_ASSERT(pCObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pCObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pCObject->getObjectParent() == pCModel);

  CPPUNIT_ASSERT(pCSpecies2 != NULL);
  CPPUNIT_ASSERT(pCSpecies2->getStatus() == CModelEntity::Status::ODE);
  pCExpression = pCSpecies2->getExpressionPtr();
  CPPUNIT_ASSERT(pCExpression != NULL);
  pCRoot = pCExpression->getRoot();
  CPPUNIT_ASSERT(pCRoot != NULL);
  CPPUNIT_ASSERT(pCRoot->mainType() == CEvaluationNode::MainType::CALL);
  pCCallNode = dynamic_cast<const CEvaluationNodeCall*>(pCRoot);
  CPPUNIT_ASSERT(pCCallNode != NULL);
  CPPUNIT_ASSERT(pCCallNode->getData() == std::string("time_dependent"));
  // the first child is a number
  pCChild1 = dynamic_cast<const CEvaluationNode*>(pCCallNode->getChild());
  CPPUNIT_ASSERT(pCChild1 != NULL);
  CPPUNIT_ASSERT(pCChild1->mainType() == CEvaluationNode::MainType::NUMBER);
  // the second node must be an object node that points to the model
  pCChild2 = dynamic_cast<const CEvaluationNode*>(pCChild1->getSibling());
  CPPUNIT_ASSERT(pCChild2 != NULL);
  CPPUNIT_ASSERT(pCChild2->mainType() == CEvaluationNode::MainType::OBJECT);
  pCObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pCChild2);
  CPPUNIT_ASSERT(pCObjectNode != NULL);
  pCObjectName = &pCObjectNode->getObjectCN();
  pCObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, *pCObjectName));
  CPPUNIT_ASSERT(pCObject != NULL);
  CPPUNIT_ASSERT(pCObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pCObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pCObject->getObjectParent() == pCModel);

  CPPUNIT_ASSERT(pCModel->getModelValues().size() == 5);
  // check parameter_1 and parameter_2 which have rules defined
  // also check parameter_4 und parameter_5 which have initial assignments
  const CModelValue* pCModelValue1 = NULL;
  const CModelValue* pCModelValue2 = NULL;
  const CModelValue* pCModelValue4 = NULL;
  const CModelValue* pCModelValue5 = NULL;
  iMax = pCModel->getModelValues().size();

  for (i = 0; i < iMax; ++i)
    {
      if (pCModel->getModelValues()[i]->getObjectName() == std::string("parameter_1"))
        {
          pCModelValue1 = pCModel->getModelValues()[i];
        }
      else if (pCModel->getModelValues()[i]->getObjectName() == std::string("parameter_2"))
        {
          pCModelValue2 = pCModel->getModelValues()[i];
        }
      else if (pCModel->getModelValues()[i]->getObjectName() == std::string("parameter_4"))
        {
          pCModelValue4 = pCModel->getModelValues()[i];
        }
      else if (pCModel->getModelValues()[i]->getObjectName() == std::string("parameter_5"))
        {
          pCModelValue5 = pCModel->getModelValues()[i];
        }
    }

  CPPUNIT_ASSERT(pCModelValue1 != NULL);
  CPPUNIT_ASSERT(pCModelValue1->getStatus() == CModelEntity::Status::ASSIGNMENT);
  pCExpression = pCModelValue1->getExpressionPtr();
  CPPUNIT_ASSERT(pCExpression != NULL);
  pCRoot = pCExpression->getRoot();
  CPPUNIT_ASSERT(pCRoot != NULL);
  CPPUNIT_ASSERT(pCRoot->mainType() == CEvaluationNode::MainType::CALL);
  pCCallNode = dynamic_cast<const CEvaluationNodeCall*>(pCRoot);
  CPPUNIT_ASSERT(pCCallNode != NULL);
  CPPUNIT_ASSERT(pCCallNode->getData() == std::string("time_dependent"));
  // the first child is a number
  pCChild1 = dynamic_cast<const CEvaluationNode*>(pCCallNode->getChild());
  CPPUNIT_ASSERT(pCChild1 != NULL);
  CPPUNIT_ASSERT(pCChild1->mainType() == CEvaluationNode::MainType::NUMBER);
  // the second node must be an object node that points to the model
  pCChild2 = dynamic_cast<const CEvaluationNode*>(pCChild1->getSibling());
  CPPUNIT_ASSERT(pCChild2 != NULL);
  CPPUNIT_ASSERT(pCChild2->mainType() == CEvaluationNode::MainType::OBJECT);
  pCObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pCChild2);
  CPPUNIT_ASSERT(pCObjectNode != NULL);
  pCObjectName = &pCObjectNode->getObjectCN();
  pCObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, *pCObjectName));
  CPPUNIT_ASSERT(pCObject != NULL);
  CPPUNIT_ASSERT(pCObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pCObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pCObject->getObjectParent() == pCModel);

  CPPUNIT_ASSERT(pCModelValue2 != NULL);
  CPPUNIT_ASSERT(pCModelValue2->getStatus() == CModelEntity::Status::ODE);
  pCExpression = pCModelValue2->getExpressionPtr();
  CPPUNIT_ASSERT(pCExpression != NULL);
  pCRoot = pCExpression->getRoot();
  CPPUNIT_ASSERT(pCRoot != NULL);
  CPPUNIT_ASSERT(pCRoot->mainType() == CEvaluationNode::MainType::CALL);
  pCCallNode = dynamic_cast<const CEvaluationNodeCall*>(pCRoot);
  CPPUNIT_ASSERT(pCCallNode != NULL);
  CPPUNIT_ASSERT(pCCallNode->getData() == std::string("time_dependent"));
  // the first child is a number
  pCChild1 = dynamic_cast<const CEvaluationNode*>(pCCallNode->getChild());
  CPPUNIT_ASSERT(pCChild1 != NULL);
  CPPUNIT_ASSERT(pCChild1->mainType() == CEvaluationNode::MainType::NUMBER);
  // the second node must be an object node that points to the model
  pCChild2 = dynamic_cast<const CEvaluationNode*>(pCChild1->getSibling());
  CPPUNIT_ASSERT(pCChild2 != NULL);
  CPPUNIT_ASSERT(pCChild2->mainType() == CEvaluationNode::MainType::OBJECT);
  pCObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pCChild2);
  CPPUNIT_ASSERT(pCObjectNode != NULL);
  pCObjectName = &pCObjectNode->getObjectCN();
  pCObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, *pCObjectName));
  CPPUNIT_ASSERT(pCObject != NULL);
  CPPUNIT_ASSERT(pCObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pCObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pCObject->getObjectParent() == pCModel);

  CPPUNIT_ASSERT(pCModelValue4 != NULL);
  CPPUNIT_ASSERT(pCModelValue4->getStatus() == CModelEntity::Status::FIXED);
  pCExpression = pCModelValue4->getInitialExpressionPtr();
  CPPUNIT_ASSERT(pCExpression != NULL);
  pCRoot = pCExpression->getRoot();
  CPPUNIT_ASSERT(pCRoot != NULL);
  CPPUNIT_ASSERT(pCRoot->mainType() == CEvaluationNode::MainType::CALL);
  pCCallNode = dynamic_cast<const CEvaluationNodeCall*>(pCRoot);
  CPPUNIT_ASSERT(pCCallNode != NULL);
  CPPUNIT_ASSERT(pCCallNode->getData() == std::string("time_dependent"));
  // the first child is a number
  pCChild1 = dynamic_cast<const CEvaluationNode*>(pCCallNode->getChild());
  CPPUNIT_ASSERT(pCChild1 != NULL);
  CPPUNIT_ASSERT(pCChild1->mainType() == CEvaluationNode::MainType::NUMBER);
  // the second node must be an object node that points to the model
  pCChild2 = dynamic_cast<const CEvaluationNode*>(pCChild1->getSibling());
  CPPUNIT_ASSERT(pCChild2 != NULL);
  CPPUNIT_ASSERT(pCChild2->mainType() == CEvaluationNode::MainType::OBJECT);
  pCObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pCChild2);
  CPPUNIT_ASSERT(pCObjectNode != NULL);
  pCObjectName = &pCObjectNode->getObjectCN();
  pCObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, *pCObjectName));
  CPPUNIT_ASSERT(pCObject != NULL);
  CPPUNIT_ASSERT(pCObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pCObject->getObjectName() == std::string("Initial Time"));
  CPPUNIT_ASSERT(pCObject->getObjectParent() == pCModel);

  CPPUNIT_ASSERT(pCModelValue5 != NULL);
  CPPUNIT_ASSERT(pCModelValue5->getStatus() == CModelEntity::Status::FIXED);
  pCExpression = pCModelValue5->getInitialExpressionPtr();
  CPPUNIT_ASSERT(pCExpression != NULL);
  pCRoot = pCExpression->getRoot();
  CPPUNIT_ASSERT(pCRoot != NULL);
  CPPUNIT_ASSERT(pCRoot->mainType() == CEvaluationNode::MainType::CALL);
  pCCallNode = dynamic_cast<const CEvaluationNodeCall*>(pCRoot);
  CPPUNIT_ASSERT(pCCallNode != NULL);
  // the first child is a number node
  CPPUNIT_ASSERT(pCCallNode->getData() == std::string("indirectly_time_dependent"));
  pCChild1 = dynamic_cast<const CEvaluationNode*>(pCCallNode->getChild());
  CPPUNIT_ASSERT(pCChild1 != NULL);
  CPPUNIT_ASSERT(pCChild1->mainType() == CEvaluationNode::MainType::NUMBER);

  // the second child is the time object
  pCChild2 = dynamic_cast<const CEvaluationNode*>(pCChild1->getSibling());
  CPPUNIT_ASSERT(pCChild2 != NULL);
  CPPUNIT_ASSERT(pCChild2->mainType() == CEvaluationNode::MainType::OBJECT);
  pCObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pCChild2);
  CPPUNIT_ASSERT(pCObjectNode != NULL);
  pCObjectName = &pCObjectNode->getObjectCN();
  pCObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, *pCObjectName));
  CPPUNIT_ASSERT(pCObject != NULL);
  CPPUNIT_ASSERT(pCObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pCObject->getObjectName() == std::string("Initial Time"));
  CPPUNIT_ASSERT(pCObject->getObjectParent() == pCModel);

  CPPUNIT_ASSERT(pCModel->getReactions().size() == 1);
  const CReaction* pCReaction = pCModel->getReactions()[0];
  CPPUNIT_ASSERT(pCReaction != NULL);
  CPPUNIT_ASSERT(pCReaction->isReversible() == false);
  const CChemEq& chemEq = pCReaction->getChemEq();
  CPPUNIT_ASSERT(chemEq.getSubstrates().size() == 1);
  CPPUNIT_ASSERT(chemEq.getProducts().size() == 1);
  CPPUNIT_ASSERT(chemEq.getModifiers().size() == 0);
  const CFunction* pCFunction = pCReaction->getFunction();
  CPPUNIT_ASSERT(pCFunction != NULL);
  pCRoot = pCFunction->getRoot();
  CPPUNIT_ASSERT(pCRoot != NULL);
  CPPUNIT_ASSERT(pCRoot->mainType() == CEvaluationNode::MainType::CALL);
  pCCallNode = dynamic_cast<const CEvaluationNodeCall*>(pCRoot);
  CPPUNIT_ASSERT(pCCallNode != NULL);
  CPPUNIT_ASSERT(pCCallNode->getData() == std::string("time_dependent"));
  // the first child is a number
  pCChild1 = dynamic_cast<const CEvaluationNode*>(pCCallNode->getChild());
  CPPUNIT_ASSERT(pCChild1 != NULL);
  CPPUNIT_ASSERT(pCChild1->mainType() == CEvaluationNode::MainType::NUMBER);
  // the second node must be an object node that points to the model
  pCChild2 = dynamic_cast<const CEvaluationNode*>(pCChild1->getSibling());
  CPPUNIT_ASSERT(pCChild2 != NULL);
  CPPUNIT_ASSERT(pCChild2->mainType() == CEvaluationNode::MainType::VARIABLE);
  // get the argument for this variable
  std::string variableName = pCChild2->getData();
  const std::vector<std::string>& parameterMapping = pCReaction->getParameterMapping(variableName);
  CPPUNIT_ASSERT(parameterMapping.size() == 1);
  std::string objectKey = parameterMapping[0];
  CPPUNIT_ASSERT(!objectKey.empty());
  pCObject = CRootContainer::getKeyFactory()->get(objectKey);
  CPPUNIT_ASSERT(pCObject != NULL);
  CPPUNIT_ASSERT(pCObject == pCModel);

  // events
  CPPUNIT_ASSERT(pCModel->getEvents().size() == 1);
  const CEvent* pCEvent = pCModel->getEvents()[0];
  CPPUNIT_ASSERT(pCEvent != NULL);
  // event trigger functionDefinition1(5.0,TIME) > 2.0
  pCExpression = pCEvent->getTriggerExpressionPtr();
  CPPUNIT_ASSERT(pCExpression != NULL);
  pCRoot = pCExpression->getRoot();
  CPPUNIT_ASSERT(pCRoot != NULL);
  // root must be the gt operator
  CPPUNIT_ASSERT(pCRoot->mainType() == CEvaluationNode::MainType::LOGICAL);
  CPPUNIT_ASSERT((pCRoot->subType()) == CEvaluationNode::SubType::GT);
  pCChild1 = dynamic_cast<const CEvaluationNode*>(pCRoot->getChild());
  CPPUNIT_ASSERT(pCChild1 != NULL);
  // first child must be the changed call
  CPPUNIT_ASSERT(pCChild1->mainType() == CEvaluationNode::MainType::CALL);
  pCCallNode = dynamic_cast<const CEvaluationNodeCall*>(pCChild1);
  CPPUNIT_ASSERT(pCCallNode != NULL);
  CPPUNIT_ASSERT(pCCallNode->getData() == std::string("time_dependent"));
  // the first child is a number
  pCChild1 = dynamic_cast<const CEvaluationNode*>(pCCallNode->getChild());
  CPPUNIT_ASSERT(pCChild1 != NULL);
  CPPUNIT_ASSERT(pCChild1->mainType() == CEvaluationNode::MainType::NUMBER);
  // the second node must be an object node that points to the model
  pCChild2 = dynamic_cast<const CEvaluationNode*>(pCChild1->getSibling());
  CPPUNIT_ASSERT(pCChild2 != NULL);
  CPPUNIT_ASSERT(pCChild2->mainType() == CEvaluationNode::MainType::OBJECT);
  pCObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pCChild2);
  CPPUNIT_ASSERT(pCObjectNode != NULL);
  pCObjectName = &pCObjectNode->getObjectCN();
  pCObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, *pCObjectName));
  CPPUNIT_ASSERT(pCObject != NULL);
  CPPUNIT_ASSERT(pCObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pCObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pCObject->getObjectParent() == pCModel);
  //
  // second child must be a number
  pCChild2 = dynamic_cast<const CEvaluationNode*>(pCRoot->getChild()->getSibling());
  CPPUNIT_ASSERT(pCChild2 != NULL);
  CPPUNIT_ASSERT(pCChild2->mainType() == CEvaluationNode::MainType::NUMBER);

  // event assignment
  CPPUNIT_ASSERT(pCEvent->getAssignments().size() == 1);
  pCExpression = pCEvent->getAssignments()[0]->getExpressionPtr();
  CPPUNIT_ASSERT(pCExpression != NULL);
  pCRoot = pCExpression->getRoot();
  CPPUNIT_ASSERT(pCRoot != NULL);
  CPPUNIT_ASSERT(pCRoot->mainType() == CEvaluationNode::MainType::CALL);
  pCCallNode = dynamic_cast<const CEvaluationNodeCall*>(pCRoot);
  CPPUNIT_ASSERT(pCCallNode != NULL);
  CPPUNIT_ASSERT(pCCallNode->getData() == std::string("time_dependent"));
  // the first child is a number
  pCChild1 = dynamic_cast<const CEvaluationNode*>(pCCallNode->getChild());
  CPPUNIT_ASSERT(pCChild1 != NULL);
  CPPUNIT_ASSERT(pCChild1->mainType() == CEvaluationNode::MainType::NUMBER);
  // the second node must be an object node that points to the model
  pCChild2 = dynamic_cast<const CEvaluationNode*>(pCChild1->getSibling());
  CPPUNIT_ASSERT(pCChild2 != NULL);
  CPPUNIT_ASSERT(pCChild2->mainType() == CEvaluationNode::MainType::OBJECT);
  pCObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pCChild2);
  CPPUNIT_ASSERT(pCObjectNode != NULL);
  pCObjectName = &pCObjectNode->getObjectCN();
  pCObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, *pCObjectName));
  CPPUNIT_ASSERT(pCObject != NULL);
  CPPUNIT_ASSERT(pCObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pCObject->getObjectName() == std::string("Time"));
  CPPUNIT_ASSERT(pCObject->getObjectParent() == pCModel);

  // check if the function definitions are imported correctly
  CFunctionDB* pFunctionDB = CRootContainer::getFunctionList();
  CPPUNIT_ASSERT(pFunctionDB != NULL);
  const CEvaluationTree* pCTree = pFunctionDB->findFunction("time_dependent");
  CPPUNIT_ASSERT(pCTree != NULL);
  pCFunction = dynamic_cast<const CFunction*>(pCTree);
  CPPUNIT_ASSERT(pCFunction != NULL);
  // should have two parameters instead of one
  CPPUNIT_ASSERT(pCFunction->getVariables().size() == 2);
  pCRoot = pCFunction->getRoot();
  CPPUNIT_ASSERT(pCRoot->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT((pCRoot->subType()) == CEvaluationNode::SubType::MULTIPLY);
  pCChild1 = dynamic_cast<const CEvaluationNode*>(pCRoot->getChild());
  CPPUNIT_ASSERT(pCChild1 != NULL);
  CPPUNIT_ASSERT(pCChild1->mainType() == CEvaluationNode::MainType::VARIABLE);
  pCChild2 = dynamic_cast<const CEvaluationNode*>(pCChild1->getSibling());
  CPPUNIT_ASSERT(pCChild2 != NULL);
  CPPUNIT_ASSERT(pCChild2->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pCChild2->getSibling() == NULL);

  pCTree = pFunctionDB->findFunction("indirectly_time_dependent");
  CPPUNIT_ASSERT(pCTree != NULL);
  pCFunction = dynamic_cast<const CFunction*>(pCTree);
  CPPUNIT_ASSERT(pCFunction != NULL);
  // should have two parameters instead of one
  CPPUNIT_ASSERT(pCFunction->getVariables().size() == 2);
  pCRoot = pCFunction->getRoot();
  CPPUNIT_ASSERT(pCRoot->mainType() == CEvaluationNode::MainType::CALL);
  pCChild1 = dynamic_cast<const CEvaluationNode*>(pCRoot->getChild());
  CPPUNIT_ASSERT(pCChild1 != NULL);
  CPPUNIT_ASSERT(pCChild1->mainType() == CEvaluationNode::MainType::VARIABLE);
  pCChild2 = dynamic_cast<const CEvaluationNode*>(pCChild1->getSibling());
  CPPUNIT_ASSERT(pCChild2 != NULL);
  CPPUNIT_ASSERT(pCChild2->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pCChild2->getSibling() == NULL);

  // make sure that the function definitions and all function calls in the
  // original SBML model are unmodified
  //
  const SBMLDocument* pSBMLDocument = pCOPASIDATAMODEL->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pSBMLDocument != NULL);
  const Model* pModel = pSBMLDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  iMax = pModel->getNumFunctionDefinitions();
  CPPUNIT_ASSERT(iMax == 2);
  const FunctionDefinition* pFunctionDefinition1 = NULL;
  const FunctionDefinition* pFunctionDefinition2 = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pModel->getFunctionDefinition(i)->getId() == std::string("functionDefinition_1"))
        {
          pFunctionDefinition1 = pModel->getFunctionDefinition(i);
        }
      else if (pModel->getFunctionDefinition(i)->getId() == std::string("functionDefinition_2"))
        {
          pFunctionDefinition2 = pModel->getFunctionDefinition(i);
        }
    }

  CPPUNIT_ASSERT(pFunctionDefinition1 != NULL);
  CPPUNIT_ASSERT(pFunctionDefinition1->getNumArguments() == 1);
  const ASTNode* pRoot = pFunctionDefinition1->getMath();
  CPPUNIT_ASSERT(pRoot != NULL);
  // the expression is the last child
  CPPUNIT_ASSERT(pRoot->getNumChildren() == 2);
  pRoot = pRoot->getChild(1);
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(pRoot->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pRoot->getNumChildren() == 2);
  CPPUNIT_ASSERT(pRoot->getChild(0)->getType() == AST_NAME_TIME);
  CPPUNIT_ASSERT(pRoot->getChild(1)->getType() == AST_NAME);
  // second function definition
  CPPUNIT_ASSERT(pFunctionDefinition2 != NULL);
  CPPUNIT_ASSERT(pFunctionDefinition2->getNumArguments() == 1);
  pRoot = pFunctionDefinition2->getMath();
  CPPUNIT_ASSERT(pRoot != NULL);
  // the expression is the last child
  CPPUNIT_ASSERT(pRoot->getNumChildren() == 2);
  pRoot = pRoot->getChild(1);
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(pRoot->getType() == AST_FUNCTION);
  CPPUNIT_ASSERT(pRoot->getNumChildren() == 1);
  CPPUNIT_ASSERT(pRoot->getChild(0)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pRoot->getChild(0)->getName() == std::string("n"));

  // initial assignment
  iMax = pModel->getListOfInitialAssignments()->size();
  CPPUNIT_ASSERT(iMax == 2);
  const InitialAssignment* pInitialAssignment1 = NULL;
  const InitialAssignment* pInitialAssignment2 = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pModel->getInitialAssignment(i)->getSymbol() == std::string("parameter_4"))
        {
          pInitialAssignment1 = pModel->getInitialAssignment(i);
        }
      else if (pModel->getInitialAssignment(i)->getSymbol() == std::string("parameter_5"))
        {
          pInitialAssignment2 = pModel->getInitialAssignment(i);
        }
    }

  CPPUNIT_ASSERT(pInitialAssignment1 != NULL);
  pRoot = pInitialAssignment1->getMath();
  CPPUNIT_ASSERT(pRoot->getType() == AST_FUNCTION);
  CPPUNIT_ASSERT(pRoot->getName() == std::string("functionDefinition_1"));
  CPPUNIT_ASSERT(pRoot->getNumChildren() == 1);
  CPPUNIT_ASSERT(pRoot->getChild(0)->getType() == AST_REAL);

  CPPUNIT_ASSERT(pInitialAssignment2 != NULL);
  pRoot = pInitialAssignment2->getMath();
  CPPUNIT_ASSERT(pRoot->getType() == AST_FUNCTION);
  CPPUNIT_ASSERT(pRoot->getName() == std::string("functionDefinition_2"));
  CPPUNIT_ASSERT(pRoot->getNumChildren() == 1);
  CPPUNIT_ASSERT(pRoot->getChild(0)->getType() == AST_REAL);

  // rules
  iMax = pModel->getListOfRules()->size();
  CPPUNIT_ASSERT(iMax == 4);

  for (i = 0; i < iMax; ++i)
    {
      // only check the expression
      // in this test we don't care if the variable is correct and if the rule
      // type is correct
      const Rule* pRule = pModel->getRule(i);
      CPPUNIT_ASSERT(pRule != NULL);
      pRoot = pRule->getMath();
      CPPUNIT_ASSERT(pRoot != NULL);
      CPPUNIT_ASSERT(pRoot->getType() == AST_FUNCTION);
      CPPUNIT_ASSERT(pRoot->getNumChildren() == 1);
      CPPUNIT_ASSERT(pRoot->getChild(0)->getType() == AST_REAL);
    }

  // reaction
  CPPUNIT_ASSERT(pModel->getListOfReactions()->size() == 1);
  const Reaction* pReaction = pModel->getReaction(0);
  CPPUNIT_ASSERT(pReaction != NULL);
  const KineticLaw* pKineticLaw = pReaction->getKineticLaw();
  CPPUNIT_ASSERT(pKineticLaw != NULL);
  pRoot = pKineticLaw->getMath();
  CPPUNIT_ASSERT(pRoot != NULL);
  // multiplication by compartment volume
  CPPUNIT_ASSERT(pRoot->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pRoot->getNumChildren() == 2);
  CPPUNIT_ASSERT(pRoot->getChild(0)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pRoot->getChild(1)->getType() == AST_FUNCTION);
  pRoot = pRoot->getChild(1);
  CPPUNIT_ASSERT(pRoot->getNumChildren() == 1);
  CPPUNIT_ASSERT(pRoot->getChild(0)->getType() == AST_REAL);

  // event
  CPPUNIT_ASSERT(pModel->getListOfEvents()->size() == 1);
  const Event* pEvent = pModel->getEvent(0);
  CPPUNIT_ASSERT(pEvent != NULL);
  const Trigger* pTrigger = pEvent->getTrigger();
  CPPUNIT_ASSERT(pTrigger != NULL);
  pRoot = pTrigger->getMath();
  CPPUNIT_ASSERT(pRoot != NULL);
  // functionDefinition_1(5.0) > 2.0
  CPPUNIT_ASSERT(pRoot->getType() == AST_RELATIONAL_GT);
  CPPUNIT_ASSERT(pRoot->getNumChildren() == 2);
  CPPUNIT_ASSERT(pRoot->getChild(1) != NULL);
  CPPUNIT_ASSERT(pRoot->getChild(1)->getType() == AST_REAL);
  CPPUNIT_ASSERT(pRoot->getChild(0) != NULL);
  pRoot = pRoot->getChild(0);
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(pRoot->getType() == AST_FUNCTION);
  CPPUNIT_ASSERT(pRoot->getNumChildren() == 1);
  CPPUNIT_ASSERT(pRoot->getChild(0)->getType() == AST_REAL);

  CPPUNIT_ASSERT(pEvent->getListOfEventAssignments()->size() == 1);
  const EventAssignment* pEventAssignment = pEvent->getEventAssignment(0);
  CPPUNIT_ASSERT(pEventAssignment != NULL);
  pRoot = pEventAssignment->getMath();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(pRoot->getType() == AST_FUNCTION);
  CPPUNIT_ASSERT(pRoot->getNumChildren() == 1);
  CPPUNIT_ASSERT(pRoot->getChild(0)->getType() == AST_REAL);
}

const char* test000075::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version2\" level=\"2\" version=\"2\">\n"
  "  <model id=\"model_1\" name=\"model_1\">\n"
  "    <notes>\n"
  "      <p xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "      This model contains an explicitly time dependent function definition.\n"
  "      On import in COPASI this should be converted to a function definition that has time as it's only argument.\n"
  "      All calls to this function must be replaced.\n"
  "      </p>\n"
  "    </notes>\n"
  "    <listOfFunctionDefinitions>\n"
  "      <functionDefinition id=\"functionDefinition_1\" name=\"time_dependent\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <lambda>\n"
  "            <bvar>\n"
  "              <ci>p</ci>\n"
  "            </bvar>\n"
  "            <apply>\n"
  "              <times/>\n"
  "              <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/time\"> time </csymbol>\n"
  "              <ci>p</ci>\n"
  "            </apply>  \n"
  "          </lambda>\n"
  "        </math>\n"
  "      </functionDefinition>\n"
  "      <functionDefinition id=\"functionDefinition_2\" name=\"indirectly_time_dependent\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <lambda>\n"
  "            <bvar>\n"
  "              <ci>n</ci>\n"
  "            </bvar>\n"
  "            <apply>\n"
  "              <ci> functionDefinition_1 </ci>\n"
  "              <ci> n </ci>\n"
  "            </apply>\n"
  "          </lambda>\n"
  "        </math>\n"
  "      </functionDefinition>\n"
  "    </listOfFunctionDefinitions>\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment_1\" size=\"1\" />\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"species_1\" compartment=\"compartment_1\" initialConcentration=\"0.0\" />\n"
  "      <species id=\"species_2\" name=\"species_2\" compartment=\"compartment_1\" initialConcentration=\"0.0\" />\n"
  "      <species id=\"species_3\" name=\"species_3\" compartment=\"compartment_1\" initialConcentration=\"0.0\" />\n"
  "      <species id=\"species_4\" name=\"species_4\" compartment=\"compartment_1\" initialConcentration=\"0.0\" />\n"
  "    </listOfSpecies>\n"
  "    <listOfParameters>\n"
  "      <parameter id=\"parameter_1\" name=\"parameter_1\" constant=\"false\"/>\n"
  "      <parameter id=\"parameter_2\" name=\"parameter_2\" constant=\"false\"/>\n"
  "      <parameter id=\"parameter_3\" name=\"parameter_3\" constant=\"false\"/>\n"
  "      <parameter id=\"parameter_4\" name=\"parameter_4\" constant=\"true\"/>\n"
  "      <parameter id=\"parameter_5\" name=\"parameter_5\" constant=\"true\"/>\n"
  "    </listOfParameters>\n"
  "    <listOfInitialAssignments>\n"
  "      <initialAssignment symbol=\"parameter_4\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <ci> functionDefinition_1 </ci>\n"
  "            <cn> 5.0 </cn>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </initialAssignment>\n"
  "      <initialAssignment symbol=\"parameter_5\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <ci> functionDefinition_2 </ci>\n"
  "            <cn> 3.2 </cn>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </initialAssignment>\n"
  "    </listOfInitialAssignments>\n"
  "    <listOfRules>\n"
  "      <assignmentRule variable=\"parameter_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <ci> functionDefinition_1 </ci>\n"
  "            <cn> 5.0 </cn>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "      <rateRule variable=\"parameter_2\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <ci> functionDefinition_1 </ci>\n"
  "            <cn> 5.0 </cn>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </rateRule>\n"
  "      <assignmentRule variable=\"species_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <ci> functionDefinition_1 </ci>\n"
  "            <cn> 5.0 </cn>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "      <rateRule variable=\"species_2\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <ci> functionDefinition_1 </ci>\n"
  "            <cn> 5.0 </cn>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </rateRule>\n"
  "    </listOfRules>\n"
  "    <listOfReactions>\n"
  "      <reaction id=\"reaction_1\" name=\"reaction_1\" reversible=\"false\">\n"
  "        <listOfReactants>\n"
  "          <speciesReference species=\"species_3\"/>\n"
  "        </listOfReactants>\n"
  "        <listOfProducts>\n"
  "          <speciesReference species=\"species_4\"/>\n"
  "        </listOfProducts>\n"
  "        <kineticLaw>\n"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "            <apply>\n"
  "              <times/>\n"
  "              <ci> compartment_1 </ci>\n"
  "              <apply>\n"
  "                <ci> functionDefinition_1 </ci>\n"
  "                <cn> 5.0 </cn>\n"
  "              </apply>\n"
  "            </apply>\n"
  "          </math>\n"
  "        </kineticLaw>\n"
  "      </reaction>\n"
  "    </listOfReactions>\n"
  "    <listOfEvents>\n"
  "      <event>\n"
  "        <trigger>\n"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "            <apply>\n"
  "              <gt/>\n"
  "              <apply>\n"
  "                <ci> functionDefinition_1 </ci>\n"
  "                <cn> 5.0 </cn>\n"
  "              </apply>\n"
  "              <cn> 2.0 </cn>\n"
  "            </apply>\n"
  "          </math>\n"
  "        </trigger>\n"
  "        <listOfEventAssignments>\n"
  "          <eventAssignment variable=\"parameter_3\">\n"
  "            <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "              <apply>\n"
  "                <ci> functionDefinition_1 </ci>\n"
  "                <cn> 5.0 </cn>\n"
  "              </apply>\n"
  "            </math>\n"
  "          </eventAssignment>\n"
  "        </listOfEventAssignments>\n"
  "      </event>\n"
  "    </listOfEvents>\n"
  "  </model>\n"
  "</sbml>\n"
  ;
