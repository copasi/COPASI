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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CLyapMethod class.
 */

#ifndef COPASI_CLyapMethod
#define COPASI_CLyapMethod

#include <string>

#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/core/CVector.h"

class CLyapProblem;
class CState;

class CLyapValidSubTypes : public std::vector< CTaskEnum::Method >
{
public:
  /**
   * Default constructor.
   */
  CLyapValidSubTypes();

  /**
   * Destructor.
   */
  ~CLyapValidSubTypes();
};

class CLyapMethod : public CCopasiMethod
{
public:
  /**
   *  A list of valid trajectory method types;
   */
  static const CLyapValidSubTypes ValidSubTypes;

  /**
   * Checks whether the given sub type is a valid method
   * @param const CTaskEnum::Method & subType
   * @return bool isValidSubType
   */
  static bool isValidSubType(const CTaskEnum::Method & subType);

protected:
  /**
   *  A pointer to the current state. This is set from outside
   *  with the setState() method and never changed anywhere else.
   *  It�s used to report the results
   *  to the calling LyapTask
   */
  //CState * mpCurrentState;

  /**
   *  A pointer to the trajectory problem.
   */
  CLyapProblem * mpProblem;

  // Operations
private:
  /**
   * Default constructor.
   */
  CLyapMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType
   * @param const CTaskEnum::Task & taskType (default: lyap)
   */
  CLyapMethod(const CDataContainer * pParent,
              const CTaskEnum::Method & methodType,
              const CTaskEnum::Task & taskType = CTaskEnum::Task::lyap);

  /**
   * Copy constructor.
   * @param "const CLyapMethod &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CLyapMethod(const CLyapMethod & src,
              const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CLyapMethod();

  /**
   *  Set a pointer to the current state.
   *  This method is used by CLyapTask::process()
   *  The results of the simulation are passed via this CState variable
   *  @param "CState *" currentState
   */
  //void setCurrentState(CState * currentState);

  /**
   *  Set a pointer to the problem.
   *  This method is used by CLyap
   *  @param "CLyapProblem *" problem
   */
  void setProblem(CLyapProblem * problem);

  /**
   *  This instructs the method to calculate a time step of deltaT
   *  starting with the current state, i.e., the result of the previous
   *  step.
   *  The new state (after deltaT) is expected in the current state.
   *  The return value is the actual timestep taken.
   *  @param "const double &" deltaT
   */
  virtual double step(const double & deltaT);

  virtual bool calculate() = 0;

  /**
   *  This instructs the method to prepare for integration
   *  starting with the initialState given.
   *  @param "const CState *" initialState
   */
  virtual void start(CVectorCore< C_FLOAT64 > & initialState);

  /**
   * Check if the method is suitable for this problem
   * @return bool suitability of the method
   */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);
};

#include "CLyapWolfMethod.h"

#endif // COPASI_CLyapMethod
