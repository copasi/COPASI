#ifndef COPASI_CStochDirectMethod
#define COPASI_CStochDirectMethod

#include "CStochMethod.h"

/**
 * CStochDirectMethod implements Gillespie's Direct Method algorithm.
 *
 * This is the simplest and earliest of the stochastic simulation
 * algorithms. A reaction and its time are each determined
 * independently using a Monte-Carlo method. Each propensity function
 * is updated after each reaction.
 */

class CStochDirectMethod : public CStochMethod
  {
  public:
    // Lifecycle methods
    /**
     * Default constructor
     */
    CStochDirectMethod();

    /**
     * Initialization.
     */
    void initMethod(C_FLOAT64 start_time) {};

    /**
     * Do one iteration of the simulation
     * @return Current simulation time or -1 if error.
     */
    C_FLOAT64 doSingleStep(C_FLOAT64 initial_time);
  };

#endif
