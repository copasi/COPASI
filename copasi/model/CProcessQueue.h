// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CProcessQueue.h,v $
//   $Revision: 1.8.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/12 19:04:02 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CProcessQueue
#define COPASI_CProcessQueue

#include <map>
#include <set>

#include "copasi/utilities/CVector.h"

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
     * @param const size_t & order
     * @param const size_t & eventId
     * @param const size_t & cascadingLevel
     */
    CKey(const C_FLOAT64 & executionTime,
         const bool & equality,
         const size_t & order,
         const size_t & eventId,
         const size_t & cascadingLevel);

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
     * @return const size_t & eventId
     */
    inline const size_t & getEventId() const {return mEventId;}

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
    size_t mCascadingLevel;

    /**
     * A Boolean value indication whether we have equality or inequality.
     * Equalities have to be handled prior to inequalities
     */
    bool mEquality;

    /**
     * The order in which simultaneous event assignments are processed.
     */
    size_t mOrder;

    /**
     * The event Id is used for creating atomic sets of assignments.
     */
    size_t mEventId;
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
     * @param CMathEvent * pEvent
     * @param CProcessQueue & processQueue
     */
    CAction(C_FLOAT64 * pTarget,
            CMathExpression * pExpression,
            CMathEvent * pEvent,
            CProcessQueue * pProcessQueue);

    /**
     * Destructor (hidden)
     */
    ~CAction();

    /**
     * Process the entry
     * @param const size_t & eventId
     */
    void process(const size_t & eventId);

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
public:
  typedef std::multimap< CKey, CAction >::iterator iterator;

  typedef std::pair < std::multimap< CKey, CAction >::iterator,
  std::multimap< CKey, CAction >::iterator > range;

  typedef range(*resolveSimultaneousAssignments)(const std::multimap< CKey, CAction > & /* assignments */,
      const C_FLOAT64 & /* time */,
      const bool & /* equality */,
      const size_t & /* cascadingLevel */);

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
   * @param const size_t & order
   * @param const size_t & eventId
   * @param C_FLOAT64 * pTarget
   * @param const C_FLOAT64 & value
   * @param CMathEvent * pEvent
   * @return bool success
   */
  bool addAssignment(const C_FLOAT64 & executionTime,
                     const bool & equality,
                     const size_t & order,
                     const size_t & eventId,
                     C_FLOAT64 * pTarget,
                     const C_FLOAT64 & value,
                     CMathEvent * pEvent);

  /**
   * Add a calculation to the process queue.
   * @param const C_FLOAT64 & executionTime
   * @param const bool & equality
   * @param const size_t & order
   * @param const size_t & eventId
   * @param C_FLOAT64 * pTarget
   * @param CMathExpression * pExpression
   * @param CMathEvent * pEvent
   * @return bool success
   */
  bool addCalculation(const C_FLOAT64 & executionTime,
                      const bool & equality,
                      const size_t & order,
                      const size_t & eventId,
                      C_FLOAT64 * pTarget,
                      CMathExpression * pExpression,
                      CMathEvent * pEvent);

  /**
   * Clear the process queue.
   * @param CMathModel * pMathModel
   */
  void initialize(CMathModel * pMathModel);

  /**
   * Process the queue.
   * @param const C_FLOAT64 & time
   * @param const bool & priorToOutput
   * @param resolveSimultaneousAssignments pResolveSimultaneousAssignments
   * @return bool stateChanged
   */
  bool process(const C_FLOAT64 & time,
               const bool & priorToOutput,
               resolveSimultaneousAssignments pResolveSimultaneousAssignments);

  /**
   * Create a unique eventId
   * @return const size_t & eventId;
   */
  const size_t & createEventId();

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
   * @@param const size_t & eventId;
   */
  void destroyEventId(const size_t & eventId);

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
   * Check whether the executions of assignment lead to newly found roots
   * @return bool rootsFound
   */
  bool rootsFound();

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
  size_t mExecutionLimit;

  /**
   * A counter of the execution steps for the current process
   */
  size_t mExecutionCounter;

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
  size_t mCascadingLevel;

  /**
   * A flag indicating that simultaneous assignments have been found.
   */
  bool mSimultaneousAssignments;

  /**
   * A set of currently active event ids
   */
  std::set< size_t > mEventIdSet;

  /**
   * A pointer to the math model the process queue belongs to.
   */
  CMathModel * mpMathModel;

  /**
   *
   */
  CVector< C_INT > mRootsFound;

  /**
   *
   */
  CVector< C_FLOAT64 > mRootValues1;

  /**
   *
   */
  CVector< C_FLOAT64 > mRootValues2;

  /**
   *
   */
  CVector< C_FLOAT64 > * mpRootValuesBefore;

  /**
   *
   */
  CVector< C_FLOAT64 > * mpRootValuesAfter;

  /**
   * A pointer to a call back method for resolving simultaneous event assignments
   */
  resolveSimultaneousAssignments mpResolveSimultaneousAssignments;
};

#endif // COPASI_CProcessQueue
