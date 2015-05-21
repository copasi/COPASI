// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/utilities/CBaseUnit.h"

// static (because CBaseUnit is not meant to be constructed)
const std::string CBaseUnit::getSymbol(Kind kind)
{
  switch (kind)
    {
      case dimensionless:
        return "";

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
        return "#";

      default:
        return "";
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

// static (because CBaseUnit is not meant to be constructed)
const CBaseUnit::Scale CBaseUnit::scaleFromPrefix(const std::string & prefix)
{
  if (prefix == "a") return atto;

  if (prefix == "f") return femto;

  if (prefix == "p") return pico;

  if (prefix == "u") return micro;

  if (prefix == "m") return milli;

  if (prefix == "c") return centi;

  if (prefix == "d") return deci;

  if (prefix == "h") return hecto;

  if (prefix == "k") return kilo;

  if (prefix == "M") return mega;

  if (prefix == "G") return giga;

  if (prefix == "T") return tera;

  if (prefix == "P") return peta;

  return zero;
}
