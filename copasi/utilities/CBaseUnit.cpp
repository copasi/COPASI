// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#include "copasi/utilities/CBaseUnit.h"

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

    case item:
      return "mol";

    case candela:
      return "cd";

    default:
      return "";
  }
}
