/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodGA.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/03/30 14:30:28 $
   End CVS Header */

/**
 * COptMethodGA class
 */

#ifndef COPASI_COptMethodGA
#define COPASI_COptMethodGA

#include "COptMethod.h"
#include "utilities/CVector.h"

class CRandom;

//  this is an abstract class that contains many virtual functions
// without definitions

class COptMethodGA : public COptMethod
  {
    friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

    // Operations
  public:
    /**
     * Copy Constructor
     * @param const COptMethodGA & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptMethodGA(const COptMethodGA & src,
                 const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~COptMethodGA();

    /**
     * Execute the optimization algorithm calling simulation routine 
     * when needed. It is noted that this procedure can give feedback 
     * of its progress by the callback function set with SetCallback.
     * @ return success;
     */
    virtual bool optimise();

  private:
    /**
     * Default Constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptMethodGA(const CCopasiContainer * pParent = NULL);

    /**
     * Initialize arrays and pointer.
     * @return bool success
     */
    bool initialize();

    /**
     * Cleanup arrays and pointers.
     * @return bool success
     */
    bool cleanup();

    /**
     * Evaluate the fitness of one individual
     * @param const CVector< C_FLOAT64 > & individual
     * @return C_FLOAT64 fitness
     */
    C_FLOAT64 evaluate(const CVector< C_FLOAT64 > & individual);

    /**
     * Ccopy individual src to position target
     * @param unsigned C_INT32 from
     * @param unsigned C_INT32 to
     * @return bool success
     */
    bool copy(unsigned C_INT32 from, unsigned C_INT32 to);

    /**
     * Swap individuals from and to
     * @param unsigned C_INT32 from
     * @param unsigned C_INT32 to
     * @return bool success
     */
    bool swap(unsigned C_INT32 from, unsigned C_INT32 to);

    /**
     * Mutate one individual
     * @param unsigned C_INT32 index
     * @return bool success
     */
    bool mutate(unsigned C_INT32 index);

    /**
     * @param const CVector< C_FLOAT64 > & parent1
     * @param const CVector< C_FLOAT64 > & parent2
     * @param CVector< C_FLOAT64 > & child1
     * @param CVector< C_FLOAT64 > & child2
     */
    bool crossover(const CVector< C_FLOAT64 > & parent1,
                   const CVector< C_FLOAT64 > & parent2,
                   CVector< C_FLOAT64 > & child1,
                   CVector< C_FLOAT64 > & child2);

    /**
     * Shuffle the parents for breading
     */
    bool shuffle();

    /**
     * Replicate the individuals with crossover
     * @return bool success
     */
    bool replicate();

    /**
     * Select surviving population
     * @return bool success
     */
    bool select();

    /**
     * Find the best individual at this generation
     * @return unsigned C_INT32 fittest
     */
    unsigned C_INT32 fittest();

    /**
     * Initialise the population
     * @param unsigned C_INT32 first
     * @param unsigned C_INT32 last (default: population size)
     * @return bool success
     */
    bool creation(unsigned C_INT32 first, unsigned C_INT32 last = ULONG_MAX);

    // Attributes
  private:
    // number of generations
    unsigned C_INT32 mGenerations;

    // size of the population
    unsigned C_INT32 mPopulationSize;

    CRandom * mpRandom;

    // number of parameters
    unsigned C_INT32 mVariableSize;

    // for array of individuals w/ candidate values for the parameters
    std::vector< CVector < C_FLOAT64 > * > mIndividual;

    CVector< bool > mCrossOverFalse;
    CVector< bool > mCrossOver;

    // array of values of objective function f/ individuals
    CVector< C_FLOAT64 > mValue;

    // indexes for shuffling the population
    CVector< unsigned C_INT32 > mShuffle;

    // number of wins of each individual in the tournament
    CVector< unsigned C_INT32 > mWins;

    // variance for mutations
    C_FLOAT64 mMutationVarians;

    unsigned int best;   // index of the best individual
  };

#endif  // COPASI_COptMethodGA
