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

#include <cmath>

#include "copasi/copasi.h"
#include "copasi/utilities/CUnitComponent.h"

CUnitComponent::CUnitComponent(CBaseUnit::Kind kind,
                               double multiplier,
                               double scale,
                               double exponent):
  mKind(kind),
  mMultiplier(multiplier),
  mScale(scale),
  mExponent(exponent)
{}

// copy constructor
CUnitComponent::CUnitComponent(const CUnitComponent & src):
  mKind(src.mKind),
  mMultiplier(src.mMultiplier),
  mScale(src.mScale),
  mExponent(src.mExponent)
{}

CUnitComponent::~CUnitComponent() {}

CBaseUnit::Kind CUnitComponent::getKind() const
{
  return mKind;
}

double CUnitComponent::getMultiplier() const
{
  return mMultiplier;
}

double CUnitComponent::getScale() const
{
  return mScale;
}

double CUnitComponent::getExponent() const
{
  return mExponent;
}

void CUnitComponent::setKind(CBaseUnit::Kind kind)
{
  mKind = kind;
}

void CUnitComponent::setMultiplier(double multiplier)
{
  mMultiplier = multiplier;
}

void CUnitComponent::setScale(double scale)
{
  mScale = scale;
}

void CUnitComponent::setExponent(double exponent)
{
  mExponent = exponent;
}

bool CUnitComponent::operator<(const CUnitComponent& rightSide) const
{
  return mKind < rightSide.mKind;
}

bool CUnitComponent::operator==(const CUnitComponent& rightSide) const
{
  return (mKind == rightSide.mKind &&
          mExponent == rightSide.mExponent &&
          mScale == rightSide.mScale &&
          fabs(mMultiplier / rightSide.mMultiplier - 1.0) < 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon());
}

bool CUnitComponent::isValid() const
{
  return (!(std::isnan(mExponent) || std::isnan(mScale) || std::isnan(mScale)));
}

// friend
std::ostream &operator<<(std::ostream &os, const CUnitComponent & o)
{
  os << "Kind: " << CBaseUnit::getSymbol(o.mKind) << ", ";
  os << "Exponent: " << o.mExponent << ", ";
  os << "Scale: " << o.mScale << ", ";
  os << "Multiplier: " << o.mMultiplier << std::endl;

  return os;
}
