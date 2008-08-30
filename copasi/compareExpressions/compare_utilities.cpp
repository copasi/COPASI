// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/compare_utilities.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/08/30 15:57:27 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243)
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
#endif  // WIN32

#include <sstream>

#include "compare_utilities.h"

#include "sbml/math/ASTNode.h"
#include "sbml/Model.h"
#include "CNormalBase.h"
#include "CNormalFraction.h"
#include "CNormalFunction.h"
#include "CNormalSum.h"
#include "CNormalProduct.h"
#include "CNormalLogical.h"
#include "CNormalLogicalItem.h"
#include "CNormalChoice.h"
#include "CNormalChoiceLogical.h"
#include "CNormalGeneralPower.h"
#include "CNormalItemPower.h"
#include "CNormalItem.h"
#include "ConvertToCEvaluationNode.h"
#include "copasi/utilities/CCopasiTree.h"
#include "copasi/function/CEvaluationTree.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationNodeObject.h"
#include "copasi/sbml/ConverterASTNode.h"
#include "sbml/FunctionDefinition.h"

ASTNode* create_expression(const ASTNode* pSource, const Model* pModel)
{
  // expand all function calls
  ASTNode* pResult = expand_function_calls(pSource, pModel);
  return pResult;
}

ASTNode* expand_function_calls(const ASTNode* pNode, const Model* pModel)
{
  ASTNode* pResult = NULL;
  if (pNode->getType() == AST_FUNCTION)
    {
      pResult = expand_function_call(pNode, pModel);
      assert(pResult != NULL);
      ASTNode* pTmp = expand_function_calls(pResult, pModel);
      assert(pTmp != NULL);
      delete pResult;
      pResult = pTmp;
    }
  else
    {
      // only make a shallow copy
      pResult = ConverterASTNode::shallowCopy(pNode);
      unsigned int i = 0;
      unsigned int iMax = pNode->getNumChildren();
      ASTNode* pChild = NULL;
      ASTNode* pNewChild = NULL;
      while (i < iMax)
        {
          pChild = pNode->getChild(i);
          assert(pChild != NULL);
          pNewChild = expand_function_calls(pChild, pModel);
          assert(pNewChild != NULL);
          pResult->addChild(pNewChild);
          ++i;
        }
    }
  return pResult;
}

ASTNode* expand_function_call(const ASTNode* pCall, const Model* pModel)
{
  // find the function that belongs to the call
  const FunctionDefinition * pFunctionDefinition = NULL;
  ASTNode* pResult = NULL;
  unsigned int i = 0, iMax = pModel->getNumFunctionDefinitions();
  while (i < iMax)
    {
      if (pModel->getFunctionDefinition(i)->getId() == pCall->getName())
        {
          pFunctionDefinition = pModel->getFunctionDefinition(i);
          break;
        }
      ++i;
    }

  // create the mapping
  iMax = pFunctionDefinition->getNumArguments();
  if (pFunctionDefinition != NULL && iMax == pCall->getNumChildren())
    {
      // map the first function argument to the first child in the call etc.
      std::map<std::string, const ASTNode*> argumentMap;
      i = 0;
      while (i < iMax)
        {
          argumentMap[pFunctionDefinition->getArgument(i)->getName()] = pCall->getChild(i);
          ++i;
        }
      // create the resulting tree
      pResult = pFunctionDefinition->getBody()->deepCopy();
      ASTNode* pTmpNode = replace_variable_names(pResult, argumentMap);
      assert(pTmpNode != NULL);
      delete pResult;
      pResult = pTmpNode;
    }
  return pResult;
}

ASTNode* replace_variable_names(const ASTNode* pNode, const std::map<std::string, const ASTNode*>& argumentMap)
{
  ASTNode* pResult = NULL;
  if (pNode->getType() == AST_NAME)
    {
      std::map<std::string, const ASTNode*>::const_iterator pos = argumentMap.find(pNode->getName());
      if (pos == argumentMap.end())
        {
          pResult = NULL;
        }
      else
        {
          pResult = pos->second->deepCopy();
        }
    }
  else
    {
      // only make a shallow copy
      pResult = ConverterASTNode::shallowCopy(pNode);
      unsigned int i = 0;
      unsigned int iMax = pNode->getNumChildren();
      ASTNode* pChild = NULL;
      ASTNode* pNewChild = NULL;
      while (i < iMax)
        {
          pChild = pNode->getChild(i);
          assert(pChild != NULL);
          pNewChild = replace_variable_names(pChild, argumentMap);
          assert(pNewChild != NULL);
          pResult->addChild(pNewChild);
          ++i;
        }
    }
  return pResult;
}

bool are_equal(const CNormalFraction* pLHS, const CNormalFraction* pRHS)
{
  bool result = true;
  // replace all variable names in the normalform so that the naming scheme
  // is consistent
  std::map<std::string, std::string> variableMap;
  CNormalFraction* pTmpLHS = new CNormalFraction(*pLHS);
  normalize_variable_names(pTmpLHS, variableMap);
  variableMap.clear();
  CNormalFraction* pTmpRHS = new CNormalFraction(*pRHS);
  normalize_variable_names(pTmpRHS, variableMap);
  result = ((*pTmpLHS) == (*pTmpRHS));
  delete pTmpLHS;
  delete pTmpRHS;
  return result;
}

void normalize_variable_names(CNormalBase* pBase, std::map<std::string, std::string>& variableMap)
{
  CNormalChoice* pChoice = NULL;
  CNormalChoiceLogical* pLogicalChoice = NULL;
  CNormalFraction* pFraction = NULL;
  CNormalFunction* pFunction = NULL;
  CNormalGeneralPower* pGeneralPower = NULL;
  CNormalItem* pItem = NULL;
  CNormalItemPower* pItemPower = NULL;
  CNormalLogical* pLogical = NULL;
  CNormalLogicalItem* pLogicalItem = NULL;
  CNormalProduct* pProduct = NULL;
  CNormalSum* pSum = NULL;
  if ((pChoice = dynamic_cast<CNormalChoice*>(pBase)) != NULL)
    {
      normalize_variable_names(&pChoice->getCondition(), variableMap);
      normalize_variable_names(&pChoice->getTrueExpression(), variableMap);
      normalize_variable_names(&pChoice->getFalseExpression(), variableMap);
    }
  else if ((pLogicalChoice = dynamic_cast<CNormalChoiceLogical*>(pBase)) != NULL)
    {
      normalize_variable_names(&pChoice->getCondition(), variableMap);
      normalize_variable_names(&pChoice->getTrueExpression(), variableMap);
      normalize_variable_names(&pChoice->getFalseExpression(), variableMap);
    }
  else if ((pFraction = dynamic_cast<CNormalFraction*>(pBase)) != NULL)
    {
      normalize_variable_names(&pFraction->getNumerator(), variableMap);
      if (!pFraction->checkDenominatorOne())
        {
          normalize_variable_names(&pFraction->getDenominator(), variableMap);
        }
    }
  else if ((pFunction = dynamic_cast<CNormalFunction*>(pBase)) != NULL)
    {
      normalize_variable_names(&pFunction->getFraction(), variableMap);
    }
  else if ((pGeneralPower = dynamic_cast<CNormalGeneralPower*>(pBase)) != NULL)
    {
      normalize_variable_names(&pGeneralPower->getLeft(), variableMap);
      normalize_variable_names(&pGeneralPower->getRight(), variableMap);
    }
  else if ((pItem = dynamic_cast<CNormalItem*>(pBase)) != NULL)
    {
      std::map<std::string, std::string>::iterator pos;
      switch (pItem->getType())
        {
        case CNormalItem::VARIABLE:
          pos = variableMap.find(pItem->getName());
          if (pos != variableMap.end())
            {
              pItem->setName(pos->second);
            }
          else
            {
              std::ostringstream ostrstr;
              ostrstr << "variable";
              ostrstr.width(7);
              ostrstr.fill('0');
              ostrstr << variableMap.size() + 1;
              variableMap[pItem->getName()] = ostrstr.str();
              pItem->setName(ostrstr.str());
            }
          break;
        default:
          break;
        }
    }
  else if ((pItemPower = dynamic_cast<CNormalItemPower*>(pBase)) != NULL)
    {
      normalize_variable_names(&pItemPower->getItem(), variableMap);
    }
  else if ((pLogical = dynamic_cast<CNormalLogical*>(pBase)) != NULL)
    {
      CNormalLogical::ChoiceSetOfSets tmpSet;
      CNormalLogical::ChoiceSetOfSets::const_iterator it = pLogical->getChoices().begin(), endit = pLogical->getChoices().end();
      while (it != endit)
        {
          CNormalLogical::ChoiceSet tmpChoiceSet;
          CNormalLogical::ChoiceSet::const_iterator innerit = (*it).first.begin(), innerendit = (*it).first.end();
          while (innerit != innerendit)
            {
              pLogicalChoice = new CNormalChoiceLogical(*(*innerit).first);
              normalize_variable_names(pLogicalChoice, variableMap);
              tmpChoiceSet.insert(std::make_pair(pLogicalChoice, (*innerit).second));
              ++innerit;
            }
          tmpSet.insert(std::make_pair(tmpChoiceSet, (*it).second));
          ++it;
        }
      pLogical->setChoices(tmpSet);
      CNormalLogical::cleanSetOfSets(tmpSet);
      CNormalLogical::ItemSetOfSets tmpSet2;
      CNormalLogical::ItemSetOfSets::const_iterator it2 = pLogical->getAndSets().begin(), endit2 = pLogical->getAndSets().end();
      while (it2 != endit2)
        {
          CNormalLogical::ItemSet tmpItemSet;
          CNormalLogical::ItemSet::const_iterator innerit = (*it2).first.begin(), innerendit = (*it2).first.end();
          while (innerit != innerendit)
            {
              pLogicalItem = new CNormalLogicalItem(*(*innerit).first);
              normalize_variable_names(pLogicalItem, variableMap);
              tmpItemSet.insert(std::make_pair(pLogicalItem, (*innerit).second));
              ++innerit;
            }
          tmpSet2.insert(std::make_pair(tmpItemSet, (*it2).second));
          ++it2;
        }
      pLogical->setAndSets(tmpSet2);
      CNormalLogical::cleanSetOfSets(tmpSet2);
    }
  else if ((pLogicalItem = dynamic_cast<CNormalLogicalItem*>(pBase)) != NULL)
    {
      normalize_variable_names(&pLogicalItem->getLeft(), variableMap);
      normalize_variable_names(&pLogicalItem->getRight(), variableMap);
    }
  else if ((pProduct = dynamic_cast<CNormalProduct*>(pBase)) != NULL)
    {
      std::set<CNormalItemPower*, compareItemPowers> tmpSet;
      std::set<CNormalItemPower*, compareItemPowers>::const_iterator it = pProduct->getItemPowers().begin(), endit = pProduct->getItemPowers().end();
      while (it != endit)
        {
          CNormalItemPower* pItemPower = new CNormalItemPower(**it);
          normalize_variable_names(pItemPower, variableMap);
          tmpSet.insert(pItemPower);
          ++it;
        }
      pProduct->setItemPowers(tmpSet);
      it = tmpSet.begin(), endit = tmpSet.end();
      while (it != endit)
        {
          delete *it;
          ++it;
        }
    }
  else if ((pSum = dynamic_cast<CNormalSum*>(pBase)) != NULL)
    {
      std::set<CNormalFraction*> tmpSet;
      std::set<CNormalFraction*>::const_iterator it = pSum->getFractions().begin(), endit = pSum->getFractions().end();
      while (it != endit)
        {
          pFraction = new CNormalFraction(**it);
          normalize_variable_names(pFraction, variableMap);
          tmpSet.insert(pFraction);
          ++it;
        }
      pSum->setFractions(tmpSet);
      it = tmpSet.begin(), endit = tmpSet.end();
      while (it != endit)
        {
          delete *it;
          ++it;
        }
      std::set<CNormalProduct*, compareProducts> tmpSet2;
      std::set<CNormalProduct*, compareProducts>::const_iterator it2 = pSum->getProducts().begin(), endit2 = pSum->getProducts().end();
      while (it2 != endit2)
        {
          pProduct = new CNormalProduct(**it2);
          normalize_variable_names(pProduct, variableMap);
          tmpSet2.insert(pProduct);
          ++it2;
        }
      pSum->setProducts(tmpSet2);
      it2 = tmpSet2.begin(), endit2 = tmpSet2.end();
      while (it2 != endit2)
        {
          delete (*it2);
          ++it2;
        }
    }
}

CNormalFraction* create_normalform(const ASTNode* pSource)
{
  CNormalFraction* pFraction = NULL;
  // translate the ASTNode based tree into an CEvaluationNode based tree and
  CEvaluationNode* pEvaluationNode = CEvaluationTree::convertASTNode(*pSource);
  // all variable nodes in this tree are objects nodes so we have to convert
  // them
  CCopasiTree<CEvaluationNode>::iterator treeIt = pEvaluationNode;
  // if the root node already is an object node, this has to be dealt with separately
  if (dynamic_cast<CEvaluationNodeObject*>(&(*treeIt)))
    {
      CEvaluationNodeVariable* pVariableNode = new CEvaluationNodeVariable(CEvaluationNodeVariable::ANY, (*treeIt).getData().substr(1, (*treeIt).getData().length() - 2));
      delete pEvaluationNode;
      pEvaluationNode = pVariableNode;
    }
  else
    {
      while (treeIt != NULL)
        {
          if (dynamic_cast<CEvaluationNodeObject*>(&(*treeIt)))
            {
              CEvaluationNodeVariable* pVariableNode = new CEvaluationNodeVariable(CEvaluationNodeVariable::ANY, (*treeIt).getData().substr(1, (*treeIt).getData().length() - 2));
              if ((*treeIt).getParent())
                {
                  (*treeIt).getParent()->addChild(pVariableNode, &(*treeIt));
                  (*treeIt).getParent()->removeChild(&(*treeIt));
                }
              delete &(*treeIt);
              treeIt = pVariableNode;
            }
          ++treeIt;
        }
    }
  if (pEvaluationNode != NULL)
    {
      // create the normalform from that
      pFraction = createNormalRepresentation(pEvaluationNode);
      delete pEvaluationNode;
    }
  return pFraction;
}

/**
 * This function replaces a call to SEC by 1/COS.
 */
ASTNode* replace_SEC(const ASTNode* pChild)
{
  ASTNode* pResult = NULL;
  if (pChild != NULL)
    {
      pResult = new ASTNode(AST_DIVIDE);
      ASTNode* pTmpNode = new ASTNode(AST_INTEGER);
      pTmpNode->setValue(1);
      pResult->addChild(pTmpNode);
      pTmpNode = new ASTNode(AST_FUNCTION_COS);
      pTmpNode->addChild(pChild->deepCopy());
      pResult->addChild(pTmpNode);
    }
  return pResult;
}

/**
 * This function replaces a call to CSC by 1/SIN.
 */
ASTNode* replace_CSC(const ASTNode* pChild)
{
  ASTNode* pResult = NULL;
  if (pChild != NULL)
    {
      pResult = new ASTNode(AST_DIVIDE);
      ASTNode* pTmpNode = new ASTNode(AST_INTEGER);
      pTmpNode->setValue(1);
      pResult->addChild(pTmpNode);
      pTmpNode = new ASTNode(AST_FUNCTION_SIN);
      pTmpNode->addChild(pChild->deepCopy());
      pResult->addChild(pTmpNode);
    }
  return pResult;
}

/**
 * This function replaces a call to COT by COS/SIN.
 */
ASTNode* replace_COT(const ASTNode* pChild)
{
  ASTNode* pResult = NULL;
  if (pChild != NULL)
    {
      pResult = new ASTNode(AST_DIVIDE);
      ASTNode* pTmpNode = new ASTNode(AST_FUNCTION_COS);
      pTmpNode->addChild(pChild->deepCopy());
      pResult->addChild(pTmpNode);
      pTmpNode = new ASTNode(AST_FUNCTION_SIN);
      pTmpNode->addChild(pChild->deepCopy());
      pResult->addChild(pTmpNode);
    }
  return pResult;
}

/**
 * This function replaces a call to SINH by (e^X-e^(-X))/2.
 */
ASTNode* replace_SINH(const ASTNode* pChild)
{
  ASTNode* pResult = NULL;
  if (pChild != NULL)
    {
      pResult = new ASTNode(AST_DIVIDE);
      ASTNode* pTmpNode = new ASTNode(AST_MINUS);
      ASTNode* pTmpNode2 = new ASTNode(AST_FUNCTION_EXP);
      pTmpNode2->addChild(pChild->deepCopy());
      pTmpNode->addChild(pTmpNode2);
      pTmpNode2 = new ASTNode(AST_FUNCTION_EXP);
      ASTNode* pTmpNode3 = new ASTNode(AST_MINUS);
      pTmpNode3->addChild(pChild->deepCopy());
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode->addChild(pTmpNode2);
      pResult->addChild(pTmpNode);
      pTmpNode = new ASTNode(AST_INTEGER);
      pTmpNode->setValue(2);
      pResult->addChild(pTmpNode);
    }
  return pResult;
}

/**
 * This function replaces a call to COSH by (e^X+e^(-X))/2
 */
ASTNode* replace_COSH(const ASTNode* pChild)
{
  ASTNode* pResult = NULL;
  if (pChild != NULL)
    {
      pResult = new ASTNode(AST_DIVIDE);
      ASTNode* pTmpNode = new ASTNode(AST_PLUS);
      ASTNode* pTmpNode2 = new ASTNode(AST_FUNCTION_EXP);
      pTmpNode2->addChild(pChild->deepCopy());
      pTmpNode->addChild(pTmpNode2);
      pTmpNode2 = new ASTNode(AST_FUNCTION_EXP);
      ASTNode* pTmpNode3 = new ASTNode(AST_MINUS);
      pTmpNode3->addChild(pChild->deepCopy());
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode->addChild(pTmpNode2);
      pResult->addChild(pTmpNode);
      pTmpNode = new ASTNode(AST_INTEGER);
      pTmpNode->setValue(2);
      pResult->addChild(pTmpNode);
    }
  return pResult;
}

/**
 * This function replaces a call to TANH by (e^X-e^(-X))/(e^X+e^(-X))
 */
ASTNode* replace_TANH(const ASTNode* pChild)
{
  ASTNode* pResult = NULL;
  if (pChild != NULL)
    {
      pResult = new ASTNode(AST_DIVIDE);
      ASTNode* pTmpNode = new ASTNode(AST_MINUS);
      ASTNode* pTmpNode2 = new ASTNode(AST_FUNCTION_EXP);
      pTmpNode2->addChild(pChild->deepCopy());
      pTmpNode->addChild(pTmpNode2);
      pTmpNode2 = new ASTNode(AST_FUNCTION_EXP);
      ASTNode* pTmpNode3 = new ASTNode(AST_MINUS);
      pTmpNode3->addChild(pChild->deepCopy());
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode->addChild(pTmpNode2);
      pResult->addChild(pTmpNode);
      pTmpNode = new ASTNode(AST_PLUS);
      pTmpNode2 = new ASTNode(AST_FUNCTION_EXP);
      pTmpNode2->addChild(pChild->deepCopy());
      pTmpNode->addChild(pTmpNode2);
      pTmpNode2 = new ASTNode(AST_FUNCTION_EXP);
      pTmpNode3 = new ASTNode(AST_MINUS);
      pTmpNode3->addChild(pChild->deepCopy());
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode->addChild(pTmpNode2);
      pResult->addChild(pTmpNode);
    }
  return pResult;
}

/**
 * This function replaces a call to SECH by 2/(e^X+e^(-X))
 */
ASTNode* replace_SECH(const ASTNode* pChild)
{
  ASTNode* pResult = NULL;
  if (pChild != NULL)
    {
      pResult = new ASTNode(AST_DIVIDE);
      ASTNode* pTmpNode = new ASTNode(AST_INTEGER);
      pTmpNode->setValue(2);
      pResult->addChild(pTmpNode);
      pTmpNode = new ASTNode(AST_PLUS);
      ASTNode* pTmpNode2 = new ASTNode(AST_FUNCTION_EXP);
      pTmpNode2->addChild(pChild->deepCopy());
      pTmpNode->addChild(pTmpNode2);
      pTmpNode2 = new ASTNode(AST_FUNCTION_EXP);
      ASTNode* pTmpNode3 = new ASTNode(AST_MINUS);
      pTmpNode3->addChild(pChild->deepCopy());
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode->addChild(pTmpNode2);
      pResult->addChild(pTmpNode);
    }
  return pResult;
}

/**
 * This function replaces a call to CSCH by 2/(e^X-e^(-X))
 */
ASTNode* replace_CSCH(const ASTNode* pChild)
{
  ASTNode* pResult = NULL;
  if (pChild != NULL)
    {
      pResult = new ASTNode(AST_DIVIDE);
      ASTNode* pTmpNode = new ASTNode(AST_INTEGER);
      pTmpNode->setValue(2);
      pResult->addChild(pTmpNode);
      pTmpNode = new ASTNode(AST_MINUS);
      ASTNode* pTmpNode2 = new ASTNode(AST_FUNCTION_EXP);
      pTmpNode2->addChild(pChild->deepCopy());
      pTmpNode->addChild(pTmpNode2);
      pTmpNode2 = new ASTNode(AST_FUNCTION_EXP);
      ASTNode* pTmpNode3 = new ASTNode(AST_MINUS);
      pTmpNode3->addChild(pChild->deepCopy());
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode->addChild(pTmpNode2);
      pResult->addChild(pTmpNode);
    }
  return pResult;
}

/**
 * This function replaces a call to COTH by (e^X+e^(-X))/(e^X-e^(-X))
 */
ASTNode* replace_COTH(const ASTNode* pChild)
{
  ASTNode* pResult = NULL;
  if (pChild != NULL)
    {
      pResult = new ASTNode(AST_DIVIDE);
      ASTNode* pTmpNode = new ASTNode(AST_PLUS);
      ASTNode* pTmpNode2 = new ASTNode(AST_FUNCTION_EXP);
      pTmpNode2->addChild(pChild->deepCopy());
      pTmpNode->addChild(pTmpNode2);
      pTmpNode2 = new ASTNode(AST_FUNCTION_EXP);
      ASTNode* pTmpNode3 = new ASTNode(AST_MINUS);
      pTmpNode3->addChild(pChild->deepCopy());
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode->addChild(pTmpNode2);
      pResult->addChild(pTmpNode);
      pTmpNode = new ASTNode(AST_MINUS);
      pTmpNode2 = new ASTNode(AST_FUNCTION_EXP);
      pTmpNode2->addChild(pChild->deepCopy());
      pTmpNode->addChild(pTmpNode2);
      pTmpNode2 = new ASTNode(AST_FUNCTION_EXP);
      pTmpNode3 = new ASTNode(AST_MINUS);
      pTmpNode3->addChild(pChild->deepCopy());
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode->addChild(pTmpNode2);
      pResult->addChild(pTmpNode);
    }
  return pResult;
}

/**
 * This function replaces a call to ARCSINH by log(X + sqrt(X^2 + 1))
 */
ASTNode* replace_ARCSINH(const ASTNode* pChild)
{
  ASTNode* pResult = NULL;
  if (pChild != NULL)
    {
      pResult = new ASTNode(AST_FUNCTION_LOG);
      ASTNode* pTmpNode = new ASTNode(AST_PLUS);
      pTmpNode->addChild(pChild->deepCopy());
      ASTNode* pTmpNode2 = new ASTNode(AST_FUNCTION_POWER);
      ASTNode* pTmpNode3 = new ASTNode(AST_PLUS);
      ASTNode* pTmpNode4 = new ASTNode(AST_FUNCTION_POWER);
      pTmpNode4->addChild(pChild->deepCopy());
      ASTNode* pTmpNode5 = new ASTNode(AST_INTEGER);
      pTmpNode5->setValue(2);
      pTmpNode4->addChild(pTmpNode5);
      pTmpNode3->addChild(pTmpNode4);
      pTmpNode4 = new ASTNode(AST_INTEGER);
      pTmpNode4->setValue(1);
      pTmpNode3->addChild(pTmpNode4);
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode3 = new ASTNode(AST_REAL);
      pTmpNode3->setValue(0.5);
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode->addChild(pTmpNode2);
      pResult->addChild(pTmpNode);
    }
  return pResult;
}

/**
 * This function replaces a call to ARCCOSH by log(X + sqrt(X-1) * sqrt(X+1))
 */
ASTNode* replace_ARCCOSH(const ASTNode* pChild)
{
  ASTNode* pResult = NULL;
  if (pChild != NULL)
    {
      pResult = new ASTNode(AST_FUNCTION_LOG);
      ASTNode* pTmpNode = new ASTNode(AST_PLUS);
      pTmpNode->addChild(pChild->deepCopy());
      ASTNode* pTmpNode2 = new ASTNode(AST_TIMES);
      ASTNode* pTmpNode3 = new ASTNode(AST_FUNCTION_POWER);
      ASTNode* pTmpNode4 = new ASTNode(AST_MINUS);
      pTmpNode4->addChild(pChild->deepCopy());
      ASTNode* pTmpNode5 = new ASTNode(AST_INTEGER);
      pTmpNode5->setValue(1);
      pTmpNode4->addChild(pTmpNode5);
      pTmpNode3->addChild(pTmpNode4);
      pTmpNode4 = new ASTNode(AST_REAL);
      pTmpNode4->setValue(0.5);
      pTmpNode3->addChild(pTmpNode4);
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode3 = new ASTNode(AST_FUNCTION_POWER);
      pTmpNode4 = new ASTNode(AST_PLUS);
      pTmpNode4->addChild(pChild->deepCopy());
      pTmpNode5 = new ASTNode(AST_INTEGER);
      pTmpNode5->setValue(1);
      pTmpNode4->addChild(pTmpNode5);
      pTmpNode3->addChild(pTmpNode4);
      pTmpNode4 = new ASTNode(AST_REAL);
      pTmpNode4->setValue(0.5);
      pTmpNode3->addChild(pTmpNode4);
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode->addChild(pTmpNode2);
      pResult->addChild(pTmpNode);
    }
  return pResult;
}

/**
 * This function replaces a call to ARCTANH by 1/2 * (log(1+X) - log(1-X))
 */
ASTNode* replace_ARCTANH(const ASTNode* pChild)
{
  ASTNode* pResult = NULL;
  if (pChild != NULL)
    {
      pResult = new ASTNode(AST_TIMES);
      ASTNode* pTmpNode = new ASTNode(AST_RATIONAL);
      pTmpNode->setValue((long)1, (long)2);
      pResult->addChild(pTmpNode);
      pTmpNode = new ASTNode(AST_MINUS);
      ASTNode* pTmpNode2 = new ASTNode(AST_FUNCTION_LOG);
      ASTNode* pTmpNode3 = new ASTNode(AST_PLUS);
      ASTNode* pTmpNode4 = new ASTNode(AST_INTEGER);
      pTmpNode4->setValue(1);;
      pTmpNode3->addChild(pTmpNode4);
      pTmpNode3->addChild(pChild->deepCopy());
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode->addChild(pTmpNode2);
      pTmpNode2 = new ASTNode(AST_FUNCTION_LOG);
      pTmpNode3 = new ASTNode(AST_MINUS);
      pTmpNode4 = new ASTNode(AST_INTEGER);
      pTmpNode4->setValue(1);;
      pTmpNode3->addChild(pTmpNode4);
      pTmpNode3->addChild(pChild->deepCopy());
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode->addChild(pTmpNode2);
      pResult->addChild(pTmpNode);
    }
  return pResult;
}

/**
 * This function replaces a call to ARCSECH by log(sqrt((1/X)-1) * sqrt(1+(1/X)) + 1/X)
 */
ASTNode* replace_ARCSECH(const ASTNode* pChild)
{
  ASTNode* pResult = NULL;
  if (pChild != NULL)
    {
      pResult = new ASTNode(AST_FUNCTION_LOG);
      ASTNode* pTmpNode = new ASTNode(AST_PLUS);
      ASTNode* pTmpNode2 = new ASTNode(AST_TIMES);
      ASTNode* pTmpNode3 = new ASTNode(AST_FUNCTION_POWER);
      ASTNode* pTmpNode4 = new ASTNode(AST_MINUS);
      ASTNode* pTmpNode5 = new ASTNode(AST_DIVIDE);
      ASTNode* pTmpNode6 = new ASTNode(AST_INTEGER);
      pTmpNode6->setValue(1);
      pTmpNode5->addChild(pTmpNode6);
      pTmpNode5->addChild(pChild->deepCopy());
      pTmpNode4->addChild(pTmpNode5);
      pTmpNode5 = new ASTNode(AST_INTEGER);
      pTmpNode5->setValue(1);
      pTmpNode4->addChild(pTmpNode5);
      pTmpNode3->addChild(pTmpNode4);
      pTmpNode4 = new ASTNode(AST_REAL);
      pTmpNode4->setValue(0.5);
      pTmpNode3->addChild(pTmpNode4);
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode3 = new ASTNode(AST_FUNCTION_POWER);
      pTmpNode4 = new ASTNode(AST_PLUS);
      pTmpNode5 = new ASTNode(AST_INTEGER);
      pTmpNode5->setValue(1);
      pTmpNode4->addChild(pTmpNode5);
      pTmpNode5 = new ASTNode(AST_DIVIDE);
      pTmpNode6 = new ASTNode(AST_INTEGER);
      pTmpNode6->setValue(1);
      pTmpNode5->addChild(pTmpNode6);
      pTmpNode5->addChild(pChild->deepCopy());
      pTmpNode4->addChild(pTmpNode5);
      pTmpNode3->addChild(pTmpNode4);
      pTmpNode4 = new ASTNode(AST_REAL);
      pTmpNode4->setValue(0.5);
      pTmpNode3->addChild(pTmpNode4);
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode->addChild(pTmpNode2);
      pTmpNode2 = new ASTNode(AST_DIVIDE);
      pTmpNode3 = new ASTNode(AST_INTEGER);
      pTmpNode3->setValue(1);
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode2->addChild(pChild->deepCopy());
      pTmpNode->addChild(pTmpNode2);
      pResult->addChild(pTmpNode);
    }
  return pResult;
}

/**
 * This function replaces a call to ARCCSCH by log(sqrt(1+ (1/ (X^2)))+(1/X))
 */
ASTNode* replace_ARCCSCH(const ASTNode* pChild)
{
  ASTNode* pResult = NULL;
  if (pChild != NULL)
    {
      pResult = new ASTNode(AST_FUNCTION_LOG);
      ASTNode* pTmpNode = new ASTNode(AST_PLUS);
      ASTNode* pTmpNode2 = new ASTNode(AST_FUNCTION_POWER);
      ASTNode* pTmpNode3 = new ASTNode(AST_PLUS);
      ASTNode* pTmpNode4 = new ASTNode(AST_INTEGER);
      pTmpNode4->setValue(1);
      pTmpNode3->addChild(pTmpNode4);
      pTmpNode4 = new ASTNode(AST_DIVIDE);
      ASTNode* pTmpNode5 = new ASTNode(AST_INTEGER);
      pTmpNode5->setValue(1);
      pTmpNode4->addChild(pTmpNode5);
      pTmpNode5 = new ASTNode(AST_FUNCTION_POWER);
      pTmpNode5->addChild(pChild->deepCopy());
      ASTNode* pTmpNode6 = new ASTNode(AST_INTEGER);
      pTmpNode6->setValue(2);
      pTmpNode5->addChild(pTmpNode6);
      pTmpNode4->addChild(pTmpNode5);
      pTmpNode3->addChild(pTmpNode4);
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode->addChild(pTmpNode2);
      pTmpNode2 = new ASTNode(AST_DIVIDE);
      pTmpNode3 = new ASTNode(AST_INTEGER);
      pTmpNode3->setValue(1);
      pTmpNode2->addChild(pTmpNode3);
      pTmpNode2->addChild(pChild->deepCopy());
      pTmpNode->addChild(pTmpNode2);
      pResult->addChild(pTmpNode);
    }
  return pResult;
}
