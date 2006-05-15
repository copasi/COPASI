/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CHybridNextReactionLSODAMethod.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: nsimus $
   $Date: 2006/05/15 12:38:24 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *   CHybridNextReactionLSODAMethod
 *
 *   First approach to an hybrid algorithm. Gibson's Next Reaction method is
 *   combined with the LSODA numerical integrator.
 *
 *   File name: CHybridNextReactionLSODAMethod.h
 *   Author:
 *   Email:
 *
 *   Last change: 08, May 2006
 *
 *   (C) European Media Lab 2003.
 */

/* HEADER FILE ***************************************************************/
#include "copasi.h"
#include "CHybridNextReactionLSODAMethod.h"
#include "model/CState.h"

CHybridNextReactionLSODAMethod::CHybridNextReactionLSODAMethod(const CCopasiContainer * pParent) : CHybridMethodLSODA(pParent)
{}

/**
 *  Simulates the system over the next interval of time. The new time after
 *  this step is returned.
 *
 *  @param  currentTime A C_FLOAT64 specifying the current time
 *  @param  endTime A C_FLOAT64 specifying the endTime of the current step()
 *  @return A C_FLOAT giving the new time
 */
C_FLOAT64 CHybridNextReactionLSODAMethod::doSingleStep(C_FLOAT64 currentTime, C_FLOAT64 endTime)
{
  C_INT32 rIndex = 0;
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
          mpCurrentState->setTime(ds);
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
          mpCurrentState->setTime(ds);
          if (++mStepsAfterPartitionSystem >= mPartitioningInterval)
            {
              partitionSystem();
              mStepsAfterPartitionSystem = 0;
            }
          updatePriorityQueue(-1, endTime);
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
          mpCurrentState->setTime(ds);
          if (++mStepsAfterPartitionSystem >= mPartitioningInterval)
            {
              partitionSystem();
              mStepsAfterPartitionSystem = 0;
            }
          updatePriorityQueue(-1, ds);
        }
      else
        {
          ds = endTime;
          // if there are deterministic reactions
          if (mFirstReactionFlag != NULL) // there is at least one deterministic reaction
            {
              integrateDeterministicPart(endTime - currentTime);
            }
          mpCurrentState->setTime(ds);
          if (++mStepsAfterPartitionSystem >= mPartitioningInterval)
            {
              partitionSystem();
              mStepsAfterPartitionSystem = 0;
            }
          updatePriorityQueue(-1, endTime);
        }
    }
  //deprecated:  outputDebug(mOutputFile, 1);  // DEBUG
  //deprecated:  outputData(mOutputFile, 1);  // DEBUG
  return ds;
}
