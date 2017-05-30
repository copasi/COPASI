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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include <sbml/math/ASTNode.h>
#include <sbml/Model.h>
#include <sbml/FunctionDefinition.h>

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
#include "CNormalTranslation.h"
#include "ConvertToCEvaluationNode.h"
#include "copasi/utilities/CCopasiTree.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/function/CFunction.h"
#include "copasi/function/CFunctionParameters.h"
#include "copasi/function/CFunctionParameter.h"
#include "copasi/function/CEvaluationTree.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationNodeObject.h"
#include "copasi/sbml/ConverterASTNode.h"
#include "copasi/model/CChemEq.h"
#include "copasi/model/CChemEqElement.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CModelValue.h"
#include "copasi/utilities/CCopasiParameter.h"
#include "copasi/CopasiDataModel/CDataModel.h"

/**
 * Creates an expanded expression from the given expression.
 * This method expands all function calls.
 * On failure NULL is returned, otherwise an expanded copy of the original node
 * is returned.
 */
ASTNode* create_expression(const ASTNode* pSource, const ListOfFunctionDefinitions* pFunctions)
{
  // expand all function calls
  ASTNode* pResult = expand_function_calls(pSource, pFunctions);
  return pResult;
}

/**
 * This method expands the function calls in the given expression.
 * On failure NULL is returned, otherwise a copy of the original node
 * is returned where all function calls have been expanded.
 */
ASTNode* expand_function_calls(const ASTNode* pNode, const ListOfFunctionDefinitions* pFunctions)
{
  ASTNode* pResult = NULL;

  if (pNode->getType() == AST_FUNCTION)
    {
      pResult = expand_function_call(pNode, pFunctions);

      if (pResult == NULL)
        {
          return NULL;
        }

      ASTNode* pTmp = expand_function_calls(pResult, pFunctions);

      if (pTmp == NULL)
        {
          delete pResult;
          return NULL;
        }

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
          pNewChild = expand_function_calls(pChild, pFunctions);

          if (pNewChild == NULL)
            {
              delete pResult;
              pResult = NULL;
              break;
            }

          pResult->addChild(pNewChild);
          ++i;
        }
    }

  return pResult;
}

/**
 * This method expands the given function call.
 * On failure NULL is returned, otherwise on expression of the expanded
 * function call is returned.
 */
ASTNode* expand_function_call(const ASTNode* pCall, const ListOfFunctionDefinitions* pFunctions)
{
  // find the function that belongs to the call
  const FunctionDefinition * pFunctionDefinition = pFunctions->get(pCall->getName());
  ASTNode* pResult = NULL;

  if (pFunctionDefinition == NULL) return NULL;

  // create the mapping
  unsigned int iMax = pFunctionDefinition->getNumArguments();

  if (pFunctionDefinition != NULL && iMax == pCall->getNumChildren())
    {
      // map the first function argument to the first child in the call etc.
      std::map<std::string, const ASTNode*> argumentMap;
      unsigned int i = 0;

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

/**
 * This method takes two normalforms and normalizes the variable names in both
 * expressions.
 * Afterwards the two expressions are compared. If they are equal true is
 * returned.
 */
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

/**
 * This method normalizes the variable names in a given normalform expression.
 * The first variable found in the expression is named "variable1", the second
 * "variable2" and so on.
 */
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
          delete(*it2);
          ++it2;
        }
    }
}

/**
 * This method converts a given ASTNode into a CNormalFraction.
 * The expression is simplified in the process to create the "final"
 * normalform.
 */
CNormalFraction* create_simplified_normalform(const ASTNode* pSource)
{
  CNormalFraction* pFraction = NULL;
  // translate the ASTNode based tree into an CEvaluationNode based tree and
  CEvaluationNode* pEvaluationNode = CEvaluationTree::fromAST(pSource, false);
  // all variable nodes in this tree are objects nodes so we have to convert
  // them
  CCopasiTree<CEvaluationNode>::iterator treeIt = pEvaluationNode;

  // if the root node already is an object node, this has to be dealt with separately
  if (dynamic_cast<CEvaluationNodeObject*>(&(*treeIt)))
    {
      CEvaluationNodeVariable* pVariableNode = new CEvaluationNodeVariable(CEvaluationNode::SubType::DEFAULT, (*treeIt).getData().substr(1, (*treeIt).getData().length() - 2));
      delete pEvaluationNode;
      pEvaluationNode = pVariableNode;
    }
  else
    {
      while (treeIt != NULL)
        {
          if (dynamic_cast<CEvaluationNodeObject*>(&(*treeIt)))
            {
              CEvaluationNodeVariable* pVariableNode = new CEvaluationNodeVariable(CEvaluationNode::SubType::DEFAULT, (*treeIt).getData().substr(1, (*treeIt).getData().length() - 2));

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
      pFraction = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(pEvaluationNode));
      delete pEvaluationNode;
    }

  return pFraction;
}

/**
 * This method converts a given ASTNode into a CNormalFraction.
 * The resulting normalform is not necessarily simplified.
 */
CNormalFraction* create_normalform(const ASTNode* pSource)
{
  CNormalFraction* pFraction = NULL;
  // translate the ASTNode based tree into an CEvaluationNode based tree and
  CEvaluationNode* pEvaluationNode = CEvaluationTree::fromAST(pSource, false);
  // all variable nodes in this tree are objects nodes so we have to convert
  // them
  CCopasiTree<CEvaluationNode>::iterator treeIt = pEvaluationNode;

  // if the root node already is an object node, this has to be dealt with separately
  if (dynamic_cast<CEvaluationNodeObject*>(&(*treeIt)))
    {
      CEvaluationNodeVariable* pVariableNode = new CEvaluationNodeVariable(CEvaluationNode::SubType::DEFAULT, (*treeIt).getData().substr(1, (*treeIt).getData().length() - 2));
      delete pEvaluationNode;
      pEvaluationNode = pVariableNode;
    }
  else
    {
      while (treeIt != NULL)
        {
          if (dynamic_cast<CEvaluationNodeObject*>(&(*treeIt)))
            {
              CEvaluationNodeVariable* pVariableNode = new CEvaluationNodeVariable(CEvaluationNode::SubType::DEFAULT, (*treeIt).getData().substr(1, (*treeIt).getData().length() - 2));

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

/**
 * This method expands the function calls in the given expression.
 * On failure NULL is returned, otherwise a copy of the original node
 * is returned where all function calls have been expanded.
 */
CEvaluationNode* expand_function_calls(const CEvaluationNode* pNode, CFunctionDB* pFunctionDB)
{
  CEvaluationNode* pResult = NULL;
  const CEvaluationNodeCall* pCall = dynamic_cast<const CEvaluationNodeCall*>(pNode);

  if (pCall != NULL)
    {
      pResult = expand_function_call(pCall, pFunctionDB);

      if (pResult == NULL)
        {
          return NULL;
        }

      CEvaluationNode* pTmp = expand_function_calls(pResult, pFunctionDB);

      if (pTmp == NULL)
        {
          delete pResult;
          return NULL;
        }

      delete pResult;
      pResult = pTmp;
    }
  else
    {
      // only make a shallow copy
      std::vector<CEvaluationNode*> v;
      pResult = pNode->copyNode(v);
      const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
      CEvaluationNode* pNewChild = NULL;

      while (pChild != NULL)
        {
          pNewChild = expand_function_calls(pChild, pFunctionDB);

          if (pNewChild == NULL)
            {
              delete pResult;
              pResult = NULL;
              break;
            }

          pResult->addChild(pNewChild);
          pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
        }
    }

  return pResult;
}

/**
 * This method expands the given function call.
 * On failure NULL is returned, otherwise on expression of the expanded
 * function call is returned.
 */
CEvaluationNode* expand_function_call(const CEvaluationNodeCall* pCall, CFunctionDB* pFunctionDB)
{
  // find the function that belongs to the call
  CEvaluationNode* pResult = NULL;
  const CEvaluationTree* pTree = pFunctionDB->findFunction(pCall->getData());

  if (pTree != NULL)
    {
      const CFunction* pFunctionDefinition = dynamic_cast<const CFunction*>(pTree);
      // create the mapping
      assert(pFunctionDefinition != NULL);
      const CFunctionParameters& functionParameters = pFunctionDefinition->getVariables();
      unsigned int i, iMax = functionParameters.size();
      // map the first function argument to the first child in the call etc.
      std::map<std::string, const CEvaluationNode*> argumentMap;
      i = 0;
      const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pCall->getChild());

      while (i < iMax)
        {
          assert(pChild != NULL);
          argumentMap[functionParameters[i]->getObjectName()] = pChild;
          pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
          ++i;
        }

      // create the resulting tree
      pResult = pFunctionDefinition->getRoot()->copyBranch();
      CEvaluationNode* pTmpNode = replace_variable_names(pResult, argumentMap);
      assert(pTmpNode != NULL);
      delete pResult;
      assert(pChild == NULL);
      pResult = pTmpNode;
    }

  return pResult;
}

CEvaluationNode* replace_variable_names(const CEvaluationNode* pNode, const std::map<std::string, const CEvaluationNode*>& argumentMap)
{
  CEvaluationNode* pResult = NULL;

  if (dynamic_cast<const CEvaluationNodeVariable*>(pNode) != NULL)
    {
      std::map<std::string, const CEvaluationNode*>::const_iterator pos = argumentMap.find(pNode->getData());

      if (pos != argumentMap.end())
        {
          pResult = pos->second->copyBranch();
        }
    }
  else
    {
      // only make a shallow copy
      std::vector<CEvaluationNode*> v;
      pResult = pNode->copyNode(v);
      const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
      CEvaluationNode* pNewChild = NULL;

      while (pChild != NULL)
        {
          pNewChild = replace_variable_names(pChild, argumentMap);
          assert(pNewChild != NULL);
          pResult->addChild(pNewChild);
          pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
        }
    }

  return pResult;
}

bool is_mass_action(const CNormalFraction* pFrac, const CModel* pModel, const CChemEq* pChemEq)
{
  bool result = true;

  // all objects must be valid and the denominator of the fraction must be one
  if (pFrac != NULL && pModel != NULL && pChemEq != NULL && pFrac->checkDenominatorOne())
    {
      const CNormalSum* pNumerator = &pFrac->getNumerator();

      if (pNumerator != NULL && pNumerator->getFractions().empty())
        {
          // the numerator has to have either one element if the reaction
          // is irreversible or two if the reaction is reversible
          if ((pChemEq->getReversibility() == true && pNumerator->getProducts().size() == 2) || pNumerator->getProducts().size() == 1)
            {
              // if the reaction is reversible we have to find out which element
              // contains the substrates and which contains the products
              const CNormalProduct* pSubstrates = NULL;

              if (pChemEq->getReversibility() == true)
                {
                  const CNormalProduct* pProducts = NULL;
                  C_FLOAT64 factor1 = (*pNumerator->getProducts().begin())->getFactor();
                  C_FLOAT64 factor2 = (*(++(pNumerator->getProducts().begin())))->getFactor();

                  if (fabs(factor1 + 1.0) < 1e-23 && fabs(factor2 - 1.0) < 1e-23)
                    {
                      pProducts = *pNumerator->getProducts().begin();
                      pSubstrates = *(++(pNumerator->getProducts().begin()));
                    }
                  else if (fabs(factor1 - 1.0) < 1e-23 && fabs(factor2 + 1.0) < 1e-23)
                    {
                      pSubstrates = *pNumerator->getProducts().begin();
                      pProducts = *(++(pNumerator->getProducts().begin()));
                    }

                  if (pProducts != NULL)
                    {
                      result = contains_necessary_mass_action_elements(pChemEq->getProducts(), pProducts, pModel);
                    }
                  else
                    {
                      result = false;
                    }
                }
              else
                {
                  if (fabs((*pNumerator->getProducts().begin())->getFactor() - 1.0) < 1e-23)
                    {
                      pSubstrates = *pNumerator->getProducts().begin();
                    }
                  else
                    {
                      result = false;
                    }
                }

              if (result == true && pSubstrates != NULL)
                {
                  // check if pSubstrates constains a product
                  // that consists of all the substrates of the reaction with the correct
                  // exponents
                  // as well as some parameter
                  result = contains_necessary_mass_action_elements(pChemEq->getSubstrates(), pSubstrates, pModel);
                }
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}

bool contains_necessary_mass_action_elements(const CDataVector<CChemEqElement>& elements, const CNormalProduct* pProduct, const CModel* pModel)
{
  // check if pProducts contains a product
  // that consists of all the products of the reaction with the correct
  // exponents
  // as well as some parameter
  bool result = true;

  if (pModel != NULL && pProduct != NULL && elements.size() > 0)
    {
      const CDataObject* pObject = NULL;
      const CNormalItem* pItem = NULL;
      const CMetab* pMetab = NULL;
      const CDataModel* pDatamodel = dynamic_cast<const CDataModel*>(pModel->getObjectParent());
      assert(pDatamodel != NULL);
      CObjectInterface::ContainerList listOfContainers;
      listOfContainers.push_back(const_cast<CModel*>(pModel));

      CDataVector<CChemEqElement> tmpV(elements, NO_PARENT);

      std::vector<const CDataObject*> tmpObjects;
      const std::set<CNormalItemPower*, compareItemPowers >& itemPowers = pProduct->getItemPowers();
      std::set <CNormalItemPower*, compareItemPowers >::const_iterator iit = itemPowers.begin(), iendit = itemPowers.end();

      while (iit != iendit && result != false)
        {

          // check that the item is an instance of CNormalItem with type VARIABLE
          // and that the variable corresponds to the common name of one of the
          // products
          // check if iit has the correct exponent
          if ((*iit)->getItemType() == CNormalItemPower::ITEM)
            {
              pItem = dynamic_cast<const CNormalItem*>(&(*iit)->getItem());

              if (pItem != NULL && pItem->getType() == CNormalItem::VARIABLE)
                {
                  std::string cn = pItem->getName();
                  pObject = CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(listOfContainers, cn));

                  if (pObject != NULL)
                    {
                      if (pObject->hasFlag(CDataObject::Reference))
                        {
                          pObject = pObject->getObjectParent();
                          assert(pObject != NULL);
                        }

                      pMetab = dynamic_cast<const CMetab*>(pObject);

                      if (pMetab != NULL)
                        {
                          CDataVector<CChemEqElement>::iterator tmpVIt = tmpV.begin(), tmpVEndit = tmpV.end();

                          while (tmpVIt != tmpVEndit)
                            {
                              // check if we have found the metab and if the exponent is correct
                              if (pMetab == tmpVIt->getMetabolite() && fabs(tmpVIt->getMultiplicity() - (*iit)->getExp()) < 1e-23)
                                {
                                  // delete the item from tmpV
                                  tmpV.remove(tmpVIt);
                                  break;
                                }

                              ++tmpVIt;
                            }
                        }
                      else
                        {
                          // the exponent has to be 1
                          if (fabs((*iit)->getExp() - 1.0) < 1e-23)
                            {
                              tmpObjects.push_back(pObject);
                            }
                          else
                            {
                              result = false;
                            }
                        }
                    }
                  else
                    {
                      result = false;
                    }
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }

          ++iit;
        }

      // only the entry for the parameter should be left in tmpV
      if (tmpV.size() == 0 && tmpObjects.size() == 1)
        {
          // check if the item is a local or global parameter
          if (!(dynamic_cast<const CModelValue*>(tmpObjects[0]) || dynamic_cast<const CCopasiParameter*>(tmpObjects[0])))
            {
              result = false;
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}
