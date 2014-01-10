// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// This class defines the kinds of SI units COPASI's units will be
// based on (like SMBL Unit.kind), as well as associated symbols
// (UTF strings), for display.

#ifndef CUNITCOMPONENT_H
#define CUNITCOMPONENT_H

#include "copasi/utilities/CBaseUnit.h"

class CUnitComponent
{
  
public:

  CBaseUnit::Kind getKind();
  double getMultiplier();
  int getScale();
  double getExponent();

  void setKind(CBaseUnit::Kind kind);
  void setMultiplier(double multiplier);
  void setScale(int scale);
  void setExponent(double exponent);

private:

  CBaseUnit::Kind mKind;
  double mMultiplier;
  int mScale;
  double mExponent;
};

#endif // CUNITCOMPONENT_H
