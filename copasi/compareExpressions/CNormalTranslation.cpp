// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalTranslation.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/03/06 20:18:33 $
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
  CEvaluationNode * root1 = simplifyTreeReptdly(root0);
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
      pResult = CNormalTranslation::createMultiplicationChain(numeratorNodes);
      // if there are items in the denominator vector create the denominator
      // chain and divide the numerato chain by the denominator chain
      if (!denominatorNodes.empty())
        {
          CEvaluationNodeOperator* pDivision = new CEvaluationNodeOperator(CEvaluationNodeOperator::DIVIDE, "/");
          pDivision->addChild(pResult);
          pDivision->addChild(CNormalTranslation::createMultiplicationChain(denominatorNodes));
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

CEvaluationNode* CNormalTranslation::createMultiplicationChain(const std::vector<CEvaluationNode*>& nodes)
{
  CEvaluationNode* pResult = NULL;
  if (nodes.size() == 0)
    {
      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");
    }
  else if (nodes.size() == 1)
    {
      pResult = nodes[0];
    }
  else
    {
      // start from the back to create the deepest nodes first
      std::vector<CEvaluationNode*>::const_reverse_iterator it = nodes.rbegin(), endit = nodes.rend();
      CEvaluationNode* pOperator = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
      CEvaluationNode* pChild2 = *it;
      ++it;
      CEvaluationNode* pChild1 = *it;
      pOperator->addChild(pChild1);
      pOperator->addChild(pChild2);
      ++it;
      pChild2 = pOperator;
      while (it != endit)
        {
          pOperator = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
          pOperator->addChild(*it);
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
}
