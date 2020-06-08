// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/copasi.h"

#include "CRDFGraph.h"

#include "CRDFSubject.h"
#include "CRDFObject.h"
#include "CRDFLiteral.h"
#include "CConstants.h"

CRDFNode::CRDFNode(CRDFGraph & graph):
  mGraph(graph),
  mId(""),
  mpSubject(NULL),
  mpObject(NULL),
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

CRDFObject & CRDFNode::getObject()
{
  if (mpObject == NULL)
    mpObject = new CRDFObject;

  return *mpObject;
}

const CRDFObject & CRDFNode::getObject() const
{
  if (mpObject == NULL)
    mpObject = new CRDFObject;

  return *mpObject;
}

CRDFPredicate::Path CRDFNode::getPath() const
{return mGraph.getPredicatePath(this);}

const std::string & CRDFNode::getFieldValue(const CRDFPredicate::ePredicateType & predicate) const
{
  static std::string Empty = "";

  const std::set< CRDFTriplet > Triplets = getDescendantsWithPredicate(predicate);

  if (Triplets.size() > 0)
    {
      const CRDFObject & Object = Triplets.begin()->pObject->getObject();

      switch (Object.getType())
        {
          case CRDFObject::LITERAL:
            return Object.getLiteral().getLexicalData();
            break;

          case CRDFObject::RESOURCE:
            return Object.getResource();
            break;

          case CRDFObject::BLANK_NODE:
            return Object.getBlankNodeID();
            break;
        }
    }

  return Empty;
}

bool CRDFNode::setFieldValue(const CMIRIAMResourceObject & value,
                             const CRDFPredicate::ePredicateType & predicate,
                             const CRDFPredicate::Path & nodePath)
{
  // If a node is associated with the resource we can just set the field value
  if (value.getNode() != NULL)
    return value.getNode()->setFieldValue(value.getURI(), predicate, nodePath);

  // We have no node and the value is invalid, i.e., nothing to do.
  if (!value.isValid())
    return true;

  // We need to create a node

  // We build each missing ancestor as a blank node.
  CRDFPredicate::sAllowedLocation const * pLocation = NULL;
  CRDFNode * pParent = createMissingAncestors(nodePath, predicate, pLocation);

  if (pParent == NULL) return false;

  // Create the missing object
  CRDFObject object;
  object.setType(CRDFObject::RESOURCE);
  object.setResource(value.getURI(), false);

  bool success = true;

  if (!mGraph.addTriplet(pParent->getSubject(), CRDFPredicate::getURI(predicate), object))
    success = false;

  return success;
}

bool CRDFNode::setFieldValue(const std::string & value,
                             const CRDFPredicate::ePredicateType & predicate,
                             const CRDFPredicate::Path & nodePath)
{
  std::set< CRDFTriplet > Triplets =
    getDescendantsWithPredicate(predicate);

  CRDFNode * pObject = NULL;

  if (Triplets.size() > 0)
    pObject = Triplets.begin()->pObject;

  // Check whether the value is not empty.
  if (value != "")
    {
      // We do not have an object
      if (pObject == NULL)
        {
          // We build each missing ancestor as a blank node.
          CRDFPredicate::sAllowedLocation const * pLocation = NULL;
          CRDFNode * pParent = createMissingAncestors(nodePath, predicate, pLocation);

          if (pParent == NULL) return false;

          // Create the missing object
          CRDFObject object;
          object.setType(pLocation->Type);

          if (object.getType() == CRDFObject::BLANK_NODE)
            object.setBlankNodeId(mGraph.generatedNodeId());

          CRDFTriplet Triplet =
            mGraph.addTriplet(pParent->getSubject(), CRDFPredicate::getURI(predicate), object);

          if (!Triplet)
            return false;

          pObject = Triplet.pObject;

          // Debugging
          assert(pObject != NULL);
        }

      // Now we finally can save the information.
      CRDFObject & Object = pObject->getObject();

      switch (Object.getType())
        {
          case CRDFObject::LITERAL:
          {
            CRDFLiteral & Literal = Object.getLiteral();
            Literal.setType(CRDFLiteral::PLAIN);
            Literal.setLexicalData(value);
          }
          break;

          case CRDFObject::RESOURCE:
            Object.setResource(value, false);
            break;

          case CRDFObject::BLANK_NODE:
            fatalError();
            break;
        }
    }
  else if (pObject != NULL)
    removeTripletFromGraph(*Triplets.begin());

  return true;
}

CRDFNode * CRDFNode::createMissingAncestors(const CRDFPredicate::Path & nodePath,
    const CRDFPredicate::ePredicateType & predicate,
    CRDFPredicate::sAllowedLocation const *& pLocation)
{
  pLocation = NULL;

  // If this is not a subject node we are not able to do anything.
  if (!isSubjectNode()) return NULL;

  // Determine the path leading to the field
  const CRDFPredicate::AllowedLocationList & Locations = CRDFPredicate::getAllowedLocationList(predicate);
  size_t i, imax = Locations.size();
  size_t SubPathIndex = C_INVALID_INDEX;

  for (i = 0; i < imax; i++)
    {
      // We ignore read only locations.
      if (Locations[i].ReadOnly)
        continue;

      SubPathIndex = CRDFPredicate::getSubPathIndex(Locations[i].Location, nodePath);

      if (SubPathIndex != C_INVALID_INDEX)
        break;
    }

  // The value can not be inserted
  if (SubPathIndex == C_INVALID_INDEX)
    return NULL;

  // Now we build each missing ancestor as a blank node.
  CRDFNode * pParent = createMissingAncestors(Locations[i].Location, SubPathIndex);

  if (pParent != NULL)
    pLocation = &Locations[i];

  return pParent;
}

CRDFNode * CRDFNode::createMissingAncestors(const CRDFPredicate::Path & predicatePath,
    const size_t & level)
{
  CRDFNode * pNode = this;

  size_t i, imax = predicatePath.size() - 1; // We only create the ancestors

  for (i = level; i < imax; i++)
    {
      std::set< CRDFTriplet > Triplets =
        getDescendantsWithPredicate(predicatePath[i]);

      // Check whether the predicate exists.
      if (Triplets.size() > 0)
        {
          pNode = Triplets.begin()->pObject;
        }
      else
        {
          CRDFObject object;
          object.setType(CRDFObject::BLANK_NODE);
          object.setBlankNodeId(mGraph.generatedNodeId());

          CRDFTriplet Triplet =
            mGraph.addTriplet(pNode->getSubject(), CRDFPredicate::getURI(predicatePath[i]), object);

          if (!Triplet)
            return NULL;
          else
            pNode = Triplet.pObject;
        }
    }

  return pNode;
}

CRDFTriplet CRDFNode::addEdge(const CRDFPredicate & predicate, CRDFNode * pObject)
{
  CRDFTriplet Failed;
  CRDFTriplet Triplet(this, predicate, pObject);

  // We do not want any duplicate triplets;
  if (mGraph.getTriplets().count(Triplet) > 0)
    return Failed;

  // If this is a bag node the only predicate allowed is rdf_li.
  if (isBagNode() && predicate != CRDFPredicate::rdf_li)
    return Failed;

  // If the predicate is rdf:li and this is not a bag node we bagify it.
  if (!isBagNode() && predicate == CRDFPredicate::rdf_li)
    {
      // Bagify the node.
      CRDFObject Object;
      Object.setType(CRDFObject::RESOURCE);
      Object.setResource("http://www.w3.org/1999/02/22-rdf-syntax-ns#Bag", false);

      if (!mGraph.addTriplet(this->getSubject(), CRDFPredicate(CRDFPredicate::rdf_type), Object))
        return Failed;
    }

  // We now can safely insert any edge with the predicate rdf_li
  if (predicate == CRDFPredicate::rdf_li)
    {
      if (!addTripletToGraph(Triplet))
        return Failed;

      return Triplet;
    }

  if (!addTripletToGraph(Triplet))
    return Failed;

  return Triplet;
}

bool
CRDFNode::removeEdge(const CRDFPredicate & predicate, CRDFNode * pObject)
{
  bool deletedSomething = false;
  // Determine whether the predicate points to a bag node
  std::set< CRDFTriplet > Triplets = mGraph.getTriplets(this, predicate);

  // Debugging
  assert(Triplets.size() > 0);

  CRDFNode * pTarget = Triplets.begin()->pObject;

  if (pTarget->isBagNode() && pTarget != pObject)
    {
      deletedSomething |= pTarget->removeEdge(CRDFPredicate::rdf_li, pObject);

      Triplets = mGraph.getTriplets(pTarget, CRDFPredicate::rdf_li);

      switch (Triplets.size())
        {
          case 0:
            // If pTarget is an empty bag node we remove it.
            // Note, this will destroy pTarget, i.e., no need to unbag
            deletedSomething |= removeEdge(predicate, pTarget);
            break;

          default:
            // We have more than 1 rdf_li element left.
            break;
        }

      return deletedSomething;
    }

  deletedSomething |= removeTripletFromGraph(CRDFTriplet(this, predicate, pObject));

  return deletedSomething;
}

std::set< CRDFTriplet > CRDFNode::getDescendantsWithPredicate(const CRDFPredicate & predicate) const
{
  std::set< CRDFTriplet > Triplets;
  CRDFPredicate::Path NodePath = mGraph.getPredicatePath(this);

  std::set< CRDFTriplet > Predicates = mGraph.getTriplets(predicate);
  std::set< CRDFTriplet >::const_iterator it = Predicates.begin();
  std::set< CRDFTriplet >::const_iterator end = Predicates.end();

  for (; it != end; ++it)
    if (it->pObject->hasAncestor(this))
      Triplets.insert(*it);

  return Triplets;
}

bool CRDFNode::isSubjectNode() const
{return mpSubject != NULL;}

bool CRDFNode::isObjectNode() const
{return mpObject != NULL;}

bool CRDFNode::isBlankNode() const
{return mIsBlankNode;}

bool CRDFNode::isBagNode() const
{
  std::set< CRDFTriplet > Triplets = mGraph.getTriplets(this, CRDFPredicate::rdf_type);
  std::set< CRDFTriplet >::const_iterator it = Triplets.begin();
  std::set< CRDFTriplet >::const_iterator end = Triplets.end();

  for (; it != end; ++it)
    if (Triplets.begin()->pObject->getObject().getResource() == "http://www.w3.org/1999/02/22-rdf-syntax-ns#Bag")
      return true;

  return false;
}

bool CRDFNode::isReadOnly() const
{
  CRDFPredicate::Path NodePath = mGraph.getPredicatePath(this);
  return CRDFPredicate::isReadOnly(NodePath);
}

bool CRDFNode::hasAncestor(const CRDFNode * pNode) const
{
  // We consider each node to be its own ancestor.
  if (pNode == this)
    return true;

  bool hasAncestor = false;

  std::set< const CRDFNode * > Parents = mGraph.getParentSubjects(this);
  std::set< const CRDFNode * >::const_iterator it = Parents.begin();
  std::set< const CRDFNode * >::const_iterator end = Parents.end();

  for (; it != end && !hasAncestor; ++it)
    hasAncestor = (*it)->hasAncestor(pNode);

  return hasAncestor;
}
