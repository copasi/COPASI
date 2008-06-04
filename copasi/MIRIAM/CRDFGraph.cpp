// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFGraph.cpp,v $
//   $Revision: 1.31 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/04 14:17:03 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <iostream>
#include <fstream>
#include <sstream>

#include "copasi.h"

#include "model/CReaction.h"
#include "function/CFunction.h"
#include "utilities/CCopasiMessage.h"

#include "CRDFGraph.h"
#include "CRDFNode.h"
#include "CRDFSubject.h"
#include "CRDFObject.h"
#include "CRDFLiteral.h"
#include "CRDFParser.h"
#include "CRDFWriter.h"
#include "CConstants.h"

CRDFGraph::CTriplet::CTriplet(CRDFNode * pSubject, const CRDFPredicate::ePredicateType & predicate, CRDFNode * pObject):
    pSubject(pSubject),
    Predicate(predicate),
    pObject(pObject)
{}

bool CRDFGraph::CTriplet::operator < (const CRDFGraph::CTriplet & rhs) const
  {
    if (Predicate != rhs.Predicate)
      return Predicate < rhs.Predicate;

    if (pSubject != rhs.pSubject)
      return pSubject < rhs.pSubject;

    return pObject < rhs.pObject;
  }

bool CRDFGraph::CTriplet::operator ! () const
  {
    return (Predicate == CRDFPredicate::end ||
            pSubject == NULL ||
            pObject == NULL);
  }

CRDFGraph::CRDFGraph():
    mpAbout(NULL),
    mChanged(false),
    mPrefix2Namespace(),
    mBlankNodeId2Node(),
    mLocalResource2Node(),
    mRemoteResourceNodes(),
    mLiteralNodes()
{}

CRDFGraph::~CRDFGraph()
{
  // Note: mpAbout is not explicitely destroyed since it is contained in the map
  // of resource nodes.

  std::map< std::string, CRDFNode * >::iterator itMap;
  std::map< std::string, CRDFNode * >::iterator endMap;

  for (itMap = mBlankNodeId2Node.begin(), endMap = mBlankNodeId2Node.end();
       itMap != endMap; ++itMap)
    pdelete(itMap->second);

  for (itMap = mLocalResource2Node.begin(), endMap = mLocalResource2Node.end();
       itMap != endMap; ++itMap)
    pdelete(itMap->second);

  std::vector< CRDFNode *>::iterator itVector;
  std::vector< CRDFNode *>::iterator endVector;

  for (itVector = mRemoteResourceNodes.begin(), endVector = mRemoteResourceNodes.end();
       itVector != endVector; ++itVector)
    pdelete(*itVector);

  for (itVector = mLiteralNodes.begin(), endVector = mLiteralNodes.end();
       itVector != endVector; ++itVector)
    pdelete(*itVector);
}

const CRDFNode * CRDFGraph::getAboutNode() const
{return mpAbout;}

const std::map< std::string, std::string > & CRDFGraph::getNameSpaceMap() const
  {return mPrefix2Namespace;}

const std::map< std::string, CRDFNode * > & CRDFGraph::getBlankNodeMap() const
  {return mBlankNodeId2Node;}

const std::map< std::string, CRDFNode * > & CRDFGraph::getLocalResourceNodeMap() const
  {return mLocalResource2Node;}

const std::vector< CRDFNode * > & CRDFGraph::getRemoteResourceNodes() const
  {return mRemoteResourceNodes;}

bool CRDFGraph::guessGraphRoot()
{
  mpAbout = NULL;
  CRDFNode * pNode;

  std::map< std::string, CRDFNode * >::iterator itMap = mLocalResource2Node.begin();
  std::map< std::string, CRDFNode * >::iterator endMap = mLocalResource2Node.end();

  for (;itMap != endMap; ++itMap)
    {
      pNode = itMap->second;

      if (pNode->isSubjectNode() && !pNode->isObjectNode())
        {
          if (mpAbout != NULL)
            {
              mpAbout = NULL;
              break;
            }

          mpAbout = pNode;
        }
    }

  return mpAbout != NULL;
}

bool CRDFGraph::addNameSpace(const std::string & prefix, const std::string & uri)
{
  std::pair< std::map< std::string, std::string >::iterator, bool > inserted =
    mPrefix2Namespace.insert(std::pair< std::string, std::string >(prefix, uri));

  if (inserted.second || (inserted.first->second == uri))
    return true;

  CCopasiMessage(CCopasiMessage::ERROR, MCMiriam + 2,
                 prefix.c_str(), inserted.first->second.c_str(), uri.c_str());
  return false;
}

CRDFGraph::CTriplet CRDFGraph::addTriplet(const CRDFSubject & subject,
    const std::string & predicate,
    const CRDFObject & object)
{
  // Find or create the subject node
  std::map< std::string, CRDFNode * >::iterator found;
  CRDFNode * pSubjectNode = NULL;

  switch (subject.getType())
    {
    case CRDFSubject::RESOURCE:
      if (subject.isLocal())
        {
          found = mLocalResource2Node.find(subject.getResource());
          if (found != mLocalResource2Node.end())
            pSubjectNode = found->second;
          else
            {
              pSubjectNode = new CRDFNode(*this);
              pSubjectNode->setSubject(subject);
              mLocalResource2Node[subject.getResource()] = pSubjectNode;
            }
        }
      else
        {
          pSubjectNode = new CRDFNode(*this);
          pSubjectNode->setSubject(subject);
          mRemoteResourceNodes.push_back(pSubjectNode);
        }
      break;

    case CRDFSubject::BLANK_NODE:
      found = mBlankNodeId2Node.find(subject.getBlankNodeID());
      if (found != mBlankNodeId2Node.end())
        pSubjectNode = found->second;
      else
        {
          pSubjectNode = new CRDFNode(*this);
          pSubjectNode->setSubject(subject);
          mBlankNodeId2Node[subject.getBlankNodeID()] = pSubjectNode;
        }
      break;
    }

  // Find or create the object node
  CRDFNode * pObjectNode = NULL;

  switch (object.getType())
    {
    case CRDFObject::RESOURCE:
      if (object.isLocal())
        {
          found = mLocalResource2Node.find(object.getResource());
          if (found != mLocalResource2Node.end())
            pObjectNode = found->second;
          else
            {
              pObjectNode = new CRDFNode(*this);
              pObjectNode->setObject(object);
              mLocalResource2Node[object.getResource()] = pObjectNode;
            }
        }
      else
        {
          pObjectNode = new CRDFNode(*this);
          pObjectNode->setObject(object);
          mRemoteResourceNodes.push_back(pObjectNode);
        }
      break;

    case CRDFObject::BLANK_NODE:
      found = mBlankNodeId2Node.find(object.getBlankNodeID());
      if (found != mBlankNodeId2Node.end())
        pObjectNode = found->second;
      else
        {
          pObjectNode = new CRDFNode(*this);
          pObjectNode->setObject(object);
          mBlankNodeId2Node[object.getBlankNodeID()] = pObjectNode;
        }
      break;

    case CRDFObject::LITERAL:
      pObjectNode = new CRDFNode(*this);
      pObjectNode->setObject(object);
      mLiteralNodes.push_back(pObjectNode);
      break;
    }

  if (!pSubjectNode->addEdgeInternal(CRDFEdge(predicate, pObjectNode)))
    return CTriplet();

  return CTriplet(pSubjectNode, CRDFPredicate::getPredicateFromURI(predicate), pObjectNode);
}

bool CRDFGraph::removeTriplet(CRDFNode * pSubject,
                              const std::string & predicate,
                              const CRDFNode * pObject)
{return removeTriplet(pSubject, CRDFEdge(predicate, pObject));}

bool CRDFGraph::removeTriplet(CRDFNode * pNode, const CRDFEdge & Edge)
{
  if (pNode == NULL) return false;

  // Since remove edge might destroy the object we save its information now
  const CRDFNode * pObject = Edge.getPropertyNode();
  CRDFObject Object = pObject->getObject();

  // Remove the edge
  if (!pNode->removeEdgeInternal(Edge))
    return false;

  // Determine whether the object was destroyed.
  bool Exists = false;
  switch (Object.getType())
    {
    case CRDFObject::RESOURCE:
      if (Object.isLocal())
        Exists = (mLocalResource2Node.count(Object.getResource()) > 0);
      else
        {
          // Check whether the pointer still exists mRemoteResourceNodes
          std::vector< CRDFNode * >::iterator it = mRemoteResourceNodes.begin();
          std::vector< CRDFNode * >::iterator end = mRemoteResourceNodes.end();
          for (; it != end; ++it)
            if (pObject == *it)
              {
                Exists = true;
                break;
              }
        }
      break;

    case CRDFObject::BLANK_NODE:
      Exists = (mBlankNodeId2Node.count(Object.getBlankNodeID()) > 0);
      break;

    case CRDFObject::LITERAL:
      {
        // Check whther the pointer still exists in mLiteralNodes
        std::vector< CRDFNode * >::iterator it = mLiteralNodes.begin();
        std::vector< CRDFNode * >::iterator end = mLiteralNodes.end();
        for (; it != end; ++it)
          if (pObject == *it)
            {
              Exists = true;
              break;
            }
      }
      break;
    }

  if (!Exists) return true;

  // Check whether the object is other wise referenced
  // Iterate over all local resource nodes
  std::map< std::string, CRDFNode * >::const_iterator itMap = mLocalResource2Node.begin();
  std::map< std::string, CRDFNode * >::const_iterator endMap = mLocalResource2Node.end();
  for (;itMap != endMap; ++itMap)
    {
      // Iterate over all edges
      CRDFNode::const_iterator it = itMap->second->getEdges().begin();
      CRDFNode::const_iterator end = itMap->second->getEdges().end();

      for (; it != end; ++it)
        if (it->second.getPropertyNode() == pObject)
          return true; // The object node is still referenced
    }

  // Iterate over all blank nodes
  itMap = mBlankNodeId2Node.begin();
  endMap = mBlankNodeId2Node.end();
  for (;itMap != endMap; ++itMap)
    {
      // Iterate over all edges
      CRDFNode::const_iterator it = itMap->second->getEdges().begin();
      CRDFNode::const_iterator end = itMap->second->getEdges().end();

      for (; it != end; ++it)
        if (it->second.getPropertyNode() == pObject)
          return true; // The object node is still referenced
    }

  // The object node is no longer referenced we recursively remove all its edges.
  CRDFNode::const_iterator it = pObject->getEdges().begin();
  CRDFNode::const_iterator end = pObject->getEdges().end();
  bool success = true;
  for (; it != end; ++it)
    success &= removeTriplet(const_cast< CRDFNode * >(pObject), it->second);

  // Remove the object from the appropriate container.
  switch (Object.getType())
    {
    case CRDFObject::RESOURCE:
      if (Object.isLocal())
        mLocalResource2Node.count(Object.getResource());
      else
        {
          // Check whether the pointer still exists mRemoteResourceNodes
          std::vector< CRDFNode * >::iterator it = mRemoteResourceNodes.begin();
          std::vector< CRDFNode * >::iterator end = mRemoteResourceNodes.end();
          for (; it != end; ++it)
            if (pObject == *it)
              {
                mRemoteResourceNodes.erase(it);
                break;
              }
        }
      break;

    case CRDFObject::BLANK_NODE:
      mBlankNodeId2Node.erase(Object.getBlankNodeID());
      break;

    case CRDFObject::LITERAL:
      {
        // Check whther the pointer still exists in mLiteralNodes
        std::vector< CRDFNode * >::iterator it = mLiteralNodes.begin();
        std::vector< CRDFNode * >::iterator end = mLiteralNodes.end();
        for (; it != end; ++it)
          if (pObject == *it)
            {
              mLiteralNodes.erase(it);
              break;
            }
      }
      break;
    }
  // Finally delete the object
  delete pObject;

  return success;
}

CRDFGraph::CTriplet CRDFGraph::moveEdge(CRDFNode * pFrom, CRDFNode * pTo, const CRDFEdge & Edge)
{
  if (pFrom == NULL || pTo == NULL) return false;

  bool success = true;

  success &= pFrom->removeEdgeInternal(Edge);
  success &= pTo->addEdgeInternal(Edge);

  CTriplet Triplet;
  if (success)
    {
      Triplet.pSubject = pTo;
      Triplet.Predicate = Edge.getPredicate();
      Triplet.pObject = const_cast< CRDFNode * >(Edge.getPropertyNode());
    }

  return Triplet;
}

CRDFPredicate::Path CRDFGraph::getPredicatePath(const CRDFNode * pNode)
{
  CRDFPredicate::Path Path;
  std::set< const CRDFNode * > Visited;

  // We loop over all local resources as they may be roots of the graph
  std::map< std::string, CRDFNode * >::const_iterator itMap = mLocalResource2Node.begin();
  std::map< std::string, CRDFNode * >::const_iterator endMap = mLocalResource2Node.end();

  const CRDFNode * pCurrent;
  for (;itMap != endMap; ++itMap)
    {
      pCurrent = itMap->second;

      // Check whether we have a root node
      if (pCurrent && pCurrent->isSubjectNode() && !pCurrent->isObjectNode())
        {
          if (pCurrent == pNode ||
              getPredicatePath(pNode, pCurrent, Path, Visited))
            {
              Path.insert(Path.begin(), CRDFPredicate::about);
              break;
            }
        }
    }

  std::cout << "NodePath: " << Path;
  return Path;
}

bool CRDFGraph::getPredicatePath(const CRDFNode * pNode,
                                 const CRDFNode * pCurrent,
                                 CRDFPredicate::Path & path,
                                 std::set< const CRDFNode * > & visited)
{
  // We need to avoid endless loops with the help of visited.
  std::pair< std::set< const CRDFNode * >::iterator, bool > Insert;

  // We need to iterate over the edges and insert each predicate
  CRDFNode::const_iterator it = pCurrent->getEdges().begin();
  CRDFNode::const_iterator end = pCurrent->getEdges().end();

  const CRDFNode * pNext;
  for (; it != end; ++it)
    {
      pNext = it->second.getPropertyNode();

      // Check whether we have allready visited the node.
      Insert = visited.insert(pNext);
      if (!Insert.second)
        return false;

      // Check whether next is the node we are looking for
      if (pNext == pNode)
        {
          // We hide the rdf_li edges
          if (it->second.getPredicate() != CRDFPredicate::rdf_li)
            path.push_back(it->second.getPredicate());
          return true;
        }

      if (getPredicatePath(pNode, pNext, path, visited))
        {
          // We hide the rdf_li edges
          if (it->second.getPredicate() != CRDFPredicate::rdf_li)
            path.insert(path.begin(), it->second.getPredicate());
          return true;
        }
    }

  return false;
}

std::string CRDFGraph::generatedBlankNodeId() const
  {
    static std::set< unsigned C_INT32 > GeneratedIds;

    unsigned C_INT32 Id = 0;
    if (GeneratedIds.rbegin() != GeneratedIds.rend())
      Id = *GeneratedIds.rbegin();

    std::stringstream IdStream;
    IdStream << "genid" << ++Id;

    while (mBlankNodeId2Node.count(IdStream.str()) != 0)
      {
        GeneratedIds.insert(Id);

        IdStream.str("");
        IdStream << "genid" << ++Id;
      }

    GeneratedIds.insert(Id);
    return IdStream.str();
  }

CRDFNode * CRDFGraph::createAboutNode(const std::string & key)
{
  if (!guessGraphRoot())
    {
      CRDFSubject subject;
      mpAbout = new CRDFNode(*this);

      std::string About = "#" + key;
      subject.setType(CRDFSubject::RESOURCE);
      subject.setResource(About, true);
      mpAbout->setSubject(subject);
      mLocalResource2Node[About] = mpAbout;
    }

  return mpAbout;
}

std::set< CRDFGraph::CTriplet > CRDFGraph::getTripletsWithPredicate(const CRDFPredicate::ePredicateType & predicate) const
  {
    std::set< CTriplet > AllTriplets;
    std::set< CTriplet > Triplets;
    CRDFNode * pNode;
    CRDFPredicate::Path Path;
    CTriplet ParentTriplet;
    ParentTriplet.Predicate = CRDFPredicate::about;

    // We must iterate over all nodes which only have the role subject;
    std::map< std::string, CRDFNode * >::const_iterator itMap = mLocalResource2Node.begin();
    std::map< std::string, CRDFNode * >::const_iterator endMap = mLocalResource2Node.end();
    for (;itMap != endMap; ++itMap)
      {
        pNode = itMap->second;

        if (pNode->isSubjectNode() && !pNode->isObjectNode())
          {
            Path = pNode->getPath();
            ParentTriplet.pObject = pNode;
            Triplets = pNode->getTripletsWithPredicate(Path, predicate, ParentTriplet);

            AllTriplets.insert(Triplets.begin(), Triplets.end());
          }
      }

    return AllTriplets;
  }
