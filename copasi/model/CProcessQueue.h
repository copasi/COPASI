// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CProcessQueue.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/17 20:55:50 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CProcessQueue
#define COPASI_CProcessQueue

#include <map>
#include <stack>

class CExpression;

class CProcessQueue
{
private:
  class CProcessQueueKey
  {
    // Operations
  public:
    /**
     * Default constructor
     */
    CProcessQueueKey();

    /**
     * Copy constructor
     * @param const CProcessQueueKey & src
     */
    CProcessQueueKey(const CProcessQueueKey & src);

    /**
     * Specific constructor
     * @param const C_FLOAT64 & executionTime
     * @param const bool & equality
     * @param const unsigned C_INT32 & eventId
     * @param const unsigned C_INT32 & cascadingLevel
     */
    CProcessQueueKey(const C_FLOAT64 & executionTime,
                     const bool & equality,
                     const unsigned C_INT32 & eventId,
                     const unsigned C_INT32 & cascadingLevel);

    /**
     * Destructor
     */
    ~CProcessQueueKey();

    /**
     * A less than sort operator for sorting the entries in the queue
     * @param const CProcessQueueKey & rhs
     * @return bool lessThan
     */
    bool operator < (const CProcessQueueKey & rhs) const;

    // Attributes
  private:
    /**
     * The time the entry is scheduled to be executed.
     */
    C_FLOAT64 mExecutionTime;

    /**
     * A Boolean value indication whether we have equality or inequality.
     * Equalities have to be handled prior to inequalities
     */
    bool mEquality;

    /**
     * The event Id is used for creating atomic sets of assignments.
     */
    unsigned C_INT32 mEventId;

    /**
     * Cascading level
     */
    unsigned C_INT32 mCascadingLevel;
  };

  class CProcessQueueAction
  {
    // Operations
  private:
    /**
     * Default constructor (hidden)
     */
    CProcessQueueAction();

  public:
    /**
     * Copy constructor
     * @param const CProcessQueueEntry & src
     */
    CProcessQueueAction(const CProcessQueueAction & src);

    /**
     * Specific constructor
     * @param C_FLOAT64 * pTarget
     * @param CExpression * pExpression
     */
    CProcessQueueAction(C_FLOAT64 * pTarget,
                        const C_FLOAT64 & value);

    /**
     * Specific constructor
     * @param C_FLOAT64 * pTarget
     * @param CExpression * pExpression
     * @param CProcessQueue & processQueue
     */
    CProcessQueueAction(C_FLOAT64 * pTarget,
                        CExpression * pExpression,
                        CProcessQueue * pProcessQueue);

    /**
     * Destructor (hidden)
     */
    ~CProcessQueueAction();

    /**
     * Process the entry
     */
    void process();

    // Attributes
  private:
    /**
     * The target of the execution.
     */
    C_FLOAT64 * mpTarget;

    /**
     * The new value if the entry is an assignment.
     */
    C_FLOAT64 mValue;

    /**
     * The expression to be evaluates if the entry is a calculation.
     */
    CExpression * mpExpression;

    /**
     * A pointer to the process queue to which a subsequent assignment must be added if
     * the entry is a calculation.
     */
    CProcessQueue * mpProcessQueue;
  };

  // Type definitions
private:
  typedef std::multimap< CProcessQueueKey, CProcessQueueAction >::iterator iterator;

  typedef std::pair < std::multimap< CProcessQueueKey, CProcessQueueAction >::iterator,
  std::multimap< CProcessQueueKey, CProcessQueueAction >::iterator > range;

  // Operations
public:
  /**
   * Default constructor
   */
  CProcessQueue();

  /**
   * Copy constructor
   */
  CProcessQueue(const CProcessQueue & src);

  /**
   * Destructor
   */
  ~CProcessQueue();

  /**
   * Add an assignment to the process queue.
   * @param const C_FLOAT64 & executionTime
   * @param const bool & equality
   * @param const unsigned C_INT32 & eventId
   * @param C_FLOAT64 * pTarget
   * @param const C_FLOAT64 & value
   * @return bool success
   */
  bool addAssignment(const C_FLOAT64 & executionTime,
                     const bool & equality,
                     const unsigned C_INT32 & eventId,
                     C_FLOAT64 * pTarget,
                     const C_FLOAT64 & value);

  /**
   * Add a calculation to the process queue.
   * @param const C_FLOAT64 & executionTime
   * @param const bool & equality
   * @param const unsigned C_INT32 & eventId
   * @param C_FLOAT64 * pTarget
   * @param CExpression * pExpression
   * @return bool success
   */
  bool addCalculation(const C_FLOAT64 & executionTime,
                      const bool & equality,
                      const unsigned C_INT32 & eventId,
                      C_FLOAT64 * pTarget,
                      CExpression * pExpression);

  /**
   * Process the queue.
   * @param const C_FLOAT64 & time
   * @param const bool & priorToOutput
   * @return bool success
   */
  bool process(const C_FLOAT64 & time,
               const bool & priorToOutput);

private:
  /**
   * Retrieve the currently pending calculations
   * @return range calculations
   */
  range getCalculations();

  /**
   * Retrieve the currently pending assignments
   * @return range assignments
   */
  range getAssignments();

  /**
   * Execute the calculations
   * @param range & calculations
   * @return bool success
   */
  bool executeCalculations(range & calculations);

  /**
   * Execute the assignments
   * @param range & assignments
   * @return bool success
   */
  bool executeAssignments(range & assignments);

  /**
   * Check whether a range is not empty
   * @param const range & range
   * bool notEmpty
   */
  static bool notEmpty(const range & range);

  // Attributes
private:
  /**
   * An ordered list of calculations in the queue.
   */
  std::multimap< CProcessQueueKey, CProcessQueueAction > mCalculations;

  /**
   * An ordered list of assignments in the queue.
   */
  std::multimap< CProcessQueueKey, CProcessQueueAction > mAssignments;

  /**
   * The limit of execution steps allowed for call to process
   */
  unsigned C_INT32 mExecutionLimit;

  /**
   * A counter of the execution steps for the current process
   */
  unsigned C_INT32 mExecutionCounter;

  /**
   * The current time
   */
  C_FLOAT64 mTime;

  /**
   * Indicate whether we processing equality or inequality
   */
  bool mEquality;

  /**
   * The cascading level of events
   */
  unsigned C_INT32 mCascadingLevel;

  /**
   * A flag indicating that simultaneous assignments have been found.
   */
  bool mSimultaneousAssignments;
};

#endif // COPASI_CProcessQueue
