
#ifndef CINTERPOLATION
#define CINTERPOLATION
#include "copasi.h"
#include "copasi/utilities/CVersion.h"
#include "copasi/utilities/CMatrix.h"
#include "copasi/utilities/CCopasiVector.h"

#include <vector>
#include <set>
#include <cstdlib>

/*************************/
/* Class of CStateRecord */
/*************************/
class CStateRecord 
{

//**Member Functions*************************************************
 public:

  /**
   * Friend Function for Debug
   */
  friend void printRecord(const CStateRecord& record);


  /**
   * Constructor
   */
  CStateRecord();

  /**
   * Assignment Constructor
   */
  CStateRecord(size_t reactionNum);


  /**
   * Copy constructor
   * @param const CStateRecord & src
   */
  CStateRecord(const CStateRecord & src);

  /**
   * Destructor
   */
  ~CStateRecord();

  /**
   * Assignment operator
   * @param const CStateRecord & rhs
   * @return CStateRecord & lhs
   */
  CStateRecord & operator=(const CStateRecord & rhs);

  /**
   * Retrieve the pointer of the C_FLOAT64 array recording all 
   * the values, 
   * @return const C_FLOAT64 *mpValue
   */
  C_FLOAT64 * getArray() const;

  /**
   * Retrive the time of the state
   * @return const C_FLOAT64 & mpValue(0)
   */
  const C_FLOAT64 & getTime() const;

  /**
   * Retrieve the Sum of Slow Reaction Propensities
   * @return const C_FLOAT64 & mpValue(mSize-1)
   */
  const C_FLOAT64 & getSlowPropensitySum() const;

  /**
   * Retrieve the attibute mSize, the length of the array
   */
  const size_t & getArrayLen() const;
  
//**Attributes********************************************

 private:
  /**
   * Array of values
   */
  C_FLOAT64 * mpValues;

  /**
   * Size of array
   */
  size_t mSize;
  
};



/***************************/
/* Class of CInterpolation */
/***************************/

class CInterpolation
{

 //********Member Functions********
 public:
  /**
   * Friend Function for Debug
   */
  friend void printInterpolation(const CInterpolation&  interp);

  /**
   * Default Constructor
   */
  CInterpolation();

  /**
   * Assignment Constructor
   */
  CInterpolation(size_t stateNum, size_t reactionNum);

  /**
   * Destructor
   */
  ~CInterpolation();

  /**
   * Retrieve the model State at the 
   * slow reaction firing time by call
   * calculateFiringTime() and
   * calculateState()
   * @return CStateRecord mInterpolationState
   */
  CStateRecord * getInterpolationState();

  /**
   * Reset the record 
   */
  void recordReset();

  /**
   * Load the New State
   * @para const C_FLOAT64 time, const unsigned C_INT32 len
   *       const C_FLOAT54 *y
   */
  void recordState(const C_FLOAT64 time, 
                   const C_FLOAT64 *y);

 private:
  /**
   * Calculate Interpolation Value
   * @param C_FLOAT64 x
   */
  C_FLOAT64 interpolation(C_FLOAT64 x);

  /**
   * Calculate time when slow reaction fires
   */
  void calculateFiringTime();

  /**
   * Calculate Model State at event time
   */
  void calculateState();

  //********Member Attributes********
 private:
  /**
   * Pointer to an array of class CStateRecord
   */
  CStateRecord * mpState;

  /**
   * A pointer of CStateRecord Object recording the state
   * of model at slow reaction firing time calculated
   * by interpolation
   */
  CStateRecord * mpInterpolationState;

  /**
   * A C_FLOAT64 pointer for interpolation array x
   */
  C_FLOAT64 * mpX;

  /**
   * A C_FLOAT64 pointer for interpolation array y
   */
  C_FLOAT64 * mpY;

  /**
   * Length of Vector mState
   */
  size_t mStateNum;

  /**
   * An integer index indicating which state is the
   * first available one for interpolation
   */
  size_t mBeginRecordIndex;

  /**
   * An integer indicating how many state has been recorded
   */
  size_t mHaveRecordNum;

  /**
   * A Bool variable indicating whether the mBeginRecordIndex
   * should be shift
   */
  bool mShiftBeginIndex; 
};

#endif
