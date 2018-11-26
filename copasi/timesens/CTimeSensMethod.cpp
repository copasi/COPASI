// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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
 *  CTimeSensMethod class.
 *  This class describes the interface to all integration methods.
 *  The various method like LSODA or Gillespie have to be derived from
 *  this class.
 *
 *  Created for COPASI by Stefan Hoops 2002
 */

#include "copasi.h"

#include "CTimeSensMethod.h"
#include "CTimeSensLsodaMethod.h"
#include "CTimeSensProblem.h"
#include "CTimeSensTask.h"

#include "model/CState.h"
#include "model/CCompartment.h"
#include "math/CMathContainer.h"

// static
const bool CTimeSensMethod::ReducedModel(false);

/**
 *  Default constructor.
 */
CTimeSensMethod::CTimeSensMethod(const CDataContainer * pParent,
                                     const CTaskEnum::Method & methodType,
                                     const CTaskEnum::Task & taskType):
  CCopasiMethod(pParent, methodType, taskType),
  mContainerState(),
  mpContainerStateTime(NULL),
  mpTask(NULL),
  mpProblem(NULL),
  mRootsFound(0),
  mpReducedModel(&ReducedModel),
  mSystemSize(0)
{
  mpTask = const_cast< CTimeSensTask * >(dynamic_cast< const CTimeSensTask * >(getObjectParent()));
}

/**
 *  Copy constructor.
 *  @param "const CTimeSensMethod &" src
 */
CTimeSensMethod::CTimeSensMethod(const CTimeSensMethod & src,
                                     const CDataContainer * pParent):
  CCopasiMethod(src, pParent),
  mContainerState(),
  mpContainerStateTime(NULL),
  mpTask(NULL),
  mpProblem(NULL),
  mRootsFound(0),
  mpReducedModel(&ReducedModel),
  mSystemSize(0)
{
  mpTask = const_cast< CTimeSensTask * >(dynamic_cast< const CTimeSensTask * >(getObjectParent()));
}

/**
 *  Destructor.
 */
CTimeSensMethod::~CTimeSensMethod()
{DESTRUCTOR_TRACE;}

// virtual
void CTimeSensMethod::signalMathContainerChanged()
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

void CTimeSensMethod::output(const bool & useMoieties)
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
 *  This method is used by CTimeSens
 *  @param "CTimeSensProblem *" problem
 */
void CTimeSensMethod::setProblem(CTimeSensProblem * problem)
{mpProblem = problem;}

// virtual
void CTimeSensMethod::stateChange(const CMath::StateChange & change)
{}

/**
 *  This instructs the method to calculate a a time step of deltaT
 *  starting with the current state, i.e., the result of the previous
 *  step.
 *  The new state (after deltaT) is expected in the current state.
 *  The return value is the actual timestep taken.
 *  @param "const double &" deltaT
 */
CTimeSensMethod::Status CTimeSensMethod::step(const double & /* deltaT */,
    const bool & /* final */)
{return FAILURE;}

void CTimeSensMethod::start()
{
  initResult(); //initializes the container and resizes state and result data structures
  //mContainerState.initialize(mpContainer->getState(*mpReducedModel));
  //mpContainerStateTime = mContainerState.array() + mpContainer->getCountFixedEventTargets();

  return;
}

//virtual
bool CTimeSensMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const CTimeSensProblem * pTP = dynamic_cast<const CTimeSensProblem *>(pProblem);

  if (!pTP)
    {
      //not a TimeSensProblem
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 8);
      return false;
    }

  return true;
}

const CVectorCore< C_INT > & CTimeSensMethod::getRoots() const
{
  return mRootsFound;
}

const bool & CTimeSensMethod::integrateReducedModel() const
{
  return *mpReducedModel;
}

void CTimeSensMethod::initResult()
{
  //****** initialize result annotations ****************

  //determine dimensions of result
  mContainerState.initialize(mpContainer->getState(*mpReducedModel));
  mpContainerStateTime = mContainerState.array() + mpContainer->getCountFixedEventTargets();

  mSystemSize = mContainerState.size() - mpContainer->getCountFixedEventTargets() - 1;
  mNumParameters = mpProblem->getNumParameters();
  //mData.dim = (C_INT)(1+mSystemSize * (1 + mNumParameters)); //including time

  
  CArray::index_type s;
  s.push_back(mSystemSize);
  s.push_back(mNumParameters);

  //resize result & annotations
  mpProblem->getResult().resize(s);
  mpProblem->getResultAnnotated()->resize();
  mpProblem->getResultAnnotated()->setDimensionDescription(0, "Variables");
  mpProblem->getResultAnnotated()->setDimensionDescription(1, "Parameters");
  size_t dim = 0;
  size_t j;

  // annotations
  /*if (mTargetValuePointers.size() > 1)
    {
      std::ostringstream tmp;
      tmp << "Target functions, " << mpProblem->getTargetFunctions().getListTypeDisplayName();
      mpProblem->getResultAnnotated()->setDimensionDescription(dim, tmp.str());
      mpProblem->getScaledResultAnnotated()->setDimensionDescription(dim, tmp.str());

      std::vector< CDataObject * > DataObjects = mpProblem->getTargetFunctions().getVariablesPointerList(pDataModel);
      std::vector< CDataObject * >::const_iterator itDataObject = DataObjects.begin();

      for (j = 0; j < mTargetValuePointers.size(); ++j, ++itDataObject)
        {
          mpProblem->getResultAnnotated()->setAnnotation(dim, j, *itDataObject);
          mpProblem->getScaledResultAnnotated()->setAnnotation(dim, j, *itDataObject);
        }

      ++dim;
    }*/

}
