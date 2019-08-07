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

#ifndef COPASI_CEvaluationNodeConstant
#define COPASI_CEvaluationNodeConstant

#include "copasi/copasi.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class ASTNode;
LIBSBML_CPP_NAMESPACE_END

class CDataModel;

/**
 * This is class for nodes presenting Constants used in an evaluation trees
 */
class CEvaluationNodeConstant : public CEvaluationNode
{
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
  virtual std::string getXPPString(const std::vector< std::string > & children) const;

  /**
   * Creates a new CEvaluationNodeCall from an ASTNode and the given children
   * @param const ASTNode* pNode
   * @param const std::vector< CEvaluationNode * > & children
   * @return CEvaluationNode * pCretedNode
   */
  static CEvaluationNode * fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children);

  /**
   * Create a new ASTNode corresponding to this ConstantNode.
   * @return ASTNode* return a pointer to the newly created node;
   */
  virtual ASTNode* toAST(const CDataModel* pDataModel) const;

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
};

#endif // COPASI_CEvaluationNodeConstant
