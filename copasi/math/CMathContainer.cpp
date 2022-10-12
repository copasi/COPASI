// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#define JIT_IMPLEMENTATION

#include "copasi/copasi.h"

#include "copasi/math/CMathContainer.h"
#include "copasi/math/CMathExpression.h"
#include "copasi/math/CMathEventQueue.h"
#include "copasi/math/CMathUpdateSequence.h"
#include "copasi/math/CJitCompiler.h"

#include "copasi/model/CModel.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CObjectLists.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/utilities/CNodeIterator.h"
#include "copasi/utilities/dgemm.h"
#include "copasi/randomGenerator/CRandom.h"
#include "copasi/lapack/blaswrap.h"

// Uncomment this line below to get debug print out.
// #define DEBUG_OUTPUT 1

// static
void CMathContainer::createRelocation(const size_t & newSize, const size_t & oldSize,
                                      CMath::sRelocate & currentRelocation,
                                      std::vector< CMath::sRelocate > & relocations,
                                      const bool & modifiedAtEnd)
{
  if (newSize != oldSize)
    {
      // Size modifications are made at the end of the current section
      if (modifiedAtEnd)
        {
          currentRelocation.pValueEnd = currentRelocation.pValueEnd + std::min(newSize, oldSize);
          currentRelocation.pObjectEnd = currentRelocation.pObjectEnd + std::min(newSize, oldSize);

          if (currentRelocation.pValueStart != currentRelocation.pValueEnd)
            {
              relocations.push_back(currentRelocation);
            }

          currentRelocation.pValueStart = currentRelocation.pValueEnd - std::min(newSize, oldSize) + oldSize;
          currentRelocation.pObjectStart = currentRelocation.pObjectEnd - std::min(newSize, oldSize) + oldSize;
          currentRelocation.pValueEnd = currentRelocation.pValueStart;
          currentRelocation.pObjectEnd = currentRelocation.pObjectStart;
          currentRelocation.offset += (newSize - oldSize);
        }
      // Size modifications are made at the beginning of the current section
      else
        {
          if (currentRelocation.pValueStart != currentRelocation.pValueEnd)
            {
              relocations.push_back(currentRelocation);
            }

          currentRelocation.pValueEnd += oldSize;
          currentRelocation.pObjectEnd += oldSize;
          currentRelocation.pValueStart = currentRelocation.pValueEnd - std::min(newSize, oldSize);
          currentRelocation.pObjectStart = currentRelocation.pObjectEnd - std::min(newSize, oldSize);
          currentRelocation.offset += (newSize - oldSize);
        }
    }
  else if (newSize > 0)
    {
      currentRelocation.pValueEnd += newSize;
      currentRelocation.pObjectEnd += newSize;
    }
}

void CMathContainer::relocateUpdateSequence(CCore::CUpdateSequence & sequence,
    const std::vector< CMath::sRelocate > & relocations) const
{
  CCore::CUpdateSequence::iterator it = sequence.begin();
  CCore::CUpdateSequence::iterator end = sequence.end();

  for (; it != end; ++it)
    {
      relocateObject(*it, relocations);
    }

  if (mOldObjects.array() == mObjects.array())
    {
      return;
    }

  std::vector< CObjectInterface * > Clean;
  it = sequence.begin();
  end = sequence.end();

  for (; it != end; ++it)
    if (*it != NULL)
      {
        Clean.push_back(*it);
      }

  sequence = Clean;
}

void CMathContainer::relocateObjectSet(CObjectInterface::ObjectSet & objectSet,
                                       const std::vector< CMath::sRelocate > & relocations) const
{
  CObjectInterface::ObjectSet ObjectSet;
  CObjectInterface::ObjectSet::iterator it = objectSet.begin();
  CObjectInterface::ObjectSet::iterator end = objectSet.end();

  for (; it != end; ++it)
    {
      CObjectInterface * pObject = const_cast< CObjectInterface * >(*it);
      relocateObject(pObject, relocations);

      if (pObject != NULL)
        {
          ObjectSet.insert(pObject);
        }
    }

  objectSet = ObjectSet;
}

void CMathContainer::relocateValue(C_FLOAT64 *& pValue,
                                   const std::vector< CMath::sRelocate > & relocations) const
{
  std::vector< CMath::sRelocate >::const_iterator it = relocations.begin();
  std::vector< CMath::sRelocate >::const_iterator end = relocations.end();

  for (; it != end; ++it)
    if (it->pValueStart <= pValue && pValue < it->pValueEnd)
      {
        pValue = it->pNewValue + (pValue - it->pOldValue) + it->offset;
        return;
      }

  if (mOldValues.array() == mValues.array()) return;

  const C_FLOAT64 * pBegin = mOldValues.array();
  const C_FLOAT64 * pEnd = pBegin + mOldValues.size();

  if (pBegin  <= pValue && pValue < pEnd)
    {
      pValue = NULL;
    }
}

void CMathContainer::relocateValue(const C_FLOAT64 *& pValue, const std::vector< CMath::sRelocate > & relocations) const
{
  relocateValue(const_cast< C_FLOAT64 *& >(pValue), relocations);
}

void CMathContainer::relocateObject(CObjectInterface *& pObject,
                                    const std::vector< CMath::sRelocate > & relocations) const
{
  if (pObject == NULL ||
      pObject == pObject->getDataObject())
    {
      return;
    }

  CMathObject * pMathObject = static_cast< CMathObject * >(pObject);
  relocateObject(pMathObject, relocations);

  pObject = pMathObject;
}

void CMathContainer::relocateObject(const CObjectInterface *& pObject, const std::vector< CMath::sRelocate > & relocations) const
{
  relocateObject(const_cast< CObjectInterface *& >(pObject), relocations);
}

void CMathContainer::relocateObject(CMathObject *& pObject, const std::vector< CMath::sRelocate > & relocations) const
{
  if (pObject == NULL) return;

  std::vector< CMath::sRelocate >::const_iterator it = relocations.begin();
  std::vector< CMath::sRelocate >::const_iterator end = relocations.end();

  for (; it != end; ++it)
    if (it->pObjectStart <= pObject && pObject < it->pObjectEnd)
      {
        pObject = it->pNewObject + (pObject - it->pOldObject) + it->offset;
        return;
      }

  if (mOldObjects.array() == mObjects.array()) return;

  const CMathObject * pBegin = mOldObjects.array();
  const CMathObject * pEnd = pBegin + mOldObjects.size();

  if (pBegin  <= pObject && pObject < pEnd)
    {
      pObject = NULL;
    }
}

void CMathContainer::relocateObject(const CMathObject *& pObject, const std::vector< CMath::sRelocate > & relocations) const
{
  relocateObject(const_cast< CMathObject *& >(pObject), relocations);
}

static C_FLOAT64 InvalidValue;

CMathContainer::CMathContainer()
  : CDataContainer("Math Container", NULL, "CMathContainer")
  , mpModel(NULL)
  , mpAvogadro(NULL)
  , mpQuantity2NumberFactor(NULL)
  , mRandom("Random", this, InvalidValue)
  , mpProcessQueue(new CMathEventQueue(*this))
  , mpRandomGenerator(CRandom::createGenerator())
  , mValues()
  , mpValuesBuffer(NULL)
  , mInitialExtensiveValues()
  , mInitialIntensiveValues()
  , mInitialExtensiveRates()
  , mInitialIntensiveRates()
  , mInitialParticleFluxes()
  , mInitialFluxes()
  , mInitialTotalMasses()
  , mInitialEventTriggers()
  , mExtensiveValues()
  , mIntensiveValues()
  , mExtensiveRates()
  , mIntensiveRates()
  , mParticleFluxes()
  , mFluxes()
  , mTotalMasses()
  , mEventTriggers()
  , mExtensiveNoise()
  , mIntensiveNoise()
  , mReactionNoise()
  , mReactionParticleNoise()
  , mEventDelays()
  , mEventPriorities()
  , mEventAssignments()
  , mEventRoots()
  , mEventRootStates()
  , mPropensities()
  , mDependentMasses()
  , mDiscontinuous()
  , mDelayValues()
  , mDelayLags()
  , mTransitionTimes()
  , mInitialState()
  , mCompleteInitialState()
  , mState()
  , mStateReduced()
  , mHistory()
  , mHistoryReduced()
  , mRate()
  , mRateReduced()
  , mNoiseReduced()
  , mInitialDependencies(this)
  , mTransientDependencies(this)
  , mUpdateSequences()
  , mSynchronizeInitialValuesSequenceExtensive()
  , mSynchronizeInitialValuesSequenceIntensive()
  , mApplyInitialValuesSequence()
  , mSimulationValuesSequence()
  , mSimulationValuesSequenceReduced()
  , mRootSequence()
  , mRootSequenceReduced()
  , mNoiseSequence()
  , mNoiseSequenceReduced()
  , mPrioritySequence()
  , mTransientDataObjectSequence()
  , mInitialStateValueExtensive()
  , mInitialStateValueIntensive()
  , mInitialStateValueAll()
  , mStateValues()
  , mReducedStateValues()
  , mSimulationRequiredValues()
  , mObjects()
  , mpObjectsBuffer(NULL)
  , mEvents()
  , mReactions()
  , mRootIsDiscrete()
  , mRootIsTimeDependent()
  , mRootProcessors()
  , mRootDerivativesState()
  , mRootDerivatives()
  , mCreateDiscontinuousPointer()
  , mDataObject2MathObject()
  , mDataValue2MathObject()
  , mDataValue2DataObject()
  , mDiscontinuityEvents("Discontinuities", this)
  , mDiscontinuityInfix2Object()
  , mTriggerInfix2Event()
  , mDelays()
  , mIsAutonomous(true)
  , mSize()
  , mNoiseInputObjects()
  , mNumTotalRootsIgnored(0)
  , mValueChangeProhibited()
#ifdef USE_JIT
  , mpJITCompiler(CJitCompiler::create())
#endif
  , mCompileTime()
{
  memset(&mSize, 0, sizeof(mSize));
}

CMathContainer::CMathContainer(CModel & model)
  : CDataContainer("Math Container", NULL, "CMathContainer")
  , mpModel(&model)
  , mpAvogadro(NULL)
  , mpQuantity2NumberFactor(NULL)
  , mRandom("Random", this, InvalidValue)
  , mpProcessQueue(new CMathEventQueue(*this))
  , mpRandomGenerator(CRandom::createGenerator())
  , mValues()
  , mOldValues()
  , mpValuesBuffer(NULL)
  , mInitialExtensiveValues()
  , mInitialIntensiveValues()
  , mInitialExtensiveRates()
  , mInitialIntensiveRates()
  , mInitialParticleFluxes()
  , mInitialFluxes()
  , mInitialTotalMasses()
  , mInitialEventTriggers()
  , mExtensiveValues()
  , mIntensiveValues()
  , mExtensiveRates()
  , mIntensiveRates()
  , mParticleFluxes()
  , mFluxes()
  , mTotalMasses()
  , mEventTriggers()
  , mExtensiveNoise()
  , mIntensiveNoise()
  , mReactionNoise()
  , mReactionParticleNoise()
  , mEventDelays()
  , mEventPriorities()
  , mEventAssignments()
  , mEventRoots()
  , mEventRootStates()
  , mPropensities()
  , mDependentMasses()
  , mDiscontinuous()
  , mDelayValues()
  , mDelayLags()
  , mTransitionTimes()
  , mInitialState()
  , mCompleteInitialState()
  , mState()
  , mStateReduced()
  , mHistory()
  , mHistoryReduced()
  , mRate()
  , mRateReduced()
  , mNoiseReduced()
  , mInitialDependencies(this)
  , mTransientDependencies(this)
  , mUpdateSequences()
  , mSynchronizeInitialValuesSequenceExtensive()
  , mSynchronizeInitialValuesSequenceIntensive()
  , mApplyInitialValuesSequence()
  , mSimulationValuesSequence()
  , mSimulationValuesSequenceReduced()
  , mRootSequence()
  , mRootSequenceReduced()
  , mNoiseSequence()
  , mNoiseSequenceReduced()
  , mPrioritySequence()
  , mTransientDataObjectSequence()
  , mInitialStateValueExtensive()
  , mInitialStateValueIntensive()
  , mInitialStateValueAll()
  , mStateValues()
  , mReducedStateValues()
  , mSimulationRequiredValues()
  , mObjects()
  , mOldObjects()
  , mpObjectsBuffer(NULL)
  , mEvents()
  , mReactions()
  , mRootIsDiscrete()
  , mRootIsTimeDependent()
  , mRootProcessors()
  , mRootDerivativesState()
  , mRootDerivatives()
  , mDataObject2MathObject()
  , mDataValue2MathObject()
  , mDataValue2DataObject()
  , mDiscontinuityEvents("Discontinuities", this)
  , mDiscontinuityInfix2Object()
  , mTriggerInfix2Event()
  , mRootCount2Events()
  , mDelays()
  , mIsAutonomous(true)
  , mSize()
  , mNoiseInputObjects()
  , mNumTotalRootsIgnored(0)
  , mValueChangeProhibited()
#ifdef USE_JIT
  , mpJITCompiler(CJitCompiler::create())
#endif
  , mCompileTime()
{
  memset(&mSize, 0, sizeof(mSize));

  // We do not want the model to know about the math container therefore we
  // do not use &model in the constructor of CDataContainer
  setObjectParent(mpModel);

  mpAvogadro = CObjectInterface::DataObject(mpModel->getObject(CCommonName("Reference=Avogadro Constant")));
  mDataValue2DataObject[(C_FLOAT64 *) mpAvogadro->getValuePointer()] = const_cast< CDataObject * >(mpAvogadro);

  mpQuantity2NumberFactor = CObjectInterface::DataObject(mpModel->getObject(CCommonName("Reference=Quantity Conversion Factor")));
  mDataValue2DataObject[(C_FLOAT64 *) mpQuantity2NumberFactor->getValuePointer()] = const_cast< CDataObject * >(mpQuantity2NumberFactor);
}

CMathContainer::CMathContainer(const CMathContainer & src)
  : CDataContainer(src, NULL)
  , mpModel(src.mpModel)
  , mpAvogadro(src.mpAvogadro)
  , mpQuantity2NumberFactor(src.mpQuantity2NumberFactor)
  , mRandom("Random", this, InvalidValue)
  , mpProcessQueue(new CMathEventQueue(*this))
  , mpRandomGenerator(CRandom::createGenerator())
  , mValues()
  , mOldValues()
  , mpValuesBuffer(src.mpValuesBuffer)
  , mInitialExtensiveValues()
  , mInitialIntensiveValues()
  , mInitialExtensiveRates()
  , mInitialIntensiveRates()
  , mInitialParticleFluxes()
  , mInitialFluxes()
  , mInitialTotalMasses()
  , mInitialEventTriggers()
  , mExtensiveValues()
  , mIntensiveValues()
  , mExtensiveRates()
  , mIntensiveRates()
  , mParticleFluxes()
  , mFluxes()
  , mTotalMasses()
  , mEventTriggers()
  , mExtensiveNoise()
  , mIntensiveNoise()
  , mReactionNoise()
  , mReactionParticleNoise()
  , mEventDelays()
  , mEventPriorities()
  , mEventAssignments()
  , mEventRoots()
  , mEventRootStates()
  , mPropensities()
  , mDependentMasses()
  , mDiscontinuous()
  , mDelayValues()
  , mDelayLags()
  , mInitialState()
  , mCompleteInitialState()
  , mState()
  , mStateReduced()
  , mHistory(src.mHistory)
  , mHistoryReduced()
  , mRate()
  , mRateReduced()
  , mNoiseReduced()
  , mInitialDependencies(src.mInitialDependencies, this)
  , mTransientDependencies(src.mTransientDependencies, this)
  , mUpdateSequences()
  , mSynchronizeInitialValuesSequenceExtensive(src.mSynchronizeInitialValuesSequenceExtensive, this)
  , mSynchronizeInitialValuesSequenceIntensive(src.mSynchronizeInitialValuesSequenceIntensive, this)
  , mApplyInitialValuesSequence(src.mApplyInitialValuesSequence, this)
  , mSimulationValuesSequence(src.mSimulationValuesSequence, this)
  , mSimulationValuesSequenceReduced(src.mSimulationValuesSequenceReduced, this)
  , mRootSequence(src.mRootSequence, this)
  , mRootSequenceReduced(src.mRootSequenceReduced, this)
  , mNoiseSequence(src.mNoiseSequence, this)
  , mNoiseSequenceReduced(src.mNoiseSequenceReduced, this)
  , mPrioritySequence(src.mPrioritySequence, this)
  , mTransientDataObjectSequence(src.mTransientDataObjectSequence, this)
  , mInitialStateValueExtensive(src.mInitialStateValueExtensive)
  , mInitialStateValueIntensive(src.mInitialStateValueIntensive)
  , mInitialStateValueAll(src.mInitialStateValueAll)
  , mStateValues(src.mStateValues)
  , mReducedStateValues(src.mReducedStateValues)
  , mSimulationRequiredValues(src.mSimulationRequiredValues)
  , mObjects()
  , mOldObjects()
  , mpObjectsBuffer(src.mpObjectsBuffer)
  , mEvents()
  , mReactions()
  , mRootIsDiscrete(src.mRootIsDiscrete)
  , mRootIsTimeDependent(src.mRootIsTimeDependent)
  , mRootProcessors(src.mRootProcessors)
  , mRootDerivativesState(src.mRootDerivativesState)
  , mRootDerivatives(src.mRootDerivatives)
  , mDataObject2MathObject(src.mDataObject2MathObject)
  , mDataValue2MathObject(src.mDataValue2MathObject)
  , mDataValue2DataObject(src.mDataValue2DataObject)
  , mDiscontinuityEvents("Discontinuities", this)
  , mDiscontinuityInfix2Object()
  , mTriggerInfix2Event()
  , mRootCount2Events()
  , mDelays()
  , mIsAutonomous(src.mIsAutonomous)
  , mSize(src.mSize)
  , mNoiseInputObjects(src.mNoiseInputObjects)
  , mNumTotalRootsIgnored(src.mNumTotalRootsIgnored)
  , mValueChangeProhibited(src.mValueChangeProhibited)
#ifdef USE_JIT
  , mpJITCompiler(src.mpJITCompiler->copy())
#endif
  , mCompileTime(src.mCompileTime)
{
  // We do not want the model to know about the math container therefore we
  // do not use &model in the constructor of CDataContainer
  setObjectParent(mpModel);

  sSize size = mSize;
  size_t ObjectCount = src.mValues.size();

  mValues.initialize(ObjectCount, mpValuesBuffer);
  mOldValues.initialize(ObjectCount, mpValuesBuffer);

  mObjects.initialize(ObjectCount, mpObjectsBuffer);
  mOldObjects.initialize(ObjectCount, mpObjectsBuffer);

  mEvents.initialize(mSize.nEvents, new CMathEvent[mSize.nEvents]);
  CMathEvent * pEvent = mEvents.begin();
  CMathEvent * pEventEnd = mEvents.end();
  const CMathEvent * pEventSrc = src.mEvents.begin();

  for (; pEvent != pEventEnd; ++pEvent, ++pEventSrc)
    pEvent->copy(*pEventSrc, *this);

  mReactions.initialize(mSize.nReactions, new CMathReaction[mSize.nReactions]);
  CMathReaction * pReaction = mReactions.begin();
  CMathReaction * pReactionEnd = mReactions.end();
  const CMathReaction * pReactionSrc = src.mReactions.begin();

  for (; pReaction != pReactionEnd; ++pReaction, ++pReactionSrc)
    pReaction->copy(*pReactionSrc, *this);

  mDelays.initialize(mSize.nDelayLags, new CMathDelay[mSize.nDelayLags]);
  CMathDelay * pDelay = mDelays.begin();
  CMathDelay * pDelayEnd = mDelays.end();
  const CMathDelay * pDelaySrc = src.mDelays.begin();

  for (; pDelay != pDelayEnd; ++pDelay, ++pDelaySrc)
    pDelay->copy(*pDelaySrc, *this);

  std::vector< CMath::sRelocate > Relocations = move(size);

  // We must not call finishResize() as that would release the src values and objects;
  mOldValues.initialize(mValues);
  mOldObjects.initialize(mObjects);

  map();

#ifdef USE_JIT
  CMathObject *pObject = mObjects.array();
  CMathObject *pObjectEnd = pObject + mObjects.size();

  for (; pObject != pObjectEnd; ++pObject)
    {
      pObject->setJITCompiler(*mpJITCompiler);
    }

  try
    {
      mpJITCompiler->compile();
    }
  catch (...)
    {}

#endif
}

CMathContainer::~CMathContainer()
{
  pdelete(mpProcessQueue);
  pdelete(mpRandomGenerator);
  pdeletev(mpValuesBuffer)
  pdeletev(mpObjectsBuffer)

  if (mEvents.array()) delete [] mEvents.array();

  if (mReactions.array()) delete [] mReactions.array();

  if (mDelays.array()) delete [] mDelays.array();

  while (mUpdateSequences.size())
    {
      deregisterUpdateSequence(*mUpdateSequences.begin());
    }

#ifdef USE_JIT
  pdelete(mpJITCompiler);
#endif

  setObjectParent(NULL);
}

bool CMathContainer::operator == (const CMathContainer & rhs)
{
  return mpModel == rhs.mpModel && mCompileTime == rhs.mCompileTime;
}

CMathContainer * CMathContainer::copy() const
{
  return new CMathContainer(*this);
}

const CVectorCore< C_FLOAT64 > & CMathContainer::getValues() const
{
  return mValues;
}

CVectorCore< C_FLOAT64 > & CMathContainer::getValues()
{
  return mValues;
}

void CMathContainer::setValues(const CVectorCore< C_FLOAT64 > & values)
{
  assert(mValues.size() == values.size());

  mValues = values;
}

const CVectorCore< C_FLOAT64 > & CMathContainer::getInitialState() const
{
  return mInitialState;
}

CVectorCore< C_FLOAT64 > & CMathContainer::getInitialState()
{
  return mInitialState;
}

void CMathContainer::setInitialState(const CVectorCore< C_FLOAT64 > & initialState)
{
  assert(mInitialState.size() == initialState.size() ||
         mState.size()  == initialState.size());

  if (mInitialState.size() == initialState.size())
    {
      memcpy(mInitialState.array(), initialState.array(), initialState.size() * sizeof(C_FLOAT64));
    }
  else
    {
      memcpy(mInitialState.array() + mSize.nFixed, initialState.array(), initialState.size() * sizeof(C_FLOAT64));
    }
}

const CVectorCore< C_FLOAT64 > & CMathContainer::getCompleteInitialState() const
{
  return mCompleteInitialState;
}

void CMathContainer::setCompleteInitialState(const CVectorCore< C_FLOAT64 > & completeInitialState)
{
  assert(mCompleteInitialState.size() == completeInitialState.size());

  memcpy(mCompleteInitialState.array(), completeInitialState.array(), completeInitialState.size() * sizeof(C_FLOAT64));
}

const CVectorCore< C_FLOAT64 > & CMathContainer::getState(const bool & reduced) const
{
  if (reduced)
    return mStateReduced;

  return mState;
}

void CMathContainer::setState(const CVectorCore< C_FLOAT64 > & state)
{
  assert(mState.size() >= state.size());

  // We must only copy if the states are different.
  if (mState.array() != state.array())
    {
      memcpy(mState.array(), state.array(), state.size() * sizeof(C_FLOAT64));
    }
}

bool CMathContainer::isStateValid() const
{
  const C_FLOAT64 * pIt = mState.array();
  const C_FLOAT64 * pEnd = pIt + mState.size();

  for (; pIt != pEnd; ++pIt)
    {
      if (std::isnan(*pIt))
        {
          return false;
        }
    }

  return true;
}

const bool & CMathContainer::isAutonomous() const
{
  return mIsAutonomous;
}

bool CMathContainer::areObjectsConstant(const CObjectInterface::ObjectSet & objects) const
{
  // Check whether all objects are constant, i.e., if they are state values or depend on any state value.
  CObjectInterface::ObjectSet::const_iterator it1 = objects.begin();
  CObjectInterface::ObjectSet::const_iterator end1 = objects.end();
  CObjectInterface::ObjectSet::const_iterator it2 = mStateValues.begin();
  CObjectInterface::ObjectSet::const_iterator end2 = mStateValues.end();

  while (it1 != end1 && it2 != end2)
    {
      if (*it1 < *it2)
        {
          ++it1;
        }
      else if (*it2 < *it1)
        {
          ++it2;
        }
      else
        {
          return false;
        }
    }

  CCore::CUpdateSequence UpdateSequence;

  mTransientDependencies.getUpdateSequence(UpdateSequence, CCore::SimulationContextFlag(CCore::SimulationContext::UpdateMoieties) | CCore::SimulationContext::EventHandling, mStateValues, objects);

  return UpdateSequence.empty();
}

const C_FLOAT64 & CMathContainer::getQuantity2NumberFactor() const
{
  return *(const C_FLOAT64 *)mpQuantity2NumberFactor->getValuePointer();
}

const CObjectInterface * CMathContainer::getQuantity2NumberFactorObject() const
{
  return mpQuantity2NumberFactor;
}

const CMathHistoryCore & CMathContainer::getHistory(const bool & reduced) const
{
  if (reduced)
    {
      return mHistoryReduced;
    }

  return mHistory;
}

void CMathContainer::setHistory(const CMathHistoryCore & history)
{
  assert(history.size() == mHistory.size() &&
         history.rows() == mHistory.rows() &&
         (history.cols() == mHistory.cols() ||
          history.cols() == mHistoryReduced.cols()));

  if (history.cols() < mHistory.cols())
    {
      mHistoryReduced = history;
    }
  else
    {
      mHistory = history;
    }
}

const CVectorCore< C_FLOAT64 > & CMathContainer::getDelayLags() const
{
  return mDelayLags;
}

CVector< C_FLOAT64 > CMathContainer::initializeAtolVector(const C_FLOAT64 & atol, const bool & reduced) const
{
  CVector< C_FLOAT64 > Atol;

  Atol.resize(getState(reduced).size());

  C_FLOAT64 * pAtol = Atol.array();
  C_FLOAT64 * pAtolEnd = pAtol + Atol.size();
  const C_FLOAT64 * pInitialValue = mInitialState.array() + mSize.nFixed;
  const CMathObject * pObject = getMathObject(getState(reduced).array());

  for (; pAtol != pAtolEnd; ++pAtol, ++pObject, ++pInitialValue)
    {
      *pAtol = atol;

      C_FLOAT64 InitialValue = fabs(*pInitialValue);

      switch (pObject->getEntityType())
        {
          case CMath::EntityType::Species:
          {
            const CMetab * pMetab = static_cast< const CMetab * >(pObject->getDataObject()->getObjectParent());
            std::map< const CDataObject *, CMathObject * >::const_iterator itFound
              = mDataObject2MathObject.find(pMetab->getCompartment()->getInitialValueReference());

            C_FLOAT64 Limit = fabs(* (C_FLOAT64 *) itFound->second->getValuePointer()) *
                              * (C_FLOAT64 *) mpQuantity2NumberFactor->getValuePointer();

            if (InitialValue != 0.0)
              *pAtol *= std::min(Limit, InitialValue);
            else
              *pAtol *= std::max(1.0, Limit);
          }
          break;

          case CMath::EntityType::GlobalQuantity:
          case CMath::EntityType::Compartment:
          case CMath::EntityType::Model:
            if (InitialValue != 0.0)
              *pAtol *= std::min(1.0, InitialValue);

            break;

          // These are fixed event targets the absolute tolerance can be large since they do not change
          default:
            *pAtol = std::max(1.0, *pAtol);
        }
    }

  return Atol;
}

const CVectorCore< C_FLOAT64 > & CMathContainer::getRate(const bool & reduced) const
{
  if (reduced)
    return mRateReduced;

  return mRate;
}

const CVectorCore< C_FLOAT64 > & CMathContainer::getNoise(const bool & reduced) const
{
  if (reduced)
    return mNoiseReduced;

  return mExtensiveNoise;
}

void CMathContainer::resetNoise()
{
  memset(mExtensiveNoise.array(), 0, sizeof(C_FLOAT64) * (mExtensiveNoise.size() + mIntensiveNoise.size() + mReactionNoise.size() + mReactionParticleNoise.size()));
}

const CVectorCore< C_FLOAT64 > & CMathContainer::getTotalMasses() const
{
  return mTotalMasses;
}

const CVectorCore< C_FLOAT64 > & CMathContainer::getParticleFluxes() const
{
  return mParticleFluxes;
}

const CVectorCore< C_FLOAT64 > & CMathContainer::getFluxes() const
{
  return mFluxes;
}

const CVectorCore< C_FLOAT64 > & CMathContainer::getPropensities() const
{
  return mPropensities;
}

const CVectorCore< C_FLOAT64 > & CMathContainer::getRoots() const
{
  return mEventRoots;
}

const CVectorCore< bool > & CMathContainer::getRootIsDiscrete() const
{
  return mRootIsDiscrete;
}

const CVectorCore< bool > & CMathContainer::getRootIsTimeDependent() const
{
  return mRootIsTimeDependent;
}

CVector< CMathEvent::CTrigger::CRootProcessor * > & CMathContainer::getRootProcessors()
{
  return mRootProcessors;
}

void CMathContainer::updateInitialValues(const CCore::Framework & framework)
{
  // This will not be able to adjust values which are in mValueChangeProhibited
  switch (framework)
    {
      case CCore::Framework::Concentration:
        applyUpdateSequence(mSynchronizeInitialValuesSequenceIntensive);
        break;

      case CCore::Framework::ParticleNumbers:
        applyUpdateSequence(mSynchronizeInitialValuesSequenceExtensive);
        break;

      case CCore::Framework::__SIZE:
        break;
    }
}

void CMathContainer::applyInitialValues()
{
  // We need to reset any left over pending actions.
  CMathEvent * pEvent = mEvents.array();
  CMathEvent * pEventEnd = pEvent + mEvents.size();

  for (; pEvent != pEventEnd; ++pEvent)
    {
      pEvent->removePendingAction();
    }

#ifdef DEBUG_OUTPUT
  std::cout << "Container Values: " << mValues << std::endl;
#endif // DEBUG_OUTPUT

  C_FLOAT64 * pInitial = mInitialExtensiveValues.array();
  C_FLOAT64 * pTransient = mExtensiveValues.array();

  memcpy(pTransient, pInitial, (pTransient - pInitial) * sizeof(C_FLOAT64));

#ifdef DEBUG_OUTPUT
  std::cout << "Container Values: " << mValues << std::endl;
#endif // DEBUG_OUTPUT

  applyUpdateSequence(mApplyInitialValuesSequence);

#ifdef DEBUG_OUTPUT
  std::cout << "Container Values: " << mValues << std::endl;
#endif // DEBUG_OUTPUT

  // Start the process queue
  mpProcessQueue->start();

  // Determine the initial root states.
  CMathEvent::CTrigger::CRootProcessor ** pRoot = mRootProcessors.array();
  CMathEvent::CTrigger::CRootProcessor ** pRootEnd = pRoot + mRootProcessors.size();

  for (; pRoot != pRootEnd; ++pRoot)
    {
      (*pRoot)->calculateTrueValue();
    }

  // Determine the trigger values
  CMathObject * pTriggerObject = getMathObject(mEventTriggers.array());
  CMathObject * pTriggerObjectEnd = pTriggerObject + mEventTriggers.size();

  for (; pTriggerObject != pTriggerObjectEnd; ++pTriggerObject)
    {
      pTriggerObject->calculateValue();
    }

  // Fire events which triggers are true and which may fire at the initial time
  C_FLOAT64 * pTrigger = mEventTriggers.array();
  C_FLOAT64 * pTriggerEnd = pTrigger + mEventTriggers.size();
  pEvent = mEvents.array();

  for (; pTrigger != pTriggerEnd; ++pTrigger, ++pEvent)
    {
      if (*pTrigger > 0.5 &&
          pEvent->fireAtInitialTime())
        {
          pEvent->fire(true);
        }
    }

#ifdef DEBUG_OUTPUT
  std::cout << "Container Values: " << mValues << std::endl;
#endif // DEBUG_OUTPUT

  // Determine roots which change state at the initial time point, i.e., roots which may have
  // a value of zero and a non zero derivative and check
  CVector< C_INT > FoundRoots(mEventRoots.size());
  C_INT * pFoundRoot = FoundRoots.array();
  C_FLOAT64 * pRootValue = mEventRoots.array();
  pRoot = mRootProcessors.array();

  bool HaveRootDerivatives = (memcmp(mRootDerivativesState.array(), mState.array(), sizeof(C_FLOAT64) * mState.size()) == 0);
  C_FLOAT64 * pRootDerivative = mRootDerivatives.array();

  for (; pRoot != pRootEnd; ++pRoot, ++pFoundRoot, ++pRootValue, ++pRootDerivative)
    {
      // Assume the root is not found.
      *pFoundRoot = 0;

      if (*pRootValue != 0.0)
        {
          continue;
        }

      // Calculate the current root derivatives on demand
      if (!HaveRootDerivatives)
        {
          calculateRootDerivatives(mRootDerivatives);
          mRootDerivativesState = mState;

          HaveRootDerivatives = true;
        }

      if ((*pRoot)->isEquality())
        {
          if (*pRootDerivative < 0.0)
            {
              *pFoundRoot = 1;
            }
        }
      else
        {
          if (*pRootDerivative > 0.0)
            {
              *pFoundRoot = 1;
            }
        }
    }

  processRoots(false, FoundRoots);

#ifdef DEBUG_OUTPUT
  std::cout << "Container Values: " << mValues << std::endl;
#endif // DEBUG_OUTPUT
  return;
}

void CMathContainer::updateSimulatedValues(const bool & useMoieties)
{
  if (useMoieties)
    {
      applyUpdateSequence(mSimulationValuesSequenceReduced);
    }
  else
    {
      applyUpdateSequence(mSimulationValuesSequence);
    }
}

void CMathContainer::updateRootValues(const bool & useMoieties)
{
  if (useMoieties)
    {
      applyUpdateSequence(mRootSequenceReduced);
    }
  else
    {
      applyUpdateSequence(mRootSequence);
    }
}

void CMathContainer::updateNoiseValues(const bool & useMoieties)
{
  if (useMoieties)
    {
      applyUpdateSequence(mNoiseSequenceReduced);
    }
  else
    {
      applyUpdateSequence(mNoiseSequence);
    }
}

void CMathContainer::updateTransientDataValues()
{
  applyUpdateSequence(mTransientDataObjectSequence);
}

const CCore::CUpdateSequence & CMathContainer::getSynchronizeInitialValuesSequence(const CCore::Framework & framework) const
{
  switch (framework)
    {
      case CCore::Framework::Concentration:
        return mSynchronizeInitialValuesSequenceIntensive;
        break;

      case CCore::Framework::ParticleNumbers:
        return mSynchronizeInitialValuesSequenceExtensive;
        break;

      case CCore::Framework::__SIZE:
        break;
    }

  return mSynchronizeInitialValuesSequenceExtensive;
}

const CCore::CUpdateSequence & CMathContainer::getApplyInitialValuesSequence() const
{
  return mApplyInitialValuesSequence;
}

const CCore::CUpdateSequence & CMathContainer::getSimulationValuesSequence(const bool & useMoieties) const
{
  if (useMoieties)
    {
      return mSimulationValuesSequenceReduced;
    }
  else
    {
      return mSimulationValuesSequence;
    }
}

const CCore::CUpdateSequence & CMathContainer::getNoiseSequence(const bool & useMoieties) const
{
  if (useMoieties)
    {
      return mNoiseSequenceReduced;
    }
  else
    {
      return mNoiseSequence;
    }
}

const CCore::CUpdateSequence & CMathContainer::getTransientDataValueSequence() const
{
  return mTransientDataObjectSequence;
}

void CMathContainer::removeDataObject(const CDataObject * pObject)
{
  DataObjectSet Descendants;
  Descendants.insert(pObject);

  if (pObject->hasFlag(CDataObject::Flag::Container))
    dynamic_cast< const CDataContainer * >(pObject)->getDescendants(Descendants);

  std::set< const CDataObject * >::const_iterator it = Descendants.begin();
  std::set< const CDataObject * >::const_iterator end = Descendants.end();

  for (; it != end; ++it)
    {
      CMathObject * pObject = getMathObject(*it);

      if (pObject == NULL)
        continue;

      mInitialDependencies.removeObject(pObject);
      mTransientDependencies.removeObject(pObject);
      pObject->setDataObject(NULL);

      CMathObject * pInitialObject = getInitialValueObject(pObject);

      if (pInitialObject == pObject
          || pInitialObject == NULL)
        continue;

      mInitialDependencies.removeObject(pInitialObject);
      mTransientDependencies.removeObject(pInitialObject);
      pInitialObject->setDataObject(NULL);
    }
}

void CMathContainer::updateHistoryValues(const bool & useMoieties)
{
  CMathHistoryCore * pHistory = (useMoieties) ? &mHistoryReduced : &mHistory;
  CMathDelay * pDelay = mDelays.array();
  CMathDelay * pDelayEnd = pDelay + mDelays.size();
  size_t lag = 0;

  for (; pDelay != pDelayEnd; ++lag, ++pDelay)
    {
      setState(pHistory->getRow(lag));
      pDelay->calculateDelayValues(useMoieties);
    }
}

void CMathContainer::updatePriorityValues()
{
  applyUpdateSequence(mPrioritySequence);
}

void CMathContainer::applyUpdateSequence(const CCore::CUpdateSequence & updateSequence)
{
  CCore::CUpdateSequence::const_iterator it = updateSequence.begin();
  CCore::CUpdateSequence::const_iterator end = updateSequence.end();

  for (; it != end; ++it)
    {
      (*it)->calculateValue();
    }
}

void CMathContainer::fetchInitialState()
{
  C_FLOAT64 * pValue = mInitialState.array();
  C_FLOAT64 * pValueEnd = pValue + mInitialState.size();
  CMathObject * pObject = mObjects.array();

  for (; pValue != pValueEnd; ++pValue, ++pObject)
    {
      // We must not fetch initial values of type assignment as they may be calculated
      // by a constant expression which is only evaluated during CMathObject::compile.
      if (pObject->getSimulationType() == CMath::SimulationType::Assignment) continue;

      const CDataObject * pDataObject = pObject->getDataObject();

      if (pDataObject != NULL)
        {
          *pValue = *(C_FLOAT64 *)pDataObject->getValuePointer();
        }
      else
        {
          *pValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
        }
    }

  return;
}

void CMathContainer::pushInitialState()
{
  // mInitialExtensiveValues, mInitialIntensiveValues, mInitialTotalMasses

  C_FLOAT64 * pValue = mInitialExtensiveValues.begin();
  C_FLOAT64 * pValueEnd = mInitialExtensiveValues.end();
  CMathObject * pObject = getMathObject(pValue);

  for (; pValue != pValueEnd; ++pValue, ++pObject)
    {
      const CDataObject * pDataObject = pObject->getDataObject();

      if (pDataObject != NULL)
        {
          *(C_FLOAT64 *)pDataObject->getValuePointer() = *pValue;
        }
    }

  pValue = mInitialIntensiveValues.begin();
  pValueEnd = mInitialIntensiveValues.end();
  pObject = getMathObject(pValue);

  for (; pValue != pValueEnd; ++pValue, ++pObject)
    {
      const CDataObject * pDataObject = pObject->getDataObject();

      if (pDataObject != NULL)
        {
          *(C_FLOAT64 *)pDataObject->getValuePointer() = *pValue;
        }
    }

  pValue = mInitialTotalMasses.begin();
  pValueEnd = mInitialTotalMasses.end();
  pObject = getMathObject(pValue);

  for (; pValue != pValueEnd; ++pValue, ++pObject)
    {
      const CDataObject * pDataObject = pObject->getDataObject();

      if (pDataObject != NULL)
        {
          *(C_FLOAT64 *)pDataObject->getValuePointer() = *pValue;
        }
    }

  return;
}

void CMathContainer::fetchState()
{
  C_FLOAT64 * pValue = mState.begin();
  C_FLOAT64 * pValueEnd = mState.end();
  CMathObject * pObject = getMathObject(pValue);

  for (; pValue != pValueEnd; ++pValue, ++pObject)
    {
      const CDataObject * pDataObject = pObject->getDataObject();

      if (pDataObject != NULL)
        {
          *pValue = *(C_FLOAT64 *)pDataObject->getValuePointer();
        }
      else
        {
          *pValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
        }
    }

  return;
}

void CMathContainer::pushState()
{
  C_FLOAT64 * pValue = mState.array();
  C_FLOAT64 * pValueEnd = pValue + mState.size();
  CMathObject * pObject = getMathObject(pValue);

  for (; pValue != pValueEnd; ++pValue, ++pObject)
    {
      const CDataObject * pDataObject = pObject->getDataObject();

      if (pDataObject != NULL)
        {
          *(C_FLOAT64 *)pDataObject->getValuePointer() = *pValue;
        }
    }

  return;
}

void CMathContainer::pushAllTransientValues()
{
  C_FLOAT64 * pValue = mExtensiveValues.array();
  C_FLOAT64 * pValueEnd = mValues.array() + mValues.size();
  CMathObject * pObject = getMathObject(pValue);

  for (; pValue != pValueEnd; ++pValue, ++pObject)
    {
      const CDataObject * pDataObject = pObject->getDataObject();

      if (pDataObject != NULL && pDataObject->getValuePointer() != NULL)
        {
          *(C_FLOAT64 *)pDataObject->getValuePointer()  = *pValue;
        }
    }

  return;
}

// virtual
CCommonName CMathContainer::getCN() const
{
  return mpModel->getCN();
}

// virtual
const CObjectInterface * CMathContainer::getObject(const CCommonName & cn) const
{
  // Since the CN should be relative we check in the model first
  const CObjectInterface * pObject = mpModel->getObject(cn);

  if (pObject == NULL)
    {
#ifdef DEBUG_OUTPUT
      std::cout << "Data Object " << cn << " not found in model." << std::endl;
#endif // DEBUG_OUTPUT

      CObjectInterface::ContainerList ListOfContainer;
      ListOfContainer.push_back(mpModel);
      ListOfContainer.push_back(mpModel->getObjectDataModel());

      CCommonName ModelCN = mpModel->getCN();

      if (cn.getPrimary() != ModelCN.getPrimary())
        {
          pObject = CObjectInterface::GetObjectFromCN(ListOfContainer, ModelCN + "," + cn);
        }
      else
        {
          pObject = CObjectInterface::GetObjectFromCN(ListOfContainer, cn);
        }
    }

  const CMathObject * pMathObject = getMathObject(pObject);

  if (pMathObject != NULL)
    {
      return pMathObject;
    }

#ifdef DEBUG_OUTPUT
  std::cout << "Data Object " << cn << " (0x" << pObject << ") has no corresponding Math Object." << std::endl;
#endif // DEBUG_OUTPUT

  return pObject;
}

const CObjectInterface * CMathContainer::getObjectFromCN(const CCommonName & cn) const
{
  CObjectInterface::ContainerList ListOfContainer;
  ListOfContainer.push_back(this);
  ListOfContainer.push_back(mpModel);
  ListOfContainer.push_back(mpModel->getObjectDataModel());

  return CObjectInterface::GetObjectFromCN(ListOfContainer, cn);
}

CMathObject * CMathContainer::getMathObject(const CObjectInterface * pObject) const
{
  if (pObject == NULL)
    return NULL;

  std::map< const CDataObject *, CMathObject * >::const_iterator found =
    mDataObject2MathObject.find(const_cast<CDataObject*>(static_cast< const CDataObject * >(pObject)));

  if (found != mDataObject2MathObject.end())
    {
      return found->second;
    }

  return NULL;
}

CMathObject * CMathContainer::getMathObject(const C_FLOAT64 * pDataValue) const
{
  if (pDataValue == NULL)
    return NULL;

  // Check whether we point to a math value.
  const C_FLOAT64 * pValues = mValues.array();

  if (pValues <= pDataValue && pDataValue < pValues + mValues.size())
    {
      return const_cast< CMathObject * >(mObjects.array() + (pDataValue - pValues));
    }

  std::map< C_FLOAT64 *, CMathObject * >::const_iterator found =
    mDataValue2MathObject.find(const_cast< C_FLOAT64 * >(pDataValue));

  if (found != mDataValue2MathObject.end())
    {
      return found->second;
    }

  return NULL;
}

CMathObject * CMathContainer::getMathObject(const CCommonName & cn) const
{
  return getMathObject(mpModel->getObject(cn));
}

CDataObject * CMathContainer::getDataObject(const C_FLOAT64 * pDataValue) const
{
  std::map< C_FLOAT64 *, CDataObject * >::const_iterator found =
    mDataValue2DataObject.find(const_cast< C_FLOAT64 * >(pDataValue));

  if (found != mDataValue2DataObject.end())
    {
      return found->second;
    }

  return NULL;
}

CMathReaction * CMathContainer::getMathReaction(const CReaction * pReaction) const
{
  if (pReaction == NULL) return NULL;

  CMathObject * pFlux = getMathObject(pReaction->getFluxReference());

  if (pFlux == NULL) return NULL;

  return const_cast< CMathReaction * >(&mReactions[(C_FLOAT64 *) pFlux->getValuePointer() - mFluxes.array()]);
}

CMathObject * CMathContainer::getCompartment(const CMathObject * pObject) const
{
  if (pObject == NULL ||
      pObject->getEntityType() != CMath::EntityType::Species)
    {
      return NULL;
    }

  CMetab * pMetab = static_cast< CMetab * >(pObject->getDataObject()->getObjectParent());

  return getMathObject(pMetab->getCompartment()->getValueReference());
}

CMathObject * CMathContainer::getLargestReactionCompartment(const CMathReaction * pReaction) const
{
  if (pReaction == NULL)
    {
      return NULL;
    }

  CMathObject * pLargestCompartment = NULL;
  CMathReaction::ObjectBalance::const_iterator it = pReaction->getObjectBalance().begin();
  CMathReaction::ObjectBalance::const_iterator end = pReaction->getObjectBalance().end();

  for (; it != end; ++it)
    {
      CMathObject * pCompartment = getCompartment(it->first);

      if (pLargestCompartment == NULL ||
          (pCompartment != NULL &&
           *(C_FLOAT64*)pLargestCompartment->getValuePointer() < * (C_FLOAT64*)pCompartment->getValuePointer()))
        {
          pLargestCompartment = pCompartment;
        }
    }

  return pLargestCompartment;
}

void CMathContainer::compile()
{
  try
    {
      allocate();

      CMath::sPointers Pointers;
      initializePointers(Pointers);

#ifdef DEBUG_OUPUT
      printPointers(Pointers);
#endif // DEBUG_OUPUT

      initializeDiscontinuousCreationPointer();

      initializeObjects(Pointers);
      initializeEvents(Pointers);

      map();
      compileObjects();
      compileEvents();

      // These are only used during initialization for setting up the tracking of
      // discontinuities and are cleared afterwards.
      mDiscontinuityEvents.clear();
      mDiscontinuityInfix2Object.clear();
      mTriggerInfix2Event.clear();
      mRootCount2Events.clear();
    }
  catch (...)
    {
      // These are only used during initialization for setting up the tracking of
      // discontinuities and are cleared afterwards.
      mDiscontinuityEvents.clear();
      mDiscontinuityInfix2Object.clear();
      mTriggerInfix2Event.clear();
      mRootCount2Events.clear();

      throw;
    }

  // Create eventual delays
  createDelays();

  createDependencyGraphs();
  createValueChangeProhibited();
  createUpdateSequences();

  CMathReaction * pReaction = mReactions.array();
  CDataVector< CReaction >::const_iterator itReaction = mpModel->getReactions().begin();
  CDataVector< CReaction >::const_iterator endReaction = mpModel->getReactions().end();

  for (; itReaction != endReaction; ++itReaction, ++pReaction)
    {
      pReaction->initialize(itReaction, *this);
    }

#ifdef USE_JIT

  try
    {
      mpJITCompiler->compile();
    }
  catch (...)
    {}

#endif

  updateInitialValues(CCore::Framework::ParticleNumbers);

  // TODO We may have unused event triggers and roots due to optimization
  // in the discontinuities.
  analyzeRoots();

  CMathDelay * pDelay = mDelays.array();
  CMathDelay * pDelayEnd = pDelay + mDelays.size();

  for (; pDelay != pDelayEnd; ++pDelay)
    {
      pDelay->createUpdateSequences();
    }

  // Check whether we have recursive delay value definitions
  {
    CObjectInterface::ObjectSet Changed;

    CMathObject *pObject = getMathObject(mDelayValues.array());
    CMathObject *pObjectEnd = pObject + mDelayValues.size();

    for (; pObject != pObjectEnd; ++pObject)
      {
        Changed.insert(pObject);
      }

    CCore::CUpdateSequence Sequence;
    mTransientDependencies.getUpdateSequence(Sequence, CCore::SimulationContext::DelayValues, Changed, Changed);

    if (!Sequence.empty())
      {
        // TODO CRITICAL Create a meaningful error message.
        fatalError();
      }
  }

#ifdef DEBUG_OUTPUT
  CMathObject *pObject = mObjects.array();
  CMathObject *pObjectEnd = pObject + mObjects.size();

  for (; pObject != pObjectEnd; ++pObject)
    {
      std::cout << *pObject;
    }

  std::cout << std::endl;
#endif // DEBUG_OUTPUT

  mCompileTime = std::chrono::steady_clock::now();
}

const CModel & CMathContainer::getModel() const
{
  return *mpModel;
}

const size_t & CMathContainer::getCountFixedEventTargets() const
{
  return mSize.nFixedEventTargets;
}

size_t CMathContainer::getCountODEs() const
{
  return mSize.nODE + mSize.nODESpecies;
}

size_t CMathContainer::getCountIndependentSpecies() const
{
  return mSize.nReactionSpecies - mSize.nMoieties;
}

const size_t & CMathContainer::getCountDependentSpecies() const
{
  return mSize.nMoieties;
}

const size_t & CMathContainer::getCountAssignments() const
{
  return mSize.nAssignment;
}

const size_t & CMathContainer::getCountFixed() const
{
  return mSize.nFixed;
}

size_t CMathContainer::getCountNoise() const
{
  return mNoiseInputObjects.size();
}

void CMathContainer::addNoiseInputObject(const CMathObject * pObject)
{
  mNoiseInputObjects.insert(pObject);
}

const CObjectInterface::ObjectSet & CMathContainer::getNoiseInputObjects() const
{
  return mNoiseInputObjects;
}

CVectorCore< CMathReaction > & CMathContainer::getReactions()
{
  return mReactions;
}

const CVectorCore< CMathReaction > & CMathContainer::getReactions() const
{
  return mReactions;
}

const CMatrix< C_FLOAT64 > & CMathContainer::getStoichiometry(const bool & reduced) const
{
  if (reduced)
    {
      return mpModel->getRedStoi();
    }

  return mpModel->getStoi();
}

const CVectorCore< CMathEvent > & CMathContainer::getEvents() const
{
  return mEvents;
}

const CMathDependencyGraph & CMathContainer::getInitialDependencies() const
{
  return mInitialDependencies;
}

const CMathDependencyGraph & CMathContainer::getTransientDependencies() const
{
  return mTransientDependencies;
}

/**
 * Retrieve the objects which represent the initial state.
 * @return CObjectInterface::ObjectSet & stateObjects
 */
const CObjectInterface::ObjectSet & CMathContainer::getInitialStateObjects() const
{
  return mInitialStateValueAll;
}

const CObjectInterface::ObjectSet & CMathContainer::getValueChangeProhibited() const
{
  return mValueChangeProhibited;
}

const CObjectInterface::ObjectSet & CMathContainer::getStateObjects(const bool & reduced) const
{
  if (reduced)
    {
      return mReducedStateValues;
    }

  return mStateValues;
}

const CObjectInterface::ObjectSet & CMathContainer::getSimulationUpToDateObjects() const
{
  return mSimulationRequiredValues;
}

CEvaluationNode * CMathContainer::copyBranch(const CEvaluationNode * pSrc,
    const bool & replaceDiscontinuousNodes)
{
  CMath::Variables< CEvaluationNode * > Variables;

  return copyBranch(pSrc, Variables, replaceDiscontinuousNodes);
}

CEvaluationNode * CMathContainer::copyBranch(const CEvaluationNode * pNode,
    const CMath::Variables< CEvaluationNode * > & variables,
    const bool & replaceDiscontinuousNodes)
{
  CNodeContextIterator< const CEvaluationNode, std::vector< CEvaluationNode * > > itNode(pNode);
  CEvaluationNode * pCopy = NULL;

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      // We need to replace variables, expand called trees, and handle discrete nodes.
      switch (itNode->mainType() | itNode->subType())
        {
          // Handle object nodes which are of type AVOGADRO
          case (CEvaluationNode::MainType::OBJECT | CEvaluationNode::SubType::AVOGADRO):
            // Create a converted node
            pCopy = createNodeFromObject(mpAvogadro);
            break;

          // Handle object nodes which are of type CN
          case (CEvaluationNode::MainType::OBJECT | CEvaluationNode::SubType::CN):
          {
            // We need to map the object to a math object if possible.
            const CObjectInterface * pObject =
              getObject(static_cast< const CEvaluationNodeObject *>(*itNode)->getObjectCN());

            // If we have a data object and it does not match the nodes object we must not use it.
            if (DataObject(pObject) != static_cast< const CEvaluationNodeObject *>(*itNode)->getObjectInterfacePtr())
              {
                pObject = static_cast< const CEvaluationNodeObject *>(*itNode)->getObjectInterfacePtr();
              }

            // Create a converted node
            pCopy = createNodeFromObject(pObject);
          }
          break;

          // Handle object nodes which are of type POINTER
          case (CEvaluationNode::MainType::OBJECT | CEvaluationNode::SubType::POINTER):
          {
            const CObjectInterface * pObject =
              getMathObject(static_cast< const CEvaluationNodeObject *>(*itNode)->getObjectValuePtr());

            // Create a converted node
            if (pObject != NULL)
              pCopy = createNodeFromObject(pObject);
            else
              pCopy = (*itNode)->copyNode(itNode.context());
          }
          break;

          // Handle variables
          case (CEvaluationNode::MainType::VARIABLE | CEvaluationNode::SubType::DEFAULT):
          {
            size_t Index =
              static_cast< const CEvaluationNodeVariable * >(*itNode)->getIndex();

            if (Index != C_INVALID_INDEX &&
                Index < variables.size())
              {
                pCopy = variables[Index]->copyBranch();
              }
            else
              {
                pCopy = new CEvaluationNodeConstant(CEvaluationNode::SubType::NaN, itNode->getData());
              }
          }
          break;

          // Handle call nodes
          case (CEvaluationNode::MainType::CALL | CEvaluationNode::SubType::FUNCTION):
          case (CEvaluationNode::MainType::CALL | CEvaluationNode::SubType::EXPRESSION):
          {
            const CEvaluationNode * pCalledNode =
              static_cast< const CEvaluationNodeCall * >(*itNode)->getCalledTree()->getRoot();

            pCopy = copyBranch(pCalledNode, itNode.context(), replaceDiscontinuousNodes);

            // The variables have been copied into place we need to delete them.
            std::vector< CEvaluationNode * >::iterator it = itNode.context().begin();
            std::vector< CEvaluationNode * >::iterator end = itNode.context().end();

            for (; it != end; ++it)
              {
                delete *it;
              }
          }
          break;

          // Handle discrete nodes
          case (CEvaluationNode::MainType::CHOICE | CEvaluationNode::SubType::IF):
          case (CEvaluationNode::MainType::FUNCTION | CEvaluationNode::SubType::FLOOR):
          case (CEvaluationNode::MainType::FUNCTION | CEvaluationNode::SubType::CEIL):
          case (CEvaluationNode::MainType::OPERATOR | CEvaluationNode::SubType::MODULUS):
          case (CEvaluationNode::MainType::OPERATOR | CEvaluationNode::SubType::REMAINDER):

            if (replaceDiscontinuousNodes)
              {
                // The node is replaced with a pointer to a math object value.
                // The math object is calculated by an assignment with the target being the
                // math object
                pCopy = replaceDiscontinuousNode(*itNode, itNode.context());
              }
            else
              {
                pCopy = itNode->copyNode(itNode.context());
              }

            break;

          default:
            pCopy = itNode->copyNode(itNode.context());
            break;
        }

      if (itNode.parentContextPtr() != NULL)
        {
          itNode.parentContextPtr()->push_back(pCopy);
        }
    }

  // It is save to return a NULL pointer

  return pCopy;
}

CEvaluationNode *
CMathContainer::replaceDiscontinuousNode(const CEvaluationNode * pSrc,
    const std::vector< CEvaluationNode * > & children)
{
  bool success = true;

  CEvaluationNode * pNode = pSrc->copyNode(children);
  std::string DiscontinuityInfix = pNode->buildInfix();

#ifdef DEBUG_OUTPUT
  std::cout << "DiscontinuityInfix: " << DiscontinuityInfix << std::endl;
#endif //DEBUG_OUTOUT

  // Check whether we have the discontinuous node already created. This can happen if the
  // discontinuity was part of an expression for a variable in a function call.
  std::map< std::string, CMathObject * >::iterator itObject = mDiscontinuityInfix2Object.find(DiscontinuityInfix);

  if (itObject != mDiscontinuityInfix2Object.end())
    {
      // No need to copy we have already on object
      CMathObject * pDiscontinuity = itObject->second;

#ifdef DEBUG_OUTPUT
      std::cout << "Existing Object found: " << *pDiscontinuity << std::endl;
#endif //DEBUG_OUTOUT

      // We need to advance both creation pointer to assure that we have the correct allocation
      // Mark the discontinuity objects as unused
      mCreateDiscontinuousPointer.pDiscontinuous->setValueType(CMath::ValueType::Undefined);
      mCreateDiscontinuousPointer.pDiscontinuous += 1;

      pdelete(pNode);

      // Return a pointer to a node pointing to the value of discontinuous object.
      return new CEvaluationNodeObject((C_FLOAT64 *) pDiscontinuity->getValuePointer());
    }

  // We have a new discontinuity
  CMathObject * pDiscontinuity = mCreateDiscontinuousPointer.pDiscontinuous;
  mCreateDiscontinuousPointer.pDiscontinuous += 1;

  // Map the discontinuity infix to the discontinuous object.
  mDiscontinuityInfix2Object[DiscontinuityInfix] = pDiscontinuity;

  // Create the expression to calculate the discontinuous object
  CMathExpression * pExpression = new CMathExpression("DiscontinuousExpression", *this);
  success &= static_cast< CEvaluationTree * >(pExpression)->setRoot(pNode);
  success &= pDiscontinuity->setExpressionPtr(pExpression);

  CMathEvent * pEvent = NULL;

  // Check whether we have already an event with the current trigger
  std::string TriggerInfix = createDiscontinuityTriggerInfix(pNode);
  std::map< std::string, CMathEvent * >::iterator itEvent = mTriggerInfix2Event.find(TriggerInfix);

  // We need to create an event.
  if (itEvent == mTriggerInfix2Event.end())
    {
      CEvent DataEvent;
      DataEvent.setType(CEvent::Discontinuity);
      DataEvent.setTriggerExpression(TriggerInfix);

      CMathEvent Event;
      CMathEvent::allocate(Event, &DataEvent, *this);
      size_t RootCount = Event.getTrigger().getRoots().size();

      std::multimap< size_t, size_t >::iterator found = mRootCount2Events.find(RootCount);

      if (found == mRootCount2Events.end()) fatalError();

      pEvent = mCreateDiscontinuousPointer.pEvent + found->second;

      mRootCount2Events.erase(found);

      // Set the trigger
      pEvent->setTriggerExpression(TriggerInfix, *this);

      // Map the trigger infix to the event.
      mTriggerInfix2Event[TriggerInfix] = pEvent;
#ifdef DEBUG_OUTPUT
      std::cout << "Created new Event: " << *pEvent << std::endl;
#endif //DEBUG_OUTOUT
    }
  else
    {
      pEvent = itEvent->second;
#ifdef DEBUG_OUTPUT
      std::cout << "Existing Event found: " << *pEvent << std::endl;
#endif //DEBUG_OUTOUT
    }

  // Add the current discontinuity as an assignment.
  pEvent->addAssignment(pDiscontinuity, pDiscontinuity);

  // Return a pointer to a node pointing to the value of discontinuous object.
  return new CEvaluationNodeObject((C_FLOAT64 *) pDiscontinuity->getValuePointer());
}

void CMathContainer::allocate()
{
  // Allocations is always done from scratch
#ifdef XXXX
  memset(&mSize, 0, sizeof(mSize));

  // Delete the old objects
  if (mValues.array() != NULL)
    {
      delete [] mValues.array();
      mValues.initialize(0, NULL);
    }

  if (mObjects.array() != NULL)
    {
      delete [] mObjects.array();
      mObjects.initialize(0, NULL);

      // This makes all update sequences invalid, i.e., we need to clear them
      std::set< CMathUpdateSequence * >::iterator itUpdateSequence = mUpdateSequences.begin();
      std::set< CMathUpdateSequence * >::iterator endUpdateSequence = mUpdateSequences.end();

      for (; itUpdateSequence != endUpdateSequence; ++itUpdateSequence)
        {
          (*itUpdateSequence)->clear();
        }
    }

  if (mEvents.array())
    {
      delete [] mEvents.array();
      mEvents.initialize(0, NULL);
    }

  if (mReactions.array())
    {
      delete [] mReactions.array();
      mReactions.initialize(0, NULL);
    }

  if (mDelays.array())
    {
      delete [] mDelays.array();
      mDelays.initialize(0, NULL);
    }

  mSynchronizeInitialValuesSequenceExtensive.clear();
  mSynchronizeInitialValuesSequenceIntensive.clear();
  mApplyInitialValuesSequence.clear();
  mSimulationValuesSequence.clear();
  mSimulationValuesSequenceReduced.clear();
  mNoiseSequence.clear();
  mNoiseSequenceReduced.clear();
  mPrioritySequence.clear();
  mTransientDataObjectSequence.clear();

  mInitialStateValueExtensive.clear();
  mInitialStateValueIntensive.clear();
  mInitialStateValueAll.clear();
  mStateValues.clear();
  mReducedStateValues.clear();
  mSimulationRequiredValues.clear();

  mDataObject2MathObject.clear();
  mDataValue2MathObject.clear();
  mDataValue2DataObject.clear();

  mInitialDependencies.clear();
  mTransientDependencies.clear();
#endif // XXXX

  sSize Size;

  Size.nFixed = CObjectLists::getListOfConstObjects(CObjectLists::ALL_LOCAL_PARAMETER_VALUES, mpModel).size();
  Size.nFixed += mpModel->getStateTemplate().getNumFixed();
  Size.nFixedEventTargets = 0;

  std::set< const CModelEntity * > EventTargets = CObjectLists::getEventTargets(mpModel);

  const CStateTemplate & StateTemplate = mpModel->getStateTemplate();

  // Determine which fixed entities are modified by events and which not.
  const CModelEntity *const* ppEntities = StateTemplate.beginFixed();
  const CModelEntity *const* ppEntitiesEnd = StateTemplate.endFixed();

  for (; ppEntities != ppEntitiesEnd; ++ppEntities)
    {
      if ((*ppEntities)->getStatus() == CModelEntity::Status::ASSIGNMENT)
        continue;

      if (EventTargets.find(*ppEntities) != EventTargets.end())
        {
          Size.nFixed--;
          Size.nFixedEventTargets++;
        }
    }

  Size.nTime = 1;
  Size.nODE = mpModel->getStateTemplate().getNumIndependent() - mpModel->getNumODEMetabs() - mpModel->getNumIndependentReactionMetabs();
  Size.nODESpecies = mpModel->getNumODEMetabs();
  Size.nReactionSpecies = mpModel->getNumIndependentReactionMetabs() + mpModel->getNumDependentReactionMetabs();
  Size.nAssignment = mpModel->getStateTemplate().getNumDependent() - mpModel->getNumDependentReactionMetabs();
  Size.nIntensiveValues = mpModel->getNumMetabs();
  Size.nReactions = mpModel->getReactions().size();
  Size.nMoieties = mpModel->getMoieties().size();
  Size.nDiscontinuities = 0;
  Size.nEvents = 0;
  Size.nEventAssignments = 0;
  Size.nEventRoots = 0;

  // Determine the space requirements for events.
  // We need to create events for nodes which are capable of introducing
  // discontinuous changes.
  createDiscontinuityEvents();
  Size.nDiscontinuities = mDiscontinuityEvents.size();
  Size.nEvents += Size.nDiscontinuities;

  // User defined events
  const CDataVector< CEvent > & Events = mpModel->getEvents();
  CDataVector< CEvent >::const_iterator itEvent = Events.begin();
  CDataVector< CEvent >::const_iterator endEvent = Events.end();

  Size.nEvents += Events.size();

  for (; itEvent != endEvent; ++itEvent)
    {
      CMathEvent Event;
      CMathEvent::allocate(Event, itEvent, *this);

      Size.nEventRoots += Event.getTrigger().getRoots().size();
      Size.nEventAssignments += Event.getAssignments().size();
    }

  itEvent = mDiscontinuityEvents.begin();
  endEvent = mDiscontinuityEvents.end();
  size_t DiscontinuityEventIndex = 0;

  for (; itEvent != endEvent; ++itEvent, ++DiscontinuityEventIndex)
    {
      CMathEvent Event;
      CMathEvent::allocate(Event, itEvent, *this);
      Size.nEventRoots += Event.getTrigger().getRoots().size();

      mRootCount2Events.insert(std::make_pair(Event.getTrigger().getRoots().size(), DiscontinuityEventIndex));

      // We do not have to allocate an assignment as discontinuity object suffices
      // as target and assignment expression.
    }

  // The number of delays is only determined after the math container objects have been
  // constructed. At that point values and objects are reallocated.
  Size.nDelayLags = 0;
  Size.nDelayValues = 0;

  Size.pValue = NULL;
  Size.pObject = NULL;

  resize(Size);
  finishResize();

  mValues = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
}

void CMathContainer::initializeObjects(CMath::sPointers & p)
{
  std::set< const CModelEntity * > EventTargets = CObjectLists::getEventTargets(mpModel);

  std::vector< const CModelEntity * > FixedEntities;
  std::vector< const CModelEntity * > FixedEventTargetEntities;

  const CStateTemplate & StateTemplate = mpModel->getStateTemplate();

  // Determine which fixed entities are modified by events and which not.
  const CModelEntity *const* ppEntities = StateTemplate.beginFixed();
  const CModelEntity *const* ppEntitiesEnd = StateTemplate.endFixed();

  for (; ppEntities != ppEntitiesEnd; ++ppEntities)
    {
      if ((*ppEntities)->getStatus() == CModelEntity::Status::ASSIGNMENT)
        continue;

      if (EventTargets.find(*ppEntities) == EventTargets.end())
        {
          FixedEntities.push_back(*ppEntities);
        }
      else
        {
          FixedEventTargetEntities.push_back(*ppEntities);
        }
    }

  // Process fixed entities which are not event targets.
  initializeMathObjects(FixedEntities, CMath::SimulationType::Fixed, p);

  // Process local reaction parameters
  std::vector<const CDataObject*> LocalReactionParameter =
    CObjectLists::getListOfConstObjects(CObjectLists::ALL_LOCAL_PARAMETER_VALUES, mpModel);
  initializeMathObjects(LocalReactionParameter, p);
  assert(mSize.nFixed == FixedEntities.size() + LocalReactionParameter.size());

  // Process fixed entities which are event targets.
  initializeMathObjects(FixedEventTargetEntities, CMath::SimulationType::EventTarget, p);
  assert(mSize.nFixedEventTargets == FixedEventTargetEntities.size());

  // The simulation time
  // Extensive Initial Value
  CMathObject::initialize(p.pInitialExtensiveValuesObject++, p.pInitialExtensiveValues++,
                          CMath::ValueType::Value, CMath::EntityType::Model, CMath::SimulationType::Time, false, true,
                          mpModel->getInitialValueReference());

  // Extensive Value
  CMathObject::initialize(p.pExtensiveValuesObject++, p.pExtensiveValues++,
                          CMath::ValueType::Value, CMath::EntityType::Model, CMath::SimulationType::Time, false, false,
                          mpModel->getValueReference());

  // Initial Extensive Rate
  CMathObject::initialize(p.pInitialExtensiveRatesObject++, p.pInitialExtensiveRates++,
                          CMath::ValueType::Rate, CMath::EntityType::Model, CMath::SimulationType::Time, false, true,
                          mpModel->getRateReference());
  // Extensive Rate
  CMathObject::initialize(p.pExtensiveRatesObject++, p.pExtensiveRates++,
                          CMath::ValueType::Rate, CMath::EntityType::Model, CMath::SimulationType::Time, false, false,
                          mpModel->getRateReference());

  // Process entities which are determined by ODEs
  std::vector< const CModelEntity * > ODEEntities;

  ppEntities = StateTemplate.beginIndependent();
  ppEntitiesEnd = StateTemplate.endIndependent();

  for (; ppEntities != ppEntitiesEnd && (*ppEntities)->getStatus() == CModelEntity::Status::ODE; ++ppEntities)
    {
      ODEEntities.push_back(*ppEntities);
    }

  initializeMathObjects(ODEEntities, CMath::SimulationType::ODE, p);
  assert(mSize.nODE + mSize.nODESpecies == ODEEntities.size());

  // Process independent species
  std::vector< const CModelEntity * > IndependentSpecies;

  ppEntities = StateTemplate.beginIndependent();
  ppEntitiesEnd = StateTemplate.endIndependent();

  for (; ppEntities != ppEntitiesEnd; ++ppEntities)
    {
      if ((*ppEntities)->getStatus() != CModelEntity::Status::REACTIONS)
        continue;

      IndependentSpecies.push_back(*ppEntities);
    }

  initializeMathObjects(IndependentSpecies, CMath::SimulationType::Independent, p);
  assert(mSize.nReactionSpecies - mSize.nMoieties == IndependentSpecies.size());

  // Process dependent species
  std::vector< const CModelEntity * > DependentSpecies;

  ppEntities = StateTemplate.beginDependent();
  ppEntitiesEnd = StateTemplate.endDependent();

  for (; ppEntities != ppEntitiesEnd && (*ppEntities)->getStatus() == CModelEntity::Status::REACTIONS; ++ppEntities)
    {
      DependentSpecies.push_back(*ppEntities);
    }

  initializeMathObjects(DependentSpecies, CMath::SimulationType::Dependent, p);
  assert(mSize.nMoieties == DependentSpecies.size());

  // Process entities which are determined by assignments
  std::vector< const CModelEntity * > AssignmentEntities;

  // We continue with the pointer ppEntities
  ppEntitiesEnd = StateTemplate.endFixed();

  for (; ppEntities != ppEntitiesEnd && (*ppEntities)->getStatus() == CModelEntity::Status::ASSIGNMENT; ++ppEntities)
    {
      AssignmentEntities.push_back(*ppEntities);
    }

  initializeMathObjects(AssignmentEntities, CMath::SimulationType::Assignment, p);
  assert(mSize.nAssignment == AssignmentEntities.size());

  // Process Reactions
  initializeMathObjects(mpModel->getReactions(), p);

  // Process Moieties
  initializeMathObjects(mpModel->getMoieties(), p);

  // Process Discontinuous Objects
  size_t n;
  assert(mSize.nDiscontinuities == mDiscontinuous.size());

  for (n = 0; n != mSize.nDiscontinuities; ++n)
    {
      CMathObject::initialize(p.pDiscontinuousObject++, p.pDiscontinuous++,
                              CMath::ValueType::Discontinuous, CMath::EntityType::Event, CMath::SimulationType::Undefined,
                              false, false, NULL);
    }

  // Delay objects are allocated after all other objects are compiled.
}

void CMathContainer::initializeEvents(CMath::sPointers & p)
{
  CMathEvent * pEvent = mEvents.array();

  // User defined events
  const CDataVector< CEvent > & Events = mpModel->getEvents();
  CDataVector< CEvent >::const_iterator itEvent = Events.begin();
  CDataVector< CEvent >::const_iterator endEvent = Events.end();

  for (; itEvent != endEvent; ++itEvent, ++pEvent)
    {
      CMathEvent::allocate(*pEvent, itEvent, *this);
      pEvent->initialize(p);
    }

  itEvent = mDiscontinuityEvents.begin();
  endEvent = mDiscontinuityEvents.end();

  for (; itEvent != endEvent; ++itEvent, ++pEvent)
    {
      CMathEvent::allocate(*pEvent, itEvent, *this);
      pEvent->initialize(p);
    }

  return;
}

bool CMathContainer::compileObjects()
{
  bool success = true;

  mNoiseInputObjects.clear();

  CMathObject *pObject = mObjects.array();
  CMathObject *pObjectEnd = pObject + mObjects.size();

  for (; pObject != pObjectEnd; ++pObject)
    {
#ifdef USE_JIT
      success &=
        pObject->compile(*this, *mpJITCompiler);
#else
      success &= pObject->compile(*this);
#endif
    }

  return success;
}

bool CMathContainer::compileEvents()
{
  bool success = true;

  CMathEvent * pItEvent = mEvents.array();

  CDataVector< CEvent >::const_iterator itEvent = mpModel->getEvents().begin();
  CDataVector< CEvent >::const_iterator endEvent = mpModel->getEvents().end();

  for (; itEvent != endEvent; ++pItEvent, ++itEvent)
    {
      success &= pItEvent->compile(itEvent, *this);
#ifdef DEBUG_OUTPUT
      std::cout << "Data Event:  " << *pItEvent << std::endl;
#endif //DEBUG_OUTOUT
    }

  itEvent = mDiscontinuityEvents.begin();
  endEvent = mDiscontinuityEvents.end();

  for (; itEvent != endEvent; ++pItEvent, ++itEvent)
    {
      success &= pItEvent->compile(*this);
#ifdef DEBUG_OUTPUT
      std::cout << "Disc. Event: " << *pItEvent << std::endl;
#endif //DEBUG_OUTOUT
    }

  // Events representing discontinuities.
  std::multimap< size_t, size_t >::iterator itUnused = mRootCount2Events.begin();
  std::multimap< size_t, size_t >::iterator endUnused = mRootCount2Events.end();
  mNumTotalRootsIgnored = 0;

  for (; itUnused != endUnused; ++itUnused)
    {
      // The event is ignored.
      ignoreDiscontinuityEvent(mCreateDiscontinuousPointer.pEvent + itUnused->second);
    }

  return success;
}

CEvaluationNode * CMathContainer::createNodeFromObject(const CObjectInterface * pObject)
{
  CEvaluationNode * pNode = NULL;

  if (pObject == NULL)
    {
      // We have an invalid value, i.e. NaN
      pNode = new CEvaluationNodeConstant(CEvaluationNode::SubType::NaN, "NAN");
    }
  else
    {
      pNode = new CEvaluationNodeObject((C_FLOAT64 *) pObject->getValuePointer());

      // Check whether we have a data object
      if (pObject == pObject->getDataObject())
        {
          // This may insert data objects which are later mapped to math objects.
          // We therefore need to sanitize it later.
          mDataValue2DataObject[(C_FLOAT64 *) pObject->getValuePointer()]
            = static_cast< CDataObject * >(const_cast< CObjectInterface * >(pObject));
        }
    }

  return pNode;
}

CEvaluationNode * CMathContainer::createNodeFromValue(const C_FLOAT64 * pDataValue)
{
  CEvaluationNode * pNode = NULL;
  CMathObject * pMathObject = NULL;

  if (pDataValue != NULL)
    {
      pMathObject = getMathObject(pDataValue);

      if (pMathObject != NULL)
        {
          pNode = new CEvaluationNodeObject((C_FLOAT64 *) pMathObject->getValuePointer());
        }
      else
        {
          // We must have a constant value like the conversion factor from the model.
          pNode = new CEvaluationNodeNumber(*pDataValue);
        }
    }
  else
    {
      // We have an invalid value, i.e. NaN
      pNode = new CEvaluationNodeConstant(CEvaluationNode::SubType::NaN, "NAN");
    }

  return pNode;
}

void CMathContainer::createDependencyGraphs()
{
  mInitialDependencies.clear();

  CMathObject *pObject = mObjects.array();
  CMathObject *pObjectEnd = pObject + (mExtensiveValues.array() - mInitialExtensiveValues.array());

  for (; pObject != pObjectEnd; ++pObject)
    {
      mInitialDependencies.addObject(pObject);
    }

  mTransientDependencies.clear();

  pObjectEnd = mObjects.array() + mObjects.size();

  for (; pObject != pObjectEnd; ++pObject)
    {
      mTransientDependencies.addObject(pObject);
    }

#ifdef COPASI_DEBUG_TRACE
  std::ofstream InitialDependencies("InitialDependencies.dot");
  mInitialDependencies.exportDOTFormat(InitialDependencies, "InitialDependencies");

  std::ofstream TransientDependencies("TransientDependencies.dot");
  mTransientDependencies.exportDOTFormat(TransientDependencies, "TransientDependencies");
#endif // COPASI_DEBUG_TRACE

  return;
}

void CMathContainer::createValueChangeProhibited()
{
  mValueChangeProhibited.clear();

  // We need to find all extensive and intensive initial species values which may not be changed,
  // i.e., the corresponding compartment size depends on it.

  // If the compartment size depends on the initial particle number than the initial concentration may not be changed
  // since [] = # / S = # / f(#).
  // If the compartment size depends on the initial concentration than the initial particle number may not be changed
  // since # = [] * S = [] * f([]).

  CDataVectorNS < CCompartment >::const_iterator it = mpModel->getCompartments().begin();
  CDataVectorNS < CCompartment >::const_iterator end = mpModel->getCompartments().end();

  for (; it != end; ++it)
    {
      // Only if the compartment has an initial expression we may have a problem
      if (it->getInitialExpressionPtr() == NULL)
        continue;

      CMathObject * pCompartment = getMathObject(it->getInitialValueReference());

      const CMathObject * pObject = mObjects.array();
      const CMathObject * pObjectEnd = getMathObject(mInitialExtensiveRates.array());

      for (; pObject != pObjectEnd; ++pObject)

        // Only species in the compartment may pose a problem
        if (pObject->getEntityType() == CMath::EntityType::Species &&
            pObject->getValueType() == CMath::ValueType::Value &&
            pCompartment == getMathObject(pObject->getCompartmentValue()))
          {
            if (mInitialDependencies.hasCircularDependencies(pCompartment, CCore::SimulationContext::UpdateMoieties, pObject))
              {
                mValueChangeProhibited.insert(pObject);
                mInitialDependencies.removePrerequisite(pObject->getCorrespondingProperty(), pCompartment);
              }
          }

      pObject =  getMathObject(mExtensiveValues.array());
      pObjectEnd = getMathObject(mExtensiveRates.array());

      for (; pObject != pObjectEnd; ++pObject)

        // Only species in the compartment may pose a problem
        if (pObject->getEntityType() == CMath::EntityType::Species &&
            pObject->getValueType() == CMath::ValueType::Value &&
            pCompartment == getMathObject(pObject->getCompartmentValue()))
          {
            CMathObject * pCompartment = getMathObject(pObject->getCompartmentValue());

            if (mTransientDependencies.hasCircularDependencies(pCompartment, CCore::SimulationContext::Default, pObject))
              {
                mValueChangeProhibited.insert(pObject);
                mTransientDependencies.removePrerequisite(pObject->getCorrespondingProperty(), pCompartment);
              }
          }
    }
}

void CMathContainer::createUpdateSequences()
{
  sanitizeDataValue2DataObject();
  createSynchronizeInitialValuesSequence();
  createApplyInitialValuesSequence();
  createUpdateSimulationValuesSequence();
  createUpdateAllTransientDataValuesSequence();

  CMathEvent * pEvent = mEvents.array();
  CMathEvent * pEventEnd = pEvent + mEvents.size();

  for (; pEvent != pEventEnd; ++pEvent)
    {
      pEvent->createUpdateSequences();
    }
}

void CMathContainer::sanitizeDataValue2DataObject()
{
  std::map< C_FLOAT64 *, CDataObject * > DataValue2DataObject = mDataValue2DataObject;

  std::map< C_FLOAT64 *, CDataObject * >::const_iterator itDataObject = DataValue2DataObject.begin();
  std::map< C_FLOAT64 *, CDataObject * >::const_iterator endDataObject = DataValue2DataObject.end();

  mDataValue2DataObject.clear();

  for (; itDataObject != endDataObject; ++itDataObject)
    if (getMathObject(itDataObject->second) == NULL)
      {
        mDataValue2DataObject.insert(*itDataObject);
      }
}

void CMathContainer::createSynchronizeInitialValuesSequence()
{
  // Collect all the changed objects, which are all initial state values
  mInitialStateValueAll.clear();
  mInitialStateValueExtensive.clear();
  mInitialStateValueIntensive.clear();

  // Collect all the requested objects
  CObjectInterface::ObjectSet RequestedExtensive;
  CObjectInterface::ObjectSet RequestedIntensive;

  const CMathObject * pObject = mObjects.array();
  const CMathObject * pObjectEnd = getMathObject(mExtensiveValues.array());

  mInitialStateValueAll.insert(mpAvogadro);
  mInitialStateValueExtensive.insert(mpAvogadro);
  mInitialStateValueIntensive.insert(mpAvogadro);

  mInitialStateValueAll.insert(mpQuantity2NumberFactor);
  mInitialStateValueExtensive.insert(mpQuantity2NumberFactor);
  mInitialStateValueIntensive.insert(mpQuantity2NumberFactor);

  for (; pObject != pObjectEnd; ++pObject)
    {
      mInitialStateValueAll.insert(pObject);

      switch (pObject->getValueType())
        {
          case CMath::ValueType::Value:

            switch (pObject->getSimulationType())
              {
                case CMath::SimulationType::Fixed:
                case CMath::SimulationType::Time:
                  mInitialStateValueExtensive.insert(pObject);
                  mInitialStateValueIntensive.insert(pObject);
                  break;

                case CMath::SimulationType::EventTarget:
                case CMath::SimulationType::ODE:
                case CMath::SimulationType::Independent:
                case CMath::SimulationType::Dependent:

                  if (pObject->getEntityType() != CMath::EntityType::Species)
                    {
                      mInitialStateValueExtensive.insert(pObject);
                      mInitialStateValueIntensive.insert(pObject);
                    }
                  else if (pObject->isIntensiveProperty())
                    {
                      mInitialStateValueIntensive.insert(pObject);
                      RequestedExtensive.insert(pObject);
                    }
                  else
                    {
                      mInitialStateValueExtensive.insert(pObject);
                      RequestedIntensive.insert(pObject);
                    }

                  break;

                case CMath::SimulationType::Conversion:

                  // If the species has an initial assignment the intensive and extensive values has to be calculated.
                  if (pObject->getCorrespondingProperty()->getSimulationType() == CMath::SimulationType::Assignment)
                    {
                      RequestedExtensive.insert(pObject);
                      RequestedIntensive.insert(pObject);
                    }
                  else if (mValueChangeProhibited.find(pObject) == mValueChangeProhibited.end())
                    {
                      if (pObject->isIntensiveProperty())
                        {
                          mInitialStateValueIntensive.insert(pObject);
                          RequestedExtensive.insert(pObject);
                        }
                      else
                        {
                          mInitialStateValueExtensive.insert(pObject);
                          RequestedIntensive.insert(pObject);
                        }
                    }

                  break;

                case CMath::SimulationType::Assignment:
                  if (pObject->getPrerequisites().size() > 0)
                    {
                      RequestedExtensive.insert(pObject);
                      RequestedIntensive.insert(pObject);
                    }
                  else
                    {
                      mInitialStateValueExtensive.insert(pObject);
                      mInitialStateValueIntensive.insert(pObject);
                    }

                  break;

                case CMath::SimulationType::__SIZE:
                  break;
              }

            break;

          // Everything which is not a value must be calculated.
          default:
            RequestedExtensive.insert(pObject);
            RequestedIntensive.insert(pObject);
            break;
        }
    }

  // Issue 1170: We need to add elements of the stoichiometry, reduced stoichiometry,
  // and link matrices.
  std::map< C_FLOAT64 *, CDataObject * >::const_iterator itDataObject = mDataValue2DataObject.begin();
  std::map< C_FLOAT64 *, CDataObject * >::const_iterator endDataObject = mDataValue2DataObject.end();

  for (; itDataObject != endDataObject; ++itDataObject)

    // Issue 3100: We must only add data objects which are part of the model
    if (itDataObject->second->getObjectAncestor("Model") != NULL)
      {
        mInitialStateValueExtensive.insert(itDataObject->second);
        mInitialStateValueIntensive.insert(itDataObject->second);
      }

  // Build the update sequence
  // Bug 2773: It is OK for one of these to fail
  mInitialDependencies.getUpdateSequence(mSynchronizeInitialValuesSequenceExtensive,
                                         CCore::SimulationContext::UpdateMoieties,
                                         mInitialStateValueExtensive,
                                         RequestedExtensive);
  mInitialDependencies.getUpdateSequence(mSynchronizeInitialValuesSequenceIntensive,
                                         CCore::SimulationContext::UpdateMoieties,
                                         mInitialStateValueIntensive,
                                         RequestedIntensive);
}

void CMathContainer::createApplyInitialValuesSequence()
{
  // At this point all initial values as well as their transient counterparts are calculated
  CObjectInterface::ObjectSet Calculated;
  const CMathObject * pObject = mObjects.array();
  const CMathObject * pObjectEnd = getMathObject(mExtensiveValues.array());
  size_t TransientOffset = pObjectEnd - pObject;

  for (; pObject != pObjectEnd; ++pObject)
    {
      Calculated.insert(pObject);
      Calculated.insert(pObject + TransientOffset);
    }

  // Collect all the changed objects, which are all initial and transient state values
  CObjectInterface::ObjectSet Changed = mInitialStateValueExtensive;
  // Initial state values

  // Collect all the requested objects
  CObjectInterface::ObjectSet Requested;

  pObject = getMathObject(mExtensiveValues.array());
  pObjectEnd = mObjects.array() + mObjects.size();

  for (; pObject != pObjectEnd; ++pObject)
    {
      switch (pObject->getValueType())
        {
          case CMath::ValueType::Value:

            switch (pObject->getSimulationType())
              {
                case CMath::SimulationType::Fixed:
                case CMath::SimulationType::Time:
                  Changed.insert(pObject);
                  break;

                case CMath::SimulationType::EventTarget:
                case CMath::SimulationType::ODE:
                case CMath::SimulationType::Independent:
                case CMath::SimulationType::Dependent:
                case CMath::SimulationType::Conversion:

                  if (pObject->getEntityType() != CMath::EntityType::Species)
                    {
                      Changed.insert(pObject);
                    }
                  else if (pObject->isIntensiveProperty())
                    {
                      Requested.insert(pObject);
                    }
                  else
                    {
                      Changed.insert(pObject);
                    }

                  break;

                case CMath::SimulationType::Assignment:
                  Changed.insert(pObject);
                  Requested.insert(pObject);
                  break;

                case CMath::SimulationType::__SIZE:
                  break;
              }

            break;

          // Everything else must be calculated.
          default:
            Requested.insert(pObject);
            break;
        }
    }

  // Build the update sequence
  mTransientDependencies.getUpdateSequence(mApplyInitialValuesSequence, CCore::SimulationContext::Default, Changed, Requested, Calculated);

  // It is possible that discontinuities only depend on constant values. Since discontinuities do not exist in the initial values
  // these are never calculate. It is save to prepend all discontinuities which are not already in the sequence
  if (mDiscontinuous.size() > 0)
    {
      // Find all discontinuities which are updated
      CCore::CUpdateSequence::const_iterator it = mApplyInitialValuesSequence.begin();
      CCore::CUpdateSequence::const_iterator end = mApplyInitialValuesSequence.end();

      CObjectInterface::ObjectSet UpdatedDiscontinuities;

      for (; it != end; ++it)
        {
          if (static_cast< CMathObject * >(*it)->getValueType() == CMath::ValueType::Discontinuous)
            {
              UpdatedDiscontinuities.insert(*it);
            }
        }

      CMathObject * pDiscontinuity = getMathObject(mDiscontinuous.array());
      CMathObject * pDiscontinuityEnd = pDiscontinuity + mDiscontinuous.size();
      std::set< CObjectInterface * > OutofDateDiscontinuities;

      for (; pDiscontinuity != pDiscontinuityEnd; ++pDiscontinuity)
        {
          if (static_cast< CMathObject * >(pDiscontinuity)->getValueType() == CMath::ValueType::Discontinuous &&
              UpdatedDiscontinuities.find(pDiscontinuity) == UpdatedDiscontinuities.end())
            {
              OutofDateDiscontinuities.insert(pDiscontinuity);
            }
        }

      if (OutofDateDiscontinuities.size() > 0)
        {
          mApplyInitialValuesSequence.insert(mApplyInitialValuesSequence.begin(), OutofDateDiscontinuities.begin(), OutofDateDiscontinuities.end());
        }
    }
}

void CMathContainer::createUpdateSimulationValuesSequence()
{
  mStateValues.clear();
  mReducedStateValues.clear();
  mSimulationRequiredValues.clear();

  // For the reduced model we force the values of the dependent variables to be calculated.
  CObjectInterface::ObjectSet ReducedSimulationRequiredValues;

  // Collect all the state objects, which are transient values of simulation type:
  //   Time, ODE, Independent, and Dependent (not for reduced model)

  const CMathObject * pObject = mObjects.array() + (mExtensiveValues.array() - mValues.array());
  const CMathObject * pObjectEnd = mObjects.array() + (mExtensiveRates.array() - mValues.array());

  for (; pObject != pObjectEnd; ++pObject)
    {
      switch (pObject->getSimulationType())
        {
          case CMath::SimulationType::EventTarget:
          case CMath::SimulationType::Time:
          case CMath::SimulationType::ODE:
          case CMath::SimulationType::Independent:
            if (mValueChangeProhibited.find(pObject) == mValueChangeProhibited.end())
              {
                mStateValues.insert(pObject);
                mReducedStateValues.insert(pObject);
              }

            break;

          case CMath::SimulationType::Dependent:
            if (mValueChangeProhibited.find(pObject) == mValueChangeProhibited.end())
              {
                mStateValues.insert(pObject);
              }

            ReducedSimulationRequiredValues.insert(pObject);
            break;

          default:
            break;
        }
    }

  // Collect all objects required for simulation, which are transient rates values of simulation type:
  //   ODE, Independent, and Dependent (not needed for reduced model) and EventRoots
  // The additional cost for calculating the rates for dependent species is neglected.
  pObject = mObjects.array() + (mExtensiveRates.array() - mValues.array()) + mSize.nFixed + mSize.nFixedEventTargets + mSize.nTime;
  pObjectEnd = pObject + mSize.nODE + mSize.nODESpecies + mSize.nReactionSpecies;

  for (; pObject != pObjectEnd; ++pObject)
    {
      mSimulationRequiredValues.insert(pObject);
      ReducedSimulationRequiredValues.insert(pObject);
    }

  pObject = mObjects.array() + (mDelayLags.array() - mValues.array());
  pObjectEnd = pObject + mDelayLags.size();

  for (; pObject != pObjectEnd; ++pObject)
    {
      mSimulationRequiredValues.insert(pObject);
      ReducedSimulationRequiredValues.insert(pObject);
    }

  // Build the update sequence
  mTransientDependencies.getUpdateSequence(mSimulationValuesSequence, CCore::SimulationContext::Default, mStateValues, mSimulationRequiredValues);
  mTransientDependencies.getUpdateSequence(mSimulationValuesSequenceReduced, CCore::SimulationContext::UseMoieties, mReducedStateValues, ReducedSimulationRequiredValues);

  // Build the update sequence used to calculate the roots.
  CObjectInterface::ObjectSet RootRequiredValues;
  pObject = mObjects.array() + (mEventRoots.array() - mValues.array());
  pObjectEnd = mObjects.array() + (mEventRootStates.array() - mValues.array());

  for (; pObject != pObjectEnd; ++pObject)
    {
      RootRequiredValues.insert(pObject);
    }

  mTransientDependencies.getUpdateSequence(mRootSequence, CCore::SimulationContext::Default, mStateValues, RootRequiredValues);
  mTransientDependencies.getUpdateSequence(mRootSequenceReduced, CCore::SimulationContext::UseMoieties, mReducedStateValues, RootRequiredValues);

  // Determine whether the model is autonomous, i.e., no simulation required value or root depends on time.
  // Create the update sequences for the transient noise;
  pObject = mObjects.array() + (mExtensiveNoise.array() - mValues.array());
  pObjectEnd = mObjects.array() + (mEventDelays.array() - mValues.array());

  CObjectInterface::ObjectSet ReducedNoise;
  CObjectInterface::ObjectSet Noise;

  for (; pObject != pObjectEnd; ++pObject)
    {
      if (pObject->getSimulationType() != CMath::SimulationType::Dependent)
        {
          ReducedNoise.insert(pObject);
        }

      Noise.insert(pObject);
    }

  mTransientDependencies.getUpdateSequence(mNoiseSequence, CCore::SimulationContext::Default, mStateValues, Noise);
  mTransientDependencies.getUpdateSequence(mNoiseSequenceReduced, CCore::SimulationContext::UseMoieties, mReducedStateValues, ReducedNoise);

  // Determine whether the model is autonomous, i.e., no simulation required value depends on time.
  // We need to additionally add the event assignments to the simulation required values as they may time dependent
  CObjectInterface::ObjectSet TimeDependentValues;
  CObjectInterface::ObjectSet TimeObject;
  TimeObject.insert(getMathObject(mState.array() + mSize.nFixedEventTargets));

  mTransientDependencies.appendAllDependents(TimeObject, TimeDependentValues);
  mIsAutonomous = TimeDependentValues.empty();

  // Build the update sequence used to calculate the priorities in the event process queue.
  CObjectInterface::ObjectSet PriorityRequiredValues;
  pObject = getMathObject(mEventPriorities.array());
  pObjectEnd = pObject + mEventPriorities.size();

  for (; pObject != pObjectEnd; ++pObject)
    {
      PriorityRequiredValues.insert(pObject);
    }

  mTransientDependencies.getUpdateSequence(mPrioritySequence, CCore::SimulationContext::Default, mStateValues, PriorityRequiredValues);
}

void CMathContainer::createUpdateAllTransientDataValuesSequence()
{
  // Collect all transient objects that have a data object associated
  CObjectInterface::ObjectSet TransientDataObjects;

  const CMathObject * pObject = mObjects.array() + (mExtensiveValues.array() - mValues.array());
  const CMathObject * pObjectEnd = mObjects.array() + mObjects.size();

  for (; pObject != pObjectEnd; ++pObject)
    {
      if (pObject->getDataObject() != NULL)
        {
          TransientDataObjects.insert(pObject);
        }
    }

  mTransientDependencies.getUpdateSequence(mTransientDataObjectSequence, CCore::SimulationContext::Default, mStateValues, TransientDataObjects, mSimulationRequiredValues);
}

void CMathContainer::analyzeRoots()
{
  CObjectInterface::ObjectSet TimeValue;
  TimeValue.insert(getMathObject(mState.array() + mSize.nFixedEventTargets));

  CObjectInterface::ObjectSet ContinuousStateValues;
  const CMathObject * pStateObject = getMathObject(mState.array() + mSize.nFixedEventTargets);
  const CMathObject * pStateObjectEnd = getMathObject(mState.array() + mState.size());

  for (; pStateObject != pStateObjectEnd; ++pStateObject)
    {
      ContinuousStateValues.insert(pStateObject);
    }

  size_t RootCount = 0;
  C_FLOAT64 * pRootValue = mEventRoots.array();
  CMathObject * pRoot = getMathObject(pRootValue);
  CMathObject * pRootEnd = pRoot + mEventRoots.size();
  bool * pIsDiscrete = mRootIsDiscrete.array();
  bool * pIsTimeDependent = mRootIsTimeDependent.array();

  for (; pRoot != pRootEnd; ++pRoot, ++RootCount, ++pIsDiscrete, ++pRootValue)
    {
      if (pRoot->getExpressionPtr() == NULL)
        {
          *pRootValue = 1;
        }

      CObjectInterface::ObjectSet Requested;
      Requested.insert(pRoot);
      CCore::CUpdateSequence UpdateSequence;

      mTransientDependencies.getUpdateSequence(UpdateSequence, CCore::SimulationContext::Default, ContinuousStateValues, Requested);
      *pIsDiscrete = UpdateSequence.empty();

      mTransientDependencies.getUpdateSequence(UpdateSequence, CCore::SimulationContext::Default, TimeValue, Requested);
      *pIsTimeDependent = !UpdateSequence.empty();
    }

  mEventRoots.initialize(RootCount, mEventRoots.array());
  mEventRootStates.initialize(RootCount, mEventRootStates.array());
  mRootIsDiscrete.resize(RootCount, true);
  mRootIsTimeDependent.resize(RootCount, true);

  mRootProcessors.resize(RootCount);
  mRootDerivatives.resize(RootCount);
  mRootDerivatives = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mRootDerivativesState.resize(mState.size());
  mRootDerivativesState = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

  CMathEvent * pEvent = mEvents.array();
  CMathEvent * pEventEnd = pEvent + mEvents.size();
  pRoot = getMathObject(mEventRoots.array());
  CMathEvent::CTrigger::CRootProcessor ** pRootProcessorPtr = mRootProcessors.array();

  for (; pEvent != pEventEnd; ++pEvent)
    {
      if (pEvent->isDisabled()) continue;

      CMathEvent::CTrigger::CRootProcessor * pRootProcessor = const_cast< CMathEvent::CTrigger::CRootProcessor * >(pEvent->getTrigger().getRoots().array());
      CMathEvent::CTrigger::CRootProcessor * pRootProcessorEnd = pRootProcessor + pEvent->getTrigger().getRoots().size();

      for (; pRootProcessor != pRootProcessorEnd; ++pRootProcessor, ++pRoot, ++pRootProcessorPtr)
        {
          assert(pRootProcessor->mpRoot == pRoot);
          *pRootProcessorPtr = pRootProcessor;
        }
    }
}

void CMathContainer::calculateRootDerivatives(CVector< C_FLOAT64 > & rootDerivatives)
{
  updateRootValues(false);

  CMatrix< C_FLOAT64 > Jacobian;
  calculateRootJacobian(Jacobian);

  CVectorCore< C_FLOAT64 > Rates(Jacobian.numCols(), mRate.array() + mSize.nFixedEventTargets);
  dgemm::eval(1.0, Jacobian, Rates, 0.0, rootDerivatives);
}

void CMathContainer::calculateRootJacobian(CMatrix< C_FLOAT64 > & jacobian)
{
  size_t NumRows = mEventRoots.size();

  // Partial derivatives with respect to time and all variables determined by ODEs and reactions.
  size_t NumCols = mSize.nTime + mSize.nODE + mSize.nODESpecies + mSize.nReactionSpecies;

  jacobian.resize(NumRows, NumCols);

  if (jacobian.size() == 0) return;

  // The rates of all state variables in the current state.
  CVector< C_FLOAT64 > Rate = mRate;

  size_t Col = 0;

  C_FLOAT64 X1 = 0.0;
  C_FLOAT64 X2 = 0.0;
  C_FLOAT64 InvDelta = 0.0;

  CVector< C_FLOAT64 > Y1(NumRows);
  CVector< C_FLOAT64 > Y2(NumRows);

  C_FLOAT64 * pX = mState.array() + mSize.nFixedEventTargets;
  C_FLOAT64 * pXEnd = mState.array() + mState.size();

  C_FLOAT64 * pJacobian = jacobian.array();
  C_FLOAT64 * pJacobianEnd = pJacobian + jacobian.size();

  const C_FLOAT64 * pRate = Rate.array() + mSize.nFixedEventTargets;

  for (; pX != pXEnd; ++pX, ++Col, ++pRate)
    {
      C_FLOAT64 Store = *pX;

      if (fabs(*pRate) < 1e4 * std::numeric_limits< C_FLOAT64 >::epsilon() * fabs(Store) ||
          fabs(*pRate) < 1e4 * std::numeric_limits< C_FLOAT64 >::min())
        {
          if (fabs(Store) < 100.0 * std::numeric_limits< C_FLOAT64 >::min())
            {
              X1 = 0.0;

              if (Store < 0.0)
                X2 = -200.0 * std::numeric_limits< C_FLOAT64 >::min();
              else
                X2 = 200.0 * std::numeric_limits< C_FLOAT64 >::min();

              InvDelta = X2;
            }
          else
            {
              X1 = 0.999 * Store;
              X2 = 1.001 * Store;
              InvDelta = 500.0 / Store;
            }
        }
      else
        {
          X1 = Store - 0.001 * *pRate;
          X2 = Store + 0.001 * *pRate;
          InvDelta = 500.0 / *pRate;
        }

      *pX = X1;
      updateRootValues(false);
      Y1 = mEventRoots;

      *pX = X2;
      updateRootValues(false);
      Y2 = mEventRoots;

      *pX = Store;

      pJacobian = jacobian.array() + Col;
      C_FLOAT64 * pY1 = Y1.array();
      C_FLOAT64 * pY2 = Y2.array();

      for (; pJacobian < pJacobianEnd; pJacobian += NumCols, ++pY1, ++pY2)
        * pJacobian = (*pY2 - *pY1) * InvDelta;
    }

  // Undo the changes.
  updateRootValues(false);
}

void CMathContainer::calculateJacobian(CMatrix< C_FLOAT64 > & jacobian,
                                       const C_FLOAT64 & derivationFactor,
                                       const bool & reduced,
                                       const bool & includeTime)
{
  size_t Rows = getState(reduced).size() - mSize.nFixedEventTargets - 1;
  size_t Columns = getState(reduced).size() - mSize.nFixedEventTargets - (includeTime ? 0 : 1);
  jacobian.resize(Rows, Columns);

  C_FLOAT64 DerivationFactor = std::max(derivationFactor, 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon());

  C_FLOAT64 * pState = mState.array() + mSize.nFixedEventTargets + (includeTime ? 0 : 1);
  const C_FLOAT64 * pRate = mRate.array() + mSize.nFixedEventTargets + 1;

  size_t Col;

  C_FLOAT64 Store;
  C_FLOAT64 X1;
  C_FLOAT64 X2;
  C_FLOAT64 InvDelta;

  CVector< C_FLOAT64 > Y1(Rows);
  CVector< C_FLOAT64 > Y2(Rows);

  C_FLOAT64 * pY1;
  C_FLOAT64 * pY2;

  C_FLOAT64 * pX = pState;
  C_FLOAT64 * pXEnd = pX + Columns;

  C_FLOAT64 * pJacobian;
  C_FLOAT64 * pJacobianEnd = jacobian.array() + jacobian.size();

  for (Col = 0; pX != pXEnd; ++pX, ++Col)
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
      updateSimulatedValues(reduced);
      memcpy(Y1.array(), pRate, Rows * sizeof(C_FLOAT64));

      *pX = X2;
      updateSimulatedValues(reduced);
      memcpy(Y2.array(), pRate, Rows * sizeof(C_FLOAT64));

      *pX = Store;

      pJacobian = jacobian.array() + Col;
      pY1 = Y1.array();
      pY2 = Y2.array();

      for (; pJacobian < pJacobianEnd; pJacobian += Columns, ++pY1, ++pY2)
        * pJacobian = (*pY2 - *pY1) * InvDelta;
    }

  updateSimulatedValues(reduced);
}

void CMathContainer::calculateJacobianDependencies(CMatrix< C_INT32 > & jacobianDependencies,
    const bool & reduced)
{
  size_t Dim = getState(reduced).size() - mSize.nFixedEventTargets - 1;
  jacobianDependencies.resize(Dim, Dim);
  jacobianDependencies = 0;

  // The required values are the rates of the variables
  CMathObject * pRateObject = getMathObject(mRate.array() + mSize.nFixedEventTargets + mSize.nTime);
  CMathObject * pRateObjectEnd = pRateObject + Dim;

  ObjectSet Requested;

  for (; pRateObject != pRateObjectEnd; ++ pRateObject)
    {
      Requested.insert(pRateObject);
    }

  // Reset the pointer so that we have the appropriate boundaries for later
  pRateObject = pRateObjectEnd - Dim;

  // For each of the variables we check whether a the rate objects needs to be calculated
  // which indicates that it is dependent.
  CMathObject * pVariable = getMathObject(mState.array() + mSize.nFixedEventTargets + mSize.nTime);
  CMathObject * pVariableEnd = pVariable + Dim;
  size_t col = 0;

  for (; pVariable != pVariableEnd; ++pVariable, ++col)
    {
      CCore::CUpdateSequence Sequence;
      ObjectSet Changed;

      Changed.insert(pVariable);

      mTransientDependencies.getUpdateSequence(Sequence, reduced ? CCore::SimulationContext::UseMoieties : CCore::SimulationContext::Default, Changed, Requested);

      CCore::CUpdateSequence::const_iterator it = Sequence.begin();
      CCore::CUpdateSequence::const_iterator end = Sequence.end();

      for (; it != end; ++it)
        if (pRateObject <= *it && *it < pRateObjectEnd)
          {
            // it points to a rate object, i.e., it is dependent.
            jacobianDependencies[static_cast< CMathObject * >(*it) - pRateObject][col] = 1;
          }
    }

  return;
}

void CMathContainer::calculateElasticityDependencies(CMatrix< C_INT32 > & elasticityDependencies,
    const bool & reduced)
{
  size_t Dim = getState(reduced).size() - mSize.nFixedEventTargets - 1;
  elasticityDependencies.resize(mSize.nReactions, Dim);
  elasticityDependencies = 0;

  // The required values are the reaction fluxes.

  CMathObject * pFluxObject = getMathObject(mFluxes.array());
  CMathObject * pFluxObjectEnd = pFluxObject + mSize.nReactions;

  ObjectSet Requested;

  for (; pFluxObject != pFluxObjectEnd; ++pFluxObject)
    {
      Requested.insert(pFluxObject);
    }

  // Reset the pointer so that we have the appropriate boundaries for later
  pFluxObject = pFluxObjectEnd - mSize.nReactions;

  // For each of the variables we check whether a the rate objects needs to be calculated
  // which indicates that it is dependent.
  CMathObject * pVariable = getMathObject(mState.array() + mSize.nFixedEventTargets + mSize.nTime);
  CMathObject * pVariableEnd = pVariable + Dim;
  size_t col = 0;

  for (; pVariable != pVariableEnd; ++pVariable, ++col)
    {
      CCore::CUpdateSequence Sequence;
      ObjectSet Changed;

      Changed.insert(pVariable);

      mTransientDependencies.getUpdateSequence(Sequence, reduced ? CCore::SimulationContext::UseMoieties : CCore::SimulationContext::Default, Changed, Requested);

      CCore::CUpdateSequence::const_iterator it = Sequence.begin();
      CCore::CUpdateSequence::const_iterator end = Sequence.end();

      for (; it != end; ++it)
        {
          CMathObject * pObject = dynamic_cast< CMathObject * >(*it);

          if (pFluxObject <= pObject && pObject < pFluxObjectEnd)
            {
              // it points to a rate object, i.e., it is dependent.
              elasticityDependencies[pObject - pFluxObject][col] = 1;
            }
        }
    }

  return;
}

CMath::StateChange CMathContainer::processQueue(const bool & equality)
{
  return mpProcessQueue->process(equality);
}

void CMathContainer::processRoots(const bool & equality,
                                  const CVector< C_INT > & rootsFound)
{
#ifdef DEBUG_OUTPUT
  std::cout << rootsFound << std::endl;
#endif // DEBUG_OUTPUT

  // Reevaluate all non found roots.
  CMathEvent::CTrigger::CRootProcessor ** pRoot = mRootProcessors.array();
  CMathEvent::CTrigger::CRootProcessor ** pRootEnd = pRoot + mRootProcessors.size();
  const C_INT * pRootFound = rootsFound.array();

  for (; pRoot != pRootEnd; ++pRoot, ++pRootFound)
    {
      if (*pRootFound == static_cast< C_INT >(CMath::RootToggleType::NoToggle))
        {
          (*pRoot)->calculateTrueValue();
        }
    }

  // Calculate the trigger values and store them before the root processors
  // are changing the state
  CMathObject * pTrigger = getMathObject(mEventTriggers.array());
  CMathObject * pTriggerEnd = pTrigger + mEventTriggers.size();

  for (; pTrigger != pTriggerEnd; ++pTrigger)
    {
      pTrigger->calculateValue();
    }

  CVector< C_FLOAT64 > Before = mEventTriggers;

  // Toggle all found roots.
  pRoot = mRootProcessors.array();
  pRootFound = rootsFound.array();
  C_FLOAT64 & Time = mState[mSize.nFixedEventTargets];

  for (; pRoot != pRootEnd; ++pRoot, ++pRootFound)
    {
      if (*pRootFound == static_cast< C_INT >(CMath::RootToggleType::ToggleBoth) ||
          (*pRootFound == static_cast< C_INT >(CMath::RootToggleType::ToggleEquality) && equality) ||
          (*pRootFound == static_cast< C_INT >(CMath::RootToggleType::ToggleInequality) && !equality))
        {
          (*pRoot)->toggle(Time, equality);
        }
    }

  // Calculate the new trigger values
  pTrigger = getMathObject(mEventTriggers.array());

  for (; pTrigger != pTriggerEnd; ++pTrigger)
    {
      pTrigger->calculateValue();
    }

  // Find out which events fire and add them to the process queue
  C_FLOAT64 * pBefore = Before.array();
  C_FLOAT64 * pAfter = mEventTriggers.array();
  CMathEvent * pEvent = mEvents.array();
  CMathEvent * pEventEnd = pEvent + mEvents.size();

  // Compare Before and the current mEventTriggers
  for (; pEvent != pEventEnd; ++pEvent, ++pBefore, ++pAfter)
    {
      if (*pBefore != *pAfter)
        {
          // We fire on any change. It is the responsibility of the event to add or remove
          // actions to the process queue.
          pEvent->fire(equality);
        }
    }

  return;
}

void CMathContainer::processRoots(const CVector< C_INT > & rootsFound)
{
  // Calculate the trigger values and store them before the root processors
  // are changing the state
  CMathObject * pTrigger = getMathObject(mEventTriggers.array());
  CMathObject * pTriggerEnd = pTrigger + mEventTriggers.size();

  for (; pTrigger != pTriggerEnd; ++pTrigger)
    {
      pTrigger->calculateValue();
    }

  CVector< C_FLOAT64 > Before = mEventTriggers;

  // Toggle all found roots.
  CMathEvent::CTrigger::CRootProcessor ** pRoot = mRootProcessors.array();
  CMathEvent::CTrigger::CRootProcessor ** pRootEnd = pRoot + mRootProcessors.size();
  const C_INT * pRootFound = rootsFound.array();
  C_FLOAT64 & Time = mState[mSize.nFixedEventTargets];

  for (; pRoot != pRootEnd; ++pRoot, ++pRootFound)
    {
      if (*pRootFound)
        {
          (*pRoot)->toggle(Time);
        }

      // We must not reevaluate.
    }

  // Calculate the new trigger values
  pTrigger = getMathObject(mEventTriggers.array());

  for (; pTrigger != pTriggerEnd; ++pTrigger)
    {
      pTrigger->calculateValue();
    }

  // Find out which events fire and add them to the process queue
  C_FLOAT64 * pBefore = Before.array();
  C_FLOAT64 * pAfter = mEventTriggers.array();
  CMathEvent * pEvent = mEvents.array();
  CMathEvent * pEventEnd = pEvent + mEvents.size();

  // Compare Before and the current mEventTriggers
  for (; pEvent != pEventEnd; ++pEvent, ++pBefore, ++pAfter)
    {
      if (*pBefore != *pAfter)
        {
          // We fire on any change. It is the responsibility of the event to add or remove
          // actions to the process queue.

          pEvent->fire(true);
        }
    }

  return;
}

CMathEventQueue & CMathContainer::getProcessQueue()
{
  return *mpProcessQueue;
}

C_FLOAT64 CMathContainer::getProcessQueueExecutionTime() const
{
  return mpProcessQueue->getProcessQueueExecutionTime();
}

void CMathContainer::initializePointers(CMath::sPointers & p)
{
  p.pInitialExtensiveValues = mInitialExtensiveValues.array();
  p.pInitialIntensiveValues = mInitialIntensiveValues.array();
  p.pInitialExtensiveRates = mInitialExtensiveRates.array();
  p.pInitialIntensiveRates = mInitialIntensiveRates.array();
  p.pInitialParticleFluxes = mInitialParticleFluxes.array();
  p.pInitialFluxes = mInitialFluxes.array();
  p.pInitialTotalMasses = mInitialTotalMasses.array();
  p.pInitialEventTriggers = mInitialEventTriggers.array();

  p.pExtensiveValues = mExtensiveValues.array();
  p.pIntensiveValues = mIntensiveValues.array();
  p.pExtensiveRates = mExtensiveRates.array();
  p.pIntensiveRates = mIntensiveRates.array();
  p.pParticleFluxes = mParticleFluxes.array();
  p.pFluxes = mFluxes.array();
  p.pTotalMasses = mTotalMasses.array();
  p.pEventTriggers = mEventTriggers.array();
  p.pExtensiveNoise = mExtensiveNoise.array();
  p.pIntensiveNoise = mIntensiveNoise.array();
  p.pReactionNoise = mReactionNoise.array();
  p.pReactionParticleNoise = mReactionParticleNoise.array();

  p.pEventDelays = mEventDelays.array();
  p.pEventPriorities = mEventPriorities.array();
  p.pEventAssignments = mEventAssignments.array();
  p.pEventRoots = mEventRoots.array();
  p.pEventRootStates = mEventRootStates.array();
  p.pPropensities = mPropensities.array();
  p.pDependentMasses = mDependentMasses.array();
  p.pDiscontinuous = mDiscontinuous.array();
  p.pDelayValue = mDelayValues.array();
  p.pDelayLag = mDelayLags.array();
  p.pTransitionTime = mTransitionTimes.array();

  C_FLOAT64 * pValues = mValues.array();
  CMathObject * pObjects = mObjects.array();

  p.pInitialExtensiveValuesObject = pObjects + (p.pInitialExtensiveValues - pValues);
  p.pInitialIntensiveValuesObject = pObjects + (p.pInitialIntensiveValues - pValues);
  p.pInitialExtensiveRatesObject = pObjects + (p.pInitialExtensiveRates - pValues);
  p.pInitialIntensiveRatesObject = pObjects + (p.pInitialIntensiveRates - pValues);
  p.pInitialParticleFluxesObject = pObjects + (p.pInitialParticleFluxes - pValues);
  p.pInitialFluxesObject = pObjects + (p.pInitialFluxes - pValues);
  p.pInitialTotalMassesObject = pObjects + (p.pInitialTotalMasses - pValues);
  p.pInitialEventTriggersObject = pObjects + (p.pInitialEventTriggers - pValues);

  p.pExtensiveValuesObject = pObjects + (p.pExtensiveValues - pValues);
  p.pIntensiveValuesObject = pObjects + (p.pIntensiveValues - pValues);
  p.pExtensiveRatesObject = pObjects + (p.pExtensiveRates - pValues);
  p.pIntensiveRatesObject = pObjects + (p.pIntensiveRates - pValues);
  p.pParticleFluxesObject = pObjects + (p.pParticleFluxes - pValues);
  p.pFluxesObject = pObjects + (p.pFluxes - pValues);
  p.pTotalMassesObject = pObjects + (p.pTotalMasses - pValues);
  p.pEventTriggersObject = pObjects + (p.pEventTriggers - pValues);

  p.pExtensiveNoiseObject = pObjects + (p.pExtensiveNoise - pValues);
  p.pIntensiveNoiseObject = pObjects + (p.pIntensiveNoise - pValues);
  p.pReactionNoiseObject = pObjects + (p.pReactionNoise - pValues);
  p.pReactionParticleNoiseObject = pObjects + (p.pReactionParticleNoise - pValues);

  p.pEventDelaysObject = pObjects + (p.pEventDelays - pValues);
  p.pEventPrioritiesObject = pObjects + (p.pEventPriorities - pValues);
  p.pEventAssignmentsObject = pObjects + (p.pEventAssignments - pValues);
  p.pEventRootsObject = pObjects + (p.pEventRoots - pValues);
  p.pEventRootStatesObject = pObjects + (p.pEventRootStates - pValues);
  p.pPropensitiesObject = pObjects + (p.pPropensities - pValues);
  p.pDependentMassesObject = pObjects + (p.pDependentMasses - pValues);
  p.pDiscontinuousObject = pObjects + (p.pDiscontinuous - pValues);
  p.pDelayValueObject = pObjects + (p.pDelayValue - pValues);
  p.pDelayLagObject = pObjects + (p.pDelayLag - pValues);
  p.pTransitionTimeObject = pObjects + (p.pTransitionTime - pValues);
}

#ifdef COPASI_DEBUG
void CMathContainer::printPointers(CMath::sPointers & p)
{
  size_t Index;
  std::cout << "Values:" << std::endl;
  Index = p.pInitialExtensiveValues - mInitialExtensiveValues.array();
  std::cout << "  mInitialExtensiveValues:[" << Index << "]" << ((mInitialExtensiveValues.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pInitialIntensiveValues - mInitialIntensiveValues.array();
  std::cout << "  mInitialIntensiveValues:[" << Index << "]" << ((mInitialIntensiveValues.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pInitialExtensiveRates - mInitialExtensiveRates.array();
  std::cout << "  mInitialExtensiveRates:[" << Index << "]" << ((mInitialExtensiveRates.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pInitialIntensiveRates - mInitialIntensiveRates.array();
  std::cout << "  mInitialIntensiveRates:[" << Index << "]" << ((mInitialIntensiveRates.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pInitialParticleFluxes - mInitialParticleFluxes.array();
  std::cout << "  mInitialParticleFluxes:[" << Index << "]" << ((mInitialParticleFluxes.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pInitialFluxes - mInitialFluxes.array();
  std::cout << "  mInitialFluxes:[" << Index << "]" << ((mInitialFluxes.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pInitialTotalMasses - mInitialTotalMasses.array();
  std::cout << "  mInitialTotalMasses:[" << Index << "]" << ((mInitialTotalMasses.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pInitialEventTriggers - mInitialEventTriggers.array();
  std::cout << "  mInitialEventTriggers:[" << Index << "]" << ((mInitialEventTriggers.size() <= Index) ? " Error" : "") << std::endl;

  Index = p.pExtensiveValues - mExtensiveValues.array();
  std::cout << "  mExtensiveValues:[" << Index << "]" << ((mExtensiveValues.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pIntensiveValues - mIntensiveValues.array();
  std::cout << "  mIntensiveValues:[" << Index << "]" << ((mIntensiveValues.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pExtensiveRates - mExtensiveRates.array();
  std::cout << "  mExtensiveRates:[" << Index << "]" << ((mExtensiveRates.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pIntensiveRates - mIntensiveRates.array();
  std::cout << "  mIntensiveRates:[" << Index << "]" << ((mIntensiveRates.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pParticleFluxes - mParticleFluxes.array();
  std::cout << "  mParticleFluxes:[" << Index << "]" << ((mParticleFluxes.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pFluxes - mFluxes.array();
  std::cout << "  mFluxes:[" << Index << "]" << ((mFluxes.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pTotalMasses - mTotalMasses.array();
  std::cout << "  mTotalMasses:[" << Index << "]" << ((mTotalMasses.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pEventTriggers - mEventTriggers.array();
  std::cout << "  mEventTriggers:[" << Index << "]" << ((mEventTriggers.size() <= Index) ? " Error" : "") << std::endl;

  Index = p.pEventDelays - mEventDelays.array();
  std::cout << "  mEventDelays:[" << Index << "]" << ((mEventDelays.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pEventPriorities - mEventPriorities.array();
  std::cout << "  mEventPriorities:[" << Index << "]" << ((mEventPriorities.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pEventAssignments - mEventAssignments.array();
  std::cout << "  mEventAssignments:[" << Index << "]" << ((mEventAssignments.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pEventRoots - mEventRoots.array();
  std::cout << "  mEventRoots:[" << Index << "]" << ((mEventRoots.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pEventRootStates - mEventRootStates.array();
  std::cout << "  mEventRootStates:[" << Index << "]" << ((mEventRootStates.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pPropensities - mPropensities.array();
  std::cout << "  mPropensities:[" << Index << "]" << ((mPropensities.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pDependentMasses - mDependentMasses.array();
  std::cout << "  mDependentMasses:[" << Index << "]" << ((mDependentMasses.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pDiscontinuous - mDiscontinuous.array();
  std::cout << "  mDiscontinuous:[" << Index << "]" << ((mDiscontinuous.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pDelayValue - mDelayValues.array();
  std::cout << "  mDelayValue:[" << Index << "]" << ((mDelayValues.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pDelayLag - mDelayLags.array();
  std::cout << "  mDelayLag:[" << Index << "]" << ((mDelayLags.size() <= Index) ? " Error" : "") << std::endl;
  Index = p.pTransitionTime - mTransitionTimes.array();
  std::cout << "  mTransitionTime:[" << Index << "]" << ((mTransitionTimes.size() <= Index) ? " Error" : "") << std::endl;
  std::cout << std::endl;
}
#endif // COPASI_DEBUG

void CMathContainer::initializeDiscontinuousCreationPointer()
{
  C_FLOAT64 * pValues = mValues.array();
  CMathObject * pObjects = mObjects.array();

  size_t nDiscontinuous = mDiscontinuous.size();
  size_t nEvents = mEvents.size() - nDiscontinuous;

  mCreateDiscontinuousPointer.pEvent = mEvents.array() + nEvents;
  mCreateDiscontinuousPointer.pDiscontinuous = pObjects + (mDiscontinuous.array() - pValues);

  /*
  mCreateDiscontinuousPointer.pEventDelay = pObjects + (mEventDelays.array() - pValues) + nEvents;
  mCreateDiscontinuousPointer.pEventPriority = pObjects + (mEventPriorities.array() - pValues) + nEvents;
  mCreateDiscontinuousPointer.pEventAssignment = pObjects + (mEventAssignments.array() - pValues) + nEventAssignments;
  mCreateDiscontinuousPointer.pEventTrigger = pObjects + (mEventTriggers.array() - pValues) + nEvents;
  mCreateDiscontinuousPointer.pEventRoot = pObjects + (mEventRoots.array() - pValues) + nEventRoots;
  */
}

// static
CMath::EntityType CMathContainer::getEntityType(const CModelEntity * pEntity)
{
  const CMetab * pSpecies = dynamic_cast< const CMetab * >(pEntity);

  if (pSpecies != NULL)
    {
      return CMath::EntityType::Species;
    }
  else if (dynamic_cast< const CCompartment * >(pEntity) != NULL)
    {
      return CMath::EntityType::Compartment;
    }
  else if (dynamic_cast< const CModelValue * >(pEntity) != NULL)
    {
      return CMath::EntityType::GlobalQuantity;
    }

  return CMath::EntityType::Undefined;
}

void CMathContainer::initializeMathObjects(const std::vector<const CModelEntity*> & entities,
    const CMath::SimulationType & simulationType,
    CMath::sPointers & p)
{
  // Process entities.
  std::vector<const CModelEntity*>::const_iterator it = entities.begin();
  std::vector<const CModelEntity*>::const_iterator end = entities.end();

  CMath::EntityType EntityType;

  for (; it != end; ++it)
    {
      EntityType = getEntityType(*it);

      // Extensive Initial Value

      // The simulation type for initial values is either CMath::Assignment or CMath::Fixed
      // We must check whether the initial value must be calculated, i.e., whether it has
      // dependencies or not. In case of species it always possible that is must be calculated.

      CMath::SimulationType SimulationType = CMath::SimulationType::Fixed;
      CDataObject * pObject = (*it)->getInitialValueReference();

      if (EntityType == CMath::EntityType::Species)
        {
          SimulationType = CMath::SimulationType::Conversion;
        }
      else if ((simulationType == CMath::SimulationType::Assignment && (*it)->getExpression() != "") ||
               (*it)->getInitialExpression() != "")
        {
          SimulationType = CMath::SimulationType::Assignment;
        }

      CMathObject::initialize(p.pInitialExtensiveValuesObject++, p.pInitialExtensiveValues++,
                              CMath::ValueType::Value, EntityType, SimulationType, false, true,
                              pObject);

      // Extensive Value
      SimulationType = simulationType;

      if (EntityType == CMath::EntityType::Species &&
          simulationType == CMath::SimulationType::Assignment)
        {
          SimulationType = CMath::SimulationType::Conversion;
        }

      CMathObject::initialize(p.pExtensiveValuesObject++, p.pExtensiveValues++,
                              CMath::ValueType::Value, EntityType, SimulationType, false, false,
                              (*it)->getValueReference());

      // Initial Extensive Rate
      SimulationType = simulationType;

      if (simulationType == CMath::SimulationType::EventTarget)
        {
          SimulationType = CMath::SimulationType::Fixed;
        }

      CMathObject::initialize(p.pInitialExtensiveRatesObject++, p.pInitialExtensiveRates++,
                              CMath::ValueType::Rate, EntityType, SimulationType, false, true,
                              (*it)->getRateReference());

      // Extensive Rate
      CMathObject::initialize(p.pExtensiveRatesObject++, p.pExtensiveRates++,
                              CMath::ValueType::Rate, EntityType, SimulationType, false, false,
                              (*it)->getRateReference());

      // Extensive Noise
      if (simulationType == CMath::SimulationType::ODE ||
          simulationType == CMath::SimulationType::Independent ||
          simulationType == CMath::SimulationType::Dependent)
        {
          CMathObject::initialize(p.pExtensiveNoiseObject++, p.pExtensiveNoise++,
                                  CMath::ValueType::Noise, EntityType, SimulationType, false, false,
                                  (*it)->getNoiseReference());
        }

      // Species have intensive values in addition to the extensive ones and transition time.
      if (EntityType == CMath::EntityType::Species)
        {
          const CMetab *pSpecies = static_cast<const CMetab*>(*it);

          // Intensive Initial Value

          // The simulation type for initial values is either CMath::SimulationType::Assignment or CMath::SimulationType::Conversion
          // In case of species it always possible that is must be calculated.
          SimulationType = CMath::SimulationType::Conversion;

          if (simulationType == CMath::SimulationType::Assignment ||
              pSpecies->getInitialExpression() != "")
            {
              SimulationType = CMath::SimulationType::Assignment;
            }

          CMathObject::initialize(p.pInitialIntensiveValuesObject++, p.pInitialIntensiveValues++,
                                  CMath::ValueType::Value, CMath::EntityType::Species, SimulationType, true, true,
                                  pSpecies->getInitialConcentrationReference());

          // Intensive Value
          SimulationType = CMath::SimulationType::Conversion;

          if (simulationType == CMath::SimulationType::Assignment)
            {
              SimulationType = simulationType;
            }

          CMathObject::initialize(p.pIntensiveValuesObject++, p.pIntensiveValues++,
                                  CMath::ValueType::Value, CMath::EntityType::Species, SimulationType, true, false,
                                  pSpecies->getConcentrationReference());

          // Initial Intensive Rate
          CMathObject::initialize(p.pInitialIntensiveRatesObject++, p.pInitialIntensiveRates++,
                                  CMath::ValueType::Rate, CMath::EntityType::Species, CMath::SimulationType::Assignment, true, true,
                                  pSpecies->getConcentrationRateReference());

          // Intensive Rate

          CMathObject::initialize(p.pIntensiveRatesObject++, p.pIntensiveRates++,
                                  CMath::ValueType::Rate, CMath::EntityType::Species, CMath::SimulationType::Assignment, true, false,
                                  pSpecies->getConcentrationRateReference());

          // Intensive Noise
          if (simulationType == CMath::SimulationType::ODE ||
              simulationType == CMath::SimulationType::Independent ||
              simulationType == CMath::SimulationType::Dependent)
            {
              CMathObject::initialize(p.pIntensiveNoiseObject++, p.pIntensiveNoise++,
                                      CMath::ValueType::Noise, CMath::EntityType::Species, CMath::SimulationType::Assignment, true, false,
                                      pSpecies->getIntensiveNoiseReference());
            }

          // Transition Time
          CMathObject::initialize(p.pTransitionTimeObject++, p.pTransitionTime++,
                                  CMath::ValueType::TransitionTime, CMath::EntityType::Species, CMath::SimulationType::Assignment, false, false,
                                  pSpecies->getTransitionTimeReference());
        }
    }
}

void CMathContainer::initializeMathObjects(const std::vector<const CDataObject *> & parameters,
    CMath::sPointers & p)
{
  // Process parameters.
  std::vector<const CDataObject *>::const_iterator it = parameters.begin();
  std::vector<const CDataObject *>::const_iterator end = parameters.end();

  for (; it != end; ++it)
    {
      // Extensive Initial Value
      CMathObject::initialize(p.pInitialExtensiveValuesObject++, p.pInitialExtensiveValues++,
                              CMath::ValueType::Value, CMath::EntityType::LocalReactionParameter, CMath::SimulationType::Fixed, false, true,
                              *it);

      // Extensive Value
      CMathObject::initialize(p.pExtensiveValuesObject++, p.pExtensiveValues++,
                              CMath::ValueType::Value, CMath::EntityType::LocalReactionParameter, CMath::SimulationType::Fixed, false, false,
                              NULL);

      // Initial Extensive Rate
      CMathObject::initialize(p.pInitialExtensiveRatesObject++, p.pInitialExtensiveRates++,
                              CMath::ValueType::Rate, CMath::EntityType::LocalReactionParameter, CMath::SimulationType::Fixed, false, true,
                              NULL);

      // Extensive Rate
      CMathObject::initialize(p.pExtensiveRatesObject++, p.pExtensiveRates++,
                              CMath::ValueType::Rate, CMath::EntityType::LocalReactionParameter, CMath::SimulationType::Fixed, false, false,
                              NULL);
    }
}

void CMathContainer::initializeMathObjects(const CDataVector< CReaction > & reactions,
    CMath::sPointers & p)
{
  // Process reactions.
  CDataVector< CReaction >::const_iterator it = reactions.begin();
  CDataVector< CReaction >::const_iterator end = reactions.end();

  for (; it != end; ++it)
    {
      // Initial Particle Flux
      CMathObject::initialize(p.pInitialParticleFluxesObject++, p.pInitialParticleFluxes++,
                              CMath::ValueType::ParticleFlux, CMath::EntityType::Reaction, CMath::SimulationType::Undefined, false, true,
                              it->getParticleFluxReference());

      // Particle Flux
      CMathObject::initialize(p.pParticleFluxesObject++, p.pParticleFluxes++,
                              CMath::ValueType::ParticleFlux, CMath::EntityType::Reaction, CMath::SimulationType::Undefined, false, false,
                              it->getParticleFluxReference());

      // Initial Flux
      CMathObject::initialize(p.pInitialFluxesObject++, p.pInitialFluxes++,
                              CMath::ValueType::Flux, CMath::EntityType::Reaction, CMath::SimulationType::Undefined, false, true,
                              it->getFluxReference());

      // Flux
      CMathObject::initialize(p.pFluxesObject++, p.pFluxes++,
                              CMath::ValueType::Flux, CMath::EntityType::Reaction, CMath::SimulationType::Undefined, false, false,
                              it->getFluxReference());

      // Noise
      CMathObject::initialize(p.pReactionNoiseObject++, p.pReactionNoise++,
                              CMath::ValueType::Noise, CMath::EntityType::Reaction, CMath::SimulationType::Undefined, false, false,
                              it->getNoiseReference());

      // Particle Noise
      CMathObject::initialize(p.pReactionParticleNoiseObject++, p.pReactionParticleNoise++,
                              CMath::ValueType::ParticleNoise, CMath::EntityType::Reaction, CMath::SimulationType::Undefined, false, false,
                              it->getParticleNoiseReference());

      // Propensity
      CMathObject::initialize(p.pPropensitiesObject++, p.pPropensities++,
                              CMath::ValueType::Propensity, CMath::EntityType::Reaction, CMath::SimulationType::Undefined, false, false,
                              it->getPropensityReference());
    }
}

void CMathContainer::initializeMathObjects(const CDataVector< CMoiety > & moieties,
    CMath::sPointers & p)
{
  // Process reactions.
  CDataVector< CMoiety >::const_iterator it = moieties.begin();
  CDataVector< CMoiety >::const_iterator end = moieties.end();

  for (; it != end; ++it)
    {
      // Initial Total Mass
      CMathObject::initialize(p.pInitialTotalMassesObject++, p.pInitialTotalMasses++,
                              CMath::ValueType::TotalMass, CMath::EntityType::Moiety, CMath::SimulationType::Undefined, false, true,
                              it->getInitialTotalNumberReference());

      // Total Mass
      CMathObject::initialize(p.pTotalMassesObject++, p.pTotalMasses++,
                              CMath::ValueType::TotalMass, CMath::EntityType::Moiety, CMath::SimulationType::Undefined, false, false,
                              it->getTotalNumberReference());

      // Dependent
      CMathObject::initialize(p.pDependentMassesObject++, p.pDependentMasses++,
                              CMath::ValueType::DependentMass, CMath::EntityType::Moiety, CMath::SimulationType::Undefined, false, false,
                              it->getDependentNumberReference());
    }
}

void CMathContainer::map()
{
  CMathObject * itObject = mObjects.begin();
  CMathObject * endObject = mObjects.end();

  for (; itObject != endObject; ++itObject)
    {
      const CDataObject * pDataObject = itObject->getDataObject();

      if (pDataObject != NULL)
        {
          mDataObject2MathObject[pDataObject] = itObject;
          mDataValue2MathObject[(C_FLOAT64 *) pDataObject->getValuePointer()] = itObject;
        }
    }
}

C_FLOAT64 * CMathContainer::getInitialValuePointer(const C_FLOAT64 * pValue) const
{
  assert((mValues.array() <= pValue && pValue < mValues.array() + mValues.size()) || getDataObject(pValue) != NULL);

  const C_FLOAT64 * pInitialValue = pValue;

  if (mExtensiveValues.array() <= pValue && pValue < mExtensiveNoise.array())
    {
      pInitialValue = mInitialExtensiveValues.array() + (pValue - mExtensiveValues.array());
    }

  return const_cast< C_FLOAT64 * >(pInitialValue);
}

CMathObject * CMathContainer::getInitialValueObject(const CMathObject * pObject) const
{
  if (pObject != NULL)
    return getMathObject(getInitialValuePointer(&pObject->getValue()));

  return NULL;
}

C_FLOAT64 * CMathContainer::getValuePointer(const C_FLOAT64 * pInitialValue) const
{
  assert((mValues.begin() <= pInitialValue && pInitialValue < mValues.end()) || getDataObject(pInitialValue) != NULL);

  const C_FLOAT64 * pValue = pInitialValue;

  if (mValues.begin() <= pInitialValue && pInitialValue < mExtensiveValues.begin())
    {
      pValue = mExtensiveValues.begin() + (pInitialValue - mValues.begin());
    }

  return const_cast< C_FLOAT64 * >(pValue);
}

CMathObject * CMathContainer::getValueObject(const CMathObject * pInitialObject) const
{
  if (pInitialObject != NULL)
    return getMathObject(getValuePointer(&pInitialObject->getValue()));

  return NULL;
}

CMath::Entity< CMathObject > CMathContainer::addAnalysisObject(const CMath::Entity< CDataObject > & entity,
    const CMath::SimulationType & simulationType,
    const std::string & infix)
{
  CMath::Entity< CMathObject > Entity;

  sSize Size = mSize;

  switch (simulationType)
    {
      case CMath::SimulationType::Fixed:
        Size.nFixed++;
        break;

      case CMath::SimulationType::ODE:
        Size.nODE++;
        break;

      case CMath::SimulationType::Assignment:
        Size.nAssignment++;
        break;

      case CMath::SimulationType::Undefined:
      case CMath::SimulationType::EventTarget:
      case CMath::SimulationType::Time:
      case CMath::SimulationType::Dependent:
      case CMath::SimulationType::Independent:
      case CMath::SimulationType::Conversion:
        fatalError();
        break;

      case CMath::SimulationType::__SIZE:
        break;
    }

  resize(Size);
  finishResize();

  CExpression Expression("Source", this);

  if (!Expression.setInfix(infix)) return Entity;

  CMathObject * pObject = mObjects.array();
  CMathObject * pObjectEnd = pObject + mObjects.size();
  size_t kind = 0;

  for (; pObject != pObjectEnd; ++pObject)
    {
      if (pObject->getValueType() != CMath::ValueType::Undefined ||
          pObject->getEntityType() != CMath::EntityType::Undefined ||
          pObject->getSimulationType() != CMath::SimulationType::Undefined) continue;

      C_FLOAT64 * pValue = (C_FLOAT64 *) pObject->getValuePointer();

      switch (kind)
        {
          case 0:
            CMathObject::initialize(pObject++, pValue++, CMath::ValueType::Value, CMath::EntityType::Analysis,
                                    (simulationType == CMath::SimulationType::Assignment) ? CMath::SimulationType::Assignment : CMath::SimulationType::Fixed,
                                    false, true, entity.InitialValue);

            if (simulationType == CMath::SimulationType::Assignment)
              {
                CMathExpression * pExpression = new CMathExpression("Assignment", *this);
                pExpression->CEvaluationTree::setRoot(copyBranch(Expression.getRoot(), false));
                pExpression->convertToInitialExpression();
                pObject->setExpressionPtr(pExpression);
              }

            Entity.InitialValue = pObject;
            ++kind;
            break;

          case 1:
            CMathObject::initialize(pObject++, pValue++, CMath::ValueType::Rate, CMath::EntityType::Analysis,
                                    simulationType, false, true,
                                    entity.InitialRate);

            if (simulationType == CMath::SimulationType::ODE)
              {
                CMathExpression * pExpression = new CMathExpression("Rate", *this);
                pExpression->CEvaluationTree::setRoot(copyBranch(Expression.getRoot(), false));
                pExpression->convertToInitialExpression();
                pObject->setExpressionPtr(pExpression);
              }

            Entity.InitialRate = pObject;
            ++kind;
            break;

          case 2:
            CMathObject::initialize(pObject++, pValue++, CMath::ValueType::Value, CMath::EntityType::Analysis,
                                    simulationType, false, false,
                                    entity.Value);

            if (simulationType == CMath::SimulationType::Assignment)
              {
                CMathExpression * pExpression = new CMathExpression("Assignment", *this);
                pExpression->CEvaluationTree::setRoot(copyBranch(Expression.getRoot(), false));
                pObject->setExpressionPtr(pExpression);
              }

            Entity.Value = pObject;
            ++kind;
            break;

          case 3:
            CMathObject::initialize(pObject++, pValue++, CMath::ValueType::Rate, CMath::EntityType::Analysis,
                                    simulationType, false, false,
                                    entity.Rate);

            if (simulationType == CMath::SimulationType::ODE)
              {
                CMathExpression * pExpression = new CMathExpression("Rate", *this);
                pExpression->CEvaluationTree::setRoot(copyBranch(Expression.getRoot(), false));
                pObject->setExpressionPtr(pExpression);
              }

            Entity.Rate = pObject;
            ++kind;
            break;
        }

#ifdef USE_JIT
      pObject->compile(*this, *mpJITCompiler);
#else
      pObject->compile(*this);
#endif

      mInitialDependencies.addObject(pObject);
    }

  assert(kind == 4);
  // We resize cleared mDataObject2MathObject and mDataValue2MathObject we must create a new map
  map();

  createUpdateSequences();

#ifdef USE_JIT

  try
    {
      mpJITCompiler->compile();
    }
  catch (...)
    {}

#endif
  return Entity;
}

bool CMathContainer::removeAnalysisObject(CMath::Entity< CMathObject > & mathObjects)
{
  sSize Size = mSize;
  size_t Index = C_INVALID_INDEX;

  switch (mathObjects.Value->getSimulationType())
    {
      case CMath::SimulationType::Fixed:
        Size.nFixed--;
        Index += mSize.nFixed;
        break;

      case CMath::SimulationType::EventTarget:
        Size.nFixedEventTargets--;
        Index += mSize.nFixed + mSize.nFixedEventTargets;
        break;

      case CMath::SimulationType::ODE:
        Size.nODE--;
        Index += mSize.nFixed + mSize.nFixedEventTargets + 2;
        break;

      case CMath::SimulationType::Assignment:
        Size.nAssignment--;
        Index += mSize.nFixed + mSize.nFixedEventTargets + mSize.nTime + mSize.nODE + mSize.nODESpecies + mSize.nReactionSpecies + mSize.nAssignment;
        break;

      case CMath::SimulationType::Undefined:
      case CMath::SimulationType::Time:
      case CMath::SimulationType::Dependent:
      case CMath::SimulationType::Independent:
      case CMath::SimulationType::Conversion:
        fatalError();
        break;

      case CMath::SimulationType::__SIZE:
        break;
    }

  // Check whether this is the last added entity.
  // Entities can only be removed in reverse order
  if (mathObjects.InitialValue != &mObjects[Index]) return false;

  // Update dependencies
  mInitialDependencies.removeObject(mathObjects.InitialValue);
  mInitialDependencies.removeObject(mathObjects.InitialRate);
  mTransientDependencies.removeObject(mathObjects.Value);
  mTransientDependencies.removeObject(mathObjects.Rate);

  // Remove references to removed objects
  mathObjects.InitialValue = NULL;
  mathObjects.InitialRate = NULL;
  mathObjects.Value = NULL;
  mathObjects.Rate = NULL;

  // Resize
  resize(Size);
  finishResize();

  // We resize cleared mDataObject2MathObject and mDataValue2MathObject we must create a new map
  map();

  // Create Update sequences
  createUpdateSequences();

#ifdef USE_JIT

  try
    {
      mpJITCompiler->compile();
    }
  catch (...)
    {}

#endif

  return true;
}

CMathEvent * CMathContainer::addAnalysisEvent(const CEvent * pDataEvent)
{
  sSize Size = mSize;
  sSize OldSize = mSize;

  CMathEvent Event;
  CMathEvent::allocate(Event, pDataEvent, *this);

  Size.nEvents++;
  Size.nEventRoots += Event.getTrigger().getRoots().size();
  Size.nEventAssignments += Event.getAssignments().size();

  resize(Size);
  finishResize();
  map();

  // The new event is the last in the list
  CMathEvent * pEvent = mEvents.array() + OldSize.nEvents;
  CMathEvent::allocate(*pEvent, pDataEvent, *this);

  CMath::sPointers p;
  initializePointers(p);

  // Account for pre-existing objects
  p.pEventTriggers += OldSize.nEvents;
  p.pEventTriggersObject += OldSize.nEvents;
  p.pInitialEventTriggers += OldSize.nEvents;
  p.pInitialEventTriggersObject += OldSize.nEvents;
  p.pEventDelays += OldSize.nEvents;
  p.pEventDelaysObject += OldSize.nEvents;
  p.pEventPriorities += OldSize.nEvents;
  p.pEventPrioritiesObject += OldSize.nEvents;

  p.pEventRootStates += OldSize.nEventRoots;
  p.pEventRootStatesObject += OldSize.nEventRoots;
  p.pEventRoots += OldSize.nEventRoots;
  p.pEventRootsObject += OldSize.nEventRoots;

  p.pEventAssignments += OldSize.nAssignment;
  p.pEventAssignmentsObject += OldSize.nAssignment;

  pEvent->initialize(p);
  pEvent->compile(pDataEvent, *this);

  // Add the objects created for the event to the dependency graphs.
  initializePointers(p);

  mInitialDependencies.addObject(p.pInitialEventTriggersObject + OldSize.nEvents);
  mTransientDependencies.addObject(p.pEventTriggersObject + OldSize.nEvents);
  mTransientDependencies.addObject(p.pEventDelaysObject + OldSize.nEvents);
  mTransientDependencies.addObject(p.pEventPrioritiesObject + OldSize.nEvents);

  for (size_t i = OldSize.nEventRoots; i != mSize.nEventRoots; ++i)
    {
      mTransientDependencies.addObject(p.pEventRootStatesObject + i);
      mTransientDependencies.addObject(p.pEventRootsObject + i);
    }

  for (size_t i = OldSize.nAssignment; i != mSize.nAssignment; ++i)
    {
      mTransientDependencies.addObject(p.pEventAssignmentsObject + i);
    }

  // Determine event targets and move objects accordingly.
  const CMathEvent::CAssignment * pAssignment = pEvent->getAssignments().array();
  const CMathEvent::CAssignment * pAssignmentEnd = pAssignment + pEvent->getAssignments().size();
  CMathObject * pFixedStart = getMathObject(mExtensiveValues.array());
  CMathObject * pFixedEnd = pFixedStart + mSize.nFixed;

  for (; pAssignment != pAssignmentEnd; ++pAssignment)
    {
      const CMathObject * pTarget = pAssignment->getTarget();

      if (pFixedStart <= pTarget && pTarget < pFixedEnd)
        {
          size_t CurrentIndex = (pTarget - pFixedStart);

          // Create a save haven
          CVector< C_FLOAT64 > EventTargetValues(4);
          CVector< CMathObject > EventTargetObjects(4);

          std::vector< CMath::sRelocate > Relocations;

          CMath::sRelocate RelocateTarget;
          RelocateTarget.pNewValue = EventTargetValues.array();
          RelocateTarget.pNewObject = EventTargetObjects.array();

          CMath::sRelocate RelocateOther;
          RelocateOther.pOldValue = mValues.array();
          RelocateOther.pNewValue = mValues.array();
          RelocateOther.pOldObject = mObjects.array();
          RelocateOther.pNewObject = mObjects.array();
          RelocateOther.offset = -1;

          // Initial value
          RelocateTarget.pValueStart = mInitialExtensiveValues.array() + CurrentIndex;
          RelocateTarget.pValueEnd = RelocateTarget.pValueStart + 1;
          RelocateTarget.pOldValue = RelocateTarget.pValueStart;
          RelocateTarget.pObjectStart = getMathObject(RelocateTarget.pValueStart);
          RelocateTarget.pObjectEnd = getMathObject(RelocateTarget.pValueEnd);
          RelocateTarget.pOldObject = getMathObject(RelocateTarget.pOldValue);
          RelocateTarget.offset = 0;
          Relocations.push_back(RelocateTarget);

          RelocateOther.pValueStart = RelocateTarget.pValueEnd;
          RelocateOther.pValueEnd = mInitialExtensiveValues.array() + mSize.nFixed  + mSize.nFixedEventTargets;
          RelocateOther.pObjectStart = getMathObject(RelocateOther.pValueStart);
          RelocateOther.pObjectEnd = getMathObject(RelocateOther.pValueEnd);
          Relocations.push_back(RelocateOther);

          // Initial rate
          RelocateTarget.pValueStart = mInitialExtensiveRates.array() + CurrentIndex;
          RelocateTarget.pValueEnd = RelocateTarget.pValueStart + 1;
          RelocateTarget.pOldValue = RelocateTarget.pValueStart;
          RelocateTarget.pObjectStart = getMathObject(RelocateTarget.pValueStart);
          RelocateTarget.pObjectEnd = getMathObject(RelocateTarget.pValueEnd);
          RelocateTarget.pOldObject = getMathObject(RelocateTarget.pOldValue);
          RelocateTarget.offset++;
          Relocations.push_back(RelocateTarget);

          RelocateOther.pValueStart = RelocateTarget.pValueEnd;
          RelocateOther.pValueEnd = mInitialExtensiveRates.array() + mSize.nFixed  + mSize.nFixedEventTargets;
          RelocateOther.pObjectStart = getMathObject(RelocateOther.pValueStart);
          RelocateOther.pObjectEnd = getMathObject(RelocateOther.pValueEnd);
          Relocations.push_back(RelocateOther);

          // Value
          RelocateTarget.pValueStart = mExtensiveValues.array() + CurrentIndex;
          RelocateTarget.pValueEnd = RelocateTarget.pValueStart + 1;
          RelocateTarget.pOldValue = RelocateTarget.pValueStart;
          RelocateTarget.pObjectStart = getMathObject(RelocateTarget.pValueStart);
          RelocateTarget.pObjectEnd = getMathObject(RelocateTarget.pValueEnd);
          RelocateTarget.pOldObject = getMathObject(RelocateTarget.pOldValue);
          RelocateTarget.offset++;
          Relocations.push_back(RelocateTarget);

          RelocateOther.pValueStart = RelocateTarget.pValueEnd;
          RelocateOther.pValueEnd = mExtensiveValues.array() + mSize.nFixed  + mSize.nFixedEventTargets;
          RelocateOther.pObjectStart = getMathObject(RelocateOther.pValueStart);
          RelocateOther.pObjectEnd = getMathObject(RelocateOther.pValueEnd);
          Relocations.push_back(RelocateOther);

          // Rate
          RelocateTarget.pValueStart = mExtensiveRates.array() + CurrentIndex;
          RelocateTarget.pValueEnd = RelocateTarget.pValueStart + 1;
          RelocateTarget.pOldValue = RelocateTarget.pValueStart;
          RelocateTarget.pObjectStart = getMathObject(RelocateTarget.pValueStart);
          RelocateTarget.pObjectEnd = getMathObject(RelocateTarget.pValueEnd);
          RelocateTarget.pOldObject = getMathObject(RelocateTarget.pOldValue);
          RelocateTarget.offset++;
          Relocations.push_back(RelocateTarget);

          RelocateOther.pValueStart = RelocateTarget.pValueEnd;
          RelocateOther.pValueEnd = mExtensiveRates.array() + mSize.nFixed  + mSize.nFixedEventTargets;
          RelocateOther.pObjectStart = getMathObject(RelocateOther.pValueStart);
          RelocateOther.pObjectEnd = getMathObject(RelocateOther.pValueEnd);
          Relocations.push_back(RelocateOther);

          Size = mSize;
          Size.nFixed--;
          Size.nFixedEventTargets++;

          relocate(Size, Relocations);

          // Move the event target out of the save haven.
          Relocations.clear();
          RelocateTarget.offset = 0;

          // Initial value
          RelocateTarget.pValueStart = EventTargetValues.array();
          RelocateTarget.pValueEnd = RelocateTarget.pValueStart + 1;
          RelocateTarget.pNewValue = mInitialExtensiveValues.array() + mSize.nFixed  + mSize.nFixedEventTargets - 1;
          RelocateTarget.pOldValue = RelocateTarget.pValueStart;
          RelocateTarget.pObjectStart = EventTargetObjects.array();
          RelocateTarget.pObjectEnd = RelocateTarget.pObjectStart + 1;
          RelocateTarget.pNewObject = getMathObject(RelocateTarget.pNewValue);
          RelocateTarget.pOldObject = RelocateTarget.pObjectStart;
          Relocations.push_back(RelocateTarget);

          // Initial Rate
          RelocateTarget.pValueStart++;
          RelocateTarget.pValueEnd++;
          RelocateTarget.pNewValue = mInitialExtensiveRates.array() + mSize.nFixed  + mSize.nFixedEventTargets - 1;
          RelocateTarget.pOldValue = RelocateTarget.pValueStart;
          RelocateTarget.pObjectStart++;
          RelocateTarget.pObjectEnd++;
          RelocateTarget.pNewObject = getMathObject(RelocateTarget.pNewValue);
          RelocateTarget.pOldObject = RelocateTarget.pObjectStart;
          Relocations.push_back(RelocateTarget);

          // Value
          RelocateTarget.pValueStart++;
          RelocateTarget.pValueEnd++;
          RelocateTarget.pNewValue = mExtensiveValues.array() + mSize.nFixed  + mSize.nFixedEventTargets - 1;
          RelocateTarget.pOldValue = RelocateTarget.pValueStart;
          RelocateTarget.pObjectStart++;
          RelocateTarget.pObjectEnd++;
          RelocateTarget.pNewObject = getMathObject(RelocateTarget.pNewValue);
          RelocateTarget.pOldObject = RelocateTarget.pObjectStart;
          Relocations.push_back(RelocateTarget);

          // Rate
          RelocateTarget.pValueStart++;
          RelocateTarget.pValueEnd++;
          RelocateTarget.pNewValue = mExtensiveRates.array() + mSize.nFixed  + mSize.nFixedEventTargets - 1;
          RelocateTarget.pOldValue = RelocateTarget.pValueStart;
          RelocateTarget.pObjectStart++;
          RelocateTarget.pObjectEnd++;
          RelocateTarget.pNewObject = getMathObject(RelocateTarget.pNewValue);
          RelocateTarget.pOldObject = RelocateTarget.pObjectStart;
          Relocations.push_back(RelocateTarget);

          Size = mSize;

          relocate(Size, Relocations);

          pFixedEnd--;
        }
    }

  // We resize cleared mDataObject2MathObject and mDataValue2MathObject we must create a new map
  map();

  analyzeRoots();
  createUpdateSequences();

#ifdef USE_JIT

  try
    {
      mpJITCompiler->compile();
    }
  catch (...)
    {}

#endif

  return pEvent;
}

bool CMathContainer::removeAnalysisEvent(CMathEvent *& pMathEvent)
{
  // We can only remove the last added event.
  CMathEvent * pEvent = &mEvents[mSize.nEvents - 1];

  if (pMathEvent != pEvent) return false;

  // Determine event targets and move objects accordingly.
  std::set< const CMathObject * > EventTargets;
  const CMathEvent::CAssignment * pAssignment = pEvent->getAssignments().array();
  const CMathEvent::CAssignment * pAssignmentEnd = pAssignment + pEvent->getAssignments().size();

  for (; pAssignment != pAssignmentEnd; ++pAssignment)
    {
      EventTargets.insert(pAssignment->getTarget());
    }

  sSize Size = mSize;

  Size.nEvents--;
  Size.nEventRoots -= pEvent->getTrigger().getRoots().size();
  Size.nEventAssignments -= pEvent->getAssignments().size();

  // Remove the objects created for the event from the dependency graphs.
  CMath::sPointers p;
  initializePointers(p);

  mInitialDependencies.removeObject(p.pInitialEventTriggersObject + Size.nEvents);
  mTransientDependencies.removeObject(p.pEventTriggersObject + Size.nEvents);
  mTransientDependencies.removeObject(p.pEventDelaysObject + Size.nEvents);
  mTransientDependencies.removeObject(p.pEventPrioritiesObject + Size.nEvents);

  for (size_t i = Size.nEventRoots; i != mSize.nEventRoots; ++i)
    {
      mTransientDependencies.removeObject(p.pEventRootStatesObject + i);
      mTransientDependencies.removeObject(p.pEventRootsObject + i);
    }

  for (size_t i = Size.nAssignment; i != mSize.nAssignment; ++i)
    {
      mTransientDependencies.removeObject(p.pEventAssignmentsObject + i);
    }

  pEvent = NULL;
  pMathEvent = NULL;

  // Resize
  resize(Size);
  finishResize();

  CMathObject * pEventTarget = getMathObject(mExtensiveValues.array()) + mSize.nFixed;
  CMathObject * pEventTargetEnd = pEventTarget + mSize.nFixedEventTargets;

  // We have remove them in the reverse order than they were added;
  while (pEventTarget != pEventTargetEnd)
    {
      pEventTargetEnd--;

      // It is save to return since we only added to the end
      if (EventTargets.count(pEventTargetEnd) == 0) return true;

      // We have found a candidate we need to make sure that this is not a target of any other event
      // before we mark it as fixed.
      const CMathEvent * pEvent = mEvents.array();
      const CMathEvent * pEventEnd = pEvent + mEvents.size();

      for (; pEvent != pEventEnd; ++pEvent)
        {
          pAssignment = pEvent->getAssignments().array();
          pAssignmentEnd = pAssignment + pEvent->getAssignments().size();

          for (; pAssignment != pAssignmentEnd; ++pAssignment)
            {
              // It is save to return since we only added to the end
              if (EventTargets.count(pAssignment->getTarget()) == 0) return true;
            }
        }

      // We have found an event target which is now fixed.
      // Create a save haven
      CVector< C_FLOAT64 > EventTargetValues(mSize.nFixedEventTargets * 4);
      CVector< CMathObject > EventTargetObjects(mSize.nFixedEventTargets * 4);

      std::vector< CMath::sRelocate > Relocations;

      CMath::sRelocate RelocateTarget;
      RelocateTarget.pNewValue = EventTargetValues.array();
      RelocateTarget.pNewObject = EventTargetObjects.array();

      // Initial value
      RelocateTarget.pValueStart = mInitialExtensiveValues.array() + mSize.nFixed;
      RelocateTarget.pValueEnd = RelocateTarget.pValueStart + mSize.nFixedEventTargets;
      RelocateTarget.pOldValue = RelocateTarget.pValueStart;
      RelocateTarget.pObjectStart = getMathObject(RelocateTarget.pValueStart);
      RelocateTarget.pObjectEnd = getMathObject(RelocateTarget.pValueEnd);
      RelocateTarget.pOldObject = getMathObject(RelocateTarget.pOldValue);
      RelocateTarget.offset = 0;
      Relocations.push_back(RelocateTarget);

      // Initial rate
      RelocateTarget.pValueStart = mInitialExtensiveRates.array() + mSize.nFixed;
      RelocateTarget.pValueEnd = RelocateTarget.pValueStart + mSize.nFixedEventTargets;
      RelocateTarget.pOldValue = RelocateTarget.pValueStart;
      RelocateTarget.pObjectStart = getMathObject(RelocateTarget.pValueStart);
      RelocateTarget.pObjectEnd = getMathObject(RelocateTarget.pValueEnd);
      RelocateTarget.pOldObject = getMathObject(RelocateTarget.pOldValue);
      RelocateTarget.offset += mSize.nFixedEventTargets;
      Relocations.push_back(RelocateTarget);

      // Value
      RelocateTarget.pValueStart = mExtensiveValues.array() + mSize.nFixed;
      RelocateTarget.pValueEnd = RelocateTarget.pValueStart + mSize.nFixedEventTargets;
      RelocateTarget.pOldValue = RelocateTarget.pValueStart;
      RelocateTarget.pObjectStart = getMathObject(RelocateTarget.pValueStart);
      RelocateTarget.pObjectEnd = getMathObject(RelocateTarget.pValueEnd);
      RelocateTarget.pOldObject = getMathObject(RelocateTarget.pOldValue);
      RelocateTarget.offset += mSize.nFixedEventTargets;
      Relocations.push_back(RelocateTarget);

      // Rate
      RelocateTarget.pValueStart = mExtensiveRates.array() + mSize.nFixed;
      RelocateTarget.pValueEnd = RelocateTarget.pValueStart + mSize.nFixedEventTargets;
      RelocateTarget.pOldValue = RelocateTarget.pValueStart;
      RelocateTarget.pObjectStart = getMathObject(RelocateTarget.pValueStart);
      RelocateTarget.pObjectEnd = getMathObject(RelocateTarget.pValueEnd);
      RelocateTarget.pOldObject = getMathObject(RelocateTarget.pOldValue);
      RelocateTarget.offset += mSize.nFixedEventTargets;
      Relocations.push_back(RelocateTarget);

      Size = mSize;

      relocate(Size, Relocations);

      Relocations.clear();

      // Move the event target out of the save haven.
      Relocations.clear();
      RelocateTarget.offset = 0;

      CMath::sRelocate RelocateOther;
      RelocateOther.offset = 0;

      // Initial value
      RelocateTarget.pValueStart = EventTargetValues.array() + mSize.nFixedEventTargets - 1;
      RelocateTarget.pValueEnd = RelocateTarget.pValueStart + 1;
      RelocateTarget.pOldValue = RelocateTarget.pValueStart;
      RelocateTarget.pNewValue = mInitialExtensiveValues.array() + mSize.nFixed;
      RelocateTarget.pObjectStart = EventTargetObjects.array() + mSize.nFixedEventTargets - 1;
      RelocateTarget.pObjectEnd = RelocateTarget.pObjectStart + 1;
      RelocateTarget.pOldObject = RelocateTarget.pObjectStart;
      RelocateTarget.pNewObject = getMathObject(RelocateTarget.pNewValue);
      Relocations.push_back(RelocateTarget);

      RelocateOther.pValueStart = RelocateTarget.pValueEnd;
      RelocateOther.pValueEnd = RelocateOther.pValueStart + mSize.nFixedEventTargets - 1;
      RelocateOther.pOldValue = RelocateOther.pValueStart;
      RelocateOther.pNewValue = RelocateTarget.pNewValue + 1;
      RelocateOther.pObjectStart = RelocateTarget.pObjectEnd;
      RelocateOther.pObjectEnd = RelocateOther.pObjectStart + mSize.nFixedEventTargets - 1;
      RelocateOther.pOldObject = RelocateOther.pObjectStart;
      RelocateOther.pNewObject = getMathObject(RelocateOther.pNewValue);
      Relocations.push_back(RelocateOther);

      // Initial Rate
      RelocateTarget.pValueStart += mSize.nFixedEventTargets;
      RelocateTarget.pValueEnd += mSize.nFixedEventTargets;
      RelocateTarget.pOldValue += mSize.nFixedEventTargets;
      RelocateTarget.pNewValue = mInitialExtensiveRates.array() + mSize.nFixed;
      RelocateTarget.pObjectStart += mSize.nFixedEventTargets;
      RelocateTarget.pObjectEnd += mSize.nFixedEventTargets;
      RelocateTarget.pOldObject += mSize.nFixedEventTargets;
      RelocateTarget.pNewObject = getMathObject(RelocateTarget.pNewValue);
      Relocations.push_back(RelocateTarget);

      RelocateOther.pValueStart += mSize.nFixedEventTargets;
      RelocateOther.pValueEnd += mSize.nFixedEventTargets;
      RelocateOther.pOldValue += mSize.nFixedEventTargets;
      RelocateOther.pNewValue = RelocateTarget.pNewValue + 1;
      RelocateOther.pObjectStart += mSize.nFixedEventTargets;
      RelocateOther.pObjectEnd += mSize.nFixedEventTargets;
      RelocateOther.pOldObject += mSize.nFixedEventTargets;
      RelocateOther.pNewObject = getMathObject(RelocateOther.pNewValue);
      Relocations.push_back(RelocateOther);

      // Value
      RelocateTarget.pValueStart += mSize.nFixedEventTargets;
      RelocateTarget.pValueEnd += mSize.nFixedEventTargets;
      RelocateTarget.pOldValue += mSize.nFixedEventTargets;
      RelocateTarget.pNewValue = mExtensiveValues.array() + mSize.nFixed;
      RelocateTarget.pObjectStart += mSize.nFixedEventTargets;
      RelocateTarget.pObjectEnd += mSize.nFixedEventTargets;
      RelocateTarget.pOldObject += mSize.nFixedEventTargets;
      RelocateTarget.pNewObject = getMathObject(RelocateTarget.pNewValue);
      Relocations.push_back(RelocateTarget);

      RelocateOther.pValueStart += mSize.nFixedEventTargets;
      RelocateOther.pValueEnd += mSize.nFixedEventTargets;
      RelocateOther.pOldValue += mSize.nFixedEventTargets;
      RelocateOther.pNewValue = RelocateTarget.pNewValue + 1;
      RelocateOther.pObjectStart += mSize.nFixedEventTargets;
      RelocateOther.pObjectEnd += mSize.nFixedEventTargets;
      RelocateOther.pOldObject += mSize.nFixedEventTargets;
      RelocateOther.pNewObject = getMathObject(RelocateOther.pNewValue);
      Relocations.push_back(RelocateOther);

      // Rate
      RelocateTarget.pValueStart += mSize.nFixedEventTargets;
      RelocateTarget.pValueEnd += mSize.nFixedEventTargets;
      RelocateTarget.pOldValue += mSize.nFixedEventTargets;
      RelocateTarget.pNewValue = mExtensiveRates.array() + mSize.nFixed;
      RelocateTarget.pObjectStart += mSize.nFixedEventTargets;
      RelocateTarget.pObjectEnd += mSize.nFixedEventTargets;
      RelocateTarget.pOldObject += mSize.nFixedEventTargets;
      RelocateTarget.pNewObject = getMathObject(RelocateTarget.pNewValue);
      Relocations.push_back(RelocateTarget);

      RelocateOther.pValueStart += mSize.nFixedEventTargets;
      RelocateOther.pValueEnd += mSize.nFixedEventTargets;
      RelocateOther.pOldValue += mSize.nFixedEventTargets;
      RelocateOther.pNewValue = RelocateTarget.pNewValue + 1;
      RelocateOther.pObjectStart += mSize.nFixedEventTargets;
      RelocateOther.pObjectEnd += mSize.nFixedEventTargets;
      RelocateOther.pOldObject += mSize.nFixedEventTargets;
      RelocateOther.pNewObject = getMathObject(RelocateOther.pNewValue);
      Relocations.push_back(RelocateOther);

      Size = mSize;
      Size.nFixed++;
      Size.nFixedEventTargets--;

      relocate(Size, Relocations);
    }

  // We resize cleared mDataObject2MathObject and mDataValue2MathObject we must create a new map
  map();

  analyzeRoots();
  createUpdateSequences();

#ifdef USE_JIT

  try
    {
      mpJITCompiler->compile();
    }
  catch (...)
    {}

#endif

  return true;
}

CRandom & CMathContainer::getRandomGenerator() const
{
  return * mpRandomGenerator;
}

const CDataObject * CMathContainer::getRandomObject() const
{
  return &mRandom;
}

void CMathContainer::createDiscontinuityEvents()
{
  CEvaluationNodeConstant VariableNode(CEvaluationNode::SubType::NaN, "NAN");
  //size_t i, imax;

  // We need to create events for nodes which are capable of introducing
  // discontinuous changes.

  // Retrieve expression trees which contain discontinuities.
  std::vector< const CEvaluationTree * > TreesWithDiscontinuities =  mpModel->getTreesWithDiscontinuities();
  std::vector< const CEvaluationTree * >::const_iterator it = TreesWithDiscontinuities.begin();
  std::vector< const CEvaluationTree * >::const_iterator end = TreesWithDiscontinuities.end();

  std::vector< CEvaluationNode * > Variables;

  for (; it != end; ++it)
    {
      createDiscontinuityEvents(*it, Variables);
    }
}

void CMathContainer::createDiscontinuityEvents(const CEvaluationTree * pTree,
    const std::vector< CEvaluationNode * > & variables)
{
  // We create an AST in which all function calls are expanded
  CEvaluationNode * pRoot = copyBranch(pTree->getRoot(), variables, false);

  CNodeIterator< CEvaluationNode  > itNode(pRoot);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      switch (itNode->mainType() | itNode->subType())
        {
          case (CEvaluationNode::MainType::CHOICE | CEvaluationNode::SubType::IF):
          case (CEvaluationNode::MainType::FUNCTION | CEvaluationNode::SubType::FLOOR):
          case (CEvaluationNode::MainType::FUNCTION | CEvaluationNode::SubType::CEIL):
          case (CEvaluationNode::MainType::OPERATOR | CEvaluationNode::SubType::MODULUS):
          case (CEvaluationNode::MainType::OPERATOR | CEvaluationNode::SubType::REMAINDER):
            createDiscontinuityDataEvent(*itNode);
            break;

          // Call nodes and variables are eliminated.
          case (CEvaluationNode::MainType::CALL | CEvaluationNode::SubType::FUNCTION):
          case (CEvaluationNode::MainType::CALL | CEvaluationNode::SubType::EXPRESSION):
          case (CEvaluationNode::MainType::VARIABLE | CEvaluationNode::SubType::DEFAULT):
            fatalError();
            break;

          default:
            break;
        }
    }

  pdelete(pRoot);

  return;
}

void CMathContainer::createDiscontinuityDataEvent(const CEvaluationNode * pNode)
{
  // We can create a data event without knowing the variables as the number
  // of roots is independent from the variable value.
  CEvent * pEvent = new CEvent();
  pEvent->setType(CEvent::Discontinuity);
  mDiscontinuityEvents.add(pEvent, true);

  pEvent->setTriggerExpression(createDiscontinuityTriggerInfix(pNode));
}

std::string CMathContainer::createDiscontinuityTriggerInfix(const CEvaluationNode * pNode)
{
  std::string TriggerInfix;

  // We need to define a data event for each discontinuity.
  switch (pNode->mainType() | pNode->subType())
    {
      case (CEvaluationNode::MainType::CHOICE | CEvaluationNode::SubType::IF):
        TriggerInfix = static_cast< const CEvaluationNode * >(pNode->getChild())->buildInfix();
        break;

      case (CEvaluationNode::MainType::FUNCTION | CEvaluationNode::SubType::FLOOR):
      case (CEvaluationNode::MainType::FUNCTION | CEvaluationNode::SubType::CEIL):
        TriggerInfix = "sin(PI*(" + static_cast< const CEvaluationNode * >(pNode->getChild())->buildInfix() + ")) > 0";
        break;

      case (CEvaluationNode::MainType::OPERATOR | CEvaluationNode::SubType::MODULUS):
        TriggerInfix = "sin(PI*(" + static_cast< const CEvaluationNode * >(pNode->getChild())->buildInfix();
        TriggerInfix += ")) > 0 || sin(PI*(" + static_cast< const CEvaluationNode * >(pNode->getChild()->getSibling())->buildInfix() + ")) > 0";
        break;

      case (CEvaluationNode::MainType::OPERATOR | CEvaluationNode::SubType::REMAINDER):
        TriggerInfix = "sin(PI*(" + static_cast< const CEvaluationNode * >(pNode->getChild())->buildInfix() + "/";
        TriggerInfix += static_cast< const CEvaluationNode * >(pNode->getChild()->getSibling())->buildInfix() + ")) > 0";
        break;

      default:
        fatalError();
        break;
    }

  return TriggerInfix;
}

void CMathContainer::createDelays()
{
  // We check all transient objects for the occurrences of delays
  CMathObject * pObject = getMathObject(mExtensiveValues.array());
  CMathObject * pObjectEnd = getMathObject(mDelayValues.array());

  // The above returns NULL if no delays are present.
  if (pObjectEnd == NULL)
    {
      pObjectEnd = const_cast< CMathObject * >(mObjects.array() + mObjects.size());
    }

  CMath::DelayData DelayData;

  for (; pObject != pObjectEnd; ++pObject)
    {
      pObject->appendDelays(DelayData);
    }

  if (DelayData.size() == 0)
    {
      mHistory.resize(0, 0, 0);

      return;
    }

  sSize Size = mSize;
  Size.nDelayLags = 0;
  Size.nDelayValues = 0;

  CMath::DelayData::iterator itDelayLag = DelayData.begin();
  CMath::DelayData::iterator endDelayLag = DelayData.end();
  std::string LagKey = "";
  std::vector< size_t > LagValueCounts;
  std::vector< size_t >::reverse_iterator itCurrentLagValueCount;

  for (; itDelayLag != endDelayLag; ++itDelayLag)
    {
      if (itDelayLag->first != LagKey)
        {
          LagKey = itDelayLag->first;
          Size.nDelayLags++;
          LagValueCounts.push_back((size_t) 0);
          itCurrentLagValueCount = LagValueCounts.rbegin();
        }

      CMath::DelayValueData::iterator itDelayValue = itDelayLag->second.begin();
      CMath::DelayValueData::iterator endDelayValue = itDelayLag->second.end();
      std::string ValueKey = "";

      for (; itDelayValue != endDelayValue; ++itDelayValue)
        {
          if (itDelayValue->first != ValueKey)
            {
              ValueKey = itDelayValue->first;
              Size.nDelayValues++;
              (*itCurrentLagValueCount)++;
            }
        }
    }

  std::vector< CMath::sRelocate > Relocations = resize(Size);

  // Update the mappings of the delays
  // We need to update all keys and values
  CMath::DelayData MappedDelayData;
  CMath::DelayData::iterator currentDelayData = MappedDelayData.end();

  for (itDelayLag = DelayData.begin(), LagKey = ""; itDelayLag != endDelayLag; ++itDelayLag)
    {
      if (itDelayLag->first != LagKey)
        {
          LagKey = itDelayLag->first;

          CMathExpression LagExpression("LagExpression", *this);
          LagExpression.setInfix(itDelayLag->first);
          LagExpression.relocate(this, Relocations);
          currentDelayData = MappedDelayData.insert(std::make_pair(LagExpression.getInfix(), CMath::DelayValueData()));
        }

      assert(currentDelayData != MappedDelayData.end());

      CMath::DelayValueData::iterator itDelayValue = itDelayLag->second.begin();
      CMath::DelayValueData::iterator endDelayValue = itDelayLag->second.end();
      std::string ValueKey;
      std::string MappedValueKey;

      for (; itDelayValue != endDelayValue; ++itDelayValue)
        {
          if (itDelayValue->first != ValueKey)
            {
              ValueKey = itDelayValue->first;

              CMathExpression ValueExpression("ValueExpression", *this);
              ValueExpression.setInfix(itDelayValue->first);
              ValueExpression.relocate(this, Relocations);
              MappedValueKey = ValueExpression.getInfix();
            }

          CMathExpression DelayExpression("DelayExpression", *this);
          DelayExpression.setInfix(itDelayValue->second.first);
          DelayExpression.relocate(this, Relocations);

          CMathObject * pDelayObject = itDelayValue->second.second;
          relocateObject(pDelayObject, Relocations);

          currentDelayData->second.insert(std::make_pair(MappedValueKey, std::make_pair(DelayExpression.getInfix(), pDelayObject)));
        }
    }

  pObject = getMathObject(mDelayValues.array());
  pObjectEnd = pObject + mDelayValues.size();
  C_FLOAT64 * pValue = mDelayValues.array();

  while (pObject != pObjectEnd)
    {
      CMathObject::initialize(pObject++, pValue++, CMath::ValueType::DelayValue, CMath::EntityType::Delay,
                              CMath::SimulationType::Undefined, false, false, NULL);
    }

  pObjectEnd += mSize.nDelayLags;

  while (pObject != pObjectEnd)
    {
      CMathObject::initialize(pObject++, pValue++, CMath::ValueType::DelayLag, CMath::EntityType::Delay,
                              CMath::SimulationType::Undefined, false, false, NULL);
    }

  CMathDelay * pDelay = mDelays.array();
  CMathObject * pDelayValueObject = getMathObject(mDelayValues.array());
  CMathObject * pDelayLagObject = getMathObject(mDelayLags.array());
  std::vector< size_t >::const_iterator itLagValueCount = LagValueCounts.begin();

  itDelayLag = MappedDelayData.begin();
  endDelayLag = MappedDelayData.end();
  LagKey = "";

  for (; itDelayLag != endDelayLag; ++itDelayLag)
    {
      // If we have a new key we create a new delay
      if (itDelayLag->first != LagKey)
        {
          // Advance the pointers except for the first time
          if (LagKey != "")
            {
              ++pDelay;
              ++pDelayLagObject;
              ++itLagValueCount;
              ++pDelayValueObject;
            }

          LagKey = itDelayLag->first;
          pDelay->create(itDelayLag, *itLagValueCount, *this, pDelayLagObject);
        }

      CMath::DelayValueData::iterator itDelayValue = itDelayLag->second.begin();
      CMath::DelayValueData::iterator endDelayValue = itDelayLag->second.end();
      std::string ValueKey = "";
      size_t index = 0;

      for (; itDelayValue != endDelayValue; ++itDelayValue)
        {
          if (itDelayValue->first != ValueKey)
            {
              // Advance the pointers except for the first time
              if (ValueKey != "")
                {
                  ++pDelayValueObject;
                  ++index;
                }

              ValueKey = itDelayValue->first;
              pDelay->addValueObject(itDelayValue, index, pDelayValueObject);
            }

          // Update the expression in which the delay occurred.
          pDelay->modifyMathObject(itDelayValue, index);
        }
    }

  finishResize();
  map();
}

void CMathContainer::createRelocations(const CMathContainer::sSize & size, std::vector< CMath::sRelocate > & relocations)
{
  CMath::sRelocate Relocate;
  Relocate.pValueStart = mSize.pValue;
  Relocate.pValueEnd = mSize.pValue;
  Relocate.pOldValue = mSize.pValue;
  Relocate.pNewValue = size.pValue;

  Relocate.pObjectStart = mSize.pObject;
  Relocate.pObjectEnd = mSize.pObject;
  Relocate.pOldObject = mSize.pObject;
  Relocate.pNewObject = size.pObject;

  Relocate.offset = 0;

  // Initial Values
  createRelocation(size.nFixed, mSize.nFixed, Relocate, relocations);
  createRelocation(size.nFixedEventTargets, mSize.nFixedEventTargets, Relocate, relocations);
  createRelocation(size.nTime, mSize.nTime, Relocate, relocations);
  // New ODE Values are the only values inserted at the beginning
  createRelocation(size.nODE, mSize.nODE, Relocate, relocations, false);
  createRelocation(size.nODESpecies, mSize.nODESpecies, Relocate, relocations);
  createRelocation(size.nReactionSpecies, mSize.nReactionSpecies, Relocate, relocations);
  createRelocation(size.nAssignment, mSize.nAssignment, Relocate, relocations);
  createRelocation(size.nIntensiveValues, mSize.nIntensiveValues, Relocate, relocations);

  // Initial Rates
  createRelocation(size.nFixed, mSize.nFixed, Relocate, relocations);
  createRelocation(size.nFixedEventTargets, mSize.nFixedEventTargets, Relocate, relocations);
  createRelocation(size.nTime, mSize.nTime, Relocate, relocations);
  // New ODE Values are the only values inserted at the beginning
  createRelocation(size.nODE, mSize.nODE, Relocate, relocations, false);
  createRelocation(size.nODESpecies, mSize.nODESpecies, Relocate, relocations);
  createRelocation(size.nReactionSpecies, mSize.nReactionSpecies, Relocate, relocations);
  createRelocation(size.nAssignment, mSize.nAssignment, Relocate, relocations);
  createRelocation(size.nIntensiveValues, mSize.nIntensiveValues, Relocate, relocations);

  // Internal Values
  createRelocation(size.nReactions, mSize.nReactions, Relocate, relocations);
  createRelocation(size.nReactions, mSize.nReactions, Relocate, relocations);
  createRelocation(size.nMoieties, mSize.nMoieties, Relocate, relocations);
  createRelocation(size.nEvents, mSize.nEvents, Relocate, relocations);

  // Transient Values
  createRelocation(size.nFixed, mSize.nFixed, Relocate, relocations);
  createRelocation(size.nFixedEventTargets, mSize.nFixedEventTargets, Relocate, relocations);
  createRelocation(size.nTime, mSize.nTime, Relocate, relocations);
  // New ODE Values are the only values inserted at the beginning
  createRelocation(size.nODE, mSize.nODE, Relocate, relocations, false);
  createRelocation(size.nODESpecies, mSize.nODESpecies, Relocate, relocations);
  createRelocation(size.nReactionSpecies, mSize.nReactionSpecies, Relocate, relocations);
  createRelocation(size.nAssignment, mSize.nAssignment, Relocate, relocations);
  createRelocation(size.nIntensiveValues, mSize.nIntensiveValues, Relocate, relocations);

  // Transient Rates
  createRelocation(size.nFixed, mSize.nFixed, Relocate, relocations);
  createRelocation(size.nFixedEventTargets, mSize.nFixedEventTargets, Relocate, relocations);
  createRelocation(size.nTime, mSize.nTime, Relocate, relocations);
  // New ODE Values are the only values inserted at the beginning
  createRelocation(size.nODE, mSize.nODE, Relocate, relocations, false);
  createRelocation(size.nODESpecies, mSize.nODESpecies, Relocate, relocations);
  createRelocation(size.nReactionSpecies, mSize.nReactionSpecies, Relocate, relocations);
  createRelocation(size.nAssignment, mSize.nAssignment, Relocate, relocations);
  createRelocation(size.nIntensiveValues, mSize.nIntensiveValues, Relocate, relocations);

  // Internal Values
  createRelocation(size.nReactions, mSize.nReactions, Relocate, relocations);
  createRelocation(size.nReactions, mSize.nReactions, Relocate, relocations);
  createRelocation(size.nMoieties, mSize.nMoieties, Relocate, relocations);
  createRelocation(size.nEvents, mSize.nEvents, Relocate, relocations);

  // Noise
  // New ODE Values are the only values inserted at the beginning
  createRelocation(size.nODE, mSize.nODE, Relocate, relocations, false);
  createRelocation(size.nODESpecies, mSize.nODESpecies, Relocate, relocations);
  createRelocation(size.nReactionSpecies, mSize.nReactionSpecies, Relocate, relocations);
  createRelocation(size.nODESpecies, mSize.nODESpecies, Relocate, relocations);
  createRelocation(size.nReactionSpecies, mSize.nReactionSpecies, Relocate, relocations);
  createRelocation(size.nReactions, mSize.nReactions, Relocate, relocations);
  createRelocation(size.nReactions, mSize.nReactions, Relocate, relocations);

  createRelocation(size.nEvents, mSize.nEvents, Relocate, relocations);
  createRelocation(size.nEvents, mSize.nEvents, Relocate, relocations);
  createRelocation(size.nEventAssignments, mSize.nEventAssignments, Relocate, relocations);
  createRelocation(size.nEventRoots, mSize.nEventRoots, Relocate, relocations);
  createRelocation(size.nEventRoots, mSize.nEventRoots, Relocate, relocations);
  createRelocation(size.nReactions, mSize.nReactions, Relocate, relocations);
  createRelocation(size.nMoieties, mSize.nMoieties, Relocate, relocations);
  createRelocation(size.nDiscontinuities, mSize.nDiscontinuities, Relocate, relocations);
  createRelocation(size.nDelayValues, mSize.nDelayValues, Relocate, relocations);
  createRelocation(size.nDelayLags, mSize.nDelayLags, Relocate, relocations);
  createRelocation(size.nIntensiveValues, mSize.nIntensiveValues, Relocate, relocations);

  if (Relocate.pValueStart != Relocate.pValueEnd)
    {
      relocations.push_back(Relocate);
    }
}

void CMathContainer::ignoreDiscontinuityEvent(CMathEvent * pEvent)
{
  pEvent->setDisabled(true);

  size_t EventIndex = pEvent - mEvents.begin();
  size_t NumRootsIgnored = pEvent->getTrigger().getRoots().size();
  size_t NumRootsToKeep = 0;

  for (CMathEvent * pIt = mEvents.begin(); pIt != pEvent; ++pIt)

    // The roots of disabled events have already been moved
    if (!pIt->isDisabled())
      {
        NumRootsToKeep += pIt->getTrigger().getRoots().size();
      }

  std::vector< CMath::sRelocate > Relocations;
  std::set< CMathObject * > UnusedObjects;

  CMath::sRelocate Relocate;
  Relocate.pValueStart = mSize.pValue;
  Relocate.pValueEnd = mSize.pValue;
  Relocate.pOldValue = mSize.pValue;
  Relocate.pNewValue = mSize.pValue;

  Relocate.pObjectStart = mSize.pObject;
  Relocate.pObjectEnd = mSize.pObject;
  Relocate.pOldObject = mSize.pObject;
  Relocate.pNewObject = mSize.pObject;

  Relocate.offset = 0;

  size_t Keep = mInitialEventTriggers.array() - mValues.array() + EventIndex;

  // Keep all initial values in place before the ignored event in place.
  createRelocation(Keep, Keep, Relocate, Relocations);
  // Skip the ignored initial event trigger
  createRelocation(0, 1, Relocate, Relocations);
  // Move the remaining initial event triggers
  createRelocation(mSize.nEvents - EventIndex - 1,
                   mSize.nEvents - EventIndex - 1,
                   Relocate, Relocations);
  // Align with the existing objects
  createRelocation(1, 0, Relocate, Relocations);
  UnusedObjects.insert(Relocate.pObjectStart - 1);

  // Keep all values in place before the ignored event in place.
  Keep = mEventTriggers.array() - mExtensiveValues.array() + EventIndex;
  createRelocation(Keep, Keep, Relocate, Relocations);
  // Skip the ignored event trigger
  createRelocation(0, 1, Relocate, Relocations);
  // Move the remaining event triggers
  createRelocation(mSize.nEvents - EventIndex - 1,
                   mSize.nEvents - EventIndex - 1,
                   Relocate, Relocations);
  // Align with the existing objects
  createRelocation(1, 0, Relocate, Relocations);
  UnusedObjects.insert(Relocate.pObjectStart - 1);

  // Keep noise related values and event delays before the ignored event.
  Keep = mEventDelays.array() - mExtensiveNoise.array() + EventIndex;

  // Event Delays
  createRelocation(Keep, Keep, Relocate, Relocations);
  // Skip the ignored event delay
  createRelocation(0, 1, Relocate, Relocations);
  // Move the remaining event delays
  createRelocation(mSize.nEvents - EventIndex - 1,
                   mSize.nEvents - EventIndex - 1,
                   Relocate, Relocations);
  // Align with the existing objects
  createRelocation(1, 0, Relocate, Relocations);
  UnusedObjects.insert(Relocate.pObjectStart - 1);

  // Event Priorities
  createRelocation(EventIndex, EventIndex, Relocate, Relocations);
  // Skip the ignored event priority
  createRelocation(0, 1, Relocate, Relocations);
  // Move the remaining event priorities
  createRelocation(mSize.nEvents - EventIndex - 1,
                   mSize.nEvents - EventIndex - 1,
                   Relocate, Relocations);
  // Align with the existing objects
  createRelocation(1, 0, Relocate, Relocations);
  UnusedObjects.insert(Relocate.pObjectStart - 1);

  // Keep the assignments and roots in place before the ignored roots
  createRelocation(mSize.nEventAssignments + NumRootsToKeep, mSize.nEventAssignments + NumRootsToKeep, Relocate, Relocations);
  // Skip the ignored roots
  createRelocation(0, NumRootsIgnored, Relocate, Relocations);
  // Move the remaining roots
  createRelocation(mSize.nEventRoots - NumRootsToKeep - NumRootsIgnored,
                   mSize.nEventRoots - NumRootsToKeep - NumRootsIgnored,
                   Relocate, Relocations);
  // Align with the existing objects
  createRelocation(NumRootsIgnored, 0, Relocate, Relocations);

  // Add the ignored root objects to the unused objects
  for (CMathObject * pObject = Relocate.pObjectStart - NumRootsIgnored; pObject != Relocate.pObjectStart; ++pObject)
    {
      UnusedObjects.insert(pObject);
    }

  if (Relocate.pValueStart != Relocate.pValueEnd)
    {
      Relocations.push_back(Relocate);
    }

  relocate(mSize, Relocations);

  std::set< CMathObject * >::iterator it = UnusedObjects.begin();
  std::set< CMathObject * >::iterator end = UnusedObjects.end();

  for (; it != end; ++it)
    {
      (*it)->setExpression("", false, *this);
    }

  mNumTotalRootsIgnored += NumRootsIgnored;
  mEventRoots.initialize(mEventRoots.size() - mNumTotalRootsIgnored, mEventRoots.array());
  mEventRootStates.initialize(mEventRootStates.size() - mNumTotalRootsIgnored, mEventRootStates.array());
  mRootProcessors.resize(mRootProcessors.size() - mNumTotalRootsIgnored, true);
  mRootIsDiscrete.resize(mRootIsDiscrete.size() - mNumTotalRootsIgnored, true);
  mRootIsTimeDependent.resize(mRootIsTimeDependent.size() - mNumTotalRootsIgnored, true);
}

std::vector< CMath::sRelocate > CMathContainer::resize(CMathContainer::sSize & size)
{
  if (size.nFixed == mSize.nFixed &&
      size.nFixedEventTargets == mSize.nFixedEventTargets &&
      size.nTime == mSize.nTime &&
      size.nODE == mSize.nODE &&
      size.nODESpecies == mSize.nODESpecies &&
      size.nReactionSpecies == mSize.nReactionSpecies &&
      size.nAssignment == mSize.nAssignment &&
      size.nIntensiveValues == mSize.nIntensiveValues &&
      size.nMoieties == mSize.nMoieties &&
      size.nEvents == mSize.nEvents &&
      size.nEventAssignments == mSize.nEventAssignments &&
      size.nEventRoots == mSize.nEventRoots &&
      size.nReactions == mSize.nReactions &&
      size.nDiscontinuities == mSize.nDiscontinuities &&
      size.nDelayValues == mSize.nDelayValues &&
      size.nDelayLags == mSize.nDelayLags)
    {
      return std::vector< CMath::sRelocate > ();
    }

  return move(size);
}

std::vector< CMath::sRelocate > CMathContainer::move(CMathContainer::sSize & size)
{
  std::vector< CMath::sRelocate > Relocations;

  // We must not relocate mDataObject2MathObject and mDataValue2MathObject as the key might have been deleted and newly allocated.
  mDataObject2MathObject.clear();
  mDataValue2MathObject.clear();

  // Determine the offsets
  // We have to cast all pointers to size_t to avoid pointer overflow.
  size_t nExtensiveValues = size.nFixed + size.nFixedEventTargets + size.nTime + size.nODE + size.nODESpecies + size.nReactionSpecies + size.nAssignment;
  size_t nNoise = size.nODE + 2 * size.nODESpecies + 2 * size.nReactionSpecies + 2 * size.nReactions;

  size_t ObjectCount = 4 * (nExtensiveValues + size.nIntensiveValues) +
                       5 * size.nReactions +
                       3 * size.nMoieties +
                       size.nDiscontinuities +
                       4 * size.nEvents + size.nEventAssignments + 2 * size.nEventRoots +
                       size.nDelayLags + size.nDelayValues +
                       size.nIntensiveValues +
                       nNoise;

  // We need to preserve the old values and objects until they are properly relocated;
  mpValuesBuffer = (ObjectCount > 0) ? new C_FLOAT64[ObjectCount] : NULL;
  mValues.initialize(ObjectCount, mpValuesBuffer);
  size.pValue = mValues.array();
  mValues = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

  mpObjectsBuffer = (ObjectCount > 0) ? new CMathObject[ObjectCount] : NULL;
  mObjects.initialize(ObjectCount, mpObjectsBuffer);
  size.pObject = mObjects.array();

  // Now we create the move information.
  createRelocations(size, Relocations);

  relocate(size, Relocations);

  return Relocations;
}

void CMathContainer::finishResize()
{
  // Delete the old objects
  if (mOldValues.array() != NULL &&
      mOldValues.array() != mValues.array())
    {
      delete [] mOldValues.array();
    }

  if (mOldObjects.array() != NULL &&
      mOldObjects.array() != mObjects.array())
    {
      delete [] mOldObjects.array();
    }

  mOldValues.initialize(mValues);
  mOldObjects.initialize(mObjects);
}

void CMathContainer::relocate(const sSize & size,
                              const std::vector< CMath::sRelocate > & Relocations)
{
  size_t nExtensiveValues = size.nFixed + size.nFixedEventTargets + size.nTime + size.nODE + size.nODESpecies + size.nReactionSpecies + size.nAssignment;

  // Move the objects to the new location
  const C_FLOAT64 * pValue = mOldValues.array();
  const C_FLOAT64 * pValueEnd = pValue + mOldValues.size();
  const CMathObject * pObject = mOldObjects.array();

  for (; pValue != pValueEnd; ++pValue, ++pObject)
    {
      // If we are here we are actually resizing
      C_FLOAT64 * pNewValue = const_cast< C_FLOAT64 *>(pValue);
      relocateValue(pNewValue, Relocations);

      if (pNewValue != NULL &&
          pNewValue != pValue)
        {
          *pNewValue = *pValue;
        }

      CMathObject * pNewObject = const_cast< CMathObject *>(pObject);
      relocateObject(pNewObject, Relocations);

      if (pNewObject != NULL &&
          pNewObject != pObject)
        {
          *pNewObject = *pObject;
          pNewObject->relocate(this, Relocations);
        }
    }

  C_FLOAT64 * pArray = size.pValue;
  mInitialExtensiveValues.initialize(nExtensiveValues, pArray);
  pArray += nExtensiveValues;
  mInitialIntensiveValues.initialize(size.nIntensiveValues, pArray);
  pArray += size.nIntensiveValues;
  mInitialExtensiveRates.initialize(nExtensiveValues, pArray);
  pArray += nExtensiveValues;
  mInitialIntensiveRates.initialize(size.nIntensiveValues, pArray);
  pArray += size.nIntensiveValues;
  mInitialParticleFluxes.initialize(size.nReactions, pArray);
  pArray += size.nReactions;
  mInitialFluxes.initialize(size.nReactions, pArray);
  pArray += size.nReactions;
  mInitialTotalMasses.initialize(size.nMoieties, pArray);
  pArray += size.nMoieties;
  mInitialEventTriggers.initialize(size.nEvents, pArray);
  pArray += size.nEvents;

  mExtensiveValues.initialize(nExtensiveValues, pArray);
  pArray += nExtensiveValues;
  mIntensiveValues.initialize(size.nIntensiveValues, pArray);
  pArray += size.nIntensiveValues;
  mExtensiveRates.initialize(nExtensiveValues, pArray);
  pArray += nExtensiveValues;
  mIntensiveRates.initialize(size.nIntensiveValues, pArray);
  pArray += size.nIntensiveValues;
  mParticleFluxes.initialize(size.nReactions, pArray);
  pArray += size.nReactions;
  mFluxes.initialize(size.nReactions, pArray);
  pArray += size.nReactions;
  mTotalMasses.initialize(size.nMoieties, pArray);
  pArray += size.nMoieties;
  mEventTriggers.initialize(size.nEvents, pArray);
  pArray += size.nEvents;

  mExtensiveNoise.initialize(size.nODE + size.nODESpecies + size.nReactionSpecies, pArray);
  pArray += size.nODE + size.nODESpecies + size.nReactionSpecies;
  mIntensiveNoise.initialize(size.nODESpecies + size.nReactionSpecies, pArray);
  pArray += size.nODESpecies + size.nReactionSpecies;
  mReactionNoise.initialize(size.nReactions, pArray);
  pArray += size.nReactions;
  mReactionParticleNoise.initialize(size.nReactions, pArray);
  pArray += size.nReactions;

  mEventDelays.initialize(size.nEvents, pArray);
  pArray += size.nEvents;
  mEventPriorities.initialize(size.nEvents, pArray);
  pArray += size.nEvents;
  mEventAssignments.initialize(size.nEventAssignments, pArray);
  pArray += size.nEventAssignments;
  mEventRoots.initialize(size.nEventRoots, pArray);
  pArray += size.nEventRoots;
  mEventRootStates.initialize(size.nEventRoots, pArray);
  pArray += size.nEventRoots;
  mPropensities.initialize(size.nReactions, pArray);
  pArray += size.nReactions;
  mDependentMasses.initialize(size.nMoieties, pArray);
  pArray += size.nMoieties;
  mDiscontinuous.initialize(size.nDiscontinuities, pArray);
  pArray += size.nDiscontinuities;
  mDelayValues.initialize(size.nDelayValues, pArray);
  pArray += size.nDelayValues;
  mDelayLags.initialize(size.nDelayLags, pArray);
  pArray += size.nDelayLags;
  mTransitionTimes.initialize(size.nIntensiveValues, pArray);
  pArray += size.nIntensiveValues;

  assert(pArray == mValues.array() + mValues.size());

  mInitialState.initialize(nExtensiveValues + size.nIntensiveValues,  mValues.array());
  mCompleteInitialState.initialize(mExtensiveValues.array() - mValues.array(), mValues.array());
  mState.initialize(size.nFixedEventTargets + size.nTime + size.nODE + size.nODESpecies + size.nReactionSpecies, mExtensiveValues.array() + size.nFixed);
  mStateReduced.initialize(mState.size() - size.nMoieties, mExtensiveValues.array() + size.nFixed);
  mRate.initialize(mState.size(), mExtensiveRates.array() + size.nFixed);
  mRateReduced.initialize(mStateReduced.size(), mExtensiveRates.array() + size.nFixed);
  mNoiseReduced.initialize(mExtensiveNoise.size() - size.nMoieties, mExtensiveNoise.array());

  mHistory.resize(mDelayLags.size(), mState.size(), mState.size());
  mHistoryReduced.initialize(mDelayLags.size(), mStateReduced.size(), mState.size(), mHistory.array());

  mRootProcessors.resize(size.nEventRoots, true);
  mRootIsDiscrete.resize(size.nEventRoots, true);
  mRootIsTimeDependent.resize(size.nEventRoots, true);

  std::set< CMathUpdateSequence * >::iterator itUpdateSequence = mUpdateSequences.begin();
  std::set< CMathUpdateSequence * >::iterator endUpdateSequence = mUpdateSequences.end();

  for (; itUpdateSequence != endUpdateSequence; ++itUpdateSequence)
    {
      relocateUpdateSequence(**itUpdateSequence, Relocations);
    }

  relocateObjectSet(mInitialStateValueExtensive, Relocations);
  relocateObjectSet(mInitialStateValueIntensive, Relocations);
  relocateObjectSet(mInitialStateValueAll, Relocations);
  relocateObjectSet(mStateValues, Relocations);
  relocateObjectSet(mReducedStateValues, Relocations);
  relocateObjectSet(mSimulationRequiredValues, Relocations);
  relocateObjectSet(mNoiseInputObjects, Relocations);
  relocateObjectSet(mValueChangeProhibited, Relocations);

  mInitialDependencies.relocate(this, Relocations);
  mTransientDependencies.relocate(this, Relocations);

  // Relocate the Events
  relocateVector(mEvents, size.nEvents, Relocations);

  // Relocate the Reactions
  relocateVector(mReactions, size.nReactions, Relocations);

  // Relocate Delays
  relocateVector(mDelays, size.nDelayLags, Relocations);

  relocateObjectSet(mValueChangeProhibited, Relocations);

  mSize = size;
  mpProcessQueue->start();
}

void CMathContainer::registerUpdateSequence(CMathUpdateSequence * pUpdateSequence)
{
  if (mUpdateSequences.insert(pUpdateSequence).second)
    {
      pUpdateSequence->setMathContainer(this);
    }
}

void CMathContainer::deregisterUpdateSequence(CMathUpdateSequence * pUpdateSequence)
{
  if (mUpdateSequences.erase(pUpdateSequence))
    {
      pUpdateSequence->setMathContainer(NULL);
    }
}
