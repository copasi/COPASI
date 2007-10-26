// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CDerive.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/10/26 13:09:46 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CDerive.h"

#include "CEvaluationNode.h"

CEvaluationNode* CDerive::deriveBranch(const CEvaluationNode* node, C_INT32 variableIndex, const CCopasiObject * pObject)
{
  CEvaluationNode * newNode = NULL;

  const CEvaluationNodeOperator * pENO = dynamic_cast<const CEvaluationNodeOperator*>(node);
  if (pENO)
    {
      if (!pENO->getLeft() || !pENO->getRight()) return NULL;
      CEvaluationNode * pLeftDeriv = deriveBranch(pENO->getLeft(), variableIndex, pObject);
      if (!pLeftDeriv) return NULL;
      CEvaluationNode * pRightDeriv = deriveBranch(pENO->getRight(), variableIndex, pObject);
    if (!pRightDeriv) {delete pLeftDeriv; return NULL;}

      // we now know that derivations of the left and right branch exist

      switch (CEvaluationNode::subType(pENO->getType()))
        {
        case CEvaluationNodeOperator::MULTIPLY:
          {
            CEvaluationNode * pLeftCopy = pENO->getLeft()->copyBranch();
            CEvaluationNode * pRightCopy = pENO->getRight()->copyBranch();

            newNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::PLUS, "+");

            CEvaluationNodeOperator * tmpNode;
            tmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
            tmpNode->addChild(pRightCopy);
            tmpNode->addChild(pLeftDeriv);
            //tmpNode->compile(NULL);
            newNode->addChild(tmpNode);

            tmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
            tmpNode->addChild(pRightDeriv);
            tmpNode->addChild(pLeftCopy);
            //tmpNode->compile(NULL);
            newNode->addChild(tmpNode);

            //if (newNode) newNode->compile(NULL);
            return newNode;
          }
          break;

        case CEvaluationNodeOperator::DIVIDE:
          {
            CEvaluationNode * pLeftCopy = pENO->getLeft()->copyBranch();
            CEvaluationNode * pRightCopy = pENO->getRight()->copyBranch();

            //numerator
            CEvaluationNodeOperator * minusNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "+");

            CEvaluationNodeOperator * tmpNode;
            tmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
            tmpNode->addChild(pRightCopy);
            tmpNode->addChild(pLeftDeriv);
            //tmpNode->compile(NULL);
            minusNode->addChild(tmpNode);

            tmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
            tmpNode->addChild(pRightDeriv);
            tmpNode->addChild(pLeftCopy);
            //tmpNode->compile(NULL);
            minusNode->addChild(tmpNode);

            minusNode->compile(NULL);

            //denominator
            CEvaluationNodeOperator * powerNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::POWER, "^");
            pRightCopy = pENO->getRight()->copyBranch();  //new copy
            powerNode->addChild(pRightCopy);
            powerNode->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "2.0"));
            //powerNode->compile(NULL);

            newNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::DIVIDE, "/");
            newNode->addChild(minusNode);
            newNode->addChild(powerNode);
            //if (newNode) newNode->compile(NULL);
            return newNode;
          }
          break;

        case CEvaluationNodeOperator::PLUS:
          newNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::PLUS, "+");
          newNode->addChild(pLeftDeriv);
          newNode->addChild(pRightDeriv);
          //TODO check for zeros

          //if (newNode) newNode->compile(NULL);
          return newNode;
          break;

          /*        case CEvaluationNodeOperator::MINUS:
                    return evaluateNode(pENO->getLeft(), callParameters, mode) - evaluateNode(pENO->getRight(), callParameters, mode);
                    break;

                  case CEvaluationNodeOperator::POWER:
                    return evaluateNode(pENO->getLeft(), callParameters, mode) ^ evaluateNode(pENO->getRight(), callParameters, mode);
                    break;*/
          //
          //           case MODULUS:
          //             Value = (C_FLOAT64) (((C_INT32) mpLeft->value()) % ((C_INT32) mpRight->value()));
          //             break;
          //

        default:
          break;
        }
    }

  const CEvaluationNodeVariable * pENV = dynamic_cast<const CEvaluationNodeVariable*>(node);
  if (pENV)
    {
      if (pObject) return NULL; // if a variable node occurs, we are differentiating a function

      if (variableIndex == pENV->getIndex())
        newNode = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");
      else
        newNode = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.0");

      return newNode;
    }

  return newNode;
}

//static
void CDerive::compileTree(CEvaluationNode* node, const CEvaluationTree * pTree)
{
  if (!node) return;
  node->compile(pTree);

  CEvaluationNode* child = dynamic_cast<CEvaluationNode*>(node->getChild());
  while (child != NULL)
    {
      compileTree(child, pTree);
      child = dynamic_cast<CEvaluationNode*>(child->getSibling());
    }
}

#ifdef xxx

CEvaluationNode* CDerive::deriveBranch(const CEvaluationNode* node, C_INT32 variableIndex, const CCopasiObject * pObject)
{
  std::vector<CEvaluationNode*> children;
  const CEvaluationNode* child = dynamic_cast<const CEvaluationNode*>(node->getChild());
  while (child != NULL)
    {
      CEvaluationNode *newchild = NULL;
      newchild = deriveBranch(child, variableIndex, pObject);
      children.push_back(newchild);
      child = dynamic_cast<const CEvaluationNode*>(child->getSibling());
    }
  children.push_back(NULL);
  CEvaluationNode *newnode = node->copyNode(children);
  return newnode;
}

#endif
