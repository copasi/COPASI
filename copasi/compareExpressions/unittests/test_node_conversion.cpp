// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_node_conversion.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/07/29 20:23:58 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "test_node_conversion.hpp"

#include <string>

#include "compareExpressions/ConvertToCEvaluationNode.h"
#include "compareExpressions/CNormalSum.h"
#include "compareExpressions/CNormalBase.h"
#include "compareExpressions/CNormalFraction.h"
#include "compareExpressions/CNormalProduct.h"
#include "compareExpressions/CNormalItem.h"
#include "compareExpressions/CNormalItemPower.h"

#include "function/CEvaluationTree.h"

void test_node_conversion::setUp(){}

void test_node_conversion::tearDown(){}

void test_node_conversion::test_0001()
{
  std::string expr("A+G+D+E");
  CEvaluationTree* pTree = new CEvaluationTree("tree", NULL, CEvaluationTree::Function);
  pTree->setInfix(expr);
  CNormalBase* pNormal = createNormalRepresentation(pTree->getRoot());
  delete pTree;
  CNormalFraction* pFraction = dynamic_cast<CNormalFraction*>(pNormal);
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne());
  const CNormalSum& pSum = pFraction->getNumerator();
  CPPUNIT_ASSERT(pSum.getFractions().size() == 0);
  CPPUNIT_ASSERT(pSum.getProducts().size() == 4);
  CEvaluationNode* pResultNode = convertToCEvaluationNode(pSum);
  CEvaluationNodeOperator* pOperator = dynamic_cast<CEvaluationNodeOperator*>(pResultNode);
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOperator->getType())) == CEvaluationNodeOperator::PLUS);
  CEvaluationNodeVariable* pVariable = NULL;
  if (dynamic_cast<CEvaluationNodeOperator*>(pOperator->getChild()))
    {
      pOperator = static_cast<CEvaluationNodeOperator*>(pOperator->getChild());
      pVariable = dynamic_cast<CEvaluationNodeVariable*>(pOperator->getSibling());
    }
  else
    {
      pVariable = dynamic_cast<CEvaluationNodeVariable*>(pOperator->getChild());
      pOperator = static_cast<CEvaluationNodeOperator*>(pVariable->getSibling());
    }
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(pVariable != NULL);
  if (dynamic_cast<CEvaluationNodeOperator*>(pOperator->getChild()))
    {
      pOperator = static_cast<CEvaluationNodeOperator*>(pOperator->getChild());
      pVariable = dynamic_cast<CEvaluationNodeVariable*>(pOperator->getSibling());
    }
  else
    {
      pVariable = dynamic_cast<CEvaluationNodeVariable*>(pOperator->getChild());
      pOperator = static_cast<CEvaluationNodeOperator*>(pVariable->getSibling());
    }
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(pVariable != NULL);
  pVariable = dynamic_cast<CEvaluationNodeVariable*>(pOperator->getChild());
  CPPUNIT_ASSERT(pVariable != NULL);
  pVariable = dynamic_cast<CEvaluationNodeVariable*>(pVariable->getSibling());
  CPPUNIT_ASSERT(pVariable != NULL);
  delete pFraction;
}

void test_node_conversion::test_0002()
{
  std::string expr("A*D+B*C");
  CEvaluationTree* pTree = new CEvaluationTree("tree", NULL, CEvaluationTree::Function);
  pTree->setInfix(expr);
  CNormalBase* pNormal = createNormalRepresentation(pTree->getRoot());
  delete pTree;
  CNormalFraction* pFraction = dynamic_cast<CNormalFraction*>(pNormal);
  CPPUNIT_ASSERT(pFraction != NULL);
  CPPUNIT_ASSERT(pFraction->checkDenominatorOne());
  const CNormalSum& pSum = pFraction->getNumerator();
  CPPUNIT_ASSERT(pSum.getFractions().size() == 0);
  CPPUNIT_ASSERT(pSum.getProducts().size() == 2);
  CEvaluationNode* pResultNode = convertToCEvaluationNode(pSum);
  CEvaluationNodeOperator* pOperator = dynamic_cast<CEvaluationNodeOperator*>(pResultNode);
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOperator->getType())) == CEvaluationNodeOperator::PLUS);
  pOperator = dynamic_cast<CEvaluationNodeOperator*>(pOperator->getChild());
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOperator->getType())) == CEvaluationNodeOperator::MULTIPLY);
  CEvaluationNodeVariable* pVariable = dynamic_cast<CEvaluationNodeVariable*>(pOperator->getChild());
  CPPUNIT_ASSERT(pVariable != NULL);
  pVariable = dynamic_cast<CEvaluationNodeVariable*>(pVariable->getSibling());
  CPPUNIT_ASSERT(pVariable != NULL);
  pOperator = dynamic_cast<CEvaluationNodeOperator*>(pOperator->getSibling());
  CPPUNIT_ASSERT(pOperator != NULL);
  CPPUNIT_ASSERT(((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOperator->getType())) == CEvaluationNodeOperator::MULTIPLY);
  pVariable = dynamic_cast<CEvaluationNodeVariable*>(pOperator->getChild());
  CPPUNIT_ASSERT(pVariable != NULL);
  pVariable = dynamic_cast<CEvaluationNodeVariable*>(pVariable->getSibling());
  CPPUNIT_ASSERT(pVariable != NULL);
}

void test_node_conversion::test_0003()
{
  std::string expr("1.0*3.0+1.0*5.0");
  CEvaluationTree* pTree = new CEvaluationTree("tree", NULL, CEvaluationTree::Function);
  pTree->setInfix(expr);
  CNormalBase* pNormal = createNormalRepresentation(pTree->getRoot());
  delete pTree;
  CNormalFraction* pFraction = dynamic_cast<CNormalFraction*>(pNormal);
  CPPUNIT_ASSERT(pFraction != NULL);
  // for now, we see if it can be converted to a string without crashing
  std::string s = pFraction->toString();
}

void test_node_conversion::test_0004()
{
  std::string expr("5.0^1.0*7.0^1.0");
  CEvaluationTree* pTree = new CEvaluationTree("tree", NULL, CEvaluationTree::Function);
  pTree->setInfix(expr);
  CNormalBase* pNormal = createNormalRepresentation(pTree->getRoot());
  delete pTree;
  CNormalFraction* pFraction = dynamic_cast<CNormalFraction*>(pNormal);
  CPPUNIT_ASSERT(pFraction != NULL);
  // for now, we see if it can be converted to a string without crashing
  std::string s = pFraction->toString();
}

void test_node_conversion::test_0005()
{
  std::string expr("A*(1/B)");
  CEvaluationTree* pTree = new CEvaluationTree("tree", NULL, CEvaluationTree::Function);
  pTree->setInfix(expr);
  CNormalBase* pNormal = createNormalRepresentation(pTree->getRoot());
  delete pTree;
  CNormalFraction* pFraction = dynamic_cast<CNormalFraction*>(pNormal);
  CPPUNIT_ASSERT(pFraction != NULL);
  // for now, we see if it can be converted to a string without crashing
  std::string s = pFraction->toString();
}
