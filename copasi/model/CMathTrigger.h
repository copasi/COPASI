// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/Attic/CMathTrigger.h,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/06/29 11:37:40 $
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
     * @param const C_FLOAT64 * pEquality
     * @return CEvalutionNode * trueExpression
     */
    CEvaluationNode * getTrueExpression(const C_FLOAT64 * pEquality) const;

    /**
     * Retrieve the expression evaluating the activity value
     * @return CEvalutionNode * activeExpression
     */
    CEvaluationNode * getActiveExpression() const;

    /**
     * Retrieve the expression evaluating the equality value
     * @return CEvalutionNode * equalityExpression
     */
    CEvaluationNode * getEqualityExpression() const;

    /**
     * Activate the root finder dependent on the currently
     * processed equality status
     * @param const bool & equality
     */
    void charge(const bool & equality);

    /**
     * Determine the activity for the initial conditions.
     */
    void calculateInitialActivity();

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
   * Check whether the fire condition is met dependent on the
   * currently processed equality status
   * @param const bool & equality
   * @return bool fire
   */
  bool fire(const bool & equality);

  /**
   * Determine the activity for the initial conditions.
   */
  void calculateInitialActivity();

  /**
   * Calculate whether the current trigger is evaluated for
   * equality.
   * @return equality
   */
  bool calculateEquality();

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
               CEvaluationNode * & pTrueExpression,
               CEvaluationNode * & pActiveExpression,
               CEvaluationNode * & pFireExpression,
               CEvaluationNode * & pEqualityExpression);
  bool compileAND(const CEvaluationNode * pSource,
                  CEvaluationNode * & pTrueExpression,
                  CEvaluationNode * & pActiveExpression,
                  CEvaluationNode * & pFireExpression,
                  CEvaluationNode * & pEqualityExpression);
  bool compileOR(const CEvaluationNode * pSource,
                 CEvaluationNode * & pTrueExpression,
                 CEvaluationNode * & pActiveExpression,
                 CEvaluationNode * & pFireExpression,
                 CEvaluationNode * & pEqualityExpression);
  bool compileXOR(const CEvaluationNode * pSource,
                  CEvaluationNode * & pTrueExpression,
                  CEvaluationNode * & pActiveExpression,
                  CEvaluationNode * & pFireExpression,
                  CEvaluationNode * & pEqualityExpression);
  bool compileEQ(const CEvaluationNode * pSource,
                 CEvaluationNode * & pTrueExpression,
                 CEvaluationNode * & pActiveExpression,
                 CEvaluationNode * & pFireExpression,
                 CEvaluationNode * & pEqualityExpression);
  bool compileNE(const CEvaluationNode * pSource,
                 CEvaluationNode * & pTrueExpression,
                 CEvaluationNode * & pActiveExpression,
                 CEvaluationNode * & pFireExpression,
                 CEvaluationNode * & pEqualityExpression);
  bool compileLT(const CEvaluationNode * pSource,
                 CEvaluationNode * & pTrueExpression,
                 CEvaluationNode * & pActiveExpression,
                 CEvaluationNode * & pFireExpression,
                 CEvaluationNode * & pEqualityExpression);
  bool compileLE(const CEvaluationNode * pSource,
                 CEvaluationNode * & pTrueExpression,
                 CEvaluationNode * & pActiveExpression,
                 CEvaluationNode * & pFireExpression,
                 CEvaluationNode * & pEqualityExpression);
  bool compileGT(const CEvaluationNode * pSource,
                 CEvaluationNode * & pTrueExpression,
                 CEvaluationNode * & pActiveExpression,
                 CEvaluationNode * & pFireExpression,
                 CEvaluationNode * & pEqualityExpression);
  bool compileGE(const CEvaluationNode * pSource,
                 CEvaluationNode * & pTrueExpression,
                 CEvaluationNode * & pActiveExpression,
                 CEvaluationNode * & pFireExpression,
                 CEvaluationNode * & pEqualityExpression);
  bool compileNOT(const CEvaluationNode * pSource,
                  CEvaluationNode * & pTrueExpression,
                  CEvaluationNode * & pActiveExpression,
                  CEvaluationNode * & pFireExpression,
                  CEvaluationNode * & pEqualityExpression);

  static
  CEvaluationNode * getEqualityExpression(CEvaluationNode * pFireExpressionLeft,
                                          CEvaluationNode * pEqualityExpressionLeft,
                                          CEvaluationNode * pFireExpressionRight,
                                          CEvaluationNode * pEqualityExpressionRight);

  static
  CEvaluationNode * getFireExpression(CEvaluationNode * pTrueExpression,
                                      CEvaluationNode * pActiveExpression);

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
   * This values indicates whether the current root processing is for
   * equality or not.
   */
  C_FLOAT64 mEquality;

  /**
   * A vector containing the root expression.
   */
  CCopasiVector< CRootFinder > mRootFinders;
};

#endif // COPASI_CMathTrigger
