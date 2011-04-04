// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathEvent.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/04/04 13:24:50 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CMathEvent
#define COPASI_CMathEvent

#include "copasi/math/CMathTrigger.h"
#include "copasi/function/CExpression.h"
#include "copasi/utilities/CVector.h"

class CEvent;
class CEventAssignment;
class CProcessQueue;
class CMathContainer;

class CMathEventN
{
public:
  class CAssignment
  {

  };

  class CTrigger
  {
  public:
    class CRoot
    {

    };

    const CVector< CRoot > & getRoots() const;

  private:
    CVector< CRoot > mRoots;
  };

  static void initialize(CMathEventN * pEvent,
                         CEvent * pDataEvent,
                         const CMathContainer & container);

  const CTrigger & getTrigger() const;

  const CVector< CAssignment > & getAssignments() const;

private:
  CTrigger mTrigger;
  CVector< CAssignment > mAssignments;

};

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
    CExpression mExpression;
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
   * The event fires and the approriate actions are scheduled
   * in the process queue.
   * @param const C_FLOAT64 & time
   * @param const bool & equality
   * @param CProcessQueue & processQueue
   */
  void fire(const C_FLOAT64 & time,
            const bool & equality,
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
   * @return const size_t & order
   */
  const size_t & getOrder() const;

  /**
   * Calculate the execution time
   * @param const C_FLOAT64 & currentTime
   * @return C_FLOAT64 executionTime
   */
  C_FLOAT64 getExecutionTime(const C_FLOAT64 & currentTime);

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
  size_t mOrder;

  /**
   * Boolean value indicating whether the event involves a delay.
   */
  bool mHaveDelay;

  /**
   * Delay expression.
   */
  CExpression mDelay;

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
