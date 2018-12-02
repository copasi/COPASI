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
  initializeDerivativesCalculations(*mpReducedModel);
 
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
      //std::vector< CDataObject * > DataObjects = mpProblem->getTargetFunctions().getVariablesPointerList(pDataModel);
      //std::vector< CDataObject * >::const_iterator itDataObject = DataObjects.begin();
  size_t i;
  for (i = 0; i < mSystemSize; ++i)
  {
    CMathObject* mo = mpContainer->getMathObject(mpContainerStateTime+i+1);
    mpProblem->getResultAnnotated()->setAnnotation(0, i,mo->getDataObject() );
  }
  for (i = 0; i < mNumParameters; ++i)
  {
    const CMathObject* mo = dynamic_cast<const CMathObject*>(mpContainer->getObject(mpProblem->getParameterCN(i)));
    mpProblem->getResultAnnotated()->setAnnotation(1, i, mo->getDataObject() );
  }

}

void CTimeSensMethod::calculate_dInitialState_dPar(CMatrix<C_FLOAT64>& s)
{
  s.resize(mSystemSize, mNumParameters);

  C_FLOAT64 DerivationFactor = 1e-5;

  //access to the initial state
  CVectorCore< C_FLOAT64 > containerInitialState;
  containerInitialState.initialize(mpContainer->getInitialState());
  const C_FLOAT64 * pInitialState = containerInitialState.array() + mpContainer->getCountFixed() + mpContainer->getCountFixedEventTargets() + 1;
  //check: is this the correct way to get the first entry of the initial state?

  C_FLOAT64 Store;
  C_FLOAT64 X1;
  C_FLOAT64 X2;
  C_FLOAT64 InvDelta;

  CVector< C_FLOAT64 > Y1(mSystemSize);
  CVector< C_FLOAT64 > Y2(mSystemSize);

  C_FLOAT64 * pY1;
  C_FLOAT64 * pY2;

  C_FLOAT64 * pS;
  C_FLOAT64 * pSEnd = s.array() + mSystemSize * mNumParameters;
  
  size_t Col;
  for (Col = 0;  Col < mNumParameters; ++Col)
    {
      Store = *mParameterValuePointers[Col];

      // We only need to make sure that we do not have an underflow problem
      if (fabs(Store) < DerivationFactor)
        {
          X1 = 0.0;

          if (Store < 0.0)
            X2 = -2.0 * DerivationFactor;
          else
            X2 = 2.0 * DerivationFactor;;
        }
      else
        {
          X1 = Store * (1.0 + DerivationFactor);
          X2 = Store * (1.0 - DerivationFactor);
        }

      InvDelta = 1.0 / (X2 - X1);

      *mParameterValuePointers[Col] = X1;
      mpContainer->updateInitialValues(CCore::Framework::ParticleNumbers); //ParticleNumbers  Concentration
      memcpy(Y1.array(), pInitialState, mSystemSize * sizeof(C_FLOAT64));

      *mParameterValuePointers[Col] = X2;
      mpContainer->updateInitialValues(CCore::Framework::ParticleNumbers);
      memcpy(Y2.array(), pInitialState, mSystemSize * sizeof(C_FLOAT64));

      *mParameterValuePointers[Col] = Store;

      pS = s.array() + Col;
      pY1 = Y1.array();
      pY2 = Y2.array();

      for (; pS < pSEnd; pS += mNumParameters, ++pY1, ++pY2)
        *pS = (*pY2 - *pY1) * InvDelta;
    }

    mpContainer->updateInitialValues(CCore::Framework::ParticleNumbers);
  }

void CTimeSensMethod::calculate_dRate_dPar(CMatrix<C_FLOAT64>& s, bool reduced)
{
  s.resize(mSystemSize, mNumParameters);

  C_FLOAT64 DerivationFactor = 1e-5;

  //access to the RHS
  const C_FLOAT64 * pRate = mpContainer->getRate(reduced).array() + mpContainer->getCountFixedEventTargets() + 1;
  //TODO: check: The mathcontainer::calculateJacobian() method uses the non-reduced rate vector always. Is this correct?

  C_FLOAT64 Store;
  C_FLOAT64 X1;
  C_FLOAT64 X2;
  C_FLOAT64 InvDelta;

  CVector< C_FLOAT64 > Y1(mSystemSize);
  CVector< C_FLOAT64 > Y2(mSystemSize);

  C_FLOAT64 * pY1;
  C_FLOAT64 * pY2;

  C_FLOAT64 * pS;
  C_FLOAT64 * pSEnd = s.array() + mSystemSize * mNumParameters;

  size_t Col;
  for (Col = 0;  Col < mNumParameters; ++Col)
    {
      Store = *mParameterValuePointers[Col];

      // We only need to make sure that we do not have an underflow problem
      if (fabs(Store) < DerivationFactor)
        {
          X1 = 0.0;

          if (Store < 0.0)
            X2 = -2.0 * DerivationFactor;
          else
            X2 = 2.0 * DerivationFactor;;
        }
      else
        {
          X1 = Store * (1.0 + DerivationFactor);
          X2 = Store * (1.0 - DerivationFactor);
        }

      InvDelta = 1.0 / (X2 - X1);

      *mParameterValuePointers[Col] = X1;
      mpContainer->applyUpdateSequence(mSeq1);
      //mpContainer->updateSimulatedValues(reduced);
      memcpy(Y1.array(), pRate, mSystemSize * sizeof(C_FLOAT64));

      *mParameterValuePointers[Col] = X2;
      mpContainer->applyUpdateSequence(mSeq1);
      //mpContainer->updateSimulatedValues(reduced);
      memcpy(Y2.array(), pRate, mSystemSize * sizeof(C_FLOAT64));

      *mParameterValuePointers[Col] = Store;

      pS = s.array() + Col;
      pY1 = Y1.array();
      pY2 = Y2.array();

      for (; pS < pSEnd; pS += mNumParameters, ++pY1, ++pY2)
        *pS = (*pY2 - *pY1) * InvDelta;
    }

  mpContainer->applyUpdateSequence(mSeq1);
  //mpContainer->updateSimulatedValues(reduced);
}

void CTimeSensMethod::initializeDerivativesCalculations(bool reduced)
{
  //we need the vector of parameters
  //the problem provides us with the CNs, we need to prepare a means to change the parameter in the math container
  mParameterValuePointers.resize(mNumParameters);

  CObjectInterface::ObjectSet Changed;
  size_t Col;
  for (Col = 0; Col<mNumParameters; ++Col)
  {
    const CMathObject* pMo = dynamic_cast<const CMathObject*>(mpContainer->getObject(mpProblem->getParameterCN(Col)));
    //const CMathObject*  pMo = mpContainer->getMathObject(mpProblem->getParameterCN(Col)); //I do not know why this does not work...
    //const CMathObject * pMo = mpContainer->getMathObject(object*);

    if (pMo != NULL)
            {
              mParameterValuePointers[Col] = (C_FLOAT64 *) pMo->getValuePointer();
              Changed.insert(pMo);
            }
          else
            {
              mParameterValuePointers[Col] = NULL;
            }
  }

  //generate an update sequence for calculate_dRate_dPar().
  //it should update the rates (RHS) after changes in the specified parameters
  mpContainer->getTransientDependencies().getUpdateSequence(mSeq1, CCore::SimulationContext::Default,
          Changed, mpContainer->getSimulationUpToDateObjects() );
  //TODO: this seems to work, but I have no idea if it is the correct and most efficient way to do it.
  //Also it may be more efficient if we create one update list for each parameter, and not a joint list for all

  //TODO: create update lists for the various other numerical derivatives calculations
}
