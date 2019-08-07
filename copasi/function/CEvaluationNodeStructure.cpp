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

#include <limits.h>

#include "copasi/copasi.h"
#include "CEvaluationNode.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeStructure::CEvaluationNodeStructure():
  CEvaluationNode(MainType::STRUCTURE, SubType::INVALID, "")
{}

CEvaluationNodeStructure::CEvaluationNodeStructure(const SubType & subType,
    const Data & data):
  CEvaluationNode(MainType::STRUCTURE, subType, data)
{
  switch (subType)
    {
      case SubType::OPEN:
      case SubType::VECTOROPEN:
        mPrecedence = PRECEDENCE_STRUCTURE_OPEN;
        break;

      case SubType::COMMA:
        mPrecedence = PRECEDENCE_STRUCTURE_COMMA;
        break;

      case SubType::CLOSE:
      case SubType::VECTORCLOSE:
        mPrecedence = PRECEDENCE_STRUCTURE_CLOSE;
        break;

      case SubType::INVALID:
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
