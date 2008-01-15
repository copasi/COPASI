// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFNode.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/15 17:45:38 $
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
  if (mIsBlankNode) return;

  pdelete(mpObject);
  mpObject = new CRDFObject(object);
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

const std::vector< CRDFEdge > & CRDFNode::getEdges() const
  {return mEdges;}

bool CRDFNode::isSubjectNode() const
  {return mpSubject != NULL;}

bool CRDFNode::isObjectNode() const
  {return mpObject != NULL;}
