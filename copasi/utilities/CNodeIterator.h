// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/core/CFlags.h"

/**
 * Iterator processing modes determining to which the method
 * next will advance the iterator.
 */
class CNodeIteratorMode
{
public:
  enum State
  {
    Start,
    Before,
    After,
    Intermediate,
    End,
    __SIZE
  };

  typedef CFlags< State > Flag;
};

template < class Node, class Context > class CNodeContextIterator
{
private:
  /**
   * Internal class handling the traversal of the tree.
   * For each nested level in the tree an element is pushed onto the stack
   */
  class CStackElement
  {
  public:
    /**
     * Default Constructor
     */
    CStackElement():
      mpNode(NULL),
      mChildCount(0),
      mNextChildIndex(0),
      mContext(),
      mpParentContext(NULL)
    {}

    /**
     * Copy constructor
     * @param const CStackElement & src
     */
    CStackElement(const CStackElement & src):
      mpNode(src.mpNode),
      mChildCount(src.mChildCount),
      mNextChildIndex(src.mNextChildIndex),
      mContext(src.mContext),
      mpParentContext(src.mpParentContext)
    {}

    /**
     * Constructor
     * @param Node * pNode
     * @param Context * pParentContext (default: NULL)
     */
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

    /**
     * Destructor
     */
    ~CStackElement() {}

    /**
     * Pointer to the node of the tree represented by the stack element
     */
    Node * mpNode;

    /**
     * The number of children of the current node
     */
    size_t mChildCount;

    /**
     * The index of the next child to be processed
     */
    size_t mNextChildIndex;

    /**
     * The context of the current node.
     */
    Context mContext;

    /**
     * The pointer to the parent node's context.
     */
    Context * mpParentContext;
  };

public:
  /**
   * Default constructor
   */
  CNodeContextIterator():
    mStack(),
    mCurrentMode(CNodeIteratorMode::End),
    mProcessingModes(CNodeIteratorMode::Flag(CNodeIteratorMode::After) | CNodeIteratorMode::End)
  {}

  /**
   * Copy constructor
   * @param const CNodeContextIterator & src
   */
  CNodeContextIterator(const CNodeContextIterator & src):
    mStack(src.mStack),
    mCurrentMode(src.mCurrentMode),
    mProcessingModes(src.mProcessingModes)
  {}

  /**
   * Constructor
   * @param Node * pNode
   * @param Context * pParentContext (default: NULL)
   */
  CNodeContextIterator(Node * pNode, Context * pParentContext = NULL):
    mStack(),
    mCurrentMode(CNodeIteratorMode::Start),
    mProcessingModes(CNodeIteratorMode::Flag(CNodeIteratorMode::After) | CNodeIteratorMode::End)
  {
    mStack.push(CStackElement(pNode, pParentContext));
  }

  /**
   * Destructor
   */
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
  /**
   * This method moves the iterator to the next node based on the
   * setting of the processing modes and returns the processing mode of the
   * iterator.
   * @return const CNodeIteratorMode::State & processingMode
   */
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

    while (!mProcessingModes.isSet(mCurrentMode))
      {
        increment();
      }

    return mCurrentMode;
  }

  /**
   * This method moves the iterator beyond the last child.
   */
  const CNodeIteratorMode::State & skipChildren()
  {
    CStackElement & Current = mStack.top();
    Current.mNextChildIndex = Current.mChildCount + 1;
    mCurrentMode = CNodeIteratorMode::After;

    return mCurrentMode;
  }

  /**
   * Dereference the iterator
   * @return Node * pNode
   */
  Node * operator*() {return mStack.top().mpNode;}

  /**
   * Dereference the iterator
   * @return Node * pNode
   */
  Node * operator->() {return mStack.top().mpNode;}

  /**
   * Retrieve the processing mode
   * @return const CNodeIteratorMode::State & processingMode
   */
  const CNodeIteratorMode::State & processingMode() const {return mCurrentMode;}

  /**
   * Retrieve the end of the iterator, i.e., the
   */
  CNodeIteratorMode::State end() const {return CNodeIteratorMode::End;}

  /**
   * Retrieve the context of the current node.
   * @return Context & context
   */
  Context & context() {return mStack.top().mContext;}

  /**
   * Retrieve the pointer to the parent node context if it exists.
   * @return Context * parentContextPtr.
   */
  Context * parentContextPtr() {return mStack.top().mpParentContext;}

  /**
   * The nesting level of the tree.
   * Note, the nesting level of the root of the tree is 1. This is to distinguish its level
   * from the end of the iterator which reports 0.
   */
  size_t level() {return mStack.size();}

  /**
   * Set the processing modes to which the method next will advance the iterator.
   * Note, the iterator will always stop at the end.
   * @param const CNodeIteratorMode::Flag & processingModes
   */
  void setProcessingModes(const CNodeIteratorMode::Flag & processingModes) {mProcessingModes = (processingModes | CNodeIteratorMode::End);}

  /**
   * Retrieve the processing modes to which the method next will advance the iterator.
   * @return CNodeIteratorMode::Flag processingModes
   */
  CNodeIteratorMode::Flag getProcessingModes() const {return (mProcessingModes & ~CNodeIteratorMode::Flag(CNodeIteratorMode::End));}

private:
  /**
   * A stack representing the nested elements of the tree.
   */
  std::stack< CStackElement > mStack;

  /**
   * The current processing mode.
   */
  CNodeIteratorMode::State mCurrentMode;

  /**
   * The processing modes to which the method next will advance the iterator
   */
  CNodeIteratorMode::Flag mProcessingModes;
};

/**
 * A convenient iterator class which has the context type int
 */
template < class Node > class CNodeIterator : public CNodeContextIterator< Node, int >
{
public:
  /**
   * Constructor
   */
  CNodeIterator():
    CNodeContextIterator< Node, int >()
  {}

  /**
   * Copy constructor.
   */
  CNodeIterator(const CNodeIterator & src):
    CNodeContextIterator< Node, int >(src)
  {}

  /**
   * Constructor
   * @param Node * pNode
   */
  CNodeIterator(Node * pNode):
    CNodeContextIterator< Node, int >(pNode)
  {}

  /**
   * Destructor
   */
  ~CNodeIterator() {}
};
#endif // COPASI_CNodeIterator
