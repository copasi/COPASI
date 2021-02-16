// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
  * COptMethodNL2SOL class
  */

#ifndef COPASI_COptMethodNL2SOL
#define COPASI_COptMethodNL2SOL

#include "copasi/optimization/COptMethod.h"
#include "copasi/core/CMatrix.h"

#include "CNL2SOL.h"

class FNL2SOL;

class COptMethodNL2SOL: public COptMethod
{
  // Operations
public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: TruncatedNewton)
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  COptMethodNL2SOL(const CDataContainer * pParent,
                   const CTaskEnum::Method & methodType = CTaskEnum::Method::NL2SOL,
                   const CTaskEnum::Task & taskType = CTaskEnum::Task::optimization);

  /**
   * Copy Constructor
   * @param const COptMethodNL2SOL & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  COptMethodNL2SOL(const COptMethodNL2SOL & src,
                   const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~COptMethodNL2SOL();

  /**
   * Execute the optimization algorithm calling simulation routine
   * when needed. It is noted that this procedure can give feedback
   * of its progress by the callback function set with SetCallback.
   * @ return success;
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


private:
  /**
   * Default Constructor
   */
  COptMethodNL2SOL();

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
   * Size of double work array
   */
  integer lv;

  /**
   * double work array
   */
  doublereal *v;

  /**
   * size of work array
   */
  integer liv;

  /**
   * integer work array
   */
  integer *iv;

  /**
   * The max number of iterations
   */
  unsigned C_INT32 mIterations;

  /**
   * number of parameters
   */
  C_INT mVariableSize;

  /**
   * parameter bounds
   */
  doublereal *bounds;

  /**
   * Indicate whether we have access to the residuals, i.e., it is a
   * fitting problem we are working on.
   */
  bool mHaveResiduals;

  /**
   * The number of residuals.
   */
  C_INT nResiduals;

  /**
   * The transpose jacobian of the residuals.
   */
  CMatrix< C_FLOAT64 > mResidualJacobianT;

  /**
   * array of candidate parameter values
   */
  CVector< C_FLOAT64 > mCurrent;

  /**
   * The last individual
   */
  CVector< C_FLOAT64 > mBest;

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
   * Evaluation function for the residuals
   */
  C_INT calcr(integer *n, integer *p, doublereal *x, integer *nf, doublereal *resid,
              integer *uiparm, doublereal *urparm, U_fp ufparm);

  /**
   * Evaluate the objective function
   * @return bool continue
   */
  const C_FLOAT64 & evaluate();

  /**
   * Functor pointing to the calculate residuals method.
   */
  FNL2SOL * fCalcr;

  /**
   * CNL2SOL function.
   */
  CNL2SOL * mpCNL2SOL;
};

#endif  // COPASI_COptMethodNL2SOL
