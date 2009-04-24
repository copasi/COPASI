// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/Attic/CMathEvent.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/24 19:27:21 $
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

class CMathEvent
{
private:
  class CAssignment
  {

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
   */
  CMathEvent();

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
  bool mDelayCalculation;

  /**
   * List of assignments
   */
  std::vector< CAssignment > mAssignments;
};

#endif // COPASI_CMathEvent
