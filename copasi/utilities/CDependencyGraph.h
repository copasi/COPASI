#ifndef COPASI_CDependencyGraph
#define COPASI_CDependencyGraph

#include <vector>
#include "../copasi.h"
/**
 * CDependencyGraphNode describes a node in the dependency graph.
 */
class CDependencyGraphNode
{
 public:
    /**
     * Constructor
     * @param react_num The number describing this node (usually corresponds to reaction number)
     */
    CDependencyGraphNode(C_INT32 num);
    
    /**
     * The destructor
     */
    ~CDependencyGraphNode();
    
    /**
     * Add a dependent to the given node, represented by its node number. 
     * This then represents an edge in the graph.
     * @param node_num The dependency, the node to which the edge connects.
     */
    void addDependent(C_INT32 node_num);

    /** 
     * Return a vector of the dependents.
     * @return A vector of the dependents.
     */
    const vector<C_INT32> &getDependents();

 private:
    /**
     * The number of this node.
     */
    C_INT32 mNodeNumber;
    /**
     * A vector containing the edges for this node. An edge is 
     * specified by the remote node to which it connects.
     */
    vector<C_INT32> mDependents;
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
      * Add a node with a given number.
      * @param node The number of the node to add.
      */
     void addNode(C_INT32 node);
     
     /**
      * Add a dependent for a particular node.
      * @param node The number of the node.
      * @param dependent The number of the dependent node.
      */
     void addDependent(C_INT32 node, C_INT32 dependent);

     /** 
      * Retrieve a vector of dependents for a given node.
      * @param node The number of the node to access.
      * @return A vector of node numbers.
      */
     const vector<C_INT32> &getDependents(C_INT32 node);

 private:
     /**
      * A vector containing the nodes in the graph
      */
     vector<CDependencyGraphNode> mNodes;
};

#endif // COPASI_CDependencyGraph
