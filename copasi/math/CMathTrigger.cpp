// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <cmath>

#include "copasi.h"

#include "CMathTrigger.h"
#include "function/CEvaluationNode.h"
#include "report/CCopasiObjectReference.h"

CMathTrigger::CRootFinder::CRootFinder(const CCopasiContainer * pParent) :
  CCopasiContainer("Root", pParent),
  mRoot("Expression", this),
  mpRootValue(NULL),
  mEquality(false),
  mDiscrete(false),
  mTrue(0.0),
  mLastToggleTime(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
{
  initObjects();
}

CMathTrigger::CRootFinder::CRootFinder(const CMathTrigger::CRootFinder & src,
                                       const CCopasiContainer * pParent) :
  CCopasiContainer(src, pParent),
  mRoot(src.mRoot, this),
  mpRootValue(NULL),
  mEquality(src.mEquality),
  mDiscrete(src.mDiscrete),
  mTrue(src.mTrue),
  mLastToggleTime(src.mLastToggleTime)
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

void CMathTrigger::CRootFinder::determineDiscrete(const std::set< const CCopasiObject * > & stateVariables)
{
  mDiscrete = !mRoot.dependsOn(stateVariables);
}

const bool & CMathTrigger::CRootFinder::isDiscrete() const
{
  return mDiscrete;
}

const bool & CMathTrigger::CRootFinder::isEquality() const
{
  return mEquality;
}

bool CMathTrigger::CRootFinder::isTrue() const
{
  return mTrue > 0.5;
}

CEvaluationNode * CMathTrigger::CRootFinder::getTrueExpression() const
{
  CEvaluationNode * pTrueExpression = NULL;

  pTrueExpression = new CEvaluationNodeLogical(CEvaluationNodeLogical::GT, "GT");
  pTrueExpression->addChild(new CEvaluationNodeObject(&mTrue));
  pTrueExpression->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.5"));

  return pTrueExpression;
}

void CMathTrigger::CRootFinder::toggle(const C_FLOAT64 & time,
                                       const bool & equality,
                                       const bool & continous)
{
  // This function must only be called if we found a root, i.e., the
  // value of the root expression changes sign. In that case it is save
  // to toggle the activity.

  if (continous &&
      !isnan(mLastToggleTime) &&
      mLastToggleTime == time)
    {
      return;
    }

  if (mDiscrete &&
      equality == true)
    {
      mTrue = (mTrue > 0.5) ? 0.0 : 1.0;
      mLastToggleTime = time;
    }
  else if (!mDiscrete)
    {
      if (equality == mEquality && mTrue < 0.5)
        {
          mTrue = 1.0;
          mLastToggleTime = time;
        }
      else if (equality != mEquality && mTrue > 0.5)
        {
          mTrue = 0.0;
          mLastToggleTime = time;
        }
    }

  return;
}

void CMathTrigger::CRootFinder::toggle(const C_FLOAT64 & time)
{
  // This function must only be called if we found a root, i.e., the
  // value of the root expression changes sign. In that case it is save
  // to toggle the activity.

  mTrue = (mTrue > 0.5) ? 0.0 : 1.0;
  mLastToggleTime = time;

  return;
}

void CMathTrigger::CRootFinder::applyInitialValues()
{
  calculateTrueValue();
  mLastToggleTime = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
}

void CMathTrigger::CRootFinder::calculateTrueValue()
{
  if ((*mpRootValue < 0.0) ||
      ((*mpRootValue <= 0.0) && !mEquality))
    {
      mTrue = 0.0;
    }
  else
    {
      mTrue = 1.0;
    }
}

C_FLOAT64 * CMathTrigger::CRootFinder::getRootValuePtr()
{
  return mpRootValue;
}

CMathTrigger::CMathTrigger(const CCopasiContainer * pParent) :
  CCopasiContainer("MathTrigger", pParent, "MathTrigger"),
  mTrueExpression("TrueExpression", this),
  mRootFinders("ListOfRoots", this),
  mFunctionVariableMap()
{}

CMathTrigger::CMathTrigger(const CMathTrigger & src,
                           const CCopasiContainer * pParent) :
  CCopasiContainer(src, pParent),
  mTrueExpression(src.mTrueExpression, this),
  mRootFinders(src.mRootFinders, this),
  mFunctionVariableMap()
{}

CMathTrigger::~CMathTrigger()
{}

void CMathTrigger::applyInitialValues()
{
  // Calculate the initial truth value for the root finders
  CCopasiVector< CRootFinder >::iterator itRoot = mRootFinders.begin();
  CCopasiVector< CRootFinder >::iterator endRoot = mRootFinders.end();

  for (; itRoot != endRoot; ++itRoot)
    {
      (*itRoot)->applyInitialValues();
    }
}

void CMathTrigger::calculateTrueValue()
{
  // Calculate the current truth value for the root finders
  CCopasiVector< CRootFinder >::iterator itRoot = mRootFinders.begin();
  CCopasiVector< CRootFinder >::iterator endRoot = mRootFinders.end();

  for (; itRoot != endRoot; ++itRoot)
    {
      (*itRoot)->calculateTrueValue();
    }
}

bool CMathTrigger::calculate()
{
  return mTrueExpression.calcValue() > 0.0;
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
  if (!pRoot->isBoolean())
    return false;

  mTrueExpression.setInfix("");
  mRootFinders.clear();

  CEvaluationNode * pTrueExpression = NULL;

  bool success = compile(pRoot, pTrueExpression);

  // Build the true expression
  mTrueExpression.setRoot(pTrueExpression);
  success &= mTrueExpression.compile(listOfContainer);

  // Compile all root finder
  CCopasiVector< CRootFinder >::iterator it = mRootFinders.begin();
  CCopasiVector< CRootFinder >::iterator end = mRootFinders.end();

  for (; it != end; ++it)
    {
      success &= (*it)->compile(listOfContainer);
    }

  assert(mFunctionVariableMap.empty());

  return success;
}

CCopasiVector< CMathTrigger::CRootFinder > & CMathTrigger::getRootFinders()
{
  return mRootFinders;
}

bool CMathTrigger::compile(const CEvaluationNode * pNode,
                           CEvaluationNode * & pTrueExpression)
{
  bool success = true;
  const CEvaluationNode::Type & Type = pNode->getType();

  switch (CEvaluationNode::type(Type))
    {
      case CEvaluationNode::LOGICAL:

        switch ((int) CEvaluationNode::subType(Type))
          {
            case CEvaluationNodeLogical::AND:
              success = compileAND(pNode, pTrueExpression);
              break;

            case CEvaluationNodeLogical::OR:
              success = compileOR(pNode, pTrueExpression);
              break;

            case CEvaluationNodeLogical::XOR:
              success = compileXOR(pNode, pTrueExpression);
              break;

            case CEvaluationNodeLogical::EQ:
              success = compileEQ(pNode, pTrueExpression);
              break;

            case CEvaluationNodeLogical::NE:
              success = compileNE(pNode, pTrueExpression);
              break;

            case CEvaluationNodeLogical::LE:
              success = compileLE(pNode, pTrueExpression);
              break;

            case CEvaluationNodeLogical::LT:
              success = compileLT(pNode, pTrueExpression);
              break;

            case CEvaluationNodeLogical::GE:
              success = compileGE(pNode, pTrueExpression);
              break;

            case CEvaluationNodeLogical::GT:
              success = compileGT(pNode, pTrueExpression);
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
              success = compileNOT(pNode, pTrueExpression);
              break;

            default:
              success = false;
              break;
          }

        break;

      case CEvaluationNode::CALL:

        switch ((int) CEvaluationNode::subType(Type))
          {
            case CEvaluationNodeCall::FUNCTION:
              success = compileFUNCTION(pNode, pTrueExpression);
              break;

            case CEvaluationNodeCall::EXPRESSION:
              success = compileEXPRESSION(pNode, pTrueExpression);
              break;

            default:
              success = false;
              break;
          }

        break;

      case CEvaluationNode::VARIABLE:

        switch ((int) CEvaluationNode::subType(Type))
          {
            case CEvaluationNodeVariable::ANY:
              success = compileVARIABLE(pNode, pTrueExpression);
              break;

            default:
              success = false;
              break;
          }

        break;

      case CEvaluationNode::CONSTANT:

        switch ((int) CEvaluationNode::subType(Type))
          {
            case CEvaluationNodeConstant::TRUE:
              pTrueExpression = new CEvaluationNodeConstant(CEvaluationNodeConstant::TRUE, "TRUE");
              success = true;
              break;

            case CEvaluationNodeConstant::FALSE:
              pTrueExpression = new CEvaluationNodeConstant(CEvaluationNodeConstant::FALSE, "FALSE");
              success = true;
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
                              CEvaluationNode * & pTrueExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  CEvaluationNode * pLeftTrueExpression = NULL;

  success &= compile(pLeft, pLeftTrueExpression);

  CEvaluationNode * pRightTrueExpression = NULL;

  success &= compile(pRight, pRightTrueExpression);

  pTrueExpression = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
  pTrueExpression->addChild(pLeftTrueExpression);
  pTrueExpression->addChild(pRightTrueExpression);

  return success;
}

bool CMathTrigger::compileOR(const CEvaluationNode * pSource,
                             CEvaluationNode * & pTrueExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  CEvaluationNode * pLeftTrueExpression = NULL;

  success &= compile(pLeft, pLeftTrueExpression);

  CEvaluationNode * pRightTrueExpression = NULL;

  success &= compile(pRight, pRightTrueExpression);

  pTrueExpression = new CEvaluationNodeLogical(CEvaluationNodeLogical::OR, "OR");
  pTrueExpression->addChild(pLeftTrueExpression);
  pTrueExpression->addChild(pRightTrueExpression);

  return success;
}

bool CMathTrigger::compileXOR(const CEvaluationNode * pSource,
                              CEvaluationNode * & pTrueExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  CEvaluationNode * pLeftTrueExpression = NULL;

  success &= compile(pLeft, pLeftTrueExpression);

  CEvaluationNode * pRightTrueExpression = NULL;

  success &= compile(pRight, pRightTrueExpression);

  pTrueExpression = new CEvaluationNodeLogical(CEvaluationNodeLogical::XOR, "XOR");
  pTrueExpression->addChild(pLeftTrueExpression);
  pTrueExpression->addChild(pRightTrueExpression);

  return success;
}

bool CMathTrigger::compileEQ(const CEvaluationNode * pSource,
                             CEvaluationNode * & pTrueExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  // Equality can be determined between Boolean and double values.
  if (CEvaluationNode::type(pLeft->getType()) != CEvaluationNode::LOGICAL)
    {
      // We treat x EQ y as (x GE y) AND (y GE x)

      // Create a temporary expression and compile it.
      CEvaluationNode * pAND = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
      CEvaluationNode * pGE = new CEvaluationNodeLogical(CEvaluationNodeLogical::GE, "GE");
      pGE->addChild(copyBranch(pLeft));
      pGE->addChild(copyBranch(pRight));
      pAND->addChild(pGE);

      pGE = new CEvaluationNodeLogical(CEvaluationNodeLogical::GE, "GE");
      pGE->addChild(copyBranch(pRight));
      pGE->addChild(copyBranch(pLeft));
      pAND->addChild(pGE);

      success &= compileAND(pAND, pTrueExpression);

      // Delete the temporary
      pdelete(pAND);
    }
  else
    {
      CEvaluationNode * pLeftTrueExpression = NULL;

      success &= compile(pLeft, pLeftTrueExpression);

      CEvaluationNode * pRightTrueExpression = NULL;

      success &= compile(pRight, pRightTrueExpression);

      pTrueExpression = new CEvaluationNodeLogical(CEvaluationNodeLogical::EQ, "EQ");
      pTrueExpression->addChild(pLeftTrueExpression);
      pTrueExpression->addChild(pRightTrueExpression);
    }

  return success;
}

bool CMathTrigger::compileNE(const CEvaluationNode * pSource,
                             CEvaluationNode * & pTrueExpression)
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

  success &= compileNOT(pNotNode, pTrueExpression);

  // Delete the temporary
  delete pNotNode;

  return success;
}

bool CMathTrigger::compileLE(const CEvaluationNode * pSource,
                             CEvaluationNode * & pTrueExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  CEvaluationNode * pNode;

  // We need to create a root finding structures
  pNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
  pNode->addChild(copyBranch(pRight));
  pNode->addChild(copyBranch(pLeft));

  CRootFinder * pRootFinder = new CRootFinder();
  pRootFinder->mRoot.setRoot(pNode);
  pRootFinder->mEquality = true;
  mRootFinders.add(pRootFinder, true);

  pTrueExpression = pRootFinder->getTrueExpression();

  return success;
}

bool CMathTrigger::compileLT(const CEvaluationNode * pSource,
                             CEvaluationNode * & pTrueExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  CEvaluationNode * pNode;

  // We need to create a root finding structures
  pNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
  pNode->addChild(copyBranch(pRight));
  pNode->addChild(copyBranch(pLeft));

  CRootFinder * pRootFinder = new CRootFinder();
  pRootFinder->mRoot.setRoot(pNode);
  pRootFinder->mEquality = false;
  mRootFinders.add(pRootFinder, true);

  pTrueExpression = pRootFinder->getTrueExpression();

  return success;
}

bool CMathTrigger::compileGE(const CEvaluationNode * pSource,
                             CEvaluationNode * & pTrueExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  CEvaluationNode * pNode;

  // We need to create a root finding structures
  pNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
  pNode->addChild(copyBranch(pLeft));
  pNode->addChild(copyBranch(pRight));

  CRootFinder * pRootFinder = new CRootFinder();
  pRootFinder->mRoot.setRoot(pNode);
  pRootFinder->mEquality = true;
  mRootFinders.add(pRootFinder, true);

  pTrueExpression = pRootFinder->getTrueExpression();

  return success;
}

bool CMathTrigger::compileGT(const CEvaluationNode * pSource,
                             CEvaluationNode * & pTrueExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  CEvaluationNode * pNode;

  // We need to create a root finding structures
  pNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
  pNode->addChild(copyBranch(pLeft));
  pNode->addChild(copyBranch(pRight));

  CRootFinder * pRootFinder = new CRootFinder();
  pRootFinder->mRoot.setRoot(pNode);
  pRootFinder->mEquality = false;
  mRootFinders.add(pRootFinder, true);

  pTrueExpression = pRootFinder->getTrueExpression();

  return success;
}

bool CMathTrigger::compileNOT(const CEvaluationNode * pSource,
                              CEvaluationNode * & pTrueExpression)
{
  bool success = true;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pSource->getChild());

  CEvaluationNode * pLeftTrueExpression = NULL;

  success &= compile(pLeft, pLeftTrueExpression);

  pTrueExpression = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
  pTrueExpression->addChild(pLeftTrueExpression);

  return success;
}

bool CMathTrigger::compileFUNCTION(const CEvaluationNode * pSource,
                                   CEvaluationNode * & pTrueExpression)
{
  if (!pSource->isBoolean())
    return false;

  const CEvaluationNodeCall * pSrc =
    static_cast< const CEvaluationNodeCall * >(pSource);

  std::vector< const CEvaluationNode * > Variables;

  const CEvaluationNode * pChild =
    static_cast< const CEvaluationNode * >(pSrc->getChild());

  while (pChild != NULL)
    {
      Variables.push_back(pChild);
      pChild = static_cast< const CEvaluationNode * >(pChild->getSibling());
    }

  mFunctionVariableMap.push(Variables);

  const CEvaluationNode * pNode = pSrc->getCalledTree()->getRoot();

  bool success = compile(pNode, pTrueExpression);

  mFunctionVariableMap.pop();

  return success;
}

bool CMathTrigger::compileEXPRESSION(const CEvaluationNode * pSource,
                                     CEvaluationNode * & pTrueExpression)
{
  if (!pSource->isBoolean())
    return false;

  const CEvaluationNode * pNode =
    static_cast< const CEvaluationNodeCall * >(pSource)->getCalledTree()->getRoot();

  return compile(pNode, pTrueExpression);
}

bool CMathTrigger::compileVARIABLE(const CEvaluationNode * pSource,
                                   CEvaluationNode * & pTrueExpression)
{
  assert(!mFunctionVariableMap.empty());

  size_t Index =
    static_cast< const CEvaluationNodeVariable * >(pSource)->getIndex();

  const CEvaluationNode * pNode = mFunctionVariableMap.top()[Index];

  if (!pNode->isBoolean())
    return false;

  return compile(pNode, pTrueExpression);
}

CEvaluationNode * CMathTrigger::copyBranch(const CEvaluationNode * pSource)
{
  if (pSource->getType() == CEvaluationNode::VARIABLE)
    {
      if (!mFunctionVariableMap.empty())
        {
          size_t Index = static_cast< const CEvaluationNodeVariable * >(pSource)->getIndex();

          if (Index != C_INVALID_INDEX &&
              Index < mFunctionVariableMap.top().size())
            {
              return mFunctionVariableMap.top()[Index]->copyBranch();
            }
        }

      // We have an invalid variables and therefore create an constant node with the
      // variable name and value NaN.
      return new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, pSource->getData());
    }

  return pSource->copyBranch();
}
