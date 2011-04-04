// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathContainer.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/04/04 13:24:50 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CMathContainer.h"

#include "model/CModel.h"
#include "model/CCompartment.h"
#include "model/CMetab.h"
#include "model/CModelValue.h"
#include "model/CObjectLists.h"
#include "CopasiDataModel/CCopasiDataModel.h"

CMathContainer::CMathContainer():
    CCopasiContainer("Math Container", NULL, "CMathContainer"),
    mpModel(NULL),
    mValues(),
    mInitialExtensiveValues(),
    mInitialIntensiveValues(),
    mExtensiveValues(),
    mIntensiveValues(),
    mExtensiveRates(),
    mIntensiveRates(),
    mFluxes(),
    mPropensities(),
    mTotalMasses(),
    mDependentMasses(),
    mInitialDependencies(),
    mTransientDependencies(),
    mObjects(),
    mEvents(),
    mDataObject2MathObject(),
    mDataValue2MathObject()
{}

CMathContainer::CMathContainer(CModel & model):
    CCopasiContainer("Math Container", NULL, "CMathContainer"),
    mpModel(&model),
    mValues(),
    mInitialExtensiveValues(),
    mInitialIntensiveValues(),
    mExtensiveValues(),
    mIntensiveValues(),
    mExtensiveRates(),
    mIntensiveRates(),
    mFluxes(),
    mPropensities(),
    mTotalMasses(),
    mDependentMasses(),
    mInitialDependencies(),
    mTransientDependencies(),
    mObjects(),
    mEvents(),
    mDataObject2MathObject(),
    mDataValue2MathObject()
{
  init();
}

CMathContainer::~CMathContainer()
{}

// virtual
CCopasiObjectName CMathContainer::getCN() const
{
  return mpModel->getCN();
}

// virtual
const CObjectInterface * CMathContainer::getObject(const CCopasiObjectName & cn) const
{
  std::vector< CCopasiContainer * > ListOfContainer;
  ListOfContainer.push_back(mpModel);

  const CObjectInterface * pObject =
    mpModel->getObjectDataModel()->ObjectFromCN(ListOfContainer, cn);
  const CMathObject * pMathObject = getMathObject(pObject);

  if (pMathObject != NULL)
    {
      return pMathObject;
    }

  return pObject;
}

CMathObject * CMathContainer::getMathObject(const CObjectInterface * pObject) const
{
  if (pObject == NULL)
    return NULL;

  std::map< CCopasiObject *, CMathObject * >::const_iterator found =
    mDataObject2MathObject.find(const_cast<CCopasiObject*>(static_cast< const CCopasiObject * >(pObject)));

  if (found != mDataObject2MathObject.end())
    {
      return found->second;
    }

  return NULL;
}

CMathObject * CMathContainer::getMathObject(const C_FLOAT64 * pDataValue) const
{
  if (pDataValue == NULL)
    return NULL;

  std::map< C_FLOAT64 *, CMathObject * >::const_iterator found =
    mDataValue2MathObject.find(const_cast< C_FLOAT64 * >(pDataValue));

  if (found != mDataValue2MathObject.end())
    {
      return found->second;
    }

  return NULL;
}


CMathObject * CMathContainer::getMathObject(const CCopasiObjectName & cn) const
{
  return getMathObject(mpModel->getObject(cn));
}

void CMathContainer::init()
{
  allocate();

  sPointers Pointers;
  initializePointers(Pointers);

  initializeObjects(Pointers);

  // TODO CRITICAL Add events
  initializeEvents(Pointers);

  compileObjects();

  createDependencyGraphs();
}

const CModel & CMathContainer::getModel() const
{
  return *mpModel;
}

void CMathContainer::allocate()
{
  size_t nLocalReactionParameters =
    CObjectLists::getListOfConstObjects(CObjectLists::ALL_LOCAL_PARAMETER_VALUES, mpModel).size();
  size_t nExtensiveValues =  mpModel->getStateTemplate().size() + nLocalReactionParameters;
  size_t nIntensiveValues = mpModel->getNumMetabs();

  size_t nReactions = mpModel->getReactions().size();
  size_t nMoieties = mpModel->getMoieties().size();

  // TODO CRITICAL Determine the space requirements for events.
  const CCopasiVector< CEvent > & Events = mpModel->getEvents();
  CCopasiVector< CEvent >::const_iterator itEvents;
  CCopasiVector< CEvent >::const_iterator endEvents = Events.end();

  size_t nEvents = Events.size();
  size_t nEventAssignments = 0;
  size_t nEventRoots = 0;

  mEvents.resize(nEvents);
  CMathEventN * pEvents = mEvents.array();

  for (; itEvents != endEvents; ++itEvents, ++pEvents)
    {
      CMathEventN::initialize(pEvents, *itEvents, *this);

      nEventAssignments += pEvents->getAssignments().size();
      nEventRoots += pEvents->getTrigger().getRoots().size();
    }

  mValues.resize(3 *(nExtensiveValues + nIntensiveValues) +
                 2 *(nReactions + nMoieties) +
                 4 * nEvents + nEventAssignments + nEventRoots);
  mValues = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

  C_FLOAT64 * pArray = mValues.array();
  mInitialExtensiveValues = CVectorCore< C_FLOAT64 >(nExtensiveValues, pArray);
  pArray += nExtensiveValues;
  mInitialIntensiveValues = CVectorCore< C_FLOAT64 >(nIntensiveValues, pArray);
  pArray += nIntensiveValues;
  mInitialEventTriggers = CVectorCore< C_FLOAT64 >(nEvents, pArray);
  pArray += nEvents;

  mExtensiveValues = CVectorCore< C_FLOAT64 >(nExtensiveValues, pArray);
  pArray += nExtensiveValues;
  mIntensiveValues = CVectorCore< C_FLOAT64 >(nIntensiveValues, pArray);
  pArray += nIntensiveValues;

  mExtensiveRates = CVectorCore< C_FLOAT64 >(nExtensiveValues, pArray);
  pArray += nExtensiveValues;
  mIntensiveRates = CVectorCore< C_FLOAT64 >(nIntensiveValues, pArray);
  pArray += nIntensiveValues;

  mFluxes = CVectorCore< C_FLOAT64 >(nReactions, pArray);
  pArray += nReactions;
  mPropensities = CVectorCore< C_FLOAT64 >(nReactions, pArray);
  pArray += nReactions;
  mTotalMasses = CVectorCore< C_FLOAT64 >(nMoieties, pArray);
  pArray += nMoieties;
  mDependentMasses = CVectorCore< C_FLOAT64 >(nMoieties, pArray);
  pArray += nMoieties;
  mEventDelays = CVectorCore< C_FLOAT64 >(nEvents, pArray);
  pArray += nEvents;
  mEventPriorities = CVectorCore< C_FLOAT64 >(nEvents, pArray);
  pArray += nEvents;
  mEventAssignments = CVectorCore< C_FLOAT64 >(nEventAssignments, pArray);
  pArray += nEventAssignments;
  mEventTriggers = CVectorCore< C_FLOAT64 >(nEvents, pArray);
  pArray += nEvents;
  mEventRoots = CVectorCore< C_FLOAT64 >(nEventRoots, pArray);
  pArray += nEventRoots;

  assert(pArray == mValues.array() + mValues.size());

  mObjects.resize(mValues.size());
}

void CMathContainer::initializeObjects(CMathContainer::sPointers & p)
{
  std::set< const CModelEntity * > EventTargets = CObjectLists::getEventTargets(mpModel);

  std::vector< const CModelEntity * > FixedEntities;
  std::vector< const CModelEntity * > FixedEventTargetEntities;

  const CStateTemplate & StateTemplate = mpModel->getStateTemplate();

  // Determine which fixed entities are modified by events and which not.
  CModelEntity *const* ppEntities = StateTemplate.beginFixed();
  CModelEntity *const* ppEntitiesEnd = StateTemplate.endFixed();

  for (; ppEntities != ppEntitiesEnd; ++ppEntities)
    {
      if ((*ppEntities)->getStatus() == CModelEntity::ASSIGNMENT)
        continue;

      if (EventTargets.find(*ppEntities) == EventTargets.end())
        {
          FixedEntities.push_back(*ppEntities);
        }
      else
        {
          FixedEventTargetEntities.push_back(*ppEntities);
        }
    }

  // Process fixed entities which are not event targets.
  initializeMathObjects(FixedEntities, CMath::Fixed, p);

  // Process local reaction parameters
  std::vector<const CCopasiObject*> LocalReactionParameter =
    CObjectLists::getListOfConstObjects(CObjectLists::ALL_LOCAL_PARAMETER_VALUES, mpModel);
  initializeMathObjects(LocalReactionParameter, p);

  // Process fixed entities which are event targets.
  initializeMathObjects(FixedEventTargetEntities, CMath::EventTarget, p);

  // The simulation time
  // Extensive Initial Value
  map(mpModel->getInitialValueReference(), p.pInitialExtensiveValuesObject);
  CMathObject::initialize(p.pInitialExtensiveValuesObject, p.pInitialExtensiveValues,
                          CMath::Value, CMath::Model, CMath::Time, false, true,
                          mpModel->getInitialValueReference());

  // Extensive Value
  map(mpModel->getValueReference(), p.pExtensiveValuesObject);
  CMathObject::initialize(p.pExtensiveValuesObject, p.pExtensiveValues,
                          CMath::Value, CMath::Model, CMath::Time, false, false,
                          mpModel->getValueReference());

  // Extensive Rate
  map(mpModel->getRateReference(), p.pExtensiveRatesObject);
  CMathObject::initialize(p.pExtensiveRatesObject, p.pExtensiveRates,
                          CMath::ValueRate, CMath::Model, CMath::Time, false, false,
                          mpModel->getRateReference());

  // Process entities which are determined by ODEs
  std::vector< const CModelEntity * > ODEEntities;

  ppEntities = StateTemplate.beginIndependent();
  ppEntitiesEnd = StateTemplate.endIndependent();

  for (; ppEntities != ppEntitiesEnd && (*ppEntities)->getStatus() == CModelEntity::ODE; ++ppEntities)
    {
      ODEEntities.push_back(*ppEntities);
    }

  initializeMathObjects(ODEEntities, CMath::ODE, p);

  // Process independent species
  std::vector< const CModelEntity * > IndependentSpecies;

  ppEntities = StateTemplate.beginIndependent();
  ppEntitiesEnd = StateTemplate.endIndependent();

  for (; ppEntities != ppEntitiesEnd; ++ppEntities)
    {
      if ((*ppEntities)->getStatus() != CModelEntity::REACTIONS)
        continue;

      IndependentSpecies.push_back(*ppEntities);
    }

  initializeMathObjects(IndependentSpecies, CMath::Independent, p);

  // Process dependent species
  std::vector< const CModelEntity * > DependentSpecies;

  ppEntities = StateTemplate.beginDependent();
  ppEntitiesEnd = StateTemplate.endDependent();

  for (; ppEntities != ppEntitiesEnd && (*ppEntities)->getStatus() == CModelEntity::REACTIONS; ++ppEntities)
    {
      DependentSpecies.push_back(*ppEntities);
    }

  initializeMathObjects(DependentSpecies, CMath::Dependent, p);

  // Process entities which are determined by assignments
  std::vector< const CModelEntity * > AssignmentEntities;

  // We continue with the pointer ppEntities
  ppEntitiesEnd = StateTemplate.endFixed();

  for (; ppEntities != ppEntitiesEnd && (*ppEntities)->getStatus() == CModelEntity::ASSIGNMENT; ++ppEntities)
    {
      AssignmentEntities.push_back(*ppEntities);
    }

  initializeMathObjects(AssignmentEntities, CMath::Assignment, p);

  // Process Reactions
  initializeMathObjects(mpModel->getReactions(), p);

  // Process Moieties
  initializeMathObjects(mpModel->getMoieties(), p);
}

void CMathContainer::initializeEvents(CMathContainer::sPointers & p)
{
}

bool CMathContainer::compileObjects()
{
  bool success = true;

  CMathObject *pObject = mObjects.array();
  CMathObject *pObjectEnd = pObject + mObjects.size();

  for (; pObject != pObjectEnd; ++pObject)
    {
      success &= pObject->compile(*this);
    }

  return success;
}

void CMathContainer::createDependencyGraphs()
{
  CMathObject *pObject = mObjects.array();
  CMathObject *pObjectEnd = pObject + mInitialExtensiveValues.size() + mInitialIntensiveValues.size();

  for (; pObject != pObjectEnd; ++pObject)
    {
      mInitialDependencies.addObject(pObject);
    }

  pObjectEnd = mObjects.array() + mObjects.size();
  {
    mTransientDependencies.addObject(pObject);
  }

  return;
}

void CMathContainer::initializePointers(CMathContainer::sPointers & p)
{
  p.pInitialExtensiveValues = mInitialExtensiveValues.array();
  p.pInitialIntensiveValues = mInitialIntensiveValues.array();
  p.pInitialEventTriggers = mInitialEventTriggers.array();

  p.pExtensiveValues = mExtensiveValues.array();
  p.pIntensiveValues = mIntensiveValues.array();

  p.pExtensiveRates = mExtensiveRates.array();
  p.pIntensiveRates = mIntensiveRates.array();

  p.pFluxes = mFluxes.array();
  p.pPropensities = mPropensities.array();
  p.pTotalMasses = mTotalMasses.array();
  p.pDependentMasses = mDependentMasses.array();
  p.pEventDelays = mEventDelays.array();;
  p.pEventPriorities = mEventPriorities.array();;
  p.pEventAssignments = mEventAssignments.array();;
  p.pEventTriggers = mEventTriggers.array();;
  p.pEventRoots = mEventRoots.array();;

  C_FLOAT64 * pValues = mValues.array();
  CMathObject * pObjects = mObjects.array();

  p.pInitialExtensiveValuesObject = pObjects + (p.pInitialExtensiveValues - pValues);
  p.pInitialIntensiveValuesObject = pObjects + (p.pInitialIntensiveValues - pValues);
  p.pInitialEventTriggersObject = pObjects + (p.pInitialEventTriggers - pValues);

  p.pExtensiveValuesObject = pObjects + (p.pExtensiveValues - pValues);
  p.pIntensiveValuesObject = pObjects + (p.pIntensiveValues - pValues);

  p.pExtensiveRatesObject = pObjects + (p.pExtensiveRates - pValues);
  p.pIntensiveRatesObject = pObjects + (p.pIntensiveRates - pValues);

  p.pFluxesObject = pObjects + (p.pFluxes - pValues);
  p.pPropensitiesObject = pObjects + (p.pPropensities - pValues);
  p.pTotalMassesObject = pObjects + (p.pTotalMasses - pValues);
  p.pDependentMassesObject = pObjects + (p.pDependentMasses - pValues);
  p.pEventDelaysObject = pObjects + (p.pEventDelays - pValues);;
  p.pEventPrioritiesObject = pObjects + (p.pEventPriorities - pValues);;
  p.pEventAssignmentsObject = pObjects + (p.pEventAssignments - pValues);;
  p.pEventTriggersObject = pObjects + (p.pEventTriggers - pValues);;
  p.pEventRootsObject = pObjects + (p.pEventRoots - pValues);;
}

// static
CMath::EntityType CMathContainer::getEntityType(const CModelEntity * pEntity)
{
  const CMetab * pSpecies = dynamic_cast< const CMetab * >(pEntity);

  if (pSpecies != NULL)
    {
      return CMath::Species;
    }
  else if (dynamic_cast< const CCompartment * >(pEntity) != NULL)
    {
      return CMath::Compartment;
    }
  else if (dynamic_cast< const CModelValue * >(pEntity) != NULL)
    {
      return CMath::GlobalQuantity;
    }

  return CMath::EntityTypeUndefined;
}

void CMathContainer::initializeMathObjects(const std::vector<const CModelEntity*> & entities,
    const CMath::SimulationType & simulationType,
    CMathContainer::sPointers & p)
{
  // Process entities.
  std::vector<const CModelEntity*>::const_iterator it = entities.begin();
  std::vector<const CModelEntity*>::const_iterator end = entities.end();

  CMath::EntityType EntityType;

  for (; it != end; ++it)
    {
      EntityType = getEntityType(*it);

      // Extensive Initial Value

      // The simulation type for initial values is either CMath::Assignment or CMath::Fixed
      // We must check whether the initial value must be calculated, i.e., whether it has
      // dependencies or not. In case of species it always possible that is must be calculated.

      // Note: If the initial value is calculated by a constant expression (e.g. sqrt(2))
      // it is assumed that the value has been calculated prior to creating the mathematical
      // model. This calculation is done when compiling the data entities.

      CMath::SimulationType SimulationType = CMath::Fixed;
      CCopasiObject * pObject = (*it)->getInitialValueReference();

      if (EntityType == CMath::Species)
        {
          SimulationType = CMath::Conversion;
        }
      else if (hasDependencies(pObject))
        {
          SimulationType = CMath::Assignment;
        }

      map(pObject, p.pInitialExtensiveValuesObject);
      CMathObject::initialize(p.pInitialExtensiveValuesObject, p.pInitialExtensiveValues,
                              CMath::Value, EntityType, SimulationType, false, true,
                              pObject);

      // Extensive Value
      SimulationType = simulationType;

      if (EntityType == CMath::Species &&
          (simulationType == CMath::EventTarget ||
           simulationType == CMath::Assignment))
        {
          SimulationType = CMath::Conversion;
        }

      map((*it)->getValueReference(), p.pExtensiveValuesObject);
      CMathObject::initialize(p.pExtensiveValuesObject, p.pExtensiveValues,
                              CMath::Value, EntityType, SimulationType, false, false,
                              (*it)->getValueReference());

      // Extensive Rate
      SimulationType = simulationType;

      if (simulationType == CMath::EventTarget)
        {
          SimulationType = CMath::Fixed;
        }

      map((*it)->getRateReference(), p.pExtensiveRatesObject);
      CMathObject::initialize(p.pExtensiveRatesObject, p.pExtensiveRates,
                              CMath::ValueRate, EntityType, SimulationType, false, false,
                              (*it)->getRateReference());

      // Species have intensive values in addition to the extensive  ones.
      if (EntityType == CMath::Species)
        {
          const CMetab *pSpecies = static_cast<const CMetab*>(*it);

          // Intensive Initial Value

          // The simulation type for initial values is either CMath::Assignment or CMath::Conversion
          // In case of species it always possible that is must be calculated.
          SimulationType = CMath::Conversion;

          if (simulationType == CMath::Assignment)
            {
              SimulationType = CMath::Assignment;
            }

          map(pSpecies->getInitialConcentrationReference(), p.pInitialIntensiveValuesObject);
          CMathObject::initialize(p.pInitialIntensiveValuesObject, p.pInitialIntensiveValues,
                                  CMath::Value, CMath::Species, SimulationType, true, true,
                                  pSpecies->getInitialConcentrationReference());

          // Intensive Value
          SimulationType = CMath::Conversion;

          if (simulationType == CMath::EventTarget ||
              simulationType == CMath::Assignment)
            {
              SimulationType = simulationType;
            }

          map(pSpecies->getConcentrationReference(), p.pIntensiveValuesObject);
          CMathObject::initialize(p.pIntensiveValuesObject, p.pIntensiveValues,
                                  CMath::Value, CMath::Species, SimulationType, true, false,
                                  pSpecies->getConcentrationReference());

          // Intensive Rate
          map(pSpecies->getConcentrationRateReference(), p.pIntensiveRatesObject);
          CMathObject::initialize(p.pIntensiveRatesObject, p.pIntensiveRates,
                                  CMath::ValueRate, CMath::Species, CMath::Assignment, true, false,
                                  pSpecies->getConcentrationRateReference());
        }
    }
}

void CMathContainer::initializeMathObjects(const std::vector<const CCopasiObject *> & parameters,
    CMathContainer::sPointers & p)
{
  // Process parameters.
  std::vector<const CCopasiObject *>::const_iterator it = parameters.begin();
  std::vector<const CCopasiObject *>::const_iterator end = parameters.end();

  for (; it != end; ++it)
    {
      // Extensive Initial Value
      map(const_cast< CCopasiObject * >(*it), p.pInitialExtensiveValuesObject);
      CMathObject::initialize(p.pInitialExtensiveValuesObject, p.pInitialExtensiveValues,
                              CMath::Value, CMath::LocalReactionParameter, CMath::Fixed, false, true,
                              *it);

      // Extensive Value
      CMathObject::initialize(p.pExtensiveValuesObject, p.pExtensiveValues,
                              CMath::Value, CMath::LocalReactionParameter, CMath::Fixed, false, false,
                              NULL);

      // Extensive Rate
      CMathObject::initialize(p.pExtensiveRatesObject, p.pExtensiveRates,
                              CMath::ValueRate, CMath::LocalReactionParameter, CMath::Fixed, false, false,
                              NULL);
    }
}

void CMathContainer::initializeMathObjects(const CCopasiVector< CReaction > & reactions,
    CMathContainer::sPointers & p)
{
  // Process reactions.
  CCopasiVector< CReaction >::const_iterator it = reactions.begin();
  CCopasiVector< CReaction >::const_iterator end = reactions.end();

  for (; it != end; ++it)
    {
      // Flux
      map((*it)->getParticleFluxReference(), p.pFluxesObject);
      CMathObject::initialize(p.pFluxesObject, p.pFluxes,
                              CMath::Flux, CMath::Reaction, CMath::SimulationTypeUndefined, false, false,
                              (*it)->getParticleFluxReference());

      // Propensity
      map((*it)->getPropensityReference(), p.pPropensitiesObject);
      CMathObject::initialize(p.pPropensitiesObject, p.pPropensities,
                              CMath::Propensity, CMath::Reaction, CMath::SimulationTypeUndefined, false, false,
                              (*it)->getPropensityReference());
    }
}

void CMathContainer::initializeMathObjects(const CCopasiVector< CMoiety > & moieties,
    CMathContainer::sPointers & p)
{
  // Process reactions.
  CCopasiVector< CMoiety >::const_iterator it = moieties.begin();
  CCopasiVector< CMoiety >::const_iterator end = moieties.end();

  for (; it != end; ++it)
    {
      // Total Mass
      map((*it)->getTotalNumberReference(), p.pTotalMassesObject);
      CMathObject::initialize(p.pTotalMassesObject, p.pTotalMasses,
                              CMath::TotalMass, CMath::Moiety, CMath::SimulationTypeUndefined, false, false,
                              (*it)->getTotalNumberReference());

      // Dependent
      map((*it)->getDependentNumberReference(), p.pDependentMassesObject);
      CMathObject::initialize(p.pDependentMassesObject, p.pDependentMasses,
                              CMath::DependentMass, CMath::Moiety, CMath::SimulationTypeUndefined, false, false,
                              (*it)->getDependentNumberReference());
    }
}

// static
bool CMathContainer::hasDependencies(const CCopasiObject * pObject)
{
  const CCopasiObject::DataObjectSet & Dependencies = pObject->getDirectDependencies();

  if (Dependencies.find(pObject->getObjectParent()) != Dependencies.end())
    {
      return Dependencies.size() > 1;
    }

  return Dependencies.size() > 0;
}

void CMathContainer::map(CCopasiObject * pDataObject, CMathObject * pMathObject)
{
  if (pDataObject != NULL)
    {
      mDataObject2MathObject[pDataObject] = pMathObject;
      mDataValue2MathObject[(C_FLOAT64 *) pDataObject->getValuePointer()] = pMathObject;
    }
}
