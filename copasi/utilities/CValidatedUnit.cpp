// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CValidatedUnit.cpp
 *
 *  Created on: Aug 1, 2016
 *      Author: shoops
 */

#include "CValidatedUnit.h"

// static
CValidatedUnit CValidatedUnit::merge(const CValidatedUnit & a,
                                     const CValidatedUnit & b)
{
  CValidatedUnit Merged(a);

  if (a == CUnit(CBaseUnit::undefined))
    {
      Merged = b;
      Merged.setConflict(a.conflict() || b.conflict());
    }
  else if (b == CUnit(CBaseUnit::undefined))
    {
      Merged.setConflict(a.conflict() || b.conflict());
    }
  else
    {
      Merged.setConflict(a.conflict() || b.conflict() || !(a == b));
    }

  return Merged;
}

CValidatedUnit::CValidatedUnit():
  CUnit(),
  mConflict(true)
{}

CValidatedUnit::CValidatedUnit(const CValidatedUnit & src):
  CUnit(src),
  mConflict(src.mConflict)
{}

CValidatedUnit::CValidatedUnit(const CUnit & unit, const bool & conflict):
  CUnit(unit),
  mConflict(conflict)
{}

CValidatedUnit::~CValidatedUnit()
{}

CValidatedUnit CValidatedUnit::exponentiate(const double & exponent) const
{
  return CValidatedUnit(CUnit::exponentiate(exponent), mConflict);
}

CValidatedUnit CValidatedUnit::operator*(const CValidatedUnit & rightSide) const
{
  return CValidatedUnit(CUnit::operator *(rightSide), mConflict || rightSide.mConflict);
}

void CValidatedUnit::setConflict(const bool & conflict)
{
  mConflict = conflict;
}

const bool & CValidatedUnit::conflict() const
{
  return mConflict;
}

bool CValidatedUnit::operator<(const CValidatedUnit & rightSide) const
{
  if (mConflict != rightSide.mConflict)
    return mConflict < rightSide.mConflict;

  return CUnit::operator <(rightSide);
}

std::ostream &operator<<(std::ostream &os, const CValidatedUnit & o)
{
  os << * static_cast< const CUnit * >(&o) << std::endl;
  os << "Conflict:   " << o.mConflict;

  return os;
}
