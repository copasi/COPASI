// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CRandomSearch class
 */

#ifndef COPASI_CRandomSearch
#define COPASI_CRandomSearch

#include "copasi/optimization/COptMethod.h"
#include "copasi/randomGenerator/CRandom.h"
#include "copasi/core/CVector.h"

//class CRandom;
//*** need to be added for definition
class COptProblem;

// YOHE: this is an abstract class that contains many virtual functions
// without definitions
//
/** @dia:pos 48.05,34.05 */
/** @dia:route COptMethod; v,46.9608,16.35,33,59.1652,34.05 */
class CRandomSearch : public COptMethod
{
  // Operations
private:
  /**
   * Default Constructor
   */
  CRandomSearch();

  /**
      * Initialize arrays and pointer.
      * @return bool success
      */
  virtual bool initialize();

  /**
   * Initialize contained objects.
   */
  void initObjects();

  /**
   * Evaluate the fitness of one individual
   * @param const CVector< C_FLOAT64 > & individual
   * @return bool continue
   */
  bool evaluate(const CVector< C_FLOAT64 > & individual);

  /**
   * Find the best individual at this generation
   * @return size_t fittest
   */
  size_t fittest();

  /**
   * number of iterations
   */
  unsigned C_INT32 mIterations;

  /**
   * The current iteration
   */
  unsigned C_INT32 mCurrentIteration;

  /**
   * a vector of the number of individuals.
   */
  CVector<C_FLOAT64> mIndividual;

  /**
   * array of values of objective function f/ individuals
   */
  C_FLOAT64 mValue;

  /**
   * a pointer to the randomnumber generator.
   */
  CRandom * mpRandom {NULL};

  /**
   * *** Perhaps this is actually not needed ****number of parameters
   */
  size_t mVariableSize;

  /**
   * The best value found so far.
   */
  C_FLOAT64 mBestValue;

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: RandomSearch)
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  CRandomSearch(const CDataContainer * pParent,
                const CTaskEnum::Method & methodType = CTaskEnum::Method::RandomSearch,
                const CTaskEnum::Task & taskType = CTaskEnum::Task::optimization);

  /**
   * Copy Constructor
   * @param const CRandomSearch & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CRandomSearch(const CRandomSearch & src,
                const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CRandomSearch();

  /**
   * Execute the optimization algorithm calling simulation routine
   * when needed. It is noted that this procedure can give feedback
   * of its progress by the callback function set with SetCallback.
   */
  virtual bool optimise();

  /**
   * Returns the maximum verbosity at which the method can log.
   */
  virtual unsigned C_INT32 getMaxLogVerbosity() const;


  virtual C_FLOAT64 getBestValue() const;

  virtual C_FLOAT64 getCurrentValue() const;

  virtual const CVector< C_FLOAT64 > * getBestParameters() const;

  virtual const CVector< C_FLOAT64 > * getCurrentParameters() const;
};

#endif  // COPASI_CRandomSearch
