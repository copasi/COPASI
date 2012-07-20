// Copyright (C) 2011 - 2012 by Pedro Mendes, Virginia Tech Intellectual
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
