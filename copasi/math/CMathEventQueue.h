// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CMathEventQueue
#define COPASI_CMathEventQueue

#include <map>
#include <set>

#include "copasi/core/CDataObject.h"
#include "copasi/core/CVector.h"
#include "copasi/math/CMathEnum.h"
#include "copasi/math/CMathUpdateSequence.h"

class CExpression;
class CMathEvent;
class CMathContainer;

class CMathEventQueue
{
public:
  class CKey
  {
    friend std::ostream &operator<<(std::ostream &os, const CKey & o);

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
    friend std::ostream &operator<<(std::ostream &os, const CAction & o);

  public:
    /**
     * Possible action item types
     */
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
     * @param CMathEventN * pEvent
     * @param CMathEventQueue * pProcessQueue
     */
    CAction(CMathEvent * pEvent,
            CMathEventQueue * pProcessQueue);

    /**
     * Specific constructor
     * @param const CVector< C_FLOAT64 > & values
     * @param CMathEventN * pEvent
     * @param CMathEventQueue * pProcessQueue
     */
    CAction(const CVector< C_FLOAT64 > & values,
            CMathEvent * pEvent,
            CMathEventQueue * pProcessQueue);

    /**
     * Destructor (hidden)
     */
    ~CAction();

    /**
     * Process the action
     * @return CMath::StateChange stateChanged
     */
    CMath::StateChange process();

    /**
     * Retrieve the event id
     * @return CMathEventN * pEvent
     */
    CMathEvent * getEvent() const;

    /**
     * Retrieve the type of action
     * @return const Type & type
     */
    const Type & getType() const;

    /**
     * Retrieve the priority
     */
    const C_FLOAT64 & getPriority() const;

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
    CMathEvent * mpEvent;

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
  typedef std::multimap< CKey, CAction >::const_iterator const_iterator;

  typedef std::pair < std::multimap< CKey, CAction >::iterator,
          std::multimap< CKey, CAction >::iterator > range;

private:
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
   * @param const CVectorCore< C_FLOAT64 > & values
   * @param CMathEventN * pEvent
   * @return bool success
   */
  bool addAssignment(const C_FLOAT64 & executionTime,
                     const bool & equality,
                     const CVectorCore< C_FLOAT64 > & values,
                     CMathEvent * pEvent);

  /**
   * Add a calculation to the process queue.
   * @param const C_FLOAT64 & executionTime
   * @param const bool & equality
   * @param CMathEventN * pEvent
   * @return bool success
   */
  bool addCalculation(const C_FLOAT64 & executionTime,
                      const bool & equality,
                      CMathEvent * pEvent);

  /**
   * Remove an action from queue
   * @param const std::pair< CMathEventQueue::CKey, CMathEventQueue::CAction > & action
   */
  void removeAction(const std::pair< CMathEventQueue::CKey, CMathEventQueue::CAction > & action);

  /**
   * Process the queue.
   * @param const bool & priorToOutput
   * @return CMath::StateChange stateChange
   */
  CMath::StateChange process(const bool & priorToOutput);

  /**
   * Retrieve the next execution time scheduled in the process queue
   * @return const C_FLOAT64 & processQueueExecutionTime
   */
  const C_FLOAT64 & getProcessQueueExecutionTime() const;

  /**
   * This prints debugging info to stdout
   */
  void printDebug() const {std::cout << *this; };

  friend std::ostream &operator<<(std::ostream &os, const CMathEventQueue & o);

private:
  /**
   * Retrieve the currently pending actions
   * @return CMathEventQueue::iterator itAction
   */
  iterator getAction();

  /**
   * Execute the calculations
   * @param CMathEventQueue::iterator itAction
   * @return CMath::StateChange stateChange
   */
  CMath::StateChange executeAction(CMathEventQueue::iterator itAction);

  /**
   * Check whether the executions of assignment lead to newly found roots
   * @return bool rootsFound
   */
  bool rootsFound();

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
  std::multimap< CKey, CAction > mActions;

  /**
   * The update sequence which need to be applied to update all roots and total
   * moieties
   */
  CCore::CUpdateSequence mUpdateSequence;

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
};

#endif // COPASI_CMathEventQueue
