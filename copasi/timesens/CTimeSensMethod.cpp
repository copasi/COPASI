// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 *  CTimeSensMethod class.
 *  This class describes the interface to all integration methods.
 *  The various method like LSODA or Gillespie have to be derived from
 *  this class.
 *
 *  Created for COPASI by Stefan Hoops 2002
 */

#include "copasi/copasi.h"

#include "CTimeSensMethod.h"
#include "CTimeSensLsodaMethod.h"
#include "CTimeSensProblem.h"
#include "CTimeSensTask.h"

#include "copasi/model/CState.h"
#include "copasi/model/CCompartment.h"
#include "copasi/math/CMathContainer.h"

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
  //initResult(); //initializes the container and resizes state and result data structures
  //initializeDerivativesCalculations(*mpReducedModel);

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
  mNumAssTargets = mpProblem->getNumTargets();
  //mData.dim = (C_INT)(1+mSystemSize * (1 + mNumParameters)); //including time

  //resize result & annotations
  CArray::index_type s;
  s.push_back(mSystemSize);
  s.push_back(mNumParameters);

  mpProblem->getStateResult().resize(s);
  mpProblem->getStateResultAnnotated()->resize();
  mpProblem->getStateResultAnnotated()->setDimensionDescription(0, "Variables");
  mpProblem->getStateResultAnnotated()->setDimensionDescription(1, "Parameters");

  mpProblem->getScaledStateResult().resize(s);
  mpProblem->getScaledStateResultAnnotated()->resize();
  mpProblem->getScaledStateResultAnnotated()->setDimensionDescription(0, "Variables");
  mpProblem->getScaledStateResultAnnotated()->setDimensionDescription(1, "Parameters");

  size_t i;

  for (i = 0; i < mSystemSize; ++i)
    {
      CMathObject* mo = mpContainer->getMathObject(mpContainerStateTime + i + 1);

      if (mo)
        {
          mpProblem->getStateResultAnnotated()->setAnnotation(0, i, mo->getDataObject());
          mpProblem->getScaledStateResultAnnotated()->setAnnotation(0, i, mo->getDataObject());
        }
    }

  for (i = 0; i < mNumParameters; ++i)
    {
      const CMathObject* mo = dynamic_cast<const CMathObject*>(mpContainer->getObject(mpProblem->getParameterCN(i)));

      if (mo)
        {
          mpProblem->getStateResultAnnotated()->setAnnotation(1, i, mo->getDataObject());
          mpProblem->getScaledStateResultAnnotated()->setAnnotation(1, i, mo->getDataObject());
        }
    }

  s.clear();
  s.push_back(mpProblem->getNumTargets());
  s.push_back(mNumParameters);

  mpProblem->getTargetsResult().resize(s);
  mpProblem->getTargetsResultAnnotated()->resize();
  mpProblem->getTargetsResultAnnotated()->setDimensionDescription(0, "Targets");
  mpProblem->getTargetsResultAnnotated()->setDimensionDescription(1, "Parameters");

  mpProblem->getScaledTargetsResult().resize(s);
  mpProblem->getScaledTargetsResultAnnotated()->resize();
  mpProblem->getScaledTargetsResultAnnotated()->setDimensionDescription(0, "Targets");
  mpProblem->getScaledTargetsResultAnnotated()->setDimensionDescription(1, "Parameters");

  for (i = 0; i < mpProblem->getNumTargets(); ++i)
    {
      const CMathObject* mo = dynamic_cast<const CMathObject*>(mpContainer->getObject(mpProblem->getTargetCN(i)));

      if (mo)
        {
          mpProblem->getTargetsResultAnnotated()->setAnnotation(0, i, mo->getDataObject());
          mpProblem->getScaledTargetsResultAnnotated()->setAnnotation(0, i, mo->getDataObject());
        }
    }

  for (i = 0; i < mNumParameters; ++i)
    {
      const CMathObject* mo = dynamic_cast<const CMathObject*>(mpContainer->getObject(mpProblem->getParameterCN(i)));

      if (mo)
        {
          mpProblem->getTargetsResultAnnotated()->setAnnotation(1, i, mo->getDataObject());
          mpProblem->getScaledTargetsResultAnnotated()->setAnnotation(1, i, mo->getDataObject());
        }
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

  CCore::Framework tmpFramework;

  size_t Col;

  for (Col = 0;  Col < mNumParameters; ++Col)
    {
      Store = *mParameterInitialValuePointers[Col];

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

      tmpFramework = mParameterIsInitialConcentration[Col] ? CCore::Framework::Concentration : CCore::Framework::ParticleNumbers;

      *mParameterInitialValuePointers[Col] = X1;

      // TODO CRITICAL Bug 2773 We are not guaranteed that this will work for concentration
      // We need to create individual update sequences for each tracked parameter instead of using brute force

      mpContainer->updateInitialValues(tmpFramework); //ParticleNumbers  Concentration
      memcpy(Y1.array(), pInitialState, mSystemSize * sizeof(C_FLOAT64));

      *mParameterInitialValuePointers[Col] = X2;
      mpContainer->updateInitialValues(tmpFramework);
      memcpy(Y2.array(), pInitialState, mSystemSize * sizeof(C_FLOAT64));

      *mParameterInitialValuePointers[Col] = Store;

      pS = s.array() + Col;
      pY1 = Y1.array();
      pY2 = Y2.array();

      for (; pS < pSEnd; pS += mNumParameters, ++pY1, ++pY2)
        * pS = (*pY2 - *pY1) * InvDelta;
    }

  mpContainer->updateInitialValues(tmpFramework);
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
      Store = *mParameterTransientValuePointers[Col];

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

      *mParameterTransientValuePointers[Col] = X1;
      mpContainer->applyUpdateSequence(mSeq1);
      //mpContainer->updateSimulatedValues(reduced);
      memcpy(Y1.array(), pRate, mSystemSize * sizeof(C_FLOAT64));

      *mParameterTransientValuePointers[Col] = X2;
      mpContainer->applyUpdateSequence(mSeq1);
      //mpContainer->updateSimulatedValues(reduced);
      memcpy(Y2.array(), pRate, mSystemSize * sizeof(C_FLOAT64));

      *mParameterTransientValuePointers[Col] = Store;

      pS = s.array() + Col;
      pY1 = Y1.array();
      pY2 = Y2.array();

      for (; pS < pSEnd; pS += mNumParameters, ++pY1, ++pY2)
        * pS = (*pY2 - *pY1) * InvDelta;
    }

  mpContainer->applyUpdateSequence(mSeq1);
  //mpContainer->updateSimulatedValues(reduced);
}

void CTimeSensMethod::calculate_dAssignments_dState(CMatrix<C_FLOAT64>& s, bool reduced)
{
  s.resize(mNumAssTargets, mSystemSize);

  C_FLOAT64 DerivationFactor = 1e-5;

  //access to the state variables
  C_FLOAT64 * pState = const_cast<C_FLOAT64*>(mpContainer->getState(reduced).array()) + mpContainer->getCountFixedEventTargets() + 1;

  C_FLOAT64 Store;
  C_FLOAT64 X1;
  C_FLOAT64 X2;
  C_FLOAT64 InvDelta;

  CVector< C_FLOAT64 > Y1(mNumAssTargets);
  CVector< C_FLOAT64 > Y2(mNumAssTargets);

  C_FLOAT64 * pY1;
  C_FLOAT64 * pY2;

  C_FLOAT64 * pX = pState;
  //C_FLOAT64 * pXEnd = pX + Dim;

  C_FLOAT64 * pS;
  C_FLOAT64 * pSEnd = s.array() + mNumAssTargets * mSystemSize;

  size_t Col;

  for (Col = 0;  Col < mSystemSize; ++Col, ++pX)
    {
      Store = *pX;

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

      *pX = X1;
      mpContainer->applyUpdateSequence(mSeq3);
      size_t i;

      for (i = 0; i < mNumAssTargets; ++i)
        Y1[i] = *mAssTargetValuePointers[i];

      *pX = X2;
      mpContainer->applyUpdateSequence(mSeq3);

      for (i = 0; i < mNumAssTargets; ++i)
        Y2[i] = *mAssTargetValuePointers[i];

      *pX = Store;

      pS = s.array() + Col;
      pY1 = Y1.array();
      pY2 = Y2.array();

      for (; pS < pSEnd; pS += mSystemSize, ++pY1, ++pY2)
        * pS = (*pY2 - *pY1) * InvDelta;
    }

  mpContainer->applyUpdateSequence(mSeq3);
}

void CTimeSensMethod::calculate_dAssignments_dPar(CMatrix<C_FLOAT64>& s)
{
  s.resize(mNumAssTargets, mNumParameters);

  C_FLOAT64 DerivationFactor = 1e-5;

  C_FLOAT64 Store;
  C_FLOAT64 X1;
  C_FLOAT64 X2;
  C_FLOAT64 InvDelta;

  CVector< C_FLOAT64 > Y1(mNumAssTargets);
  CVector< C_FLOAT64 > Y2(mNumAssTargets);

  C_FLOAT64 * pY1;
  C_FLOAT64 * pY2;

  C_FLOAT64 * pS;
  C_FLOAT64 * pSEnd = s.array() + mNumAssTargets * mNumParameters;

  size_t Col;

  for (Col = 0;  Col < mNumParameters; ++Col)
    {
      Store = *mParameterTransientValuePointers[Col];

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

      *mParameterTransientValuePointers[Col] = X1;
      mpContainer->applyUpdateSequence(mSeq2);
      size_t i;

      for (i = 0; i < mNumAssTargets; ++i)
        Y1[i] = *mAssTargetValuePointers[i];

      *mParameterTransientValuePointers[Col] = X2;
      mpContainer->applyUpdateSequence(mSeq2);

      for (i = 0; i < mNumAssTargets; ++i)
        Y2[i] = *mAssTargetValuePointers[i];

      *mParameterTransientValuePointers[Col] = Store;

      pS = s.array() + Col;
      pY1 = Y1.array();
      pY2 = Y2.array();

      for (; pS < pSEnd; pS += mNumParameters, ++pY1, ++pY2)
        * pS = (*pY2 - *pY1) * InvDelta;
    }

  mpContainer->applyUpdateSequence(mSeq2);
}

void CTimeSensMethod::initializeDerivativesCalculations(bool reduced)
{
  //we need the vector of parameters
  //the problem provides us with the CNs, we need to prepare a means to change the parameter in the math container
  mParameterInitialValuePointers.resize(mNumParameters);
  mParameterTransientValuePointers.resize(mNumParameters);
  mParameterIsInitialConcentration.resize(mNumParameters);

  CObjectInterface::ObjectSet Changed;
  size_t Col;

  for (Col = 0; Col < mNumParameters; ++Col)
    {

      const CMathObject* pMo = dynamic_cast<const CMathObject*>(mpContainer->getObject(mpProblem->getParameterCN(Col)));
      const CMathObject* pMo2;
      //const CMathObject*  pMo = mpContainer->getMathObject(mpProblem->getParameterCN(Col)); //I do not know why this does not work...
      //const CMathObject * pMo = mpContainer->getMathObject(object*);

      if (pMo != NULL)
        {
          mParameterIsInitialConcentration[Col] = pMo->isIntensiveProperty();
          mParameterInitialValuePointers[Col] = (C_FLOAT64 *) pMo->getValuePointer();
          mParameterTransientValuePointers[Col] = (C_FLOAT64 *) pMo->getValuePointer();
          pMo2 = mpContainer->getMathObject(pMo->getDataObject()->getObjectParent()->getValueObject());

          if (pMo2->getSimulationType() == CMath::SimulationType::Fixed)
            {
              mParameterTransientValuePointers[Col] = (C_FLOAT64 *) pMo2->getValuePointer();
              Changed.insert(pMo2);
            }
          else
            {
              Changed.insert(pMo);
            }
        }
      else
        {
          mParameterInitialValuePointers[Col] = NULL;
          mParameterTransientValuePointers[Col] = NULL;
        }
    }

  printObjectSet("Parameters", Changed); //debug

  //generate an update sequence for calculate_dRate_dPar().
  //it should update the rates (RHS) after changes in the specified parameters
  mpContainer->getTransientDependencies().getUpdateSequence(mSeq1, CCore::SimulationContext::Default,
      Changed, //the parameters
      mpContainer->getSimulationUpToDateObjects());
  //TODO: this seems to work, but I have no idea if it is the correct and most efficient way to do it.
  //Also it may be more efficient if we create one update list for each parameter, and not a joint list for all

  printObjectSet("Simulation objects", mpContainer->getSimulationUpToDateObjects());
  printUpdateSeq("seq1", mSeq1); //debug

  //we need a vector of Pointers to access the values of the assignment targets for which we calculate sensitivities
  mAssTargetValuePointers.resize(mNumAssTargets);
  CObjectInterface::ObjectSet assTargets;

  for (Col = 0; Col < mNumAssTargets; ++Col)
    {
      const CMathObject* pMo = dynamic_cast<const CMathObject*>(mpContainer->getObject(mpProblem->getTargetCN(Col)));
      //const CMathObject*  pMo = mpContainer->getMathObject(mpProblem->getParameterCN(Col)); //I do not know why this does not work...
      //const CMathObject * pMo = mpContainer->getMathObject(object*);

      if (pMo != NULL)
        {
          mAssTargetValuePointers[Col] = (C_FLOAT64 *) pMo->getValuePointer();
          assTargets.insert(pMo);
        }
      else
        {
          mAssTargetValuePointers[Col] = NULL;
        }
    }

  printObjectSet("targets", assTargets); //debug

  //generate an update sequence for calculate_dAssignments_dPar().
  //it should update the assignment targets after changes in the specified parameters
  mpContainer->getTransientDependencies().getUpdateSequence(mSeq2,
      CCore::SimulationContext::Default,
      Changed,  //the requested parameters
      assTargets); //the assignment targets

  printUpdateSeq("seq2", mSeq2); //debug

  //generate an update sequence for calculate_dAssignments_dState().
  //it should update the assignment targets after changes in the state variables
  mpContainer->getTransientDependencies().getUpdateSequence(mSeq3,
      CCore::SimulationContext::Default,
      mpContainer->getStateObjects(reduced),  //the state variables
      assTargets); //the assignment targets

  printUpdateSeq("seq3", mSeq3); //debug

  //TODO: create update lists for the various other numerical derivatives calculations
}


//static
void CTimeSensMethod::printObjectSet(const std::string & s, const CObjectInterface::ObjectSet & os)
{
#ifdef DEBUG_OBJECTLISTS
  std::cout << "object set: " << s << std::endl;
  CObjectInterface::ObjectSet::const_iterator it;

  for (it = os.begin(); it != os.end(); ++it)
    std::cout << " - " << (*it)->getObjectDisplayName() << std::endl;

  std::cout << std::endl;
#endif
}

//static
void CTimeSensMethod::printUpdateSeq(const std::string & s, const CCore::CUpdateSequence & us)
{
#ifdef DEBUG_OBJECTLISTS
  std::cout << "update seq: " << s << std::endl;
  CMathUpdateSequence::const_iterator it = us.begin();
  CMathUpdateSequence::const_iterator end = us.end();

  for (; it != end; ++it)
    {
      const CDataObject * pDataObject = CObjectInterface::DataObject(*it);
      const CMathObject * pMathObject = dynamic_cast< const CMathObject * >(*it);

      if (pDataObject == NULL && pMathObject == NULL)
        std::cout << " - " << "NULL";

      if (pDataObject != NULL)
        {
          std::cout << " - " << /* pDataObject->getObjectParent()->getObjectDisplayName() << " : " << */ pDataObject->getObjectDisplayName();
        }
      else if (pMathObject != NULL)
        {
          std::cout << " - " << "Mathobject:  " << pMathObject->getObjectDisplayName();
        }

      std::cout << std::endl;
    }

  std::cout << std::endl;
#endif
}
