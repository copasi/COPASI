// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include "utilities/CCopasiTask.h"
#include "utilities/CMatrix.h"
#include "utilities/CAnnotatedMatrix.h"
#include "utilities/CReadConfig.h"
#include "steadystate/CSteadyStateMethod.h"
#include "steadystate/CEigen.h"

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

  CArrayAnnotation * mpJacobianAnn;
  CArrayAnnotation * mpJacobianXAnn;

  /**
   * Whether the model is actually reducible and calculating
   * stability of the reduced steady states makes sense
   */
  bool mCalculateReducedSystem;

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

  CArrayAnnotation * mpEigenvaluesJacobianAnn;
  CArrayAnnotation * mpEigenvaluesJacobianXAnn;

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
   * @param const CCopasiContainer * pParent
   * @param const CCopasiTask::Type & type (default: steadyState)
   */
  CSteadyStateTask(const CCopasiContainer * pParent,
                   const CCopasiTask::Type & type = CCopasiTask::steadyState);
  /**
   * Copy constructor
   * @param const CSteadyStateTask & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CSteadyStateTask(const CSteadyStateTask & src,
                   const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  virtual ~CSteadyStateTask();

  /**
   * Create a method of the specified type to solve the task.
   * It is the duty of the caller to release the CCopasiMethod.
   * @param const CCopasiMethod::SubType & type
   * @return CCopasiMethod *
   */
  virtual CCopasiMethod * createMethod(const int & type) const;

  /**
   * Resizes result matrices and updates array annotations for a specific task.
   * This is used when we need to know about the data structures of a task result
   * without actually performing the task, e.g. when selecting objects for output.
   * For now we assume that this functionality is also performed when
   * initialize() is called.
   */
  virtual bool updateMatrices();

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
                          std::ostream * pOstream);

  /**
   * Process the task with or without initializing to the initial state.
   * @param const bool & useInitialValues
   * @return bool success
   */
  virtual bool process(const bool & useInitialValues);

  /**
   * Perform necessary cleanup procedures
   */
  virtual bool restore();

  /**
   * This is the output method for any object. The default implementation
   * provided with CCopasiObject uses the ostream operator<< of the object
   * to print the object.To override this default behavior one needs to
   * reimplement the virtual print function.
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const;

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
  const CArrayAnnotation * getJacobianAnnotated() const;

  /**
   * Retrieves a the jacobian of the steady state.
   * @return const CMatrix< C_FLOAT64 > jacobian
   */
  const CMatrix< C_FLOAT64 > & getJacobianReduced() const;
  const CArrayAnnotation * getJacobianXAnnotated() const;

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
