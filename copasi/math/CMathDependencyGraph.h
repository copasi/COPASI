// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathDependencyGraph.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/21 15:45:57 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CMathDependencyGraph
#define COPASI_CMathDependencyGraph

#include <map>
#include <set>
#include <vector>

#include "copasi/report/CCopasiObject.h"
#include "copasi/math/CMathEnum.h"

class CMathDependencyNode;

class CMathDependencyGraph
{
public:
  typedef std::map< const CObjectInterface *, CMathDependencyNode * > NodeMap;
  typedef NodeMap::iterator iterator;
  typedef NodeMap::const_iterator const_iterator;

  // Operations
  CMathDependencyGraph();

  ~CMathDependencyGraph();

  void clear();

  iterator addObject(const CObjectInterface * pObject);

  bool getUpdateSequence(const CMath::SimulationContextFlag & context,
                         const CObjectInterface::ObjectSet & changedObjects,
                         const CObjectInterface::ObjectSet & requestedObjects,
                         std::vector< CObjectInterface * > & updateSequence);

  void exportDOTFormat(std::ostream & os, const std::string & name) const;

private:
  static std::string getDOTNodeId(const CObjectInterface * pObject);

  // Attributes
  NodeMap mObjects2Nodes;
};

#endif // COPASI_CMathDependencyGraph
