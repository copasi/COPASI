/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeWhiteSpace.cpp,v $
  $Revision: 1.5 $
  $Name:  $
  $Author: gauges $
  $Date: 2009/02/19 15:38:50 $
  End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"
#include "CEvaluationNode.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeWhiteSpace::CEvaluationNodeWhiteSpace():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{}

CEvaluationNodeWhiteSpace::CEvaluationNodeWhiteSpace(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::WHITESPACE | subType), data)
{}

CEvaluationNodeWhiteSpace::CEvaluationNodeWhiteSpace(const CEvaluationNodeWhiteSpace & src):
    CEvaluationNode(src)
{}

CEvaluationNodeWhiteSpace::~CEvaluationNodeWhiteSpace() {}

ASTNode* CEvaluationNodeWhiteSpace::toAST(const CCopasiDataModel* /*pDataModel*/) const
  {
    fatalError();
    return NULL;
  }
