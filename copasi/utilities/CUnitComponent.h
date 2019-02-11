// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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
// based on (like SMBL Unit.kind), as well as associated symbols
// (UTF strings), for display.

#ifndef CUNITCOMPONENT_H
#define CUNITCOMPONENT_H

#include "copasi/utilities/CBaseUnit.h"

class CUnitComponent
{
  friend std::ostream &operator<<(std::ostream &os, const CUnitComponent & o);

private:
  CUnitComponent();

public:

  CUnitComponent(CBaseUnit::Kind kind,
                 double multiplier = 1,
                 double scale = 0,
                 double exponent = 1);

  /**
   * Copy constructor
   * @param const CUnitComponent & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CUnitComponent(const CUnitComponent & src);

  CBaseUnit::Kind getKind() const;
  double getMultiplier() const;
  double getScale() const;
  double getExponent() const;

  void setKind(CBaseUnit::Kind kind);
  void setMultiplier(double multiplier);
  void setScale(double scale);
  void setExponent(double exponent);
  bool operator<(const CUnitComponent& rightSide) const;
  bool operator==(const CUnitComponent& rightSide) const;

  bool isValid() const;

  ~CUnitComponent();

private:

  CBaseUnit::Kind mKind;
  double mMultiplier;
  double mScale;
  double mExponent;
};

#endif // CUNITCOMPONENT_H
