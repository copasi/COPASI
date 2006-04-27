/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeStructure.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:28:26 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"
#include "CEvaluationNode.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeStructure::CEvaluationNodeStructure():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{}

CEvaluationNodeStructure::CEvaluationNodeStructure(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::STRUCTURE | subType), data)
{
  switch (subType)
    {
    case OPEN:
    case VECTOR_OPEN:
      mPrecedence = PRECEDENCE_STRUCTURE_OPEN;
      break;

    case COMMA:
      mPrecedence = PRECEDENCE_STRUCTURE_COMMA;
      break;

    case CLOSE:
    case VECTOR_CLOSE:
      mPrecedence = PRECEDENCE_STRUCTURE_CLOSE;
      break;

    case INVALID:
      fatalError();
      break;
    }
}

CEvaluationNodeStructure::CEvaluationNodeStructure(const CEvaluationNodeStructure & src):
    CEvaluationNode(src)
{}

CEvaluationNodeStructure::~CEvaluationNodeStructure() {}

ASTNode* CEvaluationNodeStructure::toAST() const
  {
    fatalError();
    return NULL;
  }
