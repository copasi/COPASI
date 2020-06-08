// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

CEvaluationNodeVector::CEvaluationNodeVector():
  CEvaluationNode(MainType::VECTOR, SubType::INVALID, ""),
  mNodes(),
  mValues()
{mPrecedence = PRECEDENCE_FUNCTION;}

CEvaluationNodeVector::CEvaluationNodeVector(const SubType & subType,
    const Data & data):
  CEvaluationNode(MainType::VECTOR, subType, data),
  mNodes(),
  mValues()
{
  switch (subType)
    {
      case SubType::VECTOR:
        break;

      default:
        fatalError();
        break;
    }

  mPrecedence = PRECEDENCE_FUNCTION;
}

CEvaluationNodeVector::CEvaluationNodeVector(const CEvaluationNodeVector & src):
  CEvaluationNode(src),
  mNodes(src.mNodes),
  mValues(src.mValues)
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

// virtual
CValidatedUnit CEvaluationNodeVector::getUnit(const CMathContainer & /* container */,
    const std::vector< CValidatedUnit > & units) const
{
  CValidatedUnit Unit(CBaseUnit::undefined, false);

  std::vector< CValidatedUnit >::const_iterator it = units.begin();
  std::vector< CValidatedUnit >::const_iterator end = units.end();

  for (; it != end; ++it)
    {
      Unit = CValidatedUnit::merge(Unit, *it);
    }

  if (mNodes.size() != units.size())
    {
      Unit.setConflict(true);
    }

  return Unit;
}

// virtual
CValidatedUnit CEvaluationNodeVector::setUnit(const CMathContainer & container,
    const std::map < CEvaluationNode * , CValidatedUnit > & currentUnits,
    std::map < CEvaluationNode * , CValidatedUnit > & targetUnits) const
{
  CValidatedUnit Result(CEvaluationNode::setUnit(container, currentUnits, targetUnits));

  std::vector< CEvaluationNode * >::const_iterator it = mNodes.begin();
  std::vector< CEvaluationNode * >::const_iterator end = mNodes.end();

  for (; it != end; ++it)
    {
      targetUnits[*it] = Result;
    }

  return Result;
}

// static
CEvaluationNode * CEvaluationNodeVector::fromAST(const ASTNode * /* pASTNode */, const std::vector< CEvaluationNode * > & /* children */)
{
  return NULL;
}

ASTNode* CEvaluationNodeVector::toAST(const CDataModel* /*pDataModel*/) const
{
  // :TODO:
  ASTNode* node = new ASTNode(AST_FUNCTION_PIECEWISE);
  return node;
}

bool CEvaluationNodeVector::addChild(CCopasiNode< Data > * pChild,
                                     CCopasiNode< Data > * pAfter)
{
  CCopasiNode< Data >::addChild(pChild, pAfter);
  mNodes.push_back(static_cast<CEvaluationNode *>(pChild));

  return true;
}

const std::vector< CEvaluationNode * > & CEvaluationNodeVector::getNodes() const
{return mNodes;}
