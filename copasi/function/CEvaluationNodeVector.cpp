// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeVector.cpp,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/15 18:32:57 $
// End CVS Header

// Copyright (C) 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CEvaluationNode.h"
#include "CEvaluationTree.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeVector::CEvaluationNodeVector():
    CEvaluationNode((Type)(CEvaluationNode::VECTOR), ""),
    mVector()
{mPrecedence = PRECEDENCE_FUNCTION;}

CEvaluationNodeVector::CEvaluationNodeVector(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type)(CEvaluationNode::VECTOR | subType), data),
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

std::string CEvaluationNodeVector::getDisplay_MMD_String(const CEvaluationTree * /* pTree */) const
{
  return "@";
}

std::string CEvaluationNodeVector::getDisplay_XPP_String(const CEvaluationTree * /* pTree */) const
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
