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
 *  Created for COPASI by Stefan Hoops 2002
 */

#include <string>

#include "copasi/copasi.h"
#include "CSteadyStateProblem.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"

/**
 *  Default constructor.
 */
CSteadyStateProblem::CSteadyStateProblem(const CDataContainer * pParent):
  CCopasiProblem(CTaskEnum::Task::steadyState, pParent)
  //mInitialState(),
  //mHasInitialState(false)
{
  assertParameter("JacobianRequested", CCopasiParameter::Type::BOOL, true);
  assertParameter("StabilityAnalysisRequested", CCopasiParameter::Type::BOOL, true);
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CSteadyStateProblem &" src
 */
CSteadyStateProblem::CSteadyStateProblem(const CSteadyStateProblem & src,
    const CDataContainer * pParent):
  CCopasiProblem(src, pParent)
  //mInitialState(src.mInitialState),
  //mHasInitialState(src.mHasInitialState)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CSteadyStateProblem::~CSteadyStateProblem()
{DESTRUCTOR_TRACE;}

bool CSteadyStateProblem::initialize()
{
  if (!mpContainer) return false;

  return true;
}

/**
 * Set whether the jacobian is requested.
 * @param bool * jacobianRequested
 */
void CSteadyStateProblem::setJacobianRequested(const bool & jacobianRequested)
{setValue("JacobianRequested", jacobianRequested);}

/**
 * Retrieve whether the jacobian is requested.
 * @return bool jacobianRequested
 */
bool CSteadyStateProblem::isJacobianRequested() const
{return getValue< bool >("JacobianRequested");}

/**
 * Set whether stability analysis is requested.
 * @param bool * stabilityAnalysisRequested
 */
void CSteadyStateProblem::setStabilityAnalysisRequested(bool & stabilityAnalysisRequested)
{setValue("StabilityAnalysisRequested", stabilityAnalysisRequested);}

/**
 * Retrieve whether the stability analysis is requested.
 * @return bool stabilityAnalysisRequested
 */
bool CSteadyStateProblem::isStabilityAnalysisRequested() const
{return getValue< bool >("StabilityAnalysisRequested");}

/**
 * Load a steadystate problem
 * @param "CReadConfig &" configBuffer
 */
void CSteadyStateProblem::load(CReadConfig & configBuffer,
                               CReadConfig::Mode C_UNUSED(mode))
{
  if (configBuffer.getVersion() < "4.0")
    {
      configBuffer.getVariable("RepStabilityAnalysis", "bool",
                               &getValue< bool >("StabilityAnalysisRequested"),
                               CReadConfig::LOOP);
      setValue("JacobianRequested", getValue< bool >("StabilityAnalysisRequested"));
    }
}
