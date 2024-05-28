// Copyright (C) 2019 - 2024 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

#include <iostream>
#include <fstream>
#include <sstream>

#include "copasi/copasi.h"

#include "copasi/model/CReaction.h"
#include "copasi/function/CFunction.h"
#include "copasi/utilities/CCopasiMessage.h"

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
  mLiteralNodes(),
  mTriplets(),
  mSubject2Triplet(),
  mObject2Triplet(),
  mPredicate2Triplet(),
  mGeneratedIds(),
  mIdMap()
{}

CRDFGraph::~CRDFGraph()
{
  // We first clear the sets and maps
  // This is necessary since they refer to the nodes which are destroyed later.
  mTriplets.clear();
  mSubject2Triplet.clear();
  mObject2Triplet.clear();
  mPredicate2Triplet.clear();

  // Note: mpAbout is not explicitly destroyed since it is contained in the map
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

bool CRDFGraph::guessGraphRoot(const std::string & about)
{
  mpAbout = NULL;
  CRDFNode * pNode;

  std::map< std::string, CRDFNode * >::iterator itMap = mLocalResource2Node.begin();
  std::map< std::string, CRDFNode * >::iterator endMap = mLocalResource2Node.end();

  for (; itMap != endMap; ++itMap)
    {
      pNode = itMap->second;

      if (pNode->isSubjectNode() &&
          pNode->getSubject().isLocal() &&
          pNode->getSubject().getType() == CRDFSubject::RESOURCE &&
          (about == " " ||
           pNode->getSubject().getResource() == about))
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

  CCopasiMessage(CCopasiMessage::ERROR, MCAnnotation + 2,
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
              {
                pSubjectNode = found->second;

                if (!pSubjectNode->isSubjectNode())
                  pSubjectNode->setSubject(subject);
              }
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
              {
                pObjectNode = found->second;

                if (!pObjectNode->isObjectNode())
                  pObjectNode->setObject(object);
              }
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

  if (predicate == CRDFPredicate::rdf_predicate &&
      pObjectNode->getObject().getType() == CRDFObject::RESOURCE &&
      CRDFPredicate::getPredicateFromURI(pObjectNode->getObject().getResource()) == CRDFPredicate::rdf_li)
    pObjectNode->getObject().setResource(CRDFPredicate::getURI(CRDFPredicate::rdf_li), false);

  return pSubjectNode->addEdge(predicate, pObjectNode);
}

bool CRDFGraph::addTriplet(const CRDFTriplet & triplet)
{
  if (!triplet)
    return false;

  std::pair< std::set< CRDFTriplet >::iterator, bool> Insert = mTriplets.insert(triplet);

  if (Insert.second)
    {
      mSubject2Triplet.insert(std::pair< CRDFNode * const, CRDFTriplet >(triplet.pSubject, triplet));
      mObject2Triplet.insert(std::pair< CRDFNode * const, CRDFTriplet >(triplet.pObject, triplet));
      mPredicate2Triplet.insert(std::pair< const CRDFPredicate, CRDFTriplet >(triplet.Predicate, triplet));

      // DebugFile << "Inserted: " << triplet;
    }

  return true;
}

bool CRDFGraph::removeTriplet(CRDFNode * pSubject,
                              const CRDFPredicate & predicate,
                              CRDFNode * pObject)
{return pSubject->removeEdge(predicate, pObject);}

bool
CRDFGraph::removeTriplet(const CRDFTriplet & triplet)
{
  if (!triplet)
    return false;

  // DebugFile << "Removed: " << triplet;
  bool deletedSomething = false;
  // Remove the triplet
  deletedSomething |= mTriplets.erase(triplet) > 0;

  // Remove its references
  // Subject2Triplets
  std::pair< Node2Triplet::iterator, Node2Triplet::iterator> Range = mSubject2Triplet.equal_range(triplet.pSubject);

  for (; Range.first != Range.second; ++Range.first)
    if (Range.first->second == triplet)
      {
        deletedSomething = true;
        mSubject2Triplet.erase(Range.first);

        // We must stop or make sure that the iterator Range is still valid. Since
        // triplets are unique (we have at most one reference) we can stop.
        break;
      }

  Range = mObject2Triplet.equal_range(triplet.pObject);

  for (; Range.first != Range.second; ++Range.first)
    if (Range.first->second == triplet)
      {
        deletedSomething = true;
        mObject2Triplet.erase(Range.first);

        // We must stop or make sure that the iterator Range is still valid. Since
        // triplets are unique (we have at most one reference) we can stop.
        break;
      }

  std::pair< Predicate2Triplet::iterator, Predicate2Triplet::iterator> RangeP = mPredicate2Triplet.equal_range(triplet.Predicate);

  for (; RangeP.first != RangeP.second; ++RangeP.first)
    if (RangeP.first->second == triplet)
      {
        deletedSomething = true;
        mPredicate2Triplet.erase(RangeP.first);

        // We must stop or make sure that the iterator RangeP is still valid. Since
        // triplets are unique (we have at most one reference) we can stop.
        break;
      }

  deletedSomething |= destroyUnreferencedNode(triplet.pObject);
  return deletedSomething;
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
  Node2TripletRange Range = mObject2Triplet.equal_range(pCurrent);
  std::set< const CRDFNode * > Visited;

  while ((Range.first != Range.second) &&
         pCurrent != mpAbout)
    {
      // We ignore rdf_li predicates
      if (Range.first->second.Predicate != CRDFPredicate::rdf_li)
        Path.insert(Path.begin(), Range.first->second.Predicate.getType());

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

std::string CRDFGraph::generatedNodeId(const std::string & existingId)
{
  // If we have an existing Id we check whether we have already mapped it.
  if (existingId != "")
    {
      std::map< std::string, std::string >::const_iterator found = mIdMap.find(existingId);

      if (found != mIdMap.end())
        return found->second;
    }

  unsigned int Id = 0;

  if (mGeneratedIds.rbegin() != mGeneratedIds.rend())
    Id = *mGeneratedIds.rbegin();

  std::stringstream IdStream;
  IdStream << "CopasiId" << ++Id;

  while (mBlankNodeId2Node.count(IdStream.str()) != 0)
    {
      mGeneratedIds.insert(Id);

      IdStream.str("");
      IdStream << "CopasiId" << ++Id;
    }

  mGeneratedIds.insert(Id);

  // Remember the mapping for an existing Id
  if (existingId != "")
    mIdMap[existingId] = IdStream.str();

  return IdStream.str();
}

CRDFNode * CRDFGraph::createAboutNode(const std::string & key)
{
  std::string About = "#" + key;

  if (!guessGraphRoot(About))
    {
      CRDFSubject subject;
      mpAbout = new CRDFNode(*this);

      subject.setType(CRDFSubject::RESOURCE);
      subject.setResource(About, true);
      mpAbout->setSubject(subject);
      mLocalResource2Node[About] = mpAbout;
    }

  return mpAbout;
}

bool CRDFGraph::empty() const
{
  return mTriplets.size() == 0;
}

const std::set< CRDFTriplet > & CRDFGraph::getTriplets() const
{return mTriplets;}

std::set< CRDFTriplet > CRDFGraph::getTriplets(const CRDFPredicate & predicate,
    const bool & expandBag) const
{
  std::set< CRDFTriplet > Triplets;

  Predicate2TripletConstRange Range = mPredicate2Triplet.equal_range(predicate);

  for (; Range.first != Range.second; ++Range.first)
    if (expandBag &&
        Range.first->second.pObject->isBagNode())
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
  while (removeEmptyNodes()) {};
}

bool CRDFGraph::removeEmptyNodes()
{
  CRDFNode * pNode;

  std::map< std::string, CRDFNode * >::iterator it = mBlankNodeId2Node.begin();
  std::map< std::string, CRDFNode * >::iterator end = mBlankNodeId2Node.end();

  std::set< CRDFNode * > ToBeRemoved;

  for (; it != end; ++it)
    {
      pNode = it->second;
      size_t Edges =
        mSubject2Triplet.count(pNode);

      if (Edges == 0 ||
          (pNode->isBagNode() && Edges == 1))
        ToBeRemoved.insert(pNode);
    }

  std::set< CRDFNode * >::iterator itRemove = ToBeRemoved.begin();
  std::set< CRDFNode * >::iterator endRemove = ToBeRemoved.end();

  bool deletedSomething = false;

  for (; itRemove != endRemove; ++itRemove)
    {
      std::set< CRDFTriplet > Triplets = getIncomingTriplets(*itRemove);
      std::set< CRDFTriplet >::const_iterator itTriplet = Triplets.begin();
      std::set< CRDFTriplet >::const_iterator endTriplet = Triplets.end();

      if (itTriplet == endTriplet)
        deletedSomething |= destroyUnreferencedNode(*itRemove);

      for (; itTriplet != endTriplet; ++itTriplet)
        {
          deletedSomething |= itTriplet->pSubject->removeEdge(itTriplet->Predicate,
                              itTriplet->pObject);
        }
    }

  if (ToBeRemoved.size() > 0 && !deletedSomething)
    {
      CCopasiMessage(CCopasiMessage::WARNING_FILTERED, "Failure in removing empty elements from converting RDF node.");
    }

  return ToBeRemoved.size() > 0 && deletedSomething;
}

void CRDFGraph::updateNamespaces()
{
  // We make sure that all namespaces COPASI uses are known.
  addNameSpace("CopasiMT", "http://www.copasi.org/RDF/MiriamTerms#");
  addNameSpace("dcterms", "http://purl.org/dc/terms/");
  addNameSpace("rdf", "http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  addNameSpace("vCard", "http://www.w3.org/2001/vcard-rdf/3.0#");
  addNameSpace("bqbiol", "http://biomodels.net/biology-qualifiers/");
  addNameSpace("bqmodel", "http://biomodels.net/model-qualifiers/");

  std::vector< bool > Used(mPrefix2Namespace.size(), false);
  std::vector< bool >::iterator itUsed;

  // We loop over all triplets
  const_iterator it = mTriplets.begin();
  const_iterator end = mTriplets.end();

  std::map< std::string, std::string >::iterator itNamespace;
  std::map< std::string, std::string >::iterator endNamespace = mPrefix2Namespace.end();

  for (; it != end; ++it)
    {
      for (itNamespace = mPrefix2Namespace.begin(), itUsed = Used.begin();
           itNamespace != endNamespace;
           ++itNamespace, ++itUsed)
        if (!*itUsed)
          {
          if (itNamespace->first == "rdf") // never remove RDF namespace
            {
              *itUsed = true;
              break;
            }
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

bool CRDFGraph::destroyUnreferencedNode(CRDFNode * pNode)
{
  // We only can remove nodes which are no longer objects.
  if (mObject2Triplet.count(pNode) > 0)
    return false;

  // Remove all triplets where the node is subject
  std::pair< Node2Triplet::iterator, Node2Triplet::iterator> Range = mSubject2Triplet.equal_range(pNode);
  std::set< CRDFTriplet > RemoveTriplets;

  for (; Range.first != Range.second; ++Range.first)
    RemoveTriplets.insert(Range.first->second);

  std::set< CRDFTriplet >::const_iterator itTriplet = RemoveTriplets.begin();
  std::set< CRDFTriplet >::const_iterator endTriplet = RemoveTriplets.end();

  bool deletedSomething = false;

  for (; itTriplet != endTriplet; ++itTriplet)
    deletedSomething |= itTriplet->pSubject->removeEdge(itTriplet->Predicate, itTriplet->pObject);

  // Remove the object from the appropriate container.
  switch (pNode->getObject().getType())
    {
      case CRDFObject::RESOURCE:

        if (pNode->getObject().isLocal())
          deletedSomething |= mLocalResource2Node.erase(pNode->getObject().getResource()) > 0;
        else
          {
            // Check whether the pointer still exists mRemoteResourceNodes
            std::vector< CRDFNode * >::iterator it = mRemoteResourceNodes.begin();
            std::vector< CRDFNode * >::iterator end = mRemoteResourceNodes.end();

            for (; it != end; ++it)
              if (pNode == *it)
                {
                  deletedSomething = true;
                  mRemoteResourceNodes.erase(it);
                  break;
                }
          }

        break;

      case CRDFObject::BLANK_NODE:
        deletedSomething |= mBlankNodeId2Node.erase(pNode->getObject().getBlankNodeID()) > 0;
        break;

      case CRDFObject::LITERAL:
      {
        // Check whether the pointer still exists in mLiteralNodes
        std::vector< CRDFNode * >::iterator it = mLiteralNodes.begin();
        std::vector< CRDFNode * >::iterator end = mLiteralNodes.end();

        for (; it != end; ++it)
          if (pNode == *it)
            {
              deletedSomething = true;
              mLiteralNodes.erase(it);
              break;
            }
      }
      break;
    }

  // Finally delete the object
  delete pNode;
  return deletedSomething;
}

// The next two methods are coded here to allows for easier debugging of the calls
// to the private methods addTriplet and removeTriplet from its only friends.
bool CRDFNode::addTripletToGraph(const CRDFTriplet & triplet) const
{
  return mGraph.addTriplet(triplet);
}

bool CRDFNode::removeTripletFromGraph(const CRDFTriplet & triplet) const
{
  return mGraph.removeTriplet(triplet);
}


#include <sbml/xml/XMLNode.h>
#include <sbml/xml/XMLToken.h>

void addXmlNodeToGraph(CRDFGraph & graph, XMLNode & current, CRDFSubject & subject, const std::string & rdfUri, const std::string & unusedPredicate = "")
{
  CRDFObject object;
  CRDFLiteral literal;

  std::string elementName = current.getName();
  std::string predicate = current.getURI() + elementName;
  bool isDescription = elementName == "Description";
  bool isBag = elementName == "Bag";
  if (isDescription && !unusedPredicate.empty())
    predicate = unusedPredicate;
  bool haveResource = current.hasAttr("resource", rdfUri);
  bool haveText = current.getNumChildren() == 1 && current.getChild(0).isText();
  bool isBlank = !current.hasAttr("about", rdfUri) && !haveResource && !haveText;

  if (haveResource)
    {
      object.setType(CRDFObject::RESOURCE);
      object.setResource(current.getAttrValue("resource", rdfUri), false);
      graph.addTriplet(subject, predicate, object);
    }
  else if (haveText)
    {
      std::string dataType = current.getAttrValue("datatype", rdfUri);
      std::string language = current.getAttrValue("lang", rdfUri);

      object.setType(CRDFObject::LITERAL);
      if (!dataType.empty())
        {
          literal.setType(CRDFLiteral::TYPED);
          literal.setDataType(dataType);
        }
      else
        {
          literal.setType(CRDFLiteral::PLAIN);
          literal.setLanguage(language);
        }
      literal.setLexicalData(current.getChild(0).getCharacters());
      object.setLiteral(literal);
      graph.addTriplet(subject, predicate, object);
    }
  else
    {

      if (isBag)
        {
          object.setType(CRDFObject::RESOURCE);
          object.setResource(predicate, false);
          predicate = current.getURI() + "type";

          graph.addTriplet(subject, predicate, object);
        }

      if (isBlank && !isDescription && !isBag)
        {
          object.setType(CRDFObject::BLANK_NODE);
          object.setBlankNodeId(graph.generatedNodeId());
          graph.addTriplet(subject, predicate, object);

          CRDFSubject newSubject;
          newSubject.setType(CRDFSubject::BLANK_NODE);
          newSubject.setBlankNodeId(object.getBlankNodeID());

          for (int i = 0; i < current.getNumChildren(); ++i)
            {
              addXmlNodeToGraph(graph, current.getChild(i), newSubject, rdfUri, predicate);
            }
        }
      else
        {
          for (int i = 0; i < current.getNumChildren(); ++i)
            {
              addXmlNodeToGraph(graph, current.getChild(i), subject, rdfUri, predicate);
            }
        }
    }
}

CRDFGraph * CRDFGraph::fromString(const std::string & miriam)
{
  CRDFGraph * graph = new CRDFGraph();

  XMLNamespaces ns; 
  ns.add("http://www.copasi.org/RDF/MiriamTerms#", "CopasiMT");
  ns.add("http://purl.org/dc/terms/", "dcterms");
  ns.add("http://www.w3.org/1999/02/22-rdf-syntax-ns#", "rdf");
  ns.add("http://www.w3.org/2001/vcard-rdf/3.0#", "vCard");
  ns.add("http://biomodels.net/biology-qualifiers/", "bqbiol");
  ns.add("http://biomodels.net/model-qualifiers/", "bqmodel");

  XMLNode * content = XMLNode::convertStringToXMLNode(miriam, &ns);

  if (content == NULL)
  {
    // content is invalid or empty, return graph as is
    return graph;
  }

  std::string rdfUri;

  for (int i = 0; i < content->getNamespaces().getLength(); ++i)
    {
      std::string prefix = content->getNamespaces().getPrefix(i);
      std::string uri = content->getNamespaces().getURI(i);
      graph->addNameSpace(prefix, uri);

      if (prefix == "rdf")
        rdfUri = uri;
    }

  if (content->getNumChildren() > 0)
    {
      XMLNode & desc = content->getChild("Description");
      std::string about = desc.getAttrValue("about", rdfUri);

      for (int i = 0; i < desc.getNumChildren(); ++i)
        {

          CRDFSubject subject;
          subject.setType(CRDFSubject::RESOURCE);
          subject.setResource(about, true);

          addXmlNodeToGraph(*graph, desc.getChild(i), subject, rdfUri);
        }
    }

  pdelete(content);

  graph->guessGraphRoot();
  return graph;
}

std::string CRDFGraph::toXmlString()
{
  updateNamespaces();
  auto xml = toXmlNode();
  return xml.convertXMLNodeToString(&xml);
}

struct TreeNode
{
  std::string elementName;
  std::string resource;
  std::string literal;
  std::string dataType;
  std::string language;
  bool isBlank;
  std::vector< TreeNode * > children;

  bool needBag()
  {
    if (children.size() == 1 && children[0]->isBlank)
      for (TreeNode * child : children[0]->children)
        {
          if (child->elementName == "rdf:type")
            return true;
          if (child->elementName == "rdf:li")
            return true;
        }
    return false;
  }

  bool needDescription()
  {
    for (TreeNode * child : children)
      {
        if (child->isBlank)
          return true;
      }
    return false;
  }

  bool isResourceOnly()
  {
    return literal.empty() && !resource.empty() && children.empty();
  }

  XMLNode * createNode()
  {
    int pos = elementName.find(':');
    if (pos == std::string::npos)
      return NULL;

    XMLNode * node = new XMLNode(XMLTriple(elementName.substr(pos + 1), "", elementName.substr(0, pos)), XMLAttributes());
    return node;
  }

  void addLiteralToNode(XMLNode * node)
  {
    if (!dataType.empty())
      {
        node->addAttr("rdf:datatype", dataType);
      }
    if (!language.empty())
      {
        node->addAttr("rdf:lang", language);
      }

    if (!literal.empty())
      {
        node->addChild(XMLNode(literal.c_str()));
      }
  }

  void addResourceToNode(XMLNode * node)
  {
    node->addAttr("rdf:resource", resource);
  }
};

TreeNode * searchTreeByElementName(TreeNode * node, const std::string & elementName)
{
  if (node->elementName == elementName)
    {
      return node;
    }
  for (TreeNode * child : node->children)
    {
      TreeNode * result = searchTreeByElementName(child, elementName);
      if (result != nullptr)
        {
          return result;
        }
    }
  return nullptr;
}

TreeNode * searchTreeByResource(TreeNode * node, const std::string & resource)
{
  if (node->resource == resource)
    {
      return node;
    }
  for (TreeNode * child : node->children)
    {
      TreeNode * result = searchTreeByResource(child, resource);
      if (result != nullptr)
        {
          return result;
        }
    }
  return nullptr;
}

void treeNodeToXMLNode(TreeNode * rootNode, XMLNode & parent, const std::string & rdfUri)
{
  if (rootNode->isResourceOnly())
    {
      rootNode->addResourceToNode(&parent);
    }
  else if (!rootNode->literal.empty())
    {
      rootNode->addLiteralToNode(&parent);
    }

  for (auto * node : rootNode->children)
    {
      if (node->elementName == "rdf:type")
        continue;

      XMLNode * xmlNode = node->createNode();
      if (xmlNode == NULL)
        continue;

      if (node->isResourceOnly())
        {
          node->addResourceToNode(xmlNode);
        }
      else if (!node->literal.empty())
        {
          node->addLiteralToNode(xmlNode);
        }
      else
        {
          if (node->needBag())
            {
              XMLNode * bagNode = new XMLNode(XMLTriple("Bag", rdfUri, "rdf"), XMLAttributes());
              for (auto * child : node->children)
                {
                  if (child->elementName == "rdf:type")
                    continue;
                  treeNodeToXMLNode(child, *bagNode, rdfUri);
                }
              xmlNode->addChild(*bagNode);
            }
          else if (node->needDescription())
            {
              XMLNode * descriptionNode = new XMLNode(XMLTriple("Description", rdfUri, "rdf"), XMLAttributes());
              for (auto * child : node->children)
                {
                  if (child->elementName == "rdf:type")
                    continue;
                  treeNodeToXMLNode(child, *descriptionNode, rdfUri);
                }
              xmlNode->addChild(*descriptionNode);
            }
          else
            {
              for (auto * child : node->children)
                {
                  if (child->elementName == "rdf:type")
                    continue;
                  treeNodeToXMLNode(child, *xmlNode, rdfUri);
                }
            }
        }

      // add at end, since libSBML copies the node
      parent.addChild(*xmlNode);
      // which means we have to delete this one
      delete xmlNode;
    }
}

XMLNode CRDFGraph::toXmlNode()
{
  auto & rdfUri = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";
  XMLNode rdfNode(XMLTriple("RDF", rdfUri, "rdf"), XMLAttributes());
  for (auto & ns : mPrefix2Namespace)
    rdfNode.addNamespace(ns.second, ns.first);

  XMLAttributes desc_att = XMLAttributes();
  desc_att.add("rdf:about", getAboutNode()->getSubject().getResource());

  std::map< const CRDFNode *, XMLNode * > mNodeMap;

  XMLNode description(XMLTriple("Description", rdfUri, "rdf"), desc_att);

  mNodeMap[getAboutNode()] = &description;

  std::map< std::string, TreeNode * > nodeMap;
  std::vector< TreeNode * > toBeDeleted;

  TreeNode * rootNode = new TreeNode();
  toBeDeleted.push_back(rootNode);
  rootNode->resource = getAboutNode()->getSubject().getResource();
  rootNode->isBlank = false;
  nodeMap[rootNode->resource] = rootNode;

  // Create tree nodes for each RDF node
  for (const auto & triplet : mTriplets)
    {
      if (!triplet.pSubject)
        continue;

      TreeNode * node = searchTreeByResource(rootNode,
                                             triplet.pSubject->getSubject().getType() == CRDFSubject::RESOURCE
                                               ? triplet.pSubject->getSubject().getResource()
                                               : triplet.pSubject->getSubject().getBlankNodeID());
      if (!node && triplet.pSubject->getSubject().getType() == CRDFSubject::BLANK_NODE)
        node = nodeMap[triplet.pSubject->getSubject().getBlankNodeID()];

      if (node == nullptr)
        {
          node = new TreeNode();
          toBeDeleted.push_back(node);
          if (triplet.pSubject->getSubject().getType() == CRDFSubject::RESOURCE)
            {
              node->resource = triplet.pSubject->getSubject().getResource();
              node->isBlank = false;
            }
          else
            {
              node->resource = triplet.pSubject->getSubject().getBlankNodeID();
              node->isBlank = true;
            }

          nodeMap[node->resource] = node;
        }

      // add predicate
      std::string name = CRDFPredicate::getElementNameForType(triplet.Predicate.getType());
      if (name.empty())
        continue;

      TreeNode * predicateNode = new TreeNode();
      toBeDeleted.push_back(predicateNode);
      predicateNode->elementName = name;
      node->children.push_back(predicateNode);

      // and object
      if (!triplet.pObject)
        continue;
      const CRDFObject & Object = triplet.pObject->getObject();
      switch (Object.getType())
        {
        case CRDFObject::RESOURCE:
          {
            TreeNode * objectNode = new TreeNode();
            toBeDeleted.push_back(objectNode);
            objectNode->resource = Object.getResource();
            objectNode->isBlank = false;
            predicateNode->children.push_back(objectNode);
          }
          break;

        case CRDFObject::BLANK_NODE:
          {
            TreeNode * objectNode = nodeMap[Object.getBlankNodeID()];
            if (objectNode == nullptr)
              objectNode = searchTreeByResource(rootNode, Object.getBlankNodeID());
            if (objectNode == nullptr)
              {
                objectNode = new TreeNode();
                toBeDeleted.push_back(objectNode);
                objectNode->resource = Object.getBlankNodeID();
                objectNode->isBlank = true;
                if (!objectNode->resource.empty())
                  nodeMap[objectNode->resource] = objectNode;
              }
            predicateNode->children.push_back(objectNode);
          }
          break;

        case CRDFObject::LITERAL:
          {
            TreeNode * objectNode = new TreeNode();
            triplet.pSubject->getSubject().getBlankNodeID();
            objectNode->literal = Object.getLiteral().getLexicalData();
            objectNode->dataType = Object.getLiteral().getDataType();
            objectNode->language = Object.getLiteral().getLanguage();
            predicateNode->children.push_back(objectNode);
          }
          break;
        }
    }

  // now write tree as XMLNode adding to description
  treeNodeToXMLNode(rootNode, description, rdfUri);

  // add description at end (since it'll be cloned)
  rdfNode.addChild(description);

  // cleanup
  rootNode = nullptr;
  nodeMap.clear();
  for (TreeNode * node : toBeDeleted)
    delete node;
  toBeDeleted.clear();

  return rdfNode;
}
