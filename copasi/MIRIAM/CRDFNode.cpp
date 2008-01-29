// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFNode.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/01/29 15:43:44 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CRDFNode.h"
#include "CRDFSubject.h"
#include "CRDFObject.h"
#include "CRDFLiteral.h"

using namespace std;

CRDFNode::CRDFNode():
    mId(""),
    mpSubject(NULL),
    mpObject(NULL),
    mEdges(),
    mIsBlankNode(false)
{}

CRDFNode::~CRDFNode()
{
  pdelete(mpSubject);
  pdelete(mpObject);
}

void CRDFNode::setId(const std::string & id)
{mId = id;}

const std::string & CRDFNode::getId() const
  {return mId;}

void CRDFNode::setSubject(const CRDFSubject & subject)
{
  pdelete(mpSubject);
  mpSubject = new CRDFSubject(subject);

  if (mpSubject->getType() == CRDFSubject::BLANK_NODE)
    {
      mIsBlankNode = true;
      mId = mpSubject->getBlankNodeID();

      pdelete(mpObject);
      mpObject = new CRDFObject;
      mpObject->setType(CRDFObject::BLANK_NODE);
      mpObject->setBlankNodeId(mId);
    }
}

const CRDFSubject & CRDFNode::getSubject() const
  {
    if (mpSubject == NULL)
      mpSubject = new CRDFSubject;

    return *mpSubject;
  }

void CRDFNode::setObject(const CRDFObject & object)
{
  pdelete(mpObject);
  mpObject = new CRDFObject(object);

  if (mpObject->getType() == CRDFObject::BLANK_NODE)
    {
      mIsBlankNode = true;
      mId = mpObject->getBlankNodeID();

      pdelete(mpSubject);
      mpSubject = new CRDFSubject;
      mpSubject->setType(CRDFSubject::BLANK_NODE);
      mpSubject->setBlankNodeId(mId);
    }
}

const CRDFObject & CRDFNode::getObject() const
  {
    if (mpObject == NULL)
      mpObject = new CRDFObject;

    return *mpObject;
  }

void CRDFNode::addEdge(const std::string & predicate,
                       CRDFNode * pObject)
{mEdges.push_back(CRDFEdge(predicate, pObject));}

bool CRDFNode::removeEdge(const std::string & predicate)
{
  std::vector< CRDFEdge >::iterator it;
  for (it = mEdges.begin(); it != mEdges.end(); it++)
    {
      if (it->getPredicate() == predicate)
      {mEdges.erase(it); return true;}
    }
  return false;
}

const std::vector< CRDFEdge > & CRDFNode::getEdges() const
  {return mEdges;}

bool CRDFNode::isSubjectNode() const
  {return mpSubject != NULL;}

bool CRDFNode::isObjectNode() const
  {return mpObject != NULL;}

bool CRDFNode::isBlankNode() const
  {return mIsBlankNode;}

std::string CRDFNode::stringFromNode(bool recurse)
{
  string str;
  str = "ID: " + mId + " Subject: ";

  if (isSubjectNode())
  {str += "Y";}
  else
  {str += "N";}

  str += " Object: ";
  if (isObjectNode())
  {str += "Y";}
  else
  {str += "N";}

  str += " BlankNode: ";
  if (mIsBlankNode)
  {str += "Y";}
  else
  {str += "N";}

  str += " Edges: ";
  vector<CRDFEdge>::iterator iter;
  for (iter = mEdges.begin(); iter != mEdges.end(); iter++)
    {
      str += iter->getPredicate();
      if (recurse)
        {
          CRDFNode *PropertyNode = iter->getPropertyNode();
          str += " Property Node: " + PropertyNode->stringFromNode(false) + ";";
        }
    }

  if (mpSubject)
    str += "Sub Details BlankNodeID: " + mpSubject->getBlankNodeID() + " Resource: " + mpSubject->getResource();
  if (mpObject)
    {
      str += "Obj Details BlankNodeID: " + mpObject->getBlankNodeID() + " Resource: " + mpObject->getResource();
      str += " Literal: Lexical Data: " + mpObject->getLiteral().getLexicalData() + "Data Type: " + mpObject->getLiteral().getDataType() + "Language: " + mpObject->getLiteral().getLanguage();
    }

  return str;
}
