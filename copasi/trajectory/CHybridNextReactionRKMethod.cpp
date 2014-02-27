// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *   CHybridNextReactionRKMethod
 *
 *   First approach to an hybrid algorithm. Gibson's Next Reaction method is
 *   combined with a RungeKutta numerical integrator.
 *
 *   File name: CHybridNextReactionRKMethod.h
 *   Author: Juergen Pahle
 *   Email: juergen.pahle@eml-r.villa-bosch.de
 *
 *   Last change: 15, December 2004
 *
 *   (C) European Media Lab 2003.
 */

/* HEADER FILE ***************************************************************/
#include "copasi.h"
#include "CHybridNextReactionRKMethod.h"
#include "model/CState.h"

CHybridNextReactionRKMethod::CHybridNextReactionRKMethod(const CCopasiContainer * pParent) : CHybridMethod(pParent)
{}

/**
 *  Simulates the system over the next interval of time. The new time after
 *  this step is returned.
 *
 *  @param  currentTime A C_FLOAT64 specifying the current time
 *  @param  endTime A C_FLOAT64 specifying the endTime of the current step()
 *  @return A C_FLOAT giving the new time
 */
C_FLOAT64 CHybridNextReactionRKMethod::doSingleStep(C_FLOAT64 currentTime, C_FLOAT64 endTime)
{
  size_t rIndex = 0;
  C_FLOAT64 ds = 0.0;

  // if there are stochastic reactions
  if (mPQ.size() != 0) // there is at least one stochastic reaction
    {
      getStochTimeAndIndex(ds, rIndex);

      if (ds <= endTime) // ds is an absolute time value!
        {
          // if there are deterministic reactions
          if (mFirstReactionFlag != NULL) // there is at least one deterministic reaction
            {
              integrateDeterministicPart(ds - currentTime);
            }

          fireReaction(rIndex);
          *mpContainerStateTime = ds;

          if (++mStepsAfterPartitionSystem >= mPartitioningInterval)
            {
              partitionSystem();
              mStepsAfterPartitionSystem = 0;
            }

          updatePriorityQueue(rIndex, ds);
        }
      else
        {
          ds = endTime;

          // if there are deterministic reactions
          if (mFirstReactionFlag != NULL) // there is at least one deterministic reaction
            {
              integrateDeterministicPart(endTime - currentTime);
            }

          *mpContainerStateTime = ds;

          if (++mStepsAfterPartitionSystem >= mPartitioningInterval)
            {
              partitionSystem();
              mStepsAfterPartitionSystem = 0;
            }

          updatePriorityQueue(C_INVALID_INDEX, endTime);
        }
    }
  else // there is no stochastic reaction
    {
      ds = currentTime + mStepsize;

      if (ds <= endTime)
        {
          // if there are deterministic reactions
          if (mFirstReactionFlag != NULL) // there is at least one deterministic reaction
            {
              integrateDeterministicPart(mStepsize);
            }

          *mpContainerStateTime = ds;

          if (++mStepsAfterPartitionSystem >= mPartitioningInterval)
            {
              partitionSystem();
              mStepsAfterPartitionSystem = 0;
            }

          updatePriorityQueue(C_INVALID_INDEX, ds);
        }
      else
        {
          ds = endTime;

          // if there are deterministic reactions
          if (mFirstReactionFlag != NULL) // there is at least one deterministic reaction
            {
              integrateDeterministicPart(endTime - currentTime);
            }

          *mpContainerStateTime = ds;

          if (++mStepsAfterPartitionSystem >= mPartitioningInterval)
            {
              partitionSystem();
              mStepsAfterPartitionSystem = 0;
            }

          updatePriorityQueue(C_INVALID_INDEX, endTime);
        }
    }

  //deprecated:  outputDebug(mOutputFile, 1);  // DEBUG
  //deprecated:  outputData(mOutputFile, 1);  // DEBUG
  return ds;
}
