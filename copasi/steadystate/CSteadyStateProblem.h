// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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
 *  CSteadyStateProblem class.
 *  This class describes the steady state problem, i.e., it allows to specify
 *  for example initial conditions.
 *
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CSteadyStateProblem
#define COPASI_CSteadyStateProblem

#include <string>

#include "copasi/utilities/CCopasiProblem.h"
#include "copasi/utilities/CReadConfig.h"

class CSteadyStateProblem: public CCopasiProblem
{
  // Attributes
private:
  /**
   *  The initial state, i.e., the starting conditions of the trajectroy.
   */
  //CState mInitialState;

  /**
   *  was a initial state set?
   */
  //bool mHasInitialState;

public:
  // Operations

  /**
   * Default constructor.
   * @param const CDataContainer * pParent (default: NULL)
   */
  CSteadyStateProblem(const CDataContainer * pParent = NO_PARENT);

  /**
   *  Copy constructor.
   *  @param "const CSteadyStateProblem &" src
   * @paramconst CDataContainer * pParent (default: NULL)
   */
  CSteadyStateProblem(const CSteadyStateProblem & src,
                      const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  virtual ~CSteadyStateProblem();

  /**
   * Do all neccessary initialization so that calls to caluclate will
   * be successful. This is called once from CCopasiTask::process()
   * @result bool succes
   */
  virtual bool initialize();

  /**
   * Set whether the jacobian is requested.
   * @param bool & jacobianRequested
   */
  void setJacobianRequested(const bool & jacobianRequested);

  /**
   * Retrieve whether the jacobian is requested.
   * @return bool jacobianRequested
   */
  bool isJacobianRequested() const;

  /**
   * Set whether stabilty analysis is requested.
   * @param bool & stabilityAnalysisRequested
   */
  void setStabilityAnalysisRequested(bool & stabilityAnalysisRequested);

  /**
   * Retrieve whether the stabilty analysis is requested.
   * @return bool stabilityAnalysisRequested
   */
  bool isStabilityAnalysisRequested() const;

  /**
   * Load a trajectory problem
   * @param "CReadConfig &" configBuffer
   * @param "CReadConfig::Mode mode (Default: CReadConfig::NEXT)
   */
  void load(CReadConfig & configBuffer,
            CReadConfig::Mode mode = CReadConfig::NEXT);
};

#endif // COPASI_CSteadyStateProblem
