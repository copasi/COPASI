// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CEvaluationNodeUnit
#define COPASI_CEvaluationNodeUnit

#include <iostream>
#include <vector>
#include <map>

#include "copasi/copasi.h"
#include "copasi/utilities/CCopasiNode.h"
#include "CFunctionAnalyzer.h"

class CMathContainer;
class CValidatedUnit;

class CEvaluationTree;
LIBSBML_CPP_NAMESPACE_BEGIN
class ASTNode;
LIBSBML_CPP_NAMESPACE_END
class ConverterASTNode;
class CDataModel;

/**
 * This is the base class for nodes used in an evaluation trees
 */
class CEvaluationNodeUnit : public CEvaluationNode
{
private:
  /**
   * Default constructor
   */
  CEvaluationNodeUnit();

public:
  /**
   * Specific constructor
   * @param const SubType & subType
   * @param const Data & data
   */
  CEvaluationNodeUnit(const SubType & subType,
                      const Data & data);

  /**
   * Copy constructor
   * @param const CEvaluationNodeUnit & src
   */
  CEvaluationNodeUnit(const CEvaluationNodeUnit & src);

  /**
   * Destructor
   */
  virtual ~CEvaluationNodeUnit();

  /**
   * Retrieve the display string of the node and its eventual child nodes in C.
   * @return std::string CCodeString
   */
  std::string getCCodeString(const std::vector< std::string > & children) const override;

  /**
   * Retrieve the display string of the node and its eventual child nodes
   * in Berkeley Madonna format.
   * @return std::string BerkeleyMadonnaString
   */
  std::string getBerkeleyMadonnaString(const std::vector< std::string > & children) const override;

  /**
   * Retrieve the display string of the node and its eventual child nodes
   * in XPPAUT format.
   * @return std::string XPPString
   */
  std::string getXPPString(const std::vector< std::string > & children) const override;

  /**
   * Create a new invalid ASTNode.
   * @return ASTNode* return a pointer to the newly created node;
   */
  ASTNode * toAST(const CDataModel * pDataModel, int sbmlLevel = 3, int sbmlVersion = 1) const override;

  /**
   * Build the MathML string
   * @param const std::vector< std::string > & children
   * @param bool expand = true
   * @param const std::vector< std::vector< std::string > > & variables
   * @return std::string MMLString
   */
  std::string getMMLString(const std::vector< std::string > & children,
                           bool expand,
                           const std::vector< std::vector< std::string > > & variables) const override;

  /**
   * Figure out the appropriate CUnit to use, based on the child nodes.
   * This sets the default, appropriate for many cases, as Dimensionless
   * @param const CMathContainer & container
   * @param const std::vector< CValidatedUnit > & units
   * @return CUnit unit
   */
  CValidatedUnit getUnit(const CMathContainer & container,
                         const std::vector< CValidatedUnit > & units) const override;
};

#endif // COPASI_CEvaluationNode
