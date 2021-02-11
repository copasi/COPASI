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

#ifndef COPASI_CMathReaction
#define COPASI_CMathReaction

#include <utility>

#include "copasi/math/CMathEnum.h"
#include "copasi/core/CDataObject.h"
#include "copasi/core/CVector.h"

class CReaction;
class CMathObject;
class CMathContainer;

class CMathReaction
{
public:
  typedef std::set< std::pair < const CMathObject *, C_FLOAT64 > > ObjectBalance;
  typedef std::pair< C_FLOAT64 *, C_FLOAT64 > SpeciesBalance;
  typedef CVector< std::pair< C_FLOAT64 *, C_FLOAT64 > > Balance;
  /**
   * Constructor
   */
  CMathReaction();

  /**
   * Copy constructor
   */
  CMathReaction(const CMathReaction & src);

  /**
   * Destructor
   */
  ~CMathReaction();

  /**
   * Initialize the reaction from the model reaction in the given container context
   * @param const CReaction * pReaction
   * @param CMathContainer & container
   */
  void initialize(const CReaction * pReaction, CMathContainer & container);

  /**
   * Copy an existing object
   * @param const CMathReaction & src
   * @param CMathContainer & container
   */
  void copy(const CMathReaction & src, CMathContainer & container);

  /**
   * The objects and values are relocated
   * @param const CMathContainer * pContainer
   * @param const std::vector< CMath::sRelocate > & relocations
   */
  void relocate(const CMathContainer * pContainer,
                const std::vector< CMath::sRelocate > & relocations);

  /**
   * Fire the reaction count times. Note count must not necessarily be an integer
   */
  void fire();

  /**
   * Fire the reaction count times. Note count must not necessarily be an integer
   * @param const C_FLOAT64 & count
   */
  void fireMultiple(const C_FLOAT64 & count);

  /**
   * Retrieve a pointer to the mathematical object for the particle flux.
   * @return const CMathObject * pParticleFluxObject
   */
  const CMathObject * getParticleFluxObject() const;

  /**
   * Retrieve a pointer to the mathematical object for the flux.
   * @return const CMathObject * pFluxObject
   */
  const CMathObject * getFluxObject() const;

  /**
   * Retrieve a pointer to the mathematical object for the propensity.
   * @return const CMathObject * pPropensityObject
   */
  const CMathObject * getPropensityObject() const;

  /**
   * Retrieve the set of particle number objects changed when the reaction fires.
   * @return const CObjectInterface::ObjectSet & changedObjects
   */
  const CObjectInterface::ObjectSet & getChangedObjects() const;

  /**
   * Retrieve the set of modified species
   * @return const CMathReaction::Balance & balance
   */
  const Balance & getNumberBalance() const;

  /**
   * Retrieve the set of modified species objects
   * @return CMathReaction::ObjectBalance & objectBalance
   */
  const ObjectBalance & getObjectBalance() const;

  /**
   * Retrieve a pointer to the model reaction
   * @return const CReaction * pModelReaction
   */
  const CReaction * getModelReaction() const;

  /**
   * Check whether the reaction is fast
   * @return bool isFast
   */
  bool isFast() const;

private:
  /**
   * A pointer to model reaction.
   */
  const CReaction * mpReaction;

  /**
   * A pointer to the mathematical particle flux.
   */
  CMathObject * mpParticleFlux;

  /**
   * A pointer to the mathematical flux.
   */
  CMathObject * mpFlux;

  /**
   * A pointer to the mathematical propensity.
   */
  CMathObject * mpPropensity;

  /**
   * The set of changed species
   */
  CObjectInterface::ObjectSet mChangedSpecies;

  /**
   * The set of modified species and their change per reaction event
   */
  ObjectBalance mObjectBalance;

  /**
   * Information for updating the species particle numbers when the
   * reaction fires.
   */
  Balance mNumberBalance;
};

#endif // COPASI_CMathReaction
