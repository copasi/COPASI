// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

#ifndef COPASI_CObjectDependencyNode
#define COPASI_CObjectDependencyNode

#include <set>
#include <vector>

#include "copasi/core/CDataObject.h"
#include "copasi/math/CMathEnum.h"
#include "copasi/utilities/CCopasiMessage.h"

class CMathContainer;

class CMathDependencyNode
{
  // Operations
private:
  CMathDependencyNode() = delete;

public:
  /**
   * Specific constructor
   * @param const CObjectInterface * pObject
   */
  CMathDependencyNode(const CObjectInterface * pObject);

  /**
   * Copy constructor
   */
  CMathDependencyNode(const CMathDependencyNode & src);

  /**
   * Destructor
   */
  ~CMathDependencyNode();

  /**
   * Retrieve a pointer to the object the node is representing
   * @return   const CObjectInterface * pObject
   */
  const CObjectInterface * getObject() const;

  /**
   * Add a prerequisite
   * @param CMathDependencyNode * pNode
   */
  void addPrerequisite(CMathDependencyNode * pNode);

  /**
   * Remove a prerequisite
   * @param CMathDependencyNode * pNode
   */
  void removePrerequisite(CMathDependencyNode * pNode);

  /**
   * Retrieve the prerequisites
   * @return std::vector< CMathDependencyNode * > prerequisites
   */
  std::vector< CMathDependencyNode * > & getPrerequisites();

  /**
   * Add a dependent
   * @param CMathDependencyNode * pNode
   */
  void addDependent(CMathDependencyNode * pNode);

  /**
   * Remove a dependent
   * @param CMathDependencyNode * pNode
   */
  void removeDependent(CMathDependencyNode * pNode);

  /**
   * Retrieve the dependents
   * @return std::vector< CMathDependencyNode * > dependents
   */
  std::vector< CMathDependencyNode * > & getDependents();

  /**
   * Update the state of all dependents (and dependents thereof) to changed,
   * @param const CCore::SimulationContextFlag & context
   * @param const CObjectInterface::ObjectSet & changedObjects
   * @param bool ignoreCircularDependecies
   * @return bool success
   */
  bool updateDependentState(const CCore::SimulationContextFlag & context,
                            const CObjectInterface::ObjectSet & changedObjects,
                            bool ignoreCircularDependecies);

  /**
   * Update the state of all prerequisites (and prerequisites thereof) to requested.
   * @param const CCore::SimulationContextFlag & context
   * @param const CObjectInterface::ObjectSet & changedObjects
   * @param bool ignoreCircularDependecies
   * @return bool success
   */
  bool updatePrerequisiteState(const CCore::SimulationContextFlag & context,
                               const CObjectInterface::ObjectSet & changedObjects,
                               bool ignoreCircularDependecies);

  /**
   * Update the state of all prerequisites (and prerequisites thereof) to calculate.
   * @param const CCore::SimulationContextFlag & context
   * @param const CObjectInterface::ObjectSet & changedObjects
   * @param bool ignoreCircularDependecies
   * @return bool success
   */
  bool updateCalculatedState(const CCore::SimulationContextFlag & context,
                             const CObjectInterface::ObjectSet & changedObjects,
                             bool ignoreCircularDependecies);

  /**
   * Update the state of all dependents (and dependents thereof) to changed,
   * @param const CCore::SimulationContextFlag & context
   * @param bool ignoreCircularDependecies
   * @return bool success
   */
  bool updateIgnoredState(const CCore::SimulationContextFlag & context,
                          const CObjectInterface::ObjectSet & changedObjects,
                          bool ignoreCircularDependecies);

  /**
   * Build the sequence of objects which need to be updated to calculate the object value.
   * @param const CCore::SimulationContextFlag & context
   * @param std::vector < CObjectInterface * > & updateSequence
   * @param bool ignoreCircularDependecies
   * @return bool success
   */
  bool buildUpdateSequence(const CCore::SimulationContextFlag & context,
                           std::vector < CObjectInterface * > & updateSequence,
                           bool ignoreCircularDependecies);

  /**
   * Set whether the current node has changed its value
   * @param const bool & changed
   */
  void setChanged(const bool & changed);

  /**
   * Check whether the current nodes value is changed
   * @return const bool & isChanged
   */
  const bool & isChanged() const;

  /**
   * Set whether the current node's value is requested
   * @param const bool & requested
   */
  void setRequested(const bool & requested);

  /**
   * Check whether the current node's value is requested
   * @param const bool & isRequested
   */
  const bool & isRequested() const;

  /**
   * Reset the flags requested and changed
   */
  void reset();

  /**
   * Relocate the objects in the nodes of the graph.
   * @param const CMathContainer * pContainer
   * @param std::vector< CMath::sRelocate > & relocations
   */
  void relocate(const CMathContainer * pContainer,
                const std::vector< CMath::sRelocate > & relocations);

  void remove();

  void updateEdges(const std::map< CMathDependencyNode *, CMathDependencyNode * > & map);

  // Attributes
private:
  bool createMessage(bool ignoreCircularDependecies);

  const CObjectInterface * mpObject;
  std::vector< CMathDependencyNode * > mPrerequisites;
  std::vector< CMathDependencyNode * > mDependents;
  bool mChanged;
  bool mRequested;
};

#endif // COPASI_CObjectDependencyNode
