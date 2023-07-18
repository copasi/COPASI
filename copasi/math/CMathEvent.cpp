// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

#include <limits>

#include "copasi/copasi.h"

#include "CMathEnum.h"
#include "CMathEvent.h"
#include "CMathContainer.h"
#include "CMathExpression.h"
#include "CMathEventQueue.h"

#include "copasi/model/CMetab.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CEvent.h"

#include "copasi/function/CFunction.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/utilities/CNodeIterator.h"
#include "copasi/utilities/CCallback.h"

// Uncomment this line below to get numeric debug print out.
// #define DEBUG_OUTPUT 1

CMathEvent::CAssignment::CAssignment()
  : mpTarget(NULL)
  , mpAssignment(NULL)
  , mIsStateValue(false)
{}

CMathEvent::CAssignment::CAssignment(const CMathEvent::CAssignment & src)
  : mpTarget(src.mpTarget)
  , mpAssignment(src.mpAssignment)
  , mIsStateValue(src.mIsStateValue)
{}

CMathEvent::CAssignment::~CAssignment()
{}

void CMathEvent::CAssignment::initialize(CMath::sPointers & pointers)
{
  // Initialize the assignment object
  mpAssignment = pointers.pEventAssignmentsObject;
  CMathObject::initialize(pointers.pEventAssignmentsObject++, pointers.pEventAssignments++,
                          CMath::ValueType::EventAssignment, CMath::EntityType::Event, CMath::SimulationType::Undefined,
                          false, false, NULL);
}

void CMathEvent::CAssignment::copy(const CMathEvent::CAssignment & src,
                                   CMathContainer & /* container */)
{
  assert(&src != this);
  *this = src;
}

void CMathEvent::CAssignment::relocate(const CMathContainer * pContainer,
                                       const std::vector< CMath::sRelocate > & relocations)
{
  pContainer->relocateObject(mpTarget, relocations);
  pContainer->relocateObject(mpAssignment, relocations);
}

bool CMathEvent::CAssignment::compile(const CEventAssignment * pDataAssignment,
                                      CMathContainer & container)
{
  // A compiled pDataAssignment is prerequisite.
  bool success = true;
  bool MultiplyByVolume = false;

  // Determine the target object
  mpTarget = container.getMathObject(pDataAssignment->getTargetObject());

  if (mpTarget != NULL)
    {
      if (mpTarget->getEntityType() == CMath::EntityType::Species
          && mpTarget->isIntensiveProperty())
        {
          MultiplyByVolume = true;
          mpTarget = const_cast< CMathObject * >(mpTarget->getCorrespondingProperty());
        }

      if (mpTarget->getSimulationType() == CMath::SimulationType::Fixed)
        {
          mpTarget->setSimulationType(CMath::SimulationType::EventTarget);
        }
    }
  else
    {
      success = false;
    }

  CObjectInterface::ContainerList ListOfContainer;

  // Compile the assignment object in the model context
  CExpression AssignmentExpression("AssignmentExpression", &container);

  if (MultiplyByVolume)
    {
      // We are sure that we have a species
      const  CMetab * pSpecies = static_cast< CMetab * >(mpTarget->getDataObject()->getObjectParent());

      std::ostringstream Infix;
      Infix.imbue(std::locale::classic());
      Infix.precision(std::numeric_limits<double>::digits10 + 2);

      Infix << pointerToString(&container.getQuantity2NumberFactor());
      Infix << "*<";
      Infix << pSpecies->getCompartment()->getValueReference()->getCN();
      Infix << ">*(";
      Infix << pDataAssignment->getExpression();
      Infix << ")";

      success &= AssignmentExpression.setInfix(Infix.str());
    }
  else
    {
      success &= AssignmentExpression.setInfix(pDataAssignment->getExpression());
    }

  mpAssignment->setDataObject(pDataAssignment->getExpression().empty() ? NULL : pDataAssignment->getExpressionPtr());
  success &= AssignmentExpression.compile(ListOfContainer);
  success &= mpAssignment->setExpression(AssignmentExpression, container);

  return success;
}

void CMathEvent::CAssignment::setTarget(CMathObject * pTarget)
{
  mpTarget = pTarget;
}

const CMathObject * CMathEvent::CAssignment::getTarget() const
{
  return mpTarget;
}

void CMathEvent::CAssignment::setAssignment(CMathObject * pExpression)
{
  mpAssignment = pExpression;
}

const CMathObject * CMathEvent::CAssignment::getAssignment() const
{
  return mpAssignment;
}

void CMathEvent::CAssignment::setIsStateValue(bool isStateValue)
{
  mIsStateValue = isStateValue;
}

const bool & CMathEvent::CAssignment::isStateValue() const
{
  return mIsStateValue;
}

CMathEvent::CTrigger::CRootProcessor::CRootProcessor():
  mpRoot(NULL),
  mpRootState(NULL),
  mEquality(false),
  mDiscrete(false),
  mLastToggleTime(),
  mpRootValue(NULL),
  mpRootStateValue(NULL)
{}

CMathEvent::CTrigger::CRootProcessor::CRootProcessor(const CMathEvent::CTrigger::CRootProcessor & src):
  mpRoot(src.mpRoot),
  mpRootState(src.mpRootState),
  mEquality(src.mEquality),
  mDiscrete(src.mDiscrete),
  mLastToggleTime(src.mLastToggleTime),
  mpRootValue(src.mpRootValue),
  mpRootStateValue(src.mpRootStateValue)
{}

CMathEvent::CTrigger::CRootProcessor::~CRootProcessor()
{}

void CMathEvent::CTrigger::CRootProcessor::toggle(const C_FLOAT64 & time,
    const bool & equality)
{
  // This function must only be called if we found a root, i.e., the
  // value of the root expression changes sign. In that case it is save
  // to toggle the state.

  if (!std::isnan(mLastToggleTime) &&
      mLastToggleTime == time)
    {
      return;
    }

  if (mDiscrete &&
      equality == true)
    {
      *mpRootStateValue = (*mpRootStateValue > 0.5) ? 0.0 : 1.0;
      mLastToggleTime = time;
    }
  else if (!mDiscrete)
    {
      if (equality == mEquality && *mpRootStateValue < 0.5)
        {
          *mpRootStateValue = 1.0;
          mLastToggleTime = time;
        }
      else if (equality != mEquality && *mpRootStateValue > 0.5)
        {
          *mpRootStateValue = 0.0;
          mLastToggleTime = time;
        }
    }

  return;
}

void CMathEvent::CTrigger::CRootProcessor::toggle(const C_FLOAT64 & time)
{
  // This function must only be called if we found a root, i.e., the
  // value of the root expression changes sign. In that case it is save
  // to toggle the activity.

  *mpRootStateValue = (*mpRootStateValue > 0.5) ? 0.0 : 1.0;

  mLastToggleTime = time;

  return;
}

const bool & CMathEvent::CTrigger::CRootProcessor::isEquality() const
{
  return mEquality;
}

bool CMathEvent::CTrigger::CRootProcessor::isTrue() const
{
  return *mpRootStateValue > 0.5 ? true : false;
}

void CMathEvent::CTrigger::CRootProcessor::applyInitialValues()
{
  calculateTrueValue();
  mLastToggleTime = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
}

void CMathEvent::CTrigger::CRootProcessor::calculateTrueValue()
{
  if ((*mpRootValue < 0.0) ||
      ((*mpRootValue <= 0.0) && !mEquality))
    {
      *mpRootStateValue = 0.0;
    }
  else
    {
      *mpRootStateValue = 1.0;
    }

  // We advanced in time past the last continuous toggle time and can therefore reset it.
  mLastToggleTime = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
}

void CMathEvent::CTrigger::CRootProcessor::initialize(CMath::sPointers & pointers)
{
  // Initialize the root object!
  mpRoot = pointers.pEventRootsObject;
  mpRootValue = pointers.pEventRoots;
  *mpRootValue = 1.0;
  CMathObject::initialize(pointers.pEventRootsObject++, pointers.pEventRoots++,
                          CMath::ValueType::EventRoot, CMath::EntityType::Event, CMath::SimulationType::Undefined,
                          false, false, NULL);

  // Initialize the root state object!
  mpRootState = pointers.pEventRootStatesObject;
  mpRootStateValue = pointers.pEventRootStates;
  *mpRootStateValue = 1.0;
  CMathObject::initialize(pointers.pEventRootStatesObject++, pointers.pEventRootStates++,
                          CMath::ValueType::EventRootState, CMath::EntityType::Event, CMath::SimulationType::Undefined,
                          false, false, NULL);
}

void CMathEvent::CTrigger::CRootProcessor::copy(const CMathEvent::CTrigger::CRootProcessor & src,
    CMathContainer & /* container */)
{
  assert(&src != this);
  *this = src;
}

void CMathEvent::CTrigger::CRootProcessor::relocate(const CMathContainer * pContainer,
    const std::vector< CMath::sRelocate > & relocations)
{
  pContainer->relocateObject(mpRoot, relocations);
  pContainer->relocateObject(mpRootState, relocations);
  pContainer->relocateValue(mpRootValue, relocations);
  pContainer->relocateValue(mpRootStateValue, relocations);
}

bool CMathEvent::CTrigger::CRootProcessor::compile(CEvaluationNode * pRootNode,
    const bool & equality,
    CMathContainer & container)
{
  mEquality = equality;

  CObjectInterface::ContainerList ListOfContainer;
  ListOfContainer.push_back(const_cast< CMathContainer * >(&container));

  CMathExpression * pExpression = new CMathExpression("RootExpression", container);
  bool success = static_cast< CEvaluationTree * >(pExpression)->setRoot(pRootNode);
  success &= mpRoot->setExpressionPtr(pExpression);

  // Compile the root state object
  // The root state can not be automatically determined
#ifdef XXXX
  CMathExpression * pStateExpression = new CMathExpression("RootStateExpression", container);

  CEvaluationNode * pStateExpressionNode = new CEvaluationNodeLogical(CEvaluationNode::SubType::GT, "GT");
  pStateExpressionNode->addChild(new CEvaluationNodeObject((C_FLOAT64 *) mpRoot->getValuePointer()));
  pStateExpressionNode->addChild(new CEvaluationNodeNumber(CEvaluationNode::S_DOUBLE, "0.0"));

  success &= static_cast< CEvaluationTree * >(pStateExpression)->setRoot(pStateExpressionNode);
  success &= mpRootState->setExpressionPtr(pStateExpression);
#endif // XXXX

  return success;
}

void CMathEvent::CTrigger::CRootProcessor::setDataObject(const CDataObject * pDataObject)
{
  mpRoot->setDataObject(pDataObject);
}

// static
CEvaluationNode * CMathEvent::CTrigger::CRootProcessor::createTriggerExpressionNode() const
{
  return  new CEvaluationNodeObject((bool *) mpRootState->getValuePointer());
}

CMathEvent::CTrigger::CTrigger():
  mpTrigger(NULL),
  mpInitialTrigger(NULL),
  mRoots(),
  mInfix()
{}

CMathEvent::CTrigger::CTrigger(const CMathEvent::CTrigger & src):
  mpTrigger(src.mpTrigger),
  mpInitialTrigger(src.mpInitialTrigger),
  mRoots(src.mRoots.size()),
  mInfix(src.mInfix)
{}

CMathEvent::CTrigger::~CTrigger()
{}

void CMathEvent::CTrigger::allocate(const CEvent * pDataEvent,
                                    const CMathContainer & container)
{
  // Determine the number of roots.
  CMath::Variables< size_t > Variables;

  CObjectInterface::ContainerList Container;
  Container.push_back(const_cast< CMathContainer * >(&container));

  CExpression Trigger("EventTrigger", &container);
  Trigger.setIsBoolean(true);

  if (Trigger.setInfix(pDataEvent->getTriggerExpression()))
    {
      Trigger.compile(Container);
      mRoots.resize(countRoots(Trigger.getRoot(), Variables));
    }
  else
    {
      CFunction TriggerFunction("EventTrigger", &container);

      if (TriggerFunction.setInfix(pDataEvent->getTriggerExpression()))
        {
          TriggerFunction.compile();

          Variables.resize(TriggerFunction.getVariables().size());
          CMath::Variables< size_t >::iterator it = Variables.begin();
          CMath::Variables< size_t >::iterator end = Variables.end();

          for (; it != end; ++it)
            {
              *it = 0;
            }

          mRoots.resize(countRoots(TriggerFunction.getRoot(), Variables));
        }
    }

  return;
}

void CMathEvent::CTrigger::allocateDiscontinuous(const size_t & nRoots,
    const CMathContainer & /* container */)
{
  mRoots.resize(nRoots);
}

bool CMathEvent::CTrigger::isTrue() const
{
  return * (C_FLOAT64 *) mpTrigger->getValuePointer() > 0.5 ? true : false;
}

void CMathEvent::CTrigger::initialize(CMath::sPointers & pointers)
{
  mInfix.clear();

  // Initialize trigger object.
  mpTrigger = pointers.pEventTriggersObject;
  *pointers.pEventTriggers = 1.0;
  CMathObject::initialize(pointers.pEventTriggersObject++, pointers.pEventTriggers++,
                          CMath::ValueType::EventTrigger, CMath::EntityType::Event, CMath::SimulationType::Undefined,
                          false, false, NULL);

  // Initialize initial trigger object.
  mpInitialTrigger = pointers.pInitialEventTriggersObject;
  *pointers.pInitialEventTriggers = 1.0;
  CMathObject::initialize(pointers.pInitialEventTriggersObject++, pointers.pInitialEventTriggers++,
                          CMath::ValueType::EventTrigger, CMath::EntityType::Event, CMath::SimulationType::Undefined,
                          false, true, NULL);

  // Initialize root object.
  CRootProcessor * pRoot = mRoots.array();
  CRootProcessor * pRootEnd = pRoot + mRoots.size();

  for (; pRoot != pRootEnd; ++pRoot)
    {
      pRoot->initialize(pointers);
    }
}

void CMathEvent::CTrigger::copy(const CMathEvent::CTrigger & src,
                                CMathContainer & container)
{
  assert(&src != this);
  *this = src;

  mRoots.resize(src.mRoots.size());
  CRootProcessor * pRoot = mRoots.array();
  CRootProcessor * pRootEnd = pRoot + mRoots.size();
  const CRootProcessor * pRootSrc = src.mRoots.array();

  for (; pRoot != pRootEnd; ++pRoot, ++pRootSrc)
    {
      pRoot->copy(*pRootSrc, container);
    }
}

void CMathEvent::CTrigger::relocate(const CMathContainer * pContainer,
                                    const std::vector< CMath::sRelocate > & relocations)
{
  pContainer->relocateObject(mpTrigger, relocations);
  pContainer->relocateObject(mpInitialTrigger, relocations);

  CRootProcessor * pRoot = mRoots.array();
  CRootProcessor * pRootEnd = pRoot + mRoots.size();

  for (; pRoot != pRootEnd; ++pRoot)
    {
      pRoot->relocate(pContainer, relocations);
    }
}

bool CMathEvent::CTrigger::compile(const CEvent * pDataEvent,
                                   CMathContainer & container)
{
  bool success = true;

  CMath::Variables< CEvaluationNode * > Variables;

  CObjectInterface::ContainerList ListOfContainer;
  ListOfContainer.push_back(&container);

  CExpression DataTrigger("DataTrigger", &container);
  DataTrigger.setIsBoolean(true);
  const CExpression * pDataExpression = NULL;

  if (pDataEvent != NULL)
    {
      mInfix = pDataEvent->getTriggerExpression();
      pDataExpression = pDataEvent->getTriggerExpressionPtr();
    }

  if (mpTrigger != NULL)
    {
      DataTrigger.setInfix(mInfix);

      success &= DataTrigger.compile();

      CEvaluationNode * pTriggerRoot = NULL;
      CRootProcessor * pRoot = mRoots.array();

      pTriggerRoot = compile(DataTrigger.getRoot(), Variables, pRoot, container);

      assert(pRoot <= mRoots.array() + mRoots.size());

      CRootProcessor * itRoot = mRoots.begin();
      CRootProcessor * endRoot = mRoots.end();

      for (; itRoot != endRoot; ++itRoot)
        {
          itRoot->setDataObject(pDataExpression);
        }

      CMathExpression * pTrigger = new CMathExpression("EventTrigger", container);
      success &= static_cast< CEvaluationTree * >(pTrigger)->setRoot(pTriggerRoot);

      mpTrigger->setDataObject(pDataExpression);
      success &= mpTrigger->setExpressionPtr(pTrigger);
    }

  return success;
}

const CVector< CMathEvent::CTrigger::CRootProcessor > & CMathEvent::CTrigger::getRoots() const
{
  return mRoots;
}

void CMathEvent::CTrigger::setExpression(const std::string & infix,
    CMathContainer & container)
{
  mInfix = infix;

  if (mpTrigger != NULL)
    mpTrigger->setExpression(infix, true, container);

  compile(NULL, container);

#ifdef DEBUG_OUTPUT
  std::cout << *mpTrigger;
  std::cout << *mpInitialTrigger;

  CRootProcessor * pRoot = mRoots.array();
  CRootProcessor * pRootEnd = pRoot + mRoots.size();

  for (; pRoot != pRootEnd; ++pRoot)
    {
      std::cout << *pRoot->mpRoot;
      std::cout << *pRoot->mpRootState;
    }

#endif // DEBUG_OUTPUT
}

// static
size_t CMathEvent::CTrigger::countRoots(const CEvaluationNode * pNode,
                                        const CMath::Variables< size_t > & variables)
{
  size_t RootCount = 0;

  // We only need to count in boolean functions see compile for details.
  CNodeContextIterator< const CEvaluationNode, std::vector< size_t > > itNode(pNode);
  itNode.setProcessingModes(CNodeIteratorMode::Flag(CNodeIteratorMode::Before) | CNodeIteratorMode::After);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      switch (itNode.processingMode())
        {
          case CNodeIteratorMode::Before:

            // Variables return always false we need to dig deeper.
            if (itNode->mainType() == CEvaluationNode::MainType::VARIABLE ||
                itNode->isBoolean())
              {
                continue;
              }

            // We found a non boolean node which does not create a root.
            itNode.skipChildren();
            RootCount = 0;

            break;

          case CNodeIteratorMode::After:
          {
            // We do not need to check whether the root is boolean as non boolean nodes are
            // already processed
            const CEvaluationNode::MainType & MainType = itNode->mainType();
            const CEvaluationNode::SubType & SubType = itNode->subType();

            switch (MainType)
              {
                case CEvaluationNode::MainType::LOGICAL:

                  switch (SubType)
                    {
                      case CEvaluationNode::SubType::EQ:
                      case CEvaluationNode::SubType::NE:
                        RootCount = countRootsEQ(*itNode, itNode.context());
                        break;

                      case CEvaluationNode::SubType::LE:
                      case CEvaluationNode::SubType::LT:
                      case CEvaluationNode::SubType::GE:
                      case CEvaluationNode::SubType::GT:
                        RootCount = 1;
                        break;

                      default:
                        RootCount = countRootsDefault(itNode.context());
                        break;
                    }

                  break;

                case CEvaluationNode::MainType::CALL:

                  switch (SubType)
                    {
                      case CEvaluationNode::SubType::FUNCTION:
                      case CEvaluationNode::SubType::EXPRESSION:
                        RootCount = countRootsFUNCTION(*itNode, itNode.context());
                        break;

                      default:
                        RootCount = countRootsDefault(itNode.context());
                        break;
                    }

                  break;

                case CEvaluationNode::MainType::VARIABLE:

                  switch (SubType)
                    {
                      case CEvaluationNode::SubType::DEFAULT:
                        RootCount = countRootsVARIABLE(*itNode, variables);
                        break;

                      default:
                        RootCount = countRootsDefault(itNode.context());
                        break;
                    }

                  break;

                default:
                  RootCount = countRootsDefault(itNode.context());
                  break;
              }
          }
          break;

          default:
            break;
        }

      if (itNode.parentContextPtr() != NULL)
        {
          itNode.parentContextPtr()->push_back(RootCount);
        }
    }

  return RootCount;
}

// static
size_t CMathEvent::CTrigger::countRootsDefault(const std::vector< size_t > & children)
{
  size_t RootCount = 0;

  std::vector< size_t >::const_iterator it = children.begin();
  std::vector< size_t >::const_iterator end = children.end();

  for (; it != end; ++it)
    {
      RootCount += *it;
    }

  return RootCount;
}

// static
size_t CMathEvent::CTrigger::countRootsEQ(const CEvaluationNode * pNode,
    const std::vector< size_t > & children)
{
  size_t nRoots = children[0] + children[1];

  // Equality can be determined between Boolean and double values.
  if (static_cast<const CEvaluationNode *>(pNode->getChild())->isBoolean())
    {
      nRoots = children[0] + children[1];
    }
  else
    {
      nRoots = 2;
    }

  return nRoots;
}

// static
size_t CMathEvent::CTrigger::countRootsFUNCTION(const CEvaluationNode * pNode,
    const std::vector< size_t > & children)
{
  const CEvaluationNode * pTreeRoot =
    static_cast< const CEvaluationNodeCall * >(pNode)->getCalledTree()->getRoot();

  size_t nRoots = countRoots(pTreeRoot, children);

  return nRoots;
}

// static
size_t CMathEvent::CTrigger::countRootsVARIABLE(const CEvaluationNode * pNode,
    const CMath::Variables< size_t > & variables)
{
  size_t Index =
    static_cast< const CEvaluationNodeVariable * >(pNode)->getIndex();

  if (Index == C_INVALID_INDEX)
    {
      return 0;
    }

  return variables[Index];
}

// static
CEvaluationNode * CMathEvent::CTrigger::compile(const CEvaluationNode * pTriggerNode,
    const CMath::Variables< CEvaluationNode * > & variables,
    CMathEvent::CTrigger::CRootProcessor *& pRoot,
    CMathContainer & container)
{
  CEvaluationNode * pNode = NULL;

  CNodeContextIterator< const CEvaluationNode, std::vector< CEvaluationNode * > > itNode(pTriggerNode);
  itNode.setProcessingModes(CNodeIteratorMode::Flag(CNodeIteratorMode::Before) | CNodeIteratorMode::After);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      switch (itNode.processingMode())
        {
          case CNodeIteratorMode::Before:

            // Variables return always false we need to dig deeper.
            if (itNode->mainType() == CEvaluationNode::MainType::VARIABLE)
              {
                size_t Index =
                  static_cast< const CEvaluationNodeVariable * >(*itNode)->getIndex();

                if (Index != C_INVALID_INDEX &&
                    Index < variables.size() &&
                    variables[Index]->isBoolean())
                  {
                    continue;
                  }

                // We found a non boolean node which we simply copy.
                itNode.skipChildren();

                // Since a variable may be referred to multiple times we need to copy it.
                if (Index != C_INVALID_INDEX)
                  {
                    pNode = variables[Index]->copyBranch();
                  }
                else
                  {
                    // Variables must not appear in mathematical expressions.
                    // We create an constant node with the variable name and value NaN.
                    pNode = new CEvaluationNodeConstant(CEvaluationNode::SubType::NaN, itNode->getData());
                  }
              }
            else if (!itNode->isBoolean())
              {
                // We found a non boolean node which we simply copy.
                itNode.skipChildren();
                pNode = container.copyBranch(*itNode, variables, true);
              }
            else
              {
                continue;
              }

            break;

          case CNodeIteratorMode::After:

            // We do not need to check whether the root is boolean as non boolean nodes are
            // already processed
            switch (itNode->mainType() | itNode->subType())
              {
                case (CEvaluationNode::MainType::LOGICAL | CEvaluationNode::SubType::AND):
                case (CEvaluationNode::MainType::LOGICAL | CEvaluationNode::SubType::OR):
                case (CEvaluationNode::MainType::LOGICAL | CEvaluationNode::SubType::XOR):
                  pNode = compileAND(*itNode, itNode.context(), variables, pRoot, container);
                  break;

                case (CEvaluationNode::MainType::LOGICAL | CEvaluationNode::SubType::EQ):
                  pNode = compileEQ(*itNode, itNode.context(), variables, pRoot, container);
                  break;

                case (CEvaluationNode::MainType::LOGICAL | CEvaluationNode::SubType::NE):
                  pNode = compileNE(*itNode, itNode.context(), variables, pRoot, container);
                  break;

                case (CEvaluationNode::MainType::LOGICAL | CEvaluationNode::SubType::LE):
                case (CEvaluationNode::MainType::LOGICAL | CEvaluationNode::SubType::LT):
                case (CEvaluationNode::MainType::LOGICAL | CEvaluationNode::SubType::GE):
                case (CEvaluationNode::MainType::LOGICAL | CEvaluationNode::SubType::GT):
                  pNode = compileLE(*itNode, itNode.context(), variables, pRoot, container);
                  break;

                case (CEvaluationNode::MainType::FUNCTION | CEvaluationNode::SubType::NOT):
                  pNode = compileNOT(*itNode, itNode.context(), variables, pRoot, container);
                  break;

                case (CEvaluationNode::MainType::CALL | CEvaluationNode::SubType::FUNCTION):
                case (CEvaluationNode::MainType::CALL | CEvaluationNode::SubType::EXPRESSION):
                  pNode = compileFUNCTION(*itNode, itNode.context(), variables, pRoot, container);
                  break;

                case (CEvaluationNode::MainType::VARIABLE | CEvaluationNode::SubType::DEFAULT):
                  pNode = compileVARIABLE(*itNode, itNode.context(), variables, pRoot, container);
                  break;

                case (CEvaluationNode::MainType::CONSTANT | CEvaluationNode::SubType::True):
                case (CEvaluationNode::MainType::CONSTANT | CEvaluationNode::SubType::False):
                default:
                  pNode = itNode->copyNode(itNode.context());
                  break;
              }

            break;

          default:
            // This will never happen
            break;
        }

      if (itNode.parentContextPtr() != NULL)
        {
          itNode.parentContextPtr()->push_back(pNode);
        }
    }

  return pNode;
}

// static
CEvaluationNode * CMathEvent::CTrigger::compileAND(const CEvaluationNode * pTriggerNode,
    const std::vector< CEvaluationNode * > & children,
    const CMath::Variables< CEvaluationNode * > & /* variables */,
    CMathEvent::CTrigger::CRootProcessor *& /* pRoot */,
    CMathContainer & /* container */)
{
  CEvaluationNode * pNode = NULL;

  switch (pTriggerNode->subType())
    {
      case CEvaluationNode::SubType::AND:
        pNode = new CEvaluationNodeLogical(CEvaluationNode::SubType::AND, "AND");
        break;

      case CEvaluationNode::SubType::OR:
        pNode = new CEvaluationNodeLogical(CEvaluationNode::SubType::OR, "OR");
        break;

      case CEvaluationNode::SubType::XOR:
        pNode = new CEvaluationNodeLogical(CEvaluationNode::SubType::XOR, "XOR");
        break;

      default:
        break;
    }

  if (pNode != NULL)
    {
      pNode->addChild(children[0]);
      pNode->addChild(children[1]);
    }

  return pNode;
}

// static
CEvaluationNode * CMathEvent::CTrigger::compileEQ(const CEvaluationNode * pTriggerNode,
    const std::vector< CEvaluationNode * > & children,
    const CMath::Variables< CEvaluationNode * > & variables,
    CMathEvent::CTrigger::CRootProcessor *& pRoot,
    CMathContainer & container)
{
  CEvaluationNode * pNode = NULL;

  // Equality can be determined between Boolean and double values.
  if (!static_cast< const CEvaluationNode * >(pTriggerNode->getChild())->isBoolean())
    {
      // We treat x EQ y as (x GE y) AND (y GE x)
      pNode = new CEvaluationNodeLogical(CEvaluationNode::SubType::AND, "AND");

      CEvaluationNodeLogical GELeft(CEvaluationNode::SubType::GE, "GE");
      CEvaluationNode * pGELeft = compileLE(&GELeft, children, variables, pRoot, container);
      pNode->addChild(pGELeft);

      // We need to duplicate and reverse the order for the right
      std::vector< CEvaluationNode * > RightChildren;
      RightChildren.push_back(children[1]->copyBranch());
      RightChildren.push_back(children[0]->copyBranch());

      CEvaluationNodeLogical GERight(CEvaluationNode::SubType::GE, "GE");
      CEvaluationNode * pGERight = compileLE(&GERight, RightChildren, variables, pRoot, container);
      pNode->addChild(pGERight);
    }
  else
    {
      pNode = new CEvaluationNodeLogical(CEvaluationNode::SubType::EQ, "EQ");
      pNode->addChild(children[0]);
      pNode->addChild(children[1]);
    }

  return pNode;
}

// static
CEvaluationNode * CMathEvent::CTrigger::compileNE(const CEvaluationNode * pTriggerNode,
    const std::vector< CEvaluationNode * > & children,
    const CMath::Variables< CEvaluationNode * > & variables,
    CMathEvent::CTrigger::CRootProcessor *& pRoot,
    CMathContainer & container)
{
  // We treat this as NOT and EQ.
  // For this we create a modified copy of the current node.

  CEvaluationNode * pNode = new CEvaluationNodeFunction(CEvaluationNode::SubType::NOT, "NOT");

  CEvaluationNodeLogical EqNode(CEvaluationNode::SubType::EQ, "EQ");

  EqNode.addChild(children[0]->copyBranch());
  EqNode.addChild(children[1]->copyBranch());

  CEvaluationNode * pEqNode = compileEQ(&EqNode, children, variables, pRoot, container);
  pNode->addChild(pEqNode);

  return pNode;
}

// static
CEvaluationNode * CMathEvent::CTrigger::compileLE(const CEvaluationNode * pTriggerNode,
    const std::vector< CEvaluationNode * > & children,
    const CMath::Variables< CEvaluationNode * > & /* variables */,
    CMathEvent::CTrigger::CRootProcessor *& pRoot,
    CMathContainer & container)
{
  CEvaluationNode * pNode = NULL;

  // We need to compile the root finding structure
  // Create a root expression
  CEvaluationNode * pRootNode = new CEvaluationNodeOperator(CEvaluationNode::SubType::MINUS, "-");

  bool Equality = false;

  // We need to create a copy the left and right data nodes with the variables being replaced.
  switch (pTriggerNode->subType())
    {
      case CEvaluationNode::SubType::LE:
        pRootNode->addChild(children[1]);
        pRootNode->addChild(children[0]);
        Equality = true;
        break;

      case CEvaluationNode::SubType::LT:
        pRootNode->addChild(children[1]);
        pRootNode->addChild(children[0]);
        Equality = false;
        break;

      case CEvaluationNode::SubType::GE:
        pRootNode->addChild(children[0]);
        pRootNode->addChild(children[1]);
        Equality = true;
        break;

      case CEvaluationNode::SubType::GT:
        pRootNode->addChild(children[0]);
        pRootNode->addChild(children[1]);
        Equality = false;
        break;
    }

  pRoot->compile(pRootNode, Equality, container);
  pNode = pRoot->createTriggerExpressionNode();
  pRoot++;

  // We do not need to delete pRootNode as CRoot::compile takes car of it.

  return pNode;
}

// static
CEvaluationNode * CMathEvent::CTrigger::compileNOT(const CEvaluationNode * /* pTriggerNode */,
    const std::vector< CEvaluationNode * > & children,
    const CMath::Variables< CEvaluationNode * > & /* variables */,
    CMathEvent::CTrigger::CRootProcessor *& /* pRoot */,
    CMathContainer & /* container */)
{
  CEvaluationNode * pNode = NULL;

  pNode = new CEvaluationNodeFunction(CEvaluationNode::SubType::NOT, "NOT");
  pNode->addChild(children[0]);

  return pNode;
}

// static
CEvaluationNode * CMathEvent::CTrigger::compileFUNCTION(const CEvaluationNode * pTriggerNode,
    const std::vector< CEvaluationNode * > & children,
    const CMath::Variables< CEvaluationNode * > & /* variables */,
    CMathEvent::CTrigger::CRootProcessor *& pRoot,
    CMathContainer & container)
{
  const CEvaluationNode * pCalledNode =
    static_cast< const CEvaluationNodeCall * >(pTriggerNode)->getCalledTree()->getRoot();

  CEvaluationNode * pNode = compile(pCalledNode, children, pRoot, container);

  // We need to delete the children as the variables have been copied in place.
  std::vector< CEvaluationNode * >::const_iterator it = children.begin();
  std::vector< CEvaluationNode * >::const_iterator end = children.end();

  for (; it != end; ++it)
    {
      delete *it;
    }

  return pNode;
}

// static
CEvaluationNode * CMathEvent::CTrigger::compileVARIABLE(const CEvaluationNode * pTriggerNode,
    const std::vector< CEvaluationNode * > & /* children */,
    const CMath::Variables< CEvaluationNode * > & variables,
    CMathEvent::CTrigger::CRootProcessor *& /* pRoot */,
    CMathContainer & /* container */)
{
  // We need to mimic the process in CMathContainer::copyBranch;
  size_t Index =
    static_cast< const CEvaluationNodeVariable * >(pTriggerNode)->getIndex();

  if (Index != C_INVALID_INDEX &&
      Index < variables.size())
    {
      // Since a variable may be referred to multiple times we need to copy it.
      return variables[Index]->copyBranch();
    }
  else
    {
      // Variables must not appear in mathematical expressions.
      // We create a constant node with the variable name and value NaN.
      return new CEvaluationNodeConstant(CEvaluationNode::SubType::NaN, pTriggerNode->getData());
    }
}

// static
void CMathEvent::allocate(CMathEvent & Event,
                          const CEvent * pDataEvent,
                          const CMathContainer & container)
{
  Event.mTrigger.allocate(pDataEvent, container);
  Event.mAssignments.resize(pDataEvent->getAssignments().size());
}

CMathEvent::CMathEvent():
  mpContainer(NULL),
  mpTime(NULL),
  mType(CEvent::Assignment),
  mTrigger(),
  mAssignments(),
  mpDelay(NULL),
  mpPriority(NULL),
  mpCallback(NULL),
  mTargetValues(),
  mTargetPointers(),
  mEffectsSimulation(CMath::StateChange::None),
  mDelaySequence(),
  mTargetValuesSequence(),
  mPostAssignmentSequence(),
  mFireAtInitialTime(false),
  mTriggerIsPersistent(false),
  mDelayExecution(true),
  mpPendingAction(NULL),
  mDisabled(false)
{}

CMathEvent::CMathEvent(const CMathEvent & src):
  mpContainer(src.mpContainer),
  mpTime(src.mpTime),
  mType(src.mType),
  mTrigger(src.mTrigger),
  mAssignments(src.mAssignments),
  mpDelay(src.mpDelay),
  mpPriority(src.mpPriority),
  mpCallback(src.mpCallback),
  mTargetValues(src.mTargetValues.size(), const_cast< double * >(src.mTargetValues.array())),
  mTargetPointers(src.mTargetPointers),
  mEffectsSimulation(src.mEffectsSimulation),
  mDelaySequence(src.mDelaySequence),
  mTargetValuesSequence(src.mTargetValuesSequence),
  mPostAssignmentSequence(src.mPostAssignmentSequence),
  mFireAtInitialTime(src.mFireAtInitialTime),
  mTriggerIsPersistent(src.mTriggerIsPersistent),
  mDelayExecution(src.mDelayExecution),
  mpPendingAction(NULL),
  mDisabled(src.mDisabled)
{}

/**
 * Destructor
 */
CMathEvent::~CMathEvent()
{
  pdelete(mpPendingAction);
}

CMathEvent & CMathEvent::operator = (const CMathEvent & rhs)
{
  if (this == &rhs) return * this;

  mpContainer = rhs.mpContainer;
  mpTime = rhs.mpTime;
  mType = rhs.mType;
  mTrigger = rhs.mTrigger;
  mAssignments = rhs.mAssignments;
  mpDelay = rhs.mpDelay;
  mpPriority = rhs.mpPriority;
  mpCallback = rhs.mpCallback;
  mTargetValues.initialize(rhs.mTargetValues);
  mTargetPointers = rhs.mTargetPointers;
  mEffectsSimulation = rhs.mEffectsSimulation;
  mDelaySequence = rhs.mDelaySequence;
  mTargetValuesSequence = rhs.mTargetValuesSequence;
  mPostAssignmentSequence = rhs.mPostAssignmentSequence;
  mFireAtInitialTime = rhs.mFireAtInitialTime;
  mTriggerIsPersistent = rhs.mTriggerIsPersistent;
  mDelayExecution = rhs.mDelayExecution;
  mpPendingAction = NULL;
  mDisabled = rhs.mDisabled;

  return *this;
}

const CMathEvent::CTrigger & CMathEvent::getTrigger() const
{
  return mTrigger;
}

void CMathEvent::initialize(CMath::sPointers & pointers)
{
  mTrigger.initialize(pointers);

  CAssignment * pAssignment = mAssignments.array();
  CAssignment * pAssignmentEnd = pAssignment + mAssignments.size();

  // Initialize assignments.
  for (; pAssignment != pAssignmentEnd; ++pAssignment)
    {
      pAssignment->initialize(pointers);
    }

  // Initialize delay object.
  mpDelay = pointers.pEventDelaysObject;
  CMathObject::initialize(pointers.pEventDelaysObject++, pointers.pEventDelays++,
                          CMath::ValueType::EventDelay, CMath::EntityType::Event, CMath::SimulationType::Undefined,
                          false, false, NULL);

  // Initialize priority object.
  mpPriority = pointers.pEventPrioritiesObject;
  CMathObject::initialize(pointers.pEventPrioritiesObject++, pointers.pEventPriorities++,
                          CMath::ValueType::EventPriority, CMath::EntityType::Event, CMath::SimulationType::Undefined,
                          false, false, NULL);
}

void CMathEvent::copy(const CMathEvent & src, CMathContainer & container)
{
  assert(&src != this);
  *this = src;

  mTrigger.copy(src.mTrigger, container);

  mAssignments.resize(src.mAssignments.size());
  CAssignment * pAssignment = mAssignments.array();
  CAssignment * pAssignmentEnd = pAssignment + mAssignments.size();
  const CAssignment * pAssignmentSrc = src.mAssignments.array();

  for (; pAssignment != pAssignmentEnd; ++pAssignment, ++pAssignmentSrc)
    {
      pAssignment->copy(*pAssignmentSrc, container);
    }
}

void CMathEvent::relocate(const CMathContainer * pContainer,
                          const std::vector< CMath::sRelocate > & relocations)
{
  pContainer->relocateValue(mpTime, relocations);

  mTrigger.relocate(pContainer, relocations);

  CAssignment * pAssignment = mAssignments.array();
  CAssignment * pAssignmentEnd = pAssignment + mAssignments.size();

  for (; pAssignment != pAssignmentEnd; ++pAssignment)
    {
      pAssignment->relocate(pContainer, relocations);
    }

  C_FLOAT64 * pArray = mTargetValues.array();
  mpContainer->relocateValue(pArray, relocations);
  mTargetValues.initialize(mAssignments.size(), pArray);

  pContainer->relocateObject(mpDelay, relocations);
  pContainer->relocateObject(mpPriority, relocations);

  C_FLOAT64 ** ppTargetPointers = mTargetPointers.array();
  C_FLOAT64 ** ppTargetPointersEnd = ppTargetPointers + mTargetPointers.size();

  for (; ppTargetPointers != ppTargetPointersEnd; ++ppTargetPointers)
    {
      pContainer->relocateValue(*ppTargetPointers, relocations);
    }
}

bool CMathEvent::compile(const CEvent * pDataEvent,
                         CMathContainer & container)
{
  bool success = true;

  mpContainer = &container;
  mpTime = container.getState(false).array() + container.getCountFixedEventTargets();

  mType = pDataEvent->getType();
  mFireAtInitialTime = pDataEvent->getFireAtInitialTime();
  mTriggerIsPersistent = pDataEvent->getPersistentTrigger();
  mDelayExecution = pDataEvent->getDelayAssignment();

  // Compile Trigger
  success &= mTrigger.compile(pDataEvent, container);

  CAssignment * pAssignment = mAssignments.array();
  CAssignment * pAssignmentEnd = pAssignment + mAssignments.size();
  CDataVector< CEventAssignment >::const_iterator itAssignment = pDataEvent->getAssignments().begin();
  CDataVector< CEventAssignment >::const_iterator endAssignment = pDataEvent->getAssignments().end();

  if (pAssignment != NULL)
    {
      mTargetValues.initialize(mAssignments.size(),
                               (C_FLOAT64 *) pAssignment->getAssignment()->getValuePointer());
    }
  else
    {
      mTargetValues.initialize(0, NULL);
    }

  mTargetPointers.resize(mAssignments.size());
  C_FLOAT64 ** ppTarget = mTargetPointers.array();

  // Compile assignments.
  // Data events with assignments
  for (; pAssignment != pAssignmentEnd && itAssignment != endAssignment; ++pAssignment, ++itAssignment, ++ppTarget)
    {
      success &= pAssignment->compile(itAssignment, container);

      if (pAssignment->getTarget() != NULL)
        {
          *ppTarget = (C_FLOAT64 *) pAssignment->getTarget()->getValuePointer();
        }
    }

  // Discontinuities
  for (; pAssignment != pAssignmentEnd; ++pAssignment, ++ppTarget)
    {
      *ppTarget = (C_FLOAT64 *) pAssignment->getTarget()->getValuePointer();
    }

  CObjectInterface::ContainerList ListOfContainer;

  // Compile the delay object.
  mpDelay->setDataObject(pDataEvent->getDelayExpression().empty() ? NULL : pDataEvent->getDelayExpressionPtr());
  CExpression DelayExpression("DelayExpression", &container);
  success &= DelayExpression.setInfix(pDataEvent->getDelayExpression());
  success &= DelayExpression.compile(ListOfContainer);
  success &= mpDelay->setExpression(DelayExpression, container);

  // Compile the priority object.
  mpPriority->setDataObject(pDataEvent->getPriorityExpression().empty() ? NULL : pDataEvent->getPriorityExpressionPtr());
  CExpression PriorityExpression("PriorityExpression", &container);
  success &= PriorityExpression.setInfix(pDataEvent->getPriorityExpression());
  success &= PriorityExpression.compile(ListOfContainer);
  success &= mpPriority->setExpression(PriorityExpression, container);

  mDisabled = false;

  return success;
}

bool CMathEvent::compile(CMathContainer & container)
{
  bool success = true;

  mpContainer = &container;
  mpTime = container.getState(false).array() + container.getCountFixedEventTargets();

  mType = CEvent::Discontinuity;
  mFireAtInitialTime = false;
  mTriggerIsPersistent = true;
  mDelayExecution = false;

  // Compile Trigger
  success &= mTrigger.compile(NULL, container);

  CAssignment * pAssignment = mAssignments.array();
  CAssignment * pAssignmentEnd = pAssignment + mAssignments.size();

  if (pAssignment != NULL)
    {
      mTargetValues.initialize(mAssignments.size(),
                               (C_FLOAT64 *) pAssignment->getAssignment()->getValuePointer());
    }
  else
    {
      mTargetValues.initialize(0, NULL);
    }

  mTargetPointers.resize(mAssignments.size());
  C_FLOAT64 ** ppTarget = mTargetPointers.array();

  // Compile assignments.
  // Discontinuities
  for (; pAssignment != pAssignmentEnd; ++pAssignment, ++ppTarget)
    {
      *ppTarget = (C_FLOAT64 *) pAssignment->getTarget()->getValuePointer();
    }

  CObjectInterface::ContainerList ListOfContainer;

  // Compile the delay object.
  CExpression DelayExpression("DelayExpression", &container);
  success &= DelayExpression.setInfix("");
  success &= DelayExpression.compile(ListOfContainer);
  success &= mpDelay->setExpression(DelayExpression, container);

  // Compile the priority object.
  CExpression PriorityExpression("PriorityExpression", &container);
  success &= PriorityExpression.setInfix("");
  success &= PriorityExpression.compile(ListOfContainer);
  success &= mpPriority->setExpression(PriorityExpression, container);

  mDisabled = false;

  return success;
}

void CMathEvent::createUpdateSequences()
{
  if (mType == CEvent::Discontinuity)
    {
      mEffectsSimulation |= CMath::eStateChange::Discontinuity;
      return;
    }

  mEffectsSimulation = CMath::StateChange::None;

  const CObjectInterface::ObjectSet & StateValues = mpContainer->getStateObjects();
  const CObjectInterface::ObjectSet & SimulationValues = mpContainer->getSimulationUpToDateObjects();

  CObjectInterface::ObjectSet Requested;
  Requested.insert(mpDelay);
  mpContainer->getTransientDependencies().getUpdateSequence(mDelaySequence, CCore::SimulationContext::Default, StateValues, Requested, SimulationValues);

  Requested.clear();
  CObjectInterface::ObjectSet EventTargets;
  CAssignment * pAssignment = mAssignments.array();
  CAssignment * pAssignmentEnd = pAssignment + mAssignments.size();

  for (; pAssignment != pAssignmentEnd; ++pAssignment)
    {
      Requested.insert(pAssignment->getAssignment());

      const CMathObject * pTarget = pAssignment->getTarget();

      if (pTarget == NULL) continue;

      EventTargets.insert(pTarget);

      // We need to distinguish between Fixed Event Targets, Discontinuities, and State Values

      if (pTarget->getSimulationType() == CMath::SimulationType::EventTarget ||
          (pTarget->getSimulationType() == CMath::SimulationType::Conversion &&
           dynamic_cast< CModelEntity * >(pTarget->getDataObject()->getObjectParent())->getStatus() == CModelEntity::Status::FIXED))
        {
          mEffectsSimulation |= CMath::eStateChange::FixedEventTarget;
        }
      else if (StateValues.find(pTarget) != StateValues.end())
        {
          // mEffectsSimulation |= CMath::eStateChange::State;
          // This is only true if the target value changes, i.e., we need to check each individual assignments for state values when executed
          pAssignment->setIsStateValue(true);
        }
    }

  mpContainer->getTransientDependencies().getUpdateSequence(mTargetValuesSequence, CCore::SimulationContext::Default, StateValues, Requested, SimulationValues);

  // We need to add the total mass of the moieties to the state values.
  CObjectInterface::ObjectSet ExtendedStateValues = StateValues;
  const CMathObject * pTotalMass = mpContainer->getMathObject(mpContainer->getTotalMasses().array());
  const CMathObject * pTotalMassEnd = pTotalMass + mpContainer->getTotalMasses().size();

  for (; pTotalMass != pTotalMassEnd; ++pTotalMass)
    {
      ExtendedStateValues.insert(pTotalMass);
    }

  mpContainer->getTransientDependencies().getUpdateSequence(mPostAssignmentSequence, CCore::SimulationContext::UpdateMoieties, EventTargets, ExtendedStateValues);

  CCore::CUpdateSequence StateEffects;
  mpContainer->getTransientDependencies().getUpdateSequence(StateEffects, CCore::SimulationContext::Default, EventTargets, ExtendedStateValues);

  if (!StateEffects.empty())
    {
      mEffectsSimulation |= CMath::eStateChange::State;
    }

  CCore::CUpdateSequence ContiousSimulationEffects;
  mpContainer->getTransientDependencies().getUpdateSequence(ContiousSimulationEffects, CCore::SimulationContext::Default, EventTargets, SimulationValues);

  if (!ContiousSimulationEffects.empty())
    {
      mEffectsSimulation |=  CMath::eStateChange::ContinuousSimulation;
    }

  // We need to check whether root values have been changed.
  CObjectInterface::ObjectSet DiscreteSimulationValues;
  const CMathObject * pRoot = mpContainer->getMathObject(mpContainer->getRoots().begin());
  const CMathObject * pRootEnd = pRoot + mpContainer->getRoots().size();

  for (; pRoot != pRootEnd; ++pRoot)
    {
      DiscreteSimulationValues.insert(pRoot);
    }

  CCore::CUpdateSequence DiscreteSimulationEffects;
  mpContainer->getTransientDependencies().getUpdateSequence(DiscreteSimulationEffects, CCore::SimulationContext::Default, EventTargets, DiscreteSimulationValues);

  if (!DiscreteSimulationEffects.empty())
    {
      mEffectsSimulation |=  CMath::eStateChange::EventSimulation;
    }
}

void CMathEvent::fire(const bool & equality)
{
  if (mDisabled) return;

  // Discontinuities have to be fired also when the trigger switches to false.
  if (mTrigger.isTrue() || mType == CEvent::Discontinuity)
    {
      if (mDelayExecution)
        {
          mpContainer->getProcessQueue().addAssignment(getExecutionTime(), equality, getTargetValues(), this);
        }
      else
        {
          mpContainer->getProcessQueue().addCalculation(getCalculationTime(), equality, this);
        }
    }
  else if (!mTriggerIsPersistent && mpPendingAction)
    {
      mpContainer->getProcessQueue().removeAction(*mpPendingAction);
      pdelete(mpPendingAction);
    }
}

void CMathEvent::addPendingAction(const CMathEventQueue::iterator & pendingAction)
{
  if (!mTriggerIsPersistent)
    {
#ifdef DEBUG_OUTPUT
      std::cout << *this << std::endl;
      std::cout << "Add:    " << pendingAction->first << ": " << pendingAction->second << std::endl;
#endif //DEBUG_OUTOUT

      assert(mpPendingAction == NULL);
      mpPendingAction = new std::pair< CMathEventQueue::CKey, CMathEventQueue::CAction >(pendingAction->first, pendingAction->second);
    }
}

void CMathEvent::removePendingAction()
{
#ifdef DEBUG_OUTPUT

  if (mpPendingAction != NULL)
    {
      std::cout << *this << std::endl;
      std::cout << "Remove: " << mpPendingAction->first << ": " << mpPendingAction->second << std::endl;
    }

#endif //DEBUG_OUTOUT

  pdelete(mpPendingAction);
}

const CVectorCore< C_FLOAT64 > & CMathEvent::getTargetValues()
{
  mpContainer->applyUpdateSequence(mTargetValuesSequence);

  return mTargetValues;
}

CMath::StateChange CMathEvent::setTargetValues(const CVectorCore< C_FLOAT64 > & values)
{
  bool ValuesChanged = false;
  CMath::StateChange StateChange(CMath::StateChange::None);

  const C_FLOAT64 * pValue = values.array();
  const C_FLOAT64 * pValueEnd = pValue + values.size();
  C_FLOAT64 ** ppTarget = mTargetPointers.array();
  const CAssignment * pAssignment = mAssignments.begin();

  for (; pValue != pValueEnd; ++pValue, ++ppTarget, ++pAssignment)
    {
      if (2.0 * fabs(**ppTarget - *pValue) > (fabs(**ppTarget) + fabs(*pValue)) * std::numeric_limits< C_FLOAT64 >::epsilon() ||
          (fabs(**ppTarget) == std::numeric_limits< C_FLOAT64 >::infinity() && *pValue != **ppTarget) ||
          (fabs(*pValue) == std::numeric_limits< C_FLOAT64 >::infinity() && *pValue != **ppTarget))
        {
          if (pAssignment->isStateValue())
            StateChange |= CMath::eStateChange::State;

          ValuesChanged = true;
          **ppTarget = *pValue;
        }
    }

  if (ValuesChanged || mType == CEvent::Discontinuity)
    {
      mpContainer->applyUpdateSequence(mPostAssignmentSequence);
      mpContainer->updateSimulatedValues(false);
      mpContainer->updateRootValues(false);
      StateChange |= mEffectsSimulation;
    }

  return StateChange;
}

CMath::StateChange CMathEvent::executeAssignment()
{
  return setTargetValues(getTargetValues());
}

const bool & CMathEvent::delayAssignment() const
{
  return mDelayExecution;
}

const bool & CMathEvent::fireAtInitialTime() const
{
  return mFireAtInitialTime;
}

void CMathEvent::setTriggerExpression(const std::string & infix, CMathContainer & container)
{
  mTrigger.setExpression(infix, container);
}

void CMathEvent::setDelayExpression(const std::string & infix, CMathContainer & container)
{
  assert(mpDelay != NULL);

  mpDelay->setExpression(infix, false, container);
}

void CMathEvent::setPriorityExpression(const std::string & infix, CMathContainer & container)
{
  assert(mpPriority != NULL);

  mpPriority->setExpression(infix, false, container);
}

void CMathEvent::addAssignment(CMathObject * pTarget, CMathObject * pExpression)
{
  size_t OldSize = mAssignments.size();
  mAssignments.resize(OldSize + 1, true);

  CAssignment & Assignment = mAssignments[OldSize];
  Assignment.setTarget(pTarget);
  Assignment.setAssignment(pExpression);
}

const CVector< CMathEvent::CAssignment > & CMathEvent::getAssignments() const
{
  return mAssignments;
}

const CMathObject * CMathEvent::getPriority() const
{
  return mpPriority;
}

C_FLOAT64 CMathEvent::getCalculationTime() const
{
  mpContainer->applyUpdateSequence(mDelaySequence);

  if (mDelayExecution ||
      std::isnan(* (C_FLOAT64 *) mpDelay->getValuePointer()))
    {
      return *mpTime;
    }

  return *mpTime + * (C_FLOAT64 *) mpDelay->getValuePointer();
}

C_FLOAT64 CMathEvent::getExecutionTime() const
{
  mpContainer->applyUpdateSequence(mDelaySequence);

  if (!mDelayExecution ||
      std::isnan(* (C_FLOAT64 *) mpDelay->getValuePointer()))
    {
      return *mpTime;
    }

  return *mpTime + * (C_FLOAT64 *) mpDelay->getValuePointer();
}

const CEvent::Type & CMathEvent::getType() const
{
  return mType;
}

void CMathEvent::setCallback(CCallbackInterface * pCallback)
{
  mpCallback = pCallback;
}

void CMathEvent::executeCallback(void * pCaller)
{
  if (mpCallback != NULL)
    {
      (*mpCallback)(this, pCaller);
    }
}

void CMathEvent::setDisabled(const bool & disabled)
{
  mDisabled = disabled;
#ifdef DEBUG_OUTPUT
  std::cout << "Event disabled: " << *this << std::endl;
#endif //DEBUG_OUTOUT
}

/**
 * Check whether an even is disabled.
 * @return const bool & isDisabled
 */
const bool & CMathEvent::isDisabled() const
{
  return mDisabled;
}

std::ostream &operator<<(std::ostream &os, const CMathEvent & o)
{
  os << "pEvent: " << &o
     << ", Type: " << o.mType
     << ", FireAtInitialTime: " << o. mFireAtInitialTime
     << ", TriggerIsPersistent: " << o. mTriggerIsPersistent
     << ", DelayExecution: " << o. mDelayExecution
     << ", Disabled: " << o. mDisabled;

  return os;
}
