// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_COptMethodSRES
#define COPASI_COptMethodSRES

#include "optimization/COptMethod.h"
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
   * @param size_t from
   * @param size_t to
   * @return bool success
   */
  bool swap(size_t from, size_t to);

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
   * @return size_t fittest
   */
  size_t fittest();

  /**
   * Initialise the population
   * @param size_t first
   * @return bool continue
   */
  bool creation(size_t first);

  /**
   * For Stochastic Ranking, evaluate the distance ofparameters to boundaries
   * @return C_FLOAT64 phiVal
   */
  C_FLOAT64 phi(size_t indvNum);

  // Attributes
private:
  /**
   * number of generations
   */
  unsigned C_INT32 mGenerations;

  /**
   * Handle to the process report item "Current Generation"
   */
  size_t mhGenerations;

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
  size_t mVariableSize;

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

  double mTau;    // parameter for updating variances

  double mTauPrime;    // parameter for updating variances
};

#endif  // COPASI_COptMethodSRES
