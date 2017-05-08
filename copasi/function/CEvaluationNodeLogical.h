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

#ifndef COPASI_CEvaluationNodeLogical
#define COPASI_CEvaluationNodeLogical

#include "copasi.h"
LIBSBML_CPP_NAMESPACE_BEGIN
class ASTNode;
LIBSBML_CPP_NAMESPACE_END

class CCopasiDataModel;

/**
 * This is the class for nodes presenting opertors used in an evaluation trees.
 */
class CEvaluationNodeLogical : public CEvaluationNode
{
  // Operations
private:
  /**
   * Default constructor
   */
  CEvaluationNodeLogical();

public:
  /**
   * Default constructor
   * @param const SubType & subType
   * @param const Data & data
   */
  CEvaluationNodeLogical(const SubType & subType,
                         const Data & data);

  /**
   * Copy constructor
   * @param const CEvaluationNodeLogical & src
   */
  CEvaluationNodeLogical(const CEvaluationNodeLogical & src);

  /**
   * Destructor
   */
  virtual ~CEvaluationNodeLogical();

  /**
   * Calculate the numerical result of the node. It is assumed that
   * all child nodes are up to date.
   */
  virtual inline void calculate()
  {
    switch (mSubType)
      {
        case S_OR:
          mValue = (*mpLeftValue > 0.5 ||
                    *mpRightValue > 0.5) ? 1.0 : 0.0;
          break;

        case S_XOR:
          mValue = ((*mpLeftValue > 0.5 && *mpRightValue < 0.5) ||
                    (*mpLeftValue < 0.5 && *mpRightValue > 0.5)) ? 1.0 : 0.0;
          break;

        case S_AND:
          mValue = (*mpLeftValue > 0.5 &&
                    *mpRightValue > 0.5) ? 1.0 : 0.0;
          break;

        case S_EQ:
          mValue = (*mpLeftValue == *mpRightValue) ? 1.0 : 0.0;
          break;

        case S_NE:
          mValue = (*mpLeftValue != *mpRightValue) ? 1.0 : 0.0;
          break;

        case S_GT:
          mValue = (*mpLeftValue > *mpRightValue) ? 1.0 : 0.0;
          break;

        case S_GE:
          mValue = (*mpLeftValue >= *mpRightValue) ? 1.0 : 0.0;
          break;

        case S_LT:
          mValue = (*mpLeftValue < *mpRightValue) ? 1.0 : 0.0;
          break;

        case S_LE:
          mValue = (*mpLeftValue <= *mpRightValue) ? 1.0 : 0.0;
          break;
      }
  }

  /**
   * Compile a node;
   * @param const CFunction * pFunction
   * @return bool success;
   */
  virtual bool compile(const CEvaluationTree * pTree);

  /**
   * Retrieve the infix value of the node and its eventual child nodes.
   * @return const Data & value
   */
  virtual std::string getInfix(const std::vector< std::string > & children) const;

  /**
   * Retrieve the display string of the node and its eventual child nodes.
   * @return const Data & value
   */
  virtual std::string getDisplayString(const std::vector< std::string > & children) const;

  /**
   * Retrieve the disclass ASTNode;play string of the node and its eventual child nodes in C.
   * @return const Data & value
   */
  virtual std::string getCCodeString(const std::vector< std::string > & children) const;

  /**
   * Retrieve the display string of the node and its eventual child nodes
   * in Berkeley Madonna format.
   * @return const Data & value
   */
  virtual std::string getBerkeleyMadonnaString(const std::vector< std::string > & children) const;

  /**
   * Retrieve the display string of the node and its eventual child nodes
   * in XPPAUT format.
   * @return const Data & value
   */
  virtual std::string getXPPString(const std::vector< std::string > & children) const;

  /**
   * Creates a new CEvaluationNodeCall from an ASTNode and the given children
   * @param const ASTNode* pNode
   * @param const std::vector< CEvaluationNode * > & children
   * @return CEvaluationNode * pCretedNode
   */
  static CEvaluationNode * fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children);

  /**
   * Create a new ASTNode corresponding to this OperatorNode.
   * @return ASTNode* return a pointer to the newly created node;
   */
  virtual ASTNode* toAST(const CCopasiDataModel* pDataModel) const;

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

  // Attributes
private:
  // Attributes
private:
  CEvaluationNode * mpLeftNode;
  CEvaluationNode * mpRightNode;

  const C_FLOAT64 * mpLeftValue;
  const C_FLOAT64 * mpRightValue;
};

#endif // COPASI_CEvaluationNodeLogical
