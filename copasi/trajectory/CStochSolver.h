#ifndef COPASI_CStochSolver
#define COPASI_CStochSolver

#include "utilities/utilities.h"
#include "utilities/CRandom.h"
#include "model/model.h"
#include <queue>
/**
 * CStochSolver
 *
 * This class is used to perform stochastic simulations on the
 * model. The user may specify the algorithm to be used, and a default
 * is assumed if this is not given.
 *
 * The available algorithms at the moment are Gillespie's Direct
 * method, and Gibson and Bruck's Next Reaction method. // TODO: implement the latter
 *
 * These are implemented as classes inheriting their common
 * functionality from the abstract CStochMethod base class, and which
 * provide the rest themselves.  The CStochSolver class is initialized
 * with a pointer to an instance of a particular concrete class, and
 * uses this class to do each iteration of the simulation.  This is
 * essentially an implementation of the Strategy pattern described in
 * the "Design Patterns" book.
 *
 * CStochSolver must also be supplied with a reference to an instance
 * of CModel, which it passes to CStochMethod. This then extracts
 * parameters from the model relevant to the simulation.
 *
 * Prototypical use: This would be done from an instance of CTrajectory, 
 * which would call each step up to the maximum step number of maximum time.
 *
 * C_INT32 step = 0;
 * C_FLOAT32 time = 0;
 * CStochSolver solver(method);
 * solver.initialize(model);
 * while (step < total_steps && time < total_time && time >= 0)
 * {
 *     time = solver->GetMethod()->DoStep(time);
 *     step++;
 * }
 *
 */

class CStochMethod;

class CStochSolver
{
 private:
    // Private attributes
    /**
     * The type of the stochastic solver method
     */
    C_INT32 mMethodType;
  /**
   * A pointer to the method used
   */
  CStochMethod *mMethod; 
 public:
  // Lifecycle methods
  /**
   * The default constructor
   */
  CStochSolver();
  /**
   * The named constructor, giving a method to use
   * @param method An integer specifying the method to use
   */
  CStochSolver(C_INT32 method);
  
  /**
   * The destructor
   */
  ~CStochSolver();

  /**
   * This initializes the solver, creates an instance of the method, 
   * and initializes that with the given model.
   * @param model A pointer to an instance of CModel 
   */
  void initialize(CModel *model);
  /**
   * Clean up 
   */
  void cleanup();
  // Operations methods
  /**
   * Returns a pointer to the instance of the solver method.
   * @return mMethod
   */
  CStochMethod *getStochMethod();
};

/**
 * CStochMethod is a parent to concrete solvers derived from it.
 *
 * These derived solvers do the actual work of the simulation. Each
 * solver maintains a list of propensities, a_mu, one for each
 * reaction. These propensities are dependent on the state of the
 * system. i.e. the numbers of each particle, and some or all must be
 * updated after each reaction. The propensities are then used to
 * determine the next step and the time at which it occurs, after
 * which the particle numbers are updated and the time is
 * incremented. The particulars of how the updating is done, and the
 * determination of the next reaction and its time are left to the
 * derived classes.
 */

class CStochMethod
{
 protected:    
  // Protected attributes
  /**
   * A pointer to the instance of CModel being used.
   */
  CModel *mModel;
  /**
   * The propensities for the reactions
   */
  std::vector<C_FLOAT64> mAmu;
  /**
   * The sum of the propensities
   */
  C_FLOAT64 mA0;
  /**
   * The random number generator
   */
  CRandom *mRandomGenerator;
  /**
   * Failure status.
   * 0 = Success
   * !0 = Failure
   */
  C_INT32 mFail;
 public:
  // Lifecycle methods
  /**
   * Default constructor
   */
  CStochMethod();
  CStochMethod(CModel *model);
  /**
   * Destructor
   */
  virtual ~CStochMethod();
  void cleanup();
  // Operations
  /**
   * Initialize the method
   * @return mFail
   * @see mFail
   */
  virtual C_INT32 initMethod() = 0;
  /**
   * Do one iteration of the simulation
   * @return Current simulation time or -1 if error.
   */
  virtual C_FLOAT64 doStep(C_FLOAT64 time) = 0;
 protected:
  // Protected operations
  /**
   * Calculate the propensities for all reactions
   * @return mFail
   * @see mFail
   */
  C_INT32 updatePropensities();
  /**
   * Calculate one of the propensities
   * @return mFail
   * @see mFail
   */
  C_INT32 calculateAmu(C_INT32 reaction_index);
  /**
   * Generate the index of a putative reaction.
   * @return The reaction index
   */
  C_INT32 generateReactionIndex();
  /**
   * Generate the putative time taken before a reaction
   * @return The time before the reaction
   */
  C_FLOAT64 generateReactionTime();
  /**
   * Update the particle numbers according to which reaction ocurred
   * @return mFail
   * @see mFail
   */
  C_INT32 updateSystemState(C_INT32 reaction_index);
#if 0
  /**
   * Determine the value of one of the cmu's
   * @param index The position in the vector of this value of Cmu
   * @return mFail
   * @see mFail
   */
  C_INT32 CalculateCmu(C_INT32 index);
  /**
   * Determine the value of one of the hmu's 
   * @param index The position in the vector of this value of Cmu
   * @return mFail
   * @see mFail
   */
  C_INT32 CalculateHmu(C_INT32 index);
#endif // 0
};

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
   * Named constructor
   */
  CStochDirectMethod(CModel *model);
  /** 
   * Destructor
   */
  ~CStochDirectMethod();
  // Operations
  /**
   * Initialize the method
   * @return mFail
   * @see mFail
   */
  C_INT32 initMethod();
  /**
   * Do one iteration of the simulation
   * @return Current simulation time or -1 if error.
   */
  C_FLOAT64 doStep(C_FLOAT64 time);
};

/**
 * CStochFirstReactionMethod implements the First Reaction method.
 *
 * In this method, the putative reaction times tmu are calculated and
 * stored in a indexed priority queue. These are absolute times. In
 * the algorithm, the next reaction to occur is defined to be that at
 * the front of the queue. The Amu's affected by this reaction are
 * recalculated, a new putative time tmu is calculated for this
 * reaction, and the priority queue is reordered so that the node
 * associated with this reaction occurs in the proper place.
 */

//--------------NOT COMPLETE YET------------------------------------------------

class CStochNextReactionMethod: public CStochMethod
{
 private:
    // Private attributes
  /**
   * The graph of reactions and their dependent reactions. When a reaction is 
   * executed, the propensities for each of its dependents must be updated.
   */
    CDependencyGraph mDG;

  /**
   * The set of putative reactions and associated times at which each reaction occurs.
   * This is represented as a priority queue, indexed on the reaction time.
   */
    CIndexedPriorityQueue mPQ;
 public:
  // Lifecycle methods
  /**
   * Default constructor
   */
  CStochNextReactionMethod();

  /**
   * Named constructor
   */
  CStochNextReactionMethod(CModel *model);
  /** 
   * Destructor
   */
  ~CStochNextReactionMethod();
  // Operations
  /**
   * Initialize the method
   * @param start_time The time at which the simulation starts
   * @return mFail
   * @see mFail
   */
  C_INT32 initMethod(C_FLOAT64 start_time = 0);
  /**
   * Do one iteration of the simulation
   * @return Current simulation time or -1 if error.
   */
  C_FLOAT64 doStep();
 private:
  // Private operations
  /**
   * Set up the dependency graph
   */
  void setupDependencyGraph();
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

#endif // COPASI_CStochSolver
