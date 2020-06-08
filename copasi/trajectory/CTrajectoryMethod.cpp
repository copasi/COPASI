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
 *  CTrajectoryMethod class.
 *  This class describes the interface to all integration methods.
 *  The various method like LSODA or Gillespie have to be derived from
 *  this class.
 *
 *  Created for COPASI by Stefan Hoops 2002
 */

#include "copasi/copasi.h"

#include "CTrajectoryMethod.h"
#include "CLsodaMethod.h"
#include "CStochDirectMethod.h"
#include "CStochNextReactionMethod.h"
#include "CTrajAdaptiveSA.h"
#include "CTauLeapMethod.h"
#include "CHybridMethodODE45.h"
#include "CTrajectoryMethodDsaLsodar.h"
#include "CTrajectoryProblem.h"
#include "CTrajectoryTask.h"

#include "copasi/model/CState.h"
#include "copasi/model/CCompartment.h"
#include "copasi/math/CMathContainer.h"

// static
const bool CTrajectoryMethod::ReducedModel(false);

/**
 *  Default constructor.
 */
CTrajectoryMethod::CTrajectoryMethod(const CDataContainer * pParent,
                                     const CTaskEnum::Method & methodType,
                                     const CTaskEnum::Task & taskType):
  CCopasiMethod(pParent, methodType, taskType),
  mContainerState(),
  mpContainerStateTime(NULL),
  mpTask(NULL),
  mpProblem(NULL),
  mRootsFound(0),
  mpReducedModel(&ReducedModel)
{
  mpTask = const_cast< CTrajectoryTask * >(dynamic_cast< const CTrajectoryTask * >(getObjectParent()));
}

/**
 *  Copy constructor.
 *  @param "const CTrajectoryMethod &" src
 */
CTrajectoryMethod::CTrajectoryMethod(const CTrajectoryMethod & src,
                                     const CDataContainer * pParent):
  CCopasiMethod(src, pParent),
  mContainerState(),
  mpContainerStateTime(NULL),
  mpTask(NULL),
  mpProblem(NULL),
  mRootsFound(0),
  mpReducedModel(&ReducedModel)
{
  mpTask = const_cast< CTrajectoryTask * >(dynamic_cast< const CTrajectoryTask * >(getObjectParent()));
}

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
      mContainerState.initialize(mpContainer->getState(*mpReducedModel));
      mpContainerStateTime = mContainerState.array() + mpContainer->getCountFixedEventTargets();
    }
  else
    {
      mContainerState.initialize(0, NULL);
      mpContainerStateTime = NULL;
    }
}

void CTrajectoryMethod::output(const bool & useMoieties)
{
  if (mpContainer != NULL)
    {
      mpContainer->setState(mContainerState);
      mpContainer->updateSimulatedValues(useMoieties);
    }

  if (mpTask != NULL)
    {
      mpTask->output(COutputInterface::DURING);
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
CTrajectoryMethod::Status CTrajectoryMethod::step(const double & /* deltaT */,
    const bool & /* final */)
{return FAILURE;}

void CTrajectoryMethod::start()
{
  mContainerState.initialize(mpContainer->getState(*mpReducedModel));
  mpContainerStateTime = mContainerState.array() + mpContainer->getCountFixedEventTargets();

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

const CVectorCore< C_INT > & CTrajectoryMethod::getRoots() const
{
  return mRootsFound;
}

const bool & CTrajectoryMethod::integrateReducedModel() const
{
  return *mpReducedModel;
}
