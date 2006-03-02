/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CState.h,v $
   $Revision: 1.27 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/02 02:22:53 $
   End CVS Header */

/**
 *  CState class.
 *  The class CState stores the state in time of a model. The state 
 *  is described for the full model, i.e., updates of all internal
 *  metabolites is expected. The order of metabolites is as in the vector
 *  retrieved by CModel::getMetabolites. 
 *  The information is intended to be used with integration routines,
 *  but is not restricted to those.
 *
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CState
#define COPASI_CState

#include <map>

#include "utilities/CVector.h"

class CState;
class CModelEntity;

/** @dia:pos 127.851,-24.3708 */
class CStateTemplate
  {
    // Operations
  private:
    CStateTemplate();

  public:
    CStateTemplate(CState & initialState,
                   CState & currentState);
    ~CStateTemplate();

    void add(CModelEntity * entity);
    void remove(CModelEntity * entity);
    unsigned C_INT32 getIndex(CModelEntity * entity) const;
    void reorder(const CVector< CModelEntity * > & entitiesX);
    void setUserOrder(const CVector< CModelEntity * > & entities);
    const CVector<unsigned C_INT32> & getUserOrder() const;

    CModelEntity ** getEntities();
    CModelEntity ** CStateTemplate::beginIndependent();
    CModelEntity ** CStateTemplate::endIndependent();
    CModelEntity ** CStateTemplate::beginDependent();
    CModelEntity ** CStateTemplate::endDependent();
    CModelEntity ** CStateTemplate::beginFixed();
    CModelEntity ** CStateTemplate::endFixed();

    CModelEntity **const CStateTemplate::beginIndependent() const;
    CModelEntity **const CStateTemplate::endIndependent() const;
    CModelEntity **const CStateTemplate::beginDependent() const;
    CModelEntity **const CStateTemplate::endDependent() const;
    CModelEntity **const CStateTemplate::beginFixed() const;
    CModelEntity **const CStateTemplate::endFixed() const;

    unsigned C_INT32 CStateTemplate::getNumIndependent() const;
    unsigned C_INT32 CStateTemplate::getNumDependent() const;
    unsigned C_INT32 CStateTemplate::getNumVariable() const;
    unsigned C_INT32 CStateTemplate::getNumFixed() const;

    const unsigned C_INT32 & size() const;

  protected:
    void resize();

    // Attributes
  private:
    CState & mInitialState;
    CState & mCurrentState;
    CModelEntity ** mpEntities;
    unsigned C_INT32 mSize;
    CModelEntity ** mpBeginIndependent;
    CModelEntity ** mpBeginDependent;
    CModelEntity ** mpBeginFixed;
    CModelEntity ** mpEnd;
    unsigned C_INT32 mInsert;
    std::map< CModelEntity *, unsigned C_INT32 > mIndexMap;
    CVector<unsigned C_INT32> mUserOrder;
    C_FLOAT64 * mpInitialValues;
    C_FLOAT64 * mpCurrentValues;
  };

class CState
  {
  public:
    CState();
    CState(const CState & src);
    ~CState();

    CState & operator=(const CState & rhs);

    const C_FLOAT64 & getTime() const;
    void setTime(const C_FLOAT64 & time);

    C_FLOAT64 * beginIndependent();
    C_FLOAT64 * endIndependent();
    C_FLOAT64 * beginDependent();
    C_FLOAT64 * endDependent();
    C_FLOAT64 * beginFixed();
    C_FLOAT64 * endFixed();

    const C_FLOAT64 * beginIndependent() const;
    const C_FLOAT64 * endIndependent() const;
    const C_FLOAT64 * beginDependent() const;
    const C_FLOAT64 * endDependent() const;
    const C_FLOAT64 * beginFixed() const;
    const C_FLOAT64 * endFixed() const;

    unsigned C_INT32 getNumIndependent() const;
    unsigned C_INT32 getNumDependent() const;
    unsigned C_INT32 getNumVariable() const;
    unsigned C_INT32 getNumFixed() const;

    void setUpdateDependentRequired(const bool & required);
    const bool & isUpdateDependentRequired() const;

  protected:
    // These methods are only accessible from CStateTemplate
    friend class CStateTemplate;
    C_FLOAT64 * resize(const unsigned C_INT32 & size);
    void updateIterator(const unsigned C_INT32 & numIndependent,
                        const unsigned C_INT32 & numDependent,
                        const unsigned C_INT32 & numFixed);

  private:
    C_FLOAT64 * mpValues;
    unsigned C_INT32 mSize;
    C_FLOAT64 * mpBeginIndependent;
    C_FLOAT64 * mpBeginDependent;
    C_FLOAT64 * mpBeginFixed;
    C_FLOAT64 * mpEnd;
    bool mUpdateDependentRequired;

#ifdef COPASI_DEBUG
  public:
    void check(const std::string & m = "") const;
#endif
  };

#ifdef XXXX

/**
 * Calculates the jacobian of the state and stores it in the provided 
 * matrix.
 * @param CMatrix< C_FLOAT64 > & jacobian
 * @param const C_FLOAT64 & factor,
 * @param const C_FLOAT64 & resolution
 */
virtual void calculateJacobian(CMatrix< C_FLOAT64 > & jacobian,
                               const C_FLOAT64 & factor,
                               const C_FLOAT64 & resolution) const;

/**
 * Calculates the elasticity Matrix of the state and stores it in the 
 * provided matrix.
 * @param CMatrix< C_FLOAT64 > & elasticityMatrix
 * @param const C_FLOAT64 & factor,
 * @param const C_FLOAT64 & resolution
 */
virtual void calculateElasticityMatrix(CMatrix< C_FLOAT64 > & elasticityMatrix,
                                       const C_FLOAT64 & factor,
                                       const C_FLOAT64 & resolution) const;

/**
 * Calculate the jacobian of the state and store it in the provided matrix.
 * @param C_FLOAT64 * jacobian
 * @param const C_FLOAT64 & factor,
 * @param const C_FLOAT64 & resolution
 */
virtual void calculateJacobian(CMatrix< C_FLOAT64 > & jacobian,
                               const C_FLOAT64 & factor,
                               const C_FLOAT64 & resolution) const;

/**
 * Calculates the elasticity Matrix of the state and stores it in the 
 * provided matrix.
 * @param CMatrix< C_FLOAT64 > & elasticityMatrix
 * @param const C_FLOAT64 & factor,
 * @param const C_FLOAT64 & resolution
 */
virtual void calculateElasticityMatrix(CMatrix< C_FLOAT64 > & elasticityMatrix,
                                       const C_FLOAT64 & factor,
                                       const C_FLOAT64 & resolution) const;

#endif // XXXX

#endif
