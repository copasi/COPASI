// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_node_conversion.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/08/07 16:49:50 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "test_node_conversion.hpp"

#include <string>

#include "ConvertToCEvaluationNode.h"
#include "CNormalSum.h"
#include "CNormalBase.h"
#include "CNormalFraction.h"
#include "CNormalProduct.h"
#include "CNormalItem.h"
#include "CNormalItemPower.h"

#include "function/CEvaluationTree.h"

void test_node_conversion::setUp(){}

void test_node_conversion::tearDown(){}

void test_node_conversion::test_convert_cnormalsum_1()
{
  std::string expr("A+G+D+E");
  CEvaluationTree* pTree = new CEvaluationTree("tree", NULL, CEvaluationTree::Function);
  pTree->setInfix(expr);
  CNormalBase* pNormal = createNormalRepresentation(pTree->getRoot());
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
}

void test_node_conversion::test_convert_cnormalsum_2()
{
  std::string expr("A*D+B*C");
  CEvaluationTree* pTree = new CEvaluationTree("tree", NULL, CEvaluationTree::Function);
  pTree->setInfix(expr);
  CNormalBase* pNormal = createNormalRepresentation(pTree->getRoot());
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
