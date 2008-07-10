// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CDependencyGraph.cpp,v $
//   $Revision: 1.20 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/07/10 19:59:30 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"
#include "CDependencyGraph.h"
#include <algorithm>

// node

CDependencyGraphNode::CDependencyGraphNode()
{}

CDependencyGraphNode::~CDependencyGraphNode()
{}

void CDependencyGraphNode::addDependent(const unsigned C_INT32 & node_num)
{
  // Ensure that the same node is not added twice
  //  if (find(mDependents.begin(), mDependents.end(), node_num) == mDependents.end())
  //    {
  //      mDependents.push_back(node_num);
  //}
  mDependents.insert(node_num);
}

const std::set <unsigned C_INT32> & CDependencyGraphNode::getDependents() const
  {
    return mDependents;
  }

// dependency graph
CDependencyGraph::CDependencyGraph() {}
CDependencyGraph::~CDependencyGraph() {}

void CDependencyGraph::addNode(const unsigned C_INT32 & node)
{
  if (node >= mNodes.size())
    mNodes.resize(node + 1);

  //  mNodes.push_back(node);
}

void CDependencyGraph::resize(const unsigned C_INT32 & n)
{
  mNodes.resize(n);
}

void CDependencyGraph::addDependent(const unsigned C_INT32 & node, const unsigned C_INT32 & dependent)
{
  addNode(node);
  mNodes[node].addDependent(dependent);
}

const std::set <unsigned C_INT32> & CDependencyGraph::getDependents(const unsigned C_INT32 & node) const
  {
    return mNodes[node].getDependents();
  }

void CDependencyGraph::clear()
{mNodes.clear();}

std::ostream & operator<<(std::ostream &os,
                          const CDependencyGraphNode & d)
{
  std::set <unsigned C_INT32>::const_iterator it;
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
