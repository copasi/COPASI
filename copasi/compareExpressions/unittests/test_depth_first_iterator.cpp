// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_depth_first_iterator.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2012/04/22 14:51:18 $
// End CVS Header

// Copyright (C) 2012 - 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "test_depth_first_iterator.h"

#include <limits>
#include <cmath>
#include <string>

#include "function/CEvaluationTree.h"
#include "function/CEvaluationNode.h"
#include "function/CEvaluationNodeNumber.h"
#include "function/CEvaluationNodeOperator.h"
#include "report/CCopasiRootContainer.h"

#include "compareExpressions/CNormalTranslation.h"

void test_depth_first_iterator::setUp()
{
  CCopasiRootContainer::init(false, 0, NULL);
}

void test_depth_first_iterator::tearDown()
{
  CCopasiRootContainer::destroy();
}

void test_depth_first_iterator::test_dfi()
{
  std::string infix("7-(3+(4-6))+1*8");
  CEvaluationTree* pTree = new CEvaluationTree();
  pTree->setInfix(infix);
  std::string s = pTree->getInfix();
  CPPUNIT_ASSERT(pTree->getRoot() != NULL);
  CEvaluationNodeDepthFirstIterator it(pTree->getRoot());
  CPPUNIT_ASSERT(it.isValid());
  CEvaluationNode* pNode = NULL;
  CEvaluationNodeNumber* pNumberNode = NULL;
  CEvaluationNodeOperator* pOperatorNode = NULL;
  // 7
  pNode = *it;
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::NUMBER);
  pNumberNode = dynamic_cast<CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT((fabs(pNumberNode->value() - 7) / 7.0) <= std::numeric_limits<double>::min());
  // 3
  ++it;
  CPPUNIT_ASSERT(it.isValid() == true);
  pNode = *it;
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::NUMBER);
  pNumberNode = dynamic_cast<CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT((fabs(pNumberNode->value() - 3) / 3.0) <= std::numeric_limits<double>::min());
  // 4
  ++it;
  CPPUNIT_ASSERT(it.isValid() == true);
  pNode = *it;
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::NUMBER);
  pNumberNode = dynamic_cast<CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT((fabs(pNumberNode->value() - 4) / 4.0) <= std::numeric_limits<double>::min());
  // 6
  ++it;
  CPPUNIT_ASSERT(it.isValid() == true);
  pNode = *it;
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::NUMBER);
  pNumberNode = dynamic_cast<CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT((fabs(pNumberNode->value() - 6) / 6.0) <= std::numeric_limits<double>::min());
  // -
  ++it;
  CPPUNIT_ASSERT(it.isValid() == true);
  pNode = *it;
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OPERATOR);
  pOperatorNode = dynamic_cast<CEvaluationNodeOperator*>(pNode);
  CPPUNIT_ASSERT(pOperatorNode != NULL);
  CPPUNIT_ASSERT((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOperatorNode->getType()) == CEvaluationNodeOperator::MINUS);
  // +
  ++it;
  CPPUNIT_ASSERT(it.isValid() == true);
  pNode = *it;
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OPERATOR);
  pOperatorNode = dynamic_cast<CEvaluationNodeOperator*>(pNode);
  CPPUNIT_ASSERT(pOperatorNode != NULL);
  CPPUNIT_ASSERT((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOperatorNode->getType()) == CEvaluationNodeOperator::PLUS);
  // -
  ++it;
  CPPUNIT_ASSERT(it.isValid() == true);
  pNode = *it;
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OPERATOR);
  pOperatorNode = dynamic_cast<CEvaluationNodeOperator*>(pNode);
  CPPUNIT_ASSERT(pOperatorNode != NULL);
  CPPUNIT_ASSERT((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOperatorNode->getType()) == CEvaluationNodeOperator::MINUS);
  // 1
  ++it;
  CPPUNIT_ASSERT(it.isValid() == true);
  pNode = *it;
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::NUMBER);
  pNumberNode = dynamic_cast<CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT((fabs(pNumberNode->value() - 1) / 1.0) <= std::numeric_limits<double>::min());
  // 8
  ++it;
  CPPUNIT_ASSERT(it.isValid() == true);
  pNode = *it;
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::NUMBER);
  pNumberNode = dynamic_cast<CEvaluationNodeNumber*>(pNode);
  CPPUNIT_ASSERT(pNumberNode != NULL);
  CPPUNIT_ASSERT((fabs(pNumberNode->value() - 8) / 8.0) <= std::numeric_limits<double>::min());
  // *
  ++it;
  CPPUNIT_ASSERT(it.isValid() == true);
  pNode = *it;
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OPERATOR);
  pOperatorNode = dynamic_cast<CEvaluationNodeOperator*>(pNode);
  CPPUNIT_ASSERT(pOperatorNode != NULL);
  CPPUNIT_ASSERT((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOperatorNode->getType()) == CEvaluationNodeOperator::MULTIPLY);
  // +
  ++it;
  CPPUNIT_ASSERT(it.isValid() == true);
  pNode = *it;
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OPERATOR);
  pOperatorNode = dynamic_cast<CEvaluationNodeOperator*>(pNode);
  CPPUNIT_ASSERT(pOperatorNode != NULL);
  CPPUNIT_ASSERT((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOperatorNode->getType()) == CEvaluationNodeOperator::PLUS);

  ++it;
  CPPUNIT_ASSERT(it.isValid() == false);
  CPPUNIT_ASSERT(*it == NULL);

  delete pTree;
}

