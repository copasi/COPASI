// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CMathEnum
#define COPASI_CMathEnum

#include <stddef.h>

#include <map>
#include <vector>
#include <string>
#include "copasi/core/CEnumAnnotation.h"
#include "copasi/core/CFlags.h"

class CDataObject;
class CMathObject;
class CEvaluationNode;
class CObjectInterface;

class CMath
{
public:
  typedef std::multimap< std::string, std::pair< std::string, CMathObject * > > DelayValueData;
  typedef std::multimap< std::string, DelayValueData > DelayData;

  struct sPointers
  {
  public:
    double * pInitialExtensiveValues;
    double * pInitialIntensiveValues;
    double * pInitialExtensiveRates;
    double * pInitialIntensiveRates;
    double * pInitialParticleFluxes;
    double * pInitialFluxes;
    double * pInitialTotalMasses;
    double * pInitialEventTriggers;

    double * pExtensiveValues;
    double * pIntensiveValues;
    double * pExtensiveRates;
    double * pIntensiveRates;
    double * pParticleFluxes;
    double * pFluxes;
    double * pTotalMasses;
    double * pEventTriggers;

    double * pExtensiveNoise;
    double * pIntensiveNoise;
    double * pReactionNoise;
    double * pReactionParticleNoise;
    double * pEventDelays;
    double * pEventPriorities;
    double * pEventAssignments;
    double * pEventRoots;
    double * pEventRootStates;
    double * pPropensities;
    double * pDependentMasses;
    double * pDiscontinuous;
    double * pDelayValue;
    double * pDelayLag;
    double * pTransitionTime;

    CMathObject * pInitialExtensiveValuesObject;
    CMathObject * pInitialIntensiveValuesObject;
    CMathObject * pInitialExtensiveRatesObject;
    CMathObject * pInitialIntensiveRatesObject;
    CMathObject * pInitialParticleFluxesObject;
    CMathObject * pInitialFluxesObject;
    CMathObject * pInitialTotalMassesObject;
    CMathObject * pInitialEventTriggersObject;

    CMathObject * pExtensiveValuesObject;
    CMathObject * pIntensiveValuesObject;
    CMathObject * pExtensiveRatesObject;
    CMathObject * pIntensiveRatesObject;
    CMathObject * pParticleFluxesObject;
    CMathObject * pFluxesObject;
    CMathObject * pTotalMassesObject;
    CMathObject * pEventTriggersObject;

    CMathObject * pExtensiveNoiseObject;
    CMathObject * pIntensiveNoiseObject;
    CMathObject * pReactionNoiseObject;
    CMathObject * pReactionParticleNoiseObject;

    CMathObject * pEventDelaysObject;
    CMathObject * pEventPrioritiesObject;
    CMathObject * pEventAssignmentsObject;
    CMathObject * pEventRootsObject;
    CMathObject * pEventRootStatesObject;
    CMathObject * pPropensitiesObject;
    CMathObject * pDependentMassesObject;
    CMathObject * pDiscontinuousObject;
    CMathObject * pDelayValueObject;
    CMathObject * pDelayLagObject;
    CMathObject * pTransitionTimeObject;
  };

  struct sRelocate
  {
  public:
    double * pValueStart;
    double * pValueEnd;
    double * pOldValue;
    double * pNewValue;

    CMathObject * pObjectStart;
    CMathObject * pObjectEnd;
    CMathObject * pOldObject;
    CMathObject * pNewObject;

    ptrdiff_t offset;
  };

  template < class CType > class Entity
  {
  public:
    CType * InitialValue;
    CType * InitialRate;
    CType * Value;
    CType * Rate;

    Entity()
      : InitialValue(NULL)
      , InitialRate(NULL)
      , Value(NULL)
      , Rate(NULL)
    {}
  };

  enum struct SimulationContext
  {
    Default,
    // This is used to indicate deterministic simulation
    // Deterministic = 0x1,
    // This must be set when using the reduced model
    UseMoieties,
    // This updates the total mass of a moiety and must be set
    // at the beginning of the simulation or after events
    UpdateMoieties,
    // This is used to indicate stochastic simulation
    // Stochastic = 0x8,
    // Event handling
    EventHandling,
    // This is used to detect whether a delay value depends on other delay values.
    DelayValues,
    __SIZE
  };

  typedef CFlags< SimulationContext > SimulationContextFlag;

  enum struct ValueType
  {
    Undefined,
    Value,
    Rate,
    ParticleFlux,
    Flux,
    Propensity,
    Noise,
    ParticleNoise,
    TotalMass,
    DependentMass,
    Discontinuous,
    EventDelay,
    EventPriority,
    EventAssignment,
    EventTrigger,
    EventRoot,
    EventRootState,
    DelayValue,
    DelayLag,
    TransitionTime,
    __SIZE
  };

  static const CEnumAnnotation< std::string, ValueType > ValueTypeName;

  enum struct SimulationType
  {
    Undefined,
    Fixed,
    EventTarget,
    Time,
    ODE,
    Independent,
    Dependent,
    Assignment,
    Conversion,
    __SIZE
  };

  static const CEnumAnnotation< std::string, SimulationType > SimulationTypeName;

  enum struct EntityType
  {
    Undefined,
    Model,
    Analysis,
    GlobalQuantity,
    Compartment,
    Species,
    LocalReactionParameter,
    StoichiometricCoefficients,
    Reaction,
    Moiety,
    Event,
    Delay,
    __SIZE
  };

  static const CEnumAnnotation< std::string, EntityType > EntityTypeName;

  enum struct eStateChange
  {
    FixedEventTarget,
    Discontinuity,
    State,
    EventSimulation,
    ContinuousSimulation,
    __SIZE
  };

  enum struct RootToggleType
  {
    NoToggle,
    ToggleBoth,
    ToggleEquality,
    ToggleInequality,
    __SIZE
  };

  typedef CFlags< eStateChange > StateChange;

  template < class Type > class Variables: public std::vector< Type >
  {
  public:
    Variables():
      std::vector< Type >()
    {}

    Variables(const std::vector< Type > & src):
      std::vector< Type >(src)
    {}

    ~Variables()
    {}
  };
};

#endif // COPASI_CMathEnum
