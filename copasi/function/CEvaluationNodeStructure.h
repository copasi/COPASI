/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeStructure.h,v $
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

#ifndef COPASI_CEvaluationNodeStructure
#define COPASI_CEvaluationNodeStructure

class ASTNode;
class CCopasiDataModel;

/**
 * This is class for nodes presenting numbers used in an evaluation trees
 */
class CEvaluationNodeStructure : public CEvaluationNode
  {
  public:
    /**
     * Enumeration of possible node types.
     */
    enum SubType
    {
      INVALID = 0x00FFFFFF,
      OPEN = 0x00000000,
      VECTOR_OPEN = 0x00000001,
      COMMA = 0x00000002,
      CLOSE = 0x00000003,
      VECTOR_CLOSE = 0x00000004
    };

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
    virtual ASTNode* toAST(const CCopasiDataModel* pDataModel) const;
  };

#endif // COPASI_CEvaluationNodeStructure
