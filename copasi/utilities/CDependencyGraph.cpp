// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CDependencyGraph.cpp,v $
//   $Revision: 1.22 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:34:54 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

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

CDependencyGraphNode::CDependencyGraphNode():
    mDependents()
{}

CDependencyGraphNode::~CDependencyGraphNode()
{}

void CDependencyGraphNode::addDependent(const size_t & node_num)
{
  // Ensure that the same node is not added twice
  //  if (find(mDependents.begin(), mDependents.end(), node_num) == mDependents.end())
  //    {
  //      mDependents.push_back(node_num);
  //}
  mDependents.insert(node_num);
}

const std::set <size_t> & CDependencyGraphNode::getDependents() const
{
  return mDependents;
}

// dependency graph
CDependencyGraph::CDependencyGraph() {}
CDependencyGraph::~CDependencyGraph() {}

void CDependencyGraph::addNode(const size_t & node)
{
  if (node >= mNodes.size())
    mNodes.resize(node + 1);

  //  mNodes.push_back(node);
}

void CDependencyGraph::resize(const size_t & n)
{
  mNodes.resize(n);
}

void CDependencyGraph::addDependent(const size_t & node, const size_t & dependent)
{
  addNode(node);
  mNodes[node].addDependent(dependent);
}

const std::set <size_t> & CDependencyGraph::getDependents(const size_t & node) const
{
  static std::set< size_t > NoDependents;

  if (mNodes.size() <= node)
    {
      return NoDependents;
    }

  return mNodes[node].getDependents();
}

void CDependencyGraph::clear()
{mNodes.clear();}

std::ostream & operator<<(std::ostream &os,
                          const CDependencyGraphNode & d)
{
  std::set <size_t>::const_iterator it;

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
