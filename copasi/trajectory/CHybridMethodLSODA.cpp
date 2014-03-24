// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *   CHybridMethodLSODA
 *
 *   This class implements an hybrid algorithm for the simulation of a
 *   biochemical system over time.
 *
 *   File name: CHybridMethodLSODA.cpp
 *   Author: Juergen Pahle
 *   Email: juergen.pahle@eml-r.villa-bosch.de
 *
 *   Last change: 09, May 2006
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

#include "copasi.h"

#include "CHybridMethodLSODA.h"
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

/**
 *   Default constructor.
 */
CHybridMethodLSODA::CHybridMethodLSODA(const CCopasiContainer * pParent):
  CTrajectoryMethod(CCopasiMethod::hybridLSODA, pParent),
  mNumReactionSpecies(0),
  mMaxSteps(),
  mMaxStepsReached(false),
  mUseRandomSeed(true),
  mRandomSeed(),
  mMaxBalance(),
  mMaxIntBeforeStep(),
  mReactions(),
  mReactionFlags(),
  mFirstReactionFlag(NULL),
  mMetabFlags(),
  mLocalBalances(),
  mLowerStochLimit(),
  mUpperStochLimit(),
  mPartitioningInterval(),
  mStepsAfterPartitionSystem(),
  mStepsize(),
  mMetab2React(),
  mAmu(),
  mAmuOld(),
  mpRandomGenerator(NULL),
  mDG(),
  mUpdateSequences(),
  mPQ(),
  mRestartLSODA(true),
  mpFirstSpecies(NULL),
  mpFirstSpeciesValue(NULL),
  mData(),
  mY(NULL),
  mYdot(),
  mTime(),
  mEndt(),
  mLsodaStatus(),
  mReducedModel(false),
  mRtol(),
  mDefaultAtol(),
  mAtol(),
  mErrorMsg(),
  mLSODA(),
  mState(),
  mDWork(),
  mIWork(),
  mJType(),
  mOutputFile(),
  mOutputFileName(),
  mOutputCounter()
{
  assert((void *) &mData == (void *) &mData.dim);

  mData.pMethod = this;

  mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
  initializeParameter();
}

CHybridMethodLSODA::CHybridMethodLSODA(const CHybridMethodLSODA & src,
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
CHybridMethodLSODA::~CHybridMethodLSODA()
{
  cleanup();
  DESTRUCTOR_TRACE;
}

void CHybridMethodLSODA::initializeParameter()
{
  CCopasiParameter *pParm;

  assertParameter("Max Internal Steps", CCopasiParameter::UINT, (unsigned C_INT32) MAX_STEPS);
  assertParameter("Lower Limit", CCopasiParameter::DOUBLE, (C_FLOAT64) LOWER_STOCH_LIMIT);
  assertParameter("Upper Limit", CCopasiParameter::DOUBLE, (C_FLOAT64) UPPER_STOCH_LIMIT);

  assertParameter("Partitioning Interval", CCopasiParameter::UINT, (unsigned C_INT32) PARTITIONING_INTERVAL);
  assertParameter("Use Random Seed", CCopasiParameter::BOOL, (bool) USE_RANDOM_SEED);
  assertParameter("Random Seed", CCopasiParameter::UINT, (unsigned C_INT32) RANDOM_SEED);

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("HYBRID.MaxSteps")) != NULL)
    {
      setValue("Max Internal Steps", *pParm->getValue().pUINT);
      removeParameter("HYBRID.MaxSteps");

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

      if ((pParm = getParameter("HYBRID.PartitioningInterval")) != NULL)
        {
          setValue("Partitioning Interval", *pParm->getValue().pUINT);
          removeParameter("HYBRID.PartitioningInterval");
        }

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

  /* LSODA ****************************************************************************/

  assertParameter("Partitioning Stepsize",
                  CCopasiParameter::DOUBLE, (C_FLOAT64) PARTITIONING_STEPSIZE);

  assertParameter("Relative Tolerance",
                  CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-006);

  assertParameter("Absolute Tolerance",
                  CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e009);

  assertParameter("Max Internal Steps (LSODA)",
                  CCopasiParameter::UINT, (unsigned C_INT32) 10000);

  // These parameters are no longer supported.
  removeParameter("Adams Max Order");
  removeParameter("BDF Max Order");
}

bool CHybridMethodLSODA::elevateChildren()
{
  initializeParameter();
  return true;
}

/**
 *   Creates a HybridMethodLSODA adequate for the problem.
 */
CHybridMethodLSODA *CHybridMethodLSODA::createHybridMethodLSODA()
{
  C_INT32 result = 1;
  CHybridMethodLSODA * method = NULL;

  switch (result)
    {
        /*    case - 3:        // non-integer stoichometry
        CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 1);
        break;
        case - 2:        // reversible reaction exists
        CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 2);
        break;

        case - 1:        // more than one compartment involved
        CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 3);
        break;*/
      case 1:
      default:
        // Everything alright: Hybrid simulation possible
        method = new CHybridNextReactionLSODAMethod();
        break;
    }

  return method;
}

CTrajectoryMethod::Status CHybridMethodLSODA::step(const double & deltaT)
{
  // write the current state to the model
  //  mpProblem->getModel()->setState(mpCurrentState); // is that correct?

  // check for possible overflows
  size_t i;
  size_t imax;

  // :TODO: Bug 774: This assumes that the number of variable metabs is the number
  // of metabs determined by reaction. In addition they are expected at the beginning of the
  // MetabolitesX which is not the case if we have metabolites of type ODE.
  for (i = 0, imax = mpProblem->getModel()->getNumVariableMetabs(); i < imax; i++)
    if (mpProblem->getModel()->getMetabolitesX()[i]->getValue() >= mMaxIntBeforeStep)
      {
        // throw exception or something like that
      }

  // do several steps
  C_FLOAT64 time = mpProblem->getModel()->getTime();
  C_FLOAT64 endTime = time + deltaT;

  for (i = 0; ((i < mMaxSteps) && (time < endTime)); i++)
    {
      time = doSingleStep(time, endTime);
    }

  //mpCurrentState->setTime(time);

  if ((i >= mMaxSteps) && (!mMaxStepsReached))
    {
      mMaxStepsReached = true; //only report this message once
      CCopasiMessage(CCopasiMessage::WARNING, "maximum number of reaction events was reached in at least one simulation step.\nThat means time intervals in the output may not be what you requested.");
    }

  //the task expects the result in mpCurrentState
  mContainerState = mpContainer->getState();
  *mpContainerStateTime = time;

  return NORMAL;
}

void CHybridMethodLSODA::start(CVectorCore< C_FLOAT64 > & initialState)
{
  mContainerState = initialState;
  mpContainer->setState(mContainerState);

  mRestartLSODA = true;

  mpFirstSpeciesValue = const_cast< C_FLOAT64 *>(mContainerState.array()
                        + mpContainer->getCountFixedEventTargets()
                        + 1 /* Time */
                        + mpContainer->getCountODEs());

  mpFirstSpecies = mpContainer->getMathObject(mpFirstSpeciesValue);

  initMethod(*mpContainerStateTime);

  return;
}

/* PROTECTED METHODS *********************************************************/

/**
 *  Initializes the solver and sets the model to be used.
 *
 *  @param model A reference to an instance of a CModel
 */
void CHybridMethodLSODA::initMethod(C_FLOAT64 start_time)
{
  mReactions = mpContainer->getReactions();
  mAmu.resize(mReactions.size());
  mAmuOld.resize(mReactions.size());

  mNumReactionSpecies = mpContainer->getCountIndependentSpecies() + mpContainer->getCountDependentSpecies();

  /* get configuration data */
  mMaxSteps = * getValue("Max Internal Steps").pUINT;
  mLowerStochLimit = * getValue("Lower Limit").pDOUBLE;
  mUpperStochLimit = * getValue("Upper Limit").pDOUBLE;
  mStepsize = * getValue("Partitioning Stepsize").pDOUBLE;
  mPartitioningInterval = * getValue("Partitioning Interval").pUINT;
  mUseRandomSeed = * getValue("Use Random Seed").pBOOL;
  mRandomSeed = * getValue("Random Seed").pUINT;

  if (mUseRandomSeed) mpRandomGenerator->initialize(mRandomSeed);

  mStepsAfterPartitionSystem = 0;

  setupBalances(); // initialize mLocalBalances and mLocalSubstrates (has to be called first!)
  setupDependencyGraph(); // initialize mDG
  setupMetab2React(); // initialize mMetab2React
  setupPartition(); // initialize mReactionFlags
  setupPriorityQueue(start_time); // initialize mPQ

  mMaxStepsReached = false;

  /* CONFIGURE LSODA ***********************************************************************/

  mData.dim = (C_INT) mContainerState.size();
  mYdot.resize(mData.dim);

  mRtol = * getValue("Relative Tolerance").pUDOUBLE;

  mDefaultAtol = * getValue("Use Default Absolute Tolerance").pBOOL;

  mAtol = mpContainer->initializeAtolVector(* getValue("Absolute Tolerance").pUDOUBLE, false);

  mDWork.resize(22 + mData.dim * std::max<C_INT>(16, mData.dim + 9));
  mDWork[4] = mDWork[5] = mDWork[6] = mDWork[7] = mDWork[8] = mDWork[9] = 0.0;
  mIWork.resize(20 + mData.dim);

  mIWork[4] = mIWork[6] = mIWork[9] = 0;
  mIWork[5] = * getValue("Max Internal Steps (LSODA)").pUINT;
  mIWork[7] = 12;
  mIWork[8] = 5;

  /***********************************************************************************/

  return;
}

/**
 *  Cleans up memory, etc.
 */
void CHybridMethodLSODA::cleanup()
{
  delete mpRandomGenerator;
  mpRandomGenerator = NULL;
  return;
}

/* DETERMINISTIC STUFF *******************************************************/

void CHybridMethodLSODA::EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{static_cast<Data *>((void *) n)->pMethod->evalF(t, y, ydot);}

void CHybridMethodLSODA::evalF(const C_FLOAT64 * t, const C_FLOAT64 * /* y */, C_FLOAT64 * ydot)
{
  size_t i;

  *mpContainerStateTime = *t;
  mpContainer->updateSimulatedValues(false);
  memcpy(ydot, mpContainer->getRate().array(), mData.dim * sizeof(C_FLOAT64));

  // We cannot use the species rates from the container as they are calculated
  // by summing over all reactions.
  CVectorCore< C_FLOAT64 > SpeciesRates(mNumReactionSpecies, ydot + (mpFirstSpeciesValue - mContainerState.array()));
  SpeciesRates = 0.0;

  for (CHybridLSODAStochFlag * j = mFirstReactionFlag; j != NULL; j = j->mpNext)
    {
      CMathReaction & Reaction = mReactions[j->mIndex];
      CMathReaction::Balance::const_iterator itBalance = Reaction.getBalance().begin();
      CMathReaction::Balance::const_iterator endBalance = Reaction.getBalance().end();

      C_FLOAT64 * pParticleFlux = (C_FLOAT64 *) Reaction.getParticleFluxObject()->getValuePointer();

      for (; itBalance != endBalance; ++ itBalance)
        {
          SpeciesRates[itBalance->first - mpFirstSpecies] += floor(itBalance->second + 0.5) * *pParticleFlux;
        }
    }

  return;
}

/**
 *   Integrates the deterministic reactions of the system over the specified
 *   time interval.
 *
 *   @param ds A C_FLOAT64 specifying the stepsize.
 */

void CHybridMethodLSODA::integrateDeterministicPart(C_FLOAT64 deltaT)
{
  CHybridLSODAStochFlag * react = NULL;

  /* RESET LSODA **************************************************************/

  if (mRestartLSODA)
    {
      mRestartLSODA = false;
      mLsodaStatus = 1;
    }

  mState = 1;
  mJType = 2;

  mErrorMsg.str("");
  mLSODA.setOstream(mErrorMsg);

  C_INT one = 1;
  C_INT DSize = (C_INT) mDWork.size();
  C_INT ISize = (C_INT) mIWork.size();

  mY = mContainerState.array();// + mFirstMetabIndex - 1;
  mTime = *mpContainerStateTime;

  C_FLOAT64 EndTime = mTime + deltaT;

  C_FLOAT64 tdist , d__1, d__2, w0;
  tdist = fabs(deltaT);
  d__1 = fabs(mTime), d__2 = fabs(EndTime);
  w0 = std::max(d__1, d__2);

  if (tdist < std::numeric_limits< C_FLOAT64 >::epsilon() * 2. * w0) //just do nothing
    {
      //mTime = mTime + deltaT;
      //mpState->setTime(mTime);
      //*mpCurrentState = *mpState;
      mpProblem->getModel()->setTime(EndTime);

      return;
    }

  if (!mData.dim) //just do nothing if there are no variables
    {
      //mTime = mTime + deltaT;
      mpProblem->getModel()->setTime(EndTime);
      //mpState->setTime(mTime);
      //*mpCurrentState = *mpState;

      return;
    }

  mLSODA(&EvalF , //  1. evaluate F
         &mData.dim, //  2. number of variables
         mY , //  3. the array of current concentrations
         &mTime , //  4. the current time
         &EndTime , //  5. the final time
         &one , //  6. scalar error control
         &mRtol , //  7. relative tolerance array
         mAtol.array() , //  8. absolute tolerance array
         &mState , //  9. output by overshoot & interpolation
         &mLsodaStatus , // 10. the state control variable
         &one , // 11. futher options (one)
         mDWork.array() , // 12. the double work array
         &DSize , // 13. the double work array size
         mIWork.array() , // 14. the int work array
         &ISize , // 15. the int work array size
         NULL , // 16. evaluate J (not given)
         &mJType);        // 17. the type of jacobian calculate (2)

  if (mLsodaStatus == -1) mLsodaStatus = 2;

  if ((mLsodaStatus != 1) && (mLsodaStatus != 2) && (mLsodaStatus != -1))
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 6, mErrorMsg.str().c_str());
    }

  *mpContainerStateTime = mTime;
  mpContainer->updateSimulatedValues(false);

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
void CHybridMethodLSODA::getStochTimeAndIndex(C_FLOAT64 & ds, size_t & rIndex)
{
  ds = mPQ.topKey();
  rIndex = mPQ.topIndex();
  return;
}

/**
 *   Executes the specified reaction in the system once.
 *
 *   @param rIndex A size_t specifying the index of the reaction, which
 *                 will be fired.
 *   @param time   The current time
 */
void CHybridMethodLSODA::fireReaction(size_t rIndex)
{
  mReactions[rIndex].fire();

  // Update all values needed to calculate dependent propensities.
  mpContainer->applyUpdateSequence(mUpdateSequences[rIndex]);

  mRestartLSODA = true;

  return;
}

/**
 *   Updates the priority queue.
 *
 *   @param rIndex A size_t giving the index of the fired reaction (-1, if no
 *                 stochastic reaction has fired)
 *   @param time A C_FLOAT64 holding the current time
 */

void CHybridMethodLSODA::updatePriorityQueue(size_t rIndex, C_FLOAT64 time)
{
  C_FLOAT64 newTime;
  std::set <size_t>::iterator iter, iterEnd;

  if ((rIndex != C_INVALID_INDEX) && (mReactionFlags[rIndex].mpPrev == NULL))
    {
      const std::set <size_t> & DependentReactions = mDG.getDependents(rIndex);
      std::set< size_t >::const_iterator it = DependentReactions.begin();
      std::set< size_t >::const_iterator end = DependentReactions.end();

      // iterate through the set of affected reactions and update the stochastic ones in the priority queue
      for (; it != end; ++it)
        {
          if (mReactionFlags[*it].mpPrev == NULL) // reaction is stochastic!
            {
              mAmuOld[*it] = mAmu[*it];
              calculateAmu(*it);

              if (*it != rIndex)
                {
                  updateTauMu(*it, time);
                }
            }
        }
    }

  // draw new random number and update the reaction just fired
  if ((rIndex != C_INVALID_INDEX) && (mReactionFlags[rIndex].mpPrev == NULL))
    {
      // reaction is stochastic
      newTime = time + generateReactionTime(rIndex);
      mPQ.updateNode(rIndex, newTime);
    }

  return;
}

C_FLOAT64 CHybridMethodLSODA::generateReactionTime(size_t rIndex)
{
  if (mAmu[rIndex] == 0) return std::numeric_limits<C_FLOAT64>::infinity();

  C_FLOAT64 rand2 = mpRandomGenerator->getRandomOO();
  return - 1 * log(rand2) / mAmu[rIndex];
}

/**
 *   Calculates an amu value for a given reaction.
 *
 *   @param rIndex A size_t specifying the reaction to be updated
 */
void CHybridMethodLSODA::calculateAmu(size_t rIndex)
{
  CMathObject * pPropensity = const_cast< CMathObject * >(mReactions[rIndex].getPropensityObject());
  pPropensity->calculate();
  mAmu[rIndex] = * (C_FLOAT64 *) pPropensity->getValuePointer();
}

/**
 *   Updates the putative reaction time of a stochastic reaction in the
 *   priority queue. The corresponding amu and amu_old must be set prior to
 *   the call of this method.
 *
 *   @param rIndex A size_t specifying the index of the reaction
 */
void CHybridMethodLSODA::updateTauMu(size_t rIndex, C_FLOAT64 time)
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
C_INT32 CHybridMethodLSODA::checkModel(CModel * model)
{
  CCopasiVectorNS <CReaction> * mpReactions = &model->getReactions();
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
 *   Sets up an internal representation of the balances for each reaction.
 *   This is done in order to be able to deal with fixed metabolites and
 *   to avoid a time consuming search for the indices of metabolites in the
 *   model.
 */
void CHybridMethodLSODA::setupBalances()
{
  size_t i, j;
  CHybridLSODABalance newElement;
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
  mMaxIntBeforeStep = INT_MAX - 1 - mMaxSteps * mMaxBalance;

  return;
}

/**
 *   Sets up the dependency graph.
 */
void CHybridMethodLSODA::setupDependencyGraph()
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

          mpContainer->getTransientDependencies().getUpdateSequence(*itUpdateSequence, CMath::Default, Changed, Requested);

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
 *   Creates for each metabolite a set of reaction indices. If the metabolite
 *   participates in a reaction as substrate or product (that means:
 *   balance != 0) this reaction is added to the corresponding set.
 */
void CHybridMethodLSODA::setupMetab2React()
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

/**
 *   Creates an initial partitioning of the system. Deterministic and
 *   stochastic reactions are determined. The vector mReactionFlags and
 *   the vector mMetabFlags are initialized.
 */
void CHybridMethodLSODA::setupPartition()
{
  size_t i, j;
  CHybridLSODAStochFlag * prevFlag;
  C_FLOAT64 averageStochLimit = (mUpperStochLimit + mLowerStochLimit) / 2;

  // initialize vector mMetabFlags
  mMetabFlags.clear();
  mMetabFlags.resize(mNumReactionSpecies);

  C_FLOAT64 * pSpecies = mpFirstSpeciesValue;

  for (i = 0; i < mMetabFlags.size(); ++pSpecies, i++)
    {
      if (*pSpecies < averageStochLimit)
        {
          mMetabFlags[i] = LOW;
          *pSpecies = floor(*pSpecies + 0.5);
        }
      else
        mMetabFlags[i] = HIGH;
    }

  // initialize vector mReactionFlags
  mReactionFlags.clear();
  mReactionFlags.resize(mLocalBalances.size());

  for (i = 0; i < mLocalBalances.size(); i++)
    {
      mReactionFlags[i].mIndex = i;
      mReactionFlags[i].mValue = 0;

      for (j = 0; j < mLocalBalances[i].size(); j++)
        {
          if (mMetabFlags[mLocalBalances[i][j].mIndex] == LOW)
            {
              mReactionFlags[i].mValue++;
            }
        }
    }

  mFirstReactionFlag = NULL;
  prevFlag = NULL;

  for (i = 0; i < mLocalBalances.size(); i++)
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
void CHybridMethodLSODA::setupPriorityQueue(C_FLOAT64 startTime)
{
  size_t i;
  C_FLOAT64 time;

  mPQ.clear();
  mPQ.initializeIndexPointer(mReactions.size());

  for (i = 0; i < mReactions.size(); i++)
    {
      if (mReactionFlags[i].mpPrev == NULL) // Reaction is stochastic!
        {
          calculateAmu(i);
          time = startTime + generateReactionTime(i);
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
void CHybridMethodLSODA::partitionSystem()
{
  size_t i;
  std::set <size_t>::iterator iter, iterEnd;
  C_FLOAT64 key;

  C_FLOAT64 * pSpecies = mpFirstSpeciesValue;
  std::vector< size_t > NewLowSpecies;

  for (i = 0; i < mNumReactionSpecies; i++, ++pSpecies)
    {
      if ((mMetabFlags[i] == LOW) && (*pSpecies >= mUpperStochLimit))
        {
          mRestartLSODA = true;
          mMetabFlags[i] = HIGH;

          // go through all corresponding reactions and update flags
          for (iter = mMetab2React[i].begin(), iterEnd = mMetab2React[i].end(); iter != iterEnd; iter++)
            {
              mReactionFlags[*iter].mValue--;

              // if reaction gets deterministic, insert it into the linked list of deterministic reactions
              if (mReactionFlags[*iter].mValue == 0)
                {
                  insertDeterministicReaction(*iter);
                  mPQ.removeStochReaction(*iter);
                }
            }
        }

      if ((mMetabFlags[i] == HIGH) && (*pSpecies < mLowerStochLimit))
        {
          mRestartLSODA = true;
          mMetabFlags[i] = LOW;
          *pSpecies = floor(*pSpecies + 0.5);

          NewLowSpecies.push_back(i);
        }
    }

  std::vector< size_t >::const_iterator itNewLowSpecies = NewLowSpecies.begin();
  std::vector< size_t >::const_iterator endNewLowSpecies = NewLowSpecies.end();

  if (itNewLowSpecies != endNewLowSpecies)
    {
      mpContainer->updateSimulatedValues(false);
    }

  for (; itNewLowSpecies != endNewLowSpecies; ++itNewLowSpecies)
    {
      // go through all corresponding reactions and update flags
      for (iter = mMetab2React[*itNewLowSpecies].begin(), iterEnd = mMetab2React[*itNewLowSpecies].end(); iter != iterEnd; iter++)
        {
          if (mReactionFlags[*iter].mValue == 0)
            {
              removeDeterministicReaction(*iter);
              /*
                mPQ.insertStochReaction(*iter, 1234567.8);  // juergen: have to beautify this, number has to be the biggest C_FLOAT64 !!!
              */
              calculateAmu(*iter);
              mAmuOld[*iter] = mAmu[*iter];

              key = *mpContainerStateTime + generateReactionTime(*iter);

              mPQ.insertStochReaction(*iter, key);
            }

          mReactionFlags[*iter].mValue++;
        }
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
void CHybridMethodLSODA::insertDeterministicReaction(size_t rIndex)
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
void CHybridMethodLSODA::removeDeterministicReaction(size_t rIndex)
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
 *   Prints out data on standard output. Deprecated.
 */
void CHybridMethodLSODA::outputData(std::ostream & os, C_INT32 mode)
{
  static unsigned C_INT32 counter = 0;
  size_t i;

  switch (mode)
    {
      case 0:

        if (mOutputCounter == (counter++))
          {
            counter = 0;
            os << *mpContainerStateTime << " : ";

            for (i = 0; i < mNumReactionSpecies; i++)
              {
                os << *(mpFirstSpeciesValue + i) << " ";
              }

            os << std::endl;
          }

        break;

      case 1:
        os << *mpContainerStateTime << " : ";

        for (i = 0; i < mNumReactionSpecies; i++)
          {
            os << *(mpFirstSpeciesValue + i) << " ";
          }

        os << std::endl;
        break;

      default:
        ;
    }

  return;
}

/**
 *   Prints out various data on standard output for debugging purposes.
 */
void CHybridMethodLSODA::outputDebug(std::ostream & os, size_t level)
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
        os << "mMaxIntBeforeStep: " << mMaxIntBeforeStep << std::endl;
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

        os << "mFirstReactionFlag: " << std::endl;
        if (mFirstReactionFlag == NULL) os << "NULL" << std::endl; else os << *mFirstReactionFlag;

        os << "mMetabFlags: " << std::endl;

        for (i = 0; i < mMetabFlags.size(); i++)
          {
            if (mMetabFlags[i] == LOW)
              os << "LOW ";
            else
              os << "HIGH ";
          }

        os << std::endl;
        os << "mLocalBalances: " << std::endl;

        for (i = 0; i < mLocalBalances.size(); i++)
          {
            for (j = 0; j < mLocalBalances[i].size(); j++)
              os << mLocalBalances[i][j];

            os << std::endl;
          }

        os << "mLowerStochLimit: " << mLowerStochLimit << std::endl;
        os << "mUpperStochLimit: " << mUpperStochLimit << std::endl;
        //deprecated:      os << "mOutputCounter: " << mOutputCounter << endl;
        os << "mPartitioningInterval: " << mPartitioningInterval << std::endl;
        os << "mStepsAfterPartitionSystem: " << mStepsAfterPartitionSystem << std::endl;
        os << "mStepsize: " << mStepsize << std::endl;
        os << "mMetab2React: " << std::endl;

        for (i = 0; i < mMetab2React.size(); i++)
          {
            os << i << ": ";

            for (iter = mMetab2React[i].begin(), iterEnd = mMetab2React[i].end(); iter != iterEnd; ++iter)
              os << *iter << " ";

            os << std::endl;
          }

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

        os << "mReactionFlags: " << std::endl;

        for (i = 0; i < mLocalBalances.size(); i++)
          os << mReactionFlags[i];

        os << "mFirstReactionFlag: " << std::endl;
        if (mFirstReactionFlag == NULL) os << "NULL" << std::endl; else os << *mFirstReactionFlag;

        os << "mMetabFlags: " << std::endl;

        for (i = 0; i < mMetabFlags.size(); i++)
          {
            if (mMetabFlags[i] == LOW)
              os << "LOW ";
            else
              os << "HIGH ";
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

std::ostream & operator<<(std::ostream & os, const CHybridLSODAStochFlag & d)
{
  os << "CHybridLSODAStochFlag " << std::endl;
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

std::ostream & operator<<(std::ostream & os, const CHybridLSODABalance & d)
{
  os << "CHybridLSODABalance" << std::endl;
  os << "  mIndex: " << d.mIndex << " mMultiplicity: " << d.mMultiplicity
     << " mpMetabolite: " << d.mpMetabolite << std::endl;
  return os;
}

//virtual
bool CHybridMethodLSODA::isValidProblem(const CCopasiProblem * pProblem)
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

  mLowerStochLimit = * getValue("Lower Limit").pDOUBLE;
  mUpperStochLimit = * getValue("Upper Limit").pDOUBLE;

  if (mLowerStochLimit > mUpperStochLimit)
    CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 4, mLowerStochLimit, mUpperStochLimit);

  //events are not supported at the moment
  if (pTP->getModel()->getEvents().size() > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 23);
      return false;
    }

  return true;
}

//static
bool CHybridMethodLSODA::modelHasAssignments(const CModel* pModel)
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
