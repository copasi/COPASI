/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CState.h,v $
   $Revision: 1.24 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/03 09:56:11 $
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

#include "utilities/CVector.h"

class CModel;
class CStateX;

template <class CType> class CMatrix;

/** @dia:pos 127.851,-24.3708 */
class CState
  {
    friend class CStateX;

  protected:
    // Attributes
    /**
     *
     */
    /** @dia:route 0,2; h,177.081,30.2423,166.416,-24.3708,155.751 */
    const CModel * mpModel;

    /**
     *
     */
    C_FLOAT64 mTime;

    /**
     *
     */
    CVector< C_FLOAT64 > mVolumes;

    /**
     *
     */
    /** @dia:route 2,0; h,107.298,-19.4621,117.574,-24.3708,127.851 */
    CVector< C_FLOAT64 > mFixedNumbers;

    /**
     *
     */
    /** @dia:route 9,0; h,107.298,-17.5621,117.574,-24.3708,127.851 */
    CVector< C_FLOAT64 > mVariableNumbers;

    // Operations
  public:
    /**
     *
     */
    CState(const CModel * pModel = NULL);

    /**
     *
     */
    CState(const CState & state);

    /**
     *
     */
    CState(const CStateX & stateX);

    /**
     *
     */
    virtual ~CState();

    /**
     *
     */
    CState & operator =(const CState & state);

    /**
     *
     */
    CState & operator =(const CStateX & stateX);

    /**
     *
     */
    virtual void setModel(const CModel * pModel);

    /**
     *
     */
    const CModel * getModel() const;

    /**
     *
     */
    void setTime(const C_FLOAT64 & time);

    /**
     *
     */
    const C_FLOAT64 & getTime() const;

    /**
     *
     */
    const CVector< C_FLOAT64 > & getFixedNumberVector() const;

    /**
     *
     */
    const C_FLOAT64 & getFixedNumber(const unsigned C_INT32 & index) const;

    /**
     *
     */
    unsigned C_INT32 getFixedNumberSize() const;

    /**
     *
     */
    const CVector< C_FLOAT64 > & getVariableNumberVector() const;

    /**
     *
     */
    const C_FLOAT64 & getVariableNumber(const unsigned C_INT32 & index) const;

    /**
     *
     */
    unsigned C_INT32 getVariableNumberSize() const;

    /**
     *
     */
    const C_FLOAT64 & getVolume(const unsigned C_INT32 & index) const;

    /**
     *
     */
    const CVector< C_FLOAT64 > & getVolumeVector() const;

    /**
     *
     */
    unsigned C_INT32 getVolumeSize() const;

    /**
     *
     */
    void setFixedNumber(const unsigned C_INT32 & index, const C_FLOAT64 & value);

    /**
     *
     */
    void setFixedNumberVector(const CVector< C_FLOAT64 > & vektor);

    /**
     *
     */
    void setVariableNumber(const unsigned C_INT32 & index, const C_FLOAT64 & value);

    /**
     *
     */
    void setVariableNumberVector(const CVector< C_FLOAT64 > & vektor);

    /**
     *
     */
    void setVolume(const unsigned C_INT32 & index, const C_FLOAT64 & value);

    /**
     *
     */
    void setVolumeVector(const CVector< C_FLOAT64 > & vektor);

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

    friend std::ostream & operator << (std::ostream & os, const CState & A);

  protected:
    /**
     * Calculate the jacobian of the state and store it in the provided matrix.
     * @param CMatrix< C_FLOAT64 > & jacobian
     * @param const C_FLOAT64 & factor,
     * @param const C_FLOAT64 & resolution
     */
    /* virtual void getJacobianProtected(CMatrix< C_FLOAT64 > & jacobian,
                                       const C_FLOAT64 & factor,
                                       const C_FLOAT64 & resolution);*/
  };

//**********************************************************************************************************

/** @dia:pos 127.956,11.9075 */
class CStateX: public CState
  {
    friend class CState;

  protected:
    // Attributes

    /**
     *
     */
    /** @dia:route 13,0; h,107.298,-15.9621,117.627,11.9075,127.956 */
    CVector< C_FLOAT64 > mDependentNumbers;

    // Operations
  public:
    /**
     *
     */
    CStateX(const CModel * pModel = NULL);

    /**
     *
     */
    CStateX(const CState & state);

    /**
     *
     */
    CStateX(const CStateX & stateX);

    /**
     *
     */
    virtual ~CStateX();

    /**
     *
     */
    CStateX & operator =(const CState & state);

    /**
     *
     */
    CStateX & operator =(const CStateX & stateX);

    /**
     *
     */
    virtual void setModel(const CModel * pModel);

    /**
     *
     */
    const CVector< C_FLOAT64 > & getDependentNumberVector() const;

    /**
     *
     */
    const C_FLOAT64 & getDependentNumber(const unsigned C_INT32 & index) const;

    /**
     *
     */
    unsigned C_INT32 getDependentNumberSize()const;

    /**
     *
     */
    void setDependentNumber(const unsigned C_INT32 & index,
                            const C_FLOAT64 & value);

    /**
     *
     */
    void setDependentNumberVector(const CVector< C_FLOAT64 > & vektor);

    /**
     *
     */
    void updateDependentNumbers();

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

    friend std::ostream & operator << (std::ostream & os, const CStateX & A);

  protected:
    /**
     * Calculate the jacobian of the state and store it in the provided matrix.
     * @param C_FLOAT64 * jacobian
     * @param const C_FLOAT64 & factor,
     * @param const C_FLOAT64 & resolution
     */
    /*virtual void getJacobianProtected(CMatrix< C_FLOAT64 > & jacobian,
                                      const C_FLOAT64 & factor,
                                      const C_FLOAT64 & resolution);*/
  };

#endif
