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

/*!
    \file CExpression.h
    \brief Header file of class CExpression
 */

#ifndef COPASI_CExpression
#define COPASI_CExpression

#include "copasi/function/CEvaluationTree.h"
#include "copasi/core/CDataContainer.h"

class CDataModel;

class CExpression: public CEvaluationTree
{
  // Operations
public:
  /**
   * Default constructor
   * @param const std::string & name (default: "Expression")
   * @param const CDataContainer * pParent (default: NULL)
   */
  CExpression(const std::string & name = "Expression",
              const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param "const CExpression &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CExpression(const CExpression & src,
              const CDataContainer * pParent);

  /**
   *  Destructor
   */
  virtual ~CExpression();

  /**
   * Creates the corresponding initial expression for the given expression by converting
   * each transient value to the corresponding initial value.
   * @param const CExpression & expression
   * @return CExpression * pInitialExpression
   */
  static CExpression * createInitialExpression(const CExpression & expression, const CDataModel* pDataModel);

private:
  /**
   * Initialize the contained CDataObjects
   */
  void initObjects();

public:
  /**
   * Set whether this a boolean expression or not
   * @param const bool & isBoolean
   */
  void setIsBoolean(const bool & booleanRequired);

  /**
   * Set the infix description of the tree and compile it.
   * @param const std::string & infix
   * @return CIssue issue
   */
  virtual CIssue setInfix(const std::string & infix) override;

  /**
   * Compile the evaluation tree.
   * @param CObjectInterface::ContainerList listOfContainer (Default: CDataContainer::EmptyList)
   * @return CIssue issue
   */
  virtual CIssue compile(CObjectInterface::ContainerList listOfContainer =
                           CDataContainer::EmptyList);

  /**
   * Calculates the value of the function
   * @return const C_FLOAT64 & result
   */
  virtual const C_FLOAT64 & calcValue();

  /**
   * Refresh the value of the expression
   */
  void refresh();

  /**
   * Write display mathml of the expression into the ostream "out"
   * level specifies indentation
   * fullExpand==true means function calls are expanded
   */
  void writeMathML(std::ostream & out, bool fullExpand, size_t l) const;

  /**
   * Retrieve a pointer to the object defined by CN. This method may only be called
   * during compile() since the list mpListOfContainer is only valid then.
   * @param const CCommonName & CN
   * @return const CObjectInterface * value
   */
  virtual const CObjectInterface * getNodeObject(const CCommonName & CN) const override;

public:
  /**
   * Retrieve the list of container used for compile
   * @return const CObjectInterface::ContainerList & listOfContainer
   */
  const CObjectInterface::ContainerList & getListOfContainer() const;

  /**
   * This method performs an infix update if a referenced object has been renamed
   * @return bool success
   */
  bool updateInfix();

  /**
   * Retrieve the human readable display string.
   * Note, the expression must be compiled for this return a displayable
   * string.
   * @return const std::string & displayString
   */
  const std::string & getDisplayString() const;

  /**
   * Retrieve the display string in C syntax.
   */
  std::string getCCodeString() const;

  /**
   * Retrieve the display string in Berkeley Madonna syntax.
   */
  std::string getBerkeleyMadonnaString() const;

  /**
   * Retrieve the display string in XPPAUT  syntax.
   */
  std::string getXPPString() const;

  // Attribute
protected:
  /**
   * Pointer to the list of containers used for compilation.
   */
  const CObjectInterface::ContainerList * mpListOfContainer;

  /**
   * Human readable display string.
   */
  std::string mDisplayString;

  /**
   * Indicates whether the expression is boolean or not.
   */
  bool mIsBoolean;
};

#endif // COPASI_CExpression
