// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathDependencyNode.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/29 16:20:16 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMathDependencyNode.h"
#include "CMathObject.h"

CMathDependencyNode::CMathDependencyNode():
    mpObject(NULL),
    mPrerequisites(),
    mDependents(),
    mChanged(false),
    mRequested(false)
{}

CMathDependencyNode::CMathDependencyNode(const CObjectInterface * pObject):
    mpObject(pObject),
    mPrerequisites(),
    mDependents(),
    mChanged(false),
    mRequested(false)
{}

CMathDependencyNode::~CMathDependencyNode()
{}

const CObjectInterface * CMathDependencyNode::getObject() const
{
  return mpObject;
}

void CMathDependencyNode::addPrerequisite(CMathDependencyNode * pObject)
{
  mPrerequisites.insert(pObject);
}

std::set< CMathDependencyNode * > & CMathDependencyNode::getPrerequisites()
{
  return mPrerequisites;
}

void CMathDependencyNode::addDependent(CMathDependencyNode * pObject)
{
  mDependents.insert(pObject);
}

std::set< CMathDependencyNode * > & CMathDependencyNode::getDependents()
{
  return mDependents;
}

void CMathDependencyNode::updateDependentState(const CMath::SimulationContextFlag & context,
    const CObjectInterface::ObjectSet & changedObjects)
{
  std::set< CMathDependencyNode * >::iterator it = mDependents.begin();
  std::set< CMathDependencyNode * >::iterator end = mDependents.end();

  for (; it != end; ++it)
    {
      if (!(*it)->isChanged() &&
          (*it)->getObject()->isPrerequisiteForContext(mpObject, context, changedObjects))
        {
          (*it)->setChanged(true);
          (*it)->updateDependentState(context, changedObjects);
        }
    }
}

void CMathDependencyNode::updatePrerequisiteState(const CMath::SimulationContextFlag & context,
    const CObjectInterface::ObjectSet & changedObjects)
{
  std::set< CMathDependencyNode * >::iterator it = mPrerequisites.begin();
  std::set< CMathDependencyNode * >::iterator end = mPrerequisites.end();

  for (; it != end; ++it)
    {
      if (!(*it)->isRequested() &&
          mpObject->isPrerequisiteForContext((*it)->getObject(), context, changedObjects))
        {
          (*it)->setRequested(true);
          (*it)->updatePrerequisiteState(context, changedObjects);
        }
    }
}

void CMathDependencyNode::buildUpdateSequence(const CMath::SimulationContextFlag & context,
    std::vector< CObjectInterface * > & updateSequence)
{
  if (!mChanged || !mRequested)
    return;

  std::set< CMathDependencyNode * >::iterator itPrerequisites = mPrerequisites.begin();
  std::set< CMathDependencyNode * >::iterator endPrerequisites = mPrerequisites.end();

  for (; itPrerequisites != endPrerequisites; ++itPrerequisites)
    {
      if ((*itPrerequisites)->isChanged())
        return;
    }

  // For an extensive transient value of a dependent species we have 2
  // possible assignments depending on the context.
  //   1) Conversion from the intensive property
  //   2) Dependent mass off a moiety
  //
  // The solution is that the moiety automatically updates the value in conjunction
  // with the dependency graph omitting the value in the update sequence if the context
  // is CMath::UseMoities.

  const CMathObject * pObject = NULL   ;

  if (!(context & CMath::UseMoities) ||
      (pObject = dynamic_cast< const CMathObject *>(mpObject)) == NULL ||
      pObject->getSimulationType() != CMath::Dependent ||
      pObject->getValueType() != CMath::Value)
    {
      updateSequence.push_back(const_cast< CObjectInterface *>(mpObject));
    }

  mChanged = false;

  std::set< CMathDependencyNode * >::iterator it = mDependents.begin();
  std::set< CMathDependencyNode * >::iterator end = mDependents.end();

  for (; it != end; ++it)
    {
      (*it)->buildUpdateSequence(context, updateSequence);
    }
}

void CMathDependencyNode::setChanged(const bool & changed)
{
  mChanged = changed;
}

const bool & CMathDependencyNode::isChanged() const
{
  return mChanged;
}

void CMathDependencyNode::setRequested(const bool & requested)
{
  mRequested = requested;
}

const bool & CMathDependencyNode::isRequested() const
{
  return mRequested;
}

