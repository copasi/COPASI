// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathContainer.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/29 16:20:16 $
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
  struct sPointers
  {
public:
    C_FLOAT64 * pInitialExtensiveValues;
    C_FLOAT64 * pInitialIntensiveValues;
    C_FLOAT64 * pExtensiveValues;
    C_FLOAT64 * pIntensiveValues;
    C_FLOAT64 * pExtensiveRates;
    C_FLOAT64 * pIntensiveRates;
    C_FLOAT64 * pFluxes;
    C_FLOAT64 * pPropensities;
    C_FLOAT64 * pTotalMasses;
    C_FLOAT64 * pDependentMasses;

    CMathObject * pInitialExtensiveValuesObject;
    CMathObject * pInitialIntensiveValuesObject;
    CMathObject * pExtensiveValuesObject;
    CMathObject * pIntensiveValuesObject;
    CMathObject * pExtensiveRatesObject;
    CMathObject * pIntensiveRatesObject;
    CMathObject * pFluxesObject;
    CMathObject * pPropensitiesObject;
    CMathObject * pTotalMassesObject;
    CMathObject * pDependentMassesObject;
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

private:
  /**
   * Initialize the mathematical model
   */
  void init();

  /**
   * Allocate the memory for objects an values
   */
  void allocate();

  /**
   * Initialize the pointers
   * @param sPointers & pointers
   */
  void initializePointers(sPointers & pointers);

  /**
   * Initialize the objects
   */
  void initializeObjects();

  /**
   * Compile the objects
   */
  bool compileObjects();

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
                             sPointers & pointers);

  /**
   * Initialize several mathematical objects for local reaction parameters and
   * advance relevant pointers
   * @param const std::vector<const CCopasiObject *> & parameters
   * @param CMathContainer::sPointers & p
   */
  void initializeMathObjects(const std::vector<const CCopasiObject *> & parameters,
                             CMathContainer::sPointers & p);

  /**
   * Initialize several mathematical objects for local reaction parameters and
   * advance relevant pointers
   * @param const CCopasiVector< CReaction > & reactions
   * @param CMathContainer::sPointers & p
   */
  void initializeMathObjects(const CCopasiVector< CReaction > & reactions,
                             CMathContainer::sPointers & p);

  /**
   * Initialize several mathematical objects for local reaction parameters and
   * advance relevant pointers
   * @param const CCopasiVector< CMoiety > & moieties
   * @param CMathContainer::sPointers & p
   */
  void initializeMathObjects(const CCopasiVector< CMoiety > & moieties,
                             CMathContainer::sPointers & p);

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
  CVectorCore< C_FLOAT64 > mExtensiveValues;
  CVectorCore< C_FLOAT64 > mIntensiveValues;
  CVectorCore< C_FLOAT64 > mExtensiveRates;
  CVectorCore< C_FLOAT64 > mIntensiveRates;
  CVectorCore< C_FLOAT64 > mFluxes;
  CVectorCore< C_FLOAT64 > mPropensities;
  CVectorCore< C_FLOAT64 > mTotalMasses;
  CVectorCore< C_FLOAT64 > mDependentMassess;

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
   * A map from data objects to math objects
   */
  std::map< CCopasiObject *, CMathObject * > mDataObject2MathObject;

  /**
   * A map from data objects values to math objects
   */
  std::map< C_FLOAT64 *, CMathObject * > mDataValue2MathObject;
};

#endif // COPASI_CMathContainer
