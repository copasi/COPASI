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
  mChangedSpecies(),
  mObjectBalance(),
  mNumberBalance()
{}

CMathReaction::CMathReaction(const CMathReaction & src):
  mpReaction(src.mpReaction),
  mpParticleFlux(src.mpParticleFlux),
  mpFlux(src.mpFlux),
  mpPropensity(src.mpPropensity),
  mChangedSpecies(src.mChangedSpecies),
  mObjectBalance(src.mObjectBalance),
  mNumberBalance(src.mNumberBalance)
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

  mNumberBalance.resize(mpReaction->getChemEq().getBalances().size());
  SpeciesBalance * pStepUpdate = mNumberBalance.array();
  CCopasiVector < CChemEqElement >::const_iterator it = mpReaction->getChemEq().getBalances().begin();
  CCopasiVector < CChemEqElement >::const_iterator end = mpReaction->getChemEq().getBalances().end();

  for (; it != end; ++it)
    {
      CMathObject * pParticleNumber = container.getMathObject((*it)->getMetabolite()->getValueReference());

      if (pParticleNumber->getSimulationType() == CMath::Independent ||
          pParticleNumber->getSimulationType() == CMath::Dependent)
        {
          mChangedSpecies.insert(pParticleNumber);
          mObjectBalance.insert(std::pair < const CObjectInterface *, C_FLOAT64 >(pParticleNumber, (*it)->getMultiplicity()));
          pStepUpdate->first = (C_FLOAT64 *) pParticleNumber->getValuePointer();
          pStepUpdate->second = (*it)->getMultiplicity();

          ++pStepUpdate;
        }
    }

  mNumberBalance.resize(mChangedSpecies.size(), true);
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

  mNumberBalance.resize(src.mNumberBalance.size());
  SpeciesBalance * pStepUpdate = mNumberBalance.array();
  SpeciesBalance * pStepUpdateEnd = pStepUpdate + mNumberBalance.size();
  const SpeciesBalance * pStepUpdateSrc = src.mNumberBalance.array();

  for (; pStepUpdate != pStepUpdateEnd; ++pStepUpdate, ++pStepUpdateSrc)
    {
      pStepUpdate->first = pStepUpdateSrc->first + valueOffset;
      pStepUpdate->second = pStepUpdateSrc->second;
    }

  ObjectBalance::const_iterator it = src.mObjectBalance.begin();
  ObjectBalance::const_iterator end = src.mObjectBalance.end();

  for (; it != end; ++it)
    {
      mObjectBalance.insert(std::pair < const CObjectInterface *, C_FLOAT64 >(it->first + objectOffset, it->second));
    }
}

void CMathReaction::fire()
{
  SpeciesBalance * pStepUpdate = mNumberBalance.array();
  SpeciesBalance * pStepUpdateEnd = pStepUpdate + mNumberBalance.size();

  for (; pStepUpdate != pStepUpdateEnd; ++pStepUpdate)
    {
      *pStepUpdate->first += pStepUpdate->second;
    }
}

void CMathReaction::fireMultiple(const C_FLOAT64 & count)
{
  SpeciesBalance * pStepUpdate = mNumberBalance.array();
  SpeciesBalance * pStepUpdateEnd = pStepUpdate + mNumberBalance.size();

  for (; pStepUpdate != pStepUpdateEnd; ++pStepUpdate)
    {
      *pStepUpdate->first += pStepUpdate->second * count;
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

const CObjectInterface::ObjectSet & CMathReaction::getChangedObjects() const
{
  return mChangedSpecies;
}

const CMathReaction::Balance & CMathReaction::getNumberBalance() const
{
  return mNumberBalance;
}

const CReaction * CMathReaction::getModelReaction() const
{
  return mpReaction;
}

bool CMathReaction::isFast() const
{
  return (mpReaction != NULL && mpReaction->isFast());
}
