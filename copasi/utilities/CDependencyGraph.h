// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CDependencyGraph.h,v $
//   $Revision: 1.21 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:34:55 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CDependencyGraph
#define COPASI_CDependencyGraph

#include <iostream>
#include <vector>
#include <set>

/**
 * CDependencyGraphNode describes a node in the dependency graph.
 */
class CDependencyGraphNode
{
public:
  /**
   * Constructor
   */
  CDependencyGraphNode();

  /**
   * The destructor
   */
  ~CDependencyGraphNode();

  /**
   * Add a dependent to the given node, represented by its node number.
   * This then represents an edge in the graph.
   * @param const size_t $ node_num The dependency, the node to which the edge connects.
   */
  void addDependent(const size_t & node_num);

  /**
   * Return a vector of the dependents.
   * @return const std::set <size_t> & A vector of the dependents.
   */

  const std::set <size_t> & getDependents() const;

  /**
   * insert operator
   */
  friend std::ostream & operator<<(std::ostream &os,
                                   const CDependencyGraphNode & d);

private:
  /**
   * A vector containing the edges for this node. An edge is
   * specified by the remote node to which it connects.
   */

  std::set <size_t> mDependents;
};

/**
 * CDependencyGraph describes a dependency graph.
 */

class CDependencyGraph
{
public:
  /**
   * Constructor
   */
  CDependencyGraph();

  /**
   * Desctructor
   */
  ~CDependencyGraph();

  void resize(const size_t & n);

  /**
   * Add a dependent for a particular node.
   * @param node The number of the node.
   * @param dependent The number of the dependent node.
   */
  void addDependent(const size_t & node, const size_t & dependent);

  /**
   * Retrieve a vector of dependents for a given node.
   * @param node The number of the node to access.
   * @return A vector of node numbers.
   */
  const std::set <size_t> &getDependents(const size_t & node) const;

  void clear();

private:

  /**
   * Add a node with a given number.
   * @param node The number of the node to add.
   */
  void addNode(const size_t & node);

  /**
   * A vector containing the nodes in the graph
   */
  std::vector<CDependencyGraphNode> mNodes;

  /**
   * insert operator
   */
  friend std::ostream & operator<<(std::ostream &os,
                                   const CDependencyGraph & d);
};

#endif // COPASI_CDependencyGraph
