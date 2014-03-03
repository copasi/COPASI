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
 *   Last change: 26, Aug 2013
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
#include <limits.h>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <new>
#include <cmath>

#include "copasi.h"
#include "CTrajectoryProblem.h"
#include "math/CMathContainer.h"
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

#include "CExpRKMethod.h"
#include "CHybridMethodODE45.h"

//================Function for Class================
/**
 * Default constructor.
 */
CHybridMethodODE45::CHybridMethodODE45(const CCopasiContainer * pParent):
  CTrajectoryMethod(CCopasiMethod::hybridODE45, pParent)
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
 *   Destructor.
 */
CHybridMethodODE45::~CHybridMethodODE45()
{
  cleanup();
  DESTRUCTOR_TRACE;
}

//================Function for System================

bool CHybridMethodODE45::elevateChildren()
{
  initializeParameter();
  return true;
}

//virtual
bool CHybridMethodODE45::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CTrajectoryMethod::isValidProblem(pProblem)) return false;

  const CTrajectoryProblem * pTP = dynamic_cast<const CTrajectoryProblem *>(pProblem);

  if (pTP->getDuration() < 0.0)
    {
      //back integration not possible
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 9);
      return false;
    }

  //check for rules
  size_t i, imax = pTP->getModel()->getNumModelValues();

  for (i = 0; i < imax; ++i)
    {
      if (pTP->getModel()->getModelValues()[i]->getStatus() == CModelEntity::ODE)
        {
          //ode rule found
          CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 18);
          return false;
        }
    }

  imax = pTP->getModel()->getNumMetabs();

  for (i = 0; i < imax; ++i)
    {
      if (pTP->getModel()->getMetabolites()[i]->getStatus() == CModelEntity::ODE)
        {
          //ode rule found
          CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 20);
          return false;
        }
    }

  imax = pTP->getModel()->getCompartments().size();

  for (i = 0; i < imax; ++i)
    {
      if (pTP->getModel()->getCompartments()[i]->getStatus() == CModelEntity::ODE)
        {
          //ode rule found
          CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 21);
          return false;
        }
    }

  /*
  std::string message = pTP->getModel()->suitableForStochasticSimulation();

  if (message != "")
    {
      //model not suitable, message describes the problem
      CCopasiMessage(CCopasiMessage::ERROR, message.c_str());
      return false;
    }
   */

  //mLowerStochLimit = * getValue("Lower Limit").pDOUBLE;
  //mUpperStochLimit = * getValue("Upper Limit").pDOUBLE;

  //if (mLowerStochLimit > mUpperStochLimit)
  //  CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 4,
  //       mLowerStochLimit, mUpperStochLimit);

  //events are not supported at the moment
  /*
  if (pTP->getModel()->getEvents().size() > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 23);
      return false;
      }*/

  return true;
}

void CHybridMethodODE45::initializeParameter()
{
  CCopasiParameter *pParm;

  //-----------------------------------------------------------------------
  // This part will be dealt with later, when considering the partition strategy.
  // Now, under the condition of using statistic partition given by users,
  // we won't adopt such parameters listed here.

  //assertParameter("Lower Limit", CCopasiParameter::DOUBLE, (C_FAT64) LOWER_STOCH_LIMIT);
  //assertParameter("Upper Limit", CCopasiParameter::DOUBLE, (C_FLOAT64) UPPER_STOCH_LIMIT);
  //assertParameter("Partitioning Interval", CCopasiParameter::UINT, (unsigned C_INT32) PARTITIONING_INTERVAL);
  //-----------------------------------------------------------------------
  assertParameter("Max Internal Steps", CCopasiParameter::UINT, (unsigned C_INT32) MAX_STEPS);
  assertParameter("Use Random Seed", CCopasiParameter::BOOL, (bool) USE_RANDOM_SEED);
  assertParameter("Random Seed", CCopasiParameter::UINT, (unsigned C_INT32) RANDOM_SEED);

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("HYBRID.MaxSteps")) != NULL)
    {
      //-------------------------------------------------------------------
      setValue("Max Internal Steps", *pParm->getValue().pUINT);
      removeParameter("HYBRID.MaxSteps");

      /*
      if ((pParm = getParameter("HYBRID.LowerStochLimit")) != NULL)
        {
          setValue("Lower Limit", *pParm->getValue().pDOUBLE);
          removeParameter("HYBRID.LowerStochLimit");
        }

      if ((pParm = getParameter("HYBRID.UpperStochLimit")) != NULL)
        {
          setValue("Upper Limit", *pParm->getValue().pDOUBLE);
          removeParameter("HYBRID.UpperStochLimit");
        }

      if ((pParm = getParameter("HYBRID.PartitioningInterval")) != NULL)//need this part?
        {
          setValue("Partitioning Interval", *pParm->getValue().pUINT);
          removeParameter("HYBRID.PartitioningInterval");
        }
       */
      //-------------------------------------------------------------------

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

  /* ODE45 ****************************************************************************/
  //----------------------------------------------------------------------
  //addParameter("Partitioning Stepsize",
  //             CCopasiParameter::DOUBLE, (C_FLOAT64) PARTITIONING_STEPSIZE);

  //addParameter("Max Internal Steps (LSOA)",
  //             CCopasiParameter::UINT, (unsigned C_INT32) 10000);
  //-----------------------------------------------------------------------

  addParameter("Relative Tolerance",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-006);

  addParameter("Use Default Absolute Tolerance",
               CCopasiParameter::BOOL, (bool) true);

  addParameter("Absolute Tolerance",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) mDefaultAtolValue);
}

void CHybridMethodODE45::start(CVectorCore< C_FLOAT64 > & initialState)
{
  mContainerState = initialState;
  mpContainer->setState(mContainerState);

  mpFirstSpeciesValue = const_cast< C_FLOAT64 *>(mContainerState.array()
                        + mpContainer->getCountFixedEventTargets()
                        + 1 /* Time */
                        + mpContainer->getCountODEs());

  mpFirstSpecies = mpContainer->getMathObject(mpFirstSpeciesValue);

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
  mReactions = mpContainer->getReactions();
  mAmu.resize(mReactions.size());
  mAmuOld.resize(mReactions.size());

  mNumReactionSpecies = mpContainer->getCountIndependentSpecies() + mpContainer->getCountDependentSpecies();

  //(4)----set attributes related with SYSTEM
  mTimeRecord = start_time;
  mMaxSteps = * getValue("Max Internal Steps").pUINT;
  mMaxStepsReached = false;

  //(5)----set attributes related with STOCHASTIC
  mUseRandomSeed = * getValue("Use Random Seed").pBOOL;
  mRandomSeed    = * getValue("Random Seed").pUINT;

  if (mUseRandomSeed)
    mpRandomGenerator->initialize(mRandomSeed);

  setupMethod();
  setupReactionFlags();
  setupBalances();    //initialize mLocalBalances and mLocalSubstrates
  setupDependencyGraph(); // initialize mDG
  setupMetab2React(); //initialize mMetab2React
  setupMetabFlags();
  setupCalculateSet(); //should be done after setupBalances()
  setupReactAffect();

  setupPriorityQueue(start_time); // initialize mPQ

  //(6)----set attributes for ODE45
  mODE45.mODEState = ODE_INIT;

  mData.dim = (size_t)(mNumReactionSpecies + 1);  //one more for sum of propensities
  mODE45.mDim = &mData.dim;

  //mYdot.resize(mData.dim);
  mDefaultAtolValue = 1e-9;
  mODE45.mRelTol = * getValue("Relative Tolerance").pUDOUBLE;
  mODE45.mAbsTol = * getValue("Absolute Tolerance").pUDOUBLE;

  mODE45.mHybrid = true;
  mODE45.mStatis = false;

  //setupUpdateSet();

  // we don't want to directly record new results into mpState, since
  // the sum of slow reaction propensities is also recorded in mY
  mY = new C_FLOAT64[mData.dim];
  mODE45.mY = mY;

  mODE45.mDerivFunc = &CHybridMethodODE45::EvalF;

  //first calculate propensities, in the next integration process
  //system will just update the propensities record in mCalculateSet
  for (size_t i = 0; i < mNumReactions; i++)
    calculateAmu(i);

  //(7)----set attributes for Event Roots
  mRootNum = mpContainer->getRoots().size();
  mODE45.mRootNum = mRootNum;

  mRoots.resize(mRootNum);
  mRoots = 0;

  mRootValues.initialize(mpContainer->getRoots());
  mOldRoot = mRootValues;

  //clear mRootQueue
  std::queue<SRoot> empty;
  std::swap(mRootQueue, empty);

  if (mRootNum > 0)
    {
      mODE45.mEventFunc = &CHybridMethodODE45::EvalR;
    }
  else
    {
      mODE45.mEventFunc = NULL;
    }

  return;
}

/**
 *  Cleans up memory, etc.
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

  return;
}

//================Function for Model================
void CHybridMethodODE45::setupMetabFlags()
{
  size_t rctIndex;
  mMetabFlags.resize(mNumReactionSpecies);

  std::vector<CHybridODE45MetabFlag>::iterator metabIt
  = mMetabFlags.begin();
  const std::vector<CHybridODE45MetabFlag>::iterator metabEndIt
  = mMetabFlags.end();

  // initialization
  for (; metabIt != metabEndIt; ++metabIt)
    {
      metabIt->mFlag = SLOW;
      metabIt->mFastReactions.clear();
    }

  std::vector<CHybridODE45Balance>::iterator  itBalance;
  std::vector<CHybridODE45Balance>::iterator itEndBalance;

  // go over all mLocalBalances, if balance != 0,
  // and reaction is FAST, insert into set
  for (size_t rct = 0; rct < mNumReactions; ++rct)
    {
      if (mReactionFlags[rct] == FAST)
        {
          itBalance = mLocalBalances[rct].begin();
          itEndBalance = mLocalBalances[rct].end();

          for (; itBalance != itEndBalance; ++itBalance)
            {
              size_t metab = itBalance->mIndex;
              mMetabFlags[metab].mFastReactions.insert(rct);
              mMetabFlags[metab].mFlag = FAST;
            }
        }
    }

  return;
}

void CHybridMethodODE45::setupReactionFlags()
{
  mHasStoiReaction = false;
  mHasDetermReaction = false;
  mReactionFlags.resize(mNumReactions);

  for (size_t rct = 0; rct < mNumReactions; rct++)
    {
      if (mReactions[rct].getModelReaction()->isFast())
        {
          mReactionFlags[rct] = FAST;
          mHasDetermReaction = true;
        }
      else
        {
          mReactionFlags[rct] = SLOW;
          mHasStoiReaction = true;
        }
    }

  return;
}

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

/**
 * Sets up an internal representation of the balances for each reaction.
 * This is done in order to be able to deal with fixed metabolites and
 * to avoid a time consuming search for the indices of metabolites in the
 * model.
 */
void CHybridMethodODE45::setupBalances()
{
  size_t i, j;
  CHybridODE45Balance newElement;
  C_INT32 maxBalance = 0;
  size_t numReactions;

  numReactions = mReactions.size();
  mLocalBalances.clear();
  mLocalBalances.resize(numReactions);

  for (i = 0; i < numReactions; i++)
    {
      CMathReaction::Balance::const_iterator itBalance = mReactions[i].getBalance().begin();
      CMathReaction::Balance::const_iterator endBalance = mReactions[i].getBalance().end();

      for (j = 0; itBalance != endBalance; ++itBalance, ++j)
        {
          const CMathObject * pSpecies = static_cast< const CMathObject * >(itBalance->first);
          newElement.mpMetabolite = static_cast< CMetab * >(pSpecies->getDataObject()->getObjectParent());

          newElement.mIndex = itBalance->first - mpFirstSpecies;
          // + 0.5 to get a rounding out of the static_cast to C_INT32!
          newElement.mMultiplicity = static_cast<C_INT32>(floor(itBalance->second + 0.5));

          if ((newElement.mpMetabolite->getStatus()) != CModelEntity::FIXED)
            {
              if (newElement.mMultiplicity > maxBalance) maxBalance = newElement.mMultiplicity;

              mLocalBalances[i].push_back(newElement); // element is copied for the push_back
            }
        }
    }

  mMaxBalance = maxBalance;

  return;
}

/**
 * Sets up the priority queue, for pure SSA.
 *
 * @param startTime The time at which the simulation starts.
 */
void CHybridMethodODE45::setupPriorityQueue(C_FLOAT64 startTime)
{
  size_t i;
  C_FLOAT64 time;

  mPQ.clear();
  mPQ.initializeIndexPointer(mNumReactions);

  for (i = 0; i < mNumReactions; i++)
    {
      calculateAmu(i);
      time = startTime + generateReactionTime(i);
      mPQ.insertStochReaction(i, time);
    }

  return;
}

/**
 * Creates for each metabolite a set of reaction indices.
 * If the metabolite participates in a reaction as substrate
 * or modifiers, this reaction is added to the corresponding set.
 */
void CHybridMethodODE45::setupMetab2React()
{
  // Resize mMetab2React and create an initial set for each metabolite
  mMetab2React.clear();
  mMetab2React.resize(mNumReactionSpecies);

  const CMathReaction * pIt = mReactions.array();
  const CMathReaction * pEnd = pIt + mReactions.size();

  for (size_t i = 0; pIt != pEnd; ++pIt, ++i)
    {
      CMathReaction::Balance::const_iterator itSpecies = pIt->getBalance().begin();
      CMathReaction::Balance::const_iterator endSpecies = pIt->getBalance().end();

      for (; itSpecies != endSpecies; ++itSpecies)
        {
          mMetab2React[itSpecies->first - mpFirstSpecies].insert(i);
        }
    }

  return;
}

// A fast metab appearring in a reaction as a substrate or
// a modifier makes a change of propensity.
void CHybridMethodODE45::setupCalculateSet()
{
  mCalculateSet.clear();

  std::set<size_t>::iterator reactIt;

  std::vector<CHybridODE45MetabFlag>::iterator metabIt
  = mMetabFlags.begin();
  const std::vector<CHybridODE45MetabFlag>::iterator metabEndIt
  = mMetabFlags.end();

  std::vector< std::set<size_t> >::iterator m2rIt =
    mMetab2React.begin();

  for (; metabIt != metabEndIt; ++metabIt, ++m2rIt)
    {
      //for fast metabs, insert reaction into mCalculateSet
      if (metabIt->mFlag == FAST) //fast metab
        {
          for (reactIt  = m2rIt->begin();
               reactIt != m2rIt->end();
               reactIt++) // check all reactions that involves metab
            mCalculateSet.insert(*reactIt);
        }
    }

  return;
}

void CHybridMethodODE45:: setupReactAffect()
{
  mReactAffect.clear();
  mReactAffect.resize(mNumReactions);

  std::vector<std::set<size_t> >::iterator rctIt =
    mReactAffect.begin();
  const std::vector<std::set<size_t> >::iterator rctEndIt =
    mReactAffect.end();

  for (size_t rct = 0; rctIt != rctEndIt; ++rct, ++rctIt)
    {
      rctIt->clear();

      std::vector<CHybridODE45Balance>::iterator balIt =
        mLocalBalances[rct].begin();
      const std::vector<CHybridODE45Balance>::iterator balEndIt =
        mLocalBalances[rct].end();

      for (; balIt != balEndIt; ++balIt)
        {
          size_t metabId = balIt->mIndex;

          std::set<size_t>::iterator it =
            mMetab2React[metabId].begin();
          const std::set<size_t>::iterator endIt =
            mMetab2React[metabId].end();

          for (; it != endIt; ++it)
            rctIt->insert(*it);
        }
    }

  return;
}

//========Function for Simulation========
CTrajectoryMethod::Status CHybridMethodODE45::step(const double & deltaT)
{
  // write the current state to the model???

  // check for possible overflows
  size_t i;
  size_t imax;

  // :TODO: Bug 774: This assumes that the number of variable metabs is the number
  // of metabs determined by reaction. In addition they are expected at the beginning of the
  // MetabolitesX which is not the case if we have metabolites of type ODE.
  //for (i = 0, imax = mpProblem->getModel()->getNumVariableMetabs(); i < imax; i++)
  //  if (mpProblem->getModel()->getMetabolitesX()[i]->getValue() >= mMaxIntBeforeStep)
  //    {
  // throw exception or something like that
  //}

  // do several steps
  //C_FLOAT64 time = mpModel->getTime();
  C_FLOAT64 time    =  *mpContainerStateTime;
  C_FLOAT64 endTime = time + deltaT;

  if (time == mTimeRecord) //new time step
    mTimeRecord = endTime;
  else // continue current step
    endTime = mTimeRecord;

  for (i = 0; ((i < mMaxSteps) && (time < endTime)); i++)
    {
      time = doSingleStep(time, endTime);
      *mpContainerStateTime = time;

      if (mSysStatus == SYS_EVENT)
        {
          return ROOT;
        }
      else if (mSysStatus == SYS_ERR)
        return FAILURE;
    }

  // Warning Message
  if ((i >= mMaxSteps) && (!mMaxStepsReached))
    {
      mMaxStepsReached = true; //only report this message once
      CCopasiMessage(CCopasiMessage::WARNING, "maximum number of reaction events was reached in at least one simulation step.\nThat means time intervals in the output may not be what you requested.");
    }

  // get back the particle numbers

  /* Set the variable metabolites ????*/
  //C_FLOAT64 * Dbl = mpCurrentState->beginIndependent() + mFirstMetabIndex - 1;

  //for (i = 0, imax = mpProblem->getModel()->getNumVariableMetabs(); i < imax; i++, Dbl++)
  //  *Dbl = mpProblem->getModel()->getMetabolitesX()[i]->getValue();

  //the task expects the result in mpCurrentState
  //*mpCurrentState = mpProblem->getModel()->getState();
  //mpState->setTime(time);

  return NORMAL;
}

/**
 *  Simulates the system over the next interval of time. The new time after
 *  this step is returned.
 *
 *  @param  currentTime A C_FLOAT64 specifying the current time
 *  @param  endTime A C_FLOAT64 specifying the endTime of the current step()
 *  @return A C_FLOAT giving the new time
 */
C_FLOAT64 CHybridMethodODE45::doSingleStep(C_FLOAT64 currentTime, C_FLOAT64 endTime)
{
  C_FLOAT64 ds     = 0.0;
  size_t    rIndex = 0;

  if (mMethod == STOCHASTIC) //(1)----Pure SSA Method
    {
      SRoot root;

      if (mSysStatus == SYS_NEW)
        {
          //First Call SSA or Switch to SSA,
          //Calculate Roots
          mSysStatus = SYS_CONT;

          //Check Events at Current Time
          for (size_t id = 0; id < mRootNum; id++)
            {
              if (mRootValues[id] == 0.0)
                {
                  root.id = id;
                  root.t  = currentTime;
                  mRootQueue.push(root);
                }
            }
        }

      //first check mRootQueue
      if (!mRootQueue.empty())
        {
          mSysStatus = SYS_EVENT;

          root = mRootQueue.front();
          mRootQueue.pop();

          setRoot(root.id);
          return root.t;
        }
      else //copy root to mOldRoot
        {
          mOldRoot = mRootValues;
        }

      //Go one step
      bool fire = false;
      getStochTimeAndIndex(ds, rIndex);

      if (ds > endTime)
        {
          ds = endTime;
        }
      else
        {
          fire = true;
          fireReaction(rIndex);
          updatePriorityQueue(rIndex, ds);
        }

      *mpContainerStateTime = ds;

      //Check roots
      mSysStatus = SYS_CONT;

      if (fire)
        {
          for (size_t id = 0; id < mRootNum; id++)
            {
              if ((mOldRoot[id] * mRootValues[id] < 0.0) ||
                  (mRootValues[id] == 0.0))
                {
                  root.t  = ds;
                  root.id = id;
                  mRootQueue.push(root);
                }
            }

          if (!mRootQueue.empty())
            {
              root = mRootQueue.front();
              mRootQueue.pop();

              setRoot(root.id);
              mSysStatus = SYS_EVENT;
              return root.t;
            }
        }
    }
  else //(2)----Involve Deterministic Part
    {
      integrateDeterministicPart(endTime - currentTime);

      ds = mODE45.mT;

      if (mSysStatus == SYS_EVENT) //only deal with system roots
        {
          C_FLOAT64 *stateY = mContainerState.array();

          if (mHasSlow) // slow reaction fires
            {
              //what about the states of model
              fireSlowReaction4Hybrid();

              *mpContainerStateTime = ds;

              mSysStatus = SYS_NEW;
            }

          if (mHasRoot) // system roots
            {
              setRoot(mODE45.mRootId);
            }
        }
      else if (mSysStatus == SYS_END) //finish this step
        mSysStatus = SYS_NEW;
      else //error
        {
          std::cout << "mSysStatus Error happens, check the code..." << std::endl;
          mSysStatus = SYS_ERR;
        }
    }

  return ds;
}

void CHybridMethodODE45::stateChanged()
{
  mRoots[mODE45.mRootId] = 0;
  mSysStatus = SYS_NEW;

  return;
}

void CHybridMethodODE45::fireSlowReaction4Hybrid()
{
  //First Update Propensity
  std::set <size_t>::iterator reactIt = mCalculateSet.begin();
  size_t reactID;

  for (; reactIt != mCalculateSet.end(); reactIt++)
    {
      reactID = *reactIt;
      calculateAmu(reactID);
    }

  reactID = getReactionIndex4Hybrid();

  fireReaction(reactID); //Directly update current state in global view

  //update corresponding propensities
  std::set <size_t>::iterator updateIt = mReactAffect[reactID].begin();
  const std::set <size_t>::iterator updateEndIt = mReactAffect[reactID].end();

  for (; updateIt != updateEndIt; updateIt++)
    {
      reactID = *updateIt;
      calculateAmu(reactID);
    }

  return;
}

/**
 * Integrates the deterministic reactions of the system over
 * the specified time interval.
 *
 * @param ds A C_FLOAT64 specifying the stepsize.
 */
void CHybridMethodODE45::integrateDeterministicPart(C_FLOAT64 deltaT)
{
  //1----Set Parameters for ODE45 solver
  //=(1)= solver error message
  mErrorMsg.str("");

  //=(3)= set time and old time
  mODE45.mT    = *mpContainerStateTime;
  mODE45.mTEnd = mODE45.mT + deltaT;

  //=(4)= set y and ode status
  if (mSysStatus == SYS_NEW)
    {
      //only when starts a new step, we should copy state into ode solver
      C_FLOAT64 * stateY = mContainerState.array();

      for (size_t i = 0; i < mData.dim - 1; i++)
        mY[i] = stateY[i];

      mY[mData.dim - 1] = log(mpRandomGenerator->getRandomOO());

      if (mODE45.mODEState != ODE_INIT)
        mODE45.mODEState = ODE_NEW;
    }
  else if (mSysStatus == SYS_EVENT)
    mODE45.mODEState = ODE_CONT;

  //3----If time increment is too small, do nothing
  C_FLOAT64 tdist , d__1, d__2, w0;
  tdist = fabs(deltaT); //absolute time increment
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

  //7----Record State
  C_FLOAT64 *stateY = mContainerState.array();

  for (size_t i = 0; i < mData.dim - 1; i++)
    stateY[i] = mY[i]; //write result into mpState

  *mpContainerStateTime = mODE45.mTEnd;
  mpContainer->updateSimulatedValues(false); //for assignments?????????

  return;
}

/**
 * Function that sets (mRoot.array())[id]=1
 */
void CHybridMethodODE45::setRoot(const size_t id)
{
  assert(id < mRootNum && id >= 0);

  for (size_t i = 0; i < mRootNum; i++)
    (mRoots.array())[i] = 0;

  (mRoots.array())[id] = 1;
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
  //maybe here I just want the propensities amu???
  //calculateDerivative(temp);

  //1====calculate propensities
  //just care about reactions involving fast metab

  //(1)Put current time *t and independent values *y into model.
  // This step seemes necessary, since propensity calculation process
  // requires functions called from the model class.
  *mpContainerStateTime = *t;
  C_FLOAT64 * tmpY = mContainerState.array();//mpState is a local copy

  for (i = 0; i < mData.dim - 1; ++i)
    tmpY[i] = y[i];

  mpContainer->updateSimulatedValues(false); //really?
  memcpy(ydot, mpContainer->getRate().array(), mData.dim - 1 * sizeof(C_FLOAT64));

  //(2)Calculate propensities.
  std::set <size_t>::iterator reactIt = mCalculateSet.begin();
  size_t reactID;

  for (; reactIt != mCalculateSet.end(); reactIt++)
    {
      reactID = *reactIt;
      calculateAmu(reactID);
    }

  // We cannot use the species rates from the container as they are calculated
  // by summing over all reactions.
  CVectorCore< C_FLOAT64 > SpeciesRates(mNumReactionSpecies, ydot + (mpFirstSpeciesValue - mContainerState.array()));
  SpeciesRates = 0.0;

  //(2)go through all the reactions and
  //update derivatives
  for (i = 0; i < mNumReactions; i++)
    {
      if (mReactionFlags[i] == SLOW) //slow reaction
        ydot[mData.dim - 1] += mAmu[i];
      else //fast reaction
        {
          CMathReaction & Reaction = mReactions[i];
          CMathReaction::Balance::const_iterator itBalance = Reaction.getBalance().begin();
          CMathReaction::Balance::const_iterator endBalance = Reaction.getBalance().end();

          C_FLOAT64 * pParticleFlux = (C_FLOAT64 *) Reaction.getParticleFluxObject()->getValuePointer();

          for (; itBalance != endBalance; ++ itBalance)
            {
              SpeciesRates[itBalance->first - mpFirstSpecies] += floor(itBalance->second + 0.5) * *pParticleFlux;
            }
        }
    }

  return;
}

void CHybridMethodODE45::evalR(const C_FLOAT64 *t, const C_FLOAT64 *y,
                               const size_t *nr, C_FLOAT64 *r)
{
  assert(*nr == (C_INT)mRoots.size());

  *mpContainerStateTime = *t;
  C_FLOAT64 *stateY = mContainerState.array();

  for (size_t i = 0; i < mData.dim - 1; i++)
    stateY[i] = y[i]; //write result into mpState

  mpContainer->updateSimulatedValues(false); //really?

  CVectorCore< C_FLOAT64 > RootValues(*nr, r);
  RootValues = mpContainer->getRoots();

  /*
  if (mRootMasking != NONE)
    {
      maskRoots(RootValues);
    }
   */

  return;
}

//========Function for Stoichastic========
/**
 * Find the reaction index and the reaction time of the stochastic (!)
 * reaction with the lowest reaction time.
 *
 * @param ds A reference to a C_FLOAT64. The putative reaction time for the
 *           first stochastic reaction is written into this variable.
 * @param rIndex A reference to a size_t. The index of the first
 *               stochastic reaction is written into this variable.
 */
void CHybridMethodODE45::getStochTimeAndIndex(C_FLOAT64 & ds, size_t & rIndex)
{
  ds = mPQ.topKey();
  rIndex = mPQ.topIndex();
  return;
}

C_FLOAT64 CHybridMethodODE45::generateReactionTime(size_t rIndex)
{
  if (mAmu[rIndex] == 0) return std::numeric_limits<C_FLOAT64>::infinity();

  C_FLOAT64 rand2 = mpRandomGenerator->getRandomOO();
  return - 1 * log(rand2) / mAmu[rIndex];
}

/**
 * Updates the putative reaction time of a stochastic reaction in the
 * priority queue. The corresponding amu and amu_old must be set prior to
 * the call of this method.
 *
 * @param rIndex A size_t specifying the index of the reaction
 */
void CHybridMethodODE45::updateTauMu(size_t rIndex, C_FLOAT64 time)
{
  C_FLOAT64 newTime;

  // One must make sure that the calculation yields reasonable results even in the cases
  // where mAmu=0 or mAmuOld=0 or both=0. Therefore mAmuOld=0 is checked. If mAmuOld equals 0,
  // then a new random number has to be drawn, because tau equals inf and the stoch.
  // information is lost.
  // If both values equal 0, then tau should remain inf and the update of the queue can
  // be skipped!
  if (mAmuOld[rIndex] == 0.0)
    {
      if (mAmu[rIndex] != 0.0)
        {
          newTime = time + generateReactionTime(rIndex);
          mPQ.updateNode(rIndex, newTime);
        }
    }
  else
    {
      newTime = time + (mAmuOld[rIndex] / mAmu[rIndex]) * (mPQ.getKey(rIndex) - time);
      mPQ.updateNode(rIndex, newTime);
    }

  return;
}

/**
 * Calculates an amu value for a given reaction.
 *
 * @param rIndex A size_t specifying the reaction to be updated
 */
void CHybridMethodODE45::calculateAmu(size_t rIndex)
{
  CMathObject * pPropensity = const_cast< CMathObject * >(mReactions[rIndex].getPropensityObject());
  pPropensity->calculate();
  mAmu[rIndex] = * (C_FLOAT64 *) pPropensity->getValuePointer();
}

/**
 * Gets the set of metabolites which change number when a given
 * reaction is executed.
 *
 * @param rIndex The index of the reaction being executed.
 * @return The set of affected metabolites.
 */
std::set<std::string> *CHybridMethodODE45::getAffects(size_t rIndex)
{
  size_t i;
  std::set<std::string> *retset = new std::set<std::string>;

  // Get the balances  associated with the reaction at this index
  // XXX We first get the chemical equation, then the balances, since the getBalances method in CReaction is unimplemented!

  for (i = 0; i < mLocalBalances[rIndex].size(); i++)
    {
      if (mLocalBalances[rIndex][i].mMultiplicity != 0)
        retset->insert(mLocalBalances[rIndex][i].mpMetabolite->getKey());
    }

  return retset;
}

/**
 * Sets up the dependency graph.
 */
void CHybridMethodODE45::setupDependencyGraph()
{
  mDG.clear();
  mUpdateSequences.clear();

  size_t numReactions = mReactions.size();
  size_t i, j;

  mUpdateSequences.resize(numReactions);
  std::vector< CObjectInterface::UpdateSequence >::iterator itUpdateSequence = mUpdateSequences.begin();

  // For each possible pair of reactions i and j, if the intersection of
  // Affects(i) with DependsOn(j) is non-empty, add a dependency edge from i to j.
  for (i = 0; i < numReactions; i++)
    {
      CMathReaction::Balance::const_iterator itBalance = mReactions[i].getBalance().begin();
      CMathReaction::Balance::const_iterator endBalance = mReactions[i].getBalance().end();

      CObjectInterface::ObjectSet Changed;

      for (j = 0; itBalance != endBalance; ++itBalance, ++j)
        {
          Changed.insert(itBalance->first);
        }

      for (j = 0; j < numReactions; j++, ++itUpdateSequence)
        {
          CObjectInterface::ObjectSet Requested;
          Requested.insert(mReactions[j].getPropensityObject());

          mpContainer->getTransientDependencies().getUpdateSequence(CMath::Default, Changed, Requested, *itUpdateSequence);

          if (itUpdateSequence->size() > 0)
            {
              // The set intersection is non-empty
              mDG.addDependent(i, j);
              break;
            }
        }
    }

  return;
}

/**
 *   Updates the priority queue.
 *
 *   @param rIndex A size_t giving the index of the fired reaction (-1, if no
 *                 stochastic reaction has fired)
 *   @param time A C_FLOAT64 holding the current time
 */

void CHybridMethodODE45::updatePriorityQueue(size_t rIndex, C_FLOAT64 time)
{
  C_FLOAT64 newTime;
  std::set <size_t>::iterator iter, iterEnd;

  if ((rIndex != C_INVALID_INDEX))
    {
      iter = mReactAffect[rIndex].begin();
      iterEnd = mReactAffect[rIndex].end();

      for (; iter != iterEnd; iter++)
        {
          mAmuOld[*iter] = mAmu[*iter];
          calculateAmu(*iter);

          if (*iter != rIndex)
            {
              updateTauMu(*iter, time);
            }
        }
    }

  // draw new random number and update the reaction just fired
  if ((rIndex != C_INVALID_INDEX))
    {
      // reaction is stochastic
      newTime = time + generateReactionTime(rIndex);
      mPQ.updateNode(rIndex, newTime);
    }

  return;
}

/**
 *   Executes the specified reaction in the system once.
 *
 *   @param rIndex A size_t specifying the index of the reaction, which
 *                 will be fired.
 */
void CHybridMethodODE45::fireReaction(size_t rIndex)
{
  mReactions[rIndex].fire();

  // Update all values needed to calculate dependent propensities.
  mpContainer->applyUpdateSequence(mUpdateSequences[rIndex]);

  return;
}

/**
 *
 *
 */

size_t CHybridMethodODE45::getReactionIndex4Hybrid()
{
  //calculate sum of amu
  C_FLOAT64 mAmuSum = 0.0;

  for (int i = 0; i < mNumReactions; i++)
    {
      if (mReactionFlags[i] == SLOW)
        mAmuSum += mAmu[i];
    }

  //get the threshold
  C_FLOAT64 rand2 = mpRandomGenerator->getRandomOO();
  C_FLOAT64 threshold = mAmuSum * rand2;

  //get the reaction index
  size_t rIndex;
  C_FLOAT64 tmp = 0.0;

  //is there some algorithm that can get a log() complex?
  for (rIndex = 0; rIndex < mNumReactions; rIndex++)
    {
      if (mReactionFlags[rIndex] == SLOW)
        {
          tmp += mAmu[rIndex];

          if (tmp >= threshold)
            return rIndex;
        }
    }
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
      //  for (j=0; i<metabSize; j++)
      for (j = 0; j < mStoi.numRows(); j++)
        {
          multFloat = mStoi[j][i];
          multInt = static_cast<C_INT32>(floor(multFloat + 0.5)); // +0.5 to get a rounding out of the static_cast to int!

          if ((multFloat - multInt) > INT_EPSILON) return - 3; // INT_EPSILON in CHybridMethod.h
        }
    }

  return 1; // Model is appropriate for hybrid simulation
}

/**
 *   Prints out various data on standard output for debugging purposes.
 */
void CHybridMethodODE45::outputDebug(std::ostream & os, size_t level)
{
  size_t i, j;
  std::set< size_t >::iterator iter, iterEnd;

  os << "outputDebug(" << level << ") *********************************************** BEGIN" << std::endl;

  switch (level)
    {
      case 0:                              // Everything !!!
        os << " Name: " << CCopasiParameter::getObjectName() << std::endl;
        os << "current time: " << *mpContainerStateTime << std::endl;
        os << "mNumVariableMetabs: " << mNumReactionSpecies << std::endl;
        os << "mMaxSteps: " << mMaxSteps << std::endl;
        os << "mMaxBalance: " << mMaxBalance << std::endl;
        //os << "mMaxIntBeforeStep: " << mMaxIntBeforeStep << std::endl;
        os << "mReactions.size(): " << mReactions.size() << std::endl;

        for (i = 0; i < mReactions.size(); i++)
          os << *mReactions[i].getModelReaction() << std::endl;

        os << "mpMetabolites.size(): " << mNumReactionSpecies << std::endl;

        {
          const CMathObject * pSpecies = static_cast< const CMathObject * >(mpFirstSpecies);

          for (i = 0; i < mNumReactionSpecies; i++, ++pSpecies)
            os << *static_cast< CMetab * >(pSpecies->getDataObject()->getObjectParent()) << std::endl;
        }

        os << "mReactionFlags: " << std::endl;

        for (i = 0; i < mLocalBalances.size(); i++)
          os << mReactionFlags[i];

        //os << "mFirstReactionFlag: " << std::endl;
        // if (mFirstReactionFlag == NULL) os << "NULL" << std::endl; else os << *mFirstReactionFlag;

        os << "mMetabFlags: " << std::endl;

        for (i = 0; i < mMetabFlags.size(); i++)
          {
            if (mMetabFlags[i].mFlag == SLOW)
              os << "SLOW ";
            else
              os << "FAST ";
          }

        os << std::endl;
        os << "mLocalBalances: " << std::endl;

        /*
                for (i = 0; i < mLocalBalances.size(); i++)
                  {
                    for (j = 0; j < mLocalBalances[i].size(); j++)
                      os << mLocalBalances[i][j];

                    os << std::endl;
                  }

                os << "mLocalSubstrates: " << std::endl;

                for (i = 0; i < mLocalSubstrates.size(); i++)
                  {
                    for (j = 0; j < mLocalSubstrates[i].size(); j++)
                      os << mLocalSubstrates[i][j];

                    os << std::endl;
                  }
         */
        //os << "mLowerStochLimit: " << mLowerStochLimit << std::endl;
        //os << "mUpperStochLimit: " << mUpperStochLimit << std::endl;
        //deprecated:      os << "mOutputCounter: " << mOutputCounter << endl;
        //os << "mPartitioningInterval: " << mPartitioningInterval << std::endl;
        //os << "mStepsAfterPartitionSystem: " << mStepsAfterPartitionSystem << std::endl;
        //os << "mStepsize: " << mStepsize << std::endl;
        os << "mMetab2React: " << std::endl;

        for (i = 0; i < mMetab2React.size(); i++)
          {
            os << i << ": ";

            for (iter = mMetab2React[i].begin(), iterEnd = mMetab2React[i].end(); iter != iterEnd; ++iter)
              os << *iter << " ";

            os << std::endl;
          }

        os << "mAmu: " << std::endl;

        os << "mAmu: " << std::endl;

        for (i = 0; i < mReactions.size(); i++)
          os << mAmu[i] << " ";

        os << std::endl;
        os << "mAmuOld: " << std::endl;

        for (i = 0; i < mReactions.size(); i++)
          os << mAmuOld[i] << " ";

        os << std::endl;
        os << "mpRandomGenerator: " << mpRandomGenerator << std::endl;
        os << "mDG: " << std::endl << mDG;
        os << "mPQ: " << std::endl << mPQ;
        os << "Particle numbers: " << std::endl;

        {
          const C_FLOAT64 * pSpeciesValue = mpFirstSpeciesValue;

          for (i = 0; i < mNumReactionSpecies; i++, ++pSpeciesValue)
            {
              os << *pSpeciesValue << " ";
            }
        }

        os << std::endl;
        break;

      case 1:                               // Variable values only
        os << "current time: " << *mpContainerStateTime << std::endl;
        /*
          case 1:
          os << "mTime: " << mpCurrentState->getTime() << std::endl;
          os << "oldState: ";
          for (i = 0; i < mDim i++)
            os << oldState[i] << " ";
          os << std::endl;
          os << "x: ";
          for (i = 0; i < mDim; i++)
            os << x[i] << " ";
          os << std::endl;
          os << "y: ";
          for (i = 0; i < mDim; i++)
            os << y[i] << " ";
          os << std::endl;
          os << "increment: ";
          for (i = 0; i < mDim; i++)
            os << increment[i] << " ";
          os << std::endl;*/

        os << "mReactionFlags: " << std::endl;

        for (i = 0; i < mLocalBalances.size(); i++)
          os << mReactionFlags[i];

        // os << "mFirstReactionFlag: " << std::endl;
        //if (mFirstReactionFlag == NULL) os << "NULL" << std::endl; else os << *mFirstReactionFlag;

        os << "mMetabFlags: " << std::endl;

        for (i = 0; i < mMetabFlags.size(); i++)
          {
            if (mMetabFlags[i].mFlag == SLOW)
              os << "SLOW ";
            else
              os << "FAST ";
          }

        os << std::endl;
        os << "mAmu: " << std::endl;

        for (i = 0; i < mReactions.size(); i++)
          os << mAmu[i] << " ";

        os << std::endl;
        os << "mAmuOld: " << std::endl;

        for (i = 0; i < mReactions.size(); i++)
          os << mAmuOld[i] << " ";

        os << std::endl;
        os << "mPQ: " << std::endl << mPQ;
        os << "Particle numbers: " << std::endl;

        {
          const C_FLOAT64 * pSpeciesValue = mpFirstSpeciesValue;

          for (i = 0; i < mNumReactionSpecies; i++, ++pSpeciesValue)
            {
              os << *pSpeciesValue << " ";
            }
        }

        os << std::endl;
        break;

      case 2:
        break;

      default:
        ;
    }

  os << "outputDebug(" << level << ") ************************************************* END" << std::endl;
  return;
}

/**
 *   Prints out data on standard output. Deprecated.
 */
void CHybridMethodODE45::outputData()
{
  std::cout << "============Boolean============" << std::endl;

  /*
  if (mReducedModel)
    std::cout << "mReducedModel: Yes" << std::endl;
  else
    std::cout << "mReducedModel: No" << std::endl;
   */

  std::cout << std::endl;

  std::cout << "============Metab============" << std::endl;

  std::cout << "~~~~mNumVariableMetabs:~~~~ " << mNumReactionSpecies << std::endl;
  std::cout << "~~~~mFirstMetabIndex:~~~~ " << mpFirstSpeciesValue - mContainerState.array() << std::endl;
  std::cout << "~~~~mpMetabolites:~~~~" << std::endl;
  {
    const CMathObject * pSpecies = static_cast< const CMathObject * >(mpFirstSpecies);

    for (size_t i = 0; i < mNumReactionSpecies; i++, ++pSpecies)
      {
        CMetab * pMetab = static_cast< CMetab * >(pSpecies->getDataObject()->getObjectParent());

        std::cout << "metab #" << i << " name: " << pMetab->getObjectDisplayName() << std::endl;
        std::cout << "value pointer: " << pSpecies << std::endl;
        std::cout << "value: " << *pSpecies << std::endl;
      }
  }
  std::cout << std::endl;

  std::cout << "~~~~mMetabFlags:~~~~ " << std::endl;

  for (size_t i = 0; i < mMetabFlags.size(); ++i)
    {
      std::cout << "metab #" << i << std::endl;
      std::cout << "mFlag: " << mMetabFlags[i].mFlag << std::endl;
      std::cout << "mFastReactions: ";
      std::set<size_t>::iterator it = mMetabFlags[i].mFastReactions.begin();
      std::set<size_t>::iterator endIt = mMetabFlags[i].mFastReactions.end();

      for (; it != endIt; it++)
        std::cout << *it << " ";

      std::cout << std::endl;
    }

  std::cout << std::endl;

  std::cout << "============Reaction============" << std::endl;

  std::cout << "~~~~mNumReactions:~~~~ " << mNumReactions << std::endl;

  for (size_t i = 0; i < mNumReactions; ++i)
    {
      std::cout << "Reaction #: " << i << " Flag: " << mReactionFlags[i] << std::endl;
    }

  std::cout << "~~~~mLocalBalances:~~~~ " << std::endl;

  for (size_t i = 0; i < mLocalBalances.size(); ++i)
    {
      std::cout << "Reaction: " << i << std::endl;

      for (size_t j = 0; j < mLocalBalances[i].size(); ++j)
        {
          std::cout << "Index: " << mLocalBalances[i][j].mIndex << std::endl;
          std::cout << "mMultiplicity: " << mLocalBalances[i][j].mMultiplicity << std::endl;
          std::cout << "mpMetablite: " << mLocalBalances[i][j].mpMetabolite << std::endl;
        }
    }

  std::cout << "~~~~mLocalSubstrates:~~~~ " << std::endl;

  for (size_t i = 0; i < mLocalSubstrates.size(); ++i)
    {
      std::cout << "Reaction: " << i << std::endl;

      for (size_t j = 0; j < mLocalSubstrates[i].size(); ++j)
        {
          std::cout << "Index: " << mLocalSubstrates[i][j].mIndex << std::endl;
          std::cout << "mMultiplicity: " << mLocalSubstrates[i][j].mMultiplicity << std::endl;
          std::cout << "mpMetablite: " << mLocalSubstrates[i][j].mpMetabolite << std::endl;
        }
    }

  std::cout << "~~~~mMetab2React:~~~~ " << std::endl;

  for (size_t i = 0; i < mMetab2React.size(); i++)
    {
      std::cout << "metab #: " << i << std::endl;
      std::set<size_t>::iterator it = mMetab2React[i].begin();
      std::set<size_t>::iterator endIt = mMetab2React[i].end();
      std::cout << "React: ";

      for (; it != endIt; it++)
        std::cout << *it << " ";

      std::cout << std::endl;
    }

  std::cout << std::endl;
  std::cout << "~~~~mReactAffect:~~~~ " << std::endl;

  for (size_t i = 0; i < mReactAffect.size(); i++)
    {
      std::cout << "react #: " << i << std::endl;
      std::set<size_t>::iterator it = mReactAffect[i].begin();
      std::set<size_t>::iterator endIt = mReactAffect[i].end();
      std::cout << "affect: ";

      for (; it != endIt; it++)
        std::cout << *it << " ";

      std::cout << std::endl;
    }

  if (mHasStoiReaction)
    std::cout << "mHasStoiReaction: Yes" << std::endl;
  else
    std::cout << "mHasStoiReaction: No" << std::endl;

  if (mHasDetermReaction)
    std::cout << "mHasDetermReaction: Yes" << std::endl;
  else
    std::cout << "mHasDetermReaction: No" << std::endl;

  getchar();
  return;
}
