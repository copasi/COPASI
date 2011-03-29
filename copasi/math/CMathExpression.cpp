// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathExpression.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/29 16:20:16 $
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
    mPrerequisites(),
    mFunctionVariableMap()
{}

CMathExpression::CMathExpression(const CExpression & src,
                                 const CMathContainer & container):
    CEvaluationTree("CMathExpression", &container, CEvaluationTree::MathExpression),
    mPrerequisites(),
    mFunctionVariableMap()
{
  // Create a copy of the existing expression tree.
  mpRoot = src.getRoot()->copyBranch();

  // Convert the tree
  mpRoot = convertNode(mpRoot, NULL);
}

CMathExpression::CMathExpression(const CFunction & src,
                                 const CCallParameters< C_FLOAT64 > & callParameters,
                                 const CMathContainer & container):
    CEvaluationTree("CMathExpression", &container, CEvaluationTree::MathExpression),
    mPrerequisites(),
    mFunctionVariableMap()
{
  // Deal with the different function types
  switch (src.getType())
    {
      case CEvaluationTree::Function:
      case CEvaluationTree::PreDefined:
      case CEvaluationTree::UserDefined:
      {
        // Create a vector of CEvaluationNodeObject for each variable
        std::vector< const CEvaluationNode * > Variables;
        CCallParameters< C_FLOAT64 >::const_iterator it = callParameters.begin();
        CCallParameters< C_FLOAT64 >::const_iterator end = callParameters.end();

        for (; it != end; ++it)
          {
            Variables.push_back(createNodeFromValue(it->value));
          }

        mFunctionVariableMap.push(Variables);

        // Create a copy of the existing expression tree.
        mpRoot = src.getRoot()->copyBranch();

        // Convert the tree
        mpRoot = convertNode(mpRoot, &src);

        mFunctionVariableMap.pop();

        std::vector< const CEvaluationNode * >::iterator itVar = Variables.begin();
        std::vector< const CEvaluationNode * >::iterator endVar = Variables.end();

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
            mpRoot->compile(this);
          }
        else
          {
            mpRoot = pPart;
          }
      }
      break;

      case CEvaluationTree::MathExpression:
      case CEvaluationTree::Expression:
        // This cannot happen and is only here to  the compiler.
        break;
    }
}


// virtual
CMathExpression::~CMathExpression()
{
  pdelete(mpRoot);
}

const C_FLOAT64 & CMathExpression::value() const
{
  return mpRoot->value();
}

// virtual
const CObjectInterface::ObjectSet & CMathExpression::getPrerequisites() const
{
  return mPrerequisites;
}

CEvaluationNode * CMathExpression::convertNode(CEvaluationNode * pNode,
    const CEvaluationTree * pTree)
{
  // We first convert the children
  CEvaluationNode * pChild = static_cast< CEvaluationNode * >(pNode->getChild());

  while (pChild != NULL)
    {
      pChild = convertNode(pChild, pTree);
      pChild = static_cast< CEvaluationNode * >(pChild->getSibling());
    }

  // Convert the node itself if it is needed
  CEvaluationNode * pConvertedNode = pNode;

  switch (CEvaluationNode::type(pNode->getType()))
    {
      case CEvaluationNode::OBJECT:

        // We need to map the object to a math object if possible.
        if ((int) CEvaluationNode::subType(pNode->getType()) == CEvaluationNodeObject::CN)
          {
            CEvaluationNodeObject * p = static_cast< CEvaluationNodeObject *>(pNode);
            const CObjectInterface * pObject = mpContainer->getObject(p->getObjectCN());

            // Create a converted node
            pConvertedNode = createNodeFromObject(pObject);
            // Replace the existing node
            pNode->addSibling(pConvertedNode, pNode);
            delete pNode;
          }

        // TODO CRITICAL Do we need to convert POINTER nodes. Currently they only appear
        // in event triggers but may also appear in analysis entities.

        // Pointer nodes which point to MathObject should not be converted however we need
        // to make sure that they are in the list of dependencies. Currently the later only
        // occurs in converted functions for which the constructor takes care of the issue.
        break;

      case CEvaluationNode::CALL:
      {
        CEvaluationNodeCall * p = static_cast< const CEvaluationNodeCall * >(pNode);
        std::vector< const CEvaluationNode * > Variables;

        const CEvaluationNode * pVariable =
          static_cast< const CEvaluationNode * >(p->getChild());

        while (pVariable != NULL)
          {
            Variables.push_back(pVariable);
            pVariable = static_cast< const CEvaluationNode * >(pVariable->getSibling());
          }

        mFunctionVariableMap.push(Variables);

        // Copy
        pConvertedNode = p->getCalledTree()->getRoot()->copyBranch();
        // Convert the copy
        pConvertedNode = convertNode(pConvertedNode, p->getCalledTree());
        // Replace the existing node
        pNode->addSibling(pConvertedNode, pNode);
        delete pNode;

        mFunctionVariableMap.pop();
      }

      break;

      case CEvaluationNode::VARIABLE:
      {
        assert(!mFunctionVariableMap.empty());

        CEvaluationNodeVariable * p = static_cast< const CEvaluationNodeVariable * >(pNode);
        p->compile(pTree);
        size_t Index = p->getIndex();

        assert(Index < mFunctionVariableMap.top().size());

        const CEvaluationNode * pVariable = mFunctionVariableMap.top()[Index];

        // Copy
        pConvertedNode = pVariable->copyBranch();
        // Convert the copy
        pConvertedNode = convertNode(pConvertedNode, pTree);
        // Replace the existing node
        pNode->addSibling(pConvertedNode, pNode);
        delete pNode;
      }
      // References to variable values are replaced by pointers to their values.
      break;

      case CEvaluationNode::CONSTANT:
      case CEvaluationNode::NUMBER:
      case CEvaluationNode::STRUCTURE:
      case CEvaluationNode::WHITESPACE:
      case CEvaluationNode::OPERATOR:
      case CEvaluationNode::FUNCTION:
      case CEvaluationNode::CHOICE:
      case CEvaluationNode::LOGICAL:
      case CEvaluationNode::MV_FUNCTION:
      case CEvaluationNode::VECTOR:
      case CEvaluationNode::DELAY:
      case CEvaluationNode::INVALID:
        // Nothing to do or not part of the tree
        break;

    }

  pConvertedNode->compile(this);

  return pConvertedNode;
}

CEvaluationNode * CMathExpression::createNodeFromObject(const CObjectInterface * pObject)
{
  CEvaluationNode * pNode = NULL;

  if (pObject != NULL)
    {
      mPrerequisites.insert(pObject);
      pNode = new CEvaluationNodeObject((C_FLOAT64 *) pObject->getValuePointer());
    }
  else
    {
      // We have an invalid value, i.e. NaN
      pNode = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "NAN");
    }

  return pNode;
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
          mPrerequisites.insert(pMathObject);
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
      pNode->compile(this);
      pNode = p;
    }

  pNode->addChild(createNodeFromValue(itSpecies->value));
  pNode->compile(this);

  return pPart;
}
