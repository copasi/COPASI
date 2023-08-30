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

#define JIT_IMPLEMENTATION

#include <memory>

#include "copasi/copasi.h"

#include "copasi/math/CMathExpression.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/math/CJitCompiler.h"

#include "copasi/function/CExpression.h"
#include "copasi/function/CFunction.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationNodeObject.h"
#include "copasi/function/CEvaluationLexer.h"
#include "copasi/utilities/CCopasiTree.h"
#include "copasi/utilities/CNodeIterator.h"
#include "copasi/utilities/CBalanceTree.h"

#define pMathContainer static_cast< const CMathContainer * >(getObjectParent())

CMathExpression::CMathExpression() :
#ifdef USE_JIT
  CJitExpression(),
#endif
  CEvaluationTree()
  , mPrerequisites()
{}

CMathExpression::CMathExpression(const std::string & name,
                                 CMathContainer & container) :
#ifdef USE_JIT
  CJitExpression(),
#endif
  CEvaluationTree(name, &container, CEvaluationTree::MathExpression)
  , mPrerequisites()
{}

CMathExpression::CMathExpression(const CExpression & src,
                                 CMathContainer & container,
                                 const bool & replaceDiscontinuousNodes) :
#ifdef USE_JIT
  CJitExpression(),
#endif
  CEvaluationTree(src.getObjectName(), &container, CEvaluationTree::MathExpression)
  , mPrerequisites()
{
  clearNodes();

  // Create a converted copy of the existing expression tree.
  setRoot(container.copyBranch(src.getRoot(), replaceDiscontinuousNodes));

  compile();
}

CMathExpression::CMathExpression(const CFunction & src,
                                 const CCallParameters< C_FLOAT64 > & callParameters,
                                 CMathContainer & container,
                                 const bool & replaceDiscontinuousNodes) :
#ifdef USE_JIT
  CJitExpression(),
#endif
  CEvaluationTree(src.getObjectName(), &container, CEvaluationTree::MathExpression)
  , mPrerequisites()
{
  clearNodes();

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
        setRoot(container.copyBranch(src.getRoot(), Variables, replaceDiscontinuousNodes));

        // Deleted the created variables
        CMath::Variables< CEvaluationNode * >::iterator itVar = Variables.begin();
        CMath::Variables< CEvaluationNode * >::iterator endVar = Variables.end();

        for (; itVar != endVar; ++itVar)
          {
            pdelete(*itVar);
          }
      }

      break;

      case CEvaluationTree::MassAction:
      {
        // We build a mass action expression based on the call parameters.
        CCallParameters< C_FLOAT64 >::const_iterator it = callParameters.begin();

        // Handle the case we were have an invalid number of call parameters.
        if (callParameters.size() < 2)
          {
            setRoot(NULL);
          }
        else
          {
            // We always have reactants
            const C_FLOAT64 * pK = it->value;
            ++it;
            const CCallParameters< C_FLOAT64 > * pSpecies = it->vector;
            ++it;

            CEvaluationNode * pPart = createMassActionPart(pK, pSpecies);

            if (callParameters.size() < 4)
              {
                setRoot(pPart);
              }
            else
              {
                setRoot(new CEvaluationNodeOperator(CEvaluationNode::SubType::MINUS, "-"));
                getRoot()->addChild(pPart);

                pK = it->value;
                ++it;
                pSpecies = it->vector;
                ++it;

                pPart = createMassActionPart(pK, pSpecies);

                getRoot()->addChild(pPart);
              }
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

  if (src.getRoot() != NULL)
    {
      pExpression->setRoot(src.getRoot()->copyBranch());
    }

  pExpression->buildCalculationSequence();
  pExpression->mPrerequisites = src.mPrerequisites;

  return pExpression;
}

void CMathExpression::relocate(const CMathContainer * pContainer,
                               const std::vector< CMath::sRelocate > & relocations)
{
  // Apply the relocations to all nodes of type POINTER
  CCopasiTree<CEvaluationNode>::iterator it = getRoot();
  CCopasiTree<CEvaluationNode>::iterator end = NULL;

  for (; it != end; ++it)
    {
      if (it->mainType() == CEvaluationNode::MainType::OBJECT &&
          it->subType() == CEvaluationNode::SubType::POINTER)
        {
          C_FLOAT64 * pPointer = (C_FLOAT64 *) stringToPointer(it->getData());
          pContainer->relocateValue(pPointer, relocations);
          static_cast< CEvaluationNodeObject * >(&*it)->setObjectValuePtr(pPointer);
        }
    }

  mInfix = getRoot() != NULL ? getRoot()->buildInfix() : "";
  pContainer->relocateObjectSet(mPrerequisites, relocations);
}

#ifdef USE_JIT
// virtual
void CMathExpression::compileJit()
{
  CJitCompiler * pCompiler = getCompiler();
  mpJitFunction = NULL;

  if (pCompiler != NULL)
    {
      CNodeIterator< const CEvaluationNode > itNode(getRoot());
      size_t MaxLevel = 0;

      while (itNode.next() != itNode.end())
        if (itNode.level() > MaxLevel)
          MaxLevel = itNode.level();

      if (MaxLevel > 5000)
        return;

      mpJitFunction = pCompiler->compile(*this);
    }

  return;
}
#endif

const C_FLOAT64 & CMathExpression::value()
{
#ifdef USE_JIT

  if (mpJitFunction != NULL)
    mValue = calculateJit();
  else
    calculate();

#else

  calculate();

#endif

  return mValue;
}

// virtual
const CObjectInterface::ObjectSet & CMathExpression::getPrerequisites() const
{
  return mPrerequisites;
}

// virtual
CIssue CMathExpression::compile()
{
  mPrerequisites.clear();
  mValidity.clear();
  CIssue firstWorstIssue, issue;

  if (!(firstWorstIssue = updateTree()) ||
      mpNodeList == NULL)
    {
      mCalculationSequence.resize(0);

      return firstWorstIssue;
    }

  std::vector< CEvaluationNode * >::iterator it = mpNodeList->begin();
  std::vector< CEvaluationNode * >::iterator end = mpNodeList->end();

  for (; it != end; ++it)
    {
      issue = (*it)->compile();

      mValidity.add(issue);
      firstWorstIssue &= issue;

      switch ((*it)->subType())
        {
          case CEvaluationNode::SubType::POINTER:
            mPrerequisites.insert(static_cast< CEvaluationNodeObject *>(*it)->getObjectInterfacePtr());
            break;

          case CEvaluationNode::SubType::RGAMMA:
          case CEvaluationNode::SubType::RNORMAL:
          case CEvaluationNode::SubType::RPOISSON:
          case CEvaluationNode::SubType::RUNIFORM:
            mPrerequisites.insert(static_cast< CMathContainer * >(getObjectParent())->getRandomObject());
            break;
        }
    }

  assert(mPrerequisites.erase(NULL) == 0);

  if (mInfix == "@")
    {
      firstWorstIssue = CIssue::Success;
    }

  buildCalculationSequence();

  return firstWorstIssue;
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
      if ((*it)->mainType() == CEvaluationNode::MainType::OBJECT &&
          (*it)->subType() == CEvaluationNode::SubType::POINTER)
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
      mInfix = getRoot()->buildInfix();
      mpRootValue = getRoot()->getValuePointer();
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
      pNode = new CEvaluationNodeConstant(CEvaluationNode::SubType::NaN, "NAN");
    }

  return pNode;
}

CEvaluationNode * CMathExpression::createMassActionPart(const C_FLOAT64 * pK,
    const CCallParameters< C_FLOAT64 > * pSpecies)
{
  if (pSpecies->size() == 0)
    return new CEvaluationNodeConstant(CEvaluationNode::SubType::NaN, "NAN");

  std::vector< CEvaluationNode * > Nodes;
  Nodes.push_back(createNodeFromValue(pK));

  CCallParameters< C_FLOAT64 >::const_iterator itSpecies = pSpecies->begin();
  CCallParameters< C_FLOAT64 >::const_iterator endSpecies = pSpecies->end();

  for (; itSpecies != endSpecies; ++itSpecies)
    Nodes.push_back(createNodeFromValue(itSpecies->value));

  return BalanceTree< CEvaluationNode * >::create(Nodes, [](CEvaluationNode * const & pFirst, CEvaluationNode * const & pSecond)
  {
    CEvaluationNode * pNew = new CEvaluationNodeOperator(CEvaluationNode::SubType::MULTIPLY, "*");
    pNew->addChild(pFirst);
    pNew->addChild(pSecond);
    return pNew;
  });
}
