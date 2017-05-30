// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "test000093.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CExpression.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CEvent.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Rule.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/math/ASTNode.h"

#include "copasi/core/CRootContainer.h"

CDataModel* test000093::pCOPASIDATAMODEL = NULL;

void test000093::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000093::tearDown()
{
  CRootContainer::destroy();
}

void test000093::test_bug1503_1()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000093::MODEL_STRING_1);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  std::string content = pDataModel->exportSBMLToString(NULL, 2, 3);
  CPPUNIT_ASSERT(content.empty() == false);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // assert that there is only one compartment and
  // assert the compartment is not constant
  CPPUNIT_ASSERT(pModel->getNumCompartments() == 1);
  Compartment* pCompartment = pModel->getCompartment(0);
  CPPUNIT_ASSERT(pCompartment->getConstant() == false);
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  Species* pSpecies = pModel->getSpecies(1);
  std::string idSpeciesS, idSpeciesA;

  if (pSpecies->getName() == "S")
    {
      idSpeciesS = pSpecies->getId();
    }
  else
    {
      idSpeciesA = pSpecies->getId();
    }

  CPPUNIT_ASSERT(pSpecies->getHasOnlySubstanceUnits() == true);
  pSpecies = pModel->getSpecies(0);

  if (pSpecies->getName() == "S")
    {
      idSpeciesS = pSpecies->getId();
    }
  else
    {
      idSpeciesA = pSpecies->getId();
    }

  CPPUNIT_ASSERT(!idSpeciesS.empty());
  CPPUNIT_ASSERT(!idSpeciesA.empty());
  CPPUNIT_ASSERT(pSpecies->getHasOnlySubstanceUnits() == true);
  CPPUNIT_ASSERT(pModel->getNumRules() == 2);
  CPPUNIT_ASSERT(pModel->getNumInitialAssignments() == 2);
  const InitialAssignment* pAssignment1 = pModel->getInitialAssignment(0);
  CPPUNIT_ASSERT(pAssignment1 != NULL);
  CPPUNIT_ASSERT(pModel->getNumParameters() == 1);
  Parameter* pParameter = pModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter != NULL);

  // the initial expression for the species needs to be multiplied
  // by the compartment volume
  // and the reference to the species in the initial expression for the model
  // value has to be divided by the compartment volume
  const InitialAssignment* pAssignment2 = NULL;

  if (pAssignment1->getSymbol() == pParameter->getId())
    {
      pAssignment2 = pModel->getInitialAssignment(1);
    }
  else
    {
      pAssignment2 = pAssignment1;
      pAssignment1 = pModel->getInitialAssignment(1);
    }

  assert(pAssignment2 != NULL);

  // check the reference in the initial assignment to the parameter
  const ASTNode* pMath = pAssignment1->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_DIVIDE);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  const ASTNode* pChild1 = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild1 != NULL);
  const ASTNode* pChild2 = NULL;

  // one child needs to be the number 2, the other needs to be a division operator
  if (pChild1->getType() == AST_DIVIDE)
    {
      pChild2 = pMath->getChild(1);
    }
  else
    {
      pChild2 = pChild1;
      pChild1 = pMath->getChild(1);
    }

  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_DIVIDE);
  CPPUNIT_ASSERT(pChild2->getType() == AST_REAL);
  CPPUNIT_ASSERT((fabs(pChild2->getReal() - 2.0) / 2.0) < 1e-9);
  CPPUNIT_ASSERT(pChild1->getNumChildren() == 2);
  pChild2 = pChild1->getChild(1);
  CPPUNIT_ASSERT(pChild2 != NULL);
  pChild1 = pChild1->getChild(0);
  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild2->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild1->getName() == idSpeciesS);
  CPPUNIT_ASSERT(pChild2->getName() == pCompartment->getId());
  // test the initial expression for the species.
  // This must be an addition multiplied by the volume
  pMath = pAssignment2->getMath();
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
  pChild1 = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild1 != NULL);

  if (pChild1->getType() == AST_PLUS)
    {
      pChild2 = pMath->getChild(1);
    }
  else
    {
      pChild2 = pChild1;
      pChild1 = pMath->getChild(1);
    }

  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_PLUS);
  CPPUNIT_ASSERT(pChild2->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild2->getName() == pCompartment->getId());
  CPPUNIT_ASSERT(pChild1->getNumChildren() == 2);
  pChild2 = pChild1->getChild(0);
  pChild1 = pChild1->getChild(1);
  CPPUNIT_ASSERT(pChild2->getType() == AST_REAL);

  if ((fabs(pChild2->getReal() - 12.0) / 12.0) < 1e-9)
    {
      CPPUNIT_ASSERT((fabs(pChild1->getReal() - 6.0) / 6.0) < 1e-9);
    }
  else
    {
      CPPUNIT_ASSERT((fabs(pChild2->getReal() - 6.0) / 6.0) < 1e-9);
      CPPUNIT_ASSERT((fabs(pChild1->getReal() - 12.0) / 12.0) < 1e-9);
    }

  // the reference to the species in the rule for species S needs to be divided by the volume
  const Rule* pRule1 = pModel->getRule(0);
  CPPUNIT_ASSERT(pRule1 != NULL);
  const AssignmentRule* pARule1 = dynamic_cast<const AssignmentRule*>(pRule1);
  CPPUNIT_ASSERT(pARule1 != NULL);
  const Rule* pRule2 = NULL;
  const AssignmentRule* pARule2 = NULL;

  if (pARule1->getVariable() == pCompartment->getId())
    {
      pRule2 = pModel->getRule(1);
      pARule2 = dynamic_cast<const AssignmentRule*>(pRule2);
    }
  else
    {
      pRule2 = pRule1;
      pARule2 = pARule1;
      pRule1 = pModel->getRule(1);
      pARule1 = dynamic_cast<const AssignmentRule*>(pRule1);
    }

  CPPUNIT_ASSERT(pRule1 != NULL);
  CPPUNIT_ASSERT(pARule1 != NULL);
  CPPUNIT_ASSERT(pRule2 != NULL);
  CPPUNIT_ASSERT(pARule2 != NULL);
  // the first rule is the rule for the compartment which is
  // an addition of two numbers
  pMath = pARule1->getMath();
  CPPUNIT_ASSERT(pMath != 0);
  CPPUNIT_ASSERT(pMath->getType() == AST_PLUS);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  pChild2 = pMath->getChild(0);
  pChild1 = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild2->getType() == AST_REAL);

  if ((fabs(pChild2->getReal() - 3.0) / 3.0) < 1e-9)
    {
      CPPUNIT_ASSERT((fabs(pChild1->getReal() - 4.0) / 4.0) < 1e-9);
    }
  else
    {
      CPPUNIT_ASSERT((fabs(pChild2->getReal() - 4.0) / 4.0) < 1e-9);
      CPPUNIT_ASSERT((fabs(pChild1->getReal() - 3.0) / 3.0) < 1e-9);
    }

  // the second rule id the one for species S
  // this expression contains a reference to species A which must be divided by the volume
  // and the complete expression must be multiplied by the volume
  pMath = pARule2->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  pChild1 = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild1 != NULL);

  if (pChild1->getType() == AST_NAME)
    {
      pChild2 = pMath->getChild(1);
    }
  else
    {
      pChild2 = pChild1;
      pChild1 = pMath->getChild(1);
    }

  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild1->getName() == pCompartment->getId());
  CPPUNIT_ASSERT(pChild2->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pChild2->getNumChildren() == 2);
  pChild1 = pChild2->getChild(0);

  if (pChild1->getType() == AST_REAL)
    {
      pChild2 = pChild2->getChild(1);
    }
  else
    {

      pMath = pChild2;
      pChild2 = pChild1;
      pChild1 = pMath->getChild(1);
    }

  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_REAL);
  CPPUNIT_ASSERT((fabs(pChild1->getReal() - 3.0) / 3.0) < 1e-9);
  CPPUNIT_ASSERT(pChild2->getType() == AST_DIVIDE);
  CPPUNIT_ASSERT(pChild2->getNumChildren() == 2);
  pChild1 = pChild2->getChild(0);
  pChild2 = pChild2->getChild(1);
  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild1->getName() == idSpeciesA);
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild2->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild2->getName() == pCompartment->getId());

  // now we reimport the model and check if the divisions and mutliplications by the compartment have been reverted
  pDataModel->newModel(NULL, true);
  CPPUNIT_ASSERT(pDataModel->getModel()->getCompartments().size() == 0);
  bool result = pDataModel->importSBMLFromString(content);
  CPPUNIT_ASSERT(result == true);
  const CModel* pCModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pCModel->getCompartments().size() == 1);
  // there is one factor for the conversion from particles to amount
  CPPUNIT_ASSERT(pCModel->getModelValues().size() == 2);
  CPPUNIT_ASSERT(pCModel->getMetabolites().size() == 2);
  CPPUNIT_ASSERT(pCModel->getReactions().size() == 0);
  CPPUNIT_ASSERT(pCModel->getEvents().size() == 0);
  const CCompartment* pCCompartment = pCModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCCompartment != NULL);
  CPPUNIT_ASSERT(pCCompartment->getStatus() == CModelEntity::Status::ASSIGNMENT);
  const CExpression* pExpr = pCCompartment->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pEvalNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OPERATOR);
  const CEvaluationNodeOperator* pOperator = dynamic_cast<const CEvaluationNodeOperator*>(pEvalNode);
  CPPUNIT_ASSERT(pOperator->subType() == CEvaluationNode::SubType::PLUS);
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(pOperator->getChild() != NULL);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::NUMBER);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pEvalNode);

  if (fabs((pNumberNode->getValue() - 3.0) / 3.0) < 1e-6)
    {
      CPPUNIT_ASSERT(pNumberNode->getSibling() != NULL);
      pEvalNode = dynamic_cast<const CEvaluationNode*>(pNumberNode->getSibling());
      CPPUNIT_ASSERT(pEvalNode != NULL);
      CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::NUMBER);
      pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pEvalNode);
      CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 4.0) / 4.0) < 1e-6);
      CPPUNIT_ASSERT(pNumberNode->getSibling() == NULL);
    }
  else
    {
      CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 4.0) / 4.0) < 1e-6);
      CPPUNIT_ASSERT(pNumberNode->getSibling() != NULL);
      pEvalNode = dynamic_cast<const CEvaluationNode*>(pNumberNode->getSibling());
      CPPUNIT_ASSERT(pEvalNode != NULL);
      CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::NUMBER);
      pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pEvalNode);
      CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 3.0) / 3.0) < 1e-6);
      CPPUNIT_ASSERT(pNumberNode->getSibling() == NULL);
    }

  const CMetab* pMetabA = pCModel->getMetabolites()[0];

  CPPUNIT_ASSERT(pMetabA != NULL);

  const CMetab* pMetabS = NULL;

  if (pMetabA->getObjectName() == "A")
    {
      pMetabS = pCModel->getMetabolites()[1];
    }
  else
    {
      pMetabS = pMetabA;
      pMetabA = pCModel->getMetabolites()[1];
      CPPUNIT_ASSERT(pMetabA != NULL);
    }

  CPPUNIT_ASSERT(pMetabS != NULL);
  CPPUNIT_ASSERT(pMetabA->getObjectName() == "A");
  CPPUNIT_ASSERT(pMetabS->getObjectName() == "S");

  // next we test the initial expression for the model value
  const CModelValue* pModelValue = NULL;
  unsigned int iMax = pCModel->getModelValues().size();

  for (unsigned int i = 0; i < iMax; ++i)
    {
      if (pCModel->getModelValues()[i]->getObjectName() == "K")
        {
          pModelValue = pCModel->getModelValues()[i];
          break;
        }
    }

  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::Status::FIXED);
  pExpr = pModelValue->getInitialExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pEvalNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OPERATOR);
  pOperator = dynamic_cast<const CEvaluationNodeOperator*>(pEvalNode);
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(pOperator->subType() == CEvaluationNode::SubType::DIVIDE);
  CPPUNIT_ASSERT(pOperator->getChild() != NULL);
  CPPUNIT_ASSERT(pOperator->getChild()->getSibling() != NULL);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild()->getSibling());
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::NUMBER);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pEvalNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 2.0) / 2.0) < 1e-6);
  CPPUNIT_ASSERT(pNumberNode->getSibling() == NULL);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OPERATOR);
  pOperator = dynamic_cast<const CEvaluationNodeOperator*>(pEvalNode);
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(pOperator->subType() == CEvaluationNode::SubType::DIVIDE);
  CPPUNIT_ASSERT(pOperator->getChild() != NULL);
  CPPUNIT_ASSERT(pOperator->getChild()->getSibling() != NULL);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild()->getSibling());
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pEvalNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CPPUNIT_ASSERT(pObjectNode->getSibling() == NULL);
  CPPUNIT_ASSERT((pObjectNode->subType()) == CEvaluationNode::SubType::CN);
  // check the data of the object node
  std::string objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  CObjectInterface::ContainerList listOfContainers;
  listOfContainers.push_back(const_cast<CModel*>(pCModel));
  const CDataObject* pObject = pDataModel->getObjectFromCN(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("InitialVolume"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pCCompartment);

  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OPERATOR);
  pOperator = dynamic_cast<const CEvaluationNodeOperator*>(pEvalNode);
  CPPUNIT_ASSERT(pOperator->subType() == CEvaluationNode::SubType::DIVIDE);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pEvalNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CPPUNIT_ASSERT((pObjectNode->subType()) == CEvaluationNode::SubType::CN);
  // check the data of the object node
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = pDataModel->getObjectFromCN(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("InitialParticleNumber"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pMetabS);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pObjectNode->getSibling());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pEvalNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CPPUNIT_ASSERT((pObjectNode->subType()) == CEvaluationNode::SubType::CN);
  // check the data of the object node
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = pDataModel->getObjectFromCN(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("InitialValue"));

  //
  // then we test the expression and the initial expression for the two metabolites
  CPPUNIT_ASSERT(pMetabA->getStatus() == CModelEntity::Status::REACTIONS);
  pExpr = pMetabA->getInitialExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pEvalNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OPERATOR);
  pOperator = dynamic_cast<const CEvaluationNodeOperator*>(pEvalNode);
  CPPUNIT_ASSERT(pOperator->subType() == CEvaluationNode::SubType::PLUS);
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(pOperator->getChild() != NULL);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::NUMBER);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pEvalNode);

  if (fabs((pNumberNode->getValue() - 12.0) / 12.0) < 1e-6)
    {
      CPPUNIT_ASSERT(pNumberNode->getSibling() != NULL);
      pEvalNode = dynamic_cast<const CEvaluationNode*>(pNumberNode->getSibling());
      CPPUNIT_ASSERT(pEvalNode != NULL);
      CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::NUMBER);
      pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pEvalNode);
      CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 6.0) / 6.0) < 1e-6);
      CPPUNIT_ASSERT(pNumberNode->getSibling() == NULL);
    }
  else
    {
      CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 6.0) / 6.0) < 1e-6);
      CPPUNIT_ASSERT(pNumberNode->getSibling() != NULL);
      pEvalNode = dynamic_cast<const CEvaluationNode*>(pNumberNode->getSibling());
      CPPUNIT_ASSERT(pEvalNode != NULL);
      CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::NUMBER);
      pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pEvalNode);
      CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 12.0) / 12.0) < 1e-6);
      CPPUNIT_ASSERT(pNumberNode->getSibling() == NULL);
    }

  CPPUNIT_ASSERT(pMetabS->getStatus() == CModelEntity::Status::ASSIGNMENT);
  pExpr = pMetabS->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pEvalNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OPERATOR);
  pOperator = dynamic_cast<const CEvaluationNodeOperator*>(pEvalNode);
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(pOperator->subType() == CEvaluationNode::SubType::MULTIPLY);
  CPPUNIT_ASSERT(pOperator->getChild() != NULL);
  CPPUNIT_ASSERT(pOperator->getChild()->getSibling() != NULL);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild()->getSibling());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::NUMBER);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pEvalNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 3.0) / 3.0) < 1e-6);
  CPPUNIT_ASSERT(pNumberNode->getSibling() == NULL);

  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OPERATOR);
  pOperator = dynamic_cast<const CEvaluationNodeOperator*>(pEvalNode);
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(pOperator->subType() == CEvaluationNode::SubType::DIVIDE);
  CPPUNIT_ASSERT(pOperator->getChild() != NULL);
  CPPUNIT_ASSERT(pOperator->getChild()->getSibling() != NULL);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild()->getSibling());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pEvalNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CPPUNIT_ASSERT((pObjectNode->subType()) == CEvaluationNode::SubType::CN);
  // check the data of the object node
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = pDataModel->getObjectFromCN(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Volume"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pCCompartment);
  CPPUNIT_ASSERT(pObjectNode->getSibling() == NULL);

  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OPERATOR);
  pOperator = dynamic_cast<const CEvaluationNodeOperator*>(pEvalNode);
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(pOperator->subType() == CEvaluationNode::SubType::DIVIDE);
  CPPUNIT_ASSERT(pOperator->getChild() != NULL);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pEvalNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CPPUNIT_ASSERT((pObjectNode->subType()) == CEvaluationNode::SubType::CN);
  // check the data of the object node
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = pDataModel->getObjectFromCN(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("ParticleNumber"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pMetabA);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pObjectNode->getSibling());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pEvalNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CPPUNIT_ASSERT((pObjectNode->subType()) == CEvaluationNode::SubType::CN);
  // check the data of the object node
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = pDataModel->getObjectFromCN(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObjectNode->getSibling() == NULL);
}

void test000093::test_bug1503_2()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000093::MODEL_STRING_2);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  std::string content = pDataModel->exportSBMLToString(NULL, 2, 3);
  CPPUNIT_ASSERT(content.empty() == false);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // assert that there is only one compartment and
  // assert the compartment is not constant
  CPPUNIT_ASSERT(pModel->getNumCompartments() == 1);
  Compartment* pCompartment = pModel->getCompartment(0);
  CPPUNIT_ASSERT(pCompartment->getConstant() == false);
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  Species* pSpecies = pModel->getSpecies(1);
  std::string idSpeciesS, idSpeciesA;

  if (pSpecies->getName() == "S")
    {
      idSpeciesS = pSpecies->getId();
    }
  else
    {
      idSpeciesA = pSpecies->getId();
    }

  CPPUNIT_ASSERT(pSpecies->getHasOnlySubstanceUnits() == true);
  pSpecies = pModel->getSpecies(0);

  if (pSpecies->getName() == "S")
    {
      idSpeciesS = pSpecies->getId();
    }
  else
    {
      idSpeciesA = pSpecies->getId();
    }

  CPPUNIT_ASSERT(!idSpeciesS.empty());
  CPPUNIT_ASSERT(!idSpeciesA.empty());
  CPPUNIT_ASSERT(pSpecies->getHasOnlySubstanceUnits() == true);
  CPPUNIT_ASSERT(pModel->getNumRules() == 1);
  CPPUNIT_ASSERT(pModel->getNumInitialAssignments() == 2);
  const InitialAssignment* pAssignment1 = pModel->getInitialAssignment(0);
  CPPUNIT_ASSERT(pAssignment1 != NULL);
  CPPUNIT_ASSERT(pModel->getNumParameters() == 1);
  CPPUNIT_ASSERT(pModel->getNumEvents() == 1);
  Parameter* pParameter = pModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter != NULL);

  // the initial expression for the species needs to be multiplied
  // by the compartment volume
  // and the reference to the species in the initial expression for the model
  // value has to be divided by the compartment volume
  const InitialAssignment* pAssignment2 = NULL;

  if (pAssignment1->getSymbol() == pParameter->getId())
    {
      pAssignment2 = pModel->getInitialAssignment(1);
    }
  else
    {
      pAssignment2 = pAssignment1;
      pAssignment1 = pModel->getInitialAssignment(1);
    }

  assert(pAssignment2 != NULL);

  // check the reference in the initial assignment to the parameter
  const ASTNode* pMath = pAssignment1->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_DIVIDE);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  const ASTNode* pChild1 = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild1 != NULL);
  const ASTNode* pChild2 = NULL;

  // one child needs to be the number 2, the other needs to be a division operator
  if (pChild1->getType() == AST_DIVIDE)
    {
      pChild2 = pMath->getChild(1);
    }
  else
    {
      pChild2 = pChild1;
      pChild1 = pMath->getChild(1);
    }

  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_DIVIDE);
  CPPUNIT_ASSERT(pChild2->getType() == AST_REAL);
  CPPUNIT_ASSERT((fabs(pChild2->getReal() - 2.0) / 2.0) < 1e-9);
  CPPUNIT_ASSERT(pChild1->getNumChildren() == 2);
  pChild2 = pChild1->getChild(1);
  CPPUNIT_ASSERT(pChild2 != NULL);
  pChild1 = pChild1->getChild(0);
  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild2->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild1->getName() == idSpeciesS);
  CPPUNIT_ASSERT(pChild2->getName() == pCompartment->getId());
  // test the initial expression for the species.
  // This must be an addition multiplied by the volume
  pMath = pAssignment2->getMath();
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
  pChild1 = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild1 != NULL);

  if (pChild1->getType() == AST_PLUS)
    {
      pChild2 = pMath->getChild(1);
    }
  else
    {
      pChild2 = pChild1;
      pChild1 = pMath->getChild(1);
    }

  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_PLUS);
  CPPUNIT_ASSERT(pChild2->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild2->getName() == pCompartment->getId());
  CPPUNIT_ASSERT(pChild1->getNumChildren() == 2);
  pChild2 = pChild1->getChild(0);
  pChild1 = pChild1->getChild(1);
  CPPUNIT_ASSERT(pChild2->getType() == AST_REAL);

  if ((fabs(pChild2->getReal() - 12.0) / 12.0) < 1e-9)
    {
      CPPUNIT_ASSERT((fabs(pChild1->getReal() - 6.0) / 6.0) < 1e-9);
    }
  else
    {
      CPPUNIT_ASSERT((fabs(pChild2->getReal() - 6.0) / 6.0) < 1e-9);
      CPPUNIT_ASSERT((fabs(pChild1->getReal() - 12.0) / 12.0) < 1e-9);
    }

  // the reference to the species in the rule for species S needs to be divided by the volume
  const Rule* pRule1 = pModel->getRule(0);
  CPPUNIT_ASSERT(pRule1 != NULL);
  const AssignmentRule* pARule1 = dynamic_cast<const AssignmentRule*>(pRule1);
  CPPUNIT_ASSERT(pARule1 != NULL);

  // the second rule id the one for species S
  // this expression contains a reference to species A which must be divided by the volume
  // and the complete expression must be multiplied by the volume
  pMath = pARule1->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  pChild1 = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild1 != NULL);

  if (pChild1->getType() == AST_NAME)
    {
      pChild2 = pMath->getChild(1);
    }
  else
    {
      pChild2 = pChild1;
      pChild1 = pMath->getChild(1);
    }

  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild1->getName() == pCompartment->getId());
  CPPUNIT_ASSERT(pChild2->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pChild2->getNumChildren() == 2);
  pChild1 = pChild2->getChild(0);

  if (pChild1->getType() == AST_REAL)
    {
      pChild2 = pChild2->getChild(1);
    }
  else
    {

      pMath = pChild2;
      pChild2 = pChild1;
      pChild1 = pMath->getChild(1);
    }

  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_REAL);
  CPPUNIT_ASSERT((fabs(pChild1->getReal() - 3.0) / 3.0) < 1e-9);
  CPPUNIT_ASSERT(pChild2->getType() == AST_DIVIDE);
  CPPUNIT_ASSERT(pChild2->getNumChildren() == 2);
  pChild1 = pChild2->getChild(0);
  pChild2 = pChild2->getChild(1);
  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild1->getName() == idSpeciesA);
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild2->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild2->getName() == pCompartment->getId());

  // now we reimport the model and check if the divisions and mutliplications by the compartment have been reverted
  pDataModel->newModel(NULL, true);
  CPPUNIT_ASSERT(pDataModel->getModel()->getCompartments().size() == 0);
  bool result = pDataModel->importSBMLFromString(content);
  CPPUNIT_ASSERT(result == true);
  const CModel* pCModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pCModel->getCompartments().size() == 1);
  // there is one factor for the conversion from particles to amount
  CPPUNIT_ASSERT(pCModel->getModelValues().size() == 2);
  CPPUNIT_ASSERT(pCModel->getMetabolites().size() == 2);
  CPPUNIT_ASSERT(pCModel->getReactions().size() == 0);
  CPPUNIT_ASSERT(pCModel->getEvents().size() == 1);
  const CCompartment* pCCompartment = pCModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCCompartment != NULL);
  CPPUNIT_ASSERT(pCCompartment->getStatus() == CModelEntity::Status::FIXED);
  const CMetab* pMetabA = pCModel->getMetabolites()[0];

  CPPUNIT_ASSERT(pMetabA != NULL);

  const CMetab* pMetabS = NULL;

  if (pMetabA->getObjectName() == "A")
    {
      pMetabS = pCModel->getMetabolites()[1];
    }
  else
    {
      pMetabS = pMetabA;
      pMetabA = pCModel->getMetabolites()[1];
      CPPUNIT_ASSERT(pMetabA != NULL);
    }

  CPPUNIT_ASSERT(pMetabS != NULL);
  CPPUNIT_ASSERT(pMetabA->getObjectName() == "A");
  CPPUNIT_ASSERT(pMetabS->getObjectName() == "S");

  // next we test the initial expression for the model value
  const CModelValue* pModelValue = NULL;
  unsigned int iMax = pCModel->getModelValues().size();

  for (unsigned int i = 0; i < iMax; ++i)
    {
      if (pCModel->getModelValues()[i]->getObjectName() == "K")
        {
          pModelValue = pCModel->getModelValues()[i];
          break;
        }
    }

  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::Status::FIXED);
  const CExpression* pExpr = pModelValue->getInitialExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pEvalNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OPERATOR);
  const CEvaluationNodeOperator* pOperator = dynamic_cast<const CEvaluationNodeOperator*>(pEvalNode);
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(pOperator->subType() == CEvaluationNode::SubType::DIVIDE);
  CPPUNIT_ASSERT(pOperator->getChild() != NULL);
  CPPUNIT_ASSERT(pOperator->getChild()->getSibling() != NULL);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild()->getSibling());
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::NUMBER);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pEvalNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 2.0) / 2.0) < 1e-6);
  CPPUNIT_ASSERT(pNumberNode->getSibling() == NULL);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OPERATOR);
  pOperator = dynamic_cast<const CEvaluationNodeOperator*>(pEvalNode);
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(pOperator->subType() == CEvaluationNode::SubType::DIVIDE);
  CPPUNIT_ASSERT(pOperator->getChild() != NULL);
  CPPUNIT_ASSERT(pOperator->getChild()->getSibling() != NULL);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild()->getSibling());
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pEvalNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CPPUNIT_ASSERT(pObjectNode->getSibling() == NULL);
  CPPUNIT_ASSERT((pObjectNode->subType()) == CEvaluationNode::SubType::CN);
  // check the data of the object node
  std::string objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  CObjectInterface::ContainerList listOfContainers;
  listOfContainers.push_back(const_cast<CModel*>(pCModel));
  const CDataObject* pObject = pDataModel->getObjectFromCN(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("InitialVolume"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pCCompartment);

  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OPERATOR);
  pOperator = dynamic_cast<const CEvaluationNodeOperator*>(pEvalNode);
  CPPUNIT_ASSERT(pOperator->subType() == CEvaluationNode::SubType::DIVIDE);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pEvalNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CPPUNIT_ASSERT((pObjectNode->subType()) == CEvaluationNode::SubType::CN);
  // check the data of the object node
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = pDataModel->getObjectFromCN(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("InitialParticleNumber"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pMetabS);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pObjectNode->getSibling());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pEvalNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CPPUNIT_ASSERT((pObjectNode->subType()) == CEvaluationNode::SubType::CN);
  // check the data of the object node
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = pDataModel->getObjectFromCN(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("InitialValue"));

  //
  // then we test the expression and the initial expression for the two metabolites
  CPPUNIT_ASSERT(pMetabA->getStatus() == CModelEntity::Status::REACTIONS);
  pExpr = pMetabA->getInitialExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pEvalNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OPERATOR);
  pOperator = dynamic_cast<const CEvaluationNodeOperator*>(pEvalNode);
  CPPUNIT_ASSERT(pOperator->subType() == CEvaluationNode::SubType::PLUS);
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(pOperator->getChild() != NULL);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::NUMBER);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pEvalNode);

  if (fabs((pNumberNode->getValue() - 12.0) / 12.0) < 1e-6)
    {
      CPPUNIT_ASSERT(pNumberNode->getSibling() != NULL);
      pEvalNode = dynamic_cast<const CEvaluationNode*>(pNumberNode->getSibling());
      CPPUNIT_ASSERT(pEvalNode != NULL);
      CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::NUMBER);
      pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pEvalNode);
      CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 6.0) / 6.0) < 1e-6);
      CPPUNIT_ASSERT(pNumberNode->getSibling() == NULL);
    }
  else
    {
      CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 6.0) / 6.0) < 1e-6);
      CPPUNIT_ASSERT(pNumberNode->getSibling() != NULL);
      pEvalNode = dynamic_cast<const CEvaluationNode*>(pNumberNode->getSibling());
      CPPUNIT_ASSERT(pEvalNode != NULL);
      CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::NUMBER);
      pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pEvalNode);
      CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 12.0) / 12.0) < 1e-6);
      CPPUNIT_ASSERT(pNumberNode->getSibling() == NULL);
    }

  CPPUNIT_ASSERT(pMetabS->getStatus() == CModelEntity::Status::ASSIGNMENT);
  pExpr = pMetabS->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pEvalNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OPERATOR);
  pOperator = dynamic_cast<const CEvaluationNodeOperator*>(pEvalNode);
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(pOperator->subType() == CEvaluationNode::SubType::MULTIPLY);
  CPPUNIT_ASSERT(pOperator->getChild() != NULL);
  CPPUNIT_ASSERT(pOperator->getChild()->getSibling() != NULL);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild()->getSibling());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::NUMBER);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pEvalNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 3.0) / 3.0) < 1e-6);
  CPPUNIT_ASSERT(pNumberNode->getSibling() == NULL);

  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OPERATOR);
  pOperator = dynamic_cast<const CEvaluationNodeOperator*>(pEvalNode);
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(pOperator->subType() == CEvaluationNode::SubType::DIVIDE);
  CPPUNIT_ASSERT(pOperator->getChild() != NULL);
  CPPUNIT_ASSERT(pOperator->getChild()->getSibling() != NULL);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild()->getSibling());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pEvalNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CPPUNIT_ASSERT((pObjectNode->subType()) == CEvaluationNode::SubType::CN);
  // check the data of the object node
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = pDataModel->getObjectFromCN(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Volume"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pCCompartment);
  CPPUNIT_ASSERT(pObjectNode->getSibling() == NULL);

  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OPERATOR);
  pOperator = dynamic_cast<const CEvaluationNodeOperator*>(pEvalNode);
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(pOperator->subType() == CEvaluationNode::SubType::DIVIDE);
  CPPUNIT_ASSERT(pOperator->getChild() != NULL);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pOperator->getChild());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pEvalNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CPPUNIT_ASSERT((pObjectNode->subType()) == CEvaluationNode::SubType::CN);
  // check the data of the object node
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = pDataModel->getObjectFromCN(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("ParticleNumber"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pMetabA);
  pEvalNode = dynamic_cast<const CEvaluationNode*>(pObjectNode->getSibling());
  CPPUNIT_ASSERT(pEvalNode != NULL);
  CPPUNIT_ASSERT(pEvalNode->mainType() == CEvaluationNode::MainType::OBJECT);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pEvalNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CPPUNIT_ASSERT((pObjectNode->subType()) == CEvaluationNode::SubType::CN);
  // check the data of the object node
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = pDataModel->getObjectFromCN(listOfContainers, objectCN);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObjectNode->getSibling() == NULL);
}

const char* test000093::MODEL_STRING_1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.6.34 (Debug) (http://www.copasi.org) at 2010-11-02 12:24:37 UTC -->\n"
  "<?oxygen RNGSchema=\"http://www.copasi.org/static/schema/CopasiML.rng\" type=\"xml\"?>\n"
  "<COPASI xmlns=\"http://www.copasi.org/static/schema\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"34\">\n"
  "  <Model key=\"Model_1\" name=\"New Model\" simulationType=\"time\" timeUnit=\"s\" volumeUnit=\"ml\" areaUnit=\"m²\" lengthUnit=\"m\" quantityUnit=\"µmol\" type=\"deterministic\" avogadroConstant=\"6.02214e+23\">\n"
  "    <MiriamAnnotation>\n"
  "<rdf:RDF\n"
  "   xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
  "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
  "  <rdf:Description rdf:about=\"#Model_1\">\n"
  "    <dcterms:created>\n"
  "      <rdf:Description>\n"
  "        <dcterms:W3CDTF>2010-11-02T13:22:15Z</dcterms:W3CDTF>\n"
  "      </rdf:Description>\n"
  "    </dcterms:created>\n"
  "  </rdf:Description>\n"
  "</rdf:RDF>\n"
  "\n"
  "    </MiriamAnnotation>\n"
  "    <Comment>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:13pt;font-family:Lucida Grande\">\n"
  "<p>Model with variable volume compartment, micromol quantity units and a reference to the species initial amount.</p>\n"
  "<p>On export this should create an SBML file with the hasOnlySubstanceUnits flag on the species set.</p>\n"
  "<p>Assignments and initial assignment expressions to species should be multiplied by the compartment volume on export and references to species in expressions should be divided by the volume.</p>\n"
  "<p>On reimport these modifications should be reversed.</p>\n"
  "</body></html>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"assignment\" dimensionality=\"3\">\n"
  "        <Expression>\n"
  "          3+4\n"
  "        </Expression>\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "        <InitialExpression>\n"
  "          12+6\n"
  "        </InitialExpression>\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"S\" simulationType=\"assignment\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=Concentration&gt;*3\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"K\" simulationType=\"fixed\">\n"
  "        <InitialExpression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Compartments[compartment],Vector=Metabolites[S],Reference=InitialConcentration&gt;/2.0\n"
  "        </InitialExpression>\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 4.215499050000001e+17 7 0 0 \n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI> \n"
  ;

const char* test000093::MODEL_STRING_2 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.6.34 (Debug) (http://www.copasi.org) at 2010-11-02 12:29:26 UTC -->\n"
  "<?oxygen RNGSchema=\"http://www.copasi.org/static/schema/CopasiML.rng\" type=\"xml\"?>\n"
  "<COPASI xmlns=\"http://www.copasi.org/static/schema\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"34\">\n"
  "  <Model key=\"Model_1\" name=\"New Model\" simulationType=\"time\" timeUnit=\"s\" volumeUnit=\"ml\" areaUnit=\"m²\" lengthUnit=\"m\" quantityUnit=\"µmol\" type=\"deterministic\" avogadroConstant=\"6.02214e+23\">\n"
  "    <Comment>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:13pt;font-family:Lucida Grande\">\n"
  "<p>Model with variable volume compartment, micromol quantity units and a reference to the species initial amount.</p>\n"
  "<p>This time the volume is variable because there is an event assignment to it.</p>\n"
  "<p>On export this should create an SBML file with the hasOnlySubstanceUnits flag on the species set.</p>\n"
  "<p>Assignments and initial assignment expressions to species should be multiplied by the compartment volume on export and references to species in expressions should be divided by the volume.</p>\n"
  "<p>On reimport these modifications should be reversed.</p>\n"
  "</body></html>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"fixed\" dimensionality=\"3\">\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "        <InitialExpression>\n"
  "          12+6\n"
  "        </InitialExpression>\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"S\" simulationType=\"assignment\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=Concentration&gt;*3\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"K\" simulationType=\"fixed\">\n"
  "        <InitialExpression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Compartments[compartment],Vector=Metabolites[S],Reference=InitialConcentration&gt;/2.0\n"
  "        </InitialExpression>\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <ListOfEvents>\n"
  "      <Event key=\"Event_0\" name=\"event_1\" order=\"1\">\n"
  "        <TriggerExpression>\n"
  "          &lt;CN=Root,Model=New Model,Reference=Time&gt; gt 3.0\n"
  "        </TriggerExpression>\n"
  "        <ListOfAssignments>\n"
  "          <Assignment targetKey=\"Metabolite_0\">\n"
  "            <Expression>\n"
  "              3.0\n"
  "            </Expression>\n"
  "          </Assignment>\n"
  "          <Assignment targetKey=\"Compartment_0\">\n"
  "            <Expression>\n"
  "              4.0\n"
  "            </Expression>\n"
  "          </Assignment>\n"
  "        </ListOfAssignments>\n"
  "      </Event>\n"
  "    </ListOfEvents>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 4.215499050000001e+17 7.5878986554e+19 0 7 \n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n"
  ;
