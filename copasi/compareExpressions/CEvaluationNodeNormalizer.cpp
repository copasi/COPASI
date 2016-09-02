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
      switch (pNode->mainType())
        {
          case CEvaluationNode::T_INVALID:
            break;

          case CEvaluationNode::T_NUMBER:
            pResult = normalizeCEvaluationNodeNumber(dynamic_cast<const CEvaluationNodeNumber*>(pNode));
            break;

          case CEvaluationNode::T_CONSTANT:
            pResult = normalizeCEvaluationNodeConstant(dynamic_cast<const CEvaluationNodeConstant*>(pNode));
            break;

          case CEvaluationNode::T_DELAY:
            pResult = normalizeCEvaluationNodeDelay(dynamic_cast<const CEvaluationNodeDelay*>(pNode));
            break;

          case CEvaluationNode::T_OPERATOR:
            pResult = normalizeCEvaluationNodeOperator(dynamic_cast<const CEvaluationNodeOperator*>(pNode));
            break;

          case CEvaluationNode::T_OBJECT:
            pResult = normalizeCEvaluationNodeObject(dynamic_cast<const CEvaluationNodeObject*>(pNode));
            break;

          case CEvaluationNode::T_FUNCTION:
            pResult = normalizeCEvaluationNodeFunction(dynamic_cast<const CEvaluationNodeFunction*>(pNode));
            break;

          case CEvaluationNode::T_CALL:
            pResult = normalizeCEvaluationNodeCall(dynamic_cast<const CEvaluationNodeCall*>(pNode));
            break;

          case CEvaluationNode::T_STRUCTURE:
            pResult = normalizeCEvaluationNodeStructure(dynamic_cast<const CEvaluationNodeStructure*>(pNode));
            break;

          case CEvaluationNode::T_CHOICE:
            pResult = normalizeCEvaluationNodeChoice(dynamic_cast<const CEvaluationNodeChoice*>(pNode));
            break;

          case CEvaluationNode::T_VARIABLE:
            pResult = normalizeCEvaluationNodeVariable(dynamic_cast<const CEvaluationNodeVariable*>(pNode));
            break;

          case CEvaluationNode::T_WHITESPACE:
            pResult = normalizeCEvaluationNodeWhiteSpace(dynamic_cast<const CEvaluationNodeWhiteSpace*>(pNode));
            break;

          case CEvaluationNode::T_LOGICAL:
            pResult = normalizeCEvaluationNodeLogical(dynamic_cast<const CEvaluationNodeLogical*>(pNode));
            break;

          case CEvaluationNode::T_MV_FUNCTION:
            break;

          case CEvaluationNode::T_VECTOR:
            pResult = normalizeCEvaluationNodeVector(dynamic_cast<const CEvaluationNodeVector*>(pNode));
            break;
        }

      if (pResult == NULL) pResult = pNode->copyBranch();
    }

  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeNumber(const CEvaluationNodeNumber* pNode)
{
  CEvaluationNode* pResult = NULL;

  if (pNode != NULL)
    {
      // copy the node
      pResult = pNode->copyBranch();
    }

  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeConstant(const CEvaluationNodeConstant* pNode)
{
  CEvaluationNode* pResult = NULL;

  if (pNode != NULL)
    {
      // copy the node
      pResult = pNode->copyBranch();
    }

  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeOperator(const CEvaluationNodeOperator* pNode)
{
  CEvaluationNode* pResult = NULL;

  if (pNode != NULL)
    {
      switch (pNode->subType())
        {
          case CEvaluationNode::S_INVALID:
            break;

          case CEvaluationNode::S_POWER:
            pResult = CEvaluationNodeNormalizer::normalizePowerNode(pNode);
            break;

          case CEvaluationNode::S_MULTIPLY:
            pResult = CEvaluationNodeNormalizer::normalizeMultiplyNode(pNode);
            break;

          case CEvaluationNode::S_DIVIDE:
            pResult = CEvaluationNodeNormalizer::normalizeDivideNode(pNode);
            break;

          case CEvaluationNode::S_MODULUS:
            pResult = CEvaluationNodeNormalizer::normalizeModulusNode(pNode);
            break;

          case CEvaluationNode::S_PLUS:
            pResult = CEvaluationNodeNormalizer::normalizePlusNode(pNode);
            break;

          case CEvaluationNode::S_MINUS:
            pResult = CEvaluationNodeNormalizer::normalizeMinusNode(pNode);
            break;
        }

      if (pResult == NULL) pResult = pNode->copyBranch();
    }

  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeObject(const CEvaluationNodeObject* pNode)
{
  CEvaluationNode* pResult = NULL;

  if (pNode != NULL)
    {
      // copy the node
      pResult = pNode->copyBranch();
    }

  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeFunction(const CEvaluationNodeFunction* pNode)
{
  CEvaluationNode* pResult = NULL;

  if (pNode != NULL)
    {
      CEvaluationNode* pTmpResult;

      switch (pNode->subType())
        {
          case CEvaluationNode::S_INVALID:
            break;

          case CEvaluationNode::S_LOG:
          case CEvaluationNode::S_LOG10:
          case CEvaluationNode::S_EXP:
          case CEvaluationNode::S_SIN:
          case CEvaluationNode::S_COS:
          case CEvaluationNode::S_TAN:
          case CEvaluationNode::S_SEC:
          case CEvaluationNode::S_CSC:
          case CEvaluationNode::S_COT:
          case CEvaluationNode::S_SINH:
          case CEvaluationNode::S_COSH:
          case CEvaluationNode::S_TANH:
          case CEvaluationNode::S_SECH:
          case CEvaluationNode::S_CSCH:
          case CEvaluationNode::S_COTH:
          case CEvaluationNode::S_ARCSIN:
          case CEvaluationNode::S_ARCCOS:
          case CEvaluationNode::S_ARCTAN:
          case CEvaluationNode::S_ARCSEC:
          case CEvaluationNode::S_ARCCSC:
          case CEvaluationNode::S_ARCCOT:
          case CEvaluationNode::S_ARCSINH:
          case CEvaluationNode::S_ARCCOSH:
          case CEvaluationNode::S_ARCTANH:
          case CEvaluationNode::S_ARCSECH:
          case CEvaluationNode::S_ARCCSCH:
          case CEvaluationNode::S_ARCCOTH:
          case CEvaluationNode::S_SQRT:
          case CEvaluationNode::S_ABS:
          case CEvaluationNode::S_FLOOR:
          case CEvaluationNode::S_CEIL:
          case CEvaluationNode::S_FACTORIAL:
          case CEvaluationNode::S_NOT:
          case CEvaluationNode::S_MINUS:
            pResult = new CEvaluationNodeFunction(pNode->subType(), pNode->getData());
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

          case CEvaluationNode::S_RUNIFORM:
          case CEvaluationNode::S_RNORMAL:
          case CEvaluationNode::S_MIN:
          case CEvaluationNode::S_MAX:
            //case CEvaluationNode::S_DELAY:
            // normalize all children
            pResult = new CEvaluationNodeFunction(pNode->subType(), pNode->getData());
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
            case CEvaluationNode::S_MINUS:
                // relace the - by a multiplication with -1
                // !!! Maybe this is not possible since CEvaluationNodeNumber
                // elements can not hold negative numbers.
                pResult=new CEvaluationNodeOperator(CEvaluationNode::S_MULTIPLY,"");
            */
          case CEvaluationNode::S_PLUS:
            // eliminate the plus
            pResult = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
            break;

          default: break;
        }

      if (pResult == NULL) pResult = pNode->copyBranch();
    }

  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeDelay(const CEvaluationNodeDelay* pNode)
{
  CEvaluationNodeDelay* pResult = NULL;

  if (pNode != NULL)
    {
      CEvaluationNode* pTmpResult = NULL;

      switch (pNode->subType())
        {
          case CEvaluationNode::S_INVALID:
            break;

          case CEvaluationNode::S_DELAY:
            pResult = new CEvaluationNodeDelay(pNode->subType(), pNode->getData());
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
        }

      if (pResult == NULL)
        {
          pResult = static_cast<CEvaluationNodeDelay*>(pNode->copyBranch());
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

      switch (pNode->subType())
        {
          case CEvaluationNode::S_INVALID:
            break;

          case CEvaluationNode::S_EXPRESSION:
          case CEvaluationNode::S_FUNCTION:
            pResult = dynamic_cast<CEvaluationNodeCall*>(CEvaluationNode::create(pNode->mainType(), pNode->subType(), pNode->getData()));
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

      if (pResult == NULL) pResult = static_cast<CEvaluationNodeCall*>(pNode->copyBranch());
    }

  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeStructure(const CEvaluationNodeStructure* pNode)
{
  CEvaluationNode* pResult = NULL;

  if (pNode != NULL)
    {
      // copy the node
      pResult = pNode->copyBranch();
    }

  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeChoice(const CEvaluationNodeChoice* pNode)
{
  CEvaluationNodeChoice* pResult = NULL;
  CEvaluationNode* pTmpResult;

  if (pNode != NULL)
    {
      switch (pNode->subType())
        {
          case CEvaluationNode::S_INVALID:
            break;

          case CEvaluationNode::S_IF:
            // create a new choice node with normalized if, true and false
            // elements
            pResult = new CEvaluationNodeChoice(CEvaluationNode::S_IF, "if");
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

      if (pResult == NULL) pResult = static_cast<CEvaluationNodeChoice*>(pNode->copyBranch());
    }

  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeVariable(const CEvaluationNodeVariable* pNode)
{
  CEvaluationNode* pResult = NULL;

  if (pNode != NULL)
    {
      // copy the node
      pResult = pNode->copyBranch();
    }

  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeLogical(const CEvaluationNodeLogical* pNode)
{
  CEvaluationNodeLogical* pResult = NULL;
  CEvaluationNode* pTmpResult = NULL;

  if (pNode != NULL)
    {
      switch (pNode->subType())
        {
          case CEvaluationNode::S_INVALID:
            break;

          case CEvaluationNode::S_OR:
          case CEvaluationNode::S_XOR:
          case CEvaluationNode::S_AND:
          case CEvaluationNode::S_EQ:
          case CEvaluationNode::S_NE:
          case CEvaluationNode::S_LT:
          case CEvaluationNode::S_LE:
            pResult = new CEvaluationNodeLogical(pNode->subType(), pNode->getData());
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

          case CEvaluationNode::S_GT:
            // turn the order of the operands and change to LT
            pResult = new CEvaluationNodeLogical(CEvaluationNode::S_LT, "<");
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

          case CEvaluationNode::S_GE:
            // turn the order of the operands and change to LE
            pResult = new CEvaluationNodeLogical(CEvaluationNode::S_LE, "<=");
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

      if (pResult == NULL) pResult = static_cast<CEvaluationNodeLogical*>(pNode->copyBranch());
    }

  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizeCEvaluationNodeWhiteSpace(const CEvaluationNodeWhiteSpace* pNode)
{
  CEvaluationNode* pResult = NULL;

  if (pNode != NULL)
    {
      // copy node
      pResult = pNode->copyBranch();
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

      switch (pNode->subType())
        {
          case CEvaluationNode::S_VECTOR:
            // create a new vector with normalized forms of all children
            pResult = new CEvaluationNodeVector();
            pItems = &pNode->getNodes();
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

          case CEvaluationNode::S_INVALID:
            break;
        }

      if (pResult == NULL) pResult = static_cast<CEvaluationNodeVector*>(pNode->copyBranch());
    }

  return pResult;
}

CEvaluationNode* CEvaluationNodeNormalizer::normalizePowerNode(const CEvaluationNodeOperator* pNode)
{
  CEvaluationNode* pResult = NULL;

  if (pNode != NULL)
    {
      CEvaluationNode* pChild1 = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));

      if (pChild1 != NULL)
        {
          CEvaluationNode* pChild2 = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));

          if (pChild2 != NULL)
            {
              if (pChild2->mainType() == CEvaluationNode::T_NUMBER)
                {
                  if (*pChild2->getValuePointer() - 1.0 < ZERO)
                    {
                      // replace it with the first child
                      pResult = pChild1;
                      delete pChild2;
                      pChild2 = NULL;
                    }
                  else if (*pChild2->getValuePointer() < ZERO)
                    {
                      // replace it by a number node of 1
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "1");
                      delete pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }
              else
                {
                  pResult = new CEvaluationNodeOperator(CEvaluationNode::S_POWER, "^");
                  pResult->addChild(pChild1);
                  pResult->addChild(pChild2);
                }
            }
        }

      if (pResult == NULL) pResult = pNode->copyBranch();
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
          CEvaluationNode* pChild2 = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));

          if (pChild2 != NULL)
            {
              // if one of the child nodes is zero, replace the node with a number
              // node of value 0

              // if one of the nodes is a number node of 1, replace the node by the
              // other child
              if (pChild1->mainType() == CEvaluationNode::T_NUMBER)
                {
                  if (fabs(*pChild1->getValuePointer() - 1.0) < ZERO)
                    {
                      pResult = pChild2;
                      delete pChild1;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                  else if (fabs(*pChild1->getValuePointer()) < ZERO)
                    {
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "0");
                      // we are done
                      delete pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }

              if (pChild2 && pChild2->mainType() == CEvaluationNode::T_NUMBER)
                {
                  if (fabs(*pChild2->getValuePointer() - 1.0) < ZERO)
                    {
                      pResult = pChild1;
                      delete pChild2;
                      pChild2 = NULL;
                      pChild1 = NULL;
                    }
                  else if (fabs(*pChild2->getValuePointer()) < ZERO)
                    {
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "0");
                      // we are done
                      delete pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }

              if (!pResult)
                {
                  pResult = new CEvaluationNodeOperator(CEvaluationNode::S_MULTIPLY, "*");
                  pResult->addChild(pChild1);
                  pResult->addChild(pChild2);
                }

              if (pResult->mainType() == CEvaluationNode::T_OPERATOR)
                {
                  // multiply all number nodes in a multiplication chain
                  std::vector<CEvaluationNode*> chainNodes;
                  findChainNodes(dynamic_cast<CEvaluationNodeOperator*>(pResult), chainNodes);
                  CEvaluationNodeNormalizer::eliminateMultipleNumbers(pResult->subType(), chainNodes);
                  // replace multiplication of identical items by a power node with the
                  // correct power
                  CEvaluationNodeNormalizer::collectIdenticalBranches(pResult->subType(), chainNodes);
                  // reorder nodes again
                  CEvaluationNodeNormalizer::reorderNodes(chainNodes);
                  // rebuild pResult;
                  CEvaluationNode::SubType subType = pResult->subType();
                  delete pResult;
                  pResult = CEvaluationNodeNormalizer::buildOperatorBranchFromChain(subType, chainNodes);
                }
            }
        }

      if (pResult == NULL) pResult = pNode->copyBranch();
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
          CEvaluationNode* pChild2 = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));

          if (pChild2 != NULL)
            {
              // if one of the nodes is a number node of 0, replace the node by the
              // other child
              if (pChild1->mainType() == CEvaluationNode::T_NUMBER)
                {
                  if (fabs(*pChild1->getValuePointer()) < ZERO)
                    {
                      pResult = pChild2;
                      delete pChild1;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }

              if (pChild2 != NULL && pChild2->mainType() == CEvaluationNode::T_NUMBER)
                {
                  if (fabs(*pChild2->getValuePointer()) < ZERO)
                    {
                      if (pChild2 != pResult)
                        {
                          pResult = pChild1;
                          delete pChild2;
                        }

                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }

              if (!pResult)
                {
                  pResult = new CEvaluationNodeOperator(CEvaluationNode::S_PLUS, "+");
                  pResult->addChild(pChild1);
                  pResult->addChild(pChild2);
                }

              if (pResult->mainType() == CEvaluationNode::T_OPERATOR)
                {
                  // add all number nodes in a summation chain
                  std::vector<CEvaluationNode*> chainNodes;
                  findChainNodes(dynamic_cast<CEvaluationNodeOperator*>(pResult), chainNodes);
                  CEvaluationNodeNormalizer::eliminateMultipleNumbers(pResult->subType(), chainNodes);
                  // replace addition of identical items by a multiplication node with the
                  // correct number
                  CEvaluationNodeNormalizer::collectIdenticalBranches(pResult->subType(), chainNodes);
                  // reorder nodes again
                  CEvaluationNodeNormalizer::reorderNodes(chainNodes);
                  // rebuild pResult;
                  CEvaluationNode::SubType subType = pResult->subType();
                  delete pResult;
                  pResult = CEvaluationNodeNormalizer::buildOperatorBranchFromChain(subType, chainNodes);
                }
            }
          else
            {
              delete pChild1;
              pChild1 = NULL;
            }
        }

      if (pResult == NULL) pResult = pNode->copyBranch();
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
          CEvaluationNode* pChild2 = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));

          if (pChild2 != NULL)
            {
              if (pChild2->mainType() == CEvaluationNode::T_NUMBER)
                {
                  // eliminate divisions by 1
                  if (fabs(*pChild2->getValuePointer() - 1.0) < ZERO)
                    {
                      pResult = pChild1;
                      delete pChild2;
                      pChild2 = NULL;
                    }
                  else if (pChild1->mainType() == CEvaluationNode::T_NUMBER)
                    {
                      // if both children are numbers, do the calculation
                      std::ostringstream os;
                      os << *pChild1->getValuePointer() / *pChild2->getValuePointer();
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::S_DOUBLE, os.str());
                      delete pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }
              else
                {
                  // try to shorten numerator and denominator
                  // TODO find out if a factor is involved
                  if (*pChild1 == *pChild2)
                    {
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::S_DOUBLE, "1.0");
                      delete pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }

              if (pResult == NULL)
                {
                  pResult = new CEvaluationNodeOperator(CEvaluationNode::S_DIVIDE, "/");
                  pResult->addChild(pChild1);
                  pResult->addChild(pChild2);
                }
            }
          else
            {
              delete pChild1;
              pChild1 = NULL;
            }
        }

      if (pResult == NULL) pResult = pNode->copyBranch();
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
          CEvaluationNode* pChild2 = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));

          if (pChild2 != NULL)
            {
              if (pChild2->mainType() == CEvaluationNode::T_NUMBER)
                {
                  // eliminate modulus 1
                  if (fabs(*pChild2->getValuePointer() - 1.0) < ZERO)
                    {
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "0");
                      delete pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                  else if (pChild1->mainType() == CEvaluationNode::T_NUMBER &&
                           pChild1->subType() == CEvaluationNode::S_INTEGER &&
                           pChild2->subType() == CEvaluationNode::S_INTEGER)
                    {
                      // if both children are numbers, do the calculation
                      std::ostringstream os;
                      os << (long)*pChild1->getValuePointer() % (long)*pChild2->getValuePointer();
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, os.str());
                      delete pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }
              else
                {
                  // try to shorten numerator and denominator
                  // TODO find out if a factor is involved
                  if (*pChild1 == *pChild2)
                    {
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "0");
                      delete pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }

              if (pResult == NULL)
                {
                  pResult = new CEvaluationNodeOperator(CEvaluationNode::S_MODULUS, "%");
                  pResult->addChild(pChild1);
                  pResult->addChild(pChild2);
                }
            }
          else
            {
              delete pChild1;
              pChild1 = NULL;
            }
        }

      if (pResult == NULL) pResult = pNode->copyBranch();
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
          CEvaluationNode* pChild2 = CEvaluationNodeNormalizer::normalize(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));

          if (pChild2 != NULL)
            {
              if (pChild2->mainType() == CEvaluationNode::T_NUMBER)
                {
                  // eliminate subtraction of 0
                  if (fabs(*pChild2->getValuePointer()) < ZERO)
                    {
                      pResult = pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                  else if (pChild1->mainType() == CEvaluationNode::T_NUMBER)
                    {
                      // if both children are numbers, do the calculation
                      std::ostringstream os;
                      os << *pChild1->getValuePointer() - *pChild2->getValuePointer();
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::S_DOUBLE, os.str());
                      delete pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }
              else
                {
                  // TODO find out if a factor is involved
                  if (*pChild1 == *pChild2)
                    {
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::S_DOUBLE, "0.0");
                      delete pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }

              if (pResult == NULL)
                {
                  pResult = new CEvaluationNodeOperator(CEvaluationNode::S_MINUS, "-");
                  pResult->addChild(pChild1);
                  pResult->addChild(pChild2);
                }
            }
          else
            {
              delete pChild1;
              pChild1 = NULL;
            }
        }

      if (pResult == NULL) pResult = pNode->copyBranch();
    }

  return pResult;
}

bool CEvaluationNodeNormalizer::eliminateMultipleNumbers(CEvaluationNode::SubType subType, std::vector<CEvaluationNode*>& chainNodes)
{
  // check if there are several numerical values in the operator chain and
  // evaluate those operations
  bool changed = false;

  if (chainNodes.size() > 1)
    {
      std::vector<CEvaluationNode*>::iterator it = chainNodes.begin(), endit = chainNodes.end();

      if (subType == CEvaluationNode::S_MULTIPLY || subType == CEvaluationNode::S_PLUS)
        {

          double value = (subType == CEvaluationNode::S_MULTIPLY) ? 1.0 : 0.0;
          CEvaluationNodeNumber* pNumberNode = NULL;
          std::vector<CEvaluationNode*> numbers;

          while (it != endit)
            {
              pNumberNode = dynamic_cast<CEvaluationNodeNumber*>(*it);

              if (pNumberNode != NULL)
                {
                  numbers.push_back(pNumberNode);

                  if (subType == CEvaluationNode::S_MULTIPLY)
                    {
                      value *= *pNumberNode->getValuePointer();
                    }
                  else
                    {
                      value += *pNumberNode->getValuePointer();
                    }
                }

              ++it;
            }

          if (numbers.size() > 1)
            {
              changed = true;
              it = numbers.begin(), endit = numbers.end();
              // don't delete the last one since we reset it's value
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
            }
        }
    }

  return changed;
}

void CEvaluationNodeNormalizer::findChainNodes(CEvaluationNodeOperator* pNode, std::vector<CEvaluationNode*>& nodes)
{
  CEvaluationNode::SubType subType = pNode->subType();
  CEvaluationNode* pChild1 = dynamic_cast<CEvaluationNode*>(pNode->getChild());

  if (pChild1 != NULL)
    {
      CEvaluationNode* pChild2 = dynamic_cast<CEvaluationNode*>(pChild1->getSibling());

      if (pChild2 != NULL)
        {
          if (pChild1->mainType() == CEvaluationNode::T_OPERATOR && pChild1->subType() == subType)
            {
              findChainNodes(dynamic_cast<CEvaluationNodeOperator*>(pChild1), nodes);
            }
          else
            {
              nodes.push_back(pChild1->copyBranch());
            }

          if (pChild2->mainType() == CEvaluationNode::T_OPERATOR && pChild2->subType() == subType)
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

CEvaluationNodeOperator* CEvaluationNodeNormalizer::buildOperatorBranchFromChain(CEvaluationNode::SubType subType, const std::vector<CEvaluationNode*>& chainNodes)
{
  CEvaluationNodeOperator* pResult = NULL;
  std::string data;

  switch (subType)
    {
      case CEvaluationNode::S_POWER:
        data = "^";
        break;

      case CEvaluationNode::S_MULTIPLY:
        data = "*";
        break;

      case CEvaluationNode::S_DIVIDE:
        data = "/";
        break;

      case CEvaluationNode::S_MODULUS:
        data = "%";
        break;

      case CEvaluationNode::S_PLUS:
        data = "+";
        break;

      case CEvaluationNode::S_MINUS:
        data = "-";
        break;

      default:
        fatalError();
        break;
    }

  if (chainNodes.size() > 1)
    {
      std::vector<CEvaluationNode*>::const_reverse_iterator it = chainNodes.rbegin(), endit = chainNodes.rend();
      CEvaluationNodeOperator* pTmpOperator = new CEvaluationNodeOperator(subType, data);
      // add the first child
      pTmpOperator->addChild(*it);
      ++it;
      --endit;

      while (it != endit)
        {
          pTmpOperator->addChild(*it);
          pResult = new CEvaluationNodeOperator(subType, data);
          pResult->addChild(pTmpOperator);
          pTmpOperator = pResult;
          ++it;
        }

      // add the last child
      pResult->addChild(*it);
    }

  return pResult;
}

bool CEvaluationNodeNormalizer::collectIdenticalBranches(CEvaluationNode::SubType subType, std::vector<CEvaluationNode*>& chainNodes)
{
  bool changed = false;

  if (chainNodes.size() > 1)
    {
      // what is done depends on the subtype
      // if it is an additon we replace identical nodes with a multiplication of
      // the node with the number of occurences
      // for a multiplication it's the same, but we use a power instead of a
      // multiplication
      if (subType == CEvaluationNode::S_MULTIPLY || subType == CEvaluationNode::S_PLUS)
        {
          CEvaluationNodeOperator* pOperation = (subType == CEvaluationNode::S_MULTIPLY) ? new CEvaluationNodeOperator(CEvaluationNode::S_POWER, "^") : new CEvaluationNodeOperator(CEvaluationNode::S_MULTIPLY, "*");
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
              delete(*it);
              ++it;
            }

          chainNodes.clear();
          // convert the contents of the occurenceMap to new nodes
          std::map<CEvaluationNode, unsigned int>::const_iterator mapIt = occurenceMap.begin(), mapEndit = occurenceMap.end();
          std::ostringstream os;

          while (mapIt != mapEndit)
            {
              os << mapIt->second;
              CEvaluationNodeNumber* pNumberNode = new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, os.str());
              CEvaluationNodeOperator* pNewOperator = dynamic_cast<CEvaluationNodeOperator*>(CEvaluationNode::create(pOperation->mainType(), pOperation->subType(), pOperation->getData()));
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
