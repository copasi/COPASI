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

  CUnitComponent(CBaseUnit::Kind kind = CBaseUnit::item,
                 double multiplier = 1,
                 int scale = 0,
                 double exponent = 1,
                 bool isMultiplierAvogadro = false);

  /**
   * Copy constructor
   * @param const CUnitComponent & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CUnitComponent(const CUnitComponent & src);

  CBaseUnit::Kind getKind() const;
  double getMultiplier() const;
  int getScale() const;
  double getExponent() const;

  void setKind(CBaseUnit::Kind kind);
  void setMultiplier(double multiplier);
  void setScale(int scale);
  void setExponent(double exponent);
  bool operator<(const CUnitComponent& rightSide) const;

  ~CUnitComponent();

private:

  CBaseUnit::Kind mKind;
  double mMultiplier;
  int mScale;
  double mExponent;
  bool mIsMultiplierAvogadro;
};

#endif // CUNITCOMPONENT_H
