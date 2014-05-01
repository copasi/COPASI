// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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
#include "copasi/utilities/CVector.h"

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

protected:
  /**
   * Default constructor.
   * @param const CCopasiMethod::SubType & subType
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CTrajectoryMethod(const CCopasiMethod::SubType & subType,
                    const CCopasiContainer * pParent = NULL);

public:
  /**
   * Create a trajectory method for a special problem.
   * Note: the returned object has to be released after use with delete
   * a problem is also passed so that the method has a chance to choose an
   * appropriate simulation method.
   */
  static CTrajectoryMethod *
  createMethod(CCopasiMethod::SubType subType = CCopasiMethod::deterministic);

  /**
   * Copy constructor.
   * @param "const CTrajectoryMethod &" src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CTrajectoryMethod(const CTrajectoryMethod & src,
                    const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor.
   */
  ~CTrajectoryMethod();

  /**
   * Set the math container used for calculations
   * @param CMathContainer * pContainer
   */
  virtual void setContainer(CMathContainer * pContainer);

  /**
   *  Set a pointer to the problem.
   *  This method is used by CTrajectory
   *  @param "CTrajectoryProblem *" problem
   */
  void setProblem(CTrajectoryProblem * problem);

  /**
   * Inform the trajectory method that the state has changed outside
   * its control
   */
  virtual void stateChanged();

  /**
   *  This instructs the method to calculate a time step of deltaT
   *  starting with the current state, i.e., the result of the previous
   *  step.
   *  The new state (after deltaT) is expected in the current state.
   *  The return value is the actual timestep taken.
   *  @param "const double &" deltaT
   *  @return Status status
   */
  virtual Status step(const double & deltaT);

  /**
   *  This instructs the method to prepare for integration
   *  starting with the initialState given.
   *  @param "const CState *" initialState
   */
  virtual void start(CVectorCore< C_FLOAT64 > & initialState);

  /**
   * Retrieve the roots.
   * @return const CVector< C_INT > & roots
   */
  const CVector< C_INT > & getRoots() const;

  /**
   * Check if the method is suitable for this problem
   * @return bool suitability of the method
   */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

  // Attributes
protected:
  /**
   * A pointer to the math container
   */
  CMathContainer * mpContainer;

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
   *  A pointer to the trajectory problem.
   */
  CTrajectoryProblem * mpProblem;

  /**
   * Vector containing information on the current roots
   */
  CVector< C_INT > mRoots;
};

#endif // COPASI_CTrajectoryMethod
