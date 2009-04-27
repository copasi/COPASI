// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/Attic/CMathEvent.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/27 19:03:34 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CMathEvent
#define COPASI_CMathEvent

// We have not yet a stack machine for expression thus we use the old AST
#define CMathExpression CExpression

#include "copasi/function/CExpression.h"

class CMathEvent : public CCopasiContainer
{
private:
  class CAssignment : public CCopasiContainer
  {
    // Operations
  public:
    /**
     * Default constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CAssignment(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CAssignment &" src
     * @param "const CCopasiContainer * pParent (default: NULL)
     */
    CAssignment(const CAssignment & src,
                const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    ~CAssignment();

    // Attributes
  private:
    /**
     * Pointer to the value to be modified by the assignment
     */
    C_FLOAT64 * mpTarget;

    /**
     * Expression to calculate the new value.
     */
    CMathExpression mExpression;
  };

  // Operations
public:
  /**
   * Default constructor
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CMathEvent(const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param "const CMathEvent &" src
   * @param "const CCopasiContainer * pParent (default: NULL)
   */
  CMathEvent(const CMathEvent & src,
             const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  ~CMathEvent();

  // Attributes
private:
  /**
   * Trigger expression.
   */
  CMathExpression mTrigger;

  /**
   * Boolean value indicating the status of the trigger
   */
  bool mActive;

  /**
   * Boolean value indicating whether the trigger checks for equality or inequality.
   */
  bool mEquality;

  /**
   * Boolean value indicating whether the event involves a delay.
   */
  bool mHaveDelay;

  /**
   * Delay expression.
   */
  CMathExpression mDelay;

  /**
   * Boolean value indicating whether the calculation or the assignment is delayed.
   */
  bool mDelayAssignment;

  /**
   * List of assignments
   */
  CCopasiVector< CAssignment > mAssignments;
};

#endif // COPASI_CMathEvent
