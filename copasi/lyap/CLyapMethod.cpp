/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/lyap/CLyapMethod.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/05/04 10:54:43 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CLyapMethod class.
 */

#include "copasi.h"
#include "CLyapMethod.h"
#include "CLyapProblem.h"
#include "model/CState.h"
#include "model/CCompartment.h"

CLyapValidSubTypes::CLyapValidSubTypes():
    std::vector< CCopasiMethod::SubType >()
{
  push_back(CCopasiMethod::lyapWolf);
}

CLyapValidSubTypes::~CLyapValidSubTypes() {}

//******************************************************

//static
const CLyapValidSubTypes CLyapMethod::ValidSubTypes;

//static
bool CLyapMethod::isValidSubType(const CCopasiMethod::SubType & subType)
{
  unsigned C_INT32 i, imax = CLyapMethod::ValidSubTypes.size();

  for (i = 0; i < imax; i++)
    if (CLyapMethod::ValidSubTypes[i] == subType) return true;

  return false;
}

CLyapMethod *
CLyapMethod::createLyapMethod(CCopasiMethod::SubType subType,
                              CLyapProblem * pProblem)
{
  CLyapMethod * pMethod = NULL;

  switch (subType)
    {
    case unset:
    case lyapWolf:
      pMethod = new CLyapWolfMethod();
      break;

    default:
      fatalError();
    }
  return pMethod;
}

/**
 *  Default constructor.
 */
CLyapMethod::CLyapMethod(const CCopasiMethod::SubType & subType,
                         const CCopasiContainer * pParent) :
    CCopasiMethod(CCopasiTask::timeCourse, subType, pParent),
    //mpCurrentState(NULL),
    mpProblem(NULL)
{CONSTRUCTOR_TRACE;}

/**
 *  Copy constructor.
 *  @param "const CLyapMethod &" src
 */
CLyapMethod::CLyapMethod(const CLyapMethod & src,
                         const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent),
    //mpCurrentState(src.mpCurrentState),
    mpProblem(src.mpProblem)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CLyapMethod::~CLyapMethod()
{DESTRUCTOR_TRACE;}

//void CLyapMethod::setCurrentState(CState * currentState)
//{
//  mpCurrentState = currentState;
//}

/**
 *  Set a pointer to the problem.
 *  This method is used by CLyap
 *  @param "CLyapProblem *" problem
 */
void CLyapMethod::setProblem(CLyapProblem * problem)
{mpProblem = problem;}

/**
 *  This instructs the method to calculate a a time step of deltaT
 *  starting with the current state, i.e., the result of the previous
 *  step.
 *  The new state (after deltaT) is expected in the current state.
 *  The return value is the actual timestep taken.
 *  @param "const double &" deltaT
 */
void CLyapMethod::step(const double & C_UNUSED(deltaT))
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
void CLyapMethod::start(const CState * C_UNUSED(initialState))
{return;}

//virtual
bool CLyapMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const CLyapProblem * pTP = dynamic_cast<const CLyapProblem *>(pProblem);
  if (!pTP)
    {
      //not a LyapProblem
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 8);
      return false;
    }

  return true;
}
