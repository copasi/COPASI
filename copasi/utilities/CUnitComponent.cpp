// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#include "copasi/utilities/CUnitComponent.h"

CUnitComponent::CUnitComponent(CBaseUnit::Kind kind,
                               double multiplier,
                               int scale,
                               double exponent,
                               bool isMultiplierAvogadro):
  mKind(kind),
  mMultiplier(multiplier),
  mScale(scale),
  mExponent(exponent),
  mIsMultiplierAvogadro(isMultiplierAvogadro)
{}

// copy constructor
CUnitComponent::CUnitComponent(const CUnitComponent & src):
  mKind(src.mKind),
  mMultiplier(src.mMultiplier),
  mScale(src.mScale),
  mExponent(src.mExponent),
  mIsMultiplierAvogadro(src.mIsMultiplierAvogadro)
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

bool CUnitComponent::operator<(const CUnitComponent& rightSide) const
{
  return mKind < rightSide.getKind();
}
