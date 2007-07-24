// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CDependencyGraph.h,v $
//   $Revision: 1.20 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/07/24 18:40:22 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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
     * @param const unsigned C_INT32 $ node_num The dependency, the node to which the edge connects.
     */
    void addDependent(const unsigned C_INT32 & node_num);

    /**
     * Return a vector of the dependents.
     * @return const std::set <unsigned C_INT32> & A vector of the dependents.
     */

    const std::set <unsigned C_INT32> & getDependents() const;

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

    std::set <unsigned C_INT32> mDependents;
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

    void resize(const unsigned C_INT32 & n);

    /**
     * Add a dependent for a particular node.
     * @param node The number of the node.
     * @param dependent The number of the dependent node.
     */
    void addDependent(const unsigned C_INT32 & node, const unsigned C_INT32 & dependent);

    /**
     * Retrieve a vector of dependents for a given node.
     * @param node The number of the node to access.
     * @return A vector of node numbers.
     */
    const std::set <unsigned C_INT32> &getDependents(const unsigned C_INT32 & node) const;

    void clear();

  private:

    /**
     * Add a node with a given number.
     * @param node The number of the node to add.
     */
    void addNode(const unsigned C_INT32 & node);

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
