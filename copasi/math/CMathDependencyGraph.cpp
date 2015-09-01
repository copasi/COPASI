// Copyright (C) 2011 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sstream>

#include "copasi.h"

#include "CMathDependencyGraph.h"
#include "CMathDependencyNode.h"
#include "CMathObject.h"

#include "report/CCopasiContainer.h"
#include "report/CCopasiObjectName.h"
#include "utilities/CCopasiMessage.h"

// #define DEBUG_OUTPUT 1

CMathDependencyGraph::CMathDependencyGraph():
  mObjects2Nodes(),
  mObject2Index()
{}

CMathDependencyGraph::~CMathDependencyGraph()
{
  clear();
}

void CMathDependencyGraph::clear()
{
  iterator it = mObjects2Nodes.begin();
  iterator end = mObjects2Nodes.end();

  for (; it != end; ++it)
    {
      delete(it->second);
    }

  mObjects2Nodes.clear();
}

CMathDependencyGraph::iterator CMathDependencyGraph::addObject(const CObjectInterface * pObject)
{
  iterator found = mObjects2Nodes.find(pObject);

  if (found == mObjects2Nodes.end())
    {
      found = mObjects2Nodes.insert(std::make_pair(pObject, new CMathDependencyNode(pObject))).first;

      const CObjectInterface::ObjectSet & Prerequisites = pObject->getPrerequisites();
      CObjectInterface::ObjectSet::const_iterator it = Prerequisites.begin();
      CObjectInterface::ObjectSet::const_iterator end = Prerequisites.end();

      for (; it != end; ++it)
        {
          iterator foundPrerequisite = mObjects2Nodes.find(*it);

          if (foundPrerequisite == mObjects2Nodes.end())
            {
              foundPrerequisite = addObject(*it);
            }

          foundPrerequisite->second->addDependent(found->second);
          found->second->addPrerequisite(foundPrerequisite->second);
        }
    }

  return found;
}

bool CMathDependencyGraph::getUpdateSequence(CObjectInterface::UpdateSequence & updateSequence,
    const CMath::SimulationContextFlag & context,
    const CObjectInterface::ObjectSet & changedObjects,
    const CObjectInterface::ObjectSet & requestedObjects,
    const CObjectInterface::ObjectSet & calculatedObjects) const
{
  bool success = true;

  const_iterator found;
  const_iterator notFound = mObjects2Nodes.end();

  updateSequence.clear();

  CObjectInterface::ObjectSet::const_iterator it = changedObjects.begin();
  CObjectInterface::ObjectSet::const_iterator end = changedObjects.end();

#ifdef DEBUG_OUTPUT
  std::cout << "Changed:" << std::endl;
#endif // DEBUG_OUTPUT

  // Mark all nodes which are changed or need to be calculated
  for (; it != end && success; ++it)
    {
      // Issue 1170: We need to add elements of the stoichiometry, reduced stoichiometry,
      // and link matrices, i.e., we have data objects which may change
#ifdef DEBUG_OUTPUT
      if ((*it)->getDataObject() != *it)
        {
          std::cout << *static_cast< const CMathObject * >(*it) << std::endl;
        }
      else
        {
          std::cout << *static_cast< const CCopasiObject * >(*it) << std::endl;
        }

#endif // DEBUG_OUTPUT

      found = mObjects2Nodes.find(*it);

      if (found != notFound)
        {
          success &= found->second->updateDependentState(context, changedObjects);
        }
    }

  if (!success) goto finish;

  // Mark all nodes which have already been calculated and its prerequisites as not changed.
  it = calculatedObjects.begin();
  end = calculatedObjects.end();

#ifdef DEBUG_OUTPUT
  std::cout << "Up To Date:" << std::endl;
#endif // DEBUG_OUTPUT

  // Mark all nodes which are requested and its prerequisites.
  for (; it != end && success; ++it)
    {
#ifdef DEBUG_OUTPUT

      // Issue 1170: We need to add elements of the stoichiometry, reduced stoichiometry,
      // and link matrices, i.e., we have data objects which may change
      if ((*it)->getDataObject() != *it)
        {
          std::cout << *static_cast< const CMathObject * >(*it) << std::endl;
        }
      else
        {
          std::cout << *static_cast< const CCopasiObject * >(*it) << std::endl;
        }

      std::cout << *static_cast< const CMathObject * >(*it) << std::endl;
#endif // DEBUG_OUTPUT

      found = mObjects2Nodes.find(*it);

      if (found != notFound)
        {
          found->second->setChanged(false);
          success &= found->second->updateCalculatedState(context, changedObjects);
        }
    }

  it = requestedObjects.begin();
  end = requestedObjects.end();

#ifdef DEBUG_OUTPUT
  std::cout << "Requested:" << std::endl;
#endif // DEBUG_OUTPUT

  // Mark all nodes which are requested and its prerequisites.
  for (; it != end && success; ++it)
    {
      // We may have data objects which are ignored as they cannot be calculated
      if ((*it)->getDataObject() == *it)
        {
          // Objects of class CCopasiTimer must always be calculated
          if ((*it)->getDataObject()->getObjectType() == "Timer")
            {
              updateSequence.push_back(const_cast< CObjectInterface * >(*it));
            }

          continue;
        }

#ifdef DEBUG_OUTPUT
      std::cout << *static_cast< const CMathObject * >(*it) << std::endl;
#endif // DEBUG_OUTPUT

      found = mObjects2Nodes.find(*it);

      if (found != notFound)
        {
          found->second->setRequested(true);
          success &= found->second->updatePrerequisiteState(context, changedObjects);
        }
    }

#ifdef DEBUG_OUTPUT
  {
    std::ofstream GetUpdateSequence("GetUpdateSequence.dot");
    exportDOTFormat(GetUpdateSequence, "GetUpdateSequence");
    GetUpdateSequence.close();
  }
#endif // DEBUG_OUTPUT

  if (!success) goto finish;

  it = requestedObjects.begin();
  end = requestedObjects.end();

  for (; it != end && success; ++it)
    {
      // We may have data objects which are ignored as they are always up to date
      if ((*it)->getDataObject() == *it)
        {
          continue;
        }

      found = mObjects2Nodes.find(*it);

      if (found != notFound)
        {
          success &= found->second->buildUpdateSequence(context, updateSequence);
          continue;
        }

      success = false;
    }

  if (!success) goto finish;

finish:
  const_iterator itCheck = mObjects2Nodes.begin();
  const_iterator endCheck = mObjects2Nodes.end();

  for (; itCheck != endCheck; ++itCheck)
    {
      // Reset the dependency nodes for the next call.
      itCheck->second->reset();
    }

  if (!success)
    {
      updateSequence.clear();

      CCopasiMessage(CCopasiMessage::ERROR, MCMathModel + 3, (*it)->getCN().c_str());
    }

#ifdef DEBUG_OUTPUT
  CObjectInterface::UpdateSequence::const_iterator itSeq = updateSequence.begin();
  CObjectInterface::UpdateSequence::const_iterator endSeq = updateSequence.end();

  std::cout << std::endl <<  "Start" << std::endl;

  for (; itSeq != endSeq; ++itSeq)
    {
      if (dynamic_cast< const CMathObject * >(*itSeq))
        {
          std::cout << *static_cast< const CMathObject * >(*itSeq);
        }
      else
        {
          std::cout << (*itSeq)->getCN() << std::endl;
        }
    }

  std::cout << "End" << std::endl;
#endif // DEBUG_OUTPUT

  return success;
}

bool CMathDependencyGraph::dependsOn(const CObjectInterface * pObject,
                                     const CMath::SimulationContextFlag & context,
                                     const CObjectInterface * pChangedObject) const
{
  CObjectInterface::UpdateSequence UpdateSequence;
  CObjectInterface::ObjectSet ChangedObjects;

  if (pChangedObject != NULL)
    {
      ChangedObjects.insert(pChangedObject);
    }

  CObjectInterface::ObjectSet RequestedObjects;

  if (pObject != NULL)
    {
      RequestedObjects.insert(pObject);
    }

  getUpdateSequence(UpdateSequence, context, ChangedObjects, RequestedObjects);

  return !UpdateSequence.empty();
}

void CMathDependencyGraph::exportDOTFormat(std::ostream & os, const std::string & name) const
{
  os << "digraph " << name << " {" << std::endl;
  os << "rankdir=LR;" << std::endl;

  mObject2Index.clear();

  const_iterator it = mObjects2Nodes.begin();
  const_iterator end = mObjects2Nodes.end();

  for (; it != end; ++it)
    {
      const CObjectInterface * pObject = it->second->getObject();

      const std::vector< CMathDependencyNode * > & Dependents = it->second->getDependents();
      std::vector< CMathDependencyNode * >::const_iterator itDep = Dependents.begin();
      std::vector< CMathDependencyNode * >::const_iterator endDep = Dependents.end();

      for (; itDep != endDep; ++itDep)
        {
          os << "\"";
          os << getDOTNodeId(pObject);
          os << ((it->second->isChanged()) ? "\\nC" : "\\no");
          os << ((it->second->isRequested()) ? "R" : "o");
          os << "\"";
          os << " -> ";
          os << "\"";
          os << getDOTNodeId((*itDep)->getObject());
          os << (((*itDep)->isChanged()) ? "\\nC" : "\\no");
          os << (((*itDep)->isRequested()) ? "R" : "o");
          os << "\"";
          os << ";" << std::endl;
        }
    }

  os << "}" << std::endl;
}

// static
std::string CMathDependencyGraph::getDOTNodeId(const CObjectInterface * pObject) const
{
  const CCopasiObject * pDataObject = CObjectInterface::DataObject(pObject);
  const CMathObject * pMathObject = dynamic_cast< const CMathObject * >(pObject);

  if (pDataObject == NULL && pMathObject == NULL)
    {
      return "Invalid Node";
    }

  if (pDataObject == NULL)
    {
      std::ostringstream os;

      switch (pMathObject->getValueType())
        {
          case CMath::ValueTypeUndefined:
            os << "ValueTypeUndefined";
            break;

          case CMath::Value:
            os << "Value";
            break;

          case CMath::Rate:
            os << "ValueRate";
            break;

          case CMath::ParticleFlux:
            os << "ParticleFlux";
            break;

          case CMath::Flux:
            os << "Flux";
            break;

          case CMath::Propensity:
            os << "Propensity";
            break;

          case CMath::TotalMass:
            os << "TotalMass";
            break;

          case CMath::DependentMass:
            os << "DependentMass";
            break;

          case CMath::Discontinuous:
            os << "Discontinuous";
            break;

          case CMath::EventDelay:
            os << "EventDelay";
            break;

          case CMath::EventPriority:
            os << "EventPriority";
            break;

          case CMath::EventAssignment:
            os << "EventAssignment";
            break;

          case CMath::EventTrigger:
            os << "EventTrigger";
            break;

          case CMath::EventRoot:
            os << "EventRoot";
            break;

          case CMath::EventRootState:
            os << "EventRootState";
            break;
        }

      std::map< const CObjectInterface *, size_t >::const_iterator found = mObject2Index.find(pMathObject);

      if (found == mObject2Index.end())
        {
          found = mObject2Index.insert(std::make_pair(pMathObject, mObject2Index.size())).first;
        }

      os << "::"  << found->second;

      return os.str();
    }

  CCopasiObject * pReaction = pDataObject->getObjectAncestor("Reaction");

  if (pReaction != NULL && pReaction != pDataObject->getObjectParent())
    return pReaction->getObjectName() + "::" + pDataObject->getObjectParent()->getObjectName() + "::" + pDataObject->getObjectName();

  return pDataObject->getObjectParent()->getObjectName() + "::" + pDataObject->getObjectName();
}
