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
#include "CEvaluationTree.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeVector::CEvaluationNodeVector():
  CEvaluationNode(T_VECTOR, S_INVALID, ""),
  mVector()
{mPrecedence = PRECEDENCE_FUNCTION;}

CEvaluationNodeVector::CEvaluationNodeVector(const SubType & subType,
    const Data & data):
  CEvaluationNode(T_VECTOR, subType, data),
  mVector()
{
  switch (subType)
    {
      case S_VECTOR:
        break;

      default:
        fatalError();
        break;
    }

  mPrecedence = PRECEDENCE_FUNCTION;
}

CEvaluationNodeVector::CEvaluationNodeVector(const CEvaluationNodeVector & src):
  CEvaluationNode(src),
  mVector(src.mVector)
{}

CEvaluationNodeVector::~CEvaluationNodeVector() {}

// virtual
std::string CEvaluationNodeVector::getInfix(const std::vector< std::string > & children) const
{
  std::string Infix = "{";

  std::vector< std::string >::const_iterator it = children.begin();
  std::vector< std::string >::const_iterator end = children.end();

  if (it != end) Infix += *it++;

  for (; it != end; ++it)
    Infix += "," + *it;

  return Infix + "}";
}

// virtual
std::string CEvaluationNodeVector::getDisplayString(const std::vector< std::string > & children) const
{
  std::string DisplayString = "{";

  std::vector< std::string >::const_iterator it = children.begin();
  std::vector< std::string >::const_iterator end = children.end();

  if (it != end) DisplayString += *it++;

  for (; it != end; ++it)
    DisplayString += "," + *it;

  return DisplayString + "}";
}

// virtual
std::string CEvaluationNodeVector::getCCodeString(const std::vector< std::string > & /* children */) const
{
  return "@";
}

// virtual
std::string CEvaluationNodeVector::getBerkeleyMadonnaString(const std::vector< std::string > & /* children */) const
{
  return "@";
}

// virtual
std::string CEvaluationNodeVector::getXPPString(const std::vector< std::string > & /* children */) const
{
  return "@";
}

// static
CEvaluationNode * CEvaluationNodeVector::fromAST(const ASTNode * /* pASTNode */, const std::vector< CEvaluationNode * > & /* children */)
{
  return NULL;
}

ASTNode* CEvaluationNodeVector::toAST(const CCopasiDataModel* /*pDataModel*/) const
{
  // :TODO:
  ASTNode* node = new ASTNode(AST_FUNCTION_PIECEWISE);
  return node;
}

bool CEvaluationNodeVector::addChild(CCopasiNode< Data > * pChild,
                                     CCopasiNode< Data > * pAfter)
{
  CCopasiNode< Data >::addChild(pChild, pAfter);
  mVector.push_back(static_cast<CEvaluationNode *>(pChild));

  return true;
}

const std::vector< CEvaluationNode * > & CEvaluationNodeVector::getVector() const
{return mVector;}
