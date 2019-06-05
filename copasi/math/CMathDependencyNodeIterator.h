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

/*
 * CMathDependencyNodeIterator.h
 *
 *  Created on: May 11, 2012
 *      Author: shoops
 */

#ifndef COPASI_CMathDependencyNodeIterator
#define COPASI_CMathDependencyNodeIterator

#include <stack>
#include <set>

#include "copasi/math/CMathEnum.h"

class CMathDependencyNode;

/**
 * This class allows to iterator over the nodes of a dependency graph in both directions
 * (Dependents and Prerequisites) which is indicated by the type.
 */
class CMathDependencyNodeIterator
{
public:
  /**
   * Type defining whether we iterate over the dependents or prerequisites
   */
  enum Type
  {
    Dependents,
    Prerequisites
  };

  /**
   * The state of the iterator. Please note that the graph might be recursive
   * which will cause the iterator to stop.
   */
  enum State
  {
    Start,
    Before,
    After,
    Intermediate,
    End,
    Recursive,
    __SIZE
  };

  /**
   * A flag indicating to which state the iterator should advance. These may be any
   * combination of the enumeration value State. Please note the iterator will always
   * return and End and Recursive
   */
  typedef CFlags< State > Flag;

private:
  /**
   * An internal class managing the context of the each nesting level of the iterator
   */
  class CStackElement
  {
  public:
    /**
     * Default constructor
     */
    CStackElement();

    /**
     * Copy constructor
     * @param const CStackElement & src
     */
    CStackElement(const CStackElement & src);

    /**
     * Specific constructor
     * @param CMathDependencyNode * pNode
     * @param const Type & type
     * @param const CMathDependencyNode * pParent
     */
    CStackElement(CMathDependencyNode * pNode, const Type & type, const CMathDependencyNode * pParent);

    /**
     * Destructor
     */
    ~CStackElement();

    /**
     * The node the iterator points to in the current nesting level
     */
    CMathDependencyNode * mpNode;

    /**
     * The iterator type (Dependents or Prerequisites)
     */
    Type mType;

    /**
     * An iterator to the next child to be processed.
     */
    std::vector< CMathDependencyNode * >::iterator mItChild;

    /**
     * An iterator pointing beyond the last child.
     */
    std::vector< CMathDependencyNode * >::iterator mEndChild;

    /**
     * A pointer to the parent node of the current node if know
     * otherwise NULL
     */
    const CMathDependencyNode * mpParent;
  };

public:
  /**
   * Default constructor
   */
  CMathDependencyNodeIterator();

  /**
   * Copy constructor
   * @param const CMathDependencyNodeIterator & src
   */
  CMathDependencyNodeIterator(const CMathDependencyNodeIterator & src);

  /**
   * Specific constructor
   * @param CMathDependencyNode * pNode
   * @param const Type & type (default: Dependents)
   */
  CMathDependencyNodeIterator(CMathDependencyNode * pNode, const Type & type = Dependents);

  /**
   * Destructor
   */
  ~CMathDependencyNodeIterator();

private:
  /**
   * This method advances the iterator to the next internal state. The tree is
   * traversed depth first.
   *
   * Please note that the iterator points to the same node multiple times, once
   * before every child, and once after the last child to allow pre and post
   * processing. This behavior is also true for childless nodes. To determine
   * whether the iterator is in the pre, intermediate or post processing phase
   * one may check the processing mode with:
   *   const State & state()
   */
  void increment();

public:
  /**
   * This method advances the iterator to the next node and state combination for
   * which the state is in the Flag of processing modes. A return value of true indicates
   * that such a node has been found whereas false indicates the iteration has been completed
   * or failed. To determine the current state of the iterator use:
   *   const State & state()
   * @return bool success
   */
  bool next();

  /**
   * Calling this method causes the iterator to skip processing the children of the current node
   * and advance to the State to next state allowed by the processing mode
   * @return const State & state
   */
  const State & skipChildren();

  /**
   * This operator dereferences the iterator and returns a
   * pointer the node of the graph
   * @return CMathDependencyNode * pNode
   */
  CMathDependencyNode * operator*();

  /**
   * This operator dereferences the iterator and returns a
   * pointer the node of the graph
   * @return CMathDependencyNode * pNode
   */
  CMathDependencyNode * operator->();

  /**
   * Retrieve the pointer to the parent node of the current node if known
   * otherwise NULL
   * @return const CMathDependencyNode * pParent
   */
  const CMathDependencyNode * parent();

  /**
   * Retrieve the current state of the iterator
   * @return const State & state
   */
  const State & state() const;

  /**
   * Retrieve the current nesting level of the iterator
   * @return size_t level
   */
  size_t level() const;

  /**
   * Set the valid states for which the method next() should
   * return
   * @param const Flag & processingModes
   */
  void setProcessingModes(const Flag & processingModes);

  /**
   * Retrieve the valid states for which the method next() should
   * return
   * @return Flag processingModes
   */
  Flag getProcessingModes() const;

  /**
   * A stack of context for each nesting level of the iterator
   */
  std::stack< CStackElement > mStack;

private:
  /**
   * A set of currently visited nodes in the stack used to determine
   * loops or recursive dependencies
   */
  std::set< const CMathDependencyNode * > mVisited;

  /**
   * The iterator type (Dependents or Prerequisites)
   */
  Type mType;

  /**
   * The current state of the iterator
   */
  State mCurrentState;

  /**
   * The flag indicating to which state the iterator should advance. These may be any
   * combination of the enumeration value State. Please note that this flag will
   * always include return and End and Recursive
   */
  Flag mProcessingModes;
};

#endif // COPASI_CMathDependencyNodeIterator
