// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#include <type_traits>
#include "copasi/core/CVector.h"

class CMathContainer;

enum struct RootMask
{
  NONE = 0,
  CONTINUOUS_NEGATIVE = 0x1,
  CONTINUOUS_POSITIVE = 0x2,
  CONTINUOUS = 0x3,
  DISCRETE = 0x4,
  ALL = 0x7
};

RootMask operator &(RootMask lhs, RootMask rhs);
RootMask operator |(RootMask lhs, RootMask rhs);

std::ostream &operator<<(std::ostream &os, RootMask & rootMask);

class CRootMask : private CVector< RootMask >
{
public:
  void setMathContainer(CMathContainer * pContainer);

  void setTolerance(const C_FLOAT64 & tolerance);

  void create(RootMask type, const CVectorCore< C_INT > & rootsFound = CVectorCore< C_INT >());

  void setType(RootMask type);

  void apply(CVectorCore< C_FLOAT64 > & roots) const;

  bool adjust(RootMask & type, const CVectorCore< C_INT > & found);

  RootMask * begin();
  RootMask * end();

  const RootMask * begin() const;
  const RootMask * end() const;

  size_t size() const;

  operator const CVector< const RootMask > & () const;
  bool operator ==(const CRootMask & rhs) const;

private:
  RootMask mType = RootMask::NONE;
  CMathContainer * mpContainer = nullptr;
  C_FLOAT64 mAbsoluteTolerance = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
};
