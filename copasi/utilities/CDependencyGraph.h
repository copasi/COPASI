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
     * @param node_num The dependency, the node to which the edge connects.
     */
    void addDependent(const C_INT32 node_num);

    /**
     * Return a vector of the dependents.
     * @return A vector of the dependents.
     */

    const std::set <C_INT32> &getDependents() const;

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CDependencyGraphNode & d)
    {
      std::set <C_INT32>::const_iterator it;
      for (it = d.mDependents.begin(); it != d.mDependents.end(); it++)
        os << *it << "  ";

      os << std::endl;

      return os;
    }

  private:
    /**
     * A vector containing the edges for this node. An edge is 
     * specified by the remote node to which it connects.
     */

    std::set <C_INT32> mDependents;
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

    /**
     * Add a dependent for a particular node.
     * @param node The number of the node.
     * @param dependent The number of the dependent node.
     */
    void addDependent(const C_INT32 node, const C_INT32 dependent);

    /**
     * Retrieve a vector of dependents for a given node.
     * @param node The number of the node to access.
     * @return A vector of node numbers.
     */
    const std::set <C_INT32> &getDependents(const C_INT32 node) const;

    void clear();

  private:

    /**
     * Add a node with a given number.
     * @param node The number of the node to add.
     */
    void addNode(const C_INT32 node);

    /**
     * A vector containing the nodes in the graph
     */
    std::vector<CDependencyGraphNode> mNodes;

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CDependencyGraph & d)
    {
      unsigned int i;

      for (i = 0; i < d.mNodes.size(); i++)
        os << d.mNodes[i];

      os << std::endl;

      return os;
    }
  };

#endif // COPASI_CDependencyGraph
