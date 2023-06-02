// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *   CHybridMethod
 *
 *   This class implements an hybrid algorithm for the simulation of a
 *   biochemical system over time.
 *
 *   File name: CHybridMethod.cpp
 *   Author: Juergen Pahle
 *   Email: juergen.pahle@eml-r.villa-bosch.de
 *
 *   Last change: 14, December 2004
 *
 *   (C) European Media Lab 2003.
 */

/* DEFINE ********************************************************************/

#ifdef WIN32
#if _MSC_VER < 1600
#define min _cpp_min
#define max _cpp_max
#endif // _MSC_VER
#endif // WIN32

#include <limits.h>
#include <iterator>

#include "copasi/copasi.h"

#include "CHybridMethod.h"
#include "CTrajectoryProblem.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/core/CDataVector.h"
#include "copasi/core/CMatrix.h"
#include "copasi/utilities/CDependencyGraph.h"
#include "copasi/utilities/CIndexedPriorityQueue.h"
#include "copasi/randomGenerator/CRandom.h"
#include "copasi/utilities/CVersion.h"
#include "copasi/math/CMathContainer.h"

/**
 *   Default constructor.
 */
CHybridMethod::CHybridMethod(const CDataContainer * pParent,
                             const CTaskEnum::Method & methodType,
                             const CTaskEnum::Task & taskType):
  CTrajectoryMethod(pParent, methodType, taskType)
{
  initializeParameter();
}

CHybridMethod::CHybridMethod(const CHybridMethod & src,
                             const CDataContainer * pParent):
  CTrajectoryMethod(src, pParent)
{
  initializeParameter();
}

/**
 *   Destructor.
 */
CHybridMethod::~CHybridMethod()
{
  cleanup();
  DESTRUCTOR_TRACE;
}

void CHybridMethod::initializeParameter()
{
  CCopasiParameter *pParm;

  assertParameter("Max Internal Steps", CCopasiParameter::Type::INT, (C_INT32) MAX_STEPS);
  assertParameter("Lower Limit", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) LOWER_STOCH_LIMIT);
  assertParameter("Upper Limit", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) UPPER_STOCH_LIMIT);
  assertParameter("Partitioning Interval", CCopasiParameter::Type::UINT, (unsigned C_INT32) PARTITIONING_INTERVAL);
  assertParameter("Use Random Seed", CCopasiParameter::Type::BOOL, (bool) USE_RANDOM_SEED);
  assertParameter("Random Seed", CCopasiParameter::Type::UINT, (unsigned C_INT32) RANDOM_SEED);

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("HYBRID.MaxSteps")) != NULL)
    {
      setValue("Max Internal Steps", pParm->getValue< C_INT32 >());
      removeParameter("HYBRID.MaxSteps");

      if ((pParm = getParameter("HYBRID.LowerStochLimit")) != NULL)
        {
          setValue("Lower Limit", pParm->getValue< C_FLOAT64 >());
          removeParameter("HYBRID.LowerStochLimit");
        }

      if ((pParm = getParameter("HYBRID.UpperStochLimit")) != NULL)
        {
          setValue("Upper Limit", pParm->getValue< C_FLOAT64 >());
          removeParameter("HYBRID.UpperStochLimit");
        }

      if ((pParm = getParameter("HYBRID.PartitioningInterval")) != NULL)
        {
          setValue("Partitioning Interval", pParm->getValue< unsigned C_INT32 >());
          removeParameter("HYBRID.PartitioningInterval");
        }

      if ((pParm = getParameter("UseRandomSeed")) != NULL)
        {
          setValue("Use Random Seed", pParm->getValue< bool >());
          removeParameter("UseRandomSeed");
        }

      if ((pParm = getParameter("")) != NULL)
        {
          setValue("Random Seed", pParm->getValue< unsigned C_INT32 >());
          removeParameter("");
        }
    }
}

bool CHybridMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

CTrajectoryMethod::Status CHybridMethod::step(const double & deltaT,
    const bool & /* final */)
{
  // write the current state to the model
  //  mpProblem->getModel()->setState(mpCurrentState); // is that correct?

  // check for possible overflows
  size_t i;

  // do several steps
  C_FLOAT64 time = *mpContainerStateTime;
  C_FLOAT64 endTime = time + deltaT;

  for (i = 0; ((i < mMaxSteps) && (time < endTime)); i++)
    {
      time = doSingleStep(time, endTime);
    }

  *mpContainerStateTime = time;
  mpContainer->updateSimulatedValues(false);

  if ((i >= mMaxSteps) && (!mMaxStepsReached))
    {
      mMaxStepsReached = true; //only report this message once
      CCopasiMessage(CCopasiMessage::WARNING, "maximum number of reaction events was reached in at least one simulation step.\nThat means time intervals in the output may not be what you requested.");
    }

  return NORMAL;
}

void CHybridMethod::start()
{
  CTrajectoryMethod::start();

  mFirstMetabIndex = mpContainer->getCountFixedEventTargets() + 1 + mpContainer->getCountODEs();
  mpFirstMetabValue = mpContainer->getState(false).array() + mFirstMetabIndex;

  // call init of the simulation method, can be overloaded in derived classes
  mReactions.initialize(mpContainer->getReactions());
  mAmu.clear();
  mAmu.resize(mReactions.size());
  mAmuOld.clear();
  mAmuOld.resize(mReactions.size());
  mNumVariableMetabs = mpContainer->getCountIndependentSpecies() + mpContainer->getCountDependentSpecies();
  mUpdateSequences.resize(mReactions.size());

  mSpeciesRates.initialize(mNumVariableMetabs, const_cast< C_FLOAT64 * >(mpContainer->getRate(false).array()) + mFirstMetabIndex);
  mRateOffset = mpContainer->getRate(false).array() - mpContainer->getState(false).array();

  mCurrentState.initialize(mNumVariableMetabs, const_cast< C_FLOAT64 * >(mpContainer->getState(false).array()) + mFirstMetabIndex);

  mMetab2React.resize(mNumVariableMetabs);

  /* get configuration data */
  mMaxSteps = getValue< C_INT32 >("Max Internal Steps");
  mLowerStochLimit = getValue< C_FLOAT64 >("Lower Limit");
  mUpperStochLimit = getValue< C_FLOAT64 >("Upper Limit");
  mPartitioningInterval = getValue< unsigned C_INT32 >("Partitioning Interval");
  mUseRandomSeed = getValue< bool >("Use Random Seed");
  mRandomSeed = getValue< unsigned C_INT32 >("Random Seed");

  mpRandomGenerator = &mpContainer->getRandomGenerator();

  if (mUseRandomSeed)
    {
      mpRandomGenerator->initialize(mRandomSeed);
    }

  mStepsAfterPartitionSystem = 0;

  setupDependencyGraph(); // initialize mDG
  setupMetab2React(); // initialize mMetab2React
  setupPartition(); // initialize mReactionFlags
  setupPriorityQueue(); // initialize mPQ

  mMaxStepsReached = false;

  return;
}

/**
 *  Cleans up memory, etc.
 */
void CHybridMethod::cleanup()
{
  return;
}

/* DETERMINISTIC STUFF *******************************************************/

/**
 *  Simulates the system over the next interval of time. The new time after
 *  this step is returned.
 *
 *  @param  currentTime A C_FLOAT64 specifying the current time
 *  @param  endTime A C_FLOAT64 specifying the endTime of the current step()
 *  @return A C_FLOAT giving the new time
 */
C_FLOAT64 CHybridMethod::doSingleStep(C_FLOAT64 currentTime, C_FLOAT64 endTime)
{
  size_t rIndex = 0;
  C_FLOAT64 ds = endTime;

  // if there are stochastic reactions
  if (mPQ.size() != 0) // there is at least one stochastic reaction
    {
      getStochTimeAndIndex(ds, rIndex);

      if (ds <= endTime) // ds is an absolute time value!
        {
          // if there are deterministic reactions
          if (mFirstReactionFlag != NULL) // there is at least one deterministic reaction
            {
              integrateDeterministicPart(ds - currentTime);
            }

          mReactions[rIndex].fire();
          *mpContainerStateTime = ds;
          stateChange(CMath::eStateChange::State);

          if (++mStepsAfterPartitionSystem >= mPartitioningInterval)
            {
              partitionSystem();
              mStepsAfterPartitionSystem = 0;
            }

          updatePriorityQueue(rIndex, ds);
        }
      else
        {
          ds = endTime;

          // if there are deterministic reactions
          if (mFirstReactionFlag != NULL) // there is at least one deterministic reaction
            {
              integrateDeterministicPart(ds - currentTime);
            }

          *mpContainerStateTime = ds;

          if (++mStepsAfterPartitionSystem >= mPartitioningInterval)
            {
              partitionSystem();
              mStepsAfterPartitionSystem = 0;
            }

          updatePriorityQueue(C_INVALID_INDEX, endTime);
        }
    }
  else // there is no stochastic reaction
    {
      // if there are deterministic reactions
      if (mFirstReactionFlag != NULL) // there is at least one deterministic reaction
        {
          integrateDeterministicPart(ds - currentTime);
        }

      *mpContainerStateTime = ds;

      if (++mStepsAfterPartitionSystem >= mPartitioningInterval)
        {
          partitionSystem();
          mStepsAfterPartitionSystem = 0;
        }

      updatePriorityQueue(C_INVALID_INDEX, ds);
    }

  return ds;
}

/**
 *   Calculates the derivative of the system and writes it into the vector
 *   deriv. Length of deriv must be mNumVariableMetabs.
 *   CAUTION: Only deterministic reactions are taken into account. That is,
 *   this is only the derivative of the deterministic part of the system.
 *
 *   @param deriv A vector reference of length mNumVariableMetabs, into
 *                which the derivative is written
 */
void CHybridMethod::calculateDerivative(CVectorCore< C_FLOAT64 > & deriv)
{
  C_INT32 bal = 0;
  CHybridStochFlag * j;

  mpContainer->updateSimulatedValues(false);
  mSpeciesRates = 0.0;

  // For each det. reactions sum the contribution to the species rates

  for (j = mFirstReactionFlag; j != NULL; j = j->mpNext)
    {
      CMathReaction & reaction = mReactions[j->mIndex];

      const std::pair< C_FLOAT64 *, C_FLOAT64 > * pBalance = reaction.getNumberBalance().array();
      const std::pair< C_FLOAT64 *, C_FLOAT64 > * pBalanceEnd = pBalance + reaction.getNumberBalance().size();

      const C_FLOAT64 * pFlux = (C_FLOAT64 *) reaction.getParticleFluxObject()->getValuePointer();

      for (; pBalance != pBalanceEnd; ++pBalance)
        {
          // juergen: +0.5 to get a rounding out of the static_cast
          *(pBalance->first + mRateOffset) += floor(pBalance->second + 0.5) **pFlux;
        }
    }

  deriv = mSpeciesRates;

  return;
}

/* STOCHASTIC STUFF **********************************************************/

/**
 *   Find the reaction index and the reaction time of the stochastic (!)
 *   reaction with the lowest reaction time.
 *
 *   @param ds A reference to a C_FLOAT64. The putative reaction time for the
 *             first stochastic reaction is written into this variable.
 *   @param rIndex A reference to a size_t. The index of the first
 *                 stochastic reaction is written into this variable.
 */
void CHybridMethod::getStochTimeAndIndex(C_FLOAT64 & ds, size_t & rIndex)
{
  ds = mPQ.topKey();
  rIndex = mPQ.topIndex();
  return;
}

/**
 *   Updates the priority queue.
 *
 *   @param rIndex A size_t giving the index of the fired reaction (-1, if no
 *                 stochastic reaction has fired)
 *   @param time A C_FLOAT64 holding the current time
 */
void CHybridMethod::updatePriorityQueue(size_t rIndex, C_FLOAT64 time)
{
  C_FLOAT64 newTime;

  // Update all propensities depending on the current reaction (rIndex)
  if (rIndex != C_INVALID_INDEX)
    {
      mpContainer->applyUpdateSequence(mUpdateSequences[rIndex]);
    }
  else
    {
      mpContainer->updateSimulatedValues(false);

      CMathReaction * pReaction = mReactions.array();
      CMathReaction * pReactionEnd = pReaction + mReactions.size();

      for (; pReaction != pReactionEnd; ++pReaction)
        {
          const_cast< CMathObject * >(pReaction->getPropensityObject())->calculateValue();
        }
    }

  std::vector< CHybridStochFlag >::const_iterator it = mReactionFlags.begin();
  std::vector< CHybridStochFlag >::const_iterator end = mReactionFlags.end();

  for (; it != end; ++it)
    {
      if (it->mpPrev == NULL) // reaction is stochastic!
        {
          mAmuOld[it->mIndex] = mAmu[it->mIndex];
          mAmu[it->mIndex] = * (C_FLOAT64 *) mReactions[it->mIndex].getPropensityObject()->getValuePointer();

          if (it->mIndex != rIndex) updateTauMu(it->mIndex, time);
        }
    }

  // draw new random number and update the reaction just fired
  if (rIndex != C_INVALID_INDEX &&
      mReactionFlags[rIndex].mpPrev == NULL)
    {
      // reaction is stochastic
      newTime = time + generateReactionTime(rIndex);
      mPQ.updateNode(rIndex, newTime);
    }

  return;
}

C_FLOAT64 CHybridMethod::generateReactionTime(size_t rIndex)
{
  if (mAmu[rIndex] == 0) return std::numeric_limits<C_FLOAT64>::infinity();

  C_FLOAT64 rand2 = mpRandomGenerator->getRandomOO();
  return -1.0 * log(rand2) / mAmu[rIndex];
}

/**
 *   Updates the putative reaction time of a stochastic reaction in the
 *   priority queue. The corresponding amu and amu_old must be set prior to
 *   the call of this method.
 *
 *   @param rIndex A size_t specifying the index of the reaction
 */
void CHybridMethod::updateTauMu(size_t rIndex, C_FLOAT64 time)
{
  C_FLOAT64 newTime;

  // One must make sure that the calculation yields reasonable results even in the cases where mAmu=0 or mAmuOld=0 or both =0. Therefore mAmuOld=0 is checked. If mAmuOld equals 0, then a new random number has to be drawn, because tau equals inf and the stoch. information is lost. If both values equal 0, then tau should remain inf and the update of the queue can be skipped!

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

/* TESTING THE MODEL AND SETTING UP THINGS ***********************************/

/**
 *   Test the model if it is proper to perform stochastic simulations on.
 *   Several properties are tested (e.g. integer stoichometry, all reactions
 *   take place in one compartment only, irreversibility...).
 *
 *   @return 0, if everything is ok; <0, if an error occured.
 */
C_INT32 CHybridMethod::checkModel(CModel * model)
{
  CDataVectorNS <CReaction> * mpReactions = &model->getReactions();
  CMatrix <C_FLOAT64> mStoi = model->getStoi();
  size_t i, numReactions = mpReactions->size();
  size_t j;
  C_INT32 multInt;

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
 *   Sets up the dependency graph.
 */
void CHybridMethod::setupDependencyGraph()
{
  mDG.clear();
  size_t numReactions = mReactions.size();
  mDG.resize(numReactions);
  size_t i, j;

  CObjectInterface::ObjectSet PropensityObjects;

  for (i = 0; i < numReactions; i++)
    {
      PropensityObjects.insert(mReactions[i].getPropensityObject());
    }

  // Do for each reaction:
  for (i = 0; i < numReactions; i++)
    {
      CObjectInterface::ObjectSet ChangedObjects;

      CMathReaction & reaction = mReactions[i];

      CMathReaction::ObjectBalance::const_iterator itBalance = reaction.getObjectBalance().begin();
      CMathReaction::ObjectBalance::const_iterator endBalance = reaction.getObjectBalance().end();

      for (; itBalance != endBalance; ++itBalance)
        {
          ChangedObjects.insert(itBalance->first);
        }

      mpContainer->getTransientDependencies().getUpdateSequence(mUpdateSequences[i], CCore::SimulationContext::Default, ChangedObjects, PropensityObjects);

      for (j = 0; j < numReactions; j++)
        {
          if (mpContainer->getTransientDependencies().dependsOn(mReactions[j].getPropensityObject(), CCore::SimulationContext::Default, ChangedObjects))
            {
              mDG.addDependent(i, j);
            }
        }
    }

  return;
}

void CHybridMethod::setupMetab2React()
{
  size_t numReactions = mReactions.size();
  size_t i;

  for (i = 0; i < numReactions; i++)
    {
      const std::pair< C_FLOAT64 *, C_FLOAT64 > * pBalance = mReactions[i].getNumberBalance().array();
      const std::pair< C_FLOAT64 *, C_FLOAT64 > * pBalanceEnd = pBalance + mReactions[i].getNumberBalance().size();

      for (; pBalance != pBalanceEnd; ++pBalance)
        {
          mMetab2React[pBalance->first - mpFirstMetabValue].insert(i);
        }
    }
}

/**
 *   Creates an initial partitioning of the system. Deterministic and
 *   stochastic reactions are determined. The vector mReactionFlags and
 *   the vector mMetabFlags are initialized.
 */
void CHybridMethod::setupPartition()
{
  size_t i;

  // Initialize reactions flags.

  mReactionFlags.clear();
  mReactionFlags.resize(mReactions.size());

  for (i = 0; i < mReactionFlags.size(); i++)
    {
      mReactionFlags[i].mIndex = i;
      mReactionFlags[i].mValue = 0;
      mReactionFlags[i].mpNext = NULL;
      mReactionFlags[i].mpPrev = NULL;
    }

  CHybridStochFlag * prevFlag;
  C_FLOAT64 averageStochLimit = (mUpperStochLimit + mLowerStochLimit) / 2;

  // initialize vector mMetabFlags
  mMetabFlags.resize(mNumVariableMetabs);

  for (i = 0; i < mMetabFlags.size(); i++)
    {
      if (mCurrentState[i] < averageStochLimit)
        {
          mMetabFlags[i] = LOW;
          mCurrentState[i] = floor(mCurrentState[i]);

          std::set< size_t >::const_iterator itReaction = mMetab2React[i].begin();
          std::set< size_t >::const_iterator endReaction = mMetab2React[i].end();

          for (; itReaction != endReaction; ++itReaction)
            {
              mReactionFlags[*itReaction].mValue++;
            }
        }
      else
        {
          mMetabFlags[i] = HIGH;
        }
    }

  mFirstReactionFlag = NULL;
  prevFlag = NULL;

  for (i = 0; i < mReactionFlags.size(); i++)
    {
      if (mReactionFlags[i].mValue == 0)
        {
          if (mFirstReactionFlag != NULL)
            {
              prevFlag->mpNext = &mReactionFlags[i];
              mReactionFlags[i].mpPrev = prevFlag;
              prevFlag = &mReactionFlags[i];
            }
          else
            {
              mFirstReactionFlag = &mReactionFlags[i];
              mReactionFlags[i].mpPrev = &mReactionFlags[i]; // Important to distinguish between stochastic (prev == NULL) and deterministic (prev != NULL) reactions
              prevFlag = &mReactionFlags[i];
            }
        }
      else
        {
          mReactionFlags[i].mpPrev = NULL;
          mReactionFlags[i].mpNext = NULL;
        }
    }

  if (prevFlag != NULL)
    {
      prevFlag->mpNext = NULL;
    }

  return;
}

/**
 *   Sets up the priority queue.
 *
 *   @param startTime The time at which the simulation starts.
 */
void CHybridMethod::setupPriorityQueue()
{
  size_t i;
  C_FLOAT64 time;

  mPQ.clear();
  mPQ.initializeIndexPointer(mReactions.size());

  for (i = 0; i < mReactions.size(); i++)
    {
      if (mReactionFlags[i].mpPrev == NULL) // Reaction is stochastic!
        {
          const_cast< CMathObject * >(mReactions[i].getPropensityObject())->calculateValue();
          mAmu[i] = * (C_FLOAT64 *) mReactions[i].getPropensityObject()->getValuePointer();
          time = *mpContainerStateTime + generateReactionTime(i);
          mPQ.insertStochReaction(i, time);
        }
    }

  return;
}

/* HELPER METHODS ************************************************************/

/**
 *   Updates the partitioning of the system depending on the particle
 *   numbers present.
 */
void CHybridMethod::partitionSystem()
{
  bool StateChange = false;
  size_t i;
  std::set <size_t>::iterator it, end;

  for (i = 0; i < mNumVariableMetabs; i++)
    {
      if ((mMetabFlags[i] == LOW) && (mCurrentState[i] >= mUpperStochLimit))
        {
          StateChange = true;
          mMetabFlags[i] = HIGH;

          // go through all corresponding reactions and update flags
          for (it = mMetab2React[i].begin(), end = mMetab2React[i].end(); it != end; it++)
            {
              mReactionFlags[*it].mValue--;

              // if reaction gets deterministic, insert it into the linked list of deterministic reactions
              if (mReactionFlags[*it].mValue == 0)
                {
                  insertDeterministicReaction(*it);
                  mPQ.removeStochReaction(*it);
                }
            }
        }

      if ((mMetabFlags[i] == HIGH) && (mCurrentState[i] < mLowerStochLimit))
        {
          StateChange = true;
          mMetabFlags[i] = LOW;
          mCurrentState[i] = floor(mCurrentState[i]);

          // go through all corresponding reactions and update flags
          for (it = mMetab2React[i].begin(), end = mMetab2React[i].end(); it != end; it++)
            {
              if (mReactionFlags[*it].mValue == 0)
                {
                  removeDeterministicReaction(*it);
                  /*
                    mPQ.insertStochReaction(*iter, 1234567.8);  // juergen: have to beautify this, number has to be the biggest C_FLOAT64 !!!
                  */
                  const_cast< CMathObject * >(mReactions[*it].getPropensityObject())->calculateValue();
                  mAmu[*it] = * (C_FLOAT64 *) mReactions[*it].getPropensityObject()->getValuePointer();
                  mAmuOld[*it] = mAmu[*it];
                  mPQ.insertStochReaction(*it, *mpContainerStateTime + generateReactionTime(*it));
                }

              mReactionFlags[*it].mValue++;
            }
        }
    }

  if (StateChange)
    {
      stateChange(CMath::eStateChange::State);
    }

  return;
}

/**
 *   Inserts a new deterministic reaction into the linked list in the
 *   array mReactionFlags.
 *
 *   @param rIndex A size_t giving the index of the reaction to be inserted
 *                 into the list of deterministic reactions.
 */
void CHybridMethod::insertDeterministicReaction(size_t rIndex)
{
  if (mReactionFlags[rIndex].mpPrev == NULL)
    // reaction is stochastic (avoids double insertions)
    {
      if (mFirstReactionFlag != NULL)
        // there are deterministic reactions already
        {
          mFirstReactionFlag->mpPrev = &mReactionFlags[rIndex];
          mReactionFlags[rIndex].mpNext = mFirstReactionFlag;
          mFirstReactionFlag = &mReactionFlags[rIndex];
          mFirstReactionFlag->mpPrev = mFirstReactionFlag;
        }
      else
        {
          // there are no deterministic reactions
          // Important to distinguish between stochastic (prev == NULL) and deterministic (prev != NULL) reactions
          mReactionFlags[rIndex].mpPrev = &mReactionFlags[rIndex];
          mFirstReactionFlag = &mReactionFlags[rIndex];
        }

      mAmu[rIndex] = 0.0;
      mAmuOld[rIndex] = 0.0;
    }

  return;
}

/**
 *   Removes a deterministic reaction from the linked list in the
 *   array mReactionFlags.
 *
 *   @param rIndex A size_t giving the index of the reaction to be removed
 *                 from the list of deterministic reactions.
 */
void CHybridMethod::removeDeterministicReaction(size_t rIndex)
{
  if (mReactionFlags[rIndex].mpPrev != NULL)
    // reaction is deterministic
    {
      if (&mReactionFlags[rIndex] != mFirstReactionFlag)
        // reactionFlag is not the first in the linked list
        {
          mReactionFlags[rIndex].mpPrev->mpNext = mReactionFlags[rIndex].mpNext;

          if (mReactionFlags[rIndex].mpNext != NULL)
            mReactionFlags[rIndex].mpNext->mpPrev = mReactionFlags[rIndex].mpPrev;
        }
      else
        // reactionFlag is the first in the linked list
        {
          if (mReactionFlags[rIndex].mpNext != NULL) // reactionFlag is not the only one in the linked list
            {
              mFirstReactionFlag = mReactionFlags[rIndex].mpNext;
              mFirstReactionFlag->mpPrev = mFirstReactionFlag;
            }
          else // reactionFlag is the only one in the linked list
            {
              mFirstReactionFlag = NULL;
            }
        }
    }

  mReactionFlags[rIndex].mpPrev = NULL;
  mReactionFlags[rIndex].mpNext = NULL;
  return;
}

/**
 *   Prints out various data on standard output for debugging purposes.
 */
std::ostream & operator<<(std::ostream & os, const CHybridStochFlag & d)
{
  os << "CHybridStochFlag " << std::endl;
  os << "  mIndex: " << d.mIndex << " mValue: " << d.mValue << std::endl;

  if (d.mpPrev != NULL)
    os << "  prevIndex: " << d.mpPrev->mIndex << " prevPointer: " << d.mpPrev << std::endl;
  else
    os << "  prevPointer: NULL" << std::endl;

  if (d.mpNext != NULL)
    os << "  nextIndex: " << d.mpNext->mIndex << " nextPointer: " << d.mpNext << std::endl;
  else
    os << "  nextPointer: NULL" << std::endl;

  return os;
}

std::ostream & operator<<(std::ostream & os, const CHybridBalance & d)
{
  os << "CHybridBalance" << std::endl;
  os << "  mIndex: " << d.mIndex << " mMultiplicity: " << d.mMultiplicity
     << std::endl;
  return os;
}

//virtual
bool CHybridMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CTrajectoryMethod::isValidProblem(pProblem)) return false;

  const CTrajectoryProblem * pTP = dynamic_cast<const CTrajectoryProblem *>(pProblem);

  if (pTP->getDuration() < 0.0)
    {
      //back integration not possible
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 9);
      return false;
    }

  if (mpContainer->getReactions().size() < 1)
    {
      //at least one reaction necessary
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 17);
      return false;
    }

  if (mpContainer->getCountODEs() > 0)
    {
      //ode rule found
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 18);
      return false;
    }

  //TODO: rewrite CModel::suitableForStochasticSimulation() to use
  //      CCopasiMessage
  std::string message = mpContainer->getModel().suitableForStochasticSimulation();

  if (message != "")
    {
      //model not suitable, message describes the problem
      CCopasiMessage(CCopasiMessage::ERROR, message.c_str());
      return false;
    }

  /* Max Internal Steps */
  if (getValue< C_INT32 >("Max Internal Steps") <= 0)
    {
      //max steps should be at least 1
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 15);
      return false;
    }

  /* Lower Limit, Upper Limit */
  mLowerStochLimit = getValue< C_FLOAT64 >("Lower Limit");
  mUpperStochLimit = getValue< C_FLOAT64 >("Upper Limit");

  if (mLowerStochLimit > mUpperStochLimit)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 4, mLowerStochLimit, mUpperStochLimit);
      return false;
    }

  /* Partitioning Interval */
  // nothing to be done here so far

  /* Use Random Seed */
  // should be checked in the widget later on

  /* Random Seed */
  // nothing to be done here

  //events are not supported at the moment
  if (mpContainer->getEvents().size() > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 23, CTaskEnum::MethodName[getSubType()].c_str());
      return false;
    }

  return true;
}
