// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#include "copasi/utilities/CUnitComponent.h"

CUnitComponent::CUnitComponent(CBaseUnit::Kind kind,
                               double multiplier,
                               int scale,
                               double exponent):
  mKind(kind),
  mMultiplier(multiplier),
  mScale(scale),
  mExponent(exponent)
{
}

CBaseUnit::Kind CUnitComponent::getKind() const
{
  return mKind;
}

double CUnitComponent::getMultiplier() const
{
  return mMultiplier;
}

int CUnitComponent::getScale() const
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

void CUnitComponent::setScale(int scale)
{
  mScale = scale;
}

void CUnitComponent::setExponent(double exponent)
{
  mExponent = exponent;
}
