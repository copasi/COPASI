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

#include "CDerive.h"

#include "CEvaluationNode.h"
#include "utilities/CCopasiParameter.h"
#include "model/CModelValue.h"
#include "function/CFunction.h"
#include "utilities/CNodeIterator.h"

bool CDerive::isOne(const CEvaluationNode* node)
{
  const CEvaluationNodeNumber * pENN = dynamic_cast<const CEvaluationNodeNumber*>(node);

  if (pENN && *pENN->getValuePointer() == 1)
    return true;

  return false;
}

bool CDerive::isZero(const CEvaluationNode* node)
{
  const CEvaluationNodeNumber * pENN = dynamic_cast<const CEvaluationNodeNumber*>(node);

  if (pENN && *pENN->getValuePointer() == 0)
    return true;

  return false;
}

void CDerive::deleteBranch(CEvaluationNode* node)
{
  //TODO !! important
  if (node == NULL) return;

  if (node->getParent() != NULL) node->getParent()->removeChild(node);

  delete node;
}

CEvaluationNode* CDerive::multiply(CEvaluationNode* n1, CEvaluationNode* n2, bool simplify)
{
  if (simplify)
    {
      if (isZero(n1) || isZero(n2))
        {
          deleteBranch(n1);
          deleteBranch(n2);
          return new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "0");
        }

      if (isOne(n1))
        {
          if (isOne(n2))
            {
              deleteBranch(n1);
              deleteBranch(n2);
              return new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "1");
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
  tmpNode = new CEvaluationNodeOperator(CEvaluationNode::S_MULTIPLY, "*");
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
          return new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "0");
        }

      /*if (isOne(n1))
      {
        if (isOne(n2))
        {
          deleteBranch(n1);
          deleteBranch(n2);
          return new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "1");
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
  tmpNode = new CEvaluationNodeOperator(CEvaluationNode::S_DIVIDE, "/");
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
              return new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "0");
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
          return new CEvaluationNodeNumber(*tmp1->getValuePointer() + *tmp2->getValuePointer());
        }
    }

  CEvaluationNode *newNode = new CEvaluationNodeOperator(CEvaluationNode::S_PLUS, "+");
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
              return new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "0");
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
          CEvaluationNode* tmpNN = new CEvaluationNodeNumber(*tmp1->getValuePointer() - *tmp2->getValuePointer());
          return tmpNN;
        }
    }

  CEvaluationNode *newNode = new CEvaluationNodeOperator(CEvaluationNode::S_MINUS, "-");
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
          return new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "1");
        }

      if (isZero(n2) && !isZero(n1))
        {
          deleteBranch(n1);
          deleteBranch(n2);
          return new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "1");
        }

      if (isZero(n1) && !isZero(n2))
        {
          deleteBranch(n1);
          deleteBranch(n2);
          return new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "0");
        }
    }

  CEvaluationNode * tmpNode = NULL;
  tmpNode = new CEvaluationNodeOperator(CEvaluationNode::S_POWER, "^");
  tmpNode->addChild(n1);
  tmpNode->addChild(n2);
  //tmpNode->compile(NULL);

  return tmpNode;
}

CEvaluationNode * CDerive::copyBranch_var2obj(const CEvaluationNode* node, std::vector<const CEvaluationNode*> & env)
{
  CEvaluationNode * pNode = NULL;
  CNodeContextIterator< const CEvaluationNode, std::vector< CEvaluationNode * > > itNode(node);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      if (itNode.parentContextPtr() != NULL)
        {
          if (itNode->mainType() == CEvaluationNode::T_VARIABLE)
            {
              //expand variable nodes
              const CEvaluationNodeVariable* tmpVar = dynamic_cast<const CEvaluationNodeVariable*>(*itNode);
              itNode.parentContextPtr()->push_back(env[tmpVar->getIndex()]->copyBranch());
            }
          else
            itNode.parentContextPtr()->push_back(itNode->copyNode(itNode.context()));
        }
      else
        {
          assert(*itNode == node);

          if (itNode->mainType() == CEvaluationNode::T_VARIABLE)
            {
              //expand variable nodes
              const CEvaluationNodeVariable* tmpVar = dynamic_cast<const CEvaluationNodeVariable*>(*itNode);
              pNode = env[tmpVar->getIndex()]->copyBranch();
            }
          else
            pNode = itNode->copyNode(itNode.context());
        }
    }

  return pNode;
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

      switch (pENO->subType())
        {
          case CEvaluationNode::S_MULTIPLY:
          {
            CEvaluationNode * pLeftCopy = copyBranch_var2obj(pENO->getLeft(), env);
            CEvaluationNode * pRightCopy = copyBranch_var2obj(pENO->getRight(), env);

            CEvaluationNode * tmpNode1 = multiply(pRightCopy, pLeftDeriv, simplify);
            CEvaluationNode * tmpNode2 = multiply(pRightDeriv, pLeftCopy, simplify);

            return add(tmpNode1, tmpNode2, simplify);
          }
          break;

          case CEvaluationNode::S_DIVIDE:
          {
            CEvaluationNode * pLeftCopy = copyBranch_var2obj(pENO->getLeft(), env);
            CEvaluationNode * pRightCopy = copyBranch_var2obj(pENO->getRight(), env);

            //numerator
            CEvaluationNode * tmpNode1 = multiply(pRightCopy, pLeftDeriv, simplify);
            CEvaluationNode * tmpNode2 = multiply(pRightDeriv, pLeftCopy, simplify);

            CEvaluationNode * minusNode = subtract(tmpNode1, tmpNode2, simplify);

            minusNode->compile(NULL);

            //denominator
            CEvaluationNode * powerNode = power(copyBranch_var2obj(pENO->getRight(), env),
                                                new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "2"),
                                                simplify);

            return divide(minusNode, powerNode, simplify);
          }
          break;

          case CEvaluationNode::S_PLUS:

            return add(pLeftDeriv, pRightDeriv, simplify);
            break;

          case CEvaluationNode::S_MINUS:

            return subtract(pLeftDeriv, pRightDeriv, simplify);
            break;

          case CEvaluationNode::S_POWER:
          {
            // b-1
            CEvaluationNode * tmpNode = subtract(copyBranch_var2obj(pENO->getRight(), env),
                                                 new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "1"),
                                                 simplify);

            // a^(b-1)
            CEvaluationNode * powerNode = power(copyBranch_var2obj(pENO->getLeft(), env), tmpNode, simplify);

            // b*a'
            tmpNode = multiply(copyBranch_var2obj(pENO->getRight(), env),
                               pLeftDeriv, simplify);

            // ln a
            CEvaluationNodeFunction * funcNode = new CEvaluationNodeFunction(CEvaluationNode::S_LOG, "ln");
            funcNode->addChild(copyBranch_var2obj(pENO->getLeft(), env)); // add a

            // a * b' * ln a
            CEvaluationNode * tmpNode2 = multiply(copyBranch_var2obj(pENO->getLeft(), env),
                                                  multiply(pRightDeriv, funcNode, simplify),
                                                  simplify);

            // b*a + a*b * ln a
            CEvaluationNode * plusNode = add(tmpNode, tmpNode2, simplify);

            // a^(b-1)*(b*a + a*b * ln a)
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
      newNode = new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "0");
      return newNode;
    }

  const CEvaluationNodeObject *pENObj = dynamic_cast<const CEvaluationNodeObject*>(node);

  if (pENObj)
    {
      //first check whether the object is the derivation variable
      if (pObject->getCN() == pENObj->getObjectCN())
        {
          //std::cout << "*";
          return new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "1");
        }

      //now we need to check if we know something about the object so that it needs to be expanded
      const CCopasiObject * tmpObj = (const CCopasiObject *)pENObj->getObjectInterfacePtr();

      if (!tmpObj)
        return NULL;

      //object is a concentration?
      if (tmpObj->getObjectName() == "Concentration")
        {
          //std::cout << "Concentration found" << std::endl;
          //In this context, the concentration is expanded as "amount of substance/volume"
          std::string tmpstr = tmpObj->getObjectParent() ? "<" + tmpObj->getObjectParent()->getCN() + ",Reference=ParticleNumber>" : "<>";
          CEvaluationNodeObject* amount = new CEvaluationNodeObject(CEvaluationNode::S_CN, tmpstr);
          amount->compile(pTree);

          tmpstr = tmpObj->getObjectAncestor("Compartment") ? "<" + tmpObj->getObjectAncestor("Compartment")->getCN() + ",Reference=Volume>"  : "<>";
          CEvaluationNodeObject* volume = new CEvaluationNodeObject(CEvaluationNode::S_CN, tmpstr);
          volume->compile(pTree);
          CEvaluationNodeObject* volume2 = new CEvaluationNodeObject(CEvaluationNode::S_CN, tmpstr); //we need this node twice
          volume2->compile(pTree);

          CEvaluationNode* damount = deriveBranch(amount, pObject, env, pTree, simplify);
          CEvaluationNode* dvolume = deriveBranch(volume, pObject, env, pTree, simplify);

          // A / V - A*V /V^2
          return
            subtract(divide(damount, volume, simplify),
                     divide(multiply(amount, dvolume, simplify),
                            power(volume2, new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "2"), simplify),
                            simplify),
                     simplify);
        }

      //TODO:
      //object is an object with an assignment
      //object is dependent species
      //object is a reaction rate

      // otherwise return 0.
      return new CEvaluationNodeNumber(CEvaluationNode::S_INTEGER, "0");
    }

  const CEvaluationNodeCall  *pENCall = dynamic_cast<const CEvaluationNodeCall*>(node);

  if (pENCall)
    {

      //is it a function?
      const CFunction * tmpFunction = dynamic_cast<const CFunction*>(pENCall->getCalledTree());

//     const std::vector<CEvaluationNode *> getListOfChildNodes() const {return mCallNodes;}

      //create call environment for the called function
      std::vector<const CEvaluationNode*> subenv;
      size_t i, imax = pENCall->getListOfChildNodes().size();
      subenv.resize(imax);

      for (i = 0; i < imax; ++i)
        {
          CEvaluationNode* tmpnode = copyBranch_var2obj(pENCall->getListOfChildNodes()[i], env);
          compileTree(tmpnode, pTree);
          subenv[i] = tmpnode;
        }

      return deriveBranch(pENCall->getCalledTree()->getRoot(), pObject,
                          subenv,
                          pTree, simplify);
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
