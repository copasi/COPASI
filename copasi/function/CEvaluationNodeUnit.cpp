// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CEvaluationNode.h"
#include "copasi/utilities/CValidatedUnit.h"

CEvaluationNodeUnit::CEvaluationNodeUnit() :
  CEvaluationNode(MainType::UNIT, SubType::INVALID, "[?]")
{
  mValue = 1.0;
  mPrecedence = PRECEDENCE_NUMBER;
  mValueType = ValueType::Number;
}

CEvaluationNodeUnit::CEvaluationNodeUnit(const SubType & subType,
    const Data & data):
  CEvaluationNode(MainType::UNIT, subType, data)
{
  mValue = 1.0;
  mPrecedence = PRECEDENCE_NUMBER;
  mValueType = ValueType::Number;
}

CEvaluationNodeUnit::CEvaluationNodeUnit(const CEvaluationNodeUnit & src) :
  CEvaluationNode(src)
{}

// virtual
CEvaluationNodeUnit::~CEvaluationNodeUnit()
{}

// virtual
std::string CEvaluationNodeUnit::getCCodeString(const std::vector< std::string > & children) const
{
  return "1.0";
}

/**
 * Retrieve the display string of the node and its eventual child nodes
 * in Berkeley Madonna format.
 * @return std::string BerkeleyMadonnaString
 */
// virtual
std::string CEvaluationNodeUnit::getBerkeleyMadonnaString(const std::vector< std::string > & children) const
{
  return "1.0";
}

/**
 * Retrieve the display string of the node and its eventual child nodes
 * in XPPAUT format.
 * @return std::string XPPString
 */
// virtual
std::string CEvaluationNodeUnit::getXPPString(const std::vector< std::string > & children) const
{
  return "1.0";
}

// virtual
ASTNode* CEvaluationNodeUnit::toAST(const CDataModel* pDataModel) const
{
  // TODO CRITICAL Implement me!
  fatalError();

  return NULL;
}

// virtual
std::string CEvaluationNodeUnit::getMMLString(const std::vector< std::string > & /* children */,
    bool /* expand */,
    const std::vector< std::vector< std::string > > & /* variables */) const
{
  return "<mtext>" + mData + "</mtext>";
}

// virtual
CValidatedUnit CEvaluationNodeUnit::getUnit(const CMathContainer & /* container */,
    const std::vector< CValidatedUnit > & /* units */) const
{
  return CValidatedUnit(mData.substr(1, mData.length() - 2), false);
}
