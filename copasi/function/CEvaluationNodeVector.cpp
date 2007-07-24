// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeVector.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/07/24 18:40:21 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "mathematics.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeVector::CEvaluationNodeVector():
    CEvaluationNode((Type) (CEvaluationNode::VECTOR), ""),
    mVector()
{mPrecedence = PRECEDENCE_FUNCTION;}

CEvaluationNodeVector::CEvaluationNodeVector(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::VECTOR | subType), data),
    mVector()
{
  switch (subType)
    {
    case VECTOR:
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

const C_FLOAT64 & CEvaluationNodeVector::value() const
  {
    std::vector< CEvaluationNode * >::const_iterator it = mVector.begin();
    std::vector< CEvaluationNode * >::const_iterator end = mVector.end();

    for (; it != end; ++it)
      (*it)->value();

    return mValue;
  }

std::string CEvaluationNodeVector::getInfix() const
  {
    std::string Infix = "{";

    std::vector< CEvaluationNode * >::const_iterator it = mVector.begin();
    std::vector< CEvaluationNode * >::const_iterator end = mVector.end();

    if (it != end) Infix += (*it++)->getInfix();

    for (; it != end; ++it)
      Infix += "," + (*it)->getInfix();

    return Infix + "}";
  }

std::string CEvaluationNodeVector::getDisplayString(const CEvaluationTree * pTree) const
  {
    std::string DisplayString = "{";

    std::vector< CEvaluationNode * >::const_iterator it = mVector.begin();
    std::vector< CEvaluationNode * >::const_iterator end = mVector.end();

    if (it != end) DisplayString += (*it++)->getDisplayString(pTree);

    for (; it != end; ++it)
      DisplayString += "," + (*it)->getDisplayString(pTree);

    return DisplayString + "}";
  }

std::string CEvaluationNodeVector::getDisplay_C_String(const CEvaluationTree * /* pTree */) const
  {
    return "@";
  }

std::string CEvaluationNodeVector::getDisplay_MMD_String(const CEvaluationTree * /* pTree */) const
  {
    return "@";
  }

std::string CEvaluationNodeVector::getDisplay_XPP_String(const CEvaluationTree * /* pTree */) const
  {
    return "@";
  }

CEvaluationNode* CEvaluationNodeVector::createNodeFromASTTree(const ASTNode & /* node */)
{
  // :TODO:
  SubType subType;
  std::string data = "";

  CEvaluationNodeVector* convertedNode = new CEvaluationNodeVector(subType, data);
  return convertedNode;
}

ASTNode* CEvaluationNodeVector::toAST() const
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
