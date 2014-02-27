// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
#include "model/CModel.h"

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
  size_t i, imax = CLyapMethod::ValidSubTypes.size();

  for (i = 0; i < imax; i++)
    if (CLyapMethod::ValidSubTypes[i] == subType) return true;

  return false;
}

CLyapMethod * CLyapMethod::createMethod(CCopasiMethod::SubType subType)
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
  CCopasiMethod(CCopasiTask::lyap, subType, pParent),
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
double CLyapMethod::step(const double & C_UNUSED(deltaT))
{return 0;}

/**
 *  This instructs the method to calculate a a time step of deltaT
 *  starting with the initialState given.
 *  The new state (after deltaT) is expected in the current state.
 *  The return value is the actual timestep taken.
 *  @param "double &" deltaT
 *  @param "const CState *" initialState
 *  @return "const double &" actualDeltaT
 */
void CLyapMethod::start(CVectorCore< C_FLOAT64 > & /* initialState */)
{return;}

//virtual
bool CLyapMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const CLyapProblem * pLP = dynamic_cast<const CLyapProblem *>(pProblem);

  if (!pLP)
    {
      //not a LyapProblem
      CCopasiMessage(CCopasiMessage::ERROR, MCLyap + 1);
      return false;
    }

  if ((!pLP->divergenceRequested()) && (pLP->getExponentNumber() < 1))
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCLyap + 2);
      return false;
    }

  unsigned C_INT32 tmp = (unsigned C_INT32) pLP->getModel()->getState().getNumIndependent();

  if (pLP->getExponentNumber() > tmp)
    {
      //to few exponents
      CCopasiMessage(CCopasiMessage::ERROR, MCLyap + 3, tmp, tmp);
      return false;
    }

  return true;
}
