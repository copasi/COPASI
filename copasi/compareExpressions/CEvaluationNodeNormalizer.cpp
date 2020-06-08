// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

#include "CEvaluationNodeNormalizer.h"

#include <sstream>
#include <algorithm>
#include <cmath>

#include "copasi/copasi.h"
#include "copasi/utilities/CCopasiNode.h"
#include "copasi/function/CEvaluationNodeNumber.h"
#include "copasi/function/CEvaluationNodeConstant.h"
#include "copasi/function/CEvaluationNodeObject.h"
#include "copasi/function/CEvaluationNodeFunction.h"
#include "copasi/function/CEvaluationNodeCall.h"
#include "copasi/function/CEvaluationNodeStructure.h"
#include "copasi/function/CEvaluationNodeChoice.h"
#include "copasi/function/CEvaluationNodeVariable.h"
#include "copasi/function/CEvaluationNodeLogical.h"
#include "copasi/function/CEvaluationNodeVector.h"
#include "copasi/function/CEvaluationNodeWhiteSpace.h"

const double CEvaluationNodeNormalizer::ZERO = 1e-100;

CEvaluationNode* CEvaluationNodeNormalizer::normalize(const CEvaluationNode* pNode)
{

  CEvaluationNode* pResult = NULL;

  if (pNode != NULL)
    {
      switch (pNode->mainType())
        {
          case CEvaluationNode::MainType::INVALID:
            break;

          case CEvaluationNode::MainType::NUMBER:
            pResult = normalizeCEvaluationNodeNumber(dynamic_cast<const CEvaluationNodeNumber*>(pNode));
            break;

          case CEvaluationNode::MainType::CONSTANT:
            pResult = normalizeCEvaluationNodeConstant(dynamic_cast<const CEvaluationNodeConstant*>(pNode));
            break;

          case CEvaluationNode::MainType::DELAY:
            pResult = normalizeCEvaluationNodeDelay(dynamic_cast<const CEvaluationNodeDelay*>(pNode));
            break;

          case CEvaluationNode::MainType::OPERATOR:
            pResult = normalizeCEvaluationNodeOperator(dynamic_cast<const CEvaluationNodeOperator*>(pNode));
            break;

          case CEvaluationNode::MainType::OBJECT:
            pResult = normalizeCEvaluationNodeObject(dynamic_cast<const CEvaluationNodeObject*>(pNode));
            break;

          case CEvaluationNode::MainType::FUNCTION:
            pResult = normalizeCEvaluationNodeFunction(dynamic_cast<const CEvaluationNodeFunction*>(pNode));
            break;

          case CEvaluationNode::MainType::CALL:
            pResult = normalizeCEvaluationNodeCall(dynamic_cast<const CEvaluationNodeCall*>(pNode));
            break;

          case CEvaluationNode::MainType::STRUCTURE:
            pResult = normalizeCEvaluationNodeStructure(dynamic_cast<const CEvaluationNodeStructure*>(pNode));
            break;

          case CEvaluationNode::MainType::CHOICE:
            pResult = normalizeCEvaluationNodeChoice(dynamic_cast<const CEvaluationNodeChoice*>(pNode));
            break;

          case CEvaluationNode::MainType::VARIABLE:
            pResult = normalizeCEvaluationNodeVariable(dynamic_cast<const CEvaluationNodeVariable*>(pNode));
            break;

          case CEvaluationNode::MainType::WHITESPACE:
            pResult = normalizeCEvaluationNodeWhiteSpace(dynamic_cast<const CEvaluationNodeWhiteSpace*>(pNode));
            break;

          case CEvaluationNode::MainType::LOGICAL:
            pResult = normalizeCEvaluationNodeLogical(dynamic_cast<const CEvaluationNodeLogical*>(pNode));
            break;

          case CEvaluationNode::MainType::MV_FUNCTION:
            break;

          case CEvaluationNode::MainType::VECTOR:
            pResult = normalizeCEvaluationNodeVector(dynamic_cast<const CEvaluationNodeVector*>(pNode));
            break;

          case CEvaluationNode::MainType::UNIT:
            break;

          case CEvaluationNode::MainType::__SIZE:
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
          case CEvaluationNode::SubType::INVALID:
            break;

          case CEvaluationNode::SubType::POWER:
            pResult = CEvaluationNodeNormalizer::normalizePowerNode(pNode);
            break;

          case CEvaluationNode::SubType::MULTIPLY:
            pResult = CEvaluationNodeNormalizer::normalizeMultiplyNode(pNode);
            break;

          case CEvaluationNode::SubType::DIVIDE:
            pResult = CEvaluationNodeNormalizer::normalizeDivideNode(pNode);
            break;

          case CEvaluationNode::SubType::MODULUS:
            pResult = CEvaluationNodeNormalizer::normalizeModulusNode(pNode);
            break;

          case CEvaluationNode::SubType::PLUS:
            pResult = CEvaluationNodeNormalizer::normalizePlusNode(pNode);
            break;

          case CEvaluationNode::SubType::MINUS:
            pResult = CEvaluationNodeNormalizer::normalizeMinusNode(pNode);
            break;

          default:
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
          case CEvaluationNode::SubType::INVALID:
            break;

          case CEvaluationNode::SubType::LOG:
          case CEvaluationNode::SubType::LOG10:
          case CEvaluationNode::SubType::EXP:
          case CEvaluationNode::SubType::SIN:
          case CEvaluationNode::SubType::COS:
          case CEvaluationNode::SubType::TAN:
          case CEvaluationNode::SubType::SEC:
          case CEvaluationNode::SubType::CSC:
          case CEvaluationNode::SubType::COT:
          case CEvaluationNode::SubType::SINH:
          case CEvaluationNode::SubType::COSH:
          case CEvaluationNode::SubType::TANH:
          case CEvaluationNode::SubType::SECH:
          case CEvaluationNode::SubType::CSCH:
          case CEvaluationNode::SubType::COTH:
          case CEvaluationNode::SubType::ARCSIN:
          case CEvaluationNode::SubType::ARCCOS:
          case CEvaluationNode::SubType::ARCTAN:
          case CEvaluationNode::SubType::ARCSEC:
          case CEvaluationNode::SubType::ARCCSC:
          case CEvaluationNode::SubType::ARCCOT:
          case CEvaluationNode::SubType::ARCSINH:
          case CEvaluationNode::SubType::ARCCOSH:
          case CEvaluationNode::SubType::ARCTANH:
          case CEvaluationNode::SubType::ARCSECH:
          case CEvaluationNode::SubType::ARCCSCH:
          case CEvaluationNode::SubType::ARCCOTH:
          case CEvaluationNode::SubType::SQRT:
          case CEvaluationNode::SubType::ABS:
          case CEvaluationNode::SubType::FLOOR:
          case CEvaluationNode::SubType::CEIL:
          case CEvaluationNode::SubType::FACTORIAL:
          case CEvaluationNode::SubType::NOT:
          case CEvaluationNode::SubType::MINUS:
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

          case CEvaluationNode::SubType::RUNIFORM:
          case CEvaluationNode::SubType::RNORMAL:
          case CEvaluationNode::SubType::MIN:
          case CEvaluationNode::SubType::MAX:
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
          case CEvaluationNode::SubType::PLUS:
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
          case CEvaluationNode::SubType::INVALID:
            break;

          case CEvaluationNode::SubType::DELAY:
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

          default:
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
          case CEvaluationNode::SubType::INVALID:
            break;

          case CEvaluationNode::SubType::EXPRESSION:
          case CEvaluationNode::SubType::FUNCTION:
          {
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
          }
          break;

          default:
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
          case CEvaluationNode::SubType::INVALID:
            break;

          case CEvaluationNode::SubType::IF:
          {
            // create a new choice node with normalized if, true and false
            // elements
            pResult = new CEvaluationNodeChoice(CEvaluationNode::SubType::IF, "if");
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

          default:
            break;
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
          case CEvaluationNode::SubType::INVALID:
            break;

          case CEvaluationNode::SubType::OR:
          case CEvaluationNode::SubType::XOR:
          case CEvaluationNode::SubType::AND:
          case CEvaluationNode::SubType::EQ:
          case CEvaluationNode::SubType::NE:
          case CEvaluationNode::SubType::LT:
          case CEvaluationNode::SubType::LE:
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

          case CEvaluationNode::SubType::GT:
            // turn the order of the operands and change to LT
            pResult = new CEvaluationNodeLogical(CEvaluationNode::SubType::LT, "<");
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

          case CEvaluationNode::SubType::GE:
            // turn the order of the operands and change to LE
            pResult = new CEvaluationNodeLogical(CEvaluationNode::SubType::LE, "<=");
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

          default:
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
          case CEvaluationNode::SubType::VECTOR:
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

          case CEvaluationNode::SubType::INVALID:
            break;

          default:
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
              if (pChild2->mainType() == CEvaluationNode::MainType::NUMBER)
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
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::SubType::INTEGER, "1");
                      delete pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }
              else
                {
                  pResult = new CEvaluationNodeOperator(CEvaluationNode::SubType::POWER, "^");
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
              if (pChild1->mainType() == CEvaluationNode::MainType::NUMBER)
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
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::SubType::INTEGER, "0");
                      // we are done
                      delete pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }

              if (pChild2 && pChild2->mainType() == CEvaluationNode::MainType::NUMBER)
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
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::SubType::INTEGER, "0");
                      // we are done
                      delete pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }

              if (!pResult)
                {
                  pResult = new CEvaluationNodeOperator(CEvaluationNode::SubType::MULTIPLY, "*");
                  pResult->addChild(pChild1);
                  pResult->addChild(pChild2);
                }

              if (pResult->mainType() == CEvaluationNode::MainType::OPERATOR)
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
              if (pChild1->mainType() == CEvaluationNode::MainType::NUMBER)
                {
                  if (fabs(*pChild1->getValuePointer()) < ZERO)
                    {
                      pResult = pChild2;
                      delete pChild1;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }

              if (pChild2 != NULL && pChild2->mainType() == CEvaluationNode::MainType::NUMBER)
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
                  pResult = new CEvaluationNodeOperator(CEvaluationNode::SubType::PLUS, "+");
                  pResult->addChild(pChild1);
                  pResult->addChild(pChild2);
                }

              if (pResult->mainType() == CEvaluationNode::MainType::OPERATOR)
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
              if (pChild2->mainType() == CEvaluationNode::MainType::NUMBER)
                {
                  // eliminate divisions by 1
                  if (fabs(*pChild2->getValuePointer() - 1.0) < ZERO)
                    {
                      pResult = pChild1;
                      delete pChild2;
                      pChild2 = NULL;
                    }
                  else if (pChild1->mainType() == CEvaluationNode::MainType::NUMBER)
                    {
                      // if both children are numbers, do the calculation
                      std::ostringstream os;
                      os << *pChild1->getValuePointer() / *pChild2->getValuePointer();
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::SubType::DOUBLE, os.str());
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
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::SubType::DOUBLE, "1.0");
                      delete pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }

              if (pResult == NULL)
                {
                  pResult = new CEvaluationNodeOperator(CEvaluationNode::SubType::DIVIDE, "/");
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
              if (pChild2->mainType() == CEvaluationNode::MainType::NUMBER)
                {
                  // eliminate modulus 1
                  if (fabs(*pChild2->getValuePointer() - 1.0) < ZERO)
                    {
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::SubType::INTEGER, "0");
                      delete pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                  else if (pChild1->mainType() == CEvaluationNode::MainType::NUMBER &&
                           pChild1->subType() == CEvaluationNode::SubType::INTEGER &&
                           pChild2->subType() == CEvaluationNode::SubType::INTEGER)
                    {
                      // if both children are numbers, do the calculation
                      std::ostringstream os;
                      os << (long)*pChild1->getValuePointer() % (long)*pChild2->getValuePointer();
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::SubType::INTEGER, os.str());
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
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::SubType::INTEGER, "0");
                      delete pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }

              if (pResult == NULL)
                {
                  pResult = new CEvaluationNodeOperator(CEvaluationNode::SubType::MODULUS, "%");
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
              if (pChild2->mainType() == CEvaluationNode::MainType::NUMBER)
                {
                  // eliminate subtraction of 0
                  if (fabs(*pChild2->getValuePointer()) < ZERO)
                    {
                      pResult = pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                  else if (pChild1->mainType() == CEvaluationNode::MainType::NUMBER)
                    {
                      // if both children are numbers, do the calculation
                      std::ostringstream os;
                      os << *pChild1->getValuePointer() - *pChild2->getValuePointer();
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::SubType::DOUBLE, os.str());
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
                      pResult = new CEvaluationNodeNumber(CEvaluationNode::SubType::DOUBLE, "0.0");
                      delete pChild1;
                      delete pChild2;
                      pChild1 = NULL;
                      pChild2 = NULL;
                    }
                }

              if (pResult == NULL)
                {
                  pResult = new CEvaluationNodeOperator(CEvaluationNode::SubType::MINUS, "-");
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

      if (subType == CEvaluationNode::SubType::MULTIPLY || subType == CEvaluationNode::SubType::PLUS)
        {

          double value = (subType == CEvaluationNode::SubType::MULTIPLY) ? 1.0 : 0.0;
          CEvaluationNodeNumber* pNumberNode = NULL;
          std::vector<CEvaluationNode*> numbers;

          while (it != endit)
            {
              pNumberNode = dynamic_cast<CEvaluationNodeNumber*>(*it);

              if (pNumberNode != NULL)
                {
                  numbers.push_back(pNumberNode);

                  if (subType == CEvaluationNode::SubType::MULTIPLY)
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
          if (pChild1->mainType() == CEvaluationNode::MainType::OPERATOR && pChild1->subType() == subType)
            {
              findChainNodes(dynamic_cast<CEvaluationNodeOperator*>(pChild1), nodes);
            }
          else
            {
              nodes.push_back(pChild1->copyBranch());
            }

          if (pChild2->mainType() == CEvaluationNode::MainType::OPERATOR && pChild2->subType() == subType)
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
      case CEvaluationNode::SubType::POWER:
        data = "^";
        break;

      case CEvaluationNode::SubType::MULTIPLY:
        data = "*";
        break;

      case CEvaluationNode::SubType::DIVIDE:
        data = "/";
        break;

      case CEvaluationNode::SubType::MODULUS:
        data = "%";
        break;

      case CEvaluationNode::SubType::PLUS:
        data = "+";
        break;

      case CEvaluationNode::SubType::MINUS:
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
      if (subType == CEvaluationNode::SubType::MULTIPLY || subType == CEvaluationNode::SubType::PLUS)
        {
          CEvaluationNodeOperator* pOperation = (subType == CEvaluationNode::SubType::MULTIPLY) ? new CEvaluationNodeOperator(CEvaluationNode::SubType::POWER, "^") : new CEvaluationNodeOperator(CEvaluationNode::SubType::MULTIPLY, "*");
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
              CEvaluationNodeNumber* pNumberNode = new CEvaluationNodeNumber(CEvaluationNode::SubType::INTEGER, os.str());
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
