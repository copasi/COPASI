// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#include <cmath>

#include "copasi/copasi.h"
#include "CStochNextReactionMethod.h"
#include "CTrajectoryMethod.h"

#include "copasi/math/CMathContainer.h"

CStochNextReactionMethod::CStochNextReactionMethod(const CDataContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType):
  CStochMethod(pParent, methodType, taskType)
{}

CStochNextReactionMethod::CStochNextReactionMethod(const CStochMethod & src,
    const CDataContainer * pParent):
  CStochMethod(src, pParent)
{}

void CStochNextReactionMethod::initMethod()
{
  setupPriorityQueue(*mpContainerStateTime);

  mAmuOld = mAmu;
}

C_FLOAT64 CStochNextReactionMethod::doSingleStep(C_FLOAT64 /* time */, C_FLOAT64 endTime)
{
  C_FLOAT64 steptime = mPQ.topKey();

  // We need to throw an exception if mA0 is NaN
  if (std::isnan(steptime))
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 27);
    }

  if (steptime >= endTime)
    {
      return endTime;
    }
  else
    {
      size_t reaction_index = mPQ.topIndex();

      *mpContainerStateTime = steptime;
      mReactions[reaction_index].fire();
      mpContainer->applyUpdateSequence(mUpdateSequences[reaction_index]);

      updatePriorityQueue(reaction_index, steptime);

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

  for (size_t i = 0; i < mNumReactions; i++)
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
  mAmuOld[reaction_index] = mAmu[reaction_index];
  mPQ.updateNode(reaction_index, new_time);

  //now the updates for the other reactions (whose propensities may have changed)

  // if the model contains assignment we use a less efficient loop over all reactions since
  // we do not know the exact dependencies
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

          mAmuOld[index] = mAmu[index];
          mPQ.updateNode(index, new_time);
        }
    }
}
