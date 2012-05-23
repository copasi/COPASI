// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathDependencyGraph.cpp,v $
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

#include "CMathDependencyGraph.h"
#include "CMathDependencyNode.h"
#include "CMathObject.h"

#include "report/CCopasiContainer.h"
#include "report/CCopasiObjectName.h"
#include "utilities/CCopasiMessage.h"

CMathDependencyGraph::CMathDependencyGraph():
    mObjects2Nodes()
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

bool CMathDependencyGraph::getUpdateSequence(const CMath::SimulationContextFlag & context,
    const CObjectInterface::ObjectSet & changedObjects,
    const CObjectInterface::ObjectSet & requestedObjects,
    std::vector< CObjectInterface * > & updateSequence)
{
  bool success = true;
  updateSequence.clear();

  CObjectInterface::ObjectSet::const_iterator it = changedObjects.begin();
  CObjectInterface::ObjectSet::const_iterator end = changedObjects.end();

  // Mark all nodes which are changed or need to be calculated
  for (; it != end && success; ++it)
    {
      CMathDependencyNode * pNode = mObjects2Nodes[*it];

      success &= pNode->updateDependentState(context, changedObjects);
    }

  it = requestedObjects.begin();
  end = requestedObjects.end();

  // Mark all nodes which are requested and its prerequisites.
  for (; it != end && success; ++it)
    {
      CMathDependencyNode * pNode = mObjects2Nodes[*it];

      pNode->setRequested(true);
      success &= pNode->updatePrerequisiteState(context, changedObjects);
    }

  it = requestedObjects.begin();
  end = requestedObjects.end();

  for (; it != end && success; ++it)
    {
      CMathDependencyNode * pNode = mObjects2Nodes[*it];

      success &= pNode->buildUpdateSequence(context, updateSequence);
    }

  const_iterator itCheck = mObjects2Nodes.begin();
  const_iterator endCheck = mObjects2Nodes.end();

  for (; itCheck != endCheck; ++itCheck)
    {
      // Reset the dependency nodes for the next call.
      itCheck->second->setChanged(false);
    }

  if (!success)
    {
      updateSequence.clear();

      CCopasiMessage(CCopasiMessage::ERROR, MCMathModel + 3, (*it)->getCN().c_str());
    }

  return success;
}

void CMathDependencyGraph::exportDOTFormat(std::ostream & os, const std::string & name) const
{
  os << "digraph " << name << " {" << std::endl;
  os << "rankdir=LR;" << std::endl;

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
          os << getDOTNodeId(pObject);
          os << " -> ";
          os << getDOTNodeId((*itDep)->getObject());
          os << ";" << std::endl;
        }
    }

  os << "}" << std::endl;
}

// static
std::string CMathDependencyGraph::getDOTNodeId(const CObjectInterface * pObject)
{
  const CCopasiObject * pDataObject = dynamic_cast< const CCopasiObject * >(pObject);
  const CMathObject * pMathObject = dynamic_cast< const CMathObject * >(pObject);

  if (pDataObject == NULL && pMathObject == NULL)
    {
      return "\"Invalid Node\"";
    }

  if (pDataObject == NULL)
    {
      pDataObject = pMathObject->getDataObject();
    }

  if (pDataObject == NULL)
    {
      return "\"Propensity (internal)\"";
    }

  return "\"" + pDataObject->getObjectParent()->getObjectName() + "::" + pDataObject->getObjectName() + "\"";
}
