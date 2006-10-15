/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodEP.h,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 07:43:32 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_COptMethodEP
#define COPASI_COptMethodEP

#include "optimization/COptMethod.h"

#include "utilities/CVector.h"

class CRandom;

class COptMethodEP: public COptMethod
  {
    friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

    // Operations
  private:

    /**
     * Default Constructor
     */
    COptMethodEP(const CCopasiContainer * pParent = NULL);

    /**
     * Initialize arrays and pointer.
     * @return bool success
     */
    virtual bool initialize();

    /**
     * Cleanup arrays and pointers.
     * @return bool success
     */
    virtual bool cleanup();

    /**
     * Evaluate the objective function for the current parameters
     * @return const C_FLOAT64 & objectiveValue
     */
    bool evaluate(const CVector< C_FLOAT64 > & individual);

    /**
     * Initialize contained objects.
     */
    void initObjects();

    /**
     * Mutate one individual
     * @param CVector< C_FLOAT64 > & individual
     * @return bool success
     */
    bool mutate(unsigned C_INT32 i);

    /**
     * Swap individuals from and to
     * @param unsigned C_INT32 from
     * @param unsigned C_INT32 to
     * @return bool success
     */
    bool swap(unsigned C_INT32 from, unsigned C_INT32 to);

    /**
     * Replicate the individuals with crossover
     * @return bool continue
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
     * @return bool continue
     */
    bool creation();

  public:
    /**
     * Copy Constructor
     * @param const COptMethodEP & src
     */
    COptMethodEP(const COptMethodEP& src,
                 const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~COptMethodEP();

    /**
     * Execute the optimization algorithm calling simulation routine
     * when needed. It is noted that this procedure can give feedback
     * of its progress by the callback function set with SetCallback.
     */
    virtual bool optimise();

  private :
    // variables

    /**
     * number of generations
     */
    unsigned C_INT32 mGenerations;

    /**
     * size of the population
     */
    unsigned C_INT32 mGeneration;

    /**
     * Handle to the process report item "Current Generation"
     */
    unsigned C_INT32 mhGenerations;

    /**
     * size of the population
     */
    unsigned C_INT32 mPopulationSize;

    /**
     * a pointer to the randomnumber generator.
     */
    CRandom * mpRandom;

    unsigned C_INT32 mBestIndex;

    double tau1;    // parameter for updating variances

    double tau2;    // parameter for updating variances

    /**
     * number of wins of each individual in the tournament
     */
    CVector< unsigned C_INT32 > mLosses;

    /**
     * The best value found so far.
     */
    C_FLOAT64 mBestValue;

    /**
     * The value of the last evaluation.
     */
    C_FLOAT64 mEvaluationValue;

    /**
     * array of values of objective function f/ individuals
     */
    CVector <C_FLOAT64> mValue;

    /**
     * number of parameters
     */
    unsigned C_INT32 mVariableSize;

    /**
     * for array of individuals w/ candidate values for the parameters
     */
    std::vector< CVector < C_FLOAT64 > * > mIndividual;

    /**
     * for array of variances w/ variance values for the parameters
     */
    std::vector< CVector < C_FLOAT64 > * > mVariance;

    /**
     * The current iteration
     */
    unsigned C_INT32 mCurrentIteration;

    /**
     * Pivot vector used for sorting
     */
    CVector<unsigned C_INT32> mPivot;
  };

#endif  // COPASI_COptMethodEP
