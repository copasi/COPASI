/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodCoranaWalk.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: mendes $
   $Date: 2012/06/04 14:10:44 $
   End CVS Header */

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * COptMethodCoranaWalk class
 */

#ifndef COPASI_COptMethodCoranaWalk
#define COPASI_COptMethodCoranaWalk

#include <vector>
#include "utilities/CMatrix.h"
#include "optimization/COptMethod.h"

class CRandom;

class COptMethodCoranaWalk : public COptMethod
{
  friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

  // Operations
public:
  /**
   * Copy Constructor
   * @param const COptMethodCoranaWalk & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  COptMethodCoranaWalk(const COptMethodCoranaWalk & src,
                       const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  virtual ~COptMethodCoranaWalk();

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
  COptMethodCoranaWalk(const CCopasiContainer * pParent = NULL);

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
   * Evaluate the objective function
   * @return bool continue
   */
  const C_FLOAT64 & evaluate();

  // Attributes
private:

  /**
   * The current temperature
   */
  C_FLOAT64 mTemperature;

  /**
   * Handle to the process report item "iterations"
   */
  size_t mhIterations;

  /**
   * number of iterations
   */
  unsigned C_INT32 mIterations;

  /**
   * The current iteration
   */
  unsigned C_INT32 mCurrentIteration;

  /**
   * a pointer to the randomnumber generator.
   */
  CRandom * mpRandom;

  /**
   * number of parameters
   */
  size_t mVariableSize;

  /**
   * The best value found so far
   */
  C_FLOAT64 mBestValue;

  /**
   * The result of a function evaluation
   */
  C_FLOAT64 mEvaluationValue;

  /**
   * Flag indicating whether the computation shall continue
   */
  bool mContinue;

  /**
   * The current solution guess
   */
  CVector< C_FLOAT64 > mCurrent;

  /**
   * The result of a function evaluation for mCurrent
   */
  C_FLOAT64 mCurrentValue;

  /**
   * The step taken
   */
  CVector< C_FLOAT64 > mStep;

  /**
   * The number of accepted steps
   */
  CVector< size_t > mAccepted;
};

#endif  // COPASI_COptMethodCoranaWalk
