// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathContainer.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/04/25 12:50:08 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
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
    CMathObject * pEventDelay;
    CMathObject * pEventPriority;
    CMathObject * pEventAssignment;
    CMathObject * pEventTrigger;
    CMathObject * pEventRoot;
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
   * @param std::vector< std::vector< const CEvaluationNode * > > & variables
   * @param const size_t & variableLevel
   * @param const bool & replaceDiscontinuousNodes
   * @return CEvaluationNode * pCopy
   */
  CEvaluationNode * copyBranch(const CEvaluationNode * pSrc,
                               std::vector< std::vector< const CEvaluationNode * > > & variables,
                               const size_t & variableLevel,
                               const bool & replaceDiscontinuousNodes);

  CEvaluationNode * copyBranchX(const CEvaluationNode * pSrc,
                                std::vector< std::vector< const CEvaluationNode * > > & variables,
                                const size_t & variableLevel,
                                const size_t & parameterLevel,
                                const bool & replaceDiscontinuousNodes);

  /**
   * Replace a discontinuous node by an object node pointing to newly created math objects,
   * which are targets of automatically generated events.
   * @param const CEvaluationNode * pSrc
   * @param std::vector< std::vector< const CEvaluationNode * > > & variables
   * @param const size_t & variableLevel
   * @return CEvaluationNode * pCopy
   */
  CEvaluationNode * replaceDiscontinuousNode(const CEvaluationNode * pSrc,
      std::vector< std::vector< const CEvaluationNode * > > & variables,
      const size_t & variableLevel);

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
   * A pointer to the data model which mathematics are contained
   */
  CModel * mpModel;

  CVector< C_FLOAT64 > mValues;

  CVectorCore< C_FLOAT64 > mInitialExtensiveValues;
  CVectorCore< C_FLOAT64 > mInitialIntensiveValues;
  CVectorCore< C_FLOAT64 > mInitialEventTriggers;

  CVectorCore< C_FLOAT64 > mExtensiveValues;
  CVectorCore< C_FLOAT64 > mIntensiveValues;

  CVectorCore< C_FLOAT64 > mExtensiveRates;
  CVectorCore< C_FLOAT64 > mIntensiveRates;

  CVectorCore< C_FLOAT64 > mFluxes;
  CVectorCore< C_FLOAT64 > mPropensities;
  CVectorCore< C_FLOAT64 > mTotalMasses;
  CVectorCore< C_FLOAT64 > mDependentMasses;
  CVectorCore< C_FLOAT64 > mDiscontinuous;
  CVectorCore< C_FLOAT64 > mEventDelays;
  CVectorCore< C_FLOAT64 > mEventPriorities;
  CVectorCore< C_FLOAT64 > mEventAssignments;
  CVectorCore< C_FLOAT64 > mEventTriggers;
  CVectorCore< C_FLOAT64 > mEventRoots;
  CVectorCore< C_FLOAT64 > mEventRootStates;

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

  sDiscontinuous mCreateDiscontinousPointer;

  /**
   * A map from data objects to math objects
   */
  std::map< CCopasiObject *, CMathObject * > mDataObject2MathObject;

  /**
   * A map from data objects values to math objects
   */
  std::map< C_FLOAT64 *, CMathObject * > mDataValue2MathObject;
};

#endif // COPASI_CMathContainer
