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
 *  CTrajectoryMethod class.
 *  This class describes the interface to all integration methods.
 *  The various method like LSODA or Gillespie have to be derived from
 *  this class.
 *
 *  Created for COPASI by Stefan Hoops 2002
 */

#include "copasi.h"

#include "CTrajectoryMethod.h"
#include "CLsodaMethod.h"
#include "CStochDirectMethod.h"
#include "CStochNextReactionMethod.h"
#include "CTrajAdaptiveSA.h"
#include "CTauLeapMethod.h"
#include "CHybridMethodODE45.h"
#include "CTrajectoryMethodDsaLsodar.h"
#include "CTrajectoryProblem.h"
#include "model/CState.h"
#include "model/CCompartment.h"
#include "math/CMathContainer.h"

CTrajectoryMethod *
CTrajectoryMethod::createMethod(CCopasiMethod::SubType subType)
{
  CTrajectoryMethod * pMethod = NULL;

  switch (subType)
    {
      case unset:
      case deterministic:
        pMethod = new CLsodaMethod();
        break;

      case stochastic:
        pMethod = new CStochNextReactionMethod();
        break;

      case directMethod:
        pMethod = new CStochDirectMethod();
        break;

      case tauLeap:
        pMethod = new CTauLeapMethod();
        break;

      case adaptiveSA:
        pMethod = new CTrajAdaptiveSA();
        break;

      case hybridODE45:
        pMethod = new CHybridMethodODE45();
        break;

      case DsaLsodar:
        pMethod = new CTrajectoryMethodDsaLsodar();
        break;

      default:
        fatalError();
        break;
    }

  return pMethod;
}

/**
 *  Default constructor.
 */
CTrajectoryMethod::CTrajectoryMethod(const CCopasiTask::Type & type,
                                     const CCopasiMethod::SubType & subType,
                                     const CCopasiContainer * pParent) :
  CCopasiMethod(type, subType, pParent),
  mContainerState(),
  mpProblem(NULL),
  mpContainerStateTime(NULL),
  mRootsFound(0)
{CONSTRUCTOR_TRACE;}

/**
 *  Copy constructor.
 *  @param "const CTrajectoryMethod &" src
 */
CTrajectoryMethod::CTrajectoryMethod(const CTrajectoryMethod & src,
                                     const CCopasiContainer * pParent):
  CCopasiMethod(src, pParent),
  mContainerState(),
  mpContainerStateTime(NULL),
  mpProblem(NULL),
  mRootsFound(0)
{}

/**
 *  Destructor.
 */
CTrajectoryMethod::~CTrajectoryMethod()
{DESTRUCTOR_TRACE;}

// virtual
void CTrajectoryMethod::signalMathContainerChanged()
{
  if (mpContainer != NULL)
    {
      bool UpdateMoieties = false;

      CCopasiParameter * pParameter = getParameter("Integrate Reduced Model");

      if (pParameter != NULL)
        UpdateMoieties = *pParameter->getValue().pBOOL;

      mContainerState.initialize(mpContainer->getState(UpdateMoieties));
      mpContainerStateTime = mContainerState.array() + mpContainer->getTimeIndex();
    }
  else
    {
      mContainerState.initialize(0, NULL);
      mpContainerStateTime = NULL;
    }
}

/**
 *  Set a pointer to the problem.
 *  This method is used by CTrajectory
 *  @param "CTrajectoryProblem *" problem
 */
void CTrajectoryMethod::setProblem(CTrajectoryProblem * problem)
{mpProblem = problem;}

// virtual
void CTrajectoryMethod::stateChange(const CMath::StateChange & change)
{}

/**
 *  This instructs the method to calculate a a time step of deltaT
 *  starting with the current state, i.e., the result of the previous
 *  step.
 *  The new state (after deltaT) is expected in the current state.
 *  The return value is the actual timestep taken.
 *  @param "const double &" deltaT
 */
CTrajectoryMethod::Status CTrajectoryMethod::step(const double & C_UNUSED(deltaT))
{return FAILURE;}

void CTrajectoryMethod::start()
{
  bool UpdateMoieties = false;

  CCopasiParameter * pParameter = getParameter("Integrate Reduced Model");

  if (pParameter != NULL)
    UpdateMoieties = *pParameter->getValue().pBOOL;

  mContainerState.initialize(mpContainer->getState(UpdateMoieties));

  return;
}

//virtual
bool CTrajectoryMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const CTrajectoryProblem * pTP = dynamic_cast<const CTrajectoryProblem *>(pProblem);

  if (!pTP)
    {
      //not a TrajectoryProblem
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 8);
      return false;
    }

  return true;
}

const CVector< C_INT > & CTrajectoryMethod::getRoots() const
{
  return mRootsFound;
}
