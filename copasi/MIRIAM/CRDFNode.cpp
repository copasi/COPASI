// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFNode.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/02/08 23:06:53 $
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
{
  assert(pObject != NULL);
  mEdges.insert(value_type(predicate, pObject));
}

bool CRDFNode::removeEdge(const std::string & predicate,
                          CRDFNode * pObject)
{
  std::pair<iterator, iterator> Range = mEdges.equal_range(predicate);

  // Predicate not found;
  if (Range.first == Range.second)
    return false;

  // Delete all edges
  if (pObject == NULL)
    {
      mEdges.erase(Range.first, Range.second);
      return true;
    }

  // Delete specific edge
  for (; Range.first != Range.second; Range.second++)
    {
      if (Range.first->second == pObject)
        {
          mEdges.erase(Range.first);
          return true;
        }
    }

  return false;
}

const CRDFNode::multimap & CRDFNode::getEdges() const
  {return mEdges;}

bool CRDFNode::edgeExists(const std::string predicate) const
  {
    std::pair<const_iterator, const_iterator> Range = mEdges.equal_range(predicate);

    // Predicate not found;
    if (Range.first == Range.second)
    {return false;}
    return true;
  }

std::pair< CRDFNode::iterator, CRDFNode::iterator > CRDFNode::getObjectNodes(const std::string & predicate)
{return mEdges.equal_range(predicate);}

std::pair< CRDFNode::const_iterator, CRDFNode::const_iterator > CRDFNode::getObjectNodes(const std::string & predicate) const
  {return mEdges.equal_range(predicate);}

bool CRDFNode::isSubjectNode() const
  {return mpSubject != NULL;}

bool CRDFNode::isObjectNode() const
  {return mpObject != NULL;}

bool CRDFNode::isBlankNode() const
  {return mIsBlankNode;}
