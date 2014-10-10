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

#ifndef COPASI_CStochNextReactionMethod
#define COPASI_CStochNextReactionMethod

#include "trajectory/CStochMethod.h"
#include "utilities/CIndexedPriorityQueue.h"

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

public:
  /**
   * Default constructor
   */
  CStochNextReactionMethod();

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
