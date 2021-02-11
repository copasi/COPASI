// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

#include "CMathReaction.h"
#include "CMathContainer.h"

#include "copasi/model/CReaction.h"

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

  mObjectBalance.clear();
  mChangedSpecies.clear();
  mNumberBalance.resize(mpReaction->getChemEq().getBalances().size());
  SpeciesBalance * pStepUpdate = mNumberBalance.array();
  CDataVector < CChemEqElement >::const_iterator it = mpReaction->getChemEq().getBalances().begin();
  CDataVector < CChemEqElement >::const_iterator end = mpReaction->getChemEq().getBalances().end();

  for (; it != end; ++it)
    {
      const CMetab * pMetab = it->getMetabolite();

      if (pMetab != NULL)
        {
          CMathObject * pParticleNumber = container.getMathObject(pMetab->getValueReference());

          if (pParticleNumber->getSimulationType() == CMath::SimulationType::Independent ||
              pParticleNumber->getSimulationType() == CMath::SimulationType::Dependent)
            {
              mChangedSpecies.insert(pParticleNumber);
              mObjectBalance.insert(std::pair < const CMathObject *, C_FLOAT64 >(pParticleNumber, it->getMultiplicity()));
              pStepUpdate->first = (C_FLOAT64 *) pParticleNumber->getValuePointer();
              pStepUpdate->second = it->getMultiplicity();

              ++pStepUpdate;
            }
        }
    }

  mNumberBalance.resize(mChangedSpecies.size(), true);
}

void CMathReaction::copy(const CMathReaction & src,
                         CMathContainer & /* container */)
{
  assert(&src != this);
  *this = src;
}

void CMathReaction::relocate(const CMathContainer * pContainer,
                             const std::vector< CMath::sRelocate > & relocations)
{
  pContainer->relocateObject(mpParticleFlux, relocations);
  pContainer->relocateObject(mpFlux, relocations);
  pContainer->relocateObject(mpPropensity, relocations);
  pContainer->relocateObjectSet(mChangedSpecies, relocations);

  // std::set< std::pair < const CMathObject *, C_FLOAT64 > > ObjectBalance;
  ObjectBalance ObjectBalance;
  ObjectBalance::iterator itObjectBalance = mObjectBalance.begin();
  ObjectBalance::iterator endObjectBalance = mObjectBalance.end();

  for (; itObjectBalance != endObjectBalance; ++itObjectBalance)
    {
      const CMathObject * pObject = itObjectBalance->first;
      pContainer->relocateObject(pObject, relocations);

      ObjectBalance.insert(std::make_pair(pObject, itObjectBalance->second));
    }

  mObjectBalance = ObjectBalance;

  std::pair< C_FLOAT64 *, C_FLOAT64 > * pNumberBalance = mNumberBalance.array();
  std::pair< C_FLOAT64 *, C_FLOAT64 > * pNumberBalanceEnd = pNumberBalance + mNumberBalance.size();

  for (; pNumberBalance != pNumberBalanceEnd; ++pNumberBalance)
    {
      pContainer->relocateValue(pNumberBalance->first, relocations);
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

const CMathReaction::ObjectBalance & CMathReaction::getObjectBalance() const
{
  return mObjectBalance;
}

const CReaction * CMathReaction::getModelReaction() const
{
  return mpReaction;
}

bool CMathReaction::isFast() const
{
  return (mpReaction != NULL && mpReaction->isFast());
}
