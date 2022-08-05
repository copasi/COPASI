// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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
 *  CSteadyStateMethod class.
 *  This class describes the interface to all steady state methods.
 *  The variaous method like Netwon have to be derived from
 *  this class.
 *
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CSteadyStateMethod
#define COPASI_CSteadyStateMethod

#include <string>
#include <sstream>

#include "copasi/core/CMatrix.h"
#include "copasi/core/CVector.h"
#include "copasi/utilities/CCopasiMethod.h"

class CSteadyStateProblem;
class CSteadyStateTask;
class CEigen;
class CProcessReportLevel;

class CSteadyStateMethod : public CCopasiMethod
{
public:
  enum ReturnCode
  {
    notFound = 0,
    found,
    foundEquilibrium,
    foundNegative
  };

protected:
  /**
   *  A pointer to the  problem.
   */
  const CSteadyStateProblem * mpProblem;

  /**
   *  A pointer to the task.
   */
  CSteadyStateTask * mpParentTask;

  /**
   * A pointer to the steady state
   */
  CVectorCore< C_FLOAT64 > mSteadyState;

  /**
   * The state from where the method started
   */
  CVector< C_FLOAT64 > mStartState;

  /**
   * The jacobian of the steadystate
   */
  CMatrix< C_FLOAT64 > * mpJacobian;

  /**
   * The concentration rate that is considered zero
   */
  C_FLOAT64* mpSSResolution;

  /**
   * The factor for numerical derivation
   */
  C_FLOAT64* mpDerivationFactor;

  /**
   * The resolution of the variable of numerical derivation
   */
  C_FLOAT64* mpDerivationResolution;

  std::ostringstream mMethodLog;

  CVectorCore< C_FLOAT64 > mContainerState;
  CVectorCore< C_FLOAT64 > mContainerStateReduced;

  C_FLOAT64 * mpContainerStateTime;
  CVector< C_FLOAT64 * > mCompartmentVolumes;

  CVector< C_FLOAT64 > mAtol;

  // Operations
private:
  /**
   * Default constructor.
   */
  CSteadyStateMethod();

protected:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType
   * @param const CTaskEnum::Task & taskType (default: steadyState)
   */
  CSteadyStateMethod(const CDataContainer * pParent,
                     const CTaskEnum::Method & methodType,
                     const CTaskEnum::Task & taskType = CTaskEnum::Task::steadyState);
  /**
   * Specific constructor.
   * @param CTaskEnum::Method subType
   * @param const CDataContainer * pParent (default: NULL)
   */
  CSteadyStateMethod(CTaskEnum::Method subType,
                     const CDataContainer * pParent = NO_PARENT);

  /**
   * initialize parameters and handle parameters of old COPASI files
   */
  void initializeParameter();

public:
  /**
   * Copy constructor.
   * @param "const CSteadyStateMethod &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CSteadyStateMethod(const CSteadyStateMethod & src,
                     const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CSteadyStateMethod();

  bool elevateChildren();

  /**
   * This instructs the method to calculate a the steady state
   * starting with the initialState given.
   * The steady state is returned in the object pointed to by steadyState.
   * @param CVectorCore< C_FLOAT64 > & State
   * @param CMatrix< C_FLOAT64 > & jacobianX
   * @param CProcessReport * handler
   * @return CSteadyStateMethod::ReturnCode returnCode
   */
  CSteadyStateMethod::ReturnCode process(CVectorCore< C_FLOAT64 > & State,
                                         CMatrix< C_FLOAT64 > & jacobianX,
                                         CProcessReportLevel handler);

  /**
   * Check if the method is suitable for this problem
   * @return bool suitability of the method
   */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

  /**
   * Initialize the method must be called before process
   * @param const CSteadyStateProblem * pProblem
   * @return bool success
   */
  virtual bool initialize(const CSteadyStateProblem * pProblem);

  /**
   * calls the CModel methods to calculate the jacobians (at the steady state).
   * This trivial method is implemented in the method
   * because it may need to know about some method parameters
   */
  void doJacobian(CMatrix< C_FLOAT64 > & jacobian,
                  CMatrix< C_FLOAT64 > & jacobianX);

  /**
   * returns the resolution for stability analysis
   */
  C_FLOAT64 getStabilityResolution();

  std::string getMethodLog() const;

protected:

  /**
   * This instructs the method to calculate a the steady state
   * starting with the initialState given.
   * The steady state is returned in the object pointed to by steadyState.
   * @return CSteadyStateMethod::ReturnCode returnCode
   */
  virtual CSteadyStateMethod::ReturnCode
  processInternal();

  /**
   * This function has to be called at the return of any implementation
   * of the protected function process()
   * @return CSteadyStateMethod::ReturnCode returnCode
   */
  virtual CSteadyStateMethod::ReturnCode
  returnProcess(bool steadyStateFound);

  /**
   * Check whether the steady state is chemical equilibrium
   * @param const C_FLOAT64 & resolution
   * @retrun bool isEquilibrium
   */
  bool isEquilibrium(const C_FLOAT64 & resolution) const;

protected:
  /**
   * Check whether all values make physically sence, i.e.,
   * volumes and particle number are positive
   * @return bool allPositive
   */
  bool allPositive();

  void calculateJacobian(const C_FLOAT64 & oldMaxRate, const bool & reduced);
};

#include "CNewtonMethod.h"

#endif // COPASI_CSteadyStateMethod
