// Copyright (C) 2011 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CMathEnum
#define COPASI_CMathEnum

#include <map>
#include <vector>

class CCopasiObject;
class CMathObject;
class CEvaluationNode;

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

  ~CMathFlags() {}

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

  CMathFlags operator & (const int & mask) const
  {
    return (mFlags & mask);
  }

  CMathFlags & operator = (const CMathFlags & rhs)
  {
    mFlags = rhs.mFlags;
    return *this;
  }

  CMathFlags operator | (const Enum & flag) const
  {
    return (mFlags | flag);
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

    C_FLOAT64 * pEventDelays;
    C_FLOAT64 * pEventPriorities;
    C_FLOAT64 * pEventAssignments;
    C_FLOAT64 * pEventRoots;
    C_FLOAT64 * pEventRootStates;
    C_FLOAT64 * pPropensities;
    C_FLOAT64 * pDependentMasses;
    C_FLOAT64 * pDiscontinuous;

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

    CMathObject * pEventDelaysObject;
    CMathObject * pEventPrioritiesObject;
    CMathObject * pEventAssignmentsObject;
    CMathObject * pEventRootsObject;
    CMathObject * pEventRootStatesObject;
    CMathObject * pPropensitiesObject;
    CMathObject * pDependentMassesObject;
    CMathObject * pDiscontinuousObject;
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
    Rate,
    ParticleFlux,
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

  class CVariableStack
  {
  public:
    typedef std::vector< const CEvaluationNode * > StackElement;
    typedef std::vector< StackElement > Buffer;

    friend std::ostream & operator << (std::ostream & os, const CVariableStack & s);

    enum Context
    {
      Variable,
      Body
    };

  private:
    CVariableStack();

  public:
    CVariableStack(Buffer & stack);

    CVariableStack(const CVariableStack & src);

    ~CVariableStack();

    void push(const StackElement & stackElement);

    void pop();

    size_t size() const;

    const CEvaluationNode * operator [](const size_t & index) const;

  private:
    Buffer * mpStack;

  private:
    Context mContext;

    size_t mVariableLevel;

    size_t mBodyLevel;
  };

  class CAllocationStack
  {
  public:
    class CAllocation
    {
    public:
      friend std::ostream & operator << (std::ostream & os, const CAllocation & s);

      CAllocation();

      CAllocation(const CAllocation & src);

      ~CAllocation();

      CAllocation & operator = (const CAllocation & rhs);

      CAllocation & operator += (const CAllocation & rhs);

      size_t nDiscontinuous;

      size_t nTotalRoots;

      std::vector< size_t > nRootsPerDiscontinuity;
    };

    typedef std::vector< CAllocation > StackElement;
    typedef std::vector< StackElement > Buffer;

    enum Context
    {
      Variable,
      Body
    };

  private:
    CAllocationStack();

  public:
    CAllocationStack(Buffer & stack);

    CAllocationStack(const CAllocationStack & src);

    ~CAllocationStack();

    void push(const StackElement & stackElement);

    void pop();

    size_t size() const;

    const CAllocation & operator [](const size_t & index) const;

  private:
    Buffer * mpStack;

  private:
    Context mContext;

    size_t mVariableLevel;

    size_t mBodyLevel;
  };
};

std::ostream & operator << (std::ostream & os, const CMath::CVariableStack & s);

std::ostream & operator << (std::ostream & os, const CMath::CAllocationStack::CAllocation & s);

#endif // COPASI_CMathEnum
