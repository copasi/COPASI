// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CNodeIterator.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/21 13:36:05 $
// End CVS Header

// Copyright (C) 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CNodeIterator.h
 *
 *  Created on: May 11, 2012
 *      Author: shoops
 */

#ifndef COPASI_CNodeIterator
#define COPASI_CNodeIterator

#include <stack>
#include <limits>

#include "copasi/math/CMathEnum.h"

class CNodeIteratorMode
{
public:
  enum State
  {
    Start = 0x00,
    Before = 0x01,
    After = 0x02,
    Intermediate = 0x04,
    End = 0x08
  };

  typedef CMathFlags< State > Flag;
};

template < class Node, class Context > class CNodeContextIterator
{
private:
  class CStackElement
  {
  public:
    CStackElement():
        mpNode(NULL),
        mChildCount(0),
        mNextChildIndex(0),
        mContext(),
        mpParentContext(NULL)
    {}

    CStackElement(const CStackElement & src):
        mpNode(src.mpNode),
        mChildCount(src.mChildCount),
        mNextChildIndex(src.mNextChildIndex),
        mContext(src.mContext),
        mpParentContext(src.mpParentContext)
    {}

    CStackElement(Node * pNode, Context * pParentContext = NULL):
        mpNode(pNode),
        mChildCount(0),
        mNextChildIndex(0),
        mContext(),
        mpParentContext(pParentContext)
    {
      if (pNode != NULL)
        {
          mChildCount = pNode->getNumChildren();
        }
    }

    ~CStackElement() {}

    Node * mpNode;
    size_t mChildCount;
    size_t mNextChildIndex;
    Context mContext;
    Context * mpParentContext;
  };

public:
  CNodeContextIterator():
      mStack(),
      mCurrentMode(CNodeIteratorMode::End),
      mProcessingModes((CNodeIteratorMode::State)(CNodeIteratorMode::After | CNodeIteratorMode::End))
  {}

  CNodeContextIterator(const CNodeContextIterator & src):
      mStack(src.mStack),
      mCurrentMode(src.mCurrentMode),
      mProcessingModes(src.mProcessingModes)
  {}

  CNodeContextIterator(Node * pNode, Context * pParentContext = NULL):
      mStack(),
      mCurrentMode(CNodeIteratorMode::Start),
      mProcessingModes((CNodeIteratorMode::State)(CNodeIteratorMode::After | CNodeIteratorMode::End))
  {
    mStack.push(CStackElement(pNode, pParentContext));
  }

  ~CNodeContextIterator() {}

private:
  /**
   * This method moves the iterator to the next node in the tree. The tree is
   * traversed depth first. A return value of false indicates that the tree
   * has been completed traversed.
   *
   * Please note that the iterator points to the same node twice, once before
   * the first child and once after the last child to allow pre and post
   * processing. This behavior is also true for childless nodes. To determine
   * whether the iterator is in the pre or post processing phase one may check
   * the nextChildIndex where zero indicates pre and None indicates post
   * processing.
   *
   * @return bool moreNodes
   */
  void increment()
  {
    if (mStack.empty())
      {
        mCurrentMode = CNodeIteratorMode::End;

        return;
      }

    CStackElement & Current = mStack.top();

    if (Current.mNextChildIndex < Current.mChildCount)
      {
        mStack.push(CStackElement(static_cast< Node * >(Current.mpNode->getChild(Current.mNextChildIndex++)), &Current.mContext));
        mCurrentMode = CNodeIteratorMode::Before;

        return;
      }

    if (Current.mNextChildIndex == Current.mChildCount)
      {
        Current.mNextChildIndex++;
        mCurrentMode = CNodeIteratorMode::After;

        return;
      }

    mStack.pop();

    if (mStack.empty())
      {
        mCurrentMode = CNodeIteratorMode::End;

        return;
      }

    CStackElement & Parent = mStack.top();

    if (Parent.mNextChildIndex < Parent.mChildCount)
      {
        mCurrentMode = CNodeIteratorMode::Intermediate;
      }
    else
      {
        mCurrentMode = CNodeIteratorMode::After;
        Parent.mNextChildIndex++;
      }

    return;
  }

public:
  const CNodeIteratorMode::State & next()
  {
    if (mCurrentMode != CNodeIteratorMode::Start)
      {
        increment();
      }
    else
      {
        mCurrentMode = CNodeIteratorMode::Before;
      }

    while (!(mProcessingModes & mCurrentMode))
      {
        increment();
      }

    return mCurrentMode;
  }

  const CNodeIteratorMode::State & skipChildren()
  {
    CStackElement & Current = mStack.top();
    Current.mNextChildIndex = Current.mChildCount + 1;
    mCurrentMode = CNodeIteratorMode::After;

    return mCurrentMode;
  }

  Node * operator*() {return mStack.top().mpNode;}

  Node * operator->() {return mStack.top().mpNode;}

  const CNodeIteratorMode::State & processingMode() const {return mCurrentMode;}

  CNodeIteratorMode::State end() const {return CNodeIteratorMode::End;}

  Context & context() {return mStack.top().mContext;}

  Context * parentContextPtr() {return mStack.top().mpParentContext;}

  size_t level() {return mStack.size();}

  void setProcessingModes(const CNodeIteratorMode::Flag & processingModes) {mProcessingModes = (processingModes | CNodeIteratorMode::End);}

  CNodeIteratorMode::Flag getProcessingModes() const {return (mProcessingModes & ~CNodeIteratorMode::End);}

private:
  std::stack< CStackElement > mStack;

  CNodeIteratorMode::State mCurrentMode;

  CNodeIteratorMode::Flag mProcessingModes;
};

template < class Node > class CNodeIterator : public CNodeContextIterator< Node, int >
{
public:
  CNodeIterator():
      CNodeContextIterator< Node, int >()
  {}

  CNodeIterator(const CNodeIterator & src):
      CNodeContextIterator< Node, int >(src)
  {}

  CNodeIterator(Node * pNode):
      CNodeContextIterator< Node, int >(pNode)
  {}

  ~CNodeIterator() {}

};
#endif // COPASI_CNodeIterator
