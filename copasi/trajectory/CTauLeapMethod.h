/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTauLeapMethod.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/09 17:08:45 $
   End CVS Header */

/**
 *   CTauLeapMethod
 *
 *   This class implements the tau-Leap method for the simulation of a
 *   biochemical system over time (see Gillespie (2001): Approximate
 *   accelerated stochastic simulation of chemically reacting systems.
 *   J. Chemical Physics, 115:1716-1733).
 *
 *   File name: CTauLeapMethod.h
 *   Author: Juergen Pahle
 *   Email: juergen.pahle@eml-r.villa-bosch.de
 *
 *   Last change: 20, December 2004
 *
 *   (C) European Media Lab 2004.
 */
#ifndef COPASI_CTauLeapMethod
#define COPASI_CTauLeapMethod

/* INCLUDES ******************************************************************/
#include "CTrajectoryMethod.h"
#include "utilities/CCopasiVector.h"

/* DEFINE ********************************************************************/
#define TAU                    0.01
#define USE_RANDOM_SEED        1
#define RANDOM_SEED            1
#define INT_EPSILON            0.1

/* CLASSES *******************************************************************/
class CTrajectoryProblem;
class CState;
class CReaction;
class CHybridBalance;

class CTauLeapMethod : public CTrajectoryMethod
  {
    friend CTrajectoryMethod *
    CTrajectoryMethod::createTrajectoryMethod(CCopasiMethod::SubType subType,
        CTrajectoryProblem * pProblem);

    /* PUBLIC METHODS ************************************************************/

  public:
    /**
     *   Copy constructor
     *   @param "const CTauLeapMethod &" src
     */
    CTauLeapMethod(const CTauLeapMethod & src);

    /**
     *   Destructor.
     */
    ~CTauLeapMethod();

    /**
     *   Creates a CTauLeapMethod adequate for the problem.
     *   (only regular CTauLeapMethod so far)
     */
    static CTauLeapMethod *
    createTauLeapMethod(CTrajectoryProblem * pProblem = NULL);

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

    /**
     * Check if the method is suitable for this problem
     * @return bool suitability of the method
     */
    virtual bool isValidProblem(const CCopasiProblem * pProblem);

    /* PROTECTED METHODS *********************************************************/

  protected:
    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTauLeapMethod(const CCopasiContainer * pParent = NULL);

    /**
     * Initializes the solver.
     */
    void initMethod();

    /**
     *   Cleans up memory, etc.
     */
    void cleanup();

    /**
     *  Simulates the system over the next interval of time. The timestep
     *  is given as argument.
     *
     *  @param  ds A C_FLOAT64 specifying the timestep
     */
    void doSingleStep(C_FLOAT64 ds);

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
     * Calculate the propensities for all reactions
     */
    void updatePropensities();

    /**
     * Calculate one of the propensities
     */
    C_INT32 calculateAmu(C_INT32 reaction_index);

    /**
     *   Updates the system according to the probabilistic
     *   number of firings mK[i] of each reaction i
     */
    void updateSystem();

    /* VARIABLES *****************************************************************/

  protected:

    /**
     *   Pointer to the model.
     */
    const CModel * mpModel;

    /**
     *   A pointer to the reactions of the model.
     */
    const CCopasiVectorNS <CReaction> * mpReactions;

    /**
     *   Number of reactions.
     */
    unsigned C_INT32 mNumReactions;

    /**
     *   A pointer to the metabolites of the model.
     */
    CCopasiVector <CMetab> * mpMetabolites;

    /**
     *   Number of variable metabolites.
     */
    unsigned C_INT32 mNumNumbers;

    /**
     *   The propensities of the stochastic reactions.
     */
    std::vector <C_FLOAT64> mAmu;

    /**
     *   The sum of propensities.
     */
    C_FLOAT64 mA0;

    /**
     *   The k-values of the reactions, that is the
     *   probabilistic number of firings within one leap.
     */
    std::vector <C_INT64> mK;

    /**
     *   The particle numbers.
     */
    std::vector <C_INT64> mNumbers;

    /**
     *   Local representation of the stoichiometry.
     */
    std::vector < std::vector <CHybridBalance> > mLocalBalances;

    /**
     *   Local representation of the substrates.
     */
    std::vector < std::vector <CHybridBalance> > mLocalSubstrates;

    /**
     *   The tau value to use.
     */
    C_FLOAT64 mTau;

    /**
     *   Specifies if the mRandomSeed should be used.
     *   otherwise a randomly chosen seed is used.
     */
    bool mUseRandomSeed;

    /**
     *   The random seed to use.
     */
    unsigned C_INT32 mRandomSeed;

    /**
     *   The random number generator.
     */
    CRandom * mpRandomGenerator;

    /**
     *   Variables used for the generation of poisson-distr.
     *   random variables.
     */
    C_FLOAT64 sq, alxm, g, oldm;
    static const C_FLOAT64 cof[6];
  };

#endif // COPASI_CTauLeapMethod
