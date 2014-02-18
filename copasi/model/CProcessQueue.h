// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CProcessQueue
#define COPASI_CProcessQueue

#include <map>
#include <set>

#include "copasi/utilities/CVector.h"
#include "copasi/model/CEvent.h"

class CExpression;
class CMathModel;
class CMathEvent;

class CProcessQueue
{
private:
  class CKey
  {
    friend std::ostream &operator<<(std::ostream &os, const CProcessQueue & o);

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
     * @param const size_t & cascadingLevel
     */
    CKey(const C_FLOAT64 & executionTime,
         const bool & equality,
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
     * Retrieve the execution time.
     * @return const C_FLOAT64 & executionTime
     */
    inline const C_FLOAT64 & getExecutionTime() const {return mExecutionTime;}

    friend std::ostream &operator<<(std::ostream &os, const CKey & o);

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
  };

  friend std::ostream &operator<<(std::ostream &os, const CKey & o);

  class CAction
  {
  public:
    enum Type
    {
      Calculation = 0,
      Assignment,
      Callback
    };

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
     * @param CMathEvent * pEvent
     * @param CProcessQueue * pProcessQueue
     */
    CAction(CMathEvent * pEvent,
            CProcessQueue * pProcessQueue);

    /**
     * Specific constructor
     * @param const CVector< C_FLOAT64 > & values
     * @param CMathEvent * pEvent
     * @param CProcessQueue * pProcessQueue
     */
    CAction(const CVector< C_FLOAT64 > & values,
            CMathEvent * pEvent,
            CProcessQueue * pProcessQueue);

    /**
     * Destructor (hidden)
     */
    ~CAction();

    /**
     * Process the action
     * @return bool stateChanged
     */
    bool process();

    /**
     * Retrieve the event id
     * @return CMathEvent * pEvent
     */
    inline CMathEvent * getEvent() const {return mpEvent;}

    /**
     * Retrieve the type of action
     * @return const Type & type
     */
    const Type & getType() const;

    friend std::ostream &operator<<(std::ostream &os, const CAction & o);

    // Attributes
  public:
    /**
     * The type of the actions
     */
    Type mType;

    /**
     * The new value if the entry is an assignment.
     */
    CVector< C_FLOAT64 > mValues;

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

  friend std::ostream &operator<<(std::ostream &os, const CAction & o);

  // Type definitions
public:
  typedef std::multimap< CKey, CAction >::iterator iterator;

  typedef std::pair < std::multimap< CKey, CAction >::iterator, std::multimap< CKey, CAction >::iterator > range;

  typedef iterator(*resolveSimultaneousAssignments)(const std::multimap< CKey, CAction > & /* assignments */,
      const C_FLOAT64 & /* time */,
      const bool & /* equality */,
      const size_t & /* cascadingLevel */);

  /**
   * This is the type for an event call back function
   */
  typedef void (*EventCallBack)(void*, CEvent::Type type);

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
   * @param const CVector< C_FLOAT64 > & values
   * @param CMathEvent * pEvent
   * @return bool success
   */
  bool addAssignment(const C_FLOAT64 & executionTime,
                     const bool & equality,
                     const CVector< C_FLOAT64 > & values,
                     CMathEvent * pEvent);

  /**
   * Add a calculation to the process queue.
   * @param const C_FLOAT64 & executionTime
   * @param const bool & equality
   * @param CMathEvent * pEvent
   * @return bool success
   */
  bool addCalculation(const C_FLOAT64 & executionTime,
                      const bool & equality,
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
   * Retrieve the next execution time scheduled in the process queue
   * @return const C_FLOAT64 & processQueueExecutionTime
   */
  const C_FLOAT64 & getProcessQueueExecutionTime() const;

  /**
   * Set whether to continue on simultaneous events
   * @param const bool & continueSimultaneousEvents
   */
  void setContinueSimultaneousEvents(const bool & continueSimultaneousEvents);

  /**
   * Retrieve whether to continue on simultaneous events.
   * @return const bool & continueSimultaneousEvents
   */
  const bool & getContinueSimultaneousEvents() const;

  /**
   * Set whether to continue on simultaneous events
   * @param const bool & continueSimultaneousEvents
   */
  void setContinueSimultaneousEvents(const bool & continueSimultaneousEvents);

  /**
   * Retrieve whether to continue on simultaneous events.
   * @return const bool & continueSimultaneousEvents
   */
  const bool & getContinueSimultaneousEvents() const;

  /**
   * Sets an event call back. The call back function must be a static function
   * that receives a "this" pointer as first argument.
   * The function is called when the actual assignment takes place,
   * or when the assignment would take place in case the event
   * has no assignment.
   * The function is called with an integer argument:
   *    1:  An assignment has happened
   *    2:  A cut plane was crossed
   */
  void setEventCallBack(void* pTask, EventCallBack ecb);

  /**
   * This prints debugging info to stdout
   */
  void printDebug() const {std::cout << *this; };

  friend std::ostream &operator<<(std::ostream &os, const CProcessQueue & o);

private:
  /**
   * Destroy a unique eventId
   * @@param const size_t & eventId;
   */
  void destroyEventId(const size_t & eventId);

  /**
   * Retrieve the currently pending actions
   * @return CProcessQueue::iterator itAction
   */
  iterator getAction();

  /**
   * Execute the actions
   * @param CProcessQueue::iterator itAction
   * @return bool stateChanged
   */
  bool executeAction(CProcessQueue::iterator itAction);

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
  std::multimap< CKey, CAction > mActions;

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
  bool mSimultaneousAssignmentsFound;

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

  /**
   * A flag indicating to continue when simultaneous events are encountered.
   */
  bool mContinueSimultaneousEvents;

  /**
   * the object to which the call back function belongs
   */
  void * mpCallbackTask;

  /**
   * the pointer to the call back function
   */
  EventCallBack mpEventCallBack;
};

#endif // COPASI_CProcessQueue
