// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_COptPopulationMethod_H
#define COPASI_COptPopulationMethod_H

#include "copasi/optimization/COptMethod.h"
#include "copasi/core/CVector.h"
#include "copasi/OpenMP/CRandomContext.h"

class COptPopulationMethod :
  public COptMethod
{
private:
  /**
  * Default constructor.
  */
  COptPopulationMethod();
public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType
   * @param const CTaskEnum::Task & taskType
   * @param const bool & parallel
   */
  COptPopulationMethod(const CDataContainer * pParent,
                       const CTaskEnum::Method & methodType,
                       const CTaskEnum::Task & taskType,
                       const bool & parallel);

  /**
  * Copy constructor
  * @param const COptMethod & src
  * @param const CDataContainer * pParent (default: NULL)
  */
  COptPopulationMethod(const COptPopulationMethod & src,
                       const CDataContainer * pParent);

  /**
  * Destructor
  */
  virtual ~COptPopulationMethod();

  /**
   * Initialize contained objects.
   */
  void initObjects();

  /**
   * Initialize arrays and pointer. the population member ought to be
   * initialized in the subclasses.
   * @return bool success
   */
  virtual bool initialize();

  /**
   * Cleanup arrays and pointers.
   * @return bool success
   */
  virtual bool cleanup();

  C_INT32 getPopulationSize();
  C_INT32 getNumGenerations();
  C_INT32 getCurrentGeneration();

  const std::vector< CVector < C_FLOAT64 > * >& getPopulation();
  const CVector< C_FLOAT64 >& getObjectiveValues();

  /**
  * This is the output method for any object. The default implementation
  * provided with CDataObject uses the ostream operator<< of the object
  * to print the object. To override this default behavior one needs to
  * re implement the virtual print function.
  * @param std::ostream * ostream
  */
  virtual void print(std::ostream * ostream) const;

  /**
  * Output stream operator
  * @param ostream & os
  * @param const COptProblem & A
  * @return ostream & os
  */
  friend std::ostream &operator<<(std::ostream &os, const COptPopulationMethod & o);

protected:
  /**
   * size of the population / swarm size
   */
  unsigned C_INT32 mPopulationSize;

  /**
   * number of generations / iteration limit
   */
  unsigned C_INT32 mGenerations;

  /**
   * Current Generation / iteration
   */
  unsigned C_INT32 mCurrentGeneration;

  /**
  * Handle to the process report item "Current Generation" / "Current Iteration"
  */
  size_t mhGenerations;

  /**
   * number of parameters
   */
  size_t mVariableSize;

  /**
   * for array of individuals w/ candidate values for the parameters
   */
  std::vector< CVector < C_FLOAT64 > * > mIndividuals;

  /**
   * array of values of objective function f/ individuals
   */
  CVector< C_FLOAT64 > mValues;

  /**
   * a pointer to the random number generator.
   */
  CRandomContext  mRandomContext;
};

#endif // COPASI_COptPopulationMethod_H
