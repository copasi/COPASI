/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CHybridMethodLSODA.h,v $
   $Revision: 1.1.2.2 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/06/01 12:22:58 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *   CHybridMethodLSODA
 *
 *   This class implements an hybrid algorithm to simulate a biochemical
 *   system over time.
 *
 *   File name: CHybridMethodLSODA.h
 *   Author:
 *   Email:
 *
 *   Last change: 08, May 2006
 *
 *   (C) European Media Lab 2003.
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
#ifndef COPASI_CHybridMethodLSODA
#define COPASI_CHybridMethodLSODA

/* INCLUDES ******************************************************************/
#include "CTrajectoryMethod.h"
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "utilities/CVersion.h"
#include "utilities/CMatrix.h"
#include "utilities/CDependencyGraph.h"
#include "utilities/CIndexedPriorityQueue.h"
#include "utilities/CCopasiVector.h"
#include "odepack++/CLSODA.h"

/* DEFINE ********************************************************************/
#define MAX_STEPS                    1000000
#define INT_EPSILON                  0.1
#define LOWER_STOCH_LIMIT            800 //800
#define UPPER_STOCH_LIMIT            1000 //1000
#define PARTITIONING_STEPSIZE        0.001
#define PARTITIONING_INTERVAL        1
#define OUTPUT_COUNTER               100
#define DEFAULT_OUTPUT_FILE          "hybridLSODA.output"
#define SUBTYPE                      1
#define USE_RANDOM_SEED              false
#define RANDOM_SEED                  1

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
 *  Element of the array mReactionFlags. The deterministic reactions are
 *  organized in a linked list to be able to iterate over them quickly.
 **/
class CHybridLSODAStochFlag
  {
  public:
    C_INT32 mIndex;
    C_INT32 mValue;
    CHybridLSODAStochFlag * mpPrev;
    CHybridLSODAStochFlag * mpNext;

    // insert operator

    friend std::ostream & operator<<(std::ostream & os, const CHybridLSODAStochFlag & d);
  };

/**
 *    Internal representation of the balances of each reaction. The index of
 *    each metabolite in the reaction is provided.
 **/
class CHybridLSODABalance
  {
  public:
    C_INT32 mIndex;
    C_INT32 mMultiplicity;
    CMetab * mpMetabolite;

    // insert operator

    friend std::ostream & operator<<(std::ostream & os, const CHybridLSODABalance & d);
  };

class CHybridMethodLSODA : public CTrajectoryMethod
  {
    friend CTrajectoryMethod *
    CTrajectoryMethod::createTrajectoryMethod(CCopasiMethod::SubType subType,
        CTrajectoryProblem * pProblem);

    /* PUBLIC METHODS **********************************************************/

  public:
    /**
     * Copy constructor
     * @param const CHybridMethodLSODA & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CHybridMethodLSODA(const CHybridMethodLSODA & src,
                       const CCopasiContainer * pParent = NULL);

    /**
     *   Destructor.
     */
    ~CHybridMethodLSODA();

    /**
     * This methods must be called to elevate subgroups to
     * derived objects. The default implementation does nothing.
     * @return bool success
     */
    virtual bool elevateChildren();

    /**
     *  Creates a HybridMethodLSODA adequate for the problem.
     *  (only CHybridNextReactionLSODAMethod so far)
     */
    static CHybridMethodLSODA *
    createHybridMethodLSODA(CTrajectoryProblem * pProblem = NULL);

    /**
     *  This instructs the method to calculate a time step of deltaT
     *  starting with the current state, i.e., the result of the previous
     *  step.
     *  The new state (after deltaT) is expected in the current state.
     *  The return value is the actual timestep taken.
     *  @param "const double &" deltaT
     */
    virtual void step(const double & deltaT);

    /**
     *  This instructs the method to prepare for integration
     *  starting with the initialState given.
     *  @param "const CState *" initialState
     */
    virtual void start(const CState * initialState);

    /**
    * Check if the method is suitable for this problem
    * @return bool suitability of the method
    */
    virtual bool isValidProblem(const CCopasiProblem * pProblem);

    /* PROTECTED METHODS *******************************************************/

  protected:
    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CHybridMethodLSODA(const CCopasiContainer * pParent = NULL);

    /**
     * Initializes the solver.
     * @param time the current time
     */
    void initMethod(C_FLOAT64 time);

    /**
     *   Cleans up memory, etc.
     */
    void cleanup();

    /* VIRTUAL METHODS *********************************************************/

    /**
     *  Simulates the system over the next interval of time. The current time
     *  and the end time of the current step() are given as arguments.
     *
     *  @param  currentTime A C_FLOAT64 specifying the current time
     *  @param  endTime A C_FLOAT64 specifying the end time of the step()
     *  @return A C_FLOAT giving the new time
     */
    virtual C_FLOAT64 doSingleStep(C_FLOAT64 currentTime, C_FLOAT64 endTime) = 0;

    /* DETERMINISTIC STUFF *****************************************************/

    /**
     *   Integrates the deterministic reactions of the system over the
     *   specified time interval.
     *
     *   @param ds A C_FLOAT64 specifying the stepsize.
     */
    void integrateDeterministicPart(C_FLOAT64 ds);

    /**
     *   Calculates the derivative of the system and writes it into the vector
     *   deriv. Length of deriv must be mNumVariableMetabs.
     *   CAUTION: Only deterministic reactions are taken into account. That is,
     *   this is only the derivative of the deterministic part of the system.
     *
     *   @param deriv A vector reference of length mNumVariableMetabs, into
     *                which the derivative is written
     */

    void calculateDerivative(std::vector <C_FLOAT64> & deriv);

    /* specific LSODA STAFF */

    /**
     *  Calculate the default absolute tolerance
     *  @param const CModel * pModel
     *  @return C_FLOAT64 defaultAtol
     */
    C_FLOAT64 getDefaultAtol(const CModel * pModel) const;

    static void EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

    /**
     *  This evaluates the derivatives for the complete model
     */

    void evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

    /* STOCHASTIC STUFF ********************************************************/

    /**
     *   Find the reaction index and the reaction time of the stochastic (!)
     *   reaction with the lowest reaction time.
     *
     *   @param ds A reference to a C_FLOAT64. The putative reaction time for
     *             the first stochastic reaction is written into this variable.
     *   @param rIndex A reference to a C_INT32. The index of the first
     *                 stochastic reaction is written into this variable.
     */
    void getStochTimeAndIndex(C_FLOAT64 & ds, C_INT32 & rIndex);

    /**
     *   Executes the specified reaction in the system once.
     *
     *   @param rIndex A C_INT32 specifying the index of the reaction, which
     *                 will be fired.
     */
    void fireReaction(C_INT32 rIndex);

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
     *   Several properties are tested (e.g. integer stoichometry, all
     *   reactions take place in one compartment only, irreversibility...).
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
     *   Creates for each metabolite a set of reaction indices. If the
     *   metabolite participates in a reaction as substrate or product this
     *   reaction is added to the corresponding set.
     */
    void setupMetab2React();

    /**
     *   Creates for each metabolite a set of reaction indices. If the
     *   metabolite participates in a reaction as substrate, product or
     *   modifier this reaction is added to the corresponding set.
     */
    void setupMetab2ReactPlusModifier();

    /**
     *   Creates for each metabolite a set of reaction indices. Each reaction
     *   is dependent on each metabolite resulting in a complete switch.
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
     *   Updates the partitioning of the system depending on the particle
     *   numbers present.
     */
    void partitionSystem();

    /**
     *   Inserts a new deterministic reaction into the linked list in the
     *   vector mReactionFlags.
     *
     *   @param rIndex A C_INT32 giving the index of the reaction to be
     *                 inserted into the list of deterministic reactions.
     */
    void insertDeterministicReaction(C_INT32 rIndex);

    /**
     *   Removes a deterministic reaction from the linked list in the
     *   vector mReactionFlags.
     *
     *   @param rIndex A C_INT32 giving the index of the reaction to be
     *                 removed from the list of deterministic reactions.
     */
    void removeDeterministicReaction(C_INT32 rIndex);

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
    /**
     * Intialize the method parameter
     */
    void initializeParameter();

  private:

    /* VARIABLES ***************************************************************/

  public:

  protected:

    /**
     *   Status of the metabolites. Particle number can be high or low.
     */
    enum metabStatus {LOW = 0, HIGH};

    /**
     *   Version number of this class
     */
    CVersion mVersion;

    /**
     *   Pointer to the model
     */
    const CModel * mpModel;

    /**
     *   Dimension of the system. Total number of metabolites.
     */
    unsigned C_INT32 mNumVariableMetabs;

    /**
     *   Max number of doSingleStep() per step()
     */
    unsigned C_INT32 mMaxSteps;

    /**
     *   Specifies if the mRandomSeed should be used.
     *   otherwise a randomly chosen seed is used.
     */
    bool mUseRandomSeed;

    /**
     *  The random seed to use.
     */
    unsigned C_INT32 mRandomSeed;

    /**
     * maximal increase of a particle number in one step.
     */
    C_INT32 mMaxBalance;

    /**
     * This is set to maxint - mMaxSteps*mMaxBalance
     */
    C_INT32 mMaxIntBeforeStep;

    /**
     * indicates if the correction N^2 -> N*(N-1) should be performed
     */
    bool mDoCorrection;

    /**
     *   A pointer to the reactions of the model.
     */
    const CCopasiVectorNS <CReaction> * mpReactions;

    /**
     *   A pointer to the metabolites of the model.
     */
    CCopasiVector <CMetab> * mpMetabolites;

    /**
     *   The stoichometry matrix of the model.
     */
    CMatrix <C_FLOAT64> mStoi;

    /**
     *   Vectors to hold the system state and intermediate results
     */
    std::vector <C_FLOAT64> temp;

    /**
     *   Vector to hold information about how many metabolites of a reaction
     *   have low particle numbers. If no metabolite of one reaction has
     *   low particle numbers this reaction will be simulated det.
     */
    std::vector <CHybridLSODAStochFlag> mReactionFlags;
    CHybridLSODAStochFlag * mFirstReactionFlag;

    /**
     *   Vector holding information on the status of metabolites. They can
     *   have low or high particle numbers.
     */
    std::vector <metabStatus> mMetabFlags;

    /**
     *   Internal representation of the balances of each reaction. The index of
     *   each metabolite in the reaction is provided.
     */
    std::vector <std::vector <CHybridLSODABalance> > mLocalBalances;

    /**
     *   Internal representation of the substrates of each reaction. The index
     *   of each substrate-metabolite is provided.
     */
    std::vector <std::vector <CHybridLSODABalance> > mLocalSubstrates;

    /**
     *   Limit for particle numbers. If a particle number is < StochLimit the
     *   corresponding reactions must be simulated stochastically.
     */
    C_FLOAT64 mLowerStochLimit;
    C_FLOAT64 mUpperStochLimit;

    /**
     *   The system gets repartitioned after this number of elementary steps.
     */
    unsigned C_INT32 mPartitioningInterval;

    /**
     *   Number of elementary steps after the last partitioning.
     */
    unsigned C_INT32 mStepsAfterPartitionSystem;

    /**
     *   Partitioning stepsize
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
     *   Set of the reactions, which must be updated.
     */
    std::set <C_INT32> mUpdateSet;

    /**
     *   The random number generator.
     */
    CRandom * mpRandomGenerator;

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

    /*  specific LSODA STAFF */

    /**
     * this flag indicates whether the next LSODA call needs to reinitialize the
     * integrater (if the partitioning has changed or a stochastic reaction was fired)
     */
    bool mRestartLSODA;

    /**
     *  A pointer to the current state in complete model view.
     */
    CState * mpState;

    /**
     *  mDim[0] is the dimension of the ODE system.
     * mDim[1] contains CLsodaMethod * this to be used in the static method EvalF
     * Note: this works only if sizeof(C_INT) == ptr_size;
     */
    C_INT mDim[2];

    /**
     *  Pointer to the array with left hand side values.
     */
    C_FLOAT64 * mY;

    /**
     *  Vector containig the derivatives after calling eval
     */
    CVector< C_FLOAT64 > mYdot;

    /**
     *  Current time.
     */
    C_FLOAT64 mTime;

    /**
     *   Requested end time.
     */
    C_FLOAT64 mEndt;

    /**
     *  LSODA state.
     */
    C_INT mLsodaStatus;

    /**
     *
     */
    bool mReducedModel;

    /**
     *  Relative tolerance.
     */
    C_FLOAT64 mRtol;

    /**
     *
     */
    bool mDefaultAtol;

    /**
     *  Absolute tolerance.
     */
    C_FLOAT64 mAtol;

    /**
     *
     */
    std::ostringstream mErrorMsg;

    CLSODA mLSODA;
    C_INT mState;
    CVector< C_FLOAT64 > mDWork;
    CVector< C_INT > mIWork;
    C_INT mJType;

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

#include "CHybridNextReactionLSODAMethod.h"

#endif // COPASI_CHybridMethodLSODA
