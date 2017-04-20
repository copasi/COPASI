// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

//
//  CCopasiTaskStatus.h
//  COPASI
//
//  Created by Sven Sahle on 04.11.14.
//
//

#ifndef __COPASI__CCopasiTaskStatus__
#define __COPASI__CCopasiTaskStatus__

//#include <stdio.h>
#include <iostream>

//TODO if we don't mind the overhead this could be converted to a CDataObject

/**
 * This class contains status information of a CCopasiTask.
 * It includes information whether the task is initialized, finished, etc.
 * and also the result status (success or error, also task specific information)
 */
class CCopasiTaskStatus
{
public:

  /**
   * An enum that contains all (exclusive) states a task can be in.
   */
  enum State
  {
    NoState = 0, ///no state assigned
    OutputDataStructuresInitialized, ///the output annotations were initialized (by updateMatrices())
    Initialized, ///initialize() completed successfully
    ProblemCheckfailed, ///the isValidProblem() check failed
    InitializeFailed, ///initialize() failed for other reasons
    Started, ///set at the beginning of process()
    Stopped, ///user has stopped the task (from the GUI)
    FinishedSuccesfully, ///task completed successfully
    Failed, ///task failed
    FailedByParent ///task is completed, but considered failed by parent, e.g. because of constraint violations
  };

  /**
   * String literals for the GUI to display states
   */
  static const std::string StateString[];

  CCopasiTaskStatus();

  /*virtual*/ void print(std::ostream * ostream) const;

  void set(State state);

  /**
   * convenience method: sets status to Initialized or
   * InitializeFailed, according to the
   * success flag.
   */
  void setInitialized(bool success);

  const State & getState() const;

protected:

  State mState;
};

#endif /* defined(__COPASI__CCopasiTaskStatus__) */
