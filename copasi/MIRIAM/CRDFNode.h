// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFNode.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/04 17:39:32 $
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

#include "MIRIAM/CRDFEdge.h"

class CRDFSubject;
class CRDFObject;

class CRDFNode
  {
  public:
    typedef std::multimap< std::string, CRDFNode * > multimap;
    typedef std::multimap< std::string, CRDFNode * >::iterator iterator;
    typedef std::multimap< std::string, CRDFNode * >::const_iterator const_iterator;
    typedef std::multimap< std::string, CRDFNode * >::value_type value_type;

    // Operations
  public:
    /**
     * Default Constructor
     */
    CRDFNode();

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
     * @return const CRDFObject & object
     */
    const CRDFObject & getObject() const;

    /**
     * Add a property edge to the node
     * @param const std::string & predicate
     * @param CRDFNode * pObject
     */
    void addEdge(const std::string & predicate, CRDFNode * pObject);

    /**
     * Remove a property edge from the node, if no object node is
     * given all object nodes with the predicate are removed.
     * @param const std::string & predicate
     * @param CRDFNode * pObject (default: NULL)
     * @return std::string success
     */
    bool removeEdge(const std::string & predicate, CRDFNode * pObject = NULL);

    /**
     * Retrieve the property edges of the node
     * @return const CRDFNode::multimap & edges
     */
    const multimap & getEdges() const;

    /**
     * Retreive all object nodes with the given predicate
     * @param const std::string & predicate
     * @return std::pair<CRDFNode::iterator, CRDFNode::iterator> objectNodes
     */
    std::pair< iterator, iterator > getObjectNodes(const std::string & predicate);

    /**
     * Retreive all object nodes with the given predicate
     * @param const std::string & predicate
     * @return std::pair<CRDFNode::const_iterator, CRDFNode::const_iterator> objectNodes
     */
    std::pair< const_iterator, const_iterator > getObjectNodes(const std::string & predicate) const;

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
     * Check whether this is a Blank node
     * @return bool isBlankNode
     */
    bool isBlankNode() const;

    // Attributes
  private:
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
