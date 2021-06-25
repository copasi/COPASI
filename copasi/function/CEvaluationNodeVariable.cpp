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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi/copasi.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "copasi/utilities/CValidatedUnit.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeVariable::CEvaluationNodeVariable()
  : CEvaluationNode(MainType::VARIABLE, SubType::INVALID, "")
  , mIndex(C_INVALID_INDEX)
{
  mPrecedence = PRECEDENCE_NUMBER;
}

CEvaluationNodeVariable::CEvaluationNodeVariable(const SubType & subType,
    const Data & data)
  : CEvaluationNode(MainType::VARIABLE, subType, data)
  , mIndex(C_INVALID_INDEX)
{
  mPrecedence = PRECEDENCE_NUMBER;
}

CEvaluationNodeVariable::CEvaluationNodeVariable(const CEvaluationNodeVariable & src):
  CEvaluationNode(src),
  mIndex(src.mIndex)
{}

CEvaluationNodeVariable::~CEvaluationNodeVariable() {}

CIssue CEvaluationNodeVariable::compile()
{
  mpTree = getTree();

  if (!mpTree) return CIssue(CIssue::eSeverity::Error, CIssue::eKind::StructureInvalid);

  mIndex = mpTree->getVariableIndex(mData);

  if (mIndex == C_INVALID_INDEX)
    return CIssue(CIssue::eSeverity::Error, CIssue::eKind::VariableNotfound);

  if (getChild() == NULL) // We must not have any children.
    return CIssue::Success;
  else
    return CIssue(CIssue::eSeverity::Error, CIssue::eKind::TooManyArguments);
}

void CEvaluationNodeVariable::calculate()
{
  mValue = mpTree->getVariableValue(mIndex);
}

// virtual
CIssue CEvaluationNodeVariable::setValueType(const ValueType & valueType)
{
  if (mValueType == ValueType::Unknown)
    {
      mValueType = valueType;
    }

  return CEvaluationNode::setValueType(valueType);
}

size_t CEvaluationNodeVariable::getIndex() const
{return mIndex;}

// static
CEvaluationNode * CEvaluationNodeVariable::fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children)
{
  assert(pASTNode->getNumChildren() == children.size());

  return new CEvaluationNodeVariable(SubType::DEFAULT, pASTNode->getName());
}

// virtual
CValidatedUnit CEvaluationNodeVariable::getUnit(const CMathContainer & /* container */,
    const std::vector< CValidatedUnit > & units) const
{
  if (mIndex < units.size())
    {
      return units[mIndex];
    }

  return CValidatedUnit();
}

ASTNode* CEvaluationNodeVariable::toAST(const CDataModel* /*pDataModel*/) const
{
  ASTNode* node = new ASTNode();
  node->setType(AST_NAME);
  node->setName(this->getData().c_str());
  return node;
}

#include "copasi/utilities/copasimathml.h"

// virtual
std::string CEvaluationNodeVariable::getMMLString(const std::vector< std::string > & /* children */,
    bool /* expand */,
    const std::vector< std::vector< std::string > > & variables) const
{
  std::ostringstream out;

  if (mIndex < variables.size())
    {
      out << variables[mIndex][0] << std::endl;
    }
  else
    {
      out << "<mi>" << CMathMl::fixName(mData) << "</mi>" << std::endl;
    }

  return out.str();
}
