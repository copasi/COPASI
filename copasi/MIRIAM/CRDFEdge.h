// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/Attic/CRDFEdge.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/03 13:20:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CRDFEdge
#define COPASI_CRDFEdge

#include <string>

#include "copasi/MIRIAM/CRDFPredicate.h"

class CRDFNode;

class CRDFEdge
  {
    // Operations
  private:
    /**
     * Default Constructor
     */
    CRDFEdge();

  public:
    /**
     * Copy Constructor
     * @param const CRDFEdge & src
     */
    CRDFEdge(const CRDFEdge & src);

    /**
     * Specific Constructor
     * @param const CRDFPredicate::ePredicateType & predicate
     * @param const CRDFNode * pPropertyNode
     */
    CRDFEdge(const CRDFPredicate::ePredicateType & predicate,
             const CRDFNode * pPropertyNode);

    /**
     * Specific Constructor
     * @param const std::string & predicateURI
     * @param const CRDFNode * pPropertyNode
     */
    CRDFEdge(const std::string & predicateURI,
             const CRDFNode * pPropertyNode);
    /**
     * Destructor
     */
    virtual ~CRDFEdge();

    /**
     * Set the URI describing the predicate of the edge
     * @param const CRDFPredicate::ePredicateType & predicate
     */
    void setPredicate(const CRDFPredicate::ePredicateType & predicate);

    /**
     * Retrieve the predicate of the of the edge
     * @return const CRDFPredicate::ePredicateType & predicate
     */
    const CRDFPredicate::ePredicateType & getPredicate() const;

    /**
     * Set the URI describing the predicate of the edge
     * @param const std::string & predicateURI
     */
    void setPredicateURI(const std::string & predicateURI);

    /**
     * Retrieve the predicate of the of the edge
     * @return const std::string & predicateURI
     */
    const std::string & getPredicateURI() const;

    /**
     * Set the pointer to the property node
     * @param CRDFNode * pPropertyNode
     */
    void setPropertyNode(const CRDFNode * pPropertyNode);

    /**
     * Retrieve the pointer to the property node
     * @return const CRDFNode * pPropertyNode
     */
    const CRDFNode * getPropertyNode() const;

    /**
     * Comparison operator
     * @param const CRDFEdge & rhs
     * @return bool operator isEqual
     */
    bool operator == (const CRDFEdge & rhs) const;

    // Attributes
  private:
    /**
     * The prdicate of the edge
     */
    CRDFPredicate::ePredicateType mPredicate;

    /**
     * The URI predicate of the edge
     */
    std::string mPredicateURI;

    /**
     * A pointer to the property node
     */
    const CRDFNode * mpPropertyNode;
  };

#endif // COPASI_CRDFEdge
