// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/Attic/CMathTrigger.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/29 21:25:09 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMathTrigger.h"
#include "function/CEvaluationNode.h"
#include "report/CCopasiObjectReference.h"

CMathTrigger::CRootFinder::CRootFinder(const CCopasiContainer * pParent) :
    CCopasiContainer("Root", pParent),
    mRoot("Expression", this),
    mActive(0.0),
    mEquality(false)
{}

CMathTrigger::CRootFinder::CRootFinder(const CMathTrigger::CRootFinder & src,
                                       const CCopasiContainer * pParent) :
    CCopasiContainer(src, pParent),
    mRoot(src.mRoot, this),
    mActive(src.mActive),
    mEquality(src.mEquality)
{}

CMathTrigger::CRootFinder::~CRootFinder()
{}

void CMathTrigger::CRootFinder::initObjects()
{}

CMathTrigger::CMathTrigger(const CCopasiContainer * pParent) :
    CCopasiContainer("MathTrigger", pParent),
    mTriggerExpression("TriggerExpression", this),
    mActive(false),
    mActivateExpression("ActivateExpression", this),
    mRootFinders("ListOfRoots", this),
    mpExpression(NULL)
{}

CMathTrigger::CMathTrigger(const CMathTrigger & src,
                           const CCopasiContainer * pParent) :
    CCopasiContainer(src, pParent),
    mTriggerExpression(src.mTriggerExpression, this),
    mActive(src.mActive),
    mActivateExpression(src.mActivateExpression, this),
    mRootFinders(src.mRootFinders, this),
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
  mEqualityModifier = true;

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

bool CMathTrigger::compileAND(const CEvaluationNode * pSource)
{
  return false;
}

bool CMathTrigger::compileOR(const CEvaluationNode * pSource)
{
  return false;
}

bool CMathTrigger::compileXOR(const CEvaluationNode * pSource)
{
  return false;
}

bool CMathTrigger::compileEQ(const CEvaluationNode * pSource)
{
  bool success = true;
  CEvaluationNode * pNode;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  // Equality can be determined between Boolean and double values.
  if (CEvaluationNode::type(pLeft->getType()) == CEvaluationNode::LOGICAL)
    {
      // Boolean
      // We need to add an equality to the trigger expression.
      pNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::EQ, "EQ");

      if (!mTriggerNodes.empty())
        {
          mTriggerNodes.top()->addChild(pNode);
        }

      mTriggerNodes.push(pNode);

      // We need to add an inequality to the activate expression
      pNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::NE, "NE");

      if (!mActivateNodes.empty())
        {
          mActivateNodes.top()->addChild(pNode);
        }

      mActivateNodes.push(pNode);

      success &= compile(pLeft);
      success &= compile(pRight);

      pNode = mTriggerNodes.top();
      mTriggerNodes.pop();

      if (mTriggerNodes.empty())
        {
          mTriggerExpression.setRoot(pNode);
        }

      pNode = mActivateNodes.top();
      mActivateNodes.pop();

      if (mActivateNodes.empty())
        {
          mActivateExpression.setRoot(pNode);
        }
    }
  else
    {
      assert(mRootNodes.empty());

      // double
      // We need to create 2 root finding structures
      pNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
      pNode->addChild(pLeft->copyBranch());
      pNode->addChild(pRight->copyBranch());

      CRootFinder * pRootFinder = new CRootFinder();
      pRootFinder->mRoot.setRoot(pNode);
      pRootFinder->mEquality = effectiveEquality(true);
      mRootFinders.add(pRootFinder, true);

      pNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
      pNode->addChild(pRight->copyBranch());
      pNode->addChild(pLeft->copyBranch());

      pRootFinder = new CRootFinder();
      pRootFinder->mRoot.setRoot(pNode);
      pRootFinder->mEquality = effectiveEquality(true);
      mRootFinders.add(pRootFinder, true);

      // The trigger expression is:
      // (RootFinder[0].mRoot >= 0 && RootFinder[0].mActive) ||
      // (RootFinder[1].mRoot >= 0 && RootFinder[1].mActive)
      pNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::OR, "OR");
      mTriggerNodes.push(pNode);

      pNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
      mTriggerNodes.top()->addChild(pNode);
      mTriggerNodes.push(pNode);

      pNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::GE, "GE");
      mTriggerNodes.top()->addChild(pNode);
      mTriggerNodes.push(pNode);

      pNode = new CEvaluationNodeObject((C_FLOAT64 *) mRootFinders[0]->mRoot.getObject(std::string("Function=Expression,Reference=Value"))->getValuePointer());
      mTriggerNodes.top()->addChild(pNode);

      pNode = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0");
      mTriggerNodes.top()->addChild(pNode);

      mTriggerNodes.pop(); // GE

      pNode = new CEvaluationNodeObject(&mRootFinders[0]->mActive);
      mTriggerNodes.top()->addChild(pNode);

      mTriggerNodes.pop(); // AND

      pNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
      mTriggerNodes.top()->addChild(pNode);
      mTriggerNodes.push(pNode);

      pNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::GE, "GE");
      mTriggerNodes.top()->addChild(pNode);
      mTriggerNodes.push(pNode);

      pNode = new CEvaluationNodeObject((C_FLOAT64 *) mRootFinders[1]->mRoot.getObject(std::string("Function=Expression,Reference=Value"))->getValuePointer());
      mTriggerNodes.top()->addChild(pNode);

      pNode = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0");
      mTriggerNodes.top()->addChild(pNode);

      mTriggerNodes.pop(); // GE

      pNode = new CEvaluationNodeObject(&mRootFinders[1]->mActive);
      mTriggerNodes.top()->addChild(pNode);

      mTriggerNodes.pop(); // AND

      mTriggerNodes.pop(); // OR

      if (!mTriggerNodes.empty())
        {
          mTriggerNodes.top()->addChild(pNode);
        }
      else
        {
          mTriggerExpression.setRoot(pNode);
        }

      // The activate expression is always true
      pNode = new CEvaluationNodeConstant(CEvaluationNodeConstant::TRUE, "TRUE");

      if (!mActivateNodes.empty())
        {
          mActivateNodes.top()->addChild(pNode);
        }
      else
        {
          mActivateExpression.setRoot(pNode);
        }
    }

  return success;
}

bool CMathTrigger::compileNE(const CEvaluationNode * pSource)
{
  return false;
}

bool CMathTrigger::compileLE(const CEvaluationNode * pSource)
{
  return false;
}

bool CMathTrigger::compileLT(const CEvaluationNode * pSource)
{
  return false;
}

bool CMathTrigger::compileGE(const CEvaluationNode * pSource)
{
  return false;
}

bool CMathTrigger::compileGT(const CEvaluationNode * pSource)
{
  return false;
}

bool CMathTrigger::compileNOT(const CEvaluationNode * pSource)
{
  return false;
}

bool CMathTrigger::effectiveEquality(const bool & equality) const
{
  if (mEqualityModifier)
    return equality;
  else
    return !equality;
}
