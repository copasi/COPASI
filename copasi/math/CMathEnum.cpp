// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/copasi.h"

#include "CMathEnum.h"

const CEnumAnnotation< std::string, CMath::ValueType > CMath::ValueTypeName(
{
  "undefined",
  "value",
  "rate",
  "particle flux",
  "flux",
  "propensity",
  "noise",
  "particle noise",
  "total mass",
  "dependent mass",
  "discontinuous",
  "event delay",
  "event priority",
  "event assignment",
  "event trigger",
  "event root",
  "event root state",
  "delay value",
  "delay lag",
  "transition time",
});

const CEnumAnnotation< std::string, CMath::SimulationType > CMath::SimulationTypeName(
{
  "undefined",
  "fixed",
  "event target",
  "time",
  "ODE",
  "independent",
  "dependent",
  "assignment",
  "conversion"
});

const CEnumAnnotation< std::string, CMath::EntityType > CMath::EntityTypeName(
{
  "undefined",
  "model",
  "analysis",
  "global quantity",
  "compartment",
  "species",
  "local parameter",
  "stoich. coeff.",
  "reaction",
  "moiety",
  "event",
  "delay",
});

