// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

#include "CMathDependencyNodeIterator.h"
#include "CMathDependencyNode.h"
#include "CMathObject.h"

CMathDependencyNodeIterator::CStackElement::CStackElement():
  mpNode(NULL),
  mType(Dependents),
  mItChild(),
  mEndChild(),
  mpParent(NULL)
{}

CMathDependencyNodeIterator::CStackElement::CStackElement(const CMathDependencyNodeIterator::CStackElement & src):
  mpNode(src.mpNode),
  mType(src.mType),
  mItChild(src.mItChild),
  mEndChild(src.mEndChild),
  mpParent(src.mpParent)
{}

CMathDependencyNodeIterator::CStackElement::CStackElement(CMathDependencyNode * pNode,
    const CMathDependencyNodeIterator::Type & type,
    const CMathDependencyNode * pParent):
  mpNode(pNode),
  mType(type),
  mItChild(),
  mEndChild(),
  mpParent(pParent)
{
  if (pNode != NULL)
    {
      switch (mType)
        {
          case Dependents:
            mItChild = mpNode->getDependents().begin();
            mEndChild = mpNode->getDependents().end();
            break;

          case Prerequisites:
            mItChild = mpNode->getPrerequisites().begin();
            mEndChild = mpNode->getPrerequisites().end();
            break;
        }
    }
}

CMathDependencyNodeIterator::CStackElement::~CStackElement()
{}

CMathDependencyNodeIterator::CMathDependencyNodeIterator():
  mStack(),
  mVisited(),
  mType(Dependents),
  mCurrentState(End),
  mProcessingModes(After | End | Recursive)
{}

CMathDependencyNodeIterator::CMathDependencyNodeIterator(const CMathDependencyNodeIterator & src):
  mStack(src.mStack),
  mVisited(src.mVisited),
  mType(src.mType),
  mCurrentState(src.mCurrentState),
  mProcessingModes(src.mProcessingModes)
{}

CMathDependencyNodeIterator::CMathDependencyNodeIterator(CMathDependencyNode * pNode,
    const CMathDependencyNodeIterator::Type & type):
  mStack(),
  mVisited(),
  mType(type),
  mCurrentState(Start),
  mProcessingModes(After | End | Recursive)
{
  mStack.push(CStackElement(pNode, mType, NULL));
  mVisited.insert(pNode);
}

CMathDependencyNodeIterator::~CMathDependencyNodeIterator()
{}

void CMathDependencyNodeIterator::increment()
{
  // We must not further process any recursive
  if (mCurrentState == Recursive)
    {
      // We ignore all child elements of this node, i.e. we are after;
      mCurrentState = After;
    }

  if (mStack.empty())
    {
      mCurrentState = End;

      return;
    }

  CStackElement & Current = mStack.top();

  if (mCurrentState != After)
    {
      if (Current.mItChild != Current.mEndChild)
        {
          CMathDependencyNode * pNode = *Current.mItChild;

          mStack.push(CStackElement(*Current.mItChild, Current.mType, Current.mpNode));

          // This will process any children since the iterator is context unaware.
          // It is therefore expected that we encounter recursive dependencies for
          // intensive/extensive value pairs.
          Current.mItChild++;

          if (mVisited.find(pNode) != mVisited.end())
            {
              // Indicate that this node is already in the stack and processing would lead to an
              // infinite recursion.
              mCurrentState = Recursive;
            }
          else
            {
              mVisited.insert(pNode);
              mCurrentState = Before;
            }

          return;
        }

      if (Current.mItChild == Current.mEndChild)
        {
          mCurrentState = After;

          return;
        }
    }

  mVisited.erase(Current.mpNode);
  mStack.pop();

  if (mStack.empty())
    {
      mCurrentState = End;

      return;
    }

  CStackElement & Parent = mStack.top();

  if (Parent.mItChild != Parent.mEndChild)
    {
      mCurrentState = Intermediate;
    }
  else
    {
      mCurrentState = After;
    }

  return;
}

bool CMathDependencyNodeIterator::next()
{
  if (mCurrentState != Start)
    {
      increment();
    }
  else
    {
      mCurrentState = Before;
    }

  while (!mProcessingModes.isSet(mCurrentState))
    {
      increment();
    }

  return mCurrentState & ~End;
}

const CMathDependencyNodeIterator::State & CMathDependencyNodeIterator::skipChildren()
{
  CStackElement & Current = mStack.top();
  Current.mItChild = Current.mEndChild;
  mCurrentState = After;

  return mCurrentState;
}

CMathDependencyNode * CMathDependencyNodeIterator::operator*()
{
  return mStack.top().mpNode;
}

CMathDependencyNode * CMathDependencyNodeIterator::operator->()
{
  return mStack.top().mpNode;
}

const CMathDependencyNode * CMathDependencyNodeIterator::parent()
{
  return mStack.top().mpParent;
}

const CMathDependencyNodeIterator::State & CMathDependencyNodeIterator::state() const
{
  return mCurrentState;
}

size_t CMathDependencyNodeIterator::level() const
{
  return mStack.size();
}

void CMathDependencyNodeIterator::setProcessingModes(const CMathDependencyNodeIterator::Flag & processingModes)
{
  mProcessingModes = (processingModes | End | Recursive);
}

CMathDependencyNodeIterator::Flag CMathDependencyNodeIterator::getProcessingModes() const
{
  return (mProcessingModes & ~(CMathDependencyNodeIterator::Flag(End) | Recursive));
}
