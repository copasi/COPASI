// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathDependencyNode.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/23 12:56:39 $
// End CVS Header

// Copyright (C) 2012 - 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMathDependencyNode.h"
#include "CMathObject.h"
#include "CMathDependencyNodeIterator.h"

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
  mPrerequisites.push_back(pObject);
}

std::vector< CMathDependencyNode * > & CMathDependencyNode::getPrerequisites()
{
  return mPrerequisites;
}

void CMathDependencyNode::addDependent(CMathDependencyNode * pObject)
{
  mDependents.push_back(pObject);
}

std::vector< CMathDependencyNode * > & CMathDependencyNode::getDependents()
{
  return mDependents;
}

bool CMathDependencyNode::updateDependentState(const CMath::SimulationContextFlag & context,
    const CObjectInterface::ObjectSet & changedObjects)
{
  CMathDependencyNodeIterator itNode(this, CMathDependencyNodeIterator::Dependents);
  itNode.setProcessingModes(CMathDependencyNodeIterator::Before);

  while (itNode.next())
    {
      // The node itself is not modified.
      if (*itNode == this)
        {
          continue;
        }

      // We are guaranteed that the current node has a parent as the only node without is this,
      // which is handled above.
      if (!itNode->isChanged() &&
          itNode->getObject()->isPrerequisiteForContext(itNode.parent()->getObject(), context, changedObjects))
        {
          itNode->setChanged(true);
        }
      else
        {
          itNode.skipChildren();
        }
    }

  return itNode.state() == CMathDependencyNodeIterator::End;
}

bool CMathDependencyNode::updatePrerequisiteState(const CMath::SimulationContextFlag & context,
    const CObjectInterface::ObjectSet & changedObjects)
{
  CMathDependencyNodeIterator itNode(this, CMathDependencyNodeIterator::Prerequisites);
  itNode.setProcessingModes(CMathDependencyNodeIterator::Before);

  while (itNode.next())
    {
      // The node itself is not modified.
      if (*itNode == this)
        {
          continue;
        }

      // We are guaranteed that the current node has a parent as the only node without is this,
      // which is handled above.
      if (!itNode->isRequested() &&
          itNode.parent()->getObject()->isPrerequisiteForContext(itNode->getObject(), context, changedObjects))
        {
          itNode->setRequested(true);
        }
      else
        {
          itNode.skipChildren();
        }
    }

  return itNode.state() == CMathDependencyNodeIterator::End;
}

bool CMathDependencyNode::buildUpdateSequence(const CMath::SimulationContextFlag & context,
    std::vector< CObjectInterface * > & updateSequence)
{
  if (!mChanged || !mRequested)
    return true;

  CMathDependencyNodeIterator itNode(this, CMathDependencyNodeIterator::Prerequisites);
  itNode.setProcessingModes(CMathDependencyNodeIterator::Before | CMathDependencyNodeIterator::After);

  while (itNode.next())
    {
      switch (itNode.state())
        {
          case CMathDependencyNodeIterator::Before:

            if (!itNode->isChanged() || !itNode->isRequested())
              {
                itNode.skipChildren();
              }

            break;

          case CMathDependencyNodeIterator::After:

            // This check is not needed as unchanged or unrequested nodes
            // are skipped in Before processing.
            if (!itNode->isChanged() || !itNode->isRequested())
              {
                const CMathObject * pObject = NULL;

                // For an extensive transient value of a dependent species we have 2
                // possible assignments depending on the context.
                //   1) Conversion from the intensive property
                //   2) Dependent mass off a moiety
                //
                // The solution is that the moiety automatically updates the value in conjunction
                // with the dependency graph omitting the value in the update sequence if the context
                // is CMath::UseMoities.

                if (!(context & CMath::UseMoities) ||
                    (pObject = dynamic_cast< const CMathObject *>(itNode->getObject())) == NULL ||
                    pObject->getSimulationType() != CMath::Dependent ||
                    pObject->getValueType() != CMath::Value)
                  {
                    updateSequence.push_back(const_cast< CObjectInterface * >(itNode->getObject()));
                  }
              }

            break;

          default:
            break;
        }
    }

  mChanged = false;

  return itNode.state() == CMathDependencyNodeIterator::End;
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

