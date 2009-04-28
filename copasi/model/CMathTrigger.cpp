// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/Attic/CMathTrigger.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/28 17:57:25 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMathTrigger.h"
#include "function/CEvaluationNode.h"

CMathTrigger::CRoot::CRoot(const CCopasiContainer * pParent) :
    CCopasiContainer("Root", pParent),
    mRoot("Expression", this),
    mActive(0.0),
    mEquality(false)
{}

CMathTrigger::CRoot::CRoot(const CMathTrigger::CRoot & src,
                           const CCopasiContainer * pParent) :
    CCopasiContainer(src, pParent),
    mRoot(src.mRoot, this),
    mActive(src.mActive),
    mEquality(src.mEquality)
{}

CMathTrigger::CRoot::~CRoot()
{}

CMathTrigger::CMathTrigger(const CCopasiContainer * pParent) :
    CCopasiContainer("MathTrigger", pParent),
    mTriggerExpression("TriggerExpression", this),
    mActive(false),
    mActivateExpression("ActivateExpression", this),
    mRoots("ListOfRoots", this),
    mpExpression(NULL)
{}

CMathTrigger::CMathTrigger(const CMathTrigger & src,
                           const CCopasiContainer * pParent) :
    CCopasiContainer(src, pParent),
    mTriggerExpression(src.mTriggerExpression, this),
    mActive(src.mActive),
    mActivateExpression(src.mActivateExpression, this),
    mRoots(src.mRoots, this),
    mpExpression(src.mpExpression)
{}

CMathTrigger::~CMathTrigger()
{}

bool CMathTrigger::compile(const CExpression * pTriggerExpression)
{
  if (pTriggerExpression == NULL)
    return false;

  const CEvaluationNode * pRoot = pTriggerExpression->getRoot();

  if (pRoot == NULL)
    return false;

  // This is a boolean expression thus the root node must be a logical operator.
  if (CEvaluationNode::type(pRoot->getType()) != CEvaluationNode::LOGICAL &&
      pRoot->getType() != (CEvaluationNode::FUNCTION | CEvaluationNodeFunction::NOT))
    return false;

  mTriggerExpression.setRoot(NULL);
  mActivateExpression.setRoot(NULL);
  mpRoot = NULL;

  bool success = compile(pRoot);

  assert(mTriggerNodes.empty());
  assert(mActivateNodes.empty());

  return success;
}

bool CMathTrigger::compile(const CEvaluationNode * pNode)
{
  bool success = true;
  const CEvaluationNode::Type & Type = pNode->getType();

  switch (CEvaluationNode::type(Type))
    {
      case CEvaluationNode::LOGICAL:

        switch ((int) CEvaluationNode::subType(Type))
          {
            case CEvaluationNodeLogical::AND:
              success = compileAND(pNode);
              break;

            case CEvaluationNodeLogical::OR:
              success = compileOR(pNode);
              break;

            case CEvaluationNodeLogical::XOR:
              success = compileXOR(pNode);
              break;

            case CEvaluationNodeLogical::EQ:
              success = compileEQ(pNode);
              break;

            case CEvaluationNodeLogical::NE:
              success = compileNE(pNode);
              break;

            case CEvaluationNodeLogical::LE:
              success = compileLE(pNode);
              break;

            case CEvaluationNodeLogical::LT:
              success = compileLT(pNode);
              break;

            case CEvaluationNodeLogical::GE:
              success = compileGE(pNode);
              break;

            case CEvaluationNodeLogical::GT:
              success = compileGT(pNode);
              break;

            default:
              success = false;
              break;
          }

        break;

      case CEvaluationNode::FUNCTION:

        switch ((int) CEvaluationNode::subType(Type))
          {
            case CEvaluationNodeFunction::NOT:
              success = compileNOT(pNode);
              break;

            case CEvaluationNodeFunction::INVALID:
              success = false;
              break;

            default:
              assert(!mRootNodes.empty());
              mRootNodes.top()->addChild(pNode->copyBranch());
              break;
          }

        break;

      case CEvaluationNode::INVALID:
        success = false;
        break;

      default:
        assert(!mRootNodes.empty());
        mRootNodes.top()->addChild(pNode->copyBranch());
        break;
    }

  return false;
}

bool CMathTrigger::compileAND(const CEvaluationNode * pNode)
{
  return false;
}

bool CMathTrigger::compileOR(const CEvaluationNode * pNode)
{
  return false;
}

bool CMathTrigger::compileXOR(const CEvaluationNode * pNode)
{
  return false;
}

bool CMathTrigger::compileEQ(const CEvaluationNode * pNode)
{
  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pNode->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  // Equality can determined between Boolean and double values.
  if (CEvaluationNode::type(pLeft->getType()) == CEvaluationNode::LOGICAL)
    {
      // Boolean
    }
  else
    {
      // double
    }

  return false;
}

bool CMathTrigger::compileNE(const CEvaluationNode * pNode)
{
  return false;
}

bool CMathTrigger::compileLE(const CEvaluationNode * pNode)
{
  return false;
}

bool CMathTrigger::compileLT(const CEvaluationNode * pNode)
{
  return false;
}

bool CMathTrigger::compileGE(const CEvaluationNode * pNode)
{
  return false;
}

bool CMathTrigger::compileGT(const CEvaluationNode * pNode)
{
  return false;
}

bool CMathTrigger::compileNOT(const CEvaluationNode * pNode)
{
  return false;
}
