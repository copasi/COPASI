// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/utilities/CBaseUnit.h"

// static (because CBaseUnit is not meant to be constructed)
const std::string CBaseUnit::getSymbol(Kind kind)
{
  switch (kind)
    {
      case meter:
        return "m";

      case kilogram:
        return "kg";

      case second:
        return "s";

      case ampere:
        return "A";

      case kelvin:
        return "K";

    case candela:
      return "cd";

    case item:
    default:
      return "#";
  }
}

// static (because CBaseUnit is not meant to be constructed)
const CBaseUnit::Kind CBaseUnit::fromSymbol(const std::string & symbol)
{
  if (symbol == "m") return meter;
  if (symbol == "kg") return kilogram;
  if (symbol == "s") return second;
  if (symbol == "A") return ampere;
  if (symbol == "K") return kelvin;
  if (symbol == "cd") return candela;

  return item;
}
