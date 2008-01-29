// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFGraph.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/29 15:00:39 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CRDFGraph.h"
#include "CRDFNode.h"
#include "CRDFSubject.h"
#include "CRDFObject.h"

CRDFGraph::CRDFGraph():
    mpAbout(NULL),
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
