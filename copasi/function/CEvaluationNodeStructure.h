// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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

#ifndef COPASI_CEvaluationNodeStructure
#define COPASI_CEvaluationNodeStructure

#include "copasi/copasi.h"
LIBSBML_CPP_NAMESPACE_BEGIN
class ASTNode;
LIBSBML_CPP_NAMESPACE_END
class CDataModel;

/**
 * This is class for nodes presenting numbers used in an evaluation trees
 */
class CEvaluationNodeStructure : public CEvaluationNode
{
  // Operations
private:
  /**
   * Default constructor
   */
  CEvaluationNodeStructure();

public:
  /**
   * Default constructor
   * @param const SubType & subType
   * @param const Data & data
   */
  CEvaluationNodeStructure(const SubType & subType,
                           const Data & data);

  /**
   * Copy constructor
   * @param const CEvaluationNodeStructure & src
   */
  CEvaluationNodeStructure(const CEvaluationNodeStructure & src);

  /**
   * Destructor
   */
  virtual ~CEvaluationNodeStructure();

  /**
   * Create a new ASTNode corresponding to this structure node.
   * @return ASTNode* return a pointer to the newly created node;
   */
  virtual ASTNode * toAST(const CDataModel * pDataModel, int sbmlLevel = 3, int sbmlVersion = 1) const;
};

#endif // COPASI_CEvaluationNodeStructure
