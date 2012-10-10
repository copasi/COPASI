// Copyright (C) 2011 - 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CMathTrigger
#define COPASI_CMathTrigger

#include <stack>

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
     * Determine whether the root only changes during discrete events.
     * The root must be compiled before calling this method.
     * @param const std::set< const CCopasiObject *> & stateVariables
     */
    void determineDiscrete(const std::set< const CCopasiObject * > & stateVariables);

    /**
     * Check whether the root change only during discrete events.
     * @return const bool & isDiscrete
     */
    const bool & isDiscrete() const;

    /**
     * Check whether the root is checked for equality.
     * @return const bool & isEquality
     */
    const bool & isEquality() const;

    /**
     * Check whether the root's current state is true .
     * @return bool isTrue
     */
    bool isTrue() const;

    /**
     * Retrieve the expression evaluating the truth value
     * @return CEvalutionNode * trueExpression
     */
    CEvaluationNode * getTrueExpression() const;

    /**
     * Toggle the root status dependent on the
     * processed equality status
     * @param const C_FLOAT64 & time
     * @param const bool & equality
     * @param const bool & continuous
     */
    void toggle(const C_FLOAT64 & time,
                const bool & equality,
                const bool & continous);

    /**
     * Determine the truth value for the initial conditions.
     */
    void calculateInitialTrue();

    /**
     * Retrieve a pointer to the current value of the root.
     */
    C_FLOAT64 * getRootValuePtr();

    // Attributes
  private:
    /**
     * This expression calculates the root
     */
    CExpression mRoot;

    /**
     * A pointer to the value of the root expression
     */
    C_FLOAT64 * mpRootValue;

    /**
     * This indicates whether the root is checked for equality
     */
    bool mEquality;

    /**
     * This indicates whether the root changes only discretely
     */
    bool mDiscrete;

    /**
     * Indicates the truth value of the root active
     * This should be a bool but the CExpressionTree only handles double
     */
    C_FLOAT64 mTrue;

    /**
     * The time at which the last toggle of the trueth value occured
     */
    C_FLOAT64 mLastToggleTime;
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
   * Determine the true value for the initial conditions.
   */
  void calculateInitialTrue();

  /**
   * Determine the activity for the initial conditions.
   */
  void calculateInitialActivity();

  /**
   * Calculate the current trigger value.
   * @return value
   */
  bool calculate();

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
               CEvaluationNode * & pTrueExpression);
  bool compileAND(const CEvaluationNode * pSource,
                  CEvaluationNode * & pTrueExpression);
  bool compileOR(const CEvaluationNode * pSource,
                 CEvaluationNode * & pTrueExpression);
  bool compileXOR(const CEvaluationNode * pSource,
                  CEvaluationNode * & pTrueExpression);
  bool compileEQ(const CEvaluationNode * pSource,
                 CEvaluationNode * & pTrueExpression);
  bool compileNE(const CEvaluationNode * pSource,
                 CEvaluationNode * & pTrueExpression);
  bool compileLT(const CEvaluationNode * pSource,
                 CEvaluationNode * & pTrueExpression);
  bool compileLE(const CEvaluationNode * pSource,
                 CEvaluationNode * & pTrueExpression);
  bool compileGT(const CEvaluationNode * pSource,
                 CEvaluationNode * & pTrueExpression);
  bool compileGE(const CEvaluationNode * pSource,
                 CEvaluationNode * & pTrueExpression);
  bool compileNOT(const CEvaluationNode * pSource,
                  CEvaluationNode * & pTrueExpression);
  bool compileFUNCTION(const CEvaluationNode * pSource,
                       CEvaluationNode * & pTrueExpression);
  bool compileEXPRESSION(const CEvaluationNode * pSource,
                         CEvaluationNode * & pTrueExpression);
  bool compileVARIABLE(const CEvaluationNode * pSource,
                       CEvaluationNode * & pTrueExpression);

  CEvaluationNode * copyBranch(const CEvaluationNode * pSource);

  // Attributes
private:
  /**
   * This expression evaluates whether
   * the trigger value is true.
   */
  CExpression mTrueExpression;

  /**
   * A vector containing the root expression.
   */
  CCopasiVector< CRootFinder > mRootFinders;

  /**
   * A stack to map variable nodes to the value nodes provided
   * in the function call
   */
  std::stack< std::vector< const CEvaluationNode * > > mFunctionVariableMap;
};

#endif // COPASI_CMathTrigger
