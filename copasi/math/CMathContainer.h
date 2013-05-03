// Copyright (C) 2011 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CMathContainer
#define COPASI_CMathContainer

#include <map>

#include "copasi/report/CCopasiContainer.h"

#include "copasi/math/CMathObject.h"
#include "copasi/math/CMathEvent.h"
#include "copasi/math/CMathDependencyGraph.h"

#include "copasi/utilities/CVector.h"

class CModel;
class CModelEntity;
class CReaction;
class CMoiety;

template < class CType > class CCopasiVector;

class CMathContainer: public CCopasiContainer
{
private:

  struct sDiscontinuous
  {
  public:
    CMathEventN * pEvent;
    CMathObject * pDiscontinuous;
    /*
    CMathObject * pEventDelay;
    CMathObject * pEventPriority;
    CMathObject * pEventAssignment;
    CMathObject * pEventTrigger;
    CMathObject * pEventRoot;
    */
  };

  /**
   * Default Constructor
   */
  CMathContainer();

public:

  /**
   * Specific Constructor
   * @param CModel & model
   */
  CMathContainer(CModel & model);

  /**
   * Destructor
   */
  virtual ~CMathContainer();

  /**
   * Retrieve the CN of the math container
   * The math container provides values for the numerical values of model objects.
   * For the CN mechanism to work properly it has to pretend to be the model.
   * @return CCopasiObjectName
   */
  virtual CCopasiObjectName getCN() const;

  /**
   * Retrieve a descendant object by its CN.
   * If the
   */
  virtual const CObjectInterface * getObject(const CCopasiObjectName & cn) const;

  /**
   * Retrieve a pointer to corresponding the mathematical object
   * for the given abject if it exists otherwise NULL
   * @param const CObjectInterface * pObject
   * @return CMathObject * pMathObject
   */
  CMathObject * getMathObject(const CObjectInterface * pObject) const;

  /**
   * Retrieve a pointer to the mathematical object for data value pointer
   * @param const C_FLOAT64 * pDataValue
   * @return CMathObject * pMathObject
   */
  CMathObject * getMathObject(const C_FLOAT64 * pDataValue) const;

  /**
   * Retrieve a pointer to the mathematical object for the given CN
   * @param const CCopasiObjectName & cn
   * @return CMathObject * pMathObject
   */
  CMathObject * getMathObject(const CCopasiObjectName & cn) const;

  /**
   * Retrieve the model for the container
   * @return const CModel & model
   */
  const CModel & getModel() const;

  /**
   * Copy a node and all its children. Nodes are converted to suite the math container,
   * i.e., objects nodes point to math object or numbers, function calls are expanded
   * and discrete nodes are replaced by object node pointing to newly created math objects,
   * which are and targets of automatically generated events.
   * @param const CEvaluationNode * pSrc
   * @param const bool & replaceDiscontinuousNodes
   * @return CEvaluationNode * pCopy
   */
  CEvaluationNode * copyBranch(const CEvaluationNode * pSrc,
                               const bool & replaceDiscontinuousNodes);

  /**
   * Copy a node and all its children. Nodes are converted to suite the math container,
   * i.e., objects nodes point to math object or numbers, function calls are expanded
   * and discrete nodes are replaced by object node pointing to newly created math objects,
   * which are and targets of automatically generated events.
   * @param const CEvaluationNode * pSrc
   * @param const CMath::Variables & variables
   * @param const bool & replaceDiscontinuousNodes
   * @return CEvaluationNode * pCopy
   */
  CEvaluationNode * copyBranch(const CEvaluationNode * pSrc,
                               const CMath::Variables< CEvaluationNode * > & variables,
                               const bool & replaceDiscontinuousNodes);

  /**
   * Replace a discontinuous node by an object node pointing to newly created math objects,
   * which are targets of automatically generated events.
   * @param const CEvaluationNode * pSrc
   * @param const std::vector< CEvaluationNode * > & children
   * @return CEvaluationNode * pCopy
   */
  CEvaluationNode * replaceDiscontinuousNode(const CEvaluationNode * pSrc,
      const std::vector< CEvaluationNode * > & children);

  /**
   * Retrieve the pointer to the corresponding initial value
   * @param const C_FLOAT64 * pValue
   * @return C_FLOAT64 * pInitialvalue
   */
  C_FLOAT64 * getInitialValuePointer(const C_FLOAT64 * pValue) const;

private:
  /**
   * Initialize the mathematical model
   */
  void init();

  /**
   * Allocate the memory for objects and values
   */
  void allocate();

  /**
   * Initialize the pointers
   * @param sPointers & pointers
   */
  void initializePointers(CMath::sPointers & pointers);

#ifdef COPASI_DEBUG
  /**
   * Print pointer state
   * @param sPointers & pointers
   */
  void printPointers(CMath::sPointers & pointers);
#endif // COAPSI_DEBUG

  /**
   * Initialize the pointers used for the conversion of
   * discontinuous nodes.
   */
  void initializeDiscontinuousCreationPointer();

  /**
   * Initialize the objects
   * @param sPointers & pointers
   */
  void initializeObjects(CMath::sPointers & pointers);

  /**
   * Initialize the events
   * @param sPointers & pointers
   */
  void initializeEvents(CMath::sPointers & pointers);

  /**
   * Compile the objects
   */
  bool compileObjects();

  /**
   * Compile the events
   */
  bool compileEvents();

  /**
   * Convert nodes which generate discrete changes into events
   * and compiles them.
   */
  bool compileDiscreteChanges();

  /**
   * Create a node based on the given pointer to the math object
   * @param const CObjectInterface * pMathObject
   * @return CEvaluationNode * pNode
   */
  CEvaluationNode * createNodeFromObject(const CObjectInterface * pMathObject);

  /**
   * Create a node based on the given pointer to a data value
   * @param const C_FLOAT64 * pDataValue
   * @return CEvaluationNode * pNode
   */
  CEvaluationNode * createNodeFromValue(const C_FLOAT64 * pDataValue);

  /**
   * Create Dependency Graphs
   */
  void createDependencyGraphs();

  /**
   * Determine the entity type of an entity
   * @param const CModelEntity * pEntity
   * @return CMath::EntityType entityType
   */
  static CMath::EntityType getEntityType(const CModelEntity * pEntity);

  /**
   * Initialize several mathematical objects of a common simulation type and
   * advance relevant pointers
   * @param const std::vector<const CModelEntity*> & entities
   * @param const CMath::SimulationType & simulationType
   * @param sPointers & pointers
   */
  void initializeMathObjects(const std::vector<const CModelEntity*> & entities,
                             const CMath::SimulationType & simulationType,
                             CMath::sPointers & pointers);

  /**
   * Initialize several mathematical objects for local reaction parameters and
   * advance relevant pointers
   * @param const std::vector<const CCopasiObject *> & parameters
   * @param CMathContainer::sPointers & p
   */
  void initializeMathObjects(const std::vector<const CCopasiObject *> & parameters,
                             CMath::sPointers & p);

  /**
   * Initialize several mathematical objects for local reaction parameters and
   * advance relevant pointers
   * @param const CCopasiVector< CReaction > & reactions
   * @param CMathContainer::sPointers & p
   */
  void initializeMathObjects(const CCopasiVector< CReaction > & reactions,
                             CMath::sPointers & p);

  /**
   * Initialize several mathematical objects for local reaction parameters and
   * advance relevant pointers
   * @param const CCopasiVector< CMoiety > & moieties
   * @param CMathContainer::sPointers & p
   */
  void initializeMathObjects(const CCopasiVector< CMoiety > & moieties,
                             CMath::sPointers & p);

  /**
   * Determine whether on object has calculation dependencies.
   */
  static bool hasDependencies(const CCopasiObject * pObject);

  /**
   * Map the data object to the math object
   * @param CCopasiObject * pDataObject
   * @param CMathObject * pMathObject
   */
  void map(CCopasiObject * pDataObject, CMathObject * pMathObject);

  /**
   * Create an event of type CEvent::Discontinuity for each discontinuity in the model
   */
  void createDiscontinuityEvents();

  /**
   * Create an event of type CEvent::Discontinuity for each discontinuity the tree with root pNode
   * @param const CEvaluationNode * pNode
   * @param const CMath::Variables< CEvaluationNode * > & variables
   */
  void createDiscontinuityEvents(const CEvaluationNode * pNode,
                                 const CMath::Variables< CEvaluationNode * > & variables);

  /**
   * Create an event of type CEvent::Discontinuity for the given node
   * @param const CEvaluationNode * pNode
   */
  void createDiscontinuityDataEvent(const CEvaluationNode * pNode);

  /**
   * Create the infix for trigger of the event which tracks changes in a discontinuity
   * represented by the node.
   * @param const CEvaluationNode * pNode
   */
  std::string createDiscontinuityTriggerInfix(const CEvaluationNode * pNode);

  /**
   * A pointer to the data model which mathematics are contained
   */
  CModel * mpModel;
  const CObjectInterface * mpAvogadro;
  const CObjectInterface * mpQuantity2NumberFactor;

  CVector< C_FLOAT64 > mValues;

  CVectorCore< C_FLOAT64 > mInitialExtensiveValues;
  CVectorCore< C_FLOAT64 > mInitialIntensiveValues;
  CVectorCore< C_FLOAT64 > mInitialExtensiveRates;
  CVectorCore< C_FLOAT64 > mInitialIntensiveRates;
  CVectorCore< C_FLOAT64 > mInitialParticleFluxes;
  CVectorCore< C_FLOAT64 > mInitialFluxes;
  CVectorCore< C_FLOAT64 > mInitialTotalMasses;
  CVectorCore< C_FLOAT64 > mInitialEventTriggers;

  CVectorCore< C_FLOAT64 > mExtensiveValues;
  CVectorCore< C_FLOAT64 > mIntensiveValues;
  CVectorCore< C_FLOAT64 > mExtensiveRates;
  CVectorCore< C_FLOAT64 > mIntensiveRates;
  CVectorCore< C_FLOAT64 > mParticleFluxes;
  CVectorCore< C_FLOAT64 > mFluxes;
  CVectorCore< C_FLOAT64 > mTotalMasses;
  CVectorCore< C_FLOAT64 > mEventTriggers;

  CVectorCore< C_FLOAT64 > mEventDelays;
  CVectorCore< C_FLOAT64 > mEventPriorities;
  CVectorCore< C_FLOAT64 > mEventAssignments;
  CVectorCore< C_FLOAT64 > mEventRoots;
  CVectorCore< C_FLOAT64 > mEventRootStates;
  CVectorCore< C_FLOAT64 > mPropensities;
  CVectorCore< C_FLOAT64 > mDependentMasses;
  CVectorCore< C_FLOAT64 > mDiscontinuous;

  /**
   * Dependency graph for initial value calculations
   */
  CMathDependencyGraph mInitialDependencies;

  /**
   * Dependency graph for transient value calculations
   */
  CMathDependencyGraph mTransientDependencies;

  /**
   * A vector containing all math objects.
   */
  CVector< CMathObject > mObjects;

  /**
   * A vector containing all math events.
   */
  CVector< CMathEventN > mEvents;

  sDiscontinuous mCreateDiscontinuousPointer;

  /**
   * A map from data objects to math objects
   */
  std::map< CCopasiObject *, CMathObject * > mDataObject2MathObject;

  /**
   * A map from data objects values to math objects
   */
  std::map< C_FLOAT64 *, CMathObject * > mDataValue2MathObject;

  /**
   * A vector of data events for discontinuities
   */
  CCopasiVector< CEvent > mDiscontinuityEvents;

  /**
   * A map from the infix of the expression of a discontinuity to the object
   * representing it.
   */
  std::map< std::string, CMathObject * > mDiscontinuityInfix2Object;

  /**
   * A map from the discontinuity trigger infix of to event
   * representing it.
   */
  std::map< std::string,  CMathEventN * > mTriggerInfix2Event;
};

#endif // COPASI_CMathContainer
