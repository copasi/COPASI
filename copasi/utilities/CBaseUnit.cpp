// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/utilities/CBaseUnit.h"
#include "copasi/utilities/CCopasiMessage.h"

// static
const char * CBaseUnit::Name[] =
{
  "dimensionless",
  "meter",
  "gram",
  "second",
  "Ampere",
  "Kelvin",
  "item",
  "Candela",
  NULL
};

// static (because CBaseUnit is not meant to be constructed)
const std::string CBaseUnit::getSymbol(Kind kind)
{
  switch (kind)
    {
      case dimensionless:
        return "1";

      case meter:
        return "m";

      case gram:
        return "g";

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
        return "1";
    }
}

// static (because CBaseUnit is not meant to be constructed)
CBaseUnit::Kind CBaseUnit::fromSymbol(const std::string & symbol)
{
  if (symbol == "m") return meter;

  if (symbol == "g") return gram;

  if (symbol == "s") return second;

  if (symbol == "A") return ampere;

  if (symbol == "K") return kelvin;

  if (symbol == "cd") return candela;

  if (symbol == "#") return item;

  if (symbol == "1") return dimensionless;

  fatalError();

  return dimensionless;
}

// static (because CBaseUnit is not meant to be constructed)
CBaseUnit::Scale CBaseUnit::scaleFromPrefix(const std::string & prefix)
{
  if (prefix == "a") return atto;

  if (prefix == "f") return femto;

  if (prefix == "p") return pico;

  if (prefix == "u" || prefix == "\xc2\xb5") return micro;

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
