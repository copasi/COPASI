// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/Attic/CMathEvent.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/06/02 20:55:42 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CMathEvent
#define COPASI_CMathEvent

// We have not yet a stack machine for expression thus we use the old AST
#define CMathExpression CExpression

#include "copasi/model/CMathTrigger.h"
#include "copasi/function/CExpression.h"

class CEvent;
class CEventAssignment;
class CProcessQueue;

class CMathEvent : public CCopasiContainer
{
private:
  class CAssignment : public CCopasiContainer
  {
    friend class CMathEvent;

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

    /**
     * Compile the root finder
     * @param const CEventAssignment * pEvent
     * @param std::vector< CCopasiContainer * > listOfContainer
     */
    bool compile(const CEventAssignment * pAssignment,
                 std::vector< CCopasiContainer * > listOfContainer);

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

  /**
   * Compile the root finder
   * @param const CEvent * pEvent
   * @param std::vector< CCopasiContainer * > listOfContainer
   */
  bool compile(const CEvent * pEvent,
               std::vector< CCopasiContainer * > listOfContainer);

  /**
   * At least one of the root finders of the the trigger has found a
   * root. This methods checks whether the event fires and schedules
   * the event if needed.
   * @param const C_FLOAT64 & time
   * @param CProcessQueue & processQueue
   */
  void processRoot(const C_FLOAT64 & time,
                   CProcessQueue & processQueue);

  /**
   * Apply all needed refreshes so that the delay expression are
   * correctly calculated.
   */
  void applyDelayRefreshes();

  /**
   * Apply all needed refreshes so that the assignment expressions are
   * correctly calculated.
   */
  void applyValueRefreshes();

  /**
   * Apply all needed refreshes to update all values depending on the
   * assignment targets.
   */
  void applyDependentRefreshes();

  /**
   * Retrieve the trigger for this event.
   * @return CMathTrigger & mathTrigger
   */
  CMathTrigger & getMathTrigger();

  /**
   * Retrieve the order in which this event shall be processed
   * @return const unsigned C_INT32 & order
   */
  const unsigned C_INT32 & getOrder() const;

  // Attributes
private:
  /**
   * Trigger expression.
   */
  CMathTrigger mTrigger;

  /**
   * The order in which the event is processed in case of simultaneous
   * assignments
   */
  unsigned C_INT32 mOrder;

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

  /**
   * A sequence of refresh calls needed to prepare
   * to calculate the delay value.
   */
  std::vector< Refresh * > mDelayValueRefreshes;

  /**
   * A sequence of refresh calls needed to prepare
   * to calculate the current values of the assignments.
   */
  std::vector< Refresh * > mAssignmentValueRefreshes;

  /**
   * A sequence of refresh calls needed to calculate all
   * values which depend on the target values of the assignments.
   */
  std::vector< Refresh * > mDependentValueRefreshes;
};

#endif // COPASI_CMathEvent
