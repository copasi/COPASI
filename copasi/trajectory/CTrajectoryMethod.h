// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CTrajectoryMethod class.
 *  This class describes the interface to all integration methods.
 *  The various method like LSODA or Gillespie have to be derived from
 *  this class.
 *
 *  Created for COPASI by Stefan Hoops 2002
 */

#ifndef COPASI_CTrajectoryMethod
#define COPASI_CTrajectoryMethod

#include <string>

#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/core/CVector.h"
#include "copasi/math/CMathEnum.h"

class CTrajectoryTask;
class CTrajectoryProblem;
class CMathContainer;

class CTrajectoryMethod : public CCopasiMethod
{
public:
  /**
   * Enumeration value for the return value
   */
  enum Status
  {
    FAILURE = -1,
    NORMAL = 0,
    ROOT = 1
  };

  // Operations
private:
  /**
   * Default constructor.
   */
  CTrajectoryMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType
   * @param const CTaskEnum::Task & taskType (default: timeCourse)
   */
  CTrajectoryMethod(const CDataContainer * pParent,
                    const CTaskEnum::Method & methodType,
                    const CTaskEnum::Task & taskType = CTaskEnum::Task::timeCourse);

  /**
   * Copy constructor.
   * @param const CTrajectoryMethod & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CTrajectoryMethod(const CTrajectoryMethod & src,
                    const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CTrajectoryMethod();

  /**
   *  Set a pointer to the problem.
   *  This method is used by CTrajectory
   *  @param "CTrajectoryProblem *" problem
   */
  void setProblem(CTrajectoryProblem * problem);

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
   * Retrieve the roots.
   * @return const CVectorCore< C_INT > & roots
   */
  const CVectorCore< C_INT > & getRoots() const;

  /**
   * Check if the method is suitable for this problem
   * @return bool suitability of the method
   */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

  /**
   * Check whether to integrate the reduced model
   * @return const bool & integrateReducedModel
   */
  const bool & integrateReducedModel() const;

protected:
  /**
   * Signal that the math container has changed
   */
  virtual void signalMathContainerChanged();

  void output(const bool & useMoieties);

  // Attributes
protected:
  /**
   *  A reference to the current state. This is set from outside
   *  with the setState() method and never changed anywhere else.
   *  It's used to report the results to the calling TrajectoryTask
   */
  CVectorCore< C_FLOAT64 > mContainerState;

  /**
   * A pointer to the time value of the current state.
   */
  C_FLOAT64 * mpContainerStateTime;

  /**
   * The task calling the method
   */
  CTrajectoryTask * mpTask;

  /**
   *  A pointer to the trajectory problem.
   */
  CTrajectoryProblem * mpProblem;

  /**
   * Vector containing information on the current roots
   */
  CVectorCore< C_INT > mRootsFound;

  /**
   * Pointer to the value indicating whether to integrate the reduced model.
   */
  const bool * mpReducedModel;

  /**
   * Default value whether indicating whether to integrate the reduced model
   * initialized to false.
   */
  static const bool ReducedModel;
};

#endif // COPASI_CTrajectoryMethod
