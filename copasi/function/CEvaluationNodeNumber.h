// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_CEvaluationNodeNumber
#define COPASI_CEvaluationNodeNumber

class CCopasiDataModel;

/**
 * This is class for nodes presenting numbers used in an evaluation trees
 */
class CEvaluationNodeNumber : public CEvaluationNode
{
public:
  /**
   * Enumeration of possible node types.
   */
  enum SubType
  {
    INVALID = 0x00FFFFFF,
    DOUBLE = 0x00000000,
    INTEGER = 0x00000001,
    ENOTATION = 0x00000002,
    RATIONALE = 0x00000003
  };

  // Operations
private:
  /**
   * Default constructor
   */
  CEvaluationNodeNumber();

public:
  /**
   * Specific constructor
   * @param const SubType & subType
   * @param const Data & data
   */
  CEvaluationNodeNumber(const SubType & subType,
                        const Data & data);

  /**
   * Specific constructor
   * @param const C_FLOAT64 & number
   */
  CEvaluationNodeNumber(const C_FLOAT64 & number);

  /**
   * Copy constructor
   * @param const CEvaluationNodeNumber & src
   */
  CEvaluationNodeNumber(const CEvaluationNodeNumber & src);

  /**
   * Destructor
   */
  virtual ~CEvaluationNodeNumber();

  /**
   * Creates a new CEvaluationNodeCall from an ASTNode and the given children
   * @param const ASTNode* pNode
   * @param const std::vector< CEvaluationNode * > & children
   * @return CEvaluationNode * pCretedNode
   */
  static CEvaluationNode * fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children);

  /**
   * Create a new ASTNode corresponding to this NumberNode.
   * @return ASTNode* return a pointer to the newly created node;
   */
  ASTNode* toAST(const CCopasiDataModel* pDataModel) const;

  /**
   * Build the MathML string
   * @param const std::vector< std::string > & children
   * @param bool expand = true
   * @param const std::vector< std::vector< std::string > > & variables
   * @return std::string MMLString
   */
  virtual std::string getMMLString(const std::vector< std::string > & children,
                                   bool expand,
                                   const std::vector< std::vector< std::string > > & variables) const;

  /**
   * Retrieve the display string of the node and its eventual child nodes in C.
   * @return string representing a double value
   */
  virtual std::string getCCodeString(const std::vector< std::string > & children) const;
};

#endif // COPASI_CEvaluationNodeNumber
