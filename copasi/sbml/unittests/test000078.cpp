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

#include "test000078.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CReaction.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationNodeNumber.h"
#include "copasi/function/CEvaluationNodeVariable.h"
#include "copasi/function/CExpression.h"
#include "copasi/function/CEvaluationTree.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/function/CKinFunction.h"
#include "copasi/function/CEvaluationTree.h"
#include "copasi/function/CFunctionParameters.h"
#include "copasi/function/CFunctionParameter.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"

#include "copasi/core/CRootContainer.h"

CDataModel* test000078::pCOPASIDATAMODEL = NULL;

void test000078::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000078::tearDown()
{
  CRootContainer::destroy();
}

void test000078::test_l2v4_import_unordered_functions()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;

  try
    {
      CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING1));
    }
  catch (...)
    {
      // there should not be any exceptions
      CPPUNIT_ASSERT(false);
    }

  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CUnit::Mol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CUnit::l);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CUnit::s);
  // check if the function definitions were imported correctly
  CFunctionDB* pFunDB = CRootContainer::getFunctionList();
  const CEvaluationTree* pFun = pFunDB->findFunction("function_1");
  CPPUNIT_ASSERT(pFun != NULL);
  const CKinFunction* pKinFun = dynamic_cast<const CKinFunction*>(pFun);
  CPPUNIT_ASSERT(pKinFun != NULL);
  // 1 parameter called k
  // expression is 3.0 * k
  const CFunctionParameters* pFunParams = &pKinFun->getVariables();
  CPPUNIT_ASSERT(pFunParams != NULL);
  CPPUNIT_ASSERT(pFunParams->size() == 1);
  const CFunctionParameter* pFunParam = (*pFunParams)[0];
  CPPUNIT_ASSERT(pFunParam != NULL);
  CPPUNIT_ASSERT(pFunParam->getObjectName() == std::string("k"));
  const CEvaluationNode* pRoot = pKinFun->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(pRoot->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pRoot->subType() == CEvaluationNode::SubType::MULTIPLY);
  const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pRoot->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::NUMBER);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DOUBLE);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pChild);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 3.0) / 3.0) < 1e-6);
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DEFAULT);
  const CEvaluationNodeVariable* pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == std::string("k"));
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild == NULL);

  pFun = pFunDB->findFunction("function_2");
  CPPUNIT_ASSERT(pFun != NULL);
  pKinFun = dynamic_cast<const CKinFunction*>(pFun);
  CPPUNIT_ASSERT(pKinFun != NULL);
  // 2 parameters called A and B
  // expression is A + B
  pFunParams = &pKinFun->getVariables();
  CPPUNIT_ASSERT(pFunParams != NULL);
  CPPUNIT_ASSERT(pFunParams->size() == 2);
  pFunParam = (*pFunParams)[0];
  CPPUNIT_ASSERT(pFunParam != NULL);
  CPPUNIT_ASSERT(pFunParam->getObjectName() == std::string("A"));
  pFunParam = (*pFunParams)[1];
  CPPUNIT_ASSERT(pFunParam != NULL);
  CPPUNIT_ASSERT(pFunParam->getObjectName() == std::string("B"));
  pRoot = pKinFun->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(pRoot->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pRoot->subType() == CEvaluationNode::SubType::PLUS);
  pChild = dynamic_cast<const CEvaluationNode*>(pRoot->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DEFAULT);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == std::string("B"));
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DEFAULT);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == std::string("A"));
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild == NULL);

  pFun = pFunDB->findFunction("function_3");
  CPPUNIT_ASSERT(pFun != NULL);
  pKinFun = dynamic_cast<const CKinFunction*>(pFun);
  CPPUNIT_ASSERT(pKinFun != NULL);
  // 2 parameters called k and C
  // expression is C - (k * 1.3)
  pFunParams = &pKinFun->getVariables();
  CPPUNIT_ASSERT(pFunParams != NULL);
  CPPUNIT_ASSERT(pFunParams->size() == 2);
  pFunParam = (*pFunParams)[0];
  CPPUNIT_ASSERT(pFunParam != NULL);
  CPPUNIT_ASSERT(pFunParam->getObjectName() == std::string("k"));
  pFunParam = (*pFunParams)[1];
  CPPUNIT_ASSERT(pFunParam != NULL);
  CPPUNIT_ASSERT(pFunParam->getObjectName() == std::string("C"));
  pRoot = pKinFun->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(pRoot->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pRoot->subType() == CEvaluationNode::SubType::MINUS);
  pChild = dynamic_cast<const CEvaluationNode*>(pRoot->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DEFAULT);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == std::string("C"));
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::MULTIPLY);
  CPPUNIT_ASSERT(pChild->getSibling() == NULL);
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getChild());
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DEFAULT);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == std::string("k"));
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::NUMBER);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DOUBLE);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pChild);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 1.3) / 1.3) < 1e-6);
  CPPUNIT_ASSERT(pChild->getSibling() == NULL);

  pFun = pFunDB->findFunction("function_4");
  CPPUNIT_ASSERT(pFun != NULL);
  pKinFun = dynamic_cast<const CKinFunction*>(pFun);
  CPPUNIT_ASSERT(pKinFun != NULL);
  // 2 parameters called x and y
  // expression is function_2(x,y)/2.0
  pFunParams = &pKinFun->getVariables();
  CPPUNIT_ASSERT(pFunParams != NULL);
  CPPUNIT_ASSERT(pFunParams->size() == 2);
  pFunParam = (*pFunParams)[0];
  CPPUNIT_ASSERT(pFunParam != NULL);
  CPPUNIT_ASSERT(pFunParam->getObjectName() == std::string("x"));
  pFunParam = (*pFunParams)[1];
  CPPUNIT_ASSERT(pFunParam != NULL);
  CPPUNIT_ASSERT(pFunParam->getObjectName() == std::string("y"));
  pRoot = pKinFun->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(pRoot->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pRoot->subType() == CEvaluationNode::SubType::DIVIDE);
  pChild = dynamic_cast<const CEvaluationNode*>(pRoot->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::CALL);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::FUNCTION);
  const CEvaluationNodeCall* pCallNode = dynamic_cast<const CEvaluationNodeCall*>(pChild);
  CPPUNIT_ASSERT(pCallNode != NULL);
  CPPUNIT_ASSERT(pCallNode->getData() == std::string("function_2"));
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DEFAULT);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == std::string("x"));
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DEFAULT);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == std::string("y"));
  CPPUNIT_ASSERT(pChild->getSibling() == NULL);
  pChild = dynamic_cast<const CEvaluationNode*>(pRoot->getChild()->getSibling());
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::NUMBER);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DOUBLE);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pChild);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 2.0) / 2.0) < 1e-6);
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild == NULL);

  pFun = pFunDB->findFunction("function_5");
  CPPUNIT_ASSERT(pFun != NULL);
  pKinFun = dynamic_cast<const CKinFunction*>(pFun);
  CPPUNIT_ASSERT(pKinFun != NULL);
  // 3 parameters called a, b  and c
  // expression is function_3(c,a) + (function_1(b) - 5.23)
  pFunParams = &pKinFun->getVariables();
  CPPUNIT_ASSERT(pFunParams != NULL);
  CPPUNIT_ASSERT(pFunParams->size() == 3);
  pFunParam = (*pFunParams)[0];
  CPPUNIT_ASSERT(pFunParam != NULL);
  CPPUNIT_ASSERT(pFunParam->getObjectName() == std::string("a"));
  pFunParam = (*pFunParams)[1];
  CPPUNIT_ASSERT(pFunParam != NULL);
  CPPUNIT_ASSERT(pFunParam->getObjectName() == std::string("b"));
  pFunParam = (*pFunParams)[2];
  CPPUNIT_ASSERT(pFunParam != NULL);
  CPPUNIT_ASSERT(pFunParam->getObjectName() == std::string("c"));
  pRoot = pKinFun->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(pRoot->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pRoot->subType() == CEvaluationNode::SubType::PLUS);
  pChild = dynamic_cast<const CEvaluationNode*>(pRoot->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::CALL);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::FUNCTION);
  pCallNode = dynamic_cast<const CEvaluationNodeCall*>(pChild);
  CPPUNIT_ASSERT(pCallNode != NULL);
  CPPUNIT_ASSERT(pCallNode->getData() == std::string("function_3"));
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DEFAULT);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == std::string("c"));
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DEFAULT);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == std::string("a"));
  CPPUNIT_ASSERT(pChild->getSibling() == NULL);
  pChild = dynamic_cast<const CEvaluationNode*>(pRoot->getChild()->getSibling());
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::MINUS);
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::CALL);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::FUNCTION);
  pCallNode = dynamic_cast<const CEvaluationNodeCall*>(pChild);
  CPPUNIT_ASSERT(pCallNode != NULL);
  CPPUNIT_ASSERT(pCallNode->getData() == std::string("function_1"));
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DEFAULT);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == std::string("b"));
  CPPUNIT_ASSERT(pChild->getSibling() == NULL);
  pChild = dynamic_cast<const CEvaluationNode*>(pRoot->getChild()->getSibling()->getChild()->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::NUMBER);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DOUBLE);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pChild);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 5.23) / 5.23) < 1e-6);
  CPPUNIT_ASSERT(pChild->getSibling() == NULL);

  pFun = pFunDB->findFunction("function_6");
  CPPUNIT_ASSERT(pFun != NULL);
  pKinFun = dynamic_cast<const CKinFunction*>(pFun);
  CPPUNIT_ASSERT(pKinFun != NULL);
  // 3 parameters called k1, k2 and k3
  // expression is function_5(k1,k2,k3)
  pFunParams = &pKinFun->getVariables();
  CPPUNIT_ASSERT(pFunParams != NULL);
  CPPUNIT_ASSERT(pFunParams->size() == 3);
  pFunParam = (*pFunParams)[0];
  CPPUNIT_ASSERT(pFunParam != NULL);
  CPPUNIT_ASSERT(pFunParam->getObjectName() == std::string("k1"));
  pFunParam = (*pFunParams)[1];
  CPPUNIT_ASSERT(pFunParam != NULL);
  CPPUNIT_ASSERT(pFunParam->getObjectName() == std::string("k2"));
  pFunParam = (*pFunParams)[2];
  CPPUNIT_ASSERT(pFunParam != NULL);
  CPPUNIT_ASSERT(pFunParam->getObjectName() == std::string("k3"));
  pRoot = pKinFun->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(pRoot->mainType() == CEvaluationNode::MainType::CALL);
  CPPUNIT_ASSERT(pRoot->subType() == CEvaluationNode::SubType::FUNCTION);
  pCallNode = dynamic_cast<const CEvaluationNodeCall*>(pRoot);
  CPPUNIT_ASSERT(pCallNode != NULL);
  CPPUNIT_ASSERT(pCallNode->getData() == std::string("function_5"));
  pChild = dynamic_cast<const CEvaluationNode*>(pRoot->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DEFAULT);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == std::string("k1"));
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DEFAULT);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == std::string("k2"));
  pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DEFAULT);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pChild);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == std::string("k3"));
  CPPUNIT_ASSERT(pChild->getSibling() == NULL);

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
  pRoot = pTree->getRoot();
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
}

const char* test000078::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version4\" level=\"2\" version=\"4\">\n"
  "  <model id=\"Model_1\" name=\"New Model\">\n"
  "    <notes>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        <p>Model with function call in kinetics and rules.</p>\n"
  "        <p>This is to check import of unordered function definitions as allowed in L2V4</p>\n"
  "      </body>\n"
  "    </notes>\n"
  "    <listOfFunctionDefinitions>\n"
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
