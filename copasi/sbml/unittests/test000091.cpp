// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "test000091.h"

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

#include <sbml/SBMLDocument.h>
#include <sbml/Model.h>
#include <sbml/Compartment.h>
#include <sbml/Species.h>
#include <sbml/Parameter.h>
#include <sbml/Reaction.h>
#include <sbml/math/ASTNode.h>

#include "copasi/core/CRootContainer.h"

CDataModel* test000091::pCOPASIDATAMODEL = NULL;

void test000091::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000091::tearDown()
{
  CRootContainer::destroy();
}

void test000091::test_delay_in_kinetic_law()
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
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::Status::REACTIONS);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::Status::REACTIONS);
  // there should now be three model values because we created two dummy model
  // values that represent the two different delay expression
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 3);
  const CModelValue* pK1 = NULL;
  const CModelValue* pDummy1 = NULL;
  const CModelValue* pDummy2 = NULL;
  unsigned int i;

  for (i = 0; i < 3; ++i)
    {
      if (pModel->getModelValues()[i]->getObjectName() == "K1")
        {
          pK1 = pModel->getModelValues()[i];
        }
      else
        {
          if (pDummy1 == NULL)
            {
              pDummy1 = pModel->getModelValues()[i];
            }
          else
            {
              pDummy2 = pModel->getModelValues()[i];
            }
        }
    }

  CPPUNIT_ASSERT(pK1 != NULL);
  CPPUNIT_ASSERT(pK1->getStatus() == CModelEntity::Status::FIXED);
  CPPUNIT_ASSERT(fabs((pK1->getInitialValue() - 4.0) / 4.0) < 1e-9);
  CPPUNIT_ASSERT(pDummy1 != NULL);
  CPPUNIT_ASSERT(pDummy1->getStatus() == CModelEntity::Status::ASSIGNMENT);
  const CExpression* pExpr = pDummy1->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::DELAY);
  CPPUNIT_ASSERT((pNode->subType()) == CEvaluationNode::SubType::DELAY);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  CPPUNIT_ASSERT((pNode->subType()) == CEvaluationNode::SubType::CN);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCommonName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  CObjectInterface::ContainerList listOfContainers;
  listOfContainers.push_back(pModel);
  const CDataObject* pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pK1);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pObjectNode->getSibling());
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT((pNumberNode->subType()) == CEvaluationNode::SubType::DOUBLE);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 0.5) / 0.5) < 1e-3);
  CPPUNIT_ASSERT(pNumberNode->getSibling() == NULL);

  CPPUNIT_ASSERT(pDummy2 != NULL);
  CPPUNIT_ASSERT(pDummy2->getStatus() == CModelEntity::Status::ASSIGNMENT);
  pExpr = pDummy2->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::DELAY);
  CPPUNIT_ASSERT((pNode->subType()) == CEvaluationNode::SubType::DELAY);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  CPPUNIT_ASSERT((pNode->subType()) == CEvaluationNode::SubType::CN);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pK1);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pObjectNode->getSibling());
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT((pNumberNode->subType()) == CEvaluationNode::SubType::DOUBLE);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 0.2) / 0.2) < 1e-3);
  CPPUNIT_ASSERT(pNumberNode->getSibling() == NULL);

  CPPUNIT_ASSERT(pModel->getReactions().size() == 1);
  const CReaction* pReaction = pModel->getReactions()[0];
  CPPUNIT_ASSERT(pReaction != NULL);

  CPPUNIT_ASSERT(pReaction->isReversible() == false);
  // check the kinetic law
  const CFunction* pKineticFunction = pReaction->getFunction();
  CPPUNIT_ASSERT(pKineticFunction != NULL);

  const CChemEq* pChemEq = &pReaction->getChemEq();
  CPPUNIT_ASSERT(pChemEq != NULL);
  CPPUNIT_ASSERT(pChemEq->getCompartmentNumber() == 1);
  CPPUNIT_ASSERT(pChemEq->getSubstrates().size() == 1);
  const CChemEqElement* pElement = pChemEq->getSubstrates()[0];
  CPPUNIT_ASSERT(pElement != NULL);
  CPPUNIT_ASSERT(fabs(pElement->getMultiplicity() - 1.0) < 1e-3);
  CPPUNIT_ASSERT(pElement->getMetabolite() == pA);
  CPPUNIT_ASSERT(pChemEq->getProducts().size() == 1);
  pElement = pChemEq->getProducts()[0];
  CPPUNIT_ASSERT(pElement != NULL);
  CPPUNIT_ASSERT(fabs(pElement->getMultiplicity() - 1.0) < 1e-3);
  CPPUNIT_ASSERT(pElement->getMetabolite() == pB);
  CPPUNIT_ASSERT(pChemEq->getModifiers().size() == 0);

  const std::vector<std::vector<std::string> > parameterMappings = pReaction->getParameterMappings();
  CPPUNIT_ASSERT(parameterMappings.size() == 3);
  CPPUNIT_ASSERT(parameterMappings[0].size() == 1);
  CPPUNIT_ASSERT(parameterMappings[0][0] == pDummy1->getKey());
  CPPUNIT_ASSERT(parameterMappings[1].size() == 1);
  CPPUNIT_ASSERT(parameterMappings[1][0] == pDummy2->getKey());
  CPPUNIT_ASSERT(parameterMappings[2].size() == 1);
  CPPUNIT_ASSERT(parameterMappings[2][0] == pA->getKey());

  const CFunctionParameters& funPars = pKineticFunction->getVariables();
  CPPUNIT_ASSERT(funPars.size() == 3);
  // check the expression of the kinetic law
  // dummy1 * dummy2 * dummy1 * species1
  pNode = pKineticFunction->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  const CEvaluationNodeOperator* pOpNode = dynamic_cast<const CEvaluationNodeOperator*>(pNode);
  CPPUNIT_ASSERT(pOpNode != NULL);
  CPPUNIT_ASSERT((pOpNode->subType()) == CEvaluationNode::SubType::MULTIPLY);
  const CEvaluationNode* pNode2 = dynamic_cast<const CEvaluationNode*>(pOpNode->getChild()->getSibling());
  CPPUNIT_ASSERT(pNode2 != NULL);
  const CEvaluationNodeVariable* pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pNode2);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == funPars[2]->getObjectName());
  CPPUNIT_ASSERT(pVarNode->getSibling() == NULL);
  pOpNode = dynamic_cast<const CEvaluationNodeOperator*>(pNode->getChild());
  CPPUNIT_ASSERT(pOpNode != NULL);
  CPPUNIT_ASSERT((pOpNode->subType()) == CEvaluationNode::SubType::MULTIPLY);
  pNode2 = dynamic_cast<const CEvaluationNode*>(pOpNode->getChild()->getSibling());
  CPPUNIT_ASSERT(pNode2 != NULL);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pNode2);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == funPars[0]->getObjectName());
  pOpNode = dynamic_cast<const CEvaluationNodeOperator*>(pOpNode->getChild());
  CPPUNIT_ASSERT(pOpNode != NULL);
  CPPUNIT_ASSERT((pOpNode->subType()) == CEvaluationNode::SubType::MULTIPLY);
  pNode2 = dynamic_cast<const CEvaluationNode*>(pOpNode->getChild()->getSibling());
  CPPUNIT_ASSERT(pNode2 != NULL);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pNode2);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == funPars[1]->getObjectName());
  pNode2 = dynamic_cast<const CEvaluationNode*>(pOpNode->getChild());
  CPPUNIT_ASSERT(pNode2 != NULL);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pNode2);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == funPars[0]->getObjectName());

  // check for the two messages
  // we should have a message that delay is not supported and we should have a
  // message about replaced delay nodes
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 36));
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 86));

  // now we reexport the model and check if the changes we made during import
  // are exported correctly
  CPPUNIT_ASSERT(pCOPASIDATAMODEL->getCurrentSBMLDocument() != NULL);
  // export to the same level and version we imported
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, pCOPASIDATAMODEL->getCurrentSBMLDocument()->getLevel(), pCOPASIDATAMODEL->getCurrentSBMLDocument()->getVersion()).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  const Model* pCModel = pDocument->getModel();
  CPPUNIT_ASSERT(pCModel != NULL);
  // assert that there is only one compartment and
  // assert the compartment is constant
  CPPUNIT_ASSERT(pCModel->getNumCompartments() == 1);
  const Compartment* pCCompartment = pCModel->getCompartment(0);
  CPPUNIT_ASSERT(pCCompartment->getConstant() == true);
  CPPUNIT_ASSERT(pCModel->getNumSpecies() == 2);
  const Species* pSpeciesA = pCModel->getSpecies(0);
  CPPUNIT_ASSERT(pCModel->getNumParameters() == 3);
  const Parameter* pParameterK1 = pCModel->getParameter(0);
  CPPUNIT_ASSERT(pParameterK1 != NULL);
  CPPUNIT_ASSERT(pParameterK1->getConstant() == true);
  const Parameter* pParameterDummy1 = pCModel->getParameter(1);
  CPPUNIT_ASSERT(pParameterDummy1 != NULL);
  CPPUNIT_ASSERT(pParameterDummy1->getConstant() == false);
  const Parameter* pParameterDummy2 = pCModel->getParameter(2);
  CPPUNIT_ASSERT(pParameterDummy2 != NULL);
  CPPUNIT_ASSERT(pParameterDummy2->getConstant() == false);
  // there must be two rules
  const AssignmentRule* pARule = dynamic_cast<const AssignmentRule*>(pCModel->getRule(pParameterDummy1->getId()));
  CPPUNIT_ASSERT(pARule != NULL);
  const ASTNode* pANode = pARule->getMath();
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType() == AST_FUNCTION_DELAY);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  const ASTNode* pChild = pANode->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild->getName() == pParameterK1->getId());
  pChild = pANode->getChild(1);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild->getReal() - 0.5) / 0.5) < 1e-9);

  pARule = dynamic_cast<const AssignmentRule*>(pCModel->getRule(pParameterDummy2->getId()));
  CPPUNIT_ASSERT(pARule != NULL);
  pANode = pARule->getMath();
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType() == AST_FUNCTION_DELAY);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  pChild = pANode->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild->getName() == pParameterK1->getId());
  pChild = pANode->getChild(1);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild->getReal() - 0.2) / 0.2) < 1e-9);

  const Reaction* pCReaction = pCModel->getReaction(0);
  // make sure this is reaction A ->
  CPPUNIT_ASSERT(pCReaction != NULL);
  CPPUNIT_ASSERT(pCReaction->getNumReactants() == 1);
  CPPUNIT_ASSERT(pCReaction->getNumProducts() == 1);

  CPPUNIT_ASSERT(pCReaction->isSetKineticLaw() == true);
  const KineticLaw* pLaw = pCReaction->getKineticLaw();
  CPPUNIT_ASSERT(pLaw != NULL);
  CPPUNIT_ASSERT(pLaw->isSetMath() == true);
  pANode = pLaw->getMath();
  CPPUNIT_ASSERT(pANode->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  CPPUNIT_ASSERT(pANode->getChild(0)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(0)->getName() == pCCompartment->getId());
  pANode = pANode->getChild(1);
  CPPUNIT_ASSERT(pANode != NULL);
  // times a function call
  CPPUNIT_ASSERT(pANode->getType() == AST_FUNCTION);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 3);
  CPPUNIT_ASSERT(pANode->getChild(0) != NULL);
  CPPUNIT_ASSERT(pANode->getChild(0)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(0)->getName() == pParameterDummy1->getId());
  CPPUNIT_ASSERT(pANode->getChild(1) != NULL);
  CPPUNIT_ASSERT(pANode->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(1)->getName() == pParameterDummy2->getId());
  CPPUNIT_ASSERT(pANode->getChild(2) != NULL);
  CPPUNIT_ASSERT(pANode->getChild(2)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(2)->getName() == pSpeciesA->getId());

  CPPUNIT_ASSERT(pCModel->getListOfFunctionDefinitions()->size() == 1);
  const FunctionDefinition* pFunDef = pCModel->getFunctionDefinition(0);
  CPPUNIT_ASSERT(pFunDef != NULL);
  CPPUNIT_ASSERT(pFunDef->getId() == pANode->getName());
  pANode = pFunDef->getMath();
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType()  == AST_LAMBDA);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 4);
  CPPUNIT_ASSERT(pANode->getChild(0)->getType() == AST_NAME);
  std::string paramName1 = pANode->getChild(0)->getName();
  CPPUNIT_ASSERT(!paramName1.empty());
  CPPUNIT_ASSERT(pANode->getChild(1)->getType() == AST_NAME);
  std::string paramName2 = pANode->getChild(1)->getName();
  CPPUNIT_ASSERT(!paramName2.empty());
  CPPUNIT_ASSERT(pANode->getChild(2)->getType() == AST_NAME);
  std::string paramName3 = pANode->getChild(2)->getName();
  CPPUNIT_ASSERT(!paramName3.empty());

  // this is the tree of the function
  pANode = pANode->getChild(3);
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  CPPUNIT_ASSERT(pANode->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(1)->getName() == paramName3);
  pANode = pANode->getChild(0);
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  CPPUNIT_ASSERT(pANode->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(1)->getName() == paramName1);
  pANode = pANode->getChild(0);
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  CPPUNIT_ASSERT(pANode->getChild(0)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(0)->getName() == paramName1);
  CPPUNIT_ASSERT(pANode->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(1)->getName() == paramName2);
}

void test000091::test_delay_in_kinetic_law_local_parameter()
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
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::Status::REACTIONS);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::Status::REACTIONS);
  // there should now be three model values because we created two dummy model
  // values that represent the two different delay expression
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 7);
  const CModelValue* pK1 = NULL;
  // four delay replacements
  const CModelValue* pDummy1 = NULL;
  const CModelValue* pDummy2 = NULL;
  const CModelValue* pDummy3 = NULL;
  const CModelValue* pDummy4 = NULL;
  // two local parameters that had to be converted to global parameters
  const CModelValue* pGlobalized1 = NULL;
  const CModelValue* pGlobalized2 = NULL;
  // assign all the global parameters
  pK1 = pModel->getModelValues()["K1"];
  CPPUNIT_ASSERT(pK1 != NULL);
  pDummy1 = pModel->getModelValues()["delay_replacement_parameter_0"];
  CPPUNIT_ASSERT(pDummy1 != NULL);
  pDummy2 = pModel->getModelValues()["delay_replacement_parameter_1"];
  CPPUNIT_ASSERT(pDummy2 != NULL);
  pDummy3 = pModel->getModelValues()["delay_replacement_parameter_2"];
  CPPUNIT_ASSERT(pDummy3 != NULL);
  pDummy4 = pModel->getModelValues()["delay_replacement_parameter_3"];
  CPPUNIT_ASSERT(pDummy4 != NULL);

  CPPUNIT_ASSERT(pModel->getReactions().size() == 1);
  const CReaction* pReaction = pModel->getReactions()[0];
  CPPUNIT_ASSERT(pReaction != NULL);

  std::string reactionId = pReaction->getSBMLId();
  pGlobalized1 = pModel->getModelValues()[reactionId + "_local_0"];
  CPPUNIT_ASSERT(pGlobalized1 != NULL);
  pGlobalized2 = pModel->getModelValues()[reactionId + "_local_1"];
  CPPUNIT_ASSERT(pGlobalized2 != NULL);

  // check if K1 has the correct value
  CPPUNIT_ASSERT(pK1 != NULL);
  CPPUNIT_ASSERT(pK1->getStatus() == CModelEntity::Status::FIXED);
  CPPUNIT_ASSERT(fabs((pK1->getInitialValue() - 4.0) / 4.0) < 1e-9);
  // check if pGlobalized1 (former k3) has the correct value
  CPPUNIT_ASSERT(pGlobalized1 != NULL);
  CPPUNIT_ASSERT(pGlobalized1->getStatus() == CModelEntity::Status::FIXED);
  CPPUNIT_ASSERT(fabs((pGlobalized1->getInitialValue() - 0.3) / 0.3) < 1e-9);
  // check if pGlobalized2 (former k2) has the correct value
  CPPUNIT_ASSERT(pGlobalized2 != NULL);
  CPPUNIT_ASSERT(pGlobalized2->getStatus() == CModelEntity::Status::FIXED);
  CPPUNIT_ASSERT(fabs((pGlobalized2->getInitialValue() - 0.2) / 0.2) < 1e-9);

  // check if pDummy1 has the correct expression
  CPPUNIT_ASSERT(pDummy1->getStatus() == CModelEntity::Status::ASSIGNMENT);
  const CExpression* pExpr = pDummy1->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::DELAY);
  CPPUNIT_ASSERT((pNode->subType()) == CEvaluationNode::SubType::DELAY);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  CPPUNIT_ASSERT((pNode->subType()) == CEvaluationNode::SubType::CN);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCommonName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  CObjectInterface::ContainerList listOfContainers;
  listOfContainers.push_back(pModel);
  const CDataObject* pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pK1);
  const CEvaluationNodeNumber* pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pObjectNode->getSibling());
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT((pNumberNode->subType()) == CEvaluationNode::SubType::DOUBLE);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 0.5) / 0.5) < 1e-3);
  CPPUNIT_ASSERT(pNumberNode->getSibling() == NULL);

  // check if pDummy2 has the correct expression
  CPPUNIT_ASSERT(pDummy2->getStatus() == CModelEntity::Status::ASSIGNMENT);
  pExpr = pDummy2->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::DELAY);
  CPPUNIT_ASSERT((pNode->subType()) == CEvaluationNode::SubType::DELAY);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  CPPUNIT_ASSERT((pNode->subType()) == CEvaluationNode::SubType::CN);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pK1);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pObjectNode->getSibling());
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT((pNumberNode->subType()) == CEvaluationNode::SubType::DOUBLE);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 0.2) / 0.2) < 1e-3);
  CPPUNIT_ASSERT(pNumberNode->getSibling() == NULL);

  // check if pDummy3 has the correct expression
  CPPUNIT_ASSERT(pDummy3->getStatus() == CModelEntity::Status::ASSIGNMENT);
  pExpr = pDummy3->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::DELAY);
  CPPUNIT_ASSERT((pNode->subType()) == CEvaluationNode::SubType::DELAY);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  CPPUNIT_ASSERT((pNode->subType()) == CEvaluationNode::SubType::CN);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pGlobalized1);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pObjectNode->getSibling());
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT((pNumberNode->subType()) == CEvaluationNode::SubType::DOUBLE);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 0.5) / 0.5) < 1e-3);
  CPPUNIT_ASSERT(pNumberNode->getSibling() == NULL);

  // check if pDummy4 has the correct expression
  CPPUNIT_ASSERT(pDummy4->getStatus() == CModelEntity::Status::ASSIGNMENT);
  pExpr = pDummy4->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::DELAY);
  CPPUNIT_ASSERT((pNode->subType()) == CEvaluationNode::SubType::DELAY);
  pNode = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->mainType() == CEvaluationNode::MainType::OBJECT);
  CPPUNIT_ASSERT((pNode->subType()) == CEvaluationNode::SubType::CN);
  pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Value"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pGlobalized2);
  pNumberNode = dynamic_cast<const CEvaluationNodeNumber*>(pObjectNode->getSibling());
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT((pNumberNode->subType()) == CEvaluationNode::SubType::DOUBLE);
  CPPUNIT_ASSERT(fabs((pNumberNode->getValue() - 0.5) / 0.5) < 1e-3);
  CPPUNIT_ASSERT(pNumberNode->getSibling() == NULL);

  CPPUNIT_ASSERT(pReaction->isReversible() == false);
  // check the kinetic law
  const CFunction* pKineticFunction = pReaction->getFunction();
  CPPUNIT_ASSERT(pKineticFunction != NULL);

  const CChemEq* pChemEq = &pReaction->getChemEq();
  CPPUNIT_ASSERT(pChemEq != NULL);
  CPPUNIT_ASSERT(pChemEq->getCompartmentNumber() == 1);
  CPPUNIT_ASSERT(pChemEq->getSubstrates().size() == 1);
  const CChemEqElement* pElement = pChemEq->getSubstrates()[0];
  CPPUNIT_ASSERT(pElement != NULL);
  CPPUNIT_ASSERT(fabs(pElement->getMultiplicity() - 1.0) < 1e-3);
  CPPUNIT_ASSERT(pElement->getMetabolite() == pA);
  CPPUNIT_ASSERT(pChemEq->getProducts().size() == 1);
  pElement = pChemEq->getProducts()[0];
  CPPUNIT_ASSERT(pElement != NULL);
  CPPUNIT_ASSERT(fabs(pElement->getMultiplicity() - 1.0) < 1e-3);
  CPPUNIT_ASSERT(pElement->getMetabolite() == pB);
  CPPUNIT_ASSERT(pChemEq->getModifiers().size() == 0);

  const std::vector<std::vector<std::string> > parameterMappings = pReaction->getParameterMappings();
  CPPUNIT_ASSERT(parameterMappings.size() == 7);
  CPPUNIT_ASSERT(parameterMappings[0].size() == 1);
  CPPUNIT_ASSERT(pReaction->isLocalParameter(0) == false);
  CPPUNIT_ASSERT(parameterMappings[0][0] == pDummy1->getKey());
  CPPUNIT_ASSERT(parameterMappings[1].size() == 1);
  CPPUNIT_ASSERT(pReaction->isLocalParameter(1) == false);
  CPPUNIT_ASSERT(parameterMappings[1][0] == pDummy2->getKey());
  CPPUNIT_ASSERT(parameterMappings[2].size() == 1);
  CPPUNIT_ASSERT(pReaction->isLocalParameter(2) == false);
  CPPUNIT_ASSERT(parameterMappings[2][0] == pDummy3->getKey());
  CPPUNIT_ASSERT(parameterMappings[3].size() == 1);
  CPPUNIT_ASSERT(pReaction->isLocalParameter(3) == false);
  CPPUNIT_ASSERT(parameterMappings[3][0] == pDummy4->getKey());
  CPPUNIT_ASSERT(parameterMappings[4].size() == 1);
  CPPUNIT_ASSERT(pReaction->isLocalParameter(4) == true);
  const CCopasiParameter* pLocalParam = pReaction->getParameters().getParameter("k1");
  CPPUNIT_ASSERT(pLocalParam != NULL);
  CPPUNIT_ASSERT(parameterMappings[5].size() == 1);
  CPPUNIT_ASSERT(pReaction->isLocalParameter(5) == false);
  CPPUNIT_ASSERT(parameterMappings[5][0] == pGlobalized1->getKey());
  CPPUNIT_ASSERT(parameterMappings[6].size() == 1);
  CPPUNIT_ASSERT(parameterMappings[6][0] == pA->getKey());

  const CFunctionParameters& funPars = pKineticFunction->getVariables();
  CPPUNIT_ASSERT(funPars.size() == 7);
  // check the expression of the kinetic law
  // dummy1 * dummy2 * dummy1 * species1 * k1 * dummy3 * dummy4 * dummy3 * globalized1
  pNode = pKineticFunction->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  const CEvaluationNodeOperator* pOpNode = dynamic_cast<const CEvaluationNodeOperator*>(pNode);
  CPPUNIT_ASSERT(pOpNode != NULL);
  CPPUNIT_ASSERT((pOpNode->subType()) == CEvaluationNode::SubType::MULTIPLY);
  const CEvaluationNode* pNode2 = dynamic_cast<const CEvaluationNode*>(pOpNode->getChild()->getSibling());
  CPPUNIT_ASSERT(pNode2 != NULL);
  const CEvaluationNodeVariable* pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pNode2);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == funPars[5]->getObjectName());
  CPPUNIT_ASSERT(pVarNode->getSibling() == NULL);
  pOpNode = dynamic_cast<const CEvaluationNodeOperator*>(pNode->getChild());
  CPPUNIT_ASSERT(pOpNode != NULL);
  CPPUNIT_ASSERT((pOpNode->subType()) == CEvaluationNode::SubType::MULTIPLY);
  pNode2 = dynamic_cast<const CEvaluationNode*>(pOpNode->getChild()->getSibling());
  CPPUNIT_ASSERT(pNode2 != NULL);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pNode2);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == funPars[2]->getObjectName());
  pOpNode = dynamic_cast<const CEvaluationNodeOperator*>(pOpNode->getChild());
  CPPUNIT_ASSERT(pOpNode != NULL);
  CPPUNIT_ASSERT((pOpNode->subType()) == CEvaluationNode::SubType::MULTIPLY);
  pNode2 = dynamic_cast<const CEvaluationNode*>(pOpNode->getChild()->getSibling());
  CPPUNIT_ASSERT(pNode2 != NULL);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pNode2);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == funPars[3]->getObjectName());
  pOpNode = dynamic_cast<const CEvaluationNodeOperator*>(pOpNode->getChild());
  CPPUNIT_ASSERT(pOpNode != NULL);
  CPPUNIT_ASSERT((pOpNode->subType()) == CEvaluationNode::SubType::MULTIPLY);
  pNode2 = dynamic_cast<const CEvaluationNode*>(pOpNode->getChild()->getSibling());
  CPPUNIT_ASSERT(pNode2 != NULL);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pNode2);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == funPars[2]->getObjectName());
  pOpNode = dynamic_cast<const CEvaluationNodeOperator*>(pOpNode->getChild());
  CPPUNIT_ASSERT(pOpNode != NULL);
  CPPUNIT_ASSERT((pOpNode->subType()) == CEvaluationNode::SubType::MULTIPLY);
  pNode2 = dynamic_cast<const CEvaluationNode*>(pOpNode->getChild()->getSibling());
  CPPUNIT_ASSERT(pNode2 != NULL);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pNode2);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == funPars[4]->getObjectName());
  pOpNode = dynamic_cast<const CEvaluationNodeOperator*>(pOpNode->getChild());
  CPPUNIT_ASSERT(pOpNode != NULL);
  CPPUNIT_ASSERT((pOpNode->subType()) == CEvaluationNode::SubType::MULTIPLY);
  pNode2 = dynamic_cast<const CEvaluationNode*>(pOpNode->getChild()->getSibling());
  CPPUNIT_ASSERT(pNode2 != NULL);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pNode2);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == funPars[6]->getObjectName());
  pOpNode = dynamic_cast<const CEvaluationNodeOperator*>(pOpNode->getChild());
  CPPUNIT_ASSERT(pOpNode != NULL);
  CPPUNIT_ASSERT((pOpNode->subType()) == CEvaluationNode::SubType::MULTIPLY);
  pNode2 = dynamic_cast<const CEvaluationNode*>(pOpNode->getChild()->getSibling());
  CPPUNIT_ASSERT(pNode2 != NULL);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pNode2);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == funPars[0]->getObjectName());
  pOpNode = dynamic_cast<const CEvaluationNodeOperator*>(pOpNode->getChild());
  CPPUNIT_ASSERT(pOpNode != NULL);
  CPPUNIT_ASSERT((pOpNode->subType()) == CEvaluationNode::SubType::MULTIPLY);
  pNode2 = dynamic_cast<const CEvaluationNode*>(pOpNode->getChild()->getSibling());
  CPPUNIT_ASSERT(pNode2 != NULL);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pNode2);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == funPars[1]->getObjectName());

  pNode2 = dynamic_cast<const CEvaluationNode*>(pOpNode->getChild());
  CPPUNIT_ASSERT(pNode2 != NULL);
  pVarNode = dynamic_cast<const CEvaluationNodeVariable*>(pNode2);
  CPPUNIT_ASSERT(pVarNode != NULL);
  CPPUNIT_ASSERT(pVarNode->getData() == funPars[0]->getObjectName());

  // check for the two messages
  // we should have a message that delay is not supported and we should have a
  // message about replaced delay nodes
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 36));
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 86));
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 87));

  // now we reexport the model and check if the changes we made during import
  // are exported correctly
  CPPUNIT_ASSERT(pCOPASIDATAMODEL->getCurrentSBMLDocument() != NULL);
  // export to the same level and version we imported
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, pCOPASIDATAMODEL->getCurrentSBMLDocument()->getLevel(), pCOPASIDATAMODEL->getCurrentSBMLDocument()->getVersion()).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  const Model* pCModel = pDocument->getModel();
  CPPUNIT_ASSERT(pCModel != NULL);
  // assert that there is only one compartment and
  // assert the compartment is constant
  CPPUNIT_ASSERT(pCModel->getNumCompartments() == 1);
  const Compartment* pCCompartment = pCModel->getCompartment(0);
  CPPUNIT_ASSERT(pCCompartment->getConstant() == true);
  CPPUNIT_ASSERT(pCModel->getNumSpecies() == 2);
  const Species* pSpeciesA = pCModel->getSpecies(0);
  CPPUNIT_ASSERT(pCModel->getNumParameters() == 7);
  const Parameter* pParameterK1 = pCModel->getParameter(0);
  CPPUNIT_ASSERT(pParameterK1 != NULL);
  CPPUNIT_ASSERT(pParameterK1->getConstant() == true);
  CPPUNIT_ASSERT(fabs((pParameterK1->getValue() - 4.0) / 4.0) < 1e-9);
  const Parameter* pParameterDummy1 = pCModel->getParameter(1);
  CPPUNIT_ASSERT(pParameterDummy1 != NULL);
  CPPUNIT_ASSERT(pParameterDummy1->getConstant() == false);
  const Parameter* pParameterDummy2 = pCModel->getParameter(2);
  CPPUNIT_ASSERT(pParameterDummy2 != NULL);
  CPPUNIT_ASSERT(pParameterDummy2->getConstant() == false);
  const Parameter* pParameterDummy3 = pCModel->getParameter(3);
  CPPUNIT_ASSERT(pParameterDummy3 != NULL);
  CPPUNIT_ASSERT(pParameterDummy3->getConstant() == false);
  const Parameter* pGlobalizedParam1 = pCModel->getParameter(4);
  CPPUNIT_ASSERT(pGlobalizedParam1 != NULL);
  CPPUNIT_ASSERT(pGlobalizedParam1->getConstant() == true);
  CPPUNIT_ASSERT(fabs((pGlobalizedParam1->getValue() - 0.3) / 0.3) < 1e-9);
  const Parameter* pParameterDummy4 = pCModel->getParameter(5);
  CPPUNIT_ASSERT(pParameterDummy4 != NULL);
  CPPUNIT_ASSERT(pParameterDummy4->getConstant() == false);
  const Parameter* pGlobalizedParam2 = pCModel->getParameter(6);
  CPPUNIT_ASSERT(pGlobalizedParam2 != NULL);
  CPPUNIT_ASSERT(pGlobalizedParam2->getConstant() == true);
  CPPUNIT_ASSERT(fabs((pGlobalizedParam2->getValue() - 0.2) / 0.2) < 1e-9);
  //
  // there must be four rules
  const AssignmentRule* pARule = dynamic_cast<const AssignmentRule*>(pCModel->getRule(pParameterDummy1->getId()));
  CPPUNIT_ASSERT(pARule != NULL);
  const ASTNode* pANode = pARule->getMath();
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType() == AST_FUNCTION_DELAY);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  const ASTNode* pChild = pANode->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild->getName() == pParameterK1->getId());
  pChild = pANode->getChild(1);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild->getReal() - 0.5) / 0.5) < 1e-9);

  pARule = dynamic_cast<const AssignmentRule*>(pCModel->getRule(pParameterDummy2->getId()));
  CPPUNIT_ASSERT(pARule != NULL);
  pANode = pARule->getMath();
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType() == AST_FUNCTION_DELAY);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  pChild = pANode->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild->getName() == pParameterK1->getId());
  pChild = pANode->getChild(1);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild->getReal() - 0.2) / 0.2) < 1e-9);

  // rule for dummy3
  pARule = dynamic_cast<const AssignmentRule*>(pCModel->getRule(pParameterDummy3->getId()));
  CPPUNIT_ASSERT(pARule != NULL);
  pANode = pARule->getMath();
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType() == AST_FUNCTION_DELAY);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  pChild = pANode->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild->getName() == pGlobalizedParam1->getId());
  pChild = pANode->getChild(1);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild->getReal() - 0.5) / 0.5) < 1e-9);

  // rule for dummy4
  pARule = dynamic_cast<const AssignmentRule*>(pCModel->getRule(pParameterDummy4->getId()));
  CPPUNIT_ASSERT(pARule != NULL);
  pANode = pARule->getMath();
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType() == AST_FUNCTION_DELAY);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  pChild = pANode->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild->getName() == pGlobalizedParam2->getId());
  pChild = pANode->getChild(1);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild->getReal() - 0.5) / 0.5) < 1e-9);

  const Reaction* pCReaction = pCModel->getReaction(0);
  // make sure this is reaction A ->
  CPPUNIT_ASSERT(pCReaction != NULL);
  CPPUNIT_ASSERT(pCReaction->getNumReactants() == 1);
  CPPUNIT_ASSERT(pCReaction->getNumProducts() == 1);

  CPPUNIT_ASSERT(pCReaction->isSetKineticLaw() == true);
  const KineticLaw* pLaw = pCReaction->getKineticLaw();
  CPPUNIT_ASSERT(pLaw != NULL);
  CPPUNIT_ASSERT(pLaw->getNumParameters() == 1);
  const Parameter* pLocalP = pLaw->getParameter(0);
  CPPUNIT_ASSERT(pLocalP != NULL);
  CPPUNIT_ASSERT(fabs((pLocalP->getValue() - 0.1) / 0.1) < 1e-9);
  CPPUNIT_ASSERT(pLaw->isSetMath() == true);
  pANode = pLaw->getMath();
  CPPUNIT_ASSERT(pANode->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  CPPUNIT_ASSERT(pANode->getChild(0)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(0)->getName() == pCCompartment->getId());
  pANode = pANode->getChild(1);
  CPPUNIT_ASSERT(pANode != NULL);
  // times a function call
  CPPUNIT_ASSERT(pANode->getType() == AST_FUNCTION);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 7);
  CPPUNIT_ASSERT(pANode->getChild(0) != NULL);
  CPPUNIT_ASSERT(pANode->getChild(0)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(0)->getName() == pParameterDummy1->getId());
  CPPUNIT_ASSERT(pANode->getChild(1) != NULL);
  CPPUNIT_ASSERT(pANode->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(1)->getName() == pParameterDummy2->getId());
  CPPUNIT_ASSERT(pANode->getChild(2) != NULL);
  CPPUNIT_ASSERT(pANode->getChild(2)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(2)->getName() == pParameterDummy3->getId());
  CPPUNIT_ASSERT(pANode->getChild(3) != NULL);
  CPPUNIT_ASSERT(pANode->getChild(3)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(3)->getName() == pParameterDummy4->getId());
  CPPUNIT_ASSERT(pANode->getChild(4) != NULL);
  CPPUNIT_ASSERT(pANode->getChild(4)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(4)->getName() == pLocalP->getId());
  CPPUNIT_ASSERT(pANode->getChild(5) != NULL);
  CPPUNIT_ASSERT(pANode->getChild(5)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(5)->getName() == pGlobalizedParam1->getId());
  CPPUNIT_ASSERT(pANode->getChild(6) != NULL);
  CPPUNIT_ASSERT(pANode->getChild(6)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(6)->getName() == pSpeciesA->getId());

  CPPUNIT_ASSERT(pCModel->getListOfFunctionDefinitions()->size() == 1);
  const FunctionDefinition* pFunDef = pCModel->getFunctionDefinition(0);
  CPPUNIT_ASSERT(pFunDef != NULL);
  CPPUNIT_ASSERT(pFunDef->getId() == pANode->getName());
  pANode = pFunDef->getMath();
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType()  == AST_LAMBDA);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 8);
  CPPUNIT_ASSERT(pANode->getChild(0)->getType() == AST_NAME);
  std::string paramName1 = pANode->getChild(0)->getName();
  CPPUNIT_ASSERT(!paramName1.empty());
  CPPUNIT_ASSERT(pANode->getChild(1)->getType() == AST_NAME);
  std::string paramName2 = pANode->getChild(1)->getName();
  CPPUNIT_ASSERT(!paramName2.empty());
  CPPUNIT_ASSERT(pANode->getChild(2)->getType() == AST_NAME);
  std::string paramName3 = pANode->getChild(2)->getName();
  CPPUNIT_ASSERT(!paramName3.empty());
  CPPUNIT_ASSERT(pANode->getChild(3)->getType() == AST_NAME);
  std::string paramName4 = pANode->getChild(3)->getName();
  CPPUNIT_ASSERT(!paramName4.empty());
  CPPUNIT_ASSERT(pANode->getChild(4)->getType() == AST_NAME);
  std::string paramName5 = pANode->getChild(4)->getName();
  CPPUNIT_ASSERT(!paramName5.empty());
  CPPUNIT_ASSERT(pANode->getChild(5)->getType() == AST_NAME);
  std::string paramName6 = pANode->getChild(5)->getName();
  CPPUNIT_ASSERT(!paramName6.empty());
  CPPUNIT_ASSERT(pANode->getChild(6)->getType() == AST_NAME);
  std::string paramName7 = pANode->getChild(6)->getName();
  CPPUNIT_ASSERT(!paramName7.empty());
  //
  // this is the tree of the function
  pANode = pANode->getChild(7);
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  CPPUNIT_ASSERT(pANode->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(1)->getName() == paramName6);
  pANode = pANode->getChild(0);
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  CPPUNIT_ASSERT(pANode->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(1)->getName() == paramName3);
  pANode = pANode->getChild(0);
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  CPPUNIT_ASSERT(pANode->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(1)->getName() == paramName4);
  pANode = pANode->getChild(0);
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  CPPUNIT_ASSERT(pANode->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(1)->getName() == paramName3);
  pANode = pANode->getChild(0);
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  CPPUNIT_ASSERT(pANode->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(1)->getName() == paramName5);
  pANode = pANode->getChild(0);
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  CPPUNIT_ASSERT(pANode->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(1)->getName() == paramName7);
  pANode = pANode->getChild(0);
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  CPPUNIT_ASSERT(pANode->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(1)->getName() == paramName1);
  pANode = pANode->getChild(0);
  CPPUNIT_ASSERT(pANode != NULL);
  CPPUNIT_ASSERT(pANode->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pANode->getNumChildren() == 2);
  CPPUNIT_ASSERT(pANode->getChild(0)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(0)->getName() == paramName1);
  CPPUNIT_ASSERT(pANode->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pANode->getChild(1)->getName() == paramName2);
}

const char* test000091::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">\n"
  "  <model id=\"Model_1\" name=\"New Model\">\n"
  "    <notes>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        <p>Model with delay in kinetic law</p>\n"
  "      </body>\n"
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
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\"/>\n"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>\n"
  "    </listOfSpecies>\n"
  "    <listOfParameters>\n"
  "      <parameter id=\"parameter_1\" name=\"K1\" value=\"4\"/>\n"
  "    </listOfParameters>\n"
  "    <listOfReactions>\n"
  "      <reaction id=\"reaction_1\" name=\"reaction_0\" reversible=\"false\">\n"
  "        <listOfReactants>\n"
  "          <speciesReference species=\"species_1\"/>\n"
  "        </listOfReactants>\n"
  "        <listOfProducts>\n"
  "          <speciesReference species=\"species_2\"/>\n"
  "        </listOfProducts>\n"
  "        <kineticLaw>\n"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "            <apply>\n"
  "              <times/>\n"
  "              <ci> compartment_1 </ci>i\n"
  "              <apply>\n"
  "                <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/delay\">\n"
  "                 delay\n"
  "                </csymbol>\n"
  "                <ci> parameter_1 </ci>\n"
  "                <cn> 0.5 </cn>\n"
  "              </apply>\n"
  "              <apply>\n"
  "                <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/delay\">\n"
  "                 delay\n"
  "                </csymbol>\n"
  "                <ci> parameter_1 </ci>\n"
  "                <cn> 0.2 </cn>\n"
  "              </apply>\n"
  "              <apply>\n"
  "                <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/delay\">\n"
  "                 delay\n"
  "                </csymbol>\n"
  "                <ci> parameter_1 </ci>\n"
  "                <cn> 0.5 </cn>\n"
  "              </apply>\n"
  "              <ci> species_1 </ci>\n"
  "            </apply>\n"
  "          </math>\n"
  "        </kineticLaw>\n"
  "      </reaction>\n"
  "    </listOfReactions>\n"
  "  </model>\n"
  "</sbml>\n"
  ;

const char* test000091::MODEL_STRING2 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">\n"
  "  <model id=\"Model_1\" name=\"New Model\">\n"
  "    <notes>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        <p>Model with delay in kinetic law as well as local parameters in delay expression</p>\n"
  "      </body>\n"
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
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\"/>\n"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>\n"
  "    </listOfSpecies>\n"
  "    <listOfParameters>\n"
  "      <parameter id=\"parameter_1\" name=\"K1\" value=\"4\"/>\n"
  "    </listOfParameters>\n"
  "    <listOfReactions>\n"
  "      <reaction id=\"reaction_1\" name=\"reaction_0\" reversible=\"false\">\n"
  "        <listOfReactants>\n"
  "          <speciesReference species=\"species_1\"/>\n"
  "        </listOfReactants>\n"
  "        <listOfProducts>\n"
  "          <speciesReference species=\"species_2\"/>\n"
  "        </listOfProducts>\n"
  "        <kineticLaw>\n"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "            <apply>\n"
  "              <times/>\n"
  "              <ci> compartment_1 </ci>i\n"
  "              <apply>\n"
  "                <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/delay\">\n"
  "                 delay\n"
  "                </csymbol>\n"
  "                <ci> parameter_1 </ci>\n"
  "                <cn> 0.5 </cn>\n"
  "              </apply>\n"
  "              <apply>\n"
  "                <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/delay\">\n"
  "                 delay\n"
  "                </csymbol>\n"
  "                <ci> parameter_1 </ci>\n"
  "                <cn> 0.2 </cn>\n"
  "              </apply>\n"
  "              <apply>\n"
  "                <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/delay\">\n"
  "                 delay\n"
  "                </csymbol>\n"
  "                <ci> parameter_1 </ci>\n"
  "                <cn> 0.5 </cn>\n"
  "              </apply>\n"
  "              <ci> species_1 </ci>\n"
  "              <ci> k1 </ci>\n"
  "              <apply>\n"
  "                <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/delay\">\n"
  "                 delay\n"
  "                </csymbol>\n"
  "                <ci> k3 </ci>\n"
  "                <cn> 0.5 </cn>\n"
  "              </apply>\n"
  "              <apply>\n"
  "                <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/delay\">\n"
  "                 delay\n"
  "                </csymbol>\n"
  "                <ci> k2 </ci>\n"
  "                <cn> 0.5 </cn>\n"
  "              </apply>\n"
  "              <apply>\n"
  "                <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/delay\">\n"
  "                 delay\n"
  "                </csymbol>\n"
  "                <ci> k3 </ci>\n"
  "                <cn> 0.5 </cn>\n"
  "              </apply>\n"
  "              <ci> k3 </ci>\n"
  "            </apply>\n"
  "          </math>\n"
  "          <listOfParameters>"
  "            <parameter id=\"k1\" value=\"0.1\"/>"
  "            <parameter id=\"k2\" value=\"0.2\"/>"
  "            <parameter id=\"k3\" value=\"0.3\"/>"
  "          </listOfParameters>"
  "        </kineticLaw>\n"
  "      </reaction>\n"
  "    </listOfReactions>\n"
  "  </model>\n"
  "</sbml>\n"
  ;
