// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CDerive.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/07/16 18:59:37 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CDerive.h"

#include "CEvaluationNode.h"


bool CDerive::isOne(const CEvaluationNode* node)
{
  const CEvaluationNodeNumber * pENN = dynamic_cast<const CEvaluationNodeNumber*>(node);
  if (pENN && pENN->getValue()==1)
    return true;
  
  return false;
}

bool CDerive::isZero(const CEvaluationNode* node)
{
  const CEvaluationNodeNumber * pENN = dynamic_cast<const CEvaluationNodeNumber*>(node);
  if (pENN && pENN->getValue()==0)
    return true;
  
  return false;
  
}

void CDerive::deleteBranch(CEvaluationNode* node)
{
  //TODO !! important 
}


CEvaluationNode* CDerive::multiply(CEvaluationNode* n1, CEvaluationNode* n2, bool simplify)
{
  if (simplify)
  {
    if (isZero(n1) || isZero(n2))
    {
      deleteBranch(n1);
      deleteBranch(n2);
      return new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "0");
    }
    
    if (isOne(n1))
        {
          if (isOne(n2))
          {
            deleteBranch(n1);
            deleteBranch(n2);
            return new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "1");
          }
          else
          {
            deleteBranch(n1);
            return n2;
          }
        }
    if (isOne(n2))
    {
      deleteBranch(n2);
      return n1;
    }
  }

  CEvaluationNode * tmpNode = NULL;
  tmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
  tmpNode->addChild(n1);
  tmpNode->addChild(n2);
  //tmpNode->compile(NULL);
  
  return tmpNode;
}

CEvaluationNode* CDerive::divide(CEvaluationNode* n1, CEvaluationNode* n2, bool simplify)
{
  if (simplify)
  {
    if (isZero(n1))
    {
      deleteBranch(n1);
      deleteBranch(n2);
      return new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "0");
    }
    
    /*if (isOne(n1))
    {
      if (isOne(n2))
      {
        deleteBranch(n1);
        deleteBranch(n2);
        return new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "1");
      }
      else
      {
        deleteBranch(n1);
        return n2;
      }
    }*/
    
    if (isOne(n2))
    {
      deleteBranch(n2);
      return n1;
    }
  }
  
  CEvaluationNode * tmpNode = NULL;
  tmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::DIVIDE, "/");
  tmpNode->addChild(n1);
  tmpNode->addChild(n2);
  //tmpNode->compile(NULL);
  
  return tmpNode;
}

CEvaluationNode* CDerive::add(CEvaluationNode* n1, CEvaluationNode* n2, bool simplify)
{
  if (simplify)
  {
    if (isZero(n1))
    {
      if (isZero(n2))
      {
        deleteBranch(n1);
        deleteBranch(n2);
        return new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "0");
      }
      else
      {
        deleteBranch(n1);
        return n2;
      }
    }
    if (isZero(n2))
    {
      deleteBranch(n2);
      return n1;
    }
    
    // "numerical" simplification
    const CEvaluationNodeNumber * tmp1 = dynamic_cast<CEvaluationNodeNumber*>(n1);
    const CEvaluationNodeNumber * tmp2 = dynamic_cast<CEvaluationNodeNumber*>(n2);
    if (tmp1 && tmp2)
    {
      return new CEvaluationNodeNumber(tmp1->getValue()+tmp2->getValue());
    }
  }
  
  CEvaluationNode *newNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::PLUS, "+");
  newNode->addChild(n1);
  newNode->addChild(n2);
  
  return newNode;
}

CEvaluationNode* CDerive::subtract(CEvaluationNode *n1, CEvaluationNode *n2, bool simplify)
{
  if (simplify)
  {
    if (isZero(n1))
    {
      if (isZero(n2))
      {
        deleteBranch(n1);
        deleteBranch(n2);
        return new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "0");
      }
      //else
      //{
      //  deleteBranch(n1);
      //  return n2;
      //}
    }
    if (isZero(n2))
    {
      deleteBranch(n2);
      return n1;
    }
    // "numerical" simplification
    const CEvaluationNodeNumber * tmp1 = dynamic_cast<CEvaluationNodeNumber*>(n1);
    const CEvaluationNodeNumber * tmp2 = dynamic_cast<CEvaluationNodeNumber*>(n2);
    if (tmp1 && tmp2)
    {
      CEvaluationNode* tmpNN = new CEvaluationNodeNumber(tmp1->getValue()-tmp2->getValue());
      return tmpNN;
    }
  }
  
  CEvaluationNode *newNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
  newNode->addChild(n1);
  newNode->addChild(n2);
  
  return newNode;
}

CEvaluationNode* CDerive::power(CEvaluationNode* n1, CEvaluationNode* n2, bool simplify)
{
  if (simplify)
  {
    if (isOne(n2))
    {
      deleteBranch(n2);
      return n1;
    }

    if (isOne(n1))
    {
      deleteBranch(n1);
      deleteBranch(n2);
      return new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "1");
    }
    
    if (isZero(n2) && !isZero(n1))
    {
      deleteBranch(n1);
      deleteBranch(n2);
      return new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "1");
    }
      
    if (isZero(n1) && !isZero(n2))
    {
      deleteBranch(n1);
      deleteBranch(n2);
      return new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "0");
    }
  }
  
  CEvaluationNode * tmpNode = NULL;
  tmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::POWER, "^");
  tmpNode->addChild(n1);
  tmpNode->addChild(n2);
  //tmpNode->compile(NULL);
  
  return tmpNode;
}


//TODO remove pModel
CEvaluationNode* CDerive::deriveBranch(const CEvaluationNode* node, const double * pObject,
                                       //std::vector<const CEvaluationNode*>& env,
                                       //std::vector<const CCopasiObject*>& objenv,
                                       const CEvaluationTree* pTree,
                                       bool simplify)
{
  CEvaluationNode * newNode = NULL;

  const CEvaluationNodeOperator * pENO = dynamic_cast<const CEvaluationNodeOperator*>(node);

  if (pENO)
    {
      if (!pENO->getLeft() || !pENO->getRight()) return NULL;

      CEvaluationNode * pLeftDeriv = deriveBranch(pENO->getLeft(), pObject, pTree, simplify);

      if (!pLeftDeriv) return NULL;

      CEvaluationNode * pRightDeriv = deriveBranch(pENO->getRight(), pObject, pTree, simplify);

      if (!pRightDeriv) {delete pLeftDeriv; return NULL;}

      // we now know that derivations of the left and right branch exist

      switch ((CEvaluationNodeOperator::SubType) CEvaluationNode::subType(pENO->getType()))
        {
          case CEvaluationNodeOperator::MULTIPLY:
          {
            CEvaluationNode * pLeftCopy = pENO->getLeft()->copyBranch();
            CEvaluationNode * pRightCopy = pENO->getRight()->copyBranch();

            CEvaluationNode * tmpNode1 = multiply(pRightCopy, pLeftDeriv, simplify);
            CEvaluationNode * tmpNode2 = multiply(pRightDeriv, pLeftCopy, simplify);

            return add(tmpNode1, tmpNode2, simplify);
          }
          break;

          case CEvaluationNodeOperator::DIVIDE:
          {
            CEvaluationNode * pLeftCopy = pENO->getLeft()->copyBranch();
            CEvaluationNode * pRightCopy = pENO->getRight()->copyBranch();

            //numerator
            CEvaluationNode * tmpNode1 = multiply(pRightCopy, pLeftDeriv, simplify);
            CEvaluationNode * tmpNode2 = multiply(pRightDeriv, pLeftCopy, simplify);

            CEvaluationNode * minusNode = subtract(tmpNode1, tmpNode2, simplify);
            
            minusNode->compile(NULL);

            //denominator
            CEvaluationNode * powerNode = power(pENO->getRight()->copyBranch(),
                                                new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "2"),
                                                simplify);
            
            return divide(minusNode, powerNode, simplify);
          }
          break;

          case CEvaluationNodeOperator::PLUS:
            
            return add(pLeftDeriv, pRightDeriv, simplify);
            break;

          case CEvaluationNodeOperator::MINUS:

            return subtract(pLeftDeriv, pRightDeriv, simplify);
            break;

          case CEvaluationNodeOperator::POWER:
          {
            // b-1
            CEvaluationNode * tmpNode = subtract(pENO->getRight()->copyBranch(),
                                                 new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "1"),
                                                 simplify);
            
            // a^(b-1)
            CEvaluationNode * powerNode = power(pENO->getLeft()->copyBranch(), tmpNode, simplify);


            // b*a'
            tmpNode = multiply(pENO->getRight()->copyBranch(),
                               pLeftDeriv, simplify);
            
            // ln a
            CEvaluationNodeFunction * funcNode = new CEvaluationNodeFunction(CEvaluationNodeFunction::LOG, "ln");
            funcNode->addChild(pENO->getLeft()->copyBranch()); // add a
            
            // a * b' * ln a
            CEvaluationNode * tmpNode2 = multiply(pENO->getLeft()->copyBranch(),
                                                  multiply(pRightDeriv, funcNode, simplify),
                                                  simplify);

            // b*a´ + a*b´* ln a
            CEvaluationNode * plusNode = add(tmpNode, tmpNode2, simplify);
            

            // a^(b-1)*(b*a´ + a*b´ * ln a)
            return multiply(powerNode, plusNode, simplify);
          }
          break;

          default:
            break;
        }
    }

  const CEvaluationNodeVariable * pENV = dynamic_cast<const CEvaluationNodeVariable*>(node);

  if (pENV)
    {
    //variable nodes are not supported here
    return NULL;
    }

  const CEvaluationNodeNumber * pENN = dynamic_cast<const CEvaluationNodeNumber*>(node);

  if (pENN)
    {
      newNode = new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "0");
      return newNode;
    }

  const CEvaluationNodeObject *pENObj = dynamic_cast<const CEvaluationNodeObject*>(node);
  if (pENObj)
    {
      //only pointer type object nodes are supported
      if (pENObj->getType()!= (CEvaluationNode::OBJECT | CEvaluationNodeObject::POINTER))
        return NULL;
    
      //first check whether the object is the derivation variable
      if (pObject == pENObj->getValuePointer())
        {
        std::cout << "*";
        return new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "1");
        }
    
      //now we need to check if we know something about the object
    
      //has it an algebraic expression?
    
      //otherwise return 0
      return new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "0");
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
