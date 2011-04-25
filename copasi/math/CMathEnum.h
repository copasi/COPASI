// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathEnum.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/04/25 12:50:08 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CMathEnum
#define COPASI_CMathEnum

#include <map>

class CCopasiObject;
class CMathObject;

template <class Enum> class CMathFlags
{
public:
  CMathFlags():
      mFlags(0)
  {}

  CMathFlags(const CMathFlags & src):
      mFlags(src.mFlags)
  {}

  CMathFlags(const Enum & flag):
      mFlags((int) flag)
  {}

  CMathFlags(const int & flag):
      mFlags(flag)
  {}

  ~CMathFlags();

  operator int () const
  {
    return mFlags;
  }

  Enum operator & (const Enum & flag) const
  {
    return (Enum)(mFlags & flag);
  }

  CMathFlags operator & (const CMathFlags & mask) const
  {
    return (mFlags & mask);
  }

  CMathFlags & operator = (const CMathFlags & rhs)
  {
    mFlags = rhs.mFlags;
    return *this;
  }

  CMathFlags operator | (const CMathFlags & other) const
  {
    return (mFlags | other);
  }

  CMathFlags & operator |= (const CMathFlags & other)
  {
    mFlags |= other.mFlags;
    return *this;
  }

private:
  int mFlags;
};

class CMath
{
public:
  struct sPointers
  {
public:
    C_FLOAT64 * pInitialExtensiveValues;
    C_FLOAT64 * pInitialIntensiveValues;
    C_FLOAT64 * pInitialEventTriggers;
    C_FLOAT64 * pExtensiveValues;
    C_FLOAT64 * pIntensiveValues;
    C_FLOAT64 * pExtensiveRates;
    C_FLOAT64 * pIntensiveRates;
    C_FLOAT64 * pFluxes;
    C_FLOAT64 * pPropensities;
    C_FLOAT64 * pTotalMasses;
    C_FLOAT64 * pDependentMasses;
    C_FLOAT64 * pDiscontinuous;
    C_FLOAT64 * pEventDelays;
    C_FLOAT64 * pEventPriorities;
    C_FLOAT64 * pEventAssignments;
    C_FLOAT64 * pEventTriggers;
    C_FLOAT64 * pEventRoots;
    C_FLOAT64 * pEventRootStates;

    CMathObject * pInitialExtensiveValuesObject;
    CMathObject * pInitialIntensiveValuesObject;
    CMathObject * pInitialEventTriggersObject;
    CMathObject * pExtensiveValuesObject;
    CMathObject * pIntensiveValuesObject;
    CMathObject * pExtensiveRatesObject;
    CMathObject * pIntensiveRatesObject;
    CMathObject * pFluxesObject;
    CMathObject * pPropensitiesObject;
    CMathObject * pTotalMassesObject;
    CMathObject * pDependentMassesObject;
    CMathObject * pDiscontinuousObject;
    CMathObject * pEventDelaysObject;
    CMathObject * pEventPrioritiesObject;
    CMathObject * pEventAssignmentsObject;
    CMathObject * pEventTriggersObject;
    CMathObject * pEventRootsObject;
    CMathObject * pEventRootStatesObject;
  };

public:
  enum SimulationContext
  {
    SimulationContextUndefined = 0x0,
    // This must be set when using the reduced model
    UseMoities = 0x1,
    // This updates the total mass of a moiety and must be set
    // at the beginning of the simulation or after events
    UpdateMoities = 0x2,
    // Event handling
    EventHandling = 0x4
  };

  typedef CMathFlags< SimulationContext > SimulationContextFlag;

  enum ValueType
  {
    ValueTypeUndefined,
    Value,
    ValueRate,
    Flux,
    Propensity,
    TotalMass,
    DependentMass,
    Discontinuous,
    EventDelay,
    EventPriority,
    EventAssignment,
    EventTrigger,
    EventRoot,
    EventRootState
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
    Event
  };
};

#endif // COPASI_CMathEnum
