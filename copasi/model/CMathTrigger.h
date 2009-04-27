// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/Attic/CMathTrigger.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/27 19:03:57 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CMathTrigger
#define COPASI_CMathTrigger

// We have not yet a stack machine for expression thus we use the old AST
#define CMathExpression CExpression

#include "copasi/function/CExpression.h"

class CMathTrigger : public CCopasiContainer
{
private:
  class CRoot : public CCopasiContainer
  {
    // Operations
  public:
    /**
     * Default constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CRoot(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CRoot &" src
     * @param "const CCopasiContainer * pParent (default: NULL)
     */
    CRoot(const CRoot & src,
          const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CRoot();

    // Attributes
  private:
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
  bool compileAND();
  bool compileOR();
  bool compileXOR();
  bool compileNOT();
  bool compileEQUALITY();

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
  CCopasiVector< CRoot > mRoots;
};

#endif // COPASI_CMathTrigger
