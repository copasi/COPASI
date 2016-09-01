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
          mValue = (mpLeft->getValue() > 0.5 ||
                    mpRight->getValue() > 0.5) ? 1.0 : 0.0;
          break;

        case S_XOR:
          mValue = ((mpLeft->getValue() > 0.5 && mpRight->getValue() < 0.5) ||
                    (mpLeft->getValue() < 0.5 && mpRight->getValue() > 0.5)) ? 1.0 : 0.0;
          break;

        case S_AND:
          mValue = (mpLeft->getValue() > 0.5 &&
                    mpRight->getValue() > 0.5) ? 1.0 : 0.0;
          break;

        case S_EQ:
          mValue = (mpLeft->getValue() == mpRight->getValue()) ? 1.0 : 0.0;
          break;

        case S_NE:
          mValue = (mpLeft->getValue() != mpRight->getValue()) ? 1.0 : 0.0;
          break;

        case S_GT:
          mValue = (mpLeft->getValue() > mpRight->getValue()) ? 1.0 : 0.0;
          break;

        case S_GE:
          mValue = (mpLeft->getValue() >= mpRight->getValue()) ? 1.0 : 0.0;
          break;

        case S_LT:
          mValue = (mpLeft->getValue() < mpRight->getValue()) ? 1.0 : 0.0;
          break;

        case S_LE:
          mValue = (mpLeft->getValue() <= mpRight->getValue()) ? 1.0 : 0.0;
          break;
      }
  }

  /**
   * Compile a node;
   * @param const CEvaluationTree * pTree
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
   * Figure out the appropriate CUnit to use, based on the child nodes.
   * This sets the default, appropriate for many cases, as Dimensionless
   * @param const CMathContainer & container
   * @param const std::vector< CUnit > & units
   * @return CUnit unit
   */
  virtual CValidatedUnit getUnit(const CMathContainer & container,
                                 const std::vector< CValidatedUnit > & units) const;

  /**
   * Set the unit for the node and return the resulting unit. The child node units are
   * added to the map
   * @param const CMathContainer & container
   * @param const std::map < CEvaluationNode * , CValidatedUnit > & currentUnits
   * @param std::map < CEvaluationNode * , CValidatedUnit > & targetUnits
   * @return CUnit unit
   */
  virtual CValidatedUnit setUnit(const CMathContainer & container,
                                 const std::map < CEvaluationNode * , CValidatedUnit > & currentUnits,
                                 std::map < CEvaluationNode * , CValidatedUnit > & targetUnits) const;

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
  CEvaluationNode * mpLeft;

  CEvaluationNode * mpRight;
};

#endif // COPASI_CEvaluationNodeLogical
