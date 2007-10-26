// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CDerive.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/10/26 14:55:48 $
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
            powerNode->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "2"));
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

        case CEvaluationNodeOperator::MINUS:
          newNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
          newNode->addChild(pLeftDeriv);
          newNode->addChild(pRightDeriv);
          //TODO check for zeros

          //if (newNode) newNode->compile(NULL);
          return newNode;
          break;

        case CEvaluationNodeOperator::POWER:
          {
            CEvaluationNode * pLeftCopy = pENO->getLeft()->copyBranch();
            CEvaluationNode * pRightCopy = pENO->getRight()->copyBranch();

            // a^(b-1)
            CEvaluationNodeOperator * powerNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::POWER, "^");
            powerNode->addChild(pLeftCopy); // add a

            CEvaluationNodeOperator * tmpNode;
            tmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
            tmpNode->addChild(pRightCopy); // add b
            tmpNode->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "1")); // 1
            powerNode->addChild(tmpNode); // add b-1

            // b*a´ + a*b´* ln a
            CEvaluationNodeOperator * plusNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::PLUS, "+");

            tmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
            pRightCopy = pENO->getRight()->copyBranch();  //new copy of b
            tmpNode->addChild(pRightCopy); // add b
            tmpNode->addChild(pLeftDeriv); // add a´
            plusNode->addChild(tmpNode); // add b*a´

            tmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
            pLeftCopy = pENO->getLeft()->copyBranch();  //new copy of a
            tmpNode->addChild(pLeftCopy); // add a

            CEvaluationNodeOperator * tmptmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
            tmptmpNode->addChild(pRightDeriv); // add b´
            CEvaluationNodeFunction * funcNode = new CEvaluationNodeFunction(CEvaluationNodeFunction::LOG, "ln"); // ln a
            pLeftCopy = pENO->getLeft()->copyBranch();  //new copy of a
            funcNode->addChild(pLeftCopy); // add a
            tmptmpNode->addChild(funcNode); // add ln a

            tmpNode->addChild(tmptmpNode); // add b´ * ln a
            plusNode->addChild(tmpNode); // add a * b´ * ln a

            // a^(b-1)*(b*a´ + a*b´ * ln a)
            newNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
            newNode->addChild(powerNode);
            newNode->addChild(plusNode);
            return newNode;
          }
          break;

        default:
          break;
        }
    }

  const CEvaluationNodeVariable * pENV = dynamic_cast<const CEvaluationNodeVariable*>(node);
  if (pENV)
    {
      if (pObject) return NULL; // if a variable node occurs, we are differentiating a function

      if (variableIndex == pENV->getIndex())
        newNode = new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "1");
      else
        newNode = new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "0");

      return newNode;
    }

  const CEvaluationNodeNumber * pENN = dynamic_cast<const CEvaluationNodeNumber*>(node);
  if (pENN)
    {
      newNode = new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "0");
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
