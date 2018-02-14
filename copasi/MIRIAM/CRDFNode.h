// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFNode.h,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/07/16 19:00:06 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CRDFNode
#define COPASI_CRDFNode

#include <string>
#include <map>
#include <vector>
#include <set>

#include "copasi/MIRIAM/CRDFPredicate.h"

class CRDFGraph;
class CRDFSubject;
class CRDFObject;
class CMIRIAMResourceObject;

class CRDFNode
{
  // Operations
private:
  /**
   * Default Constructor
   */
  CRDFNode();

  CRDFNode(const CRDFNode & CRDFNode);

  CRDFNode & operator = (const CRDFNode & rhs);

public:
  /**
   * Specific Constructor
   * @param CRDFGraph & graph
   */
  CRDFNode(CRDFGraph & graph);

  /**
   * Destructor
   */
  ~CRDFNode();

  /**
   * Set the Id of the node
   * @param const std::string & id
   */
  void setId(const std::string & id);

  /**
   * Retrieve the Id of the node
   * @return const std::string & id
   */
  const std::string & getId() const;

  /**
   * Set the subject data of the node
   * @param const CRDFSubject & subject
   */
  void setSubject(const CRDFSubject & subject);

  /**
   * Retrieve the subject data of the node. It is recommended to
   * call isSubjectNode before retrieving the subject.
   * @return const CRDFSubject & subject
   */
  const CRDFSubject & getSubject() const;

  /**
   * Set the object data of the node
   * @param const CRDFObject & object
   */
  void setObject(const CRDFObject & object);

  /**
   * Retrieve the object data of the node. It is recommended to
   * call isObjectNode before retrieving the object.
   * @return CRDFObject & object
   */
  CRDFObject & getObject();

  /**
   * Retrieve the object data of the node. It is recommended to
   * call isObjectNode before retrieving the object.
   * @return const CRDFObject & object
   */
  const CRDFObject & getObject() const;

  /**
   * Retrieve a predicate path to the node.
   * @return CRDFPredicate::Path path
   */
  CRDFPredicate::Path getPath() const;

  /**
   * Retrieve the string representation of the property predicate
   * @param const CRDFPredicate::ePredicateType & predicate
  * @return const std::string & fieldValue
   */
  const std::string & getFieldValue(const CRDFPredicate::ePredicateType & predicate) const;

  /**
   * Set the field value for the property predicate
   * @param const CMIRIAMResource & value
   * @param const CRDFPredicate::ePredicateType & predicate
   * @param const CRDFPredicate::Path & nodePath
   * @return bool success
   */
  bool setFieldValue(const CMIRIAMResourceObject & value,
                     const CRDFPredicate::ePredicateType & predicate,
                     const CRDFPredicate::Path & nodePath);

  /**
   * Set the field value for the property predicate
   * @param const std::string & value
   * @param const CRDFPredicate::ePredicateType & predicate
   * @param const CRDFPredicate::Path & nodePath
   * @return bool success
   */
  bool setFieldValue(const std::string & value,
                     const CRDFPredicate::ePredicateType & predicate,
                     const CRDFPredicate::Path & nodePath);

  /**
   * Add a property edge to the node.
   * @param const CRDFPredicate & edge
   * @param CRDFNode * pObject
   * @return CRDFTriplet triplet
   */
  CRDFTriplet addEdge(const CRDFPredicate & predicate, CRDFNode * pObject);

  /**
   * This method is for internal use only.
   * The method is declared public since friend declarations may not refer to public methods.
   * @param const CRDFTriplet & triplet
   * @return bool success.
   */
  bool addTripletToGraph(const CRDFTriplet & triplet) const;

  /**
   * Remove a property edge from the node.
   * @param const CRDFPredicate & edge
   * @param CRDFNode * pObject
   * @return true, if an element was deleted, false otherwise
   */
  bool removeEdge(const CRDFPredicate & predicate, CRDFNode * pObject);

  /**
   * This method is for internal use only.
   * The method is declared public since friend declarations may not refer to public methods.
   * @param const CRDFTriplet & triplet
   * @return true, if an element was deleted, false otherwise
   */
  bool removeTripletFromGraph(const CRDFTriplet & triplet) const;

  /**
   *
   *
   */
  std::set< CRDFTriplet > getDescendantsWithPredicate(const CRDFPredicate & predicate) const;

  /**
   * Check whether this is a subject node
   * @return bool isSubjectNode
   */
  bool isSubjectNode() const;

  /**
   * Check whether this is a object node
   * @return bool isObjectNode
   */
  bool isObjectNode() const;

  /**
   * Check whether this is a blank node
   * @return bool isBlankNode
   */
  bool isBlankNode() const;

  /**
   * Check whether this is a bag node
   * @return isBagNode
   */
  bool isBagNode() const;

  /**
   * Check whether the node is read only
   * @return bool isReadOnly
   */
  bool isReadOnly() const;

  /**
   * Check whether the given node is in the path, i.e., has the given node
   * as an ancestor
   * @param const CRDFNode * pNode
   * @return bool hasAncestor
   */
  bool hasAncestor(const CRDFNode * pNode) const;

private:
  CRDFNode * createMissingAncestors(const CRDFPredicate::Path & nodePath,
                                    const CRDFPredicate::ePredicateType & predicate,
                                    CRDFPredicate::sAllowedLocation const *& pLocation);

  CRDFNode * createMissingAncestors(const CRDFPredicate::Path & predicatePath,
                                    const size_t & level);

  // Attributes
private:
  /**
   * The graph in which the node is located.
   */
  CRDFGraph & mGraph;

  /**
   * The Id of the node
   */
  std::string mId;

  /**
   * A pointer to the subject if of type SUBJECT or BOTH
   */
  mutable CRDFSubject * mpSubject;

  /**
   * A pointer to the object if of type OBJECT or BOTH
   */
  mutable CRDFObject * mpObject;

  /**
   * Stores whether this is a blank node
   */
  bool mIsBlankNode;
};

#endif // COPASI_CRDFNode
