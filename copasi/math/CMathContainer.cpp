// Copyright (C) 2011 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CMathContainer.h"
#include "CMathExpression.h"

#include "model/CModel.h"
#include "model/CCompartment.h"
#include "model/CMetab.h"
#include "model/CModelValue.h"
#include "model/CObjectLists.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CNodeIterator.h"

CMathContainer::CMathContainer():
  CCopasiContainer("Math Container", NULL, "CMathContainer"),
  mpModel(NULL),
  mpAvogadro(NULL),
  mpQuantity2NumberFactor(NULL),
  mValues(),
  mInitialExtensiveValues(),
  mInitialIntensiveValues(),
  mInitialExtensiveRates(),
  mInitialIntensiveRates(),
  mInitialParticleFluxes(),
  mInitialFluxes(),
  mInitialTotalMasses(),
  mInitialEventTriggers(),
  mExtensiveValues(),
  mIntensiveValues(),
  mExtensiveRates(),
  mIntensiveRates(),
  mParticleFluxes(),
  mFluxes(),
  mTotalMasses(),
  mEventTriggers(),
  mEventDelays(),
  mEventPriorities(),
  mEventAssignments(),
  mEventRoots(),
  mEventRootStates(),
  mPropensities(),
  mDependentMasses(),
  mDiscontinuous(),
  mFixedCount(0),
  mEventTargetCount(0),
  mODECount(0),
  mIndependentCount(0),
  mDependentCount(0),
  mAssignmentCount(0),
  mInitialState(),
  mState(),
  mStateReduced(),
  mInitialDependencies(),
  mTransientDependencies(),
  mSynchronizeInitialValuesSequenceExtensive(),
  mSynchronizeInitialValuesSequenceIntensive(),
  mApplyInitialValuesSequence(),
  mSimulationValuesSequence(),
  mSimulationValuesSequenceReduced(),
  mInitialStateValueExtensive(),
  mInitialStateValueIntensive(),
  mStateValues(),
  mReducedStateValues(),
  mSimulationRequiredValues(),
  mObjects(),
  mEvents(),
  mReactions(),
  mCreateDiscontinuousPointer(),
  mDataObject2MathObject(),
  mDataValue2MathObject(),
  mDiscontinuityEvents("Discontinuities", this),
  mDiscontinuityInfix2Object(),
  mTriggerInfix2Event()
{}

CMathContainer::CMathContainer(CModel & model):
  CCopasiContainer("Math Container", NULL, "CMathContainer"),
  mpModel(&model),
  mpAvogadro(NULL),
  mpQuantity2NumberFactor(NULL),
  mValues(),
  mInitialExtensiveValues(),
  mInitialIntensiveValues(),
  mInitialExtensiveRates(),
  mInitialIntensiveRates(),
  mInitialParticleFluxes(),
  mInitialFluxes(),
  mInitialTotalMasses(),
  mInitialEventTriggers(),
  mExtensiveValues(),
  mIntensiveValues(),
  mExtensiveRates(),
  mIntensiveRates(),
  mParticleFluxes(),
  mFluxes(),
  mTotalMasses(),
  mEventTriggers(),
  mEventDelays(),
  mEventPriorities(),
  mEventAssignments(),
  mEventRoots(),
  mEventRootStates(),
  mPropensities(),
  mDependentMasses(),
  mDiscontinuous(),
  mFixedCount(0),
  mEventTargetCount(0),
  mODECount(0),
  mIndependentCount(0),
  mDependentCount(0),
  mAssignmentCount(0),
  mInitialState(),
  mState(),
  mStateReduced(),
  mInitialDependencies(),
  mTransientDependencies(),
  mSynchronizeInitialValuesSequenceExtensive(),
  mSynchronizeInitialValuesSequenceIntensive(),
  mApplyInitialValuesSequence(),
  mSimulationValuesSequence(),
  mSimulationValuesSequenceReduced(),
  mInitialStateValueExtensive(),
  mInitialStateValueIntensive(),
  mStateValues(),
  mReducedStateValues(),
  mSimulationRequiredValues(),
  mObjects(),
  mEvents(),
  mReactions(),
  mDataObject2MathObject(),
  mDataValue2MathObject(),
  mDiscontinuityEvents("Discontinuities", this),
  mDiscontinuityInfix2Object(),
  mTriggerInfix2Event()
{
  // We do not want the model to know about the math container therefore we
  // do not use &model in the constructor of CCopasiContainer
  setObjectParent(mpModel);

  mpAvogadro = mpModel->getObject(CCopasiObjectName("Reference=Avogadro Constant"));
  mpQuantity2NumberFactor = mpModel->getObject(CCopasiObjectName("Reference=Quantity Conversion Factor"));

  init();
}

CMathContainer::CMathContainer(const CMathContainer & src):
  CCopasiContainer(src, NULL),
  mpModel(src.mpModel),
  mpAvogadro(src.mpAvogadro),
  mpQuantity2NumberFactor(src.mpQuantity2NumberFactor),
  mValues(src.mValues),
  mInitialExtensiveValues(),
  mInitialIntensiveValues(),
  mInitialExtensiveRates(),
  mInitialIntensiveRates(),
  mInitialParticleFluxes(),
  mInitialFluxes(),
  mInitialTotalMasses(),
  mInitialEventTriggers(),
  mExtensiveValues(),
  mIntensiveValues(),
  mExtensiveRates(),
  mIntensiveRates(),
  mParticleFluxes(),
  mFluxes(),
  mTotalMasses(),
  mEventTriggers(),
  mEventDelays(),
  mEventPriorities(),
  mEventAssignments(),
  mEventRoots(),
  mEventRootStates(),
  mPropensities(),
  mDependentMasses(),
  mDiscontinuous(),
  mFixedCount(src.mFixedCount),
  mEventTargetCount(src.mEventTargetCount),
  mODECount(src.mODECount),
  mIndependentCount(src.mIndependentCount),
  mDependentCount(src.mDependentCount),
  mAssignmentCount(src.mAssignmentCount),
  mInitialState(),
  mState(),
  mStateReduced(),
  mInitialDependencies(),
  mTransientDependencies(),
  mSynchronizeInitialValuesSequenceExtensive(),
  mSynchronizeInitialValuesSequenceIntensive(),
  mApplyInitialValuesSequence(),
  mSimulationValuesSequence(),
  mSimulationValuesSequenceReduced(),
  mInitialStateValueExtensive(),
  mInitialStateValueIntensive(),
  mStateValues(),
  mReducedStateValues(),
  mSimulationRequiredValues(),
  mObjects(src.mObjects.size()),
  mEvents(src.mEvents.size()),
  mReactions(src.mReactions.size()),
  mDataObject2MathObject(),
  mDataValue2MathObject(),
  mDiscontinuityEvents("Discontinuities", this),
  mDiscontinuityInfix2Object(),
  mTriggerInfix2Event()
{
  // We do not want the model to know about the math container therefore we
  // do not use &model in the constructor of CCopasiContainer
  setObjectParent(mpModel);

  // Determine the offsets
  // We have to cast all pointers to size_t to avoid pointer overflow.
  size_t ValueOffset = ((size_t) mValues.array()) - ((size_t) src.mValues.array());
  size_t ObjectOffset = ((size_t) mObjects.array()) - ((size_t) src.mObjects.array());

  mInitialExtensiveValues = CVectorCore< C_FLOAT64 >(src.mInitialExtensiveValues.size(),
                            (C_FLOAT64 *)((size_t) src.mInitialExtensiveValues.array() + ValueOffset));
  mInitialIntensiveValues = CVectorCore< C_FLOAT64 >(src.mInitialIntensiveValues.size(),
                            (C_FLOAT64 *)((size_t) src.mInitialIntensiveValues.array() + ValueOffset));
  mInitialExtensiveRates = CVectorCore< C_FLOAT64 >(src.mInitialExtensiveRates.size(),
                           (C_FLOAT64 *)((size_t) src.mInitialExtensiveRates.array() + ValueOffset));
  mInitialIntensiveRates = CVectorCore< C_FLOAT64 >(src.mInitialIntensiveRates.size(),
                           (C_FLOAT64 *)((size_t) src.mInitialIntensiveRates.array() + ValueOffset));
  mInitialParticleFluxes = CVectorCore< C_FLOAT64 >(src.mInitialParticleFluxes.size(),
                           (C_FLOAT64 *)((size_t) src.mInitialParticleFluxes.array() + ValueOffset));
  mInitialFluxes = CVectorCore< C_FLOAT64 >(src.mInitialFluxes.size(),
                   (C_FLOAT64 *)((size_t) src.mInitialFluxes.array() + ValueOffset));
  mInitialTotalMasses = CVectorCore< C_FLOAT64 >(src.mInitialTotalMasses.size(),
                        (C_FLOAT64 *)((size_t) src.mInitialTotalMasses.array() + ValueOffset));
  mInitialEventTriggers = CVectorCore< C_FLOAT64 >(src.mInitialEventTriggers.size(),
                          (C_FLOAT64 *)((size_t) src.mInitialEventTriggers.array() + ValueOffset));

  mExtensiveValues = CVectorCore< C_FLOAT64 >(src.mExtensiveValues.size(),
                     (C_FLOAT64 *)((size_t) src.mExtensiveValues.array() + ValueOffset));
  mIntensiveValues = CVectorCore< C_FLOAT64 >(src.mIntensiveValues.size(),
                     (C_FLOAT64 *)((size_t) src.mIntensiveValues.array() + ValueOffset));
  mExtensiveRates = CVectorCore< C_FLOAT64 >(src.mExtensiveRates.size(),
                    (C_FLOAT64 *)((size_t) src.mExtensiveRates.array() + ValueOffset));
  mIntensiveRates = CVectorCore< C_FLOAT64 >(src.mIntensiveRates.size(),
                    (C_FLOAT64 *)((size_t) src.mIntensiveRates.array() + ValueOffset));
  mParticleFluxes = CVectorCore< C_FLOAT64 >(src.mParticleFluxes.size(),
                    (C_FLOAT64 *)((size_t) src.mParticleFluxes.array() + ValueOffset));
  mFluxes = CVectorCore< C_FLOAT64 >(src.mFluxes.size(),
                                     (C_FLOAT64 *)((size_t) src.mFluxes.array() + ValueOffset));
  mTotalMasses = CVectorCore< C_FLOAT64 >(src.mTotalMasses.size(),
                                          (C_FLOAT64 *)((size_t) src.mTotalMasses.array() + ValueOffset));
  mEventTriggers = CVectorCore< C_FLOAT64 >(src.mEventTriggers.size(),
                   (C_FLOAT64 *)((size_t) src.mEventTriggers.array() + ValueOffset));

  mEventDelays = CVectorCore< C_FLOAT64 >(src.mEventDelays.size(),
                                          (C_FLOAT64 *)((size_t) src.mEventDelays.array() + ValueOffset));
  mEventPriorities = CVectorCore< C_FLOAT64 >(src.mEventPriorities.size(),
                     (C_FLOAT64 *)((size_t) src.mEventPriorities.array() + ValueOffset));
  mEventAssignments = CVectorCore< C_FLOAT64 >(src.mEventAssignments.size(),
                      (C_FLOAT64 *)((size_t) src.mEventAssignments.array() + ValueOffset));
  mEventRoots = CVectorCore< C_FLOAT64 >(src.mEventRoots.size(),
                                         (C_FLOAT64 *)((size_t) src.mEventRoots.array() + ValueOffset));
  mEventRootStates = CVectorCore< C_FLOAT64 >(src.mEventRootStates.size(),
                     (C_FLOAT64 *)((size_t) src.mEventRootStates.array() + ValueOffset));
  mPropensities = CVectorCore< C_FLOAT64 >(src.mPropensities.size(),
                  (C_FLOAT64 *)((size_t) src.mPropensities.array() + ValueOffset));
  mDependentMasses = CVectorCore< C_FLOAT64 >(src.mDependentMasses.size(),
                     (C_FLOAT64 *)((size_t) src.mDependentMasses.array() + ValueOffset));
  mDiscontinuous = CVectorCore< C_FLOAT64 >(src.mDiscontinuous.size(),
                   (C_FLOAT64 *)((size_t) src.mDiscontinuous.array() + ValueOffset));

  mInitialState = CVectorCore< C_FLOAT64 >(src.mInitialState.size(),
                  (C_FLOAT64 *)((size_t) src.mInitialState.array() + ValueOffset));
  mState = CVectorCore< C_FLOAT64 >(src.mState.size(),
                                    (C_FLOAT64 *)((size_t) src.mState.array() + ValueOffset));
  mStateReduced = CVectorCore< C_FLOAT64 >(src.mStateReduced.size(),
                  (C_FLOAT64 *)((size_t) src.mStateReduced.array() + ValueOffset));

  // Update the mappings
  std::map< CCopasiObject *, CMathObject * >::const_iterator itData = src.mDataObject2MathObject.begin();
  std::map< CCopasiObject *, CMathObject * >::const_iterator endData = src.mDataObject2MathObject.end();

  for (; itData != endData; ++itData)
    {
      mDataObject2MathObject[itData->first] = (CMathObject *)(((size_t) itData->second) + ObjectOffset);
    }

  std::map< C_FLOAT64 *, CMathObject * >::const_iterator itValue = src.mDataValue2MathObject.begin();
  std::map< C_FLOAT64 *, CMathObject * >::const_iterator endValue = src.mDataValue2MathObject.end();

  for (; itValue != endValue; ++itValue)
    {
      mDataValue2MathObject[itValue->first] = (CMathObject *)(((size_t) itValue->second) + ObjectOffset);
    }

  // Copy the objects
  CMathObject * pObject = mObjects.array();
  CMathObject * pObjectEnd = pObject + mObjects.size();
  const CMathObject * pObjectSrc = src.mObjects.array();

  for (; pObject != pObjectEnd; ++pObject, ++pObjectSrc)
    {
      pObject->copy(*pObjectSrc, *this, ValueOffset, ObjectOffset);
    }

  CMathEventN * pEvent = mEvents.array();
  CMathEventN * pEventEnd = pEvent + mEvents.size();
  const CMathEventN * pEventSrc = src.mEvents.array();

  for (; pEvent != pEventEnd; ++pEvent, ++pEventSrc)
    {
      pEvent->copy(*pEventSrc, *this, ValueOffset, ObjectOffset);
    }

  CMathReaction * pReaction = mReactions.array();
  CMathReaction * pReactionEnd = pReaction + mReactions.size();
  const CMathReaction * pReactionSrc = src.mReactions.array();

  for (; pReaction != pReactionEnd; ++pReaction, ++pReactionSrc)
    {
      pReaction->copy(*pReactionSrc, *this, ValueOffset, ObjectOffset);
    }

  createDependencyGraphs();
}

CMathContainer::~CMathContainer()
{}

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
  assert(mInitialState.size() == initialState.size());

  memcpy(mInitialState.array(), initialState.array(), mInitialState.size() * sizeof(C_FLOAT64));
}

const CVectorCore< C_FLOAT64 > & CMathContainer::getState() const
{
  return mState;
}

CVectorCore< C_FLOAT64 > & CMathContainer::getState()
{
  return mState;
}

void CMathContainer::setState(const CVectorCore< C_FLOAT64 > & state)
{
  assert(mState.size() == state.size());

  memcpy(mState.array(), state.array(), mState.size() * sizeof(C_FLOAT64));
}

const CVectorCore< C_FLOAT64 > & CMathContainer::getStateReduced() const
{
  return mStateReduced;
}

CVectorCore< C_FLOAT64 > & CMathContainer::getStateReduced()
{
  return mStateReduced;
}

void CMathContainer::setStateReduced(const CVectorCore< C_FLOAT64 > & stateReduced)
{
  assert(mStateReduced.size() == stateReduced.size());

  memcpy(mStateReduced.array(), stateReduced.array(), mStateReduced.size() * sizeof(C_FLOAT64));
}

void CMathContainer::updateInitialValues(const CModelParameter::Framework & framework)
{
  switch (framework)
    {
      case CModelParameter::Concentration:
        applyUpdateSequence(mSynchronizeInitialValuesSequenceIntensive);
        break;

      case CModelParameter::ParticleNumbers:
        applyUpdateSequence(mSynchronizeInitialValuesSequenceExtensive);
        break;
    }
}

void CMathContainer::applyInitialValues()
{
  C_FLOAT64 * pInitial = mInitialExtensiveValues.array();
  C_FLOAT64 * pTransient = mExtensiveValues.array();

  memcpy(pTransient, pInitial, (pTransient - pInitial) * sizeof(C_FLOAT64));

  applyUpdateSequence(mApplyInitialValuesSequence);
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

void CMathContainer::applyUpdateSequence(const CObjectInterface::UpdateSequence & updateSequence)
{
  UpdateSequence::const_iterator it = updateSequence.begin();
  UpdateSequence::const_iterator end = updateSequence.end();

  for (; it != end; ++it)
    {
      static_cast< CMathObject * >(*it)->calculate();
    }
}

// virtual
CCopasiObjectName CMathContainer::getCN() const
{
  return mpModel->getCN();
}

// virtual
const CObjectInterface * CMathContainer::getObject(const CCopasiObjectName & cn) const
{
  std::vector< CCopasiContainer * > ListOfContainer;
  ListOfContainer.push_back(mpModel);

  const CObjectInterface * pObject = NULL;
  CCopasiObjectName ModelCN = mpModel->getCN();

  if (cn.getPrimary() != ModelCN.getPrimary())
    {
      pObject = mpModel->getObjectDataModel()->ObjectFromCN(ListOfContainer, ModelCN + "," + cn);
    }
  else
    {
      pObject = mpModel->getObjectDataModel()->ObjectFromCN(ListOfContainer, cn);
    }

  const CMathObject * pMathObject = getMathObject(pObject);

  if (pMathObject != NULL)
    {
      return pMathObject;
    }

  std::cout << "Data Object " << cn << " (0x" << pObject << ") has no corresponding Math Object." << std::endl;

  return pObject;
}

CMathObject * CMathContainer::getMathObject(const CObjectInterface * pObject) const
{
  if (pObject == NULL)
    return NULL;

  std::map< CCopasiObject *, CMathObject * >::const_iterator found =
    mDataObject2MathObject.find(const_cast<CCopasiObject*>(static_cast< const CCopasiObject * >(pObject)));

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

CMathObject * CMathContainer::getMathObject(const CCopasiObjectName & cn) const
{
  return getMathObject(mpModel->getObject(cn));
}

void CMathContainer::init()
{
  allocate();

  CMath::sPointers Pointers;
  initializePointers(Pointers);
#ifdef COPASI_DEBUG
  printPointers(Pointers);
#endif

  initializeDiscontinuousCreationPointer();

  initializeObjects(Pointers);
  initializeEvents(Pointers);

  compileObjects();
  compileEvents();

  // These are only used during initialization for setting up the tracking of
  // discontinuities and are cleared afterwards.
  mDiscontinuityEvents.clear();
  mDiscontinuityInfix2Object.clear();
  mTriggerInfix2Event.clear();

  // TODO CRITICAL We may have unused event triggers and roots due to optimization
  // in the discontinuities.
  createDependencyGraphs();

  mReactions.resize(mpModel->getReactions().size());
  CMathReaction * pReaction = mReactions.array();
  CMathReaction * pReactionEnd = pReaction + mReactions.size();
  CCopasiVector< CReaction >::const_iterator itReaction = mpModel->getReactions().begin();

  for (; pReaction != pReactionEnd; ++itReaction, ++pReaction)
    {
      pReaction->initialize(*itReaction, *this);
    }

  updateInitialValues(CModelParameter::ParticleNumbers);

#ifdef COPASI_DEBUG
  CMathObject *pObject = mObjects.array();
  CMathObject *pObjectEnd = pObject + mObjects.size();

  for (; pObject != pObjectEnd; ++pObject)
    {
      std::cout << *pObject;
    }

  std::cout << std::endl;
#endif // COPASI_DEBUG
}

const CModel & CMathContainer::getModel() const
{
  return *mpModel;
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
      switch ((int) itNode->getType())
        {
            // Handle object nodes which are of type CN
          case (CEvaluationNode::OBJECT | CEvaluationNodeObject::CN):
          {
            // We need to map the object to a math object if possible.
            const CObjectInterface * pObject =
              getObject(static_cast< const CEvaluationNodeObject *>(*itNode)->getObjectCN());

            // Create a converted node
            pCopy = createNodeFromObject(pObject);
          }
          break;

          // Handle object nodes which are of type POINTER
          case (CEvaluationNode::OBJECT | CEvaluationNodeObject::POINTER):
          {
            const CObjectInterface * pObject =
              getMathObject(static_cast< const CEvaluationNodeObject *>(*itNode)->getObjectValuePtr());

            // Create a converted node
            pCopy = createNodeFromObject(pObject);
          }
          break;

          // Handle variables
          case (CEvaluationNode::VARIABLE | CEvaluationNodeVariable::ANY):
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
                pCopy = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, itNode->getData());
              }
          }
          break;

          // Handle call nodes
          case (CEvaluationNode::CALL | CEvaluationNodeCall::FUNCTION):
          case (CEvaluationNode::CALL | CEvaluationNodeCall::EXPRESSION):
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
          case (CEvaluationNode::CHOICE | CEvaluationNodeChoice::IF):
          case (CEvaluationNode::FUNCTION | CEvaluationNodeFunction::FLOOR):
          case (CEvaluationNode::FUNCTION | CEvaluationNodeFunction::CEIL):
          case (CEvaluationNode::OPERATOR | CEvaluationNodeOperator::MODULUS):

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

  // assert(pCopy != NULL);

  return pCopy;
}

CEvaluationNode *
CMathContainer::replaceDiscontinuousNode(const CEvaluationNode * pSrc,
    const std::vector< CEvaluationNode * > & children)
{
  bool success = true;

  CEvaluationNode * pNode = pSrc->copyNode(children);
  std::string DiscontinuityInfix = pNode->buildInfix();

  // Check whether we have the discontinuous node already created. This can happen if the
  // discontinuity was part of an expression for a variable in a function call.
  std::map< std::string, CMathObject * >::iterator itObject = mDiscontinuityInfix2Object.find(DiscontinuityInfix);

  if (itObject != mDiscontinuityInfix2Object.end())
    {
      // No need to copy we have already on object
      CMathObject * pDiscontinuity = itObject->second;

      // We need to advance both creation pointer to assure that we have the correct allocation
      mCreateDiscontinuousPointer.pDiscontinuous += 1;
      mCreateDiscontinuousPointer.pEvent += 1;

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

  CMathEventN * pEvent = NULL;

  // Check whether we have already an event with the current trigger
  std::string TriggerInfix = createDiscontinuityTriggerInfix(pNode);
  std::map< std::string, CMathEventN * >::iterator itEvent = mTriggerInfix2Event.find(TriggerInfix);

  // We need to create an event.
  if (itEvent == mTriggerInfix2Event.end())
    {
      pEvent = mCreateDiscontinuousPointer.pEvent;

      // Set the trigger
      pEvent->setTriggerExpression(TriggerInfix, *this);

      // Map the trigger infix to the event.
      mTriggerInfix2Event[TriggerInfix] = pEvent;
    }
  else
    {
      pEvent = itEvent->second;
    }

  mCreateDiscontinuousPointer.pEvent += 1;

  // Add the current discontinuity as an assignment.
  pEvent->addAssignment(pDiscontinuity, pDiscontinuity);

  // Return a pointer to a node pointing to the value of discontinuous object.
  return new CEvaluationNodeObject((C_FLOAT64 *) pDiscontinuity->getValuePointer());
}

void CMathContainer::allocate()
{
  size_t nLocalReactionParameters =
    CObjectLists::getListOfConstObjects(CObjectLists::ALL_LOCAL_PARAMETER_VALUES, mpModel).size();
  size_t nExtensiveValues =  mpModel->getStateTemplate().size() + nLocalReactionParameters;
  size_t nIntensiveValues = mpModel->getNumMetabs();

  size_t nReactions = mpModel->getReactions().size();
  size_t nMoieties = mpModel->getMoieties().size();

  size_t nDiscontinuities = 0;
  size_t nEvents = 0;
  size_t nEventAssignments = 0;
  size_t nEventRoots = 0;

  // Determine the space requirements for events.
  // We need to create events for nodes which are capable of introducing
  // discontinuous changes.
  createDiscontinuityEvents();
  nDiscontinuities += mDiscontinuityEvents.size();
  nEvents += nDiscontinuities;

  // User defined events
  const CCopasiVector< CEvent > & Events = mpModel->getEvents();
  CCopasiVector< CEvent >::const_iterator itEvent = Events.begin();
  CCopasiVector< CEvent >::const_iterator endEvent = Events.end();

  nEvents += Events.size();
  mEvents.resize(nEvents);

  CMathEventN * pEvent = mEvents.array();

  for (; itEvent != endEvent; ++itEvent, ++pEvent)
    {
      CMathEventN::allocate(pEvent, *itEvent, *this);

      nEventRoots += pEvent->getTrigger().getRoots().size();
      nEventAssignments += pEvent->getAssignments().size();
    }

  itEvent = mDiscontinuityEvents.begin();
  endEvent = mDiscontinuityEvents.end();

  for (; itEvent != endEvent; ++itEvent, ++pEvent)
    {
      CMathEventN::allocate(pEvent, *itEvent, *this);
      nEventRoots += pEvent->getTrigger().getRoots().size();

      // We do not have to allocate an assignment as discontinuity object suffices
      // as target and assignment expression.
    }

  mValues.resize(4 * (nExtensiveValues + nIntensiveValues) +
                 5 * nReactions +
                 3 * nMoieties +
                 nDiscontinuities +
                 4 * nEvents + nEventAssignments + 2 * nEventRoots);
  mValues = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

  C_FLOAT64 * pArray = mValues.array();

  mInitialExtensiveValues = CVectorCore< C_FLOAT64 >(nExtensiveValues, pArray);
  pArray += nExtensiveValues;
  mInitialIntensiveValues = CVectorCore< C_FLOAT64 >(nIntensiveValues, pArray);
  pArray += nIntensiveValues;
  mInitialExtensiveRates = CVectorCore< C_FLOAT64 >(nExtensiveValues, pArray);
  pArray += nExtensiveValues;
  mInitialIntensiveRates = CVectorCore< C_FLOAT64 >(nIntensiveValues, pArray);
  pArray += nIntensiveValues;
  mInitialParticleFluxes = CVectorCore< C_FLOAT64 >(nReactions, pArray);
  pArray += nReactions;
  mInitialFluxes = CVectorCore< C_FLOAT64 >(nReactions, pArray);
  pArray += nReactions;
  mInitialTotalMasses = CVectorCore< C_FLOAT64 >(nMoieties, pArray);
  pArray += nMoieties;
  mInitialEventTriggers = CVectorCore< C_FLOAT64 >(nEvents, pArray);
  pArray += nEvents;

  mExtensiveValues = CVectorCore< C_FLOAT64 >(nExtensiveValues, pArray);
  pArray += nExtensiveValues;
  mIntensiveValues = CVectorCore< C_FLOAT64 >(nIntensiveValues, pArray);
  pArray += nIntensiveValues;
  mExtensiveRates = CVectorCore< C_FLOAT64 >(nExtensiveValues, pArray);
  pArray += nExtensiveValues;
  mIntensiveRates = CVectorCore< C_FLOAT64 >(nIntensiveValues, pArray);
  pArray += nIntensiveValues;
  mParticleFluxes = CVectorCore< C_FLOAT64 >(nReactions, pArray);
  pArray += nReactions;
  mFluxes = CVectorCore< C_FLOAT64 >(nReactions, pArray);
  pArray += nReactions;
  mTotalMasses = CVectorCore< C_FLOAT64 >(nMoieties, pArray);
  pArray += nMoieties;
  mEventTriggers = CVectorCore< C_FLOAT64 >(nEvents, pArray);
  pArray += nEvents;

  mEventDelays = CVectorCore< C_FLOAT64 >(nEvents, pArray);
  pArray += nEvents;
  mEventPriorities = CVectorCore< C_FLOAT64 >(nEvents, pArray);
  pArray += nEvents;
  mEventAssignments = CVectorCore< C_FLOAT64 >(nEventAssignments, pArray);
  pArray += nEventAssignments;
  mEventRoots = CVectorCore< C_FLOAT64 >(nEventRoots, pArray);
  pArray += nEventRoots;
  mEventRootStates = CVectorCore< C_FLOAT64 >(nEventRoots, pArray);
  pArray += nEventRoots;
  mPropensities = CVectorCore< C_FLOAT64 >(nReactions, pArray);
  pArray += nReactions;
  mDependentMasses = CVectorCore< C_FLOAT64 >(nMoieties, pArray);
  pArray += nMoieties;
  mDiscontinuous = CVectorCore< C_FLOAT64 >(nDiscontinuities, pArray);
  pArray += nDiscontinuities;

  assert(pArray == mValues.array() + mValues.size());

  mObjects.resize(mValues.size());

  mInitialState = CVectorCore< C_FLOAT64 >(mInitialExtensiveRates.array() - mValues.array(),
                  mValues.array());
  mState = CVectorCore< C_FLOAT64 >(mODECount + mIndependentCount + mDependentCount,
                                    mExtensiveValues.array() + mFixedCount + mEventTargetCount);
  mStateReduced = CVectorCore< C_FLOAT64 >(mODECount + mIndependentCount,
                  mExtensiveValues.array() + mFixedCount + mEventTargetCount);
}

void CMathContainer::initializeObjects(CMath::sPointers & p)
{
  std::set< const CModelEntity * > EventTargets = CObjectLists::getEventTargets(mpModel);

  std::vector< const CModelEntity * > FixedEntities;
  std::vector< const CModelEntity * > FixedEventTargetEntities;

  const CStateTemplate & StateTemplate = mpModel->getStateTemplate();

  // Determine which fixed entities are modified by events and which not.
  CModelEntity *const* ppEntities = StateTemplate.beginFixed();
  CModelEntity *const* ppEntitiesEnd = StateTemplate.endFixed();

  for (; ppEntities != ppEntitiesEnd; ++ppEntities)
    {
      if ((*ppEntities)->getStatus() == CModelEntity::ASSIGNMENT)
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
  initializeMathObjects(FixedEntities, CMath::Fixed, p);
  mFixedCount = FixedEntities.size();

  // Process local reaction parameters
  std::vector<const CCopasiObject*> LocalReactionParameter =
    CObjectLists::getListOfConstObjects(CObjectLists::ALL_LOCAL_PARAMETER_VALUES, mpModel);
  initializeMathObjects(LocalReactionParameter, p);
  mFixedCount += LocalReactionParameter.size();

  // Process fixed entities which are event targets.
  initializeMathObjects(FixedEventTargetEntities, CMath::EventTarget, p);
  mEventTargetCount = FixedEventTargetEntities.size();

  // The simulation time
  // Extensive Initial Value
  map(mpModel->getInitialValueReference(), p.pInitialExtensiveValuesObject);
  CMathObject::initialize(p.pInitialExtensiveValuesObject, p.pInitialExtensiveValues,
                          CMath::Value, CMath::Model, CMath::Time, false, true,
                          mpModel->getInitialValueReference());

  // Extensive Value
  map(mpModel->getValueReference(), p.pExtensiveValuesObject);
  CMathObject::initialize(p.pExtensiveValuesObject, p.pExtensiveValues,
                          CMath::Value, CMath::Model, CMath::Time, false, false,
                          mpModel->getValueReference());

  // Initial Extensive Rate
  CMathObject::initialize(p.pInitialExtensiveRatesObject, p.pInitialExtensiveRates,
                          CMath::Rate, CMath::Model, CMath::Time, false, true,
                          mpModel->getRateReference());
  // Extensive Rate
  map(mpModel->getRateReference(), p.pExtensiveRatesObject);
  CMathObject::initialize(p.pExtensiveRatesObject, p.pExtensiveRates,
                          CMath::Rate, CMath::Model, CMath::Time, false, false,
                          mpModel->getRateReference());

  // Process entities which are determined by ODEs
  std::vector< const CModelEntity * > ODEEntities;

  ppEntities = StateTemplate.beginIndependent();
  ppEntitiesEnd = StateTemplate.endIndependent();

  for (; ppEntities != ppEntitiesEnd && (*ppEntities)->getStatus() == CModelEntity::ODE; ++ppEntities)
    {
      ODEEntities.push_back(*ppEntities);
    }

  initializeMathObjects(ODEEntities, CMath::ODE, p);
  mODECount = ODEEntities.size();

  // Process independent species
  std::vector< const CModelEntity * > IndependentSpecies;

  ppEntities = StateTemplate.beginIndependent();
  ppEntitiesEnd = StateTemplate.endIndependent();

  for (; ppEntities != ppEntitiesEnd; ++ppEntities)
    {
      if ((*ppEntities)->getStatus() != CModelEntity::REACTIONS)
        continue;

      IndependentSpecies.push_back(*ppEntities);
    }

  initializeMathObjects(IndependentSpecies, CMath::Independent, p);
  mIndependentCount = IndependentSpecies.size();

  // Process dependent species
  std::vector< const CModelEntity * > DependentSpecies;

  ppEntities = StateTemplate.beginDependent();
  ppEntitiesEnd = StateTemplate.endDependent();

  for (; ppEntities != ppEntitiesEnd && (*ppEntities)->getStatus() == CModelEntity::REACTIONS; ++ppEntities)
    {
      DependentSpecies.push_back(*ppEntities);
    }

  initializeMathObjects(DependentSpecies, CMath::Dependent, p);
  mDependentCount = DependentSpecies.size();

  // Process entities which are determined by assignments
  std::vector< const CModelEntity * > AssignmentEntities;

  // We continue with the pointer ppEntities
  ppEntitiesEnd = StateTemplate.endFixed();

  for (; ppEntities != ppEntitiesEnd && (*ppEntities)->getStatus() == CModelEntity::ASSIGNMENT; ++ppEntities)
    {
      AssignmentEntities.push_back(*ppEntities);
    }

  initializeMathObjects(AssignmentEntities, CMath::Assignment, p);
  mAssignmentCount = AssignmentEntities.size();

  // Process Reactions
  initializeMathObjects(mpModel->getReactions(), p);

  // Process Moieties
  initializeMathObjects(mpModel->getMoieties(), p);

  // Process Discontinuous Objects
  size_t n, nDiscontinuous = mDiscontinuous.size();

  for (n = 0; n != nDiscontinuous; ++n)
    {
      CMathObject::initialize(p.pDiscontinuousObject, p.pDiscontinuous,
                              CMath::Discontinuous, CMath::Event, CMath::SimulationTypeUndefined,
                              false, false, NULL);
    }
}

void CMathContainer::initializeEvents(CMath::sPointers & p)
{
  // Initialize events.
  CMathEventN * pEvent = mEvents.array();
  CMathEventN * pEventEnd = pEvent + mEvents.size();

  for (; pEvent != pEventEnd; ++pEvent)
    {
      pEvent->initialize(p);
    }

  return;
}

bool CMathContainer::compileObjects()
{
  bool success = true;

  CMathObject *pObject = mObjects.array();
  CMathObject *pObjectEnd = pObject + mObjects.size();

  for (; pObject != pObjectEnd; ++pObject)
    {
      success &= pObject->compile(*this);
    }

  return success;
}

bool CMathContainer::compileEvents()
{
  bool success = true;

  CMathEventN * pItEvent = mEvents.array();
  CCopasiVector< CEvent >::const_iterator itEvent = mpModel->getEvents().begin();
  CCopasiVector< CEvent >::const_iterator endEvent = mpModel->getEvents().end();

  for (; itEvent != endEvent; ++pItEvent, ++itEvent)
    {
      success &= pItEvent->compile(*itEvent, *this);
    }

  // Events representing discontinuities are already compiled.

  return success;
}

CEvaluationNode * CMathContainer::createNodeFromObject(const CObjectInterface * pObject)
{
  CEvaluationNode * pNode = NULL;

  if (pObject == NULL)
    {
      // We have an invalid value, i.e. NaN
      pNode = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "NAN");
    }
  else if (pObject == mpAvogadro ||
           pObject == mpQuantity2NumberFactor)
    {
      pNode = new CEvaluationNodeNumber(*(C_FLOAT64 *) pObject->getValuePointer());
    }
  else
    {
      pNode = new CEvaluationNodeObject((C_FLOAT64 *) pObject->getValuePointer());
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
      pNode = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "NAN");
    }

  return pNode;
}

void CMathContainer::createDependencyGraphs()
{
  CMathObject *pObject = mObjects.array();
  CMathObject *pObjectEnd = pObject + (mExtensiveValues.array() - mInitialExtensiveValues.array());

  for (; pObject != pObjectEnd; ++pObject)
    {
      mInitialDependencies.addObject(pObject);
    }

  pObjectEnd = mObjects.array() + mObjects.size();

  for (; pObject != pObjectEnd; ++pObject)
    {
      mTransientDependencies.addObject(pObject);
    }

#ifdef COPASI_DEBUG
  std::ofstream InitialDependencies("InitialDependencies.dot");
  mInitialDependencies.exportDOTFormat(InitialDependencies, "InitialDependencies");

  std::ofstream TransientDependencies("TransientDependencies.dot");
  mTransientDependencies.exportDOTFormat(TransientDependencies, "TransientDependencies");
#endif // COPASI_DEBUG

  createSynchronizeInitialValuesSequence();
  createApplyInitialValuesSequence();
  createUpdateSimulationValuesSequence();

  return;
}

void CMathContainer::createSynchronizeInitialValuesSequence()
{
  // TODO CRITICAL Issue 1170: We need to add elements of the stoichiometry, reduced stoichiometry,
  // and link matrices.

  // Collect all the changed objects, which are all transient values
  mInitialStateValueExtensive.clear();
  mInitialStateValueIntensive.clear();
  const CMathObject * pObject = mObjects.array();
  const CMathObject * pObjectEnd = pObject + (mInitialExtensiveRates.array() - mValues.array());

  for (; pObject != pObjectEnd; ++pObject)
    {
      if (pObject->getEntityType() != CMath::Species)
        {
          mInitialStateValueExtensive.insert(pObject);
          mInitialStateValueIntensive.insert(pObject);
        }
      else if (pObject->isIntensiveProperty())
        {
          mInitialStateValueIntensive.insert(pObject);
        }
      else
        {
          mInitialStateValueExtensive.insert(pObject);
        }
    }

  // Collect all the requested objects
  CObjectInterface::ObjectSet RequestedExtensive;
  CObjectInterface::ObjectSet RequestedIntensive;
  pObject = mObjects.array();

  for (; pObject != pObjectEnd; ++pObject)
    {
      if (pObject->getEntityType() != CMath::Species)
        {
          continue;
        }
      else if (pObject->isIntensiveProperty())
        {
          RequestedExtensive.insert(pObject);
        }
      else
        {
          RequestedIntensive.insert(pObject);
        }
    }

  pObjectEnd = mObjects.array() + (mExtensiveValues.array() - mValues.array());

  for (; pObject != pObjectEnd; ++pObject)
    {
      RequestedExtensive.insert(pObject);
      RequestedIntensive.insert(pObject);
    }

  // Build the update sequence
  mInitialDependencies.getUpdateSequence(CMath::UpdateMoieties,
                                         mInitialStateValueExtensive,
                                         RequestedExtensive,
                                         mSynchronizeInitialValuesSequenceExtensive);
  mInitialDependencies.getUpdateSequence(CMath::UpdateMoieties,
                                         mInitialStateValueIntensive,
                                         RequestedIntensive,
                                         mSynchronizeInitialValuesSequenceIntensive);
}

void CMathContainer::createApplyInitialValuesSequence()
{
  // Collect all the changed objects, which are all transient values
  CObjectInterface::ObjectSet Changed;
  const CMathObject * pObject = mObjects.array() + (mExtensiveValues.array() - mValues.array());
  const CMathObject * pObjectEnd = mObjects.array() + (mEventDelays.array() - mValues.array());

  for (; pObject != pObjectEnd; ++pObject)
    {
      Changed.insert(pObject);
    }

  // Collect all the requested objects
  CObjectInterface::ObjectSet Requested;
  pObjectEnd = mObjects.array() + mObjects.size();

  for (; pObject != pObjectEnd; ++pObject)
    {
      Requested.insert(pObject);
    }

  // Build the update sequence
  mTransientDependencies.getUpdateSequence(CMath::Default, Changed, Requested, mApplyInitialValuesSequence);
}

void CMathContainer::createUpdateSimulationValuesSequence()
{
  mStateValues.clear();
  mReducedStateValues.clear();
  mSimulationRequiredValues.clear();

  // Collect all the state objects, which are transient values of simulation type:
  //   Time, ODE, Independent, and Dependent (not for reduced model)

  const CMathObject * pObject = mObjects.array() + (mExtensiveValues.array() - mValues.array());
  const CMathObject * pObjectEnd = mObjects.array() + (mExtensiveRates.array() - mValues.array());

  for (; pObject != pObjectEnd; ++pObject)
    {
      switch (pObject->getSimulationType())
        {
          case CMath::Time:
          case CMath::ODE:
          case CMath::Independent:
            mStateValues.insert(pObject);
            mReducedStateValues.insert(pObject);
            break;

          case CMath::Dependent:
            mStateValues.insert(pObject);
            break;

          default:
            break;
        }
    }

  // Collect all objects required for simulation, which are transient rates values of simulation type:
  //   ODE, Independent, and Dependent (not needed for reduced model) and EventRoots
  // The additional cost for calculating the rates for dependent species is neglected.
  pObject = mObjects.array() + (mExtensiveRates.array() - mValues.array()) + mFixedCount + mEventTargetCount + 1 /* Time */;
  pObjectEnd = mObjects.array() + (mIntensiveRates.array() - mValues.array());

  for (; pObject != pObjectEnd; ++pObject)
    {
      mSimulationRequiredValues.insert(pObject);
    }

  pObject = mObjects.array() + (mEventRoots.array() - mValues.array());
  pObjectEnd = mObjects.array() + (mEventRootStates.array() - mValues.array());

  for (; pObject != pObjectEnd; ++pObject)
    {
      mSimulationRequiredValues.insert(pObject);
    }

  // Build the update sequence
  mTransientDependencies.getUpdateSequence(CMath::Default, mStateValues, mSimulationRequiredValues, mSimulationValuesSequence);
  mTransientDependencies.getUpdateSequence(CMath::UseMoieties, mReducedStateValues, mSimulationRequiredValues, mSimulationValuesSequenceReduced);
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

  p.pEventDelays = mEventDelays.array();
  p.pEventPriorities = mEventPriorities.array();
  p.pEventAssignments = mEventAssignments.array();
  p.pEventRoots = mEventRoots.array();
  p.pEventRootStates = mEventRootStates.array();
  p.pPropensities = mPropensities.array();
  p.pDependentMasses = mDependentMasses.array();
  p.pDiscontinuous = mDiscontinuous.array();

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

  p.pEventDelaysObject = pObjects + (p.pEventDelays - pValues);
  p.pEventPrioritiesObject = pObjects + (p.pEventPriorities - pValues);
  p.pEventAssignmentsObject = pObjects + (p.pEventAssignments - pValues);
  p.pEventRootsObject = pObjects + (p.pEventRoots - pValues);
  p.pEventRootStatesObject = pObjects + (p.pEventRootStates - pValues);
  p.pPropensitiesObject = pObjects + (p.pPropensities - pValues);
  p.pDependentMassesObject = pObjects + (p.pDependentMasses - pValues);
  p.pDiscontinuousObject = pObjects + (p.pDiscontinuous - pValues);
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
  std::cout << std::endl;
}
#endif // COAPSI_DEBUG

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
      return CMath::Species;
    }
  else if (dynamic_cast< const CCompartment * >(pEntity) != NULL)
    {
      return CMath::Compartment;
    }
  else if (dynamic_cast< const CModelValue * >(pEntity) != NULL)
    {
      return CMath::GlobalQuantity;
    }

  return CMath::EntityTypeUndefined;
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

      CMath::SimulationType SimulationType = CMath::Fixed;
      CCopasiObject * pObject = (*it)->getInitialValueReference();

      if (EntityType == CMath::Species)
        {
          SimulationType = CMath::Conversion;
        }
      else if ((simulationType == CMath::Assignment && (*it)->getExpression() != "") ||
               (*it)->getInitialExpression() != "")
        {
          SimulationType = CMath::Assignment;
        }

      map(pObject, p.pInitialExtensiveValuesObject);
      CMathObject::initialize(p.pInitialExtensiveValuesObject, p.pInitialExtensiveValues,
                              CMath::Value, EntityType, SimulationType, false, true,
                              pObject);

      // Extensive Value
      SimulationType = simulationType;

      if (EntityType == CMath::Species &&
          (simulationType == CMath::EventTarget ||
           simulationType == CMath::Assignment))
        {
          SimulationType = CMath::Conversion;
        }

      map((*it)->getValueReference(), p.pExtensiveValuesObject);
      CMathObject::initialize(p.pExtensiveValuesObject, p.pExtensiveValues,
                              CMath::Value, EntityType, SimulationType, false, false,
                              (*it)->getValueReference());

      // Initial Extensive Rate
      SimulationType = simulationType;

      if (simulationType == CMath::EventTarget)
        {
          SimulationType = CMath::Fixed;
        }

      CMathObject::initialize(p.pInitialExtensiveRatesObject, p.pInitialExtensiveRates,
                              CMath::Rate, EntityType, SimulationType, false, true,
                              (*it)->getRateReference());

      // Extensive Rate
      map((*it)->getRateReference(), p.pExtensiveRatesObject);
      CMathObject::initialize(p.pExtensiveRatesObject, p.pExtensiveRates,
                              CMath::Rate, EntityType, SimulationType, false, false,
                              (*it)->getRateReference());

      // Species have intensive values in addition to the extensive  ones.
      if (EntityType == CMath::Species)
        {
          const CMetab *pSpecies = static_cast<const CMetab*>(*it);

          // Intensive Initial Value

          // The simulation type for initial values is either CMath::Assignment or CMath::Conversion
          // In case of species it always possible that is must be calculated.
          SimulationType = CMath::Conversion;

          if (simulationType == CMath::Assignment)
            {
              SimulationType = CMath::Assignment;
            }

          map(pSpecies->getInitialConcentrationReference(), p.pInitialIntensiveValuesObject);
          CMathObject::initialize(p.pInitialIntensiveValuesObject, p.pInitialIntensiveValues,
                                  CMath::Value, CMath::Species, SimulationType, true, true,
                                  pSpecies->getInitialConcentrationReference());

          // Intensive Value
          SimulationType = CMath::Conversion;

          if (simulationType == CMath::EventTarget ||
              simulationType == CMath::Assignment)
            {
              SimulationType = simulationType;
            }

          map(pSpecies->getConcentrationReference(), p.pIntensiveValuesObject);
          CMathObject::initialize(p.pIntensiveValuesObject, p.pIntensiveValues,
                                  CMath::Value, CMath::Species, SimulationType, true, false,
                                  pSpecies->getConcentrationReference());

          // Initial Intensive Rate
          CMathObject::initialize(p.pInitialIntensiveRatesObject, p.pInitialIntensiveRates,
                                  CMath::Rate, CMath::Species, CMath::Assignment, true, true,
                                  pSpecies->getConcentrationRateReference());

          // Intensive Rate
          map(pSpecies->getConcentrationRateReference(), p.pIntensiveRatesObject);
          CMathObject::initialize(p.pIntensiveRatesObject, p.pIntensiveRates,
                                  CMath::Rate, CMath::Species, CMath::Assignment, true, false,
                                  pSpecies->getConcentrationRateReference());
        }
    }
}

void CMathContainer::initializeMathObjects(const std::vector<const CCopasiObject *> & parameters,
    CMath::sPointers & p)
{
  // Process parameters.
  std::vector<const CCopasiObject *>::const_iterator it = parameters.begin();
  std::vector<const CCopasiObject *>::const_iterator end = parameters.end();

  for (; it != end; ++it)
    {
      // Extensive Initial Value
      map(const_cast< CCopasiObject * >(*it), p.pInitialExtensiveValuesObject);
      CMathObject::initialize(p.pInitialExtensiveValuesObject, p.pInitialExtensiveValues,
                              CMath::Value, CMath::LocalReactionParameter, CMath::Fixed, false, true,
                              *it);

      // Extensive Value
      CMathObject::initialize(p.pExtensiveValuesObject, p.pExtensiveValues,
                              CMath::Value, CMath::LocalReactionParameter, CMath::Fixed, false, false,
                              NULL);

      // Initial Extensive Rate
      CMathObject::initialize(p.pInitialExtensiveRatesObject, p.pInitialExtensiveRates,
                              CMath::Rate, CMath::LocalReactionParameter, CMath::Fixed, false, true,
                              NULL);

      // Extensive Rate
      CMathObject::initialize(p.pExtensiveRatesObject, p.pExtensiveRates,
                              CMath::Rate, CMath::LocalReactionParameter, CMath::Fixed, false, false,
                              NULL);
    }
}

void CMathContainer::initializeMathObjects(const CCopasiVector< CReaction > & reactions,
    CMath::sPointers & p)
{
  // Process reactions.
  CCopasiVector< CReaction >::const_iterator it = reactions.begin();
  CCopasiVector< CReaction >::const_iterator end = reactions.end();

  for (; it != end; ++it)
    {
      // Initial Particle Flux
      CMathObject::initialize(p.pInitialParticleFluxesObject, p.pInitialParticleFluxes,
                              CMath::ParticleFlux, CMath::Reaction, CMath::SimulationTypeUndefined, false, true,
                              (*it)->getParticleFluxReference());

      // Particle Flux
      map((*it)->getParticleFluxReference(), p.pParticleFluxesObject);
      CMathObject::initialize(p.pParticleFluxesObject, p.pParticleFluxes,
                              CMath::ParticleFlux, CMath::Reaction, CMath::SimulationTypeUndefined, false, false,
                              (*it)->getParticleFluxReference());

      // Initial Flux
      CMathObject::initialize(p.pInitialFluxesObject, p.pInitialFluxes,
                              CMath::Flux, CMath::Reaction, CMath::SimulationTypeUndefined, false, true,
                              (*it)->getFluxReference());

      // Flux
      map((*it)->getFluxReference(), p.pFluxesObject);
      CMathObject::initialize(p.pFluxesObject, p.pFluxes,
                              CMath::Flux, CMath::Reaction, CMath::SimulationTypeUndefined, false, false,
                              (*it)->getFluxReference());

      // Propensity
      map((*it)->getPropensityReference(), p.pPropensitiesObject);
      CMathObject::initialize(p.pPropensitiesObject, p.pPropensities,
                              CMath::Propensity, CMath::Reaction, CMath::SimulationTypeUndefined, false, false,
                              (*it)->getPropensityReference());
    }
}

void CMathContainer::initializeMathObjects(const CCopasiVector< CMoiety > & moieties,
    CMath::sPointers & p)
{
  // Process reactions.
  CCopasiVector< CMoiety >::const_iterator it = moieties.begin();
  CCopasiVector< CMoiety >::const_iterator end = moieties.end();

  for (; it != end; ++it)
    {
      // Initial Total Mass
      CMathObject::initialize(p.pInitialTotalMassesObject, p.pInitialTotalMasses,
                              CMath::TotalMass, CMath::Moiety, CMath::SimulationTypeUndefined, false, true,
                              (*it)->getTotalNumberReference());

      // Total Mass
      map((*it)->getTotalNumberReference(), p.pTotalMassesObject);
      CMathObject::initialize(p.pTotalMassesObject, p.pTotalMasses,
                              CMath::TotalMass, CMath::Moiety, CMath::SimulationTypeUndefined, false, false,
                              (*it)->getTotalNumberReference());

      // Dependent
      map((*it)->getDependentNumberReference(), p.pDependentMassesObject);
      CMathObject::initialize(p.pDependentMassesObject, p.pDependentMasses,
                              CMath::DependentMass, CMath::Moiety, CMath::SimulationTypeUndefined, false, false,
                              (*it)->getDependentNumberReference());
    }
}

// static
bool CMathContainer::hasDependencies(const CCopasiObject * pObject)
{
  const CCopasiObject::DataObjectSet & Dependencies = pObject->getDirectDependencies();

  if (Dependencies.find(pObject->getObjectParent()) != Dependencies.end())
    {
      return Dependencies.size() > 1;
    }

  return Dependencies.size() > 0;
}

void CMathContainer::map(CCopasiObject * pDataObject, CMathObject * pMathObject)
{
  if (pDataObject != NULL)
    {
      mDataObject2MathObject[pDataObject] = pMathObject;
      mDataValue2MathObject[(C_FLOAT64 *) pDataObject->getValuePointer()] = pMathObject;
    }
}

C_FLOAT64 * CMathContainer::getInitialValuePointer(const C_FLOAT64 * pValue) const
{
  assert(mValues.array() <= pValue && pValue < mValues.array() + mValues.size());

  const C_FLOAT64 * pInitialValue = pValue;

  if (mExtensiveValues.array() <= pValue && pValue < mEventDelays.array())
    {
      pInitialValue = mInitialExtensiveValues.array() + (pValue - mExtensiveValues.array());
    }

  return const_cast< C_FLOAT64 * >(pInitialValue);
}

void CMathContainer::createDiscontinuityEvents()
{
  CEvaluationNodeConstant VariableNode(CEvaluationNodeConstant::_NaN, "NAN");
  size_t i, imax;

  // We need to create events for nodes which are capable of introducing
  // discontinuous changes.

  // Retrieve expression trees which contain discontinuities.
  std::vector< const CEvaluationTree * > TreesWithDiscontinuities =  mpModel->getTreesWithDiscontinuities();
  std::vector< const CEvaluationTree * >::const_iterator it = TreesWithDiscontinuities.begin();
  std::vector< const CEvaluationTree * >::const_iterator end = TreesWithDiscontinuities.end();

  for (; it != end; ++it)
    {
      createDiscontinuityEvents(*it);
    }
}

void CMathContainer::createDiscontinuityEvents(const CEvaluationTree * pTree)
{
  CEvaluationNodeConstant VariableNode(CEvaluationNodeConstant::_NaN, "NAN");
  CNodeIterator< const CEvaluationNode > itNode(pTree->getRoot());

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      switch ((int) itNode->getType())
        {
          case (CEvaluationNode::CHOICE | CEvaluationNodeChoice::IF):
          case (CEvaluationNode::FUNCTION | CEvaluationNodeFunction::FLOOR):
          case (CEvaluationNode::FUNCTION | CEvaluationNodeFunction::CEIL):
          case (CEvaluationNode::OPERATOR | CEvaluationNodeOperator::MODULUS):
            createDiscontinuityDataEvent(*itNode);
            break;

            // Call nodes may include discontinuities but each called tree is handled
            // separately.
          case (CEvaluationNode::CALL | CEvaluationNodeCall::FUNCTION):
          case (CEvaluationNode::CALL | CEvaluationNodeCall::EXPRESSION):
            createDiscontinuityEvents(static_cast< const CEvaluationNodeCall * >(*itNode)->getCalledTree());
            break;

          default:
            break;
        }
    }

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
  switch ((int) pNode->getType())
    {
      case (CEvaluationNode::CHOICE | CEvaluationNodeChoice::IF):
        TriggerInfix = static_cast< const CEvaluationNode * >(pNode->getChild())->buildInfix();
        break;

      case (CEvaluationNode::FUNCTION | CEvaluationNodeFunction::FLOOR):
      case (CEvaluationNode::FUNCTION | CEvaluationNodeFunction::CEIL):
        TriggerInfix = "sin(PI*(" + static_cast< const CEvaluationNode * >(pNode->getChild())->buildInfix() + ")) > 0";
        break;

      case (CEvaluationNode::OPERATOR | CEvaluationNodeOperator::MODULUS):
        TriggerInfix = "sin(PI*(" + static_cast< const CEvaluationNode * >(pNode->getChild())->buildInfix();
        TriggerInfix += ")) > 0 || sin(PI*(" + static_cast< const CEvaluationNode * >(pNode->getChild()->getSibling())->buildInfix() + ")) > 0";
        break;

      default:
        fatalError();
        break;
    }

  return TriggerInfix;
}
