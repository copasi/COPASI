// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFGraph.cpp,v $
//   $Revision: 1.20 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/02/20 19:06:27 $
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

#include "utilities/CCopasiMessage.h"

unsigned int CRDFGraph::nodeIDCounter = 0;

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

bool CRDFGraph::getNodeIDsForTable(const std::string& tableName, std::vector<CRDFObject>& objects, CRDFObject& tableObj)
{
  std::string predicate = tableName2Predicate(tableName);
  CRDFNode* pTableNode = getNodeForPredicate(predicate);
  if (!pTableNode)
  {return false;}
  tableObj = pTableNode->getObject();
  objects.clear();

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

void CRDFGraph::addRecordToTable(const std::string& tableName, CRDFObject& tableObj, const CRDFObject& childObj)
{
  std::string predicate = "";

  //create the about node if it does not exist.
  if (!mpAbout)
  {createAboutNode();}

  CRDFNode * pTableNode = findNodeFromObject(tableObj);
  //create the table node as a blank node if it does not exist.
  if (!pTableNode)
    {
      std::string predicate = tableName2Predicate(tableName);
      addTriplet(mpAbout->getSubject(), predicate, childObj);
      pTableNode = findNodeFromObject(childObj);
      tableObj = childObj;
    }

  if (isBagNode(pTableNode))
  {addObjectToBagNode(tableName, pTableNode, childObj);}
  else
    {
      if (pTableNode->getEdges().size() > 0)
        {
          addBagNodeToTable(tableName, tableObj);
          //since addBagNodeToTable() would have changed tableObj find it again.
          pTableNode = findNodeFromObject(tableObj);
          addObjectToBagNode(tableName, pTableNode, childObj);
        }
      else
        {
          if (tableName == "Creators")
          {buildCreatorRecord(pTableNode);}
          else if (tableName == "Publications")
          {buildPublicationRecord(pTableNode);}
          else if (tableName == "Created")
          {buildCreatedRecord(pTableNode);}
          else if (tableName == "Modifieds")
          {buildModifiedRecord(pTableNode);}
        }
    }
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
  pObjNode = findNodeFromObject(object);

  if (object.getType() == CRDFObject::BLANK_NODE)
    // A Bag Node should be a BLANK_NODE anyway
    {
      if (tableName == "Creators")
      {buildCreatorRecord(pObjNode);}
      else if (tableName == "Publications")
      {buildPublicationRecord(pObjNode);}
      else if (tableName == "Modifieds")
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
      subject.setType(CRDFSubject::BLANK_NODE);
      subject.setBlankNodeId(pObjNode->getId());
      object.setType(CRDFObject::BLANK_NODE);
      object.setBlankNodeId(blankNodeId);
      addTriplet(subject, predicate, object);
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
      subject.setType(CRDFSubject::BLANK_NODE);
      subject.setBlankNodeId(pObjNode->getId());
      object.setType(CRDFObject::LITERAL);
      lit.setType(CRDFLiteral::PLAIN);
      object.setLiteral(lit);
      addTriplet(subject, predicate, object);
      subject.clearData(); object.clearData();
    }

  predicate = getNameSpaceURI("vCard") + "ORG";
  if (!pObjNode->edgeExists(predicate))
    {
      blankNodeId = getGeneratedId();
      subject.setType(CRDFSubject::BLANK_NODE);
      subject.setBlankNodeId(pObjNode->getId());
      object.setType(CRDFObject::BLANK_NODE);
      object.setBlankNodeId(blankNodeId);
      addTriplet(subject, predicate, object);
      subject.clearData(); object.clearData();
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

void CRDFGraph::buildPublicationRecord(const CRDFNode * pObjNode)
{
  CRDFSubject subject; CRDFObject object; CRDFLiteral lit; std::string predicate;

  predicate = getNameSpaceURI("bqmodel") + "isDescribedBy";
  if (!pObjNode->edgeExists(predicate))
    {
      subject.setType(CRDFSubject::BLANK_NODE);
      subject.setBlankNodeId(pObjNode->getId());
      object.setType(CRDFObject::RESOURCE);
      addTriplet(subject, predicate, object);
      subject.clearData(); object.clearData();
    }
}

void CRDFGraph::buildCreatedRecord(const CRDFNode * pObjNode)
{
  CRDFSubject subject; CRDFObject object; CRDFLiteral lit;
  std::string predicate;
  std::pair< CRDFNode::const_iterator, CRDFNode::const_iterator > pr;

  predicate = getNameSpaceURI("dcterms") + "W3CDTF";
  if (!pObjNode->edgeExists(predicate))
    {
      subject.setType(CRDFSubject::BLANK_NODE);
      subject.setBlankNodeId(pObjNode->getId());
      object.setType(CRDFObject::LITERAL);
      lit.setType(CRDFLiteral::PLAIN);
      object.setLiteral(lit);
      addTriplet(subject, predicate, object);
      subject.clearData(); object.clearData();
    }
}

void CRDFGraph::buildModifiedRecord(const CRDFNode * pObjNode)
{
  CRDFSubject subject; CRDFObject object; CRDFLiteral lit;
  std::string predicate;
  std::pair< CRDFNode::const_iterator, CRDFNode::const_iterator > pr;

  predicate = getNameSpaceURI("dcterms") + "W3CDTF";
  if (!pObjNode->edgeExists(predicate))
    {
      subject.setType(CRDFSubject::BLANK_NODE);
      subject.setBlankNodeId(pObjNode->getId());
      object.setType(CRDFObject::LITERAL);
      lit.setType(CRDFLiteral::PLAIN);
      object.setLiteral(lit);
      addTriplet(subject, predicate, object);
      subject.clearData(); object.clearData();
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

bool CRDFGraph::removeRecordFromTable(const std::string& tableName, CRDFObject& tableObj, const CRDFObject& childObj)
{
  CRDFNode::multimap::const_iterator it;
  CRDFNode * tableNode = findNodeFromObject(tableObj);
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

      if (removeNode(it->second))
        {
          tableNode->removeEdge(it->first);
          if (tableNode->getEdges().size() == 2)
          {removeBagNodeFromTable(tableName, tableObj);}
        }
    }
  else
    {
      if (removeNode(tableNode))
        {
          mpAbout->removeEdge(tableName2Predicate(tableName));
          tableObj.clearData();
        }
    }
  return true;
}

bool CRDFGraph::isBagNode(const CRDFNode * pNode)
{
  std::string bagPredicate = getNameSpaceURI("rdf") + "type";
  const CRDFNode::multimap& nodeEdges = pNode->getEdges();
  CRDFNode::multimap::const_iterator it;
  for (it = nodeEdges.begin(); it != nodeEdges.end(); it++)
    {
      if (it->first == bagPredicate)
      {return true;}
    }
  return false;
}

bool CRDFGraph::addBagNodeToTable(const std::string& tableName, CRDFObject& tableObj)
{
  std::string tablePredicate = tableName2Predicate(tableName);
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

  tableObj = pTableNode->getObject();
  return true;
}

bool CRDFGraph::removeBagNodeFromTable(const std::string& tableName, CRDFObject& tableObj)
{
  std::string tablePredicate = tableName2Predicate(tableName);

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
      //Finally return the object as the new tableObj.
      tableObj = pObjectNode->getObject();
    }
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

bool CRDFGraph::setFieldValue(const std::string& fieldName, const CRDFObject& obj, const std::string& fieldValue)
{
  CRDFNode * pFieldNode = findFieldNodeFromObject(fieldName, obj);
  if (!pFieldNode || !pFieldNode->isObjectNode())
    {
      //Since no field found, build the record.
      if (fieldName == "FamilyName" || fieldName == "GivenName" || fieldName == "Email" || fieldName == "Orgname")
      {buildCreatorRecord(mBlankNodeId2Node[obj.getBlankNodeID()]);}
      else if (fieldName == "PubmedID")
      {buildPublicationRecord(mBlankNodeId2Node[obj.getBlankNodeID()]);}
      else if (fieldName == "Created")
        {
          CRDFNode * pTableNode = findNodeFromObject(obj);
          if (!pTableNode)
            {
              //addRecordToTable("Created", CRDFObject(obj), obj);
              //Do you really want to pass a temporary object as reference?
              pTableNode = findNodeFromObject(obj);
            }
          else
          {buildCreatedRecord(mBlankNodeId2Node[obj.getBlankNodeID()]);}
        }
      else if (fieldName == "DateModified")
      {buildModifiedRecord(mBlankNodeId2Node[obj.getBlankNodeID()]);}

      //try again
      pFieldNode = findFieldNodeFromObject(fieldName, obj);
      if (!pFieldNode || !pFieldNode->isObjectNode()
          || pFieldNode->getObject().getType() == CRDFObject::BLANK_NODE)
        //Field Node is a leaf and cannot be a BLANK_NODE
      {return false;}
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
          mLocalResource2Node[fieldValue] = pFieldNode;
        }
      object.setResource(fieldValue, pFieldNode->getObject().isLocal());
      break;
    }
  pFieldNode->setObject(object);
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
  std::string predicate = "";
  predicate = fieldName2Predicate(fieldName);
  fieldNode = getNodeForPredicate(predicate, findNodeFromObject(startObj));
  return fieldNode;
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
      bool IsBagNode = isBagNode(pNode);
      if ((IsBagNode && pNode->getEdges().size() == 1) || (!IsBagNode && pNode->getEdges().size() == 0))
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
  std::map<std::string, std::string>::const_iterator it = mPrefix2Namespace.find(lookupStr);
  if (it != mPrefix2Namespace.end())
  {return it->second;}

  if (lookupStr == "rdf")
  {return "http://www.w3.org/1999/02/22-rdf-syntax-ns#";}
  else if (lookupStr == "dc")
  {return "http://purl.org/dc/elements/1.1/";}
  else if (lookupStr == "dcterms")
  {return "http://purl.org/dc/terms/";}
  else if (lookupStr == "vCard")
  {return "http://www.w3.org/2001/vcard-rdf/3.0#";}
  else if (lookupStr == "bqbiol")
  {return "http://biomodels.net/biology-qualifiers/";}
  else if (lookupStr == "bqmodel")
  {return "http://biomodels.net/model-qualifiers/";}
  else
  {return "";}
}

std::string CRDFGraph::fieldName2Predicate(const std::string& fieldName)
{
  std::string predicate = "";
  if (fieldName == "FamilyName")
  {predicate = getNameSpaceURI("vCard") + "Family";}
  else if (fieldName == "GivenName")
  {predicate = getNameSpaceURI("vCard") + "Given";}
  else if (fieldName == "Email")
  {predicate = getNameSpaceURI("vCard") + "EMAIL";}
  else if (fieldName == "Orgname")
  {predicate = getNameSpaceURI("vCard") + "Orgname";}
  else if (fieldName == "PubmedID")
  {predicate = getNameSpaceURI("bqmodel") + "isDescribedBy";}
  else if (fieldName == "Created" || fieldName == "DateModified")
  {predicate = getNameSpaceURI("dcterms") + "W3CDTF";}
  return predicate;
}

std::string CRDFGraph::tableName2Predicate(const std::string& tableName)
{
  std::string predicate;
  if (tableName == "Creators")
  {predicate = getNameSpaceURI("dc") + "creator";}
  else if (tableName == "Publications")
  {predicate = getNameSpaceURI("bqmodel") + "isDescribedBy";}
  else if (tableName == "Created")
  {predicate = getNameSpaceURI("dcterms") + "created";}
  else if (tableName == "Modifieds")
  {predicate = getNameSpaceURI("dcterms") + "modified";}
  return predicate;
}
