/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodSRES.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/05/02 20:30:39 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_COptMethodSRES
#define COPASI_COptMethodSRES

#include "COptMethod.h"
#include "utilities/CVector.h"

class CRandom;

/**
 * COptMethodSRES class
 */

class COptMethodSRES : public COptMethod
  {
    friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

    // Operations
  public:
    /**
     * Copy Constructor
     * @param const COptMethodSRES & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptMethodSRES(const COptMethodSRES & src,
                   const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~COptMethodSRES();

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
    COptMethodSRES(const CCopasiContainer * pParent = NULL);

    /**
     * Initialize contained objects.
     */
    void initObjects();

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
     * Evaluate the fitness of one individual
     * @param const CVector< C_FLOAT64 > & individual
     * @return bool continue
     */
    bool evaluate(const CVector< C_FLOAT64 > & individual);

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
     * Mutate the new generation
     */
    bool mutate();

    /**
     * Select surviving population
     * @return success
     */
    void select();

    /**
     * Find the best individual at this generation
     * @return unsigned C_INT32 fittest
     */
    unsigned C_INT32 fittest();

    /**
     * Initialise the population
     * @param unsigned C_INT32 first
     * @return bool continue
     */
    bool creation(unsigned C_INT32 first);

    /**
     * For Stochastic Ranking, evaluate the distance ofparameters to boundaries
     * @return C_FLOAT64 phiVal
     */
    C_FLOAT64 phi(C_INT32 indvNum);

    // Attributes
  private:
    /**
     * number of generations
     */
    unsigned C_INT32 mGenerations;

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

    /**
     * Probability value used for SR ****
     */
    C_FLOAT64 mPf;

    /**
     * number of parameters
     */
    unsigned C_INT32 mVariableSize;

    /**
     * for array of individuals w/ candidate values for the parameters
     */
    std::vector< CVector < C_FLOAT64 > * > mIndividual;

    /**
     * For Stochastic Ranking.  Used for array of Phi values for the individuals
     */
    CVector < C_FLOAT64 > mPhi;

    /**
     * for array of variances w/ variance values for the parameters
     */
    std::vector< CVector < C_FLOAT64 > * > mVariance;

    /**
     * A vector of maximal variances
     */
    CVector < C_FLOAT64 > mMaxVariance;

    /**
     * The value of the last evaluation.
     */
    C_FLOAT64 mEvaluationValue;

    /**
     * array of values of objective function f/ individuals
     */
    CVector< C_FLOAT64 > mValue;

    C_FLOAT64 mBestValue;

    unsigned C_INT32 mGeneration;

    double tau1;    // parameter for updating variances

    double tau2;    // parameter for updating variances
  };

#endif  // COPASI_COptMethodSRES
