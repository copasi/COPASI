#include "CStochNextReactionMethod.h"

CStochNextReactionMethod::CStochNextReactionMethod()
    : CStochMethod()
{}

void CStochNextReactionMethod::initMethod(C_FLOAT64 start_time)
{
  setupPriorityQueue(start_time);
}

C_FLOAT64 CStochNextReactionMethod::doSingleStep(C_FLOAT64 C_UNUSED(time))
{
  C_FLOAT64 steptime = mPQ.topKey();
  C_INT32 reaction_index = mPQ.topIndex();
  updateSystemState(reaction_index);
  updatePriorityQueue(reaction_index, steptime);

  //printDebugInfo();
  return steptime;
}

//void CStochNextReactionMethod::printDebugInfo()
//{
//  cout << mPQ << endl;
//}

void CStochNextReactionMethod::setupPriorityQueue(C_FLOAT64 start_time)
{
  C_FLOAT64 time;

  for (unsigned C_INT32 i = 0; i < mpModel->getReactions().size(); i++)
    {
      time = start_time + generateReactionTime(i);
      mPQ.pushPair(i, time);
    }

  mPQ.buildHeap();
}

void CStochNextReactionMethod::updatePriorityQueue(C_INT32 reaction_index, C_FLOAT64 time)
{
  const std::set<C_INT32> & dep_nodes = mDG.getDependents(reaction_index);

  C_FLOAT64 new_time = time + generateReactionTime(reaction_index);

  mPQ.updateNode(reaction_index, new_time);

  std::set<C_INT32>::const_iterator di;

  for (di = dep_nodes.begin(); di != dep_nodes.end(); di++)
    {
      if (*di != reaction_index)
        {
          C_INT32 index = *di;
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
