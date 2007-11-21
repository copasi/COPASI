// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFGraph.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/21 16:15:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CRDFGraph.h"
#include "CRDFNode.h"
#include "CRDFSubject.h"
#include "CRDFObject.h"

CRDFGraph::CRDFGraph():
    mpAbout(new CRDFNode),
    mBlankNodeId2Node(),
    mResource2Node(),
    mLiteralNodes()
{}

CRDFGraph::~CRDFGraph()
{
  std::map< std::string, CRDFNode * >::iterator itMap;
  std::map< std::string, CRDFNode * >::iterator endMap;

  for (itMap = mBlankNodeId2Node.begin(), endMap = mBlankNodeId2Node.end();
       itMap != endMap; ++itMap)
    delete itMap->second;

  for (itMap = mResource2Node.begin(), endMap = mResource2Node.end();
       itMap != endMap; ++itMap)
    delete itMap->second;

  std::vector< CRDFNode *>::iterator itVector;
  std::vector< CRDFNode *>::iterator endVector;
  for (itVector = mLiteralNodes.begin(), endVector = mLiteralNodes.end();
       itVector != endVector; ++itVector)
    delete *itVector;
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
      found = mResource2Node.find(subject.getResource());
      if (found != mResource2Node.end())
        pSubjectNode = found->second;
      else
        {
          pSubjectNode = mpAbout;
          pSubjectNode->setSubject(subject);
          mResource2Node[subject.getResource()] = pSubjectNode;
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
      found = mResource2Node.find(object.getResource());
      if (found != mResource2Node.end())
        pObjectNode = found->second;
      else
        {
          pObjectNode = new CRDFNode;
          pObjectNode->setObject(object);
          mResource2Node[object.getResource()] = pObjectNode;
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
