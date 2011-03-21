// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathEnum.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/21 15:45:57 $
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
  enum SimulationContext
  {
    SimulationContextUndefined = 0x0,
    // This must be set when using the reduced model
    UseMoities = 0x1,
    // This updates the total mass of a moiety and must be set
    // at the beginning of the simulation or after events
    UpdateMoities = 0x2
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
    DependentMass
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
    Assignment
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
    Moiety
  };
};

#endif // COPASI_CMathEnum
