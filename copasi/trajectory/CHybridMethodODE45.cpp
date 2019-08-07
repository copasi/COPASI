// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 *   CHybridMethodODE45
 *
 *   This class implements an hybrid algorithm for the simulation of a
 *   biochemical system over time.
 *
 *   File name: CHybridMethodODE45.cpp
 *   Author: Shuo Wang
 *   Email: shuowang.learner@gmail.com
 *
 *   Last change: 11, Aug 2014
 *
 */

/* DEFINE ********************************************************************/

#ifdef WIN32
#if _MSC_VER < 1600
#define min _cpp_min
#define max _cpp_max
#endif // _MSC_VER
#endif // WIN32

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <new>
#include <cmath>
#include <fstream>

#include "copasi/copasi.h"
#include "CTrajectoryProblem.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CState.h"
#include "copasi/model/CChemEq.h"
#include "copasi/model/CChemEqElement.h"
#include "copasi/model/CCompartment.h"
#include "copasi/core/CDataVector.h"
#include "copasi/core/CMatrix.h"
#include "copasi/utilities/CDependencyGraph.h"
#include "copasi/utilities/CIndexedPriorityQueue.h"
#include "copasi/utilities/CVersion.h"
#include "copasi/randomGenerator/CRandom.h"
#include "copasi/math/CMathContainer.h"
#include "CHybridMethodODE45.h"

// Uncomment this line below to get debug print out.
// #define DEBUG_OUTPUT 1

// static
std::string CHybridMethodODE45::PartitioningStrategy[] =
{
  "All Reactions Deterministic",
  "User specified Partition",
  "All Reactions Stochastic",
  ""
};

//================Function for Class================
/**
 * Default constructor.
 */
CHybridMethodODE45::CHybridMethodODE45(const CDataContainer * pParent,
                                       const CTaskEnum::Method & methodType,
                                       const CTaskEnum::Task & taskType):
  CTrajectoryMethod(pParent, methodType, taskType),
  mSlowReactions(),
  mFirstReactionSpeciesIndex(C_INVALID_INDEX),
  mCountReactionSpecies(C_INVALID_INDEX),
  mHasStoiReaction(false),
  mHasDetermReaction(false),
  mIntegrationType(HYBRID),
  mLastSuccessState(),
  mTargetTime(0.0),
  mODE45(),
  mODEInitalized(false),
  mRootCounter(0),
  mMaxStepsReached(false),
  mMaxBalance(0),
  mData(),
  mY(),
  mpYdot(NULL),
  mCountContainerVariables(0),
  mSpeciesRateUpdateSequence(),
  mRKMethodStatus(CRungeKutta::INITIALIZE),
  mAmuVariables(),
  mAmuPointers(),
  mA0(0.0),
  mContainerFluxes(),
  mSavedFluxes(),
  mFluxPointers(),
  mPropensitiesUpdateSequence(),
  mEventProcessing(false),
  mFireReaction(false),
  mRootMask(),
  mDiscreteRoots(),
  mRootMasking(NONE),
  mRootValuesLeft(),
  mRootValuesRight(),
  mRootsNonZero(),
  mpRandomGenerator(NULL),
  mOutputFile(),
  mOutputFileName(),
  mOutputCounter(0),
  mpMaxInternalSteps(NULL),
  mpRelativeTolerance(NULL),
  mpAbsoluteTolerance(NULL),
  mpPartitioningStrategy(NULL),
  mpUseRandomSeed(NULL),
  mpRandomSeed(NULL),
  mpFastReactions(NULL)
{
  assert((void *) &mData == (void *) &mData.dim);
  mData.pMethod = this;
  initializeParameter();
}

/**
 * Copy Constructor
 */
CHybridMethodODE45::CHybridMethodODE45(const CHybridMethodODE45 & src,
                                       const CDataContainer * pParent):
  CTrajectoryMethod(src, pParent),
  mSlowReactions(),
  mFirstReactionSpeciesIndex(C_INVALID_INDEX),
  mCountReactionSpecies(C_INVALID_INDEX),
  mHasStoiReaction(false),
  mHasDetermReaction(false),
  mIntegrationType(HYBRID),
  mLastSuccessState(),
  mTargetTime(0.0),
  mODE45(),
  mODEInitalized(false),
  mRootCounter(0),
  mMaxStepsReached(false),
  mMaxBalance(0),
  mData(),
  mY(),
  mpYdot(NULL),
  mCountContainerVariables(0),
  mSpeciesRateUpdateSequence(),
  mRKMethodStatus(CRungeKutta::INITIALIZE),
  mAmuVariables(),
  mAmuPointers(),
  mA0(0.0),
  mContainerFluxes(),
  mSavedFluxes(),
  mFluxPointers(),
  mPropensitiesUpdateSequence(),
  mEventProcessing(false),
  mFireReaction(false),
  mRootMask(),
  mDiscreteRoots(),
  mRootMasking(NONE),
  mRootValuesLeft(),
  mRootValuesRight(),
  mRootsNonZero(),
  mpRandomGenerator(NULL),
  mOutputFile(),
  mOutputFileName(),
  mOutputCounter(0),
  mpMaxInternalSteps(NULL),
  mpRelativeTolerance(NULL),
  mpAbsoluteTolerance(NULL),
  mpPartitioningStrategy(NULL),
  mpUseRandomSeed(NULL),
  mpRandomSeed(NULL),
  mpFastReactions(NULL)
{
  assert((void *) &mData == (void *) &mData.dim);
  mData.pMethod = this;
  initializeParameter();
}

/**
 * Destructor.
 */
CHybridMethodODE45::~CHybridMethodODE45()
{
  if (mRootsFound.array() != NULL)
    {
      delete [] mRootsFound.array();
    }
}

//================Function for System================

/**
 * This methods must be called to elevate subgroups to
 * derived objects. The default implementation does nothing.
 * @return bool success
 */
bool CHybridMethodODE45::elevateChildren()
{
  initializeParameter();
  return true;
}

/**
 * Check if the method is suitable for this problem
 * @return bool suitability of the method
 */
bool CHybridMethodODE45::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CTrajectoryMethod::isValidProblem(pProblem)) return false;

  const CTrajectoryProblem * pTP = dynamic_cast<const CTrajectoryProblem *>(pProblem);

  if (pTP->getDuration() < 0.0)
    {
      // back integration not possible
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 9);
      return false;
    }

  return true;
}

/**
 * Initialize the method parameter
 */
void CHybridMethodODE45::initializeParameter()
{
  mpMaxInternalSteps = assertParameter("Max Internal Steps", CCopasiParameter::Type::UINT, (unsigned C_INT32) 100000);
  mpRelativeTolerance = assertParameter("Relative Tolerance", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.0e-006);
  mpAbsoluteTolerance = assertParameter("Absolute Tolerance", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.0e-009);
  mpPartitioningStrategy = assertParameter("Partitioning Strategy", CCopasiParameter::Type::STRING, PartitioningStrategy[1]);
  mpFastReactions = assertGroup("Deterministic Reactions");
  mpUseRandomSeed = assertParameter("Use Random Seed", CCopasiParameter::Type::BOOL, (bool) USE_RANDOM_SEED);
  mpRandomSeed = assertParameter("Random Seed", CCopasiParameter::Type::UINT, (unsigned C_INT32) RANDOM_SEED);

  std::vector< std::pair < std::string, std::string > > ValidValues;
  std::string * pStr = PartitioningStrategy;

  while (*pStr != "")
    {
      ValidValues.push_back(std::make_pair(*pStr, *pStr));
      pStr++;
    }

  getParameter("Partitioning Strategy")->setValidValues(ValidValues);

  CCopasiParameter FastReactionTemplate("Reaction", CCopasiParameter::Type::CN);
  std::vector< std::pair < CCommonName, CCommonName > > Reactions;
  Reactions.push_back(std::make_pair(CCommonName("Reactions"), CCommonName("Reactions")));
  FastReactionTemplate.setValidValues(Reactions);

  mpFastReactions->getElementTemplates().addParameter(FastReactionTemplate);
}

/**
 * This instructs the method to prepare for integration
 * starting with the initialState given.
 * @param "const CState *" initialState
 */
void CHybridMethodODE45::start()
{
  CTrajectoryMethod::start();

  /* Release previous state and make the initialState the current */
  mLastSuccessState = mContainerState;

  // Call initMethod function
  // Partition the system into stochastic and deterministic reactions
  partitionSystem();

  // Determine the integration type
  determineIntegrationType();

  mCountContainerVariables = mContainerState.size() - mpContainer->getCountFixedEventTargets();
  mData.dim = mCountContainerVariables;

  if (mIntegrationType == HYBRID)
    {
      mData.dim += mSlowReactions.size();
    }

  mY.resize(mData.dim);
  mpYdot = mpContainer->getRate(false).array() + mpContainer->getCountFixedEventTargets();

  mFirstReactionSpeciesIndex = 1 + mpContainer->getCountODEs();
  mCountReactionSpecies = mpContainer->getCountDependentSpecies() + mpContainer->getCountIndependentSpecies();

  // we don't want to directly record new results into mpState, since
  // the sum of slow reaction propensities is also recorded in mY

  mAmuVariables.initialize(mSlowReactions.size(), mY.array() + mCountContainerVariables);
  mAmuVariables = 0.0;

  mTargetTime = *mpContainerStateTime;
  mRootCounter = 0;
  mMaxStepsReached = false;

  mpRandomGenerator = &mpContainer->getRandomGenerator();

  if (*mpUseRandomSeed)
    {
      mpRandomGenerator->initialize(*mpRandomSeed);
    }

  mA0 = -log(mpRandomGenerator->getRandomOO());

  //(6)----set attributes for ODE45
  mRKMethodStatus = CRungeKutta::INITIALIZE;

  //(7)----set attributes for Event Roots
  mRootValuesLeft.resize(mpContainer->getRoots().size());
  mRootValuesRight.initialize(mpContainer->getRoots());
  mRootsNonZero.resize(mpContainer->getRoots().size());
  mRootsNonZero = 0.0;

  if (mRootsFound.array() != NULL)
    {
      delete [] mRootsFound.array();
    }

  size_t NumRoots = mpContainer->getRoots().size();

  mRootsFound.initialize(NumRoots, new C_INT[NumRoots]);

  if (mIntegrationType == HYBRID)
    {
      mMethodRootsFound.resize(mpContainer->getRoots().size() + 1);
      mpHybridRoot = mMethodRootsFound.array() + mpContainer->getRoots().size();
    }
  else
    {
      mMethodRootsFound.resize(mpContainer->getRoots().size());
      mpHybridRoot = NULL;
    }

  mRootsFound = 0;
  mMethodRootsFound = 0;

  mDiscreteRoots.initialize(mpContainer->getRootIsDiscrete());
  mRootMasking    = NONE;
  mRKMethodStatus = CRungeKutta::INITIALIZE;

  return;
}

//================Function for Model================

/**
 * Check whether a function is fast or not.
 */
void CHybridMethodODE45::partitionSystem()
{
  size_t nFast = 0;
  size_t nSlow = 0;

  if (*mpPartitioningStrategy == PartitioningStrategy[AllDeterministic])
    {
      nFast = mpContainer->getReactions().size();
    }
  else if (*mpPartitioningStrategy == PartitioningStrategy[UserSpecified])
    {
      nFast = mpFastReactions->size();
      nSlow = mpContainer->getReactions().size() - nFast;
    }
  else if (*mpPartitioningStrategy == PartitioningStrategy[AllStochastic])
    {
      nSlow = mpContainer->getReactions().size();
    }
  else
    {
      fatalError();
    }

  mHasStoiReaction   = (nSlow > 0);
  mHasDetermReaction = (nFast > 0);

  mContainerFluxes.initialize(mpContainer->getFluxes());
  mSlowReactions.resize(nSlow);
  mAmuPointers.resize(nSlow);
  mFluxPointers.resize(nSlow);

  CObjectInterface::ObjectSet Propensities;
  CObjectInterface::ObjectSet Fluxes;

  if (*mpPartitioningStrategy != PartitioningStrategy[AllDeterministic])
    {
      std::set< CMathReaction * > SlowReactions;

      // All reactions are slow
      CMathReaction * pReaction = mpContainer->getReactions().array();
      CMathReaction * pReactionEnd = pReaction + mpContainer->getReactions().size();

      for (; pReaction != pReactionEnd; ++pReaction)
        {
          SlowReactions.insert(pReaction);
        }

      if (*mpPartitioningStrategy == PartitioningStrategy[UserSpecified])
        {
          CCopasiParameterGroup::elements::const_iterator it = mpFastReactions->beginIndex();
          CCopasiParameterGroup::elements::const_iterator end = mpFastReactions->endIndex();

          for (; it != end; ++it)
            {
              const CReaction * pModelReaction = dynamic_cast< const CReaction * >(getObjectFromCN((*it)->getValue< CCommonName >()));

              if (pModelReaction == NULL) continue;

              pReaction = mpContainer->getMathReaction(pModelReaction);

              if (pReaction == NULL) continue;

              SlowReactions.erase(pReaction);
            }
        }

      std::set< CMathReaction * >::iterator itSlow = SlowReactions.begin();
      std::set< CMathReaction * >::iterator endSlow = SlowReactions.end();

      CMathReaction ** ppSlowReaction = mSlowReactions.array();
      C_FLOAT64 ** ppSlowAmu = mAmuPointers.array();
      C_FLOAT64 ** ppSlowFlux = mFluxPointers.array();

      for (; itSlow != endSlow; ++itSlow)
        {
          *ppSlowReaction = *itSlow;
          ++ppSlowReaction;
          *ppSlowAmu = (C_FLOAT64 *)(*itSlow)->getPropensityObject()->getValuePointer();
          ++ppSlowAmu;
          *ppSlowFlux = (C_FLOAT64 *)(*itSlow)->getFluxObject()->getValuePointer();
          ++ppSlowFlux;

          Propensities.insert((*itSlow)->getPropensityObject());
          Fluxes.insert((*itSlow)->getFluxObject());
        }
    }

  CObjectInterface::ObjectSet::const_iterator it = mpContainer->getSimulationUpToDateObjects().begin();
  CObjectInterface::ObjectSet::const_iterator end = mpContainer->getSimulationUpToDateObjects().end();
  CObjectInterface::ObjectSet SpeciesRates;

  for (; it != end; ++it)
    {
      const CMathObject * pObject = static_cast< const CMathObject * >(*it);

      if ((pObject->getSimulationType() == CMath::SimulationType::Dependent ||
           pObject->getSimulationType() == CMath::SimulationType::Independent) &&
          pObject->getValueType() == CMath::ValueType::Rate)
        {
          SpeciesRates.insert(pObject);
        }
    }

  // Create the sequence which updates the species rates discarding the contribution of the slow reactions.
  mpContainer->getTransientDependencies().getUpdateSequence(mSpeciesRateUpdateSequence, CCore::SimulationContext::Default, Fluxes, SpeciesRates);

  // Create the sequence which updates the propensities of the slow reactions.
  mpContainer->getTransientDependencies().getUpdateSequence(mPropensitiesUpdateSequence, CCore::SimulationContext::Default, Fluxes, Propensities);

  return;
}

/**
 * Setup mMethod, switching between Deterministic Method and
 * Hybrid Method
 */
void CHybridMethodODE45::determineIntegrationType()
{
  if (mHasStoiReaction)
    {
      mIntegrationType = HYBRID;
    }
  else
    {
      mIntegrationType = DETERMINISTIC;
    }

  return;
}

//========Function for Simulation========
/**
 *  This instructs the method to calculate a time step of deltaT
 *  starting with the current state, i.e., the result of the previous
 *  step.
 *  The new state (after deltaT) is expected in the current state.
 *  The return value is the actual timestep taken.
 *  @param "const double &" deltaT
 *  @return Status status
 */
CTrajectoryMethod::Status CHybridMethodODE45::step(const double & deltaT,
    const bool & /* final */)
{
  // do several steps
  C_FLOAT64 time    = *mpContainerStateTime;
  C_FLOAT64 endTime  = time + deltaT;
  mEventProcessing = false;

  if (endTime != mTargetTime) //new time step
    {
      mTargetTime = endTime;
      mRootCounter = 0;
    }

  size_t counter = 0;

  while (mRootCounter < *mpMaxInternalSteps &&
         fabs(time - endTime) > 100.0 * (fabs(endTime) * std::numeric_limits< C_FLOAT64 >::epsilon() + std::numeric_limits< C_FLOAT64 >::min()))
    {
      time = doSingleStep(endTime);
      ++counter;

      if (mEventProcessing)
        {
          mLastSuccessState = mContainerState;
          mRootCounter++;
          counter = 0;

          return ROOT;
        }
      else if (mRKMethodStatus != CRungeKutta::ERROR)
        {
          if (mpProblem->getAutomaticStepSize()) break;

          if (counter >= *mpMaxInternalSteps)
            return FAILURE;

          continue;
        }
      else
        {
          return FAILURE;
        }
    }

  // Warning Message
  if ((mRootCounter >= *mpMaxInternalSteps) && (!mMaxStepsReached))
    {
      mMaxStepsReached = true; //only report this message once
      CCopasiMessage(CCopasiMessage::WARNING, "maximum number of reaction events was reached in at least one simulation step.\nThat means time intervals in the output may not be what you requested.");
    }

  mLastSuccessState = mContainerState;

  return NORMAL;
}

/**
 *  Simulates the system over the next interval of time. The new time after
 *  this step is returned.
 *
 *  @param  endTime A C_FLOAT64 specifying the endTime of the current step()
 *  @return A C_FLOAT giving the new time
 */
C_FLOAT64 CHybridMethodODE45::doSingleStep(C_FLOAT64 endTime)
{
  if (mRKMethodStatus == CRungeKutta::ERROR)
    {
      return *mpContainerStateTime;
    }

  if (mFireReaction) // Handle reaction events which were postponed due to system events
    {
      fireReaction();

      if (mEventProcessing)
        {
          return *mpContainerStateTime;
        }
    }

  integrateDeterministicPart(endTime);

  C_FLOAT64 ds = *mpContainerStateTime;

  if (mFireReaction && !mEventProcessing) // Handle reaction events if no system events are found
    {
      fireReaction();
    }

  return ds;
}

void CHybridMethodODE45::stateChange(const CMath::StateChange & change)
{
  if ((change & (CMath::StateChange(CMath::eStateChange::State) | CMath::eStateChange::ContinuousSimulation | CMath::eStateChange::EventSimulation)) &&
      mRKMethodStatus != CRungeKutta::INITIALIZE)
    {
      mRKMethodStatus = CRungeKutta::RESTART;
      destroyRootMask();
    }

  return;
}

/**
 * Fire slow reaction and update populations and propensities
 * when Hybrid Method is used
 */
void CHybridMethodODE45::fireReaction()
{
  // At this point the container state and the simulated values, i.e. the roots are
  // correctly calculated
  mRootValuesLeft = mRootValuesRight;

  CMathReaction * pReaction = getReactionToFire();
  pReaction->fire();
  mFireReaction = false;

  mAmuVariables = 0.0;
  mA0 = -log(mpRandomGenerator->getRandomOO());

  // Update all values needed for simulation.
  // TODO PERFORMANCE Use a reaction dependent update sequence.
  mpContainer->updateSimulatedValues(false);
  mpContainer->updateRootValues(false);

  destroyRootMask();
  mEventProcessing = checkRoots();
  mRKMethodStatus = CRungeKutta::RESTART;

  return;
}

/**
 * Check whether a root has been found
 */
bool CHybridMethodODE45::checkRoots()
{
  bool hasRoots = false;

  C_FLOAT64 *pRootValueOld = mRootValuesLeft.array();
  C_FLOAT64 *pRootValueNew = mRootValuesRight.array();
  C_FLOAT64 *pRootNonZero = mRootsNonZero.array();

  C_INT *pRootFound    = mRootsFound.array();
  C_INT *pRootFoundEnd    = pRootFound + mRootsFound.size();

  const bool * pIsDiscrete = mpContainer->getRootIsDiscrete().array();
  const bool * pIsTimeDependent = mpContainer->getRootIsTimeDependent().array();

  for (; pRootFound != pRootFoundEnd; pRootValueOld++, pRootValueNew++, pRootFound++, pRootNonZero++, pIsDiscrete++, pIsTimeDependent++)
    {
      if (*pRootValueOld **pRootValueNew < 0.0 ||
          (*pRootValueNew == 0.0 && *pIsTimeDependent && !*pIsDiscrete))
        {
          // These root changes are not caused by the time alone as those are handled in do single step.
          hasRoots = true;
          *pRootFound = static_cast< C_INT >(CMath::RootToggleType::ToggleBoth);
        }
      else if (*pRootValueNew == 0.0 &&
               *pRootValueOld != 0.0)
        {
          hasRoots = true;
          *pRootFound = static_cast< C_INT >(CMath::RootToggleType::ToggleEquality); // toggle only equality
          *pRootNonZero = *pRootValueOld;
        }
      else if (*pRootValueNew != 0.0 &&
               *pRootValueOld == 0.0 &&
               *pRootValueNew **pRootNonZero < 0.0)
        {
          hasRoots = true;
          *pRootFound = static_cast< C_INT >(CMath::RootToggleType::ToggleInequality); // toggle only inequality
        }
      else
        {
          *pRootFound = static_cast< C_INT >(CMath::RootToggleType::NoToggle);
        }
    }

  return hasRoots;
}

//========Function for ODE45========
/**
 * Integrates the deterministic reactions of the system over
 * the specified time interval.
 *
 * @param ds A C_FLOAT64 specifying the stepsize.
 */
void CHybridMethodODE45::integrateDeterministicPart(C_FLOAT64 endTime)
{
  C_FLOAT64 StartTime = *mpContainerStateTime;

  //1----Set Parameters for ODE45 solver

  //=(3)= set time and old time

  //=(4)= set y and ode status
  if (mRKMethodStatus == CRungeKutta::INITIALIZE ||
      mRKMethodStatus == CRungeKutta::RESTART)
    {
      //only when starts a new step, we should copy state into ode solver
      memcpy(mY.array(), mpContainerStateTime, mCountContainerVariables * sizeof(C_FLOAT64));
    }
  else if (mRKMethodStatus != CRungeKutta::ERROR)
    {
      mRKMethodStatus = CRungeKutta::CONTINUE;
    }
  else
    {
      fatalError();
    }

  //3----If time increment is too small, do nothing
  C_FLOAT64 tdist = fabs(endTime - *mpContainerStateTime); //absolute time increment
  C_FLOAT64 w0 = std::max(fabs(*mpContainerStateTime), fabs(endTime));

  if (tdist < std::numeric_limits< C_FLOAT64 >::epsilon() * 2. * w0) //just do nothing
    {
      mRKMethodStatus = CRungeKutta::ERROR;
      *mpContainerStateTime = endTime;

      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 6, "delta is too small");
      mRKMethodStatus = CRungeKutta::ERROR;

      return;
    }

  //4----just do nothing if there are no variables
  if (!mData.dim)
    {
      *mpContainerStateTime = endTime;
      return;
    }

  //5----do integration
  mRKMethodStatus = mODE45(&mData.dim, mY.array(), mpContainerStateTime, &endTime,
                           mMethodRootsFound.size(), mMethodRootsFound.array(), mRKMethodStatus, mpProblem->getAutomaticStepSize(),
                           mpRelativeTolerance, mpAbsoluteTolerance, mpMaxInternalSteps, EvalF, EvalR);

  //6----check status
  if (mRKMethodStatus == CRungeKutta::ERROR)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 6, mODE45.getErrorMesssage().c_str());
    }
  else if (mRKMethodStatus == CRungeKutta::ROOTFOUND)
    {
      if (mRootCounter > 0.99 * *mpMaxInternalSteps ||
          StartTime == *mpContainerStateTime) // oscillation around roots
        {
          switch (mRootMasking)
            {
              case NONE:
              case DISCRETE:
                mRKMethodStatus = CRungeKutta::RESTART;

                mLastSuccessState = mContainerState;
                createRootMask();
                mRootCounter = 0;
                return;

                break;

              case ALL:
                break;
            }
        }

      // We need to determine whether we have a slow reaction event or
      // another event or both.
      mFireReaction = (mpHybridRoot != NULL && *mpHybridRoot != 0);

      mEventProcessing = false;
      memcpy(mRootsFound.array(), mMethodRootsFound.array(), mRootsFound.size() * sizeof(C_INT));

      C_INT * pRootFound = mRootsFound.array();
      C_INT * pRootFoundEnd = pRootFound + mRootsFound.size();

      for (; pRootFound != pRootFoundEnd; ++pRootFound)
        if (*pRootFound != 0)
          {
            mEventProcessing = true;
            break;
          }
    }
  else
    {
      switch (mRootMasking)
        {
          case NONE:
          case DISCRETE:
            break;

          case ALL:
          {
            const bool *pDiscrete = mDiscreteRoots.array();
            bool *pMask = mRootMask.array();
            bool const * const pMaskEnd = pMask + mRootMask.size();

            bool destroy = true;

            for (; pMask != pMaskEnd; ++pMask, ++pDiscrete)
              {
                if (*pMask)
                  {
                    if (*pDiscrete)
                      destroy = false;
                    else
                      *pMask = false;
                  }
              }

            if (destroy)
              destroyRootMask();
            else
              mRootMasking = DISCRETE;

            if (mRKMethodStatus != CRungeKutta::ERROR) //&& (mRKMethodStatus != SYS_EVENT))
              mRKMethodStatus = CRungeKutta::RESTART;
          }
        } //end switch
    } //end if

  // Update the container state and the simulated values.
  memcpy(mpContainerStateTime, mY.array(), mCountContainerVariables * sizeof(C_FLOAT64));
  mpContainer->updateSimulatedValues(false);

  return;
}

/**
 * Dummy f function for calculating derivative of y
 */
void CHybridMethodODE45::EvalF(const size_t * n, const C_FLOAT64 * t, const C_FLOAT64 * y,
                               C_FLOAT64 * ydot)
{static_cast<Data *>((void *) n)->pMethod->evalF(t, y, ydot);}

/**
 * Dummy f function for calculating roots value
 */
void CHybridMethodODE45::EvalR(const size_t * n, const C_FLOAT64 * t, const C_FLOAT64 * y,
                               const size_t * nr, C_FLOAT64 * r)
{static_cast<Data *>((void *) n)->pMethod->evalR(t, y, nr, r);}

/**
 * Derivative Calculation Function
 */
void CHybridMethodODE45::evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{
#ifdef DEBUG_OUTPUT
  std::cout << "evalF T    : " << *t << std::endl;
  std::cout << "evalF Y    : " << CVectorCore< const C_FLOAT64 >(mData.dim, y) << std::endl;
#endif // DEBUG_OUTPUT

  memcpy(mpContainerStateTime, y, mCountContainerVariables * sizeof(C_FLOAT64));
  *mpContainerStateTime = *t;

  mpContainer->updateSimulatedValues(false);
  memcpy(ydot, mpYdot, mCountContainerVariables * sizeof(C_FLOAT64));

  //(3) Deal with slow reactions
  if (mIntegrationType == HYBRID)
    {
      mSavedFluxes = mContainerFluxes;
      // Calculate the propensities of the slow reactions
      mpContainer->applyUpdateSequence(mPropensitiesUpdateSequence);

      C_FLOAT64 **ppSlowAmu = mAmuPointers.array();
      C_FLOAT64 **ppSlowAmuEnd = ppSlowAmu + mAmuPointers.size();
      C_FLOAT64 **ppSlowFlux = mFluxPointers.array();
      C_FLOAT64 *pAmu = ydot + mCountContainerVariables;

      for (; ppSlowAmu != ppSlowAmuEnd; ++ppSlowAmu, ++pAmu, ++ppSlowFlux)
        {
          *pAmu = **ppSlowAmu;

          // We temporary set the slow reaction flux to 0 so that we can correctly calculate the species
          // rates ignoring the slow reactions. The next call to updateSimulatedValues will undo this.
          **ppSlowFlux = 0.0;
        }

      // Calculate the species rates discarding the slow reaction fluxes.
      mpContainer->applyUpdateSequence(mSpeciesRateUpdateSequence);

      // Update species rates
      memcpy(ydot + mFirstReactionSpeciesIndex, mpYdot + mFirstReactionSpeciesIndex, mCountReactionSpecies * sizeof(C_FLOAT64));

      // Reset the fluxes
      mContainerFluxes = mSavedFluxes;
      mpContainer->applyUpdateSequence(mSpeciesRateUpdateSequence);
    }

  //
#ifdef DEBUG_OUTPUT
  std::cout << "evalF dY/dT: " << CVectorCore< C_FLOAT64 >(mData.dim, ydot) << std::endl;
#endif // DEBUG_OUTPUT

  return;
}

/**
 * Dummy Function for calculating roots value
 */
void CHybridMethodODE45::evalR(const C_FLOAT64 *t, const C_FLOAT64 *y,
                               const size_t *nr, C_FLOAT64 *r)
{
#ifdef DEBUG_OUTPUT
  std::cout << "evalR T    : " << *t << std::endl;
  std::cout << "evalR Y    : " << CVectorCore< const C_FLOAT64 >(mData.dim, y) << std::endl;
#endif // DEBUG_OUTPUT

  memcpy(mpContainerStateTime, y, mCountContainerVariables * sizeof(C_FLOAT64));
  *mpContainerStateTime = *t;

  mpContainer->updateRootValues(false);

  CVectorCore< C_FLOAT64 > RootValues;

  if (mIntegrationType == HYBRID)
    {
      RootValues.initialize(*nr - 1, r);

      C_FLOAT64 * pHybridRoot = r + (*nr - 1);

      const C_FLOAT64 * pAmu = y + mCountContainerVariables;
      const C_FLOAT64 * pAmuEnd = pAmu + mAmuPointers.size();

      *pHybridRoot = mA0;

      for (; pAmu != pAmuEnd; ++pAmu)
        {
          *pHybridRoot -= *pAmu;
        }
    }
  else
    {
      RootValues.initialize(*nr, r);
    }

  RootValues = mpContainer->getRoots();

#ifdef DEBUG_OUTPUT
  std::cout << "evalR Roots: " << CVectorCore< const C_FLOAT64 >(*nr, r) << std::endl;
#endif // DEBUG_OUTPUT

  if (mRootMasking != NONE)
    {
      maskRoots(RootValues);
    }

#ifdef DEBUG_OUTPUT
  std::cout << "evalR Roots: " << CVectorCore< const C_FLOAT64 >(*nr, r) << std::endl;
#endif // DEBUG_OUTPUT

  return;
}

/**
 * Calculate which slow reaction fires
 */
CMathReaction * CHybridMethodODE45::getReactionToFire()
{
  // calculate the sum of the integrated propensities
  C_FLOAT64 * pAmu = mAmuVariables.array();
  C_FLOAT64 * pAmuEnd = pAmu + mAmuVariables.size();

  //get the threshold
  C_FLOAT64 A0 = mA0 * mpRandomGenerator->getRandomOO();

  //get the reaction index
  CMathReaction ** ppSlowReaction = mSlowReactions.array();
  pAmu = mAmuVariables.array();

  for (; pAmu != pAmuEnd; ++pAmu, ++ppSlowReaction)
    {
      A0 -= *pAmu;

      if (A0 <= 0.0)
        {
          return *ppSlowReaction;
        }
    }

  // Silence the compiler warning related to
  // the fact that it would theoretically be possible
  // to not execute the return statement in the above
  // loop (e.g. mNumSlowReactions = 0)

  return *(--ppSlowReaction);
}

//========Root Masking========
void CHybridMethodODE45::maskRoots(CVectorCore<C_FLOAT64 > & rootValues)
{
  const bool *pMask    = mRootMask.array();
  const bool *pMaskEnd = pMask + mRootMask.size();

  C_FLOAT64 *pRoot = rootValues.array();

  for (; pMask != pMaskEnd; ++pMask, ++pRoot)
    {
      if (*pMask)
        *pRoot = 1.0;
    }

  return;
}

void CHybridMethodODE45::createRootMask()
{
  double absoluteTolerance = 1.e-12;

  size_t NumRoots = mRootsFound.size();
  mRootMask.resize(NumRoots);
  CVector< C_FLOAT64 > RootValues;
  RootValues.resize(NumRoots);
  CVector< C_FLOAT64 > RootDerivatives;
  RootDerivatives.resize(NumRoots);

  mpContainer->updateRootValues(false);
  RootValues = mpContainer->getRoots();
  mpContainer->calculateRootDerivatives(RootDerivatives);

  bool *pMask = mRootMask.array();
  bool *pMaskEnd = pMask + mRootMask.size();
  C_FLOAT64 * pRootValue = RootValues.array();
  C_FLOAT64 * pRootDerivative = RootDerivatives.array();

  for (; pMask != pMaskEnd; ++pMask, ++pRootValue, ++pRootDerivative)
    {
      *pMask = (fabs(*pRootDerivative) < absoluteTolerance ||
                fabs(*pRootValue) < 1e3 * std::numeric_limits< C_FLOAT64 >::min()) ? true : false;
    }

  mRootMasking = ALL;
}

void CHybridMethodODE45::destroyRootMask()
{
  mRootMask.resize(0);
  mRootMasking = NONE;
}

//========Help Function========
/**
 * Test the model if it is proper to perform stochastic simulations on.
 * Several properties are tested (e.g. integer stoichometry, all reactions
 * take place in one compartment only, irreversibility...).
 *
 * @return 0, if everything is ok; <0, if an error occured.
 */
C_INT32 CHybridMethodODE45::checkModel(CModel * model)
{
  CDataVectorNS <CReaction> * mpReactions = &model->getReactions();
  //CMatrix <C_FLOAT64> mStoi = model->getStoiReordered();
  CMatrix <C_FLOAT64> mStoi = model->getStoi();
  C_INT32 multInt;
  size_t i, j, numReactions = mpReactions->size();
  C_FLOAT64 multFloat;
  //  size_t metabSize = mpMetabolites->size();

  for (i = 0; i < numReactions; i++) // for every reaction
    {
      // TEST getCompartmentNumber() == 1
      if ((*mpReactions)[i].getCompartmentNumber() != 1) return - 1;

      // TEST isReversible() == 0
      if ((*mpReactions)[i].isReversible() != 0) return - 2;

      // TEST integer stoichometry
      // Iterate through each the metabolites
      // juergen: the number of rows of mStoi equals the number of non-fixed metabs!

      for (j = 0; j < mStoi.numRows(); j++)
        {
          multFloat = mStoi[j][i];
          multInt = static_cast<C_INT32>(floor(multFloat + 0.5)); // +0.5 to get a rounding out of the static_cast to int!

          if ((multFloat - multInt) > INT_EPSILON) return - 3; // INT_EPSILON in CHybridMethod.h
        }
    }

  return 1; // Model is appropriate for hybrid simulation
}
