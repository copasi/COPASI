// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFNode.h,v $
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

#ifndef COPASI_CRDFNode
#define COPASI_CRDFNode

#include <string>
#include <map>
#include <vector>
#include <set>

#include "copasi/MIRIAM/CRDFEdge.h"
#include "copasi/MIRIAM/CRDFGraph.h"

class CRDFSubject;
class CRDFObject;
class CMIRIAMResource;

class CRDFNode
  {
  public:
    typedef std::multimap< CRDFPredicate::ePredicateType, CRDFEdge > multimap;
    typedef std::multimap< CRDFPredicate::ePredicateType, CRDFEdge >::iterator iterator;
    typedef std::multimap< CRDFPredicate::ePredicateType, CRDFEdge >::const_iterator const_iterator;
    typedef std::multimap< CRDFPredicate::ePredicateType, CRDFEdge >::value_type value_type;

    // Operations
  private:
    /**
     * Default Constructor
     */
    CRDFNode();

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
     * @param const CRDFPredicate::Path & nodePath
     * @param const CRDFGraph::CTriplet & parentTriplet
     * @return const std::string & fieldValue
     */
    const std::string & getFieldValue(const CRDFPredicate::ePredicateType & predicate,
                                      const CRDFPredicate::Path & nodePath,
                                      const CRDFTriplet & parentTriplet) const;

    /**
     * Set the field value for the property predicate
     * @param const CMIRIAMResource & value
     * @param const CRDFPredicate::ePredicateType & predicate
     * @param const CRDFPredicate::Path & nodePath
     * @param const CRDFTriplet & parentTriplet
     * @return bool success
     */
    bool setFieldValue(const CMIRIAMResource & value,
                       const CRDFPredicate::ePredicateType & predicate,
                       const CRDFPredicate::Path & nodePath,
                       const CRDFTriplet & parentTriplet);

    /**
     * Set the field value for the property predicate
     * @param const std::string & value
     * @param const CRDFPredicate::ePredicateType & predicate
     * @param const CRDFPredicate::Path & nodePath
     * @param const CRDFTriplet & parentTriplet
     * @return bool success
     */
    bool setFieldValue(const std::string & value,
                       const CRDFPredicate::ePredicateType & predicate,
                       const CRDFPredicate::Path & nodePath,
                       const CRDFTriplet & parentTriplet);

    /**
     * Add a property edge to the node.
     * @param const CRDFEdge & edge
     * @return bool success
     */
    bool addEdgeInternal(const CRDFEdge & edge);

    /**
     * Remove a property edge from the node.
     * @param const CRDFEdge & edge
     * @return std::string success
     */
    bool removeEdgeInternal(const CRDFEdge & edge);

    /**
     * Retrieve the property edges of the node
     * @return const CRDFNode::multimap & edges
     */
    const multimap & getEdges() const;

    /**
     * Retreive all object nodes with the given predicate
     * @param const CRDFPredicate::ePredicateType & predicate
     * @return std::pair<CRDFNode::iterator, CRDFNode::iterator> edges
     */
    std::pair< iterator, iterator > getEdgesWithPredicate(const CRDFPredicate::ePredicateType & predicate);

    /**
     * Retreive all object nodes with the given predicate
     * @param const CRDFPredicate::ePredicateType & predicate
     * @return std::pair<CRDFNode::const_iterator, CRDFNode::const_iterator> edges
     */
    std::pair< const_iterator, const_iterator > getEdgesWithPredicate(const CRDFPredicate::ePredicateType & predicate) const;

    /**
     * Retreive all supported triplets with the given predicate which are reachable from this node.
     * @param const CRDFPredicate::ePredicateType & predicate
     * @param const CRDFPredicate::Path & nodePath,
     * @param const CRDFTriplet & parentTriplet
     * @return std::set< CRDFTriplet >
     */
    std::set< CRDFTriplet > getTripletsWithPredicate(const CRDFPredicate::Path & nodePath,
        const CRDFPredicate::ePredicateType & predicate,
        const CRDFTriplet & parentTriplet) const;

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

  private:
    void getTripletsWithPredicate(const CRDFPredicate::Path & predicatePath,
                                  unsigned C_INT32 level,
                                  std::set< CRDFTriplet > & triplets,
                                  std::set< const CRDFNode * > visited,
                                  const CRDFNode * pParent) const;

    CRDFNode * createMissingAncestors(const CRDFPredicate::Path & nodePath,
                                      const CRDFPredicate::ePredicateType & predicate,
                                      CRDFPredicate::sAllowedLocation const *& pLocation,
                                      const CRDFTriplet & parentTriplet);

    CRDFNode * createMissingAncestors(const CRDFPredicate::Path & predicatePath,
                                      const unsigned C_INT32 & level,
                                      const CRDFPredicate::Path & nodePath,
                                      const CRDFTriplet & parentTriplet);

    bool removeEmptyAncestors(const CRDFPredicate::Path & predicatePath,
                              const unsigned C_INT32 & level,
                              const CRDFPredicate::Path & nodePath,
                              const CRDFTriplet & parentTriplet);

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
     * A map between the predicates and property nodes
     */
    multimap mEdges;

    /**
     * Stores whether this is a blank node
     */
    bool mIsBlankNode;
  };

#endif // COPASI_CRDFNode
