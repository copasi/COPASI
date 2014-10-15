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
 *  CSteadyStateProblem class.
 *  This class describes the steady state problem, i.e., it allows to specify
 *  for example initial conditions.
 *
 *  Created for COPASI by Stefan Hoops 2002
 */

#include <string>

#include "copasi.h"
#include "CSteadyStateProblem.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModel.h"

/**
 *  Default constructor.
 */
CSteadyStateProblem::CSteadyStateProblem(const CCopasiContainer * pParent):
  CCopasiProblem(CTaskEnum::steadyState, pParent)
  //mInitialState(),
  //mHasInitialState(false)
{
  addParameter("JacobianRequested", CCopasiParameter::BOOL, true);
  addParameter("StabilityAnalysisRequested", CCopasiParameter::BOOL, true);
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CSteadyStateProblem &" src
 */
CSteadyStateProblem::CSteadyStateProblem(const CSteadyStateProblem & src,
    const CCopasiContainer * pParent):
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
void CSteadyStateProblem::setJacobianRequested(bool & jacobianRequested)
{setValue("JacobianRequested", jacobianRequested);}

/**
 * Retrieve whether the jacobian is requested.
 * @return bool jacobianRequested
 */
bool CSteadyStateProblem::isJacobianRequested() const
{return * getValue("JacobianRequested").pBOOL;}

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
{return * getValue("StabilityAnalysisRequested").pBOOL;}

/**
 * Load a steadystate problem
 * @param "CReadConfig &" configBuffer
 */
void CSteadyStateProblem::load(CReadConfig & configBuffer,
                               CReadConfig::Mode C_UNUSED(mode))
{
  if (configBuffer.getVersion() < "4.0")
    {
      configBuffer.getVariable("RepStabilityAnalysis", "bool" ,
                               getValue("StabilityAnalysisRequested").pBOOL,
                               CReadConfig::LOOP);
      setValue("JacobianRequested",
               * getValue("StabilityAnalysisRequested").pBOOL);
    }
}
