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

#include "sbml/math/ASTNode.h"

CEvaluationNodeWhiteSpace::CEvaluationNodeWhiteSpace():
  CEvaluationNode(MainType::WHITESPACE, SubType::INVALID, "")
{}

CEvaluationNodeWhiteSpace::CEvaluationNodeWhiteSpace(const SubType & subType,
    const Data & data):
  CEvaluationNode(MainType::WHITESPACE, subType, data)
{}

CEvaluationNodeWhiteSpace::CEvaluationNodeWhiteSpace(const CEvaluationNodeWhiteSpace & src):
  CEvaluationNode(src)
{}

CEvaluationNodeWhiteSpace::~CEvaluationNodeWhiteSpace() {}

ASTNode* CEvaluationNodeWhiteSpace::toAST(const CDataModel* /*pDataModel*/) const
{
  fatalError();
  return NULL;
}
