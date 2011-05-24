// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathExpression.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/24 16:32:32 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMathExpression.h"
#include "CMathContainer.h"

#include "function/CExpression.h"
#include "function/CFunction.h"
#include "function/CEvaluationNode.h"
#include "function/CEvaluationNodeObject.h"

#define mpContainer static_cast< const CMathContainer * >(getObjectParent())

CMathExpression::CMathExpression():
    CEvaluationTree(),
    mPrerequisites()
{}

CMathExpression::CMathExpression(const std::string & name,
                                 CMathContainer & container):
    CEvaluationTree(name, &container, CEvaluationTree::MathExpression),
    mPrerequisites()
{}

CMathExpression::CMathExpression(const CExpression & src,
                                 CMathContainer & container,
                                 const bool & replaceDiscontinuousNodes):
    CEvaluationTree(src.getObjectName(), &container, CEvaluationTree::MathExpression),
    mPrerequisites()
{
  std::vector< std::vector< const CEvaluationNode * > > Variables;

  // Create a converted copy of the existing expression tree.
  mpRoot = container.copyBranch(src.getRoot(), replaceDiscontinuousNodes);

  compile();
}

CMathExpression::CMathExpression(const CFunction & src,
                                 const CCallParameters< C_FLOAT64 > & callParameters,
                                 CMathContainer & container,
                                 const bool & replaceDiscontinuousNodes):
    CEvaluationTree(src.getObjectName(), &container, CEvaluationTree::MathExpression),
    mPrerequisites()
{
  // Deal with the different function types
  switch (src.getType())
    {
      case CEvaluationTree::Function:
      case CEvaluationTree::PreDefined:
      case CEvaluationTree::UserDefined:
      {
        std::cout << src.getObjectName() << ": " << src.getInfix() << std::endl;

        // Create a vector of CEvaluationNodeObject for each variable
        CMath::CVariableStack::StackElement CallParameters;
        CCallParameters< C_FLOAT64 >::const_iterator it = callParameters.begin();
        CCallParameters< C_FLOAT64 >::const_iterator end = callParameters.end();

        for (; it != end; ++it)
          {
            CallParameters.push_back(createNodeFromValue(it->value));
          }

        CMath::CVariableStack::Buffer Stack;
        CMath::CVariableStack VariableStack(Stack);

        VariableStack.push(CallParameters);

        // Create a converted copy of the existing expression tree.
        mpRoot = container.copyBranch(src.getRoot(), VariableStack, replaceDiscontinuousNodes);

        VariableStack.pop();

        CMath::CVariableStack::StackElement::iterator itVar = CallParameters.begin();
        CMath::CVariableStack::StackElement::iterator endVar = CallParameters.end();

        for (; itVar != endVar; ++itVar)
          {
            delete *itVar;
          }
      }

      break;

      case CEvaluationTree::MassAction:
      {
        // We build a mass action expression based on the call parameters.
        CCallParameters< C_FLOAT64 >::const_iterator it = callParameters.begin();

        // We always have reactants
        const C_FLOAT64 * pK = it->value;
        ++it;
        const CCallParameters< C_FLOAT64 > * pSpecies = it->vector;
        ++it;

        CEvaluationNode * pPart = createMassActionPart(pK, pSpecies);

        if (it != callParameters.end())
          {
            mpRoot = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
            mpRoot->addChild(pPart);

            pK = it->value;
            ++it;
            pSpecies = it->vector;
            ++it;

            pPart = createMassActionPart(pK, pSpecies);

            mpRoot->addChild(pPart);
          }
        else
          {
            mpRoot = pPart;
          }
      }
      break;

      case CEvaluationTree::MathExpression:
      case CEvaluationTree::Expression:
        // This cannot happen and is only here to satisfy the compiler.
        break;
    }

  compile();
}

// virtual
CMathExpression::~CMathExpression()
{}

const C_FLOAT64 & CMathExpression::value() const
{
  return mpRoot->value();
}

// virtual
const CObjectInterface::ObjectSet & CMathExpression::getPrerequisites() const
{
  return mPrerequisites;
}

// virtual
bool CMathExpression::compile()
{
  mPrerequisites.clear();
  mUsable = true;

  updateTree();

  std::vector< CEvaluationNode * >::iterator it = mpNodeList->begin();
  std::vector< CEvaluationNode * >::iterator end = mpNodeList->end();

  for (; it != end; ++it)
    {
      mUsable &= (*it)->compile(this);

      if ((*it)->getType() == (CEvaluationNode::OBJECT | CEvaluationNodeObject::POINTER))
        {
          std::istringstream Value;
          void * pValue;
          Value.str((*it)->getData().substr(2));
          Value.flags(std::ios::right | std::ios::hex | std::ios::showbase);
          Value >> pValue;

          mPrerequisites.insert(mpContainer->getMathObject((C_FLOAT64 *) pValue));
        }
    }

  std::cout << getObjectName() << ": " << mInfix << std::endl;

  if (mInfix == "@")
    {
      mUsable = true;
    }

  assert(mUsable);

  return mUsable;
}


CEvaluationNode * CMathExpression::createNodeFromValue(const C_FLOAT64 * pDataValue)
{
  CEvaluationNode * pNode = NULL;
  CMathObject * pMathObject = NULL;

  if (pDataValue != NULL)
    {
      pMathObject = mpContainer->getMathObject(pDataValue);

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

CEvaluationNode * CMathExpression::createMassActionPart(const C_FLOAT64 * pK,
    const CCallParameters< C_FLOAT64 > * pSpecies)
{
  CEvaluationNode * pPart = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
  pPart->addChild(createNodeFromValue(pK));

  CEvaluationNode * pNode = pPart;
  CCallParameters< C_FLOAT64 >::const_iterator itSpecies = pSpecies->begin();
  CCallParameters< C_FLOAT64 >::const_iterator endSpecies = pSpecies->end();

  for (; itSpecies != endSpecies - 1; ++itSpecies)
    {
      CEvaluationNode * p = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
      p->addChild(createNodeFromValue(itSpecies->value));
      pNode->addChild(p);
      pNode = p;
    }

  pNode->addChild(createNodeFromValue(itSpecies->value));

  return pPart;
}
