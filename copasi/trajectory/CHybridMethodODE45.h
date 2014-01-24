// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 *   CHybridMethodODE45
 *
 *   This class implements an hybrid algorithm to simulate a biochemical
 *   system over time.
 *
 *   File name: CHybridMethodODE45.h
 *   Author: Shuo Wang
 *   Email: shuowang.learner@gmail.com
 *
 *   Last change: 26, Aug 2013
 *
 */
/**
 *   Partition the system into a deterministic part and a stochastic part.
 *   That is, every reaction is either classified deterministic or
 *   stochastic. Deterministic reactions involve only those metabolites (on
 *   substrate and product side), which have a high particle number.
 *   Therefore it is legal to integrate this part of the system with e.g. a
 *   numerical integrator. The concentration and relative particle number
 *   change should be low enough, so that the probabilities of all the
 *   reactions in the system show only little changes. The stochastic
 *   reactions must be simulated with an exact stochastic method (e.g. next
 *   reaction method (Gibson)), because their firing changes the reaction
 *   probabilities in the system significantly.
 */

#ifndef COPASI_CHybridMethodODE45
#define COPASI_CHybridMethodODE45

/* INCLUDES ******************************************************************/
#include <set>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <new>

#include "copasi/trajectory/CTrajectoryMethod.h"

#include "copasi/utilities/CVersion.h"
#include "copasi/utilities/CMatrix.h"
#include "copasi/utilities/CDependencyGraph.h"
#include "copasi/utilities/CIndexedPriorityQueue.h"
#include "copasi/utilities/CCopasiVector.h"
#include "CExpRKMethod.h"

/* DEFINE ********************************************************************/
#define MAX_STEPS                    1000000
#define INT_EPSILON                  0.1
//#define LOWER_STOCH_LIMIT            800 //800
//#define UPPER_STOCH_LIMIT            1000 //1000
//#define RUNGE_KUTTA_STEPSIZE         0.001

//#define PARTITIONING_STEPSIZE        0.001
//#define PARTITIONING_INTERVAL        1
//#define OUTPUT_COUNTER               100

//#define DEFAULT_OUTPUT_FILE          "hybrid_lsoda.output"
#define SUBTYPE                      1
#define USE_RANDOM_SEED              false
#define RANDOM_SEED                  1

//Simulation Part
#define SLOW                         0
#define FAST                         1

//Method Used
#define STOCHASTIC                   0
#define DETERMINISTIC                1
#define HYBRID                       2


//Interpolation Part
//#define INTERP_RECORD_NUM            6
#define ODE_ERR                     -2
#define ODE_INIT                     0
#define ODE_NEW                      1
#define ODE_CONT                     2
#define ODE_EVENT                    3
#define ODE_FINISH                   4


//mSysStatus Part
#define SYS_ERR                     -2
#define SYS_NEW                      1
#define SYS_CONT                     2
#define SYS_EVENT                    3
#define SYS_CHANGE                   4
#define SYS_END                      5

//Event Flag
#define SLOW_REACT                  -1

/* Function Pointer **********************************************************/
//typedef void (*pEvalF)(const C_INT*, const double*, const double*, double*);

/* CLASSES *******************************************************************/

class CMetab;
class CTrajectoryProblem;
class CState;
class CModel;
class CVersion;
class CReaction;
class CRandom;
class CIndexedPriorityQueue;
class CDependencyGraph;


/**
 * Internal representation of the balances of each reaction.
 * The index of each metabolite in the reaction is provided.
 */
class CHybridODE45Balance
{
public:
  size_t  mIndex;
  C_INT32 mMultiplicity;
  CMetab *mpMetabolite;

  // insert operator
  //friend std::ostream & operator<<(std::ostream & os, const CHybridODE45Balance & d);
};

/**
 * A class to record whether a metab is slow or fast
 * @param fastReactions is applied to store which reactions this
 *        metab participates
 * @param flag, if set is empty -> false, else, -> true
 */
class CHybridODE45MetabFlag
{
public:
  std::set<size_t> mFastReactions;
  size_t mFlag;
};

class CHybridMethodODE45 : public CTrajectoryMethod
{

  friend CTrajectoryMethod *
  CTrajectoryMethod::createMethod(CCopasiMethod::SubType subType);

public:
  struct Data
  {
    size_t dim;
    CHybridMethodODE45 * pMethod;
  };

  //================Function for Class================
protected:
  /**
   * Default Constructor
   */
  CHybridMethodODE45(const CCopasiContainer * pParent = NULL);

public:
  /**
   * Copy constructor
   * @param const CHybridMethodODE45 & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CHybridMethodODE45(const CHybridMethodODE45 & src,
                     const CCopasiContainer * pParent = NULL);
  /**
   *   Destructor.
   */
  ~CHybridMethodODE45();

  //================Function for System================
public:

  /**
  * Check if the method is suitable for this problem
  * @return bool suitability of the method
  */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  /**
   * This instructs the method to prepare for integration
   * starting with the initialState given.
   * @param "const CState *" initialState
   */
  virtual void start(const CState * initialState);

protected:
  /**
   * Initializes the solver.
   * @param time the current time
   */
  void initMethod(C_FLOAT64 time);

  /**
   *   Cleans up memory, etc.
   */
  void cleanup();

private:
  /**
   * Intialize the method parameter
   */
  void initializeParameter();

  //================Function for Model================
public:

protected:
  /**
   * setup mMetabFlags
   */
  void setupMetabFlags();

  /**
   * setup mReactionFlags
   */
  void setupReactionFlags();

  /**
   * setup mMethod
   */
  void setupMethod();

  /**
   *
   */
  void setupCalculateSet();

  /**
   * Sets up an internal representation of the balances for each reaction.
   * This is done in order to be able to deal with fixed metabolites and
   * to avoid a time consuming search for the indices of metabolites in the
   * model.
   */
  void setupBalances();

  /**
   * Sets up an internal representation of the balances for each reaction.
   * This is done in order to be able to deal with fixed metabolites and
   * to avoid a time consuming search for the indices of metabolites in the
   * model.
   */
  void setupMetab2React();

  void setupReactAffect();

  //================Function for ODE45================
public:

protected:
  /**
   *  Calculate the default absolute tolerance
   *  @param const CModel * pModel
   *  @return C_FLOAT64 defaultAtol
   */
  C_FLOAT64 getDefaultAtol(const CModel * pModel) const;

  /**
   * Integrates the deterministic reactions of the system over the
   * specified time interval.
   *
   * @param ds A C_FLOAT64 specifying the stepsize.
   */
  void integrateDeterministicPart(C_FLOAT64 ds);

  /**
   * Dummy Function for calculating derivative of ODE systems
   */
  static void EvalF(const size_t * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

/**
   * Dummy Function for calculating roots value
   */
  static void EvalR(const size_t * n, const C_FLOAT64 * t, const C_FLOAT64 * y, 
		    const size_t * nr, C_FLOAT64 * r);

  /**
   *  This evaluates the derivatives for the complete model
   */
  void evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);


  /**
   * This evaluates the roots value of the system
   */
  void evalR(const C_FLOAT64 * t, const C_FLOAT64 * y, const size_t *nr, C_FLOAT64 *r);

  //================Function for Simulation================
public:
  /**
   *  This instructs the method to calculate a time step of deltaT
   *  starting with the current state, i.e., the result of the previous
   *  step.
   *  The new state (after deltaT) is expected in the current state.
   *  The return value is the actual timestep taken.
   *  @param "const double &" deltaT
   *  @return Status status
   */
  virtual Status step(const double & deltaT);

protected:
  /**
   *  Simulates the system over the next interval of time. The current time
   *  and the end time of the current step() are given as arguments.
   *
   *  @param  currentTime A C_FLOAT64 specifying the current time
   *  @param  endTime A C_FLOAT64 specifying the end time of the step()
   *  @return A C_FLOAT giving the new time
   */
  C_FLOAT64 doSingleStep(C_FLOAT64 currentTime, C_FLOAT64 endTime);

  /**
   * Calculates an amu value for a given reaction.
   *
   * @param rIndex A size_t specifying the reaction to be updated
   */
  void calculateAmu(size_t rIndex);


  /**
   * Do inverse interpolation to find the state when a slow reaction
   * is fired.
   */
  void doInverseInterpolation(const C_FLOAT64 time);

  /**
   * Fire slow reaction and update populations and propensities
   * when Hybrid Method is used
   */
  void fireSlowReaction4Hybrid();

  /**
   * Clear mRoots and set the id-th equal to 1
   */
  void setRoot(const size_t id);

  //================Function for Stoichastic Part================
protected:

  /**
   * Sets up the dependency graph
   */
  void setupDependencyGraph();

  /**
   * Sets up the priority queue.
   *
   * @param startTime The time at which the simulation starts.
   */
  void setupPriorityQueue(C_FLOAT64 startTime = 0.0);

  /**
   * Updates the priority queue.
   *
   * @param rIndex A size_t giving the index of the fired reaction
   * @param time A C_FLOAT64 holding the time taken by this reaction
   */
  void updatePriorityQueue(size_t rIndex, C_FLOAT64 time);

  /**
   * Executes the specified reaction in the system once.
   *
   * @param rIndex A size_t specifying the index of the reaction, which
   *               will be fired.
   */
  void fireReaction(size_t rIndex);

  /**
   * Function return a reaction index which is a slow reaction firing
   * at the event time.
   */
  size_t getReactionIndex4Hybrid();

  /**
   * Find the reaction index and the reaction time of the stochastic (!)
   * reaction with the lowest reaction time.
   *
   * @param ds A reference to a C_FLOAT64. The putative reaction time for
   *           the first stochastic reaction is written into this variable.
   * @param rIndex A reference to a size_t. The index of the first
   *               stochastic reaction is written into this variable.
   */
  void getStochTimeAndIndex(C_FLOAT64 & ds, size_t & rIndex);

  /**
   * Generates a putative reaction time for the given reaction.
   *
   * @param rIndex A size_t specifying the index of the reaction
   * @return A C_FLOAT64 holding the calculated reaction time
   */
  C_FLOAT64 generateReactionTime(size_t rIndex);

  /**
   *   Updates the putative reaction time of a stochastic reaction in the
   *   priority queue. The corresponding amu and amu_old must be set prior to
   *   the call of this method.
   *
   *   @param rIndex A size_t specifying the index of the reaction
   *   @param time A C_FLOAT64 specifying the current time
   */
  void updateTauMu(size_t rIndex, C_FLOAT64 time);

 private:
  /**
   * Gets the set of metabolites on which a given reaction depends.
   *
   * @param rIndex The index of the reaction being executed.
   * @return The set of metabolites depended on.
   */
  std::set <std::string> *getDependsOn(size_t rIndex);

  /**
   * Gets the set of metabolites which change number when a given
   * reaction is executed.
   *
   * @param rIndex The index of the reaction being executed.
   * @return The set of affected metabolites.
   */
  std::set <std::string> *getAffects(size_t rIndex);

  //================Function for Root Interpolation==============
 private:
  /**
   *
   *
   *
   */
  virtual void stateChanged();
  
  //================Help Functions================
protected:
  /**
   * Test the model if it is proper to perform stochastic simulations on.
   * Several properties are tested (e.g. integer stoichometry, all reactions
   * take place in one compartment only, irreversibility...).
   *
   * @return 0, if everything is ok; <0, if an error occured.
   */
  C_INT32 checkModel(CModel * model);

  /**
   * Prints out data on standard output.
   */
  //void outputData(std::ostream & os, C_INT32 mode);
  void outputData();
  void outputState(const CState * pS);

  /**
   * Prints out various data on standard output for debugging purposes.
   */
  void outputDebug(std::ostream & os, size_t level);

  /**
   * tests if the model contains a global value with an assignment rule that is
   * used in calculations
   */
  static bool modelHasAssignments(const CModel* pModel);

//Attributes:
  //================Model Related================

  //~~~~~~~~Model Describtion~~~~~~~~
  /**
   * Pointer to the model
   */
  CModel * mpModel;

  /**
   *   The stoichometry matrix of the model.
   */
  CMatrix <C_FLOAT64> mStoi;

  /**
   * indicates if the correction N^2 -> N*(N-1) should be performed
   */
  bool mDoCorrection;

  /**
   *
   */
  //bool mReducedModel;

  //~~~~~~~~Metabs Related~~~~~~~~
  /**
   * Dimension of the system. Total number of metabolites.
   */
  size_t mNumVariableMetabs;

  /**
   * A pointer to the metabolites of the model.
   */
  CCopasiVector <CMetab> * mpMetabolites;

  /**
   * index of the first metab in CState
   */
  size_t mFirstMetabIndex;

  /**
   * Vector holding information on the status of metabolites. They can
   * be FAST or SLOW.
   */
  std::vector<CHybridODE45MetabFlag> mMetabFlags;

  //~~~~~~~~Reaction Related~~~~~~~~
  /**
   * Number of Reactions
   */
  size_t mNumReactions;

  /**
   * Fast reactions are set FAST and
   * slow ones are SLOW
   */
  CVector <size_t> mReactionFlags;

  /**
   *   A pointer to the reactions of the model.
   */
  const CCopasiVectorNS <CReaction> * mpReactions;

  /**
   * Internal representation of the balances of each reaction. The index of
   * each metabolite in the reaction is provided.
   */
  std::vector <std::vector <CHybridODE45Balance> > mLocalBalances;

  /**
   * Internal representation of the substrates of each reaction. The index
   * of each substrate-metabolite is provided.
   */
  std::vector <std::vector <CHybridODE45Balance> > mLocalSubstrates;

  /**
   *   Vector of relations between metabolites with reactions.
   */
  std::vector <std::set <size_t> > mMetab2React;

  /**
   * Vector of sets that the indeces of propencities which should be
   * updated after one reaction has been fired
   */
  std::vector <std::set<size_t> > mReactAffect;

  /**
   * Bool value
   */
  bool mHasStoiReaction;

  /**
   *
   */
  bool mHasDetermReaction;

  /**
   * An Integer showes the method now CHybridMethod used
   * 0 == Stochastic
   * 1 == Deterministic
   * 2 == Hybrid
   */
  size_t mMethod;

  //================Attributes for State================
  /**
   *  A pointer to the current state in complete model view.
   */
  CState * mpState;

  /**
   * Vectors to hold the system state and intermediate results
   */
  CVector <C_FLOAT64> temp;

  /**
   * Time Record
   */
  C_FLOAT64 mTimeRecord;

  //=================Attributes for ODE45 Solver================
  /**
   * mODE45
   */
  CExpRKMethod mODE45;

  /**
   *   Max number of doSingleStep() per step()
   */
  size_t mMaxSteps;
  bool   mMaxStepsReached;

  /** Is this useful in my method?
   * maximal increase of a particle number in one step.
   */
  size_t mMaxBalance;

  /**
   * mData.dim is the dimension of the ODE system.
   * mData.pMethod contains CLsodaMethod * this to be used
   * in the static method EvalF
   */
  Data mData;

  /**
   *  Pointer to the array with left hand side values.
   */
  C_FLOAT64 * mY;

  /**
   *  Vector containig the derivatives after calling eval
   */
  //CVector< C_FLOAT64 > mYdot;

  //  /**
  //   * ODE45 state, corresponding to iflag in rkf45, an ODE45
  //   * solver argument
  //   */
  C_INT mODEState;

  /**
   * state of ODE45, indicating what to do next in the step part
   * -1, error emerge
   *  0, finish all integration
   *  1, finish one step integration
   *  2, has event
   */
   C_INT mSysStatus;

  /**
   *
   */
  bool mDefaultAtol;

  /**
   * The propensities of the stochastic reactions.
   */
  CVector <C_FLOAT64> mAmu;
  CVector <C_FLOAT64> mAmuOld;

  /**
   * Set of the reactions, which must be updated.
   * Reactions have at lease one fast metab as subtract with
   * non-zero balance
   */
  std::set <size_t> mCalculateSet;

  /**
   * Set of the reactions, which must update after one
   * slow reaction fires
   */
  std::set <size_t> mUpdateSet;

  //================Attributes for Root Interpolation================
  //  /**
  //   * Status of Root and Slow Event
  //   */
  bool mHasRoot;
  bool mHasSlow;

  /**
   * Number of Roots
   */
  size_t mRootNum;

  /**
   * Value of Roots
   */
  CVectorCore< C_FLOAT64 > *mpRootValue;
  
  C_FLOAT64 * mpRT;
  
  //=================Root Dealing Part for Stochastic Part================
  C_FLOAT64 * mOldRoot;

  std::queue<SRoot> mRootQueue;

 
  //================Stochastic Related================
  /**
   * The random number generator.
   */
  CRandom * mpRandomGenerator;

  /**
   * Specifies if the mRandomSeed should be used.
   * otherwise a randomly chosen seed is used.
   */
  bool mUseRandomSeed;

  /**
   *  The random seed to use.
   */
  unsigned C_INT32 mRandomSeed;

  /**
   * The graph of reactions and their dependent reactions.
   * When a reaction is executed, the propensities for each of
   * its dependents must be updated.
   */
  CDependencyGraph mDG;

  /**
   * The set of putative stochastic (!) reactions and associated times at
   * which each reaction occurs. This is represented as a priority queue,
   * sorted by the reaction time. This heap changes dynamically as
   * stochastic reactions become deterministic (delete this reaction from
   * the queue) or vice versa (insert a new reaction into the queue).
   */
  CIndexedPriorityQueue mPQ;

  //========System Related========
  /**
   * File output stream to write data.
   */
  std::ofstream mOutputFile;

  /**
   * Output filename.
   */
  std::string mOutputFileName;

  /**
   * Output counter.
   */
  size_t mOutputCounter;

  /**
   * Indicates whether the model has global quantities
   * with assignment rules.
   * If it has, we will use a less efficient way to update the model
   * state to handle this.
   */
  bool mHasAssignments;

  /**
   *
   */
  std::ostringstream mErrorMsg;
};

#endif // COPASI_CHybridMethodODE45
