// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFGraph.cpp,v $
//   $Revision: 1.33 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/10 20:31:11 $
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
#include "CRDFSubject.h"
#include "CRDFObject.h"
#include "CRDFLiteral.h"
#include "CRDFParser.h"
#include "CRDFWriter.h"
#include "CConstants.h"

CRDFGraph::CRDFGraph():
    mpAbout(NULL),
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

CRDFTriplet CRDFGraph::addTriplet(const CRDFSubject & subject,
                                  const CRDFPredicate & predicate,
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

  return pSubjectNode->addEdge(predicate, pObjectNode);
}

bool CRDFGraph::addTriplet(const CRDFTriplet & triplet)
{
  std::cout << "Adding Triplet: " << triplet;

  if (!triplet)
    return false;

  std::pair< std::set< CRDFTriplet >::iterator, bool> Insert = mTriplets.insert(triplet);

  if (Insert.second)
    {
      mSubject2Triplet.insert(std::pair< CRDFNode *, CRDFTriplet >(triplet.pSubject, triplet));
      mObject2Triplet.insert(std::pair< CRDFNode *, CRDFTriplet >(triplet.pObject, triplet));
      mPredicate2Triplet.insert(std::pair< CRDFPredicate, CRDFTriplet >(triplet.Predicate, triplet));
    }

  return true;
}

void CRDFGraph::removeTriplet(CRDFNode * pSubject,
                              const CRDFPredicate & predicate,
                              CRDFNode * pObject)
{pSubject->removeEdge(predicate, pObject);}

void CRDFGraph::removeTriplet(const CRDFTriplet & triplet)
{
  std::cout << "Removing Triplet: " << triplet;

  if (!triplet)
    return;

  // Remove the triplet
  mTriplets.erase(triplet);

  // Remove its references
  // Subject2Triplets
  std::pair< Node2Triplet::iterator, Node2Triplet::iterator> Range = mSubject2Triplet.equal_range(triplet.pSubject);
  for (; Range.first != Range.second; ++Range.first)
    if (Range.first->second == triplet)
      {
        mSubject2Triplet.erase(Range.first);
        break;
      }

  Range = mObject2Triplet.equal_range(triplet.pObject);
  for (; Range.first != Range.second; ++Range.first)
    if (Range.first->second == triplet)
      {
        mObject2Triplet.erase(Range.first);
        break;
      }

  std::pair< Predicate2Triplet::iterator, Predicate2Triplet::iterator> RangeP = mPredicate2Triplet.equal_range(triplet.Predicate);
  for (; RangeP.first != RangeP.second; ++RangeP.first)
    if (RangeP.first->second == triplet)
      {
        mPredicate2Triplet.erase(RangeP.first);
        break;
      }

  destroyUnreferencedNode(triplet.pObject);
  return;
}

CRDFTriplet CRDFGraph::moveTriplet(CRDFNode * pNewSubject, const CRDFTriplet & triplet)
{
  CRDFTriplet Triplet = triplet;

  if (pNewSubject == NULL || !Triplet)
    return Triplet;

  // We first create the new triplet before we remove the old to avoid
  // destruction of the object/
  Triplet = pNewSubject->addEdge(triplet.Predicate, triplet.pObject);
  triplet.pSubject->removeEdge(triplet.Predicate, triplet.pObject);

  return Triplet;
}

CRDFPredicate::Path CRDFGraph::getPredicatePath(const CRDFNode * pNode)
{
  CRDFPredicate::Path Path;
  CRDFNode * pCurrent = const_cast< CRDFNode * >(pNode);
  Node2TripletConstRange Range = mObject2Triplet.equal_range(pCurrent);
  std::set< const CRDFNode * > Visited;

  while (Range.first != Range.second)
    {
      // We ignore rdf_li predicates
      if (Range.first->second.Predicate != CRDFPredicate::rdf_li)
        Path.insert(Path.begin(), Range.first->second.Predicate);

      pCurrent = Range.first->second.pSubject;

      std::pair< std::set< const CRDFNode * >::iterator, bool > Inserted =
        Visited.insert(pCurrent);
      if (!Inserted.second)
        break;

      Range = mObject2Triplet.equal_range(pCurrent);
    }

  if (pCurrent == mpAbout)
    Path.insert(Path.begin(), CRDFPredicate::about);

  return Path;
}

std::string CRDFGraph::generatedBlankNodeId() const
  {
    static std::set< unsigned C_INT32 > GeneratedIds;

    unsigned C_INT32 Id = 0;
    if (GeneratedIds.rbegin() != GeneratedIds.rend())
      Id = *GeneratedIds.rbegin();

    std::stringstream IdStream;
    IdStream << "CopasiId" << ++Id;

    while (mBlankNodeId2Node.count(IdStream.str()) != 0)
      {
        GeneratedIds.insert(Id);

        IdStream.str("");
        IdStream << "CopasiId" << ++Id;
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

const std::set< CRDFTriplet > & CRDFGraph::getTriplets() const
  {return mTriplets;}

std::set< CRDFTriplet > CRDFGraph::getTriplets(const CRDFPredicate & predicate) const
  {
    std::set< CRDFTriplet > Triplets;

    Predicate2TripletConstRange Range = mPredicate2Triplet.equal_range(predicate);
    for (; Range.first != Range.second; ++Range.first)
      if (Range.first->second.pObject->isBagNode())
        {
          std::set< CRDFTriplet > LiTriplets = getTriplets(Range.first->second.pObject, CRDFPredicate::rdf_li);
          std::set< CRDFTriplet >::const_iterator it = LiTriplets.begin();
          std::set< CRDFTriplet >::const_iterator end = LiTriplets.end();
          for (; it != end; ++it)
            Triplets.insert(CRDFTriplet(Range.first->second.pSubject, predicate, it->pObject));
        }
      else
        Triplets.insert(Range.first->second);

    return Triplets;
  }

std::set< CRDFTriplet > CRDFGraph::getTriplets(const CRDFNode * pSubject) const
  {
    std::set< CRDFTriplet > Triplets;

    Node2TripletConstRange Range = mSubject2Triplet.equal_range(const_cast< CRDFNode * >(pSubject));
    for (; Range.first != Range.second; ++Range.first)
      Triplets.insert(Range.first->second);

    return Triplets;
  }

std::set< CRDFTriplet > CRDFGraph::getTriplets(const CRDFNode * pSubject,
    const CRDFPredicate & predicate) const
  {
    std::set< CRDFTriplet > Triplets;

    Predicate2TripletConstRange Range = mPredicate2Triplet.equal_range(predicate);
    for (; Range.first != Range.second; ++Range.first)
      if (Range.first->second.pSubject == pSubject)
        Triplets.insert(Range.first->second);

    return Triplets;
  }

std::set< CRDFTriplet > CRDFGraph::getIncomingTriplets(const CRDFNode * pObject) const
  {
    std::set< CRDFTriplet > Triplets;

    Node2TripletConstRange Range = mObject2Triplet.equal_range(const_cast< CRDFNode * >(pObject));
    for (; Range.first != Range.second; ++Range.first)
      Triplets.insert(Range.first->second);

    return Triplets;
  }

std::set< const CRDFNode * > CRDFGraph::getParentSubjects(const CRDFNode * pObject) const
  {
    std::set< const CRDFNode * > Nodes;

    Node2TripletConstRange Range = mObject2Triplet.equal_range(const_cast< CRDFNode * >(pObject));
    for (; Range.first != Range.second; ++Range.first)
      Nodes.insert(Range.first->second.pSubject);

    return Nodes;
  }

void CRDFGraph::clean()
{
  while (removeEmptyNodes());
}

bool CRDFGraph::removeEmptyNodes()
{
  CRDFNode * pNode;

  std::map< std::string, CRDFNode * >::iterator it = mBlankNodeId2Node.begin();
  std::map< std::string, CRDFNode * >::iterator end = mBlankNodeId2Node.end();

  std::set< CRDFNode * > ToBeRemoved;

  for (;it != end; ++it)
    {
      pNode = it->second;
      unsigned int Edges =
        mSubject2Triplet.count(pNode);

      if (Edges == 0 ||
          (pNode->isBagNode() && Edges == 1))
        ToBeRemoved.insert(pNode);
    }

  std::set< CRDFNode * >::iterator itRemove = ToBeRemoved.begin();
  std::set< CRDFNode * >::iterator endRemove = ToBeRemoved.end();
  for (; itRemove != endRemove; ++itRemove)
    {
      std::set< CRDFTriplet > Triplets = getIncomingTriplets(*itRemove);
      std::set< CRDFTriplet >::const_iterator itTriplet = Triplets.begin();
      std::set< CRDFTriplet >::const_iterator endTriplet = Triplets.end();

      if (itTriplet == endTriplet)
        this->destroyUnreferencedNode(*itRemove);

      for (; itTriplet != endTriplet; ++itTriplet)
        itTriplet->pSubject->removeEdge(itTriplet->Predicate,
                                        itTriplet->pObject);
    }

  return ToBeRemoved.size();
}

void CRDFGraph::removeUnusedNamespaces()
{
  std::vector< bool > Used(mPrefix2Namespace.size(), false);
  std::vector< bool >::iterator itUsed;

  // We loop over all triplets
  const_iterator it = mTriplets.begin();
  const_iterator end = mTriplets.end();

  std::map< std::string, std::string >::iterator itNamespace;
  std::map< std::string, std::string >::iterator endNamespace = mPrefix2Namespace.end();
  for (;it != end; ++it)
    {
      for (itNamespace = mPrefix2Namespace.begin(), itUsed = Used.begin();
           itNamespace != endNamespace;
           ++itNamespace, ++itUsed)
        if (!*itUsed)
          {
            const std::string & Predicate = it->Predicate.getURI();
            if (Predicate.compare(0, itNamespace->second.length(), itNamespace->second) == 0)
              {
                *itUsed = true;
                break;
              }
          }
    }

  itNamespace = mPrefix2Namespace.begin();
  itUsed = Used.begin();
  std::vector< std::string > ToBeRemoved;
  for (itNamespace = mPrefix2Namespace.begin(), itUsed = Used.begin();
       itNamespace != endNamespace;
       ++itNamespace, ++itUsed)
    if (!*itUsed)
      ToBeRemoved.push_back(itNamespace->first);

  std::vector< std::string >::iterator itRemove = ToBeRemoved.begin();
  std::vector< std::string >::iterator endRemove = ToBeRemoved.end();
  for (; itRemove != endRemove; ++itRemove)
    mPrefix2Namespace.erase(*itRemove);
}

void CRDFGraph::destroyUnreferencedNode(CRDFNode * pNode)
{
  // We only can remove nodes which are no longer objects.
  if (mObject2Triplet.count(pNode) > 0)
    return;

  std::cout << "Destroying: " << pNode->getObject() << std::endl;

  // Remove all triplets where the node is subject
  std::pair< Node2Triplet::iterator, Node2Triplet::iterator> Range = mSubject2Triplet.equal_range(pNode);
  std::set< CRDFTriplet > RemoveTriplets;
  for (; Range.first != Range.second; ++Range.first)
    RemoveTriplets.insert(Range.first->second);

  std::set< CRDFTriplet >::const_iterator itTriplet = RemoveTriplets.begin();
  std::set< CRDFTriplet >::const_iterator endTriplet = RemoveTriplets.end();
  for (; itTriplet != endTriplet; ++itTriplet)
    itTriplet->pSubject->removeEdge(itTriplet->Predicate, itTriplet->pObject);

  // Remove the object from the appropriate container.
  switch (pNode->getObject().getType())
    {
    case CRDFObject::RESOURCE:
      if (pNode->getObject().isLocal())
        mLocalResource2Node.erase(pNode->getObject().getResource());
      else
        {
          // Check whether the pointer still exists mRemoteResourceNodes
          std::vector< CRDFNode * >::iterator it = mRemoteResourceNodes.begin();
          std::vector< CRDFNode * >::iterator end = mRemoteResourceNodes.end();
          for (; it != end; ++it)
            if (pNode == *it)
              {
                mRemoteResourceNodes.erase(it);
                break;
              }
        }
      break;

    case CRDFObject::BLANK_NODE:
      mBlankNodeId2Node.erase(pNode->getObject().getBlankNodeID());
      break;

    case CRDFObject::LITERAL:
      {
        // Check whther the pointer still exists in mLiteralNodes
        std::vector< CRDFNode * >::iterator it = mLiteralNodes.begin();
        std::vector< CRDFNode * >::iterator end = mLiteralNodes.end();
        for (; it != end; ++it)
          if (pNode == *it)
            {
              mLiteralNodes.erase(it);
              break;
            }
      }
      break;
    }

  // Finally delete the object
  delete pNode;
}

// The next two methods are coded here to allows for easier debugging of the calls
// to the private methods addTriplet and removeTriplet from its only friends.
bool CRDFNode::addTripletToGraph(const CRDFTriplet & triplet) const
  {
    return mGraph.addTriplet(triplet);
  }

void CRDFNode::removeTripletFromGraph(const CRDFTriplet & triplet) const
  {
    mGraph.removeTriplet(triplet);
  }
