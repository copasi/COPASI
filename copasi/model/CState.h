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

class CState
  {
    friend class CStateX;

  protected:
    // Attributes
    /**
     *
     */
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
    CParticleNumberList mFixedNumbers;

    /**
     *
     */
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
     * Calculate the jacobian of the state and store it in the provided matrix.
     * @param C_FLOAT64 * jacobian
     * @param const C_FLOAT64 & factor,
     * @param const C_FLOAT64 & resolution
     */
    virtual void getJacobian(CMatrix< C_FLOAT64 > & jacobian,
                             const C_FLOAT64 & factor,
                             const C_FLOAT64 & resolution) const;

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

class CStateX: public CState
  {
    friend class CState;

  protected:
    // Attributes

    // Associations

    /**
     *
     */
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
