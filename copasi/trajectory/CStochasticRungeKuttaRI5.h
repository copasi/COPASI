// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CStochasticRungeKuttaRI5
#define COPASI_CStochasticRungeKuttaRI5

#include <sstream>

#include "copasi/core/CMatrix.h"
#include "copasi/core/CVector.h"
#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/trajectory/CRootFinder.h"
#include "copasi/model/CState.h"

class CModel;
class CRandom;

class CStochasticRungeKuttaRI5 : public CTrajectoryMethod
{
public:

  // Operations
private:
  /**
   * Constructor.
   */
  CStochasticRungeKuttaRI5();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: deterministic)
   * @param const CTaskEnum::Task & taskType (default: timeCourse)
   */
  CStochasticRungeKuttaRI5(const CDataContainer * pParent,
                           const CTaskEnum::Method & methodType = CTaskEnum::Method::stochasticRunkeKuttaRI5,
                           const CTaskEnum::Task & taskType = CTaskEnum::Task::timeCourse);

  /**
   * Copy constructor.
   * @param "const CStochasticRungeKuttaRI5 &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CStochasticRungeKuttaRI5(const CStochasticRungeKuttaRI5 & src,
                           const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CStochasticRungeKuttaRI5();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  /**
   * Inform the trajectory method that the state has changed outside
   * its control
   * @param const CMath::StateChange & change
   */
  virtual void stateChange(const CMath::StateChange & change);

  /**
   *  This instructs the method to calculate a time step of deltaT
   *  starting with the current state, i.e., the result of the previous
   *  step.
   *  The new state (after deltaT) is expected in the current state.
   *  The return value is the actual timestep taken.
   *  @param const double & deltaT
   *  @param const bool & final (default: false)
   *  @return Status status
   */
  virtual Status step(const double & deltaT, const bool & final = false);

  /**
   *  This instructs the method to prepare for integration
   */
  virtual void start();

  /**
   *  This evaluates the roots
   */
  void evalRoot(const double & time, CVectorCore< C_FLOAT64 > & rootValues);

private:
  /**
   *  This evaluates the derivatives
   */
  void evalRate(C_FLOAT64 * rates);

  /**
   *  This evaluates the noise
   */
  void evalNoise(C_FLOAT64 * pNoise, const size_t & noiseDimension);

  /**
   * Initialize the method parameter
   */
  void initializeParameter();

  void generateRandomNumbers();
  C_FLOAT64 randomIHat();
  C_FLOAT64 randomITilde();

  void buildStage1();
  void buildStage2();
  void buildStage3();
  void calculateStateVariables(const double & time);
  CTrajectoryMethod::Status internalStep();

  C_FLOAT64 calculateSmallestPhysicalValue() const;
  void createRootMask();
  void destroyRootMask();

  CVectorCore< C_FLOAT64 > mContainerVariables;
  CVectorCore< C_FLOAT64 > mContainerRates;
  CVectorCore< C_FLOAT64 > mContainerNoise;
  CVectorCore< C_FLOAT64 > mContainerRoots;

  size_t mNumVariables;
  size_t mNumNoise;
  size_t mNumRoots;

  /**
   * A pointer to the value of "Internal Steps Size"
   */
  C_FLOAT64 * mpInternalStepSize;

  /**
   * A pointer to the value of "Max Internal Steps"
   */
  unsigned C_INT32 * mpMaxInternalSteps;

  /**
   * A pointer to the value "Force Physical Correctness"
   */
  bool * mpForcePhysicalCorrectness;

  /**
   * A pointer to the value of "Tolerance for Root Finder"
   */
  C_FLOAT64 * mpRootRelativeTolerance;

  /**
   * A pointer to to the value "Absolute Tolerance"
   */
  C_FLOAT64 * mpAbsoluteTolerance;

  CVector< C_FLOAT64 > mAtol;

  /**
   * A pointer to the random number generator
   */
  CRandom * mpRandom;

  C_FLOAT64 mStepSize;
  C_FLOAT64 mSqrtStepSize;

  CVector< C_FLOAT64 > mRandomIHat;
  CVector< C_FLOAT64 > mRandomITilde;
  CMatrix< C_FLOAT64 > mRandomIMatrix;

  C_FLOAT64 mTime;
  C_FLOAT64 mTargetTime;
  C_FLOAT64 mTargetDelta;

  C_FLOAT64 mLastCalculatedTime;
  CVector< C_FLOAT64 > mLastCalculatedVariables;

  size_t mInternalSteps;

  CVector< C_FLOAT64 > mH10;
  CVector< C_FLOAT64 > mSumAll1;
  CMatrix< C_FLOAT64 > mSumPartial1;

  CVector< C_FLOAT64 > mH20;
  CMatrix< C_FLOAT64 > mH2k;
  CMatrix< C_FLOAT64 > mHH2k;
  CVector< C_FLOAT64 > mSumAll2;
  CMatrix< C_FLOAT64 > mSumPartial2;

  CVector< C_FLOAT64 > mH30;
  CMatrix< C_FLOAT64 > mH3k;
  CMatrix< C_FLOAT64 > mHH3k;

  CMatrix< C_FLOAT64 > mA;
  CVector< CMatrix< C_FLOAT64 > > mB;
  CVector< CMatrix< C_FLOAT64 > > mBB;

  CVector< C_FLOAT64 * > mNoiseInputValues;
  CVector< CCore::CUpdateSequence > mNoiseUpdateSequences;
  CVector< bool > mPhysicalValues;

  CRootFinder mRootFinder;
  CRootFinder::Eval * mpRootValueCalculator;
  CVectorCore< C_FLOAT64 > mRoots;
  size_t mRootCounter;

  CVector< C_INT > mRootMask;
  CRootFinder::RootMasking mRootMasking;

  /**
   * A pointer to the value which indicate the physical correctness root was found.
   */
  C_INT * mpPhysicalCorrectnessRootFound;
};

#endif // COPASI_CStochasticRungeKuttaRI5
