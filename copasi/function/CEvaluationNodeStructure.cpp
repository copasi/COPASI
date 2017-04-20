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

#include <limits.h>

#include "copasi.h"
#include "CEvaluationNode.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeStructure::CEvaluationNodeStructure():
  CEvaluationNode(T_STRUCTURE, S_INVALID, "")
{}

CEvaluationNodeStructure::CEvaluationNodeStructure(const SubType & subType,
    const Data & data):
  CEvaluationNode(T_STRUCTURE, subType, data)
{
  switch (subType)
    {
      case S_OPEN:
      case S_VECTOR_OPEN:
        mPrecedence = PRECEDENCE_STRUCTURE_OPEN;
        break;

      case S_COMMA:
        mPrecedence = PRECEDENCE_STRUCTURE_COMMA;
        break;

      case S_CLOSE:
      case S_VECTOR_CLOSE:
        mPrecedence = PRECEDENCE_STRUCTURE_CLOSE;
        break;

      case S_INVALID:
        fatalError();
        break;
    }
}

CEvaluationNodeStructure::CEvaluationNodeStructure(const CEvaluationNodeStructure & src):
  CEvaluationNode(src)
{}

CEvaluationNodeStructure::~CEvaluationNodeStructure() {}

ASTNode* CEvaluationNodeStructure::toAST(const CDataModel* /*pDataModel*/) const
{
  fatalError();
  return NULL;
}
