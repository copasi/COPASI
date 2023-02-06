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

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CSteadyStateTask class.
 *
 * This class implements a steady state task which is comprised of a
 * of a problem and a method. Additionally calls to the reporting
 * methods are done when initialized.
 *
 * Created for COPASI by Stefan Hoops 2002
 */

#ifndef COPASI_CSteadyStateTask
#define COPASI_CSteadyStateTask

#include <iostream>

#include "copasi/core/CMatrix.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/core/CDataArray.h"
#include "copasi/utilities/CReadConfig.h"
#include "copasi/steadystate/CSteadyStateMethod.h"
#include "copasi/steadystate/CEigen.h"

class CSteadyStateProblem;
class CReportDefinitionVector;

class CSteadyStateTask : public CCopasiTask
{
  //Attributes
private:
  /**
   * A pointer to the found steady state.
   */
  CVector< C_FLOAT64 > mSteadyState;

  /**
   * The jacobian of the steady state.
   */
  CMatrix< C_FLOAT64 > mJacobian;

  /**
   * The jacobian of the steady state.
   */
  CMatrix< C_FLOAT64 > mJacobianReduced;

  CDataArray * mpJacobianAnn;
  CDataArray * mpJacobianXAnn;

  /**
   * The Eigenvalues of the Jacobian of the system
   */
  CEigen mEigenValues;

  /**
   * The Eigenvalues of the Jacobian of the reduced system
   */
  CEigen mEigenValuesX;

  /**
   * The Eigenvalues matrix of the Jacobian of the system
   */
  CMatrix<C_FLOAT64> mEigenvaluesMatrix;

  /**
   * The Eigenvalues matrix of the Jacobian of the reduced system
   */
  CMatrix<C_FLOAT64> mEigenvaluesXMatrix;

  CDataArray * mpEigenvaluesJacobianAnn;
  CDataArray * mpEigenvaluesJacobianXAnn;

  /**
   * The result of the steady state analysis.
   */
  CSteadyStateMethod::ReturnCode mResult;

  //Operations
private:
  /**
   * Default constructor
   */
  CSteadyStateTask();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Task & type (default: steadyState)
   */
  CSteadyStateTask(const CDataContainer * pParent,
                   const CTaskEnum::Task & type = CTaskEnum::Task::steadyState);
  /**
   * Copy constructor
   * @param const CSteadyStateTask & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CSteadyStateTask(const CSteadyStateTask & src,
                   const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CSteadyStateTask();

  /**
   * Resizes result matrices and updates array annotations for a specific task.
   * This is used when we need to know about the data structures of a task result
   * without actually performing the task, e.g. when selecting objects for output.
   * For now we assume that this functionality is also performed when
   * initialize() is called.
   */
  virtual bool updateMatrices() override;

  /**
   * Initialize the task. If an ostream is given this ostream is used
   * instead of the target specified in the report. This allows nested
   * tasks to share the same output device.
   * @param const OutputFlag & of
   * @param COutputHandler * pOutputHandler
   * @param std::ostream * pOstream (default: NULL)
   * @return bool success
   */
  virtual bool initialize(const OutputFlag & of,
                          COutputHandler * pOutputHandler,
                          std::ostream * pOstream) override;

  /**
   * Process the task with or without initializing to the initial state.
   * @param const bool & useInitialValues
   * @return bool success
   */
  virtual bool process(const bool & useInitialValues) override;

  /**
   * Perform necessary cleanup procedures
   */
  virtual bool restore(const bool & updateModel = true) override;

  /**
   * This is the output method for any object. The default implementation
   * provided with CDataObject uses the ostream operator<< of the object
   * to print the object.To override this default behavior one needs to
   * reimplement the virtual print function.
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const override;

#ifndef SWIG

  /**
   * Retrieve the list of valid methods
   * @return const CTaskEnum::Method * pValidMethods
   */
  virtual const CTaskEnum::Method * getValidMethods() const override;
#endif

  /**
   * Loads parameters for this solver with data coming from a
   * CReadConfig object. (CReadConfig object reads an input stream)
   * @param configbuffer reference to a CReadConfig object.
   */
  void load(CReadConfig & configBuffer);

  /**
   * Retrieves a pointer to steady state.
   * @return const CVectorCore< C_FLOAT64 > & steadyState
   */
  const CVectorCore< C_FLOAT64 > & getState() const;

  /**
   * Retrieves a the jacobian of the steady state.
   * @return const CMatrix< C_FLOAT64 > jacobian
   */
  const CMatrix< C_FLOAT64 > & getJacobian() const;
  const CDataArray * getJacobianAnnotated() const;

  /**
   * Retrieves a the jacobian of the steady state.
   * @return const CMatrix< C_FLOAT64 > jacobian
   */
  const CMatrix< C_FLOAT64 > & getJacobianReduced() const;
  const CDataArray * getJacobianXAnnotated() const;

  /**
   * Retrieves a the eigenvalues of the steady state.
   * @return const CEigen & eigenValues
   */
  const CEigen & getEigenValues() const;

  /**
   * Retrieves a the eigenvalues of the steady state.
   * @return const CEigen & eigenValues
   */
  const CEigen & getEigenValuesReduced() const;

  /**
   * Converts the eigenvalues vector to matrix
   * @param CEigen &eigenvalues
   * @return CMatrix<C_FLOAT64> &matrix
   */
//  CMatrix<C_FLOAT64> & createEigenvalueMatrix(CEigen &eigenvalues);

  const CSteadyStateMethod::ReturnCode & getResult() const {return mResult;}

  // Friend functions
  friend std::ostream &operator<<(std::ostream &os,
                                  const CSteadyStateTask &A);

private:
  /**
   * cleanup()
   */
  void cleanup();

  void initObjects();
};

#endif // COPASI_CSteadyStateTask
