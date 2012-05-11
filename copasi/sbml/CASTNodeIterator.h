// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/Attic/CASTNodeIterator.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/11 15:42:13 $
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

#ifndef COPASI_CASTNodeIterator
#define COPASI_CASTNodeIterator

#include <stack>
#include <limits>

#include "sbml/math/ASTNode.h"

template < class Context > class CASTNodeContextIterator
{
public:
  static const size_t InvalidIndex = (size_t) - 1;

  class CStackElement
  {
  public:
    CStackElement():
        pASTNode(NULL),
        childCount(0),
        nextChildIndex(0),
        context()
    {}

    CStackElement(const CStackElement & src):
        pASTNode(src.pASTNode),
        childCount(src.childCount),
        nextChildIndex(src.nextChildIndex),
        context(src.context)
    {}

    CStackElement(ASTNode * pNode, const Context & context = Context()):
        pASTNode(pNode),
        childCount(0),
        nextChildIndex(0),
        context(context)
    {
      if (pASTNode != NULL)
        {
          childCount = pASTNode->getNumChildren();
        }
    }

    ~CStackElement() {}

    ASTNode * pASTNode;
    size_t childCount;
    size_t nextChildIndex;
    Context context;
  };

public:
  CASTNodeContextIterator():
      mStack()
  {}

  CASTNodeContextIterator(const CASTNodeContextIterator & src):
      mStack(src.mStack)
  {}

  CASTNodeContextIterator(ASTNode * pNode, const Context & context = Context()):
      mStack()
  {
    mStack.push(CStackElement(pNode, context));
  }

  ~CASTNodeContextIterator() {}

  bool next()
  {
    if (mStack.empty()) return false;

    CStackElement & Current = mStack.top();

    if (Current.nextChildIndex < Current.childCount)
      {
        CStackElement Child(Current.pASTNode->getChild(Current.nextChildIndex++), Current.context);

        if (Current.nextChildIndex == Current.childCount)
          {
            Current.nextChildIndex = InvalidIndex;
          }

        mStack.push(Child);

        return true;
      }

    mStack.pop();

    return !mStack.empty();
  }

  ASTNode * operator*() {return mStack.top().pASTNode;}

  ASTNode * operator->() {return mStack.top().pASTNode;}

  size_t childCount() const {return mStack.top().childCount;}

  size_t nextChildIndex() const {return mStack.top().nextChildIndex;}

  Context & context() {return mStack.top().context;}

private:
  std::stack< CStackElement > mStack;
};

class CASTNodeIterator : public CASTNodeContextIterator<int>
{
public:
  CASTNodeIterator():
      CASTNodeContextIterator<int>()
  {}

  CASTNodeIterator(const CASTNodeIterator & src):
      CASTNodeContextIterator<int>(src)
  {}

  CASTNodeIterator(ASTNode * pNode):
      CASTNodeContextIterator<int>(pNode)
  {}

  ~CASTNodeIterator() {}

};
#endif // COPASI_CASTNodeIterator
