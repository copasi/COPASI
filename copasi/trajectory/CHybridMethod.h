/**
 *   CHybridMethod
 *
 *   This class implements an hybrid algorithm to simulate a biochemical 
 *   system over time.
 *
 *   File name: CHybridMethod.h
 *   Author: Juergen Pahle
 *   Email: juergen.pahle@eml.villa-bosch.de
 *
 *   Last change: 24, Februar 2003
 *
 *   (C) European Media Lab 2003.
 */
#ifndef COPASI_CHybridMethod
#define COPASI_CHybridMethod

/* INCLUDES ******************************************************************/
#include "copasi.h"
#include "CTrajectoryMethod.h"
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "utilities/CVersion.h"
#include "utilities/CMatrix.h"
#include "utilities/CDependencyGraph.h"
#include "utilities/CIndexedPriorityQueue.h"

/* DEFINE ********************************************************************/
#define MAX_STEPS              1000
#define INT_EPSILON            0.1
#define LOWER_STOCH_LIMIT      800 //800
#define UPPER_STOCH_LIMIT      1000 //1000
#define RUNGE_KUTTA_STEPSIZE   0.001
#define OUTPUT_COUNTER         100
#define DEFAULT_OUTPUT_FILE    "hybrid.output"

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
 *   Element of the array mStochReactionFlags. The deterministic reactions are
 *   organized in a linked list to be able to iterate over them quickly.
 */
class StochFlag
  {
  public:
    C_INT32 index;
    C_INT32 value;
    StochFlag * prev;
    StochFlag * next;

    // insert operator
    friend std::ostream & operator<<(std::ostream & os, const StochFlag & d)
    {
      os << "StochFlag " << std::endl;
      os << "  index: " << d.index << " value: " << d.value << std::endl;
      if (d.prev != NULL)
        os << "  prevIndex: " << d.prev->index << " prevPointer: " << d.prev << std::endl;
      else
        os << "  prevPointer: NULL" << std::endl;
      if (d.next != NULL)
        os << "  nextIndex: " << d.next->index << " nextPointer: " << d.next << std::endl;
      else
        os << "  nextPointer: NULL" << std::endl;
      return os;
    }
  };

/**
 *   Internal representation of the balances of each reaction. The index of
 *   each metabolite in the reaction is provided.
 */
class Balance
  {
  public:
    C_INT32 index;
    C_INT32 balance;
    CMetab * metabolitePointer;

    // insert operator
    friend std::ostream & operator<<(std::ostream & os, const Balance & d)
    {
      os << "Balance" << std::endl;
      os << "  index: " << d.index << " balance: " << d.balance
      << " metabPointer: " << d.metabolitePointer << std::endl;
      return os;
    }
  };

class CHybridMethod : private CTrajectoryMethod
  {
    friend CTrajectoryMethod *
    CTrajectoryMethod::createTrajectoryMethod(CTrajectoryMethod::Type type, CTrajectoryProblem * pProblem);

    /* PUBLIC METHODS **********************************************************/

  public:
    /**
     *   Copy constructor
     *   @param "const CHybridMethod &" src
     */
    CHybridMethod(const CHybridMethod & src);

    /**
     *   Destructor.
     */
    ~CHybridMethod();

    /**
     *  Chooses a hybrid method adequate for the problem
     */
    static CHybridMethod *
    createHybridMethod(CTrajectoryProblem * pProblem = NULL);

    /**
     *  This instructs the method to calculate a time step of deltaT
     *  starting with the current state, i.e., the result of the previous
     *  step.
     *  The new state (after deltaT) is expected in the current state.
     *  The return value is the actual timestep taken.
     *  @param "const double &" deltaT
     *  @return "const double" actualDeltaT
     */
    const double step(const double & deltaT);

    /**
     *  This instructs the method to calculate a time step of deltaT
     *  starting with the initialState given.
     *  Also initialization of the method is done.
     *  The new state (after deltaT) is expected in the current state.
     *  The return value is the actual timestep taken.
     *  @param "double &" deltaT
     *  @param "const CState *" initialState
     *  @return "const double" actualDeltaT
     */
    const double step(const double & deltaT, const CState * initialState);

    /* PROTECTED METHODS *******************************************************/

  protected:
    /**
     *   Default constructor.
     */
    CHybridMethod();

    /**
     *   Initializes the solver.
     *
     *   @param time the current time
     */
    void initMethod(C_FLOAT64 time);

    /**
     *   Cleans up memory, etc.
     */
    void cleanup();

    /* VIRTUAL METHODS *********************************************************/

    /**
     *  Simulates the system over the next interval of time. The current time and
     *  the end time of the current step() are given as arguments.
     *
     *  @param  currentTime A C_FLOAT64 specifying the current time
     *  @param  endTime A C_FLOAT64 specifying the end time of the step()
     *  @return A C_FLOAT giving the new time
     */
    virtual C_FLOAT64 doSingleStep(C_FLOAT64 currentTime, C_FLOAT64 endTime) = 0;

    /* DETERMINISTIC STUFF *****************************************************/

    /**
     *   Integrates the deterministic reactions of the system over the specified 
     *   time interval.
     *
     *   @param ds A C_FLOAT64 specifying the stepsize.
     */
    void integrateDeterministicPart(C_FLOAT64 ds);

    /**
     *   Integrates the deterministic reactions of the system over the specified 
     *   time interval.
     *
     *   @param ds A C_FLOAT64 specifying the stepsize.
     */
    void integrateDeterministicPartEuler(C_FLOAT64 ds);

    /**
     *   Does one 4th order RungeKutta step to integrate the system numerically.
     *
     *   @param dt A C_FLOAT64 specifying the stepsize
     *   @param test A C_INT32 determining, if the result is stored in the array
     *               testState (test != 0) or in the array y (test == 0)
     */
    void rungeKutta(C_FLOAT64 dt,
                    C_INT32 test);

    /**
     *   Calculates the derivative of the system and writes it into the array
     *   deriv. Length of deriv must be mDim. CAUTION: Only deterministic
     *   reactions are taken into account. That is, this is only the derivative
     *   of the deterministic part of the system.  
     *
     *   @param deriv An array of length mDim, into which the derivative is
     *                written
     */
    void calculateDerivative(C_FLOAT64 * deriv);

    /**
     *   Gathers the state of the system into the array target. Later on CState
     *   should be used for this. Length of the array target must be mDim.
     *
     *   @param target An array of C_FLOAT64s with length mDim, into which the
     *                 state of the system is written
     */
    void getState(C_FLOAT64 * target);

    /**
     *   Gathers the state of the system into the array target. Later on CState
     *   should be used for this. Length of the array target must be mDim.
     *
     *   @param target An array of C_INT32s with length mDim, into which the
     *                 state of the system is written
     */
    void getState(C_INT32 * target);

    /**
     *   Writes the state specified in the array source into the model. Later on
     *   CState should be used for this. Length of the array source must be mDim
     *   (Total number of metabolites in the model).
     *
     *   @param source An array of C_FLOAT64s with length mDim, holding the
     *                 state of the system to be set in the model
     */
    void setState(C_FLOAT64 * source);

    /**
     *   Changes the state of the system by the values stored in the array
     *   increment. Later on CState should be used for this. Length of the array
     *   increment must be mDim (Total number of metabolites in the model).
     *   Important: Only particle numbers of metabolites i with increment[i]!=0
     *   are changed. That means, that no errors are introduced by converting the
     *   particle numbers into double and back into int.
     *
     *   @param increment An array of C_FLOAT64s with length mDim, holding the
     *                    increment of the state of the system
     *   @param y         An array of C_FLOAT64s with length mDim, holding the
     *                    new state of the system
     *   @param oldState  An arry of C_INT32s with length mDim, holding the
     *                    old state of the system
     */
    void changeState(C_FLOAT64 * increment,
                     C_FLOAT64 * y,
                     C_INT32 * oldState);

    /**
     *   Updates the partitioning depending on the change of the system state
     *   caused by numerical integration of the deterministic part of the
     *   system.
     *
     *   @param increment An array of C_FLOAT64s with length mDim, holding the
     *                    increment of the state of the system
     *   @param y         An array of C_FLOAT64s with length mDim, holding the
     *                    new state of the system
     *   @param time      The current time
     */
    void updatePartitionDet(C_FLOAT64 * increment,
                            C_FLOAT64 * y,
                            C_FLOAT64 time);

    /* STOCHASTIC STUFF ********************************************************/

    /**
     *   Find the reaction index and the reaction time of the stochastic (!)
     *   reaction with the lowest reaction time.
     *
     *   @param ds A reference to a C_FLOAT64. The putative reaction time for the
     *             first stochastic reaction is written into this variable.
     *   @param rIndex A reference to a C_INT32. The index of the first
     *                 stochastic reaction is written into this variable.
     */
    void getStochTimeAndIndex(C_FLOAT64 & ds, C_INT32 & rIndex);

    /**
     *   Executes the specified reaction in the system once. Checks if by firing
     *   this reaction (that is changing particle numbers) any other
     *   deterministic reaction gets stochastic or vice versa and updates
     *   mStochReactionFlags accordingly. In addition every dependent reaction's
     *   amu is updated.
     *
     *   @param rIndex A C_INT32 specifying the index of the reaction, which 
     *                 will be fired.
     *   @param time   The current time
     */
    void fireReactionAndUpdatePartition(C_INT32 rIndex, C_FLOAT64 time);

    /**
     *   Updates the priority queue.
     *
     *   @param rIndex A C_INT32 giving the index of the fired reaction
     *   @param time A C_FLOAT64 holding the time taken by this reaction
     */
    void updatePriorityQueue(C_INT32 rIndex, C_FLOAT64 time);

    /**
     *   Generates a putative reaction time for the given reaction.
     *
     *   @param rIndex A C_INT32 specifying the index of the reaction
     *   @return A C_FLOAT64 holding the calculated reaction time
     */
    C_FLOAT64 generateReactionTime(C_INT32 rIndex);

    /**
     *   Calculates an amu value for a given reaction.
     *
     *   @param rIndex A C_INT32 specifying the reaction to be updated
     */
    void calculateAmu(C_INT32 rIndex);

    /**
     *   Updates the putative reaction time of a stochastic reaction in the 
     *   priority queue. The corresponding amu and amu_old must be set prior to
     *   the call of this method.
     *
     *   @param rIndex A C_INT32 specifying the index of the reaction
     *   @param time A C_FLOAT64 specifying the current time
     */
    void updateTauMu(C_INT32 rIndex, C_FLOAT64 time);

    /* TESTING THE MODEL AND SETTING UP THINGS *********************************/

    /**
     *   Test the model if it is proper to perform stochastic simulations on.
     *   Several properties are tested (e.g. integer stoichometry, all reactions
     *   take place in one compartment only, ...).
     *
     *   @param model The model to be checked
     *   @return 1, if hybrid simulation is possible; <0, if an error occured.
     */
    static C_INT32 checkModel(CModel * model);

    /**
     *   Sets up an internal representation of the balances for each reaction.
     *   This is done in order to be able to deal with fixed metabolites and
     *   to avoid a time consuming search for the indices of metabolites in the
     *   model.
     */
    void setupBalances();

    /**
     *   Sets up the dependency graph
     */
    void setupDependencyGraph();

    /**
     *   Creates for each metabolite a set of reaction indices. If the metabolite
     *   participates in a reaction as substrate or product this reaction is
     *   added to the corresponding set. 
     */
    void setupMetab2React();

    /**
     *   Creates for each metabolite a set of reaction indices. If the metabolite
     *   participates in a reaction as substrate, product or modifier this
     *   reaction is added to the corresponding set. 
     */
    void setupMetab2ReactPlusModifier();

    /**
     *   Creates for each metabolite a set of reaction indices. Each reaction is
     *   dependent on each metabolite resulting in a complete switch. 
     */
    void setupMetab2ReactComplete();

    /**
     *   Creates an initial partitioning of the system. Deterministic and 
     *   stochastic reactions are determined. The array mStochReactions is
     *   initialized.
     */
    void setupPartition();

    /**
     *   Sets up the priority queue.
     *
     *   @param startTime The time at which the simulation starts.
     */
    void setupPriorityQueue(C_FLOAT64 startTime = 0.0);

    /* HELPER METHODS **********************************************************/

    /**
     *   Inserts a new deterministic reaction into the linked list in the
     *   array mStochReactionFlags.
     *
     *   @param rIndex A C_INT32 giving the index of the reaction to be inserted
     *                 into the list of deterministic reactions.
     */
    void insertDeterministicReaction(C_INT32 rIndex);

    /**
     *   Removes a deterministic reaction from the linked list in the
     *   array mStochReactionFlags.
     *
     *   @param rIndex A C_INT32 giving the index of the reaction to be removed
     *                 from the list of deterministic reactions.
     */
    void removeDeterministicReaction(C_INT32 rIndex);

    /**
     *   Finds the index of a metabolite in the vector mMetabolites given the
     *   address.
     *   This method could be moved into the CModel later on.
     *
     *   @param metab A pointer to an instance of CMetab.
     *   @return A C_INT32 holding the index of the metabolite. Returns -1, if
     *           the metabolite is not in the vector.
     */
    C_INT32 findMetab(const CMetab * metab);

    /**
     *   Gets the set of metabolites on which a given reaction depends.
     *
     *   @param rIndex The index of the reaction being executed.
     *   @return The set of metabolites depended on.
     */
    std::set <std::string> *getDependsOn(C_INT32 rIndex);

    /**
     *   Gets the set of metabolites which change number when a given
     *   reaction is executed.
     *
     *   @param rIndex The index of the reaction being executed.
     *   @return The set of affected metabolites.
     */
    std::set <std::string> *getAffects(C_INT32 rIndex);

    /**
     *   Gets the set of metabolites, which participate in the given
     *   reaction either as substrate, product or modifier.
     *
     *   @param rIndex The index of the reaction being executed.
     *   @return The set of participating metabolites.
     */
    std::set <C_INT32> *getParticipatesIn(C_INT32 rIndex);

    /**
     *   Prints out data on standard output.
     */
    void outputData(std::ostream & os, C_INT32 mode);

    /**
     *   Prints out various data on standard output for debugging purposes.
     */
    void outputDebug(std::ostream & os, C_INT32 level);

    /* PRIVATE METHODS *********************************************************/

  private:

    /* VARIABLES ***************************************************************/

  public:

  protected:
    /**
     *   Version number of this class
     */
    CVersion mVersion;

    /**
     *   Pointer to the model
     */
    CModel * mpModel;

    /**
     *   Current time.
     */
    C_FLOAT64 mTime;

    /**
     *   Dimension of the system. Total number of metabolites.
     */
    unsigned C_INT32 mDim;

    /**
     *   Max number of doSingleStep() per step()
     */
    unsigned C_INT32 mMaxSteps;

    /**
     * maximal increase of a particle number in one step.
     */
    C_INT32 mMaxBalance;

    /**
     * This is set to maxint - mMaxSteps*mMaxBalance
     */
    C_INT32 mMaxIntBeforeStep;

    /**
     *   A pointer to the reactions of the model.
     */
    CCopasiVectorNS <CReaction> * mReactions;

    /**
     *   A pointer to the metabolites of the model.
     */
    CCopasiVector <CMetab> * mMetabolites;

    /**
     *   The stoichometry matrix of the model.
     */
    CMatrix <C_FLOAT64> mStoi;

    /**
     *   Arrays to hold the system state and intermediate results
     */
    C_FLOAT64 * x;
    C_FLOAT64 * y;
    C_FLOAT64 * increment;
    C_FLOAT64 * temp;
    C_FLOAT64 * k1;
    C_FLOAT64 * k2;
    C_FLOAT64 * k3;
    C_FLOAT64 * k4;
    C_FLOAT64 * testState;
    C_INT32 * oldState;

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
    /**
     *   Array to hold information about how much metabolites of a reaction
     *   have low particle numbers. If no metabolite of one reaction has
     *   low particle numbers this reaction will be simulated deterministically.
     */
    StochFlag * mStochReactionFlags;
    StochFlag * mFirstFlag;

    /**
     *   Internal representation of the balances of each reaction. The index of
     *   each metabolite in the reaction is provided.
     */
    std::vector <std::vector <Balance> > mBalances;

    /**
     *   Limit for particle numbers. If a particle number is < StochLimit the
     *   corresponding reactions must be simulated stochastically.
     */
    C_INT32 mLowerStochLimit;
    C_INT32 mUpperStochLimit;

    /**
     *   Stepsize for the rungeKutta steps of the numerical integrator.
     */
    C_FLOAT64 mStepsize;

    /**
     *   Vector of relations between metabolites to reactions.
     */
    std::vector <std::set <C_INT32> > mMetab2React;

    /**
     *   The propensities of the stochastic reactions.
     */
    std::vector <C_FLOAT64> mAmu;
    std::vector <C_FLOAT64> mAmuOld;

    /**
     *   Set of the reaction, which must be updated.
     */
    std::set <C_INT32> mUpdateSet;

    /**
     *   The random number generator.
     */
    CRandom * mRandomGenerator;

    /**
     *   Failure status. 
     *   0 = Everything is ok!
     *   !0 = Error.
     */
    C_INT32 mFail;

    /**
     *   The graph of reactions and their dependent reactions. When a reaction is
     *   executed, the propensities for each of its dependents must be updated.
     */
    CDependencyGraph mDG;

    /**
     *   The set of putative stochastic (!) reactions and associated times at
     *   which each reaction occurs. This is represented as a priority queue,
     *   sorted by the reaction time. This heap changes dynamically as
     *   stochastic reactions become deterministic (delete this reaction from
     *   the queue) or vice versa (insert a new reaction into the queue).
     */
    CIndexedPriorityQueue mPQ;

    // DEPRECATED:
    /**
     *   File output stream to write data.
     */
    std::ofstream mOutputFile;

    /**
     *   Output filename.
     */
    std::string mOutputFileName;

    /**
     *   Output counter.
     */
    C_INT32 mOutputCounter;

  private:
  };

#include "CHybridNextReactionRKMethod.h"

#endif // COPASI_CHybridMethod
