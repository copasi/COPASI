/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CHybridNextReactionRKMethod.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: jpahle $ 
   $Date: 2004/12/17 12:31:54 $
   End CVS Header */

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
