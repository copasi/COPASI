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
 *   Last change: 11, Aug 2014
 *
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
#include "copasi/utilities/CCopasiVector.h"
#include "CExpRKMethod.h"

/* DEFINE ********************************************************************/
#define MAX_STEPS_ODE                10000
#define INT_EPSILON                  0.1
#define SUBTYPE                      1
#define USE_RANDOM_SEED              false
#define RANDOM_SEED                  1

//Simulation Part
#define SLOW                         false
#define FAST                         true

//Event Flag
#define SLOW_REACT                  -1

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
class CModelEntity;

/**
 * Internal representation of the balances of each reaction.
 * The index of each metabolite in the reaction is provided.
 */
class CHybridODE45Balance
{
public:
    size_t  mIndex;
    C_FLOAT64 mMultiplicity;
    CMetab *mpMetabolite;
};

/**
 * A class to record whether a metab is slow or fast
 * @param fastReactions is applied to store which reactions this
 *        metab participates
 * @param flag, if set is empty -> false, else, -> true
 */

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

protected:
    enum RootMasking
    {
        NONE = 0,
        ALL,
        DISCRETE
    };

    enum MethodUsed
    {
        STOCHASTIC,
        DETERMINISTIC,
        HYBRID
    };

    enum ODEState
    {
        ODE_ERR = -2,
        ODE_INIT = 0,
        ODE_NEW  = 1,
        ODE_CONT = 2,
        ODE_EVENT = 3,
        ODE_FINISH = 4
    };

    enum SystemStatus
    {
        SYS_ERR = -2,
        SYS_NEW = 1,
        SYS_CONT = 2,
        SYS_EVENT = 3,
        SYS_END = 5
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
     * Destructor.
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
     * Check whether a function is fast or not.
     */
    void setupReactionFlags();

    /**
     * Setup mMethod, switching between Deterministic Method and 
     * Hybrid Method
     */
    void setupMethod();

    /**
     * Sets up an internal representation of the balances for each reaction.
     * This is done in order to be able to deal with fixed metabolites and
     * to avoid a time consuming search for the indices of metabolites in the
     * model.
     */
    void setupBalances();


    //================Function for ODE45================
public:

protected:

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
     * This evaluates the derivatives for the complete model
     */
    void evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);


    /**
     * This evaluates the roots value of the system
     */
    void evalR(const C_FLOAT64 * t, const C_FLOAT64 * y, const size_t *nr, C_FLOAT64 *r);

    //================Function for Simulation================
public:
    /**
     * This instructs the method to calculate a time step of deltaT
     * starting with the current state, i.e., the result of the previous
     * step.
     * The new state (after deltaT) is expected in the current state.
     * The return value is the actual timestep taken.
     * @param "const double &" deltaT
     * @return Status status
     */
    virtual Status step(const double & deltaT);

protected:
    /**
     * Simulates the system over the next interval of time. The current time
     * and the end time of the current step() are given as arguments.
     *
     * @param  endTime A C_FLOAT64 specifying the end time of the step()
     * @return A C_FLOAT giving the new time
     */
    C_FLOAT64 doSingleStep(C_FLOAT64 endTime);

    /**
     * Calculates amu values of slow reactions.
     */
    void calculateAmu();


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


    //================Function for Root==============
private:
    /**
     * Function called from TrajectoryMethod which update 
     * system state and inform ODE solver to restart
     * integration.
     */
    virtual void stateChanged();

    void maskRoots(CVectorCore<C_FLOAT64> & rootValues);

    void createRootMask();
  
    void destroyRootMask();

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
     * Print out data on standard output.
     */
    void outputData();

    /**
     * Print out System state
     */
    void outputState(const CState * pS);

    /**
     * tests if the model contains a global value with an assignment rule that is
     * used in calculations
     */
    static bool modelHasAssignments(const CModel* pModel);

    /**
     * Print out system state given in array y
     */
    void outputY(C_FLOAT64 *y);

//Attributes:
    //================Model Related================
private:
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


    //~~~~~~~~Metabs Related~~~~~~~~
    /**
     * Index of Reaction Metabs in CState
     */
    size_t mReactMetabId;


    /**
     * Dimension of the system. Total number of metabolites.
     */
    size_t mNumReactMetabs;

    /**
     * A pointer to the metabolites of the model.
     */
    CCopasiVector <CMetab> * mpMetabolites;

    /**
     * index of the first metab in CState
     */
    size_t mFirstMetabIndex;


    //~~~~~~~~Reaction Related~~~~~~~~
    /**
     * Number of Reactions
     */
    size_t mNumReactions;

    /**
     * Number of Slow Reactions
     */
    size_t mNumSlowReactions;

    /**
     * Index of Slow Reactions
     */
    CVector <size_t> mSlowIndex;

    /**
     * A pointer to the reactions of the model.
     */
    const CCopasiVectorNS <CReaction> * mpReactions;

    /**
     * A vector recording CReaction points to slow reactions
     */
    CVector < CReaction* > mSlowReactionPointer;

    /**
     * Internal representation of the balances of each reaction. The index of
     * each metabolite in the reaction is provided.
     */
    std::vector <std::vector <CHybridODE45Balance> > mLocalBalances;

    /**
     * Bool value
     */
    bool mHasStoiReaction;
    bool mHasDetermReaction;

    /**
     * An Integer showes the method now CHybridMethod used
     * 0 == Stochastic
     * 1 == Deterministic
     * 2 == Hybrid
     */
    MethodUsed mMethod;

    //================Attributes for State================
    /**
     *  A pointer to the current state in complete model view.
     */
    CState * mpState;

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
     * Record whether ODE solver has been initialized
     */
    bool mODEInitalized;

    /**
     *   Max number of doSingleStep() per step()
     */
    size_t mMaxSteps;
    size_t mRootCounter;
    bool   mMaxStepsReached;

    /**
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
     * state of ODE45, indicating what to do next in the step part
     * -1, error emerge
     *  0, finish all integration
     *  1, finish one step integration
     *  2, has event
     */
    ODEState mODEState;

    SystemStatus mSysStatus;

    /**
     * The propensities of the stochastic reactions.
     */
    CVector <C_FLOAT64> mAmu;

    //================Attributes for Root================
    /**
     * Status of Root and Slow Event
     */
    bool mHasRoot;
    bool mHasSlow;

    /**
     * Number of Roots
     */
    size_t mRootNum;

    /**
     * A mask which hides all roots being constant and zero.
     */
    CVector< bool > mRootMask;

    /**
     * A which indicates whether roots change only discretely.
     */
    CVector< bool > mDiscreteRoots;

    /**
     * Root counter to determine whether the internal
     * step limit is exceeded.
     */
    //size_t mRootCounter;
  
protected:
    /**
     * A Boolean flag indicating whether we should try masking roots
     */
    RootMasking mRootMasking;


    //=================Root Dealing Part for Stochastic Part================
private:

    /**
     * Value of Roots
     */
  
    C_FLOAT64 * mpRT;

 
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

    /**
     *
     */
    C_FLOAT64 mFactor;
};

#endif // COPASI_CHybridMethodODE45
