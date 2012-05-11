// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CNodeIterator.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/11 16:51:55 $
// End CVS Header

// Copyright (C) 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CASTIterator.h
 *
 *  Created on: May 11, 2012
 *      Author: shoops
 */

#ifndef COPASI_CNodeIterator
#define COPASI_CNodeIterator

#include <stack>
#include <limits>

template < class Node, class Context > class CNodeContextIterator
{
public:
  static const size_t None = (size_t) - 1;

private:
  class CStackElement
  {
  public:
    CStackElement():
        mpNode(NULL),
        mChildCount(0),
        mNextChildIndex(0),
        mContext()
    {}

    CStackElement(const CStackElement & src):
        mpNode(src.mpNode),
        mChildCount(src.mChildCount),
        mNextChildIndex(src.mNextChildIndex),
        mContext(src.mContext)
    {}

    CStackElement(Node * pNode, const Context & context = Context()):
        mpNode(pNode),
        mChildCount(0),
        mNextChildIndex(0),
        mContext(context)
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
  };

public:
  CNodeContextIterator():
      mStack()
  {}

  CNodeContextIterator(const CNodeContextIterator & src):
      mStack(src.mStack)
  {}

  CNodeContextIterator(Node * pNode, const Context & context = Context()):
      mStack()
  {
    mStack.push(CStackElement(pNode, context));
  }

  ~CNodeContextIterator() {}

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
  bool next()
  {
    if (mStack.empty()) return false;

    CStackElement & Current = mStack.top();

    if (Current.mNextChildIndex < Current.mChildCount)
      {
        CStackElement Child(Current.mpNode->getChild(Current.mNextChildIndex++), Current.mContext);

        if (Current.mNextChildIndex == Current.mChildCount)
          {
            Current.mNextChildIndex = None;
          }

        mStack.push(Child);

        return true;
      }

    if (Current.mNextChildIndex != None)
      {
        Current.mNextChildIndex = None;
      }
    else
      {
        mStack.pop();
      }

    return !mStack.empty();
  }

  Node * operator*() {return mStack.top().mpNode;}

  Node * operator->() {return mStack.top().mpNode;}

  size_t childCount() const {return mStack.top().mChildCount;}

  size_t nextChildIndex() const {return mStack.top().mNextChildIndex;}

  Context & context() {return mStack.top().mContext;}

private:
  std::stack< CStackElement > mStack;
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

  CNodeIterator(ASTNode * pNode):
      CNodeContextIterator< Node, int >(pNode)
  {}

  ~CNodeIterator() {}

};
#endif // COPASI_CNodeIterator
