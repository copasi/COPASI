// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
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

#include "CHybridMethodODE45.h"
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

#include "CExpRKMethod.h"


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
  //Now, under the condition of using statistic partition given by users,
  //we won't adopt such parameters listed here.
  assertParameter("Max Internal Steps", CCopasiParameter::UINT, (unsigned C_INT32) MAX_STEPS);
  //assertParameter("Lower Limit", CCopasiParameter::DOUBLE, (C_FAT64) LOWER_STOCH_LIMIT);
  //assertParameter("Upper Limit", CCopasiParameter::DOUBLE, (C_FLOAT64) UPPER_STOCH_LIMIT);

  //assertParameter("Partitioning Interval", CCopasiParameter::UINT, (unsigned C_INT32) PARTITIONING_INTERVAL);
  //-----------------------------------------------------------------------

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

  //????????????????????????????????????????????????????????
  // These parameters are no longer supported.
  //removeParameter("Adams Max Order");
  //removeParameter("BDF Max Order");
  //????????????????????????????????????????????????????????
}

void CHybridMethodODE45::start(const CState * initialState)
{

  //set inital state
  mpProblem->getModel()->setState(*initialState);

  //set mpState
  mpState = new CState(mpProblem->getModel()->getState());

  //set the mpModel
  mpModel = mpProblem->getModel();
  assert(mpModel);

  //set mDoCorrection
  if (mpModel->getModelType() == CModel::deterministic)
    mDoCorrection = true;
  else
    mDoCorrection = false;

  //set mHasAssignments
  mHasAssignments = modelHasAssignments(mpModel);

  //set mFirstMetabIndex
  mFirstMetabIndex = mpModel->getStateTemplate().getIndex(mpModel->getMetabolitesX()[0]);

  // Call initMethod function
  initMethod(mpProblem->getModel()->getTime());

  //output data to check init status
  //outputData();
  return;
}

/**
 *  Initializes the solver and sets the model to be used.
 *  @param model A reference to an instance of a CModel
 */
void CHybridMethodODE45::initMethod(C_FLOAT64 start_time)
{
  //(1)----set attributes related with REACTIONS
  mpReactions   = &mpModel->getReactions();
  mNumReactions = mpReactions->size();

  mAmu.resize(mNumReactions);
  mAmuOld.resize(mNumReactions);

  setupReactionFlags();

  //(2)----set attributes related with METABS
  mpMetabolites = &(const_cast < CCopasiVector < CMetab > & >(mpModel->getMetabolitesX()));

  mNumVariableMetabs = mpModel->getNumIndependentReactionMetabs()
                       + mpModel->getNumDependentReactionMetabs();

  setupBalances();    //initialize mLocalBalances and mLocalSubstrates
  setupMetab2React(); //initialize mMetab2React
  setupMetabFlags();

  //(3)----set attributes related with STATE
  temp.resize(mNumVariableMetabs + 1);

  //(4)----set attributes related with SYSTEM
  mTimeRecord = start_time;
  mMaxSteps = * getValue("Max Internal Steps").pUINT;
  mMaxStepsReached = false;
  setupMethod();

  //(5)----set attributes related with STOCHASTIC
  mUseRandomSeed = * getValue("Use Random Seed").pBOOL;
  mRandomSeed    = * getValue("Random Seed").pUINT;

  if (mUseRandomSeed)
    mpRandomGenerator->initialize(mRandomSeed);

  //mStoi = mpModel->getStoiReordered();
  mStoi = mpModel->getStoi();
  mUpdateSet.clear();// how to set this parameter
  setupCalculateSet(); //should be done after setupBalances()
  setupReactAffect();

  setupDependencyGraph(); // initialize mDG
  setupPriorityQueue(start_time); // initialize mPQ

  //(6)----set attributes for ODE45
  mODE45.mODEState = ODE_INIT;

  mData.dim = (C_INT)(mNumVariableMetabs + 1);  //one more for sum of propensities
  mODE45.mDim = &mData.dim;

  //mYdot.resize(mData.dim);
  mDefaultAtolValue = 1e-9;
  mODE45.mRelTol = * getValue("Relative Tolerance").pUDOUBLE;
  mDefaultAtol   = * getValue("Use Default Absolute Tolerance").pBOOL;

  if (mDefaultAtol)
    {
      std::cout << "mDefaultAtol" << std::endl;
      mODE45.mAbsTol = getDefaultAtol(mpProblem->getModel());
      setValue("Absolute Tolerance", mODE45.mAbsTol);
    }
  else
    mODE45.mAbsTol = * getValue("Absolute Tolerance").pUDOUBLE;

  std::cout << "atol " << mODE45.mAbsTol << std::endl;
  std::cout << "rtol " << mODE45.mRelTol << std::endl;

  mODE45.mHybrid = true;
  mODE45.mStatis = false;

  //setupUpdateSet();

  // we don't want to directly record new results into mpState, since
  // the sum of slow reaction propensities is also recorded in mY
  mY    = new C_FLOAT64[mData.dim];
  mODE45.mY = mY;

  mODE45.mDerivFunc = &CHybridMethodODE45::EvalF;

  //first calculate propensities, in the next integration process
  //system will just update the propensities record in mCalculateSet
  for (size_t i = 0; i < mNumReactions; i++)
    calculateAmu(i);

  //(7)----set attributes for Event Roots
  mRootNum = mpModel->getNumRoots();
  mRoots.resize(mRootNum);
  mODE45.mRootNum = mRootNum;

  //clear mRootQueue
  std::queue<SRoot> empty;
  std::swap(mRootQueue, empty);

  if(mRootNum > 0)
    {
      mODE45.mEventFunc = &CHybridMethodODE45::EvalR;
      mpRT        = new C_FLOAT64[mRootNum];
      mOldRoot    = new C_FLOAT64[mRootNum];
      mpRootValue = new CVectorCore< C_FLOAT64 >(mRootNum, mpRT);
      
      mpModel->evaluateRoots(*mpRootValue, true);
      for (int i = 0; i<mRootNum; i++)
	mOldRoot[i] = (mpRootValue->array())[i];
    }
  else
    {
      mODE45.mEventFunc = NULL;
      mpRT        = NULL;
      mOldRoot    = NULL;
      mpRootValue = NULL;
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
  mpModel = NULL;

  //  delete mpState;
  //  mpState = NULL;

  delete [] mY;
  mY = NULL;

  //  delete [] mRootTime;

  delete [] mpRT;
  delete [] mOldRoot;
  delete mpRootValue;
  mpRootValue = NULL;

  return;
}

//================Function for Model================
void CHybridMethodODE45::setupMetabFlags()
{
  size_t rctIndex;
  mMetabFlags.resize(mNumVariableMetabs);

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
      if ((*mpReactions)[rct]->isFast())
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
  else if(!mHasStoiReaction && mHasDetermReaction)
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
  size_t maxBalance = 0;

  mLocalBalances.clear();
  mLocalBalances.resize(mNumReactions);
  mLocalSubstrates.clear();
  mLocalSubstrates.resize(mNumReactions);

  for (i = 0; i < mNumReactions; i++)
    {
      const CCopasiVector <CChemEqElement> * balances =
        &(*mpReactions)[i]->getChemEq().getBalances();

      for (j = 0; j < balances->size(); j++)
        {
          newElement.mpMetabolite = const_cast < CMetab* >((*balances)[j]->getMetabolite());
          newElement.mIndex = mpModel->getMetabolitesX().getIndex(newElement.mpMetabolite);
          // + 0.5 to get a rounding out of the static_cast to C_INT32!
          newElement.mMultiplicity = static_cast<C_INT32>(floor((*balances)[j]->getMultiplicity()
                                     + 0.5));

          if ((newElement.mpMetabolite->getStatus()) != CModelEntity::FIXED)
            {
              if (newElement.mMultiplicity > maxBalance) maxBalance = newElement.mMultiplicity;

              mLocalBalances[i].push_back(newElement); // element is copied for the push_back
            }
        }

      balances = &(*mpReactions)[i]->getChemEq().getSubstrates();

      for (j = 0; j < balances->size(); j++)
        {
          newElement.mpMetabolite = const_cast < CMetab* >((*balances)[j]->getMetabolite());
          newElement.mIndex = mpModel->getMetabolitesX().getIndex(newElement.mpMetabolite);
          // + 0.5 to get a rounding out of the static_cast to C_INT32!
          newElement.mMultiplicity = static_cast<C_INT32>(floor((*balances)[j]->getMultiplicity()
                                     + 0.5));

          mLocalSubstrates[i].push_back(newElement); // element is copied for the push_back
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
  mMetab2React.clear();
  mMetab2React.resize(mNumVariableMetabs);

  CMetab * pMetab;
  CReaction * pReaction;

  //Check wether metabs play as substrates and modifiers
  for (size_t rct = 0; rct < mNumReactions; ++rct)
    {
      size_t index;
      
      //deal with substrates
      CCopasiVector <CChemEqElement> metab =
        (*mpReactions)[rct]->getChemEq().getSubstrates();

      for (size_t i = 0; i < metab.size(); i++)
        {
          pMetab = const_cast < CMetab* >
                    (metab[i]->getMetabolite());
          index = mpModel->getMetabolitesX().getIndex(pMetab);

          if ((pMetab->getStatus()) != CModelEntity::FIXED)
            mMetab2React[index].insert(rct);
        }

      //deal with modifiers
      metab = (*mpReactions)[rct]->getChemEq().getModifiers();

      for (size_t i = 0; i < metab.size(); i++)
        {
          pMetab = const_cast < CMetab* >
                    (metab[i]->getMetabolite());
          index = mpModel->getMetabolitesX().getIndex(pMetab);

          if ((pMetab->getStatus()) != CModelEntity::FIXED)
            mMetab2React[index].insert(rct);
	}
    }
   
  //Check wether metabs appear in reaction laws
  std::set< const CCopasiObject * > changed;
  for (size_t metab=0; metab<mNumVariableMetabs; metab++)
    {
      pMetab = (*mpMetabolites)[metab];
     
      if (pMetab->getStatus() != CModelEntity::FIXED)
	{
	  changed.clear();
	  changed.insert(mpModel->getValueReference());
	  changed.insert(pMetab->getValueReference());

	  for (size_t react=0; react<mNumReactions; react++)
	    {
	      pReaction = (*mpReactions)[react];
	      if(pReaction->getParticleFluxReference()->dependsOn(changed))
		mMetab2React[metab].insert(react);
	    }
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
  C_FLOAT64 time = mpModel->getTime();
  C_FLOAT64 endTime = time + deltaT;

  if (time == mTimeRecord) //new time step
    mTimeRecord = endTime;
  else // continue current step
    endTime = mTimeRecord;

  for (i = 0; ((i < mMaxSteps) && (time < endTime)); i++)
    {
      time = doSingleStep(time, endTime);
      if (mSysStatus == SYS_EVENT)
	{
	  mpState->setTime(time);
	  *mpCurrentState = *mpState;
	  return ROOT;
	}
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
  mpState->setTime(time);
  *mpCurrentState = *mpState;
  //mpCurrentState->setTime(time);

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
  if(mMethod == STOCHASTIC) //(1)----Pure SSA Method
    {
      SRoot root;
      if(mSysStatus == SYS_NEW)
	{ 
	  //First Call SSA or Switch to SSA, 
	  //Calculate Roots
	  mSysStatus = SYS_CONT;

	  //Check Events at Current Time
	  mpModel->evaluateRoots(*mpRootValue, true);
	  for(size_t id=0; id<mRootNum; id++)
	    {
	      if((mpRootValue->array())[id] == 0.0)
		{
		  root.id = id;
		  root.t  = currentTime;
		  mRootQueue.push(root);
		}
	    }
	}

      //first check mRootQueue
      if(!mRootQueue.empty())
	{
	  mSysStatus = SYS_EVENT;

	  root = mRootQueue.front();
	  mRootQueue.pop();

	  setRoot(root.id);
	  return root.t;
	}
      else //copy root to mOldRoot
	{
	  for(size_t i=0; i<mRootNum; i++)
	    mOldRoot[i] = (mpRootValue->array())[i];
	}

      //Go one step
      bool fire = false;
      getStochTimeAndIndex(ds, rIndex);
      if(ds > endTime)
	  ds = endTime;
      else
	{
	  fire = true;
	  fireReaction(rIndex);
	  updatePriorityQueue(rIndex, ds);
	}

      //Record state
      *mpState = mpModel->getState();
      mpState->setTime(ds);
      mpModel->setState(*mpState);

      //Check roots
      mSysStatus = SYS_CONT;
      if(fire)
	{
	  mpModel->evaluateRoots(*mpRootValue, true);
	  for(size_t id=0; id<mRootNum; id++)
	    {
	      if( (mOldRoot[id]*(mpRootValue->array())[id]<0.0) || 
		  ((mpRootValue->array())[id]==0.0) )
		{
		  root.t  = ds;
		  root.id = id;
		  mRootQueue.push(root);
		}
	    }

	  if(!mRootQueue.empty())
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
      if(mSysStatus == SYS_EVENT) //only deal with system roots
	{
	  if(mHasSlow)// slow reaction fires
	    {
	      //what about the states of model
	      fireSlowReaction4Hybrid();
	      stateChanged(); //SYS_EVENT->SYS_NEW
	    }
	  
	  if(mHasRoot) // system roots
	      setRoot(mODE45.mRootId);
	}
      else if(mSysStatus == SYS_END)//finish this step
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
  *mpState = *mpCurrentState;
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
  *mpState = mpModel->getState();

  //update corresponding propensities
  std::set <size_t>::iterator updateIt
    = mReactAffect[reactID].begin();
  const std::set <size_t>::iterator updateEndIt
    = mReactAffect[reactID].end();

  for (; updateIt != updateEndIt; updateIt++)
    {
      reactID = *updateIt;
      calculateAmu(reactID);
    }

  return;
}


//========Function for ODE45========
C_FLOAT64 CHybridMethodODE45::getDefaultAtol(const CModel * pModel) const
{
  if (!pModel)
    return mDefaultAtolValue;

  const CCopasiVectorNS< CCompartment > & Compartment =
    pModel->getCompartments();

  size_t i, imax;

  C_FLOAT64 Volume = std::numeric_limits< C_FLOAT64 >::max();

  for (i = 0, imax = Compartment.size(); i < imax; i++)
    {
      if (Compartment[i]->getValue() < Volume)
        Volume = Compartment[i]->getValue();
    }

  if (Volume == std::numeric_limits< C_FLOAT64 >::max())
    return mDefaultAtolValue;

  return std::min(1.e-3, std::max(mDefaultAtolValue, 1.0/(pModel->getQuantity2NumberFactor())));
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

  //=(2)= set state
  *mpState = mpModel->getState();

  //=(3)= set time and old time
  mODE45.mT    = mpState->getTime();
  mODE45.mTEnd = mODE45.mT + deltaT;

  //=(4)= set y and ode status
  if(mSysStatus = SYS_NEW)
    {
      //only when starts a new step, we should copy state into ode solver
      C_FLOAT64 * stateY = mpState->beginIndependent();
      for (size_t i = 0; i < mData.dim - 1; i++, stateY++)
	mY[i] = *stateY;
      
      mY[mData.dim-1] = log(mpRandomGenerator->getRandomOO());

      /*
      if(!mODE45.initialized())
	mODE45.mODEState = ODE_INIT;
      else
	mODE45.mODEState = ODE_NEW;
      */
      if(mODE45.mODEState != ODE_INIT)
	mODE45.mODEState = ODE_NEW;

    }
  else if(mSysStatus = SYS_EVENT)
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
      mpModel->setTime(mODE45.mTEnd);
      return;
    }

  //4----just do nothing if there are no variables
  if (!mData.dim)
    {
      mODE45.mT = mODE45.mTEnd;
      mSysStatus = SYS_END;
      mpModel->setTime(mODE45.mTEnd);
      return;
    }

  //5----do interpolation
  mODE45.integrate();

  //6----check status
  if(mODE45.mODEState == ODE_ERR)
    {
      mSysStatus = SYS_ERR;
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 6, mErrorMsg.str().c_str());
    }
  else if(mODE45.mODEState == ODE_EVENT)
    {
      mHasSlow = false;
      mHasRoot = false;
      if(mODE45.mRootId == SLOW_REACT)
	mHasSlow = true;
      else
	mHasRoot = true;

      mSysStatus = SYS_EVENT;
    }
  else
    mSysStatus = SYS_END;

  //7----Record State
  C_FLOAT64 *stateY = mpState->beginIndependent();
  for (size_t i = 0; i < mData.dim-1; i++)
    stateY[i] = mY[i]; //write result into mpState

  mpState->setTime(mODE45.mT);
  mpModel->setState(*mpState);
  mpModel->updateSimulatedValues(false); //for assignments?????????

  return;
}

/**
 * Function that sets (mRoot.array())[id]=1
 */
void CHybridMethodODE45::setRoot(const size_t id)
{
  for(size_t i=0; i<mRootNum; i++)
    (mRoots.array())[i] = 0;
  (mRoots.array())[id]= 1;
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
  mpState->setTime(*t);
  C_FLOAT64 * tmpY = mpState->beginIndependent();//mpState is a local copy

  for (i = 0; i < mData.dim-1; ++i)
    tmpY[i] = y[i];

  mpModel->setState(*mpState);
  mpModel->updateSimulatedValues(false); //really?

  //(2)Calculate propensities.
  std::set <size_t>::iterator reactIt = mCalculateSet.begin();
  size_t reactID;

  for (; reactIt != mCalculateSet.end(); reactIt++)
    {
      reactID = *reactIt;
      calculateAmu(reactID);
    }

  //2====calculate derivative
  //(1)initialize
  for (i = 0; i < mData.dim; i++)
    ydot[i] = 0.0;

  //(2)go through all the reactions and
  //update derivatives
  std::vector <CHybridODE45Balance>::iterator metabIt;
  std::vector <CHybridODE45Balance>::iterator metabEndIt;
  size_t metabIndex;

  for (i = 0; i < mNumReactions; i++)
    {
      if (mReactionFlags[i] == SLOW) //slow reaction
        ydot[mData.dim-1] += mAmu[i];
      else //fast reaction
        {
          metabIt    = mLocalBalances[i].begin();
          metabEndIt = mLocalBalances[i].end();

          for (; metabIt != metabEndIt; metabIt++)
            {
              metabIndex = metabIt->mIndex;
              ydot[metabIndex] += metabIt->mMultiplicity * mAmu[i];
            }
        }
    }

  return;
}


void CHybridMethodODE45::evalR(const C_FLOAT64 *t, const C_FLOAT64 *y,
			       const size_t *nr, C_FLOAT64 *r)
{
  assert(*nr == (C_INT)mRoots.size());
  //assert(r == (C_FLOAT64*)mpRT);

  mpState->setTime(*t);
  mpModel->setState(*mpState);
  
  //if(*mpReduceModel)
  //    mpModel->updateSimulatedValues(*mpReducedModel);
  CVectorCore< C_FLOAT64 > rootValues(*nr, r);
  mpModel->evaluateRoots(rootValues, true);

  /*
    if(mRootMasking != NONE)
      maskRoots(rootValues);
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
  if (!mDoCorrection)
    {
      mAmu[rIndex] = (*mpReactions)[rIndex]->calculateParticleFlux();
      return;
    }

  // We need the product of the cmu and hmu for this step.
  // We calculate this in one go, as there are fewer steps to
  // perform and we eliminate some possible rounding errors.
  C_FLOAT64 amu = 1; // initially
  //size_t total_substrates = 0;
  C_INT32 num_ident = 0;
  C_INT32 number = 0;
  C_INT32 lower_bound;
  // substrate_factor - The substrates, raised to their multiplicities,
  // multiplied with one another. If there are, e.g. m substrates of type m,
  // and n of type N, then substrate_factor = M^m * N^n.
  C_FLOAT64 substrate_factor = 1;
  // First, find the reaction associated with this index.
  // Keep a pointer to this.
  // Iterate through each substrate in the reaction
  const std::vector<CHybridODE45Balance> & substrates = mLocalSubstrates[rIndex];

  int flag = 0;

  for (size_t i = 0; i < substrates.size(); i++)
    {
      num_ident = substrates[i].mMultiplicity;

      if (num_ident > 1)
        {
          flag = 1;
          number = static_cast<C_INT32>((*mpMetabolites)[substrates[i].mIndex]->getValue());
          lower_bound = number - num_ident;
          substrate_factor = substrate_factor
                             * pow((double) number, (int) num_ident - 1); //optimization

          number--; // optimization

          while (number > lower_bound)
            {
              amu *= number;
              number--;
            }
        }
    }

  if ((amu == 0) || (substrate_factor == 0))  // at least one substrate particle number is zero
    {
      mAmu[rIndex] = 0;
      return;
    }

  // rate_factor is the rate function divided by substrate_factor.
  // It would be more efficient if this was generated directly, since in effect we
  // are multiplying and then dividing by the same thing (substrate_factor)!
  C_FLOAT64 rate_factor = (*mpReactions)[rIndex]->calculateParticleFlux();

  if (flag)
    {
      amu *= rate_factor / substrate_factor;;
      mAmu[rIndex] = amu;
    }
  else
    {
      mAmu[rIndex] = rate_factor;
    }

  return;

  // a more efficient way to calculate mass action kinetics could be included
}

/**
 *   Gets the set of metabolites on which a given reaction depends.
 *
 *   @param rIndex The index of the reaction being executed.
 *   @return The set of metabolites depended on.
 */
std::set<std::string> *CHybridMethodODE45::getDependsOn(size_t rIndex)
{
  std::set<std::string> *retset = new std::set<std::string>;

  size_t i, imax = (*mpReactions)[rIndex]->getFunctionParameters().size();
  size_t j, jmax;

  for (i = 0; i < imax; ++i)
    {
      if ((*mpReactions)[rIndex]->getFunctionParameters()[i]->getUsage()
          == CFunctionParameter::PARAMETER)
        continue;

      const std::vector <std::string> & metabKeylist =
        (*mpReactions)[rIndex]->getParameterMappings()[i];
      jmax = metabKeylist.size();

      for (j = 0; j < jmax; ++j)
        retset->insert(metabKeylist[j]);
    }

  return retset;
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
  std::vector< std::set<std::string>* > DependsOn;
  std::vector< std::set<std::string>* > Affects;
  size_t numReactions = mpReactions->size();
  size_t i, j;

  // Do for each reaction:
  for (i = 0; i < mNumReactions; i++)
    {
      // Get the set of metabolites  which affect the value of amu for this
      // reaction i.e. the set on which amu depends. This may be  more than
      // the set of substrates, since the kinetics can involve other
      // reactants, e.g. catalysts. We thus need to step through the
      // rate function and pick out every reactant which can vary.
      DependsOn.push_back(getDependsOn(i));
      // Get the set of metabolites which are affected when this reaction takes place
      Affects.push_back(getAffects(i));
    }

  // For each possible pair of reactions i and j, if the intersection of
  // Affects(i) with DependsOn(j) is non-empty, add a dependency edge from i to j.
  for (i = 0; i < mNumReactions; i++)
    {
      for (j = 0; j < mNumReactions; j++)
        {
          // Determine whether the intersection of these two sets is non-empty
          // Could also do this with set_intersection generic algorithm, but that
          // would require operator<() to be defined on the set elements.

          std::set<std::string>::iterator iter = Affects[i]->begin();

          for (; iter != Affects[i]->end(); iter++)
            {
              if (DependsOn[j]->count(*iter))
                {
                  // The set intersection is non-empty
                  mDG.addDependent(i, j);
                  break;
                }
            }
        }

      // Ensure that self edges are included
      //mDG.addDependent(i, i);
    }

  // Delete the memory allocated in getDependsOn() and getAffects()
  // since this is allocated in other functions.
  for (i = 0; i < numReactions; i++)
    {
      delete DependsOn[i];
      delete Affects[i];
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
  size_t index;
  std::set <size_t>::iterator iter, iterEnd;

  //if the model contains assignments we use a less efficient loop over all (stochastic) 
  //reactions to capture all changes
  //we do not know the exact dependencies.
  //TODO: this should be changed later in order to get a more efficient update scheme
  if (mHasAssignments)
    {
      mpModel->updateSimulatedValues(false);

      for (index = 0; index < mNumReactions; index++)
        {
	  mAmuOld[index] = mAmu[index];
	  calculateAmu(index);

	  if (mAmuOld[index] != mAmu[index])
	    if (index != rIndex) updateTauMu(index, time);
        }
    }
  else
    {
      // iterate through the set of affected reactions and update the stochastic
      // ones in the priority queue
      iter = mReactAffect[rIndex].begin();
      iterEnd = mReactAffect[rIndex].end();
      for (; iter != iterEnd; iter++)
        {
	  index = *iter;
	  mAmuOld[index] = mAmu[index];
	  calculateAmu(index);

	  if (*iter != rIndex) updateTauMu(index, time);
        }
    }

  // draw new random number and update the reaction just fired
  if (rIndex != C_INVALID_INDEX)
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
  // Change the particle numbers according to which step took place.
  // First, get the vector of balances in the reaction we've got.
  // (This vector expresses the number change of each metabolite
  // in the reaction.) Then step through each balance, using its
  // multiplicity to calculate a new value for the associated
  // metabolite. Finally, update the metabolite.

  size_t i;
  C_FLOAT64 newNumber;

  CMetab * pMetab;

  for (i = 0; i < mLocalBalances[rIndex].size(); i++)
    {
      pMetab = mLocalBalances[rIndex][i].mpMetabolite;
      newNumber = pMetab->getValue() + mLocalBalances[rIndex][i].mMultiplicity;

      pMetab->setValue(newNumber);
      pMetab->refreshConcentration();
    }

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
        os << "current time: " << mpCurrentState->getTime() << std::endl;
        os << "mNumVariableMetabs: " << mNumVariableMetabs << std::endl;
        os << "mMaxSteps: " << mMaxSteps << std::endl;
        os << "mMaxBalance: " << mMaxBalance << std::endl;
        //os << "mMaxIntBeforeStep: " << mMaxIntBeforeStep << std::endl;
        os << "mpReactions.size(): " << mpReactions->size() << std::endl;

        for (i = 0; i < mpReactions->size(); i++)
          os << *(*mpReactions)[i] << std::endl;

        os << "mpMetabolites.size(): " << mpMetabolites->size() << std::endl;

        for (i = 0; i < mpMetabolites->size(); i++)
          os << *(*mpMetabolites)[i] << std::endl;

        os << "mStoi: " << std::endl;

        for (i = 0; i < mStoi.numRows(); i++)
          {
            for (j = 0; j < mStoi.numCols(); j++)
              os << mStoi[i][j] << " ";

            os << std::endl;
          }

        os << "temp: ";

        for (i = 0; i < mNumVariableMetabs; i++)
          os << temp[i] << " ";

        os << std::endl;

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

        for (i = 0; i < mpReactions->size(); i++)
          os << mAmu[i] << " ";

        os << std::endl;
        os << "mAmuOld: " << std::endl;

        for (i = 0; i < mpReactions->size(); i++)
          os << mAmuOld[i] << " ";

        os << std::endl;
        os << "mUpdateSet: " << std::endl;

        for (iter = mUpdateSet.begin(), iterEnd = mUpdateSet.end(); iter != iterEnd; iter++)
          os << *iter;

        os << std::endl;
        os << "mpRandomGenerator: " << mpRandomGenerator << std::endl;
        os << "mDG: " << std::endl << mDG;
        os << "mPQ: " << std::endl << mPQ;
        os << "Particle numbers: " << std::endl;

        for (i = 0; i < mpMetabolites->size(); i++)
          {
            os << (*mpMetabolites)[i]->getValue() << " ";
          }

        os << std::endl;
        break;

      case 1:                               // Variable values only
        os << "current time: " << mpCurrentState->getTime() << std::endl;
        /*
        case 1:
        os << "mTime: " << mpCurrentState->getTime() << std::endl;
        os << "oldState: ";
        for (i = 0; i < mDim; i++)
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
        os << "temp: ";

        for (i = 0; i < mNumVariableMetabs; i++)
          os << temp[i] << " ";

        os << std::endl;

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

        for (i = 0; i < mpReactions->size(); i++)
          os << mAmu[i] << " ";

        os << std::endl;
        os << "mAmuOld: " << std::endl;

        for (i = 0; i < mpReactions->size(); i++)
          os << mAmuOld[i] << " ";

        os << std::endl;
        os << "mUpdateSet: " << std::endl;

        for (iter = mUpdateSet.begin(), iterEnd = mUpdateSet.end(); iter != iterEnd; iter++)
          os << *iter;

        os << std::endl;
        os << "mPQ: " << std::endl << mPQ;
        os << "Particle numbers: " << std::endl;

        for (i = 0; i < mpMetabolites->size(); i++)
          {
            os << (*mpMetabolites)[i]->getValue() << " ";
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

  if (mDoCorrection)
    std::cout << "mDoCorrection: Yes" << std::endl;
  else
    std::cout << "mDoCorrection: No" << std::endl;
  /*
  if (mReducedModel)
    std::cout << "mReducedModel: Yes" << std::endl;
  else
    std::cout << "mReducedModel: No" << std::endl;
  */

  std::cout << std::endl;

  std::cout << "============Metab============" << std::endl;

  std::cout << "~~~~mNumVariableMetabs:~~~~ " << mNumVariableMetabs << std::endl;
  std::cout << "~~~~mFirstMetabIndex:~~~~ " << mFirstMetabIndex << std::endl;
  std::cout << "~~~~mpMetabolites:~~~~" << std::endl;
  for (size_t i=0; i<mpMetabolites->size(); i++)
    {
      std::cout << "metab #" << i << " name: " << (*mpMetabolites)[i]->getObjectDisplayName() << std::endl;
      std::cout << "value pointer: " << (*mpMetabolites)[i]->getValuePointer() << std::endl;
      std::cout << "value: " << *((double *)(*mpMetabolites)[i]->getValuePointer()) << std::endl;
    }
  std::cout << std::endl;

  std::cout << "~~~~mMetabFlags:~~~~ " << std::endl;
  for (size_t i=0; i<mMetabFlags.size(); ++i)
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
  for (size_t i=0; i<mNumReactions; ++i)
    {
      std::cout << "Reaction #: " << i << " Flag: " << mReactionFlags[i] << std::endl;
    }
  std::cout << "~~~~mLocalBalances:~~~~ " << std::endl;
  for (size_t i=0; i<mLocalBalances.size(); ++i)
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
  for (size_t i=0; i<mLocalSubstrates.size(); ++i)
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
  for(size_t i=0; i<mMetab2React.size(); i++)
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

/**
 * Print State Data for Debug
 */
void CHybridMethodODE45::outputState(const CState* mpState)
{
  const C_FLOAT64 time = mpState->getTime();
  std::cout << "**State Output**" << std::endl;
  std::cout << "Time: " << time << std::endl;

  std::cout << "Indep #: " << mpState->getNumIndependent() << " Id: ";
  const C_FLOAT64 *pIt = mpState->beginIndependent();
  const C_FLOAT64 *pEnd = mpState->endIndependent();
  for (; pIt != pEnd; pIt++)
    std::cout << *pIt << " ";
  std::cout << std::endl;

  std::cout << "Dep #: " << mpState->getNumDependent() << " Id: ";
  pIt = mpState->beginDependent();
  pEnd = mpState->endDependent();
  for (; pIt != pEnd; pIt++)
    std::cout << *pIt << " ";
  std::cout << std::endl;

  std::cout << "Fix #: " << mpState->getNumIndependent() << " Id: ";
  pIt = mpState->beginFixed();
  pEnd = mpState->endFixed();
  for (; pIt != pEnd; pIt++)
    std::cout << *pIt << " ";
  std::cout << std::endl;

  getchar();
  return;
}

bool CHybridMethodODE45::modelHasAssignments(const CModel* pModel)
{
  size_t i, imax = pModel->getNumModelValues();

  for (i = 0; i < imax; ++i)
    {
      if (pModel->getModelValues()[i]->getStatus() == CModelEntity::ASSIGNMENT)
        if (pModel->getModelValues()[i]->isUsed())
          {
            //used assignment found
            return true;
          }
    }

  imax = pModel->getNumMetabs();

  for (i = 0; i < imax; ++i)
    {
      if (pModel->getMetabolites()[i]->getStatus() == CModelEntity::ASSIGNMENT)
        if (pModel->getMetabolites()[i]->isUsed())
          {
            //used assignment found
            return true;
          }
    }

  imax = pModel->getCompartments().size();

  for (i = 0; i < imax; ++i)
    {
      if (pModel->getCompartments()[i]->getStatus() == CModelEntity::ASSIGNMENT)
        if (pModel->getCompartments()[i]->isUsed())
          {
            //used assignment found
            return true;
          }
    }
  return false;
}
