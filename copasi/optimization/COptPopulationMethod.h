// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#ifndef COPASI_COptPopulationMethod_H
#define COPASI_COptPopulationMethod_H

#include <copasi/optimization/COptMethod.h>
#include <copasi/utilities/CVector.h>

class CRandom;

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
  * @param const CCopasiContainer * pParent
  * @param const CTaskEnum::Method & methodType
  * @param const CTaskEnum::Task & taskType (default: optimization)
  */
  COptPopulationMethod(const CCopasiContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType = CTaskEnum::optimization);

  /**
  * Copy constructor
  * @param const COptMethod & src
  * @param const CCopasiContainer * pParent (default: NULL)
  */
  COptPopulationMethod(const COptPopulationMethod & src,
    const CCopasiContainer * pParent);

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
  CRandom * mpRandom;


};

#endif // COPASI_COptPopulationMethod_H
