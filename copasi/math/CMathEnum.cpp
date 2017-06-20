// Copyright (C) 2011 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

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

