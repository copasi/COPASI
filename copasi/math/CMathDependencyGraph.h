// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CMathDependencyGraph
#define COPASI_CMathDependencyGraph

#include <map>
#include <set>
#include <vector>

#include "copasi/core/CDataObject.h"
#include "copasi/math/CMathEnum.h"

class CMathContainer;
class CMathDependencyNode;

class CMathDependencyGraph
{
public:
  typedef std::map< const CObjectInterface *, CMathDependencyNode * > NodeMap;
  typedef NodeMap::iterator iterator;
  typedef NodeMap::const_iterator const_iterator;

  // Operations
  /**
   * Constructor
   */
  CMathDependencyGraph(CMathContainer * pContainer = NULL);

  /**
   * Copy constructor
   */
  CMathDependencyGraph(const CMathDependencyGraph & src, CMathContainer * pContainer = NULL);

  /**
   * Destructor
   */
  ~CMathDependencyGraph();

  /**
   * Clear the whole dependency tree
   */
  void clear();

  /**
   * Add an object and all its prerequisites to the tree
   * @param const CObjectInterface * pObject
   * @return std::map< const CObjectInterface *, CMathDependencyNode * >::iterator itObject
   */
  iterator addObject(const CObjectInterface * pObject);

  /**
   * Remove an object and all its prerequisites to the tree
   * @param const CObjectInterface * pObject
   */
  void removeObject(const CObjectInterface * pObject);

  /**
   * Remove a prerequisite of an object
   * @param const CObjectInterface * pObject
   * @param const CObjectInterface * pPrerequisite
   */
  void removePrerequisite(const CObjectInterface * pObject, const CObjectInterface * pPrerequisite);

  /**
   * Construct a update sequence for the given context. Please note the calculated objects
   * must be calculated based on the same changed values and context.
   * @param const CCore::SimulationContextFlag & context
   * @param CCore::CUpdateSequence & updateSequence
   * @param const CObjectInterface::ObjectSet & changedObjects
   * @param const CObjectInterface::ObjectSet & requestedObjects
   * @param const CObjectInterface::ObjectSet & calculatedObjects (default: none)
   * @return bool success
   */
  bool getUpdateSequence(CCore::CUpdateSequence & updateSequence,
                         const CCore::SimulationContextFlag & context,
                         const CObjectInterface::ObjectSet & changedObjects,
                         const CObjectInterface::ObjectSet & requestedObjects,
                         const CObjectInterface::ObjectSet & calculatedObjects = CObjectInterface::ObjectSet()) const;

  /**
   * Check whether the given object depends on the changed object in given context
   * @param const CObjectInterface * pObject
   * @param const CCore::SimulationContextFlag & context
   * @param const CObjectInterface * pChangedObject
   * @return bool dependsOn
   */
  bool dependsOn(const CObjectInterface * pObject,
                 const CCore::SimulationContextFlag & context,
                 const CObjectInterface * pChangedObject) const;

  /**
   * Check whether the given object depends on any of the changed objects in given context
   * @param const CObjectInterface * pObject
   * @param const CCore::SimulationContextFlag & context
   * @param const CObjectInterface::ObjectSet & changedObjects
   * @return bool dependsOn
   */
  bool dependsOn(const CObjectInterface * pObject,
                 const CCore::SimulationContextFlag & context,
                 const CObjectInterface::ObjectSet & changedObjects) const;

  /**
   * Check whether the given object depends on the changed object in given context
   * @param const CCore::SimulationContextFlag & context
   * @param const CObjectInterface * pChangedObject
   * @return bool dependsOn
   */
  bool hasCircularDependencies(const CObjectInterface * pObject,
                               const CCore::SimulationContextFlag & context,
                               const CObjectInterface * pChangedObject) const;

  /**
   * Append all objects which directly depend on the given changed objects
   * @param const CObjectInterface::ObjectSet & changedObjects
   * @param CObjectInterface::ObjectSet & dependentObjects
   * @return bool objectsAppendee
   */
  bool appendDirectDependents(const CObjectInterface::ObjectSet & changedObjects,
                              CObjectInterface::ObjectSet & dependentObjects) const;

  /**
   * Append all objects which depend on the given changed objects
   * @param const CObjectInterface::ObjectSet & changedObjects
   * @param CObjectInterface::ObjectSet & dependentObjects
   * @return bool objectsAppendee
   */
  bool appendAllDependents(const CObjectInterface::ObjectSet & changedObjects,
                           CObjectInterface::ObjectSet & dependentObjects,
                           const CObjectInterface::ObjectSet & ignoredObjects = CObjectInterface::ObjectSet()) const;

  /**
   * Relocate the objects in the nodes of the graph.
   * @param const CMathContainer * pContainer
   * @param std::vector< CMath::sRelocate > & relocations
   */
  void relocate(const CMathContainer * pContainer,
                const std::vector< CMath::sRelocate > & relocations);

  void exportDOTFormat(std::ostream & os, const std::string & name) const;

private:
  std::string getDOTNodeId(const CObjectInterface * pObject) const;

  // Attributes
  NodeMap mObjects2Nodes;

  mutable std::map< const CObjectInterface *, size_t > mObject2Index;

  CMathContainer *mpContainer;
};

#endif // COPASI_CMathDependencyGraph
