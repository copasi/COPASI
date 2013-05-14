// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
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
  mModifiedSpecies(),
  mStepUpdates()
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
      mModifiedSpecies.insert(pParticleNumber);
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

  CObjectInterface::ObjectSet::const_iterator it = src.mModifiedSpecies.begin();
  CObjectInterface::ObjectSet::const_iterator end = src.mModifiedSpecies.end();

  for (; it != end; ++it)
    {
      mModifiedSpecies.insert(*it + objectOffset);
    }
}

void CMathReaction::fire(const C_FLOAT64 & count)
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

const CObjectInterface::ObjectSet & CMathReaction::getModifiedSpecies() const
{
  return mModifiedSpecies;
}

const CReaction * CMathReaction::getModelReaction() const
{
  return mpReaction;
}
