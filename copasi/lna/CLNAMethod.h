// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CLNAMethod_H__
#define COPASI_CLNAMethod_H__

#include <vector>

#include "copasi/core/CMatrix.h"
#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/core/CDataArray.h"
#include "copasi/steadystate/CSteadyStateMethod.h"

#define LNA_OK 0
#define LNA_NOT_OK 1

class CModel;

class CLNAMethod: public CCopasiMethod
{
public:
  enum EVStatus
  {
    allNeg = 0,
    nonNegEigenvaluesExist
  };

private:
  /**
   * LNA Matrices
   */
  CMatrix<C_FLOAT64> mBMatrixReduced;
  CDataArray* mBMatrixReducedAnn;

  CMatrix<C_FLOAT64> mCovarianceMatrixReduced;
  CDataArray* mCovarianceMatrixReducedAnn;

  CMatrix<C_FLOAT64> mCovarianceMatrix;
  CDataArray* mCovarianceMatrixAnn;

  // Jacobian matrix of the reduced system
  CMatrix<C_FLOAT64> mJacobianReduced;

  // Link matrix that links the dependent and the reduced system
  CMatrix<C_FLOAT64> mL;

  C_FLOAT64 mSteadyStateResolution;

  CSteadyStateMethod::ReturnCode mSSStatus;

  CLNAMethod::EVStatus mEVStatus;

  void initObjects();

private:
  /**
   * Default constructor.
   */
  CLNAMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: linearNoiseApproximation)
   * @param const CTaskEnum::Task & taskType (default: lna)
   */
  CLNAMethod(const CDataContainer * pParent,
             const CTaskEnum::Method & methodType = CTaskEnum::Method::linearNoiseApproximation,
             const CTaskEnum::Task & taskType = CTaskEnum::Task::lna);

  /**
   * Copy constructor
   * @param const CLNAMethod & src
   * @param const CDataContainer * pParent (Default: NULL)
   */
  CLNAMethod(const CLNAMethod & src,
             const CDataContainer * pParent);

  /**
   * Deconstructor
   */
  virtual ~CLNAMethod();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  const CMatrix<C_FLOAT64> & getBMatrixReduced() const
  {return mBMatrixReduced;}

  const CDataArray* getBMatrixReducedAnn() const
  {return mBMatrixReducedAnn;}

  const CMatrix<C_FLOAT64> & getCovarianceMatrix() const
  {return mCovarianceMatrix;}

  const CDataArray* getCovarianceMatrixAnn() const
  {return mCovarianceMatrixAnn;}

  const CMatrix<C_FLOAT64> & getCovarianceMatrixReduced() const
  {return mCovarianceMatrixReduced;}

  const CDataArray* getCovarianceMatrixReducedAnn() const
  {return mCovarianceMatrixReducedAnn;}

  // remove the following, or change scaled versions to
  // fano factors, coefficient of variations etc.
  const CDataArray* getScaledBMatrixReducedAnn() const
  {return mBMatrixReducedAnn;}

  const CDataArray* getUnscaledBMatrixReducedAnn() const
  {return mBMatrixReducedAnn;}

  const CDataArray* getScaledCovarianceMatrixAnn() const
  {return mCovarianceMatrixAnn;}

  const CDataArray* getScaledCovarianceMatrixReducedAnn() const
  {return mCovarianceMatrixReducedAnn;}

  const CDataArray* getUnscaledCovarianceMatrixAnn() const
  {return mCovarianceMatrixAnn;}

  const CDataArray* getUnscaledCovarianceMatrixReducedAnn() const
  {return mCovarianceMatrixReducedAnn;}

  int calculateCovarianceMatrixReduced();

  void calculateCovarianceMatrixFull();

  /**
   * Resizes all result matrices and updates the corresponding
   * array annotations.
   * This needs to be called before output initialization (in case
   * the output references parts of the matrix) from the task
   * initialization, but it also needs to be called before
   * selecting elements of the matrices in the object selection
   * dialog.
   * The model needs to be set before calling this.
   */
  virtual void resizeAllMatrices();

  /**
   * the LNA entry point
   */
  int CalculateLNA();

  /**
   *
   */
  virtual bool process();

  /**
   * Read some parameters from configuration file
   */
  C_INT32 load(CReadConfig & configBuffer);

  void setSteadyStateStatus(CSteadyStateMethod::ReturnCode SSStatus);

  void setEigenValueStatus(CLNAMethod::EVStatus status);

  const CSteadyStateMethod::ReturnCode & getSteadyStateStatus() const
  {return mSSStatus;}

  const CLNAMethod::EVStatus & getEigenValueStatus() const
  {return mEVStatus;}

  void setSteadyStateResolution(C_FLOAT64 factor);

  /**
  * Check if the method is suitable for this problem
  * @return bool suitability of the method
  */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

private:
  /**
   * Intialize the method parameter
   */
  void initializeParameter();
};
#endif // COPASI_CLNAMethod_H__
