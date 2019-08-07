// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_CStochNextReactionMethod
#define COPASI_CStochNextReactionMethod

#include "copasi/trajectory/CStochMethod.h"
#include "copasi/utilities/CIndexedPriorityQueue.h"

class CStochNextReactionMethod: public CStochMethod
{
private:
  // Private attributes

  /**
   * The set of putative reactions and associated times at which each reaction occurs.
   * This is represented as a priority queue, indexed on the reaction time.
   */
  CIndexedPriorityQueue mPQ;

  /**
   * Vector of the previously calculated propensities
   */
  CVector< C_FLOAT64 > mAmuOld;

  /**
   * Initialization.
   */
  virtual void initMethod();

private:
  /**
   * Default constructor
   */
  CStochNextReactionMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: stochastic)
   * @param const CTaskEnum::Task & taskType (default: timeCourse)
   */
  CStochNextReactionMethod(const CDataContainer * pParent,
                           const CTaskEnum::Method & methodType = CTaskEnum::Method::stochastic,
                           const CTaskEnum::Task & taskType = CTaskEnum::Task::timeCourse);

  /**
   * Copy constructor.
   * @param const CStochMethod & src,
   * @param const CDataContainer * pParent (Default: NULL)
   */
  CStochNextReactionMethod(const CStochMethod & src,
                           const CDataContainer * pParent);

  /**
   * Do one iteration of the simulation
   * @return Current simulation time or -1 if error.
   */
  C_FLOAT64 doSingleStep(C_FLOAT64 time, C_FLOAT64 endTime);

  /**
   * print internal information (for debugging)
   */
  //void printDebugInfo();

private:
  /**
   * Set up the priority queue.
   * @param start_time The time at which the simulation starts.
   */
  void setupPriorityQueue(C_FLOAT64 start_time = 0);
  /**
   * Update the priority queue
   */
  void updatePriorityQueue(size_t reaction_index, C_FLOAT64 time);
};

#endif
