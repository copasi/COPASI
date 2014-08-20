// Copyright (C) 2013 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMathReaction.h"
#include "CMathContainer.h"

#include "model/CReaction.h"

CMathReaction::CMathReaction():
  mpReaction(NULL),
  mpParticleFlux(NULL),
  mpFlux(NULL),
  mpPropensity(NULL),
  mBalance(),
  mStepUpdates()
{}

CMathReaction::CMathReaction(const CMathReaction & src):
  mpReaction(src.mpReaction),
  mpParticleFlux(src.mpParticleFlux),
  mpFlux(src.mpFlux),
  mpPropensity(src.mpPropensity),
  mBalance(src.mBalance),
  mStepUpdates(src.mStepUpdates)
{}

CMathReaction::~CMathReaction()
{}

void CMathReaction::initialize(const CReaction * pReaction, CMathContainer & container)
{
  mpReaction = pReaction;

  // Sanity Check
  if (mpReaction == NULL) return;

  mpParticleFlux = container.getMathObject(mpReaction->getParticleFluxReference());
  mpFlux = container.getMathObject(mpReaction->getFluxReference());
  mpPropensity = container.getMathObject(mpReaction->getPropensityReference());

  mStepUpdates.resize(mpReaction->getChemEq().getBalances().size());
  std::pair< C_FLOAT64, C_FLOAT64 * > * pStepUpdate = mStepUpdates.array();
  std::pair< C_FLOAT64, C_FLOAT64 * > * pStepUpdateEnd = pStepUpdate + mStepUpdates.size();
  CCopasiVector < CChemEqElement >::const_iterator it = mpReaction->getChemEq().getBalances().begin();

  for (; pStepUpdate != pStepUpdateEnd; ++pStepUpdate, ++it)
    {
      CMathObject * pParticleNumber = container.getMathObject((*it)->getMetabolite()->getValueReference());
      mBalance.insert(std::pair < const CObjectInterface *, C_FLOAT64 >(pParticleNumber, (*it)->getMultiplicity()));
      pStepUpdate->first = (*it)->getMultiplicity();
      pStepUpdate->second = (C_FLOAT64 *) pParticleNumber->getValuePointer();
    }
}

void CMathReaction::copy(const CMathReaction & src,
                         CMathContainer & /* container */,
                         const size_t & valueOffset,
                         const size_t & objectOffset)
{
  mpReaction = src.mpReaction;

  mpParticleFlux = src.mpParticleFlux + objectOffset;
  mpFlux = src.mpFlux + objectOffset;
  mpPropensity = src.mpPropensity + objectOffset;

  mStepUpdates.resize(src.mStepUpdates.size());
  std::pair< C_FLOAT64, C_FLOAT64 * > * pStepUpdate = mStepUpdates.array();
  std::pair< C_FLOAT64, C_FLOAT64 * > * pStepUpdateEnd = pStepUpdate + mStepUpdates.size();
  const std::pair< C_FLOAT64, C_FLOAT64 * > * pStepUpdateSrc = src.mStepUpdates.array();

  for (; pStepUpdate != pStepUpdateEnd; ++pStepUpdate, ++pStepUpdateSrc)
    {
      pStepUpdate->first = pStepUpdateSrc->first;
      pStepUpdate->second = pStepUpdateSrc->second + valueOffset;
    }

  Balance::const_iterator it = src.mBalance.begin();
  Balance::const_iterator end = src.mBalance.end();

  for (; it != end; ++it)
    {
      mBalance.insert(std::pair < const CObjectInterface *, C_FLOAT64 >(it->first + objectOffset, it->second));
    }
}

void CMathReaction::fire()
{
  std::pair< C_FLOAT64, C_FLOAT64 * > * pStepUpdate = mStepUpdates.array();
  std::pair< C_FLOAT64, C_FLOAT64 * > * pStepUpdateEnd = pStepUpdate + mStepUpdates.size();

  for (; pStepUpdate != pStepUpdateEnd; ++pStepUpdate)
    {
      *pStepUpdate->second += pStepUpdate->first;
    }
}

void CMathReaction::fireMultiple(const C_FLOAT64 & count)
{
  std::pair< C_FLOAT64, C_FLOAT64 * > * pStepUpdate = mStepUpdates.array();
  std::pair< C_FLOAT64, C_FLOAT64 * > * pStepUpdateEnd = pStepUpdate + mStepUpdates.size();

  for (; pStepUpdate != pStepUpdateEnd; ++pStepUpdate)
    {
      *pStepUpdate->second += pStepUpdate->first * count;
    }
}

const CMathObject * CMathReaction::getParticleFluxObject() const
{
  return mpParticleFlux;
}

const CMathObject * CMathReaction::getFluxObject() const
{
  return mpFlux;
}

const CMathObject * CMathReaction::getPropensityObject() const
{
  return mpPropensity;
}

const std::set< std::pair < const CObjectInterface *, C_FLOAT64 > > & CMathReaction::getBalance() const
{
  return mBalance;
}

const CReaction * CMathReaction::getModelReaction() const
{
  return mpReaction;
}

bool CMathReaction::isFast() const
{
  return (mpReaction != NULL && mpReaction->isFast());
}
