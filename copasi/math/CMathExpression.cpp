// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathExpression.cpp,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/21 14:12:02 $
// End CVS Header

// Copyright (C) 2012 - 2011 by Pedro Mendes, Virginia Tech Intellectual
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
        CMath::Variables< CEvaluationNode * > Variables;

        CCallParameters< C_FLOAT64 >::const_iterator it = callParameters.begin();
        CCallParameters< C_FLOAT64 >::const_iterator end = callParameters.end();

        for (; it != end; ++it)
          {
            CMath::Variables< CEvaluationNode * >::value_type Variable;
            Variable.push_back(createNodeFromValue(it->value));
            Variables.push_back(Variable);
          }

        // Create a converted copy of the existing expression tree.
        mpRoot = container.copyBranch(src.getRoot(), Variables, replaceDiscontinuousNodes);

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

const C_FLOAT64 & CMathExpression::value()
{
  calculate();

  return mValue;
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
          void * pValue = stringToPointer((*it)->getData());

          // TODO CRITICAL It is possible that the user selects non model objects, i.e.,
          // problem or method values within the expression. These cannot be mapped to a
          // math objects and therefore dependencies will be broken.

          CMathObject * pMathObject = mpContainer->getMathObject((C_FLOAT64 *) pValue);

          if (pMathObject != NULL)
            {
              mPrerequisites.insert(pMathObject);
            }
          else
            {
              // For the moment we stop.
              assert(false);
            }
        }
    }

  if (mInfix == "@")
    {
      mUsable = true;
    }

  assert(mUsable);

  buildCalculationSequence();

  return mUsable;
}

bool CMathExpression::convertToInitialExpression()
{
  if (getObjectName().substr(0, 7) != "Initial")
    {
      setObjectName("Initial" + getObjectName());
    }

  std::vector< CEvaluationNode * >::iterator it = mpNodeList->begin();
  std::vector< CEvaluationNode * >::iterator end = mpNodeList->end();
  bool changed = false;

  for (; it != end; ++it)
    {
      if ((*it)->getType() == (CEvaluationNode::OBJECT | CEvaluationNodeObject::POINTER))
        {
          CEvaluationNodeObject * pNode = static_cast< CEvaluationNodeObject *>(*it);
          const C_FLOAT64 * pValue = pNode->getObjectValuePtr();
          C_FLOAT64 * pInitialValue = mpContainer->getInitialValuePointer(pValue);

          if (pValue != pInitialValue)
            {
              changed = true;
              pNode->setObjectValuePtr(pInitialValue);

              mPrerequisites.erase(mpContainer->getMathObject(pValue));
              mPrerequisites.insert(mpContainer->getMathObject(pInitialValue));
            }
        }
    }

  if (changed)
    {
      mInfix = mpRoot->buildInfix();
    }

  return true;
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
