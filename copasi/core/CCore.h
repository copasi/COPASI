// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CCoreEnum
#define COPASI_CCoreEnum

#include "copasi/core/CFlags.h"

class CMathUpdateSequence;

class CCore
{
public:
  typedef CMathUpdateSequence CUpdateSequence;

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

  enum struct Framework
  {
    Concentration = 0,
    ParticleNumbers
  };
};

#endif // COPASI_CCoreEnum
