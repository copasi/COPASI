// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CEvaluationNodeNormalizer.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/11/13 15:30:16 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CEvaluationNodeNormalizer.h"

#include <sstream>
#include <algorithm>
#include <cmath>

#include "copasi.h"
#include "utilities/CCopasiNode.h"
#include "function/CEvaluationNodeNumber.h"
#include "function/CEvaluationNodeConstant.h"
#include "function/CEvaluationNodeObject.h"
#include "function/CEvaluationNodeFunction.h"
#include "function/CEvaluationNodeCall.h"
#include "function/CEvaluationNodeStructure.h"
#include "function/CEvaluationNodeChoice.h"
#include "function/CEvaluationNodeVariable.h"
#include "function/CEvaluationNodeLogical.h"
#include "function/CEvaluationNodeVector.h"
#include "function/CEvaluationNodeWhiteSpace.h"

const double CEvaluationNodeNormalizer::ZERO = 1e-100;

CEvaluationNode* CEvaluationNodeNormalizer::normalize(const CEvaluationNode* pNode)
{

  CEvaluationNode* pResult = NULL;
  if (pNode != NULL)
    {
      switch (CEvaluationNode::type(pNode->getType()))
        {
        case CEvaluationNode::INVALID:
          break;
        case CEvaluationNode::NUMBER:
          pResult = normalizeCEvaluationNodeNumber(dynamic_cast<const CEvaluationNodeNumber*>(pNode));
          break;
        case CEvaluationNode::CONSTANT:
          pResult = normalizeCEvaluationNodeConstant(dynamic_cast<const CEvaluationNodeConstant*>(pNode));
          break;
        case CEvaluationNode::OPERATOR:
          pResult = normalizeCEvaluationNodeOperator(dynamic_cast<const CEvaluationNodeOperator*>(pNode));
          break;
        case CEvaluationNode::OBJECT:
          pResult = normalizeCEvaluationNodeObject(dynamic_cast<const CEvaluationNodeObject*>(pNode));
          break;
        case CEvaluationNode::FUNCTION:
          pResult = normalizeCEvaluationNodeFunction(dynamic_cast<const CEvaluationNodeFunction*>(pNode));
          break;
        case CEvaluationNode::CALL:
          pResult = normalizeCEvaluationNodeCall(dynamic_cast<const CEvaluationNodeCall*>(pNode));
          break;
        case CEvaluationNode::STRUCTURE:
          pResult = normalizeCEvaluationNodeStructure(dynamic_cast<const CEvaluationNodeStructure*>(pNode));
          break;
        case CEvaluationNode::CHOICE:
          pResult = normalizeCEvaluationNodeChoice(dynamic_cast<const CEvaluationNodeChoice*>(pNode));
          break;
        case CEvaluationNode::VARIABLE:
          pResult = normalizeCEvaluationNodeVariable(dynamic_cast<const CEvaluationNodeVariable*>(pNode));
          break;
        case CEvaluationNode::WHITESPACE:
          pResult = normalizeCEvaluationNodeWhiteSpace(dynamic_cast<const CEvaluationNodeWhiteSpace*>(pNode));
          break;
        case CEvaluationNode::LOGICAL:
          pResult = normalizeCEvaluationNodeLogical(dynamic_cast<const CEvaluationNodeLogical*>(pNode));
          break;
        case CEvaluationNode::MV_FUNCTION:
          break;
        case CEvaluationNode::VECTOR:
          pResult = normalizeCEvaluationNodeVector(dynamic_cast<const CEvaluationNodeVector*>(pNode));
          break;
        }
    }
  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeNumber(const CEvaluationNodeNumber* pNode)
{
  CEvaluationNode* pResult = NULL;
  if (pNode != NULL)
    {
      // copy the node
      pResult = new CEvaluationNodeNumber(*pNode);
    }
  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeConstant(const CEvaluationNodeConstant* pNode)
{
  CEvaluationNode* pResult = NULL;
  if (pNode != NULL)
    {
      // copy the node
      pResult = new CEvaluationNodeConstant(*pNode);
    }
  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeOperator(const CEvaluationNodeOperator* pNode)
{
  CEvaluationNode* pResult = NULL;
  if (pNode != NULL)
    {
      switch ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pNode->getType()))
        {
        case CEvaluationNodeOperator::INVALID:
          break;
        case CEvaluationNodeOperator::POWER:
          pResult = CEvaluationNodeNormalizer::normalizePowerNode(pNode);
          break;
        case CEvaluationNodeOperator::MULTIPLY:
          pResult = CEvaluationNodeNormalizer::normalizeMultiplyNode(pNode);
          break;
        case CEvaluationNodeOperator::DIVIDE:
          pResult = CEvaluationNodeNormalizer::normalizeDivideNode(pNode);
          break;
        case CEvaluationNodeOperator::MODULUS:
          pResult = CEvaluationNodeNormalizer::normalizeModulusNode(pNode);
          break;
        case CEvaluationNodeOperator::PLUS:
          pResult = CEvaluationNodeNormalizer::normalizePlusNode(pNode);
          break;
        case CEvaluationNodeOperator::MINUS:
          pResult = CEvaluationNodeNormalizer::normalizeMinusNode(pNode);
          break;
        }
    }
  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeObject(const CEvaluationNodeObject* pNode)
{
  CEvaluationNode* pResult = NULL;
  if (pNode != NULL)
    {
      // copy the node
      pResult = new CEvaluationNodeObject(*pNode);
    }
  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeFunction(const CEvaluationNodeFunction* pNode)
{
  CEvaluationNode* pResult = NULL;
  if (pNode != NULL)
    {
      CEvaluationNode* pTmpResult;
      switch ((CEvaluationNodeFunction::SubType)CEvaluationNode::subType(pNode->getType()))
        {
        case CEvaluationNodeFunction::INVALID:
          break;
        case CEvaluationNodeFunction::LOG:
        case CEvaluationNodeFunction::LOG10:
        case CEvaluationNodeFunction::EXP:
        case CEvaluationNodeFunction::SIN:
        case CEvaluationNodeFunction::COS:
        case CEvaluationNodeFunction::TAN:
        case CEvaluationNodeFunction::SEC:
        case CEvaluationNodeFunction::CSC:
        case CEvaluationNodeFunction::COT:
        case CEvaluationNodeFunction::SINH:
        case CEvaluationNodeFunction::COSH:
        case CEvaluationNodeFunction::TANH:
        case CEvaluationNodeFunction::SECH:
        case CEvaluationNodeFunction::CSCH:
        case CEvaluationNodeFunction::COTH:
        case CEvaluationNodeFunction::ARCSIN:
        case CEvaluationNodeFunction::ARCCOS:
        case CEvaluationNodeFunction::ARCTAN:
        case CEvaluationNodeFunction::ARCSEC:
        case CEvaluationNodeFunction::ARCCSC:
        case CEvaluationNodeFunction::ARCCOT:
        case CEvaluationNodeFunction::ARCSINH:
        case CEvaluationNodeFunction::ARCCOSH:
        case CEvaluationNodeFunction::ARCTANH:
        case CEvaluationNodeFunction::ARCSECH:
        case CEvaluationNodeFunction::ARCCSCH:
        case CEvaluationNodeFunction::ARCCOTH:
        case CEvaluationNodeFunction::SQRT:
        case CEvaluationNodeFunction::ABS:
        case CEvaluationNodeFunction::FLOOR:
        case CEvaluationNodeFunction::CEIL:
        case CEvaluationNodeFunction::FACTORIAL:
        case CEvaluationNodeFunction::NOT:
        case CEvaluationNodeFunction::MINUS:
          pResult = new CEvaluationNodeFunction((CEvaluationNodeFunction::SubType)CEvaluationNode::subType(pNode->getType()), "");
          pTmpResult = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
          if (pTmpResult != NULL)
            {
              pResult->addChild(pTmpResult);
            }
          else
            {
              delete pResult;
              pResult = NULL;
            }
          break;
        case CEvaluationNodeFunction::RUNIFORM:
        case CEvaluationNodeFunction::RNORMAL:
          // normalize all children
          pResult = new CEvaluationNodeFunction((CEvaluationNodeFunction::SubType)CEvaluationNode::subType(pNode->getType()), "");
          pTmpResult = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
          if (pTmpResult != NULL)
            {
              pResult->addChild(pTmpResult);
              pTmpResult = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));
              if (pTmpResult != NULL)
                {
                  pResult->addChild(pTmpResult);
                }
              else
                {
                  delete pResult;
                  pResult = NULL;
                }
            }
          else
            {
              delete pResult;
              pResult = NULL;
            }
          break;
          /*
          case CEvaluationNodeFunction::MINUS:
              // relace the - by a multiplication with -1
              // !!! Maybe this is not possible since CEvaluationNodeNumber
              // elements can not hold negative numbers.
              pResult=new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY,"");
          */
        case CEvaluationNodeFunction::PLUS:
          // eliminate the plus
          pResult = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
          break;
        }
    }
  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeCall(const CEvaluationNodeCall* pNode)
{
  CEvaluationNodeCall* pResult = NULL;
  if (pNode != NULL)
    {
      CEvaluationNode* pTmpResult = NULL;
      CCopasiNode<std::string>* pTmpNode = NULL;
      switch ((CEvaluationNodeCall::SubType)CEvaluationNode::subType(pNode->getType()))
        {
        case CEvaluationNodeCall::INVALID:
          break;
        case CEvaluationNodeCall::EXPRESSION:
        case CEvaluationNodeCall::FUNCTION:
          pResult = new CEvaluationNodeCall(*pNode);
          // remove all call nodes
          while (!pResult->getListOfChildNodes().empty())
            {
              pResult->removeChild(pResult->getChild());
            }
          // add normalized call nodes
          const std::vector<CEvaluationNode*>& callNodes = pNode->getListOfChildNodes();
          std::vector<CEvaluationNode*>::const_iterator it = callNodes.begin(), endit = callNodes.end();
          while (it != endit)
            {
              pTmpResult = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(*it));
              if (pTmpResult != NULL)
                {
                  pResult->addChild(pTmpResult);
                }
              else
                {
                  // delete all newly created call nodes
                  while (!pResult->getListOfChildNodes().empty())
                    {
                      pTmpNode = pResult->getChild();
                      pResult->removeChild(pTmpNode);
                      delete pTmpNode;
                    }
                  delete pResult;
                  pResult = NULL;
                  break;
                }
              ++it;
            }
          break;
        }
    }
  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeStructure(const CEvaluationNodeStructure* pNode)
{
  CEvaluationNode* pResult = NULL;
  if (pNode != NULL)
    {
      // copy the node
      pResult = new CEvaluationNodeStructure(*pNode);
    }
  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeChoice(const CEvaluationNodeChoice* pNode)
{
  CEvaluationNodeChoice* pResult = NULL;
  CEvaluationNode* pTmpResult;
  if (pNode != NULL)
    {
      switch ((CEvaluationNodeChoice::SubType)CEvaluationNode::type(pNode->getType()))
        {
        case CEvaluationNodeChoice::INVALID:
          break;
        case CEvaluationNodeChoice::IF:
          // create a new choice node with normalized if, true and false
          // elements
          pResult = new CEvaluationNodeChoice(CEvaluationNodeChoice::IF, "");
          // if element
          pTmpResult = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
          if (pTmpResult != NULL)
            {
              pResult->addChild(pTmpResult);
              // true element
              pTmpResult = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));
              if (pTmpResult != NULL)
                {
                  pResult->addChild(pTmpResult);
                  // false element
                  pTmpResult = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()->getSibling()));
                  if (pTmpResult != NULL)
                    {
                      pResult->addChild(pTmpResult);
                    }
                  else
                    {
                      delete pResult;
                      pResult = NULL;
                    }
                }
              else
                {
                  delete pResult;
                  pResult = NULL;
                }
            }
          else
            {
              delete pResult;
              pResult = NULL;
            }
        }
    }
  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeVariable(const CEvaluationNodeVariable* pNode)
{
  CEvaluationNode* pResult = NULL;
  if (pNode != NULL)
    {
      // copy the node
      pResult = new CEvaluationNodeVariable(*pNode);
    }
  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeLogical(const CEvaluationNodeLogical* pNode)
{
  CEvaluationNodeLogical* pResult = NULL;
  CEvaluationNode* pTmpResult = NULL;
  if (pNode != NULL)
    {
      switch ((CEvaluationNodeLogical::SubType)CEvaluationNode::subType(pNode->getType()))
        {
        case CEvaluationNodeLogical::INVALID:
          break;
        case CEvaluationNodeLogical::OR:
        case CEvaluationNodeLogical::XOR:
        case CEvaluationNodeLogical::AND:
        case CEvaluationNodeLogical::EQ:
        case CEvaluationNodeLogical::NE:
        case CEvaluationNodeLogical::LT:
        case CEvaluationNodeLogical::LE:
          pResult = new CEvaluationNodeLogical((CEvaluationNodeLogical::SubType)CEvaluationNode::subType(pNode->getType()), "");
          pTmpResult = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
          if (pTmpResult != NULL)
            {
              pResult->addChild(pTmpResult);
              pTmpResult = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));
              if (pTmpResult != NULL)
                {
                  pResult->addChild(pTmpResult);
                }
              else
                {
                  delete pResult;
                  pResult = NULL;
                }
            }
          else
            {
              delete pResult;
              pResult = NULL;
            }
          break;
        case CEvaluationNodeLogical::GT:
          // turn the order of the operands and change to LT
          pResult = new CEvaluationNodeLogical(CEvaluationNodeLogical::LT, "");
          pTmpResult = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));
          if (pTmpResult != NULL)
            {
              pResult->addChild(pTmpResult);
              pTmpResult = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
              if (pTmpResult != NULL)
                {
                  pResult->addChild(pTmpResult);
                }
              else
                {
                  delete pResult;
                  pResult = NULL;
                }
            }
          else
            {
              delete pResult;
              pResult = NULL;
            }
          break;
        case CEvaluationNodeLogical::GE:
          // turn the order of the operands and change to LE
          pResult = new CEvaluationNodeLogical(CEvaluationNodeLogical::LE, "");
          pTmpResult = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));
          if (pTmpResult != NULL)
            {
              pResult->addChild(pTmpResult);
              pTmpResult = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
              if (pTmpResult != NULL)
                {
                  pResult->addChild(pTmpResult);
                }
              else
                {
                  delete pResult;
                  pResult = NULL;
                }
            }
          else
            {
              delete pResult;
              pResult = NULL;
            }
          break;
        }
    }
  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeWhiteSpace(const CEvaluationNodeWhiteSpace* pNode)
{
  CEvaluationNode* pResult = NULL;
  if (pNode != NULL)
    {
      // copy node
      pResult = new CEvaluationNodeWhiteSpace(*pNode);
    }
  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeVector(const CEvaluationNodeVector* pNode)
{
  CEvaluationNodeVector* pResult = NULL;
  CEvaluationNode* pTmpResult;
  if (pNode != NULL)
    {
      const std::vector<CEvaluationNode*>* pItems;
      std::vector<CEvaluationNode*>::const_iterator it, endit;
      switch ((CEvaluationNodeVector::SubType)CEvaluationNode::subType(pNode->getType()))
        {
        case CEvaluationNodeVector::VECTOR:
          // create a new vector with normalized forms of all children
          pResult = new CEvaluationNodeVector();
          pItems = &pNode->getVector();
          it = pItems->begin();
          endit = pItems->end();
          while (it != endit)
            {
              pTmpResult = CEvaluationNodeNormalizer::normalize(*it);
              if (pTmpResult != NULL)
                {
                  if (!pResult->addChild(pTmpResult))
                    {
                      delete pResult;
                      pResult = NULL;
                      break;
                    }
                }
              else
                {
                  delete pResult;
                  pResult = NULL;
                  break;
                }
              ++it;
            }
          break;
        case CEvaluationNodeVector::INVALID:
          break;
        }
    }
  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizePowerNode(const CEvaluationNodeOperator* pNode)
{
  CEvaluationNode* pResult;
  if (pNode != NULL)
    {
      const CEvaluationNode* pChild1 = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
      if (pChild1 != NULL)
        {
          const CEvaluationNode* pChild2 = dynamic_cast<const CEvaluationNode*>(pChild1->getSibling());
          if (pChild2 != NULL)
            {
              if (CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::NUMBER)
                {
                  if (pChild2->value() - 1.0 < ZERO)
                    {
                      // replace it with the first child
                      pResult = CEvaluationNodeNormalizer::normalize(pChild1);
                    }
                  else if (pChild2->value() < ZERO)
                    {
                      // replace it by a number node of 1
                      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "1");
                    }
                }
              else
                {
                  pResult = new CEvaluationNodeOperator(CEvaluationNodeOperator::POWER, "");
                  CEvaluationNode* pTmpResult = CEvaluationNodeNormalizer::normalize(pChild1);
                  if (pTmpResult != NULL)
                    {
                      pResult->addChild(pTmpResult);
                      pTmpResult = CEvaluationNodeNormalizer::normalize(pChild2);
                      if (pTmpResult != NULL)
                        {
                          pResult->addChild(pTmpResult);
                        }
                      else
                        {
                          delete pResult;
                          pResult = NULL;
                        }
                    }
                  else
                    {
                      delete pResult;
                      pResult = NULL;
                    }
                }
            }
        }
    }
  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeMultiplyNode(const CEvaluationNodeOperator* pNode)
{
  CEvaluationNode* pResult = NULL;
  if (pNode != NULL)
    {
      CEvaluationNode* pChild1 = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
      if (pChild1 != NULL)
        {
          CEvaluationNode* pChild2 = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pChild1->getSibling()));
          if (pChild2 != NULL)
            {
              // if one of the child nodes is zero, replace the node with a number
              // node of value 0

              // if one of the nodes is a number node of 1, replace the node by the
              // other child
              if (CEvaluationNode::type(pChild1->getType()) == CEvaluationNode::NUMBER)
                {
                  if (std::abs(pChild1->value() - 1.0) < ZERO)
                    {
                      pResult = pChild2;
                      // to save some work in the second if clause below
                      // we set pChild2 to its normalized form
                      pChild2 = pResult;
                    }
                  else if (std::abs(pChild1->value()) < ZERO)
                    {
                      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "0");
                      // we are done
                      pChild2 = NULL;
                    }
                }
              if (pChild2 != NULL && CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::NUMBER)
                {
                  if (std::abs(pChild2->value() - 1.0) < ZERO)
                    {
                      pResult = pChild1;
                      pChild1 = pResult;
                    }
                  else if (std::abs(pChild2->value()) < ZERO)
                    {
                      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "0");
                      // we are done
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }
              if (!pResult)
                {
                  pResult = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
                  pResult->addChild(pChild1);
                  pResult->addChild(pChild2);
                }
              if (pResult->getType() == CEvaluationNode::OPERATOR && pChild2 != NULL) // if pChild2 is NULL, the node was replace by a number node with value 0
                {
                  // multiply all number nodes in a multiplication chain
                  std::vector<CEvaluationNode*> chainNodes;
                  findChainNodes(dynamic_cast<CEvaluationNodeOperator*>(pResult), chainNodes);
                  CEvaluationNodeNormalizer::eliminateMultipleNumbers((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pResult->getType()), chainNodes);
                  // replace multiplication of identical items by a power node with the
                  // correct power
                  CEvaluationNodeNormalizer::collectIdenticalBranches((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pResult->getType()), chainNodes);
                  // reorder nodes again
                  CEvaluationNodeNormalizer::reorderNodes(chainNodes);
                  // rebuild pResult;
                  CEvaluationNodeOperator::SubType subType = (CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pResult->getType());
                  delete pResult;
                  pResult = CEvaluationNodeNormalizer::buildOperatorBranchFromChain(subType, chainNodes);
                }
            }
        }
    }
  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizePlusNode(const CEvaluationNodeOperator* pNode)
{
  CEvaluationNode* pResult = NULL;
  if (pNode != NULL)
    {
      CEvaluationNode* pChild1 = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
      if (pChild1 != NULL)
        {
          CEvaluationNode* pChild2 = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pChild1->getSibling()));
          if (pChild2 != NULL)
            {
              // if one of the nodes is a number node of 0, replace the node by the
              // other child
              if (CEvaluationNode::type(pChild1->getType()) == CEvaluationNode::NUMBER)
                {
                  if (std::abs(pChild1->value()) < ZERO)
                    {
                      pResult = pChild2;
                      // to save some work in the second if clause below
                      // we set pChild2 to its normalized form
                      pChild2 = pResult;
                    }
                }
              if (pChild2 != NULL && CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::NUMBER)
                {
                  if (std::abs(pChild2->value()) < ZERO)
                    {
                      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "0");
                      // we are done
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }
              if (!pResult)
                {
                  pResult = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "+");
                  pResult->addChild(pChild1);
                  pResult->addChild(pChild2);
                }
              if (pResult->getType() == CEvaluationNode::OPERATOR && pChild2 != NULL) // if pChild2 is NULL, the node was replace by a number node with value 0
                {
                  // add all number nodes in a summation chain
                  std::vector<CEvaluationNode*> chainNodes;
                  findChainNodes(dynamic_cast<CEvaluationNodeOperator*>(pResult), chainNodes);
                  CEvaluationNodeNormalizer::eliminateMultipleNumbers((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pResult->getType()), chainNodes);
                  // replace addition of identical items by a multiplication node with the
                  // correct number
                  CEvaluationNodeNormalizer::collectIdenticalBranches((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pResult->getType()), chainNodes);
                  // reorder nodes again
                  CEvaluationNodeNormalizer::reorderNodes(chainNodes);
                  // rebuild pResult;
                  CEvaluationNodeOperator::SubType subType = (CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pResult->getType());
                  delete pResult;
                  pResult = CEvaluationNodeNormalizer::buildOperatorBranchFromChain(subType, chainNodes);
                }
            }
        }
    }
  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeDivideNode(const CEvaluationNodeOperator* pNode)
{
  CEvaluationNode* pResult = NULL;
  if (pNode != NULL)
    {
      CEvaluationNode* pChild1 = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
      if (pChild1 != NULL)
        {
          CEvaluationNode* pChild2 = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pChild1->getSibling()));
          if (pChild2 != NULL)
            {
              if (CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::NUMBER)
                {
                  // eliminate divisions by 1
                  if (std::abs(pChild2->value() - 1.0) < ZERO)
                    {
                      pResult = pChild1;
                    }
                  else if (CEvaluationNode::type(pChild1->getType()) == CEvaluationNode::NUMBER)
                    {
                      // if both children are numbers, do the calculation
                      std::ostringstream os;
                      os << pChild1->value() / pChild2->value();
                      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, os.str());
                    }
                }
              else
                {
                  // try to shorten numerator and denominator
                  // TODO find out if a factor is involved
                  if (*pChild1 == *pChild2)
                    {
                      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");
                    }
                }
            }
        }
    }
  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeModulusNode(const CEvaluationNodeOperator* pNode)
{
  CEvaluationNode* pResult = NULL;
  if (pNode != NULL)
    {
      CEvaluationNode* pChild1 = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
      if (pChild1 != NULL)
        {
          CEvaluationNode* pChild2 = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pChild1->getSibling()));
          if (pChild2 != NULL)
            {
              if (CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::NUMBER)
                {
                  // eliminate modulus 1
                  if (std::abs(pChild2->value() - 1.0) < ZERO)
                    {
                      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "0");
                    }
                  else if (CEvaluationNode::type(pChild1->getType()) == CEvaluationNode::NUMBER &&
                           (CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pChild1->getType()) == CEvaluationNodeNumber::INTEGER &&
                           (CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pChild2->getType()) == CEvaluationNodeNumber::INTEGER)
                    {
                      // if both children are numbers, do the calculation
                      std::ostringstream os;
                      os << (long)pChild1->value() % (long)pChild2->value();
                      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, os.str());
                    }
                }
              else
                {
                  // try to shorten numerator and denominator
                  // TODO find out if a factor is involved
                  if (*pChild1 == *pChild2)
                    {
                      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "0");
                    }
                }
            }
        }
    }
  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeMinusNode(const CEvaluationNodeOperator* pNode)
{
  CEvaluationNode* pResult = NULL;
  if (pNode != NULL)
    {
      CEvaluationNode* pChild1 = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
      if (pChild1 != NULL)
        {
          CEvaluationNode* pChild2 = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pChild1->getSibling()));
          if (pChild2 != NULL)
            {
              if (CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::NUMBER)
                {
                  // eliminate subtraction of 0
                  if (std::abs(pChild2->value()) < ZERO)
                    {
                      pResult = pChild1;
                    }
                  else if (CEvaluationNode::type(pChild1->getType()) == CEvaluationNode::NUMBER)
                    {
                      // if both children are numbers, do the calculation
                      std::ostringstream os;
                      os << pChild1->value() - pChild2->value();
                      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, os.str());
                    }
                }
              else
                {
                  // TODO find out if a factor is involved
                  if (*pChild1 == *pChild2)
                    {
                      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.0");
                    }
                }
            }
        }
    }
  return pResult;
}

bool CEvaluationNodeNormalizer::eliminateMultipleNumbers(CEvaluationNodeOperator::SubType subType, std::vector<CEvaluationNode*>& chainNodes)
{
  // check if there are several numerical values in the operator chain and
  // evaluate those operations
  bool changed = false;
  if (chainNodes.size() > 1)
    {
      std::vector<CEvaluationNode*>::iterator it = chainNodes.begin(), endit = chainNodes.end();
      if (subType == CEvaluationNodeOperator::MULTIPLY || subType == CEvaluationNodeOperator::PLUS)
        {

          double value = (subType == CEvaluationNodeOperator::MULTIPLY) ? 1.0 : 0.0;
          CEvaluationNodeNumber* pNumberNode = NULL;
          std::vector<CEvaluationNode*> numbers;
          while (it != endit)
            {
              pNumberNode = dynamic_cast<CEvaluationNodeNumber*>(*it);
              if (pNumberNode != NULL)
                {
                  numbers.push_back(pNumberNode);
                  if (subType == CEvaluationNodeOperator::MULTIPLY)
                    {
                      value *= pNumberNode->value();
                    }
                  else
                    {
                      value += pNumberNode->value();
                    }
                }
              ++it;
            }
          if (numbers.size() > 1)
            {
              changed = true;
              it = numbers.begin(), endit = numbers.end();
              --endit;
              while (it != endit)
                {
                  chainNodes.erase(std::find(chainNodes.begin(), chainNodes.end(), *it));
                  delete *it;
                  ++it;
                }
              std::ostringstream os;
              os << value;
              (*it)->setData(os.str());
              chainNodes.push_back(*it);
            }
        }
    }
  return changed;
}

void CEvaluationNodeNormalizer::findChainNodes(CEvaluationNodeOperator* pNode, std::vector<CEvaluationNode*>& nodes)
{
  CEvaluationNodeOperator::SubType subType = (CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pNode->getType());
  CEvaluationNode* pChild1 = dynamic_cast<CEvaluationNode*>(pNode->getChild());
  if (pChild1 != NULL)
    {
      CEvaluationNode* pChild2 = dynamic_cast<CEvaluationNode*>(pChild1->getSibling());
      if (pChild2 != NULL)
        {
          if (CEvaluationNode::type(pChild1->getType()) == CEvaluationNode::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild1->getType())) == subType)
            {
              findChainNodes(dynamic_cast<CEvaluationNodeOperator*>(pChild1), nodes);
            }
          else
            {
              nodes.push_back(pChild1->copyBranch());
            }
          if (CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild2->getType())) == subType)
            {
              findChainNodes(dynamic_cast<CEvaluationNodeOperator*>(pChild2), nodes);
            }
          else
            {
              nodes.push_back(pChild2->copyBranch());
            }
        }
    }
}

CEvaluationNodeOperator* CEvaluationNodeNormalizer::buildOperatorBranchFromChain(CEvaluationNodeOperator::SubType subType, const std::vector<CEvaluationNode*>& chainNodes)
{
  CEvaluationNodeOperator* pResult = NULL;
  if (chainNodes.size() > 1)
    {
      std::vector<CEvaluationNode*>::const_reverse_iterator it = chainNodes.rbegin(), endit = chainNodes.rend();
      CEvaluationNodeOperator* pTmpOperator = new CEvaluationNodeOperator(subType, "");
      // add the first child
      pTmpOperator->addChild(*it);
      ++it;
      --endit;
      while (it != endit)
        {
          pTmpOperator->addChild(*it);
          pResult = new CEvaluationNodeOperator(subType, "");
          pResult->addChild(pTmpOperator);
          pTmpOperator = pResult;
          ++it;
        }
      // add the last child
      pResult->addChild(*it);
    }
  return pResult;
}

bool CEvaluationNodeNormalizer::collectIdenticalBranches(CEvaluationNodeOperator::SubType subType, std::vector<CEvaluationNode*>& chainNodes)
{
  bool changed = false;
  if (chainNodes.size() > 1)
    {
      // what is done depends on the subtype
      // if it is an additon we replace identical nodes with a multiplication of
      // the node with the number of occurences
      // for a multiplication it's the same, but we use a power instead of a
      // multiplication
      // for a subtraction and a division, we have to watch the order of the
      // operands
      if (subType == CEvaluationNodeOperator::MULTIPLY || subType == CEvaluationNodeOperator::PLUS)
        {
          CEvaluationNodeOperator* pOperation = (subType == CEvaluationNodeOperator::MULTIPLY) ? new CEvaluationNodeOperator(CEvaluationNodeOperator::POWER, "^") : new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
          std::vector<CEvaluationNode*>::iterator it = chainNodes.begin(), endit = chainNodes.end();
          std::map<CEvaluationNode, unsigned int> occurenceMap;
          while (it != endit)
            {
              std::map<CEvaluationNode, unsigned int>::iterator pos = occurenceMap.find(**it);
              if (pos == occurenceMap.end())
                {
                  occurenceMap[**it] = 1;
                }
              else
                {
                  ++(pos->second);
                  changed = true;
                }
              // delete the node
              delete (*it);
              ++it;
            }
          chainNodes.clear();
          // convert the contents of the occurenceMap to new nodes
          std::map<CEvaluationNode, unsigned int>::const_iterator mapIt = occurenceMap.begin(), mapEndit = occurenceMap.end();
          std::ostringstream os;
          while (mapIt != mapEndit)
            {
              os << mapIt->second;
              CEvaluationNodeNumber* pNumberNode = new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, os.str());
              CEvaluationNodeOperator* pNewOperator = new CEvaluationNodeOperator(*pOperation);
              pNewOperator->addChild(pNumberNode);
              pNewOperator->addChild(mapIt->first.copyBranch());
              chainNodes.push_back(pNewOperator);
              os.str("");
              ++mapIt;
            }
          delete pOperation;
        }
    }
  return changed;
}

bool CEvaluationNodeNormalizer::reorderNodes(std::vector<CEvaluationNode*>& chainNodes)
{
  std::sort(chainNodes.begin(), chainNodes.end(), lessCEvaluationNodes());
  return true;
}
