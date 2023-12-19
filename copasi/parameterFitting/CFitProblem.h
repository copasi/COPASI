// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CFitProblem
#define COPASI_CFitProblem

#include "copasi/optimization/COptProblem.h"
#include <copasi/parameterFitting/CFitItem.h>
#include "copasi/core/CMatrix.h"

class CExperimentSet;
class CCrossValidationSet;
class CTrajectoryProblem;
class CState;
class CFitConstraint;
class CDataArray;
class CExperiment;
class CTimeSensTask;
class CTimeSensProblem;

template < class CMatrixType > class CMatrixInterface;

class CFitProblem : public COptProblem
{
public:
  // Operations
  /**
   * Default constructor
   * @param const CTaskEnum::Task & type (default: parameterFitting)
   * @param const CDataContainer * pParent (default: NULL)
   */
  CFitProblem(const CTaskEnum::Task & type = CTaskEnum::Task::parameterFitting,
              const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor.
   * @param const CFitProblem & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CFitProblem(const CFitProblem & src,
              const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CFitProblem();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren() override;

  /**
   * Set the call back of the problem
   * @param CProcessReport * pCallBack
   * @result bool success
   */
  virtual bool setCallBack(CProcessReportLevel callBack) override;

  /**
   * Do all necessary initialization so that calls to calculate will
   * be successful. This is called once from CCopasiTask::process()
   * @result bool success
   */
  virtual bool initialize() override;

  /**
   * Do the calculation based on CalculateVariables and fill
   * CalculateResults with the results.
   * @result bool continue
   */
  virtual bool calculate() override;

  /**
   * Do all necessary restore procedures so that the
   * model is in the same state as before
   * @param const bool & updateModel
   * @result bool success
   */
  virtual bool restore(const bool & updateModel) override;

  bool restore(const bool& updateModel, CExperiment* pExp);

  /**
   * Check whether all functional constraints are fulfilled.
   * @result bool fulfilled
   */
  virtual bool checkFunctionalConstraints() override;

  /**
   * This is the output method for any object. The default implementation
   * provided with CDataObject uses the ostream operator<< of the object
   * to print the object.To override this default behavior one needs to
   * reimplement the virtual print function.
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const override;

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CFitProblem & A
   * @return ostream & os
   */
  friend std::ostream &operator<<(std::ostream &os, const CFitProblem & o);

  /**
   * This is the output method for any result of a problem. The default implementation
   * provided with CCopasiProblem. Does only print "Not implemented." To override this
   * default behavior one needs to reimplement the virtual printResult function.
   * @param std::ostream * ostream
   */
  virtual void printResult(std::ostream * ostream) const override;

  /**
   * Fetch a new initial state from the model.
   */
  void updateInitialState();

  /**
   * Set residual required
   * @param const bool & required
   * @return bool success
   */
  bool setResidualsRequired(const bool & required);

  /**
   * Retrieve the vector of residuals
   * @return const CVector< C_FLOAT64 > & residuals
   */
  const CVector< C_FLOAT64 > & getResiduals() const;

  /**
   * calculate the FIM from the parameter estimation jacobian
   */
  void calcFIM(const CMatrix< C_FLOAT64 >& jacobian, CMatrix< C_FLOAT64 >& fim);

  /**
   * calculate the FIM from only a part of the parameter estimation jacobian
   * only columns from a to b-1 are used or excluded, depending on the exclude flag
   */
  void calcPartialFIM(const CMatrix< C_FLOAT64 >& jacobian, CMatrix< C_FLOAT64 >& fim, size_t a, size_t b, bool exclude = false);

  /**
   * calculate the Eigenvalues and -vectors for a matrix.
   * This is intended for the FIM, and we assume only real (and positive) eigenvalues
   */
  void calcEigen(const CMatrix< C_FLOAT64 >& fim, CMatrix< C_FLOAT64 >& eigenvalues, CMatrix< C_FLOAT64 >& eigenvectors);

  /**
   * calculate the inverse of a matrix and normalize it.
   * This is used for calculating the correlation Matric from the FIM,
   * and therefore we can assume a symmetric positive definite matrix
   * The SD of the parameters is also calculated from the diagonal of the covariance
   * if scale is true, the cov matrix will be scaled to unity diagonal elements
   */
  bool calcCov(const CMatrix< C_FLOAT64 >& fim, CMatrix< C_FLOAT64 >& corr, CVector< C_FLOAT64 >& sd, bool scale);

  /**
   * Calculate the statistics for the problem
   * @param const C_FLOAT64 & factor (Default: 1.0e-003)
   * @param const C_FLOAT64 & resolution (Default: 1.0e-009)
   */
  virtual bool calculateStatistics(const C_FLOAT64 & factor = 1.0e-003,
                                   const C_FLOAT64 & resolution = 1.0e-009) override;

  /**
   * Retrieve the root mean square of the objective value.
   * @return const C_FLOAT64 & RMS
   */
  const C_FLOAT64 & getRMS() const;

  /**
   * Retrieve the std. deviation of the objective value.
   * @return const C_FLOAT64 & stdDeviation
   */
  const C_FLOAT64 & getStdDeviation() const;

  /**
   * Retrieve the std. deviation  for each solution variable.
   * @return const CVector< C_FLOAT64 > & variableStdDeviations
   */
  const CVector< C_FLOAT64 > & getVariableStdDeviations() const;

  /**
   * Retrieve the Jacobian of the parameter estimation.
   */
  CDataArray & getParameterEstimationJacobian() const;

  /**
   * Retrieve the scaled Jacobian of the parameter estimation.
   * It is scaled by parameter values
   */
  CDataArray & getScaledParameterEstimationJacobian() const;

  /**
   * Retrieve the Fisher Information Matrix of the solution variables.
   * @return CArrayAnnotation & fisherInformationMatrix
   */
  CDataArray & getFisherInformation() const;

  /**
   * Retrieve the Eigenvalues of the Fisher Information Matrix of the solution variables.
   * @return CArrayAnnotation & fimEigenvalues
   */
  CDataArray & getFisherInformationEigenvalues() const;

  /**
   * Retrieve the Eigenvectors corresponding to the Eigenvalues of the Fisher Information Matrix of the solution variables.
   * @return CArrayAnnotation & fimEigenvectors
   */
  CDataArray & getFisherInformationEigenvectors() const;

  /**
   * Retrieve the scaled Fisher Information Matrix of the solution variables.
   * @return CArrayAnnotation & fisherInformationMatrix
   */
  CDataArray & getScaledFisherInformation() const;

  /**
   * Retrieve the Eigenvalues of the scaled Fisher Information Matrix of the solution variables.
   * @return CArrayAnnotation & fimEigenvalues
   */
  CDataArray & getScaledFisherInformationEigenvalues() const;

  /**
   * Retrieve the Eigenvectors corresponding to the Eigenvalues of the scaled Fisher Information Matrix of the solution variables.
   * @return CArrayAnnotation & fimEigenvectors
   */
  CDataArray & getScaledFisherInformationEigenvectors() const;

  /**
   * Retrieve the correlations of the solution variables.
   * @return CArrayAnnotation & variableCorrelations
   */
  CDataArray & getCorrelations() const;

  /**
   * Retrieve the experiment set.
   * @return const CExperimentSet & experiementSet
   */
  const CExperimentSet & getExperimentSet() const;

  /**
   * Retrieve the experiment set.
   * @return const CExperimentSet & experiementSet
   */
  CExperimentSet & getExperimentSet();

  /**
   * Retrieve the cross validation set.
   * @return const CCrossValidationSet & crossValidationSet
   */
  const CCrossValidationSet & getCrossValidationSet() const;

  /**
   * Retrieve the cross validation set.
   * @return const CCrossValidationSet & crossValidationSet
   */
  CCrossValidationSet & getCrossValidationSet();

  /**
   * Add a fit item to the problem.
   * @param const CCommonName & objectCN
   * @return CFitItem optItemAdded
   */
  CFitItem & addFitItem(const CCommonName & objectCN);

  /**
   * Add a fit constraint to the problem.
   * @param const CCommonName & objectCN
   * @return CFitConstraint optItemAdded
   */
  CFitConstraint & addFitConstraint(const CCommonName & objectCN);

  /**
   * Set the solution.
   * @param const C_FLOAT64 & value
   * @param const CVector< C_FLOAT64 > & variables
   * @param const bool & algorithmOrder (default: false)
   * @return bool continue;
   */
  virtual bool setSolution(const C_FLOAT64 & value,
                           const CVector< C_FLOAT64 > & variables,
                           const bool & algorithmOrder = false) override;

  /**
   * Retrieve the result for the cross validation solution
   */
  const C_FLOAT64 & getCrossValidationSolutionValue() const;

  /**
   * Retrieve the root mean square of the cross validation solution
   * @return const C_FLOAT64 & RMS
   */
  const C_FLOAT64 & getCrossValidationRMS() const;

  /**
   * Retrieve the standard deviation of the cross validation solution
   * @return const C_FLOAT64 & RMS
   */
  const C_FLOAT64 & getCrossValidationSD() const;

  /**
   * Fix files written with Version 4.10.55, which wrote the square root of user defined weights for the
   * parameter fitting task
   */
  void fixBuild55();

  /**
   * Sets the 'Create Parameter Sets' parameter. When set it will create new model parameter
   * sets for each experiment after a run.
   */
  void setCreateParameterSets(const bool & create);

  /**
   * @return the value of the 'Create Parameter Sets' parameter that controls whether parameter
   * sets should be created automatically.
   */
  const bool & getCreateParameterSets() const;

  void setUseTimeSens(bool value);

  const bool& getUseTimeSens() const;

  void createParameterSets();

  const CMatrix<C_FLOAT64>& getTimeSensJac() const;
  CMatrix<C_FLOAT64>& getTimeSensJac();

protected:
  /**
   * Signal that the math container has changed
   */
  virtual void signalMathContainerChanged() override;

  /**
   * Do all necessary restore procedures for the container
   * is in the same state as before or the new state if update is true.
   * @param const bool & update
   */
  virtual void updateContainer(const bool & update) override;

  /**
   * Create a parameter set with the given name and the current model values
   *
   */
  void createParameterSet(const std::string & Name);

private:
  /**
   * Allocates all group parameters and assures that they are
   * properly initialized.
   */
  void initializeParameter();

  virtual bool createObjectiveFunction();

  /**
   * Initialize objects
   */
  void initObjects();

  /**
   * Do the calculation for the cross validation based on the solution variables
   * and determine whether to continue parameter fitting
   * @result bool continue
   */
  bool calculateCrossValidation();

private:
  // Attributes
  /**
   * A pointer to the value of the CCopasiParameter holding the Steady-State CN
   */
  std::string * mpParmSteadyStateCN;

  /**
   * A pointer to the value of the CCopasiParameter holding the Time Course CN
   */
  std::string * mpParmTimeCourseCN;

  /**
   * The experiment set to which the model is fitted.
   */
  CExperimentSet * mpExperimentSet;

  /**
   * Pointer to CSteadyStateTask.  To be used in calculate() to select between
   * trajectory and steady state method
   */
  CSteadyStateTask * mpSteadyState;

  /**
   * Pointer to CTrajectory.  To be used in calculate() to select between
   * trajectory and steady state method
   */
  CTrajectoryTask * mpTrajectory;

  /**
   * Pointer to the values which need to be updated for each experiment.
   */
  CMatrix< C_FLOAT64 * > mExperimentValues;

  /**
   * A vector of refresh methods which contains the sequence of refresh methods
   * to update the initial values for each experiment.
   * */
  CVector< CCore::CUpdateSequence > mExperimentInitialUpdates;

  /**
   * Matrix of constraints for each experiment.
   */
  CMatrix< CFitConstraint * > mExperimentConstraints;

  /**
   * A vector of refresh methods which contains the sequence of refresh methods
   * to update the constraint values for each experiment.
   * */
  CVector< CCore::CUpdateSequence > mExperimentConstraintUpdates;

  /**
   * The simulation values for the experiments.
   */
  CVector< C_FLOAT64 > mExperimentDependentValues;

  /**
   * The experiment set to which the model is fitted.
   */
  CCrossValidationSet * mpCrossValidationSet;

  /**
   * Matrix of update methods for items for each cross validation.
   */
  CMatrix< C_FLOAT64 * > mCrossValidationValues;

  /**
   * A vector of refresh methods which contains the sequence of refresh methods
   * to update the initial values for each cross validation.
   * */
  CVector< CCore::CUpdateSequence > mCrossValidationInitialUpdates;

  /**
   * Matrix of constraints for each experiment.
   */
  CMatrix< CFitConstraint * > mCrossValidationConstraints;

  /**
   * A vector of refresh methods which contains the sequence of refresh methods
   * to update the constraint values for each cross validation.
   * */
  CVector< CCore::CUpdateSequence > mCrossValidationConstraintUpdates;

  /**
   * The simulation values for the experiments.
   */
  CVector< C_FLOAT64 > mCrossValidationDependentValues;

  /**
   * The objective value of the cross validation set.
   */
  C_FLOAT64 mCrossValidationSolutionValue;

  /**
   * The RMS of the cross validation set.
   */
  C_FLOAT64 mCrossValidationRMS;

  /**
   * The standard deviation of the cross validation set.
   */
  C_FLOAT64 mCrossValidationSD;

  /**
   * The objective value of the cross validation used to determine when to stop
   * parameter estimation due to overfitting
   */
  C_FLOAT64 mCrossValidationObjective;

  /**
   * A counter to determine whether the threshold is reached.
   */
  unsigned C_INT32 mThresholdCounter;

  /**
   * The initial state of the model prior to any modification
   */
  CVector< C_FLOAT64 > mCompleteInitialState;

  /**
   * A pointer to the time of the container
   */
  C_FLOAT64 * mpInitialStateTime;

  /**
   * Matrix of the residuals.
   */
  CVector< C_FLOAT64 > mResiduals;

  /**
   * The root mean square of the solution
   */
  C_FLOAT64 mRMS;

  /**
   * The standard deviation of the solution
   */
  C_FLOAT64 mSD;

  /**
   * The vector of standard deviations of the parameters
   */
  CVector< C_FLOAT64 > mParameterSD;

  /**
   * the Jacobian of tha parameter estimation,
   *i.e. the derivatives of the residuals with respect to the parameters
   */
  CMatrix< C_FLOAT64 > mDeltaResidualDeltaParameter;
  CMatrixInterface< CMatrix< C_FLOAT64 > > * mpDeltaResidualDeltaParameterInterface;
  CDataArray * mpDeltaResidualDeltaParameterMatrix;

  /**
   * the scaled Jacobian of tha parameter estimation,
   * i.e. the derivatives of the residuals with respect to the parameters,
   * scaled by parameter value
   */
  CMatrix< C_FLOAT64 > mDeltaResidualDeltaParameterScaled;
  CMatrixInterface< CMatrix< C_FLOAT64 > > * mpDeltaResidualDeltaParameterScaledInterface;
  CDataArray * mpDeltaResidualDeltaParameterScaledMatrix;

  /**
   * The Fisher information or parameter correlation matrix
   */
  CMatrix< C_FLOAT64 > mFisher;
  CMatrixInterface< CMatrix< C_FLOAT64 > > * mpFisherMatrixInterface;
  CDataArray * mpFisherMatrix;

  /**
   * The Fisher information Matrix Eigenvalues and corresponding Eigenvectors
   */
  CMatrix< C_FLOAT64 > mFisherEigenvalues;
  CMatrixInterface< CMatrix< C_FLOAT64 > > * mpFisherEigenvaluesMatrixInterface;
  CDataArray * mpFisherEigenvaluesMatrix;

  CMatrix< C_FLOAT64 > mFisherEigenvectors;
  CMatrixInterface< CMatrix< C_FLOAT64 > > * mpFisherEigenvectorsMatrixInterface;
  CDataArray * mpFisherEigenvectorsMatrix;

  /**
   * The Fisher information or parameter correlation matrix scaled to parameter values
   */
  CMatrix< C_FLOAT64 > mFisherScaled;
  CMatrixInterface< CMatrix< C_FLOAT64 > > * mpFisherScaledMatrixInterface;
  CDataArray * mpFisherScaledMatrix;

  /**
   * The scaled Fisher information Matrix Eigenvalues and corresponding Eigenvectors
   */
  CMatrix< C_FLOAT64 > mFisherScaledEigenvalues;
  CMatrixInterface< CMatrix< C_FLOAT64 > > * mpFisherScaledEigenvaluesMatrixInterface;
  CDataArray * mpFisherScaledEigenvaluesMatrix;

  CMatrix< C_FLOAT64 > mFisherScaledEigenvectors;
  CMatrixInterface< CMatrix< C_FLOAT64 > > * mpFisherScaledEigenvectorsMatrixInterface;
  CDataArray * mpFisherScaledEigenvectorsMatrix;

  /**
   * The  parameter correlation matrix
   */
  CMatrix< C_FLOAT64 > mCorrelation;
  CMatrixInterface< CMatrix< C_FLOAT64 > > * mpCorrelationMatrixInterface;
  CDataArray * mpCorrelationMatrix;

  /**
   * A pointer to the value of the CCopasiParameter holding Create Parameter Sets
   */
  bool * mpCreateParameterSets;

  /** A flag indicating whether or not to use time sens task */
  bool* mpUseTimeSens;

  CTimeSensTask* mpTimeSens;

  CMatrix< C_FLOAT64 > mJacTimeSens;

  std::string* mpParmTimeSensCN;
};

#endif  // COPASI_CFitProblem
