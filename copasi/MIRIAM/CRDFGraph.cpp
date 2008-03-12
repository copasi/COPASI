// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFGraph.cpp,v $
//   $Revision: 1.25 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/12 13:28:06 $
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

#include "CRDFGraph.h"
#include "CRDFNode.h"
#include "CRDFSubject.h"
#include "CRDFObject.h"
#include "CRDFLiteral.h"
#include "CRDFParser.h"
#include "CRDFWriter.h"
#include "CConstants.h"

#include "utilities/CCopasiMessage.h"

unsigned int CRDFGraph::nodeIDCounter = 0;

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
    delete itMap->second;

  for (itMap = mLocalResource2Node.begin(), endMap = mLocalResource2Node.end();
       itMap != endMap; ++itMap)
    delete itMap->second;

  std::vector< CRDFNode *>::iterator itVector;
  std::vector< CRDFNode *>::iterator endVector;

  for (itVector = mRemoteResourceNodes.begin(), endVector = mRemoteResourceNodes.end();
       itVector != endVector; ++itVector)
    delete *itVector;

  for (itVector = mLiteralNodes.begin(), endVector = mLiteralNodes.end();
       itVector != endVector; ++itVector)
    delete *itVector;
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

bool CRDFGraph::addTriplet(const CRDFSubject & subject,
                           const std::string & predicate,
                           const CRDFObject & object)
{
  bool success = true;

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
              pSubjectNode = new CRDFNode;
              pSubjectNode->setSubject(subject);
              mLocalResource2Node[subject.getResource()] = pSubjectNode;
            }
        }
      else
        {
          pSubjectNode = new CRDFNode;
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
          pSubjectNode = new CRDFNode;
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
              pObjectNode = new CRDFNode;
              pObjectNode->setObject(object);
              mLocalResource2Node[object.getResource()] = pObjectNode;
            }
        }
      else
        {
          pObjectNode = new CRDFNode;
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
          pObjectNode = new CRDFNode;
          pObjectNode->setObject(object);
          mBlankNodeId2Node[object.getBlankNodeID()] = pObjectNode;
        }
      break;

    case CRDFObject::LITERAL:
      pObjectNode = new CRDFNode;
      pObjectNode->setObject(object);
      mLiteralNodes.push_back(pObjectNode);
      break;
    }

  pSubjectNode->addEdge(predicate, pObjectNode);

  return success;
}

void CRDFGraph::addRecordToTable(const std::string& tableName, const CRDFObject& childObj)
{
  std::string predicate = "";

  //create the about node if it does not exist.
  if (!mpAbout)
  {createAboutNode();}

  CRDFNode* pTableNode = NULL;
  if (mpAbout->edgeExists(tagName2Predicate(tableName)))
  {pTableNode = getNodeForPredicate(tagName2Predicate(tableName), mpAbout);}

  //create the table node as a blank node if it does not exist.
  if (!pTableNode)
    {
      std::string predicate = tagName2Predicate(tableName);
      addTriplet(mpAbout->getSubject(), predicate, childObj);
      pTableNode = findNodeFromObject(childObj);
      if (childObj.getType() == CRDFObject::RESOURCE)
        {
          addBagNodeToTable(tableName);
          return;
        }
    }

  if (isBagNode(pTableNode))
  {addObjectToBagNode(tableName, pTableNode, childObj);}
  else
    {
      if (pTableNode->getEdges().size() > 0
          || pTableNode->getObject().getType() == CRDFObject::RESOURCE
          || pTableNode->getObject().getType() == CRDFObject::LITERAL)
        {
          addBagNodeToTable(tableName);
          //since addBagNodeToTable() would have changed the tableNode. Find it again.
          pTableNode = getNodeForPredicate(tagName2Predicate(tableName), mpAbout);
          addObjectToBagNode(tableName, pTableNode, childObj);
        }
      else if (pTableNode->getObject().getType() == CRDFObject::BLANK_NODE)
        {
          if (tableName == "dc:creator")
          {buildCreatorRecord(pTableNode);}
          else if (tableName == "dcterms:references")
          {buildReferenceRecord(pTableNode);}
          else if (tableName == "dcterms:created")
          {buildCreatedRecord(pTableNode);}
          else if (tableName == "dcterms:modified")
          {buildModifiedRecord(pTableNode);}
        }
    }
  mChanged = true;
}

bool CRDFGraph::getNodeIDsForTable(const std::string& tableName, std::vector<CRDFObject>& objects)
{
  std::string predicate = tagName2Predicate(tableName);
  CRDFNode* pTableNode = getNodeForPredicate(predicate, mpAbout);
  if (!pTableNode)
  {return false;}

  if (isBagNode(pTableNode))
    {
      std::string bagPredicate = getNameSpaceURI("rdf") + "type";
      CRDFNode::const_iterator it = pTableNode->getEdges().begin();
      CRDFNode::const_iterator end = pTableNode->getEdges().end();
      for (; it != end; it++)
        {
          if (it->first != bagPredicate)
          {objects.push_back(it->second->getObject());}
        }
    }
  else
  {objects.push_back(pTableNode->getObject());}
  return true;
}

void CRDFGraph::addObjectToBagNode(const std::string& tableName, CRDFNode* pTableNode, const CRDFObject& object)
{
  if (!isBagNode(pTableNode))
  {return;}
  std::string predicate;
  CRDFNode * pObjNode = NULL;
  unsigned int noOfObjects = getNoOfObjectsInTable(pTableNode);
  do
    {
      std::stringstream sstr;
      noOfObjects++;
      sstr << getNameSpaceURI("rdf") << "_" << noOfObjects;
      predicate = sstr.str();
    }
  while (pTableNode->edgeExists(predicate));

  addTriplet(pTableNode->getSubject(), predicate, object);

  if (object.getType() == CRDFObject::BLANK_NODE)
    {
      pObjNode = findNodeFromObject(object);
      if (tableName == "dc:creator")
      {buildCreatorRecord(pObjNode);}
      else if (tableName == "dcterms:references")
      {buildReferenceRecord(pObjNode);}
      else if (tableName == "dcterms:modified")
      {buildModifiedRecord(pObjNode);}
    }
}

void CRDFGraph::buildCreatorRecord(const CRDFNode * pObjNode)
{
  CRDFSubject subject;
  CRDFObject object;
  CRDFLiteral lit;
  std::string predicate, blankNodeId;
  std::pair< CRDFNode::const_iterator, CRDFNode::const_iterator > pr;

  predicate = getNameSpaceURI("vCard") + "N";

  if (!pObjNode->edgeExists(predicate))
    {
      blankNodeId = getGeneratedId();
      object.setType(CRDFObject::BLANK_NODE);
      object.setBlankNodeId(blankNodeId);
      addTriplet(pObjNode->getSubject(), predicate, object);
      subject.clearData(); object.clearData();
      pr = pObjNode->getObjectNodes(predicate);
    }
  else
    {
      pr = pObjNode->getObjectNodes(predicate);
      blankNodeId = pr.first->second->getId();
    }

  predicate = getNameSpaceURI("vCard") + "Family";
  if (!pr.first->second->edgeExists(predicate))
    {
      subject.setType(CRDFSubject::BLANK_NODE);
      subject.setBlankNodeId(blankNodeId);
      object.setType(CRDFObject::LITERAL);
      lit.setType(CRDFLiteral::PLAIN);
      object.setLiteral(lit);
      addTriplet(subject, predicate, object);
      subject.clearData(); object.clearData();
    }

  predicate = getNameSpaceURI("vCard") + "Given";
  if (!pr.first->second->edgeExists(predicate))
    {
      subject.setType(CRDFSubject::BLANK_NODE);
      subject.setBlankNodeId(blankNodeId);
      object.setType(CRDFObject::LITERAL);
      lit.setType(CRDFLiteral::PLAIN);
      object.setLiteral(lit);
      addTriplet(subject, predicate, object);
      subject.clearData(); object.clearData();
    }

  predicate = getNameSpaceURI("vCard") + "EMAIL";
  if (!pObjNode->edgeExists(predicate))
    {
      object.setType(CRDFObject::LITERAL);
      lit.setType(CRDFLiteral::PLAIN);
      object.setLiteral(lit);
      addTriplet(pObjNode->getSubject(), predicate, object);
      object.clearData();
    }

  predicate = getNameSpaceURI("vCard") + "ORG";
  if (!pObjNode->edgeExists(predicate))
    {
      blankNodeId = getGeneratedId();
      object.setType(CRDFObject::BLANK_NODE);
      object.setBlankNodeId(blankNodeId);
      addTriplet(pObjNode->getSubject(), predicate, object);
      object.clearData();
      pr = pObjNode->getObjectNodes(predicate);
    }
  else
    {
      pr = pObjNode->getObjectNodes(predicate);
      blankNodeId = pr.first->second->getId();
    }

  predicate = getNameSpaceURI("vCard") + "Orgname";
  if (!pr.first->second->edgeExists(predicate))
    {
      subject.setType(CRDFSubject::BLANK_NODE);
      subject.setBlankNodeId(blankNodeId);
      object.setType(CRDFObject::LITERAL);
      lit.setType(CRDFLiteral::PLAIN);
      object.setLiteral(lit);
      addTriplet(subject, predicate, object);
      subject.clearData(); object.clearData();
    }
}

void CRDFGraph::buildReferenceRecord(const CRDFNode * pObjNode)
{
  CRDFSubject subject;
  CRDFObject object;
  CRDFLiteral lit;
  std::string predicate, blankNodeId;
  std::pair< CRDFNode::const_iterator, CRDFNode::const_iterator > pr;

  predicate = getNameSpaceURI("rdf") + "type";
  std::string bibURI = getNameSpaceURI("dcterms") + "bibliographicCitation";
  if (!isTypeNode(pObjNode, bibURI))
    {
      object.setType(CRDFObject::RESOURCE);
      object.setResource(bibURI, false);
      addTriplet(pObjNode->getSubject(), predicate, object);
      object.clearData();
    }

  predicate = getNameSpaceURI("dcterms") + "identifier";

  if (!pObjNode->edgeExists(predicate))
    {
      blankNodeId = getGeneratedId();
      object.setType(CRDFObject::BLANK_NODE);
      object.setBlankNodeId(blankNodeId);
      addTriplet(pObjNode->getSubject(), predicate, object);
      object.clearData();
      pr = pObjNode->getObjectNodes(predicate);
    }
  else
    {
      pr = pObjNode->getObjectNodes(predicate);
      blankNodeId = pr.first->second->getId();
    }

  predicate = getNameSpaceURI("rdf") + "type";
  if (!isBagNode(pr.first->second))
    {
      object.setType(CRDFObject::RESOURCE);
      object.setResource(getNameSpaceURI("rdf") + "Bag", false);
      addTriplet(pr.first->second->getSubject(), predicate, object);
      object.clearData();
    }

  predicate = getNameSpaceURI("rdf") + "_1";
  if (!pr.first->second->edgeExists(predicate))
    {
      subject.setType(CRDFSubject::BLANK_NODE);
      subject.setBlankNodeId(blankNodeId);
      object.setType(CRDFObject::RESOURCE);
      object.setResource("", false);
      addTriplet(subject, predicate, object);
      subject.clearData(); object.clearData();
    }

  predicate = getNameSpaceURI("rdf") + "_2";
  if (!pr.first->second->edgeExists(predicate))
    {
      subject.setType(CRDFSubject::BLANK_NODE);
      subject.setBlankNodeId(blankNodeId);
      object.setType(CRDFObject::RESOURCE);
      object.setResource("", false);
      addTriplet(subject, predicate, object);
      subject.clearData(); object.clearData();
    }

  predicate = getNameSpaceURI("dcterms") + "description";
  if (!pObjNode->edgeExists(predicate))
    {
      object.setType(CRDFObject::LITERAL);
      lit.setType(CRDFLiteral::PLAIN);
      object.setLiteral(lit);
      addTriplet(pObjNode->getSubject(), predicate, object);
      object.clearData();
    }
}

void CRDFGraph::buildCreatedRecord(const CRDFNode * pObjNode)
{
  CRDFObject object; CRDFLiteral lit;
  std::string predicate;
  std::pair< CRDFNode::const_iterator, CRDFNode::const_iterator > pr;

  predicate = getNameSpaceURI("dcterms") + "W3CDTF";
  if (!pObjNode->edgeExists(predicate))
    {
      object.setType(CRDFObject::LITERAL);
      lit.setType(CRDFLiteral::PLAIN);
      object.setLiteral(lit);
      addTriplet(pObjNode->getSubject(), predicate, object);
      object.clearData();
    }
}

void CRDFGraph::buildModifiedRecord(const CRDFNode * pObjNode)
{
  CRDFObject object; CRDFLiteral lit;
  std::string predicate;
  std::pair< CRDFNode::const_iterator, CRDFNode::const_iterator > pr;

  predicate = getNameSpaceURI("dcterms") + "W3CDTF";
  if (!pObjNode->edgeExists(predicate))
    {
      object.setType(CRDFObject::LITERAL);
      lit.setType(CRDFLiteral::PLAIN);
      object.setLiteral(lit);
      addTriplet(pObjNode->getSubject(), predicate, object);
      object.clearData();
    }
}

void CRDFGraph::createAboutNode()
{
  CRDFSubject subject;
  mpAbout = new CRDFNode();
  std::string aboutResource = getGeneratedId();
  subject.setType(CRDFSubject::RESOURCE);
  subject.setResource(aboutResource, true);
  mpAbout->setSubject(subject);
  mLocalResource2Node[aboutResource] = mpAbout;
}

bool CRDFGraph::removeRecordFromTable(const std::string& tableName, const CRDFObject& childObj)
{
  CRDFNode::multimap::const_iterator it;
  CRDFNode* tableNode = getNodeForPredicate(tagName2Predicate(tableName), mpAbout);
  if (!tableNode)
  {return false;}

  bool IsBagNode = isBagNode(tableNode);

  const CRDFNode::multimap& tableEdges = tableNode->getEdges();
  if (IsBagNode)
    {
      for (it = tableEdges.begin(); it != tableEdges.end(); it++)
        {
          if (it->second->getObject() == childObj)
          {break;}
        }

      if (it == tableEdges.end())
      {return false;}

      if (removeNode(it->second))
        {
          tableNode->removeEdge(it->first);
          if (tableNode->getObject().getType() != CRDFObject::RESOURCE
              && tableNode->getEdges().size() == 2)
          {removeBagNodeFromTable(tableName);}
        }
    }
  else
    {
      if (removeNode(tableNode))
      {mpAbout->removeEdge(tagName2Predicate(tableName));}
      else
      {return false;}
    }
  mChanged = true;
  return true;
}

bool CRDFGraph::isBagNode(const CRDFNode * pNode)
{return isTypeNode(pNode, getNameSpaceURI("rdf") + "Bag");}

bool CRDFGraph::isTypeNode(const CRDFNode * pNode, std::string typeResource)
{
  std::string typePredicate = getNameSpaceURI("rdf") + "type";
  const CRDFNode::multimap& nodeEdges = pNode->getEdges();
  CRDFNode::multimap::const_iterator it;
  for (it = nodeEdges.begin(); it != nodeEdges.end(); it++)
    {
      if (it->first == typePredicate)
        {
          if (typeResource == "")
          {return true;}
          else if (it->second->getObject().getResource() == typeResource)
          {return true;}
        }
    }
  return false;
}

bool CRDFGraph::addBagNodeToTable(const std::string& tableName)
{
  std::string tablePredicate = tagName2Predicate(tableName);
  CRDFSubject subject; CRDFObject object; std::string predicate;

  const CRDFNode::multimap& nodeEdges = mpAbout->getEdges();
  CRDFNode::multimap::const_iterator it;
  for (it = nodeEdges.begin(); it != nodeEdges.end(); it++)
    {
      if (it->first == tablePredicate)
      {break;}
    }
  if (it == nodeEdges.end())
  {return false;}

  CRDFNode * pTableNode = it->second;

  if (isBagNode(pTableNode))
  {return true;}

  //point pObjectNode to pTableNode.
  CRDFNode * pObjectNode = pTableNode;
  //remove Table Edge from about.
  mpAbout->removeEdge(tablePredicate);
  //create new tableNode
  std::string tableBlnkNodeId = getGeneratedId();
  subject.setType(CRDFSubject::RESOURCE);
  subject.setResource(mpAbout->getSubject().getResource(), mpAbout->getSubject().isLocal());
  object.setType(CRDFObject::BLANK_NODE);
  object.setBlankNodeId(tableBlnkNodeId);
  addTriplet(subject, tablePredicate, object);
  subject.clearData(); object.clearData();

  pTableNode = mBlankNodeId2Node[tableBlnkNodeId];

  //Set type of this table node to Bag
  predicate = getNameSpaceURI("rdf") + "type";
  subject.setType(CRDFSubject::BLANK_NODE);
  subject.setBlankNodeId(pTableNode->getId());
  object.setType(CRDFObject::RESOURCE);
  object.setResource(getNameSpaceURI("rdf") + "Bag", false);
  addTriplet(subject, predicate, object);
  subject.clearData(); object.clearData();

  predicate = getNameSpaceURI("rdf") + "_1";
  subject.setType(CRDFSubject::BLANK_NODE);
  subject.setBlankNodeId(pTableNode->getId());
  if (pObjectNode && pObjectNode->isObjectNode())
  {object = pObjectNode->getObject();}
  addTriplet(subject, predicate, object);
  subject.clearData(); object.clearData();

  return true;
}

bool CRDFGraph::removeBagNodeFromTable(const std::string& tableName)
{
  std::string tablePredicate = tagName2Predicate(tableName);

  const CRDFNode::multimap& nodeEdges = mpAbout->getEdges();
  CRDFNode::multimap::const_iterator it;
  for (it = nodeEdges.begin(); it != nodeEdges.end(); it++)
    {
      if (it->first == tablePredicate)
      {break;}
    }
  if (it == nodeEdges.end())
  {return false;}

  CRDFNode * pTableNode = it->second;

  if (!isBagNode(pTableNode))
  {return true;}

  if (getNoOfObjectsInTable(pTableNode) > 1)
  {return false;}

  std::string bagPredicate = getNameSpaceURI("rdf") + "type";
  const CRDFNode::multimap& tableNodeEdges = pTableNode->getEdges();
  CRDFNode::multimap::const_iterator tit;
  for (tit = tableNodeEdges.begin(); tit != tableNodeEdges.end(); tit++)
    {
      if (tit->first != bagPredicate)
      {break;}
    }

  //First point about to object Node
  CRDFNode * pObjectNode = NULL;
  if (tit != tableNodeEdges.end())
  {pObjectNode = tit->second;}
  if (pObjectNode)
    {
      mpAbout->removeEdge(tablePredicate);
      mpAbout->addEdge(tablePredicate, pObjectNode);
      //Remove Edge between table and object node
      pTableNode->removeEdge(tit->first);
      //Now delete the table node and its children.
      removeNode(pTableNode);
    }
  return true;
}

void CRDFGraph::bagTheNode(CRDFNode* pNode, CRDFObject* pChildObj)
{
  if (isBagNode(pNode))
  {return;}

  CRDFSubject subject; CRDFObject object; std::string predicate;
  CRDFNode::multimap edgesToRemove;

  std::string newBlankNodeId = getGeneratedId();
  subject.setType(CRDFSubject::BLANK_NODE);
  subject.setBlankNodeId(newBlankNodeId);

  //remove all Edges from the node and simultaneously add them to the newBlankNode.
  CRDFNode::const_iterator it = pNode->getEdges().begin();
  CRDFNode::const_iterator end = pNode->getEdges().end();
  for (; it != end; it++)
    {
      addTriplet(subject, it->first, it->second->getObject());
      std::pair<std::string, CRDFNode*> pr(it->first, it->second);
      edgesToRemove.insert(pr);
    }
  subject.clearData();

  it = edgesToRemove.begin(); end = edgesToRemove.end();
  for (; it != end; it++)
  {pNode->removeEdge(it->first, it->second);}

  //add the new Blank Node as an edge to the original pNode.
  CRDFNode* newBlankNode = mBlankNodeId2Node[newBlankNodeId];
  predicate = getNameSpaceURI("rdf") + "_1";
  pNode->addEdge(predicate, newBlankNode);
  if (pChildObj)
  {*pChildObj = newBlankNode->getObject();}

  //Finally add the BagNode to pNode.
  predicate = getNameSpaceURI("rdf") + "type";
  object.setType(CRDFObject::RESOURCE);
  object.setResource(getNameSpaceURI("rdf") + "Bag", false);
  addTriplet(pNode->getSubject(), predicate, object);
  object.clearData();
}

bool CRDFGraph::unbagTheNode(CRDFNode* pNode, CRDFObject* pChildObj)
{
  if (!isBagNode(pNode))
  {return true;}

  if (pNode->getEdges().size() > 2)
  {return false;}

  CRDFNode::multimap edgesToRemove;

  //Point it to Blank node edge.
  std::string bagPredicate = getNameSpaceURI("rdf") + "type";
  const CRDFNode::multimap& nodeEdges = pNode->getEdges();
  CRDFNode::multimap::const_iterator it = nodeEdges.begin();
  CRDFNode::multimap::const_iterator end = nodeEdges.end();
  CRDFNode* blankNode = NULL;
  std::string blankNodePredicate;
  for (; it != end; it++)
    {
      if (it->first != bagPredicate)
        {
          blankNodePredicate = it->first;
          blankNode = it->second;
          break;
        }
    }

  //remove the BagNode edge from pNode;
  pNode->removeEdge(bagPredicate);
  //remove the BlankNode edge from pNode;
  pNode->removeEdge(blankNodePredicate);

  //remove all Edges from the Blank node and simultaneously add them to pNode.
  it = blankNode->getEdges().begin();
  end = blankNode->getEdges().end();
  for (; it != end; it++)
    {
      addTriplet(pNode->getSubject(), it->first, it->second->getObject());
      std::pair<std::string, CRDFNode*> pr(it->first, it->second);
      edgesToRemove.insert(pr);
    }

  it = edgesToRemove.begin(); end = edgesToRemove.end();
  for (; it != end; it++)
  {blankNode->removeEdge(it->first, it->second);}

  if (pChildObj)
  {*pChildObj = pNode->getObject();}
  //Finally delete the BlankNode;
  mBlankNodeId2Node.erase(blankNode->getId());
  pdelete(blankNode);
  return true;
}

unsigned int CRDFGraph::getNoOfObjectsInTable(const CRDFNode * pTableNode)
{
  std::string bagPredicate = getNameSpaceURI("rdf") + "type";
  unsigned int count = 0;
  if (isBagNode(pTableNode))
    {
      const CRDFNode::multimap& nodeEdges = pTableNode->getEdges();
      CRDFNode::multimap::const_iterator it;
      for (it = nodeEdges.begin(); it != nodeEdges.end(); it++)
        {
          if (it->first != bagPredicate)
          {count++;}
        }
    }
  return count;
}

std::string CRDFGraph::getFieldValue(const std::string& fieldName, const CRDFObject& obj)
{
  CRDFNode * pFieldNode = findFieldNodeFromObject(fieldName, obj);
  if (!pFieldNode)
  {return "";}

  const CRDFObject & Object = pFieldNode->getObject();
  switch (Object.getType())
    {
    case CRDFObject::LITERAL:
      {
        const CRDFLiteral & Literal = Object.getLiteral();
        switch (Literal.getType())
          {
          case CRDFLiteral::PLAIN:
          case CRDFLiteral::TYPED:
            return Literal.getLexicalData();
            break;
          }
      }
      break;

    case CRDFObject::RESOURCE:
      return Object.getResource();
      break;
    case CRDFObject::BLANK_NODE:
      return Object.getBlankNodeID();
      break;
    }
  return "";
}

bool CRDFGraph::setFieldValue(const std::string& fieldName, CRDFObject& obj, const std::string& fieldValue)
{
  CRDFNode * pFieldNode = findFieldNodeFromObject(fieldName, obj);
  if (!pFieldNode || !pFieldNode->isObjectNode())
    {
      //Since no field found, build the record.
      if (fieldName == "vCard:Family" || fieldName == "vCard:Given" || fieldName == "vCard:EMAIL" || fieldName == "vCard:Orgname")
        {
          buildCreatorRecord(mBlankNodeId2Node[obj.getBlankNodeID()]);
          mChanged = true;
        }
      else if (fieldName == "PubmedId" || fieldName == "DOI" || fieldName == "dcterms:description")
        {
          buildReferenceRecord(mBlankNodeId2Node[obj.getBlankNodeID()]);
          mChanged = true;
        }
      else if (fieldName == "dcterms:W3CDTF")
        {
          CRDFNode * pTableNode = findNodeFromObject(obj);
          if (!pTableNode)
            {
              //addRecordToTable("Created", CRDFObject(obj), obj);
              pTableNode = findNodeFromObject(obj);
            }
          else
            {
              buildCreatedRecord(mBlankNodeId2Node[obj.getBlankNodeID()]);
              mChanged = true;
            }
        }
      else if (fieldName == "dcterms:W3CDTF")
        {
          buildModifiedRecord(mBlankNodeId2Node[obj.getBlankNodeID()]);
          mChanged = true;
        }

      //try again
      pFieldNode = findFieldNodeFromObject(fieldName, obj);
      if (!pFieldNode || !pFieldNode->isObjectNode()
          || pFieldNode->getObject().getType() == CRDFObject::BLANK_NODE)
        //Field Node is a leaf and cannot be a BLANK_NODE
        return false;
    }

  CRDFObject object; CRDFLiteral lit;
  switch (pFieldNode->getObject().getType())
    {
    case CRDFObject::LITERAL:
      lit.setLexicalData(fieldValue);
      object.setType(CRDFObject::LITERAL);
      object.setLiteral(lit);
      break;
    case CRDFObject::RESOURCE:
      object.setType(CRDFObject::RESOURCE);
      if (pFieldNode->getObject().isLocal())
        {
          mLocalResource2Node.erase(pFieldNode->getObject().getResource());
          //new resource will be considered remote resource.
          //Hence add in RemoteResource List.
          mRemoteResourceNodes.push_back(pFieldNode);
        }
      object.setResource(fieldValue, false);
      break;

    case CRDFObject::BLANK_NODE:
      return false;
      break;
    }

  pFieldNode->setObject(object);
  //Since RESOURCE and LITERAL don't recurse and the object's value has changed.
  if (obj.getType() == CRDFObject::RESOURCE || obj.getType() == CRDFObject::LITERAL)
  {obj = object;}

  mChanged = true;
  return true;
}

CRDFNode* CRDFGraph::findNodeFromObject(const CRDFObject& object)
{
  std::map< std::string, CRDFNode * >::iterator found;
  CRDFNode * pNode = NULL;
  switch (object.getType())
    {
    case CRDFObject::BLANK_NODE:
      if (strlen(object.getBlankNodeID().c_str()) == 0) break;
      found = mBlankNodeId2Node.find(object.getBlankNodeID());
      if (found != mBlankNodeId2Node.end())
      {pNode = found->second;}
      break;
    case CRDFObject::RESOURCE:
      if (strlen(object.getResource().c_str()) == 0) break;
      if (object.isLocal())
        {
          found = mLocalResource2Node.find(object.getResource());
          if (found != mLocalResource2Node.end())
          {pNode = found->second;}
        }
      else
        {
          std::vector< CRDFNode * >::iterator it;
          for (it = mRemoteResourceNodes.begin(); it != mRemoteResourceNodes.end(); it++)
            {
              if ((*it)->getObject().getResource() == object.getResource())
              {pNode = *it; break;}
            }
        }
      break;
    case CRDFObject::LITERAL:
      if (strlen(object.getLiteral().getLexicalData().c_str()) == 0) break;
      std::vector< CRDFNode * >::iterator it;
      for (it = mLiteralNodes.begin(); it != mLiteralNodes.end(); it++)
        {
          if ((*it)->getObject().getLiteral().getLexicalData() == object.getLiteral().getLexicalData())
          {pNode = *it; break;}
        }
      break;
    }
  return pNode;
}

CRDFNode* CRDFGraph::findFieldNodeFromObject(const std::string& fieldName, const CRDFObject& startObj)
{
  CRDFNode* fieldNode = NULL;
  CRDFNode* fieldNode2 = NULL;
  std::string predicate = "";
  std::string prefix = "";

  std::map<std::string, std::string> referencePredicates = CConstants::getReferencePredicates();
  if (fieldName == "PubmedId")
  {prefix = referencePredicates["Pubmed"];}
  else if (fieldName == "DOI")
  {prefix = referencePredicates["DOI"];}

  if (fieldName == "PubmedId" || fieldName == "DOI")
    {
      if (startObj.getType() == CRDFObject::RESOURCE)
        {
          fieldNode = findNodeFromObject(startObj);
          if (fieldNode->getObject().getResource().find(prefix, 0) != std::string::npos)
          {return fieldNode;}
          return NULL;
        }
      else if (startObj.getType() == CRDFObject::BLANK_NODE)
        {
          predicate = tagName2Predicate("rdf:_1");
          fieldNode = getNodeForPredicate(predicate, findNodeFromObject(startObj));

          if (fieldNode == NULL)
          {return fieldNode;}
          if (fieldNode->getObject().getResource().find(prefix, 0) != std::string::npos)
          {return fieldNode;}
          else
            {
              predicate = tagName2Predicate("rdf:_2");
              fieldNode2 = getNodeForPredicate(predicate, findNodeFromObject(startObj));
              if (fieldNode2 == NULL)
                return fieldNode2;
              if (fieldNode2->getObject().getResource().find(prefix, 0) != std::string::npos)
                return fieldNode2;
              else
                {
                  if (fieldName == "PubmedId" && fieldNode->getObject().getResource() == "")
                    return fieldNode;
                  else if (fieldName == "DOI" && fieldNode2->getObject().getResource() == "")
                    return fieldNode2;
                  else
                    return NULL;
                }
            }
        }
    }

  //if RESOURCE or LITERAL just return the startObj
  if (startObj.getType() == CRDFObject::RESOURCE ||
      startObj.getType() == CRDFObject::LITERAL)
    {
      return findNodeFromObject(startObj);
    }
  else if (startObj.getType() == CRDFObject::BLANK_NODE)
    {
      predicate = tagName2Predicate(fieldName);
      fieldNode = getNodeForPredicate(predicate, findNodeFromObject(startObj));
      return fieldNode;
    }

  return NULL;
}

CRDFNode* CRDFGraph::getNodeForPredicate(const std::string& predicate, const CRDFNode * startNode)
{
  if (!startNode)
  {return NULL;}

  if (!(startNode->isSubjectNode()))
  {return NULL;}

  CRDFNode * nodeForPredicate = NULL;
  CRDFNode::multimap::const_iterator it;
  const CRDFNode::multimap & edges = startNode->getEdges();
  for (it = edges.begin(); it != edges.end(); it++)
    {
      if (it->first == predicate)
        {
          nodeForPredicate = it->second;
          break;
        }
      else
        {
          CRDFNode* ret = getNodeForPredicate(predicate, it->second);
          if (ret != NULL)
          {return ret;}
        }
    }
  return nodeForPredicate;
}

bool CRDFGraph::removeNode(CRDFNode *pNode)
{
  if (pNode->getObject().getType() == CRDFObject::BLANK_NODE)
  {mBlankNodeId2Node.erase(pNode->getObject().getBlankNodeID());}
  else if (pNode->getObject().getType() == CRDFObject::RESOURCE)
    {
      if (pNode->getObject().isLocal())
      {mLocalResource2Node.erase(pNode->getObject().getResource());}
      else
        {
          std::vector< CRDFNode * >::iterator it;
          for (it = mRemoteResourceNodes.begin(); it != mRemoteResourceNodes.end(); it++)
            {
              if (*it == pNode)
              {mRemoteResourceNodes.erase(it); break;}
            }
        }
      return true;
    }
  else if (pNode->getObject().getType() == CRDFObject::LITERAL)
    {
      std::vector< CRDFNode * >::iterator it;
      for (it = mLiteralNodes.begin(); it != mLiteralNodes.end(); it++)
        {
          if (*it == pNode)
          {mLiteralNodes.erase(it); break;}
        }
    }

  if (pNode)
    {
      CRDFNode::multimap::const_iterator vit;
      for (vit = pNode->getEdges().begin(); vit != pNode->getEdges().end(); vit++)
      {removeNode(vit->second);}
      pdelete(pNode);
    }
  return true;
}

void CRDFGraph::compressGraph()
{
  if (mpAbout)
  {compressNode(mpAbout);}
}

bool CRDFGraph::compressNode(CRDFNode* pNode)
{
  if (pNode == NULL)
  {return false;}

  CRDFNode::multimap edgesToRemove;
  CRDFNode::const_iterator it = pNode->getEdges().begin();
  CRDFNode::const_iterator end = pNode->getEdges().end();
  //first recurse
  for (; it != end; it++)
    {
      std::pair< std::string, CRDFNode * > pr(it->first, it->second);
      if (compressNode(it->second))
      {edgesToRemove.insert(pr);}
    }

  end = edgesToRemove.end();
  for (it = edgesToRemove.begin(); it != end; it++)
  {pNode->removeEdge(it->first, it->second);}

  //compress
  CRDFSubject subject; CRDFObject object; CRDFLiteral lit;
  subject.clearData(); object.clearData(); lit.setLexicalData("");

  subject.setType(CRDFSubject::RESOURCE);
  CRDFObject::eObjectType nodeType = CRDFObject::RESOURCE;
  if (pNode != mpAbout)
  {nodeType = pNode->getObject().getType();}
  object.setType(nodeType);
  if (object.getType() == CRDFObject::LITERAL)
  {object.setLiteral(lit);}

  //If this is empty node - first check for about node.
  if (pNode == mpAbout)
    {
      if (pNode->getSubject() == subject)
      {return removeNode(pNode);}
    }
  else if (nodeType == CRDFObject::BLANK_NODE)
    {
      bool IsTypeNode = isTypeNode(pNode);
      if ((IsTypeNode && pNode->getEdges().size() == 1) || (!IsTypeNode && pNode->getEdges().size() == 0))
      {return removeNode(pNode);}
    }
  else if ((nodeType == CRDFObject::RESOURCE || nodeType == CRDFObject::LITERAL) && pNode->getObject() == object)
  {return removeNode(pNode);}
  return false;
}

std::string CRDFGraph::getGeneratedId()
{
  std::stringstream ss;
  ss << "GeneratedID" << ++nodeIDCounter;
  return ss.str();
}

std::string CRDFGraph::getNameSpaceURI(const std::string& lookupStr)
{
  //first look into the dynamically built data structure.
  std::map<std::string, std::string>::const_iterator it = mPrefix2Namespace.find(lookupStr);
  if (it != mPrefix2Namespace.end())
  {return it->second;}

  //then look into program hard coded data structure.
  std::map<std::string, std::string> prefix2URI = CConstants::getPrefix2URI();
  it = prefix2URI.find(lookupStr);
  if (it != prefix2URI.end())
  {return it->second;}
  else
  {return "";}
}

std::string CRDFGraph::tagName2Predicate(const std::string& tableName)
{
  std::string predicate;
  std::string::size_type loc = tableName.find(":", 0);
  if (loc == std::string::npos)
  {return "";}
  predicate = getNameSpaceURI(tableName.substr(0, loc)) + tableName.substr(loc + 1);
  return predicate;
}

CRDFGraph* CRDFGraph::loadGraph(CModelEntity* pEntity)
{
  mChanged = false;
  return CRDFParser::graphFromXml(pEntity->getMiriamAnnotation());
}
bool CRDFGraph::saveGraph(CModelEntity* pEntity)
{
  if (mChanged)
    {
      compressGraph();
      pEntity->setMiriamAnnotation(CRDFWriter::xmlFromGraph(this));
      mChanged = false;
      return true;
    }
  return false;
}

bool CRDFGraph::isChanged()
{return mChanged;}
