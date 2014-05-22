// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <limits>

#include "copasi.h"

#include "CMathEvent.h"
#include "CMathContainer.h"
#include "CMathExpression.h"
#include "CMathEventQueue.h"

#include "model/CEvent.h"

#include "function/CFunction.h"
#include "report/CCopasiRootContainer.h"
#include "utilities/CNodeIterator.h"
#include "utilities/CCallback.h"

CMathEvent::CAssignment::CAssignment():
  mpTarget(NULL),
  mpAssignment(NULL)
{}

CMathEvent::CAssignment::~CAssignment()
{}

void CMathEvent::CAssignment::initialize(CMath::sPointers & pointers)
{
  // Initialize the assignment object
  mpAssignment = pointers.pEventAssignmentsObject;
  CMathObject::initialize(pointers.pEventAssignmentsObject, pointers.pEventAssignments,
                          CMath::EventAssignment, CMath::Event, CMath::SimulationTypeUndefined,
                          false, false, NULL);
}

void CMathEvent::CAssignment::copy(const CMathEvent::CAssignment & src,
                                   CMathContainer & /* container */,
                                   const size_t & /* valueOffset */,
                                   const size_t & objectOffset)
{
  mpTarget = src.mpTarget + objectOffset;
  mpAssignment = src.mpAssignment + objectOffset;
}

bool CMathEvent::CAssignment::compile(CEventAssignment * pDataAssignment,
                                      CMathContainer & container)
{
  // A compiled pDataAssignment is prerequisite.
  bool success = true;

  // Determine the target object
  mpTarget = container.getMathObject(pDataAssignment->getTargetObject());

  if (mpTarget != NULL &&
      mpTarget->getSimulationType() == CMath::Fixed)
    {
      mpTarget->setSimulationType(CMath::EventTarget);
    }

  std::vector< CCopasiContainer * > ListOfContainer;

  // Compile the assignment object in the model context
  CExpression AssignmentExpression("AssignmentExpression", &container);
  success &= AssignmentExpression.setInfix(pDataAssignment->getExpression());
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

CMathEvent::CTrigger::CRootProcessor::CRootProcessor():
  mpRoot(NULL),
  mpRootState(NULL),
  mEquality(false),
  mDiscrete(false),
  mLastToggleTime(),
  mpRootValue(NULL),
  mpRootStateValue(NULL)
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
  CMathObject::initialize(pointers.pEventRootsObject, pointers.pEventRoots,
                          CMath::EventRoot, CMath::Event, CMath::SimulationTypeUndefined,
                          false, false, NULL);

  // Initialize the root state object!
  mpRootState = pointers.pEventRootStatesObject;
  mpRootStateValue = pointers.pEventRootStates;
  *mpRootStateValue = 1.0;
  CMathObject::initialize(pointers.pEventRootStatesObject, pointers.pEventRootStates,
                          CMath::EventRootState, CMath::Event, CMath::SimulationTypeUndefined,
                          false, false, NULL);
}

void CMathEvent::CTrigger::CRootProcessor::copy(const CMathEvent::CTrigger::CRootProcessor & src,
    CMathContainer & /* container */,
    const size_t & valueOffset,
    const size_t & objectOffset)
{
  mpRoot = src.mpRoot + objectOffset;
  mpRootState = src.mpRootState + objectOffset;
  mEquality = src.mEquality;
  mDiscrete = src.mDiscrete;
  mLastToggleTime = src.mLastToggleTime;
  mpRootValue = src.mpRootStateValue + valueOffset;
  mpRootStateValue = src.mpRootStateValue + valueOffset;
}

bool CMathEvent::CTrigger::CRootProcessor::compile(CEvaluationNode * pRootNode,
    const bool & equality,
    CMathContainer & container)
{
  mEquality = equality;

  std::vector< CCopasiContainer * > ListOfContainer;
  ListOfContainer.push_back(const_cast< CMathContainer * >(&container));

  CMathExpression * pExpression = new CMathExpression("RootExpression", container);
  bool success = static_cast< CEvaluationTree * >(pExpression)->setRoot(pRootNode);
  success &= mpRoot->setExpressionPtr(pExpression);

  // Compile the root state object
  // The root state can not be automatically determined
#ifdef XXXX
  CMathExpression * pStateExpression = new CMathExpression("RootStateExpression", container);

  CEvaluationNode * pStateExpressionNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::GT, "GT");
  pStateExpressionNode->addChild(new CEvaluationNodeObject((C_FLOAT64 *) mpRoot->getValuePointer()));
  pStateExpressionNode->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.0"));

  success &= static_cast< CEvaluationTree * >(pStateExpression)->setRoot(pStateExpressionNode);
  success &= mpRootState->setExpressionPtr(pStateExpression);
#endif // XXXX

  return success;
}

// static
CEvaluationNode * CMathEvent::CTrigger::CRootProcessor::createTriggerExpressionNode() const
{
  return  new CEvaluationNodeObject((C_FLOAT64 *) mpRootState->getValuePointer());
}

CMathEvent::CTrigger::CTrigger():
  mpTrigger(NULL),
  mpInitialTrigger(NULL),
  mRoots(),
  mDualAction(false)
{}

CMathEvent::CTrigger::~CTrigger()
{}

void CMathEvent::CTrigger::allocate(const CEvent * pDataEvent,
                                    const CMathContainer & container)
{
  // Determine the number of roots.
  CMath::Variables< size_t > Variables;

  std::vector< CCopasiContainer * > Container;
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
  // Initialize trigger object.
  mpTrigger = pointers.pEventTriggersObject;
  *pointers.pEventTriggers = 1.0;
  CMathObject::initialize(pointers.pEventTriggersObject, pointers.pEventTriggers,
                          CMath::EventTrigger, CMath::Event, CMath::SimulationTypeUndefined,
                          false, false, NULL);

  // Initialize initial trigger object.
  mpInitialTrigger = pointers.pInitialEventTriggersObject;
  *pointers.pInitialEventTriggers = 1.0;
  CMathObject::initialize(pointers.pInitialEventTriggersObject, pointers.pInitialEventTriggers,
                          CMath::EventTrigger, CMath::Event, CMath::SimulationTypeUndefined,
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
                                CMathContainer & container,
                                const size_t & valueOffset,
                                const size_t & objectOffset)
{
  mpTrigger = src.mpTrigger + objectOffset;
  mpInitialTrigger = src.mpInitialTrigger + objectOffset;

  mRoots.resize(src.mRoots.size());
  CRootProcessor * pRoot = mRoots.array();
  CRootProcessor * pRootEnd = pRoot + mRoots.size();
  const CRootProcessor * pRootSrc = src.mRoots.array();

  for (; pRoot != pRootEnd; ++pRoot, ++pRootSrc)
    {
      pRoot->copy(*pRootSrc, container, valueOffset, objectOffset);
    }

  mDualAction = src.mDualAction;
}

bool CMathEvent::CTrigger::compile(CEvent * pDataEvent,
                                   CMathContainer & container)
{
  bool success = true;

  CMath::Variables< CEvaluationNode * > Variables;

  std::vector< CCopasiContainer * > ListOfContainer;
  ListOfContainer.push_back(&container);

  CExpression DataTrigger("DataTrigger", &container);
  DataTrigger.setIsBoolean(true);

  if (pDataEvent != NULL)
    {
      DataTrigger.setInfix(pDataEvent->getTriggerExpression());
      mDualAction = false;
    }
  else
    {
      DataTrigger.setInfix(mpTrigger->getExpressionPtr()->getInfix());
    }

  success &= DataTrigger.compile();

  CEvaluationNode * pTriggerRoot = NULL;
  CRootProcessor * pRoot = mRoots.array();

  pTriggerRoot = compile(DataTrigger.getRoot(), Variables, pRoot, container);

  assert(pRoot == mRoots.array() + mRoots.size());

  CMathExpression * pTrigger = new CMathExpression("EventTrigger", container);
  success &= static_cast< CEvaluationTree * >(pTrigger)->setRoot(pTriggerRoot);

  success &= mpTrigger->setExpressionPtr(pTrigger);

  return success;
}

const CVector< CMathEvent::CTrigger::CRootProcessor > & CMathEvent::CTrigger::getRoots() const
{
  return mRoots;
}

void CMathEvent::CTrigger::setExpression(const std::string & infix,
    CMathContainer & container)
{
  assert(mpTrigger != NULL);

  mpTrigger->setExpression(infix, true, container);

  compile(NULL, container);

  std::cout << *mpTrigger;
  std::cout << *mpInitialTrigger;

  CRootProcessor * pRoot = mRoots.array();
  CRootProcessor * pRootEnd = pRoot + mRoots.size();

  for (; pRoot != pRootEnd; ++pRoot)
    {
      std::cout << *pRoot->mpRoot;
      std::cout << *pRoot->mpRootState;
    }
}

// static
size_t CMathEvent::CTrigger::countRoots(const CEvaluationNode * pNode,
                                        const CMath::Variables< size_t > & variables)
{
  size_t RootCount = 0;

  // TODO CRITICAL We only need to count in boolean functions see compile for details.
  CNodeContextIterator< const CEvaluationNode, std::vector< size_t > > itNode(pNode);
  itNode.setProcessingModes(CNodeIteratorMode::Before | CNodeIteratorMode::After);

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
            if (CEvaluationNode::type(itNode->getType()) == CEvaluationNode::VARIABLE ||
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
            const CEvaluationNode::Type & Type = itNode->getType();

            switch (CEvaluationNode::type(Type))
              {
                case CEvaluationNode::LOGICAL:

                  switch ((int) CEvaluationNode::subType(Type))
                    {
                      case CEvaluationNodeLogical::EQ:
                      case CEvaluationNodeLogical::NE:
                        RootCount = countRootsEQ(*itNode, itNode.context());
                        break;

                      case CEvaluationNodeLogical::LE:
                      case CEvaluationNodeLogical::LT:
                      case CEvaluationNodeLogical::GE:
                      case CEvaluationNodeLogical::GT:
                        RootCount = 1;
                        break;

                      default:
                        RootCount = countRootsDefault(itNode.context());
                        break;
                    }

                  break;

                case CEvaluationNode::CALL:

                  switch ((int) CEvaluationNode::subType(Type))
                    {
                      case CEvaluationNodeCall::FUNCTION:
                      case CEvaluationNodeCall::EXPRESSION:
                        RootCount = countRootsFUNCTION(*itNode, itNode.context());
                        break;

                      default:
                        RootCount = countRootsDefault(itNode.context());
                        break;
                    }

                  break;

                case CEvaluationNode::VARIABLE:

                  switch ((int) CEvaluationNode::subType(Type))
                    {
                      case CEvaluationNodeVariable::ANY:
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
  itNode.setProcessingModes(CNodeIteratorMode::Before | CNodeIteratorMode::After);

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
            if (CEvaluationNode::type(itNode->getType()) == CEvaluationNode::VARIABLE)
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
                    pNode = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, itNode->getData());
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
            switch ((int) itNode->getType())
              {
                case(CEvaluationNode::LOGICAL | CEvaluationNodeLogical::AND):
                case(CEvaluationNode::LOGICAL | CEvaluationNodeLogical::OR):
                case(CEvaluationNode::LOGICAL | CEvaluationNodeLogical::XOR):
                  pNode = compileAND(*itNode, itNode.context(), variables, pRoot, container);
                  break;

                case(CEvaluationNode::LOGICAL | CEvaluationNodeLogical::EQ):
                  pNode = compileEQ(*itNode, itNode.context(), variables, pRoot, container);
                  break;

                case(CEvaluationNode::LOGICAL | CEvaluationNodeLogical::NE):
                  pNode = compileNE(*itNode, itNode.context(), variables, pRoot, container);
                  break;

                case(CEvaluationNode::LOGICAL | CEvaluationNodeLogical::LE):
                case(CEvaluationNode::LOGICAL | CEvaluationNodeLogical::LT):
                case(CEvaluationNode::LOGICAL | CEvaluationNodeLogical::GE):
                case(CEvaluationNode::LOGICAL | CEvaluationNodeLogical::GT):
                  pNode = compileLE(*itNode, itNode.context(), variables, pRoot, container);
                  break;

                case(CEvaluationNode::FUNCTION | CEvaluationNodeFunction::NOT):
                  pNode = compileNOT(*itNode, itNode.context(), variables, pRoot, container);
                  break;

                case(CEvaluationNode::CALL | CEvaluationNodeCall::FUNCTION):
                case(CEvaluationNode::CALL | CEvaluationNodeCall::EXPRESSION):
                  pNode = compileFUNCTION(*itNode, itNode.context(), variables, pRoot, container);
                  break;

                case(CEvaluationNode::VARIABLE | CEvaluationNodeVariable::ANY):
                  pNode = compileVARIABLE(*itNode, itNode.context(), variables, pRoot, container);
                  break;

                case(CEvaluationNode::CONSTANT | CEvaluationNodeConstant::TRUE):
                case(CEvaluationNode::CONSTANT | CEvaluationNodeConstant::FALSE):
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

  switch ((int) CEvaluationNode::subType(pTriggerNode->getType()))
    {
      case CEvaluationNodeLogical::AND:
        pNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
        break;

      case CEvaluationNodeLogical::OR:
        pNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::OR, "OR");
        break;

      case CEvaluationNodeLogical::XOR:
        pNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::XOR, "XOR");
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
      pNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");

      CEvaluationNodeLogical GELeft(CEvaluationNodeLogical::GE, "GE");
      CEvaluationNode * pGELeft = compileLE(&GELeft, children, variables, pRoot, container);
      pNode->addChild(pGELeft);

      // We need to duplicate and reverse the order for the right
      std::vector< CEvaluationNode * > RightChildren;
      RightChildren.push_back(children[1]->copyBranch());
      RightChildren.push_back(children[0]->copyBranch());

      CEvaluationNodeLogical GERight(CEvaluationNodeLogical::GE, "GE");
      CEvaluationNode * pGERight = compileLE(&GERight, RightChildren, variables, pRoot, container);
      pNode->addChild(pGERight);
    }
  else
    {
      pNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::EQ, "EQ");
      pNode->addChild(children[0]);
      pNode->addChild(children[1]);
    }

  return pNode;
}

// static
CEvaluationNode * CMathEvent::CTrigger::compileNE(const CEvaluationNode * /* pTriggerNode */,
    const std::vector< CEvaluationNode * > & children,
    const CMath::Variables< CEvaluationNode * > & variables,
    CMathEvent::CTrigger::CRootProcessor *& pRoot,
    CMathContainer & container)
{
  CEvaluationNode * pNode = NULL;

  // We treat this as NOT and EQ.
  // For this we create a modified copy of the current node.

  CEvaluationNode * pNotNode = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");

  CEvaluationNodeLogical EqNode(CEvaluationNodeLogical::EQ, "EQ");

  EqNode.addChild(children[0]);
  EqNode.addChild(children[1]);

  CEvaluationNode * pEqNode = compileEQ(&EqNode, children, variables, pRoot, container);
  pNotNode->addChild(pEqNode);

  // We need to remove the children since the ownership has been transferred to pEqNode.
  EqNode.removeChild(children[0]);
  EqNode.removeChild(children[1]);

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
  CEvaluationNode * pRootNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");

  bool Equality = false;

  // We need to create a copy the left and right data nodes with the variables being replaced.
  switch ((int) CEvaluationNode::subType(pTriggerNode->getType()))
    {
      case CEvaluationNodeLogical::LE:
        pRootNode->addChild(children[1]);
        pRootNode->addChild(children[0]);
        Equality = true;
        break;

      case CEvaluationNodeLogical::LT:
        pRootNode->addChild(children[1]);
        pRootNode->addChild(children[0]);
        Equality = false;
        break;

      case CEvaluationNodeLogical::GE:
        pRootNode->addChild(children[0]);
        pRootNode->addChild(children[1]);
        Equality = true;
        break;

      case CEvaluationNodeLogical::GT:
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

  pNode = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
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
      return new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, pTriggerNode->getData());
    }
}

// static
void CMathEvent::allocate(CMathEvent * pEvent,
                          const CEvent * pDataEvent,
                          const CMathContainer & container)
{
  pEvent->mTrigger.allocate(pDataEvent, container);
  pEvent->mAssignments.resize(pDataEvent->getAssignments().size());
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
  mEffectsSimulation(CMath::NoChange),
  mCreateCalculationActionSequence(),
  mTargetValuesSequence(),
  mPostAssignmentSequence(),
  mFireAtInitialTime(false),
  mPersistentTrigger(false),
  mDelayAssignment(true),
  mpPendingAction(NULL)
{}

/**
 * Destructor
 */
CMathEvent::~CMathEvent()
{
  pdelete(mpPendingAction);
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
  CMathObject::initialize(pointers.pEventDelaysObject, pointers.pEventDelays,
                          CMath::EventDelay, CMath::Event, CMath::SimulationTypeUndefined,
                          false, false, NULL);

  // Initialize priority object.
  mpPriority = pointers.pEventDelaysObject;
  CMathObject::initialize(pointers.pEventPrioritiesObject, pointers.pEventPriorities,
                          CMath::EventPriority, CMath::Event, CMath::SimulationTypeUndefined,
                          false, false, NULL);
}

void CMathEvent::copy(const CMathEvent & src, CMathContainer & container, const size_t & valueOffset, const size_t & objectOffset)
{
  mType = src.mType;
  mTrigger.copy(src.mTrigger, container, valueOffset, objectOffset);

  mAssignments.resize(src.mAssignments.size());
  CAssignment * pAssignment = mAssignments.array();
  CAssignment * pAssignmentEnd = pAssignment + mAssignments.size();
  const CAssignment * pAssignmentSrc = src.mAssignments.array();

  for (; pAssignment != pAssignmentEnd; ++pAssignment, ++pAssignmentSrc)
    {
      pAssignment->copy(*pAssignmentSrc, container, valueOffset, objectOffset);
    }

  mpDelay = src.mpDelay + objectOffset;
  mpPriority = src.mpPriority + objectOffset;
  mFireAtInitialTime = src.mFireAtInitialTime;
  mPersistentTrigger = src.mPersistentTrigger;
  mDelayAssignment = src.mDelayAssignment;
}

bool CMathEvent::compile(CEvent * pDataEvent,
                         CMathContainer & container)
{
  bool success = true;

  mpContainer = &container;
  mpTime = container.getState().array() + container.getTimeIndex();

  mType = pDataEvent->getType();
  mFireAtInitialTime = pDataEvent->getFireAtInitialTime();
  mPersistentTrigger = pDataEvent->getPersistentTrigger();
  mDelayAssignment = pDataEvent->getDelayAssignment();

  // Compile Trigger
  success &= mTrigger.compile(pDataEvent, container);

  CAssignment * pAssignment = mAssignments.array();
  CAssignment * pAssignmentEnd = pAssignment + mAssignments.size();
  CCopasiVector< CEventAssignment >::const_iterator itAssignment = pDataEvent->getAssignments().begin();
  CCopasiVector< CEventAssignment >::const_iterator endAssignment = pDataEvent->getAssignments().end();

  mTargetValues.initialize(mAssignments.size(),
                           (C_FLOAT64 *) pAssignment->getAssignment()->getValuePointer());
  mTargetPointers.resize(mAssignments.size());
  C_FLOAT64 ** ppTarget = mTargetPointers.array();

  // Compile assignments.
  // Data events with assignments
  for (; pAssignment != pAssignmentEnd && itAssignment != endAssignment; ++pAssignment, ++itAssignment, ++ppTarget)
    {
      success &= pAssignment->compile(*itAssignment, container);
      *ppTarget = (C_FLOAT64 *) pAssignment->getTarget()->getValuePointer();
    }

  // Discontinuities
  for (; pAssignment != pAssignmentEnd; ++pAssignment, ++itAssignment, ++ppTarget)
    {
      *ppTarget = (C_FLOAT64 *) pAssignment->getTarget()->getValuePointer();
    }

  std::vector< CCopasiContainer * > ListOfContainer;

  // Compile the delay object.
  CExpression DelayExpression("DelayExpression", &container);
  success &= DelayExpression.setInfix(pDataEvent->getDelayExpression());
  success &= DelayExpression.compile(ListOfContainer);
  success &= mpDelay->setExpression(DelayExpression, container);

  // Compile the priority object.
  CExpression PriorityExpression("PriorityExpression", &container);
  success &= PriorityExpression.setInfix(pDataEvent->getPriorityExpression());
  success &= PriorityExpression.compile(ListOfContainer);
  success &= mpPriority->setExpression(PriorityExpression, container);

  return success;
}

void CMathEvent::createUpdateSequences()
{
  mEffectsSimulation = CMath::NoChange;

  const CObjectInterface::ObjectSet & StateValues = mpContainer->getStateObjects();
  const CObjectInterface::ObjectSet & SimulationValues = mpContainer->getSimulationUpToDateObjects();

  if (mDelayAssignment)
    {
      mCreateCalculationActionSequence.clear();
    }
  else
    {
      CObjectInterface::ObjectSet Requested;
      Requested.insert(mpDelay);
      mpContainer->getTransientDependencies().getUpdateSequence(mCreateCalculationActionSequence, CMath::Default, StateValues, Requested, SimulationValues);
    }

  CObjectInterface::ObjectSet Requested;

  if (mDelayAssignment)
    {
      Requested.insert(mpDelay);
    }

  CObjectInterface::ObjectSet EventTargets;
  const CAssignment * pAssignment = mAssignments.array();
  const CAssignment * pAssignmentEnd = pAssignment + mAssignments.size();

  for (; pAssignment != pAssignmentEnd; ++pAssignment)
    {
      Requested.insert(pAssignment->getAssignment());

      const CMathObject * pTarget = pAssignment->getTarget();
      EventTargets.insert(pTarget);

      if (StateValues.find(pTarget) != StateValues.end())
        {
          mEffectsSimulation |= CMath::State;
        }
    }

  mpContainer->getTransientDependencies().getUpdateSequence(mTargetValuesSequence, CMath::Default, StateValues, Requested, SimulationValues);

  // We need to add the total mass of the moieties to the state values.
  CObjectInterface::ObjectSet ExtendedStateValues = StateValues;
  const CMathObject * pTotalMass = mpContainer->getMathObject(mpContainer->getTotalMasses().array());
  const CMathObject * pTotalMassEnd = pTotalMass + mpContainer->getTotalMasses().size();

  for (; pTotalMass != pTotalMassEnd; ++pTotalMass)
    {
      ExtendedStateValues.insert(pTotalMass);
    }

  mpContainer->getTransientDependencies().getUpdateSequence(mPostAssignmentSequence, CMath::UpdateMoieties, EventTargets, ExtendedStateValues);

  // We need to remove the event roots from the simulation values
  CObjectInterface::ObjectSet ContinuousSimulationValues;
  CObjectInterface::ObjectSet DiscreteSimulationValues;
  CObjectInterface::ObjectSet::const_iterator it = SimulationValues.begin();
  CObjectInterface::ObjectSet::const_iterator end = SimulationValues.end();

  for (; it != end; ++it)
    {
      if (static_cast< const CMathObject * >(*it)->getEntityType() != CMath::Event)
        {
          ContinuousSimulationValues.insert(*it);
        }
      else
        {
          DiscreteSimulationValues.insert(*it);
        }
    }

  CObjectInterface::UpdateSequence StateEffects;
  mpContainer->getTransientDependencies().getUpdateSequence(StateEffects, CMath::Default, EventTargets, ExtendedStateValues);

  if (StateEffects.size() > 0)
    {
      mEffectsSimulation |= CMath::State;
    }

  CObjectInterface::UpdateSequence ContiousSimulationEffects;
  mpContainer->getTransientDependencies().getUpdateSequence(ContiousSimulationEffects, CMath::Default, EventTargets, ContinuousSimulationValues);

  if (ContiousSimulationEffects.size() > 0)
    {
      mEffectsSimulation |=  CMath::ContinuousSimulation;
    }

  CObjectInterface::UpdateSequence DiscreteSimulationEffects;
  mpContainer->getTransientDependencies().getUpdateSequence(DiscreteSimulationEffects, CMath::Default, EventTargets, DiscreteSimulationValues);

  if (DiscreteSimulationEffects.size() > 0)
    {
      mEffectsSimulation |=  CMath::EventSimulation;
    }
}

void CMathEvent::fire(const bool & equality)
{
  // Discontinuities have to be fired also when the trigger switches to false.

  if (mTrigger.isTrue() || mType == CEvent::Discontinuity)
    {
      if (mDelayAssignment)
        {
          mpContainer->getProcessQueue().addAssignment(getExecutionTime(), equality, getTargetValues(), this);
        }
      else
        {
          mpContainer->getProcessQueue().addCalculation(getCalculationTime(), equality, this);
        }
    }
  else if (mPersistentTrigger && mpPendingAction)
    {
      mpContainer->getProcessQueue().removeAction(*mpPendingAction);
      pdelete(mpPendingAction);
    }
}

void CMathEvent::addPendingAction(const CMathEventQueue::iterator & pendingAction)
{
  if (mPersistentTrigger)
    {
      assert(mpPendingAction == NULL);

      mpPendingAction = new std::pair< CMathEventQueue::CKey, CMathEventQueue::CAction >(pendingAction->first, pendingAction->second);
    }
}

void CMathEvent::removePendingAction()
{
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
  CMath::StateChange StateChange = CMath::NoChange;

  const C_FLOAT64 * pValue = values.array();
  const C_FLOAT64 * pValueEnd = pValue + values.size();
  C_FLOAT64 ** ppTarget = mTargetPointers.array();

  for (; pValue != pValueEnd; ++pValue, ++ppTarget)
    {
      if (**ppTarget != *pValue)
        {
          ValuesChanged = true;
          **ppTarget = *pValue;
        }
    }

  if (ValuesChanged || mType == CEvent::Discontinuity)
    {
      mpContainer->applyUpdateSequence(mPostAssignmentSequence);
      mpContainer->updateSimulatedValues(false);
      StateChange = mEffectsSimulation;
    }

  return StateChange;
}

CMath::StateChange CMathEvent::executeAssignment()
{
  return setTargetValues(getTargetValues());
}

const bool & CMathEvent::delayAssignment() const
{
  return mDelayAssignment;
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
  if (mDelayAssignment ||
      std::isnan(* (C_FLOAT64 *) mpDelay->getValuePointer()))
    {
      return *mpTime;
    }

  return *mpTime + * (C_FLOAT64 *) mpDelay->getValuePointer();
}

C_FLOAT64 CMathEvent::getExecutionTime() const
{
  if (!mDelayAssignment ||
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
