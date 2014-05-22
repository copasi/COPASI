// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CMathEvent
#define COPASI_CMathEvent

#include "copasi/model/CEvent.h"
#include "copasi/math/CMathTrigger.h"
#include "copasi/math/CMathEventQueue.h"

#include "copasi/function/CExpression.h"
#include "copasi/utilities/CVector.h"

class CMathContainer;
class CMathObject;

class CMathEvent
{
public:
  class CAssignment
  {
  public:
    /**
     * Default constructor
     */
    CAssignment();

    /**
     * Destructor
     */
    ~CAssignment();

    void initialize(CMath::sPointers & pointers);

    /**
     * Copy an existing object
     * @param const CAssignment & src
     * @param CMathContainer & container
     * @param const size_t & valueOffset
     * @param const size_t & objectOffset
     */
    void copy(const CAssignment & src, CMathContainer & container, const size_t & valueOffset, const size_t & objectOffset);

    bool compile(CEventAssignment * pDataAssignment,
                 CMathContainer & container);

    void setTarget(CMathObject * pTarget);

    const CMathObject * getTarget() const;

    void setAssignment(CMathObject * pAssignment);

    const CMathObject * getAssignment() const;

  private:
    CMathObject * mpTarget;
    CMathObject * mpAssignment;
  };

  class CTrigger
  {
  public:
    class CRootProcessor
    {
    public:
      /**
       * Default constructor
       */
      CRootProcessor();

      /**
       * Destructor
       */
      ~CRootProcessor();

      /**
       * Toggle the root status dependent on the
       * processed equality status
       * @param const C_FLOAT64 & time
       * @param const bool & equality
       * @param const bool & continuous
       */
      void toggle(const C_FLOAT64 & time,
                  const bool & equality);

      /**
       * Toggle the root status dependent on the
       * processed equality status
       * @param const C_FLOAT64 & time
       */
      void toggle(const C_FLOAT64 & time);

      /**
       * Check whether the root needs to be checked for equality;
       * @return const bool & isEquality
       */
      const bool & isEquality() const;

      /**
       * Initialize all values of the root processor.
       */
      void applyInitialValues();

      /**
       * Determine the truth value for the current root.
       */
      void calculateTrueValue();

      /**
       * Check whether the root state is true
       * @return bool isTrue
       */
      bool isTrue() const;

      void initialize(CMath::sPointers & pointers);

      /**
       * Copy an existing object
       * @param const CRootProcessor & src
       * @param CMathContainer & container
       * @param const size_t & valueOffset
       * @param const size_t & objectOffset
       */
      void copy(const CRootProcessor & src, CMathContainer & container, const size_t & valueOffset, const size_t & objectOffset);

      bool compile(CEvaluationNode * pRootNode,
                   const bool & equality,
                   CMathContainer & container);

      CEvaluationNode * createTriggerExpressionNode() const;

    public:
      CMathObject * mpRoot;
      CMathObject * mpRootState;
      bool mEquality;
      bool mDiscrete;
      C_FLOAT64 mLastToggleTime;
      C_FLOAT64 * mpRootValue;
      C_FLOAT64 * mpRootStateValue;
    };

    /**
     * Default constructor
     */
    CTrigger();

    /**
     * Destructor
     */
    ~CTrigger();

    void allocate(const CEvent * pDataEvent,
                  const CMathContainer & container);

    void allocateDiscontinuous(const size_t & nRoots,
                               const CMathContainer & container);

    /**
     * Check whether the root state is true
     * @return bool isTrue
     */
    bool isTrue() const;

    void initialize(CMath::sPointers & pointers);

    /**
     * Copy an existing object
     * @param const CTrigger & src
     * @param CMathContainer & container
     * @param const size_t & valueOffset
     * @param const size_t & objectOffset
     */
    void copy(const CTrigger & src, CMathContainer & container, const size_t & valueOffset, const size_t & objectOffset);

    bool compile(CEvent * pDataEvent,
                 CMathContainer & container);

    const CVector< CRootProcessor > & getRoots() const;

    /**
     * Set the trigger expression
     * @param const std::string & infix
     * @param CMathContainer & container
     */
    void setExpression(const std::string & infix, CMathContainer & container);

  private:
    static size_t countRoots(const CEvaluationNode * pNode,
                             const CMath::Variables< size_t > & variables);

    static size_t countRootsDefault(const std::vector< size_t > & children);

    static size_t countRootsEQ(const CEvaluationNode * pNode,
                               const std::vector< size_t > & children);

    static size_t countRootsFUNCTION(const CEvaluationNode * pNode,
                                     const std::vector< size_t > & children);

    static size_t countRootsVARIABLE(const CEvaluationNode * pNode,
                                     const CMath::Variables< size_t > & variables);

    static CEvaluationNode * compile(const CEvaluationNode * pNode,
                                     const CMath::Variables< CEvaluationNode * > & variables,
                                     CMathEvent::CTrigger::CRootProcessor *& pRoot,
                                     CMathContainer & container);

    static CEvaluationNode * compileAND(const CEvaluationNode * pNode,
                                        const std::vector< CEvaluationNode * > & children,
                                        const CMath::Variables< CEvaluationNode * > & variables,
                                        CMathEvent::CTrigger::CRootProcessor *& pRoot,
                                        CMathContainer & container);

    static CEvaluationNode * compileEQ(const CEvaluationNode * pNode,
                                       const std::vector< CEvaluationNode * > & children,
                                       const CMath::Variables< CEvaluationNode * > & variables,
                                       CMathEvent::CTrigger::CRootProcessor *& pRoot,
                                       CMathContainer & container);

    static CEvaluationNode * compileNE(const CEvaluationNode * pNode,
                                       const std::vector< CEvaluationNode * > & children,
                                       const CMath::Variables< CEvaluationNode * > & variables,
                                       CMathEvent::CTrigger::CRootProcessor *& pRoot,
                                       CMathContainer & container);

    static CEvaluationNode * compileLE(const CEvaluationNode * pNode,
                                       const std::vector< CEvaluationNode * > & children,
                                       const CMath::Variables< CEvaluationNode * > & variables,
                                       CMathEvent::CTrigger::CRootProcessor *& pRoot,
                                       CMathContainer & container);

    static CEvaluationNode * compileNOT(const CEvaluationNode * pNode,
                                        const std::vector< CEvaluationNode * > & children,
                                        const CMath::Variables< CEvaluationNode * > & variables,
                                        CMathEvent::CTrigger::CRootProcessor *& pRoot,
                                        CMathContainer & container);

    static CEvaluationNode * compileFUNCTION(const CEvaluationNode * pNode,
        const std::vector< CEvaluationNode * > & children,
        const CMath::Variables< CEvaluationNode * > & variables,
        CMathEvent::CTrigger::CRootProcessor *& pRoot,
        CMathContainer & container);

    static CEvaluationNode * compileVARIABLE(const CEvaluationNode * pNode,
        const std::vector< CEvaluationNode * > & children,
        const CMath::Variables< CEvaluationNode * > & variables,
        CMathEvent::CTrigger::CRootProcessor *& pRoot,
        CMathContainer & container);

    CMathObject * mpTrigger;
    CMathObject * mpInitialTrigger;
    CVector< CRootProcessor > mRoots;
    bool mDualAction;
  };

  /**
   * Default constructor
   */
  CMathEvent();

  /**
   * Destructor
   */
  ~CMathEvent();

  static void allocate(CMathEvent * pEvent,
                       const CEvent * pDataEvent,
                       const CMathContainer & container);

  void initialize(CMath::sPointers & pointers);

  /**
   * Copy an existing object
   * @param const CMathEventN & src
   * @param CMathContainer & container
   * @param const size_t & valueOffset
   * @param const size_t & objectOffset
   */
  void copy(const CMathEvent & src, CMathContainer & container, const size_t & valueOffset, const size_t & objectOffset);

  bool compile(CEvent * pDataEvent,
               CMathContainer & container);

  /**
   * Create the update sequences required for event processing.
   */
  void createUpdateSequences();

  /**
   * The event fires and the appropriate actions are scheduled
   * in the process queue.
   * @param const bool & equality
   */
  void fire(const bool & equality);

  /**
   * Add a pending action to the event;
   * @param const CMathEventQueue::iterator & pendingAction
   */
  void addPendingAction(const CMathEventQueue::iterator & pendingAction);

  /**
   * Remove the pending action to the event;
   */
  void removePendingAction();

  /**
   * Calculate and retrieve the new target values
   * @return const CVectorCore< C_FLOAT64 > & targetValues
   */
  const CVectorCore< C_FLOAT64 > & getTargetValues();

  /**
   * Set the target values
   * @param const CVectorCore< C_FLOAT64 > & targetValues
   * @return CMath::StateChange stateChanged
   */
  CMath::StateChange setTargetValues(const CVectorCore< C_FLOAT64 > & targetValues);

  /**
   * Calculate and assign the new target values
   * @return CMath::StateChange stateChanged
   */
  CMath::StateChange executeAssignment();

  /**
   * Check whether to delay the assignment
   * @return const bool & delayAssignment
   */
  const bool & delayAssignment() const;

  /**
   * Check whether the event may fire at initial time.
   * @return const bool & fireAtInitialTime
   */
  const bool & fireAtInitialTime() const;

  /**
   * Set the trigger expression
   * @param const std::string & infix
   * @param CMathContainer & container
   */
  void setTriggerExpression(const std::string & infix, CMathContainer & container);

  /**
   * Set the delay expression
   * @param const std::string & infix
   * @param CMathContainer & container
   */
  void setDelayExpression(const std::string & infix, CMathContainer & container);

  /**
   * Set the priority expression
   * @param const std::string & infix
   * @param CMathContainer & container
   */
  void setPriorityExpression(const std::string & infix, CMathContainer & container);

  /**
   * Add an assignment
   * @param CMathObject * pTarget
   * @param CMathObject * pExpression
   */
  void addAssignment(CMathObject * pTarget, CMathObject * pExpression);

  const CTrigger & getTrigger() const;

  const CVector< CAssignment > & getAssignments() const;

  const CMathObject * getPriority() const;

  /**
   * Retrieve the time for calculating the assignment expression
   * @return C_FLOAT64 calculationTime
   */
  C_FLOAT64 getCalculationTime() const;

  /**
   * Retrieve the time for executing the assignmentS
   * @return C_FLOAT64 executionTime
   */
  C_FLOAT64 getExecutionTime() const;

  /**
   * Retrieve the type of the event
   * @return const CEvent::Type & type
   */
  const CEvent::Type & getType() const;

  void setCallback(CCallbackInterface * pCallback);

  void executeCallback(void * pCaller = NULL);

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
   * The type of the event.
   */
  CEvent::Type mType;

  /**
   * The trigger expression.
   */
  CTrigger mTrigger;

  /**
   * The assignments.
   */
  CVector< CAssignment > mAssignments;

  /**
   * A pointer to the delay object.
   */
  CMathObject * mpDelay;

  /**
   * A pointer to the priority object.
   */
  CMathObject * mpPriority;

  /**
   * A pointer to an optional callback
   */
  CCallbackInterface * mpCallback;

  /**
   * Vector reference of target Values
   */
  CVectorCore< C_FLOAT64 > mTargetValues;

  /**
   * Vector of pointers to targets
   */
  CVector< C_FLOAT64 * > mTargetPointers;

  /**
   * Flag indicating whether the event effects the discrete and/or the continuous state values.
   */
  CMath::StateChange mEffectsSimulation;

  /**
   * The update sequence executed prior to creating calculation actions.
   */
  CObjectInterface::UpdateSequence mCreateCalculationActionSequence;

  /**
   * The update sequence executed prior to creating assignment actions.
   */
  CObjectInterface::UpdateSequence mTargetValuesSequence;

  /**
   * The update sequence executed after the new values are assigned to update the state.
   */
  CObjectInterface::UpdateSequence mPostAssignmentSequence;

  /**
   * A Boolean flag indicating whether the event may fire at the initial time.
   */
  bool mFireAtInitialTime;

  /**
   * A Boolean flag indicating whether the trigger expression must remain true between
   * trigger phase and assignment phase (mPersitenTrigger = false).
   */
  bool mPersistentTrigger;

  /**
   * A Boolean flag indicating whether to delay assignment phase or calculation phase.
   */
  bool mDelayAssignment;

  /**
   * A pointer to the currently pending actions for used for persistent triggers
   */
  std::pair< CMathEventQueue::CKey, CMathEventQueue::CAction > * mpPendingAction;
};

#endif // COPASI_CMathEvent
