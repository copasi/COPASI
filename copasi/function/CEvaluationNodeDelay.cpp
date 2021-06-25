// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sbml/math/ASTNode.h>

#include "copasi/copasi.h"

#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/utilities/utility.h"
#include "copasi/utilities/CValidatedUnit.h"
#include "copasi/core/CRootContainer.h"

CEvaluationNodeDelay::CEvaluationNodeDelay():
  CEvaluationNode(MainType::DELAY, SubType::INVALID, ""),
  mpDelayValueNode(NULL),
  mpDelayLagNode(NULL),
  mpDelayValueValue(NULL),
  mpDelayLagValue(NULL)
{
  mPrecedence = PRECEDENCE_NUMBER;
  mValueType = ValueType::Number;
}

CEvaluationNodeDelay::CEvaluationNodeDelay(const SubType & subType,
    const Data & /* data */):
  CEvaluationNode(MainType::DELAY, subType, "delay"),
  mpDelayValueNode(NULL),
  mpDelayLagNode(NULL),
  mpDelayValueValue(NULL),
  mpDelayLagValue(NULL)
{
  mPrecedence = PRECEDENCE_NUMBER;
  mValueType = ValueType::Number;

  switch (subType)
    {
      case SubType::DELAY:
        mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
        break;

      default:
        fatalError();
        break;
    }
}

CEvaluationNodeDelay::CEvaluationNodeDelay(const CEvaluationNodeDelay & src):
  CEvaluationNode(src),
  mpDelayValueNode(src.mpDelayValueNode),
  mpDelayLagNode(src.mpDelayLagNode),
  mpDelayValueValue(src.mpDelayValueValue),
  mpDelayLagValue(src.mpDelayLagValue)
{}

CEvaluationNodeDelay::~CEvaluationNodeDelay() {}

CIssue CEvaluationNodeDelay::compile()
{
  switch (mSubType)
    {
      case SubType::DELAY:
        mpDelayValueNode = static_cast<CEvaluationNode *>(getChild());

        if (mpDelayValueNode == NULL) return CIssue(CIssue::eSeverity::Error, CIssue::eKind::StructureInvalid);;

        mpDelayValueValue = mpDelayValueNode->getValuePointer();

        mpDelayLagNode = static_cast<CEvaluationNode *>(mpDelayValueNode->getSibling());

        if (mpDelayLagNode == NULL) return CIssue(CIssue::eSeverity::Error, CIssue::eKind::StructureInvalid);

        mpDelayLagValue = mpDelayLagNode->getValuePointer();

        if (mpDelayLagNode->getSibling() == NULL) // We must have exactly 2 children
          return CIssue::Success;
        else
          return CIssue(CIssue::eSeverity::Error, CIssue::eKind::TooManyArguments);

        break;

      default:
        return CIssue(CIssue::eSeverity::Error, CIssue::eKind::StructureInvalid);
        break;
    }

  return CIssue::Success;
}

// virtual
std::string CEvaluationNodeDelay::getInfix(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeDelay*>(this)->compile())
    {
      switch (mSubType)
        {
          case SubType::DELAY:
            return mData + "(" + children[0] + "," + children[1] + ")";
            break;

          default:
            break;
        }
    }

  return "@";
}

// virtual
std::string CEvaluationNodeDelay::getDisplayString(const std::vector< std::string > & children) const
{
  switch (mSubType)
    {
      case SubType::DELAY:
        return mData + "(" + children[0] + "," + children[1] + ")";
        break;

      default:
        break;
    }

  return "@";
}

// virtual
std::string CEvaluationNodeDelay::getCCodeString(const std::vector< std::string > & children) const
{
  switch (mSubType)
    {
      case SubType::DELAY:
        return mData + "(" + children[0] + "," + children[1] + ")";
        break;

      default:
        break;
    }

  return "@";
}

// virtual
std::string CEvaluationNodeDelay::getBerkeleyMadonnaString(const std::vector< std::string > & children) const
{
  switch (mSubType)
    {
      case SubType::DELAY:
        return mData + "(" + children[0] + "," + children[1] + ")";
        break;

      default:
        break;
    }

  return "@";
}

// virtual
std::string CEvaluationNodeDelay::getXPPString(const std::vector< std::string > & children) const
{
  switch (mSubType)
    {
      case SubType::DELAY:
        return mData + "(" + children[0] + "," + children[1] + ")";
        break;

      default:
        break;
    }

  return "@";
}

// virtual
CValidatedUnit CEvaluationNodeDelay::getUnit(const CMathContainer & container,
    const std::vector< CValidatedUnit > & units) const
{
  // The units of the delay functions are the units of the delay value which is the first child
  CValidatedUnit Delay = units[0];
  CValidatedUnit Lag = CValidatedUnit::merge(CValidatedUnit(container.getModel().getTimeUnit(), false), units[1]);

  Delay.setConflict(Delay.conflict() || Lag.conflict());

  return Delay;
}

// virtual
CValidatedUnit CEvaluationNodeDelay::setUnit(const CMathContainer & container,
    const std::map < CEvaluationNode *, CValidatedUnit > & currentUnits,
    std::map < CEvaluationNode *, CValidatedUnit > & targetUnits) const
{
  CValidatedUnit Delay(CEvaluationNode::setUnit(container, currentUnits, targetUnits));

  targetUnits[mpDelayValueNode] = Delay;
  targetUnits[mpDelayLagNode] = CValidatedUnit(container.getModel().getTimeUnit(), false);

  return Delay;
}

// static
CEvaluationNode * CEvaluationNodeDelay::fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children)
{
  assert(pASTNode->getNumChildren() == children.size());

  size_t i = 0, iMax = children.size();

  SubType subType = SubType::DELAY;
  std::string data = "delay";

  CEvaluationNode * pConvertedNode = new CEvaluationNodeDelay(subType, data);

  for (i = 0; i < iMax; ++i)
    {
      pConvertedNode->addChild(children[i]);
    }

  pConvertedNode->compile();
  return pConvertedNode;
}

ASTNode* CEvaluationNodeDelay::toAST(const CDataModel* pDataModel) const
{
  ASTNode* pNode = new ASTNode(AST_FUNCTION_DELAY);
  const CEvaluationNode* child = static_cast<const CEvaluationNode*>(this->getChild());

  while (child)
    {
      pNode->addChild(child->toAST(pDataModel));
      child = static_cast<const CEvaluationNode*>(child->getSibling());
    }

  return pNode;
}

#include "copasi/utilities/copasimathml.h"

// virtual
std::string CEvaluationNodeDelay::getMMLString(const std::vector< std::string > & children,
    bool /* expand */,
    const std::vector< std::vector< std::string > > & /* variables */) const
{
  std::ostringstream out;

  switch (mSubType)
    {
      case SubType::DELAY:
        out << "<mrow>" << std::endl;

        out << "<mi>" << mData << "</mi>" << std::endl;
        out << "<mrow>" << std::endl;
        out << "<mo> (</mo>" << std::endl;
        out << "<mrow>" << std::endl;

        out << children[0];

        out << "<mo> , </mo>" << std::endl;

        out << children[1];

        out << "</mrow>" << std::endl;
        out << "<mo>) </mo>" << std::endl;

        out << "</mrow>" << std::endl;
        out << "</mrow>" << std::endl;
        break;

      default:
        break;
    }

  return out.str();
}
