#ifndef COPASI_CStochSolver
#define COPASI_CStochSolver

#include "utilities/utilities.h"

class CModel;
class CRandom;

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
#if 0
  /**
   * The maximum time for which the simulation should run.
   */
  C_FLOAT32 mMaxTime;
  /**
   * The maximum number of steps over which to iterate.
   */
  C_INT32 mMaxSteps;
#endif // 0
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
   */
  C_INT32 calculateAmu(C_INT32);
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

class CStochDirectMethod: public CStochMethod
{
 public:
  // Lifecycle methods
  /**
   * Default constructor
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
 private:
  // Private operations
  /**
   * Get the next reaction
   * @return the index of the reaction which occurs.
   */
  C_INT32 getReaction();
  /**
   * Get the time taken by the reaction
   * @return the time taken for this reaction
   */
  C_FLOAT64 getTime();
  /**
   * Update the particle numbers according to which reaction ocurred
   * @return mFail
   * @see mFail
   */
  C_INT32 updateSystemState(C_INT32 reaction_idx);
};

/**
 * CStochNextReactionMethod implements the Next Reaction method.
 *
 * In this method, the putative reaction times tmu are calculated and
 * stored in a indexed priority queue. In the algorithm, the next
 * reaction to occur is defined to be that at the front of the
 * queue. The Amu's affected by this reaction are recalculated, a new
 * putative time tmu is calculated for this reaction, and the priority
 * queue is reordered so that the node associated with this reaction
 * occurs in the proper place.
 */

//--------------NOT COMPLETE YET------------------------------------------------

class CStochNextReactionMethod: public CStochMethod
{
 private:
  // Private attributes
  /**
   * The set of putative times at which each reaction occurs
   */
  //    CCopasiIndPriQueue<C_FLOAT64> tmu; // must still write this class
 public:
  // Lifecycle methods
  /**
   * Default constructor
   */
  CStochNextReactionMethod();
  /** 
   * Destructor
   */
  ~CStochNextReactionMethod();
  // Operations
  /**
   * Do one iteration of the simulation
   * @return Current simulation time or -1 if error.
   */
  C_FLOAT64 Step();
 private:
  // Private operations
};

#endif // COPASI_CStochSolver
