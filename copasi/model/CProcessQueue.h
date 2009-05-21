// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CProcessQueue.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/05/21 15:34:38 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CProcessQueue
#define COPASI_CProcessQueue

#include <map>
#include <set>

// We have not yet a stack machine for expression thus we use the old AST
#define CMathExpression CExpression

class CMathExpression;
class CMathModel;
class CMathEvent;

class CProcessQueue
{
private:
  class CKey
  {
    // Operations
  public:
    /**
     * Default constructor
     */
    CKey();

    /**
     * Copy constructor
     * @param const CKey & src
     */
    CKey(const CKey & src);

    /**
     * Specific constructor
     * @param const C_FLOAT64 & executionTime
     * @param const bool & equality
     * @param const unsigned C_INT32 & eventId
     * @param const unsigned C_INT32 & cascadingLevel
     */
    CKey(const C_FLOAT64 & executionTime,
         const bool & equality,
         const unsigned C_INT32 & eventId,
         const unsigned C_INT32 & cascadingLevel);

    /**
     * Destructor
     */
    ~CKey();

    /**
     * A less than sort operator for sorting the entries in the queue
     * @param const CKey & rhs
     * @return bool lessThan
     */
    bool operator < (const CKey & rhs) const;

    /**
     * Retrieve the event id
     * @return const unsigned C_INT32 & eventId
     */
    inline const unsigned C_INT32 & getEventId() const {return mEventId;}

    /**
     * Retrieve the execution time.
     * @return const C_FLOAT64 & executionTime
     */
    inline const C_FLOAT64 & getExecutionTime() const {return mExecutionTime;}

    // Attributes
  private:
    /**
     * The time the entry is scheduled to be executed.
     */
    C_FLOAT64 mExecutionTime;

    /**
     * Cascading level
     */
    unsigned C_INT32 mCascadingLevel;

    /**
     * A Boolean value indication whether we have equality or inequality.
     * Equalities have to be handled prior to inequalities
     */
    bool mEquality;

    /**
     * The event Id is used for creating atomic sets of assignments.
     */
    unsigned C_INT32 mEventId;
  };

  class CAction
  {
    // Operations
  private:
    /**
     * Default constructor (hidden)
     */
    CAction();

  public:
    /**
     * Copy constructor
     * @param const CAction & src
     */
    CAction(const CAction & src);

    /**
     * Specific constructor
     * @param C_FLOAT64 * pTarget
     * @param CMathExpression * pExpression
     * @param CMathEvent * pEvent
     */
    CAction(C_FLOAT64 * pTarget,
            const C_FLOAT64 & value,
            CMathEvent * pEvent);

    /**
     * Specific constructor
     * @param C_FLOAT64 * pTarget
     * @param CMathExpression * pExpression
     * @param CMathExpression * pDelayExpression
     * @param CMathEvent * pEvent
     * @param CProcessQueue & processQueue
     */
    CAction(C_FLOAT64 * pTarget,
            CMathExpression * pExpression,
            CMathExpression * pDelayExpression,
            CMathEvent * pEvent,
            CProcessQueue * pProcessQueue);

    /**
     * Destructor (hidden)
     */
    ~CAction();

    /**
     * Process the entry
     * @param const unsigned C_INT32 & eventId
     */
    void process(const unsigned C_INT32 & eventId);

    /**
     * Retrieve the event id
     * @return CMathEvent * pEvent
     */
    inline CMathEvent * getEvent() const {return mpEvent;}

    // Attributes
  public:
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
    CMathExpression * mpExpression;

    /**
     * The expression to be evaluates if the entry is a calculation.
     */
    CMathExpression * mpDelayExpression;

    /**
     * The event associated with this action
     */
    CMathEvent * mpEvent;

    /**
     * A pointer to the process queue to which a subsequent assignment must be added if
     * the entry is a calculation.
     */
    CProcessQueue * mpProcessQueue;
  };

  // Type definitions
private:
  typedef std::multimap< CKey, CAction >::iterator iterator;

  typedef std::pair < std::multimap< CKey, CAction >::iterator,
  std::multimap< CKey, CAction >::iterator > range;

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
   * @param CMathEvent * pEvent
   * @return bool success
   */
  bool addAssignment(const C_FLOAT64 & executionTime,
                     const bool & equality,
                     const unsigned C_INT32 & eventId,
                     C_FLOAT64 * pTarget,
                     const C_FLOAT64 & value,
                     CMathEvent * pEvent);

  /**
   * Add a calculation to the process queue.
   * @param const C_FLOAT64 & executionTime
   * @param const bool & equality
   * @param const unsigned C_INT32 & eventId
   * @param C_FLOAT64 * pTarget
   * @param CMathExpression * pExpression
   * @param CMathExpression * pDelayExpression
   * @param CMathEvent * pEvent
   * @return bool success
   */
  bool addCalculation(const C_FLOAT64 & executionTime,
                      const bool & equality,
                      const unsigned C_INT32 & eventId,
                      C_FLOAT64 * pTarget,
                      CMathExpression * pExpression,
                      CMathExpression * pDelayExpression,
                      CMathEvent * pEvent);

  /**
   * Initialize the process queue.
   * @param CMathModel * pMathModel
   * @return bool success
   */
  bool initialize(CMathModel * pMathModel);

  /**
   * Process the queue.
   * @param const C_FLOAT64 & time
   * @param const bool & priorToOutput
   * @return bool success
   */
  bool process(const C_FLOAT64 & time,
               const bool & priorToOutput);

  /**
   * Create a unique eventId
   * @return const unsigned C_INT32 & eventId;
   */
  const unsigned C_INT32 & createEventId();

  /**
   * Retrieve the next execution time scheduled in the process queue
   * @return const C_FLOAT64 & processQueueExecutionTime
   */
  const C_FLOAT64 & getProcessQueueExecutionTime() const;

  /**
   * Checks whether the process queue is empty
   * @return bool isEmpty
   */
  bool isEmpty() const;

private:
  /**
   * Destroy a unique eventId
   * @@param const unsigned C_INT32 & eventId;
   */
  void destroyEventId(const unsigned C_INT32 & eventId);

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
  std::multimap< CKey, CAction > mCalculations;

  /**
   * An ordered list of assignments in the queue.
   */
  std::multimap< CKey, CAction > mAssignments;

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

  /**
   * A set of currently active event ids
   */
  std::set< unsigned C_INT32 > mEventIdSet;

  /**
   * A pointer to the model
   */
  CMathModel * mpMathModel;
};

#endif // COPASI_CProcessQueue
