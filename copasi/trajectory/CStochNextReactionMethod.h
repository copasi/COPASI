#ifndef COPASI_CStochNextReactionMethod
#define COPASI_CStochNextReactionMethod

#include "CStochMethod.h"
#include "utilities/CIndexedPriorityQueue.h"

class CStochNextReactionMethod: public CStochMethod
  {
    friend CStochMethod *
    CStochMethod::createStochMethod(CTrajectoryProblem * pProblem);

  private:
    // Private attributes

    /**
     * The set of putative reactions and associated times at which each reaction occurs.
     * This is represented as a priority queue, indexed on the reaction time.
     */
    CIndexedPriorityQueue mPQ;

    /**
     * Initialization.
     */
    void initMethod(C_FLOAT64 start_time);

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
    void updatePriorityQueue(C_INT32 reaction_index, C_FLOAT64 time);
  };

#endif
