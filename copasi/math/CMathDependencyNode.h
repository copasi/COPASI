// Copyright (C) 2011 - 2012 by Pedro Mendes, Virginia Tech Intellectual
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
  CMathDependencyNode(const CObjectInterface * pObject);

  ~CMathDependencyNode(void);

  const CObjectInterface * getObject() const;

  void addPrerequisite(CMathDependencyNode * pNode);

  std::vector< CMathDependencyNode * > & getDependents();

  void addDependent(CMathDependencyNode * pNode);

  std::vector< CMathDependencyNode * > & getPrerequisites();

  bool updateDependentState(const CMath::SimulationContextFlag & context,
                            const CObjectInterface::ObjectSet & changedObjects);

  bool updatePrerequisiteState(const CMath::SimulationContextFlag & context,
                               const CObjectInterface::ObjectSet & changedObjects);

  bool buildUpdateSequence(const CMath::SimulationContextFlag & context,
                           std::vector< CObjectInterface * > & updateSequence);

  void setChanged(const bool & changed);

  const bool & isChanged() const;

  void setRequested(const bool & requested);

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
