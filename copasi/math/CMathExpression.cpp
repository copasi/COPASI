// Copyright (C) 2011 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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
#include "function/CEvaluationLexer.h"

#include "utilities/CCopasiTree.h"

#define pMathContainer static_cast< const CMathContainer * >(getObjectParent())

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
  CEvaluationLexer::freeNodeList(mpNodeList);

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
  CEvaluationLexer::freeNodeList(mpNodeList);

  // Deal with the different function types
  switch (src.getType())
    {
      case CEvaluationTree::Function:
      case CEvaluationTree::PreDefined:
      case CEvaluationTree::UserDefined:
      {
        // Create a vector of CEvaluationNodeObject for each variable
        CMath::Variables< CEvaluationNode * > Variables;

        CCallParameters< C_FLOAT64 >::const_iterator it = callParameters.begin();
        CCallParameters< C_FLOAT64 >::const_iterator end = callParameters.end();

        for (; it != end; ++it)
          {
            Variables.push_back(createNodeFromValue(it->value));
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

// static
CMathExpression * CMathExpression::copy(const CMathExpression & src,
                                        CMathContainer & container)
{
  CMathExpression * pExpression = new CMathExpression(src.getObjectName(), container);
  pExpression->setRoot(src.getRoot()->copyBranch());

  return pExpression;
}

void CMathExpression::relocate(const std::vector< CMath::sRelocate > & relocations)
{
  // Apply the relocations to all nodes of type POINTER
  CCopasiTree<CEvaluationNode>::iterator it = getRoot();
  CCopasiTree<CEvaluationNode>::iterator end = NULL;

  for (; it != end; ++it)
    {
      if (it->getType() == (CEvaluationNode::OBJECT | CEvaluationNodeObject::POINTER))
        {
          C_FLOAT64 * pPointer = (C_FLOAT64 *) stringToPointer(it->getData());
          CMathContainer::relocateValue(pPointer, relocations);
          static_cast< CEvaluationNodeObject * >(&*it)->setObjectValuePtr(pPointer);
        }
    }

  mInfix = mpRoot->buildInfix();
  CMathContainer::relocateObjectSet(mPrerequisites, relocations);
}

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

  if (!updateTree())
    {
      mUsable = false;
      mCalculationSequence.resize(0);

      return mUsable;
    }

  std::vector< CEvaluationNode * >::iterator it = mpNodeList->begin();
  std::vector< CEvaluationNode * >::iterator end = mpNodeList->end();

  for (; it != end; ++it)
    {
      mUsable &= (*it)->compile(this);

      if ((*it)->getType() == (CEvaluationNode::OBJECT | CEvaluationNodeObject::POINTER))
        {
          void * pValue = stringToPointer((*it)->getData());

          CMathObject * pMathObject = pMathContainer->getMathObject((C_FLOAT64 *) pValue);

          if (pMathObject != NULL)
            {
              mPrerequisites.insert(pMathObject);
            }
          else
            {
              CCopasiObject * pDataObject = pMathContainer->getDataObject((C_FLOAT64 *) pValue);

              if (pDataObject != NULL)
                {
                  mPrerequisites.insert(pDataObject);
                }
              else
                {
                  // This must never happen
                  fatalError();
                }
            }
        }
    }

  if (mInfix == "@")
    {
      mUsable = true;
    }

  buildCalculationSequence();

  return mUsable;
}

bool CMathExpression::convertToInitialExpression()
{
  if (getObjectName().substr(0, 7) != "Initial")
    {
      setObjectName("Initial" + getObjectName());
    }

  if (mpNodeList == NULL)
    {
      return false;
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
          C_FLOAT64 * pInitialValue = pMathContainer->getInitialValuePointer(pValue);

          if (pValue != pInitialValue)
            {
              changed = true;
              pNode->setObjectValuePtr(pInitialValue);

              mPrerequisites.erase(pMathContainer->getMathObject(pValue));
              mPrerequisites.insert(pMathContainer->getMathObject(pInitialValue));
            }
        }
    }

  if (changed)
    {
      mInfix = mpRoot->buildInfix();
    }

  return true;
}

bool CMathExpression::setRoot(CEvaluationNode* pRootNode)
{
  return CEvaluationTree::setRoot(pRootNode);
}

CEvaluationNode * CMathExpression::createNodeFromValue(const C_FLOAT64 * pDataValue)
{
  CEvaluationNode * pNode = NULL;
  CMathObject * pMathObject = NULL;

  if (pDataValue != NULL)
    {
      pMathObject = pMathContainer->getMathObject(pDataValue);

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
