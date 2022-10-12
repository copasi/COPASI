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

#include "copasi/copasi.h"

#include "CMathDependencyNode.h"
#include "CMathObject.h"
#include "CMathDependencyNodeIterator.h"
#include "CMathContainer.h"

#include "copasi/model/CMetab.h"

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

bool CMathDependencyNode::updateDependentState(const CCore::SimulationContextFlag & context,
    const CObjectInterface::ObjectSet & changedObjects,
    bool ignoreCircularDependecies)
{
  bool success = true;

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
              success &= itNode->createMessage(ignoreCircularDependecies);
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

  return success;
}

bool CMathDependencyNode::updatePrerequisiteState(const CCore::SimulationContextFlag & context,
    const CObjectInterface::ObjectSet & changedObjects,
    bool ignoreCircularDependecies)
{
  bool success = true;

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
              success &= itNode->createMessage(ignoreCircularDependecies);
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
          itNode.parent()->getObject()->isPrerequisiteForContext(itNode->getObject(), context, changedObjects) &&
          changedObjects.find(itNode->getObject()) == changedObjects.end())
        {
          itNode->setRequested(true);
        }
      else
        {
          itNode.skipChildren();
        }
    }

  return success;
}

bool CMathDependencyNode::updateCalculatedState(const CCore::SimulationContextFlag & context,
    const CObjectInterface::ObjectSet & changedObjects,
    bool ignoreCircularDependecies)
{
  bool success = true;

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
              success &= itNode->createMessage(ignoreCircularDependecies);
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

  return success;
}

bool CMathDependencyNode::updateIgnoredState(const CCore::SimulationContextFlag & context,
    const CObjectInterface::ObjectSet & changedObjects,
    bool ignoreCircularDependecies)
{
  bool success = true;

  if (isChanged())
    {
      setChanged(false);

      CMathDependencyNodeIterator itNode(this, CMathDependencyNodeIterator::Dependents);
      itNode.setProcessingModes(CMathDependencyNodeIterator::Before);

      while (itNode.next())
        {
          // If we have a recursive dependency we need make sure that this is due to
          // an intensive/extensive value pair
          if (itNode.state() == CMathDependencyNodeIterator::Recursive)
            {
              if (itNode.parent()->getObject()->isPrerequisiteForContext(itNode->getObject(), context, changedObjects))
                {
                  success &= itNode->createMessage(ignoreCircularDependecies);
                }

              continue;
            }

          // The node itself is not modified.
          if (*itNode == this)
            {
              continue;
            }

          bool PrerequisiteChanged = false;
          std::vector< CMathDependencyNode * >::const_iterator it = itNode->getPrerequisites().begin();
          std::vector< CMathDependencyNode * >::const_iterator end = itNode->getPrerequisites().end();

          for (; it != end; ++it)
            if ((*it)->isChanged() &&
                itNode->getObject()->isPrerequisiteForContext((*it)->getObject(), context, changedObjects))
              {
                PrerequisiteChanged = true;
                break;
              }

          if (!PrerequisiteChanged)
            {
              itNode->updateIgnoredState(context, changedObjects, ignoreCircularDependecies);
            }
        }

      return itNode.state() == CMathDependencyNodeIterator::End;
    }

  return success;
}

bool CMathDependencyNode::buildUpdateSequence(const CCore::SimulationContextFlag & context,
    std::vector < CObjectInterface * > & updateSequence,
    bool ignoreCircularDependecies)
{
  bool success = true;

  if (!mChanged || !mRequested)
    return success;

  CMathDependencyNodeIterator itNode(this, CMathDependencyNodeIterator::Prerequisites);
  itNode.setProcessingModes(CMathDependencyNodeIterator::Flag(CMathDependencyNodeIterator::Before) | CMathDependencyNodeIterator::After);

  while (itNode.next())
    {
      const CMathObject * pMathObject = dynamic_cast< const CMathObject * >(itNode->getObject());

      switch (itNode.state())
        {
          case CMathDependencyNodeIterator::Recursive:
            if (context.isSet(CCore::SimulationContext::UseMoieties) &&
                itNode.parent() != NULL &&
                pMathObject != NULL &&
                pMathObject->getEntityType() == CMath::EntityType::Species &&
                pMathObject->getValueType() == CMath::ValueType::Value &&
                !pMathObject->isInitialValue() &&
                pMathObject->isIntensiveProperty())
              {
                const CMathObject * pMathParent = dynamic_cast< const CMathObject * >(itNode.parent()->getObject());

                if (pMathParent != NULL &&
                    pMathObject->getCorrespondingProperty() == pMathParent &&
                    pMathParent->getSimulationType() == CMath::SimulationType::Dependent)
                  {
                    itNode.skipChildren();
                    continue;
                  }
              }

            success &= itNode->createMessage(ignoreCircularDependecies);
            break;

          case CMathDependencyNodeIterator::Before:

            if (!itNode->isChanged() || !itNode->isRequested())
              {
                itNode.skipChildren();
              }
            else if (context.isSet(CCore::SimulationContext::UseMoieties) &&
                     itNode.parent() != NULL &&
                     pMathObject != NULL &&
                     pMathObject->getEntityType() == CMath::EntityType::Species &&
                     pMathObject->getValueType() == CMath::ValueType::Value &&
                     !pMathObject->isInitialValue() &&
                     pMathObject->isIntensiveProperty())
              {
                const CMathObject * pMathParent = dynamic_cast< const CMathObject * >(itNode.parent()->getObject());

                if (pMathParent != NULL &&
                    pMathObject->getCorrespondingProperty() == pMathParent &&
                    pMathParent->getSimulationType() == CMath::SimulationType::Dependent)
                  {
                    itNode.skipChildren();
                  }
              }

            break;

          case CMathDependencyNodeIterator::After:

            // This check is not needed as unchanged or unrequested nodes
            // are skipped in Before processing.
            if (itNode->isChanged() && itNode->isRequested())
              {
                // For an extensive transient value of a dependent species we have 2
                // possible assignments depending on the context.
                //   1) Conversion from the intensive property
                //   2) Dependent mass off a moiety
                //
                // The solution is that the moiety automatically updates the value in conjunction
                // with the dependency graph omitting the value in the update sequence if the context
                // is CMath::UseMoieties.
                // Therefore, an extensive transient dependent value of a species must not be updated

                if (!context.isSet(CCore::SimulationContext::UseMoieties) ||
                    pMathObject == NULL ||
                    pMathObject->getSimulationType() != CMath::SimulationType::Dependent ||
                    pMathObject->getValueType() != CMath::ValueType::Value ||
                    pMathObject->isInitialValue() ||
                    pMathObject->isIntensiveProperty())
                  {
                    // For math objects we can check whether they can be calculated all others are scheduled.
                    if (pMathObject == NULL ||
                        pMathObject->canCalculateValue())
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

  return success;
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

void CMathDependencyNode::relocate(const CMathContainer * pContainer,
                                   const std::vector< CMath::sRelocate > & relocations)
{
  pContainer->relocateObject(mpObject, relocations);
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

bool CMathDependencyNode::createMessage(bool ignoreCircularDependecies)
{
  if (!ignoreCircularDependecies)
    {
      if (getObject() != NULL)
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCMathModel + 3, getObject()->getCN().c_str());
        }
      else
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCMathModel + 3, "cn not found");
        }
    }

  return ignoreCircularDependecies;
}
