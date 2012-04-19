// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathEvent.cpp,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/04/19 14:34:39 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <limits>

#include "copasi.h"

#include "CMathEvent.h"
#include "CMathContainer.h"
#include "CMathExpression.h"

#include "model/CMathModel.h"
#include "model/CEvent.h"

#include "report/CCopasiRootContainer.h"

CMathEventN::CAssignment::CAssignment():
    mpTarget(NULL),
    mpAssignment(NULL)
{}

CMathEventN::CAssignment::~CAssignment()
{}

void CMathEventN::CAssignment::initialize(CMath::sPointers & pointers)
{
  // Initialize the assignment object
  mpAssignment = pointers.pEventAssignmentsObject;
  CMathObject::initialize(pointers.pEventAssignmentsObject, pointers.pEventAssignments,
                          CMath::EventAssignment, CMath::Event, CMath::SimulationTypeUndefined,
                          false, false, NULL);
}

bool CMathEventN::CAssignment::compile(CEventAssignment * pDataAssignment,
                                       CMathContainer & container)
{
  // A compiled pDataAssignment is prerequisite.
  bool success = true;

  // Determine the target object
  mpTarget = container.getMathObject(pDataAssignment->getTargetObject());

  if (mpTarget->getSimulationType() == CMath::Fixed)
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

bool CMathEventN::CAssignment::compileDiscontinuous(const CMathObject * pObject,
    CMathContainer & /* container */)
{
  bool success = true;

  mpTarget = const_cast< CMathObject * >(pObject);
  mpAssignment = const_cast< CMathObject * >(pObject);

  return success;
}

CMathEventN::CTrigger::CRoot::CRoot():
    mpRoot(NULL),
    mpRootState(NULL),
    mEquality(false),
    mDiscrete(false)
{}

CMathEventN::CTrigger::CRoot::~CRoot()
{}

void CMathEventN::CTrigger::CRoot::initialize(CMath::sPointers & pointers)
{
  // Initialize the root object!
  mpRoot = pointers.pEventRootsObject;
  CMathObject::initialize(pointers.pEventRootsObject, pointers.pEventRoots,
                          CMath::EventRoot, CMath::Event, CMath::SimulationTypeUndefined,
                          false, false, NULL);

  // Initialize the root state object!
  mpRootState = pointers.pEventRootStatesObject;
  CMathObject::initialize(pointers.pEventRootStatesObject, pointers.pEventRootStates,
                          CMath::EventRootState, CMath::Event, CMath::SimulationTypeUndefined,
                          false, false, NULL);


}

bool CMathEventN::CTrigger::CRoot::compile(CEvaluationNode * pRootNode,
    const bool & equality,
    CMathContainer & container)
{
  mEquality = equality;

  std::vector< CCopasiContainer * > ListOfContainer;
  ListOfContainer.push_back(const_cast< CMathContainer * >(&container));

  CMathExpression * pExpression = new CMathExpression("RootExpression", container);
  bool success = pExpression->setRoot(pRootNode);
  success &= mpRoot->setExpressionPtr(pExpression);

  // Compile the root state object
  CMathExpression * pStateExpression = new CMathExpression("RootStateExpression", container);

  CEvaluationNode * pStateExpressionNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::GT, "GT");
  pStateExpressionNode->addChild(new CEvaluationNodeObject((C_FLOAT64 *) mpRoot->getValuePointer()));
  pStateExpressionNode->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.5"));

  success &= pStateExpression->setRoot(pStateExpressionNode);
  success &= mpRootState->setExpressionPtr(pStateExpression);

  return success;
}

// static
CEvaluationNode * CMathEventN::CTrigger::CRoot::createTriggerExpressionNode() const
{
  return  new CEvaluationNodeObject((C_FLOAT64 *) mpRootState->getValuePointer());
}

CMathEventN::CTrigger::CTrigger():
    mpTrigger(NULL),
    mpInitialTrigger(NULL),
    mRoots(),
    mDualAction(false)
{}

CMathEventN::CTrigger::~CTrigger()
{}

void CMathEventN::CTrigger::allocate(const CEvent * pDataEvent,
                                     const CMathContainer & container)
{
  // Determine the number of roots.
  CMath::CVariableStack::StackElement Variables;
  CMath::CVariableStack::Buffer VariableBuffer;
  CMath::CVariableStack VariableStack(VariableBuffer);

  CMath::CAllocationStack::StackElement Allocations;
  CMath::CAllocationStack::Buffer AllocationBuffer;
  CMath::CAllocationStack AllocationStack(AllocationBuffer);

  std::vector< CCopasiContainer * > Container;
  Container.push_back(const_cast< CMathContainer * >(&container));

  CExpression Trigger("EventTrigger", &container);
  Trigger.setBooleanRequired(true);
  Trigger.setInfix(pDataEvent->getTriggerExpression());

  bool success = Trigger.compile();

  assert(success);

  mRoots.resize(countRoots(Trigger.getRoot(), VariableStack, AllocationStack));
}

void CMathEventN::CTrigger::allocateDiscontinuous(const size_t & nRoots,
    const CMathContainer & /* container */)
{
  mRoots.resize(nRoots);
}

void CMathEventN::CTrigger::initialize(CMath::sPointers & pointers)
{
  // Initialize trigger object.
  mpTrigger = pointers.pEventTriggersObject;
  CMathObject::initialize(pointers.pEventTriggersObject, pointers.pEventTriggers,
                          CMath::EventTrigger, CMath::Event, CMath::SimulationTypeUndefined,
                          false, false, NULL);

  // Initialize initial trigger object.
  mpInitialTrigger = pointers.pInitialEventTriggersObject;
  CMathObject::initialize(pointers.pInitialEventTriggersObject, pointers.pInitialEventTriggers,
                          CMath::EventTrigger, CMath::Event, CMath::SimulationTypeUndefined,
                          false, true, NULL);

  // Initialize root object.
  CRoot * pRoot = mRoots.array();
  CRoot * pRootEnd = pRoot + mRoots.size();

  for (; pRoot != pRootEnd; ++pRoot)
    {
      pRoot->initialize(pointers);
    }
}

bool CMathEventN::CTrigger::compile(CEvent * pDataEvent,
                                    CMathContainer & container)
{
  bool success = true;

  CMath::CVariableStack::Buffer Stack;
  CMath::CVariableStack VariableStack(Stack);

  std::vector< CCopasiContainer * > ListOfContainer;
  ListOfContainer.push_back(&container);

  CExpression DataTrigger("DataTrigger", &container);
  DataTrigger.setBooleanRequired(true);
  DataTrigger.setInfix(pDataEvent->getTriggerExpression());

  success &= DataTrigger.compile();

  CEvaluationNode * pTriggerRoot = NULL;
  CRoot * pRoot = mRoots.array();

  success &= compile(pTriggerRoot, DataTrigger.getRoot(), VariableStack, pRoot, container);

  assert(pRoot == mRoots.array() + mRoots.size());
  assert(VariableStack.size() == 0);

  CMathExpression * pTrigger = new CMathExpression("EventTrigger", container);
  success &= pTrigger->setRoot(pTriggerRoot);

  success &= mpTrigger->setExpressionPtr(pTrigger);

  mDualAction = false;

  return success;
}

bool CMathEventN::CTrigger::compileDiscontinuous(const CMathObject * pObject,
    CMathContainer & container)
{
  bool success = true;

  std::vector< CCopasiContainer * > ListOfContainer;
  ListOfContainer.push_back(const_cast< CMathContainer * >(&container));

  // The trigger depends on the root node of the expression of the
  // discontinuous object.
  CExpression DataTrigger("DataTrigger", &container);
  DataTrigger.setBooleanRequired(true);
  const CEvaluationNode * pNode = pObject->getExpressionPtr()->getRoot();

  switch ((int) pNode->getType())
    {
      case(CEvaluationNode::CHOICE | CEvaluationNodeChoice::IF):
      {
        success &= DataTrigger.setInfix(static_cast< const CEvaluationNode * >(pNode->getChild())->getInfix());
        mDualAction = true;

        // Modify discontinuous object expression.
        CMathObject * pMathObject = const_cast< CMathObject * >(pObject);
        CMathExpression * pMathExpression = const_cast< CMathExpression * >(pObject->getExpressionPtr());
        CEvaluationNode * pMathRoot = pMathExpression->getRoot();

        // We replace the conditional expression with the value of the trigger
        delete pMathRoot->getChild();
        success &= pMathRoot->addChild(new CEvaluationNodeObject((C_FLOAT64 *) mpTrigger->getValuePointer()), pMathRoot);

        success &= pMathExpression->compile();
        success &= pMathObject->compile(container);
      }

      break;

      case(CEvaluationNode::FUNCTION | CEvaluationNodeFunction::FLOOR):
      {
        const CEvaluationNode * pArg = static_cast< const CEvaluationNode * >(pNode->getChild());

        CEvaluationNode * pOR = new CEvaluationNodeLogical(CEvaluationNodeLogical::XOR, "XOR");

        CEvaluationNode * pLT = new CEvaluationNodeLogical(CEvaluationNodeLogical::LT, "LT");
        pLT->addChild(container.copyBranch(pArg, false));
        pLT->addChild(new CEvaluationNodeObject((C_FLOAT64 *) pObject->getValuePointer()));
        pOR->addChild(pLT);

        CEvaluationNode * pLE = new CEvaluationNodeLogical(CEvaluationNodeLogical::LE, "LE");

        CEvaluationNode * pPlus = new CEvaluationNodeOperator(CEvaluationNodeOperator::PLUS, "+");
        pPlus->addChild(new CEvaluationNodeObject((C_FLOAT64 *) pObject->getValuePointer()));
        pPlus->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0"));
        pLE->addChild(pPlus);

        pLE->addChild(container.copyBranch(pArg, false));
        pOR->addChild(pLE);

        success &= DataTrigger.setRoot(pOR);
        success &= DataTrigger.updateTree();
        mDualAction = false;
      }
      break;

      case(CEvaluationNode::FUNCTION | CEvaluationNodeFunction::CEIL):
      {
        const CEvaluationNode * pArg = static_cast< const CEvaluationNode * >(pNode->getChild());

        CEvaluationNode * pOR = new CEvaluationNodeLogical(CEvaluationNodeLogical::XOR, "XOR");

        CEvaluationNode * pLE = new CEvaluationNodeLogical(CEvaluationNodeLogical::LE, "LE");
        pLE->addChild(container.copyBranch(pArg, false));

        CEvaluationNode * pMinus = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
        pMinus->addChild(new CEvaluationNodeObject((C_FLOAT64 *) pObject->getValuePointer()));
        pMinus->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0"));
        pLE->addChild(pMinus);

        pOR->addChild(pLE);

        CEvaluationNode * pLT = new CEvaluationNodeLogical(CEvaluationNodeLogical::LT, "LT");
        pLT->addChild(new CEvaluationNodeObject((C_FLOAT64 *) pObject->getValuePointer()));
        pLT->addChild(container.copyBranch(pArg, false));
        pOR->addChild(pLT);

        success &= DataTrigger.setRoot(pOR);
        success &= DataTrigger.updateTree();
        mDualAction = false;
      }
      break;

      default:
        success = false;
        break;
    }

  success &= DataTrigger.compile(ListOfContainer);

  CEvaluationNode * pTriggerRoot = NULL;
  CRoot * pRoot = mRoots.array();

  CMath::CVariableStack::Buffer Stack;
  CMath::CVariableStack VariableStack(Stack);

  success &= compile(pTriggerRoot, DataTrigger.getRoot(), VariableStack, pRoot, container);

  assert(pRoot == mRoots.array() + mRoots.size());
  assert(VariableStack.size() == 0);

  CMathExpression * pTrigger = new CMathExpression("EventTrigger", container);
  success &= pTrigger->setRoot(pTriggerRoot);
  success &= mpTrigger->setExpressionPtr(pTrigger);


  return success;
}

const CVector< CMathEventN::CTrigger::CRoot > & CMathEventN::CTrigger::getRoots() const
{
  return mRoots;
}

// static
size_t CMathEventN::CTrigger::countRoots(const CEvaluationNode * pNode,
    CMath::CVariableStack & variableStack,
    CMath::CAllocationStack & allocationStack)
{
  const CEvaluationNode::Type & Type = pNode->getType();

  switch (CEvaluationNode::type(Type))
    {
      case CEvaluationNode::LOGICAL:

        switch ((int) CEvaluationNode::subType(Type))
          {
            case CEvaluationNodeLogical::EQ:
            case CEvaluationNodeLogical::NE:
              return countRootsEQ(pNode, variableStack, allocationStack);
              break;

            case CEvaluationNodeLogical::LE:
            case CEvaluationNodeLogical::LT:
            case CEvaluationNodeLogical::GE:
            case CEvaluationNodeLogical::GT:
              return countRootsLE(pNode, variableStack, allocationStack);
              break;

            default:
              break;
          }

        break;

      case CEvaluationNode::CALL:

        switch ((int) CEvaluationNode::subType(Type))
          {
            case CEvaluationNodeCall::FUNCTION:
            case CEvaluationNodeCall::EXPRESSION:
              return countRootsFUNCTION(pNode, variableStack, allocationStack);
              break;

            default:
              break;
          }

        break;

      case CEvaluationNode::VARIABLE:

        switch ((int) CEvaluationNode::subType(Type))
          {
            case CEvaluationNodeVariable::ANY:
              return countRootsVARIABLE(pNode, variableStack, allocationStack);
              break;

            default:
              break;
          }

        break;

      default:
        break;
    }

  size_t nRoots = 0;
  const CEvaluationNode * pChild =
    static_cast< const CEvaluationNode * >(pNode->getChild());

  while (pChild != NULL)
    {
      nRoots += countRoots(pChild, variableStack, allocationStack);
      pChild = static_cast< const CEvaluationNode * >(pChild->getSibling());
    }

  return nRoots;
}

// static
size_t CMathEventN::CTrigger::countRootsEQ(const CEvaluationNode * pNode,
    CMath::CVariableStack & variableStack,
    CMath::CAllocationStack & allocationStack)
{
  size_t nRoots = 0;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pNode->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  nRoots += countRoots(pLeft, variableStack, allocationStack);
  nRoots += countRoots(pRight, variableStack, allocationStack);

  // Equality can be determined between Boolean and double values.
  if (CEvaluationNode::type(pLeft->getType()) != CEvaluationNode::LOGICAL)
    {
      // We treat x EQ y as (x GE y) AND (y GE x)
      nRoots *= 2; // Left and right roots are duplicated
      nRoots += 2; // add both GE comparisons.
    }

  return nRoots;
}

// static
size_t CMathEventN::CTrigger::countRootsLE(const CEvaluationNode * pNode,
    CMath::CVariableStack & variableStack,
    CMath::CAllocationStack & allocationStack)
{
  size_t nRoots = 0;

  const CEvaluationNode * pLeft = static_cast<const CEvaluationNode *>(pNode->getChild());
  const CEvaluationNode * pRight = static_cast<const CEvaluationNode *>(pLeft->getSibling());

  nRoots += countRoots(pLeft, variableStack, allocationStack);
  nRoots += countRoots(pRight, variableStack, allocationStack);

  nRoots += 1;

  return nRoots;
}

// static
size_t CMathEventN::CTrigger::countRootsFUNCTION(const CEvaluationNode * pNode,
    CMath::CVariableStack & variableStack,
    CMath::CAllocationStack & allocationStack)
{
  // We need to mimic the process in CMathContainer::copyBranch;
  CMath::CVariableStack::StackElement Variables;

  const CEvaluationNode * pChild =
    static_cast< const CEvaluationNode * >(pNode->getChild());

  // We create temporary copies in which the discontinuous nodes are not replaced.
  while (pChild != NULL)
    {
      // TODO CRITICAL We should count the roots of each variable here instead when the
      // variable is used as the later may duplicate roots.
      Variables.push_back(pChild);
      pChild = static_cast< const CEvaluationNode * >(pChild->getSibling());
    }

  variableStack.push(Variables);

  const CEvaluationNode * pTreeRoot =
    static_cast< const CEvaluationNodeCall * >(pNode)->getCalledTree()->getRoot();

  size_t nRoots = countRoots(pTreeRoot, variableStack, allocationStack);

  variableStack.pop();

  return nRoots;
}

// static
size_t CMathEventN::CTrigger::countRootsVARIABLE(const CEvaluationNode * pNode,
    CMath::CVariableStack & variableStack,
    CMath::CAllocationStack & allocationStack)
{
  size_t Index =
    static_cast< const CEvaluationNodeVariable * >(pNode)->getIndex();

  const CEvaluationNode * pVariableNode = variableStack[Index];

  return countRoots(pVariableNode, variableStack, allocationStack);
}

// static
bool CMathEventN::CTrigger::compile(CEvaluationNode *& pTriggerNode,
                                    const CEvaluationNode * pDataNode,
                                    CMath::CVariableStack & variableStack,
                                    CMathEventN::CTrigger::CRoot *& pRoot,
                                    CMathContainer & container)
{
  bool success = true;

  switch ((int) pDataNode->getType())
    {
      case(CEvaluationNode::LOGICAL | CEvaluationNodeLogical::AND):
      case(CEvaluationNode::LOGICAL | CEvaluationNodeLogical::OR):
      case(CEvaluationNode::LOGICAL | CEvaluationNodeLogical::XOR):
        return compileAND(pTriggerNode, pDataNode, variableStack, pRoot, container);
        break;

      case(CEvaluationNode::LOGICAL | CEvaluationNodeLogical::EQ):
        return compileEQ(pTriggerNode, pDataNode, variableStack, pRoot, container);
        break;

      case(CEvaluationNode::LOGICAL | CEvaluationNodeLogical::NE):
        return compileNE(pTriggerNode, pDataNode, variableStack, pRoot, container);
        break;

      case(CEvaluationNode::LOGICAL | CEvaluationNodeLogical::LE):
      case(CEvaluationNode::LOGICAL | CEvaluationNodeLogical::LT):
      case(CEvaluationNode::LOGICAL | CEvaluationNodeLogical::GE):
      case(CEvaluationNode::LOGICAL | CEvaluationNodeLogical::GT):
        return compileLE(pTriggerNode, pDataNode, variableStack, pRoot, container);
        break;

      case(CEvaluationNode::FUNCTION | CEvaluationNodeFunction::NOT):
        return compileNOT(pTriggerNode, pDataNode, variableStack, pRoot, container);
        break;

      case(CEvaluationNode::CALL | CEvaluationNodeCall::FUNCTION):
      case(CEvaluationNode::CALL | CEvaluationNodeCall::EXPRESSION):
        return compileFUNCTION(pTriggerNode, pDataNode, variableStack, pRoot, container);
        break;

      case(CEvaluationNode::VARIABLE | CEvaluationNodeVariable::ANY):
        return compileVARIABLE(pTriggerNode, pDataNode, variableStack, pRoot, container);
        break;

      case(CEvaluationNode::CONSTANT | CEvaluationNodeConstant::TRUE):
      case(CEvaluationNode::CONSTANT | CEvaluationNodeConstant::FALSE):
        return compileCONSTANT(pTriggerNode, pDataNode, variableStack, pRoot, container);
        break;

      default:
        assert(false);
        break;
    }

  return success;
}

// static
bool CMathEventN::CTrigger::compileAND(CEvaluationNode *& pTriggerNode,
                                       const CEvaluationNode * pDataNode,
                                       CMath::CVariableStack & variableStack,
                                       CMathEventN::CTrigger::CRoot *& pRoot,
                                       CMathContainer & container)
{
  bool success = true;

  const CEvaluationNode * pDataLeft = static_cast<const CEvaluationNode *>(pDataNode->getChild());
  const CEvaluationNode * pDataRight = static_cast<const CEvaluationNode *>(pDataLeft->getSibling());

  CEvaluationNode * pTriggerLeft = NULL;
  success &= compile(pTriggerLeft, pDataLeft, variableStack, pRoot, container);

  CEvaluationNode * pTriggerRight = NULL;
  success &= compile(pTriggerRight, pDataRight, variableStack, pRoot, container);

  switch ((int) CEvaluationNode::subType(pDataNode->getType()))
    {
      case CEvaluationNodeLogical::AND:
        pTriggerNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
        break;

      case CEvaluationNodeLogical::OR:
        pTriggerNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::OR, "OR");
        break;

      case CEvaluationNodeLogical::XOR:
        pTriggerNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::XOR, "XOR");
        break;

      default:
        success = false;
        break;
    }

  if (pTriggerNode != NULL)
    {
      pTriggerNode->addChild(pTriggerLeft);
      pTriggerNode->addChild(pTriggerRight);
    }

  return success;
}

// static
bool CMathEventN::CTrigger::compileEQ(CEvaluationNode *& pTriggerNode,
                                      const CEvaluationNode * pDataNode,
                                      CMath::CVariableStack & variableStack,
                                      CMathEventN::CTrigger::CRoot *& pRoot,
                                      CMathContainer & container)
{
  bool success = true;

  const CEvaluationNode * pDataLeft = static_cast<const CEvaluationNode *>(pDataNode->getChild());
  const CEvaluationNode * pDataRight = static_cast<const CEvaluationNode *>(pDataLeft->getSibling());

  // Equality can be determined between Boolean and double values.
  if (CEvaluationNode::type(pDataLeft->getType()) != CEvaluationNode::LOGICAL)
    {
      // We treat x EQ y as (x GE y) AND (y GE x)

      // Create a temporary expression and compile it.
      CEvaluationNode * pAND = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
      CEvaluationNode * pGELeft = new CEvaluationNodeLogical(CEvaluationNodeLogical::GE, "GE");
      pGELeft->addChild(pDataLeft->copyBranch());
      pGELeft->addChild(pDataRight->copyBranch());
      pAND->addChild(pGELeft);

      CEvaluationNode * pGERight = new CEvaluationNodeLogical(CEvaluationNodeLogical::GE, "GE");
      pGERight->addChild(pDataRight->copyBranch());
      pGERight->addChild(pDataLeft->copyBranch());
      pAND->addChild(pGERight);

      success &= compileAND(pTriggerNode, pAND, variableStack, pRoot, container);

      // Delete the temporary
      pdelete(pAND);
    }
  else
    {
      CEvaluationNode * pTriggerLeft = NULL;
      success &= compile(pTriggerLeft, pDataLeft, variableStack, pRoot, container);

      CEvaluationNode * pTriggerRight = NULL;
      success &= compile(pTriggerRight, pDataRight, variableStack, pRoot, container);


      pTriggerNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::EQ, "EQ");
      pTriggerNode->addChild(pTriggerLeft);
      pTriggerNode->addChild(pTriggerRight);
    }

  return success;
}

// static
bool CMathEventN::CTrigger::compileNE(CEvaluationNode *& pTriggerNode,
                                      const CEvaluationNode * pDataNode,
                                      CMath::CVariableStack & variableStack,
                                      CMathEventN::CTrigger::CRoot *& pRoot,
                                      CMathContainer & container)
{
  bool success = true;

  const CEvaluationNode * pDataLeft = static_cast<const CEvaluationNode *>(pDataNode->getChild());
  const CEvaluationNode * pDataRight = static_cast<const CEvaluationNode *>(pDataLeft->getSibling());

  // We treat this as NOT and EQ.
  // For this we create a modified copy of the current node.

  CEvaluationNode * pNotNode = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
  CEvaluationNode * pEqNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::EQ, "EQ");

  pEqNode->addChild(pDataLeft->copyBranch());
  pEqNode->addChild(pDataRight->copyBranch());

  pNotNode->addChild(pEqNode);

  success &= compileNOT(pTriggerNode, pNotNode, variableStack, pRoot, container);

  // Delete the temporary
  pdelete(pNotNode);

  return success;
}

// static
bool CMathEventN::CTrigger::compileLE(CEvaluationNode *& pTriggerNode,
                                      const CEvaluationNode * pDataNode,
                                      CMath::CVariableStack & variableStack,
                                      CMathEventN::CTrigger::CRoot *& pRoot,
                                      CMathContainer & container)
{
  bool success = true;

  const CEvaluationNode * pDataLeft = static_cast<const CEvaluationNode *>(pDataNode->getChild());
  const CEvaluationNode * pDataRight = static_cast<const CEvaluationNode *>(pDataLeft->getSibling());

  // We need to compile the root finding structure
  // Create a root expression
  CEvaluationNode * pRootNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");

  bool Equality = false;

  // We need to create a copy the left and right data nodes with the variables being replaced.
  switch ((int) CEvaluationNode::subType(pDataNode->getType()))
    {
      case CEvaluationNodeLogical::LE:
        pRootNode->addChild(container.copyBranch(pDataRight, variableStack, true));
        pRootNode->addChild(container.copyBranch(pDataLeft, variableStack, true));
        Equality = true;
        break;

      case CEvaluationNodeLogical::LT:
        pRootNode->addChild(container.copyBranch(pDataRight, variableStack, true));
        pRootNode->addChild(container.copyBranch(pDataLeft, variableStack, true));
        Equality = false;
        break;

      case CEvaluationNodeLogical::GE:
        pRootNode->addChild(container.copyBranch(pDataLeft, variableStack, true));
        pRootNode->addChild(container.copyBranch(pDataRight, variableStack, true));
        Equality = true;
        break;

      case CEvaluationNodeLogical::GT:
        pRootNode->addChild(container.copyBranch(pDataLeft, variableStack, true));
        pRootNode->addChild(container.copyBranch(pDataRight, variableStack, true));
        Equality = false;
        break;
    }

  success &= pRoot->compile(pRootNode, Equality, container);
  pTriggerNode = pRoot->createTriggerExpressionNode();
  pRoot++;

  // We do not need to delete pRootNode as CRoot::compile takes car of it.

  return success;
}

// static
bool CMathEventN::CTrigger::compileNOT(CEvaluationNode *& pTriggerNode,
                                       const CEvaluationNode * pDataNode,
                                       CMath::CVariableStack & variableStack,
                                       CMathEventN::CTrigger::CRoot *& pRoot,
                                       CMathContainer & container)
{
  bool success = true;

  const CEvaluationNode * pData = static_cast<const CEvaluationNode *>(pDataNode->getChild());

  CEvaluationNode * pTrigger = NULL;
  success &= compile(pTrigger, pData, variableStack, pRoot, container);

  pTriggerNode = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
  pTriggerNode->addChild(pTrigger);

  return success;
}

// static
bool CMathEventN::CTrigger::compileFUNCTION(CEvaluationNode *& pTriggerNode,
    const CEvaluationNode * pDataNode,
    CMath::CVariableStack & variableStack,
    CMathEventN::CTrigger::CRoot *& pRoot,
    CMathContainer & container)
{
  if (!pDataNode->isBoolean())
    return false;

  // We need to mimic the process in CMathContainer::copyBranch;

  CMath::CVariableStack::StackElement Variables;

  const CEvaluationNode * pChild =
    static_cast< const CEvaluationNode * >(pDataNode->getChild());

  // We create temporary copies in which the discontinuous nodes are not replaced.
  while (pChild != NULL)
    {
      Variables.push_back(container.copyBranch(pChild, variableStack, false));
      pChild = static_cast< const CEvaluationNode * >(pChild->getSibling());
    }

  variableStack.push(Variables);

  const CEvaluationNode * pCalledNode =
    static_cast< const CEvaluationNodeCall * >(pDataNode)->getCalledTree()->getRoot();

  bool success = compile(pTriggerNode, pCalledNode, variableStack, pRoot, container);

  variableStack.pop();

  CMath::CVariableStack::StackElement::iterator itVariable = Variables.begin();
  CMath::CVariableStack::StackElement::iterator endVariable = Variables.end();

  // Delete temporary copies.
  for (; itVariable != endVariable; ++itVariable)
    {
      pdelete(*itVariable);
    }

  return success;
}

// static
bool CMathEventN::CTrigger::compileVARIABLE(CEvaluationNode *& pTriggerNode,
    const CEvaluationNode * pDataNode,
    CMath::CVariableStack & variableStack,
    CMathEventN::CTrigger::CRoot *& pRoot,
    CMathContainer & container)
{
  // We need to mimic the process in CMathContainer::copyBranch;

  size_t Index =
    static_cast< const CEvaluationNodeVariable * >(pDataNode)->getIndex();

  const CEvaluationNode * pIndexedNode = variableStack[Index];

  if (!pIndexedNode->isBoolean())
    return false;

  return compile(pTriggerNode, pIndexedNode, variableStack, pRoot, container);
}

// static
bool CMathEventN::CTrigger::compileCONSTANT(CEvaluationNode *& pTriggerNode,
    const CEvaluationNode * pDataNode,
    CMath::CVariableStack & /* variableStack */,
    CMathEventN::CTrigger::CRoot *& pRoot,
    CMathContainer & container)
{
  bool success = true;

  CEvaluationNode * pRootNode = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");

  switch ((int) CEvaluationNode::subType(pDataNode->getType()))
    {
      case CEvaluationNodeConstant::TRUE:
        pTriggerNode = new CEvaluationNodeConstant(CEvaluationNodeConstant::TRUE, "TRUE");
        break;

      case CEvaluationNodeConstant::FALSE:
        pTriggerNode = new CEvaluationNodeConstant(CEvaluationNodeConstant::FALSE, "FALSE");
        break;
    }

  success &= pRoot->compile(pRootNode, true, container);
  pRoot++;

  return success;
}

// static
void CMathEventN::allocate(CMathEventN * pEvent,
                           const CEvent * pDataEvent,
                           const CMathContainer & container)
{
  pEvent->mTrigger.allocate(pDataEvent, container);
  pEvent->mAssignments.resize(pDataEvent->getAssignments().size());
}

// static
void CMathEventN::allocateDiscontinuous(CMathEventN * pEvent,
                                        const size_t & nRoots,
                                        const CMathContainer & container)
{
  pEvent->mTrigger.allocateDiscontinuous(nRoots, container);
  pEvent->mAssignments.resize(1);
}

CMathEventN::CMathEventN():
    mTrigger(),
    mAssignments(),
    mpDelay(NULL),
    mpPriority(NULL),
    mFireAtInitialTime(false),
    mPersistentTrigger(false),
    mDelayAssignment(true)
{}

/**
 * Destructor
 */
CMathEventN::~CMathEventN()
{}

const CMathEventN::CTrigger & CMathEventN::getTrigger() const
{
  return mTrigger;
}

void CMathEventN::initialize(CMath::sPointers & pointers)
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

bool CMathEventN::compile(CEvent * pDataEvent,
                          CMathContainer & container)
{
  bool success = true;

  mFireAtInitialTime = pDataEvent->getFireAtInitialTime();
  mPersistentTrigger = pDataEvent->getPersistentTrigger();
  mDelayAssignment = pDataEvent->getDelayAssignment();

  // Compile Trigger
  success &= mTrigger.compile(pDataEvent, container);

  CAssignment * pAssignment = mAssignments.array();
  CAssignment * pAssignmentEnd = pAssignment + mAssignments.size();
  CCopasiVector< CEventAssignment >::const_iterator itAssignment = pDataEvent->getAssignments().begin();

  // Compile assignments.
  for (; pAssignment != pAssignmentEnd; ++pAssignment, ++itAssignment)
    {
      success &= pAssignment->compile(*itAssignment, container);
    }

  std::vector< CCopasiContainer * > ListOfContainer;
  ListOfContainer.push_back(const_cast< CMathContainer * >(&container));

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

bool CMathEventN::compileDiscontinuous(const CMathObject * pObject,
                                       CMathContainer & container)
{
  bool success = true;

  mFireAtInitialTime = false;
  mPersistentTrigger = false;
  mDelayAssignment = false;

  // Compile Trigger
  success &= mTrigger.compileDiscontinuous(pObject, container);

  // Compile assignments.
  success &= mAssignments[0].compileDiscontinuous(pObject, container);

  // Compile the delay object.
  CExpression DelayExpression("DelayExpression", &container);
  success &= DelayExpression.setInfix("");
  success &= mpDelay->setExpression(DelayExpression, container);

  // Compile the priority object.
  CExpression PriorityExpression("PriorityExpression", &container);
  success &= PriorityExpression.setInfix("");
  success &= mpPriority->setExpression(PriorityExpression, container);

  return success;
}


const CVector< CMathEventN::CAssignment > & CMathEventN::getAssignments() const
{
  return mAssignments;
}

CMathEvent::CAssignment::CAssignment(const CCopasiContainer * pParent) :
    CCopasiContainer("MathEventAssignment", pParent),
    mpTarget(NULL),
    mExpression("Expression", this)
{}

CMathEvent::CAssignment::CAssignment(const CMathEvent::CAssignment & src,
                                     const CCopasiContainer * pParent) :
    CCopasiContainer(src, pParent),
    mpTarget(src.mpTarget),
    mExpression(src.mExpression, this)
{}

CMathEvent::CAssignment::~CAssignment()
{}

bool CMathEvent::CAssignment::compile(const CEventAssignment * pAssignment,
                                      std::vector< CCopasiContainer * > listOfContainer)
{
  if (pAssignment == NULL)
    return false;

  bool success = true;

  mpTarget = NULL;

  if (pAssignment->getTargetObject() != NULL)
    {
      mpTarget = (C_FLOAT64 *) pAssignment->getTargetObject()->getValuePointer();
    }

  if (mpTarget == NULL)
    success = false;

  success &= mExpression.setInfix(pAssignment->getExpression());
  success &= mExpression.compile(listOfContainer);

  setDirectDependencies(mExpression.getDirectDependencies());

  return success;
}

CMathEvent::CMathEvent(const CCopasiContainer * pParent) :
    CCopasiContainer("MathEvent", pParent, "MathEvent"),
    mTrigger(this),
    mOrder(false),
    mHaveDelay(false),
    mDelay("DelayExpression", this),
    mDelayAssignment(true),
    mAssignments("ListOfMathEventAssignment", this),
    mDelayValueRefreshes(),
    mAssignmentValueRefreshes(),
    mDependentValueRefreshes()
{}

CMathEvent::CMathEvent(const CMathEvent & src,
                       const CCopasiContainer * pParent) :
    CCopasiContainer(src, pParent),
    mTrigger(src.mTrigger, this),
    mOrder(src.mOrder),
    mHaveDelay(src.mHaveDelay),
    mDelay(src.mDelay, this),
    mDelayAssignment(src.mDelayAssignment),
    mAssignments(src.mAssignments, this),
    mDelayValueRefreshes(src.mDelayValueRefreshes),
    mAssignmentValueRefreshes(src.mAssignmentValueRefreshes),
    mDependentValueRefreshes(src.mDependentValueRefreshes)
{}

CMathEvent::~CMathEvent()
{}

bool CMathEvent::compile(const CEvent * pEvent,
                         std::vector< CCopasiContainer * > listOfContainer)
{
  // A CMathEvent must be part of CMathModel to be compiled.
  CMathModel * pMathModel = dynamic_cast< CMathModel *>(getObjectAncestor("CMathModel"));

  if (pMathModel == NULL)
    return false;

  bool success = true;

  success &= mTrigger.compile(pEvent->getTriggerExpressionPtr(), listOfContainer);

  success &= mDelay.setInfix(pEvent->getDelayExpression());
  success &= mDelay.compile(listOfContainer);

  mHaveDelay = (mDelay.getInfix() != "");

  // Build the list of refresh calls needed to assure that the delay expression
  // can be calculated.

  mDelayValueRefreshes = pMathModel->buildRequiredRefreshList(mDelay.getDirectDependencies());

  mDelayAssignment = pEvent->getDelayAssignment();

  mAssignments.clear();

  CCopasiVectorN< CEventAssignment >::const_iterator it = pEvent->getAssignments().begin();
  CCopasiVectorN< CEventAssignment >::const_iterator end = pEvent->getAssignments().end();

  std::set< const CCopasiObject * > Assignments;
  std::set< const CCopasiObject * > Targets;

  for (; it != end; ++it)
    {
      CAssignment * pAssignment = new CAssignment();

      mAssignments.add(pAssignment, true);
      success &= pAssignment->compile(*it, listOfContainer);

      Assignments.insert(pAssignment);
      Targets.insert((*it)->getTargetObject());
    }

  // Build the list of refresh calls needed to assure that the assignment expressions
  // can be calculated.
  mAssignmentValueRefreshes = pMathModel->buildRequiredRefreshList(Assignments);

  // Build the list of refresh calls needed to assure that all dependent model values
  // are updated after the assignments are executed.
  mDependentValueRefreshes = pMathModel->buildDependendRefreshList(Targets);

  return success;
}

void CMathEvent::fire(const C_FLOAT64 & time,
                      const bool & equality,
                      CProcessQueue & processQueue)
{
  size_t EventId = processQueue.createEventId();

  // Add each assignment to the calculation queue
  CCopasiVector< CAssignment >::iterator itAssignment = mAssignments.begin();
  CCopasiVector< CAssignment >::iterator endAssignment = mAssignments.end();

  // Determine the execution time of the calculation of the event.
  C_FLOAT64 CalculationTime = getCalculationTime(time);

  // We can only add calculations even if the calculation time is the current time.
  // This is due to the fact that equality and inequality checks are treated differently.
  for (; itAssignment != endAssignment; ++itAssignment)
    {
      // We must delay the calculation of the new target value
      processQueue.addCalculation(CalculationTime,
                                  equality,
                                  mOrder,
                                  EventId,
                                  (*itAssignment)->mpTarget,
                                  &(*itAssignment)->mExpression,
                                  this);
    }
}

void CMathEvent::applyDelayRefreshes()
{
  std::vector< Refresh * >::const_iterator itRefresh = mDelayValueRefreshes.begin();
  std::vector< Refresh * >::const_iterator endRefresh = mDelayValueRefreshes.end();

  while (itRefresh != endRefresh)
    (**itRefresh++)();

  return;
}

void CMathEvent::applyValueRefreshes()
{
  std::vector< Refresh * >::const_iterator itRefresh = mAssignmentValueRefreshes.begin();
  std::vector< Refresh * >::const_iterator endRefresh = mAssignmentValueRefreshes.end();

  while (itRefresh != endRefresh)
    (**itRefresh++)();

  return;
}

void CMathEvent::applyDependentRefreshes()
{
  std::vector< Refresh * >::const_iterator itRefresh = mDependentValueRefreshes.begin();
  std::vector< Refresh * >::const_iterator endRefresh = mDependentValueRefreshes.end();

  while (itRefresh != endRefresh)
    (**itRefresh++)();

  return;
}

CMathTrigger & CMathEvent::getMathTrigger()
{
  return mTrigger;
}

const size_t & CMathEvent::getOrder() const
{
  return mOrder;
}

C_FLOAT64 CMathEvent::getCalculationTime(const C_FLOAT64 & currentTime)
{
  if (mDelayAssignment)
    {
      return currentTime;
    }

  return calculateDelayedTime(currentTime);
}

C_FLOAT64 CMathEvent::getAssignmentTime(const C_FLOAT64 & currentTime)
{
  if (!mDelayAssignment)
    {
      return currentTime;
    }

  return calculateDelayedTime(currentTime);
}

C_FLOAT64 CMathEvent::calculateDelayedTime(const C_FLOAT64 & currentTime)
{
  if (mDelay.getInfix() == "")
    {
      return currentTime;
    }

  // We make sure everything is up to date.
  applyDelayRefreshes();

  C_FLOAT64 DelayedTime = currentTime + mDelay.calcValue();

  // Events are only allowed in forward integration. Thus the ExecutionTime
  // must not be less than the time.
  if (DelayedTime - currentTime < 0.0)
    {
      // We allow small numerical errors.
      C_FLOAT64 Scale =
        (fabs(DelayedTime) + fabs(currentTime)) * 50.0 * std::numeric_limits< C_FLOAT64 >::epsilon();

      // Both are approximately zero
      if (Scale < 100.0 * std::numeric_limits< C_FLOAT64 >::min())
        {
          DelayedTime = currentTime;
        }
      // The difference is small compared to the scale
      else if (fabs(DelayedTime - currentTime) < Scale)
        {
          DelayedTime = currentTime;
        }
      // The execution time is definitely in the past
      else
        {
          // Create an error message and throw an exception.
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCMathModel + 2, DelayedTime, currentTime);
        }
    }

  return DelayedTime;
}
