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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CEvaluationNodeObject
#define COPASI_CEvaluationNodeObject

#include "copasi/core/CRegisteredCommonName.h"

class CRegisteredCommonName;
class CDataModel;

/**
 * This is class for nodes presenting numbers used in an evaluation trees
 */
class CEvaluationNodeObject : public CEvaluationNode
{
  // Operations
private:
  /**
   * Default constructor
   */
  CEvaluationNodeObject();

public:
  /**
   * Default constructor
   * @param const SubType & subType
   * @param const Data & data
   */
  CEvaluationNodeObject(const SubType & subType,
                        const Data & data);

  /**
   * Specific constructor
   * @param const Data & data
   */
  CEvaluationNodeObject(const C_FLOAT64 * pValue);

  /**
   * Specific constructor
   * @param const Data & data
   */
  CEvaluationNodeObject(const bool * pValue);

  /**
   * Copy constructor
   * @param const CEvaluationNodeObject & src
   */
  CEvaluationNodeObject(const CEvaluationNodeObject & src);

  /**
   * Destructor
   */
  virtual ~CEvaluationNodeObject();

  /**
   * Compile a node;
   * @param const CEvaluationTree * pTree
   * @return CIssue issue;
   */
  virtual CIssue compile() override;

  /**
   * Map object whose CN starts with srcSN to children of the target container
   * @param const std::string srcCN
   * @param const CDataContainer * pTarget
   * @return bool success;
   */
  bool mapObject(const std::string srcCN, const CDataContainer * pTarget);

  /**
   * Retrieve the value of the node.
   * @return const Data & value
   */
  virtual const Data & getData() const override;

  /**
   * Set the data of the Node.
   * @param const Data & data
   * @return bool success
   */
  virtual bool setData(const Data & data) override;

  /**
   * Retrieve the infix value of the node and its eventual child nodes.
   * @return const Data & value
   */
  virtual std::string getInfix(const std::vector< std::string > & children) const override;

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
   * Retrieve the display string of the node and its eventual child nodes in
   * Berkeley Madonna format.
   * @return const Data & value
   */
  virtual std::string getBerkeleyMadonnaString(const std::vector< std::string > & children) const override;

  /**
   * Retrieve the display string of the node and its eventual child nodes in
   * XPPAUT format.
   * @return const Data & value
   */
  virtual std::string getXPPString(const std::vector< std::string > & children) const override;

  /**
   * Figure out the appropriate CUnit to use, based on the child nodes.
   * This sets the default, appropriate for many cases, as Dimensionless
   * @param const CMathContainer & container
   * @param const std::vector< CUnit > & units
   * @return CUnit unit
   */
  virtual CValidatedUnit getUnit(const CMathContainer & container,
                                 const std::vector< CValidatedUnit > & units) const override;

  /**
   * Creates a new CEvaluationNodeCall from an ASTNode and the given children
   * @param const ASTNode* pNode
   * @param const std::vector< CEvaluationNode * > & children
   * @return CEvaluationNode * pCretedNode
   */
  static CEvaluationNode * fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children);

  /**
   * Converts this node to an ASTNode.
   * @return ASTNode the resulting ASTNode.
   */
  virtual ASTNode* toAST(const CDataModel* pDataModel) const override;

  /**
   * Retrieve the CN of the referred object.
   * @return const CRegisteredCommonName & objectCN
   */
  const CRegisteredCommonName & getObjectCN() const;

  /**
   * Retrieve the pointer to the referred object interface
   * @return const CObjectInterface * pObjectInterface
   */
  const CObjectInterface * getObjectInterfacePtr() const;

  /**
   * Retrieve the pointer to the value of the referred object
   * @return const C_FLOAT64 * pObjectValue
   */
  const C_FLOAT64 * getObjectValuePtr() const;

  /**
   * Set the pointer to the value of the referred object
   * @param C_FLOAT64 * pObjectValue
   */
  void setObjectValuePtr(C_FLOAT64 * pObjectValue);

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

  //Attributes
private:
  /**
   * Pointer to the object
   */
  const CObjectInterface * mpObject;

  /**
   * The registered object name to track eventual renaming.
   */
  CRegisteredCommonName mRegisteredObjectCN;
};

#endif // COPASI_CEvaluationNodeObject
