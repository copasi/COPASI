// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CState class.
 *  The class CState stores the state in time of a model. The state
 *  is described for the full model, i.e., updates of all internal
 *  metabolites is expected. The order of metabolites is as in the vector
 *  retrieved by CModel::getMetabolites.
 *  The information is intended to be used with integration routines,
 *  but is not restricted to those.
 *
 *  Created for COPASI by Stefan Hoops 2002
 */

#ifndef COPASI_CState
#define COPASI_CState

#include <map>

#include "copasi/core/CVector.h"

class CState;
class CModel;
class CModelEntity;

class CStateTemplate
{
  // Operations
private:
  /**
   * Default Constructor (inaccessible)
   */
  CStateTemplate();

public:
  /**
   * Specific constructor
   * @param CModel & model
   */
  CStateTemplate(CModel & model);

  /**
   * Destructor
   */
  ~CStateTemplate();

  /**
   * Add an entity to the template.
   * @param const CModelEntity * entity
   */
  void add(const CModelEntity * entity);

  /**
   * Remove an entity from the template.
   * @param const CModelEntity * entity
   */
  void remove(const CModelEntity * entity);

  /**
   * Retrieve the index of an entity in the template.
   * Returns C_INVALID_INDEX if the entity is not found.
   * @param const CModelEntity * entity
   * @return size_t index
   */
  size_t getIndex(const CModelEntity * entity) const;

  /**
   * Reorder the template.
   * @param const CVector< const CModelEntity * > & newOrder
   */
  void reorder(const CVector< CModelEntity * > & newOrder);

  /**
   * Set the user preferred order of the entities.
   * @param const CVector< const CModelEntity * > & userOrder
   */
  void setUserOrder(const CVector< const CModelEntity * > & userOrder);

  /**
   * Retrieve a pivot vector which can be used to reconstruct the user order.
   * @return const CVector<size_t> & userOrder
   */
  const CVector<size_t> & getUserOrder() const;

  /**
   * Retrieve the array of pointers to all independent entities.
   * @return CModelEntities ** independentEntities
   */
  const CModelEntity *const* beginIndependent() const;

  /**
   * Retrieve pointer just beyond the independent entities.
   * @return CModelEntities ** endIndependentEntities
   */
  const CModelEntity *const* endIndependent() const;

  /**
   * Retrieve the array of pointers to all dependent entities,
   * which are only dependent species for a reduced model.
   * @return CModelEntities ** dependentEntities
   */
  const CModelEntity *const* beginDependent() const;

  /**
   * Retrieve pointer just beyond the dependent entities.
   * @return CModelEntities ** endDependentEntities
   */
  const CModelEntity *const* endDependent() const;

  /**
   * Retrieve the array of pointers to all fixed entities.
   * @return CModelEntities ** fixedEntities
   */
  const CModelEntity *const* beginFixed() const;

  /**
   * Retrieve pointer just beyond the fixed entities.
   * @return CModelEntities ** endFixedEntities
   */
  const CModelEntity *const* endFixed() const;

  /**
   * Retrieve the array of pointers to all entities.
   * @return const CVector< const CModelEntity *> & entities
   */
  const CVector< const CModelEntity *> &  getEntities() const;

  /**
   * Retrieve the number of independent entities.
   * @return size_t numIndependent
   */
  size_t getNumIndependent() const;

  /**
   * Retrieve the number of dependent entities.
   * @return size_t numDependent
   */
  size_t getNumDependent() const;

  /**
   * Retrieve the number of variable entities, i.e., the sum of
   * independent and dependent variables.
   * @return size_t numVariable
   */
  size_t getNumVariable() const;

  /**
   * Retrieve the number of fixed entities.
   * @return size_t numFixed
   */
  size_t getNumFixed() const;

  /**
   * Retrieve size of the template, i.e., the number of entities.
   * @return size_t size
   */
  const size_t & size() const;

protected:
  /**
   * Resize the template
   */
  void resize();

  // Attributes
private:
  /**
   * A reference to the model
   */
  CModel & mModel;

  /**
   * The array of entities
   */
  CVector< const CModelEntity * > mEntities;

  /**
   * The allocate size of the template
   */
  size_t mSize;

  /**
   * A pointer to the independent entities
   */
  const CModelEntity *const* mpBeginIndependent;

  /**
   * A pointer to the dependent entities
   */
  const CModelEntity *const* mpBeginDependent;

  /**
   * A pointer to the fixed entities
   */
  const CModelEntity *const* mpBeginFixed;

  /**
   * A pointer just beyond the entities
   */
  const CModelEntity *const* mpEnd;

  /**
   * The index in which the next added entity must be inserted.
   */
  size_t mInsert;

  /**
   * A map of pointer to entities to the index it appear in the template
   */
  std::map< const CModelEntity *, size_t > mIndexMap;

  /**
   * A pivot vector storing the user order of the entities
   */
  CVector<size_t> mUserOrder;
};

#endif
