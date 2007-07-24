// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/CTSSAMethod.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/07/24 18:40:26 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CTSSAMethod class.
 *  This class describes the interface to all  time scale separation analysis methods.
 *  The variaous method like ILDM or CSP have to be derived from
 *  this class.
 *
 */

#include "copasi.h"

#include "CTSSAMethod.h"
#include "CILDMMethod.h"
#include "CCSPMethod.h"

#include "CTSSAProblem.h"
#include "model/CState.h"
#include "model/CCompartment.h"

CTSSAMethod *
CTSSAMethod::createTSSAMethod(CCopasiMethod::SubType subType,
                              CTSSAProblem * /* pProblem */)
{
  CTSSAMethod * pMethod = NULL;

  switch (subType)
    {
    case unset:
    case tssILDM:
      pMethod = new CILDMMethod();
      break;

    case tssCSP:
      pMethod = new CCSPMethod();
      break;

    default:
      fatalError();
    }
  return pMethod;
}

/**
 *  Default constructor.
 */
CTSSAMethod::CTSSAMethod(const CCopasiMethod::SubType & subType,
                         const CCopasiContainer * pParent) :
    CCopasiMethod(CCopasiTask::tssAnalysis, subType, pParent),
    mpCurrentState(NULL),
    mpProblem(NULL)
{CONSTRUCTOR_TRACE;}

/**
 *  Copy constructor.
 *  @param "const CTSSAMethod &" src
 */
CTSSAMethod::CTSSAMethod(const CTSSAMethod & src,
                         const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent),
    mpCurrentState(src.mpCurrentState),
    mpProblem(src.mpProblem)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CTSSAMethod::~CTSSAMethod()
{DESTRUCTOR_TRACE;}

void CTSSAMethod::setCurrentState(CState * currentState)
{
  mpCurrentState = currentState;
}

/**
 *  Set a pointer to the problem.
 *  This method is used by CTSSA
 *  @param "CTSSAProblem *" problem
 */
void CTSSAMethod::setProblem(CTSSAProblem * problem)
{mpProblem = problem;}

/**
 *  This instructs the method to calculate a a time step of deltaT
 *  starting with the current state, i.e., the result of the previous
 *  step.
 *  The new state (after deltaT) is expected in the current state.
 *  The return value is the actual timestep taken.
 *  @param "const double &" deltaT
 */
void CTSSAMethod::step(const double & C_UNUSED(deltaT))
{return ;}

/**
 *  This instructs the method to calculate a a time step of deltaT
 *  starting with the initialState given.
 *  The new state (after deltaT) is expected in the current state.
 *  The return value is the actual timestep taken.
 *  @param "double &" deltaT
 *  @param "const CState *" initialState
 *  @return "const double &" actualDeltaT
 */
void CTSSAMethod::start(const CState * C_UNUSED(initialState))
{return;}

//virtual
bool CTSSAMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const CTSSAProblem * pTP = dynamic_cast<const CTSSAProblem *>(pProblem);
  if (!pTP)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTSSAMethod + 2);
      return false;
    }

  return true;
}
