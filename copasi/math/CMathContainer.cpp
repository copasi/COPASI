// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathContainer.cpp,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/21 14:12:02 $
// End CVS Header

// Copyright (C) 2012 - 2011 by Pedro Mendes, Virginia Tech Intellectual
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
    mValues(),
    mInitialExtensiveValues(),
    mInitialIntensiveValues(),
    mInitialExtensiveRates(),
    mInitialIntensiveRates(),
    mInitialParticleFluxes(),
    mInitialFluxes(),
    mInitialEventTriggers(),
    mExtensiveValues(),
    mIntensiveValues(),
    mExtensiveRates(),
    mIntensiveRates(),
    mParticleFluxes(),
    mFluxes(),
    mEventTriggers(),
    mEventDelays(),
    mEventPriorities(),
    mEventAssignments(),
    mEventRoots(),
    mEventRootStates(),
    mPropensities(),
    mTotalMasses(),
    mDependentMasses(),
    mDiscontinuous(),
    mInitialDependencies(),
    mTransientDependencies(),
    mObjects(),
    mEvents(),
    mCreateDiscontinuousPointer(),
    mDataObject2MathObject(),
    mDataValue2MathObject()
{}

CMathContainer::CMathContainer(CModel & model):
    CCopasiContainer("Math Container", NULL, "CMathContainer"),
    mpModel(&model),
    mValues(),
    mInitialExtensiveValues(),
    mInitialIntensiveValues(),
    mInitialExtensiveRates(),
    mInitialIntensiveRates(),
    mInitialParticleFluxes(),
    mInitialFluxes(),
    mInitialEventTriggers(),
    mExtensiveValues(),
    mIntensiveValues(),
    mExtensiveRates(),
    mIntensiveRates(),
    mParticleFluxes(),
    mFluxes(),
    mEventTriggers(),
    mEventDelays(),
    mEventPriorities(),
    mEventAssignments(),
    mEventRoots(),
    mEventRootStates(),
    mPropensities(),
    mTotalMasses(),
    mDependentMasses(),
    mDiscontinuous(),
    mInitialDependencies(),
    mTransientDependencies(),
    mObjects(),
    mEvents(),
    mDataObject2MathObject(),
    mDataValue2MathObject()
{
  // We do not want the model to know about the math container therefore we
  // do not use &model in the constructor of CCopasiContainer
  setObjectParent(mpModel);
  init();
}

CMathContainer::~CMathContainer()
{}

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
  initializeDiscontinuousCreationPointer();

  initializeObjects(Pointers);
  initializeEvents(Pointers);

  compileObjects();
  compileEvents();

  createDependencyGraphs();
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
          case(CEvaluationNode::OBJECT | CEvaluationNodeObject::CN):
          {
            // We need to map the object to a math object if possible.
            const CObjectInterface * pObject =
              getObject(static_cast< const CEvaluationNodeObject *>(*itNode)->getObjectCN());

            // Create a converted node
            pCopy = createNodeFromObject(pObject);
          }
          break;

          // Handle object nodes which are of type POINTER
          case(CEvaluationNode::OBJECT | CEvaluationNodeObject::POINTER):
          {
            const CObjectInterface * pObject =
              getMathObject(static_cast< const CEvaluationNodeObject *>(*itNode)->getObjectValuePtr());

            // Create a converted node
            pCopy = createNodeFromObject(pObject);
          }
          break;

          // Handle variables
          case(CEvaluationNode::VARIABLE | CEvaluationNodeVariable::ANY):
          {
            size_t Index =
              static_cast< const CEvaluationNodeVariable * >(*itNode)->getIndex();

            pCopy = variables[Index][0]->copyBranch();
          }
          break;

          // Handle call nodes
          case(CEvaluationNode::CALL | CEvaluationNodeCall::FUNCTION):
          case(CEvaluationNode::CALL | CEvaluationNodeCall::EXPRESSION):
          {
            CMath::Variables< CEvaluationNode * > Variables;
            std::vector< CEvaluationNode * >::iterator it = itNode.context().begin();
            std::vector< CEvaluationNode * >::iterator end = itNode.context().end();

            for (; it != end; ++it)
              {
                CMath::Variables< CEvaluationNode * >::value_type Variable;
                Variable.push_back(*it);
                Variables.push_back(Variable);
              }

            const CEvaluationNode * pCalledNode =
              static_cast< const CEvaluationNodeCall * >(*itNode)->getCalledTree()->getRoot();

            pCopy = copyBranch(pCalledNode, Variables, replaceDiscontinuousNodes);

            // The variables have been copied into place we need to delete them.
            for (; it != end; ++it)
              {
                delete *it;
              }
          }
          break;

          // Handle discrete nodes
          case(CEvaluationNode::CHOICE | CEvaluationNodeChoice::IF):
          case(CEvaluationNode::FUNCTION | CEvaluationNodeFunction::FLOOR):
          case(CEvaluationNode::FUNCTION | CEvaluationNodeFunction::CEIL):

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

  assert(pCopy != NULL);

  return pCopy;
}

CEvaluationNode *
CMathContainer::replaceDiscontinuousNode(const CEvaluationNode * pSrc,
    const std::vector< CEvaluationNode * > & children)
{
  bool success = true;

  // Create a node pointing to the discontinuous object.
  CEvaluationNode * pCopy =
    new CEvaluationNodeObject((C_FLOAT64 *) mCreateDiscontinuousPointer.pDiscontinuous->getValuePointer());

  // Compile the discontinuous object
  CMathExpression * pExpression = new CMathExpression("DiscontinuousExpression", *this);

  success &= pExpression->setRoot(pSrc->copyNode(children));
  success &= mCreateDiscontinuousPointer.pDiscontinuous->setExpressionPtr(pExpression);

  mCreateDiscontinuousPointer.pDiscontinuous += 1;

#ifdef XXXX // TODO CRITICAL We postpone the creation of events for discontinuous nodes till later.
  success &= mCreateDiscontinuousPointer.pEvent->compileDiscontinuous(mCreateDiscontinuousPointer.pDiscontinuous, *this);


  // Since the children are copied first it is better to defer advancing the pointers
  mCreateDiscontinuousPointer.pEvent += 1;
  mCreateDiscontinuousPointer.pEventDelay += 1;
  mCreateDiscontinuousPointer.pEventPriority += 1;
  mCreateDiscontinuousPointer.pEventAssignment += 1;
  mCreateDiscontinuousPointer.pEventTrigger += 1;

  // TODO CRITICAL This is not correct we need the corresponding information
  // from CMath::CAllocationStack::CAllocation
  mCreateDiscontinuousPointer.pEventRoot += 2;
#endif // XXXX

  assert(success);

  return pCopy;
}

void CMathContainer::determineDiscontinuityAllocationRequirement(CMath::CAllocationStack::CAllocation & allocations) const
{
  allocations.nDiscontinuous = 0;
  allocations.nTotalRoots = 0;
  allocations.nRootsPerDiscontinuity.clear();

  // We need to create events for nodes which are capable of introducing
  // discontinuous changes.
  std::vector< const CEvaluationTree * > TreesWithDiscontinuities =  mpModel->getTreesWithDiscontinuities();
  std::vector< const CEvaluationTree * >::const_iterator it = TreesWithDiscontinuities.begin();
  std::vector< const CEvaluationTree * >::const_iterator end = TreesWithDiscontinuities.end();

  for (; it != end; ++it)
    {
      CMath::CVariableStack::StackElement Variables;
      CMath::CVariableStack::Buffer VariableBuffer;
      CMath::CVariableStack VariableStack(VariableBuffer);

      CMath::CAllocationStack::StackElement Allocations;
      CMath::CAllocationStack::Buffer AllocationBuffer;
      CMath::CAllocationStack AllocationStack(AllocationBuffer);

      CEvaluationNodeConstant Variable(CEvaluationNodeConstant::_NaN, "NAN");
      const CFunction * pFunction = dynamic_cast< const CFunction * >(*it);

      if (pFunction != NULL)
        {
          Variables.resize(pFunction->getVariables().size());
          CMath::CVariableStack::StackElement::iterator itVar = Variables.begin();
          CMath::CVariableStack::StackElement::iterator endVar = Variables.end();

          for (; itVar != endVar; ++itVar)
            {
              *itVar = &Variable;
            }

          VariableStack.push(Variables);

          Allocations.resize(pFunction->getVariables().size());
          AllocationStack.push(Allocations);
        }

      determineDiscontinuityAllocationRequirement((*it)->getRoot(),
          VariableStack,
          AllocationStack,
          allocations);

      std::cout << (*it)->getInfix() << " " << allocations << std::endl << std::endl;

      if (pFunction != NULL)
        {
          VariableStack.pop();
          AllocationStack.pop();
        }
    }

  return;
}

void CMathContainer::determineDiscontinuityAllocationRequirement(const CEvaluationNode * pNode,
    CMath::CVariableStack & variableStack,
    CMath::CAllocationStack & allocationStack,
    CMath::CAllocationStack::CAllocation & allocations) const
{
  // TODO CRITICAL We need to analyze the trees with discontinuities to determine how many
  // events need to be created and how many roots each event trigger has.

  // We need to replace variables, expand called trees, and handle discrete nodes.
  switch ((int) pNode->getType())
    {
        // Handle variables
      case(CEvaluationNode::VARIABLE | CEvaluationNodeVariable::ANY):

        // We do not need to do anything
        if (false)
          {
            // We only need to add the allocation requirements from the stack to the
            size_t Index =
              static_cast< const CEvaluationNodeVariable * >(pNode)->getIndex();

            allocations += allocationStack[Index];
          }

        break;

        // Handle call nodes
      case(CEvaluationNode::CALL | CEvaluationNodeCall::FUNCTION):
      case(CEvaluationNode::CALL | CEvaluationNodeCall::EXPRESSION):
      {
        CMath::CVariableStack::StackElement Variables;
        CMath::CAllocationStack::StackElement Allocations;

        const CEvaluationNode * pChild =
          static_cast< const CEvaluationNode * >(pNode->getChild());

        // We determine the allocations requirements for each variable.
        while (pChild != NULL)
          {
            CMath::CAllocationStack::CAllocation Allocation;

            determineDiscontinuityAllocationRequirement(pChild,
                variableStack,
                allocationStack,
                allocations);

            Allocations.push_back(Allocation);
            Variables.push_back(pChild);

            pChild = static_cast< const CEvaluationNode * >(pChild->getSibling());
          }

        variableStack.push(Variables);
        allocationStack.push(Allocations);

        const CEvaluationNode * pCalledNode =
          static_cast< const CEvaluationNodeCall * >(pNode)->getCalledTree()->getRoot();

        determineDiscontinuityAllocationRequirement(pCalledNode,
            variableStack,
            allocationStack,
            allocations);

        variableStack.pop();
        allocationStack.pop();
      }
      break;

      // Handle discrete nodes
      case(CEvaluationNode::CHOICE | CEvaluationNodeChoice::IF):
      {
        const CEvaluationNode * pIf = static_cast< const CEvaluationNode * >(pNode->getChild());
        const CEvaluationNode * pTrue = static_cast< const CEvaluationNode * >(pIf->getSibling());
        const CEvaluationNode * pFalse = static_cast< const CEvaluationNode * >(pTrue->getSibling());

        // We need to analyze the true and false expression.
        determineDiscontinuityAllocationRequirement(pTrue,
            variableStack,
            allocationStack,
            allocations);

        determineDiscontinuityAllocationRequirement(pFalse,
            variableStack,
            allocationStack,
            allocations);


      }

      // TODO CRITICAL We need to analyze the condition to determine how many roots
      // are actually created.
      allocations.nDiscontinuous++;
      allocations.nTotalRoots += 2;
      allocations.nRootsPerDiscontinuity.push_back(2);

      break;

      case(CEvaluationNode::FUNCTION | CEvaluationNodeFunction::FLOOR):
      case(CEvaluationNode::FUNCTION | CEvaluationNodeFunction::CEIL):
        determineDiscontinuityAllocationRequirement(static_cast< const CEvaluationNode * >(pNode->getChild()),
            variableStack,
            allocationStack,
            allocations);

        allocations.nDiscontinuous++;
        allocations.nTotalRoots += 2;
        allocations.nRootsPerDiscontinuity.push_back(2);

        break;

      default:
        // Handle all other nodes.
        const CEvaluationNode * pChild =
          static_cast< const CEvaluationNode * >(pNode->getChild());

        while (pChild != NULL)
          {
            determineDiscontinuityAllocationRequirement(pChild,
                variableStack,
                allocationStack,
                allocations);

            pChild = static_cast< const CEvaluationNode * >(pChild->getSibling());
          }

        break;
    }

  // std::cout << pNode->getInfix() << ": " << allocations << std::endl;
}

void CMathContainer::allocate()
{
  size_t nLocalReactionParameters =
    CObjectLists::getListOfConstObjects(CObjectLists::ALL_LOCAL_PARAMETER_VALUES, mpModel).size();
  size_t nExtensiveValues =  mpModel->getStateTemplate().size() + nLocalReactionParameters;
  size_t nIntensiveValues = mpModel->getNumMetabs();

  size_t nReactions = mpModel->getReactions().size();
  size_t nMoieties = mpModel->getMoieties().size();

  size_t nEvents = 0;
  size_t nEventAssignments = 0;
  size_t nEventRoots = 0;

  // Determine the space requirements for events.
  const CCopasiVector< CEvent > & Events = mpModel->getEvents();
  CCopasiVector< CEvent >::const_iterator itEvent = Events.begin();
  CCopasiVector< CEvent >::const_iterator endEvent = Events.end();

  nEvents += Events.size();
  mEvents.resize(nEvents);
  CMathEventN * pEvent = mEvents.array();

  for (; itEvent != endEvent; ++itEvent, ++pEvent)
    {
      CMathEventN::allocate(pEvent, *itEvent, *this);

      nEventAssignments += pEvent->getAssignments().size();
      nEventRoots += pEvent->getTrigger().getRoots().size();
    }

  // We need to create events for nodes which are capable of introducing
  // discontinuous changes.

  CMath::CAllocationStack::CAllocation AllocationRequirement;

  determineDiscontinuityAllocationRequirement(AllocationRequirement);

# ifdef XXXX // TODO CRITICAL We postpone the creation of events for discontinuous nodes till later
  std::vector< size_t >::const_iterator itDiscontinuous = AllocationRequirement.nRootsPerDiscontinuity.begin();
  std::vector< size_t >::const_iterator endDiscontinuous = AllocationRequirement.nRootsPerDiscontinuity.end();

  for (; itDiscontinuous != endDiscontinuous; ++itDiscontinuous, ++pEvent)
    {
      CMathEventN::allocateDiscontinuous(pEvent, *itDiscontinuous, *this);

      nEventAssignments += pEvent->getAssignments().size();
      nEventRoots += pEvent->getTrigger().getRoots().size();
    }

# endif // XXXX

  mValues.resize(4 *(nExtensiveValues + nIntensiveValues) +
                 5 * nReactions +
                 2 * nMoieties +
                 AllocationRequirement.nDiscontinuous +
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
  mTotalMasses = CVectorCore< C_FLOAT64 >(nMoieties, pArray);
  pArray += nMoieties;
  mDependentMasses = CVectorCore< C_FLOAT64 >(nMoieties, pArray);
  pArray += nMoieties;
  mDiscontinuous = CVectorCore< C_FLOAT64 >(AllocationRequirement.nDiscontinuous, pArray);
  pArray += AllocationRequirement.nDiscontinuous;

  assert(pArray == mValues.array() + mValues.size());

  mObjects.resize(mValues.size());
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

  // Process local reaction parameters
  std::vector<const CCopasiObject*> LocalReactionParameter =
    CObjectLists::getListOfConstObjects(CObjectLists::ALL_LOCAL_PARAMETER_VALUES, mpModel);
  initializeMathObjects(LocalReactionParameter, p);

  // Process fixed entities which are event targets.
  initializeMathObjects(FixedEventTargetEntities, CMath::EventTarget, p);

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

  // Process dependent species
  std::vector< const CModelEntity * > DependentSpecies;

  ppEntities = StateTemplate.beginDependent();
  ppEntitiesEnd = StateTemplate.endDependent();

  for (; ppEntities != ppEntitiesEnd && (*ppEntities)->getStatus() == CModelEntity::REACTIONS; ++ppEntities)
    {
      DependentSpecies.push_back(*ppEntities);
    }

  initializeMathObjects(DependentSpecies, CMath::Dependent, p);

  // Process entities which are determined by assignments
  std::vector< const CModelEntity * > AssignmentEntities;

  // We continue with the pointer ppEntities
  ppEntitiesEnd = StateTemplate.endFixed();

  for (; ppEntities != ppEntitiesEnd && (*ppEntities)->getStatus() == CModelEntity::ASSIGNMENT; ++ppEntities)
    {
      AssignmentEntities.push_back(*ppEntities);
    }

  initializeMathObjects(AssignmentEntities, CMath::Assignment, p);

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

  CMathEventN * pEvent = mEvents.array();
  CCopasiVector< CEvent >::const_iterator itEvent = mpModel->getEvents().begin();
  CCopasiVector< CEvent >::const_iterator endEvent = mpModel->getEvents().end();

  for (; itEvent != endEvent; ++pEvent, ++itEvent)
    {
      success &= pEvent->compile(*itEvent, *this);
    }

  return success;
}

CEvaluationNode * CMathContainer::createNodeFromObject(const CObjectInterface * pObject)
{
  CEvaluationNode * pNode = NULL;

  if (pObject != NULL)
    {
      pNode = new CEvaluationNodeObject((C_FLOAT64 *) pObject->getValuePointer());
    }
  else
    {
      // We have an invalid value, i.e. NaN
      pNode = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "NAN");
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

  return;
}

void CMathContainer::initializePointers(CMath::sPointers & p)
{
  p.pInitialExtensiveValues = mInitialExtensiveValues.array();
  p.pInitialIntensiveValues = mInitialIntensiveValues.array();
  p.pInitialExtensiveRates = mInitialExtensiveRates.array();
  p.pInitialIntensiveRates = mInitialIntensiveRates.array();
  p.pInitialParticleFluxes = mInitialParticleFluxes.array();
  p.pInitialFluxes = mInitialFluxes.array();
  p.pInitialEventTriggers = mInitialEventTriggers.array();

  p.pExtensiveValues = mInitialEventTriggers.array();
  p.pIntensiveValues = mIntensiveValues.array();
  p.pExtensiveRates = mExtensiveRates.array();
  p.pIntensiveRates = mIntensiveRates.array();
  p.pParticleFluxes = mParticleFluxes.array();
  p.pFluxes = mFluxes.array();
  p.pEventTriggers = mEventTriggers.array();

  p.pEventDelays = mEventDelays.array();
  p.pEventPriorities = mEventPriorities.array();
  p.pEventAssignments = mEventAssignments.array();
  p.pEventRoots = mEventRoots.array();
  p.pEventRootStates = mEventRootStates.array();
  p.pPropensities = mPropensities.array();
  p.pTotalMasses = mTotalMasses.array();
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
  p.pInitialEventTriggersObject = pObjects + (p.pInitialEventTriggers - pValues);

  p.pExtensiveValuesObject = pObjects + (p.pExtensiveValues - pValues);
  p.pIntensiveValuesObject = pObjects + (p.pIntensiveValues - pValues);
  p.pExtensiveRatesObject = pObjects + (p.pExtensiveRates - pValues);
  p.pIntensiveRatesObject = pObjects + (p.pIntensiveRates - pValues);
  p.pParticleFluxesObject = pObjects + (p.pParticleFluxes - pValues);
  p.pFluxesObject = pObjects + (p.pFluxes - pValues);
  p.pEventTriggersObject = pObjects + (p.pEventTriggers - pValues);

  p.pEventDelaysObject = pObjects + (p.pEventDelays - pValues);
  p.pEventPrioritiesObject = pObjects + (p.pEventPriorities - pValues);
  p.pEventAssignmentsObject = pObjects + (p.pEventAssignments - pValues);
  p.pEventRootsObject = pObjects + (p.pEventRoots - pValues);
  p.pEventRootStatesObject = pObjects + (p.pEventRootStates - pValues);
  p.pPropensitiesObject = pObjects + (p.pPropensities - pValues);
  p.pTotalMassesObject = pObjects + (p.pTotalMasses - pValues);
  p.pDependentMassesObject = pObjects + (p.pDependentMasses - pValues);
  p.pDiscontinuousObject = pObjects + (p.pDiscontinuous - pValues);
}

void CMathContainer::initializeDiscontinuousCreationPointer()
{
  C_FLOAT64 * pValues = mValues.array();
  CMathObject * pObjects = mObjects.array();

  size_t nDiscontinuous = mDiscontinuous.size();
  size_t nEvents = mEvents.size() - nDiscontinuous;
  size_t nEventAssignments = mEventAssignments.size() - nDiscontinuous;
  size_t nEventRoots = mEventRoots.size() - 2 * nDiscontinuous;

  mCreateDiscontinuousPointer.pEvent = mEvents.array() + nEvents;
  mCreateDiscontinuousPointer.pDiscontinuous = pObjects + (mDiscontinuous.array() - pValues);
  mCreateDiscontinuousPointer.pEventDelay = pObjects + (mEventDelays.array() - pValues) + nEvents;
  mCreateDiscontinuousPointer.pEventPriority = pObjects + (mEventPriorities.array() - pValues) + nEvents;
  mCreateDiscontinuousPointer.pEventAssignment = pObjects + (mEventAssignments.array() - pValues) + nEventAssignments;
  mCreateDiscontinuousPointer.pEventTrigger = pObjects + (mEventTriggers.array() - pValues) + nEvents;
  mCreateDiscontinuousPointer.pEventRoot = pObjects + (mEventRoots.array() - pValues) + nEventRoots;
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

