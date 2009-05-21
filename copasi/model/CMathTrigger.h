// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/Attic/CMathTrigger.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/05/21 16:35:48 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CMathTrigger
#define COPASI_CMathTrigger

#include <stack>

// We have not yet a stack machine for expression thus we use the old AST
#define CMathExpression CExpression

#include "copasi/function/CExpression.h"

class CMathTrigger : public CCopasiContainer
{
public:
  class CRootFinder : public CCopasiContainer
  {
    friend class CMathTrigger;

    // Operations
  public:
    /**
     * Default constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CRootFinder(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CRoot &" src
     * @param "const CCopasiContainer * pParent (default: NULL)
     */
    CRootFinder(const CRootFinder & src,
                const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CRootFinder();

    /**
     * Initialize the contained object references.
     */
    void initObjects();

    /**
     * Compile the root finder
     * @param std::vector< CCopasiContainer * > listOfContainer
     */
    bool compile(std::vector< CCopasiContainer * > listOfContainer);

    /**
     * Retrieve the expression evaluating the truth value
     * CEvalutionNode * trueExpression
     */
    CEvaluationNode * getTrueExpression() const;

    /**
     * Retrieve the expression evaluating the fire value
     * CEvalutionNode * fireExpression
     */
    CEvaluationNode * getFireExpression() const;

    /**
     * Retrieve the expression evaluating the equality value
     * CEvalutionNode * equalityExpression
     */
    CEvaluationNode * getEqualityExpression() const;

    /**
     * Activate the root finder if the charge expression is true;
     * Charge expression: mRoot.mValue <= 0 && !mActive
     */
    void charge();

    /**
     * Retrieve a pointer to the current value of the root.
     */
    C_FLOAT64 * getRootValuePtr();

    // Attributes
  private:
    /**
     * This expression calculates the root
     */
    CMathExpression mRoot;

    /**
     * A pointer to the value of the root expression
     */
    C_FLOAT64 * mpRootValue;

    /**
     * This indicates whether the root is checked for equality
     */
    bool mEquality;

    /**
     * Indicates whether the trigger is active
     */
    // TODO This should be a bool but the CExpressionTree only handles double
    C_FLOAT64 mActive;
  };

  // Operations
public:
  /**
   * Default constructor
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CMathTrigger(const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param "const CMathTrigger &" src
   * @param "const CCopasiContainer * pParent (default: NULL)
   */
  CMathTrigger(const CMathTrigger & src,
               const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  virtual ~CMathTrigger();

  /**
   * Check whether the fire condition is met.
   * @return bool fire
   */
  bool fire();

  /**
   * Compile the trigger
   * @param const CExpression * pTriggerExpression
   * @param std::vector< CCopasiContainer * > listOfContainer
   * @return bool success
   */
  bool compile(const CExpression * pTriggerExpression,
               std::vector< CCopasiContainer * > listOfContainer);

  /**
   * Retrieve  the list of root finders
   * @return CCopasiVector< CRootFinder > & rootFinders
   */
  CCopasiVector< CRootFinder > & getRootFinders();

private:
  bool compile(const CEvaluationNode * pSource,
               CEvaluationNode * & pFireExpression,
               CEvaluationNode * & pEqualityExpression);
  bool compileAND(const CEvaluationNode * pSource,
                  CEvaluationNode * & pFireExpression,
                  CEvaluationNode * & pEqualityExpression);
  bool compileOR(const CEvaluationNode * pSource,
                 CEvaluationNode * & pFireExpression,
                 CEvaluationNode * & pEqualityExpression);
  bool compileXOR(const CEvaluationNode * pSource,
                  CEvaluationNode * & pFireExpression,
                  CEvaluationNode * & pEqualityExpression);
  bool compileEQ(const CEvaluationNode * pSource,
                 CEvaluationNode * & pFireExpression,
                 CEvaluationNode * & pEqualityExpression);
  bool compileNE(const CEvaluationNode * pSource,
                 CEvaluationNode * & pFireExpression,
                 CEvaluationNode * & pEqualityExpression);
  bool compileLT(const CEvaluationNode * pSource,
                 CEvaluationNode * & pFireExpression,
                 CEvaluationNode * & pEqualityExpression);
  bool compileLE(const CEvaluationNode * pSource,
                 CEvaluationNode * & pFireExpression,
                 CEvaluationNode * & pEqualityExpression);
  bool compileGT(const CEvaluationNode * pSource,
                 CEvaluationNode * & pFireExpression,
                 CEvaluationNode * & pEqualityExpression);
  bool compileGE(const CEvaluationNode * pSource,
                 CEvaluationNode * & pFireExpression,
                 CEvaluationNode * & pEqualityExpression);
  bool compileNOT(const CEvaluationNode * pSource,
                  CEvaluationNode * & pFireExpression,
                  CEvaluationNode * & pEqualityExpression);

  void pushNodes(CEvaluationNode * pActiveNode,
                 CEvaluationNode * pTrueNode);
  void popNodes();
  void addNodes(CEvaluationNode * pActiveNode,
                CEvaluationNode * pTrueNode);

  static
  CEvaluationNode * getEqualityExpression(CEvaluationNode * pFireExpressionLeft,
                                          CEvaluationNode * pEqualityExpressionLeft,
                                          CEvaluationNode * pFireExpressionRight,
                                          CEvaluationNode * pEqualityExpressionRight);

  CEvaluationNode * getFireExpression() const;

  // Attributes
private:
  /**
   * This expression evaluates whether
   * the trigger is active.
   */
  CMathExpression mActiveExpression;

  /**
   * This expression evaluates whether
   * the trigger value is true.
   */
  CMathExpression mTrueExpression;

  /**
   * This expression evaluates the boolean operators to determine whether
   * the trigger fires.
   */
  CMathExpression mFireExpression;

  /**
   * This expression evaluates whether the check us for equality.
   */
  CMathExpression mEqualityExpression;

  /**
   * A vector containing the root expression.
   */
  CCopasiVector< CRootFinder > mRootFinders;

  /**
   * The stack of nodes used to build the expression to
   * determine whether a trigger is active
   */
  std::stack< CEvaluationNode * > mActiveNodes;

  /**
   * The stack of nodes used to build the expression to
   * determine whether a trigger is true.
   */
  std::stack< CEvaluationNode * > mTrueNodes;

  /**
   * The stack of nodes used to build the fire expression
   */
  std::stack< CEvaluationNode * > mFireNodes;

  /**
   * The stack of nodes used to build the expression to
   * determine whether the check is for equality
   */
  std::stack< CEvaluationNode * > mEqualityNodes;
};

#endif // COPASI_CMathTrigger
