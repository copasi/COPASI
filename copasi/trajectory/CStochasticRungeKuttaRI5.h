// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CStochasticRungeKuttaRI5
#define COPASI_CStochasticRungeKuttaRI5

#include <sstream>

#include "copasi/utilities/CVector.h"
#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/odepack++/CLSODA.h"
#include "copasi/odepack++/CLSODAR.h"
#include "copasi/model/CState.h"

class CModel;

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
   * @param const CCopasiContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: deterministic)
   * @param const CTaskEnum::Task & taskType (default: timeCourse)
   */
  CStochasticRungeKuttaRI5(const CCopasiContainer * pParent,
                           const CTaskEnum::Method & methodType = CTaskEnum::stochasticRunkeKuttaRI5,
                           const CTaskEnum::Task & taskType = CTaskEnum::timeCourse);

  /**
   * Copy constructor.
   * @param "const CStochasticRungeKuttaRI5 &" src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CStochasticRungeKuttaRI5(const CStochasticRungeKuttaRI5 & src,
                           const CCopasiContainer * pParent);

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
   *  The return value is the actual time step taken.
   *  @param "const double &" deltaT
   *  @return Status status
   */
  virtual CTrajectoryMethod::Status step(const double & deltaT);

  /**
   *  This instructs the method to prepare for integration
   */
  virtual void start();

private:
  /**
   *  This evaluates the derivatives
   */
  void evalRate(CVectorCore< C_FLOAT64 > & rates);

  /**
   *  This evaluates the roots
   */
  void evalNoise(CVectorCore< C_FLOAT64 > & noise);

  /**
   *  This evaluates the roots
   */
  void evalRoot(CVectorCore< C_FLOAT64 > & roots);

  /**
   * Initialize the method parameter
   */
  void initializeParameter();

  CVectorCore< C_FLOAT64 > mContainerRates;
  CVectorCore< C_FLOAT64 > mContainerNoise;
  CVectorCore< C_FLOAT64 > mContainerRoots;

  /**
   * A pointer to the value of "Internal Steps Size"
   */
  C_FLOAT64 * mpInternalStepSize;

  /**
   * A pointer to the value of "Max Internal Steps"
   */
  unsigned C_INT32 * mpMaxInternalSteps;
};

#endif // COPASI_CStochasticRungeKuttaRI5
