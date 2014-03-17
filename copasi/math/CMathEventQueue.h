// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CMathEventQueue
#define COPASI_CMathEventQueue

#include <map>
#include <set>

#include "copasi/model/CEvent.h"
#include "copasi/utilities/CVector.h"
#include "copasi/math/CMathContainer.h"

class CExpression;
class CMathEventN;

class CMathEventQueue
{
private:
  class CKey
  {
    friend std::ostream &operator<<(std::ostream &os, const CMathEventQueue & o);

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
    /**
     * Possible action item types
     */
    enum Type
    {
      Calculation,
      Assignment
    };

    // Operations
  private:
    /**
     * Default constructor (hidden)
     */
    CAction();

  public:
    /**
     * Constructor
     * @param const CMathEventQueue::CAction::Type & type
     * @param CMathEventN * pEvent
     * @param CMathEventQueue * pProcessQueue
     *
     */
    CAction(const CMathEventQueue::CAction::Type & type,
            CMathEventN * pEvent,
            CMathEventQueue * pProcessQueue);

    /**
     * Copy constructor
     * @param const CAction & src
     */
    CAction(const CAction & src);

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
     * @return CMathEventN * pEvent
     */
    inline CMathEventN * getEvent() const {return mpEvent;}

    friend std::ostream &operator<<(std::ostream &os, const CAction & o);

    // Attributes
  private:
    /**
     * The type of action item
     */
    Type mType;

    /**
     * The new value if the entry is an assignment.
     */
    CVector< C_FLOAT64 > mValues;

    /**
     * A pointer to the priority value
     */
    const C_FLOAT64 * mpPriority;

    /**
     * The event associated with this action
     */
    CMathEventN * mpEvent;

    /**
     * A pointer to the process queue to which a subsequent assignment must be added if
     * the entry is a calculation.
     */
    CMathEventQueue * mpProcessQueue;
  };

  friend std::ostream &operator<<(std::ostream &os, const CAction & o);

  // Type definitions
public:
  typedef std::multimap< CKey, CAction >::iterator iterator;

  typedef std::pair < std::multimap< CKey, CAction >::iterator,
          std::multimap< CKey, CAction >::iterator > range;

  typedef range(*resolveSimultaneousAssignments)(const std::multimap< CKey, CAction > & /* assignments */,
      const C_FLOAT64 & /* time */,
      const bool & /* equality */,
      const size_t & /* cascadingLevel */);

  /**
   * This is the type for an event call back function
   */
  typedef void (*EventCallBack)(void*, CEvent::Type type);

  // Operations
  /**
   * Default constructor
   */
  CMathEventQueue();

public:
  /**
   * Default constructor
   * @param CMathContainer & mathContainer
   */
  CMathEventQueue(CMathContainer & mathContainer);

  /**
   * Destructor
   */
  ~CMathEventQueue();

  /**
   * Start the event queue
   */
  void start();

  /**
   * Add an assignment to the process queue.
   * @param const C_FLOAT64 & executionTime
   * @param const bool & equality
   * @param CMathEventN * pEvent
   * @return bool success
   */
  bool addAssignment(const C_FLOAT64 & executionTime,
                     const bool & equality,
                     CMathEventN * pEvent);

  /**
   * Add a calculation to the process queue.
   * @param const C_FLOAT64 & executionTime
   * @param const bool & equality
   * @param CMathEventN * pEvent
   * @return bool success
   */
  bool addCalculation(const C_FLOAT64 & executionTime,
                      const bool & equality,
                      CMathEventN * pEvent);

  /**
   * Process the queue.
   * @param const bool & priorToOutput
   * @param resolveSimultaneousAssignments pResolveSimultaneousAssignments
   * @return bool stateChanged
   */
  bool process(const bool & priorToOutput,
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

  friend std::ostream &operator<<(std::ostream &os, const CMathEventQueue & o);

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
   * A pointer to the math container the event queue belongs to.
   */
  CMathContainer * mpContainer;

  /**
   * A pointer to the current container time
   */
  const C_FLOAT64 * mpTime;

  /**
   * An ordered list of calculations in the queue.
   */
  std::multimap< CKey, CAction > mCalculations;

  /**
   * An ordered list of assignments in the queue.
   */
  std::multimap< CKey, CAction > mAssignments;

  /**
   * The update sequence which need to be applied to update all roots and total
   * moieties
   */
  CObjectInterface::UpdateSequence mUpdateSequence;

  /**
   * The limit of execution steps allowed for call to process
   */
  size_t mExecutionLimit;

  /**
   * A counter of the execution steps for the current process
   */
  size_t mExecutionCounter;

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

#endif // COPASI_CMathEventQueue
