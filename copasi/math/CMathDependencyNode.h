// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathDependencyNode.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/29 16:20:16 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
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

  std::set< CMathDependencyNode * > & getDependents();

  void addDependent(CMathDependencyNode * pNode);

  std::set< CMathDependencyNode * > & getPrerequisites();

  void updateDependentState(const CMath::SimulationContextFlag & context,
                            const CObjectInterface::ObjectSet & changedObjects);

  void updatePrerequisiteState(const CMath::SimulationContextFlag & context,
                               const CObjectInterface::ObjectSet & changedObjects);

  void buildUpdateSequence(const CMath::SimulationContextFlag & context,
                           std::vector< CObjectInterface * > & updateSequence);

  void setChanged(const bool & changed);

  const bool & isChanged() const;

  void setRequested(const bool & requested);

  const bool & isRequested() const;

  // Attributes
private:
  const CObjectInterface * mpObject;
  std::set< CMathDependencyNode * > mPrerequisites;
  std::set< CMathDependencyNode * > mDependents;
  bool mChanged;
  bool mRequested;
};

#endif // COPASI_CObjectDependencyNode
