// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/Attic/CMathTrigger.cpp,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/06/18 20:06:48 $
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
    mpRootValue(NULL),
    mEquality(false),
    mActive(0.0)
{
  initObjects();
}

CMathTrigger::CRootFinder::CRootFinder(const CMathTrigger::CRootFinder & src,
                                       const CCopasiContainer * pParent) :
    CCopasiContainer(src, pParent),
    mRoot(src.mRoot, this),
    mpRootValue(NULL),
    mEquality(src.mEquality),
    mActive(src.mActive)
{
  initObjects();
}

CMathTrigger::CRootFinder::~CRootFinder()
{}

void CMathTrigger::CRootFinder::initObjects()
{
  mpRootValue =
    (C_FLOAT64 *)mRoot.getObject(std::string("Reference=Value"))->getValuePointer();

  addDirectDependency(&mRoot);
  setRefresh(&mRoot, &CExpression::refresh);
}

bool CMathTrigger::CRootFinder::compile(std::vector< CCopasiContainer * > listOfContainer)
{
  bool success = true;

  success &= mRoot.compile(listOfContainer);

  return true;
}

CEvaluationNode * CMathTrigger::CRootFinder::getTrueExpression() const
{
  CEvaluationNode * pNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::GE, "GE");
  pNode->addChild(new CEvaluationNodeObject(mpRootValue));
  pNode->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.0"));

  return pNode;
}

CEvaluationNode * CMathTrigger::CRootFinder::getFireExpression() const
{
  CEvaluationNode * pNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
  pNode->addChild(new CEvaluationNodeObject(&mActive));
  pNode->addChild(getTrueExpression());

  return pNode;
}

CEvaluationNode * CMathTrigger::CRootFinder::getEqualityExpression() const
{
  if (mEquality)
    return new CEvaluationNodeConstant(CEvaluationNodeConstant::TRUE, "TRUE");
  else
    return new CEvaluationNodeConstant(CEvaluationNodeConstant::FALSE, "FALSE");
}

void CMathTrigger::CRootFinder::charge()
{
  // TODO ALGORITHM We need to experiment with this!

  // TODO CRITICAL This implementation does not deactivate
  // checks for inequality

  if ((mActive < 1.0) &&
      ((*mpRootValue < 0.0) ||
       ((*mpRootValue <= 0.0) && !mEquality)))
    {
      mActive = 1.0;
    }
  else if ((mActive > 0.0) &&
           ((*mpRootValue > 0.0) ||
            ((*mpRootValue >= 0.0) && mEquality)))
    {
      mActive = 0.0;
    }

  return;
}

void CMathTrigger::CRootFinder::calculateInitialActivity()
{
  if ((*mpRootValue < 0.0)
      || ((*mpRootValue <= 0.0) && !mEquality))
    {
      mActive = 1.0;
    }
  else
    {
      mActive = 0.0;
    }
}

C_FLOAT64 * CMathTrigger::CRootFinder::getRootValuePtr()
{
  return mpRootValue;
}

CMathTrigger::CMathTrigger(const CCopasiContainer * pParent) :
    CCopasiContainer("MathTrigger", pParent, "MathTrigger"),
    mActiveExpression("ActiveExpression", this),
    mTrueExpression("TrueExpression", this),
    mFireExpression("TriggerExpression", this),
    mEqualityExpression("EqualityExpression", this),
    mRootFinders("ListOfRoots", this)
{}

CMathTrigger::CMathTrigger(const CMathTrigger & src,
                           const CCopasiContainer * pParent) :
    CCopasiContainer(src, pParent),
    mActiveExpression(src.mActiveExpression, this),
    mTrueExpression(src.mTrueExpression, this),
    mFireExpression(src.mFireExpression, this),
    mEqualityExpression(src.mEqualityExpression, this),
    mRootFinders(src.mRootFinders, this)
{}

CMathTrigger::~CMathTrigger()
{}

bool CMathTrigger::fire()
{
  // We assume that all root finder are having their current values.

  // First we calculate whether the expression fires.
  bool fire = (mFireExpression.calcValue() > 0);

  // Charge the root finders
  CCopasiVector< CRootFinder >::iterator itRoot = mRootFinders.begin();
  CCopasiVector< CRootFinder >::iterator endRoot = mRootFinders.end();

  for (; itRoot != endRoot; ++itRoot)
    {
      (*itRoot)->charge();
    }

  return fire;
}

void CMathTrigger::calculateInitialActivity()
{
  // Calculate the initial activity for the root finders
  CCopasiVector< CRootFinder >::iterator itRoot = mRootFinders.begin();
  CCopasiVector< CRootFinder >::iterator endRoot = mRootFinders.end();

  for (; itRoot != endRoot; ++itRoot)
    {
      (*itRoot)->calculateInitialActivity();
    }
}

bool CMathTrigger::calculateEquality()
{
  return mEqualityExpression.calcValue() > 0.0;
}

bool CMathTrigger::compile(const CExpression * pTriggerExpression,
                           std::vector< CCopasiContainer * > listOfContainer)
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

  mActiveExpression.setRoot(NULL);
  mTrueExpression.setRoot(NULL);
  mFireExpression.setRoot(NULL);
  mEqualityExpression.setRoot(NULL);
  mRootFinders.clear();

  CEvaluationNode * pFireExpression = NULL;
  CEvaluationNode * pEqualityExpression = NULL;

  bool success = compile(pRoot, pFireExpression, pEqualityExpression);

  assert(mActiveNodes.empty());
  assert(mTrueNodes.empty());
  assert(mFireNodes.empty());
  assert(mEqualityNodes.empty());

  // Build the fire expression
  mFireExpression.setRoot(pFireExpression);
  success &= mFireExpression.compile(listOfContainer);

  // Build the equality expression
  mEqualityExpression.setRoot(pEqualityExpression);
  success &= mEqualityExpression.compile(listOfContainer);

  // Compile all root finder
  CCopasiVector< CRootFinder >::iterator it = mRootFinders.begin();
  CCopasiVector< CRootFinder >::iterator end = mRootFinders.end();

  for (; it != end; ++it)
    {
      success &= (*it)->compile(listOfContainer);
    }

  return success;
}

CCopasiVector< CMathTrigger::CRootFinder > & CMathTrigger::getRootFinders()
{
  return mRootFinders;
}

bool CMathTrigger::compile(const CEvaluationNode * pNode,
                           CEvaluationNode * & pFireExpression,
                           CEvaluationNode * & pEqualityExpression)
{
  bool success = true;
  const CEvaluationNode::Type & Type = pNode->getType();

  switch (CEvaluationNode::type(Type))
    {
      case CEvaluationNode::LOGICAL:

        switch ((int) CEvaluationNode::subType(Type))
          {
            case CEvaluationNodeLogical::AND:
              success = compileAND(pNode, pFireExpression, pEqualityExpression);
              break;

            case CEvaluationNodeLogical::OR:
              success = compileOR(pNode, pFireExpression, pEqualityExpression);
              break;

            case CEvaluationNodeLogical::XOR:
              success = compileXOR(pNode, pFireExpression, pEqualityExpression);
              break;

            case CEvaluationNodeLogical::EQ:
              success = compileEQ(pNode, pFireExpression, pEqualityExpression);
              break;

            case CEvaluationNodeLogical::NE:
              success = compileNE(pNode, pFireExpression, pEqualityExpression);
              break;

            case CEvaluationNodeLogical::LE:
              success = compileLE(pNode, pFireExpression, pEqualityExpression);
              break;

            case CEvaluationNodeLogical::LT:
              success = compileLT(pNode, pFireExpression, pEqualityExpression);
              break;

            case CEvaluationNodeLogical::GE:
              success = compileGE(pNode, pFireExpression, pEqualityExpression);
              break;

            case CEvaluationNodeLogical::GT:
              success = compileGT(pNode, pFireExpression, pEqualityExpression);
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
              success = compileNOT(pNode, pFireExpression, pEqualityExpression);
              break;

            default:
              success = false;
              break;
          }

        break;

      default:
        success = false;
        break;
    }

  return success;
}

bool CMathTrigger::compileAND(const CEvaluationNode * pSource,
                              CEvaluationNode * & pFireExpression,
                              CEvaluationNode * & pEqualityExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  pushNodes(new CEvaluationNodeLogical(CEvaluationNodeLogical::OR, "OR"),
            new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND"));

  CEvaluationNode * pLeftFireExpression;
  CEvaluationNode * pLeftEqualityExpression;

  success &= compile(pLeft, pLeftFireExpression, pLeftEqualityExpression);

  CEvaluationNode * pRightFireExpression;
  CEvaluationNode * pRightEqualityExpression;

  success &= compile(pRight, pRightFireExpression, pRightEqualityExpression);

  pFireExpression = getFireExpression();
  pEqualityExpression = getEqualityExpression(pLeftFireExpression, pLeftEqualityExpression,
                        pRightFireExpression, pRightEqualityExpression);

  popNodes();

  return success;
}

bool CMathTrigger::compileOR(const CEvaluationNode * pSource,
                             CEvaluationNode * & pFireExpression,
                             CEvaluationNode * & pEqualityExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  pushNodes(new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND"),
            new CEvaluationNodeLogical(CEvaluationNodeLogical::OR, "OR"));

  CEvaluationNode * pLeftFireExpression;
  CEvaluationNode * pLeftEqualityExpression;

  success &= compile(pLeft, pLeftFireExpression, pLeftEqualityExpression);

  CEvaluationNode * pRightFireExpression;
  CEvaluationNode * pRightEqualityExpression;

  success &= compile(pRight, pRightFireExpression, pRightEqualityExpression);

  pFireExpression = getFireExpression();
  pEqualityExpression = getEqualityExpression(pLeftFireExpression, pLeftEqualityExpression,
                        pRightFireExpression, pRightEqualityExpression);

  popNodes();

  return success;
}

bool CMathTrigger::compileXOR(const CEvaluationNode * pSource,
                              CEvaluationNode * & pFireExpression,
                              CEvaluationNode * & pEqualityExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  pushNodes(new CEvaluationNodeLogical(CEvaluationNodeLogical::EQ, "EQ"),
            new CEvaluationNodeLogical(CEvaluationNodeLogical::XOR, "XOR"));

  CEvaluationNode * pLeftFireExpression;
  CEvaluationNode * pLeftEqualityExpression;

  success &= compile(pLeft, pLeftFireExpression, pLeftEqualityExpression);

  CEvaluationNode * pRightFireExpression;
  CEvaluationNode * pRightEqualityExpression;

  success &= compile(pRight, pRightFireExpression, pRightEqualityExpression);

  pFireExpression = getFireExpression();
  pEqualityExpression = getEqualityExpression(pLeftFireExpression, pLeftEqualityExpression,
                        pRightFireExpression, pRightEqualityExpression);

  popNodes();

  return success;
}

bool CMathTrigger::compileEQ(const CEvaluationNode * pSource,
                             CEvaluationNode * & pFireExpression,
                             CEvaluationNode * & pEqualityExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  // Equality can be determined between Boolean and double values.
  if (CEvaluationNode::type(pLeft->getType()) != CEvaluationNode::LOGICAL)
    {
      // We treat x EQ y as (x GE y) EQ (y GE x)

      // Create a temporary expression and compile it.
      CEvaluationNode * pEQ = new CEvaluationNodeLogical(CEvaluationNodeLogical::EQ, "EQ");
      CEvaluationNode * pGE = new CEvaluationNodeLogical(CEvaluationNodeLogical::GE, "GEZ");
      pGE->addChild(pLeft->copyBranch());
      pGE->addChild(pRight->copyBranch());
      pEQ->addChild(pGE);

      pGE = new CEvaluationNodeLogical(CEvaluationNodeLogical::GE, "GE");
      pGE->addChild(pRight->copyBranch());
      pGE->addChild(pLeft->copyBranch());
      pEQ->addChild(pGE);

      success &= compileEQ(pEQ, pFireExpression, pEqualityExpression);

      // Delete the temporary
      pdelete(pEQ);
    }
  else
    {
      pushNodes(new CEvaluationNodeLogical(CEvaluationNodeLogical::XOR, "XOR"),
                new CEvaluationNodeLogical(CEvaluationNodeLogical::EQ, "EQ"));

      CEvaluationNode * pLeftFireExpression;
      CEvaluationNode * pLeftEqualityExpression;

      success &= compile(pLeft, pLeftFireExpression, pLeftEqualityExpression);

      CEvaluationNode * pRightFireExpression;
      CEvaluationNode * pRightEqualityExpression;

      success &= compile(pRight, pRightFireExpression, pRightEqualityExpression);

      pFireExpression = getFireExpression();
      pEqualityExpression = getEqualityExpression(pLeftFireExpression, pLeftEqualityExpression,
                            pRightFireExpression, pRightEqualityExpression);

      popNodes();
    }

  return success;
}

bool CMathTrigger::compileNE(const CEvaluationNode * pSource,
                             CEvaluationNode * & pFireExpression,
                             CEvaluationNode * & pEqualityExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  // We treat this as NOT and EQ.
  // For this we create a modified copy of the current node.

  CEvaluationNode * pNotNode = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
  CEvaluationNode * pEqNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::EQ, "EQ");
  pEqNode->addChild(pLeft->copyBranch());
  pEqNode->addChild(pRight->copyBranch());
  pNotNode->addChild(pEqNode);

  success &= compileNOT(pNotNode, pFireExpression, pEqualityExpression);

  // Delete the temporary
  delete pNotNode;

  return success;
}

bool CMathTrigger::compileLE(const CEvaluationNode * pSource,
                             CEvaluationNode * & pFireExpression,
                             CEvaluationNode * & pEqualityExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  CEvaluationNode * pNode;

  // We need to create a root finding structures
  pNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
  pNode->addChild(pRight->copyBranch());
  pNode->addChild(pLeft->copyBranch());

  CRootFinder * pRootFinder = new CRootFinder();
  pRootFinder->mRoot.setRoot(pNode);
  pRootFinder->mEquality = true;
  mRootFinders.add(pRootFinder, true);

  pFireExpression = pRootFinder->getFireExpression();
  pEqualityExpression = pRootFinder->getEqualityExpression();

  return success;
}

bool CMathTrigger::compileLT(const CEvaluationNode * pSource,
                             CEvaluationNode * & pFireExpression,
                             CEvaluationNode * & pEqualityExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  CEvaluationNode * pNode;

  // We need to create a root finding structures
  pNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
  pNode->addChild(pRight->copyBranch());
  pNode->addChild(pLeft->copyBranch());

  CRootFinder * pRootFinder = new CRootFinder();
  pRootFinder->mRoot.setRoot(pNode);
  pRootFinder->mEquality = false;
  mRootFinders.add(pRootFinder, true);

  pFireExpression = pRootFinder->getFireExpression();
  pEqualityExpression = pRootFinder->getEqualityExpression();

  return success;
}

bool CMathTrigger::compileGE(const CEvaluationNode * pSource,
                             CEvaluationNode * & pFireExpression,
                             CEvaluationNode * & pEqualityExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  CEvaluationNode * pNode;

  // We need to create a root finding structures
  pNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
  pNode->addChild(pLeft->copyBranch());
  pNode->addChild(pRight->copyBranch());

  CRootFinder * pRootFinder = new CRootFinder();
  pRootFinder->mRoot.setRoot(pNode);
  pRootFinder->mEquality = true;
  mRootFinders.add(pRootFinder, true);

  pFireExpression = pRootFinder->getFireExpression();
  pEqualityExpression = pRootFinder->getEqualityExpression();

  return success;
}

bool CMathTrigger::compileGT(const CEvaluationNode * pSource,
                             CEvaluationNode * & pFireExpression,
                             CEvaluationNode * & pEqualityExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  CEvaluationNode * pNode;

  // We need to create a root finding structures
  pNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
  pNode->addChild(pLeft->copyBranch());
  pNode->addChild(pRight->copyBranch());

  CRootFinder * pRootFinder = new CRootFinder();
  pRootFinder->mRoot.setRoot(pNode);
  pRootFinder->mEquality = false;
  mRootFinders.add(pRootFinder, true);

  pFireExpression = pRootFinder->getFireExpression();
  pEqualityExpression = pRootFinder->getEqualityExpression();

  return success;
}

bool CMathTrigger::compileNOT(const CEvaluationNode * pSource,
                              CEvaluationNode * & pFireExpression,
                              CEvaluationNode * & pEqualityExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());

  pushNodes(new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT"),
            new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT"));

  CEvaluationNode * pLeftFireExpression;
  CEvaluationNode * pLeftEqualityExpression;

  success &= compile(pLeft, pLeftFireExpression, pLeftEqualityExpression);

  pFireExpression = getFireExpression();

  pEqualityExpression = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
  pEqualityExpression->addChild(pLeftEqualityExpression);
  pdelete(pLeftFireExpression);

  popNodes();

  return success;
}

void CMathTrigger::pushNodes(CEvaluationNode * pActiveNode,
                             CEvaluationNode * pTrueNode)
{
  if (!mActiveNodes.empty())
    {
      mActiveNodes.top()->addChild(pActiveNode);
    }

  mActiveNodes.push(pActiveNode);

  if (!mTrueNodes.empty())
    {
      mTrueNodes.top()->addChild(pTrueNode);
    }

  mTrueNodes.push(pTrueNode);
}

void CMathTrigger::popNodes()
{
  CEvaluationNode * pNode = mActiveNodes.top();
  mActiveNodes.pop();

  if (mActiveNodes.empty())
    {
      mActiveExpression.setRoot(pNode);
    }

  pNode = mTrueNodes.top();
  mTrueNodes.pop();

  if (mTrueNodes.empty())
    {
      mTrueExpression.setRoot(pNode);
    }
}

void CMathTrigger::addNodes(CEvaluationNode * pActiveNode,
                            CEvaluationNode * pTrueNode)
{
  if (!mActiveNodes.empty())
    {
      mActiveNodes.top()->addChild(pActiveNode);
    }
  else
    {
      mActiveExpression.setRoot(pActiveNode);
    }

  if (!mTrueNodes.empty())
    {
      mTrueNodes.top()->addChild(pTrueNode);
    }
  else
    {
      mTrueExpression.setRoot(pTrueNode);
    }
}

// static
CEvaluationNode * CMathTrigger::getEqualityExpression(CEvaluationNode * pFireExpressionX,
    CEvaluationNode * pEqualityExpressionX,
    CEvaluationNode * pFireExpressionY,
    CEvaluationNode * pEqualityExpressionY)
{
  CEvaluationNode * pResult = NULL;
  CEvaluationNode * pIntermediate = NULL;

  CEvaluationNode * pX = NULL;
  CEvaluationNode * pY = NULL;
  CEvaluationNode * pXY = NULL;

  bool XStatic = false;
  bool XEqual = false;
  bool YStatic = false;
  bool YEqual = false;

  if (CEvaluationNode::type(pEqualityExpressionX->getType()) == CEvaluationNode::CONSTANT)
    {
      XStatic = true;

      if (CEvaluationNode::subType(pEqualityExpressionX->getType()) == (int) CEvaluationNodeConstant::TRUE)
        {
          XEqual = true;

          pX = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
          pX->addChild(pFireExpressionX->copyBranch());

          CEvaluationNode *pNot = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
          pNot->addChild(pFireExpressionY->copyBranch());
          pX->addChild(pNot);
        }
    }
  else
    {
      pX = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
      pX->addChild(pFireExpressionX->copyBranch());

      CEvaluationNode * pAnd = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
      pAnd->addChild(pEqualityExpressionX->copyBranch());

      CEvaluationNode *pNot = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
      pNot->addChild(pFireExpressionY->copyBranch());
      pAnd->addChild(pNot);

      pX->addChild(pAnd);
    }

  if (CEvaluationNode::type(pEqualityExpressionY->getType()) == CEvaluationNode::CONSTANT)
    {
      YStatic = true;

      if (CEvaluationNode::subType(pEqualityExpressionY->getType()) == (int) CEvaluationNodeConstant::TRUE)
        {
          YEqual = true;

          pY = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
          pY->addChild(pFireExpressionY->copyBranch());

          CEvaluationNode *pNot = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
          pNot->addChild(pFireExpressionX->copyBranch());
          pY->addChild(pNot);
        }
    }
  else
    {
      pY = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
      pY->addChild(pFireExpressionY->copyBranch());

      CEvaluationNode * pAnd = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
      pAnd->addChild(pEqualityExpressionY->copyBranch());

      CEvaluationNode *pNot = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
      pNot->addChild(pFireExpressionX->copyBranch());
      pAnd->addChild(pNot);

      pY->addChild(pAnd);
    }

  if (XStatic && YStatic)
    {
      if (XEqual && YEqual)
        {
          pdelete(pX);
          pdelete(pY);

          pXY = new CEvaluationNodeConstant(CEvaluationNodeConstant::TRUE, "TRUE");
        }
    }
  else if (XStatic)
    {
      if (XEqual)
        pXY = pEqualityExpressionY;
    }
  else if (YStatic)
    {
      if (YEqual)
        pXY = pEqualityExpressionX;
    }
  else
    {
      pXY = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
      pXY->addChild(pEqualityExpressionX);
      pXY->addChild(pEqualityExpressionY);
    }

  if (pX != NULL && pY != NULL)
    {
      pIntermediate = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
      pIntermediate->addChild(pX);
      pIntermediate->addChild(pY);
    }
  else if (pX != NULL)
    {
      pIntermediate = pX;
    }
  else if (pY != NULL)
    {
      pIntermediate = pY;
    }

  if (pIntermediate != NULL && pXY != NULL)
    {
      pResult = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
      pResult->addChild(pIntermediate);
      pResult->addChild(pXY);
    }
  else if (pIntermediate != NULL)
    {
      pResult = pIntermediate;
    }
  else if (pXY != NULL)
    {
      pResult = pXY;
    }
  else
    {
      pResult = new CEvaluationNodeConstant(CEvaluationNodeConstant::FALSE, "FALSE");
    }

  // We used copyBranch thus we need to delete the expressions.
  pdelete(pFireExpressionX);
  pdelete(pEqualityExpressionX);
  pdelete(pFireExpressionY);
  pdelete(pEqualityExpressionY);

  return pResult;
}

CEvaluationNode * CMathTrigger::getFireExpression() const
{
  CEvaluationNode * pNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
  pNode->addChild(mActiveNodes.top()->copyBranch());
  pNode->addChild(mTrueNodes.top()->copyBranch());

  return pNode;
}
