// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFNode.cpp,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/05 15:34:56 $
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
#include "CConstants.h"

CRDFNode::CRDFNode(CRDFGraph & graph):
    mGraph(graph),
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

const std::string & CRDFNode::getFieldValue(const CRDFPredicate::ePredicateType & predicate,
    const CRDFPredicate::Path & nodePath,
    const CRDFTriplet & parentTriplet) const
  {
    static std::string Empty = "";

    const std::set< CRDFTriplet > Triplets =
      getTripletsWithPredicate(nodePath, predicate, parentTriplet);

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

bool CRDFNode::setFieldValue(const CMIRIAMResource & value,
                             const CRDFPredicate::ePredicateType & predicate,
                             const CRDFPredicate::Path & nodePath,
                             const CRDFTriplet & parentTriplet)
{
  // If a node is associated with the resource we can just set the field value
  if (value.getNode() != NULL)
    return value.getNode()->setFieldValue(value.getURI(), predicate, nodePath, parentTriplet);

  // We have no node and the value is invalid, i.e., nothing to do.
  if (!value.isValid())
    return true;

  // We need to create a node

  // We build each missing ancestor as a blank node.
  CRDFPredicate::sAllowedLocation const * pLocation = NULL;
  CRDFNode * pParent = createMissingAncestors(nodePath, predicate, pLocation, parentTriplet);
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
                             const CRDFPredicate::Path & nodePath,
                             const CRDFTriplet & parentTriplet)
{
  std::set< CRDFTriplet > Triplets =
    getTripletsWithPredicate(nodePath, predicate, parentTriplet);

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
          CRDFNode * pParent = createMissingAncestors(nodePath, predicate, pLocation, parentTriplet);
          if (pParent == NULL) return false;

          // Create the missing object
          CRDFObject object;
          object.setType(pLocation->Type);
          if (object.getType() == CRDFObject::BLANK_NODE)
            object.setBlankNodeId(mGraph.generatedBlankNodeId());

          CRDFTriplet Triplet =
            mGraph.addTriplet(pParent->getSubject(), CRDFPredicate::getURI(predicate), object);
          if (!Triplet)
            return false;

          pObject = Triplet.pObject;

          // Debugging
          assert(pObject != NULL);
        }
      else if (pObject->isReadOnly())
        {
          // If this is not a subject node we are not able to do anything.
          if (!isSubjectNode()) return false;

          // Determine the path leading to the field
          const CRDFPredicate::AllowedLocationList & Locations = CRDFPredicate::getAllowedLocationList(predicate);
          unsigned C_INT32 i, imax = Locations.size();
          unsigned C_INT32 SubPathIndex = C_INVALID_INDEX;
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
            return false;

          // Now we build each missing ancestor as a blank node.
          CRDFNode * pParent = createMissingAncestors(Locations[i].Location, SubPathIndex, nodePath, parentTriplet);
          if (pParent == NULL) return false;

          // We move the object to the new location.
          if (!mGraph.moveEdge(Triplets.begin()->pSubject, pParent, CRDFEdge(predicate, pObject)))
            return false;
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
          Object.setResource(value, false);
          break;
        }
    }
  else if (pObject != NULL)
    {
      mGraph.removeTriplet(this, CRDFPredicate::getURI(predicate), pObject);

      // Delete obsolete parent objects
      // Determine the path leading to the field
      const CRDFPredicate::AllowedLocationList & Locations = CRDFPredicate::getAllowedLocationList(predicate);
      unsigned C_INT32 i, imax = Locations.size();
      unsigned C_INT32 SubPathIndex = C_INVALID_INDEX;
      for (i = 0; i < imax; i++)
        {
          SubPathIndex = CRDFPredicate::getSubPathIndex(Locations[i].Location, nodePath);
          if (SubPathIndex != C_INVALID_INDEX)
            break;
        }

      // Since we had an object this should never happen.
      if (SubPathIndex == C_INVALID_INDEX)
        return false;

      // Now we remove each empty ancestor.
      if (!removeEmptyAncestors(Locations[i].Location, SubPathIndex, nodePath, parentTriplet))
        return false;
    }

  return true;
}

CRDFNode * CRDFNode::createMissingAncestors(const CRDFPredicate::Path & nodePath,
    const CRDFPredicate::ePredicateType & predicate,
    CRDFPredicate::sAllowedLocation const *& pLocation,
    const CRDFTriplet & parentTriplet)
{
  pLocation = NULL;

  // If this is not a subject node we are not able to do anything.
  if (!isSubjectNode()) return NULL;

  // Determine the path leading to the field
  const CRDFPredicate::AllowedLocationList & Locations = CRDFPredicate::getAllowedLocationList(predicate);
  unsigned C_INT32 i, imax = Locations.size();
  unsigned C_INT32 SubPathIndex = C_INVALID_INDEX;
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
  CRDFNode * pParent = createMissingAncestors(Locations[i].Location, SubPathIndex, nodePath, parentTriplet);

  if (pParent != NULL)
    pLocation = &Locations[i];

  return pParent;
}

CRDFNode * CRDFNode::createMissingAncestors(const CRDFPredicate::Path & predicatePath,
    const unsigned C_INT32 & level,
    const CRDFPredicate::Path & nodePath,
    const CRDFTriplet & parentTriplet)
{
  CRDFNode * pNode = this;

  unsigned C_INT32 i, imax = predicatePath.size() - 1; // We only create the ancestors
  for (i = level; i < imax; i++)
    {
      std::set< CRDFTriplet > Triplets =
        getTripletsWithPredicate(nodePath, predicatePath[i], parentTriplet);

      // Check whether the predicate exists.
      if (Triplets.size() > 0)
        {
          pNode = Triplets.begin()->pObject;
        }
      else
        {
          CRDFObject object;
          object.setType(CRDFObject::BLANK_NODE);
          object.setBlankNodeId(mGraph.generatedBlankNodeId());

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

bool CRDFNode::removeEmptyAncestors(const CRDFPredicate::Path & predicatePath,
                                    const unsigned C_INT32 & level,
                                    const CRDFPredicate::Path & nodePath,
                                    const CRDFTriplet & parentTriplet)
{
  std::set< CRDFTriplet > Triplets;
  std::set< CRDFTriplet >::const_iterator it;
  unsigned C_INT32 i;

  // We only create the ancestors
  for (i = predicatePath.size() - 1; i >= level; i--)
    {
      Triplets = getTripletsWithPredicate(nodePath, predicatePath[i], parentTriplet);
      if (Triplets.size() > 0 &&
          (it = Triplets.begin())->pObject->getEdges().size() == 0)
        if (!mGraph.removeTriplet(it->pSubject, CRDFPredicate::getURI(it->Predicate), it->pObject))
          return false;
    }

  return true;
}

bool CRDFNode::addEdgeInternal(const CRDFEdge & edge)
{
  std::pair<iterator, iterator> Range;

  // If this is a bag node the only predicate allowed is rdf:li.
  // This also prevents a duplicate type bag.
  if (isBagNode() &&
      edge.getPredicate() != CRDFPredicate::rdf_li)
    return false;

  // If the predicate is rdf:li we should check whether the node is a bag node, however the
  // order of edges can not be guarantied
  // if (!isBagNode() &&
  //     edge.getPredicate() == CRDFPredicate::rdf_li)
  //   return false;

  // We need to make sure that we have no duplicate edges;
  Range = mEdges.equal_range(edge.getPredicate());

  for (; Range.first != Range.second; ++Range.first)
    if (edge == Range.first->second) break;

  // We found an existing edge with the same predicate and object.
  if (Range.first != Range.second)
    return false;

  if (isBagNode() ||
      edge.getPredicate() == CRDFPredicate::rdf_li)
    {
      // We have already checked that this is a rdf:li edge, i.e.,
      // we can savely insert the edge.
      mEdges.insert(value_type(edge.getPredicate(), edge));
      return true;
    }

  // Check whether the predicate exists
  Range = mEdges.equal_range(edge.getPredicate());
  if (Range.first != Range.second)
    {
      const CRDFNode * pNode = Range.first->second.getPropertyNode();

      // Is it already a bag node.
      if (!pNode->isBagNode())
        {
          // Remember the existing edge with the predicate.
          CRDFEdge ExistingEdge = Range.first->second;

          // Remove the existing edge locally. All objects are preserved
          mEdges.erase(Range.first);

          // Debugging: assure that no more edges with the predicate exist.
          assert(mEdges.count(edge.getPredicate()) == 0);

          // Insert a triplet into the graph
          CRDFObject Object;
          Object.setType(CRDFObject::BLANK_NODE);
          Object.setBlankNodeId(mGraph.generatedBlankNodeId());

          mGraph.addTriplet(getSubject(), edge.getPredicateURI(), Object);

          Range = mEdges.equal_range(edge.getPredicate());
          // Debugging: assure that we have exactly one edge with the predicate.
          assert(Range.first != Range.second);
          pNode = Range.first->second.getPropertyNode();

          Object.setType(CRDFObject::RESOURCE);
          Object.setResource("http://www.w3.org/1999/02/22-rdf-syntax-ns#Bag", false);

          // set the rdf:type of the newly created node to rdf:Bag
          mGraph.addTriplet(pNode->getSubject(), CRDFPredicate::getURI(CRDFPredicate::rdf_type), Object);

          // Add the existing edge to the bag node.
          ExistingEdge.setPredicate(CRDFPredicate::rdf_li);
          const_cast< CRDFNode * >(pNode)->addEdgeInternal(ExistingEdge);
        }

      // pNode points to a bag node we therefore can insert an edge with predicate rdf:li
      CRDFEdge Edge(edge);
      Edge.setPredicate(CRDFPredicate::rdf_li);
      return const_cast< CRDFNode * >(pNode)->addEdgeInternal(Edge);
    }

  mEdges.insert(value_type(edge.getPredicate(), edge));
  return true;
}

bool CRDFNode::removeEdgeInternal(const CRDFEdge & edge)
{
  bool success = true;
  // Find all edges with the same predicate;
  std::pair<iterator, iterator> Range = mEdges.equal_range(edge.getPredicate());

  // Predicate not found;
  if (Range.first == Range.second)
    return false;

  // Check whether the edge points to a bag node
  if (Range.first->second.getPropertyNode()->isBagNode())
    {
      CRDFEdge Edge(edge);
      Edge.setPredicate(CRDFPredicate::rdf_li);
      success &= const_cast< CRDFNode * >(Range.first->second.getPropertyNode())->removeEdgeInternal(Edge);

      if (success)
        {
          // If the bag is empty we remove it too
          std::pair< CRDFNode::const_iterator, CRDFNode::const_iterator > Bag =
            Range.first->second.getPropertyNode()->getEdgesWithPredicate(CRDFPredicate::rdf_li);
          if (Bag.first == Bag.second)
            success &= mGraph.removeTriplet(this,
                                            Range.first->second.getPredicateURI(),
                                            Range.first->second.getPropertyNode());

          return true;
        }
    }

  for (; Range.first != Range.second; ++Range.first)
    if (edge == Range.first->second)
      {
        mEdges.erase(Range.first);
        return true;
      }

  return false;
}

const CRDFNode::multimap & CRDFNode::getEdges() const
  {return mEdges;}

std::pair< CRDFNode::iterator, CRDFNode::iterator > CRDFNode::getEdgesWithPredicate(const CRDFPredicate::ePredicateType & predicate)
{return mEdges.equal_range(predicate);}

std::pair< CRDFNode::const_iterator, CRDFNode::const_iterator > CRDFNode::getEdgesWithPredicate(const CRDFPredicate::ePredicateType & predicate) const
  {return mEdges.equal_range(predicate);}

bool CRDFNode::isSubjectNode() const
  {return mpSubject != NULL;}

bool CRDFNode::isObjectNode() const
  {return mpObject != NULL;}

bool CRDFNode::isBlankNode() const
  {return mIsBlankNode;}

bool CRDFNode::isBagNode() const
  {
    std::pair<const_iterator, const_iterator> Range = mEdges.equal_range(CRDFPredicate::rdf_type);

    // Note, this assumes that we only have rdf:type attribute.
    if (Range.first != Range.second &&
        Range.first->second.getPropertyNode()->getObject().getResource() ==
        "http://www.w3.org/1999/02/22-rdf-syntax-ns#Bag")
      return true;
    else
      return false;
  }

bool CRDFNode::isReadOnly() const
  {
    CRDFPredicate::Path NodePath = mGraph.getPredicatePath(this);
    return CRDFPredicate::isReadOnly(NodePath);
  }

std::set< CRDFTriplet > CRDFNode::getTripletsWithPredicate(const CRDFPredicate::Path & nodePath,
    const CRDFPredicate::ePredicateType & predicate,
    const CRDFTriplet & parentTriplet) const
  {
    std::set< CRDFTriplet > Triplets;

    // The current node cannot be accessed through any path.
    if (nodePath.size() == 0)
      return Triplets;

    // First retreive all absolute pathes which lead to the desired predicate.
    const CRDFPredicate::AllowedLocationList & PathList =
      CRDFPredicate::getAllowedLocationList(predicate);

    unsigned C_INT32 i, imax = PathList.size();
    unsigned C_INT32 SubPathIndex;
    for (i = 0; i < imax; i++)
      {
        std::set< const CRDFNode * > Visited;
        const CRDFPredicate::Path & Path = PathList[i].Location;

        SubPathIndex = CRDFPredicate::getSubPathIndex(Path, nodePath);
        std::cout << "Index: " << SubPathIndex << std::endl;

        // We need to remove the predicate pathes, which do not go through this node.
        if (SubPathIndex == C_INVALID_INDEX)
          continue;

        // Check whether we are at right object.
        if (SubPathIndex == Path.size())
          {
            // This means that we have the correct predicate.
            if (isBagNode())
              {
                // If this is a bag node we need to add all li elements.
                // This is done by calling getTripletsWithPredicate with the current level.
                getTripletsWithPredicate(Path, SubPathIndex - 1, Triplets, Visited, parentTriplet.pSubject);
              }
            else
              Triplets.insert(parentTriplet);
          }
        else
          {
            // We are now sure that the PredicatePath is the same as the nodePath for
            // (SubPathIndex - 1) predicates. We travers the tree starting with the
            // remaining predicate path.
            getTripletsWithPredicate(Path, SubPathIndex, Triplets, Visited, NULL);
          }
      }

    return Triplets;
  }

void CRDFNode::getTripletsWithPredicate(const std::vector < CRDFPredicate::ePredicateType > & predicatePath,
                                        unsigned C_INT32 level,
                                        std::set< CRDFTriplet > & triplets,
                                        std::set< const CRDFNode * > visited,
                                        const CRDFNode * pParent) const
  {
    // We need to avoid endless loops with the help of visited.
    std::pair< std::set< const CRDFNode * >::iterator, bool > Insert;

    // We need to iterate over the edges matching predicate
    std::pair< const_iterator, const_iterator > Range;
    CRDFPredicate::ePredicateType Predicate = predicatePath[level];

    if (isBagNode())
      Predicate = CRDFPredicate::rdf_li;

    Range = getEdgesWithPredicate(Predicate);

    const CRDFNode * pNext;
    for (; Range.first != Range.second; ++Range.first)
      {
        pNext = Range.first->second.getPropertyNode();

        // Check whether we have allready visited this node.
        Insert = visited.insert(pNext);
        if (!Insert.second) return;

        std::cout << predicatePath.size() << std::endl;

        if (pNext->isBagNode())
          pNext->getTripletsWithPredicate(predicatePath, level, triplets, visited, this);
        else if (level == predicatePath.size() - 1)
          {
            if (Predicate == CRDFPredicate::rdf_li)
              triplets.insert(CRDFTriplet(const_cast< CRDFNode * >(pParent),
                                          predicatePath[level],
                                          const_cast< CRDFNode * >(pNext)));
            else
              triplets.insert(CRDFTriplet(const_cast< CRDFNode * >(this),
                                          predicatePath[level],
                                          const_cast< CRDFNode * >(pNext)));
          }
        else
          pNext->getTripletsWithPredicate(predicatePath, level + 1, triplets, visited, NULL);
      }

    return;
  }
