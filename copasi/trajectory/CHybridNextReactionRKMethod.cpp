/**
 *   CHybridNextReactionRKMethod
 *
 *   First approach to an hybrid algorithm. Gibson's Next Reaction method is
 *   combined with a RungeKutta numerical integrator.
 *
 *   File name: CHybridNextReactionRKMethod.h
 *   Author: Juergen Pahle
 *   Email: juergen.pahle@eml.villa-bosch.de
 *
 *   Last change: 24, January 2003
 *
 *   (C) European Media Lab 2003.
 */

/* HEADER FILE ***************************************************************/
#include "copasi.h"
#include "CHybridNextReactionRKMethod.h"

CHybridNextReactionRKMethod::CHybridNextReactionRKMethod() : CHybridMethod()
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
          if (mFirstFlag != NULL) // there is at least one deterministic reaction
            {
              integrateDeterministicPart(ds - currentTime);
              updatePartitionDet(increment, y, ds);
            }
          fireReactionAndUpdatePartition(rIndex, ds);
          updatePriorityQueue(rIndex, ds);
        }
      else
        {
          // if there are deterministic reactions
          if (mFirstFlag != NULL) // there is at least one deterministic reaction
            {
              integrateDeterministicPart(endTime - currentTime);
              updatePartitionDet(increment, y, endTime);
            }
          updatePriorityQueue(-1, endTime);
          ds = endTime;
        }
    }
  else // there is no stochastic reaction
    {
      ds = currentTime + mStepsize;
      if (ds <= endTime)
        {
          // if there are deterministic reactions
          if (mFirstFlag != NULL) // there is at least one deterministic reaction
            {
              integrateDeterministicPart(mStepsize);
              updatePartitionDet(increment, y, ds);
            }
          updatePriorityQueue(-1, ds);
        }
      else
        {
          // if there are deterministic reactions
          if (mFirstFlag != NULL) // there is at least one deterministic reaction
            {
              integrateDeterministicPart(endTime - currentTime);
              updatePartitionDet(increment, y, endTime);
            }
          updatePriorityQueue(-1, endTime);
          ds = endTime;
        }
    }
  //deprecated:  outputDebug(mOutputFile, 1);  // DEBUG
  //deprecated:  outputData(mOutputFile, 1);  // DEBUG
  return ds;
}
