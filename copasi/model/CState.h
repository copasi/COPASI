/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CState.h,v $
   $Revision: 1.19 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/03 20:47:26 $
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

#include "CParticleNumberList.h"

class CReadConfig;
class CWriteConfig;
class CModel;
class CStateX;

template <class CType> class CMatrix;

/** @dia:pos 127.601,-24.3708 */
class CState
  {
    friend class CStateX;

  protected:
    // Attributes
    /**
     *
     */
    /** @dia:route 0,2; h,177.081,30.2423,172.597,-24.3708,169.315 */
    const CModel * mpModel;

    /**
     *
     */
    C_FLOAT64 mTime;

    /**
     *
     */
    CVector< C_FLOAT64 > mVolumes;

    // Associations

    /**
     *
     */
    /** @dia:route 2,0; h,118.692,-19.4621,125.683,-24.3708,127.601 */
    CParticleNumberList mFixedNumbers;

    /**
     *
     */
    /** @dia:route 9,0; h,118.692,-17.5621,125.683,-24.3708,127.601 */
    CParticleNumberList mVariableNumbers;

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
     * Load a state
     * @param "CReadConfig &" configBuffer
     */
    virtual void load(CReadConfig & configBuffer);

    /**
     * Save a state
     * @param "CWriteConfig &" configBuffer
     */
    virtual void save(CWriteConfig & configBuffer) const;

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
    const CVector< C_FLOAT64 > & getFixedNumberVectorDbl() const;

    /**
     *
     */
    const CVector< C_INT32 > & getFixedNumberVectorInt() const;

    /**
     *
     */
    const C_FLOAT64 & getFixedNumberDbl(const unsigned C_INT32 & index) const;

    /**
     *
     */
    const C_INT32 & getFixedNumberInt(const unsigned C_INT32 & index) const;

    /**
     *
     */
    const unsigned C_INT32 & getFixedNumberSize() const;

    /**
     *
     */
    const CVector< C_FLOAT64 > & getVariableNumberVectorDbl() const;

    /**
     *
     */
    const CVector< C_INT32 > & getVariableNumberVectorInt() const;

    /**
     *
     */
    const C_FLOAT64 & getVariableNumberDbl(const unsigned C_INT32 & index) const;

    /**
     *
     */
    const C_INT32 & getVariableNumberInt(const unsigned C_INT32 & index) const;

    /**
     *
     */
    const unsigned C_INT32 & getVariableNumberSize() const;

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
    void setFixedNumber(const unsigned C_INT32 & index, const C_INT32 & value);

    /**
     *
     */
    void setFixedNumber(const unsigned C_INT32 & index, const C_FLOAT64 & value);

    /**
     *
     */
    void setFixedNumberVector(const CVector< C_INT32 > & vektor);

    /**
     *
     */
    void setFixedNumberVector(const CVector< C_FLOAT64 > & vektor);

    /**
     *
     */
    void setVariableNumber(const unsigned C_INT32 & index, const C_INT32 & value);

    /**
     *
     */
    void setVariableNumber(const unsigned C_INT32 & index, const C_FLOAT64 & value);

    /**
     *
     */
    void setVariableNumberVector(const CVector< C_INT32 > & vektor);

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
    virtual void getJacobian(CMatrix< C_FLOAT64 > & jacobian,
                             const C_FLOAT64 & factor,
                             const C_FLOAT64 & resolution) const;

    /**
     * Calculates the elasticity Matrix of the state and stores it in the 
     * provided matrix.
     * @param CMatrix< C_FLOAT64 > & elasticityMatrix
     * @param const C_FLOAT64 & factor,
     * @param const C_FLOAT64 & resolution
     */
    virtual void getElasticityMatrix(CMatrix< C_FLOAT64 > & elasticityMatrix,
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
    virtual void getJacobianProtected(CMatrix< C_FLOAT64 > & jacobian,
                                      const C_FLOAT64 & factor,
                                      const C_FLOAT64 & resolution);
  };

/** @dia:pos 127.547,11.4075 */
/** @dia:route CState; v,148.458,9.42919,13.5356,148.667,11.4075 */
class CStateX: public CState
  {
    friend class CState;

  protected:
    // Attributes

    // Associations

    /**
     *
     */
    /** @dia:route 13,0; h,118.692,-15.9621,125.604,11.4075,127.547 */
    CParticleNumberList mDependentNumbers;

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
     * Load a state
     * @param "CReadConfig &" configBuffer
     */
    virtual void load(CReadConfig & configBuffer);

    /**
     * Save a state
     * @param "CWriteConfig &" configBuffer
     * @param "const CState * pState
     */
    virtual void save(CWriteConfig & configBuffer);

    /**
     *
     */
    virtual void setModel(const CModel * pModel);

    /**
     *
     */
    const CVector< C_FLOAT64 > & getDependentNumberVectorDbl() const;

    /**
     *
     */
    const CVector< C_INT32 > & getDependentNumberVectorInt() const;

    /**
     *
     */
    const C_FLOAT64 & getDependentNumberDbl(const unsigned C_INT32 & index) const;

    /**
     *
     */
    const C_INT32 & getDependentNumberInt(const unsigned C_INT32 & index) const;

    /**
     *
     */
    const unsigned C_INT32 & getDependentNumberSize()const;

    /**
     *
     */
    void setDependentNumber(const unsigned C_INT32 & index,
                            const C_INT32 & value);

    /**
     *
     */
    void setDependentNumber(const unsigned C_INT32 & index,
                            const C_FLOAT64 & value);

    /**
     *
     */
    void setDependentNumberVector(const CVector< C_INT32 > & vektor);

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
    virtual void getJacobian(CMatrix< C_FLOAT64 > & jacobian,
                             const C_FLOAT64 & factor,
                             const C_FLOAT64 & resolution) const;

    /**
     * Calculates the elasticity Matrix of the state and stores it in the 
     * provided matrix.
     * @param CMatrix< C_FLOAT64 > & elasticityMatrix
     * @param const C_FLOAT64 & factor,
     * @param const C_FLOAT64 & resolution
     */
    virtual void getElasticityMatrix(CMatrix< C_FLOAT64 > & elasticityMatrix,
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
    virtual void getJacobianProtected(CMatrix< C_FLOAT64 > & jacobian,
                                      const C_FLOAT64 & factor,
                                      const C_FLOAT64 & resolution);
  };

#endif
