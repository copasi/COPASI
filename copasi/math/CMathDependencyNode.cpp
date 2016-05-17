// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMathDependencyNode.h"
#include "CMathObject.h"
#include "CMathDependencyNodeIterator.h"
#include "CMathContainer.h"

#include "model/CMetab.h"

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

CMathDependencyNode::CMathDependencyNode(const CMathDependencyNode & src):
  mpObject(src.mpObject),
  mPrerequisites(src.mPrerequisites),
  mDependents(src.mDependents),
  mChanged(src.mChanged),
  mRequested(src.mRequested)
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

void CMathDependencyNode::removePrerequisite(CMathDependencyNode * pNode)
{
  std::vector< CMathDependencyNode * >::iterator it = mPrerequisites.begin();
  std::vector< CMathDependencyNode * >::iterator end = mPrerequisites.end();

  for (; it != end; ++it)
    if (*it == pNode)
      {
        mPrerequisites.erase(it);
        break;
      }
}

std::vector< CMathDependencyNode * > & CMathDependencyNode::getPrerequisites()
{
  return mPrerequisites;
}

void CMathDependencyNode::addDependent(CMathDependencyNode * pNode)
{
  mDependents.push_back(pNode);
}

void CMathDependencyNode::removeDependent(CMathDependencyNode * pNode)
{
  std::vector< CMathDependencyNode * >::iterator it = mDependents.begin();
  std::vector< CMathDependencyNode * >::iterator end = mDependents.end();

  for (; it != end; ++it)
    if (*it == pNode)
      {
        mDependents.erase(it);
        break;
      }
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
      // If we have a recursive dependency we need make sure that this is due to
      // an intensive/extensive value pair
      if (itNode.state() == CMathDependencyNodeIterator::Recursive)
        {
          if (itNode->getObject()->isPrerequisiteForContext(itNode.parent()->getObject(), context, changedObjects))
            {
              return false;
            }

          continue;
        }

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
      // If we have a recursive dependency we need make sure that this is due to
      // an intensive/extensive value pair
      if (itNode.state() == CMathDependencyNodeIterator::Recursive)
        {
          if (itNode.parent()->getObject()->isPrerequisiteForContext(itNode->getObject(), context, changedObjects))
            {
              return false;
            }

          continue;
        }

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

bool CMathDependencyNode::updateCalculatedState(const CMath::SimulationContextFlag & context,
    const CObjectInterface::ObjectSet & changedObjects)
{
  CMathDependencyNodeIterator itNode(this, CMathDependencyNodeIterator::Prerequisites);
  itNode.setProcessingModes(CMathDependencyNodeIterator::Before);

  while (itNode.next())
    {
      // If we have a recursive dependency we need make sure that this is due to
      // an intensive/extensive value pair
      if (itNode.state() == CMathDependencyNodeIterator::Recursive)
        {
          if (itNode.parent()->getObject()->isPrerequisiteForContext(itNode->getObject(), context, changedObjects))
            {
              return false;
            }

          continue;
        }

      // The node itself is not modified.
      if (*itNode == this)
        {
          continue;
        }

      // We are guaranteed that the current node has a parent as the only node without is this,
      // which is handled above.
      if (itNode->isChanged() &&
          itNode.parent()->getObject()->isPrerequisiteForContext(itNode->getObject(), context, changedObjects))
        {
          itNode->setChanged(false);
        }
      else
        {
          itNode.skipChildren();
        }
    }

  return itNode.state() == CMathDependencyNodeIterator::End;
}

bool CMathDependencyNode::buildUpdateSequence(const CMath::SimulationContextFlag & context,
    CObjectInterface::UpdateSequence & updateSequence)
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
            if (itNode->isChanged() && itNode->isRequested())
              {
                const CObjectInterface * pObject = itNode->getObject();
                const CMathObject * pMathObject = dynamic_cast< const CMathObject *>(pObject);
                const CParticleReference * pParticleNumber = NULL;

                // For an extensive transient value of a dependent species we have 2
                // possible assignments depending on the context.
                //   1) Conversion from the intensive property
                //   2) Dependent mass off a moiety
                //
                // The solution is that the moiety automatically updates the value in conjunction
                // with the dependency graph omitting the value in the update sequence if the context
                // is CMath::UseMoieties.

                if (!(context & CMath::UseMoieties) ||
                    (pMathObject == NULL &&
                     (pParticleNumber = dynamic_cast< const CParticleReference *>(pObject)) == NULL) ||
                    (pMathObject != NULL &&
                     pMathObject->getCorrespondingProperty() != static_cast< const CMathObject *>(mpObject) &&
                     (pMathObject->getSimulationType() != CMath::Dependent ||
                      pMathObject->getValueType() != CMath::Value)) ||
                    (pParticleNumber != NULL &&
                     !static_cast< const CMetab * >(pParticleNumber->getObjectParent())->isDependent()))
                  {
                    // Only Math Objects with expressions can be updated.
                    if (pMathObject != NULL &&
                        pMathObject->getExpressionPtr() != NULL)
                      {
                        updateSequence.push_back(const_cast< CObjectInterface * >(itNode->getObject()));
                      }

                    itNode->setChanged(false);
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

void CMathDependencyNode::reset()
{
  mChanged = false;
  mRequested = false;
}

void CMathDependencyNode::relocate(const std::vector< CMath::sRelocate > & relocations)
{
  CMathContainer::relocateObject(mpObject, relocations);
}

void CMathDependencyNode::remove()
{
  std::vector< CMathDependencyNode * >::iterator it = mPrerequisites.begin();
  std::vector< CMathDependencyNode * >::iterator end = mPrerequisites.end();

  for (; it != end; ++it)
    {
      (*it)->removeDependent(this);
    }

  it = mDependents.begin();
  end = mDependents.end();

  for (; it != end; ++it)
    {
      (*it)->removePrerequisite(this);
    }
}

void CMathDependencyNode::updateEdges(const std::map< CMathDependencyNode *, CMathDependencyNode * > & map)
{
  std::vector< CMathDependencyNode * >::iterator it = mPrerequisites.begin();
  std::vector< CMathDependencyNode * >::iterator end = mPrerequisites.end();

  for (; it != end; ++it)
    {
      std::map< CMathDependencyNode *, CMathDependencyNode * >::const_iterator found = map.find(*it);
      *it = found->second;
    }

  it = mDependents.begin();
  end = mDependents.end();

  for (; it != end; ++it)
    {
      std::map< CMathDependencyNode *, CMathDependencyNode * >::const_iterator found = map.find(*it);
      *it = found->second;
    }
}
