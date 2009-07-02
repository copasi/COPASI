// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/Attic/CMathTrigger.cpp,v $
//   $Revision: 1.20 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/07/02 11:43:13 $
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

CEvaluationNode * CMathTrigger::CRootFinder::getTrueExpression(const C_FLOAT64 * pEquality) const
{
  CEvaluationNode * pTrueExpression = NULL;

  if (mEquality)
    {
      pTrueExpression = new CEvaluationNodeLogical(CEvaluationNodeLogical::GE, "GE");
      pTrueExpression->addChild(new CEvaluationNodeObject(mpRootValue));
      pTrueExpression->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.0"));
    }
  else
    {
      pTrueExpression = new CEvaluationNodeLogical(CEvaluationNodeLogical::OR, "OR");

      CEvaluationNode * pGT = new CEvaluationNodeLogical(CEvaluationNodeLogical::GT, "GT");
      pGT->addChild(new CEvaluationNodeObject(mpRootValue));
      pGT->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.0"));
      pTrueExpression->addChild(pGT);

      CEvaluationNode * pAND = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");

      CEvaluationNode * pInequality = new CEvaluationNodeLogical(CEvaluationNodeLogical::LT, "LT");
      pInequality->addChild(new CEvaluationNodeObject(pEquality));
      pInequality->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0"));
      pAND->addChild(pInequality);

      CEvaluationNode * pGE = new CEvaluationNodeLogical(CEvaluationNodeLogical::GE, "GE");
      pGE->addChild(new CEvaluationNodeObject(mpRootValue));
      pGE->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.0"));
      pAND->addChild(pGE);

      pTrueExpression->addChild(pAND);
    }

  return pTrueExpression;
}

CEvaluationNode * CMathTrigger::CRootFinder::getActiveExpression() const
{
  CEvaluationNode * pNode = new CEvaluationNodeObject(&mActive);

  return pNode;
}

CEvaluationNode * CMathTrigger::CRootFinder::getEqualityExpression() const
{
  if (mEquality)
    return new CEvaluationNodeConstant(CEvaluationNodeConstant::TRUE, "TRUE");
  else
    return new CEvaluationNodeConstant(CEvaluationNodeConstant::FALSE, "FALSE");
}

void CMathTrigger::CRootFinder::charge(const bool & equality)
{
  // TODO ALGORITHM We need to experiment with this!

  if ((mActive < 1.0) &&
      (equality == mEquality))
    {
      mActive = 1.0;
    }
  else if ((mActive > 0.0) &&
           (equality == mEquality))
    {
      mActive = 0.0;
    }

  return;
}

void CMathTrigger::CRootFinder::calculateInitialActivity()
{
  if ((*mpRootValue < 0.0) ||
      ((*mpRootValue <= 0.0) && !mEquality))
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
    mEquality(1.0),
    mRootFinders("ListOfRoots", this)
{}

CMathTrigger::CMathTrigger(const CMathTrigger & src,
                           const CCopasiContainer * pParent) :
    CCopasiContainer(src, pParent),
    mActiveExpression(src.mActiveExpression, this),
    mTrueExpression(src.mTrueExpression, this),
    mFireExpression(src.mFireExpression, this),
    mEqualityExpression(src.mEqualityExpression, this),
    mEquality(src.mEquality),
    mRootFinders(src.mRootFinders, this)
{}

CMathTrigger::~CMathTrigger()
{}

bool CMathTrigger::fire(const bool & equality)
{
  // Set the equality value so that the fire condition can be evaluated
  // correctly.
  mEquality = equality ? 1.0 : 0.0;

  // We assume that all root finder are having their current values.
  bool Fire = mFireExpression.calcValue() > 0;
  bool Equality = mEqualityExpression.calcValue() > 0;

  return (Fire && (Equality == equality));
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

  CEvaluationNode * pTrueExpression = NULL;
  CEvaluationNode * pActiveExpression = NULL;
  CEvaluationNode * pFireExpression = NULL;
  CEvaluationNode * pEqualityExpression = NULL;

  bool success = compile(pRoot, pTrueExpression, pActiveExpression,
                         pFireExpression, pEqualityExpression);

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
                           CEvaluationNode * & pTrueExpression,
                           CEvaluationNode * & pActiveExpression,
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
              success = compileAND(pNode, pTrueExpression, pActiveExpression,
                                   pFireExpression, pEqualityExpression);
              break;

            case CEvaluationNodeLogical::OR:
              success = compileOR(pNode, pTrueExpression, pActiveExpression,
                                  pFireExpression, pEqualityExpression);
              break;

            case CEvaluationNodeLogical::XOR:
              success = compileXOR(pNode, pTrueExpression, pActiveExpression,
                                   pFireExpression, pEqualityExpression);
              break;

            case CEvaluationNodeLogical::EQ:
              success = compileEQ(pNode, pTrueExpression, pActiveExpression,
                                  pFireExpression, pEqualityExpression);
              break;

            case CEvaluationNodeLogical::NE:
              success = compileNE(pNode, pTrueExpression, pActiveExpression,
                                  pFireExpression, pEqualityExpression);
              break;

            case CEvaluationNodeLogical::LE:
              success = compileLE(pNode, pTrueExpression, pActiveExpression,
                                  pFireExpression, pEqualityExpression);
              break;

            case CEvaluationNodeLogical::LT:
              success = compileLT(pNode, pTrueExpression, pActiveExpression,
                                  pFireExpression, pEqualityExpression);
              break;

            case CEvaluationNodeLogical::GE:
              success = compileGE(pNode, pTrueExpression, pActiveExpression,
                                  pFireExpression, pEqualityExpression);
              break;

            case CEvaluationNodeLogical::GT:
              success = compileGT(pNode, pTrueExpression, pActiveExpression,
                                  pFireExpression, pEqualityExpression);
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
              success = compileNOT(pNode, pTrueExpression, pActiveExpression,
                                   pFireExpression, pEqualityExpression);
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
                              CEvaluationNode * & pTrueExpression,
                              CEvaluationNode * & pActiveExpression,
                              CEvaluationNode * & pFireExpression,
                              CEvaluationNode * & pEqualityExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  CEvaluationNode * pLeftTrueExpression = NULL;
  CEvaluationNode * pLeftActiveExpression = NULL;
  CEvaluationNode * pLeftFireExpression = NULL;
  CEvaluationNode * pLeftEqualityExpression = NULL;

  success &= compile(pLeft, pLeftTrueExpression, pLeftActiveExpression,
                     pLeftFireExpression, pLeftEqualityExpression);

  CEvaluationNode * pRightTrueExpression = NULL;
  CEvaluationNode * pRightActiveExpression = NULL;
  CEvaluationNode * pRightFireExpression = NULL;
  CEvaluationNode * pRightEqualityExpression = NULL;

  success &= compile(pRight, pRightTrueExpression, pRightActiveExpression,
                     pRightFireExpression, pRightEqualityExpression);

  pTrueExpression = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
  pTrueExpression->addChild(pLeftTrueExpression->copyBranch());
  pTrueExpression->addChild(pRightTrueExpression->copyBranch());

  pActiveExpression = new CEvaluationNodeLogical(CEvaluationNodeLogical::OR, "OR");
  pActiveExpression->addChild(pLeftActiveExpression->copyBranch());
  pActiveExpression->addChild(pRightActiveExpression->copyBranch());

  pFireExpression = getFireExpression(pTrueExpression, pActiveExpression);
  pEqualityExpression = getEqualityExpression(pLeftFireExpression, pLeftEqualityExpression,
                        pRightFireExpression, pRightEqualityExpression);

  // We used copyBranch thus we need to delete the expressions.
  pdelete(pLeftTrueExpression);
  pdelete(pLeftActiveExpression);
  pdelete(pLeftFireExpression);
  pdelete(pLeftEqualityExpression);

  pdelete(pRightTrueExpression);
  pdelete(pRightActiveExpression);
  pdelete(pRightFireExpression);
  pdelete(pRightEqualityExpression);

  return success;
}

bool CMathTrigger::compileOR(const CEvaluationNode * pSource,
                             CEvaluationNode * & pTrueExpression,
                             CEvaluationNode * & pActiveExpression,
                             CEvaluationNode * & pFireExpression,
                             CEvaluationNode * & pEqualityExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  CEvaluationNode * pLeftTrueExpression = NULL;
  CEvaluationNode * pLeftActiveExpression = NULL;
  CEvaluationNode * pLeftFireExpression = NULL;
  CEvaluationNode * pLeftEqualityExpression = NULL;

  success &= compile(pLeft, pLeftTrueExpression, pLeftActiveExpression,
                     pLeftFireExpression, pLeftEqualityExpression);

  CEvaluationNode * pRightTrueExpression = NULL;
  CEvaluationNode * pRightActiveExpression = NULL;
  CEvaluationNode * pRightFireExpression = NULL;
  CEvaluationNode * pRightEqualityExpression = NULL;

  success &= compile(pRight, pRightTrueExpression, pRightActiveExpression,
                     pRightFireExpression, pRightEqualityExpression);

  pTrueExpression = new CEvaluationNodeLogical(CEvaluationNodeLogical::OR, "OR");
  pTrueExpression->addChild(pLeftTrueExpression->copyBranch());
  pTrueExpression->addChild(pRightTrueExpression->copyBranch());

  pActiveExpression = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
  pActiveExpression->addChild(pLeftActiveExpression->copyBranch());
  pActiveExpression->addChild(pRightActiveExpression->copyBranch());

  pFireExpression = getFireExpression(pTrueExpression, pActiveExpression);
  pEqualityExpression = getEqualityExpression(pLeftFireExpression, pLeftEqualityExpression,
                        pRightFireExpression, pRightEqualityExpression);

  // We used copyBranch thus we need to delete the expressions.
  pdelete(pLeftTrueExpression);
  pdelete(pLeftActiveExpression);
  pdelete(pLeftFireExpression);
  pdelete(pLeftEqualityExpression);

  pdelete(pRightTrueExpression);
  pdelete(pRightActiveExpression);
  pdelete(pRightFireExpression);
  pdelete(pRightEqualityExpression);

  return success;
}

bool CMathTrigger::compileXOR(const CEvaluationNode * pSource,
                              CEvaluationNode * & pTrueExpression,
                              CEvaluationNode * & pActiveExpression,
                              CEvaluationNode * & pFireExpression,
                              CEvaluationNode * & pEqualityExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  CEvaluationNode * pLeftTrueExpression = NULL;
  CEvaluationNode * pLeftActiveExpression = NULL;
  CEvaluationNode * pLeftFireExpression = NULL;
  CEvaluationNode * pLeftEqualityExpression = NULL;

  success &= compile(pLeft, pLeftTrueExpression, pLeftActiveExpression,
                     pLeftFireExpression, pLeftEqualityExpression);

  CEvaluationNode * pRightTrueExpression = NULL;
  CEvaluationNode * pRightActiveExpression = NULL;
  CEvaluationNode * pRightFireExpression = NULL;
  CEvaluationNode * pRightEqualityExpression = NULL;

  success &= compile(pRight, pRightTrueExpression, pRightActiveExpression,
                     pRightFireExpression, pRightEqualityExpression);

  pTrueExpression = new CEvaluationNodeLogical(CEvaluationNodeLogical::XOR, "XOR");
  pTrueExpression->addChild(pLeftTrueExpression->copyBranch());
  pTrueExpression->addChild(pRightTrueExpression->copyBranch());

  pActiveExpression = new CEvaluationNodeLogical(CEvaluationNodeLogical::EQ, "EQ");
  pActiveExpression->addChild(pLeftActiveExpression->copyBranch());
  pActiveExpression->addChild(pRightActiveExpression->copyBranch());

  pFireExpression = getFireExpression(pTrueExpression, pActiveExpression);
  pEqualityExpression = getEqualityExpression(pLeftFireExpression, pLeftEqualityExpression,
                        pRightFireExpression, pRightEqualityExpression);

  // We used copyBranch thus we need to delete the expressions.
  pdelete(pLeftTrueExpression);
  pdelete(pLeftActiveExpression);
  pdelete(pLeftFireExpression);
  pdelete(pLeftEqualityExpression);

  pdelete(pRightTrueExpression);
  pdelete(pRightActiveExpression);
  pdelete(pRightFireExpression);
  pdelete(pRightEqualityExpression);

  return success;
}

bool CMathTrigger::compileEQ(const CEvaluationNode * pSource,
                             CEvaluationNode * & pTrueExpression,
                             CEvaluationNode * & pActiveExpression,
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
      CEvaluationNode * pGE = new CEvaluationNodeLogical(CEvaluationNodeLogical::GE, "GE");
      pGE->addChild(pLeft->copyBranch());
      pGE->addChild(pRight->copyBranch());
      pEQ->addChild(pGE);

      pGE = new CEvaluationNodeLogical(CEvaluationNodeLogical::GE, "GE");
      pGE->addChild(pRight->copyBranch());
      pGE->addChild(pLeft->copyBranch());
      pEQ->addChild(pGE);

      success &= compileEQ(pEQ, pTrueExpression, pActiveExpression,
                           pFireExpression, pEqualityExpression);

      // Delete the temporary
      pdelete(pEQ);
    }
  else
    {
      CEvaluationNode * pLeftTrueExpression = NULL;
      CEvaluationNode * pLeftActiveExpression = NULL;
      CEvaluationNode * pLeftFireExpression = NULL;
      CEvaluationNode * pLeftEqualityExpression = NULL;

      success &= compile(pLeft, pLeftTrueExpression, pLeftActiveExpression,
                         pLeftFireExpression, pLeftEqualityExpression);

      CEvaluationNode * pRightTrueExpression = NULL;
      CEvaluationNode * pRightActiveExpression = NULL;
      CEvaluationNode * pRightFireExpression = NULL;
      CEvaluationNode * pRightEqualityExpression = NULL;

      success &= compile(pRight, pRightTrueExpression, pRightActiveExpression,
                         pRightFireExpression, pRightEqualityExpression);

      pTrueExpression = new CEvaluationNodeLogical(CEvaluationNodeLogical::EQ, "EQ");
      pTrueExpression->addChild(pLeftTrueExpression->copyBranch());
      pTrueExpression->addChild(pRightTrueExpression->copyBranch());

      pActiveExpression = new CEvaluationNodeLogical(CEvaluationNodeLogical::XOR, "XOR");
      pActiveExpression->addChild(pLeftActiveExpression->copyBranch());
      pActiveExpression->addChild(pRightActiveExpression->copyBranch());

      pFireExpression = getFireExpression(pTrueExpression, pActiveExpression);
      pEqualityExpression = getEqualityExpression(pLeftFireExpression, pLeftEqualityExpression,
                            pRightFireExpression, pRightEqualityExpression);

      // We used copyBranch thus we need to delete the expressions.
      pdelete(pLeftTrueExpression);
      pdelete(pLeftActiveExpression);
      pdelete(pLeftFireExpression);
      pdelete(pLeftEqualityExpression);

      pdelete(pRightTrueExpression);
      pdelete(pRightActiveExpression);
      pdelete(pRightFireExpression);
      pdelete(pRightEqualityExpression);
    }

  return success;
}

bool CMathTrigger::compileNE(const CEvaluationNode * pSource,
                             CEvaluationNode * & pTrueExpression,
                             CEvaluationNode * & pActiveExpression,
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

  success &= compileNOT(pNotNode, pTrueExpression, pActiveExpression,
                        pFireExpression, pEqualityExpression);

  // Delete the temporary
  delete pNotNode;

  return success;
}

bool CMathTrigger::compileLE(const CEvaluationNode * pSource,
                             CEvaluationNode * & pTrueExpression,
                             CEvaluationNode * & pActiveExpression,
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

  pTrueExpression = pRootFinder->getTrueExpression(&mEquality);
  pActiveExpression = pRootFinder->getActiveExpression();
  pEqualityExpression = pRootFinder->getEqualityExpression();

  pFireExpression = getFireExpression(pTrueExpression, pActiveExpression);

  return success;
}

bool CMathTrigger::compileLT(const CEvaluationNode * pSource,
                             CEvaluationNode * & pTrueExpression,
                             CEvaluationNode * & pActiveExpression,
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

  pTrueExpression = pRootFinder->getTrueExpression(&mEquality);
  pActiveExpression = pRootFinder->getActiveExpression();
  pEqualityExpression = pRootFinder->getEqualityExpression();

  pFireExpression = getFireExpression(pTrueExpression, pActiveExpression);

  return success;
}

bool CMathTrigger::compileGE(const CEvaluationNode * pSource,
                             CEvaluationNode * & pTrueExpression,
                             CEvaluationNode * & pActiveExpression,
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

  pTrueExpression = pRootFinder->getTrueExpression(&mEquality);
  pActiveExpression = pRootFinder->getActiveExpression();
  pEqualityExpression = pRootFinder->getEqualityExpression();

  pFireExpression = getFireExpression(pTrueExpression, pActiveExpression);

  return success;
}

bool CMathTrigger::compileGT(const CEvaluationNode * pSource,
                             CEvaluationNode * & pTrueExpression,
                             CEvaluationNode * & pActiveExpression,
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

  pTrueExpression = pRootFinder->getTrueExpression(&mEquality);
  pActiveExpression = pRootFinder->getActiveExpression();
  pEqualityExpression = pRootFinder->getEqualityExpression();

  pFireExpression = getFireExpression(pTrueExpression, pActiveExpression);

  return success;
}

bool CMathTrigger::compileNOT(const CEvaluationNode * pSource,
                              CEvaluationNode * & pTrueExpression,
                              CEvaluationNode * & pActiveExpression,
                              CEvaluationNode * & pFireExpression,
                              CEvaluationNode * & pEqualityExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());

  CEvaluationNode * pLeftTrueExpression = NULL;
  CEvaluationNode * pLeftActiveExpression = NULL;
  CEvaluationNode * pLeftFireExpression = NULL;
  CEvaluationNode * pLeftEqualityExpression = NULL;

  success &= compile(pLeft, pLeftTrueExpression, pLeftActiveExpression,
                     pLeftFireExpression, pLeftEqualityExpression);

  pTrueExpression = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
  pTrueExpression->addChild(pLeftTrueExpression->copyBranch());

  pActiveExpression = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
  pActiveExpression->addChild(pLeftActiveExpression->copyBranch());

  pFireExpression = getFireExpression(pTrueExpression, pActiveExpression);

  pEqualityExpression = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
  pEqualityExpression->addChild(pLeftEqualityExpression);

  // We used copyBranch thus we need to delete the expressions.
  pdelete(pLeftTrueExpression);
  pdelete(pLeftActiveExpression);
  pdelete(pLeftFireExpression);
  pdelete(pLeftEqualityExpression);

  return success;
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

  return pResult;
}

// static
CEvaluationNode * CMathTrigger::getFireExpression(CEvaluationNode * pTrueExpression,
    CEvaluationNode * pActiveExpression)
{
  CEvaluationNode * pNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
  pNode->addChild(pTrueExpression->copyBranch());
  pNode->addChild(pActiveExpression->copyBranch());

  return pNode;
}
