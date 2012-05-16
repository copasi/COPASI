/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeConstant.h,v $
  $Revision: 1.26 $
  $Name:  $
  $Author: shoops $
  $Date: 2012/05/16 15:02:45 $
  End CVS Header */

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_CEvaluationNodeConstant
#define COPASI_CEvaluationNodeConstant

class ASTNode;
class CCopasiDataModel;

/**
 * This is class for nodes presenting Constants used in an evaluation trees
 */
class CEvaluationNodeConstant : public CEvaluationNode
{
public:
  /**
   * Enumeration of possible node types.
   */
  enum SubType
  {
    INVALID = 0x00FFFFFF,
    PI = 0x00000000,
    EXPONENTIALE = 0x00000001,

#ifdef TRUE
# undef TRUE
#endif
    TRUE = 0x00000002,

#ifdef FALSE
# undef FALSE
#endif
    FALSE = 0x00000003,

    _INFINITY = 0x00000004,
    _NaN = 0x00000005
  };

  // Operations
private:
  /**
   * Default constructor
   */
  CEvaluationNodeConstant();

public:
  /**
   * Default constructor
   * @param const SubType & subType
   * @param const Data & data
   */
  CEvaluationNodeConstant(const SubType & subType,
                          const Data & data);

  /**
   * Copy constructor
   * @param const CEvaluationNodeConstant & src
   */
  CEvaluationNodeConstant(const CEvaluationNodeConstant & src);

  /**
   * Destructor
   */
  virtual ~CEvaluationNodeConstant();

  /**
   *  Retrieve the display string of the node and its eventual child nodes.
   *  in C format.
   *  @return const Data & value
   * */
  virtual std::string getCCodeString(const std::vector< std::string > & children) const;

  /**
   *  Retrieve the display string of the node and its eventual child nodes.
   *  in Berkeley Madonna format.
   *  @return const Data & value
   * */
  virtual std::string getBerkeleyMadonnaString(const std::vector< std::string > & children) const;

  /**
   **  Retrieve the display string of the node and its eventual child nodes.
   **  in XPPAUT format.
   **  @return const Data & value
   **/
  virtual std::string getDisplay_XPP_String(const CEvaluationTree * pTree) const;

  /**
   * Creates a new CEvaluationNodeCall from an ASTNode and the given children
   * @param const ASTNode* pNode
   * @param const std::vector< CEvaluationNode * > & children
   * @return CEvaluationNode * pCretedNode
   */
  static CEvaluationNode * fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children);

  /**
   * Check whether the result is Boolean
   * @return bool isBoolean
   */
  virtual bool isBoolean() const;

  /**
   * Create a new ASTNode corresponding to this ConstantNode.
   * @return ASTNode* return a pointer to the newly created node;
   */
  virtual ASTNode* toAST(const CCopasiDataModel* pDataModel) const;

  /**
   * generate display MathML recursively
   */
  virtual void writeMathML(std::ostream & out,
                           const std::vector<std::vector<std::string> > & env,
                           bool expand = true,
                           size_t l = 0) const;
};

#endif // COPASI_CEvaluationNodeConstant
