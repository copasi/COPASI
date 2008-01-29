// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFGraph.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/29 20:14:44 $
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

bool CRDFGraph::printGraph()
{
  std::ofstream outFile;
  outFile.open ("output.txt");

  if (mpAbout)
    {
      outFile << mpAbout->stringFromNode() << std::endl;
      outFile << std::endl;
    }

  std::map< std::string, CRDFNode *>::iterator iter;
  for (iter = mBlankNodeId2Node.begin(); iter != mBlankNodeId2Node.end(); iter++)
    {
      outFile << "String: " << iter->first << ", Node: " << iter->second->stringFromNode() << std::endl;
    }
  outFile << std::endl;

  for (iter = mLocalResource2Node.begin(); iter != mLocalResource2Node.end(); iter++)
    {
      outFile << "String: " << iter->first << ", Node: " << iter->second->stringFromNode() << std::endl;
    }
  outFile << std::endl;

  std::vector< CRDFNode * >::iterator it;
  for (it = mLiteralNodes.begin(); it != mLiteralNodes.end(); it++)
    {
      outFile << "Node: " << (*it)->stringFromNode() << std::endl;
    }
  outFile << std::endl;

  outFile.close();
  return true;
}

bool CRDFGraph::getNodeIDsForTable(const std::string& tableName, std::vector<std::string>& nodeIds, std::string& tableNodeID)
{
  std::string predicate = tableName2Predicate(tableName);
  CRDFNode* tableBlankNode = getNodeForPredicate(predicate);
  if (!tableBlankNode)
  {return false;}
  tableNodeID = tableBlankNode->getId();

  bool isBagNode = false;
  std::string bagPredicate = getNameSpaceURI("rdf") + "type";
  std::vector< CRDFEdge >::const_iterator it;
  const std::vector<CRDFEdge> & edges = tableBlankNode->getEdges();
  for (it = edges.begin(); it != edges.end(); it++)
    {
      if (it->getPredicate() == bagPredicate)
      {isBagNode = true; break;}
    }
  if (isBagNode)
    {
      for (it = edges.begin(); it != edges.end(); it++)
        {
          if (it->getPredicate() != bagPredicate)
          {nodeIds.push_back(it->getPropertyNode()->getId());}
        }
    }
  else
  {nodeIds.push_back(tableBlankNode->getId());}
  return true;
}

void CRDFGraph::addObjectToTable(const std::string& tableName, std::string& tableNodeID, const std::string& childNodeID)
{
  CRDFSubject subject; CRDFObject object; std::string predicate = "";
  std::map< std::string, CRDFNode * >::iterator found;
  if (strlen(childNodeID.c_str()) == 0)
  {return;}

  //create the about node if it does not exist.
  if (!mpAbout)
    {
      mpAbout = new CRDFNode();
      std::string aboutResource = getGeneratedId();
      subject.setType(CRDFSubject::RESOURCE);
      subject.setResource(aboutResource, true);
      mpAbout->setSubject(subject);
      subject.clearData();
      mLocalResource2Node[aboutResource] = mpAbout;
    }
  CRDFNode * pTableNode = NULL;
  found = mBlankNodeId2Node.find(tableNodeID);
  if (found != mBlankNodeId2Node.end())
  {pTableNode = found->second;}
  //create the table node if it does not exist.
  if (!pTableNode)
    {
      predicate = tableName2Predicate(tableName);
      tableNodeID = childNodeID;
      subject.setType(CRDFSubject::RESOURCE);
      subject.setResource(mpAbout->getSubject().getResource(), true);
      object.setType(CRDFObject::BLANK_NODE);
      object.setBlankNodeId(tableNodeID);
      addTriplet(subject, predicate, object);
      subject.clearData(); object.clearData();
      pTableNode = mBlankNodeId2Node[tableNodeID];
    }

  if (isBagNode(pTableNode))
    {
      predicate = getNameSpaceURI("rdf") + "_" + childNodeID;

      subject.setType(CRDFSubject::BLANK_NODE);
      subject.setBlankNodeId(pTableNode->getId());
      object.setType(CRDFObject::BLANK_NODE);
      object.setBlankNodeId(childNodeID);
      addTriplet(subject, predicate, object);
      subject.clearData(); object.clearData();

      CRDFNode * pObjNode = NULL;
      found = mBlankNodeId2Node.find(childNodeID);
      if (found != mBlankNodeId2Node.end())
      {pObjNode = found->second;}
      if (tableName == "Creators")
      {addNewCreatorNodes(pObjNode);}
    }
  else
    {
      if (tableName == "Creators")
      {addNewCreatorNodes(pTableNode);}
    }
}

void CRDFGraph::addNewCreatorNodes(const CRDFNode * pObjNode)
{
  CRDFSubject subject;
  CRDFObject object;
  CRDFLiteral lit;

  std::string nameBlnkNodeId = getGeneratedId();

  std::string predicate = getNameSpaceURI("vcard") + "N";
  subject.setType(CRDFSubject::BLANK_NODE);
  subject.setBlankNodeId(pObjNode->getId());
  object.setType(CRDFObject::BLANK_NODE);
  object.setBlankNodeId(nameBlnkNodeId);
  addTriplet(subject, predicate, object);
  subject.clearData(); object.clearData();

  predicate = getNameSpaceURI("vcard") + "Family";
  subject.setType(CRDFSubject::BLANK_NODE);
  subject.setBlankNodeId(nameBlnkNodeId);
  object.setType(CRDFObject::LITERAL);
  lit.setType(CRDFLiteral::PLAIN);
  object.setLiteral(lit);
  addTriplet(subject, predicate, object);
  subject.clearData(); object.clearData();

  predicate = getNameSpaceURI("vcard") + "Given";
  subject.setType(CRDFSubject::BLANK_NODE);
  subject.setBlankNodeId(nameBlnkNodeId);
  object.setType(CRDFObject::LITERAL);
  lit.setType(CRDFLiteral::PLAIN);
  object.setLiteral(lit);
  addTriplet(subject, predicate, object);
  subject.clearData(); object.clearData();

  predicate = getNameSpaceURI("vcard") + "EMAIL";
  subject.setType(CRDFSubject::BLANK_NODE);
  subject.setBlankNodeId(pObjNode->getId());
  object.setType(CRDFObject::LITERAL);
  lit.setType(CRDFLiteral::PLAIN);
  object.setLiteral(lit);
  addTriplet(subject, predicate, object);
  subject.clearData(); object.clearData();

  predicate = getNameSpaceURI("vcard") + "ORG";
  nameBlnkNodeId = getGeneratedId();
  subject.setType(CRDFSubject::BLANK_NODE);
  subject.setBlankNodeId(pObjNode->getId());
  object.setType(CRDFObject::BLANK_NODE);
  object.setBlankNodeId(nameBlnkNodeId);
  addTriplet(subject, predicate, object);
  subject.clearData(); object.clearData();

  CRDFNode * pOrgNode = mBlankNodeId2Node[nameBlnkNodeId];

  predicate = getNameSpaceURI("vcard") + "Orgname";
  subject.setType(CRDFSubject::BLANK_NODE);
  subject.setBlankNodeId(pOrgNode->getId());
  object.setType(CRDFObject::LITERAL);
  lit.setType(CRDFLiteral::PLAIN);
  object.setLiteral(lit);
  addTriplet(subject, predicate, object);
  subject.clearData(); object.clearData();
}

bool CRDFGraph::removeObjectFromTable(const std::string& tableName, std::string& tableNodeID, const std::string& childNodeID)
{
  if (strlen(tableNodeID.c_str()) == 0 || strlen(childNodeID.c_str()) == 0)
  {return false;}

  std::string bagPredicate = getNameSpaceURI("rdf") + "type";
  std::vector< CRDFEdge >::const_iterator it;
  CRDFNode * tableNode = mBlankNodeId2Node[tableNodeID];
  bool IsBagNode = isBagNode(tableNode);
  if (tableNode)
    {
      const std::vector< CRDFEdge >& tableEdges = tableNode->getEdges();
      if (IsBagNode)
        {
          for (it = tableEdges.begin(); it != tableEdges.end(); it++)
            {
              if (it->getPropertyNode()->getId() == childNodeID)
              {break;}
            }
        }
    }
  if (removeNode(childNodeID, CRDFObject::BLANK_NODE))
    {
      if (tableNode && IsBagNode)
      {tableNode->removeEdge(it->getPredicate());}
      else if (!IsBagNode && mpAbout)
        {
          mpAbout->removeEdge(tableName2Predicate(tableName));
          tableNodeID = "";
        }
    }
  return true;
}

bool CRDFGraph::isBagNode(const CRDFNode * pNode)
{
  std::string bagPredicate = getNameSpaceURI("rdf") + "type";
  const std::vector< CRDFEdge >& nodeEdges = pNode->getEdges();
  std::vector< CRDFEdge >::const_iterator it;
  for (it = nodeEdges.begin(); it != nodeEdges.end(); it++)
    {
      if (it->getPredicate() == bagPredicate)
      {return true;}
    }
  return false;
}

bool CRDFGraph::addBagNodeToTable(const std::string& tableName, std::string& tableGraphID)
{
  std::string tablePredicate = tableName2Predicate(tableName);
  CRDFSubject subject; CRDFObject object; std::string predicate;

  const std::vector< CRDFEdge >& nodeEdges = mpAbout->getEdges();
  std::vector< CRDFEdge >::const_iterator it;
  for (it = nodeEdges.begin(); it != nodeEdges.end(); it++)
    {
      if (it->getPredicate() == tablePredicate)
      {break;}
    }
  if (it == nodeEdges.end())
  {return false;}

  CRDFNode * pTableNode = it->getPropertyNode();

  //Add bag node only if 1 object present in table.
  /*if (getNoOfObjectsInTable(pTableNode) != 1)
  {return false;}*/

  //point pObjectNode to pTableNode.
  CRDFNode * pObjectNode = pTableNode;
  //remove Table Edge from about.
  mpAbout->removeEdge(tablePredicate);
  //create new tableNode
  std::string tableBlnkNodeId = getGeneratedId();
  subject.setType(CRDFSubject::RESOURCE);
  subject.setResource(mpAbout->getSubject().getResource(), true);
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
  object.setResource(getNameSpaceURI("rdf") + "Bag", true);
  addTriplet(subject, predicate, object);
  subject.clearData(); object.clearData();

  predicate = getNameSpaceURI("rdf") + "_1";
  subject.setType(CRDFSubject::BLANK_NODE);
  subject.setBlankNodeId(pTableNode->getId());
  object.setType(CRDFObject::BLANK_NODE);
  object.setBlankNodeId(pObjectNode->getId());
  addTriplet(subject, predicate, object);
  subject.clearData(); object.clearData();

  tableGraphID = pTableNode->getId();
  return true;
}

bool CRDFGraph::removeBagNodeFromTable(const std::string& tableName, std::string& tableGraphID)
{
  std::string tablePredicate = tableName2Predicate(tableName);

  const std::vector< CRDFEdge >& nodeEdges = mpAbout->getEdges();
  std::vector< CRDFEdge >::const_iterator it;
  for (it = nodeEdges.begin(); it != nodeEdges.end(); it++)
    {
      if (it->getPredicate() == tablePredicate)
      {break;}
    }
  if (it == nodeEdges.end())
  {return false;}

  CRDFNode * pTableNode = it->getPropertyNode();

  if (getNoOfObjectsInTable(pTableNode) > 1)
  {return false;}

  std::string bagPredicate = getNameSpaceURI("rdf") + "type";
  const std::vector< CRDFEdge >& tableNodeEdges = pTableNode->getEdges();
  std::vector< CRDFEdge >::const_iterator tit;
  for (tit = tableNodeEdges.begin(); tit != tableNodeEdges.end(); tit++)
    {
      if (tit->getPredicate() != bagPredicate)
      {break;}
    }

  //First point about to object Node
  CRDFNode * pObjectNode = tit->getPropertyNode();
  mpAbout->removeEdge(tablePredicate);
  mpAbout->addEdge(tablePredicate, pObjectNode);
  //Remove Edge between table and object node
  pTableNode->removeEdge(tit->getPredicate());
  //Now delete the table node and its children.
  removeNode(pTableNode->getId(), CRDFObject::BLANK_NODE);
  //Finally return the ID of object as the new tableNodeID.
  tableGraphID = pObjectNode->getId();
  return true;
}

unsigned int CRDFGraph::getNoOfObjectsInTable(const CRDFNode * pTableNode)
{
  std::string bagPredicate = getNameSpaceURI("rdf") + "type";
  unsigned int count = 0;
  const std::vector< CRDFEdge >& nodeEdges = pTableNode->getEdges();
  std::vector< CRDFEdge >::const_iterator it;
  for (it = nodeEdges.begin(); it != nodeEdges.end(); it++)
    {
      if (it->getPredicate() != bagPredicate)
      {count++;}
    }
  return count;
}

std::string CRDFGraph::getFieldValue(const std::string& fieldName, const std::string& graphNodeId)
{
  std::string predicate = fieldName2Predicate(fieldName);
  CRDFNode* fieldNode = getNodeForPredicate(predicate, mBlankNodeId2Node[graphNodeId]);

  if (!fieldNode)
  {return "Field Not Found";}

  const CRDFObject & Object = fieldNode->getObject();
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

bool CRDFGraph::setFieldValue(const std::string& fieldName, const std::string& graphNodeId, const std::string& fieldValue)
{
  std::string predicate = fieldName2Predicate(fieldName);
  CRDFNode* fieldNode = getNodeForPredicate(predicate, mBlankNodeId2Node[graphNodeId]);
  if (!fieldNode)
  {return false;}

  const CRDFObject & Object = fieldNode->getObject();
  CRDFObject * newObject = new CRDFObject (Object);
  switch (Object.getType())
    {
    case CRDFObject::LITERAL:
      {
        CRDFLiteral* Literal = new CRDFLiteral(Object.getLiteral());
        Literal->setLexicalData(fieldValue);
        newObject->setLiteral(*Literal);
        break;
      }
      break;
    case CRDFObject::RESOURCE:
      newObject->setResource(fieldValue, true);
      break;
    case CRDFObject::BLANK_NODE:
      newObject->setBlankNodeId(fieldValue);
      break;
    }
  fieldNode->setObject(*newObject);
  return true;
}

CRDFNode* CRDFGraph::getNodeForPredicate(const std::string& predicate, const CRDFNode * startNode)
{
  if (!startNode)
    {
      if (mpAbout)
      {startNode = mpAbout;}
      else
      {return NULL;}
    }

  if (!(startNode->isSubjectNode()))
  {return NULL;}

  CRDFNode * nodeForPredicate = NULL;
  std::vector< CRDFEdge >::const_iterator it;
  const std::vector<CRDFEdge> & edges = startNode->getEdges();
  for (it = edges.begin(); it != edges.end(); it++)
    {
      if (it->getPredicate() == predicate)
        {
          nodeForPredicate = it->getPropertyNode();
          break;
        }
      else
        {
          CRDFNode* ret = getNodeForPredicate(predicate, it->getPropertyNode());
          if (ret != NULL)
          {return ret;}
        }
    }
  return nodeForPredicate;
}

bool CRDFGraph::removeNode(const std::string& nodeIdOrResourceOrLiteral, CRDFObject::eObjectType nodeType)
{
  CRDFNode * pNodeToDel = NULL;

  if (nodeType == CRDFObject::BLANK_NODE)
    {
      std::map< std::string, CRDFNode * >::iterator it = mBlankNodeId2Node.find(nodeIdOrResourceOrLiteral);
      if (it != mBlankNodeId2Node.end())
      {pNodeToDel = it->second;}
      if (!pNodeToDel){return false;}
      mBlankNodeId2Node.erase(it);
    }
  else if (nodeType == CRDFObject::RESOURCE)
    {
      std::map< std::string, CRDFNode * >::iterator it = mLocalResource2Node.find(nodeIdOrResourceOrLiteral);
      if (it != mLocalResource2Node.end())
      {pNodeToDel = it->second;}
      if (!pNodeToDel){return false;}
      mLocalResource2Node.erase(it);
    }
  else if (nodeType == CRDFObject::LITERAL)
    {
      std::vector< CRDFNode * >::iterator it;
      for (it = mLiteralNodes.begin(); it != mLiteralNodes.end(); it++)
        {
          if ((*it)->getObject().getLiteral().getLexicalData() == nodeIdOrResourceOrLiteral)
            {
              pNodeToDel = *it;
              mLiteralNodes.erase(it); break;
            }
        }
      if (!pNodeToDel){return false;}
    }

  if (pNodeToDel)
    {
      std::vector< CRDFEdge >::const_iterator vit;
      for (vit = pNodeToDel->getEdges().begin(); vit != pNodeToDel->getEdges().end(); vit++)
        {
          CRDFObject::eObjectType childNodeType = vit->getPropertyNode()->getObject().getType();
          switch (childNodeType)
            {
            case CRDFObject::BLANK_NODE:
              removeNode(vit->getPropertyNode()->getId(), childNodeType);
              break;
            case CRDFObject::RESOURCE:
              removeNode(vit->getPropertyNode()->getObject().getResource(), childNodeType);
              break;
            case CRDFObject::LITERAL:
              removeNode(vit->getPropertyNode()->getObject().getLiteral().getLexicalData(), childNodeType);
              break;
            }
        }
      pdelete(pNodeToDel);
    }
  return true;
}

std::string CRDFGraph::getGeneratedId()
{
  std::stringstream ss;
  ss << "GeneratedID" << ++nodeIDCounter;
  return ss.str();
}

std::string CRDFGraph::getNameSpaceURI(const std::string& lookupStr)
{
  if (lookupStr == "rdf")
  {return "http://www.w3.org/1999/02/22-rdf-syntax-ns#";}
  else if (lookupStr == "dc")
  {return "http://purl.org/dc/elements/1.1/";}
  else if (lookupStr == "dcterms")
  {return "http://purl.org/dc/terms/";}
  else if (lookupStr == "vcard")
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
  {predicate = getNameSpaceURI("vcard") + "Family";}
  else if (fieldName == "GivenName")
  {predicate = getNameSpaceURI("vcard") + "Given";}
  else if (fieldName == "Email")
  {predicate = getNameSpaceURI("vcard") + "EMAIL";}
  else if (fieldName == "Orgname")
  {predicate = getNameSpaceURI("vcard") + "Orgname";}
  return predicate;
}

std::string CRDFGraph::tableName2Predicate(const std::string& tableName)
{
  std::string predicate;
  if (tableName == "Creators")
  {predicate = getNameSpaceURI("dc") + "creator";}
  return predicate;
}
