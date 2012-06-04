// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CStochNextReactionMethod.cpp,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/06/04 17:58:01 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"
#include "CStochNextReactionMethod.h"
#include "CTrajectoryMethod.h"
#include "model/CCompartment.h"
#include "model/CModel.h"

CStochNextReactionMethod::CStochNextReactionMethod()
    : CStochMethod()
{}

void CStochNextReactionMethod::initMethod(C_FLOAT64 start_time)
{
  setupPriorityQueue(start_time);
}

C_FLOAT64 CStochNextReactionMethod::doSingleStep(C_FLOAT64 C_UNUSED(time), C_FLOAT64 endTime)
{
  C_FLOAT64 steptime = mPQ.topKey();

  if (steptime >= endTime)
    {
      return endTime;
    }
  else
    {
      size_t reaction_index = mPQ.topIndex();
      updateSystemState(reaction_index, steptime);
      updatePriorityQueue(reaction_index, steptime);
      //printDebugInfo();
      return steptime;
    }
}

//void CStochNextReactionMethod::printDebugInfo()
//{
//  cout << mPQ << endl;
//}

void CStochNextReactionMethod::setupPriorityQueue(C_FLOAT64 start_time)
{
  C_FLOAT64 time;

  mPQ.clear();

  for (size_t i = 0; i < mpModel->getReactions().size(); i++)
    {
      time = start_time + generateReactionTime(i);
      mPQ.pushPair(i, time);
    }

  mPQ.buildHeap();
}

void CStochNextReactionMethod::updatePriorityQueue(size_t reaction_index, C_FLOAT64 time)
{
  //first the new time for the currently fired reaction
  C_FLOAT64 new_time = time + generateReactionTime(reaction_index);
  mPQ.updateNode(reaction_index, new_time);

  //now the updates for the other reactions (whose propensities may have changed)

  //if the model contains assignment we use a less efficient loop over all reactions since
  // we do not know the exact dependencies
  if (mHasAssignments)
    {
      size_t i;

      for (i = 0; i < mNumReactions; ++i)
        {
          if (i != reaction_index)
            {
              if (mAmu[i] == mAmuOld[i])
                continue;

              C_FLOAT64 new_time;

              if (mAmuOld[i] > 0)
                {
                  new_time = time + (mAmuOld[i] / mAmu[i]) * (mPQ.getKey(i) - time);
                }
              else
                {
                  new_time = time + generateReactionTime(i);
                }

              mPQ.updateNode(i, new_time);
            }
        }
    }
  else
    {
      const std::set<size_t> & dep_nodes = mDG.getDependents(reaction_index);
      std::set<size_t>::const_iterator di;

      for (di = dep_nodes.begin(); di != dep_nodes.end(); ++di)
        {
          if (*di != reaction_index)
            {
              size_t index = *di;
              C_FLOAT64 new_time;

              if (mAmuOld[index] > 0)
                {
                  new_time = time + (mAmuOld[index] / mAmu[index]) * (mPQ.getKey(index) - time);
                }
              else
                {
                  new_time = time + generateReactionTime(index);
                }

              mPQ.updateNode(index, new_time);
            }
        }
    }
}
