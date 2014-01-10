// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#include "copasi/utilities/CUnitComponent.h"

CBaseUnit::Kind CUnitComponent::getKind()
{
  return mKind;
}

double CUnitComponent::getMultiplier()
{
  return mMultiplier;
}

int CUnitComponent::getScale()
{
  return mScale;
}

double CUnitComponent::getExponent()
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
