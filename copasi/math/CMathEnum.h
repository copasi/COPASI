// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CMathEnum
#define COPASI_CMathEnum

#include <map>
#include <vector>
#include "copasi/utilities/CFlags.h"

class CCopasiObject;
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
    C_FLOAT64 * pInitialExtensiveValues;
    C_FLOAT64 * pInitialIntensiveValues;
    C_FLOAT64 * pInitialExtensiveRates;
    C_FLOAT64 * pInitialIntensiveRates;
    C_FLOAT64 * pInitialParticleFluxes;
    C_FLOAT64 * pInitialFluxes;
    C_FLOAT64 * pInitialTotalMasses;
    C_FLOAT64 * pInitialEventTriggers;

    C_FLOAT64 * pExtensiveValues;
    C_FLOAT64 * pIntensiveValues;
    C_FLOAT64 * pExtensiveRates;
    C_FLOAT64 * pIntensiveRates;
    C_FLOAT64 * pParticleFluxes;
    C_FLOAT64 * pFluxes;
    C_FLOAT64 * pTotalMasses;
    C_FLOAT64 * pEventTriggers;

    C_FLOAT64 * pExtensiveNoise;
    C_FLOAT64 * pIntensiveNoise;
    C_FLOAT64 * pReactionNoise;
    C_FLOAT64 * pReactionParticleNoise;
    C_FLOAT64 * pEventDelays;
    C_FLOAT64 * pEventPriorities;
    C_FLOAT64 * pEventAssignments;
    C_FLOAT64 * pEventRoots;
    C_FLOAT64 * pEventRootStates;
    C_FLOAT64 * pPropensities;
    C_FLOAT64 * pDependentMasses;
    C_FLOAT64 * pDiscontinuous;
    C_FLOAT64 * pDelayValue;
    C_FLOAT64 * pDelayLag;
    C_FLOAT64 * pTransitionTime;

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
    C_FLOAT64 * pValueStart;
    C_FLOAT64 * pValueEnd;
    C_FLOAT64 * pOldValue;
    C_FLOAT64 * pNewValue;

    CMathObject * pObjectStart;
    CMathObject * pObjectEnd;
    CMathObject * pOldObject;
    CMathObject * pNewObject;

    size_t offset;
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

  enum ValueType
  {
    ValueTypeUndefined,
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
    TransitionTime
  };

  enum SimulationType
  {
    SimulationTypeUndefined,
    Fixed,
    EventTarget,
    Time,
    ODE,
    Independent,
    Dependent,
    Assignment,
    Conversion
  };

  enum EntityType
  {
    EntityTypeUndefined,
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
    Delay
  };

  enum struct eStateChange
  {
    FixedEventTarget,
    Discontinuity,
    State,
    EventSimulation,
    ContinuousSimulation,
    __SIZE
  };

  enum RootToggleType
  {
    NoToggle = 0x0,
    ToggleBoth = 0x1,
    ToggleEquality = 0x2,
    ToggleInequality = 0x3
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
