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

#include "CInterpolation.h"

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

  std::string message = pTP->getModel()->suitableForStochasticSimulation();

  if (message != "")
    {
      //model not suitable, message describes the problem
      CCopasiMessage(CCopasiMessage::ERROR, message.c_str());
      return false;
    }

  //mLowerStochLimit = * getValue("Lower Limit").pDOUBLE;
  //mUpperStochLimit = * getValue("Upper Limit").pDOUBLE;

  //if (mLowerStochLimit > mUpperStochLimit)
  //  CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 4,
  //       mLowerStochLimit, mUpperStochLimit);

  //events are not supported at the moment
  if (pTP->getModel()->getEvents().size() > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 23);
      return false;
    }

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
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e009);

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
  mMaxSteps = * getValue("Max Internal Steps").pUINT;
  mMaxStepsReached = false;
  setupMethod();

  //(5)----set attributes related with STOCHASTIC
  mUseRandomSeed = * getValue("Use Random Seed").pBOOL;
  mRandomSeed = * getValue("Random Seed").pUINT;

  if (mUseRandomSeed)
    mpRandomGenerator->initialize(mRandomSeed);

  mStoi = mpModel->getStoiReordered();
  mUpdateSet.clear();// how to set this parameter
  setupCalculateSet(); //should be done after setupBalances()
  setupReactAffect();

  setupDependencyGraph(); // initialize mDG
  setupPriorityQueue(start_time); // initialize mPQ

  //(6)----set attributes for INTERPOLATION
  mpInterpolation = new CInterpolation(INTERP_RECORD_NUM, mNumVariableMetabs);
  mStateRecord.resize((INTERP_RECORD_NUM - 2) * (2 + mNumVariableMetabs));

  //(7)----set attributes for ODE45
  mODE45Status = NEW_STEP;
  mData.dim = (C_INT)(mNumVariableMetabs + 1);  //one more for sum of propensities
  mYdot.resize(mData.dim);

  mRtol = * getValue("Relative Tolerance").pUDOUBLE;
  mDefaultAtol = * getValue("Use Default Absolute Tolerance").pBOOL;

  if (mDefaultAtol)
    {
      mAtol = getDefaultAtol(mpProblem->getModel());
      setValue("Absolute Tolerance", mAtol);
    }
  else
    mAtol = * getValue("Absolute Tolerance").pUDOUBLE;

  mDWork.resize(3 + 6 * mData.dim);
  mIWork.resize(5);

  //setupUpdateSet();

  // we don't want to directly record new results into mpState, since
  // the sum of slow reaction propensities is also recorded in mY
  mY    = new C_FLOAT64[mData.dim];
  mOldY = new C_FLOAT64[mData.dim];

  //first calculate propensities, in the next integration process
  //system will just update the propensities record in mCalculateSet
  for (size_t i = 0; i < mNumReactions; i++)
    calculateAmu(i);

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

  delete mpState;
  mpState = NULL;

  delete mpInterpolation;
  mpInterpolation = NULL;

  delete [] mY;
  mY = NULL;

  delete [] mOldY;
  mOldY = NULL;

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

  for (size_t rct = 0; rct < mNumReactions; ++rct)
    {
      CMetab *mpMetab;
      size_t index;

      //deal with substrates
      CCopasiVector <CChemEqElement> metab =
        (*mpReactions)[rct]->getChemEq().getSubstrates();

      for (size_t i = 0; i < metab.size(); i++)
        {
          mpMetab = const_cast < CMetab* >
                    (metab[i]->getMetabolite());
          index = mpModel->getMetabolitesX().getIndex(mpMetab);

          if ((mpMetab->getStatus()) != CModelEntity::FIXED)
            mMetab2React[index].insert(rct);
        }

      //deal with modifiers
      metab = (*mpReactions)[rct]->getChemEq().getModifiers();

      for (size_t i = 0; i < metab.size(); i++)
        {
          mpMetab = const_cast < CMetab* >
                    (metab[i]->getMetabolite());
          index = mpModel->getMetabolitesX().getIndex(mpMetab);

          if ((mpMetab->getStatus()) != CModelEntity::FIXED)
            mMetab2React[index].insert(rct);
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

  for (i = 0; ((i < mMaxSteps) && (time < endTime)); i++)
    time = doSingleStep(time, endTime);

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
  C_FLOAT64 ds = 0.0;
  size_t rIndex = 0;

  //1----pure SSA method
  if (mMethod == STOCHASTIC) //has only stochastic reactions
    {
      getStochTimeAndIndex(ds, rIndex);

      if (ds > endTime)
	ds = endTime;
      else
	{
	  fireReaction(rIndex);
	  updatePriorityQueue(rIndex, ds);
	}

      //population has been changed and record to the mCurrentState
      //in fireReaction(). So here just store time
      *mpState = mpModel->getState();
      mpState->setTime(ds);
      mpModel->setState(*mpState);

      //outputState(mpCurrentState);
      //getchar();
    }
  //2----Method with Deterministic Part
  else if (mMethod == DETERMINISTIC) //has only deterministic reactions
    {
      integrateDeterministicPart(endTime - currentTime);
      ds = mpState->getTime();
      mODE45Status = CONTINUE;
      // Till now, state has been recorded
    }
  else if (mMethod == HYBRID)//Hybrid Method
    {
      integrateDeterministicPart(endTime - currentTime);
      ds = mpState->getTime();

      if (mODE45Status == HAS_EVENT) //fire slow reaction
	{
	  doInverseInterpolation();

	  fireSlowReaction4Hybrid();
	  mODE45Status = NEW_STEP;	      
	}
      else 
	mODE45Status = CONTINUE;
    }

  return ds;
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
    return 1.0e009;

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
    return 1.0e009;

  return Volume * pModel->getQuantity2NumberFactor() * 1.e-12;
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
  mTime = mpState->getTime();
  C_FLOAT64 EndTime = mTime + deltaT;

  mOldTime = mTime;

  //=(4)= set y and old_y
  C_FLOAT64 * stateY = mpState->beginIndependent();

  for (size_t i = 0; i < mData.dim - 1; i++, stateY++)
    {
      mOldY[i] = *stateY;
      mY[i]    = *stateY;
    }

  if (mODE45Status == NEW_STEP)
    {
      C_FLOAT64 rand2 = mpRandomGenerator->getRandomOO();
      mY[mData.dim - 1] = log(rand2);
    }

  mOldY[mData.dim - 1] = mY[mData.dim - 1];

  //2----Reset ODE45 Solver
  mIFlag = -1; //integration by one step

  //3----If time increment is too small, do nothing
  C_FLOAT64 tdist , d__1, d__2, w0;
  tdist = fabs(deltaT); //absolute time increment
  d__1 = fabs(mTime), d__2 = fabs(EndTime);
  w0 = std::max(d__1, d__2);

  if (tdist < std::numeric_limits< C_FLOAT64 >::epsilon() * 2. * w0) //just do nothing
    {
      mpModel->setTime(EndTime);
      return;
    }

  //4----just do nothing if there are no variables
  if (!mData.dim)
    {
      mpModel->setTime(EndTime);
      return;
    }

  while((mODE45Status == CONTINUE) 
	|| (mODE45Status == NEW_STEP) )
    {
      //(1)----ODE Solver
      rkf45_(&EvalF ,                 //1. evaluate F
	     &mData.dim,              //2. number of variables
	     mY ,                     //3. the array of current concentrations
	     &mTime ,                 //4. the current time
	     &EndTime ,               //5. the final time
	     &mRtol ,                 //6. relative tolerance array
	     &mAtol ,                 //7. absolute tolerance array
	     &mIFlag ,                //8. the state for input and output
	     mDWork.array() ,         //9. the double work array
	     mIWork.array() ,         //10. the int work array
	     mStateRecord.array());   //11. the array to record temp state

      //(2)----set mODE45Status
      if (mIFlag == 2)
	{
 	  if (mY[mData.dim - 1] >= 0.0)
	    mODE45Status = HAS_EVENT;
	  else
	    mODE45Status = REACH_END_TIME; //reach EndTime
	}
      else if (mIFlag == -2) //finish one step integration
	{
	  if (mY[mData.dim - 1] >= 0.0) //has an event
	    mODE45Status = HAS_EVENT;
	  else
	    mODE45Status = CONTINUE;
	}
      else //error happens
	{
	  mODE45Status = HAS_ERR;
	  std::cout << "Error Type: " << mIFlag << std::endl;
	  CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 6, mErrorMsg.str().c_str());
	}//end if
    }//end while

  //5----Record State
  stateY = mpState->beginIndependent();
  for (size_t i = 0; i < mData.dim-1; i++)
    stateY[i] = mY[i]; //write result into mpState

  mpState->setTime(mTime);
  mpModel->setState(*mpState);
  mpModel->updateSimulatedValues(false); //for assignments?????????

  return;
}

void CHybridMethodODE45::doInverseInterpolation()
{

  //==(1)==for one-step method, reset record each time when do interpolation
  mpInterpolation->recordReset();

  //==(2)==set record in class interpolation
  mpInterpolation->recordState(mOldTime, mOldY);
  size_t offset;

  if (mUseStateRecord)
    {
      for (size_t i = 0; i < INTERP_RECORD_NUM-2; i++) //record the middle 4 states
	{
	  offset = i * (mData.dim + 1);
	  mpInterpolation->recordState(mStateRecord[offset],
				       mStateRecord.array() + offset + 1);
	}
    }

  mpInterpolation->recordState(mTime, mY);

  //==(3)==do interpolation
  mpEventState = mpInterpolation->getInterpolationState();

  //==(4)==record the state
  mTime = mpEventState->getTime();
  C_FLOAT64 * tmpY   = mpEventState->getArray() + 1;
  C_FLOAT64 * stateY = mpState->beginIndependent();

  for (size_t i = 0; i < mData.dim-1; i++)
    stateY[i] = tmpY[i]; //write result into mpState

  mpState->setTime(mTime);
  mpModel->setState(*mpState);
  mpModel->updateSimulatedValues(false); //for assignments?????????

  return;
}

/**
 * Dummy f function for calculating derivative of y
 */
void CHybridMethodODE45::EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{static_cast<Data *>((void *) n)->pMethod->evalF(t, y, ydot);}

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

  for (i = 0; i < mData.dim - 1; ++i)
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
        ydot[mData.dim - 1] += mAmu[i];
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

/*========Functions for C Code from f2c========*/
C_INT CHybridMethodODE45::rkf45_(pEvalF f, const C_INT *neqn, double *y,
                                 double *t, double *tout,
                                 double *relerr, double *abserr,
                                 C_INT *iflag, double *work,
                                 C_INT *iwork, double *yrcd)
{
  static C_INT k1, k2, k3, k4, k5, k6, k1m;

  /*     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  /*     This is a modefied fehlberg fourth-fifth order runge-kutta method */
  /*     based on h.a.watts and l.f.shapine's fortran ODE solver rkf45.f */
  /*     with one more input double precision vector recording time */
  /*     points between t and t+h in each steap and */
  /*     approximations of y in such corresponding times. */
  /*     yrcd is a vector of length 4*(neqn+1), where "4" is related with */
  /*     four middle time points: */
  /*     c1=t+h/4, c2=t+3h/8, c3=t+h/2, c4=t+12h/13. */
  /*     yrcd can be seperated into four parts, each of which is a double */
  /*     precision vector of length neqn+1. The first member is assigned */
  /*     to time record, and the last neqn members are for y at the */
  /*     corresponding time. */
  /*     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /*     fehlberg fourth-fifth order runge-kutta method */

  /*     written by h.a.watts and l.f.shampine */
  /*                   sandia laboratories */
  /*                  albuquerque,new mexico */

  /*    rkf45 is primarily designed to solve non-stiff and mildly stiff */
  /*    differential equations when derivative evaluations are inexpensive. */
  /*    rkf45 should generally not be used when the user is demanding */
  /*    high accuracy. */

  /* abstract */

  /*    subroutine  rkf45  integrates a system of neqn first order */
  /*    ordinary differential equations of the form */
  /*             dy(i)/dt = f(t,y(1),y(2),...,y(neqn)) */
  /*              where the y(i) are given at t . */
  /*    typically the subroutine is used to integrate from t to tout but it */
  /*    can be used as a one-step integrator to advance the solution a */
  /*    single step in the direction of tout.  on return the parameters in */
  /*    the call list are set for continuing the integration. the user has */
  /*    only to call rkf45 again (and perhaps define a new value for tout). */
  /*    actually, rkf45 is an interfacing routine which calls subroutine */
  /*    rkfs for the solution.  rkfs in turn calls subroutine  fehl which */
  /*    computes an approximate solution over one step. */

  /*    rkf45  uses the runge-kutta-fehlberg (4,5)  method described */
  /*    in the reference */
  /*    e.fehlberg , low-order classical runge-kutta formulas with stepsize */
  /*                 control , nasa tr r-315 */

  /*    the performance of rkf45 is illustrated in the reference */
  /*    l.f.shampine,h.a.watts,s.davenport, solving non-stiff ordinary */
  /*                 differential equations-the state of the art , */
  /*                 sandia laboratories report sand75-0182 , */
  /*                 to appear in siam review. */

  /*    the parameters represent- */
  /*      f -- subroutine f(t,y,yp) to evaluate derivatives yp(i)=dy(i)/dt */
  /*      neqn -- number of equations to be integrated */
  /*      y(*) -- solution vector at t */
  /*      t -- independent variable */
  /*      tout -- output point at which solution is desired */
  /*      relerr,abserr -- relative and absolute error tolerances for local */
  /*            error test. at each step the code requires that */
  /*                 abs(local error) .le. relerr*abs(y) + abserr */
  /*            for each component of the local error and solution vectors */
  /*      iflag -- indicator for status of integration */
  /*      work(*) -- array to hold information internal to rkf45 which is */
  /*            necessary for subsequent calls. must be dimensioned */
  /*            at least  3+6*neqn */
  /*      iwork(*) -- C_INT array used to hold information internal to */
  /*            rkf45 which is necessary for subsequent calls. must be */
  /*            dimensioned at least  5 */

  /*  first call to rkf45 */

  /*    the user must provide storage in his calling program for the arrays */
  /*    in the call list  -      y(neqn) , work(3+6*neqn) , iwork(5)  , */
  /*    declare f in an external statement, supply subroutine f(t,y,yp) and */
  /*    initialize the following parameters- */

  /*      neqn -- number of equations to be integrated.  (neqn .ge. 1) */
  /*      y(*) -- vector of initial conditions */
  /*      t -- starting point of integration , must be a variable */
  /*      tout -- output point at which solution is desired. */
  /*            t=tout is allowed on the first call only, in which case */
  /*            rkf45 returns with iflag=2 if continuation is possible. */
  /*      relerr,abserr -- relative and absolute local error tolerances */
  /*            which must be non-negative. relerr must be a variable while */
  /*            abserr may be a constant. the code should normally not be */
  /*            used with relative error control smaller than about 1.e-8 . */
  /*            to avoid limiting precision difficulties the code requires */
  /*            relerr to be larger than an internally computed relative */
  /*            error parameter which is machine dependent. in particular, */
  /*            pure absolute error is not permitted. if a smaller than */
  /*            allowable value of relerr is attempted, rkf45 increases */
  /*            relerr appropriately and returns control to the user before */
  /*            continuing the integration. */
  /*      iflag -- +1,-1  indicator to initialize the code for each new */
  /*            problem. normal input is +1. the user should set iflag=-1 */
  /*            only when one-step integrator control is essential. in this */
  /*            case, rkf45 attempts to advance the solution a single step */
  /*            in the direction of tout each time it is called. since this */
  /*            mode of operation results in extra computing overhead, it */
  /*            should be avoided unless needed. */

  /*  output from rkf45 */

  /*      y(*) -- solution at t */
  /*      t -- last point reached in integration. */
  /*      iflag = 2 -- integration reached tout. indicates successful retur */
  /*                   and is the normal mode for continuing integration. */
  /*            =-2 -- a single successful step in the direction of tout */
  /*                   has been taken. normal mode for continuing */
  /*                   integration one step at a time. */
  /*            = 3 -- integration was not completed because relative error */
  /*                   tolerance was too small. relerr has been increased */
  /*                   appropriately for continuing. */
  /*            = 4 -- integration was not completed because more than */
  /*                   3000 derivative evaluations were needed. this */
  /*                   is approximately 500 steps. */
  /*            = 5 -- integration was not completed because solution */
  /*                   vanished making a pure relative error test */
  /*                   impossible. must use non-zero abserr to continue. */
  /*                   using the one-step integration mode for one step */
  /*                   is a good way to proceed. */
  /*            = 6 -- integration was not completed because requested */
  /*                   accuracy could not be achieved using smallest */
  /*                   allowable stepsize. user must increase the error */
  /*                   tolerance before continued integration can be */
  /*                   attempted. */
  /*            = 7 -- it is likely that rkf45 is inefficient for solving */
  /*                   this problem. too much output is restricting the */
  /*                   natural stepsize choice. use the one-step integrator */
  /*                   mode. */
  /*            = 8 -- invalid input parameters */
  /*                   this indicator occurs if any of the following is */
  /*                   satisfied -   neqn .le. 0 */
  /*                                 t=tout  and  iflag .ne. +1 or -1 */
  /*                                 relerr or abserr .lt. 0. */
  /*                                 iflag .eq. 0  or  .lt. -2  or  .gt. 8 */
  /*      work(*),iwork(*) -- information which is usually of no interest */
  /*                   to the user but necessary for subsequent calls. */
  /*                   work(1),...,work(neqn) contain the first derivatives */
  /*                   of the solution vector y at t. work(neqn+1) contains */
  /*                   the stepsize h to be attempted on the next step. */
  /*                   iwork(1) contains the derivative evaluation counter. */

  /*  subsequent calls to rkf45 */

  /*    subroutine rkf45 returns with all information needed to continue */
  /*    the integration. if the integration reached tout, the user need onl */
  /*    define a new tout and call rkf45 again. in the one-step integrator */
  /*    mode (iflag=-2) the user must keep in mind that each step taken is */
  /*    in the direction of the current tout. upon reaching tout (indicated */
  /*    by changing iflag to 2),the user must then define a new tout and */
  /*    reset iflag to -2 to continue in the one-step integrator mode. */

  /*    if the integration was not completed but the user still wants to */
  /*    continue (iflag=3,4 cases), he just calls rkf45 again. with iflag=3 */
  /*    the relerr parameter has been adjusted appropriately for continuing */
  /*    the integration. in the case of iflag=4 the function counter will */
  /*    be reset to 0 and another 3000 function evaluations are allowed. */

  /*    however,in the case iflag=5, the user must first alter the error */
  /*    criterion to use a positive value of abserr before integration can */
  /*    proceed. if he does not,execution is terminated. */

  /*    also,in the case iflag=6, it is necessary for the user to reset */
  /*    iflag to 2 (or -2 when the one-step integration mode is being used) */
  /*    as well as increasing either abserr,relerr or both before the */
  /*    integration can be continued. if this is not done, execution will */
  /*    be terminated. the occurrence of iflag=6 indicates a trouble spot */
  /*    (solution is changing rapidly,singularity may be present) and it */
  /*    often is inadvisable to continue. */

  /*    if iflag=7 is encountered, the user should use the one-step */
  /*    integration mode with the stepsize determined by the code or */
  /*    consider switching to the adams codes de/step,intrp. if the user */
  /*    insists upon continuing the integration with rkf45, he must reset */
  /*    iflag to 2 before calling rkf45 again. otherwise,execution will be */
  /*    terminated. */

  /*    if iflag=8 is obtained, integration can not be continued unless */
  /*    the invalid input parameters are corrected. */

  /*    it should be noted that the arrays work,iwork contain information */
  /*    required for subsequent integration. accordingly, work and iwork */
  /*    should not be altered. */

  /*     compute indices for the splitting of the work array */

  /* Parameter adjustments */
  --yrcd;
  --y;
  --work;
  --iwork;

  /* Function Body */
  k1m = *neqn + 1;
  //k1m = *neqn;
  k1 = k1m + 1;
  k2 = k1 + *neqn;
  k3 = k2 + *neqn;
  k4 = k3 + *neqn;
  k5 = k4 + *neqn;
  k6 = k5 + *neqn;

  /*     this interfacing routine merely relieves the user of a long */
  /*     calling list via the splitting apart of two working storage */
  /*     arrays. if this is not compatible with the users compiler, */
  /*     he must use rkfs directly. */

  rkfs_((pEvalF)f, neqn, &y[1], t, tout, relerr, abserr, iflag,
        &work[1], &work[k1m], &work[k1], &work[k2], &work[k3],
        &work[k4], &work[k5], &work[k6], &work[k6 + 1], &iwork[1],
        &iwork[2], &iwork[3], &iwork[4], &iwork[5], &yrcd[1]);

  return 0;
} /* rkf45_ */

C_INT CHybridMethodODE45::rkfs_(pEvalF f, const C_INT *neqn, double *y, double *
                                t, double *tout, double *relerr, double *abserr, C_INT *
                                iflag, double *yp, double *h__, double *f1, double *
                                f2, double *f3, double *f4, double *f5, double *savre,
                                double *savae, C_INT *nfe, C_INT *kop, C_INT *init,
                                C_INT *jflag, C_INT *kflag, double *yrcd)
{
  /* Initialized data */

  static double remin = 1e-12;
  static C_INT maxnfe = 3000;

  /* System generated locals */
  C_INT i__1;
  double d__1, d__2, d__3, d__4;

  /* Builtin functions */
  /* Subroutine */
  //int s_stop(char *, ftnlen);
  //double pow_dd(double *, double *);
  //C_INT i_sign(C_INT *, C_INT *);
  //double d_sign(double *, double *);

  /* Local variables */
  static double a;
  static C_INT k;
  static double s, ae, ee, dt, et, u26, rer, tol, ypk;
  static double hmin, toln;
  static C_INT mflag;
  static double scale, eeoet;
  static int hfaild;
  static double esttol, twoeps;
  static int output;

  /* fehlberg fourth-fifth order runge-kutta method */

  /* rkfs integrates a system of first order ordinary differential */
  /* equations as described in the comments for rkf45 . */
  /* the arrays yp,f1,f2,f3,f4,and f5 (of dimension at least neqn) and */
  /* the variables h,savre,savae,nfe,kop,init,jflag,and kflag are used */
  /* internally by the code and appear in the call list to eliminate */
  /* local retention of variables between calls. accordingly, they */
  /* should not be altered. items of possible interest are */
  /*     yp - derivative of solution vector at t */
  /*     h  - an appropriate stepsize to be used for the next step */
  /*     nfe- counter on the number of derivative function evaluations */

  /*  remin is the minimum acceptable value of relerr.  attempts */
  /*  to obtain higher accuracy with this subroutine are usually */
  /*  very expensive and often unsuccessful. */

  /* Parameter adjustments */
  --yrcd;
  --f5;
  --f4;
  --f3;
  --f2;
  --f1;
  --yp;
  --y;

  /* Function Body */

  /* the expense is controlled by restricting the number */
  /* of function evaluations to be approximately maxnfe. */
  /* as set, this corresponds to about 500 steps. */

  /* here two constants emboding the machine epsilon is present */
  /* twoesp is set to twice the machine epsilon while u26 is set */
  /* to 26 times the machine epsilon */

  /* data twoeps, u26/4.4d-16, 5.72d-15/  *** */
  twoeps = 2.f * std::numeric_limits< C_FLOAT64 >::epsilon();
  //twoeps = 4.4e-16;
  u26    = twoeps * 13.f;

  /* check input parameters */
  if (*neqn < 1)
    {
      goto L10;
    }

  if (*relerr < 0. || *abserr < 0.)
    {
      goto L10;
    }

  mflag = abs(*iflag);

  if (mflag >= 1 && mflag <= 8)
    {
      goto L20;
    }

  /* invalid input */
L10:
  *iflag = 8;
  return 0;

  /* is this the first call */
L20:

  if (mflag == 1)
    {
      goto L50;
    }

  /* check continuation possibilities */

  if (*t == *tout && *kflag != 3)
    {
      goto L10;
    }

  if (mflag != 2)
    {
      goto L25;
    }

  /* iflag = +2 or -2 */
  if (*kflag == 3)
    {
      goto L45;
    }

  if (*init == 0)
    {
      goto L45;
    }

  if (*kflag == 4)
    {
      goto L40;
    }

  if (*kflag == 5 && *abserr == 0.)
    {
      goto L30;
    }

  if (*kflag == 6 && *relerr <= *savre && *abserr <= *savae)
    {
      goto L30;
    }

  goto L50;

  /* iflag = 3,4,5,6,7 or 8 */
L25:

  if (*iflag == 3)
    {
      goto L45;
    }

  if (*iflag == 4)
    {
      goto L40;
    }

  if (*iflag == 5 && *abserr > 0.)
    {
      goto L45;
    }

  /* integration cannot be continued since user did not respond to */
  /* the instructions pertaining to iflag=5,6,7 or 8 */
L30:
  //s_stop("", (ftnlen)0);
  std::cout << "STOP 0 statement executed" << std::endl;
  return -1;

  /* reset function evaluation counter */
L40:
  *nfe = 0;

  if (mflag == 2)
    {
      goto L50;
    }

  /* reset flag value from previous call */
L45:
  *iflag = *jflag;

  if (*kflag == 3)
    {
      mflag = abs(*iflag);
    }

  /* save input iflag and set continuation flag value for subsequent */
  /* input checking */
L50:
  *jflag = *iflag;
  *kflag = 0;

  /* save relerr and abserr for checking input on subsequent calls */
  *savre = *relerr;
  *savae = *abserr;

  /* restrict relative error tolerance to be at least as large as */
  /* 2*eps+remin to avoid limiting precision difficulties arising */
  /* from impossible accuracy requests */

  rer = twoeps + remin;

  if (*relerr >= rer)
    {
      goto L55;
    }

  /* relative error tolerance too small */
  *relerr = rer;
  *iflag = 3;
  *kflag = 3;
  return 0;

L55:
  dt = *tout - *t;

  if (mflag == 1)
    {
      goto L60;
    }

  if (*init == 0)
    {
      goto L65;
    }

  goto L80;

  /* initialization -- */
  /* set initialization completion indicator,init */
  /* set indicator for too many output points,kop */
  /* evaluate initial derivatives */
  /* set counter for function evaluations,nfe */
  /* evaluate initial derivatives */
  /* set counter for function evaluations,nfe */
  /* estimate starting stepsize */

L60:
  *init = 0;
  *kop = 0;

  a = *t;
  (*f)(neqn, &a, &y[1], &yp[1]);
  *nfe = 1;

  if (*t != *tout)
    {
      goto L65;
    }

  *iflag = 2;
  return 0;

L65:
  *init = 1;
  *h__ = fabs(dt);
  toln = 0.f;
  i__1 = *neqn;

  for (k = 1; k <= i__1; ++k)
    {
      tol = *relerr * (d__1 = y[k], fabs(d__1)) + *abserr;

      if (tol <= 0.f)
        {
          goto L70;
        }

      toln = tol;
      ypk = (d__1 = yp[k], fabs(d__1));
      /* Computing 5th power */
      d__1 = *h__, d__2 = d__1, d__1 *= d__1;

      if (ypk * (d__2 * (d__1 * d__1)) > tol)
        {
          d__3 = tol / ypk;
          *h__ = pow(d__3, .2);
        }

L70:
      ;
    }

  if (toln <= 0.)
    {
      *h__ = 0.;
    }

  /* Computing MAX */
  /* Computing MAX */
  d__3 = fabs(*t), d__4 = fabs(dt);
  d__1 = *h__, d__2 = u26 * std::max(d__3, d__4);
  *h__ = std::max(d__1, d__2);
  //*jflag = i_sign(2, iflag);
  *jflag = *iflag >= 0 ? 2 : -2;

  /* set stepsize for integration in the direction from t to tout */

L80:
  //*h__ = d_sign(h__, &dt);
  *h__ = dt >= 0 ? fabs(*h__) : -fabs(*h__);

  /* test to see if rkf45 is being severely impacted by too many */
  /* output points */

  if (fabs(*h__) >= fabs(dt) * 2.)
    {
      ++(*kop);
    }

  if (*kop != 100)
    {
      goto L85;
    }

  /* unnecessary frequency of output */
  *kop = 0;
  *iflag = 7;
  return 0;

L85:

  if (fabs(dt) > u26 * fabs(*t))
    {
      goto L95;
    }

  /* if too close to output point,extrapolate and return */
  i__1 = *neqn;

  for (k = 1; k <= i__1; ++k)
    {
      /* L90: */
      y[k] += dt * yp[k];
    }

  a = *tout;
  (*f)(neqn, &a, &y[1], &yp[1]);
  ++(*nfe);
  
  std::cout << "Step too Small" << std::endl;
  mUseStateRecord = false;
  goto L300;

  /* initialize output point indicator */

L95:
  output = 0;

  /* to avoid premature underflow in the error tolerance function, */
  /* scale the error tolerances */

  scale = 2. / *relerr;
  ae = scale * *abserr;

  /* step by step integration */

L100:
  hfaild = 0;

  /* set smallest allowable stepsize */
  hmin = u26 * fabs(*t);

  /* adjust stepsize if necessary to hit the output point. */
  /* look ahead two steps to avoid drastic changes in the stepsize and */
  /* thus lessen the impact of output points on the code. */

  dt = *tout - *t;

  if (fabs(dt) >= fabs(*h__) * 2.)
    {
      goto L200;
    }

  if (fabs(dt) > fabs(*h__))
    {
      goto L150;
    }

  /* the next successful step will complete the integration to the */
  /* output point */

  output = 1;
  *h__ = dt;
  goto L200;

L150:
  *h__ = dt * .5;

  /* core integrator for taking a single step */

  /* the tolerances have been scaled to avoid premature underflow in */
  /* computing the error tolerance function et. */
  /* to avoid problems with zero crossings,relative error is measured */
  /* using the average of the magnitudes of the solution at the */
  /* beginning and end of a step. */
  /* the error estimate formula has been grouped to control loss of */
  /* significance. */
  /* to distinguish the various arguments, h is not permitted */
  /* to become smaller than 26 units of roundoff in t. */
  /* practical limits on the change in the stepsize are enforced to */
  /* smooth the stepsize selection process and to avoid excessive */
  /* chattering on problems having discontinuities. */
  /* to prevent unnecessary failures, the code uses 9/10 the stepsize */
  /* it estimates will succeed. */
  /* after a step failure, the stepsize is not allowed to increase for */
  /* the next attempted step. this makes the code more efficient on */
  /* problems having discontinuities and more effective in general */
  /* since local extrapolation is being used and extra caution seems */
  /* warranted. */

  /* test number of derivative function evaluations. */
  /* if okay,try to advance the integration from t to t+h */

L200:

  if (*nfe <= maxnfe)
    {
      goto L220;
    }

  /* too much work */
  *iflag = 4;
  *kflag = 4;
  return 0;

  /* advance an approximate solution over one step of length h */

L220:
  fehl_((pEvalF)f, neqn, &y[1], t, h__, &yp[1], &f1[1], &f2[1],
        &f3[1], &f4[1], &f5[1], &f1[1], &yrcd[1]);
  *nfe += 5;
  mUseStateRecord = true;

  /* compute and test allowable tolerances versus local error estimates*/
  /* and remove scaling of tolerances. note that relative error is */
  /* measured with respect to the average of the magnitudes of the */
  /* solution at the beginning and end of the step. */

  eeoet = 0.;
  i__1 = *neqn;

  for (k = 1; k <= i__1; ++k)
    {
      et = (d__1 = y[k], fabs(d__1)) + (d__2 = f1[k], fabs(d__2)) + ae;

      if (et > 0.)
        {
          goto L240;
        }

      /* inappropriate error tolerance */
      *iflag = 5;
      return 0;

L240:
      ee = (d__1 = yp[k] * -2090. + (f3[k] * 21970. - f4[k] * 15048.) + (f2[k] * 22528. - f5[k] * 27360.), fabs(d__1));
      /* L250: */
      /* Computing MAX */
      d__1 = eeoet, d__2 = ee / et;
      eeoet = std::max(d__1, d__2);
    }

  esttol = fabs(*h__) * eeoet * scale / 752400.;

  if (esttol <= 1.)
    {
      goto L260;
    }

  /* unsuccessful step */
  /* reduce the stepsize , try again */
  /* the decrease is limited to a factor of 1/10 */

  hfaild = 1;
  output = 0;
  s = .1;

  if (esttol < 59049.)
    {
      s = .9 / pow(esttol, .2);
    }

  *h__ = s * *h__;

  if (fabs(*h__) > hmin)
    {
      goto L200;
    }

  /* requested error unattainable at smallest allowable stepsize */
  *iflag = 6;
  *kflag = 6;
  return 0;

  /* successful step */
  /* store solution at t+h */
  /* and evaluate derivatives there */

L260:
  *t += *h__;
  i__1 = *neqn;

  for (k = 1; k <= i__1; ++k)
    {
      /* L270: */
      y[k] = f1[k];
    }

  a = *t;
  (*f)(neqn, &a, &y[1], &yp[1]);
  ++(*nfe);

  /* choose next stepsize */
  /* the increase is limited to a factor of 5 */
  /* if step failure has just occurred, next */
  /* stepsize is not allowed to increase */

  s = 5.;

  if (esttol > 1.889568e-4)
    {
      s = .9 / pow(esttol, .2);
    }

  if (hfaild)
    {
      s = std::min(s, 1.);
    }

  /* Computing MAX */
  d__2 = s * fabs(*h__);
  d__1 = std::max(d__2, hmin);
  //*h__ = d_sign(&d__1, h__);
  *h__ = *h__ >= 0 ? fabs(d__1) : -fabs(d__1);

  /* end of core integrator */

  /* should we take another step */
  if (output)
    {
      goto L300;
    }

  if (*iflag > 0)
    {
      goto L100;
    }

  /* integration successfully completed */

  /* one-step mode */
  *iflag = -2;
  return 0;

  /* interval mode */
L300:
  *t = *tout;
  *iflag = 2;
  return 0;
} /* rkfs_ */

C_INT CHybridMethodODE45::fehl_(pEvalF f, const C_INT *neqn, double *y,
                                double *t, double *h__,
                                double *yp, double *f1,
                                double *f2, double *f3,
                                double *f4, double *f5,
                                double *s, double *yrcd)
{
  /* System generated locals */
  C_INT i__1;
  double d__1;

  /* Local variables */
  static C_INT k;
  static double ch;
  static C_INT base;

  /* fehlberg fourth-fifth order runge-kutta method */

  /* fehl integrates a system of neqn first order */
  /* ordinary differential equations of the form */
  /*             dy(i)/dt=f(t,y(1),---,y(neqn)) */
  /* where the initial values y(i) and the initial derivatives */
  /* yp(i) are specified at the starting point t. fehl advances */
  /* the solution over the fixed step h and returns */
  /* the fifth order (sixth order accurate locally) solution */
  /* approximation at t+h in array s(i). */
  /* f1,---,f5 are arrays of dimension neqn which are needed */
  /* for internal storage. */
  /* the formulas have been grouped to control loss of significance. */
  /* fehl should be called with an h not smaller than 13 units of */
  /* roundoff in t so that the various independent arguments can be */
  /* distinguished. */

  /* Parameter adjustments */
  --yrcd;
  --s;
  --f5;
  --f4;
  --f3;
  --f2;
  --f1;
  --yp;
  --y;

  /* Function Body */

  //~~~~~~~~(1)~~~~~~~~
  ch = *h__ / 4.;
  i__1 = *neqn;

  for (k = 1; k <= i__1; ++k)
    {
      f5[k] = y[k] + ch * yp[k];
    }

  d__1 = *t + ch;
  (*f)(neqn, &d__1, &f5[1], &f1[1]);

  /* Record trcd and yrcd at t+h/4 */
  base = 1;
  yrcd[base] = *t + ch;
  i__1 = *neqn;

  for (k = 1; k <= i__1; ++k)
    {
      yrcd[base + k] = f5[k];
    }

  //~~~~~~~~(2)~~~~~~~~
  ch = *h__ * 3. / 32.;
  i__1 = *neqn;

  for (k = 1; k <= i__1; ++k)
    {
      f5[k] = y[k] + ch * (yp[k] + f1[k] * 3.);
    }

  d__1 = *t + *h__ * 3. / 8.;
  (*f)(neqn, &d__1, &f5[1], &f2[1]);

  /* Record trcd and yrcd at t+3h/8 */
  base = *neqn + 2;
  yrcd[base] = *t + *h__ * 3. / 8.;
  i__1 = *neqn;

  for (k = 1; k <= i__1; ++k)
    {
      yrcd[base + k] = f5[k];
    }

  //~~~~~~~~(3)~~~~~~~~
  ch = *h__ / 2197.;
  i__1 = *neqn;

  for (k = 1; k <= i__1; ++k)
    {
      f5[k] = y[k] + ch * (yp[k] * 1932. + (f2[k] * 7296.
                                            - f1[k] * 7200.));
    }

  d__1 = *t + *h__ * 12. / 13.;
  (*f)(neqn, &d__1, &f5[1], &f3[1]);

  /* Record trcd and yrcd at t+12h/13 */
  base = (*neqn + 1) * 3 + 1;
  yrcd[base] = *t + *h__ * 12. / 13.;
  i__1 = *neqn;

  for (k = 1; k <= i__1; ++k)
    {
      yrcd[base + k] = f5[k];
    }

  //~~~~~~~~(4)~~~~~~~~
  ch = *h__ / 4104.;
  i__1 = *neqn;

  for (k = 1; k <= i__1; ++k)
    {
      f5[k] = y[k] + ch * (yp[k] * 8341. - f3[k] * 845.
                           + (f2[k] * 29440. - f1[k] * 32832.));
    }

  d__1 = *t + *h__;
  (*f)(neqn, &d__1, &f5[1], &f4[1]);

  //~~~~~~~~(5)~~~~~~~~
  ch = *h__ / 20520.;
  i__1 = *neqn;

  for (k = 1; k <= i__1; ++k)
    {
      f1[k] = y[k] + ch * (yp[k] * -6080.
                           + (f3[k] * 9295. - f4[k] * 5643.)
                           + (f1[k] * 41040. - f2[k] * 28352.));
    }

  d__1 = *t + *h__ / 2.;
  (*f)(neqn, &d__1, &f1[1], &f5[1]);

  /* Record trcd and yrcd at t+h/2 */
  //base = (*neqn + 1 << 1) + 1;
  base = (*neqn + 1) * 2 + 1;
  yrcd[base] = *t + *h__ / 2.;
  i__1 = *neqn;

  for (k = 1; k <= i__1; ++k)
    {
      yrcd[base + k] = f1[k];
    }

  //~~~~~~~~(6)~~~~~~~~
  /* compute approximate solution at t+h */
  ch = *h__ / 7618050.;
  i__1 = *neqn;

  for (k = 1; k <= i__1; ++k)
    {
      s[k] = y[k] + ch * (yp[k] * 902880.
                          + (f3[k] * 3855735. - f4[k] * 1371249.)
                          + (f2[k] * 3953664. + f5[k] * 277020.));
    }

  return 0;
} /* fehl_ */

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
  CMatrix <C_FLOAT64> mStoi = model->getStoiReordered();
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

  if (mReducedModel)
    std::cout << "mReducedModel: Yes" << std::endl;
  else
    std::cout << "mReducedModel: No" << std::endl;

  std::cout << std::endl;

  std::cout << "============Metab============" << std::endl;

  std::cout << "~~~~mNumVariableMetabs:~~~~ " << mNumVariableMetabs << std::endl;
  std::cout << "~~~~mFirstMetabIndex:~~~~ " << mFirstMetabIndex << std::endl;
  std::cout << "~~~~mpMetabolites:~~~~" << std::endl;
  for (size_t i=0; i<mpMetabolites->size(); i++)
    {
      std::cout << "metab #" << i + 1 << " name: " << (*mpMetabolites)[i]->getObjectDisplayName() << std::endl;
      std::cout << "value pointer: " << (*mpMetabolites)[i]->getValuePointer() << std::endl;
      std::cout << "value: " << *((double *)(*mpMetabolites)[i]->getValuePointer()) << std::endl;
    }
  std::cout << std::endl;

  std::cout << "~~~~mMetabFlags:~~~~ " << std::endl;
  for (size_t i=0; i<mMetabFlags.size(); ++i)
    {
      std::cout << "metab #" << i + 1 << std::endl;
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
      std::cout << "Reaction #: " << i+1 << " Flag: " << mReactionFlags[i] << std::endl;
    }
  std::cout << "~~~~mLocalBalances:~~~~ " << std::endl;
  for (size_t i=0; i<mLocalBalances.size(); ++i)
    {
      std::cout << "Reaction: " << i + 1 << std::endl;

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
      std::cout << "Reaction: " << i + 1 << std::endl;

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
      std::cout << "metab #: " << i + 1 << std::endl;
      std::set<size_t>::iterator it = mMetab2React[i].begin();
      std::set<size_t>::iterator endIt = mMetab2React[i].end();
      std::cout << "React: ";

      for (; it != endIt; it++)
        std::cout << *it << " ";

      std::cout << std::endl;
    }

  std::cout << "mReactAffect: " << std::endl;

  for (size_t i = 0; i < mReactAffect.size(); i++)
    {
      std::cout << "react #: " << i + 1 << std::endl;
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
