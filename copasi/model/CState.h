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

namespace TNT {template <class CType>
  class Matrix; }

class CState
  {
  protected:
    // Attributes
    const CModel * mpModel;
    C_FLOAT64 mTime;
    unsigned C_INT32 mVolumeSize;
    C_FLOAT64 * mVolumes;

    // Associations
    CParticleNumberList mVariableNumbers;
    CParticleNumberList mFixedNumbers;

    // Operations
  public:
    CState(const CModel * pModel = NULL);
    CState(const CState & state);
    CState(const CStateX & stateX);
    virtual ~CState();
    CState & operator =(const CState & state);
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

    virtual void setModel(const CModel * pModel);
    const CModel * getModel() const;
    void setTime(const C_FLOAT64 & time);
    const C_FLOAT64 & getTime() const;
    const C_FLOAT64 * getFixedNumberArrayDbl() const;
    const C_INT32 * getFixedNumberArrayInt() const;
    const C_FLOAT64 & getFixedNumberDbl(const unsigned C_INT32 & index) const;
    const C_INT32 & getFixedNumberInt(const unsigned C_INT32 & index) const;
    const unsigned C_INT32 & getFixedNumberSize() const;
    const C_FLOAT64 * getVariableNumberArrayDbl() const;
    const C_INT32 * getVariableNumberArrayInt() const;
    const C_FLOAT64 & getVariableNumberDbl(const unsigned C_INT32 & index) const;
    const C_INT32 & getVariableNumberInt(const unsigned C_INT32 & index) const;
    const unsigned C_INT32 & getVariableNumberSize() const;
    const C_FLOAT64 & getVolume(const unsigned C_INT32 & index) const;
    const C_FLOAT64 * getVolumeArray() const;
    const unsigned C_INT32 & getVolumeSize() const;
    void setFixedNumber(const unsigned C_INT32 & index, const C_INT32 & value);
    void setFixedNumber(const unsigned C_INT32 & index, const C_FLOAT64 & value);
    void setFixedNumberArray(const C_INT32 * values);
    void setFixedNumberArray(const C_FLOAT64 * values);
    void setVariableNumber(const unsigned C_INT32 & index, const C_INT32 & value);
    void setVariableNumber(const unsigned C_INT32 & index, const C_FLOAT64 & value);
    void setVariableNumberArray(const C_INT32 * values);
    void setVariableNumberArray(const C_FLOAT64 * values);
    void setVolume(const unsigned C_INT32 & index, const C_FLOAT64 & value);
    void setVolumeArray(const C_FLOAT64 * values);

    /**
     * Calculate the jacobian of the state and store it in the provided matrix.
     * @param TNT::Matrix < C_FLOAT64 > & jacobian
     * @param const C_FLOAT64 & factor,
     * @param const C_FLOAT64 & resolution
     */
    virtual void getJacobian(TNT::Matrix < C_FLOAT64 > & jacobian,
                             const C_FLOAT64 & factor,
                             const C_FLOAT64 & resolution) const;

  protected:
    /**
     * Calculate the jacobian of the state and store it in the provided matrix.
     * @param TNT::Matrix < C_FLOAT64 > & jacobian
     * @param const C_FLOAT64 & factor,
     * @param const C_FLOAT64 & resolution
     */
    virtual void getJacobianProtected(TNT::Matrix < C_FLOAT64 > & jacobian,
                                      const C_FLOAT64 & factor,
                                      const C_FLOAT64 & resolution);

    virtual void cleanup();
  };

class CStateX: public CState
  {
  protected:
    // Attributes

    // Associations
    CParticleNumberList mDependentNumbers;

    // Operations
  public:
    CStateX(const CModel * pModel = NULL);
    CStateX(const CState & state);
    CStateX(const CStateX & stateX);
    virtual ~CStateX();
    CStateX & operator =(const CState & state);
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

    virtual void setModel(const CModel * pModel);
    const C_FLOAT64 * getDependentNumberArrayDbl() const;
    const C_INT32 * getDependentNumberArrayInt() const;
    const C_FLOAT64 & getDependentNumberDbl(const unsigned C_INT32 & index) const;
    const C_INT32 & getDependentNumberInt(const unsigned C_INT32 & index) const;
    const unsigned C_INT32 & getDependentNumberSize()const;
    void setDependentNumber(const unsigned C_INT32 & index,
                            const C_INT32 & value);
    void setDependentNumber(const unsigned C_INT32 & index,
                            const C_FLOAT64 & value);
    void setDependentNumberArray(const C_INT32 * values);
    void setDependentNumberArray(const C_FLOAT64 * values);
    void updateDependentNumbers();

    /**
     * Calculate the jacobian of the state and store it in the provided matrix.
     * @param TNT::Matrix < C_FLOAT64 > & jacobian
     * @param const C_FLOAT64 & factor,
     * @param const C_FLOAT64 & resolution
     */
    virtual void getJacobian(TNT::Matrix < C_FLOAT64 > & jacobian,
                             const C_FLOAT64 & factor,
                             const C_FLOAT64 & resolution) const;
  protected:
    virtual void cleanup();
  };
#endif
