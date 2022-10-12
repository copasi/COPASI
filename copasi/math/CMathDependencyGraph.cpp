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

#include <sstream>

#include "copasi/copasi.h"

#include "CMathDependencyGraph.h"
#include "CMathDependencyNode.h"
#include "CMathObject.h"
#include "CMathContainer.h"

#include "copasi/core/CDataContainer.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/optimization/COptItem.h"

// Uncomment this line below to get debug print out.
// #define DEBUG_OUTPUT 1

CMathDependencyGraph::CMathDependencyGraph(CMathContainer * pContainer):
  mObjects2Nodes(),
  mObject2Index(),
  mpContainer(pContainer)
{}

CMathDependencyGraph::CMathDependencyGraph(const CMathDependencyGraph & src,
    CMathContainer * pContainer):
  mObjects2Nodes(),
  mObject2Index(),
  mpContainer(pContainer != NULL ? pContainer : src.mpContainer)
{
  std::map< CMathDependencyNode *, CMathDependencyNode * > Src2New;

  NodeMap::const_iterator itSrc = src.mObjects2Nodes.begin();
  NodeMap::const_iterator endSrc = src.mObjects2Nodes.end();

  for (; itSrc != endSrc; ++itSrc)
    {
      CMathDependencyNode * pNode = new CMathDependencyNode(*itSrc->second);
      mObjects2Nodes.insert(std::make_pair(itSrc->first, pNode));
      Src2New.insert(std::make_pair(itSrc->second, pNode));
    }

  NodeMap::iterator it = mObjects2Nodes.begin();
  NodeMap::iterator end = mObjects2Nodes.end();

  for (; it != end; ++it)
    {
      it->second->updateEdges(Src2New);
    }
}

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
      delete (it->second);
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

void CMathDependencyGraph::removeObject(const CObjectInterface * pObject)
{
  iterator found = mObjects2Nodes.find(pObject);

  if (found == mObjects2Nodes.end()) return;

  found->second->remove();
  delete found->second;
  mObjects2Nodes.erase(found);
}

void CMathDependencyGraph::removePrerequisite(const CObjectInterface * pObject, const CObjectInterface * pPrerequisite)
{
  iterator foundObject = mObjects2Nodes.find(pObject);
  iterator foundPrerequisite = mObjects2Nodes.find(pPrerequisite);

  if (foundObject == mObjects2Nodes.end() ||
      foundPrerequisite == mObjects2Nodes.end())
    return;

  foundObject->second->removePrerequisite(foundPrerequisite->second);
  foundPrerequisite->second->removeDependent(foundObject->second);
}

bool CMathDependencyGraph::getUpdateSequence(CCore::CUpdateSequence & updateSequence,
    const CCore::SimulationContextFlag & context,
    const CObjectInterface::ObjectSet & changedObjects,
    const CObjectInterface::ObjectSet & requestedObjects,
    const CObjectInterface::ObjectSet & calculatedObjects) const
{
  bool success = true;

  const_iterator found;
  const_iterator notFound = mObjects2Nodes.end();

  std::vector<CObjectInterface*> UpdateSequence;

#ifdef DEBUG_OUTPUT
  std::cout << "Changed:" << std::endl;
#endif // DEBUG_OUTPUT

  // The object triggering recalculation of random function is always changed if it exists
  found = mObjects2Nodes.find(mpContainer->getRandomObject());

  if (found != notFound)
    {
      success &= found->second->updateDependentState(context, changedObjects, true);
#ifdef DEBUG_OUTPUT
      std::cout << *static_cast< const CDataObject * >(mpContainer->getRandomObject()) << std::endl;
#endif // DEBUG_OUTPUT
    }

  CObjectInterface::ObjectSet::const_iterator it = changedObjects.begin();
  CObjectInterface::ObjectSet::const_iterator end = changedObjects.end();

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
          std::cout << *static_cast< const CDataObject * >(*it) << std::endl;
        }

#endif // DEBUG_OUTPUT

      found = mObjects2Nodes.find(*it);

      if (found != notFound)
        {
          success &= found->second->updateDependentState(context, changedObjects, true);
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
          std::cout << *static_cast< const CDataObject * >(*it) << std::endl;
        }

      std::cout << *static_cast< const CMathObject * >(*it) << std::endl;
#endif // DEBUG_OUTPUT

      found = mObjects2Nodes.find(*it);

      if (found != notFound)
        {
          found->second->setChanged(false);
          success &= found->second->updateCalculatedState(context, changedObjects, true);
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
#ifdef DEBUG_OUTPUT
      std::cout << *it << std::endl;
#endif // DEBUG_OUTPUT

      if (*it == NULL)
        {
          success = false; // we should not have NULL elements here
          break;
        }

      // Objects of class CCopasiTimer must always be calculated
      if ((*it)->getDataObject() != NULL &&
          (*it)->getDataObject()->getObjectType() == "Timer")
        {
          UpdateSequence.push_back(const_cast< CObjectInterface * >(*it));
          continue;
        }

#ifdef DEBUG_OUTPUT

      if ((*it)->getDataObject() == *it)
        {
          std::cout << (*it)->getCN() << std::endl;
        }
      else
        {
          std::cout << *static_cast< const CMathObject * >(*it) << std::endl;
        }

#endif // DEBUG_OUTPUT

      found = mObjects2Nodes.find(*it);

      if (found != notFound)
        {
          found->second->setRequested(true);
          success &= found->second->updatePrerequisiteState(context, changedObjects, true);
        }
    }

  if (!success) goto finish;

#ifdef DEBUG_OUTPUT
  {
    std::ofstream GetUpdateSequence("GetUpdateSequence.dot");
    exportDOTFormat(GetUpdateSequence, "GetUpdateSequence");
    GetUpdateSequence.close();
  }
#endif // DEBUG_OUTPUT

  it = requestedObjects.begin();
  end = requestedObjects.end();

  for (; it != end; ++it)
    {
      found = mObjects2Nodes.find(*it);

      if (found != notFound)
        {
          success &= found->second->buildUpdateSequence(context, UpdateSequence, false);
          continue;
        }

      // This is not an error we may have objects which are not part of the dependency tree
      // success = false;
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
      UpdateSequence.clear();
    }

  updateSequence.setMathContainer(mpContainer);
  updateSequence = UpdateSequence;

#ifdef DEBUG_OUTPUT
  CCore::CUpdateSequence::const_iterator itSeq = updateSequence.begin();
  CCore::CUpdateSequence::const_iterator endSeq = updateSequence.end();

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
                                     const CCore::SimulationContextFlag & context,
                                     const CObjectInterface * pChangedObject) const
{
  CCore::CUpdateSequence UpdateSequence;
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

bool CMathDependencyGraph::dependsOn(const CObjectInterface * pObject,
                                     const CCore::SimulationContextFlag & context,
                                     const CObjectInterface::ObjectSet & changedObjects) const
{
  CCore::CUpdateSequence UpdateSequence;
  CObjectInterface::ObjectSet RequestedObjects;

  if (pObject != NULL)
    {
      RequestedObjects.insert(pObject);
    }

  getUpdateSequence(UpdateSequence, context, changedObjects, RequestedObjects);

  return !UpdateSequence.empty();
}

bool CMathDependencyGraph::hasCircularDependencies(const CObjectInterface * pObject,
    const CCore::SimulationContextFlag & context,
    const CObjectInterface * pChangedObject) const
{
  CCore::CUpdateSequence UpdateSequence;
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

  size_t Size = CCopasiMessage::size();

  bool hasCircularDependencies = !getUpdateSequence(UpdateSequence, context, ChangedObjects, RequestedObjects);

  while (CCopasiMessage::size() > Size)
    {
      CCopasiMessage::getLastMessage();
    }

  return hasCircularDependencies;
}

bool CMathDependencyGraph::appendDirectDependents(const CObjectInterface::ObjectSet & changedObjects,
    CObjectInterface::ObjectSet & dependentObjects) const
{
  dependentObjects.erase(NULL);
  size_t Size = dependentObjects.size();

  CObjectInterface::ObjectSet::const_iterator it = changedObjects.begin();
  CObjectInterface::ObjectSet::const_iterator end = changedObjects.end();

  for (; it != end; ++it)
    {
      NodeMap::const_iterator found = mObjects2Nodes.find(*it);

      if (found != mObjects2Nodes.end())
        {
          std::vector< CMathDependencyNode * >::const_iterator itNode = found->second->getDependents().begin();
          std::vector< CMathDependencyNode * >::const_iterator endNode = found->second->getDependents().end();

          for (; itNode != endNode; ++itNode)
            {
              dependentObjects.insert((*itNode)->getObject());
            }
        }
    }

  dependentObjects.erase(NULL);

  return dependentObjects.size() > Size;
}

bool CMathDependencyGraph::appendAllDependents(const CObjectInterface::ObjectSet & changedObjects,
    CObjectInterface::ObjectSet & dependentObjects,
    const CObjectInterface::ObjectSet & ignoredObjects) const
{
  bool success = true;

  dependentObjects.erase(NULL);
  size_t Size = dependentObjects.size();

  const_iterator found;
  const_iterator notFound = mObjects2Nodes.end();

  std::vector<CObjectInterface*> UpdateSequence;

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
          std::cout << *static_cast< const CDataObject * >(*it) << std::endl;
        }

#endif // DEBUG_OUTPUT

      found = mObjects2Nodes.find(*it);

      if (found != notFound)
        {
          success &= found->second->updateDependentState(CCore::SimulationContext::Default, changedObjects, true);
        }
    }

  // Mark all nodes which are ignored and thus break dependencies.
  it = ignoredObjects.begin();
  end = ignoredObjects.end();

#ifdef DEBUG_OUTPUT
  std::cout << "Ignored:" << std::endl;
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
          std::cout << *static_cast< const CDataObject * >(*it) << std::endl;
        }

#endif // DEBUG_OUTPUT

      found = mObjects2Nodes.find(*it);

      if (found != notFound)
        {
          success &= found->second->updateIgnoredState(CCore::SimulationContext::Default, changedObjects, true);
        }
    }

#ifdef DEBUG_OUTPUT
  {
    std::ofstream AppendAllDependents("AppendAllDependents.dot");
    exportDOTFormat(AppendAllDependents, "AppendAllDependents");
    AppendAllDependents.close();
  }
#endif // DEBUG_OUTPUT

  const_iterator itCheck = mObjects2Nodes.begin();
  const_iterator endCheck = mObjects2Nodes.end();

  for (; itCheck != endCheck; ++itCheck)
    {
      if (itCheck->second->isChanged())
        {
          dependentObjects.insert(itCheck->first);
        }

      // Reset the dependency nodes for the next call.
      itCheck->second->reset();
    }

  dependentObjects.erase(NULL);

  return dependentObjects.size() > Size;
}

void CMathDependencyGraph::relocate(const CMathContainer * pContainer,
                                    const std::vector< CMath::sRelocate > & relocations)
{
  NodeMap Objects2Nodes;

  const_iterator it = mObjects2Nodes.begin();
  const_iterator end = mObjects2Nodes.end();

  std::vector< const CObjectInterface * > ToBeRemoved;

  for (; it != end; ++it)
    {
      const CObjectInterface * pObject = it->first;
      pContainer->relocateObject(pObject, relocations);

      if (pObject != NULL)
        {
          it->second->relocate(pContainer, relocations);
          Objects2Nodes.insert(std::make_pair(pObject, it->second));
        }
      else
        {
          ToBeRemoved.push_back(it->first);
        }
    }

  std::vector< const CObjectInterface * >::const_iterator itRemove = ToBeRemoved.begin();
  std::vector< const CObjectInterface * >::const_iterator endRemove = ToBeRemoved.end();

  for (; itRemove != endRemove; ++itRemove)
    {
      removeObject(*itRemove);
    }

  mObjects2Nodes = Objects2Nodes;
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
  const CDataObject * pDataObject = CObjectInterface::DataObject(pObject);
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
          case CMath::ValueType::Undefined:
            os << "ValueTypeUndefined";
            break;

          case CMath::ValueType::Value:
            os << "Value";
            break;

          case CMath::ValueType::Rate:
            os << "ValueRate";
            break;

          case CMath::ValueType::ParticleFlux:
            os << "ParticleFlux";
            break;

          case CMath::ValueType::Flux:
            os << "Flux";
            break;

          case CMath::ValueType::Propensity:
            os << "Propensity";
            break;

          case CMath::ValueType::TotalMass:
            os << "TotalMass";
            break;

          case CMath::ValueType::DependentMass:
            os << "DependentMass";
            break;

          case CMath::ValueType::Discontinuous:
            os << "Discontinuous";
            break;

          case CMath::ValueType::EventDelay:
            os << "EventDelay";
            break;

          case CMath::ValueType::EventPriority:
            os << "EventPriority";
            break;

          case CMath::ValueType::EventAssignment:
            os << "EventAssignment";
            break;

          case CMath::ValueType::EventTrigger:
            os << "EventTrigger";
            break;

          case CMath::ValueType::EventRoot:
            os << "EventRoot";
            break;

          case CMath::ValueType::EventRootState:
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

  CDataObject * pReaction = pDataObject->getObjectAncestor("Reaction");

  if (pReaction != NULL && pReaction != pDataObject->getObjectParent())
    return pReaction->getObjectName() + "::" + pDataObject->getObjectParent()->getObjectName() + "::" + pDataObject->getObjectName();

  CDataObject * pEvent = pDataObject->getObjectAncestor("Event");

  if (pEvent != NULL && pEvent != pDataObject->getObjectParent())
    return pEvent->getObjectName() + "::Assignment::" + pDataObject->getObjectParent()->getObjectName();

  if (dynamic_cast< const COptItem * >(pDataObject))
    return "OptItem::" + static_cast< const COptItem * >(pDataObject)->getObject()->getObjectDisplayName();

  return pDataObject->getObjectParent()->getObjectName() + "::" + pDataObject->getObjectName();
}
