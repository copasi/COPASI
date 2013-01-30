// Copyright (C) 2011 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CObjectDependencyNode
#define COPASI_CObjectDependencyNode

#include <set>
#include <vector>

#include "copasi/report/CCopasiObject.h"
#include "copasi/math/CMathEnum.h"

class CMathDependencyNode
{
  // Operations
private:
  CMathDependencyNode(void);

public:
  /**
   * Specific constructor
   * @param const CObjectInterface * pObject
   */
  CMathDependencyNode(const CObjectInterface * pObject);

  /**
   * Destructor
   */
  ~CMathDependencyNode(void);

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
   * Retrieve the dependents
   * @return std::vector< CMathDependencyNode * > dependents
   */
  std::vector< CMathDependencyNode * > & getDependents();

  /**
   * Update the state of all dependents (and dependents thereof) to changed,
   * @param const CMath::SimulationContextFlag & context
   * @param const CObjectInterface::ObjectSet & changedObjects
   * @return bool success
   */
  bool updateDependentState(const CMath::SimulationContextFlag & context,
                            const CObjectInterface::ObjectSet & changedObjects);

  /**
   * Update the state of all prerequisites (and prerequisites thereof) to requested.
   * @param const CMath::SimulationContextFlag & context
   * @param const CObjectInterface::ObjectSet & changedObjects
   * @return bool success
   */
  bool updatePrerequisiteState(const CMath::SimulationContextFlag & context,
                               const CObjectInterface::ObjectSet & changedObjects);

  /**
   * Build the sequence of objects which need to be updated to calculate the object value.
   * @param const CMath::SimulationContextFlag & context
   * @param std::vector< CObjectInterface * > & updateSequence
   * @return bool success
   */
  bool buildUpdateSequence(const CMath::SimulationContextFlag & context,
                           std::vector< CObjectInterface * > & updateSequence);

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

  // Attributes
private:
  const CObjectInterface * mpObject;
  std::vector< CMathDependencyNode * > mPrerequisites;
  std::vector< CMathDependencyNode * > mDependents;
  bool mChanged;
  bool mRequested;
};

#endif // COPASI_CObjectDependencyNode
