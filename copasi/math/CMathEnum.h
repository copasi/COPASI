// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

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
    TransitionTime
  };

private:
  constexpr static CEnumAnnotationInstance _ValueTypeName{
    ValueType::Undefined,
    MapNode{ValueType::Undefined, "undefined"},
    MapNode{ValueType::Value, "value"},
    MapNode{ValueType::Rate, "rate"},
    MapNode{ValueType::ParticleFlux, "particle flux"},
    MapNode{ValueType::Flux, "flux"},
    MapNode{ValueType::Propensity, "propensity"},
    MapNode{ValueType::Noise, "noise"},
    MapNode{ValueType::ParticleNoise, "particle noise"},
    MapNode{ValueType::TotalMass, "total mass"},
    MapNode{ValueType::DependentMass, "dependent mass"},
    MapNode{ValueType::Discontinuous, "discontinuous"},
    MapNode{ValueType::EventDelay, "event delay"},
    MapNode{ValueType::EventPriority, "event priority"},
    MapNode{ValueType::EventAssignment, "event assignment"},
    MapNode{ValueType::EventTrigger, "event trigger"},
    MapNode{ValueType::EventRoot, "event root"},
    MapNode{ValueType::EventRootState, "event root state"},
    MapNode{ValueType::DelayValue, "delay value"},
    MapNode{ValueType::DelayLag, "delay lag"},
    MapNode{ValueType::TransitionTime, "transition time"}};

public:
  constexpr static CEnumAnnotation< ValueType, std::string_view > ValueTypeName{_ValueTypeName};

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
    Conversion
  };

private:
  constexpr static CEnumAnnotationInstance _SimulationTypeName{
    SimulationType::Undefined,
    MapNode{SimulationType::Undefined, "undefined"},
    MapNode{SimulationType::Fixed, "fixed"},
    MapNode{SimulationType::EventTarget, "event target"},
    MapNode{SimulationType::Time, "time"},
    MapNode{SimulationType::ODE, "ODE"},
    MapNode{SimulationType::Independent, "independent"},
    MapNode{SimulationType::Dependent, "dependent"},
    MapNode{SimulationType::Assignment, "assignment"},
    MapNode{SimulationType::Conversion, "conversion"}};

public:
  constexpr static CEnumAnnotation< SimulationType, std::string_view > SimulationTypeName{_SimulationTypeName};

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
    Delay
  };

private:
  constexpr static CEnumAnnotationInstance _EntityTypeName{
    EntityType::Undefined,
    MapNode{EntityType::Undefined, "undefined"},
    MapNode{EntityType::Model, "model"},
    MapNode{EntityType::Analysis, "analysis"},
    MapNode{EntityType::GlobalQuantity, "global quantity"},
    MapNode{EntityType::Compartment, "compartment"},
    MapNode{EntityType::Species, "species"},
    MapNode{EntityType::LocalReactionParameter, "local parameter"},
    MapNode{EntityType::StoichiometricCoefficients, "stoich. coeff."},
    MapNode{EntityType::Reaction, "reaction"},
    MapNode{EntityType::Moiety, "moiety"},
    MapNode{EntityType::Event, "event"},
    MapNode{EntityType::Delay, "delay"}};

public:
  constexpr static CEnumAnnotation< EntityType, std::string_view > EntityTypeName{_EntityTypeName};

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
