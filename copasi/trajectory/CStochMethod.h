#ifndef COPASI_CStochMethod
#define COPASI_CStochMethod

#include "utilities/CVector.h"
#include "CTrajectoryMethod.h"
#include "CTrajectoryProblem.h"
#include "model/CModel.h"

/**
 * Integer Balances  for internal use
 */

class CStochBalance
  {
  public:
    //CStochBalance();
    CMetab * mMetabAddr;
    C_INT32 mBalance;
  };

class CRandom;

class CStochMethod : private CTrajectoryMethod
  {
    friend CTrajectoryMethod *
    CTrajectoryMethod::createTrajectoryMethod(CTrajectoryMethod::Type type);

  protected:

    /**
     * The propensities for the reactions
     */
    std::vector<C_FLOAT64> mAmu;
    /**
     * The sum of the propensities
     */
    C_FLOAT64 mA0;

    /**
     * The stored propensities for the reactions before the last update
     */
    std::vector<C_FLOAT64> mAmuOld;
    /**
     * The sum of the propensities before the last update
     */
    C_FLOAT64 mA0Old;

    /**
     * Do one iteration of the simulation
     * @return Current simulation time or -1 if error.
     */
    virtual C_FLOAT64 doSingleStep(C_FLOAT64 time) = 0;

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
     * Generate the putative time taken before any reaction takes place
     * @return The time before the reaction
     */
    C_FLOAT64 generateReactionTime();

    /**
     * Generate the putative time taken before a special reaction takes place
     * @return The time before the reaction
     */
    C_FLOAT64 generateReactionTime(C_INT32 reaction_index);

    /**
     * Update the particle numbers according to which reaction ocurred
     * @return mFail
     * @see mFail
     */
    C_INT32 updateSystemState(C_INT32 reaction_index);

    /**
    * Set up the dependency graph and the balances
    */
    void setupDependencyGraphAndBalances();

  private:

    /**
     * Get the set of metabolites on which a given reaction depends.
     * @param reaction_index The index of the reaction being executed.
     * @return The set of metabolites depended on.
     */

    std::set<CMetab*> *getDependsOn(C_INT32 reaction_index);

    /**
     * Get the set of metabolites which change number when a given
     * reaction is executed.
     * @param reaction_index The index of the reaction being executed.
     * @return The set of affected metabolites.
     */
    std::set<CMetab*> *getAffects(C_INT32 reaction_index);

    /**
    * max number of single stochastic steps to do in one step()
    */
    C_INT32 mMaxSteps;

  public:
    /**
     *  Default constructor.
     */
    CStochMethod();
    /**
     *  Copy constructor.
     *  @param "const CStochMethod &" src
     */
    CStochMethod(const CStochMethod & src);

    /**
     *  Destructor.
     */
    ~CStochMethod();

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
     *  The new state (after deltaT) is expected in the current state.
     *  The return value is the actual timestep taken.
     *  @param "double &" deltaT
     *  @param "const CState *" initialState
     *  @return "const double" actualDeltaT
     */
    const double step(const double & deltaT, const CState * initialState);

    // the following operations were public in Clsoda.

  protected:

    /**
     * The random number generator
     */
    CRandom *mRandomGenerator;

    /**
     * A pointer to the instance of CModel being used. May get thrown out later
     */
    CModel *mpModel;

    /**
     * The graph of reactions and their dependent reactions. When a reaction is
     * executed, the propensities for each of its dependents must be updated.
     */
    CDependencyGraph mDG;

    /**
     * The balances of the reactions as integers
     */
    std::vector < std::vector <CStochBalance> > mLocalBalances;
  };
#endif // COPASI_CStochMethod
