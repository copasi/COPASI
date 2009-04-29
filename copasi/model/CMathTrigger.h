// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/Attic/CMathTrigger.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/29 21:25:09 $
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
private:
  class CRootFinder : public CCopasiContainer
  {
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

    // Attributes
  public:
    /**
     * This expression calculates the root
     */
    CMathExpression mRoot;

    /**
     * Indicates whether the trigger is active
     */
    // TODO This should be a bool but the CExpressionTree only handles double
    C_FLOAT64 mActive;

    /**
     * This indicates whether the root is checked for equality
     */
    bool mEquality;
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
   * Compile the trigger
   * @param const CExpression * pTriggerExpression
   * @return bool success
   */
  bool compile(const CExpression * pTriggerExpression);

private:
  bool compile(const CEvaluationNode * pSource);
  bool compileAND(const CEvaluationNode * pSource);
  bool compileOR(const CEvaluationNode * pSource);
  bool compileXOR(const CEvaluationNode * pSource);
  bool compileEQ(const CEvaluationNode * pSource);
  bool compileNE(const CEvaluationNode * pSource);
  bool compileLT(const CEvaluationNode * pSource);
  bool compileLE(const CEvaluationNode * pSource);
  bool compileGT(const CEvaluationNode * pSource);
  bool compileGE(const CEvaluationNode * pSource);
  bool compileNOT(const CEvaluationNode * pSource);

  bool effectiveEquality(const bool & equality) const;

  // Attributes
private:
  /**
   * This expression evaluates the boolean operators to determine whether
   * the trigger fires.
   */
  CMathExpression mTriggerExpression;

  /**
   * Indicates whether the trigger is active.
   */
  bool mActive;

  /**
   * This expression evaluates whether the trigger is reactivated.
   */
  CMathExpression mActivateExpression;

  /**
   * A vector containing the root expression.
   */
  CCopasiVector< CRootFinder > mRootFinders;

  /**
   * A pointer to the Boolean trigger expression to be compiled
   */
  CExpression * mpExpression;

  /**
   * The stack of trigger nodes
   */
  std::stack< CEvaluationNode * > mTriggerNodes;

  /**
   * The stack of activate nodes
   */
  std::stack< CEvaluationNode * > mActivateNodes;

  /**
   * The currently processed root finding structure
   */
  CRootFinder * mpRoot;

  /**
   * The stack of root nodes
   */
  std::stack< CEvaluationNode * > mRootNodes;

  /**
   * Indicates how to modify the equality
   */
  bool mEqualityModifier;
};

#endif // COPASI_CMathTrigger
