// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalTranslation.cpp,v $
//   $Revision: 1.16 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/05/06 11:58:12 $
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
#include <string>
#include <set>
#include <vector>
#include <iostream>

#include "copasi.h"

#include "CNormalBase.h"
#include "ConvertToCEvaluationNode.h"
#include "CNormalTranslation.h"
#include "CNormalFraction.h"
#include "CNormalSum.h"
#include "CNormalProduct.h"
#include "CNormalLogical.h"

#include "function/CEvaluationTree.h"
#include "function/CEvaluationNodeConstant.h"

const double CNormalTranslation::ZERO = 1e-100;

/**
 * Simplify an evaluation tree given by the root node by creating a new simplified tree from the original one.
 * The tree itself is actually not created!
 * @return CEvaluationNode*, pointer to root node of the newly created tree.
 */
CEvaluationNode* CNormalTranslation::simplifyTree(const CEvaluationNode* node)
{
  //std::cout << "simplifyTree called." << std::endl;
  const CEvaluationNode * child = dynamic_cast<const CEvaluationNode*>(node->getChild());
  CEvaluationNode * newchild = NULL;
  std::vector<CEvaluationNode*> children;
  while (child != NULL)
    {
      newchild = simplifyTree(child);
      child = dynamic_cast<const CEvaluationNode*>(child->getSibling());
      children.push_back(newchild);
    }
  CEvaluationNode* newnode = node->simplifyNode(children);
  return newnode;
}

/**
 * Creating a simplified tree by calling simplifyTree repeatedly until it cannot be simplified further.
 * The tree itself is actually not created!
 * @return CEvaluationNode*, pointer to root node of the newly created tree.
 */
CEvaluationNode * CNormalTranslation::simplifyTreeReptdly(const CEvaluationNode* root0)
{
  //std::cout << "<p>simplifyTreeReptly called.</p>" << std::endl;
  //std::cout << root0->getInfix() << std::endl;
  CEvaluationNode * root1 = simplifyTree(root0);
  //std::cout << "<p>" << root1->getInfix() << "</p>" << std::endl;
  //std::cout << "<p>";
  //root1->printRecursively(std::cout);
  //std::cout << "</p>" << std::endl;
  //std::cout << "<p><math xmlns=\"&mathml;\">" << std::endl;
  //root1->writeMathML(std::cout,std::vector<std::vector<std::string> >());
  //std::cout << "</math></p>" << std::endl;
  //root1->printRecursively(std::cout,0);
  //std::cout << root1->getInfix() << std::endl;
  if (root1->getInfix() != root0->getInfix())
    {
      CEvaluationNode * root2 = simplifyTreeReptdly(root1);
      delete root1;
      return root2;
    }
  else
    {
      return root1;
    }
}

/**
 * Translate and simplify a tree given by the root node into CNormal structure
 * @return CNormalFraction*
 */
CNormalFraction* CNormalTranslation::normAndSimplify(const CEvaluationNode* root0)
{
  //std::cout << "<p>normAndSimplyfy called.</p>" << std::endl;
  //CEvaluationNode * root1 = simplifyTreeReptdly(root0);
  CEvaluationNode* root1 = CNormalTranslation::simplify(root0);
  CEvaluationNode* root2 = CNormalTranslation::expandPowerExponents(root1);
  delete root1;
  CNormalFraction* base = createNormalRepresentation(root2);
  /*
  std::set<const CNormalLogical*> logicals=base->findLogicals();
  std::set<const CNormalLogical*>::iterator it=logicals.begin();
  std::set<const CNormalLogical*>::iterator endit=logicals.end();
  std::cout << "Found " << logicals.size() << " logicals: " << std::endl;
  while(it!=endit)
  {
      std::cout << (*it)->debug();
    ++it;
  }
  */
  //std::cout << "<p>Created Normal Repr.: " << base->toString() << "</p>" << std::endl;
  base->simplify();
  /*
  logicals=base->findLogicals();
  it=logicals.begin();
  endit=logicals.end();
  std::cout << "Found " << logicals.size() << " logicals: " << std::endl;
  while(it!=endit)
  {
      std::cout << (*it)->debug();
    ++it;
  }
  */
  delete root2;

  return base;
}

/**
 * Translate and simplify a tree by calling normAndSimplify repeatedly until it cannot be simplified further
 * @return CNormalFraction*
 */
CNormalFraction* CNormalTranslation::normAndSimplifyReptdly(const CEvaluationTree* tree0)
{
  //std::cout << "<p>normAndSimplifyReptdly called.</p>" << std::endl;
  const CEvaluationNode* root0 = tree0->getRoot();

  CNormalFraction * base0 = normAndSimplify(root0);

  std::stringstream tmp;
  tmp << base0->toString();
  //std::cout << "<p>Normal Repr.: " << base0->toString() << "</p>" << std::endl;

  CEvaluationTree * tree1 = new CEvaluationTree("second tree", NULL, CEvaluationTree::Function);

  tree1->setInfix(tmp.str());
  //std::cout << "<p>Infix: " << tree1->getRoot()->getInfix() << "</p>" << std::endl;
  //std::cout << "<p><math xmlns=\"&mathml;\">" << std::endl;
  //tree1->getRoot()->writeMathML(std::cout,std::vector<std::vector<std::string> >());
  //std::cout << "</math></p>" << std::endl;
  if (tree1->getInfix() != tree0->getInfix())
    {
      CNormalFraction * base1 = normAndSimplifyReptdly(tree1);
      delete tree1;
      delete base0;
      return base1;
    }
  else
    {
      delete tree1;
      return base0;
    }
}

/**
 * Translate and simplify a tree by calling normAndSimplify repeatedly until it cannot be simplified further
 * @return CNormalFraction*
 */
CNormalFraction* CNormalTranslation::normAndSimplifyReptdly(const CEvaluationNode* root0)
{
  //std::cout << "<p>normAndSimplifyReptdly called.</p>" << std::endl;
  //const CEvaluationNode* root0=tree0->getRoot();
  CNormalFraction * base0 = normAndSimplify(root0);

  std::stringstream tmp;
  //tmp << base0->toString();

  //CEvaluationTree * tree1 = new CEvaluationTree("second tree", NULL, CEvaluationTree::Function);
  //std::cout << "<p>Normal Repr.: " << base0->toString() <<"</p>" << std::endl;
  CEvaluationNode* pTmpNode = convertToCEvaluationNode(*base0);
  //std::cout << "<p>Infix: " << pTmpNode->getInfix() << "</p>" << std::endl;
  //std::cout << "<p><math xmlns=\"&mathml;\">" << std::endl;
  //pTmpNode->writeMathML(std::cout,std::vector<std::vector<std::string> >());
  //tree1->setInfix(tmp.str());
  //std::cout << "</math></p>" << std::endl;
  CNormalFraction* pFraction = dynamic_cast<CNormalFraction*>(base0);
  assert(pFraction != NULL);

  //if (pTmpNode->getInfix() != root0->getInfix())
  if ((pFraction->getNumerator().getFractions().size() != 0) || (pFraction->getDenominator().getFractions().size() != 0))
    {
      CNormalFraction * base1 = normAndSimplifyReptdly(pTmpNode);
      delete pTmpNode;
      delete base0;
      return base1;
    }
  else
    {
      delete pTmpNode;
      return base0;
    }
}

CEvaluationNode* CNormalTranslation::expandPowerExponents(const CEvaluationNode* pRoot)
{
  CEvaluationNode* pResult = NULL;
  const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pRoot->getChild());
  std::vector<CEvaluationNode*> children;
  while (pChild != NULL)
    {
      CEvaluationNode* pNewChild = CNormalTranslation::expandPowerExponents(pChild);
      children.push_back(pNewChild);
      pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
    }
  if (CEvaluationNode::type(pRoot->getType()) == CEvaluationNode::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pRoot->getType())) == CEvaluationNodeOperator::POWER)
    {
      assert(children.size() == 2);
      std::vector<const CEvaluationNode*> summands;
      CNormalTranslation::findSummands(children[1], summands);
      // for each summand create a power node with a copy of the first child
      // in children as child 1 and a copy of the summand as child 2
      std::vector<CEvaluationNode*> numeratorNodes;
      std::vector<CEvaluationNode*> denominatorNodes;
      std::vector<const CEvaluationNode*>::iterator it = summands.begin(), endit = summands.end();
      while (it != endit)
        {
          CEvaluationNodeOperator* pPowerNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::POWER, "^");
          pPowerNode->addChild(children[0]->copyBranch());
          if (CEvaluationNode::type((*it)->getType()) == CEvaluationNode::FUNCTION && ((CEvaluationNodeFunction::SubType)CEvaluationNode::subType((*it)->getType())) == CEvaluationNodeFunction::MINUS)
            {
              pPowerNode->addChild(dynamic_cast<const CEvaluationNode*>((*it)->getChild())->copyBranch());
              denominatorNodes.push_back(pPowerNode);
            }
          else if ((CEvaluationNode::type((*it)->getType()) == CEvaluationNode::NUMBER && dynamic_cast<const CEvaluationNodeNumber*>((*it))->value() < 0.0))
            {
              std::ostringstream os;
              os.precision(18);
              os << fabs(dynamic_cast<const CEvaluationNodeNumber*>(*it)->value());
              pPowerNode->addChild(new CEvaluationNodeNumber((CEvaluationNodeNumber::SubType)CEvaluationNode::subType((*it)->getType()), os.str().c_str()));
              denominatorNodes.push_back(pPowerNode);
            }
          else
            {
              pPowerNode->addChild((*it)->copyBranch());
              numeratorNodes.push_back(pPowerNode);
            }
          ++it;
        }
      delete children[0];
      delete children[1];
      // create the numerator chain
      pResult = CNormalTranslation::createOperatorChain(CEvaluationNodeOperator::MULTIPLY, "*", numeratorNodes);
      std::vector<CEvaluationNode*>::iterator vit = numeratorNodes.begin(), vendit = numeratorNodes.end();
      while (vit != vendit)
        {
          delete (*vit);
          ++vit;
        }
      // if there are items in the denominator vector create the denominator
      // chain and divide the numerato chain by the denominator chain
      if (!denominatorNodes.empty())
        {
          CEvaluationNodeOperator* pDivision = new CEvaluationNodeOperator(CEvaluationNodeOperator::DIVIDE, "/");
          pDivision->addChild(pResult);
          pDivision->addChild(CNormalTranslation::createOperatorChain(CEvaluationNodeOperator::MULTIPLY, "*", denominatorNodes));
          vit = denominatorNodes.begin(), vendit = denominatorNodes.end();
          while (vit != vendit)
            {
              delete (*vit);
              ++vit;
            }
          pResult = pDivision;
        }
    }
  else
    {
      // copy the node and add the children
      pResult = CEvaluationNode::create(pRoot->getType(), pRoot->getData());
      std::vector<CEvaluationNode*>::iterator it = children.begin(), endit = children.end();
      while (it != endit)
        {
          pResult->addChild(*it);
          ++it;
        }
    }
  return pResult;
}

CEvaluationNode* CNormalTranslation::createOperatorChain(CEvaluationNodeOperator::SubType type, const char* data, const std::vector<CEvaluationNode*>& nodes)
{
  CEvaluationNode* pResult = NULL;
  if (nodes.size() == 0)
    {
      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");
    }
  else if (nodes.size() == 1)
    {
      pResult = nodes[0]->copyBranch();
    }
  else
    {
      // start from the back to create the deepest nodes first
      std::vector<CEvaluationNode*>::const_reverse_iterator it = nodes.rbegin(), endit = nodes.rend();
      CEvaluationNode* pOperator = new CEvaluationNodeOperator(type, data);
      CEvaluationNode* pChild2 = (*it)->copyBranch();
      ++it;
      CEvaluationNode* pChild1 = (*it)->copyBranch();
      pOperator->addChild(pChild1->copyBranch());
      pOperator->addChild(pChild2->copyBranch());
      ++it;
      pChild2 = pOperator;
      while (it != endit)
        {
          pOperator = new CEvaluationNodeOperator(type, data);
          pOperator->addChild((*it)->copyBranch());
          pOperator->addChild(pChild2);
          pChild2 = pOperator;
          ++it;
        }
      pResult = pOperator;
    }
  return pResult;
}

void CNormalTranslation::findSummands(const CEvaluationNode* pRoot, std::vector<const CEvaluationNode*>& summands)
{
  if (CEvaluationNode::type(pRoot->getType()) == CEvaluationNode::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pRoot->getType())) == CEvaluationNodeOperator::PLUS)
    {
      const CEvaluationNode* pChild1 = dynamic_cast<const CEvaluationNode*>(pRoot->getChild());
      assert(pChild1 != NULL);
      if (pChild1 != NULL)
        {
          const CEvaluationNode* pChild2 = dynamic_cast<const CEvaluationNode*>(pChild1->getSibling());
          assert(pChild2 != NULL);
          if (pChild2 != NULL)
            {
              assert(pChild2->getSibling() == NULL);
              if (CEvaluationNode::type(pChild1->getType()) == CEvaluationNode::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild1->getType())) == CEvaluationNodeOperator::PLUS)
                {
                  CNormalTranslation::findSummands(pChild1, summands);
                }
              else
                {
                  summands.push_back(pChild1);
                }
              if (CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild2->getType())) == CEvaluationNodeOperator::PLUS)
                {
                  CNormalTranslation::findSummands(pChild2, summands);
                }
              else
                {
                  summands.push_back(pChild2);
                }
            }
        }
    }
  else
    {
      summands.push_back(pRoot);
    }
}

// new routines

/**
 * This method elminates subexpressions from an expression
 */
CEvaluationNode* CNormalTranslation::eliminate(const CEvaluationNode* pOrig)
{
  CEvaluationNode* pResult = pOrig->copyBranch();
  CEvaluationNode* pTmp = NULL;
  //CNormalFraction* base = createNormalRepresentation(pOrig);
  //assert(base != NULL);
  std::string infix = pResult->getInfix(); //base->toString();
  std::cout << "Eliminate start: " << infix << std::endl;
  //delete base;
  bool changed = true;
  while (changed)
    {
      // first make elementary eliminations
      pTmp = CNormalTranslation::elementaryElimination(pResult);
      delete pResult;
      // now get rid of nested powers a^b^c
      pResult = CNormalTranslation::eliminateNestedPowers(pTmp);
      delete pTmp;
      // now cancel since cancelation can lead to new nodes for which
      // elementary elimination would be possible, we might have to run
      // this loop again
      pTmp = CNormalTranslation::cancel(pResult);
      delete pResult;
      // check if we are done
      // we are done if the infix has not changed over one loop run
      //base = createNormalRepresentation(pResult);
      //assert(base != NULL);
      if (/*base->toString()*/pTmp->getInfix() == infix)
        {
          changed = false;
        }
      else
        {
          infix = pTmp->getInfix(); //base->toString();
          std::cout << "Eliminate end: " << infix << std::endl;
        }
      pResult = pTmp;
      //delete base;
      //base = NULL;
    }
  return pResult;
}

/**
 * This routine is responsible for recursively simplifying a given
 * CEvaluationNode based tree.
 */
CEvaluationNode* CNormalTranslation::simplify(const CEvaluationNode* pOrig)
{
  CEvaluationNode* pResult = NULL;
  bool finished = false;
  //CNormalFraction* base = createNormalRepresentation(pOrig);
  //assert(base != NULL);
  std::string infix = pOrig->getInfix(); //base->toString();
  std::string infix2 = infix;
  std::cout << "Simplify start: " << infix << std::endl;
  //delete base;
  //base = NULL;
  CEvaluationNode* pTmp = pOrig->copyBranch();
  while (!finished)
    {
      pResult = CNormalTranslation::eliminate(pTmp);
      delete pTmp;
      /*
      bool changed = true;
      while (changed)
        {
          // first make elementary eliminations
          pResult = CNormalTranslation::elementaryElimination(pOrig);
          // now get rid of nested powers a^b^c
          pTmp = CNormalTranslation::eliminateNestedPowers(pResult);
          delete pResult;
          // now cancel since cancelation can lead to new nodes for which
          // elementary elimination would be possible, we might have to run
          // this loop again
          pResult = CNormalTranslation::cancel(pTmp);
          delete pTmp;
          // check if we are done
          // we are done if the infix has not changed over one loop run
          base = createNormalRepresentation(pResult);
          assert(base != NULL);
          if (base->toString() == infix2)
            {
              changed = false;
            }
          else
            {
              infix2 = base->toString();
            }
          delete base;
          base = NULL;
        }
      */
      // now we evaluate everything that can be evaluated, e.g. operations on
      // numbers
      pTmp = CNormalTranslation::evaluateNumbers(pResult);
      delete pResult;
      // this method combines identical multiplicants and summands
      pResult = CNormalTranslation::cancel(pTmp);
      delete pTmp;
      // now expand the exponents in the power nodes and multiply products
      // expansions can lead to new cancelations being possible so we might
      // need to rerun the whole loop
      pTmp = CNormalTranslation::expandPowerNodes(pResult);
      delete pResult;
      pResult = CNormalTranslation::expandProducts(pTmp);
      delete pTmp;
      // check if we are done
      // we are done, once the infix has not changed during one loop run
      //base = createNormalRepresentation(pResult);
      //assert(base != NULL);
      if (/*base->toString()*/pResult->getInfix() == infix)
        {
          finished = true;
        }
      else
        {
          infix = pResult->getInfix(); //base->toString();
          std::cout << "Simplify end: " << infix << std::endl;
        }
      //delete base;
      //base = NULL;
      pTmp = pResult;
    }
  return pResult;
}

/**
 * This routine is responsible for all elementary eliminations, e.g. addition
 * of 0.
 * These steps can not lead to new simplifications in the children of the node
 * being simplified, so it is not necessary to run this on the children again.
 */
CEvaluationNode* CNormalTranslation::elementaryElimination(const CEvaluationNode* pOrig)
{
  // this is done depth first
  CEvaluationNode* pResult = NULL;
  std::vector<CEvaluationNode*> children;
  const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pOrig->getChild());
  while (pChild != NULL)
    {
      CEvaluationNode* pNewChild = elementaryElimination(pChild);
      assert(pNewChild != NULL);
      children.push_back(pNewChild);
      pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
    }
  if (CEvaluationNode::type(pOrig->getType()) == CEvaluationNode::OPERATOR)
    {
      // check if we can eliminate anything
      // check if one of the children is (-)0, (-)1, NaN or INFINITY
      assert(children.size() == 2);
      switch ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOrig->getType()))
        {
        case CEvaluationNodeOperator::POWER:
          pResult = CNormalTranslation::elementaryEliminationPower(pOrig, children);
          break;
        case CEvaluationNodeOperator::MODULUS:
          pResult = CNormalTranslation::elementaryEliminationModulus(pOrig, children);
          break;
        case CEvaluationNodeOperator::MULTIPLY:
          pResult = CNormalTranslation::elementaryEliminationMultiply(pOrig, children);
          break;
        case CEvaluationNodeOperator::DIVIDE:
          pResult = CNormalTranslation::elementaryEliminationDivide(pOrig, children);
          break;
        case CEvaluationNodeOperator::PLUS:
          pResult = CNormalTranslation::elementaryEliminationPlus(pOrig, children);
          break;
        case CEvaluationNodeOperator::MINUS:
          pResult = CNormalTranslation::elementaryEliminationMinus(pOrig, children);
          break;
        default:
          // we should never end up here
          fatalError();
          break;
        }
    }
  else if (CEvaluationNode::type(pOrig->getType()) == CEvaluationNode::FUNCTION)
    {
      pResult = CNormalTranslation::elementaryEliminationFunction(pOrig, children);
    }
  else
    {
      // just make a swallow copy of the original node
      // and add the new children
      pResult = pOrig->copyNode(children);
    }
  return pResult;
}

/**
 * This method makes elementary eliminations on function nodes
 */
CEvaluationNode* CNormalTranslation::elementaryEliminationFunction(const CEvaluationNode* pFunctionNode, std::vector<CEvaluationNode*>& children)
{
  // PLUS(X) -> X
  // X(NaN) -> NaN
  // MINUX(X) where X is a number -> -X
  CEvaluationNode* pResult = NULL;
  unsigned int i, iMax = children.size();
  switch ((CEvaluationNodeFunction::SubType)CEvaluationNode::subType(pFunctionNode->getType()))
    {
    case CEvaluationNodeFunction::INVALID:
      break;
    case CEvaluationNodeFunction::PLUS:
      assert(children.size() == 1);
      pResult = children[0];
      break;
    case CEvaluationNodeFunction::MINUS:
      assert(children.size() == 1);
      if (CEvaluationNode::type(children[0]->getType()) == CEvaluationNode::NUMBER)
        {
          std::ostringstream os;
          os.precision(18);
          os << -1.0*dynamic_cast<const CEvaluationNodeNumber*>(children[0])->value();
          pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, os.str().c_str());
        }
      else if (CEvaluationNode::type(children[0]->getType()) == CEvaluationNode::CONSTANT &&
               ((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(children[0]->getType())) == CEvaluationNodeConstant::_NaN)
        {
          pResult = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "NaN");
        }
      if (pResult != NULL)
        {
          // delete the unused children
          delete children[0];
        }
      else
        {
          // MINUS(X) -> -1.0 * X
          pResult = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
          pResult->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "-1.0"));
          pResult->addChild(children[0]);
        }
      break;
    default:
      for (i = 0;i < iMax;++i)
        {
          if (CEvaluationNode::type(children[i]->getType()) == CEvaluationNode::CONSTANT && ((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(children[i]->getType())) == CEvaluationNodeConstant::_NaN)
            {
              pResult = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "NaN");
              break;
            }
        }
      if (pResult != NULL)
        {
          // delete the unused children
          for (i = 0;i < iMax;++i)
            {
              delete children[i];
            }
        }
      else
        {
          // make a copy of the original node and add the children
          pResult = pFunctionNode->copyNode(children);
        }
      break;
    }
  return pResult;
}

/**
 * This method makes the elementary elimination on a power node.
 */
CEvaluationNode* CNormalTranslation::elementaryEliminationPower(const CEvaluationNode* pPowerNode, const std::vector<CEvaluationNode*>& children)
{
  CEvaluationNode* pResult = NULL;
  assert(CEvaluationNode::type(pPowerNode->getType()) == CEvaluationNode::OPERATOR);
  assert(((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pPowerNode->getType())) == CEvaluationNodeOperator::POWER);
  assert(children.size() == 2);
  if (CEvaluationNode::type(children[0]->getType()) == CEvaluationNode::NUMBER)
    {
      // 0 and 1
      CEvaluationNodeNumber* pNumberNode = dynamic_cast<CEvaluationNodeNumber*>(children[0]);
      assert(pNumberNode != NULL);
      double value = pNumberNode->value();
      if (fabs(value) < ZERO)
        {
          // 0^(NaN) -> NaN
          if (children[1]->getType() == CEvaluationNode::CONSTANT && ((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(children[1]->getType())) == CEvaluationNodeConstant::_NaN)
            {
              pResult = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "NaN");
              // delete the unused children
              delete children[0];
              delete children[1];
            }
          else if (children[1]->getType() == CEvaluationNode::NUMBER)
            {
              CEvaluationNodeNumber* pNumberNode2 = dynamic_cast<CEvaluationNodeNumber*>(children[1]);
              double value = pNumberNode2->value();
              // 0^0 -> NaN
              // 0^(-x) -> NaN
              if (fabs(value) < ZERO || value < 0.0)
                {
                  pResult = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "NaN");
                  // delete the unused children
                  delete children[0];
                  delete children[1];
                }
            }
          // 0^x -> 0
          if (pResult == NULL)
            {
              pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.0");
              // delete the unused children
              delete children[0];
              delete children[1];
            }
        }
      else if (fabs(value - 1.0) < ZERO)
        {
          // 1^NaN -> NaN
          // 1^x -> 1
          if (CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::CONSTANT && ((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(children[1]->getType())) == CEvaluationNodeConstant::_NaN)
            {
              pResult = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "NaN");
              // delete the unused children
              delete children[0];
              delete children[1];
            }
          if (pResult == NULL)
            {
              pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");
              // delete the unused children
              delete children[0];
              delete children[1];
            }
        }
      /* ignore -1 for now
         else if(fabs(value + 1.0) < ZERO)
         {
         }
         */
    }
  else if (CEvaluationNode::type(children[0]->getType()) == CEvaluationNode::CONSTANT)
    {
      // infinity and NaN
      if (((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(children[0]->getType())) == CEvaluationNodeConstant::_NaN)
        {
          // NaN^x -> NaN
          pResult = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "NaN");
          // delete the unused children
          delete children[0];
          delete children[1];
        }
      else if (((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(children[0]->getType())) == CEvaluationNodeConstant::_INFINITY)
        {
          // INFINITY^(-NaN) -> NaN
          // INFINITY^-x -> 0.0 // x being a positive number
          // INFINITY^x -> INFINITY // x being a positive number
          // INFINITY^0 -> 1
          if (CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::NUMBER)
            {
              CEvaluationNodeNumber* pNumberNode2 = dynamic_cast<CEvaluationNodeNumber*>(children[1]);
              assert(pNumberNode2 != NULL);
              double value = pNumberNode2->value();
              // INFINITY^0 -> 1
              if (fabs(value) < ZERO)
                {
                  pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");
                  // delete the unused children
                  delete children[0];
                  delete children[1];
                }
              // INFINITY^x -> INFINITY // x being a positive number
              else if (value > 0.0)
                {
                  pResult = new CEvaluationNodeConstant(CEvaluationNodeConstant::_INFINITY, "inf");
                  // delete the unused children
                  delete children[0];
                  delete children[1];
                }
              // INFINITY^-x -> 0.0 // x being a positive number
              else
                {
                  pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.0");
                  // delete the unused children
                  delete children[0];
                  delete children[1];
                }
            }
          else if (CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::CONSTANT && ((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(children[1]->getType())) == CEvaluationNodeConstant::_NaN)
            {
              // INFINITY^NaN    -> NaN
              pResult = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "NaN");
              // delete the unused children
              delete children[0];
              delete children[1];
            }
          /* the minus function is eliminated
          else if(CEvaluationNode::type(children[1]->getType())==CEvaluationNode::FUNCTION && ((CEvaluationNodeFunction::SubType)CEvaluationNode::subType(children[1]->getType()))==CEvaluationNodeFunction::MINUS)
          {
              CEvaluationNode* pChild=dynamic_cast<CEvaluationNode*>(children[1]->getChild());
              // INFINITY^(-CONSTANT) -> 0.0 // where CONSTANT != NaN
              if(CEvaluationNode::type(pChild->getType())==CEvaluationNode::CONSTANT)
              {
                  pResult=new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE,"0.0");
                  // delete the unused children
                  delete children[0];
                  delete children[1];
              }
          }
          */
          else if (CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::NUMBER)
            {
              CEvaluationNodeNumber* pNumberNode2 = dynamic_cast<CEvaluationNodeNumber*>(children[1]);
              assert(pNumberNode2 != NULL);
              double value = pNumberNode2->value();
              // INFINITY^0 -> 1.0
              if (fabs(value) < ZERO)
                {
                  pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");
                  // delete the unused children
                  delete children[0];
                  delete children[1];
                }
              // INFINITY^(-x) -> 0.0
              else if (value > 0.0)
                {
                  pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.0");
                  // delete the unused children
                  delete children[0];
                  delete children[1];
                }
              // INFINITY^x -> INFINITY
              else
                {
                  pResult = new CEvaluationNodeConstant(CEvaluationNodeConstant::_INFINITY, "inf");
                  // delete the unused children
                  delete children[0];
                  delete children[1];
                }
            }
          // INFINITY ^ x -> INFINITY
          if (pResult == NULL)
            {
              pResult = new CEvaluationNodeConstant(CEvaluationNodeConstant::_INFINITY, "inf");
              // delete the unused children
              delete children[0];
              delete children[1];
            }
        }
    }
  /* the minus function is eliminated
  else if((CEvaluationNode::type(children[0]->getType())==CEvaluationNode::FUNCTION) && (((CEvaluationNodeFunction::SubType)CEvaluationNode::subType(children[0]->getType()))==CEvaluationNodeFunction::MINUS) && (CEvaluationNode::type(dynamic_cast<CEvaluationNode*>(children[0]->getChild())->getType())==CEvaluationNode::CONSTANT))
  {
      if(((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(dynamic_cast<CEvaluationNode*>(children[0]->getChild())->getType()))==CEvaluationNodeConstant::_INFINITY)
      {
          // -INFINITY^0 -> 1.0
          // -INFINITY^-NaN -> NaN
          // -INFINITY^-INFINITY -> 0.0
          // -INFINITY^-x where x is a positve number -> 0.0
          if(CEvaluationNode::type(children[1]->getType())==CEvaluationNode::CONSTANT)
          {
              // -INFINITY^NaN -> NaN
              // -INFINITY^INFINITY -> NaN ???
              if(((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(children[1]->getType()))==CEvaluationNodeConstant::_NaN || ((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(children[1]->getType()))==CEvaluationNodeConstant::_INFINITY)
              {
                  pResult=new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN,"NaN");
                  // delete the unused children
                  delete children[0];
                  delete children[1];
              }
          }
          else if(CEvaluationNode::type(children[1]->getType())==CEvaluationNode::NUMBER)
          {
              CEvaluationNodeNumber* pNumberNode2=dynamic_cast<CEvaluationNodeNumber*>(children[1]);
              double value=pNumberNode2->value();
              // -INFINITY^0 -> 1.0
              if(fabs(value) < ZERO)
              {
                  pResult=new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE,"1.0");
                  // delete the unused children
                  delete children[0];
                  delete children[1];
              }
              // -INFINITY^-x where x is a positive number -> 0.0
              else if(value < 0.0)
              {
                  pResult=new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE,"0.0");
                  // delete the unused children
                  delete children[0];
                  delete children[1];
              }
          }
          else if(CEvaluationNode::type(children[1]->getType())==CEvaluationNode::FUNCTION && ((CEvaluationNodeFunction::SubType)CEvaluationNode::subType(children[1]->getType()))==CEvaluationNodeFunction::MINUS)
          {
              CEvaluationNode* pChild=dynamic_cast<CEvaluationNode*>(children[1]->getChild());
              assert(pChild!=NULL);
              if(CEvaluationNode::type(pChild->getType())==CEvaluationNode::CONSTANT)
              {
                  // -INFINITY^-NaN -> NaN
                  if(((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(pChild->getType()))==CEvaluationNodeConstant::_NaN)
                  {
                      pResult=new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN,"NaN");
                      // delete the unused children
                      delete children[0];
                      delete children[1];
                  }
              }
              else if(CEvaluationNode::type(pChild->getType())==CEvaluationNode::NUMBER)
              {
                  CEvaluationNodeNumber* pNumberNode2=dynamic_cast<CEvaluationNodeNumber*>(pChild);
                  double value=pNumberNode2->value();
                  // -INFINITY^0 -> 1.0
                  if(fabs(value) < ZERO)
                  {
                      pResult=new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE,"1.0");
                      // delete the unused children
                      delete children[0];
                      delete children[1];
                  }
                  // -INFINITY^-x where x is a positive number -> 0.0
                  else if(value > 0.0)
                  {
                      pResult=new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE,"0.0");
                      // delete the unused children
                      delete children[0];
                      delete children[1];
                  }
              }
          }
          // ignore the rest
      }
  }
  */
  else if (CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::NUMBER)
    {
      // 0 and 1
      CEvaluationNodeNumber* pNumberNode2 = dynamic_cast<CEvaluationNodeNumber*>(children[1]);
      assert(pNumberNode2 != NULL);
      double value = pNumberNode2->value();
      // x^0 -> 1.0
      if (fabs(value) < ZERO)
        {
          pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");
          // delete the unused children
          delete children[0];
          delete children[1];
        }
      else if (fabs(value - 1.0) < ZERO)
        {
          // make a deep copy of the first child
          pResult = children[0];
          // delete the unused child
          delete children[1];
        }
      /* ignore -1 since this may interfere with other simplification
       * mechanisms.
       * Negative exponents will be eliminated in the end.
       else if(fabs(value + 1.0) < ZERO)
       {
       }
       */
    }
  else if (CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::CONSTANT)
    {
      // infinity and NaN
      if (((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(children[1]->getType())) == CEvaluationNodeConstant::_NaN)
        {
          pResult = children[1];
          // delete the unused child
          delete children[0];
        }
      else if (((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(children[1]->getType())) == CEvaluationNodeConstant::_INFINITY)
        {
          pResult = children[1];
          // delete the unused child
          delete children[0];
        }
    }
  /* The minus function is eliminated
  else if((CEvaluationNode::type(children[1]->getType())==CEvaluationNode::FUNCTION) && (((CEvaluationNodeFunction::SubType)CEvaluationNode::subType(children[1]->getType()))==CEvaluationNodeFunction::MINUS) && (CEvaluationNode::type(dynamic_cast<CEvaluationNode*>(children[1]->getChild())->getType())==CEvaluationNode::CONSTANT))
  {
      // x^-INFINITY -> 0.0
      if(((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(dynamic_cast<CEvaluationNode*>(children[1]->getChild())->getType()))==CEvaluationNodeConstant::_INFINITY)
      {
          pResult=new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE,"0.0");
          // delete the unused children
          delete children[0];
          delete children[1];
      }
  }
  */
  if (pResult == NULL)
    {
      // none of the above conditions was true so pResult is still unset
      // just make a shallow copy of the original node and add the children
      pResult = pPowerNode->copyNode(children);
    }
  return pResult;
}

/**
 * This method makes the elementary elimination on a modulus node.
 */
CEvaluationNode* CNormalTranslation::elementaryEliminationModulus(const CEvaluationNode* pModulusNode, const std::vector<CEvaluationNode*>& children)
{
  CEvaluationNode* pResult = NULL;
  assert(CEvaluationNode::type(pModulusNode->getType()) == CEvaluationNode::OPERATOR);
  assert(((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pModulusNode->getType())) == CEvaluationNodeOperator::MODULUS);
  assert(children.size() == 2);
  // if one child is NaN, the result is NaN
  if ((CEvaluationNode::type(children[0]->getType()) == CEvaluationNode::CONSTANT &&
       ((CEvaluationNodeConstant::SubType)(CEvaluationNode::subType(children[0]->getType()))) == CEvaluationNodeConstant::_NaN) ||
      (CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::CONSTANT &&
       ((CEvaluationNodeConstant::SubType)(CEvaluationNode::subType(children[1]->getType()))) == CEvaluationNodeConstant::_NaN))
    {
      pResult = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "Nan");
      // delete the unused children
      delete children[0];
      delete children[1];
    }
  // X%X -> 0
  CNormalFraction* base1 = createNormalRepresentation(children[0]);
  CNormalFraction* base2 = createNormalRepresentation(children[1]);
  if (base1->toString() == base2->toString())
    {
      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.0");
      // delete the unused children
      delete children[0];
      delete children[1];
    }
  else if (CEvaluationNode::type(children[0]->getType()) == CEvaluationNode::NUMBER)
    {
      // 0 and 1
      CEvaluationNodeNumber* pNumberNode = dynamic_cast<CEvaluationNodeNumber*>(children[0]);
      assert(pNumberNode != NULL);
      double value = pNumberNode->value();
      if (fabs(value) < ZERO)
        {
          pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.0");
          // delete the unused children
          delete children[0];
          delete children[1];
        }
      else if (fabs(value - 1.0) < ZERO)
        {
          // 1%X where X is any number other than 1 will give 1.0
          // the case where X is 1 is already covered above
          if (CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::NUMBER)
            {
              pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");
              // delete the unused children
              delete children[0];
              delete children[1];
            }
        }
      // ignore the rest
    }
  /* ignored for now
  else if(CEvaluationNode::type(children[0]->getType())==CEvaluationNode::CONSTANT)
  {
      // infinity (NaN is already covered above)
      else if(((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(children[0]->getType()))==CEvaluationNodeConstant::_INFINITY)
      {
      }
  }
  else if((CEvaluationNode::type(children[0]->getType())==CEvaluationNode::FUNCTION) && (((CEvaluationNodeFunction::SubType)CEvaluationNode::subType(children[0]->getType()))==CEvaluationNodeFunction::MINUS) && (CEvaluationNode::type(dynamic_cast<CEvaluationNode*>(children[0]->getChild())->getType())==CEvaluationNode::CONSTANT))
  {
      // -INFINITY
      if(((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(dynamic_cast<CEvaluationNode*>(children[0]->getChild())->getType()))==CEvaluationNodeConstant::_INFINITY)
      {
      }
  }
  */
  else if (CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::NUMBER)
    {
      // 0 and 1
    }
  /* ignored for now
  else if(CEvaluationNode::type(children[1]->getType())==CEvaluationNode::CONSTANT)
  {
      // infinity (NaN is already covered above)
      else if(((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(children[1]->getType()))==CEvaluationNodeConstant::_INFINITY)
      {
      }
  }
  else if((CEvaluationNode::type(children[1]->getType())==CEvaluationNode::FUNCTION) && (((CEvaluationNodeFunction::SubType)CEvaluationNode::subType(children[1]->getType()))==CEvaluationNodeFunction::MINUS) && (CEvaluationNode::type(dynamic_cast<CEvaluationNode*>(children[1]->getChild())->getType())==CEvaluationNode::CONSTANT))
  {
      // -INFINITY
      if(((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(dynamic_cast<CEvaluationNode*>(children[1]->getChild())->getType()))==CEvaluationNodeConstant::_INFINITY)
      {
      }
  }
  */
  delete base1;
  delete base2;
  base1 = NULL;
  base2 = NULL;
  if (pResult == NULL)
    {
      // none of the above conditions was true so pResult is still unset
      // just make a shallow copy of the original node and add the children
      pResult = pModulusNode->copyNode(children);
    }
  return pResult;
}

/**
 * This method makes the elementary elimination on a multiply node.
 */
CEvaluationNode* CNormalTranslation::elementaryEliminationMultiply(const CEvaluationNode* pMultiplyNode, const std::vector<CEvaluationNode*>& children)
{
  CEvaluationNode* pResult = NULL;
  assert(CEvaluationNode::type(pMultiplyNode->getType()) == CEvaluationNode::OPERATOR);
  assert(((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pMultiplyNode->getType())) == CEvaluationNodeOperator::MULTIPLY);
  assert(children.size() == 2);
  // if one child is NaN, the result is NaN
  if ((CEvaluationNode::type(children[0]->getType()) == CEvaluationNode::CONSTANT &&
       ((CEvaluationNodeConstant::SubType)(CEvaluationNode::subType(children[0]->getType()))) == CEvaluationNodeConstant::_NaN) ||
      (CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::CONSTANT &&
       ((CEvaluationNodeConstant::SubType)(CEvaluationNode::subType(children[1]->getType()))) == CEvaluationNodeConstant::_NaN))
    {
      pResult = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "Nan");
      // delete the unused children
      delete children[0];
      delete children[1];
    }
  // if one child is 0, the result is 0
  else if ((CEvaluationNode::type(children[0]->getType()) == CEvaluationNode::NUMBER &&
            fabs(dynamic_cast<const CEvaluationNodeNumber*>(children[0])->value())< ZERO) ||
           (CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::NUMBER &&
            fabs(dynamic_cast<const CEvaluationNodeNumber*>(children[1])->value())< ZERO))
    {
      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.0");
      // delete the unused children
      delete children[0];
      delete children[1];
    }
  // if one child is 1, the result is the other child
  else if ((CEvaluationNode::type(children[0]->getType()) == CEvaluationNode::NUMBER &&
            fabs(dynamic_cast<const CEvaluationNodeNumber*>(children[0])->value() - 1.0)< ZERO))
    {
      pResult = children[1];
      // delete the unused child
      delete children[0];
    }
  else if ((CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::NUMBER &&
            fabs(dynamic_cast<const CEvaluationNodeNumber*>(children[1])->value() - 1.0)< ZERO))
    {
      pResult = children[0];
      // delete the unused child
      delete children[1];
    }
  /* ignored for now
  else if(CEvaluationNode::type(children[0]->getType())==CEvaluationNode::CONSTANT)
  {
      // infinity (NaN is already covered above)
      if(((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(children[0]->getType()))==CEvaluationNodeConstant::_INFINITY)
      {
      }
  }
  else if(CEvaluationNode::type(children[1]->getType())==CEvaluationNode::CONSTANT)
  {
      // infinity (NaN is already covered above)
      if(((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(children[1]->getType()))==CEvaluationNodeConstant::_INFINITY)
      {
      }
  }

  else if((CEvaluationNode::type(children[0]->getType())==CEvaluationNode::FUNCTION) && (((CEvaluationNodeFunction::SubType)CEvaluationNode::subType(children[0]->getType()))==CEvaluationNodeFunction::MINUS) && (CEvaluationNode::type(dynamic_cast<CEvaluationNode*>(children[0]->getChild())->getType())==CEvaluationNode::CONSTANT))
  {
      // -INFINITY
      if(((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(dynamic_cast<CEvaluationNode*>(children[0]->getChild())->getType()))==CEvaluationNodeConstant::_INFINITY)
      {
      }
  }
  else if((CEvaluationNode::type(children[1]->getType())==CEvaluationNode::FUNCTION) && (((CEvaluationNodeFunction::SubType)CEvaluationNode::subType(children[1]->getType()))==CEvaluationNodeFunction::MINUS) && (CEvaluationNode::type(dynamic_cast<CEvaluationNode*>(children[1]->getChild())->getType())==CEvaluationNode::CONSTANT))
  {
      // -INFINITY
      if(((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(dynamic_cast<CEvaluationNode*>(children[1]->getChild())->getType()))==CEvaluationNodeConstant::_INFINITY)
      {
      }
  }
  */
  if (pResult == NULL)
    {
      // none of the above conditions was true so pResult is still unset
      // just make a shallow copy of the original node and add the children
      pResult = pMultiplyNode->copyNode(children);
    }
  return pResult;
}

/**
 * This method makes the elementary elimination on a divide node.
 */
CEvaluationNode* CNormalTranslation::elementaryEliminationDivide(const CEvaluationNode* pDivideNode, const std::vector<CEvaluationNode*>& children)
{
  CEvaluationNode* pResult = NULL;
  assert(CEvaluationNode::type(pDivideNode->getType()) == CEvaluationNode::OPERATOR);
  assert(((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pDivideNode->getType())) == CEvaluationNodeOperator::DIVIDE);
  assert(children.size() == 2);
  // if one of the children is NaN, the result is NaN
  CNormalFraction* base1 = createNormalRepresentation(children[0]);
  CNormalFraction* base2 = createNormalRepresentation(children[1]);
  if ((CEvaluationNode::type(children[0]->getType()) == CEvaluationNode::CONSTANT &&
       ((CEvaluationNodeConstant::SubType)(CEvaluationNode::subType(children[0]->getType()))) == CEvaluationNodeConstant::_NaN) ||
      (CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::CONSTANT &&
       ((CEvaluationNodeConstant::SubType)(CEvaluationNode::subType(children[1]->getType()))) == CEvaluationNodeConstant::_NaN))
    {
      pResult = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "Nan");
      // delete the unused children
      delete children[0];
      delete children[1];
    }
  // the second child is 0, the result is NaN
  else if ((CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::NUMBER &&
            fabs(dynamic_cast<const CEvaluationNodeNumber*>(children[1])->value())< ZERO))
    {
      pResult = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "NaN");
      // delete the unused children
      delete children[0];
      delete children[1];
    }
  // if the first child is 0, the result is 0
  else if ((CEvaluationNode::type(children[0]->getType()) == CEvaluationNode::NUMBER &&
            fabs(dynamic_cast<const CEvaluationNodeNumber*>(children[0])->value())< ZERO))
    {
      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.0");
      // delete the unused children
      delete children[0];
      delete children[1];
    }
  // if both children are the same, the result is 1
  else if (base1->toString() == base2->toString())
    {
      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");
      // delete the unused children
      delete children[0];
      delete children[1];
    }
  // if the second child is 1, the result is the first child
  else if ((CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::NUMBER &&
            fabs(dynamic_cast<const CEvaluationNodeNumber*>(children[1])->value() - 1.0)< ZERO))
    {
      pResult = children[0];
      // delete the unused child
      delete children[1];
    }
  /* for now, we ignore INFINITY since this complicates things
  // if the second child is INFINITY, the result is 0.0 (this is only true if
  // the first child does not contain infinity
  else if(CEvaluationNode::type(children[1]->getType())==CEvaluationNode::CONSTANT && ((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(children[1]->getType()))==CEvaluationNodeConstant::_INFINITY)
  {
      pResult=new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE,"0.0");
      // delete the unused children
      delete children[0];
      delete children[1];
  }
  // if the first child is INFINITY, the result is INFINITY
  else if(CEvaluationNode::type(children[0]->getType())==CEvaluationNode::CONSTANT && ((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(children[0]->getType()))==CEvaluationNodeConstant::_INFINITY)
  {
      pResult=children[1];
      // delete the unused child
      delete children[0];
  }
  */
  delete base1;
  delete base2;
  base1 = NULL;
  base2 = NULL;
  if (pResult == NULL)
    {
      // none of the above conditions was true so pResult is still unset
      // just make a shallow copy of the original node and add the children
      pResult = pDivideNode->copyNode(children);
    }
  return pResult;
}

/**
 * This method makes the elementary elimination on a plus node.
 */
CEvaluationNode* CNormalTranslation::elementaryEliminationPlus(const CEvaluationNode* pPlusNode, const std::vector<CEvaluationNode*>& children)
{
  CEvaluationNode* pResult = NULL;
  assert(CEvaluationNode::type(pPlusNode->getType()) == CEvaluationNode::OPERATOR);
  assert(((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pPlusNode->getType())) == CEvaluationNodeOperator::PLUS);
  assert(children.size() == 2);
  // if one child is NaN, the result is NaN
  if ((CEvaluationNode::type(children[0]->getType()) == CEvaluationNode::CONSTANT &&
       ((CEvaluationNodeConstant::SubType)(CEvaluationNode::subType(children[0]->getType()))) == CEvaluationNodeConstant::_NaN) ||
      (CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::CONSTANT &&
       ((CEvaluationNodeConstant::SubType)(CEvaluationNode::subType(children[1]->getType()))) == CEvaluationNodeConstant::_NaN))
    {
      pResult = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "Nan");
      // delete the unused children
      delete children[0];
      delete children[1];
    }
  // the second child is 0, the result is the first child
  else if ((CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::NUMBER &&
            fabs(dynamic_cast<const CEvaluationNodeNumber*>(children[1])->value())< ZERO))
    {
      pResult = children[0];
      // delete the unused child
      delete children[1];
    }
  // if the first child is 0, the result is the second child
  else if ((CEvaluationNode::type(children[0]->getType()) == CEvaluationNode::NUMBER &&
            fabs(dynamic_cast<const CEvaluationNodeNumber*>(children[0])->value())< ZERO))
    {
      pResult = children[1];
      // delete the unused child
      delete children[0];
    }
  if (pResult == NULL)
    {
      // none of the above conditions was true so pResult is still unset
      // just make a shallow copy of the original node and add the children
      pResult = pPlusNode->copyNode(children);
    }
  return pResult;
}

/**
 * This method makes the elementary elimination on a minus node.
 */
CEvaluationNode* CNormalTranslation::elementaryEliminationMinus(const CEvaluationNode* pMinusNode, const std::vector<CEvaluationNode*>& children)
{
  CEvaluationNode* pResult = NULL;
  assert(CEvaluationNode::type(pMinusNode->getType()) == CEvaluationNode::OPERATOR);
  assert(((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pMinusNode->getType())) == CEvaluationNodeOperator::MINUS);
  assert(children.size() == 2);
  // if one child is NaN, the result is NaN (one could also consider to put
  // the second condition first so that to NaN would cancel each other out
  CNormalFraction* base1 = createNormalRepresentation(children[0]);
  CNormalFraction* base2 = createNormalRepresentation(children[1]);
  if ((CEvaluationNode::type(children[0]->getType()) == CEvaluationNode::CONSTANT &&
       ((CEvaluationNodeConstant::SubType)(CEvaluationNode::subType(children[0]->getType()))) == CEvaluationNodeConstant::_NaN) ||
      (CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::CONSTANT &&
       ((CEvaluationNodeConstant::SubType)(CEvaluationNode::subType(children[1]->getType()))) == CEvaluationNodeConstant::_NaN))
    {
      pResult = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "Nan");
      // delete the unused children
      delete children[0];
      delete children[1];
    }
  // if both nodes are equal, the result is 0.0
  else if (base1->toString() == base2->toString())
    {
      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.0");
      // delete the unused children
      delete children[0];
      delete children[1];
    }
  // the second child is 0, the result is the first child
  else if ((CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::NUMBER &&
            fabs(dynamic_cast<const CEvaluationNodeNumber*>(children[1])->value())< ZERO))
    {
      pResult = children[0];
      // delete the unused child
      delete children[1];
    }
  // if the first child is 0, the result is -1 times the second child
  else if ((CEvaluationNode::type(children[0]->getType()) == CEvaluationNode::NUMBER &&
            fabs(dynamic_cast<const CEvaluationNodeNumber*>(children[0])->value())< ZERO))
    {
      pResult = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
      pResult->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0"));
      pResult->addChild(children[1]);
      // delete the unused child
      delete children[0];
    }
  delete base1;
  delete base2;
  base1 = NULL;
  base2 = NULL;
  if (pResult == NULL)
    {
      // none of the above conditions was true so pResult is still unset
      // just make a shallow copy of the original node and add the children
      pResult = pMinusNode->copyNode(children);
    }
  return pResult;
}

/**
 * This method evaluates operators acting on two numbers
 */
CEvaluationNode* CNormalTranslation::evaluateNumbers(const CEvaluationNode* pOrig)
{
  // TODO since the nodes are not ordered, it can happen that two number
  // TODO nodes in a chain are seperated by a nonnumber node.
  // TODO We have to find chains and evaluate all number nodes in the chain
  CEvaluationNode* pResult = NULL;
  std::vector<CEvaluationNode*> children;
  const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pOrig->getChild());
  while (pChild != NULL)
    {
      children.push_back(CNormalTranslation::evaluateNumbers(pChild));
      pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
    }
  if (CEvaluationNode::type(pOrig->getType()) == CEvaluationNode::OPERATOR)
    {
      assert(children.size() == 2);
      if (CEvaluationNode::type(children[0]->getType()) == CEvaluationNode::NUMBER && CEvaluationNode::type(children[1]->getType()) == CEvaluationNode::NUMBER)
        {
          const CEvaluationNodeNumber* pNumberNode1 = dynamic_cast<const CEvaluationNodeNumber*>(children[0]);
          const CEvaluationNodeNumber* pNumberNode2 = dynamic_cast<const CEvaluationNodeNumber*>(children[1]);
          std::ostringstream os;
          os.precision(18);
          switch ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOrig->getType()))
            {
            case CEvaluationNodeOperator::POWER:
              os << pow(pNumberNode1->value(), pNumberNode2->value());
              pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, os.str().c_str());
              break;
            case CEvaluationNodeOperator::MODULUS:
              os << (((int)pNumberNode1->value()) % ((int)pNumberNode2->value()));
              pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, os.str().c_str());
              break;
            case CEvaluationNodeOperator::MULTIPLY:
              os << (pNumberNode1->value()*pNumberNode2->value());
              pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, os.str().c_str());
              break;
            case CEvaluationNodeOperator::DIVIDE:
              os << (pNumberNode1->value() / pNumberNode2->value());
              pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, os.str().c_str());
              break;
            case CEvaluationNodeOperator::PLUS:
              os << (pNumberNode1->value() + pNumberNode2->value());
              pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, os.str().c_str());
              break;
            case CEvaluationNodeOperator::MINUS:
              os << (pNumberNode1->value() - pNumberNode2->value());
              pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, os.str().c_str());
              break;
            case CEvaluationNodeOperator::INVALID:
              break;
            }
          delete children[0];
          delete children[1];
        }
    }
  // TODO think about implementing some simplifications on function calls
  if (pResult == NULL)
    {
      pResult = pOrig->copyNode(children);
    }
  return pResult;
}

/**
 * This method removes nested power nodes, e.g. (a^b)^c -> a^(b*c)
 */
CEvaluationNode* CNormalTranslation::eliminateNestedPowers(const CEvaluationNode* pOrig)
{
  CEvaluationNode* pResult = NULL;
  std::vector<CEvaluationNode*> children;
  const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pOrig->getChild());
  while (pChild != NULL)
    {
      children.push_back(CNormalTranslation::eliminateNestedPowers(pChild));
      pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
    }
  if (CEvaluationNode::type(pOrig->getType()) == CEvaluationNode::OPERATOR &&
      ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOrig->getType())) == CEvaluationNodeOperator::POWER)
    {
      // check if the first child is also a power node
      assert(children.size() == 2);
      if (CEvaluationNode::type(children[0]->getType()) == CEvaluationNode::OPERATOR &&
          ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(children[0]->getType())) == CEvaluationNodeOperator::POWER)
        {
          pResult = new CEvaluationNodeOperator(CEvaluationNodeOperator::POWER, "^");
          const CEvaluationNode* pChild = dynamic_cast<CEvaluationNode*>(children[0]->getChild());
          assert(pChild != NULL);
          pResult->addChild(pChild->copyBranch());
          CEvaluationNode* pMult = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
          pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
          assert(pChild != NULL);
          pMult->addChild(pChild->copyBranch());
          pMult->addChild(children[1]);
          // delete the unused child
          delete children[0];
          pResult->addChild(pMult);
        }
    }
  if (pResult == NULL)
    {
      pResult = pOrig->copyNode(children);
    }
  return pResult;
}

/**
 * This method splits a product into the individual elements
 */
void CNormalTranslation::splitProduct(const CEvaluationNode* pRoot, std::vector<const CEvaluationNode*>& multiplications, std::vector<const CEvaluationNode*>& divisions, bool division)
{
  if (CEvaluationNode::type(pRoot->getType()) == CEvaluationNode::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pRoot->getType()) == CEvaluationNodeOperator::MULTIPLY || (CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pRoot->getType()) == CEvaluationNodeOperator::DIVIDE))
    {
      const CEvaluationNode* pChild1 = dynamic_cast<const CEvaluationNode*>(pRoot->getChild());
      assert(pChild1 != NULL);
      const CEvaluationNode* pChild2 = dynamic_cast<const CEvaluationNode*>(pChild1->getSibling());
      assert(pChild2 != NULL);
      assert(pChild2->getSibling() == NULL);
      if (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pRoot->getType())) == CEvaluationNodeOperator::MULTIPLY)
        {
          if (CEvaluationNode::type(pChild1->getType()) == CEvaluationNode::OPERATOR &&
              (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild1->getType())) == CEvaluationNodeOperator::MULTIPLY ||
               ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild1->getType())) == CEvaluationNodeOperator::DIVIDE))
            {
              CNormalTranslation::splitProduct(pChild1, multiplications, divisions, division);
            }
          else
            {
              if (division == false)
                {
                  multiplications.push_back(pChild1);
                }
              else
                {
                  divisions.push_back(pChild1);
                }
            }
          if (CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::OPERATOR &&
              (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild2->getType())) == CEvaluationNodeOperator::MULTIPLY ||
               ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild2->getType())) == CEvaluationNodeOperator::DIVIDE))
            {
              CNormalTranslation::splitProduct(pChild2, multiplications, divisions, division);
            }
          else
            {
              if (division == false)
                {
                  multiplications.push_back(pChild2);
                }
              else
                {
                  divisions.push_back(pChild2);
                }
            }
        }
      else if (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pRoot->getType())) == CEvaluationNodeOperator::DIVIDE)
        {
          if (CEvaluationNode::type(pChild1->getType()) == CEvaluationNode::OPERATOR &&
              (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild1->getType())) == CEvaluationNodeOperator::MULTIPLY ||
               ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild1->getType())) == CEvaluationNodeOperator::DIVIDE))
            {
              CNormalTranslation::splitProduct(pChild1, multiplications, divisions, !division);
            }
          else
            {
              if (division == false)
                {
                  multiplications.push_back(pChild1);
                }
              else
                {
                  divisions.push_back(pChild1);
                }
            }
          if (CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::OPERATOR &&
              (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild2->getType())) == CEvaluationNodeOperator::MULTIPLY ||
               ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild2->getType())) == CEvaluationNodeOperator::DIVIDE))
            {
              CNormalTranslation::splitProduct(pChild2, multiplications, divisions, !division);
            }
          else
            {
              if (division == false)
                {
                  divisions.push_back(pChild2);
                }
              else
                {
                  multiplications.push_back(pChild2);
                }
            }
        }
    }
  else
    {
      multiplications.push_back(pRoot);
    }
}

/**
 * This method splits a sum into the individual elements
 */
void CNormalTranslation::splitSum(const CEvaluationNode* pRoot, std::vector<CEvaluationNode*>& additions, std::vector<CEvaluationNode*>& subtractions, bool minus)
{
  if (CEvaluationNode::type(pRoot->getType()) == CEvaluationNode::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pRoot->getType()) == CEvaluationNodeOperator::PLUS || (CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pRoot->getType()) == CEvaluationNodeOperator::MINUS))
    {
      const CEvaluationNode* pChild1 = dynamic_cast<const CEvaluationNode*>(pRoot->getChild());
      assert(pChild1 != NULL);
      const CEvaluationNode* pChild2 = dynamic_cast<const CEvaluationNode*>(pChild1->getSibling());
      assert(pChild2 != NULL);
      assert(pChild2->getSibling() == NULL);
      if (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pRoot->getType())) == CEvaluationNodeOperator::PLUS)
        {
          if (CEvaluationNode::type(pChild1->getType()) == CEvaluationNode::OPERATOR &&
              (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild1->getType())) == CEvaluationNodeOperator::PLUS ||
               ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild1->getType())) == CEvaluationNodeOperator::MINUS))
            {
              CNormalTranslation::splitSum(pChild1, additions, subtractions, minus);
            }
          else
            {
              if (minus == false)
                {
                  additions.push_back(pChild1->copyBranch());
                }
              else
                {
                  subtractions.push_back(pChild1->copyBranch());
                }
            }
          if (CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::OPERATOR &&
              (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild2->getType())) == CEvaluationNodeOperator::PLUS ||
               ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild2->getType())) == CEvaluationNodeOperator::MINUS))
            {
              CNormalTranslation::splitSum(pChild2, additions, subtractions, minus);
            }
          else
            {
              if (minus == false)
                {
                  additions.push_back(pChild2->copyBranch());
                }
              else
                {
                  subtractions.push_back(pChild2->copyBranch());
                }
            }
        }
      else if (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pRoot->getType())) == CEvaluationNodeOperator::MINUS)
        {
          if (CEvaluationNode::type(pChild1->getType()) == CEvaluationNode::OPERATOR &&
              (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild1->getType())) == CEvaluationNodeOperator::PLUS ||
               ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild1->getType())) == CEvaluationNodeOperator::MINUS))
            {
              CNormalTranslation::splitSum(pChild1, additions, subtractions, !minus);
            }
          else
            {
              if (minus == false)
                {
                  additions.push_back(pChild1->copyBranch());
                }
              else
                {
                  subtractions.push_back(pChild1->copyBranch());
                }
            }
          if (CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::OPERATOR &&
              (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild2->getType())) == CEvaluationNodeOperator::PLUS ||
               ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pChild2->getType())) == CEvaluationNodeOperator::MINUS))
            {
              CNormalTranslation::splitSum(pChild2, additions, subtractions, !minus);
            }
          else
            {
              if (minus == false)
                {
                  subtractions.push_back(pChild2->copyBranch());
                }
              else
                {
                  additions.push_back(pChild2->copyBranch());
                }
            }
        }
    }
  else
    {
      additions.push_back(pRoot->copyBranch());
    }
  // check for negative numbers in additions and add them to subtractions
  // likewise check for negative numbers in substractions and add them to
  // additions
  // do the same for multiplications with a negative number
  std::vector<CEvaluationNode*>::iterator it = additions.begin();
  while (it != additions.end())
    {
      if (CEvaluationNode::type((*it)->getType()) == CEvaluationNode::NUMBER && dynamic_cast<const CEvaluationNodeNumber*>(*it)->value() < 0.0)
        {
          std::ostringstream os;
          os << static_cast<CEvaluationNodeNumber*>(*it)->value() * -1.0;
          os.precision(18);
          CEvaluationNode* pTmpNumber = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, os.str().c_str());
          subtractions.push_back(pTmpNumber);
          delete *it;
          it = additions.erase(it);
        }
      else if(CEvaluationNode::type((*it)->getType()) == CEvaluationNode::OPERATOR && (CEvaluationNodeOperator::SubType)CEvaluationNode::subType((*it)->getType()) == CEvaluationNodeOperator::MULTIPLY)
        {
          // actually there should be code that tests if both are negative
          // numbers
          if((CEvaluationNode::type(dynamic_cast<const CEvaluationNode*>((*it)->getChild())->getType()) == CEvaluationNode::NUMBER && dynamic_cast<const CEvaluationNodeNumber*>((*it)->getChild())->value() < 0.0))
            {
              if(fabs(dynamic_cast<const CEvaluationNodeNumber*>((*it)->getChild())->value()) - 1.0 < ZERO)
                {
                  subtractions.push_back(dynamic_cast<const CEvaluationNode*>((*it)->getChild()->getSibling())->copyBranch());
                  delete *it;
                  it = additions.erase(it);
                }
              else
                {
                  CEvaluationNode* pTmp = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
                  std::ostringstream os;
                  os << static_cast<const CEvaluationNodeNumber*>((*it)->getChild())->value() * -1.0;
                  os.precision(18);
                  pTmp->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, os.str().c_str()));
                  pTmp->addChild(dynamic_cast<const CEvaluationNode*>((*it)->getChild()->getSibling())->copyBranch());
                  subtractions.push_back(pTmp);
                  delete *it;
                  it = additions.erase(it);
                }
            }
          else if (CEvaluationNode::type(dynamic_cast<const CEvaluationNode*>((*it)->getChild()->getSibling())->getType()) == CEvaluationNode::NUMBER && dynamic_cast<const CEvaluationNodeNumber*>((*it)->getChild()->getSibling())->value() < 0.0)
            {
              if(fabs(dynamic_cast<const CEvaluationNodeNumber*>((*it)->getChild()->getSibling())->value()) - 1.0 < ZERO)
                {
                  subtractions.push_back(dynamic_cast<const CEvaluationNode*>((*it)->getChild())->copyBranch());
                  delete *it;
                  it = additions.erase(it);
                }
              else
                {
                  CEvaluationNode* pTmp = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
                  pTmp->addChild(dynamic_cast<const CEvaluationNode*>((*it)->getChild())->copyBranch());
                  std::ostringstream os;
                  os << static_cast<const CEvaluationNodeNumber*>((*it)->getChild()->getSibling())->value() * -1.0;
                  os.precision(18);
                  pTmp->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, os.str().c_str()));
                  subtractions.push_back(pTmp);
                  delete *it;
                  it = additions.erase(it);
                }
            }
          else
            {
              ++it;
            }
        }
      else
        {
          ++it;
        }
    }
  it = subtractions.begin();
  while (it != subtractions.end())
    {
      if (CEvaluationNode::type((*it)->getType()) == CEvaluationNode::NUMBER && dynamic_cast<const CEvaluationNodeNumber*>(*it)->value() < 0.0)
        {
          std::ostringstream os;
          os << static_cast<CEvaluationNodeNumber*>(*it)->value() * -1.0;
          os.precision(18);
          CEvaluationNode* pTmpNumber = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, os.str().c_str());
          additions.push_back(pTmpNumber);
          delete *it;
          it = subtractions.erase(it);
        }
      else if(CEvaluationNode::type((*it)->getType()) == CEvaluationNode::OPERATOR && (CEvaluationNodeOperator::SubType)CEvaluationNode::subType((*it)->getType()) == CEvaluationNodeOperator::MULTIPLY)
        {
          // actually there should be code that tests if both are negative
          // numbers
          if((CEvaluationNode::type(dynamic_cast<const CEvaluationNode*>((*it)->getChild())->getType()) == CEvaluationNode::NUMBER && dynamic_cast<const CEvaluationNodeNumber*>((*it)->getChild())->value() < 0.0))
            {
              if(fabs(dynamic_cast<const CEvaluationNodeNumber*>((*it)->getChild())->value()) - 1.0 < ZERO)
                {
                  additions.push_back(dynamic_cast<const CEvaluationNode*>((*it)->getChild()->getSibling())->copyBranch());
                  delete *it;
                  it = subtractions.erase(it);
                }
              else
                {
                  CEvaluationNode* pTmp = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
                  std::ostringstream os;
                  os << static_cast<const CEvaluationNodeNumber*>((*it)->getChild())->value() * -1.0;
                  os.precision(18);
                  pTmp->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, os.str().c_str()));
                  pTmp->addChild(dynamic_cast<const CEvaluationNode*>((*it)->getChild()->getSibling())->copyBranch());
                  additions.push_back(pTmp);
                  delete *it;
                  it = subtractions.erase(it);
                }
            }
          else if (CEvaluationNode::type(dynamic_cast<const CEvaluationNode*>((*it)->getChild()->getSibling())->getType()) == CEvaluationNode::NUMBER && dynamic_cast<const CEvaluationNodeNumber*>((*it)->getChild()->getSibling())->value() < 0.0)
            {
              if(fabs(dynamic_cast<const CEvaluationNodeNumber*>((*it)->getChild()->getSibling())->value()) - 1.0 < ZERO)
                {
                  additions.push_back(dynamic_cast<const CEvaluationNode*>((*it)->getChild())->copyBranch());
                  delete *it;
                  it = subtractions.erase(it);
                }
              else
                {
                  CEvaluationNode* pTmp = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
                  pTmp->addChild(dynamic_cast<const CEvaluationNode*>((*it)->getChild())->copyBranch());
                  std::ostringstream os;
                  os << static_cast<const CEvaluationNodeNumber*>((*it)->getChild()->getSibling())->value() * -1.0;
                  os.precision(18);
                  pTmp->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, os.str().c_str()));
                  additions.push_back(pTmp);
                  delete *it;
                  it = subtractions.erase(it);
                }
            }
          else
            {
              ++it;
            }
        }
      else
        {
          ++it;
        }
    }
}

/**
 * This method expands the exponents of power nodes, e.g. A^(x+y) -> A^x * A^y
 */
CEvaluationNode* CNormalTranslation::expandPowerNodes(const CEvaluationNode* pOrig)
{
  CEvaluationNode* pResult = NULL;
  std::vector<CEvaluationNode*> children;
  const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pOrig->getChild());
  while (pChild != NULL)
    {
      children.push_back(CNormalTranslation::expandPowerNodes(pChild));
      pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
    }
  if (CEvaluationNode::type(pOrig->getType()) == CEvaluationNode::OPERATOR &&
      ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOrig->getType())) == CEvaluationNodeOperator::POWER)
    {
      std::vector<CEvaluationNode*> additions, subtractions;
      CNormalTranslation::splitSum(children[1], additions, subtractions, false);
      // the root node is a fraction
      // the denominator is a product of all subtraction nodes
      // the numerator is a product of all addition nodes
      if (!additions.empty() || !subtractions.empty())
        {
          // replace all nodes in additions and subtractions by
          // children[0]^node so we can use the generic method to create the
          // multiplication chain
          unsigned int i, iMax = additions.size();
          for (i = 0;i < iMax;++i)
            {
              CEvaluationNode* pTmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::POWER, "^");
              pTmpNode->addChild(children[0]->copyBranch());
              // don't copy additions element since this has been created in
              // splitSum
              pTmpNode->addChild(additions[i]);
              additions[i] = pTmpNode;
            }
          iMax = subtractions.size();
          for (i = 0;i < iMax;++i)
            {
              CEvaluationNode* pTmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::POWER, "^");
              pTmpNode->addChild(children[0]->copyBranch());
              // don't copy subtractions element since this has been created in
              // splitSum
              pTmpNode->addChild(subtractions[i]);
              subtractions[i] = pTmpNode;
            }
          pResult = CNormalTranslation::createOperatorChain(CEvaluationNodeOperator::MULTIPLY, "*", additions);
          assert(pResult != NULL);
          if (!subtractions.empty())
            {
              CEvaluationNode* pTmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::DIVIDE, "/");
              pTmpNode->addChild(pResult);
              pResult = pTmpNode;
              pTmpNode = CNormalTranslation::createOperatorChain(CEvaluationNodeOperator::MULTIPLY, "*", subtractions);
              assert(pTmpNode != NULL);
              pResult->addChild(pTmpNode);
            }
          // delete the children
          delete children[0];
          delete children[1];
        }
    }
  if (pResult == NULL)
    {
      pResult = pOrig->copyNode(children);
    }
  return pResult;
}

/**
 * The methods get a vector of multiplication elements and a vector of division
 * elements and tries to find elements with the same power base in those two vectors.
 */
std::vector<std::pair<CEvaluationNode*, CEvaluationNode*> > CNormalTranslation::matchPowerBases(const std::vector<const CEvaluationNode*>& multiplications, const std::vector<const CEvaluationNode*>& divisions)
{
  std::vector<std::pair<const CEvaluationNode*, std::vector<CEvaluationNode*> > > matchMap;
  std::vector<const CEvaluationNode*>::const_iterator vit = multiplications.begin(), vendit = multiplications.end();
  while (vit != vendit)
    {
      const CEvaluationNode* pBase = (*vit);
      CEvaluationNode* pExponent = NULL;
      if (CEvaluationNode::type(pBase->getType()) == CEvaluationNode::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pBase->getType())) == CEvaluationNodeOperator::POWER)
        {
          pBase = dynamic_cast<const CEvaluationNode*>(pBase->getChild());
          pExponent = dynamic_cast<const CEvaluationNode*>(pBase->getSibling())->copyBranch();
        }
      else
        {
          pExponent = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");
        }
      // check if a base with the same infix is already in the map.
      // if not, add the base
      // if yes, add the exponent to the vector associated with the base
      std::vector<std::pair<const CEvaluationNode*, std::vector<CEvaluationNode*> > >::iterator mapIt = matchMap.begin(), mapEndit = matchMap.end();
      while (mapIt != mapEndit)
        {
          CNormalFraction* base1 = createNormalRepresentation(mapIt->first);
          CNormalFraction* base2 = createNormalRepresentation(pBase);
          if (base1->toString() == base2->toString())
            {
              mapIt->second.push_back(pExponent);
              delete base1;
              delete base2;
              break;
            }
          delete base1;
          delete base2;
          ++mapIt;
        }
      if (mapIt == mapEndit)
        {
          std::vector<CEvaluationNode*> v;
          v.push_back(pExponent);
          matchMap.push_back(std::make_pair(pBase, v));
        }
      ++vit;
    }
  std::vector<std::pair<const CEvaluationNode*, std::vector<CEvaluationNode*> > > matchMap2;
  vit = divisions.begin(), vendit = divisions.end();
  while (vit != vendit)
    {
      const CEvaluationNode* pBase = (*vit);
      CEvaluationNode* pExponent = NULL;
      if (CEvaluationNode::type(pBase->getType()) == CEvaluationNode::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pBase->getType())) == CEvaluationNodeOperator::POWER)
        {
          pBase = dynamic_cast<const CEvaluationNode*>(pBase->getChild());
          pExponent = dynamic_cast<const CEvaluationNode*>(pBase->getSibling())->copyBranch();
        }
      else
        {
          pExponent = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");
        }
      // check if a base with the same infix is already in the map.
      // if not, add the base
      // if yes, add the exponent to the vector associated with the base
      std::vector<std::pair<const CEvaluationNode*, std::vector<CEvaluationNode*> > >::iterator mapIt = matchMap2.begin(), mapEndit = matchMap2.end();
      while (mapIt != mapEndit)
        {
          CNormalFraction* base1 = createNormalRepresentation(mapIt->first);
          CNormalFraction* base2 = createNormalRepresentation(pBase);
          if (base1->toString() == base2->toString())
            {
              mapIt->second.push_back(pExponent);
              delete base1;
              delete base2;
              break;
            }
          delete base1;
          delete base2;
          ++mapIt;
        }
      if (mapIt == mapEndit)
        {
          std::vector<CEvaluationNode*> v;
          v.push_back(pExponent);
          matchMap2.push_back(std::make_pair(pBase, v));
        }
      ++vit;
    }
  // now combine the two maps
  std::vector<std::pair<CEvaluationNode*, CEvaluationNode*> > result;
  std::vector<std::pair<const CEvaluationNode*, std::vector<CEvaluationNode*> > >::iterator mapIt = matchMap.begin(), mapEndit = matchMap.end();
  while (mapIt != mapEndit)
    {
      std::vector<CEvaluationNode*> constVect;
      constVect.insert(constVect.begin(), mapIt->second.begin(), mapIt->second.end());
      CEvaluationNode* pNode = CNormalTranslation::createOperatorChain(CEvaluationNodeOperator::PLUS, "+", constVect);
      result.push_back(std::make_pair(pNode, mapIt->first->copyBranch()));
      // delete the obsolete nodes
      unsigned int i, iMax = mapIt->second.size();
      for (i = 0;i < iMax;++i)
        {
          delete mapIt->second[i];
        }
      ++mapIt;
    }
  mapIt = matchMap2.begin(), mapEndit = matchMap2.end();
  while (mapIt != mapEndit)
    {
      std::vector<CEvaluationNode*> constVect;
      constVect.insert(constVect.begin(), mapIt->second.begin(), mapIt->second.end());
      CEvaluationNode* pNode = CNormalTranslation::createOperatorChain(CEvaluationNodeOperator::PLUS, "+", constVect);
      // now check if we already have a base with the same infix in the
      // results
      unsigned int i, iMax = result.size();
      for (i = 0;i < iMax;++i)
        {
          CNormalFraction* base1 = createNormalRepresentation(result[i].second);
          CNormalFraction* base2 = createNormalRepresentation(mapIt->first);
          if (base1->toString() == base2->toString())
            {
              CEvaluationNode* pTmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
              pTmpNode->addChild(result[i].first);
              pTmpNode->addChild(pNode);
              result[i] = std::make_pair(pTmpNode, result[i].second);
              delete base1;
              delete base2;
              break;
            }
          delete base1;
          delete base2;
        }
      if (i == iMax)
        {
          if (CEvaluationNode::type(pNode->getType()) == CEvaluationNode::NUMBER)
            {
              std::ostringstream os;
              os << static_cast<CEvaluationNodeNumber*>(pNode)->value() * -1.0;
              os.precision(18);
              CEvaluationNode* pTmpNumber = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, os.str().c_str());
              delete pNode;
              result.push_back(std::make_pair(pTmpNumber, mapIt->first->copyBranch()));
            }
          else
            {
              CEvaluationNode* pTmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
              pTmpNode->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "-1.0"));
              pTmpNode->addChild(pNode);
              result.push_back(std::make_pair(pTmpNode, mapIt->first->copyBranch()));
            }
        }
      // delete the obsolete nodes
      iMax = mapIt->second.size();
      for (i = 0;i < iMax;++i)
        {
          delete mapIt->second[i];
        }
      ++mapIt;
    }
  return result;
}

/**
 * The methods get a vector of addition elements and a vector of subtractions
 * elements and tries to find equal elements in those two vectors.
 */
std::vector<std::pair<CEvaluationNode*, CEvaluationNode*> > CNormalTranslation::matchSummands(const std::vector<CEvaluationNode*>& additions, const std::vector<CEvaluationNode*>& subtractions)
{
  // the individual elements could be  multiplication chains and there could
  // be a common factor somewhere in the chain
  // Since I only want to get rid of numbers, it might be enough to
  // consider only those multiplication chains the contain a number node and
  // something else, everything else is ambiguous anyway and depends on
  // the order of the nodes in the chain
  std::vector<std::pair<const CEvaluationNode*, std::vector<CEvaluationNode*> > > matchMap;
  std::vector<CEvaluationNode*>::const_iterator vit = additions.begin(), vendit = additions.end();
  while (vit != vendit)
    {
      const CEvaluationNode* pNode = (*vit);
      CEvaluationNode* pFactor = NULL;
      if (CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pNode->getType())) == CEvaluationNodeOperator::MULTIPLY)
        {
          const CEvaluationNode* pChild1 = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
          assert(pChild1 != NULL);
          const CEvaluationNode* pChild2 = dynamic_cast<const CEvaluationNode*>(pChild1->getSibling());
          assert(pChild2 != NULL);
          assert(pChild2->getSibling() == NULL);
          if (CEvaluationNode::type(pChild1->getType()) == CEvaluationNode::NUMBER)
            {
              pNode = pChild2;
              pFactor = pChild1->copyBranch();
            }
          else if (CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::NUMBER)
            {
              pNode = pChild1;
              pFactor = pChild2->copyBranch();
            }
          else
            {
              pFactor = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");
            }
        }
      else
        {
          pFactor = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");
        }
      // check if a node with the same infix is already in the map.
      // if not, add the base
      // if yes, add the exponent to the vector associated with the base
      std::vector<std::pair<const CEvaluationNode*, std::vector<CEvaluationNode*> > >::iterator mapIt = matchMap.begin(), mapEndit = matchMap.end();
      while (mapIt != mapEndit)
        {
          CNormalFraction* base1 = createNormalRepresentation(mapIt->first);
          CNormalFraction* base2 = createNormalRepresentation(pNode);
          if (base1->toString() == base2->toString())
            {
              mapIt->second.push_back(pFactor);
              delete base1;
              delete base2;
              break;
            }
          delete base1;
          delete base2;
          ++mapIt;
        }
      if (mapIt == mapEndit)
        {
          std::vector<CEvaluationNode*> v;
          v.push_back(pFactor);
          matchMap.push_back(std::make_pair(pNode, v));
        }
      ++vit;
    }
  std::vector<std::pair<const CEvaluationNode*, std::vector<CEvaluationNode*> > > matchMap2;
  vit = subtractions.begin(), vendit = subtractions.end();
  while (vit != vendit)
    {
      const CEvaluationNode* pNode = (*vit);
      CEvaluationNode* pFactor = NULL;
      if (CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pNode->getType())) == CEvaluationNodeOperator::MULTIPLY)
        {
          const CEvaluationNode* pChild1 = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
          assert(pChild1 != NULL);
          const CEvaluationNode* pChild2 = dynamic_cast<const CEvaluationNode*>(pChild1->getSibling());
          assert(pChild2 != NULL);
          assert(pChild2->getSibling() == NULL);
          if (CEvaluationNode::type(pChild1->getType()) == CEvaluationNode::NUMBER)
            {
              pNode = pChild2;
              pFactor = pChild1->copyBranch();
            }
          else if (CEvaluationNode::type(pChild2->getType()) == CEvaluationNode::NUMBER)
            {
              pNode = pChild1;
              pFactor = pChild2->copyBranch();
            }
          else
            {
              pFactor = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");
            }
        }
      else
        {
          pFactor = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");
        }
      // check if a node with the same infix is already in the map.
      // if not, add the node
      // if yes, add the 1 to the vector associated with the base
      std::vector<std::pair<const CEvaluationNode*, std::vector<CEvaluationNode*> > >::iterator mapIt = matchMap2.begin(), mapEndit = matchMap2.end();
      while (mapIt != mapEndit)
        {
          CNormalFraction* base1 = createNormalRepresentation(mapIt->first);
          CNormalFraction* base2 = createNormalRepresentation(pNode);
          if (base1->toString() == base2->toString())
            {
              mapIt->second.push_back(pFactor);
              delete base1;
              delete base2;
              break;
            }
          delete base1;
          delete base2;
          ++mapIt;
        }
      if (mapIt == mapEndit)
        {
          std::vector<CEvaluationNode*> v;
          v.push_back(pFactor);
          matchMap2.push_back(std::make_pair(pNode, v));
        }
      ++vit;
    }
  // now combine the two maps
  std::vector<std::pair<CEvaluationNode*, CEvaluationNode*> > result;
  std::vector<std::pair<const CEvaluationNode*, std::vector<CEvaluationNode*> > >::iterator mapIt = matchMap.begin(), mapEndit = matchMap.end();
  while (mapIt != mapEndit)
    {
      std::vector<CEvaluationNode*> constVect;
      constVect.insert(constVect.begin(), mapIt->second.begin(), mapIt->second.end());
      CEvaluationNode* pNode = CNormalTranslation::createOperatorChain(CEvaluationNodeOperator::PLUS, "+", constVect);
      result.push_back(std::make_pair(pNode, mapIt->first->copyBranch()));
      // delete the obsolete nodes
      unsigned int i, iMax = mapIt->second.size();
      for (i = 0;i < iMax;++i)
        {
          delete mapIt->second[i];
        }
      ++mapIt;
    }
  mapIt = matchMap2.begin(), mapEndit = matchMap2.end();
  while (mapIt != mapEndit)
    {
      std::vector<CEvaluationNode*> constVect;
      constVect.insert(constVect.begin(), mapIt->second.begin(), mapIt->second.end());
      CEvaluationNode* pNode = CNormalTranslation::createOperatorChain(CEvaluationNodeOperator::PLUS, "+", constVect);
      // now check if we already have a base with the same infix in the
      // results
      unsigned int i, iMax = result.size();
      for (i = 0;i < iMax;++i)
        {
          CNormalFraction* base1 = createNormalRepresentation(result[i].second);
          CNormalFraction* base2 = createNormalRepresentation(mapIt->first);
          if (base1->toString() == base2->toString())
            {
              CEvaluationNode* pTmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
              pTmpNode->addChild(result[i].first);
              pTmpNode->addChild(pNode);
              result[i] = std::make_pair(pTmpNode, result[i].second);
              delete base1;
              delete base2;
              break;
            }
          delete base1;
          delete base2;
        }
      if (i == iMax)
        {
          CEvaluationNode* pTmpNode = NULL;
          if (CEvaluationNode::type(pNode->getType()) == CEvaluationNode::NUMBER)
            {
              std::ostringstream os;
              os.precision(18);
              os << dynamic_cast<const CEvaluationNodeNumber*>(pNode)->value() * -1.0;
              pTmpNode = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, os.str().c_str());
            }
          else
            {
              pTmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
              pTmpNode->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "-1.0"));
              pTmpNode->addChild(pNode);
            }
          result.push_back(std::make_pair(pTmpNode, mapIt->first->copyBranch()));
        }
      // delete the obsolete nodes
      iMax = mapIt->second.size();
      for (i = 0;i < iMax;++i)
        {
          delete mapIt->second[i];
        }
      ++mapIt;
    }
  return result;
}

/**
 * This method expands products. (A+B)*(C+D) -> (A*C)+(A*D)+(B*C)+(B*D)
 */
CEvaluationNode* CNormalTranslation::expandProducts(const CEvaluationNode* pOrig)
{
  CEvaluationNode* pResult = NULL;
  std::vector<CEvaluationNode*> children;
  const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pOrig->getChild());
  while (pChild != NULL)
    {
      children.push_back(CNormalTranslation::expandProducts(pChild));
      pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
    }
  if (CEvaluationNode::type(pOrig->getType()) == CEvaluationNode::OPERATOR &&
      ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOrig->getType())) == CEvaluationNodeOperator::MULTIPLY)
    {
      assert(children.size() == 2);
      pResult = CNormalTranslation::multiply(children[0], children[1]);
      // delete the children
      delete children[0];
      delete children[1];
    }
  if (pResult == NULL)
    {
      pResult = pOrig->copyNode(children);
    }
  return pResult;
}

/**
 * Multiplies the two given nodes and returns the result.
 */
CEvaluationNode* CNormalTranslation::multiply(const CEvaluationNode* pNode1, const CEvaluationNode* pNode2)
{
  CEvaluationNode* pResult = NULL;
  std::vector<CEvaluationNode*> additions1, subtractions1;
  CNormalTranslation::splitSum(pNode1, additions1, subtractions1, false);
  std::vector<CEvaluationNode*> additions2, subtractions2;
  CNormalTranslation::splitSum(pNode2, additions2, subtractions2, false);
  // multiply every element in additions1 with every element in additions2
  // and subtractions2 the results for the multiplication with the elements
  // of subtractions2 must be multiplied by -1
  // multiply every element in subtraction1 with every element in additions2
  // and subtractions2 the results for the multiplication with the elements
  // of additions2 must be multiplied by -1
  std::vector<CEvaluationNode*> tmp;
  unsigned int i, iMax = additions1.size();
  for (i = 0;i < iMax;++i)
    {
      unsigned int j, jMax = additions2.size();
      for (j = 0;j < jMax;++j)
        {
          CEvaluationNode* pMult = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
          pMult->addChild(additions1[i]->copyBranch());
          pMult->addChild(additions2[j]->copyBranch());
          tmp.push_back(pMult);
        }
    }
  iMax = subtractions1.size();
  for (i = 0;i < iMax;++i)
    {
      unsigned int j, jMax = subtractions2.size();
      for (j = 0;j < jMax;++j)
        {
          CEvaluationNode* pMult = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
          pMult->addChild(subtractions1[i]->copyBranch());
          pMult->addChild(subtractions2[j]->copyBranch());
          tmp.push_back(pMult);
        }
    }
  if (!tmp.empty())
    {
      pResult = CNormalTranslation::createOperatorChain(CEvaluationNodeOperator::PLUS, "+", tmp);
    }
  iMax = tmp.size();
  for (i = 0;i < iMax;++i)
    {
      delete tmp[i];
    }
  tmp.clear();
  iMax = additions1.size();
  for (i = 0;i < iMax;++i)
    {
      unsigned int j, jMax = subtractions2.size();
      for (j = 0;j < jMax;++j)
        {
          CEvaluationNode* pMult = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
          pMult->addChild(additions1[i]->copyBranch());
          pMult->addChild(subtractions2[j]->copyBranch());
          tmp.push_back(pMult);
        }
    }
  iMax = subtractions1.size();
  for (i = 0;i < iMax;++i)
    {
      unsigned int j, jMax = additions2.size();
      for (j = 0;j < jMax;++j)
        {
          CEvaluationNode* pMult = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
          pMult->addChild(subtractions1[i]->copyBranch());
          pMult->addChild(additions2[j]->copyBranch());
          tmp.push_back(pMult);
        }
    }
  if (!tmp.empty())
    {
      if (pResult != NULL)
        {
          CEvaluationNode* pTmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
          pTmpNode->addChild(pResult);
          pResult = pTmpNode;
          pTmpNode = CNormalTranslation::createOperatorChain(CEvaluationNodeOperator::PLUS, "+", tmp);
          pResult->addChild(pTmpNode);
        }
      else
        {
          CEvaluationNode* pTmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
          pTmpNode->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "-1.0"));
          pResult = pTmpNode;
          pTmpNode = CNormalTranslation::createOperatorChain(CEvaluationNodeOperator::PLUS, "+", tmp);
          pResult->addChild(pTmpNode);
        }
      iMax = tmp.size();
      for (i = 0;i < iMax;++i)
        {
          delete tmp[i];
        }
    }
  std::vector<CEvaluationNode*>::iterator it = additions1.begin(), endit = additions1.end();
  // delete all newly created entries in additions and subtractions
  while (it != endit)
    {
      delete *it;
      ++it;
    }
  it = subtractions1.begin();
  endit = subtractions1.end();
  while (it != endit)
    {
      delete *it;
      ++it;
    }
  it = additions2.begin(), endit = additions2.end();
  while (it != endit)
    {
      delete *it;
      ++it;
    }
  it = subtractions2.begin();
  endit = subtractions2.end();
  while (it != endit)
    {
      delete *it;
      ++it;
    }
  return pResult;
}

/**
 * This method does all the canceling on a given node and its children.
 */
CEvaluationNode* CNormalTranslation::cancel(const CEvaluationNode* pOrig)
{
  // try to find multiplication chains where something is divided by itself
  // or multiplied by -1 times itself
  // also consider powers (it's the bases that have to match)
  //
  // try to find addition changes where there is a subtraction of two
  // identical nodes or an addition of one node and the same node times -1
  CEvaluationNode* pResult = NULL;
  std::vector<CEvaluationNode*> children;
  if (CEvaluationNode::type(pOrig->getType()) == CEvaluationNode::OPERATOR)
    {
      if (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOrig->getType())) == CEvaluationNodeOperator::PLUS ||
          ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOrig->getType())) == CEvaluationNodeOperator::MINUS)
        {
          // we are in a sum
          std::vector<CEvaluationNode*> additions, subtractions;
          CNormalTranslation::splitSum(pOrig, additions, subtractions, false);
          // collect all nodes in additions and subtractions
          unsigned int i, iMax = additions.size();
          for (i = 0;i < iMax;++i)
            {
              CEvaluationNode* pChild = CNormalTranslation::cancel(additions[i]);
              delete additions[i];
              additions[i] = pChild;
            }
          iMax = subtractions.size();
          for (i = 0;i < iMax;++i)
            {
              CEvaluationNode* pChild = CNormalTranslation::cancel(subtractions[i]);
              delete subtractions[i];
              subtractions[i] = pChild;
            }
          // find identical nodes in additions and subtractions
          // The first entry in the pair is the collected factor
          // the second entry is the original branch
          // make sure the collected factor is again simplified
          std::vector<std::pair<CEvaluationNode*, CEvaluationNode*> > collected = CNormalTranslation::matchSummands(additions, subtractions);
          std::vector<CEvaluationNode*> chain;
          iMax = collected.size();
          for (i = 0;i < iMax;++i)
            {
              std::pair<CEvaluationNode*, CEvaluationNode*> pair = collected[i];
              //CEvaluationNode* pTmpNode = CNormalTranslation::eliminate(pair.first);
              //delete pair.first;
              // if simplified node is 0.0, we ignore this node
              if (CEvaluationNode::type(pair.first->getType()) == CEvaluationNode::NUMBER &&
                  fabs(dynamic_cast<CEvaluationNodeNumber*>(pair.first)->value()) < ZERO)
                {
                  delete pair.first;
                  delete pair.second;
                }
              else if (CEvaluationNode::type(pair.first->getType()) == CEvaluationNode::NUMBER &&
                       fabs(dynamic_cast<CEvaluationNodeNumber*>(pair.first)->value() - 1.0) < ZERO)
                {
                  delete pair.first;
                  chain.push_back(pair.second);
                }
              else
                {
                  CEvaluationNode* pMult = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
                  pMult->addChild(pair.first);
                  pMult->addChild(pair.second);
                  chain.push_back(pMult);
                }
            }
          pResult = CNormalTranslation::createOperatorChain(CEvaluationNodeOperator::PLUS, "+", chain);
          // delete the chain nodes
          iMax = chain.size();
          for (i = 0;i < iMax;++i)
            {
              delete chain[i];
            }
        }
      else if (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOrig->getType())) == CEvaluationNodeOperator::MULTIPLY ||
               ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOrig->getType())) == CEvaluationNodeOperator::DIVIDE)
        {
          // we are in a product
          std::vector<const CEvaluationNode*> multiplications, divisions;
          CNormalTranslation::splitProduct(pOrig, multiplications, divisions, false);
          // collect all nodes in multiplications and divisions
          unsigned int i, iMax = multiplications.size();
          for (i = 0;i < iMax;++i)
            {
              CEvaluationNode* pChild = CNormalTranslation::cancel(multiplications[i]);
              multiplications[i] = pChild;
            }
          iMax = divisions.size();
          for (i = 0;i < iMax;++i)
            {
              CEvaluationNode* pChild = CNormalTranslation::cancel(divisions[i]);
              divisions[i] = pChild;
            }
          // find identical nodes in multiplications and divisions
          // The first entry in the pair is the collected power exponent
          // the second entry is the original power base
          // make sure the collected factor is again simplified
          std::vector<std::pair<CEvaluationNode*, CEvaluationNode*> > collected = CNormalTranslation::matchPowerBases(multiplications, divisions);
          std::vector<CEvaluationNode*> numeratorChain;
          std::vector<CEvaluationNode*> denominatorChain;
          iMax = collected.size();
          for (i = 0;i < iMax;++i)
            {
              std::pair<CEvaluationNode*, CEvaluationNode*> pair = collected[i];
              //CEvaluationNode* pTmpNode = CNormalTranslation::eliminate(pair.first);
              //delete pair.first;
              // if simplified node is a 0.0, we ignore this node
              if (CEvaluationNode::type(pair.first->getType()) == CEvaluationNode::NUMBER)
                {
                  if (fabs(dynamic_cast<CEvaluationNodeNumber*>(pair.first)->value()) < ZERO)
                    {
                      delete pair.first;
                      delete pair.second;
                    }
                  else if(dynamic_cast<CEvaluationNodeNumber*>(pair.first)->value() > 0.0)
                    {
                      if (fabs(dynamic_cast<CEvaluationNodeNumber*>(pair.first)->value() - 1.0) < ZERO)
                        {
                          delete pair.first;
                          numeratorChain.push_back(pair.second);
                        }
                      else
                        {
                          CEvaluationNode* pPower = new CEvaluationNodeOperator(CEvaluationNodeOperator::POWER, "^");
                          pPower->addChild(pair.second);
                          pPower->addChild(pair.first);
                          numeratorChain.push_back(pPower);
                        }
                    }
                  else
                    {
                      if (fabs(dynamic_cast<CEvaluationNodeNumber*>(pair.first)->value() + 1.0) < ZERO)
                        {
                          delete pair.first;
                          denominatorChain.push_back(pair.second);
                        }
                      else
                        {
                          CEvaluationNode* pPower = new CEvaluationNodeOperator(CEvaluationNodeOperator::POWER, "^");
                          pPower->addChild(pair.second);
                          std::ostringstream os;
                          os.precision(18);
                          os << fabs(dynamic_cast<const CEvaluationNodeNumber*>(pair.first)->value());
                          pPower->addChild(new CEvaluationNodeNumber((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pair.first->getType()), os.str().c_str()));
                          delete pair.first;
                          denominatorChain.push_back(pPower);
                        }
                    }
                }
              else
                {
                  CEvaluationNode* pPower = new CEvaluationNodeOperator(CEvaluationNodeOperator::POWER, "^");
                  // check if the node is -1.0 * SOMETHING
                  if (CEvaluationNode::type(pair.first->getType()) == CEvaluationNode::OPERATOR && (CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pair.first->getType()) == CEvaluationNodeOperator::MULTIPLY
                      && CEvaluationNode::type(dynamic_cast<const CEvaluationNode*>(pair.first->getChild())->getType()) == CEvaluationNode::NUMBER)
                    {
                      if (fabs(static_cast<const CEvaluationNodeNumber*>(pair.first->getChild())->value() + 1.0) < ZERO)
                        {
                          pPower->addChild(pair.second);
                          pPower->addChild(dynamic_cast<const CEvaluationNode*>(pair.first->getChild()->getSibling())->copyBranch());
                          delete pair.first;
                          denominatorChain.push_back(pPower);
                        }
                      else if (fabs(static_cast<const CEvaluationNodeNumber*>(pair.first->getChild())->value()) < ZERO)
                        {
                          // delete the power node and add
                          delete pPower;
                          delete pair.first;
                          numeratorChain.push_back(pair.second);
                        }
                      else if (static_cast<const CEvaluationNodeNumber*>(pair.first->getChild())->value() < 0.0)
                        {
                          pPower->addChild(pair.second);
                          pPower->addChild(pair.first);
                          denominatorChain.push_back(pPower);
                        }
                      else
                        {
                          pPower->addChild(pair.second);
                          pPower->addChild(pair.first);
                          numeratorChain.push_back(pPower);
                        }
                    }
                  else
                    {
                      pPower->addChild(pair.second);
                      pPower->addChild(pair.first);
                      numeratorChain.push_back(pPower);
                    }
                }
            }
          pResult = CNormalTranslation::createOperatorChain(CEvaluationNodeOperator::MULTIPLY, "*", numeratorChain);
          if (!denominatorChain.empty())
            {
              CEvaluationNode* pTmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::DIVIDE, "/");
              pTmpNode->addChild(pResult);
              pResult = pTmpNode;
              pTmpNode = CNormalTranslation::createOperatorChain(CEvaluationNodeOperator::MULTIPLY, "*", denominatorChain);
              pResult->addChild(pTmpNode);
            }
          // delete the chain nodes
          iMax = numeratorChain.size();
          for (i = 0;i < iMax;++i)
            {
              delete numeratorChain[i];
            }
          iMax = denominatorChain.size();
          for (i = 0;i < iMax;++i)
            {
              delete denominatorChain[i];
            }
        }
      else
        {
          const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pOrig->getChild());
          while (pChild != NULL)
            {
              children.push_back(CNormalTranslation::cancel(pChild));
              pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
            }
          assert(children.size() == 2);
        }
    }
  else
    {
      const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pOrig->getChild());
      while (pChild != NULL)
        {
          children.push_back(CNormalTranslation::cancel(pChild));
          pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
        }
    }
  if (pResult == NULL)
    {
      pResult = pOrig->copyNode(children);
    }
  return pResult;
}

// TODO for comparing in infix, it should be brought into a normalform first
