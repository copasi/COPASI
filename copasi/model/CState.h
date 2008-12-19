// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CState.h,v $
//   $Revision: 1.35.8.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/11/12 18:43:06 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include "utilities/CVector.h"

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
     * @param CState & initialState
     * @param CState & currentState
     */
    CStateTemplate(CModel & model,
                   CState & initialState,
                   CState & currentState);

    /**
     * Destructor
     */
    ~CStateTemplate();

    /**
     * Add an entity to the template.
     * @param CModelEntity * entity
     */
    void add(CModelEntity * entity);

    /**
     * Remove an entity from the template.
     * @param CModelEntity * entity
     */
    void remove(CModelEntity * entity);

    /**
     * Retrieve the index of an entity in the template.
     * Returns C_INVALID_INDEX if the entity is not found.
     * @param const CModelEntity * entity
     * @return unsigned C_INT32 index
     */
    unsigned C_INT32 getIndex(const CModelEntity * entity) const;

    /**
     * Reorder the template.
     * @param const CVector< CModelEntity * > & newOrder
     */
    void reorder(const CVector< CModelEntity * > & newOrder);

    /**
     * Set the user preferred order of the entities.
     * @param const CVector< CModelEntity * > & userOrder
     */
    void setUserOrder(const CVector< CModelEntity * > & userOrder);

    /**
     * Retrieve a pivot vector which can be used to reconstruct the user order.
     * @return const CVector<unsigned C_INT32> & userOrder
     */
    const CVector<unsigned C_INT32> & getUserOrder() const;

    /**
     * Retrieve the array of pointers to all entities.
     * @return CModelEntities ** entities
     */
    CModelEntity ** getEntities();

    /**
     * Retrieve the array of pointers to all independent entities.
     * @return CModelEntities ** independentEntities
     */
    CModelEntity ** beginIndependent();

    /**
     * Retrieve pointer just beyond the independent entities.
     * @return CModelEntities ** endIndependentEntities
     */
    CModelEntity ** endIndependent();

    /**
     * Retrieve the array of pointers to all dependent entities,
     * which are only dependent species for a reduced model.
     * @return CModelEntities ** dependentEntities
     */
    CModelEntity ** beginDependent();

    /**
     * Retrieve pointer just beyond the dependent entities.
     * @return CModelEntities ** endDependentEntities
     */
    CModelEntity ** endDependent();

    /**
     * Retrieve the array of pointers to all fixed entities.
     * @return CModelEntities ** fixedEntities
     */
    CModelEntity ** beginFixed();

    /**
     * Retrieve pointer just beyond the fixed entities.
     * @return CModelEntities ** endFixedEntities
     */
    CModelEntity ** endFixed();

    /**
     * Retrieve the array of pointers to all entities.
     * @return CModelEntities *const* entities
     */
    CModelEntity *const* getEntities() const;

    /**
     * Retrieve the array of pointers to all independent entities.
     * @return CModelEntities *const* independentEntities
     */
    CModelEntity *const* beginIndependent() const;

    /**
     * Retrieve pointer just beyond the independent entities.
     * @return CModelEntities *const* endIndependentEntities
     */
    CModelEntity *const* endIndependent() const;

    /**
     * Retrieve the array of pointers to all dependent entities,
     * which are only dependent species for a reduced model.
     * @return CModelEntities *const* dependentEntities
     */
    CModelEntity *const* beginDependent() const;

    /**
     * Retrieve pointer just beyond the dependent entities.
     * @return CModelEntities ** endDependentEntities
     */
    CModelEntity *const* endDependent() const;

    /**
     * Retrieve the array of pointers to all fixed entities.
     * @return CModelEntities *const* fixedEntities
     */
    CModelEntity *const* beginFixed() const;

    /**
     * Retrieve pointer just beyond the fixed entities.
     * @return CModelEntities *const* endFixedEntities
     */
    CModelEntity *const* endFixed() const;

    /**
     * Retrieve the number of independent entities.
     * @return unsigned C_INT32 numIndependent
     */
    unsigned C_INT32 getNumIndependent() const;

    /**
     * Retrieve the number of dependent entities.
     * @return unsigned C_INT32 numDependent
     */
    unsigned C_INT32 getNumDependent() const;

    /**
     * Retrieve the number of variable entities, i.e., the sum of
     * independent and dependent variables.
     * @return unsigned C_INT32 numVariable
     */
    unsigned C_INT32 getNumVariable() const;

    /**
     * Retrieve the number of fixed entities.
     * @return unsigned C_INT32 numFixed
     */
    unsigned C_INT32 getNumFixed() const;

    /**
     * Retrieve size of the template, i.e., the number of entities.
     * @return unsigned C_INT32 size
     */
    const unsigned C_INT32 & size() const;

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
     * A reference to the initial state of the model
     */
    CState & mInitialState;

    /**
     * A reference to the current state of the model
     */
    CState & mCurrentState;

    /**
     * The array of entities
     */
    CModelEntity ** mpEntities;

    /**
     * The allocate size of the template
     */
    unsigned C_INT32 mSize;

    /**
     * A pointer to the independent entities
     */
    CModelEntity ** mpBeginIndependent;

    /**
     * A pointer to the dependent entities
     */
    CModelEntity ** mpBeginDependent;

    /**
     * A pointer to the fixed entities
     */
    CModelEntity ** mpBeginFixed;

    /**
     * A pointer just beyond the entities
     */
    CModelEntity ** mpEnd;

    /**
     * The index in which the next added entity must be inserted.
     */
    unsigned C_INT32 mInsert;

    /**
     * A map of pointer to entities to the index it appear in the template
     */
    std::map< CModelEntity *, unsigned C_INT32 > mIndexMap;

    /**
     * A pivot vector storing the user order of the entities
     */
    CVector<unsigned C_INT32> mUserOrder;

    /**
     * The array of initial values of all entities
     */
    C_FLOAT64 * mpInitialValues;

    /**
     * The array of current values of all entities
     */
    C_FLOAT64 * mpCurrentValues;
  };

class CState
  {
  public:
    /**
     * Constructor
     */
    CState();

    /**
     * Copy constructor
     * @param const CState & src
     */
    CState(const CState & src);

    /**
     * Destructor
     */
    ~CState();

    /**
     * Assignment operator
     * @param const CState & rhs
     * @return CState & lhs
     */
    CState & operator=(const CState & rhs);

    /**
     * Retrieve the time of the state
     * @return const C_FLOAT64 & time
     */
    const C_FLOAT64 & getTime() const;

    /**
     * Set the time of the state
     * @param const C_FLOAT64 & time
     */
    void setTime(const C_FLOAT64 & time);

    /**
     * Retrieve the array of pointers of values of all independent entities.
     * @return C_FLOAT64 * independentValues
     */
    C_FLOAT64 * beginIndependent();

    /**
     * Retrieve pointer just beyond the values of all independent entities.
     * @return C_FLOAT64 * endIndependentValues
     */
    C_FLOAT64 * endIndependent();

    /**
     * Retrieve the array of pointers of values of all dependent entities,
     * which are only dependent species for a reduced model.
     * @return C_FLOAT64 * dependentValues
     */
    C_FLOAT64 * beginDependent();

    /**
     * Retrieve pointer just beyond the values of all dependent entities.
     * @return C_FLOAT64 * endDependentValues
     */
    C_FLOAT64 * endDependent();

    /**
     * Retrieve the array of pointers of values of all fixed entities.
     * @return C_FLOAT64 * fixedValues
     */
    C_FLOAT64 * beginFixed();

    /**
     * Retrieve pointer just beyond the values of all fixed entities.
     * @return C_FLOAT64 * endFixedValues
     */
    C_FLOAT64 * endFixed();

    /**
     * Retrieve the array of pointers of values of all independent entities.
     * @return const C_FLOAT64 * independentValues
     */
    const C_FLOAT64 * beginIndependent() const;

    /**
     * Retrieve pointer just beyond the values of all independent entities.
     * @return const C_FLOAT64 * endIndependentValues
     */
    const C_FLOAT64 * endIndependent() const;

    /**
     * Retrieve the array of pointers of values of all dependent entities,
     * which are only dependent species for a reduced model.
     * @return const C_FLOAT64 * dependentValues
     */
    const C_FLOAT64 * beginDependent() const;

    /**
     * Retrieve pointer just beyond the values of all dependent entities.
     * @return const C_FLOAT64 * endDependentValues
     */
    const C_FLOAT64 * endDependent() const;

    /**
     * Retrieve the array of pointers of values of all fixed entities.
     * @return const C_FLOAT64 * fixedValues
     */
    const C_FLOAT64 * beginFixed() const;

    /**
     * Retrieve pointer just beyond the values of all fixed entities.
     * @return const C_FLOAT64 * endFixedValues
     */
    const C_FLOAT64 * endFixed() const;

    /**
     * Retrieve the number of independent entities.
     * @return unsigned C_INT32 numIndependent
     */
    unsigned C_INT32 getNumIndependent() const;

    /**
     * Retrieve the number of dependent entities.
     * @return unsigned C_INT32 numDependent
     */
    unsigned C_INT32 getNumDependent() const;

    /**
     * Retrieve the number of variable entities, i.e., the sum of
     * independent and dependent variables.
     * @return unsigned C_INT32 numVariable
     */
    unsigned C_INT32 getNumVariable() const;

    /**
     * Retrieve the number of fixed entities.
     * @return unsigned C_INT32 numFixed
     */
    unsigned C_INT32 getNumFixed() const;

    /*
    void setUpdateDependentRequired(const bool & required);
    const bool & isUpdateDependentRequired() const;
    */

  protected:
    // These methods are only accessible from CStateTemplate
    friend class CStateTemplate;
    C_FLOAT64 * resize(const unsigned C_INT32 & size);

    /**
     * Update the pointers to the different types of entities
     * @param const unsigned C_INT32 & numIndependent
     * @param const unsigned C_INT32 & numDependent
     * @param const unsigned C_INT32 & numFixed
     */
    void updateIterator(const unsigned C_INT32 & numIndependent,
                        const unsigned C_INT32 & numDependent,
                        const unsigned C_INT32 & numFixed);

  private:
    /**
     * Array of entity values
     */
    C_FLOAT64 * mpValues;

    /**
     * Size of the state
     */
    unsigned C_INT32 mSize;

    /**
     * Pointer to the beginning of values of independent entities.
     */
    C_FLOAT64 * mpBeginIndependent;

    /**
     * Pointer to the beginning of values of dependent entities.
     */
    C_FLOAT64 * mpBeginDependent;

    /**
     * Pointer to the beginning of values of fixed entities.
     */
    C_FLOAT64 * mpBeginFixed;

    /**
     * Pointer just beyond the values of fixed entities.
     */
    C_FLOAT64 * mpEnd;

    /**
     * Indicates whether the state is of a reduced or complete model
     */
    bool mUpdateDependentRequired;
  };

#endif
