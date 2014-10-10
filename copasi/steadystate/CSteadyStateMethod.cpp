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
 *  CSteadyStateMethod class.
 *  This class describes the interface to all steady state methods.
 *  The various method like Newton have to be derived from
 *  this class.
 *
 *  Created for COPASI by Stefan Hoops 2002
 */

#include "copasi.h"

#include "utilities/CCopasiVector.h"
#include "CSteadyStateMethod.h"
#include "CSteadyStateProblem.h"
#include "CSteadyStateTask.h"
#include "CEigen.h"

#include "math/CMathContainer.h"
#include "model/CModel.h"

CSteadyStateMethod *
CSteadyStateMethod::createMethod(CCopasiMethod::SubType subType)
{
  CSteadyStateMethod * pMethod = NULL;

  switch (subType)
    {
      case unset:
      case Newton:
        pMethod = new CNewtonMethod();
        break;

      default:
        fatalError();
    }

  return pMethod;
}

/**
 *  Default constructor.
 */
CSteadyStateMethod::CSteadyStateMethod(CCopasiMethod::SubType subType,
                                       const CCopasiContainer * pParent):
  CCopasiMethod(CCopasiTask::steadyState, subType, pParent),
  mpProblem(NULL),
  mContainerState(),
  mContainerStateReduced(),
  mpContainerStateTime(NULL)
{
  initializeParameter();
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CSteadyStateMethod &" src
 */
CSteadyStateMethod::CSteadyStateMethod(const CSteadyStateMethod & src,
                                       const CCopasiContainer * pParent):
  CCopasiMethod(src, pParent),
  mpProblem(src.mpProblem),
  mContainerState(),
  mContainerStateReduced(),
  mpContainerStateTime(NULL)
{
  initializeParameter();
  CONSTRUCTOR_TRACE;
}

/**
 *  Destructor.
 */
CSteadyStateMethod::~CSteadyStateMethod()
{DESTRUCTOR_TRACE;}

void CSteadyStateMethod::initializeParameter()
{
  CCopasiParameter *pParm;

  assertParameter("Resolution", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-009);
  mpSSResolution = (C_FLOAT64*)getValue("Resolution").pUDOUBLE;
  mpDerivationResolution = (C_FLOAT64*)getValue("Resolution").pUDOUBLE;

  assertParameter("Derivation Factor", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-003);
  mpDerivationFactor = (C_FLOAT64*)getValue("Derivation Factor").pUDOUBLE;

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("Newton.DerivationFactor")) != NULL)
    {
      setValue("Derivation Factor", *pParm->getValue().pUDOUBLE);
      removeParameter("Newton.DerivationFactor");
    }

  if ((pParm = getParameter("Newton.Resolution")) != NULL)
    {
      setValue("Resolution", *pParm->getValue().pUDOUBLE);
      removeParameter("Newton.Resolution");
    }
}

bool CSteadyStateMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

/**
 * This instructs the method to calculate a the steady state
 * starting with the initialState given.
 * The steady state is returned in the object pointed to by steadyState.
 * @param CState * steadyState
 * @param const CState * initialState
 * @param C_FLOAT64 * jacobian
 * @param CEigen * eigenValues
 * @return CSteadyStateMethod::ReturnCode returnCode
 */
CSteadyStateMethod::ReturnCode
CSteadyStateMethod::process(CVectorCore< C_FLOAT64 > & State,
                            CMatrix< C_FLOAT64 > & jacobianX,
                            CProcessReport * handler)
{
  mpParentTask = dynamic_cast<CSteadyStateTask *>(getObjectParent());
  assert(mpParentTask);

  mSteadyState.initialize(State);
  mpJacobianX = & jacobianX;
  mpCallBack = handler;

  return processInternal();
}

/**
 * This function has to be called at the return of any implementation
 * of the protected function process
 * @param bool success
 * @param const C_FLOAT64 & factor
 * @param const C_FLOAT64 & resolution
 * @return CSteadyStateMethod::ReturnCode returnCode
 */
CSteadyStateMethod::ReturnCode
CSteadyStateMethod::returnProcess(bool steadyStateFound)
{
  if (!steadyStateFound)
    return CSteadyStateMethod::notFound;

  if (!allPositive())
    return CSteadyStateMethod::foundNegative;

  if (isEquilibrium(*mpSSResolution))
    return CSteadyStateMethod::foundEquilibrium;

  return CSteadyStateMethod::found;
}

/**
 * This instructs the method to calculate a the steady state
 * @return CSteadyStateMethod::ReturnCode returnCode
 */
CSteadyStateMethod::ReturnCode
CSteadyStateMethod::processInternal()
{return CSteadyStateMethod::notFound;}

bool CSteadyStateMethod::isEquilibrium(const C_FLOAT64 & resolution) const
{
  const CMathReaction * pReaction = mpContainer->getReactions().array();
  const CMathReaction * pReactionEnd = pReaction + mpContainer->getReactions().size();

  for (; pReaction != pReactionEnd; ++pReaction)
    {
      // We are checking the amount flux whether we have an equilibrium.
      // TODO CRITICAL Do we need to scale with the compartment size?
      if (* (C_FLOAT64 *) pReaction->getFluxObject()->getValuePointer() > resolution)
        {
          return false;
        }
    }

  return true;
}

bool CSteadyStateMethod::allPositive()
{
  mpContainer->updateSimulatedValues(true);

  const C_FLOAT64 * pValue = mContainerState.array();
  const C_FLOAT64 * pValueEnd = mpContainer->getRate(false).array();
  const CMathObject * pValueObject = mpContainer->getMathObject(pValue);

  // We need to check that all metabolites have positive particle numbers
  // with respect to the given resolution.
  C_FLOAT64 ParticleResolution = *mpDerivationResolution * mpContainer->getModel().getQuantity2NumberFactor();

  for (; pValue != pValueEnd; ++pValue, ++pValueObject)
    {
      switch (pValueObject->getEntityType())
        {
          case CMath::Compartment:

            if (*pValue < - *mpDerivationResolution)
              {
                return false;
              }

            break;

          case CMath::Species:

            if (*pValue < - ParticleResolution)
              {
                return false;
              }

            break;

            // No restrictions on other values
          default:
            break;
        }
    }

  return true;
}

//virtual
bool CSteadyStateMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const CSteadyStateProblem * pP = dynamic_cast<const CSteadyStateProblem *>(pProblem);

  if (!pP)
    {
      //not a TrajectoryProblem
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Problem is not a steady state problem.");
      return false;
    }

  return true;
}

bool CSteadyStateMethod::initialize(const CSteadyStateProblem * pProblem)
{
  mpProblem = pProblem;

  mContainerState.initialize(mpContainer->getState(false));
  mContainerStateReduced.initialize(mpContainer->getState(true));
  mpContainerStateTime = mContainerState.array() + mpContainer->getTimeIndex();

  return true;
}

void CSteadyStateMethod::doJacobian(CMatrix< C_FLOAT64 > & jacobian,
                                    CMatrix< C_FLOAT64 > & jacobianX)
{
  mpContainer->setState(mSteadyState);

  mpContainer->calculateJacobian(jacobian, *mpDerivationResolution, false);
  mpContainer->calculateJacobian(jacobianX, *mpDerivationResolution, true);
}

C_FLOAT64 CSteadyStateMethod::getStabilityResolution()
{
  C_FLOAT64* pTmp = (C_FLOAT64*)getValue("Resolution").pUDOUBLE;
  assert(pTmp);
  return *pTmp;
}

void CSteadyStateMethod::calculateJacobianX(const C_FLOAT64 & oldMaxRate)
{
  mpContainer->setState(mContainerStateReduced);
  mpContainer->calculateJacobian(*mpJacobianX, std::min(*mpDerivationFactor, oldMaxRate), true);
}

std::string CSteadyStateMethod::getMethodLog() const
{
  return mMethodLog.str();
}
