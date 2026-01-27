// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#include "copasi/core/CCore.h"

class CRandom;

class CIntervalValue
{
public:
  enum struct Range {
    containsZero,
    positive,
    negative,
    invalid
  };

  CIntervalValue() = delete;

  CIntervalValue(const CIntervalValue & src) = delete;

  CIntervalValue(const C_FLOAT64 *& pMinimum, const C_FLOAT64 *& pMaximum);

  C_FLOAT64 randomValue(CRandom * pRandom) const;

  const Range & getRange() const;

  bool const & isLogarithmic() const;

  const C_FLOAT64 & getMinimum() const;

  const C_FLOAT64 & getMaximum() const;

  const C_FLOAT64 & getSize() const;

  const C_FLOAT64 & getLogarithmicScale() const;

  void compile();

private:
  const C_FLOAT64 *& mpMinimum;

  const C_FLOAT64 *& mpMaximum;

  C_FLOAT64 mSize;

  Range mRange;

  bool mIsLogarithmic;

  C_FLOAT64 mLogarithmicScale;
};
