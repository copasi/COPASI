/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CDependencyGraph.cpp,v $
   $Revision: 1.15 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/02 11:52:02 $
   End CVS Header */

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "CDependencyGraph.h"
#include <algorithm>

// node

CDependencyGraphNode::CDependencyGraphNode()
{}

CDependencyGraphNode::~CDependencyGraphNode()
{}

void CDependencyGraphNode::addDependent(const C_INT32 node_num)
{
  // Ensure that the same node is not added twice
  //  if (find(mDependents.begin(), mDependents.end(), node_num) == mDependents.end())
  //    {
  //      mDependents.push_back(node_num);
  //}
  mDependents.insert(node_num);
}

const std::set <C_INT32> & CDependencyGraphNode::getDependents() const
  {
    return mDependents;
  }

// dependency graph
CDependencyGraph::CDependencyGraph() {}
CDependencyGraph::~CDependencyGraph() {}

void CDependencyGraph::addNode(const C_INT32 node)
{
  if (node >= mNodes.size())
    mNodes.resize(node + 1);

  //  mNodes.push_back(node);
}

void CDependencyGraph::resize(C_INT32 n)
{
  mNodes.resize(n);
}

void CDependencyGraph::addDependent(const C_INT32 node, const C_INT32 dependent)
{
  addNode(node);
  mNodes[node].addDependent(dependent);
}

const std::set <C_INT32> & CDependencyGraph::getDependents(C_INT32 node) const
  {
    return mNodes[node].getDependents();
  }

void CDependencyGraph::clear()
{mNodes.clear();}

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

std::ostream & operator<<(std::ostream &os,
                          const CDependencyGraphNode & d)
{
  std::set <C_INT32>::const_iterator it;
  for (it = d.mDependents.begin(); it != d.mDependents.end(); it++)
    os << *it << "  ";

  os << std::endl;

  return os;
}

std::ostream & operator<<(std::ostream &os,
                          const CDependencyGraph & d)
{
  unsigned int i;

  for (i = 0; i < d.mNodes.size(); i++)
    os << d.mNodes[i];

  os << std::endl;

  return os;
}
