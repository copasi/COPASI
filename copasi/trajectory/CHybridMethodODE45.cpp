// Copyright (C) 2013 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"
#include "CTrajectoryProblem.h"
#include "model/CModel.h"
#include "model/CMetab.h"
#include "model/CReaction.h"
#include "model/CState.h"
#include "model/CChemEq.h"
#include "model/CChemEqElement.h"
#include "model/CCompartment.h"
#include "utilities/CCopasiVector.h"
#include "utilities/CMatrix.h"
#include "utilities/CDependencyGraph.h"
#include "utilities/CIndexedPriorityQueue.h"
#include "utilities/CVersion.h"
#include "randomGenerator/CRandom.h"
#include "math/CMathContainer.h"
#include "CExpRKMethod.h"
#include "CHybridMethodODE45.h"

//================Function for Class================
/**
 * Default constructor.
 */
CHybridMethodODE45::CHybridMethodODE45(const CCopasiContainer * pParent,
                                       const CTaskEnum::Method & methodType,
                                       const CTaskEnum::Task & taskType):
  CTrajectoryMethod(pParent, methodType, taskType)
{
  assert((void *) &mData == (void *) &mData.dim);
  mData.pMethod = this;

  mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
  initializeParameter();
}

/**
 * Copy Constructor
 */
CHybridMethodODE45::CHybridMethodODE45(const CHybridMethodODE45 & src,
                                       const CCopasiContainer * pParent):
  CTrajectoryMethod(src, pParent)
{
  assert((void *) &mData == (void *) &mData.dim);
  mData.pMethod = this;

  mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
  initializeParameter();
}

/**
 * Destructor.
 */
CHybridMethodODE45::~CHybridMethodODE45()
{
  cleanup();
  DESTRUCTOR_TRACE;
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
      //b ack integration not possible
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 9);
      return false;
    }

  return true;
}

/**
 * Intialize the method parameter
 */
void CHybridMethodODE45::initializeParameter()
{
  CCopasiParameter *pParm;

  assertParameter("Max Internal Steps", CCopasiParameter::UINT, (unsigned C_INT32) MAX_STEPS_ODE);
  assertParameter("Use Random Seed", CCopasiParameter::BOOL, (bool) USE_RANDOM_SEED);
  assertParameter("Random Seed", CCopasiParameter::UINT, (unsigned C_INT32) RANDOM_SEED);

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("HYBRID.MaxSteps")) != NULL)
    {

      setValue("Max Internal Steps", *pParm->getValue().pUINT);
      removeParameter("HYBRID.MaxSteps");

      if ((pParm = getParameter("UseRandomSeed")) != NULL)
        {
          setValue("Use Random Seed", *pParm->getValue().pBOOL);
          removeParameter("UseRandomSeed");
        }

      if ((pParm = getParameter("")) != NULL)
        {
          setValue("Random Seed", *pParm->getValue().pUINT);
          removeParameter("");
        }
    }

  if ((pParm = getParameter("Relative Tolerance")) == NULL)
    {
      addParameter("Relative Tolerance",
                   CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-006);
    }

  if ((pParm = getParameter("Absolute Tolerance")) == NULL)
    {
      addParameter("Absolute Tolerance",
                   CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-009);
    }
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
  initMethod(*mpContainerStateTime);

  return;
}

/**
 *  Initializes the solver and sets the model to be used.
 *  @param model A reference to an instance of a CModel
 */
void CHybridMethodODE45::initMethod(C_FLOAT64 start_time)
{
  //(1)----set attributes related with REACTIONS
  mpFirstOdeVariable = mpContainerStateTime + 1;

  setupReactionFlags();

  //(4)----set attributes related with SYSTEM
  // We ignore fixed event targets and time and add one for sum of propensities
  mData.dim = (C_INT)(mContainerState.size() - mpContainer->getCountFixedEventTargets());

  mTimeRecord = start_time;
  mMaxSteps   = * getValue("Max Internal Steps").pUINT;
  mRootCounter = 0;
  mMaxStepsReached = false;
  setupMethod();

  //=======Check Method Uses Here========
  if (mMethod == STOCHASTIC)
    {
      std::cerr << "At Least One Reaction should be set FAST" << std::endl;
      return; //need error message here......
    }

  //(5)----set attributes related with STOCHASTIC
  mUseRandomSeed = * getValue("Use Random Seed").pBOOL;
  mRandomSeed    = * getValue("Random Seed").pUINT;

  if (mUseRandomSeed)
    mpRandomGenerator->initialize(mRandomSeed);

  //(6)----set attributes for ODE45
  mSysStatus = SYS_NEW;
  mODE45.mODEState = ODE_INIT;
  mODE45.mDim = &mData.dim;

  mODE45.mRelTol = * getValue("Relative Tolerance").pUDOUBLE;
  mODE45.mAbsTol = * getValue("Absolute Tolerance").pUDOUBLE;
  mODE45.mHybrid = true;
  mODE45.mStatis = false;

  // we don't want to directly record new results into mpState, since
  // the sum of slow reaction propensities is also recorded in mY
  mY = new C_FLOAT64[mData.dim];
  mODE45.mY = mY;
  mODE45.mDerivFunc = &CHybridMethodODE45::EvalF;

  //(7)----set attributes for Event Roots
  mNumRoots        = mpContainer->getRoots().size();
  mODE45.mRootNum = mNumRoots;
  mRootMasking    = NONE;

  //================================
  if (mNumRoots > 0)
    {
      mRootsFound.resize(mNumRoots);

      for (size_t i = 0; i < mNumRoots; ++i)
        (mRootsFound.array())[i] = 0;

      mODE45.mEventFunc = &CHybridMethodODE45::EvalR;
      mpRT        = new C_FLOAT64[mNumRoots];
      mpRootValue = new CVectorCore< C_FLOAT64 >(mNumRoots, mpRT);

      mDiscreteRoots.initialize(mpContainer->getRootIsDiscrete());
    }
  else
    {
      mODE45.mEventFunc = NULL;
      mpRT        = NULL;
      mpRootValue = NULL;

      mRootsFound.resize(0);
    }

  return;
}

/**
 *  Clean up memory, etc.
 */
void CHybridMethodODE45::cleanup()
{
  delete mpRandomGenerator;
  mpRandomGenerator = NULL;

  if (mY)
    {
      delete [] mY;
      mY = NULL;
    }

  if (mpRT)
    {
      delete [] mpRT;
      mpRT = NULL;
    }

  if (mpRootValue)
    {
      delete mpRootValue;
      mpRootValue = NULL;
    }

  return;
}

//================Function for Model================

/**
 * Check whether a function is fast or not.
 */
void CHybridMethodODE45::setupReactionFlags()
{
  CMathReaction * pReaction = mpContainer->getReactions().array();
  CMathReaction * pReactionEnd = pReaction + mpContainer->getReactions().size();

  size_t nFast = 0;
  size_t nSlow = 0;

  for (; pReaction != pReactionEnd; ++pReaction)
    {
      if (pReaction->isFast())
        {
          nFast++;
        }
      else
        {
          nSlow++;
        }
    }

  mHasStoiReaction   = (nSlow > 0);
  mHasDetermReaction = (nFast > 0);

  mSlowReactions.resize(nSlow);
  CMathReaction ** ppSlowReaction = mSlowReactions.array();
  mAmu.resize(nSlow);

  pReaction = mpContainer->getReactions().array();

  for (; pReaction != pReactionEnd; ++pReaction)
    {
      if (!pReaction->isFast())
        {
          *ppSlowReaction = pReaction;
          ++ppSlowReaction;
        }
    }

  return;
}

/**
 * Setup mMethod, switching between Deterministic Method and
 * Hybrid Method
 */
void CHybridMethodODE45::setupMethod()
{
  if (mHasStoiReaction && !mHasDetermReaction)
    mMethod = STOCHASTIC;
  else if (!mHasStoiReaction && mHasDetermReaction)
    mMethod = DETERMINISTIC;
  else
    mMethod = HYBRID;

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
CTrajectoryMethod::Status CHybridMethodODE45::step(const double & deltaT)
{
  // do several steps
  C_FLOAT64 time    = *mpContainerStateTime;
  C_FLOAT64 endTime;

  if (time == mTimeRecord) //new time step
    {
      mTimeRecord  += deltaT;
      mRootCounter  = 0;
    }

  endTime = mTimeRecord;

  while (mRootCounter < mMaxSteps && time < endTime)
    {
      time = doSingleStep(endTime);

      if (mSysStatus == SYS_EVENT)
        {
          mLastSuccessState = mContainerState;
          mRootCounter++;
          return ROOT;
        }
      else if (mSysStatus == SYS_CONT)
        continue;
      else if (mSysStatus == SYS_ERR)
        return FAILURE;
    }

  // Warning Message
  if ((mRootCounter >= mMaxSteps) && (!mMaxStepsReached))
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
  C_FLOAT64 ds     = 0.0;
  size_t    rIndex = 0;

  integrateDeterministicPart(endTime);
  ds = mODE45.mT;

  //<i> ~~~~ Doing things about mRootMasking
  if (mSysStatus == SYS_EVENT && mHasRoot)
    {
      if (mRootCounter > 0.99 * mMaxSteps
          || mODE45.mT == *mpContainerStateTime) //oscillation around roots
        {
          switch (mRootMasking)
            {
              case NONE:
              case DISCRETE:
              {
                mLastSuccessState  = mContainerState;
                createRootMask();
                mSysStatus = SYS_NEW;
                break;
              }
              case ALL:
              {
                mSysStatus = SYS_CONT;
                break;
              }
            }

          mRootCounter = 0;
        }
      else
        {
          setRoot(mODE45.mRootId);
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
            bool const * const pMaskEnd = pMask + mNumRoots;
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

            if (mSysStatus != SYS_ERR) //&& (mSysStatus != SYS_EVENT))
              mSysStatus = SYS_CONT;
          }
        } //end switch
    } //end if

  //<ii> ~~~~ Check mSysStatus
  if ((mSysStatus == SYS_EVENT) && mHasSlow) //only deal with system roots
    {
      fireSlowReaction4Hybrid();
      mSysStatus = SYS_NEW;
    }
  else if (mSysStatus == SYS_END) //finish this step
    {
      mSysStatus = SYS_NEW;
    }
  else if (mSysStatus != SYS_CONT && mSysStatus != SYS_EVENT && mSysStatus != SYS_NEW)
    {
      std::cout << "mSysStatus " << mSysStatus << std::endl;
      std::cout << "mSysStatus Error happens, check the code..." << std::endl;
      mSysStatus = SYS_ERR;
    }

  return ds;
}

void CHybridMethodODE45::stateChange(const CMath::StateChange & change)
{
  if (change & CMath::ContinuousSimulation)
    {
      (mRootsFound.array())[mODE45.mRootId] = 0;
      mSysStatus = SYS_NEW;
      destroyRootMask();
    }

  return;
}

/**
 * Fire slow reaction and update populations and propensities
 * when Hybrid Method is used
 */
void CHybridMethodODE45::fireSlowReaction4Hybrid()
{
  updatePropensities();

  CMathReaction * pReaction = getReaction4Hybrid();
  pReaction->fire();

  // Update all values needed for simulation.
  mpContainer->updateSimulatedValues(false);

  return;
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
  //1----Set Parameters for ODE45 solver
  //=(1)= solver error message
  mErrorMsg.str("");

  //=(3)= set time and old time
  mODE45.mT    = *mpContainerStateTime;
  mODE45.mTEnd = endTime;

  //=(4)= set y and ode status
  if (mSysStatus == SYS_NEW)
    {
      //only when starts a new step, we should copy state into ode solver
      C_FLOAT64 * stateY = mpContainerStateTime + 1; // The first value determined by an ODE or reaction.

      for (size_t i = 0; i < mData.dim - 1; i++)
        mY[i] = stateY[i];

      C_FLOAT64 randNum = mpRandomGenerator->getRandomOO();
      mY[mData.dim - 1] = log(randNum);

      if (mODE45.mODEState != ODE_INIT)
        mODE45.mODEState = ODE_NEW;
    }
  else if ((mSysStatus == SYS_EVENT) || (mSysStatus == SYS_CONT))
    {
      mODE45.mODEState = ODE_CONT;
    }
  else
    {
      std::cout << "Wrong mSysStatus = " << mSysStatus << std::endl;
    }

  //3----If time increment is too small, do nothing
  C_FLOAT64 tdist , d__1, d__2, w0;
  tdist = fabs(mODE45.mTEnd - mODE45.mT); //absolute time increment
  d__1  = fabs(mODE45.mT), d__2 = fabs(mODE45.mTEnd);
  w0 = std::max(d__1, d__2);

  if (tdist < std::numeric_limits< C_FLOAT64 >::epsilon() * 2. * w0) //just do nothing
    {
      mODE45.mT  = mODE45.mTEnd;
      mSysStatus = SYS_END;
      *mpContainerStateTime = mODE45.mTEnd;
      std::cout << "delta is too small" << std::endl;
      return;
    }

  //4----just do nothing if there are no variables
  if (!mData.dim)
    {
      mODE45.mT = mODE45.mTEnd;
      mSysStatus = SYS_END;
      *mpContainerStateTime = mODE45.mTEnd;
      return;
    }

  //5----do interpolation
  mODE45.integrate();

  //6----check status
  if (mODE45.mODEState == ODE_ERR)
    {
      mSysStatus = SYS_ERR;
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 6, mErrorMsg.str().c_str());
    }
  else if (mODE45.mODEState == ODE_EVENT)
    {
      mHasSlow = false;
      mHasRoot = false;

      if (mODE45.mRootId == SLOW_REACT)
        mHasSlow = true;
      else
        mHasRoot = true;

      mSysStatus = SYS_EVENT;
    }
  else
    mSysStatus = SYS_END;

  //7----Record State to Container

  *mpContainerStateTime = mODE45.mTEnd;

  //only when starts a new step, we should copy state into ode solver
  C_FLOAT64 * stateY = mpContainerStateTime + 1; // The first value determined by an ODE or reaction.

  for (size_t i = 0; i < mData.dim - 1; i++)
    stateY[i] = mY[i];

  //Dependent Reaction Metabs have been updated by ODE solver
  mpContainer->updateSimulatedValues(false);
  return;
}

/**
 * Function that sets (mRoot.array())[id]=1
 */
void CHybridMethodODE45::setRoot(const size_t id)
{
  assert(id < mNumRoots && id >= 0);

  for (size_t i = 0; i < mNumRoots; i++)
    (mRootsFound.array())[i] = 0;

  (mRootsFound.array())[id] = 1;
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
  size_t i;

  //========No need to record State, right?========
  //1====calculate propensities

  //(1)Put current time *t and independent values *y into model.
  // This step seems necessary, since propensity calculation process
  // requires functions called from the model class.
  *mpContainerStateTime = *t;
  C_FLOAT64 * tmpY = mpContainerStateTime + 1; // The first value determined by an ODE or reaction.
  memcpy(tmpY, y, (mData.dim - 1) * sizeof(C_FLOAT64));

  mpContainer->updateSimulatedValues(false);

  //(2) Calculate derivatives
  updatePropensities();
  ydot[mData.dim - 1] = mAmuSum;

  //(3) Modify fast reactions
  // update derivatives
  // This part is based on the assumption that number of slow reactions is much less than
  // fast reactions. If number of slow reactions is dominate, little difference is there
  // compared to previous version.
  memcpy(ydot, mpContainer->getRate(false).array() + 1, (mData.dim - 1) * sizeof(C_FLOAT64));

  if (mHasSlow)
    {
      CMathReaction ** ppReaction = mSlowReactions.array();
      CMathReaction ** ppReactionEnd = ppReaction + mSlowReactions.size();

      for (; ppReaction != ppReactionEnd; ++ppReaction)
        {
          const CMathReaction::SpeciesBalance * it = (*ppReaction)->getNumberBalance().array();
          const CMathReaction::SpeciesBalance * end = it + (*ppReaction)->getNumberBalance().size();

          C_FLOAT64 * pParticleFlux = (C_FLOAT64 *)(*ppReaction)->getParticleFluxObject()->getValuePointer();

          for (; it != end; ++it)
            {
              ydot[it->first - mpFirstOdeVariable] -= it->second * *pParticleFlux;
            }
        }
    }

  return;
}

/**
 * Dummy Function for calculating roots value
 */
void CHybridMethodODE45::evalR(const C_FLOAT64 *t, const C_FLOAT64 *y,
                               const size_t *nr, C_FLOAT64 *r)
{
  *mpContainerStateTime = *t;
  mpContainer->updateSimulatedValues(false);

  CVectorCore< C_FLOAT64 > RootValues(*nr, r);
  RootValues = mpContainer->getRoots();

  std::cout << "State: " << mpContainer->getState(false) << std::endl;
  std::cout << "Roots: " << RootValues << std::endl;

  if (mRootMasking != NONE)
    {
      maskRoots(RootValues);
    }

  std::cout << "Roots: " << RootValues << std::endl;

  return;
}

//========Function for Stoichastic========
void CHybridMethodODE45::updatePropensities()
{
  mAmuSum = 0.0;

  C_FLOAT64 * pAmu = mAmu.array();
  C_FLOAT64 * pAmuEnd = pAmu + mAmu.size();
  CMathReaction ** ppReaction = mSlowReactions.array();

  for (; pAmu != pAmuEnd; ++pAmu, ++ppReaction)
    {
      CMathObject * pPropensity = const_cast< CMathObject * >((*ppReaction)->getPropensityObject());

      pPropensity->calculate();
      *pAmu = * (C_FLOAT64 *) pPropensity->getValuePointer();
      mAmuSum += *pAmu;
    }
}

/**
 * Calculate which slow reaction fires
 */
CMathReaction * CHybridMethodODE45::getReaction4Hybrid()
{
  //get the threshold
  C_FLOAT64 rand2 = mpRandomGenerator->getRandomOO();
  C_FLOAT64 threshold = mAmuSum * rand2;

  //get the reaction index
  C_FLOAT64 tmp = 0.0;

  //is there some algorithm that can get a log() complex?
  C_FLOAT64 * pAmu = mAmu.array();
  C_FLOAT64 * pAmuEnd = pAmu + mAmu.size();
  CMathReaction ** ppReaction = mSlowReactions.array();

  for (; pAmu != pAmuEnd; ++pAmu, ++ppReaction)
    {
      tmp += *pAmu;

      if (tmp >= threshold)
        {
          break;
        }
    }

  return *ppReaction;
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

  mpContainer->updateSimulatedValues(false);
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
  CCopasiVectorNS <CReaction> * mpReactions = &model->getReactions();
  //CMatrix <C_FLOAT64> mStoi = model->getStoiReordered();
  CMatrix <C_FLOAT64> mStoi = model->getStoi();
  C_INT32 multInt;
  size_t i, j, numReactions = mpReactions->size();
  C_FLOAT64 multFloat;
  //  size_t metabSize = mpMetabolites->size();

  for (i = 0; i < numReactions; i++) // for every reaction
    {
      // TEST getCompartmentNumber() == 1
      if ((*mpReactions)[i]->getCompartmentNumber() != 1) return - 1;

      // TEST isReversible() == 0
      if ((*mpReactions)[i]->isReversible() != 0) return - 2;

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
