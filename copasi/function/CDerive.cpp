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
CEvaluationNode* CDerive::deriveBranch(const CEvaluationNode* node, const CCopasiObject * pObject,
                                       std::vector<const CEvaluationNode*>& env,
                                       //std::vector<const CCopasiObject*>& objenv,
                                       const CEvaluationTree* pTree,
                                       bool simplify)
{
  CEvaluationNode * newNode = NULL;

  const CEvaluationNodeOperator * pENO = dynamic_cast<const CEvaluationNodeOperator*>(node);

  if (pENO)
    {
      if (!pENO->getLeft() || !pENO->getRight()) return NULL;

      CEvaluationNode * pLeftDeriv = deriveBranch(pENO->getLeft(), pObject, env, pTree, simplify);

      if (!pLeftDeriv) return NULL;

      CEvaluationNode * pRightDeriv = deriveBranch(pENO->getRight(), pObject, env, pTree, simplify);

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
    if (!env[pENV->getIndex()])
      return NULL;
    
    //basically just expand the tree. 
    return deriveBranch(env[pENV->getIndex()], pObject, env, pTree, simplify);
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
      //first check whether the object is the derivation variable
      if (pObject->getCN() == pENObj->getObjectCN())
        {
        std::cout << "*";
        return new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "1");
        }
    
      //now we need to check if we know something about the object so that it needs to be expanded
      const CCopasiObject * tmpObj = (const CCopasiObject *)pENObj->getObjectInterfacePtr();
      if (!tmpObj)
        return NULL;
    
      //object is a concentration?
      if (tmpObj->getObjectName() == "Concentration")
        {
        std::cout << "Concentration found" << std::endl;
        //In this context, the concentration is expanded as "amount of substance/volume"
        std::string tmpstr = tmpObj->getObjectParent() ? "<" + tmpObj->getObjectParent()->getCN() + ",Reference=ParticleNumber>" : "<>";
        CEvaluationNodeObject* amount = new CEvaluationNodeObject(CEvaluationNodeObject::CN, tmpstr);
        amount->compile(pTree);
        
        tmpstr = tmpObj->getObjectAncestor("Compartment") ? "<" + tmpObj->getObjectAncestor("Compartment")->getCN() + ",Reference=Volume>"  : "<>";
        CEvaluationNodeObject* volume = new CEvaluationNodeObject(CEvaluationNodeObject::CN, tmpstr);
        volume->compile(pTree);
        CEvaluationNodeObject* volume2 = new CEvaluationNodeObject(CEvaluationNodeObject::CN, tmpstr); //we need this node twice
        volume2->compile(pTree);
        
        CEvaluationNode* damount = deriveBranch(amount, pObject, env, pTree, simplify);
        CEvaluationNode* dvolume = deriveBranch(volume, pObject, env, pTree, simplify);
        
        // A´/V - A*V´/V^2
        return
        subtract(divide(damount, volume, simplify),
                 divide(multiply(amount, dvolume, simplify),
                        power(volume2, new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "2"), simplify),
                        simplify),
                 simplify);
        }
    
    //TODO:
      //object is an object with an assignment
      //object is dependent species
      //object is a reaction rate
    
      // otherwise return 0.
      return new CEvaluationNodeNumber(CEvaluationNodeNumber::INTEGER, "0");
    }
  
  return newNode;
}

/*


CEvaluationNode* CDerive::deriveBranch(const CEvaluationNode* node, unsigned C_INT32 variableIndex, const CCopasiObject * pObject)
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

      switch ((CEvaluationNodeOperator::SubType) CEvaluationNode::subType(pENO->getType()))
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

*/

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
