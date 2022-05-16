// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// This class defines the kinds of SI units COPASI's units will be
// based on, as well as associated symbols (UTF strings), for display.

#ifndef CBASEUNIT_H
#define CBASEUNIT_H

// SI units based on http://physics.nist.gov/cuu/Units/units.html

#include <string>

class CBaseUnit
{
  static const char * Name[];

public:
  enum Kind
  {
    dimensionless = 0, // must be the lowest value
    meter,
    gram,
    second,
    ampere,
    kelvin,
    item,  // mole can be derived with the current value of Avagadro's Number
    candela,
    avogadro,
    undefined
  };

  static const std::string getSymbol(Kind kind);

  static Kind fromSymbol(const std::string & symbol);

  //http://physics.nist.gov/cuu/Units/prefixes.html
  enum Scale
  {
    // SCALE    [yzafpnumcdhkMGTPEZY]
    yocto = -24,
    zepto = -21,
    atto = -18,
    femto = -15,
    pico = -12,
    nano = -9,
    micro = -6,
    milli = -3,
    centi = -2,
    deci = -1,
    zero = 0,
    hecto = 2,
    kilo = 3,
    mega = 6,
    giga = 9,
    tera = 12,
    peta = 15,
    exa = 18,
    zetta = 21,
    yotta = 24
  };

  static Scale scaleFromPrefix(const std::string & prefix);
  static std::string prefixFromScale(int scale);
};

#endif // CBASEUNIT_H
