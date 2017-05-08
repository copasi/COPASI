// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"
#include "CEvaluationNode.h"
#include "CFunction.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeVariable::CEvaluationNodeVariable():
  CEvaluationNode(T_VARIABLE, S_INVALID, ""),
  mpTree(NULL),
  mIndex(C_INVALID_INDEX)
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeVariable::CEvaluationNodeVariable(const SubType & subType,
    const Data & data):
  CEvaluationNode(T_VARIABLE, subType, data),
  mpTree(NULL),
  mIndex(C_INVALID_INDEX)
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeVariable::CEvaluationNodeVariable(const CEvaluationNodeVariable & src):
  CEvaluationNode(src),
  mpTree(src.mpTree),
  mIndex(src.mIndex)
{}

CEvaluationNodeVariable::~CEvaluationNodeVariable() {}

bool CEvaluationNodeVariable::compile(const CEvaluationTree * pTree)
{
  mpTree = pTree;

  if (!pTree) return false;

  mIndex = pTree->getVariableIndex(mData);

  if (mIndex == C_INVALID_INDEX) return false;

  return (getChild() == NULL); // We must not have any children.
}

void CEvaluationNodeVariable::calculate()
{
  mValue = mpTree->getVariableValue(mIndex);
}

// virtual
bool CEvaluationNodeVariable::setValueType(const ValueType & valueType)
{
  if (mValueType == Unknown)
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

  return new CEvaluationNodeVariable(S_DEFAULT, pASTNode->getName());
}

ASTNode* CEvaluationNodeVariable::toAST(const CCopasiDataModel* /*pDataModel*/) const
{
  ASTNode* node = new ASTNode();
  node->setType(AST_NAME);
  node->setName(this->getData().c_str());
  return node;
}

#include "utilities/copasimathml.h"

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
