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

class CModel;

class CStateX;

class CState
  {
    // Friends

    friend class CStateX;

    // Attributes

  private:
    /**
     *  The model this state state aplies to.
     */
    const CModel * mModel;

    /**
     *  The time of this state
     */
    C_FLOAT64 mTime;

    /**
     *  The number of volumes stored in the state, i.e.,
     *  the number of compartments of the model.
     */
    unsigned C_INT32 mVolumesSize;

    /**
     *  The volumes
     */
    C_FLOAT64 * mVolumes;

    /**
     *  The number of particle numbers stored in the state
     *  , i.e., the number of metabolites of the model.
     */
    unsigned C_INT32 mNumbersSize;

    /**
     *  The number of particles expected to be updated by the
     *  setNumbers methods.
     *  , i.e., the number of metabolites of the model.
     */
    unsigned C_INT32 mNumbersUpdated;

    /**
     *  The particle numbers as long integers
     */
    C_INT32 * mNumbersInt;

    /**
     *  The particle numbers as doubles
     */
    C_FLOAT64 * mNumbersDbl;

    // Operations

  public:
    /**
     *  Default constructor
     */
    CState(const CModel * model = NULL);

    /**
     *  Copy constructor
     *  @param "const CState &" src
     */
    CState(const CState & src);

    /**
     *  Destructor
     */
    ~CState();

    /**
     *  Set the indexed number as a long integer.
     *  @param "const unsigned C_INT32 &" index
     *  @param "const C_INT32 &" number
     */
    void setNumber(const unsigned C_INT32 & index ,
                   const C_INT32 & number)
    {
      *(mNumbersInt + index) = number;
      *(mNumbersDbl + index) = (C_FLOAT64) number;
    }

    /**
     *  Set the indexed number as a double.
     *  @param "const unsigned C_INT32 &" index
     *  @param "const C_FLOAT64 &" number
     */
    void setNumber(const unsigned C_INT32 & index ,
                   const C_FLOAT64 & number)
    {
      *(mNumbersInt + index) = (C_INT32) number;
      *(mNumbersDbl + index) = number;
    }

    /**
     *  Set all numbers as long integers at once.
     *  The methods expect a vector of length mNumbersUpdated.
     *  @param "const C_INT32 * numbers"
     */
    void setNumbers(const C_INT32 * numbers)
    {
      C_INT32 * TmpInt = mNumbersInt;
      const C_INT32 * TmpIn = numbers;
      const C_INT32 * End = TmpIn + mNumbersUpdated;
      C_FLOAT64 * TmpDbl = mNumbersDbl;

      while (TmpIn < End)
        {
          *(TmpInt++) = *TmpIn;
          *(TmpDbl++) = (C_FLOAT64) * (TmpIn++);
        }
    }

    /**
     *  Retrieves the numers of the state as long integers.
     *  The method return a vector of length mNumbersSize.
     *  @return "const C_INT32 *" volumes
     */
    const C_INT32 * getNumbersInt() const { return mNumbersInt; }

    /**
     *  Set all numbers as double at once.
     *  The methods expect a vector of length mNumbersUpdated.
     *  @param "const C_FLAOT64 * numbers"
     */
    void setNumbers(const C_FLOAT64 * numbers)
    {
      C_INT32 * TmpInt = mNumbersInt;
      C_FLOAT64 * TmpDbl = mNumbersDbl;
      const C_FLOAT64 * TmpIn = numbers;
      const C_FLOAT64 * End = TmpIn + mNumbersUpdated;

      while (TmpIn < End)
        {
          *(TmpInt++) = (C_INT32) * TmpIn;
          *(TmpDbl++) = *(TmpIn++);
        }
    }

    /**
     *  Retrieves the numbers of the state as double.
     *  The method return a vector of length mVolumeSize.
     *  @return "const C_FLOAT64 *" volumes
     */
    const C_FLOAT64 * getNumbersDbl() const { return mNumbersDbl; }

    /**
     *  Set the indexed volume.
     *  @param "const unsigned C_INT32 &" index
     *  @param "const C_FLOAT64 &" volume
     */
    void setVolume(const unsigned C_INT32 & index ,
                   const C_FLOAT64 & volume)
    {*(mVolumes + index) = volume; }

    /**
     *  Set all volumes at once.
     *  The methods expect a vector of length mVolumesSize.
     *  @param "const C_FLOAT64 *" volumes
     */
    void setVolumes(const C_FLOAT64 * volumes)
    {
      C_FLOAT64 * Tmp = mVolumes;
      const C_FLOAT64 * TmpIn = volumes;
      const C_FLOAT64 * End = TmpIn + mVolumesSize;

      while (TmpIn < End)
        *(Tmp++) = *(TmpIn++);
    }

    /**
     *  Retrieves the volumes of the state.
     *  The method return a vector of length mVolumeSize.
     *  @return "const C_FLOAT64 *" volumes
     */
  const C_FLOAT64 * getVolumes() const { return mVolumes; }

    /**
     *  Retrieves the size of the numbers vector;
     *  @param "const unsigned C_INT32 &" numbersSize
     */
    const unsigned C_INT32 & getNumbersSize() const;

    /**
     *  Retrieves the size of the updated numbers vector;
     *  @param "const unsigned C_INT32 &" numbersUpdated
     *
     */
    const unsigned C_INT32 & getNumbersUpdated() const;

    /**
     *  Retrieves the size of the volumes vector;
     *  @param "const unsigned C_INT32 &" volumesSize
     */
    const unsigned C_INT32 & getVolumesSize() const;
  };

/**
 *  CState class.
 *  The class CState stores the state in time of a model. The state 
 *  is described for the full model, i.e., updates of all internal
 *  metabolites is expected. The order of metabolites is as in the vector
 *  retrieved by CModel::getMetabolitesX. 
 *  The information is intended to be used with integration routines,
 *  but is not restricted to those.
 *
 *  Created for Copasi by Stefan Hoops 2002
 */

class CStateX : public CState
  {
    // Operations;

  public:
    /**
     *  Default constructor
     */
    CStateX(const CModel * model = NULL);

    /**
     *  Copy constructor
     *  @param "const CState &" src
     */
    CStateX(const CStateX & src);

    /**
     *  Destructor
     */
    ~CStateX();
  }

;

#endif //COPASI_CState
