#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "CDependencyGraph.h"
#include <algorithm>

// node

CDependencyGraphNode::CDependencyGraphNode()
{}

CDependencyGraphNode::CDependencyGraphNode(C_INT32 C_UNUSED(node_number))
{}

CDependencyGraphNode::~CDependencyGraphNode()
{}

void CDependencyGraphNode::addDependent(C_INT32 node_num)
{
  // Ensure that the same node is not added twice
  //  if (find(mDependents.begin(), mDependents.end(), node_num) == mDependents.end())
  //    {
  //      mDependents.push_back(node_num);
  //}

  mDependents.insert(node_num);
}

//const std::vector<C_INT32> & CDependencyGraphNode::getDependents()

const std::set <C_INT32> & CDependencyGraphNode::getDependents()
{
  return mDependents;
}

// dependency graph
CDependencyGraph::CDependencyGraph() {}
CDependencyGraph::~CDependencyGraph() {}

void CDependencyGraph::addNode(C_INT32 node)
{
  if (node >= mNodes.size())
    mNodes.resize(node + 1);

  //  mNodes.push_back(node);
}

void CDependencyGraph::addDependent(C_INT32 node, C_INT32 dependent)
{
  addNode(node);
  mNodes[node].addDependent(dependent);
}

const std::set <C_INT32> & CDependencyGraph::getDependents(C_INT32 node)
{
  return mNodes[node].getDependents();
}

#ifdef TEST_DEPENDENCY_GRAPH

int main(int argc, char **argv)
{
  const C_INT32 NNODES = 4;
  const C_INT32 NDEPS = 4;
  C_INT32 inarr[NNODES][NDEPS] = {{0, 1, 2, 0},
                                  {1, 1, 3, 0},
                                  {2, 3, 0, 1},
                                  {3, 0, 1, 2}};
  std::cout << "Creating dependency graph\n";
  CDependencyGraph dg;
  C_INT32 i = 0, j = 0;

  for (i = 0; i < NNODES; i++)
    {
      std::cout << "Adding node " << i << " with dependents ";
      dg.addNode(i);

      for (j = 0; j < NDEPS; j++)
        {
          std::cout << inarr[i][j] << " ";
          dg.addDependent(i, inarr[i][j]);
        }

      std::cout << std::endl;
    }

  // Display the vector of dependents for each node
  for (i = 0; i < NNODES; i++)
    {
      j = 0;
      std::cout << "Node: " << i << " Dependents: ";
      //      std::vector<C_INT32> depvec = dg.getDependents(i);

      std::set <C_INT32> depset = dg.getDependents(i);

      //      while (j < depvec.size())
      //        {
      //          std::cout << depvec[j] << " ";
      //          j++;
      //}
      for (std::set <C_INT32>::iterator iter = depset.begin(); iter != depset.end(); iter++)
        {
          std::cout << *iter << " ";
        }

      std::cout << std::endl;
    }
}

#endif // TEST_DEPENDENCY_GRAPH
