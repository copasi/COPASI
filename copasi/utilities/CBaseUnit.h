// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual 
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
  
public:
  enum Kind
  { // prime numbers to make reliable to quickly calculate if CUnit is dimensionless
    meter = 2,
    kilogram = 3,
    second = 5,
    ampere = 7,
    kelvin = 11,
    item = 13,  // mole can be derived with the current value of Avagadro's Number
    candela = 17
  };

  static const std::string getSymbol(Kind kind);
};

#endif // CBASEUNIT_H
