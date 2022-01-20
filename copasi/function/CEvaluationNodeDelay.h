// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

#ifndef COPASI_CEvaluationNodeDelay
#define COPASI_CEvaluationNodeDelay

#include <iostream>
#include <vector>

#include "copasi/copasi.h"
#include "copasi/function/CEvaluationNode.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class ASTNode;
LIBSBML_CPP_NAMESPACE_END

class CDataModel;

/**
 * This is class for nodes representing the (SBML) delay function.
 */
class CEvaluationNodeDelay : public CEvaluationNode
{
  // Operations
private:
  /**
   * Default constructor
   */
  CEvaluationNodeDelay();

public:
  /**
   * constructor
   * @param const SubType & subType
   * @param const Data & data
   */
  CEvaluationNodeDelay(const SubType & subType,
                       const Data & data);

  /**
   * Copy constructor
   * @param const CEvaluationNodeDelay & src
   */
  CEvaluationNodeDelay(const CEvaluationNodeDelay & src);

  /**
   * Destructor
   */
  virtual ~CEvaluationNodeDelay();

  /**
   * Retrieve the display string of the node and its eventual child nodes.
   * @return const Data & value
   */
  virtual std::string getDisplayString(const std::vector< std::string > & children) const override;

  /**
   * Retrieve the display string of the node and its eventual child nodes in C.
   * @return const Data & value
   */
  virtual std::string getCCodeString(const std::vector< std::string > & children) const override;

  /**
   * Retrieve the display string of the node and its eventual child nodes
   * in Berkeley Madonna format.
   * @return const Data & value
   */
  virtual std::string getBerkeleyMadonnaString(const std::vector< std::string > & children) const override;

  /**
   ** Retrieve the display string of the node and its eventual child nodes
   ** in XPPAUT format.
   ** @return const Data & value
   **/
  virtual std::string getXPPString(const std::vector< std::string > & children) const override;

  /**
   * Figure out the appropriate CUnit to use, based on the child nodes.
   * This sets the default, appropriate for many cases, as Dimensionless
   * @param const CMathContainer & container
   * @param const std::vector< CValidatedUnit > & units
   * @return CValidatedUnit unit
   */
  virtual CValidatedUnit getUnit(const CMathContainer & container,
                                 const std::vector< CValidatedUnit > & units) const override;

  /**
   * Set the unit for the node and return the resulting unit. The child node units are
   * added to the map
   * @param const CMathContainer & container
   * @param const std::map < CEvaluationNode * , CValidatedUnit > & currentUnits
   * @param std::map < CEvaluationNode * , CValidatedUnit > & targetUnits
   * @return CValidatedUnit unit
   */
  virtual CValidatedUnit setUnit(const CMathContainer & container,
                                 const std::map < CEvaluationNode *, CValidatedUnit > & currentUnits,
                                 std::map < CEvaluationNode *, CValidatedUnit > & targetUnits) const override;

  /**
   * Creates a new CEvaluationNodeCall from an ASTNode and the given children
   * @param const ASTNode* pNode
   * @param const std::vector< CEvaluationNode * > & children
   * @return CEvaluationNode * pCretedNode
   */
  static CEvaluationNode * fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children);

  /**
   * Create a new ASTNode corresponding to this delay node.
   * @return ASTNode* return a pointer to the newly created node;
   */
  ASTNode* toAST(const CDataModel* pDataModel) const override;

  /**
   * Build the MathML string
   * @param const std::vector< std::string > & children
   * @param bool expand = true
   * @param const std::vector< std::vector< std::string > > & variables
   * @return std::string MMLString
   */
  virtual std::string getMMLString(const std::vector< std::string > & children,
                                   bool expand,
                                   const std::vector< std::vector< std::string > > & variables) const override;

  /**
   * Compile a node;
   * @param const CEvaluationTree * pTree
   * @return CIssue issue;
   */
  virtual CIssue compile() override;

  /**
   * Retrieve the infix value of the node and its eventual child nodes.
   * @return const Data & value
   */
  virtual std::string getInfix(const std::vector< std::string > & children) const override;

private:
  CEvaluationNode * mpDelayValueNode;
  CEvaluationNode * mpDelayLagNode;
  const C_FLOAT64 * mpDelayValueValue;
  const C_FLOAT64 * mpDelayLagValue;
};

#endif // COPASI_CEvaluationNodeDelay
